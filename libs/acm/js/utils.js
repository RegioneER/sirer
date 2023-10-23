/**
 * FUNZIONI AUSILIARIE JAVASCRIPT
 */
function confirm_copy(file_xml,study_root,study_prefix){
	if(confirm('Do you confirm the copy of this file to the study structure?')){
		if(file_exists(file_xml,study_root,study_prefix)){
			return confirm('The file '+file_xml+' already exists in the study structure.\nOverwrite it?');
		}
		else{
			return true;
		}
	}
	else{
		return false;
	}
}
function file_exists(file_xml,study_root,study_prefix){
	exists=false;
	$.ajax({
		type : "POST",
		url : "?/study/builder/"+study_root+"/file_exists/"+file_xml ,
		data : "file_xml="+file_xml+"&study_root="+study_root+"&study_prefix="+study_prefix,
		dataType : "json",
		async: false, //aspetto che torni dalla chiamata ajax
		success : function(data,textStatus,jqXHR ) {
			if (data.sstatus == 'exists') {
				exists=true;
			} else {
				exists=false;
			}
		}
	});
	return exists;
}

function setEasyPie(){
	$('.easy-pie-chart.percentage').each(function(){
		var $box = $(this).closest('.infobox');
		var barColor = $(this).data('color') || (!$box.hasClass('infobox-dark') ? $box.css('color') : 'rgba(255,255,255,0.95)');
		var trackColor = barColor == 'rgba(255,255,255,0.95)' ? 'rgba(255,255,255,0.25)' : '#E2E2E2';
		var size = parseInt($(this).data('size')) || 50;
		$(this).easyPieChart({
			barColor: barColor,
			trackColor: trackColor,
			scaleColor: false,
			lineCap: 'butt',
			lineWidth: parseInt(size/10),
			animate: /msie\s*(8|7|6)/.test(navigator.userAgent.toLowerCase()) ? false : 1000,
			size: size
		});
	})
}

//TODO: per autocompletamento codice codemirror sistituire json sottostante con contenuto di form.xsd contenuto in hidden id="xsd_form_attributes"
function getSelectedRange(editor) {
	return { from: editor.getCursor(true), to: editor.getCursor(false) };
}
var dummy = {
	attrs: {
		color: ["red", "green", "blue", "purple", "white", "black", "yellow"],
		size: ["large", "medium", "small"],
		description: null
	},
	children: []
};
var tags = {
	"!top": ["top"],
	top: {
		attrs: {
			lang: ["en", "de", "fr", "nl"],
			freeform: null
		},
		children: ["animal", "plant"]
	},
	animal: {
		attrs: {
			name: null,
			isduck: ["yes", "no"]
		},
		children: ["wings", "feet", "body", "head", "tail"]
	},
	plant: {
		attrs: {name: null},
		children: ["leaves", "stem", "flowers"]
	},
	wings: dummy, feet: dummy, body: dummy, head: dummy, tail: dummy,
	leaves: dummy, stem: dummy, flowers: dummy
};

function setNestable(id, depth, is_clonable, is_structure, is_nestable) {
	$('#' + id).nestable({
		maxDepth : depth,
		clonable : is_clonable,
		structure : is_structure,
		nestable : is_nestable
	});
}

/**
 * DSARACENO
 * chiamata da study.module.php in funzione _getLista()
 * mostra l'elenco degli attributi per ogni esame o visita
 */

function visiteExamEdit(type, obj, box_message) {
	//alert(box_message);
	// id dell'elemento
	var id = $(obj).attr('id').substring($(obj).attr('id').lastIndexOf('_') + 1);
	var data = $.parseJSON($('#H_' + type + '_' + id).val());
	// mostro la dialog per visualizzare gli attributi dell'elemento'
	if(type=='V'){
		box_title="Visit ";
	}
	else if(type=='E'){
		box_title="Exam ";
	}
	else {
		box_title="Group ";
	}
	box_title+=$.trim($('#handler_' + type + '_' + id + ' .structName').html())+" options"
	bootbox.dialog({
		message : box_message,
		title : box_title,
		className : "structLoader",
		buttons : {
			success : {
				label : "Confirm",
				className : "btn-success",
				callback : function() {
					$('#handler_' + type + '_' + id + ' .structName').html($('.structLoader input.title').val());
					var j = -1;
					var elementsStruct = {};
					var isValid=true;
					var messages="";
					var new_title="";
					$.each($('.structLoader input'), function(i, v) {
						var	label = $(v).prop("name");
						if (label != undefined) {
							var value=$(v).val();
							if( $(v).prop("type")=='checkbox' && $(v).prop("checked")){
								$(v).attr("checked",true);
								value="yes";
							}
							else if( $(v).prop("type")=='checkbox' && !$(v).prop("checked") ){
								$(v).attr("checked",false);
								value="";
							}

							if (value != "" && value != undefined) {
								elementsStruct[label] = value;
							}
							if(  ($(v).prop("type")=='text' || $(v).prop("type")=='number' || $(v).prop("type")=='xml') && (value=="" || value==undefined) && label!="max_all_in" ){
								isValid=false;
								messages+="- Mandatory Attribute, can not be empty: <b>"+label+"</b><br/>";

							}
							if(label=='text'){
								new_title=value;
							}
						}
					});

					if(isValid){
						var arr = JSON.stringify(elementsStruct);

						$('#H_' + type + '_' + id).val(arr);
						$('#handler_' + type + '_' + id + ' .structName').html(new_title);
						var my_new_bootbox='<div>'+$("div.bootbox-body").children().html()+'<div>';
						$('#handler_'+ type + '_' + id+' #a_'+id).attr('onclick','visiteExamEdit(\''+type+'\',this,\''+my_new_bootbox+'\')');
					}
					else{
						bootbox.alert(messages, function() {visiteExamEdit(type,obj,box_message)});
					}
				}
			},
			danger : {
				label : "Cancel",
				className : "btn-primary",
				callback : function() {

				}
			}
		}
	});
	$.each($('.structLoader .form-group'), function(i, v) {
		var label = $(v).find('label').html();
		var value = $(v).find('input').val();
		$.each(data, function(k, h) {
			if (k == label) {
				$(v).find('input').val(h);
			}
		});
	});

}

/**
 *VMAZZEO
 * box di dialogo per l'inserimento del nome del file della nuova form
 */
