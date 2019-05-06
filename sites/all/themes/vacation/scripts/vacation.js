//Custom override layer.m.js
var message = {
  loading: function(s) {
    if (s == null) {
      s = 30;
    }

    var a = layer.open({
      type: 2,
      content: '',
      shadeClose: false,
      time: s
    });
    return a;
  },
  alert: function(text, s) {
    if (s == null) {
      s = 3;
    }

    var a1 = layer.open({
      content: '<p>' + text + '</p>',
      style: 'background:#000; opacity:0.8; font-weight:bold; margin:0px; height:auto; color:#fff; border:0px solid #fff; text-align:center',
      time: s
    });
    return a1;
  },
  hideAll: function() {
    layer.closeAll();
  }
};

(function($) {
  'use strict';

  var MESSAGE = {
    TypeOfLeaveRequired: Drupal.t('Please select Type of Leave'),
    LeaveDurationRequired: Drupal.t('Please input Leave Duration'),
    TotalDaysRequired: Drupal.t('Please input Total Days'),
    ApproverRequired: Drupal.t('Please add an Approver'),
    ApproverError: Drupal.t('Please select two or more Approver'),
    TotalDaysError: Drupal.t('Please input a valid number'),
    DateRangeError: Drupal.t('Please enter the valid date and time'),
    RejectReasonRequired: Drupal.t('Please enter the reject reason'),
    CommentError: Drupal.t('Please write description'),
    name: Drupal.t('name', {}, { context: "vacation" }),
    leaveDuration: Drupal.t('leaveDuration', {}, { context: "vacation" }),
    totalDays: Drupal.t('totalDays', {}, { context: "vacation" }),
    typeOfLeave: Drupal.t('typeOfLeave', {}, { context: "vacation" }),
    approver: Drupal.t('approver', {}, { context: "vacation" }),
    comment: Drupal.t('comment', {}, { context: "vacation" }),
  };

  function formatDate(date) {
    var dateArray = date.split('-');

    return dateArray[1] + '/' + dateArray[2] + '/' + dateArray[0];
  }

  // auto totalDays
  function autoTotalDays() {
    var $totalDays = $('#edit-field-total-days-und-0-value'),
      autototalDaysUrl,
      startDate = $('.start-date').val(),
      endDate = $('.end-date').val(),
      startTime = $('.start-time').val(),
      endTime = $('.end-time').val(),
      leaveType = $('#edit-field-type-of-leave-und').val();

    autototalDaysUrl = location.protocol + '//' + location.host + '/calculate_vocation_duration/' + startDate + '%20' + startTime + '/' + endDate + '%20' + endTime + '/' + leaveType;

    $.getJSON(autototalDaysUrl).done(function(res) {
      if(res.days){
        $totalDays.val(res.days);
      }else{
        $totalDays.val('');
      }
    }).fail(function() {
      message.alert(MESSAGE.DateRangeError);
    });
  }

  $(document).ready(function() {
    var $popup = $('.popup'),
      $selectedWrapper = $('.selected-approver'),
      $approver = $('input[name="approve_user_id"]'),
      $main_content = $('#main-content'),
      uidArray = [];

    function hasUid(uid) {
      var len = uidArray.length,
        i = 0;
      for (i; i < len; i++) {
        if (uidArray[i] === uid) {
          return true;
        }
      }

      return false;
    }

    function removeUid(uid) {
      var len = uidArray.length,
        i = 0;
      for (i; i < len; i++) {
        if (uidArray[i] === uid) {
          uidArray.splice(i, 1);
          return true;
        }
      }

      return false;
    }

    // initial uidArray
    if ($approver.length && $approver.val() != '') {
      uidArray = $approver.val().split(",");
    }

    $('#vocation-node-form').submit(function() {
      var $typeOfLeave = $('#edit-field-type-of-leave-und'),
        $leaveDuration = $('.custom-leave-duration').find('input'),
        $totalDays = $('#edit-field-total-days-und-0-value'),
        startDate = $('.start-date').val(),
        endDate = $('.end-date').val(),
        startTime = $('.start-time').val(),
        endTime = $('.end-time').val(),
        len = $leaveDuration.length,
        i = 0,
        reg = /^\d+(\.\d{1})?$/;

      if ($typeOfLeave.val() == '_none') {
        message.alert(MESSAGE.TypeOfLeaveRequired);
        return false;
      }
      
      if($typeOfLeave.val() == 'adjust-break'){
          if($('#edit-field-comment-und-0-value').val() == ''){
            message.alert(MESSAGE.CommentError);
            return false;
          }
      }

      for (i; i < len; i++) {
        if ($($leaveDuration[i]).val() == '') {
          message.alert(MESSAGE.LeaveDurationRequired);
          return false;
        }
      }

      if ((startDate > endDate) || (startDate == endDate && startTime >= endTime)) {
        message.alert(MESSAGE.DateRangeError);
        return false;
      }

      if ($totalDays.val() == '') {
        message.alert(MESSAGE.TotalDaysRequired);
        return false;
      }

      // if (reg.test($totalDays.val()) == false) {
      //   message.alert(MESSAGE.TotalDaysError);
      //   return false;
      // }

      $approver.val(uidArray.join(','));

      if ($totalDays.val() > 2) {
        if (uidArray.length < 2) {
          message.alert(MESSAGE.ApproverError);
          return false;
        }
      }

      if ($approver.val() == '') {
        message.alert(MESSAGE.ApproverRequired);
        return false;
      }

      $('#edit-field-leave-duration-und-0-value-timeEntry-popup-1').val(startTime);
      $('#edit-field-leave-duration-und-0-value2-timeEntry-popup-1').val(endTime);
      $('#edit-field-leave-duration-und-0-value-datepicker-popup-0').val(formatDate(startDate));
      $('#edit-field-leave-duration-und-0-value2-datepicker-popup-0').val(formatDate(endDate));

      $(this).find('.form-submit').attr('disabled', 'disabled');

      return true;
    });

    $('.add-approver').click(function() {
      $popup.show();
      $main_content.hide();
      $(window).scrollTop('0');
    });

    $popup.on('click', '.close-btn', function() {
      $popup.hide();
      $main_content.show();
    }).on('click', '.user-item', function() {
      var uid = $(this).data('uid'),
        $userItem;

      $popup.hide();
      $main_content.show();

      if (!hasUid(uid)) {
        uidArray.push(uid);
        $userItem = $(this).clone();
        $userItem.append('<div class="remove-approver">-</div>');
        $('.selected-approver-field').append($userItem);
      }
    });

    $('.selected-approver-field').on('click', '.remove-approver', function() {
      var $userItem = $(this).parent();

      removeUid($userItem.data('uid'));
      $userItem.remove();
    });

    $('#edit-reject').on('click', function(e) {
      if ($('#edit-reject-reason').val() == '') {
        message.alert(MESSAGE.RejectReasonRequired);
        return false;
      }
    });

  });

  // auto totalDays
  autoTotalDays();
  $('.start-date, .end-date, .start-time, .end-time').on('input propertychange', function() {
    autoTotalDays();
  });

  // search page popup detail
  $('.page-vacation-search tbody').on('click', '.views-field', function() {
    var strHTML = '';
    var obj = {};
    var $this = $(this),
      $tr = $this.parent('tr');

    obj.name = $.trim($tr.find('.views-field-name').text());
    obj.leaveDuration = $.trim($tr.find('.views-field-field-leave-duration').text());
    obj.totalDays = $.trim($tr.find('.views-field-field-total-days').text());
    obj.typeOfLeave = $.trim($tr.find('.views-field-field-type-of-leave').text());
    obj.approver = $.trim($tr.find('.views-field-field-approver').text());
    obj.comment = $.trim($tr.find('.views-field-field-comment').text());

    $.each(obj, function(ind, item) {
      strHTML += '<div class="item">' +
                    '<div class="title">' + MESSAGE[ind] + '</div>' +
                    '<div class="content">' + item + '</div>' +
                  '</div>';
    });

    var popupHTML = '<div class="info-popup">' +
        '<div class="container">' +
        '<div class="btn-close">+</div>' +
        strHTML +
        '</div>' +
      '</div>';

    $('body').append(popupHTML);

  });

  $('body').on('click', '.info-popup, .info-popup .btn-close', function() {
    $('.info-popup').remove();
  });

  $('body').on('click', '.container', function(event) {
      event.stopPropagation();
  });

})(jQuery);
