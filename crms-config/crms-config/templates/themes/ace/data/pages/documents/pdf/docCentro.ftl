<#global page={
	"content": path.pages+"/"+mainContent,
	"styles" : ["select2","jquery-ui-full", "datepicker", "jqgrid","daterangepicker"],
	"scripts" : ["select2","jquery-ui-full","bootbox" ,"datepicker", "daterangepicker", "jqgrid","pages/home.js","common/elementEdit.js", "chosen" , "spinner" , "datepicker" , "timepicker" , "daterangepicker" , "colorpicker" , "knob" , "autosize", "inputlimiter", "maskedinput", "tag", "tokenInput"],
	"inline_scripts":[],
	"title" : "Ricerca Avanzata",
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
	"title":"<i class=\"icon-search\"></i> Ricerca Avanzata",
	"links":[]
}
/>

<@addmenuitem>
{
	"class":"",
	"link":"${baseUrl}/app/documents/new/21",
	"level_1":true,
	"title":"Nuovo studio",
	"icon":{"icon":"icon-folder-open","title":"Nuovo studio"}
		}
</@addmenuitem>

<@addmenuitem>
{
	"class":"",
	"link":"#",
	"level_1":true,
	"title":"Nuovo Centro",
	"icon":{"icon":"icon-hospital","title":"Nuovo centro"},
	"id": "addCenter"
		}
</@addmenuitem>

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

    function registerHooverOnTr(){
        $('.list-table tr').unbind("mouseenter");
        $('.list-table tr').unbind("mouseleave");
        $('.list-table tr').mouseenter(function(){
            $(this).css('cursor', 'pointer');
            $(this).addClass("highlightRow");
        });
        $('.list-table tr').mouseleave(function(){
            $(this).css('cursor', 'default');
            $(this).removeClass("highlightRow");
        });
    }

    function refreshStudi(result){
            $('#studi-list').html("");
            $.each(result, function(i, field){
                trContent="<td>"+field.metadata.UniqueIdStudio_id+"</td>";
                trContent+="<td>"+field.metadata.IDstudio_CodiceProt+"</td>";
                trContent+='<td>'+field.metadata.IDstudio_TitoloProt+'</td>';
                if (field.metadata.datiPromotore_promotore && field.metadata.datiPromotore_promotore[0]) {
                    trContent+='<td>'+field.metadata.datiPromotore_promotore[0].title+'</td>';
                }
                else trContent+='<td>&nbsp;</td>';
                fmt = new DateFmt("%d/%m/%y %H.%M");
                trContent+='<td>'+fmt.format(new Date(field.creationDt))+'</td>';
                if (field.lastUpdateDt!=null) trContent+='<td>'+fmt.format(new Date(field.lastUpdateDt))+'</td>';
                else trContent+='<td>&nbsp;</td>';
                $('#studi-list').append('<tr onclick="window.location.href=\'${baseUrl}/app/documents/detail/'+field.id+'\'">'+trContent+'</tr>');
            });
            registerHooverOnTr();


    }



        $("#advancedSearchForm").submit(function() {
			$('#button-search #std-label').hide();
			$('#button-search #searching-label').show();
			$('#button-search').addClass("disabled");
            var url = "${baseUrl}/app/rest/documents/advancedSearch/Studio"; // the script where you handle the form input.
            $('#studi-list').html("<img src='${baseUrl}/int/images/loading.gif'>");
            dates=$('#id-date-range-picker-1').val().split(" - ");
            $('#obj_creationDt_gteq').val(dates[0]);
            $('#obj_creationDt_lteq').val(dates[1]);
            
            $.ajax({
                type: "GET",
                url: url,
                dataType:"json",
                data: $("#advancedSearchForm").serialize(), // serializes the form's elements.
                success: function(data)
                {
                    $('#button-search #std-label').show();
					$('#button-search #searching-label').hide();
					$('#button-search').removeClass("disabled");
                    refreshStudi(data);
                }
            });
            
            return false;
        });
        
        $('#datiStudio_tipoStudio_eq').select2();
        
        $('input[name=date-range-picker]').daterangepicker({
        	format: 'DD/MM/YYYY'
        	});
        $('input[name=date-range-picker]').daterangepicker().prev().on(ace.click_event, function(){
			$(this).next().focus();
		});


</@script>