function newFormName(boxtitle,box_message,href,prefix) {
	bootbox.dialog({
		message : box_message,
		title : '<label>' + boxtitle + '</label>',
		buttons : {
			success : {
				label : "Confirm",
				className : "btn-success",
				callback : function() {
					var is_valid=true;
					var messages='All fields are mandatories, please re-compile correctly all the fields';
					var data_="";
					if($('#form_type').val()=='standard'){
						data_+="form_type=standard&";
						$("input[id$='-field']:visible,select:visible").each(function(){
							if(is_valid && $(this).val()!=""){
								data_+=$(this).attr('name')+"="+$(this).val()+"&";
							}
							else{
								is_valid=false;
							}
						});
					}
					else if($('#form_type').val()=='main_sub'){
						data_+="form_type=main_sub&";
						$("input[id$='-field']:visible,select:visible").each(function(){
							if(is_valid && $(this).val()!=""){
								data_+=$(this).attr('name')+"="+$(this).val()+"&";
							}
							else{
								is_valid=false;
							}
						});
					}
					if(is_valid){
						$.ajax({
							type : "POST",
							url : "?/study/builder/" + prefix +"/new_form",
							data : data_,
							dataType : "json",
							async: false, //aspetto che torni dalla chiamata ajax
							success : function(data) {
								if (data.sstatus != 'ok') {
									alert("ERRORE\n" + data.error + "\n" + data.detail.toString());
									bootbox.alert(messages, function() {newFormName(boxtitle,box_message,href,prefix)});
								} else {
									location.href=href+data.file;
								}
							}
						});
					}
					else{
						bootbox.alert(messages, function() {newFormName(boxtitle,box_message,href,prefix)});
					}
				}
			},
			danger : {
				label : "Cancel",
				className : "btn-primary",
			}
		}
	});
	$("#form_type option[value='']").remove();
	boxFormType();
}
function boxFormType(){
	$('#form_type').bind('change',function(){
		if( $(this).val()=='main_sub') {
			$( '#div_main_sub' ).show();
			$( '#div_standard').hide();
			$( '#div_visit_selection').hide();
		}else if( $(this).val()=='standard') {
			$( '#div_standard').show();
			$( '#div_main_sub' ).hide();
			$( '#div_visit_selection').hide();
		}else if( $(this).val()=='visit_selection') {
			$( '#div_visit_selection').show();
			$( '#div_standard').hide();
			$( '#div_main_sub' ).hide();
		}
	});
	$('#form_type').change();
}
/**
 * VMAZZEO
 *
 * chiamata da user.module.php in funzione user_privileges_form()
 *  * ritorna i profili attivi per lo studio selezionato
 */
function changeStudyPrefix_GetProfilesListPerStudy() {
	$("#USER_PROFILE_ID option").remove();
	$.ajax({
		type : "GET",
		url : "?/profiles/profiles_list_no_global_per_study/" + $("#STUDY_PREFIX").val(),
		dataType : "json",
		success : function(data) {
			if (data.sstatus == 'ko') {
				alert("ERRORE\n" + data.error + "\n" + data.detail.toString());
			} else {
				$("#USER_PROFILE_ID").append("<option value=''></option>");
				$.each(data, function(skey, sval) {

					if (sval.ID != undefined && sval.D_CODE != undefined) {
						$("#USER_PROFILE_ID").append("<option value='" + sval.ID + "'>" + sval.D_CODE + "</option>");
					}

				});
			}
			$("#USER_PROFILE_ID").focus();
		}
	});
}

function changeStudyPrefix_GetSitesListPerStudy() {
	$("#SITE_ID option").remove();
	$.ajax({
		type : "GET",
		url : "?/center/centers_list_per_study/" + $("#STUDY_PREFIX").val(),
		dataType : "json",
		success : function(data) {
			if (data.sstatus == 'ko') {
				alert("ERRORE\n" + data.error + "\n" + data.detail.toString());
			} else {
				$("#SITE_ID").append("<option value=''></option>");
				$.each(data, function(skey, sval) {
					if (sval.SITE_ID != undefined && sval.DESCR != undefined) {
						$("#SITE_ID").append("<option value='" + sval.SITE_ID + "'>" + sval.DESCR + "</option>");
					}

				});
			}
			$("#SITE_ID").focus();
		}
	});
}


function changeStudyPrefix_GetSitesListPerStudyAndUser() {
	$("#SITE_ID option").remove();
	$.ajax({
		type : "GET",
		url : "?/center/centers_list_per_study_and_user/" + $("#STUDY_PREFIX").val()+"/"+$("#USERID-field").val(),
		dataType : "json",
		success : function(data) {
			if (data.sstatus == 'ko') {
				alert("ERRORE\n" + data.error + "\n" + data.detail.toString());
			} else {
				if (data.sstatus=='no_center') alert(data.detail.toString());
				$("#SITE_ID").append("<option value=''></option>");
				$.each(data, function(skey, sval) {
					if (sval.SITE_ID != undefined && sval.DESCR != undefined) {
						$("#SITE_ID").append("<option value='" + sval.SITE_ID + "'>" + sval.DESCR + "</option>");
					}

				});
			}
			$("#SITE_ID").focus();
		}
	});
}

function file_input(id, multiple) {
	if (!multiple) {
		$(id).ace_file_input({
			no_file : 'No File ...',
			btn_choose : 'Choose',
			btn_change : 'Change',
			droppable : false,
			onchange : null,
			thumbnail : true, //| true | large
			whitelist : 'xml',
			blacklist : '*'
			//onchange:''
			//
		});
	} else {
		$(id).ace_file_input({
			style : 'well',
			btn_choose : 'Drop files here or click to choose',
			btn_change : null,
			no_icon : null,
			droppable : true,
			thumbnail : 'fit'//large | fit
			//,    icon_remove:null//set null, to hide remove/reset button
			/**,before_change:function(files, dropped) {
			 //Check an example below
			 //or examples/file-upload.html
			 return true;
			 }*/
			/**,before_remove : function() {
			 return true;
			 }*/
			,
			preview_error : function(filename, error_code) {
				//name of the file that failed
				//error_code values
				//1 = 'FILE_LOAD_FAILED',
				//2 = 'IMAGE_LOAD_FAILED',
				//3 = 'THUMBNAIL_FAILED'
				//alert(error_code);
			}
		}).on('change', function() {
			//console.log($(this).data('ace_input_files'));
			//console.log($(this).data('ace_input_method'));
		});
	}
}

/**
 * DSARACENO
 * salvataggio study structure
 * questa funzione crea la struttura del visite_exam caricandola dagli elementi draggabili e li manda in post a /saveVisiteExam
 */
function visiteExamSave(prefix) {
	var visiteExam = {};
	var c = 0;
	$.each($('#study_structure .dd-handle'), function(i, v) {
		var id = $(v).attr('id').replace("handler_", "");
		var idArr = id.split("_");
		var info = {};
		info['type'] = idArr[0];
		info['number'] = idArr[1];
		info['title'] = $.trim($(v).find('.structName').html());
		info['attributes'] = $('#H_' + idArr[0] + '_' + idArr[1]).val();
		visiteExam[c++] = info;
	});
	$.post(	"?/study/builder/" + prefix + "/saveVisiteExam",
		{info: visiteExam},
		function(data) {
			bootbox.dialog({
				message : data.messages,
				title : 'Validating structure...',
				className : "structLoader"});
		},
		"json");
}

/**
 * BUILDER GRAFICO DRAGnDROP
 * chiamato da study_form_builder ('/study/builder/:prefix/buildForm/:form', 'study_form_builder')
 *
 */
