<#assign type=model['docDefinition']/>
<#global page={
	"content": path.pages+"/"+mainContent,
	"styles" : ["jquery-ui-full", "datepicker","pages/report.css","x-editable"],
	"scripts" : ["jquery-ui-full","datepicker","bootbox", "token-input" ,"common/elementEdit.js","x-editable", "nestable"],
	"inline_scripts":[],
	"title" : "Report",
 	"description" : "Report" 
} />
<#include "../../partials/form-elements/elementSpecific.ftl">
<#include "../../partials/form-elements/select.ftl" />
<@breadcrumbsData el />
<@reportBuilder el/>
<@script>

var elementiReport=new Object();

function populateList(){
	var areaListUrl="${baseUrl}/app/rest/documents/getElementsByParentWithChilds/${el.id}";
	$.ajax(areaListUrl).done(function(data){ 
		$('#reportsArea-list').html("");
		for (i=0;i<data.length;i++){
			elementiReport[data[i].id]=data[i];
			var itm=$("<li class=\"dd-item dd2-item\">");
			itm.attr('data-id', data[i].id);
			itm.attr('data-group', 1);
			itm.attr('data-pos', data[i].position);
			var div=$('<div class="dd-handle dd2-handle">');
			var i1=$('<i class="normal-icon icon-list blue bigger-130">');
			var i2=$('<i class="drag-icon icon-move bigger-125">');
			var aedit=$('<a class="edit-area blue" href="#">').append($('<i class="pull-right icon-pencil bigger-130">'));
			var aplus=$('<a class="add-report-to-area blue" href="#">').append($('<i class="pull-right icon-plus bigger-130">'));
			var atrash=$('<a class="remove-area red" href="#">').append($('<i class="pull-right icon-trash bigger-130">'));
			var content=$('<div class="dd2-content">');
			content.html(data[i].titleString+" - "+data[i].id);
			aree[data[i].id]=data[i].titleString;
			div.append(i1);
			div.append(i2);
			itm.append(div);
			content.append(atrash);
			content.append(aedit);
			content.append(aplus);
			itm.append(content);
			if (data[i].children!=null && data[i].children.length>0){
				var sublist=$('<ol class="dd-list">');
				var sortable=new Object();
				for (c=0;c<data[i].children.length;c++){
					sortable[data[i].children[c].position]=data[i].children[c];
				}
				var keys=[];
				for (var key in sortable){
					keys.push(key);
				}
				keys.sort();
				for (icidx in keys){
					var ic=keys[icidx];
					console.log(ic);
					elementiReport[sortable[ic].id]=sortable[ic];
					var itmc=$("<li class=\"dd-item dd2-item\">");
					itmc.attr('data-id', sortable[ic].id);
					itmc.attr('data-group', 2);
					itmc.attr('data-pos', sortable[ic].position);
					var divc=$('<div class="dd-handle dd2-handle">');
					var i1c=$('<i class="normal-icon icon-signal blue bigger-130">');
					var i2c=$('<i class="drag-icon icon-move bigger-125">');
					var contentc=$('<div class="dd2-content">');
					contentc.html(sortable[ic].titleString+" - "+sortable[ic].position);
					if (sortable[ic].metadata.report_default && sortable[ic].metadata.report_default[0]=="1###Si") {
						contentc.html(contentc.html()+" <span class=\"red\">(default)</span>");
					}
					var aeditc=$('<a class="edit-report blue" href="#">').append($('<i class="pull-right icon-pencil bigger-130">'));
					var alockc=$('<a class="edit-report-rules blue" href="#">').append($('<i class="pull-right icon-lock bigger-130">'));
					var atrashc=$('<a class="remove-report red" href="#">').append($('<i class="pull-right icon-trash bigger-130">'));
					contentc.append(atrashc);
					contentc.append(aeditc);
					contentc.append(alockc);
					divc.append(i1c);
					divc.append(i2c);
					itmc.append(divc);
					itmc.append(contentc);
					sublist.append(itmc);
				}
				itm.append(sublist);
			}
			$('#reportsArea-list').append(itm);
		}		
		registerList();
	});
}

var reportsObj=new Object();
var elDragged=new Object();
var aree=new Object();

