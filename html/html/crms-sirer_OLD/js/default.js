$('[data-rel=tooltip]').tooltip({container:'body'});
$('[data-rel=popover]').popover({container:'body'});
var tabVisible=false;
function callDynamic(func, parameters) {
	if (func.match(/Action$/)) {
		this[func].apply(this, parameters);
	} 
}

function toggleAction(){
	
}

window.onbeforeunload = function() {
	if($ && $.axmr ){
		if($.axmr.countUpdated()>0){
			return "Vi sono elementi non salvati, sicuro di voler proseguire la navigazione perdendo il lavoro corrente?";
		}
	}
	return;
}

function ajaxCountPopulateCustom(jQueryDomEl, elTypeId, customController){
	jQueryDomEl.html('<i class="icon-spinner icon-spin"></i>');
	var countReq = $.ajax({
		url: baseUrl+"/app"+customController,
		type: "GET",
		dataType: "json"
		});
		
	countReq.done(function( msg ) {
		jQueryDomEl.html(msg);
	});
}

function ajaxCountPopulate(jQueryDomEl, elTypeId, filters){
	if (filters != undefined && filters!='') filters="?"+filters;
	else filters='';
	jQueryDomEl.html('<i class="icon-spinner icon-spin"></i>');
	var countReq = $.ajax({
		url: baseUrl+"/app/rest/documents/advancedSearchCount/"+elTypeId+filters,
		type: "GET",
		dataType: "json"
		});
		
	countReq.done(function( msg ) {
		jQueryDomEl.html(msg);
	});
}

function ajaxCountPopulateRetVal(elTypeId, filters){
	if (filters != undefined && filters!='') filters="?"+filters;
	else filters='';
	var retval=-1;
	var countReq = $.ajax({
		url: baseUrl+"/app/rest/documents/advancedSearchCount/"+elTypeId+filters,
		type: "GET",
		dataType: "json",
		async: false, //aspetto che torni dalla chiamata ajax
		success : function(data) {
					retval=data;
				  }
		});
	
	return retval;
}

//Distruggi la vecchia richiesta e crea la nuova
var lastRequestXHR;