function initBuilder() {
	var fields=$('#form_fields').val();

	var obj_fields = JSON.parse(fields);
	$.each(obj_fields,function(i,obj){
		if(obj.label){
			obj.label=$("<div/>").html(obj.label).text();
		}
		if(obj.field_options && obj.field_options.txt_value){
			obj.field_options.txt_value=$("<div/>").html(obj.field_options.txt_value).text();
		}
	});
	fb = new Formbuilder({
		selector : '.fb-main',

		bootstrapData :obj_fields
	});

	fb.on('save', function(payload) {

		$.ajax({
			method:'post',
			data: {json:payload},
			url: location.href+'/save',
			dataType : "json",
			success : function(data){
				bootbox.dialog({
					message : data.messages,
					title : 'Saving Form',
					className : "structLoader"});
				var fields=JSON.parse(payload);
				$('#form_fields').val(JSON.stringify(fields.fields));
				populateLinkTo($("select[data-rv-value='model." + (( __t = (Formbuilder.options.mappings.LINK_TO )) == null ? '' : __t) +"']"));
				populateLinkTo($("select[data-rv-value='model." + (( __t = (Formbuilder.options.mappings.LINK_TO_SEND )) == null ? '' : __t) +"']"));
				populateFieldCondition($("select[data-rv-value='model." + (( __t = (Formbuilder.options.mappings.CONDITION )) == null ? '' : __t) +"']"));
				populateFieldCompilaCondition("input[id='model." + (( __t = (Formbuilder.options.mappings.COMPILA_CONDITION_VAR )) == null ? '' : __t) + "']","input[data-rv-input='model." + (( __t = (Formbuilder.options.mappings.COMPILA_CONDITION_VAR )) == null ? '' : __t) + "']");
				populateFToCall($("select[data-rv-value='model." + (( __t = (Formbuilder.options.mappings.F_TO_CALL )) == null ? '' : __t) +"']"));
				if (data.sstatus == 'not_valid') {
					fb.mainView.formSaved=false;

				} else {
					//console.log(data);
					//fb.mainView.bootstrapData=payload;
					fb.mainView.formSaved=true;
					fb.mainView.saveFormButton.attr('disabled', true).text(Formbuilder.options.dict.ALL_CHANGES_SAVED);
				}
			}
		});
		return fb.mainView.formSaved;
	});
	$('.hidden-CODPAT,.hidden-ESAM,.hidden-PROGR,.hidden-VISITNUM,.hidden-VISITNUM_PROGR,.hidden-USERID_INS,.hidden-INVIOCO,.hidden-CENTER,.hidden-SITEID,.hidden-SUBJID').parent().hide();
}

function leggiForm() {
	return $('#form_fields').val();//JSON.stringify(fb.mainView.bootstrapData);//
}

function saveForm(){
	alert('saving');
	return false;

}

//GENHD-33
function populateFieldBYTB(bytb_select,option_selected){
	if(option_selected === undefined){
		option_selected=$(bytb_select).val();
	}
	$(bytb_select).find('option').remove();
	var tables=JSON.parse($("#structure_db_tables").val());
	var my_table=JSON.parse(leggiForm())[0].form_options['table'];
	var current_field=JSON.parse($("#current_field").val());
	$(bytb_select).append("<option value=''></option>");
	jQuery.each(tables,function(table){
		if(table !== 'null' ){
			$(bytb_select).append("<option value='" + table + "'>" + table + "</option>");
		}
	});
	if(option_selected !== undefined){
		$(bytb_select).val(option_selected).change();
	}
	$(bytb_select).unbind().bind("change",function(e){
		option_selected=undefined;
		$("select[data-rv-value='model.field_options.bytbcode']").find('option').remove();
		$("select[data-rv-value='model.field_options.bytbdecode']").find('option').remove();
		$("select[data-rv-value='model.field_options.bytbcode']").append("<option value=''></option>");
		$("select[data-rv-value='model.field_options.bytbdecode']").append("<option value=''></option>");
		var my_fields=tables[$(e.target).val()];
		jQuery.each(my_fields,function(key,field){
			if(field !== 'null'){
				$("select[data-rv-value='model.field_options.bytbcode']").append("<option value='" + field + "'>" + field + "</option>");
				$("select[data-rv-value='model.field_options.bytbdecode']").append("<option value='" + field + "'>" + field + "</option>");
			}
		});
		$("select[data-rv-value='model.field_options.bytbcode']").val(option_selected);
		$("select[data-rv-value='model.field_options.bytbcode']").trigger("change");
		$("select[data-rv-value='model.field_options.bytbdecode']").val(option_selected);
		$("select[data-rv-value='model.field_options.bytbdecode']").trigger("change");
		my_cid=fb.mainView.editView.model.cid;
		if(fb.mainView.collection._byId[my_cid].changed.field_options.bytb!==undefined){
			fb.mainView.collection._byId[my_cid].attributes.field_options.bytbcode="";
			fb.mainView.collection._byId[my_cid].attributes.field_options.bytbdecode="";
		}
		fb.mainView.handleFormUpdate();
	});
}

function populateFieldBYTBCODE(bytb_select,table_selected,option_selected){
	if(option_selected === undefined){
		option_selected=$(bytb_select).val();
	}
	$(bytb_select).find('option').remove();
	var fields=JSON.parse($("#structure_db_tables").val())[table_selected];
	$(bytb_select).append("<option value=''></option>");
	jQuery.each(fields,function(key,field){
		if(field !== 'null'){
			$(bytb_select).append("<option value='" + field + "'>" + field + "</option>");
		}
	});
	if(option_selected !== undefined){
		$(bytb_select).val(option_selected).change();
	}
}

function populateFieldRangeCheckValue(rangeCheck_selects,rangeCheck_model){

	$(rangeCheck_selects).each(function(key_value,check_value){

		$(check_value).find('option').remove();
		//var fields=JSON.parse($("#structure_db_tables").val())[JSON.parse(leggiForm())[0].form_options['table']];
		var fields=JSON.parse($("#form_fields").val());
		$(check_value).append("<option value=''></option>");

		jQuery.each(fields,function(key_field,field){
			if(field.field_type!=='form' && field.field_options.var !== ""){
				var field_braket="["+field.field_options.var+"]";
				$(check_value).append("<option value='"+field_braket+"'>" + field.field_options.var + "</option>");
			}
		});
		$(check_value).val(rangeCheck_model[key_value].checkValue);
		$(check_value).append("<option value='custom_value'>Custom value</option>");
		if($(check_value).val()==""){
			$(check_value).val('custom_value');
			$(check_value).parent().parent().find("input[data-rv-input='option:checkValue']").css("display","inline");
		}
		else{
			$(check_value).parent().parent().find("input[data-rv-input='option:checkValue']").css("display","none");
		}

		$(this).on("change",function(){
			if( $(this).val()!='custom_value'){
				$(this).parent().parent().find("input[data-rv-input='option:checkValue']").val($(this).val());
				$(this).parent().parent().find("input[data-rv-input='option:checkValue']").css("display","none")
			}
			else{
				$(this).parent().parent().find("input[data-rv-input='option:checkValue']").val("");
				$(this).parent().parent().find("input[data-rv-input='option:checkValue']").css("display","inline");
			}
			fb.mainView.handleFormUpdate();
		});

	});
}


function populateLinkTo(link_to_select,option_selected){
	if(option_selected === undefined){
		option_selected=$(link_to_select).val();
	}
	$(link_to_select).find('option').remove();
	var xml_files=JSON.parse($('#structure_forms').val());
	//var current_field=JSON.parse($("#current_field").val());
	$(link_to_select).append("<option value='|ME|'>Current Form</option>");
	$(link_to_select).append("<option value='|NEXT|'>Next Form</option>");
	$(link_to_select).append("<option value='index.php?CENTER=[CENTER]|and|CODPAT=[CODPAT]|and|VISITNUM=[VISITNUM]|and|exams=visite_exams.xml'>Patient's view</option>");
	jQuery.each(xml_files,function(key_visit,visit){
		$(link_to_select).append("<optgroup label=\""+ visit.text +"\">");
		jQuery.each(visit,function(key_exam,exam){
			if(exam.text!==undefined && exam.xml!==undefined){
				link="index.php?CENTER=[CENTER]|and|CODPAT=[CODPAT]|and|VISITNUM=[VISITNUM]|and|ESAM=" + key_exam + "|and|form=" + exam.xml ;
				$(link_to_select).append("<option value='" + link + "'>" + exam.text + "</option>");
			}
		});
		$(link_to_select).append("</optgroup>");
	});
	if(option_selected !== undefined){
		$(link_to_select).val(option_selected).change();
	}
}

