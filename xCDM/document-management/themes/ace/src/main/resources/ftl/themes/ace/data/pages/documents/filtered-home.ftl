
<#global page={
	"content": path.pages+"/"+mainContent,
	"styles" : ["select2","jquery-ui-full", "datepicker", "jqgrid"],
	"scripts" : [ "select2","jquery-ui-full","bootbox" ,"datepicker", "jqgrid","pages/home.js","common/elementEdit.js", "chosen" , "spinner" , "datepicker" , "timepicker" , "daterangepicker" , "colorpicker" , "knob" , "autosize", "inputlimiter", "maskedinput", "tag"],
	"inline_scripts":[],
	"title" : "Lista",
 	"description" : "Lista" 
} />

<#global breadcrumbs=
{
	"title":"Lista oggetti",
	"links":[]
}
/>


<@script>
    
    
    <#if model['rootElements'][0].type.typeId!='reports'>
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
    
    function genericList(){
    console.log("sono qui");
		var grid_selector = "#list-grid-table";
		var pager_selector = "#list-grid-pager";
		var url=baseUrl+"/app/rest/documents/jqgrid/advancedSearch/${model['getCreatableRootElementTypes'][0].typeId}";
		var colNames=['Id','Titolo','Data creazione', 'Data modifica'];
		var colModel=[		
		  			{name:'id',index:'id', width:20, sorttype:"int",jsonmap:"id"},
					{name:'sponsor',index:'title', width:40,jsonmap:"titleString"},
					{name:'created',index:'created', width:30,formatter:TSToDate, sorttype:"date",jsonmap:"creationDt"},
					{name:'updated',index:'updated', width:30,formatter:TSToDate, sorttype:"date",jsonmap:"lastUpdateDt" }
				];
		var caption = "Lista elementi";
		setupGrid(grid_selector, pager_selector, url, colModel,colNames, caption);
	}
    
    genericList();
    <#else>
    	window.location.href='${baseUrl}/app/documents/detail/${model['rootElements'][0].id}';
    </#if>
</@script>

<@defaultSidebar/>


