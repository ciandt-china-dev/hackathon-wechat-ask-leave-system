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
		DateRangeError: Drupal.t('Please enter the valid date and time')
	};

	$(document).ready(function() {
		var $popup = $('.popup'),
			$selectedWrapper = $('.selected-approver'),
			uid = '';

		$('#vocation-node-form').submit(function() {
			var $typeOfLeave = $('#edit-field-type-of-leave-und'),
				$leaveDuration = $('#edit-field-leave-duration').find('input'),
				$totalDays = $('#edit-field-total-days-und-0-value'),
				$approver = $('input[name="approve_user_id"]'),
				startDate = $('.start-date').val(),
				endDate = $('.end-date').val(),
				startTime = $('.start-time').val(),
				endTime = $('.end-time').val(),
				len = $leaveDuration.length,
				i = 0;

			if ($typeOfLeave.val() == '_none') {
				message.alert(MESSAGE.TypeOfLeaveRequired);
				return false;
			}

			for (i; i < len; i++) {
				if ($($leaveDuration[i]).val() == '') {
					message.alert(MESSAGE.LeaveDurationRequired);
					return false;
				}
			}

			if ((startDate == '') || (endDate == '') || (startTime == '') || (endTime == '') || (startDate > endDate) || (startDate == endDate && startTime > endTime)) {
				message.alert(MESSAGE.DateRangeError);
				return false;
			}

			if ($totalDays.val() == '') {
				message.alert(MESSAGE.TotalDaysRequired);
				return false;
			}

			$approver.val(uid);

			if ($approver.val() == '') {
				message.alert(MESSAGE.ApproverRequired);
				return false;
			}

			$('#edit-field-leave-duration-und-0-value-timeEntry-popup-1').val(startTime);
			$('#edit-field-leave-duration-und-0-value2-timeEntry-popup-1').val(endTime);
			$('#edit-field-leave-duration-und-0-value-datepicker-popup-0').val(startDate.replace(/-/g, '/'));
			$('#edit-field-leave-duration-und-0-value2-datepicker-popup-0').val(endDate.replace(/-/g, '/'));

			return false;
		});

		$popup.find('.close-btn').click(function() {
			$popup.hide();
		});

		$popup.find('.user-item').click(function() {

			$popup.hide();
			$('.selected-approver-field').html($(this).html());
			if (!$selectedWrapper.hasClass('selected')) {
				$selectedWrapper.addClass('selected');
			}
			uid = $(this).data('uid');
		});

		$('.add-approver').click(function() {
			$popup.show();
		});

		$('.remove-approver').click(function() {
			$('.selected-approver-field').empty();
			$selectedWrapper.removeClass('selected');
		});

	});

})(jQuery);