function populateFToCall(link_to_select,option_selected){
	if(option_selected === undefined){
		option_selected=$(link_to_select).val();
	}
	$(link_to_select).find('option').remove();
	var f_to_calls=JSON.parse($('#f_to_calls').val());
	//var current_field=JSON.parse($("#current_field").val());
	jQuery.each(f_to_calls,function(key,f_to_call){
		$(link_to_select).append("<option value='" + f_to_call + "'>" + f_to_call + "</option>");
	});
	if(option_selected !== undefined){
		$(link_to_select).val(option_selected).change();
	}
}

//GENHD-18 vmazzeo
function populateFieldCondition(condition_select,option_selected){
	if(option_selected === undefined){
		option_selected=$(condition_select).val();
	}
	$(condition_select).find('option').remove();
	var fields=JSON.parse(leggiForm());
	var current_field=JSON.parse($("#current_field").val());
	$(condition_select).append("<option value=''></option>");
	jQuery.each(fields,function(key,value){
		if(key > 0){ //salta "form_"
			if(value.field_options.var !== 'null' && value.field_options.var!==current_field.field_options.var){
				$(condition_select).append("<option value='" + value.field_options.var + "'>" + value.field_options.var + "</option>");
			}
		}
	});
	if(option_selected !== undefined){
		$(condition_select).val(option_selected).change();
	}
}

function populateFieldCompilaCondition(compila_condition_select2,compila_condition_hidden){

	var fields=JSON.parse(leggiForm());
	var current_field=JSON.parse($("#current_field").val());
	var my_data = [];
	jQuery.each(fields,function(key,value){
		if(key > 0){ //salta "form_"
			if(value.field_options.var !== 'null' && value.field_options.var!==current_field.field_options.var){
				my_data.push({id: value.field_options.var, text: value.field_options.var});
			}
		}
	});

	//var valori_esistenti="[\""+$(compila_condition_select2).val().replace(/\|/g,"\",\"")+"\"]";
	//alert(valori_esistenti);
	$(compila_condition_select2).select2({data: my_data,
			multiple: true,
			initSelection : function (element, callback) {
				var original_values=element.val().replace(/,/g,"|").split("|");
				var data=[];
				jQuery.each(original_values,function(key,value){
					data.push({id:value,text:value});
				});
				element.val("");
				callback(data);
			}
		}
	);//svuoto e re-istanzio la select multipla


	$(compila_condition_select2).on("change", function(e) {
		var valori_con_pipe=e.val.toString().replace(/,/g,"|");
		fb.mainView.editView.model.attributes.field_options.compila_condition_var=valori_con_pipe;//valorizzo il reale compila_condition_var (hidden)
		fb.mainView.handleFormUpdate();
	});
}


/**
 * VMAZZEO 18.11.2014
 * VAXMR-166 - Gestire interrogazioni su oggetti ACM con risultato jqGRID
 */

//Distruggi la vecchia richiesta e crea la nuova
var lastRequestXHR;

function setupGrid(grid_selector, pager_selector, url, colModel,colNames, caption,rowNum_par){
	if (lastRequestXHR != null) {
		lastRequestXHR.abort();
	}
	//$(grid_selector).GridUnload();
	if(rowNum_par===null||rowNum_par===undefined){
		rowNum_par=500;
	}
	jQuery(grid_selector).jqGrid("initFontAwesome").jqGrid({
		//direction: "rtl",	
		url: url,
		datatype: "json",
		height: 'auto',
		colNames:colNames,
		colModel:colModel,
		repeatitems:false,
		jsonReader: {
			id: "_id_", //-->JQGID
			repeatitems: false,
			root: "root",
			page: "page",
			//row: "row",
			total:function(obj){
				return Math.ceil(obj.total/obj.rows);
			},
			//cell: "field",
			records: "total"
		},
		viewrecords : true,
		rowNum:rowNum_par, //GENHD-37 Corretto a 50, il tutto si è aggiustato con il fix al paginatore (ora gestito direttamente da jqgrid)
		rowList:[10,50,100,200,500,1000],
		pager : pager_selector,
		altRows: true,
		//toppager: true,			
		caption: caption,
		autowidth: true,
		loadonce: false,
		ignoreCase: true,
		sortable: true,
		// loadComplete : function() {
		// var table = this;
		// setTimeout(function(){
// 				
		// updatePagerIcons(table);
		// enableTooltips(table);
// 				
		// }, 0);
		// },
		loadBeforeSend: function (xhr) {
			lastRequestXHR = xhr;
		}
		//onSelectRow: function(id){
		//  window.location.href=baseUrl+'/app/documents/detail/'+id;
		//}

	});
	//enable search/filter toolbar
	jQuery(grid_selector).jqGrid('filterToolbar',
		{
			stringResult:true,
			searchOperators: false,
			searchOnEnter: false,
			autosearch: true,
			defaultSearch: "cn",
			rows:1000
		}
	);
	//navButtons
	// jQuery(grid_selector).jqGrid('navGrid',pager_selector,
	// { 	//navbar options
	// edit: false,
	// add: false,
	// del: false
	// }
// 		
// 		
	// );
	var resize=function(grid_selector){
		jQuery(grid_selector).setGridWidth(((jQuery(grid_selector).closest('.page-content').width())-40));

	}    ;

	function valueOfField(idField){
		field=$('#'+idField);
		if (field.attr('istokeninput')=='true'){
			if(field.val()=='') return '';
			value=field.tokenInput("get");
			if (value.length>0)
				return value[0].id;
			else return "";
		}
		if (field.attr('type')=='radio'){
			return $('#'+idField+':checked').attr('title');
		}else if (field.prop('tagName')=='SELECT'){
			return field.find('option:selected').val();
		}else {
			return field.val();
		}
	}
	jQuery(window).bind('resize', function() {
		resize(grid_selector);
	}).trigger('resize');
	jQuery('.sidebar-collapse').find('i').on('click',function(){
		setTimeout(function(){resize(grid_selector);},10);
	});
	resize(grid_selector);
	setTimeout(function(){resize(grid_selector);},1);
}

 function setupGridAdvancedSearch(grid_selector, pager_selector, url, colModel,colNames, caption,rowNum_par){
	if (lastRequestXHR != null) {
		lastRequestXHR.abort();
	}
	//$(grid_selector).GridUnload();
	if(rowNum_par===null||rowNum_par===undefined){
		rowNum_par=500;
	}
	jQuery(grid_selector).jqGrid("initFontAwesome").jqGrid({
		//direction: "rtl",
		url: url,
		datatype: "json",
		height: 'auto',
		colNames:colNames,
		colModel:colModel,
		repeatitems:false,
		jsonReader: {
			id: "id", //-->JQGID
			repeatitems: false,
			root: "root",
			page: "page",
			//row: "row",
			total:function(obj){
				return Math.ceil(obj.total/obj.rows);
			},
			//cell: "field",
			records: "total"
		},
		viewrecords : true,
		rowNum:rowNum_par, //GENHD-37 Corretto a 50, il tutto si è aggiustato con il fix al paginatore (ora gestito direttamente da jqgrid)
		rowList:[10,50,100,200,500,1000],
		pager : pager_selector,
		altRows: true,
		//toppager: true,
		caption: caption,
		autowidth: true,
		loadonce: false,
		ignoreCase: true,
		sortable: true,
		// loadComplete : function() {
		// var table = this;
		// setTimeout(function(){
//
		// updatePagerIcons(table);
		// enableTooltips(table);
//
		// }, 0);
		// },
		beforeRequest : function (xhr) {
			new_url=lastRequestURL;
			if(jQuery(grid_selector).jqGrid("getGridParam", "postData").filters) {
				console.log("loadBeforeSend 1 ", jQuery(grid_selector).jqGrid("getGridParam", "postData"));
				rules=JSON.parse(jQuery(grid_selector).jqGrid("getGridParam", "postData").filters).rules;
				new_url=url+"?";
				for(i=0;i<rules.length;i++){
					val = rules[i].data;
					param = (rules[i].field).replace("metadata.", "") + "_like";
					new_url+="&"+param+"="+val;
				}
				jQuery(grid_selector).jqGrid("setGridParam",{url:new_url});

				console.log("loadBeforeSend 2 ", jQuery(grid_selector).jqGrid("getGridParam", "url"));
			}
			else{
				jQuery(grid_selector).jqGrid("setGridParam",{url:lastRequestURL});
			}
			lastRequestURL =new_url;
			lastRequestXHR = xhr;
		},
		onSelectRow: function(id){
		  window.location.href='/sirer/app/documents/detail/'+id;
		}

	});
	//enable search/filter toolbar
	jQuery(grid_selector).jqGrid('filterToolbar',
		{
			stringResult:true,
			searchOperators: false,
			searchOnEnter: false,
			autosearch: true,
			defaultSearch: "like",
			rows:1000
		}
	);
	//navButtons
	// jQuery(grid_selector).jqGrid('navGrid',pager_selector,
	// { 	//navbar options
	// edit: false,
	// add: false,
	// del: false
	// }
//
//
	// );
	var resize=function(grid_selector){
		jQuery(grid_selector).setGridWidth(((jQuery(grid_selector).closest('.page-content').width())-40));

	}    ;

	function valueOfField(idField){
		field=$('#'+idField);
		if (field.attr('istokeninput')=='true'){
			if(field.val()=='') return '';
			value=field.tokenInput("get");
			if (value.length>0)
				return value[0].id;
			else return "";
		}
		if (field.attr('type')=='radio'){
			return $('#'+idField+':checked').attr('title');
		}else if (field.prop('tagName')=='SELECT'){
			return field.find('option:selected').val();
		}else {
			return field.val();
		}
	}
	jQuery(window).bind('resize', function() {
		resize(grid_selector);
	}).trigger('resize');
	jQuery('.sidebar-collapse').find('i').on('click',function(){
		setTimeout(function(){resize(grid_selector);},10);
	});
	resize(grid_selector);
	setTimeout(function(){resize(grid_selector);},1);
}