function compareJson(){
	console.log("compareJson");
	actualTree=$('.dd').nestable("serialize");
	console.log(actualTree);
	//Primo controllo: livello 1 = gruppo 1 -> livello 2 = gruppo 2
	for (i=0;i<actualTree.length;i++){
		if (actualTree[i].group!=1) {
			bootbox.alert("Non e' possibile effettuare lo spostamento richiesto");
			populateList();
		}
		if (actualTree[i].children!=null && actualTree[i].children.length>0){
			for (c=0;c<actualTree[i].children.length;c++){
				if (actualTree[i].children[c].group!=2) {
					bootbox.alert("Non e' possibile effettuare lo spostamento richiesto");
					populateList();
				}
				if (actualTree[i].children[c].children!=null) {
					bootbox.alert("Non e' possibile effettuare lo spostamento richiesto");
					populateList();
				}
				posl2=c+1;
				parentEl=actualTree[i].id;
				if (actualTree[i].children[c].id==elDragged.id){
					if (parentEl==elDragged.parent){
						console.log("sono rimasto sotto lo stesso padre");
						$.post("${baseUrl}/app/rest/documents/move/"+actualTree[i].children[c].id+"/to/"+posl2).done(function(){
							console.log("aggiornato in db");
						});
					}else {
						console.log("ho anche cambiato padre");
						$.post("${baseUrl}/app//rest/documents/move/"+actualTree[i].children[c].id+"/to/"+posl2+"/parent/"+parentEl).done(function(){
							console.log("aggiornato in db");
						});
					}
				}
			}
		}
		posl1=i+1;
		if (actualTree[i].id==elDragged.id && posl1!=actualTree[i].pos){
			console.log("Mi sembra che l'id:"+actualTree[i].id+" sia passato dalla posizione "+actualTree[i].pos+" a "+posl1);
			$.post("${baseUrl}/app/rest/documents/move/"+actualTree[i].id+"/to/"+posl1).done(function(){
				console.log("aggiornato in db");
			});
		}
	}
}


function registerList(){
	$(".edit-area").unbind("click");
	$(".edit-area").click(function(){
		editArea($(this).parent().closest(".dd-item").attr("data-id"));
	});
	
	$(".add-report-to-area").unbind("click");
	$(".add-report-to-area").click(function(){
		addReportToArea($(this).parent().closest(".dd-item").attr("data-id"));
	});
	
	$(".remove-area").unbind("click");
	$(".remove-area").click(function(){
		console.log("elimino area "+$(this).parent().closest(".dd-item").attr("data-id"));
		$.ajax("${baseUrl}/app/rest/documents/delete/"+$(this).parent().closest(".dd-item").attr("data-id")).
		done(function(){
			populateList();
		}).fail(function(){
			populateList();
		});;
	});
	
	$(".edit-report").unbind("click");
	$(".edit-report").click(function(){
		editReport($(this).parent().closest(".dd-item").attr("data-id"));
	});
	
	$(".remove-report").unbind("click");
	$(".remove-report").click(function(){
		console.log("Elimino il report: "+$(this).parent().closest(".dd-item").attr("data-id"));
		$.ajax("${baseUrl}/app/rest/documents/delete/"+$(this).parent().closest(".dd-item").attr("data-id")).
		done(function(){
			populateList();
		}).fail(function(){
			populateList();
		});
	});
	
	$(".edit-report-rules").unbind("click");
	$(".edit-report-rules").click(function(){
		editReportRules($(this).parent().closest(".dd-item").attr("data-id"));	
	});

	$('.dd').nestable();
	reportsObj=$('.dd').nestable("serialize");
	$('.dd-handle a').unbind('mousedown');
	$('.dd-handle a').on('mousedown', function(e){
		e.stopPropagation();
	});
	$('.dd-handle').unbind('mousedown');
	$('.dd-handle').on('mousedown', function(e){
		el=$(e.target).closest('.dd-item');
		elParent=el.parent().closest('.dd-item');
		elDragged.id=el.attr('data-id');
		elDragged.group=el.attr('data-group');
		elDragged.pos=el.attr('data-pos');
		if (elParent) elDragged.parent=elParent.attr('data-id');
		else elDragged.parent=null;
		
	});
	$('.dd').unbind("change");
	$('.dd').on('change', function(evt) {
	   compareJson();
	});
	
}
populateList();

var areaFormAction="";
var reportFormAction="";
var editingArea=false;
var editingReport=false;

function editArea(id){
	if (id!=null){
		editingArea=true;
		areaFormAction="${baseUrl}/app/rest/documents/update/"+id;
		$('#reportsAreaTemplate_nome').val(elementiReport[id].metadata.reportsAreaTemplate_nome[0]);
	}else {
		editingArea=false;
		areaFormAction="${baseUrl}/app/rest/documents/save/reportsArea";
		$('#reportsAreaTemplate_nome').val("");
	}
	$('#AreaForm').modal();
}

function addReportToArea(id){
	editReport();
	$('#report_form_parentId').val(id);
}


function editReport(id){
	if (id!=null){
		editingReport=true;
		reportFormAction="${baseUrl}/app/rest/documents/update/"+id;
		$('#report_nome').val(elementiReport[id].metadata.report_nome[0]);
		$('#report_url').val(elementiReport[id].metadata.report_url[0]);
		if (document.forms['reportForm-form'].report_default[0].value==elementiReport[id].metadata.report_default[0]){
			document.forms['reportForm-form'].report_default[0].checked=true;
		}else {
			document.forms['reportForm-form'].report_default[1].checked=true;
		}
	}else {
		editingReport=false;
		reportFormAction="${baseUrl}/app/rest/documents/save/report";
		$('#report_nome').val("");
		$('#report_url').val("");
		document.forms['reportForm-form'].report_default[0].checked=false;
		document.forms['reportForm-form'].report_default[1].checked=false;
	}
	$('#ReportForm').modal();
}

