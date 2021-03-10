$.fn.animateHighlight = function(highlightColor, duration) {
    var highlightBg = highlightColor || "#FFFF9C";
    var animateMs = duration || 500;
    var originalBg = this.css("backgroundColor");
    this.stop().css("background-color", highlightBg).animate({backgroundColor: originalBg}, animateMs);
};

$(document).ready(function() {
	var datePickerElements =  new Array();
	var elementsChanged = [];
				
	alert(traslation_array['Avviso modifiche JS']);

	// Copio il valore iniziale di tutte i campi data
	// Day
	$("td[id^='cell_input_'][class='input']").find("input:text[name$='D']").each(function() {
		datePickerElements[$(this).attr("name")] = $(this).val();
	});
	// Month
	$("td[id^='cell_input_'][class='input']").find("select option:selected").each(function() {
		datePickerElements[$(this).parent().attr("name")] = $(this).val();
	});
	// Year
	$("td[id^='cell_input_'][class='input']").find("input:text[name$='Y']").each(function() {
		datePickerElements[$(this).attr("name")] = $(this).val();
	});
	
	$(window).bind('beforeunload', function(){
		// Controllo prima le date
		for (var key in datePickerElements) {
			// Day e Year
			if (((key.substring(key.length, key.length - 1) == 'D') || (key.substring(key.length, key.length - 1) == 'Y'))
				&& (datePickerElements[key] != $("td[id^='cell_input_'][class='input']").find("input[type='text'][name='"+key+"']").val()))
			{
				elementsChanged.push($("td[id^='cell_input_'][class='input']").find("input[type='text'][name='"+key+"']"));
			}
			// Month
			if ((key.substring(key.length, key.length - 1) == 'M')
				&& (datePickerElements[key] != $("td[id^='cell_input_'][class='input']").find("select[name='"+key+"']").val()))
			{
				elementsChanged.push($("td[id^='cell_input_'][class='input']").find("select[name='"+key+"']"));
			}
		}

		// Controllo tutti gli elementi cambiati
		if (elementsChanged.length > 0) {
			$.each(elementsChanged, function(key, value) {
				$(value).closest("td.input").animateHighlight();
			});						
			return 'If you have made any changes to the fields without clicking the Save or Freeze button, your changes will be lost.';
		}
	});
	
	// Change degli input
	$(":input").change(function () {
		elementsChanged.push($(this));
	}); 
	
	// Hack per il radioclear
	$("a[onclick^='radioclear']").each(function() {
		$(this).click(function() {
			elementsChanged.push($(this));
		});
	});
 	
	$("form.niceform").submit(function() {
		$.each(elementsChanged, function(key, value) { 
			$(value).closest("td.input").removeAttr("style");
		});						
		datePickerElements =  new Array();
		elementsChanged = [];
	});

	$("form.niceform").bind('reset', function() {
		$.each(elementsChanged, function(key, value) { 
			$(value).closest("td.input").removeAttr("style");
		});
		elementsChanged = [];						
	});
});