/* VAXMR-297*/
function showAddProfileStudyUsersGlobal(study_prefix,profile_code) {
	var grid_selector="#user-list-grid-table_not_assoc";
	var pager_selector="#user-list-grid-pager_not_assoc";
	var url="/acm/?/profiles/study/get_profile_study_users_not_associated/"+study_prefix+"/jqGrid/"+profile_code;
	var colModel=[{"name":"USERID","index":"USERID","width":"20","align":"left","sortable":true,"search":true,"sorttype":"text","firstsortorder":"asc","jsonmap":"USERID"},{"name":"ENABLED","index":"ENABLED","width":"20","align":"left","sortable":true,"search":false,"sorttype":"text","firstsortorder":"asc","jsonmap":"ENABLED"},{"name":"_ACTIONS_","index":"_ACTIONS_","sortable":false,"search":false,"width":"20","align":"left","jsonmap":"_ACTIONS_"}];
	var colNames=["USERID","ENABLED","&nbsp;"];
	var caption="Select Users";
	setupGrid(grid_selector, pager_selector, url, colModel,colNames, caption,10);
	$("#not_associated_users_modal").modal();
	var resize_me=function(grid_selector){
		jQuery(grid_selector).setGridWidth((jQuery(grid_selector).closest('.modal-body').width()-10));
	};
	jQuery(window).bind('resize', function() {
		resize_me(grid_selector);
	}).trigger('resize');
	jQuery('.sidebar-collapse').find('i').on('click',function(){
		setTimeout(function(){resize_me(grid_selector);},10);
	});
	jQuery(grid_selector).setGridWidth((jQuery(grid_selector).closest('.modal-body').width()-10));
	setTimeout(function(){jQuery(window).trigger('resize');},150);

	//funzione per intecettare la chiusura della finestra modale e aggiornare la tabella degli utenti associati allo studio/profilo
	$('#not_associated_users_modal').on('hidden.bs.modal', function () {
		$('#user-list-grid-table').trigger('reloadGrid');
	});
	//setTimeout(function(){$("#not_associated_users_modal").height($("#gbox_user-list-grid-table_not_assoc").height());},10);

}

function assoc_new_user_global(prefix,userid,profileid,no_callback){
	$.ajax({
		type : "GET",
		url : '/acm/?/profiles/study/assoc_new_user_global/' + prefix + '/'+userid+'/'+profileid,
		dataType : "json",
		async : false,
		success : function(data) {
			if (data.sstatus == 'ko') {
				alert("ERRORE\n" + data.error + "\n" + data.detail.toString());
			} else {
				if(no_callback===undefined){
					//se l'associazione utente/studio/profilo è avvenuta con successo, aggiorno la mia tabella nella finestra modale
					// $('.modal-body').html('<table id="user-list-grid-table_not_assoc"></table><div id="user-list-grid-pager_not_assoc"></div>');
					// showAddProfileStudyUsersGlobal(prefix,profileid);
					$("#user-list-grid-table_not_assoc").trigger("reloadGrid");
				}
				else{
					$.gritter.add({
						title: 'Profilo associato all\'utente',
						text: '',
						class_name: 'gritter-success gritter-light',
						time: 1000
					});
					//setTimeout(function(){$.gritter.removeAll();},1000)
					//return alert("Profilo associato all'utente");
				}
			}
		}
	});
}

