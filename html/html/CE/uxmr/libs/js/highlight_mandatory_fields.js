/**
 * Highlight mandatory fields on XMR forms based on
 * the contents of 'c1' javascript variable compiled
 * by each field.
 * 
 * changelog:
 * v0.1 - 2011-05-10: initial release;
 * 
 * By Mauro Verrocchio.
 */

$(document).ready(function() {
	// css class for highlighting
//	var highlightBg = "#FFFF9C";
	var highlightBg = "#E25151";
	
	// breaks down of the fields  
	function splitC1() {
		return c1.substring(2, c1.length-2).split(">><<");
	}
	
	// main entry point of submitting form
	$("form.niceform").submit(function() {
		var go_submitting = true;
		
		$(splitC1()).each(function() {
			var field_name = this.split("###")[1];
			var field_label = this.split("###")[2];
			var field_type = this.split("###")[0];
			
			// for each field type, checks against the value of the field
			var field_to_highlight;
			switch (true) {
				case /^r/.test(field_type):
					// radio type
					if ($("input[type='radio'][name='"+field_name+"']").length > 0 &&
						$("input[type='radio'][name='"+field_name+"']:checked").length == 0) {
							$($("input[type='radio'][name='"+field_name+"']")).closest("td.input").css("background-color", highlightBg);
							go_submitting = false;
					}
					break;

				case /^t/.test(field_type):
					// simple input text and input password type
					if ($("input[type='text'][id='"+field_name+"']").length > 0 &&
						$("input[type='text'][id='"+field_name+"']").val() == '') {
							$("#cell_input_"+field_name).css("background-color", highlightBg);
							go_submitting = false;
					}
					if ($("input[type='password'][name='"+field_name+"']").length > 0 &&
						$("input[type='password'][name='"+field_name+"']").val() == '') {
							$("#cell_input_"+field_name).css("background-color", highlightBg);
							go_submitting = false;
					}
					break;

				case /^fxp/.test(field_type):
					// input type float (with the new onblur can be empty)
					if ($("input[type='text'][id='"+field_name+"']").length > 0 &&
						$("input[type='text'][id='"+field_name+"']").val() != '' && 
						!$.isNumber($("input[type='text'][id='"+field_name+"']").val())) {
							$($("input[type='text'][id='"+field_name+"']")).closest("td.input").css("background-color", highlightBg);
							go_submitting = false;
					}
					break;

				case /^si/.test(field_type):
					// select type
					if ($("select[name='"+field_name+"']").length > 0 &&
						$("select[name='"+field_name+"'] option:selected").val() == '') {
							$($("select[name='"+field_name+"']")).closest("td.input").css("background-color", highlightBg);
							go_submitting = false;
					}
					break;
			}
		});	
			
		//return go_submitting;
	});
	
	$("form.niceform").bind('reset', function() {
		$("td.input").each(function() {
			$(this).css("background-color", "");
		});
		$("td[id^='cell_input_']").each(function() {
			$(this).css("background-color", "");
		});
	});

//	
//	var datePickerElements =  new Array();
//	var elementsChanged = [];
//				
//	alert(traslation_array['Avviso modifiche JS']);
//
//	// Copio il valore iniziale di tutte i campi data
//	// Day
//	$("td[id^='cell_input_'][class='input']").find("input:text[name$='D']").each(function() {
//		datePickerElements[$(this).attr("name")] = $(this).val();
//	});
//	// Month
//	$("td[id^='cell_input_'][class='input']").find("select option:selected").each(function() {
//		datePickerElements[$(this).parent().attr("name")] = $(this).val();
//	});
//	// Year
//	$("td[id^='cell_input_'][class='input']").find("input:text[name$='Y']").each(function() {
//		datePickerElements[$(this).attr("name")] = $(this).val();
//	});
//	
//	$(window).bind('beforeunload', function(){
//		// Controllo prima le date
//		for (var key in datePickerElements) {
//			// Day e Year
//			if (((key.substring(key.length, key.length - 1) == 'D') || (key.substring(key.length, key.length - 1) == 'Y'))
//				&& (datePickerElements[key] != $("td[id^='cell_input_'][class='input']").find("input[type='text'][name='"+key+"']").val()))
//			{
//				elementsChanged.push($("td[id^='cell_input_'][class='input']").find("input[type='text'][name='"+key+"']"));
//			}
//			// Month
//			if ((key.substring(key.length, key.length - 1) == 'M')
//				&& (datePickerElements[key] != $("td[id^='cell_input_'][class='input']").find("select[name='"+key+"']").val()))
//			{
//				elementsChanged.push($("td[id^='cell_input_'][class='input']").find("select[name='"+key+"']"));
//			}
//		}
//
//		// Controllo tutti gli elementi cambiati
//		if (elementsChanged.length > 0) {
//			$.each(elementsChanged, function(key, value) {
//				$(value).closest("td.input").animateHighlight();
//			});						
//			return 'If you have made any changes to the fields without clicking the Save or Freeze button, your changes will be lost.';
//		}
//	});
//	
//	// Change degli input
//	$(":input").change(function () {
//		elementsChanged.push($(this));
//	}); 
//	
//	// Hack per il radioclear
//	$("a[onclick^='radioclear']").each(function() {
//		$(this).click(function() {
//			elementsChanged.push($(this));
//		});
//	});
// 	
//	$("form.niceform").submit(function() {
//		$.each(elementsChanged, function(key, value) { 
//			$(value).closest("td.input").removeAttr("style");
//		});						
//		datePickerElements =  new Array();
//		elementsChanged = [];
//	});
//
//	$("form.niceform").bind('reset', function() {
//		$.each(elementsChanged, function(key, value) { 
//			$(value).closest("td.input").removeAttr("style");
//		});
//		elementsChanged = [];						
//	});
});
