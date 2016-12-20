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
		DateRangeError: Drupal.t('Please enter the valid date and time')
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
				endTime = $('.end-time').val();

		autototalDaysUrl = location.protocol + '//' +
											location.host +
											'/calculate_vocation_duration/' +
											startDate + '%20' + startTime + '/' +
											endDate + '%20' + endTime;

		if ((startDate > endDate) || (startDate == endDate && startTime > endTime)) {

			$totalDays.val('');
			message.alert(MESSAGE.DateRangeError);

		} else {
			$.getJSON(autototalDaysUrl).done(function(res) {
				$totalDays.val(res.days);
			}).fail(function() {
				message.alert(MESSAGE.DateRangeError);
			});
		}

	}

	$(document).ready(function() {
		var $popup = $('.popup'),
			$selectedWrapper = $('.selected-approver'),
			$approver = $('input[name="approve_user_id"]'),
			uidArray = [];
                        
                        // initial uidArray
                        if($('input[name="approve_user_id"]').val()!=''){
                            uidArray = $('input[name="approve_user_id"]').val().split(",");
                        }

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

			if (reg.test($totalDays.val()) == false) {
				message.alert(MESSAGE.TotalDaysError);
				return false;
			}

			$approver.val(uidArray.join(','));
                        
                        if($totalDays.val()>3){
                            if(uidArray.length<2){
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
		});

		$popup.on('click', '.close-btn', function() {
			$popup.hide();
		}).on('click', '.user-item', function() {
			var uid = $(this).data('uid'),
				$userItem;

			$popup.hide();

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

	});

	// auto totalDays
	autoTotalDays();
	$('.start-date, .end-date, .start-time, .end-time').on('input propertychange', function() {
		autoTotalDays();
	});

})(jQuery);