function showAddProfileStudyUsersNoGlobal(study_prefix,profile_code,siteid) {
	var grid_selector="#user-list-grid-table_not_assoc";
	var pager_selector="#user-list-grid-pager_not_assoc";
	var my_siteid="";
	if(siteid!==undefined){
		my_siteid=siteid;
	}
	var url="/acm/?/profiles/study/get_profile_study_center_users_not_associated/"+study_prefix+"/jqGrid/"+profile_code+"/"+my_siteid;
	var colModel=[{"name":"USERID","index":"USERID","width":"20","align":"left","sortable":true,"search":true,"sorttype":"text","firstsortorder":"asc","jsonmap":"USERID"},{"name":"ENABLED","index":"ENABLED","width":"20","align":"left","sortable":true,"search":false,"sorttype":"text","firstsortorder":"asc","jsonmap":"ENABLED"},{"name":"_ACTIONS_","index":"_ACTIONS_","sortable":false,"search":false,"width":"20","align":"left","jsonmap":"_ACTIONS_"}];
	var colNames=["USERID","ENABLED","&nbsp;"];
	var caption="Select Users";
	setupGrid(grid_selector, pager_selector, url, colModel,colNames, caption,10);
	$("#not_associated_users_modal").modal();
	var resize_me=function(grid_selector){
		jQuery(grid_selector).setGridWidth((jQuery(grid_selector).closest('.modal-body').width()-10));
	};
	jQuery(window).bind('resize', function() {
		resize_me(grid_selector);
	}).trigger('resize');
	jQuery('.sidebar-collapse').find('i').on('click',function(){
		setTimeout(function(){resize_me(grid_selector);},10);
	});
	jQuery(grid_selector).setGridWidth((jQuery(grid_selector).closest('.modal-body').width()-10));
	setTimeout(function(){jQuery(window).trigger('resize');},150);


	//popolo lista centri disponibili
	if($("#SITE_ID").val()==""){
		changeStudyPrefix_GetSitesList(study_prefix,profile_code,siteid);
	}

	$("#SITE_ID").on("change", function(){
		//ricarico tabella utenti non associati
		var newUrl="/acm/?/profiles/study/get_profile_study_center_users_not_associated/"+study_prefix+"/jqGrid/"+profile_code+"/"+$(this).val();
		$("#user-list-grid-table_not_assoc").setGridParam({url:newUrl});
		$("#user-list-grid-table_not_assoc").trigger("reloadGrid");
	});
	//funzione per intecettare la chiusura della finestra modale e aggiornare la tabella degli utenti associati allo studio/profilo
	$('#not_associated_users_modal').on('hidden.bs.modal', function () {
		$('#user-list-grid-table').trigger('reloadGrid');
	});
	//setTimeout(function(){$("#not_associated_users_modal").height($("#gbox_user-list-grid-table_not_assoc").height());},10);

}
function assoc_new_user_noglobal(prefix,userid,profileid,siteid,no_callback){
	if(siteid===undefined){
		siteid=$("#SITE_ID").val();
	}
	if(siteid!=""){
		$.ajax({
			type : "GET",
			url : '/acm/?/profiles/study/assoc_new_user_noglobal/' + prefix + '/'+userid+'/'+profileid+"/"+siteid,
			dataType : "json",
			async : false,
			success : function(data) {
				if (data.sstatus == 'ko') {
					alert("ERRORE\n" + data.error + "\n" + data.detail.toString());
				} else {
					if(no_callback===undefined){
						//se l'associazione utente/studio/profilo è avvenuta con successo, aggiorno la mia tabella nella finestra modale
						//$('#table_not_assoc').html('<table id="user-list-grid-table_not_assoc"></table><div id="user-list-grid-pager_not_assoc"></div>');
						//popolo lista centri disponibili
						//changeStudyPrefix_GetSitesList();
						//showAddProfileStudyUsersNoGlobal(prefix,profileid,$("#SITE_ID").val());
						//ricarico tabella utenti non associati
						$("#user-list-grid-table_not_assoc").trigger("reloadGrid");
					}
					else{
						$.gritter.add({
							title: 'Profilo associato all\'utente',
							text: '',
							class_name: 'gritter-success gritter-light',
							time: 1000
						});
						//setTimeout(function(){$.gritter.removeAll();},1000);
						//return alert("Profilo associato all'utente");
					}
				}
			}
		});
	}
	else{
		$.gritter.add({
			title: 'Sito non selezionato',
			text: '',
			class_name: 'gritter-success gritter-light',
			time: 1000
		});
		//setTimeout(function(){$.gritter.removeAll();},1000);
		//alert("ERRORE\nSito non selezionato");
	}
}

function changeStudyPrefix_GetSitesList(study_prefix,profile_code,siteid){
	$("#SITE_ID option").remove();
	$.ajax({
		type : "GET",
		url : "?/center/get_list_center/",
		dataType : "json",
		success : function(data) {
			if (data.sstatus == 'ko') {
				$.gritter.add({
					title: 'Si è verificato un errore',
					text: '',
					class_name: 'gritter-error gritter-light',
					time: 1000
				});
				//setTimeout(function(){$.gritter.removeAll();},1000);//alert("ERRORE\n" + data.error + "\n" + data.detail.toString());
			} else {
				$("#SITE_ID").append("<option value=''></option>");
				$.each(data, function(skey, sval) {
					if (sval.ID != undefined && sval.DESCR != undefined && sval.ACTIVE == 1) {
						$("#SITE_ID").append("<option value='" + sval.ID + "'>" + sval.DESCR + "</option>");
					}

				});
			}
			$("#SITE_ID").focus();
			if(siteid!==undefined){
				$("SITE_ID").val(siteid);
			}
			if(study_prefix !== undefined && profile_code !== undefined && siteid != undefined){
				$('#SITE_ID').on('change', function () {
					$('#table_not_assoc').html('<table id="user-list-grid-table_not_assoc"></table>'+
						'	<div id="user-list-grid-pager_not_assoc"></div>');
					//popolo lista centri disponibili
					//changeStudyPrefix_GetSitesList();
					showAddProfileStudyUsersNoGlobal(study_prefix,profile_code,$(this).val());

				});
			}
		}
	});
}

function showAddStudyUsersAssociation(centerid){
	var grid_selector="#user-list-grid-table_not_assoc";
	var pager_selector="#user-list-grid-pager_not_assoc";
	var url="/acm/?/center/study/get_list_users_not_associated/"+centerid+"/jqGrid";
	var colModel=[{"name":"USERID","index":"USERID","width":"20","align":"left","sortable":true,"search":true,"sorttype":"text","firstsortorder":"asc","jsonmap":"USERID"},{"name":"ENABLED","index":"ENABLED","width":"20","align":"left","sortable":true,"search":false,"sorttype":"text","firstsortorder":"asc","jsonmap":"ENABLED"},{"name":"_ACTIONS_","index":"_ACTIONS_","sortable":false,"search":false,"width":"20","align":"left","jsonmap":"_ACTIONS_"}];
	var colNames=["USERID","ENABLED","&nbsp;"];
	var caption="Select Users";
	setupGrid(grid_selector, pager_selector, url, colModel,colNames, caption,10);
	$("#not_associated_users_modal").modal();
	var resize_me=function(grid_selector){
		jQuery(grid_selector).setGridWidth((jQuery(grid_selector).closest('.modal-body').width()-10));
	};
	jQuery(window).bind('resize', function() {
		resize_me(grid_selector);
	}).trigger('resize');
	jQuery('.sidebar-collapse').find('i').on('click',function(){
		setTimeout(function(){resize_me(grid_selector);},10);
	});
	jQuery(grid_selector).setGridWidth((jQuery(grid_selector).closest('.modal-body').width()-10));
	setTimeout(function(){jQuery(window).trigger('resize');},150);


	//funzione per intecettare la chiusura della finestra modale e aggiornare la tabella degli utenti associati allo studio/profilo
	$('#not_associated_users_modal').on('hidden.bs.modal', function () {
		$('#user-list-grid-table').trigger('reloadGrid');
	});
}
function center_assoc_new_user(centerid,userid){
	$.ajax({
		type : "GET",
		url : '/acm/?/center/study/center_assoc_new_user/' + centerid + '/'+userid,
		dataType : "json",
		success : function(data) {
			if (data.sstatus == 'ko') {
				$.gritter.add({
					title: 'Si è verificato un errore',
					text: '',
					class_name: 'gritter-error gritter-light',
					time: 1000
				});
				//setTimeout(function(){$.gritter.removeAll();},1000);//alert("ERRORE\n" + data.error + "\n" + data.detail.toString());
			} else {
				//se l'associazione utente/studio/profilo è avvenuta con successo, aggiorno la mia tabella nella finestra modale
				//$('.modal-body').html('<table id="user-list-grid-table_not_assoc"></table><div id="user-list-grid-pager_not_assoc"></div>');
				//showAddStudyUsersAssociation(centerid);
				$('#user-list-grid-table_not_assoc').trigger('reloadGrid');
			}
		}
	});
}

