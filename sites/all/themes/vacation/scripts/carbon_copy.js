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

  });
})(jQuery);
