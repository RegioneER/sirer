<#global page={
	"content": path.pages+"/"+mainContent,
	"styles" : ["select2","jquery-ui-full", "datepicker", "jqgrid"],
	"scripts" : ["select2","jquery-ui-full","bootbox" ,"datepicker", "jqgrid","pages/home.js","common/elementEdit.js", "chosen" , "spinner" , "datepicker" , "timepicker" , "daterangepicker" , "colorpicker" , "knob" , "autosize", "inputlimiter", "maskedinput", "tag"],
	"inline_scripts":[],
	"title" : "Home page",
 	"description" : "Dynamic tables and grids using jqGrid plugin" 
} />
<@style>
.select2-container {
	min-width:330px;
}

.infobox{
    width: 150px;
    height: 103px;
    text-align: center;
		//background-image: -moz-linear-gradient(bottom, #F2F2F2 0%, #FFFFFF 100%);
}

.infobox > .infobox-data {
    text-align: center;
    padding-left: 0px;
}

div#budget div{

}

</@style>
<#global breadcrumbs=
{
	"title":"Home Page",
	"links":[]
}
/>

<@defaultSidebar/>

<#--
<@script>
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
    
	    
	function studyList(query){
		var grid_selector = "#home-grid-table";
		var pager_selector = "#home-grid-pager";
		var url=baseUrl+"/app/rest/documents/jqgrid/advancedSearch/Studio";
		if (query!=undefined) {
			var url=baseUrl+"/app/rest/documents/jqgrid/advancedSearch/Studio?"+query;
		}
		var colNames=['Id','Codice', 'Titolo', 'Stato'];
		var colModel=[		
		  			{name:'id',index:'id', width:20, sorttype:"int", firstsortorder:"desc",jsonmap:"id"},
		  			{name:'titolo',index:'dettaglioStudio_codiceStudio',width:30,jsonmap:"metadata.dettaglioStudio_codiceStudio"},
		  			{name:'titolo',index:'datiBase_titoloStudio',width:30,jsonmap:"metadata.datiBase_titoloStudio"},
					{name:'titolo',index:'datiBase_stato',width:30,jsonmap:"metadata.datiBase_stato"}
				];
		var caption = "Studi";
		setupGrid(grid_selector, pager_selector, url, colModel,colNames, caption);
	}
	
	ajaxCountPopulate($('#studi_ins .infobox-data-number'), 'Studio');
	ajaxCountPopulate($('#studi_1 .infobox-data-number'), 'Studio','datiBase_statoCod_like=1');
	ajaxCountPopulate($('#studi_2 .infobox-data-number'), 'Studio','datiBase_statoCod_eq=2');
	ajaxCountPopulate($('#studi_3 .infobox-data-number'), 'Studio','datiBase_statoCod_eq=3');
	ajaxCountPopulate($('#studi_4 .infobox-data-number'), 'Studio','datiBase_statoCod_eq=4');
	ajaxCountPopulate($('#studi_5 .infobox-data-number'), 'Studio','datiBase_statoCod_eq=5');
	ajaxCountPopulate($('#studi_6 .infobox-data-number'), 'Studio','datiBase_statoCod_eq=6');
	ajaxCountPopulate($('#studi_7 .infobox-data-number'), 'Studio','datiBase_statoCod_eq=7');
	ajaxCountPopulate($('#studi_8 .infobox-data-number'), 'Studio','datiBase_statoCod_eq=8');
	ajaxCountPopulate($('#studi_9 .infobox-data-number'), 'Studio','datiBase_statoCod_eq=9');
	
	$('.infobox').removeClass('infobox-dark');
	$('#studi_ins').addClass('infobox-dark');
	studyList();
	
</@script>
<@onclick "studi_ins">
			$('.infobox').removeClass('infobox-dark');
			$('#studi_ins').addClass('infobox-dark');
			studyList();	
</@onclick>


<@onclick "studi_1">
			$('.infobox').removeClass('infobox-dark');
			$('#studi_1').addClass('infobox-dark');
			studyList('datiBase_statoCod_like=1');	
</@onclick>


<@onclick "studi_2">
			$('.infobox').removeClass('infobox-dark');
			$('#studi_2').addClass('infobox-dark');
			studyList('datiBase_statoCod_eq=2');	
</@onclick>

<@onclick "studi_3">
			$('.infobox').removeClass('infobox-dark');
			$('#studi_3').addClass('infobox-dark');
			studyList('datiBase_statoCod_eq=3');
</@onclick>

<@onclick "studi_4">
			$('.infobox').removeClass('infobox-dark');
			$('#studi_4').addClass('infobox-dark');
			studyList('datiBase_statoCod_eq=4');
</@onclick>

<@onclick "studi_5">
			$('.infobox').removeClass('infobox-dark');
			$('#studi_5').addClass('infobox-dark');
			studyList('datiBase_statoCod_eq=5');
</@onclick>

<@onclick "studi_6">
			$('.infobox').removeClass('infobox-dark');
			$('#studi_6').addClass('infobox-dark');
			studyList('datiBase_statoCod_eq=6');
</@onclick>

<@onclick "studi_7">
			$('.infobox').removeClass('infobox-dark');
			$('#studi_7').addClass('infobox-dark');
			studyList('datiBase_statoCod_eq=7');
</@onclick>

<@onclick "studi_8">
			$('.infobox').removeClass('infobox-dark');
			$('#studi_8').addClass('infobox-dark');
			studyList('datiBase_statoCod_eq=8');
</@onclick>

<@onclick "studi_9">
			$('.infobox').removeClass('infobox-dark');
			$('#studi_9').addClass('infobox-dark');
			studyList('datiBase_statoCod_eq=9');
</@onclick>
-->