//STSANSVIL-2387 aggiunta funzione per eliminare associazione profilo-utente
function showDeleteProfileUsers(grid_selector) {
	var myGrid = $('#' + grid_selector);
	var selectedRow = myGrid.jqGrid ('getGridParam', 'selrow');
	var user = selectedRow.split('|')[0];
	var study_code = selectedRow.split('|')[1];
	var profile_id = selectedRow.split('|')[2];
	var profile_code = myGrid.jqGrid ('getCell', selectedRow, 'PROFILE_CODE');

	if (confirm('Are you sure you want to delete the ' + profile_code + ' profile for the user ' + user + '?')) {
		$.ajax({
			type : "GET",
			url : "?/profiles/study/delete_user_profile/" + study_code + "/" + user + "/" + profile_id,
			dataType : "json",
			success : function(data) {
				if (data.sstatus == 'ko') {
					alert("ERRORE\n" + data.error + "\n" + data.detail.toString());
				} else {
					alert("Profile deleted");
					location.reload();
				}
			}
		});
	}
}

function showAddProfileUsers(userid){ //VAXMR-300
	$("#STUDY_PREFIX").unbind().bind("change",function(){
		changeStudyPrefix_GetAllProfilesListPerStudy();
		$("#SITE_ID option").remove();
		$("#SITE_ID").parent().parent().hide();
	});
	$("#USER_PROFILE_ID").unbind().bind("change",function(){
		if($(this).val().substring(0,1)!=0){
			$("#SITE_ID").parent().show();
			changeStudyPrefix_GetSitesList();
			if($(this).val().substring(0,1)==1){ //single site scope
				$("#SITE_ID").prop("multiple","");
			}
			else{ //multi site scope
				$("#SITE_ID").prop("multiple","multiple");
			}
		}
		else{
			$("#SITE_ID option").remove();
			$("#SITE_ID").parent().hide();
		}
	});
	$("#not_associated_profiles_modal").modal();
	$('#STUDY_PREFIX').select2('destroy');
	$('#SITE_ID').select2('destroy');
	$('#USER_PROFILE_ID').select2('destroy');
	$('#not_associated_profiles_modal').on('hidden.bs.modal', function () {
		$("#STUDY_PREFIX").val("");
		$("#USER_PROFILE_ID option").remove();
		$("#SITE_ID option").remove();
		$("#SITE_ID").prop("multiple","");
		$("#SITE_ID").parent().parent().hide();
		$('#user-list-grid-table').trigger('reloadGrid');
	});
}

function changeStudyPrefix_GetAllProfilesListPerStudy() {
	$("#USER_PROFILE_ID option").remove();
	$.ajax({
		type : "GET",
		url : "?/profiles/profiles_list_per_study/" + $("#STUDY_PREFIX").val(),
		dataType : "json",
		success : function(data) {
			if (data.sstatus == 'ko') {
				alert("ERRORE\n" + data.error + "\n" + data.detail.toString());
			} else {
				$("#USER_PROFILE_ID").append("<option value=''></option>");
				$.each(data, function(skey, sval) {

					if (sval.ID != undefined && sval.D_CODE != undefined) {
						//if(sval.SCOPE==$("#SCOPE").val()){
						$("#USER_PROFILE_ID").append("<option value='" + sval.SCOPE + "#" + sval.ID + "'>" + sval.D_CODE + "</option>");
						//}
					}

				});
			}
			$("#USER_PROFILE_ID").focus();
		}
	});
}

function assoc_new_user_privilege(){
	var userid=$("#USERID-field").val();
	var study_prefix=$("#STUDY_PREFIX").val();
	var scope=$("#USER_PROFILE_ID").val().substring(0,1);
	var profileid=$("#USER_PROFILE_ID").val().substring(2);
	var siteid=$("#SITE_ID").val() !== null ? $("#SITE_ID").val() : "*";
	var active="on";
	switch (scope) { //a seconda dello scope prescelto
		case "0": //global scope
			$.ajax({ //controllo se l'utente è già associato al profilo
				type : "GET",
				url : "?/user/get_list_privilege/"+userid+"/"+study_prefix+"/"+siteid+"/"+profileid,
				dataType : "json",
				async : false,
				success : function(data) {
					if (data.sstatus == 'ko') {//se non lo è lo associo
						assoc_new_user_global(study_prefix,userid,profileid,true);
					} else {
						//alert("Aggiungo privilegio profilo globale");
						$.gritter.add({
							title: 'Profilo già associato',
							text: '',
							class_name: 'gritter-error gritter-light',
							time: 1000
						});
						//setTimeout(function(){$.gritter.removeAll();},1000);//alert("ERRORE\nProfilo già associato");
					}
				}
			});
			break;
		case "1": //single site scope
			$.ajax({ //controllo se l'utente è già associato al profilo
				type : "GET",
				url : "?/user/get_list_privilege/"+userid+"/"+study_prefix+"/"+siteid+"/"+profileid,
				dataType : "json",
				async : false,
				success : function(data) {
					if (data.sstatus == 'ko') {//se non lo è lo associo
						assoc_new_user_noglobal(study_prefix,userid,profileid,siteid,true);
					} else {
						$.gritter.add({
							title: 'Profilo già associato',
							text: '',
							class_name: 'gritter-error gritter-light',
							time: 1000,
						});
						//setTimeout(function(){$.gritter.removeAll();},1000);//alert("ERRORE\nProfilo già associato");
					}
				}
			});
			break;
		case "2": //multi site scope
			$('#SITE_ID option:selected').each(function(){
				var siteid=$(this).val();
				$.ajax({ //controllo se l'utente è già associato al profilo
					type : "GET",
					url : "?/user/get_list_privilege/"+userid+"/"+study_prefix+"/"+siteid+"/"+profileid,
					dataType : "json",
					//async : false,
					success : function(data) {
						if (data.sstatus == 'ko') {//se non lo è lo associo
							assoc_new_user_noglobal(study_prefix,userid,profileid,siteid,true);
						} else {
							$.gritter.add({
								title: 'Profilo già associato',
								text: '',
								class_name: 'gritter-error gritter-light',
								time: 1000
							});
							//setTimeout(function(){$.gritter.removeAll();},1000);//alert("ERRORE\nProfilo già associato");
						}
					}
				});
			});

			break;
		default :
			$.gritter.add({
				title: 'Profilo non selezionato',
				text: '',
				class_name: 'gritter-error gritter-light',
				time: 1000
			});
			// setTimeout(function(){$.gritter.removeAll();},1000);//alert("profilo non selezionato");
			break;
	}
}

