(function($) {
  $(document).ready(function() {
    if ($('.node-vocation-form').length) {

      var users = [
        {
          'list_ele': '.initial-approver-list',
          'input_ele': '#approver-autocomplete-search',
          'append_ele_string': '.popup',
          'close_btn': '.close-btn'
        },
        {
          'list_ele': '.initial-cc-list',
          'input_ele': '#cc-autocomplete-search',
          'append_ele_string': '.cc-popup',
          'close_btn': '.cc-close-btn'
        }
      ];

      $.each(users, function(i, v) {
        // Move popup element to popup-content to fix layout issue on wechat.
        $(v.append_ele_string).appendTo('#popup-content');

        $(v.append_ele_string).on('click', v.close_btn, function() {
          $(v.input_ele).val('');
          $(v.input_ele).autocomplete('search', '');
        }).on('click', '.user-item', function() {
          $(v.input_ele).trigger('blur');
          $(v.input_ele).val('');
          $(v.input_ele).autocomplete('search', '');
        });

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
        .data('ui-autocomplete')._renderItem = function(ul, item) {
          $ele1.hide();
          return $('<li>')
            .addClass('user-item')
            .attr('data-uid', item.uid)
            .append('<span class="image"><img src="' + item.icon + '" /></span><span class="name">' + item.value + '</span>')
            .appendTo( ul );
        };
      }
    }
  });
})(jQuery);