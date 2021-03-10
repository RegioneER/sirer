
function showHide(elementId){
	if (!isVisible(elementId)){
		$('[data-caret="down"][data-rel="'+elementId+'"]').hide();
		$('[data-caret="up"][data-rel="'+elementId+'"]').show();
		$('#'+elementId).show();
	}else {
		$('[data-caret="down"][data-rel="'+elementId+'"]').show();
		$('[data-caret="up"][data-rel="'+elementId+'"]').hide();
		$('#'+elementId).hide();
	}
}

function isVisible(elementId){
	return $('#'+elementId).is(":visible");
}

$('[data-caret-container]').click(function(){
	elIdRef=$(this).attr('data-caret-container-element');
	showHide(elIdRef);
	return false;
});

$('[data-caret]').click(function(){
	if ($(this).attr("data-caret")=='down'){
		$('[data-caret="down"][data-rel="'+$(this).attr("data-rel")+'"]').hide();
		$('[data-caret="up"][data-rel="'+$(this).attr("data-rel")+'"]').show();
		$('#'+$(this).attr("data-rel")).show();
	}else {
		$('[data-caret="up"][data-rel="'+$(this).attr("data-rel")+'"]').hide();
		$('[data-caret="down"][data-rel="'+$(this).attr("data-rel")+'"]').show();
		$('#'+$(this).attr("data-rel")).hide();
	}
	return false;	 
});


$(".field_check").change(function() {
    if(this.checked) {
    	if ($('[name="'+$(this).val()+'"]').val()=='') $('[name="'+$(this).val()+'"]').val($(this).val().split(".")[$(this).val().split(".").length-1]);
        $('[name="'+$(this).val()+'"]').attr('disabled', false);
    }else {
    	$('[name="'+$(this).val()+'"]').val("");
    	$('[name="'+$(this).val()+'"]').attr('disabled', true);
    }
});


$(".field_linked").change(function() {
	dataIdx=$(this).val();
	if(this.checked) {
    	elTypeName=$(this).attr('data-elTypeName');
    	templateName=$(this).attr('data-templateName');
    	fieldName=$(this).attr('data-fieldName');
    	elpath=$(this).attr('data-elpath');
    	$('[data-idx="'+dataIdx+'"]').html("");
    	(function(elTypeName, templateName, fieldName, elpath, dataIdx){
    		$.getJSON("/xCDM-Report-Designer/index.php?/getLinkedFieldSpec&elTypeName="+elTypeName+"&templateName="+templateName+"&fieldName="+fieldName, function(data){
    			appendLinkedElDetails(elTypeName, templateName, fieldName, elpath, dataIdx, data);
    			
        	});    		
    	})(elTypeName, templateName, fieldName, elpath, dataIdx);
    }else{
    	$('[data-idx="'+dataIdx+'"]').html("");
    }
});

function appendLinkedElDetails(elTypeName, parenttemplateName, parentfieldName, elpath, dataIdx, data){
	var ulContainer=$('<ul>');
	for (var subTypeName in data){
		var liEl=$('<li>');
		liEl.html("el:"+subTypeName);
		if (data[subTypeName].fields){
			var ulFieldsContainer=$('<ul>campi:');
			for (var templateName in data[subTypeName].fields){
				var liTemplate=$('<li>');
				liTemplate.html("t:"+templateName);
				ulFieldsContainer.append(liTemplate);
				var ulTemplateFieldsContainer=$('<ul>');
				for (i=0;i<data[subTypeName].fields[templateName].length;i++){
					var fld=data[subTypeName].fields[templateName][i];
					var liFieldEl=$('<li>');
					liFieldEl.html(fld.name);
					
					var lbl=$('<label>');
					var chk=$('<input>');
					
					chk.attr('name','fields[]');
					chk.addClass('ace');
					chk.addClass("field_check");
					chk.attr('type','checkbox');
					var subElPath=elpath+"_"+parenttemplateName+"."+parentfieldName+"_"+subTypeName+"_"+templateName+"."+fld.name;
					chk.val(subElPath);
					var spn=$('<span>');
					spn.addClass('lbl');
					
					lbl.append(chk);
					lbl.append(spn);
					liFieldEl.append("&nbsp;");
					liFieldEl.append(lbl);
					if (fld.type!='ELEMENT_LINK'){
						var inp=$('<input>');
						inp.attr('type','textbox');
						inp.attr('placeholder','nome colonna ...');
						inp.attr('name', subElPath);
						inp.attr('size',20);
						inp.attr('disabled',true);
						(function(chk, inp){
							chk.change(function(){
								if(this.checked) {
									if (inp.val()=='') inp.val($(this).val().split(".")[$(this).val().split(".").length-1]);
							        inp.attr('disabled', false);
								}else {
									inp.val('');
									inp.attr('disabled', true);
								}
							})
						})(chk,inp);
						liFieldEl.append('&nbsp;');
						liFieldEl.append(inp);
					}else {
						ulContainerLinked=$('<ul>');
						ulContainerLinked.attr('data-idx',subElPath);
						liFieldEl.append(ulContainerLinked);
						(function (chk, elTypeName, templateName, fieldName, elpath, dataIdx){
							chk.change(function(){
								if(this.checked) {
									$.getJSON("/xCDM-Report-Designer/index.php?/getLinkedFieldSpec&elTypeName="+elTypeName+"&templateName="+templateName+"&fieldName="+fieldName, function(data){
										appendLinkedElDetails(elTypeName, templateName, fieldName, elpath, dataIdx, data);	
									});
								}else {
									$('[data-idx="'+dataIdx+'"]').html("");
								}
							});
						})(chk, subTypeName, templateName, fld.name, subElPath, subElPath);
					}
					ulTemplateFieldsContainer.append(liFieldEl);
				}
				ulFieldsContainer.append(ulTemplateFieldsContainer);
			}
			liEl.append(ulFieldsContainer);
		}
		ulContainer.append(liEl);
	}
	$('[data-idx="'+dataIdx+'"]').append(ulContainer);
}

$('form[name="reportDesigner"] button[type="submit"]').click(function(){
	if ($('form[name="reportDesigner"] input[name="rep_prefix"]').val()=='') {
		alert('inserire il prefisso per le viste da creare');
		return false;
	}
	
});


$("#reportDesigner").submit(function(e) {

    var url = $(this).attr('action');

    $.ajax({
           type: "POST",
           url: url,
           data: $("#reportDesigner").serialize(), // serializes the form's elements.
           success: function(data)
           {
        	   bootbox.dialog({message: data});
           }
         });

    e.preventDefault(); // avoid to execute the actual submit of the form.
});


function copyToClipboard(elementId) {


	  var aux = document.createElement("input");
	  aux.setAttribute("value", document.getElementById(elementId).innerHTML);
	  document.body.appendChild(aux);
	  aux.select();
	  document.execCommand("copy");

	  document.body.removeChild(aux);

	}