function toggle_study_profile(study_prefix,profile_id,status)
{
	$.ajax({
		type : "GET",
		url : "?/profiles/study/toggle_study_profile/"+study_prefix+"/"+profile_id+"/"+status,
		dataType : "json",
		async : false,
		success : function(data) {
			if (data.sstatus == 'ko') {

			} else {
				$("#user-list-grid-table").trigger('reloadGrid');
			}
		}
	});
}

function toggle_study_profile_user(study_prefix,user_id,profile_id)
{
	$.ajax({
		type : "GET",
		url : "?/profiles/study/toggle/"+study_prefix+"/"+user_id+"/"+profile_id+"/0",
		dataType : "json",
		async : false,
		success : function(data) {
			if (data.sstatus == 'ko') {

			} else {
				$("#user-list-grid-table").trigger('reloadGrid');
			}
		}
	});
}

function toggle_study_profile_center_user(user_id,study_prefix,site_id,profile_id){
	$.ajax({
		type : "GET",
		url : "?/profiles/study/center/toggle/"+user_id+"/"+study_prefix+"/"+site_id+"/"+profile_id,
		dataType : "json",
		async : false,
		success : function(data) {
			if (data.sstatus == 'ko') {

			} else {
				$("#user-list-grid-table").trigger('reloadGrid');
			}
		}
	});
}

function toggle_user_view_hub(profile_scope,user_id,study_prefix,site_id,profile_id,active_toggle){
	$.ajax({
		type : "GET",
		url : "?/user/view/toggle/hub/"+profile_scope+"/"+user_id+"/"+study_prefix+"/"+site_id+"/"+profile_id+"/"+active_toggle,
		dataType : "json",
		async : false,
		success : function(data) {
			if (data.sstatus == 'ko') {

			} else {
				$("#user-list-grid-table").trigger('reloadGrid');
			}
		}
	});
	//,url_for('user/view/toggle/hub/[PROFILE_SCOPE]/'.$username.'/[STUDY_PREFIX]/[SITE_ID]/[PROFILE_ID]/[ACTIVE_TOGGLE]')
}

function deleteUser(accesso_eseguito,userid){
	if(accesso_eseguito==1){
		bootbox.alert("L'utente "+userid+" non può essere eliminato perchè ha già fatto il primo accesso.");
	}
	else{
		bootbox.confirm("Confermi l'eliminazione dell'utente "+userid+" ?", function(result){
			if(result){
				$.ajax({
					type : "GET",
					url : "?/user/delete/"+userid,
					dataType : "json",
					async : false,
					success : function(data) {
						if (data.sstatus == 'ko') {

						} else {
							$("#user-list-grid-table").trigger('reloadGrid');
						}
					}
				});
			}
		});
	}
}


function deletePersonale(azienda,cf){
	bootbox.confirm("Confermi l'eliminazione del personale "+cf+" ?", function(result){
		if(result){
			$.ajax({
				type : "GET",
				url : "?/strutture/personale/elimina/"+azienda+"/"+cf,
				dataType : "json",
				async : false,
				success : function(data) {
					if (data.sstatus == 'ko') {

					} else {
						$("#user-list-grid-table").trigger('reloadGrid');
					}
				}
			});
		}
	});
}

function disablePersonale(azienda,cf,abilitato){
	var azione="a disabilitazione";
	if(abilitato==0){
		azione="\'abilitazione ";
	}
	bootbox.confirm("Confermi l"+azione+" del personale "+cf+"? <br/><b>(questa azione non verrà propagata all'eventuale utenza corrispondente)</b> ", function(result){
		if(result){
			$.ajax({
				type : "GET",
				url : "?/strutture/personale/disabilita/"+azienda+"/"+cf,
				dataType : "json",
				async : false,
				success : function(data) {
					if (data.sstatus == 'ko') {

					} else {
						$("#user-list-grid-table").trigger('reloadGrid');
					}
				}
			});
		}
	});
}

function showAddUOUsersAssociation(id_azienda,uoid){
	var grid_selector="#user-list-grid-table_not_assoc";
	var pager_selector="#user-list-grid-pager_not_assoc";
	var url="/acm/?/strutture/uo/get_list_users_not_associated/"+id_azienda+"/"+uoid+"/jqGrid";
	var colModel=[{"name":"USERID","index":"USERID","width":"20","align":"left","sortable":true,"search":true,"sorttype":"text","firstsortorder":"asc","jsonmap":"USERID"},{"name":"ENABLED","index":"ENABLED","width":"20","align":"left","sortable":true,"search":false,"sorttype":"text","firstsortorder":"asc","jsonmap":"ENABLED"},{"name":"_ACTIONS_","index":"_ACTIONS_","sortable":false,"search":false,"width":"20","align":"left","jsonmap":"_ACTIONS_"}];
	var colNames=["USERID","ENABLED","&nbsp;"];
	var caption="Select Users";
	setupGrid(grid_selector, pager_selector, url, colModel,colNames, caption,10);
	$("#not_associated_users_modal").modal();
	var resize_me=function(grid_selector){
		jQuery(grid_selector).setGridWidth((jQuery(grid_selector).closest('.modal-body').width()-10));
	};
	jQuery(window).bind('resize', function() {
		resize_me(grid_selector);
	}).trigger('resize');
	jQuery('.sidebar-collapse').find('i').on('click',function(){
		setTimeout(function(){resize_me(grid_selector);},10);
	});
	jQuery(grid_selector).setGridWidth((jQuery(grid_selector).closest('.modal-body').width()-10));
	setTimeout(function(){jQuery(window).trigger('resize');},150);


	//funzione per intecettare la chiusura della finestra modale e aggiornare la tabella degli utenti associati allo studio/profilo
	$('#not_associated_users_modal').on('hidden.bs.modal', function () {
		$('#user-list-grid-table').trigger('reloadGrid');
	});
}
function uo_assoc_new_user(aziendaid,uoid,userid){
	$.ajax({
		type : "GET",
		url : '/acm/?/strutture/uo/uo_assoc_new_user/' + aziendaid + '/'+ uoid + '/'+userid,
		dataType : "json",
		success : function(data) {
			if (data.sstatus == 'ko') {
				$.gritter.add({
					title: 'Si è verificato un errore',
					text: '',
					class_name: 'gritter-error gritter-light',
					time: 1000
				});
				//setTimeout(function(){$.gritter.removeAll();},1000);//alert("ERRORE\n" + data.error + "\n" + data.detail.toString());
			} else {
				//se l'associazione utente/studio/profilo è avvenuta con successo, aggiorno la mia tabella nella finestra modale
				//$('.modal-body').html('<table id="user-list-grid-table_not_assoc"></table><div id="user-list-grid-pager_not_assoc"></div>');
				//showAddStudyUsersAssociation(uoid);
				$('#user-list-grid-table_not_assoc').trigger('reloadGrid');
			}
		}
	});
}
//STSANSVIL-1260
function ereditaUtentiDaCE(center_id){
	bootbox.confirm("Confermi di voler scaricare la lista degli utenti dal ce di appartenenza?", function(result){
		if(result){
			$.ajax({
				type : "GET",
				url : "?/center/center_get_users_from_ce/"+center_id,
				dataType : "json",
				async : false,
				success : function(data) {
					if (data.sstatus == 'ko') {

					} else {
						location.reload();
					}
				}
			});
		}
	});
}