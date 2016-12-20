(function ($) {
  "use strict";

  // This code may appear on pages without any calendar, thus without any
  // other js from this module: assure Drupal.availabilityCalendar is defined.
  Drupal.availabilityCalendar = Drupal.availabilityCalendar || {};

  /**
   * Couples the 2 inputs via the data attributes data-date-range-end and
   * data-date-range-start so that they point to each other. This will turn the
   * datepicker into a date range picker.
   *
   * However, this is not enough:
   * - Leave from date_popup.js ()date module) as is: we want to show the date
   *   picker on click or focus on the 1st date.
   * - Undo from date_popup.js (date module): we do not want to the 2nd date to
   *   get its own date picker. As the date_popup attach behavior may or may not
   *   already have run we will both have to unbind the focus event from
   *   date_popup (has already run) and remove the date popup object for th 2nd
   *   date from the Drupal.settings.datePopup object.
   *   
   * - We want the date picker of the 1st date to show on click or focus on the
   *   2nd date.
   *
   * @param {HTMLInputElement} dateField1
   * @param {HTMLInputElement} dateField2
   * @param {Object} datePopups
   */
  Drupal.availabilityCalendar.dateRangePicker = function (dateField1, dateField2, datePopups) {
    /**
     * @type {?string}
     *   The id of the element whose focus handler is being executed. This is
     *   used to prevent endless recursion.
     */
    var handling = null;

    $(dateField1).attr("data-date-range-end", "#" + dateField2.id);
    $(dateField2).attr("data-date-range-start", "#" + dateField1.id);

    // If date_popup attach behavior has already run:
    //   Unbind focus event from 2nd date as set by date_popup.js: this is not
    //   name-spaced, so only way to do so is by unbinding ALL focus handlers.
    //   (This should also unbind our own event handlers when this page uses
    //   ajax refreshing.)
    $(dateField2).unbind("focus").unbind("click");
    // Else:
    //   Remove property for 2nd field from datePopups, so that date_popup
    //   attach behavior will not process it after us.
    delete datePopups[dateField2.id];

    // And set our own date range picker showing handlers on the 2nd date field.
    $(dateField2).bind("focus click", function(event) {
      if (handling !== event.target.id) {
        handling = event.target.id;

        // When the 2nd date gets focus or gets clicked, show the date range
        // picker that is attached to the 1st date.
        $($(event.target).attr("data-date-range-start")).focus();
        // But we still want the actual focus on the 2nd date to allow manually
        // entering or clearing a value. Prevent recursion by passing true for
        // the parameter fromHere.
        $(this).focus();
        handling = null;
      }
    });
  };

  /**
   * Turns related date fields into date range pickers.
   *
   * Date pairs should point to each other via the data-date-range-end and
   * data-date-range-start attributes. These should contain the id of the other
   * date field.
   *
   * In Drupal it is often difficult to know the id an element will get when
   * rendered. Therefore, if the data-date-range-end does not contain a valid
   * selector that results in 1 existing element, it is treated as a replacement
   * instruction on the name attribute to arrive at the name of the related date
   * field. This is used by the Views availability filter handler.
   *
   * @param {Element} context
   * @param {Object} datePopups
   */
  Drupal.availabilityCalendar.dateRangePickerCoupler = function(context, datePopups) {
    // Find date popups that form pairs to turn into a date range picker.
    for (var id in datePopups) {
      if (datePopups.hasOwnProperty(id)) {
        var from = $("#" + id + "[data-date-range-end]", context);
        if (from.length > 0) {
          // Try the data-date-range-end attribute as a selector.
          var to = $(from.attr("data-date-range-end"), context);
          if (to.length === 0) {
            // Not a selector: try as a replacement instruction in the form
            // "search replace" where the "search" part in the name of the
            // from element will be replaced by the "replace" part to arrive
            // at the name of the related date field.
            var fromName = from.attr("name");
            var replacement = from.attr("data-date-range-end").split(" ", 2);
            if (replacement.length === 2) {
              var toName = fromName.replace(replacement[0], replacement[1]);
              to = $("[name='" + toName + "']", context);
            }
          }
          if (to.length > 0) {
            // Turn into a date range picker.
            Drupal.availabilityCalendar.dateRangePicker(from[0], to[0], datePopups);
          }
        }
      }
    }
  };

  /**
   * If the form uses auto submit, we prevent that it does so on coupled
   * elements that together define a date range, by adding the
   * ctools-auto-submit-exclude class to the date inputs.
   * However, that means that we have to take that task over by triggering the
   * auto submit if the datepicker is dismissed AND both elements have either a
   * correct value or are cleared.
   *
   * @param {Element} context
   */
  Drupal.availabilityCalendar.dateRangePickerAutoSubmit = function(context) {
    /**
     * @type {Object<string, {inputStartVal, inputEndVal}>}
     *   stores the start values of the 2 fields that comprise a date range
     *   picker, allowing us at a later stage to determine whether to auto
     *   submit or not.
     *
     *   These values are indexed by the id of the 1st input, so we can have
     *   multiple date range picker instances.
     */
    var startValues = {};
    
    /**
     * @type {Object<string, boolean>}
     *   While the date range picker is showing we do not want to auto submit
     *   the form. These 2 variables keep track of change events for the start
     *   and end date, so we can perform the auto submit when the date picker
     *   closes for the active instance.
     *
     *   These values are indexed by the id of the 1st input, so we can have
     *   multiple date range picker instances.
     */
    var deferredChangeStart = {};
    /**
     * @type {Object<string, boolean>}
     */
    var deferredChangeEnd = {};

    //noinspection JSUnusedLocalSymbols
    /**
     * Stores the start values, so we can later determine if we may trigger
     * incomplete values.
     *
     * @param {number} index
     * @param {HTMLInputElement} element
     */
    function initializeStartValues(index, element) {
      var inputStart = $(element);
      var inputEnd = $($(element).attr("data-date-range-end"));
      startValues[element.id] = {inputStartVal: inputStart.val(), inputEndVal: inputEnd.val()};
    }

    /**
     * Determines whether to trigger the auto submit.
     *
     * If the old and new values do not differ we do not have to auto submit.
     *
     * But if they differ, but both the new and the old values are to be
     * considered an incomplete or non-valid range, we don't have to submit
     * because the result of filter (not filtering) will not change.
     *
     * @param {Object} inst
     *
     * @returns {boolean}
     */
    function doTrigger(inst) {
      // - The old and new values must differ AND
      // - (The new values define a valid range OR
      // -  The old values define a valid range)
      var id = inst.inputStart[0].id;
      var format = $.datepicker._get(inst, "dateFormat");
      return (inst.inputStart.val() !== startValues[id].inputStartVal || inst.inputEnd.val() !== startValues[id].inputEndVal) &&
        ((validate(inst.inputStart.val(), format) && validate(inst.inputEnd.val(), format)) ||
         (validate(startValues[id].inputStartVal, format) && validate(startValues[id].inputEndVal, format))
        );
    }

    /**
     * Triggers a submit.
     *
     * Copied (and adapted) from ctools/js/auto-submit.js.
     *
     * @param form
     */
    function triggerSubmit(form) {
      form = $(form);
      if (!form.hasClass("ctools-ajaxing")) {
        form.find(".ctools-auto-submit-click").click();
      }
    }

    /**
     * Validates a date string against the given format.
     *
     * @param {string} dateStr
     * @param {string} format
     *
     * @returns {boolean}
     */
    function validate(dateStr, format) {
      try {
        return Boolean($.datepicker.parseDate(format, dateStr));
      }
      catch (e) {
        return false;
      }
    }

    /**
     * Change handler for the date fields of a date range picker, if the date
     * popup is not or no longer showing and the fields were changed.
     *
     * @param {HTMLInputElement} target
     *   The element triggering this method.
     * @param {Object} inst
     *   The jquery object containing the changed element.
     */
    function dateRangePickerChanged(target, inst) {
      if (!$.datepicker._datepickerShowing) {
        if (!inst.inputStart.is(".date-range-picker-auto-submit-exclude")) {
          if (doTrigger(inst)) {
            triggerSubmit(target.form);
          }
        }
      }
    }

    //noinspection JSUnusedLocalSymbols
    /**
     * onClose handler: gets called when a date range picker instance closes.
     * 
     * This handler looks for deferred change events and if there are, triggers
     * an auto submit (via dateRangePickerChanged()).
     * 
     * @param {string} dateStr
     * @param {Object} inst
     */
    function dateRangePickerOnClose(dateStr, inst) {
      var id = inst.inputStart[0].id;
      var input;
      if (deferredChangeStart[id]) {
        input = inst.inputStart[0];
      }
      else if (deferredChangeEnd[id]) {
        input = inst.inputEnd[0];
      }

      if (input) {
        deferredChangeStart[id] = false;
        deferredChangeEnd[id] = false;
        dateRangePickerChanged(input, inst);
      }
    }

    function deferUntilDateRangePickerCloses(eltInputStart, target, inst) {
      // If the date range picker is showing we defer processing the change
      // event to when it closes: at that moment we will auto submit.
      if (eltInputStart === target) {
        deferredChangeStart[eltInputStart.id] = true;
      }
      else {
        deferredChangeEnd[eltInputStart.id] = true;
      }
      inst.settings.onClose = dateRangePickerOnClose;
    }

    /**
     * Change handler for the 2 date range picker fields.
     *
     * This function can get called in 3 ways:
     * 1) The user is changing the fields directly (date range picker is not
     * showing):
     *   Auto submit if
     * 2) The date range picker is showing and is changing 1 of the fields:
     *   Defer the actual event handling, i.e. auto submitting the form, until
     *   the date range picker closes.
     *
     * @param {Event} event
     */
    function dateRangePickerOnChange(event) {
      var eltInputStart = $(event.target).attr("data-date-range-end") ? event.target : $($(event.target).attr("data-date-range-start"))[0];
      var inst = $.datepicker._getInst(eltInputStart);
      if (!$.datepicker._datepickerShowing) {
        dateRangePickerChanged(event.target, inst);
      }
      else {
        deferUntilDateRangePickerCloses(eltInputStart, event.target, inst);
      }
    }

    $(".ctools-auto-submit-full-form", context)
      .find("[data-date-range-end], [data-date-range-start]")
      .filter(":not(.ctools-auto-submit-exclude)")
      .addClass("ctools-auto-submit-exclude date-range-picker-auto-submit")
      .bind("change", dateRangePickerOnChange)
      .filter("[data-date-range-end]")
      .each(initializeStartValues);
  };

  /**
   * Initialization code based on the Drupal behaviors paradigm.
   */
  Drupal.behaviors.availabilityCalendarDateRangePicker = {
    /**
     * 
     * @param {Element} context
     * @param {{datePopup: object}} settings
     */
    attach: function (context, settings) {
      if (settings.datePopup) {
        Drupal.availabilityCalendar.dateRangePickerCoupler(context, settings.datePopup);
        // Do no longer use settings.datePopup as properties will have been
        // deleted.
        Drupal.availabilityCalendar.dateRangePickerAutoSubmit(context);
      }
    }
  };

}(jQuery));
