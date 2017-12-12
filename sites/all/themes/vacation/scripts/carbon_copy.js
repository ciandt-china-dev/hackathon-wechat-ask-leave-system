(function($) {
  $(document).ready(function() {
    // Define variables for CC user feature.
    var $cc_popup = $('.cc-popup'),
        $selectedCCWrapper = $('.selected-cc'),
        $cc_user = $('input[name="cc_user_id"]'),
        ccUidArray = [];

    function hasCCUid(uid) {
      var len = ccUidArray.length,
          i = 0;
      for (i; i < len; i++) {
        if (ccUidArray[i] === uid) {
          return true;
        }
      }

      return false;
    }

    function removeCCUid(uid) {
      var len = ccUidArray.length,
          i = 0;
      for (i; i < len; i++) {
        if (ccUidArray[i] === uid) {
          ccUidArray.splice(i, 1);
          return true;
        }
      }

      return false;
    }

    // Initial ccUidArray.
    if ($cc_user.length && $cc_user.val() != '') {
      ccUidArray = $cc_user.val().split(",");
    }
    // Join the CC user list to the input value.
    $('#vocation-node-form').submit(function() {
      $cc_user.val(ccUidArray.join(','));
    });

    // Click event for popup showup.
    $('.add-cc').click(function() {
      $cc_popup.show();
    });
    // Popup close and select event.
    $cc_popup.on('click', '.cc-close-btn', function() {
      $cc_popup.hide();
    }).on('click', '.user-item', function() {
      var uid = $(this).data('uid'),
          $userItem;

      $cc_popup.hide();

      if (!hasCCUid(uid)) {
        ccUidArray.push(uid);
        $userItem = $(this).clone();
        $userItem.append('<div class="remove-cc">-</div>');
        $('.selected-cc-field').append($userItem);
      }
    });

    $('.selected-cc-field').on('click', '.remove-cc', function() {
      var $userItem = $(this).parent();

      removeCCUid($userItem.data('uid'));
      $userItem.remove();
    });

    if ($('.page-vacation-request').length) {
      var users = [
        {
          'list_ele': '.initial-approver-list',
          'input_ele': '#approver-autocomplete-search',
          'append_ele_string': '.popup'
        },
        {
          'list_ele': '.initial-cc-list',
          'input_ele': '#cc-autocomplete-search',
          'append_ele_string': '.cc-popup'
        }
      ];

      $.each(users, function(i, v) {
        userAutoCompleteImpl($(v.list_ele), $(v.input_ele), v.append_ele_string);
      });

      // $ele1: origin data list parent element.
      // $ele2: autocomplete input element.
      // ele3_string: append to element string.
      function userAutoCompleteImpl($ele1, $ele2, ele3_string) {
        var data_list = [];
        $ele1.find('.user-item').each(function() {
          var _this = $(this),
              uid = _this.attr('data-uid'),
              value = _this.children('.name').text(),
              icon = _this.find('img').attr('src');
          data_list.push({
            uid: uid,
            value: value,
            icon: icon
          });
        });

        $ele2.autocomplete({
          minLength: 0,
          source: data_list,
          appendTo: ele3_string
        })
        .data( "ui-autocomplete" )._renderItem = function( ul, item ) {
          $ele1.hide();
          return $( "<li>" )
            .addClass("user-item")
            .attr('data-uid', item.uid)
            .append('<span class="image"><img src="' + item.icon + '" /></span><span class="name">' + item.value + '</span>')
            .appendTo( ul );
        };
      }
    }

  });
})(jQuery);