function setupGrid(grid_selector, pager_selector, url, colModel,colNames, caption, callback){
if (lastRequestXHR != null) {
	lastRequestXHR.abort();
} 
	if($(grid_selector).GridUnload)$(grid_selector).GridUnload();
	jQuery(grid_selector).jqGrid({
		//direction: "rtl",	
		url: url,
		datatype: "json",
		height: 'auto',
		colNames:colNames,
		colModel:colModel,
		sortorder: "desc",
		jsonReader: {
			id: "id",
            repeatitems: false,
            root: "root",
            page: "page",
            total:function(obj){
            	return Math.ceil(obj.total/obj.rows);
            },
            cell: "metadata",
            records: "total"
        },
		viewrecords : true,
		rowNum:20,
		rowList:[10,20,30],
		pager : pager_selector,
		altRows: true,
		//toppager: true,			
		caption: caption,
		autowidth: true,
		loadComplete : function() {
			var table = this;
			setTimeout(function(){
				
				updatePagerIcons(table);
				enableTooltips(table);
				
			}, 0);
		},
		loadBeforeSend: function (xhr) {
	        lastRequestXHR = xhr;
	    },
		onSelectRow: function(id){ 
	      window.location.href=baseUrl+'/app/documents/detail/'+id;
		}

	});
	//enable search/filter toolbar
	//jQuery(grid_selector).jqGrid('filterToolbar',{defaultSearch:true,stringResult:true})		
	//navButtons
	jQuery(grid_selector).jqGrid('navGrid',pager_selector,
		{ 	//navbar options
			edit: false,
			add: false,
			del: false
		}
		
		
	);
	var resize=function(grid_selector){
		jQuery(grid_selector).setGridWidth(((jQuery(grid_selector).closest('.home-container').width())-40));
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

function updatePagerIcons(table) {
	var replacement = 
	{
		'ui-icon-seek-first' : 'icon-double-angle-left bigger-140',
		'ui-icon-seek-prev' : 'icon-angle-left bigger-140',
		'ui-icon-seek-next' : 'icon-angle-right bigger-140',
		'ui-icon-seek-end' : 'icon-double-angle-right bigger-140'
	};
	$('.ui-pg-table:not(.navtable) > tbody > tr > .ui-pg-button > .ui-icon').each(function(){
		var icon = $(this);
		var $class = $.trim(icon.attr('class').replace('ui-icon', ''));
		
		if($class in replacement) icon.attr('class', 'ui-icon '+replacement[$class]);
	})
}

function valueOfField(idField){
	field=$('#'+idField);
	 if (field.attr('istokeninput')=='true'){
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

Number.prototype.formatMoney = function(c, d, t, v){
	var n = this, 
    c = isNaN(c = Math.abs(c)) ? 2 : c, 
    d = d == undefined ? "," : d, 
    t = t == undefined ? "." : t, 
    v = v == undefined ? "&euro;" : v, 
    s = n < 0 ? "-" : "", 
    i = parseInt(n = Math.abs(+n || 0).toFixed(c)) + "", 
    j = (j = i.length) > 3 ? j % 3 : 0;
    //if(n==Math.floor(n))c=0;
    console.log("qui= "+n);
   return s + (j ? i.substr(0, j) + t : "") + i.substr(j).replace(/(\d{3})(?=\d)/g, "$1" + t) + (c ? d + Math.abs(n - i).toFixed(c).slice(2) : "")+" "+v;
 };
 
 String.prototype.formatMoney = function(c, d, t, v){
	   var n = parseFloat(this);		
	   if(isNaN(n)) return this;
	   return n.formatMoney(c, d, t, v);
};

function loadingScreen(msg, img, timeout){
	bootbox.hideAll();
	if(img){
		if(img.match('loading')) {
			img='<i class="icon-spinner icon-spin"></i>';
		}else if(img.match('green_check')){
			//img='<i class="icon-ok green" ></i>';
			notifySingle('success', msg, 'success', 'icon-ok green');
			return;
		}else if(img.match('alerta')){
			img='<i class="icon-warning-sign red"></i>';
		}else{
			img='<img src="'+img+'" />';
		}
	}else{
		img='';
	}
	//bootbox.alert(msg+' '+img);
	bootbox.dialog({ 
		message: msg+' '+img,
		closeButton: false,
		onEscape: false
	});
}

function toggleLoadingScreen(){
	bootbox.hideAll();
}

$(document).ready(function(){
	setTimeout(function(){
		var hash = $.trim( window.location.hash );
		if(hash){
			$('a[href$="'+hash+'"]').click();
		}
		else {
			$('a[data-toggle=tab]').first().click();
		}
	},100);
	$('a[data-toggle=tab]').on('click',function(){
		var hash=this.href;
		hash=hash.replace(/^[^#]*/,'');
		window.location.hash=hash;
	});
	
	$(window).bind('hashchange', function(e) {
		console.log('hashchange');
		var $tabToggle=$('a[data-toggle=tab][href='+window.location.hash+']');
		var $tabLI=$tabToggle.closest('li');
		var luogo=location.href;
		var realTarget=window.location.hash;
		realTarget=realTarget.replace(/#/,'');
		realTarget='#pane-'+realTarget;
		if($tabLI.is('.filtered-tab')){
			var classes=$tabLI.attr("class");
			var breakEach=false;
			var breakVar=false;
			var continueVar=true;
			classes=classes.split(" ");
			$.each(classes, function(i,currClass){
				if(currClass=='filtered-tab'){
					breakEach=true;
					return continueVar;
				}
				
				if(breakEach) {
					$('.filtered-tab').removeClass('active-section');
					$('.filtered-tab.'+currClass).addClass('active-section');
					
					luogo=luogo.replace(/#.*$/,"#"+currClass);
					return breakVar;
				}
			});
		}
		
		if($(window.location.hash+'.tab-pane:hidden').size()>0){
			$tabToggle.click();
		}
		if($(realTarget+'.tab-pane:hidden').size()>0){
			$tabToggle.click();
		}
		
		openSidebarByUrl(luogo);
	});
	
	$(window).trigger('hashchange');
	
	setTimeout(function() {
		  if (window.location.hash) {
		    window.scrollTo(0, 0);
		  }
		}, 100);
	$('.filtered-tab-toggle').click(function(event){
		event.preventDefault();
		event.stopPropagation(); 
		if($('body').is('.nav-toggled')){
			$('body').removeClass('nav-toggled');
			ace.data.set( 'tab-toggle', 0);
		}else{
			$('body').addClass('nav-toggled');
			ace.data.set('tab-toggle', 1);
		}
		return false;
	});
	var tabToggle=ace.data.get('tab-toggle');
	if(tabToggle=="1"){
		$('body').addClass('nav-toggled');
	}
	var rightbarToggle=ace.data.get('rightbar-toggle');
	if(rightbarToggle=="1"){
		sidebarToggle(true);
	}
});

function openSidebarByUrl(luogo) {
	var parti=luogo.split('/');
	luogo=parti[parti.length-1];
	console.log(luogo);
	$('a[href$='+luogo+']')

	$('.sidebar .active').removeClass('active');
	$('.sidebar .open').removeClass('open');
	var active=$('.sidebar a[href$='+luogo+']').closest('li');
	active.addClass('active');
	active.closest('ul').closest('li').addClass('open active').closest('ul').closest('li').addClass('open active');
	if($('.sidebar .active').size()==0){
		luogo=luogo.replace(/#.*$/,'');
		var active=$('.sidebar a[href$="/'+luogo+'"]').closest('li');
		active.addClass('active');
		active.closest('ul').closest('li').addClass('open active');
	}
	if($('.sidebar .active').size()==0){
		luogo=luogo.replace(/#.*$/,'');
		var active=$('.sidebar a[href~='+luogo+']').first().closest('li');
		active.addClass('active');
		active.closest('ul').closest('li').addClass('open active');
	}
	if($('.sidebar .active').size()==0 && (typeof(sidebarDefault) != "undefined") && sidebarDefault){
		luogo=sidebarDefault;
		var active=$('.sidebar a[href$='+luogo+']').first().closest('li');
		active.addClass('active');
		active.closest('ul').closest('li').addClass('open active');
		if($('.sidebar .active').size()==0){
			luogo=luogo.replace(/#.*$/,'');
			var active=$('.sidebar a[href~='+luogo+']').first().closest('li');
			active.addClass('active');
			active.closest('ul').closest('li').addClass('open active');
		}
	}
}

function notify(message, type, icon, timeout, id){
	if(message=="")return;
	var color1;
	var color2;
	switch(type){
		case 'success':
			color1='success';
			color2='green';
			break;
		case 'warning':
			color1='warning';
			color2='orange';
			break;
		case 'danger':
			color1='danger';
			color2='red';
			break;
		case 'info':
			color1='info';
			color2='info';
			break;
		default:
			color1=color2=type;
	}
	var html="	<div id=\""+id+"\" class=\"alert alert-block alert-"+color1+" \">";
	html+="	<button data-dismiss=\"alert\" class=\"close\" type=\"button\">";
	html+="<i class=\"icon-remove\"></i>";
	html+="</button>";
	if(icon) html+="<i class=\""+icon+" "+color2+"\"></i> ";
	html+=message;
	html+="</div>";
	$(':input').change(function(){
		notify('','warning','warning');
	});
	$(".auto-alert").remove();
	$('.page-content').prepend(html);

}

function notifySingle(id, message, type, icon, timeout){
	if($('#'+id).size()==0){
		notify(message, type, icon, timeout, id);
	}
	if(timeout && timeout>0){
		setTimeout(function(){clearSingleNotification(id);},timeout)
	}
}

function clearNotification(){
	$('.alert.alert-block').remove();
}
function clearSingleNotification(id){
	$('#'+id+'.alert.alert-block').remove();
}

function sidebarToggle(open){
	if(open){
		$('.sidebar-right').css({width:'0px',position:'absolute'}).prev().addClass('col-xs-12');
		$('#rightbar-toggle').css({left:'2px'}).find('i').removeClass('icon-chevron-right').addClass('icon-chevron-left');
		$('.status-bar-content').css({width:'0px',display:'none',overflow:'hidden'});
		ace.data.set( 'rightbar-toggle', 1);
	}else{
		$('.sidebar-right').removeAttr('style').prev().removeClass('col-xs-12');
		$('#rightbar-toggle').removeAttr('style').find('i').removeClass('icon-chevron-left').addClass('icon-chevron-right');
		$('.status-bar-content').removeAttr('style');
		ace.data.set( 'rightbar-toggle', 0);
	}
	if(typeof resizeGrids!="undefined"){
		$('.tab-content').css({overflow:'hidden'});
		setTimeout(resizeGrids,10);
	}
	
}

$('#rightbar-toggle').on('click',function(){
	sidebarToggle($(this).find('i').is('.icon-chevron-right'));
});

$('.to-money').each(function(){
	var html=$(this).html();
	html=html.formatMoney();
	$(this).removeClass('to-money').addClass('monetized');
	$(this).html(html);
});

$('.tab-pane').each(function(){
	var originalId=this.id;
	id='pane-'+originalId;
	$(this).attr('id',id);
	if(!$('[href=#'+originalId+']').attr('data-toggle')){
		$('[href=#'+originalId+']').on('click',function (e) {
			  var target=this.href;
			  target=target.replace(/.*#/,'');
			  var realTarget='#pane-'+target;
			  $(realTarget).closest('.tab-content').find('.in.active').removeClass('in').removeClass('active');
			  $(realTarget).addClass('in active');
		});
	}
	
	
});

$('[data-toggle=tab]').on('shown.bs.tab',function (e) {
	  var target=this.href;
	  target=target.replace(/.*#/,'');
	  var realTarget='#pane-'+target;
	  $(realTarget).closest('.tab-content').find('.in.active').removeClass('in').removeClass('active');
	  $(realTarget).addClass('in active');
});
/*
 HDCRPMS-142 13.04.2017 vmazzeo ***INIZIO***
 */
function descrStudioElk(studio){
 return studio.IDstudio.values.CodiceProt+' ('+studio.UniqueIdStudio.values.id+')';
}
function descrCentroElk(centro){
 ret=centro.IdCentro.values.PI+' ('+centro.IdCentro.values.Struttura+')';
 return ret;
}
function setupGridElk(grid_selector, pager_selector, url, filter, colModel,colNames, caption, callback, fieldslist){
if (lastRequestXHR != null) {
	lastRequestXHR.abort();
} 
postQuery=new Object();
	postQuery.filter=filter;
	if (fieldslist!=undefined && fieldslist!=null) {
		postQuery.fields=fieldslist;
	}
	if($(grid_selector).GridUnload)$(grid_selector).GridUnload();
	jQuery(grid_selector).jqGrid({
		//direction: "rtl",	
		url: url,
		mtype: 'POST',
		datatype: "json",
		postData: postQuery,
		height: 'auto',
		colNames:colNames,
		colModel:colModel,
		sortorder: "desc",
		jsonReader: {
			id: "id",
            repeatitems: false,
            root: "root",
            page: "page",
            total:function(obj){
            	return Math.ceil(obj.total/obj.rows);
            },
            cell: "metadata",
            records: "total"
        },
		viewrecords : true,
		rowNum:20,
		rowList:[10,20,30],
		pager : pager_selector,
		altRows: true,
		//toppager: true,			
		caption: caption,
		autowidth: true,
		loadComplete : function() {
			var table = this;
			setTimeout(function(){
				
				updatePagerIcons(table);
				enableTooltips(table);
				
			}, 0);
		},
		loadBeforeSend: function (xhr) {
	        lastRequestXHR = xhr;
	    },
		onSelectRow: function(id){ 
	      window.location.href=baseUrl+'/app/documents/detail/'+id;
		}

	});
	//enable search/filter toolbar
	//jQuery(grid_selector).jqGrid('filterToolbar',{defaultSearch:true,stringResult:true})		
	//navButtons
	jQuery(grid_selector).jqGrid('navGrid',pager_selector,
		{ 	//navbar options
			edit: false,
			add: false,
			del: false
		}
		
		
	);
	var resize=function(grid_selector){
		jQuery(grid_selector).setGridWidth(((jQuery(grid_selector).closest('.home-container').width())-40));
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



function ajaxCountPopulateElk(jQueryDomEl, elTypeId, filters){
	if (filters == undefined || filters=='')  filters='{"match_all": {}}';
	jQueryDomEl.html('<i class="icon-spinner icon-spin"></i>');
	var countReq = $.ajax({
		url: baseUrl+"/app/rest/elk/querycount/full/"+elTypeId.toLowerCase(),
		type: "POST",
		data: { filter: filters},
		dataType: "json"
		});
		
	countReq.done(function( msg ) {
		jQueryDomEl.html(msg);
	});
}
/*
 HDCRPMS-142 13.04.2017 vmazzeo ***FINE***
 */
/*
 * VAXMR-405
 * vmazzeo 21.09.2016
 * 
 * gestisco il deseleziona dei radio button inserendo un hidden con valore nullo se nessuna option selezionata,
 * altrimenti la elimino
 * 
 */

function valorizzaRadio(id_radio){
  //if(id_radio.match("radioClear-"))
  if($('#'+id_radio+':checked').val()===undefined)
  {
  	$("#radioClear-"+id_radio+" div input").remove();
    my_hidden=$("<input></input>");
    my_hidden.attr("type","hidden");
    my_hidden.attr("name",id_radio);
    my_hidden.attr("value","");
    if($("hidden[name='"+id_radio+"']").length==0){
      $("#radioClear-"+id_radio+" div").append(my_hidden);
    }
  }
  else{
    $("#radioClear-"+id_radio+" div input").remove();
  } 
}


$('.addCenter').click(function(){AddCenter();});
/*
$('#select_study').modal();
*/
function AddCenter(){
	if($('#modalAddCenter').size()==0){
		$('body').append('<div id="modalAddCenter" class="modal fade">'+
  '<div class="modal-dialog">'+
    '<div class="modal-content">'+
      '<div class="modal-header">'+
        '<button type="button" class="close" data-dismiss="modal"><span aria-hidden="true">×</span><span class="sr-only">Close</span></button>'+
        '<h4 class="modal-title"><i class="icon-hospital"></i> Aggiungi un nuovo centro</h4>'+
      '</div>'+
      '<div class="modal-body">'+
      	'Seleziona lo studio: <input id="select_study" name="select_study"/>'+
	  '</div>'+
      '<div class="modal-footer">'+
      	
	  '</div>'+
    '</div><!-- /.modal-content -->'+
  '</div><!-- /.modal-dialog -->'+
'</div>');
		$('#select_study').select2({
			minimumInputLength: 1,
			maximumSelectionSize: 1,
			containerCssClass:'select2-ace',
			allowClear: true,
			ajax: { 
					url:'/crms-toscana/app/rest/documents/advancedSearch/Studio',
					dataType: 'json',
					quietMillis: 1000,
					cache: true,
					data: function (term, page) {
								return {
									'IDstudio_CodiceProt_like': term
								};
							},
					results: function (data, page) { 
						var length=data.length;
						var results=new Array();
						for(var i=0;i<length;i++){
							results[i]={id:data[i].id,text:data[i].titleString};
						}
						return {results: results, more: false};
					}
				}
	});
	}
	$('#modalAddCenter').modal();
    setTimeout("$('#select_study').select2(\"open\");",500); 
    $('#select_study').on("select2-selecting", function(e) { 
		window.location.href='/crms-toscana/app/documents/addChild/'+e.val+'/Centro';
	});
}

$('#select_study').select2({
		minimumInputLength: 1,
		maximumSelectionSize: 1,
		containerCssClass:'select2-ace',
		allowClear: true,
		ajax: { 
				url:'/crms-toscana/app/rest/documents/advancedSearch/Studio',
				dataType: 'json',
				quietMillis: 1000,
				cache: true,
				data: function (term, page) {
							return {
								'IDstudio_CodiceProt_like': term
							};
						},
				results: function (data, page) { 
					var length=data.length;
					var results=new Array();
					for(var i=0;i<length;i++){
						results[i]={id:data[i].id,text:data[i].titleString};
					}
					return {results: results, more: false};
				}
			}
});
