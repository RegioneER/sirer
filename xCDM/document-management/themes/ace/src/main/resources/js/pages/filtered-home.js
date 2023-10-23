function TSToDate(date){
	var fmt = new DateFmt("%d/%m/%y %H.%M");
	return fmt.format(new Date(date));
}

function DateFmt(fstr) {
    this.formatString = fstr

    var mthNames = ["Jan","Feb","Mar","Apr","May","Jun","Jul","Aug","Sep","Oct","Nov","Dec"];
    var dayNames = ["Sun","Mon","Tue","Wed","Thu","Fri","Sat"];
    var zeroPad = function(number) {
        return ("0"+number).substr(-2,2);
    }

    var twoDigit= function(string){
        return (string+'').substr(2,2);
    }

    var dateMarkers = {
        d:['getDate',function(v) { return zeroPad(v)}],
        m:['getMonth',function(v) { return zeroPad(v+1)}],
        n:['getMonth',function(v) { return mthNames[v]; }],
        w:['getDay',function(v) { return dayNames[v]; }],
        y:['getFullYear',function(v) { return twoDigit(v)}],
        H:['getHours',function(v) { return zeroPad(v)}],
        M:['getMinutes',function(v) { return zeroPad(v)}],
        S:['getSeconds',function(v) { return zeroPad(v)}],
        i:['toISOString']
    };

    this.format = function(date) {
        var dateTxt = this.formatString.replace(/%(.)/g, function(m, p) {
            var rv = date[(dateMarkers[p])[0]]()

            if ( dateMarkers[p][1] != null ) rv = dateMarkers[p][1](rv)

            return rv

        });

        return dateTxt
    }

}

function listaPI(children){
	var text="";
	for(var i=0;i<children.length;i++){
		var child=children[i];
		if(child.type.typeId=="Centro"){
			text+=descrCentro(child.metadata)+'<br>';
		}
	}
	return text;
}

function prepareDelete(children, obj){
	for(var i=0;i<children.length;i++){
		var child=children[i];
		if(child.type.typeId=="Centro"){
			
			if($.isArray(child.metadata['ValiditaCTC_val']) && child.metadata['ValiditaCTC_val'][0]){
				return "";
			}
		}
	}
	return "<a href=\"#\" onclick=\"if(confirm('Sei sicuro di voler eliminare lo studio?')) {deleteElement('"+obj.id+"');return false;\" > <img width=\"30px\" height=\"30px\" src=\"/img/trash.png\" alt=\"Elimina\"></a>";
}

function descrStudio(studio){
	return studio.IDstudio_CodiceProt+' ('+studio.UniqueIdStudio_id+')';
}

function descrCentro(centro){
	return centro.IdCentro_PI[0].split("###")[1]+' ('+centro.IdCentro_Struttura[0].split("###")[1]+')';
}

function descrBudget(budget){
	return budget.Base_Nome[0]+' v. '+budget.Budget_Versione[0];
}

function toLength(string){
	var length= 100;
	if(!string) return string;
	if(string.length<=length) return string;
	else return string.substring(0, length-3) + "...";
}


jQuery(function($) {
	
	function setupGrid(grid_selector, pager_selector, url, colModel,colNames, caption){
		$.each(colModel, function(i,element){
            element.title=false;
        });
		jQuery(grid_selector).jqGrid({
			//direction: "rtl",	
			url: url,
			datatype: "json",
			height: 'auto',
			colNames:colNames,
			colModel:colModel,
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
			rowNum:5,
			//rowList:[10,20,30],
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
		
	}

	//studi
	var grid_selector = "#list-grid-table";
	var pager_selector = "#list-grid-pager";
	var url=baseUrl+"/app/rest/documents/jqgrid/getRootElementsByTypePaged/"+typeId+"?rule=single&level=1";
	var caption = "Lista ";
	if(typeId=='Studio'){
		caption="Lista studi";
		var colNames=['Id','Codice','Titolo','Sponsor','Principal Investigator','Data creazione', 'Data modifica',''];
		var colModel=[		
		  			{name:'id',index:'UniqueIdStudio_id', width:20, sorttype:"int",jsonmap:"metadata.UniqueIdStudio_id"},
					{name:'codice',index:'IDstudio_CodiceProt',width:30,jsonmap:"metadata.IDstudio_CodiceProt"},
					{name:'titolo',index:'IDstudio_TitoloProt',formatter:toLength,  width:70,jsonmap:"metadata.IDstudio_TitoloProt.0"},
					{name:'sponsor',index:'datiPromotore_promotore', width:40,jsonmap:"metadata.datiPromotore_promotore.0.title"},
					{name:'pi',index:'IdCentro_PI', width:40,formatter:listaPI,jsonmap:"children"},
					{name:'created',index:'created', width:30,formatter:TSToDate, sorttype:"date",jsonmap:"creationDt"},
					{name:'updated',index:'updated', width:30,formatter:TSToDate, sorttype:"date",jsonmap:"lastUpdateDt" },
					{name:'delete',index:'delete',formatter:prepareDelete, width:10,jsonmap:"children"}
				];
	}else{
		var colNames=['Titolo','Data creazione', 'Data modifica'];
		var colModel=[		
		  			{name:'titolo',index:'titolo',formatter:toLength,  width:70,jsonmap:"titleString"},
					{name:'created',index:'created', width:30,formatter:TSToDate, sorttype:"date",jsonmap:"creationDt"},
					{name:'updated',index:'updated', width:30,formatter:TSToDate, sorttype:"date",jsonmap:"lastUpdateDt" }
				];
	}
	
	
	
	setupGrid(grid_selector, pager_selector, url, colModel, colNames, caption);
	
	
	
	//replace icons with FontAwesome icons like above
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

	function enableTooltips(table) {
		$('.navtable .ui-pg-button').tooltip({container:'body'});
		$(table).find('.ui-pg-div').tooltip({container:'body'});
	}

	//var selr = jQuery(grid_selector).jqGrid('getGridParam','selrow');
	

});