$('.saveArea').click(function(){
	if (editingArea){
		$.post(areaFormAction, {reportsAreaTemplate_nome: $('#reportsAreaTemplate_nome').val()})
		.done(function(){
			populateList();
			$('#AreaForm').modal('hide');
		});
	}else {
		$.post(areaFormAction, {parentId: "${el.id}", reportsAreaTemplate_nome: $('#reportsAreaTemplate_nome').val()})
		.done(function(){
			populateList();
			$('#AreaForm').modal('hide');
		});
	}
});

$('.addArea').click(function(){
	editArea();
});


$('.saveReport').click(function(){
	if (editingReport){
		if (document.forms['reportForm-form'].report_default[1].checked) {
			$.post(reportFormAction, {report_nome: $('#report_nome').val(), report_url: $('#report_url').val(), report_default: "0###No"})
		.done(function(){
			populateList();
			$('#ReportForm').modal('hide');
			});
		}else {
			$.post(reportFormAction, {report_nome: $('#report_nome').val(), report_url: $('#report_url').val(), report_default: "1###Si"})
		.done(function(){
			populateList();
			$('#ReportForm').modal('hide');
		});
		}
		
	}else {
		if (document.forms['reportForm-form'].report_default[1].checked) {
			$.post(reportFormAction, {parentId: $('#report_form_parentId').val(), report_nome: $('#report_nome').val(), report_url: $('#report_url').val(), report_default: "0###No"})
			.done(function(){
				populateList();
				$('#ReportForm').modal('hide');
			});
		}else {
			$.post(reportFormAction, {parentId: $('#report_form_parentId').val(), report_nome: $('#report_nome').val(), report_url: $('#report_url').val(), report_default: "1###Si"})
			.done(function(){
				populateList();
				$('#ReportForm').modal('hide');
			});
		}
	}
});

var thisAcl=new Array();

function getAcl(id){
	$('.policy-area table tbody').html("");
	thisAcl=new Array();
	$.getJSON("${baseUrl}/app/rest/documents/"+id+"/acl/getAll", function(result){
		for (i=0;i<result.length;i++){
			if (result[i].predPolicy && result[i].predPolicy.name=='Full'){
				//
			}else {
				thisAcl[thisAcl.length]=result[i];	
			}
		}
	}).done(function(){
		console.log(thisAcl);
		for (i=0;i<thisAcl.length;i++){
			containers="";
			for (c=0;c<thisAcl[i].containers.length;c++){
				if (containers!="") containers+", ";
				containers+=thisAcl[i].containers[c].container;
			}
			$('.policy-area table tbody').append("<tr><td>"+containers+"</td><td><i class='icon-check'></i>&nbsp;</td><td><a class='remove-rule' href='#' data-id='"+thisAcl[i].id+"'><i class='icon-trash'></i></a>&nbsp;</td></tr>");
		}
		$('.remove-rule').unbind("click");
		$('.remove-rule').click(function(){
			ruleId=$(this).attr("data-id");
			restUrl="${baseUrl}/app/rest/documents/"+selectedReportForRule+"/acl/delete/"+ruleId;
			$.ajax(restUrl).done(function(){getAcl(selectedReportForRule);});
		});
	});
}

var selectedReportForRule=null;

function editReportRules(id){
	selectedReportForRule=id;
	$('.policy-area').show();
	$('.policy-area h4 span').html(elementiReport[id].titleString);
	getAcl(id);
}

$('.add-rule').click(function(){
	$('#RuleForm').modal();
});

$('.addRule-to-group').click(function(){
	console.log($('#authoritySelect').val());
	$.post('${baseUrl}/app/rest/documents/'+selectedReportForRule+'/acl/save', {groups: $('#authoritySelect').val(), view: "1", canBrowse: "1", policy:""}).
	done(function(){
		getAcl(selectedReportForRule);
		$('#RuleForm').modal('hide');
	});
});



 $("#authoritySelect").select2({
    placeholder: "Cerca un gruppo di utenti",
    minimumInputLength: 2,
    ajax: { 
    	url: "${baseUrl}/uService/rest/user/searchAuth",
    	dataType: 'json',
    	data: function (term, page) {
		    return {
		    	term: term
		    };
    	},
    	results: function (data, page) { // parse the results into the format expected by Select2.
	    	var ret=new Array();
	    	for (i=0;i<data.length;i++){
		    	var itm=new Object();
		    	itm.id=data[i].authority;
		    	itm.text=data[i].authority;
		    	ret[i]=itm;
	    	}
	    	return {results: ret};
    	}
    }
});


</@script>
