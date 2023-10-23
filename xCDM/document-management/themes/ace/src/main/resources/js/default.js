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

//Distruggi la vecchia richiesta e crea la nuova
var lastRequestXHR;

function setupGrid(grid_selector, pager_selector, url, colModel,colNames, caption, callback){
    if (lastRequestXHR != null) {
        lastRequestXHR.abort();
    }
    $.each(colModel, function(i,element){
		element.title=false;
	});
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
	      if(callback){
                callback();
            }
           else {
                window.location.href=baseUrl+'/app/documents/detail/'+id;
           }
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
	bootbox.alert(msg+' '+img);
}

function toggleLoadingScreen(){
	bootbox.hideAll();
}

$(document).ready(function(){

    $(".template-form").addClass("form-horizontal");
    $('.form-horizontal').each(function(){
      $(this).find('label').each(function(){
        var $label=$(this);
        var exclude=$label.closest('.radio');
        var exclude2=$label.closest('.checkbox');
        var exclude3=$label.closest('.ace-file-input');
        if(exclude.size()==0 && exclude2.size()==0 && exclude3.size()==0){
          var $inputs=$(this).parent().children('*').not('label');
          var $parent=$label.parent();
          var $wrap=$("<div class=\"col-sm-9\"></div>");
          $label.addClass("col-sm-3 control-label");
          var $formGroup=$label.closest('.form-group');
          if($formGroup.size()==0){
            $parent.addClass("form-group");
          }
          $parent.append($wrap);
          $wrap.append($inputs);
        }
      });
      var $divisori=$('.divisore').closest('.col-sm-9');
      $divisori.prev('label').remove();
      $divisori.removeClass('col-sm-9').addClass('col-sm-12');
      var $divisori=$('.divisore').closest('.field-view');
      $divisori.prev('label').remove();


    });
    $(window).scroll(function(){
         if($(window).scrollTop() > 10) {
            $('#btn-scroll-up').css("position","fixed");
         } else {
            $('#btn-scroll-up').css("position","absolute");
         }
    });
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
	$('a[href$="'+luogo+'"]')

	$('.sidebar .active').removeClass('active');
	$('.sidebar .open').removeClass('open');
	var active=$('.sidebar a[href$="'+luogo+'"]').closest('li');
	active.addClass('active');
	active.closest('ul').closest('li').addClass('open active').closest('ul').closest('li').addClass('open active');
	if($('.sidebar .active').size()==0){
		luogo=luogo.replace(/#.*$/,'');
		var active=$('.sidebar a[href$="'+luogo+'"]').closest('li');
		active.addClass('active');
		active.closest('ul').closest('li').addClass('open active');
	}
	if($('.sidebar .active').size()==0){
		luogo=luogo.replace(/#.*$/,'');
		var active=$('.sidebar a[href~="'+luogo+'"]').first().closest('li');
		active.addClass('active');
		active.closest('ul').closest('li').addClass('open active');
	}
	if($('.sidebar .active').size()==0 && (typeof(sidebarDefault) != "undefined") && sidebarDefault){
		luogo=sidebarDefault;
		var active=$('.sidebar a[href$="'+luogo+'"]').first().closest('li');
		active.addClass('active');
		active.closest('ul').closest('li').addClass('open active');
		if($('.sidebar .active').size()==0){
			luogo=luogo.replace(/#.*$/,'');
			var active=$('.sidebar a[href~="'+luogo+'"]').first().closest('li');
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


function setupGridElk(grid_selector, pager_selector, url, filter, colModel,colNames, caption, callback){
    if (lastRequestXHR != null) {
        lastRequestXHR.abort();
    }
    postQuery=new Object();
	postQuery.filter=filter;
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
		    if(callback){
		        callback();
		    }
	       else {
	            window.location.href=baseUrl+'/app/documents/detail/'+id;
	       }
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