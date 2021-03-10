<#global page={
    "content": path.pages+"/"+mainContent,
    "styles" : ["select2","jquery-ui-full", "datepicker", "jqgrid","daterangepicker"],
    "scripts" : ["select2","jquery-ui-full","bootbox" ,"datepicker", "daterangepicker", "jqgrid","pages/home.js","common/elementEdit.js", "chosen" , "spinner" , "datepicker" , "timepicker" , "daterangepicker" , "colorpicker" , "knob" , "autosize", "inputlimiter", "maskedinput", "tag", "tokenInput"],
    "inline_scripts":[],
    "title" : "Ricerca Avanzata",
    "description" : "Dynamic tables and grids using jqGrid plugin" 
} />
<#assign userSitesList=[] />
<#if userDetails.getSitesID()??>
<#assign userSitesList=userDetails.getSitesID() />
</#if>

<#assign userSitesCodesList=[] />
<#if userDetails.getSitesCodes()??>
<#assign userSitesCodesList=userDetails.getSitesCodes() />
</#if>

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

.table-responsive tr {
    cursor:pointer;
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
    var currentUserGroups="${getUserGroups(userDetails)}";
    var flagPI = currentUserGroups.indexOf("PI");
    var flagSP = currentUserGroups.indexOf("SP");
    var flagDIR = currentUserGroups.indexOf("DIR");//STSANSVIL-712 DIR vede sempre e solo i suoi anche in BOX Studi in BD Regionale
    var prependSite=''; //OK?!
    var prependStudio='';
    <#assign userCF = userDetails.username />
    <#if userDetails.getAnaDataValue('CODICE_FISCALE')?? >
        <#assign userCF = userDetails.getAnaDataValue('CODICE_FISCALE') />
    </#if>
    if (flagPI>=0){
        prependSite='{"or":['+
        <#assign first=true/>
        <#list userSitesCodesList as site>
            '   {"match": {"metadata.IdCentro.values.PINomeCognome_CODESTRING": "${userCF}"}},'+
            '   {"match": {"createdBy": "${userDetails.username}"}}<#if !site?is_last>,</#if>'+
        </#list>
        '  ]},';
    }
    else if (flagSP>=0){ //STSANSVIL-742
        prependSite='{"match": {"createdBy": "${userDetails.username}"}},';
    }
    else{
        <#if userSitesCodesList?? && userSitesCodesList?size gt 0>
            prependSite='{"or":['+
            <#assign first=true/>
            <#list userSitesCodesList as site>
                <#if first>
                    <#assign first=false/>
                <#else>
                ','+
                </#if>
                '   {"match": {"metadata.IdCentro.values.Struttura_CODESTRING": "${site}.0"}}'+
            </#list>
            '  ]},';
        </#if>
    }
    if(flagSP>=0){
        prependStudio='{"match": {"createdBy": "${userDetails.username}"}},';
    }
    else{
        <#if userSitesCodesList?? && userSitesCodesList?size gt 0>
            prependStudio='{"or":['+
            <#assign first=true/>
            <#list userSitesCodesList as site>
                <#if first>
                    <#assign first=false/>
                <#else>
                    ','+
                </#if>
                '   {"match": {"children.Centro.metadata.IdCentro.values.Struttura_CODESTRING": "${site}.0"}}'+
            </#list>
            '  ]},';
        </#if>
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

    registerHooverOnTr();



        //TOSCANA-195
        $("#advancedSearchForm").submit(function() {
            var grid_selector = "#studi-list-grid-table";
            var pager_selector = "#studi-list-grid-pager";
            var url=baseUrl+"/app/rest/elk/query/jqgrid/full/studio";
            var filter=prependStudio;
            if(flagDIR>=0){
                var studiInsRegFilter='';
                studiInsRegFilter+='{"and" : [{"match_all":{}}]}'; //+'{"query": {"bool": {"must": [{ "wildcard": {"metadata.UniqueIdStudio.values.cto_NOTANALYZED": "'+userGroup+'"}}]}}}';
                filter+=studiInsRegFilter;
            }
            else if(flagSP>=0){
                prependStudio=prependStudio.replace(",","");
                filter+=prependStudio;
            }
            var anyFilter=false;//<< porta in -ctms
            if(prependStudio!=""){
                anyFilter=true;
            }
            if($("#UniqueIdStudio_id_like").val()!=""){

                if(anyFilter){
                filter+=',';
            }
                filter+='{"match":{"metadata.UniqueIdStudio.values.id":'+$("#UniqueIdStudio_id_like").val()+'}}';
                anyFilter=true;
            }
            if($("#IDstudio_CodiceProt_like").val()!=""){

                if(anyFilter){
                    filter+=',';
                }
                filter+='{"match":{"metadata.IDstudio.values.CodiceProt":"'+$("#IDstudio_CodiceProt_like").val()+'"}}';
                anyFilter=true;
            }
            if($("#IDstudio_TitoloProt_like").val()!=""){
                if(anyFilter){
                    filter+=',';
                }
                filter+='{"match":{"metadata.IDstudio.values.TitoloProt":"'+$("#IDstudio_TitoloProt_like").val()+'"}}';
                anyFilter=true;
            }
            if($("#datiPromotore_promotore_eq").val()!=""){
                if(anyFilter){
                    filter+=',';
                }
                filter+='{"match":{"children.PromotoreStudio.metadata.datiPromotore.values.promotore_ELID":"'+$("#datiPromotore_promotore_eq").val()+'"}}';
                anyFilter=true;
            }
            if($("#datiCRO_denominazione_eq").val()!=""){
                if(anyFilter){
                    filter+=',';
                }
                filter+='{"match":{"children.CROStudio.metadata.datiCRO.values.denominazione_ELID":"'+$("#datiCRO_denominazione_eq").val()+'"}}';
                anyFilter=true;
            }
            if($("#datiStudio_eudractNumber_eq").val()!=""){
                if(anyFilter){
                    filter+=',';
                }
                filter+='{"match":{"metadata.datiStudio.values.eudractNumber_NOTANALYZED":"'+$("#datiStudio_eudractNumber_eq").val()+'"}}';
                anyFilter=true;
            }else if($("#datiStudio_tipoStudio_eq").val()!=""){ //metto in else eudractNumber e tipoStudio perchè se ho l'eudract voglio cercare solo per eudract e non pure per tipo studio
                if(anyFilter){
                    filter+=',';
                }
                filter+='{"match":{"metadata.datiStudio.values.tipoStudio_CODE":"'+$("#datiStudio_tipoStudio_eq").val()+'"}}';
                anyFilter=true;
            }

            if($("#datiStudio_AreaTematicaPrincipale_eq").val()!=""){
                if(anyFilter){
                    filter+=',';
                }
                filter+='{"match":{"metadata.datiStudio.values.AreaTematicaPrincipale_CODESTRING":"'+$("#datiStudio_AreaTematicaPrincipale_eq").val()+'.0"}}';
                anyFilter=true;
            }

            if($("#id-date-range-picker-1").val()!=""){
                var dates=$('#id-date-range-picker-1').val().split(" - ");
                date_gte=dates[0];
                date_lte=dates[1];
                filter+='{"range":{"createdOn":{"gte":"'+date_gte+'||/d","lte":"'+date_lte+'||/d","format":"dd/MM/yyyy"}}}';


                anyFilter=true;
            }


            if(!anyFilter){
                filter='{"match_all":{}}';
            }
            var colNames=['Id','Codice','Titolo','Data Creazione','Data Ultima modifica'];//'Promotore',

            var colModel=[
                {name:'id',index:'UniqueIdStudio_id', width:20, sorttype:"int", firstsortorder:"desc",jsonmap:"metadata.UniqueIdStudio.values.id"},
                {name:'codice',index:'IDstudio_CodiceProt',width:30,jsonmap:"metadata.IDstudio.values.CodiceProt"},
                {name:'titolo',index:'IDstudio_TitoloProt',formatter:toLength,  width:70,jsonmap:"metadata.IDstudio.values.TitoloProt"},
                {name:'created',index:'created', width:30,formatter:TSToDate, sorttype:"date",firstsortorder:"desc",jsonmap:"createdOn"},
                {name:'updated',index:'updated', width:30,formatter:TSToDate, sorttype:"date",jsonmap:"updatedOn" }
            ];//{name:'sponsor',index:'datiPromotore_promotore', width:40,jsonmap:"children.PromotoreStudio.metadata.datiPromotore.values.promotore"},
            var caption = "Risultati della ricerca";
            fields="createdBy,metadata.IdCentro.values.Struttura";
            setupGridElk(grid_selector, pager_selector, url, filter, colModel,colNames, caption,null, fields);

            return false;
        });


        /*

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
        });*/
        
        $('#datiStudio_tipoStudio_eq').select2();
        
        $('input[name=date-range-picker]').daterangepicker({
            format: 'DD/MM/YYYY',
            locale: {
                cancelLabel: 'Annulla',
                applyLabel: 'Applica'
             }
            });
        $('input[name=date-range-picker]').daterangepicker().prev().on(ace.click_event, function(){
            $(this).next().focus();
        });
        
        /*
        function refreshCentri(result){
            $('#centri-list').html("");
            $.each(result, function(i, field){
                trContent="<td>"+field.parent.metadata.UniqueIdStudio_id[0]+"</td>";
                
                if (field.metadata.IdCentro_Struttura && field.metadata.IdCentro_Struttura[0]){
                    trContent+="<td>"+field.metadata.IdCentro_Struttura[0].replace(/^.*###/,"")+"</td>";    
                }
                else trContent+='<td>&nsbp;</td>';
                
                if (field.metadata.IdCentro_UO && field.metadata.IdCentro_UO[0]){
                    trContent+="<td>"+field.metadata.IdCentro_UO[0].replace(/^.*###/,"")+"</td>";
                }
                else trContent+='<td>&nsbp;</td>';
                
                if (field.metadata.IdCentro_PI && field.metadata.IdCentro_PI[0]){
                    trContent+="<td>"+field.metadata.IdCentro_PI[0].replace(/^.*###/,"")+"</td>";
                }
                else trContent+='<td>&nbsp;</td>';
                
                fmt = new DateFmt("%d/%m/%y");
                if (field.metadata.DatiCentro_InizioDt && field.metadata.DatiCentro_InizioDt[0]){
                    trContent+='<td>'+fmt.format(new Date(field.metadata.DatiCentro_InizioDt[0]))+'</td>';
                }
                else trContent+='<td>&nbsp;</td>';
                
                if (field.metadata.DatiCentro_FineDt && field.metadata.DatiCentro_FineDt[0]){
                    trContent+='<td>'+fmt.format(new Date(field.metadata.DatiCentro_FineDt[0]))+'</td>';
                }
                else trContent+='<td>&nbsp;</td>';
                $('#centri-list').append('<tr onclick="window.location.href=\'${baseUrl}/app/documents/detail/'+field.id+'\'">'+trContent+'</tr>');
            });
            registerHooverOnTr();


    }
        
        $("#advancedSearchFormCentro").submit(function() {
            $('#button-searchCentro #std-label').hide();
            $('#button-searchCentro #searching-label').show();
            $('#button-searchCentro').addClass("disabled");
            var url = "${baseUrl}/app/rest/documents/advancedSearch/Centro"; // the script where you handle the form input.
            $('#centri-list').html("<img src='${baseUrl}/int/images/loading.gif'>");
            dates=$('#id-date-range-picker-5').val().split(" - ");
            $('#DatiCentro_InizioDt_gteq').val(dates[0]);
            $('#DatiCentro_InizioDt_lteq').val(dates[1]);
            dates=$('#id-date-range-picker-6').val().split(" - ");
            $('#DatiCentro_FineDt_gteq').val(dates[0]);
            $('#DatiCentro_FineDt_lteq').val(dates[1]);
            $.ajax({
                type: "GET",
                url: url,
                dataType:"json",
                data: $("#advancedSearchFormCentro").serialize(), // serializes the form's elements.
                success: function(data)
                {
                    $('#button-searchCentro #std-label').show();
                    $('#button-searchCentro #searching-label').hide();
                    $('#button-searchCentro').removeClass("disabled");
                    refreshCentri(data);
                }
            });
            
            return false;
        });
        */
        //TOSCANA-195
        $("#advancedSearchFormCentro").submit(function() {
            var grid_selector = "#centri-list-grid-table";
            var pager_selector = "#centri-list-grid-pager";
            var url=baseUrl+"/app/rest/elk/query/jqgrid/full/centro";
            var filter = prependSite;
            if(flagSP>=0 || flagDIR>=0){
                filter=filter.replace(",","");
            }
            var anyFilter=true;
            if($("#IdCentro_Struttura_eq").val()!=""){
                if(anyFilter){
                filter+=',';
            }
                filter+='{"match":{"metadata.IdCentro.values.Struttura_CODESTRING":"'+$("#IdCentro_Struttura_eq").val()+'.0"}}';
                anyFilter=true;
            }
            if($("#IdCentro_UO_eq").val()!=""){
                if(anyFilter){
                    filter+=',';
                }
                filter+='{"match":{"metadata.IdCentro.values.UO":"'+$("#IdCentro_UO_eq :selected").html()+'"}}';
                anyFilter=true;
            }
            if($("#IdCentro_PI_eq").val()!=""){
                if(anyFilter){
                    filter+=',';
                }
                filter+='{"match":{"metadata.IdCentro.values.PINomeCognome_CODESTRING":"'+$("#IdCentro_PI_eq").val()+'"}}';
                anyFilter=true;
            }
            if($("#IstruttoriaCE_DelibNum").val()!=""){
                if(anyFilter){
                    filter+=',';
                }
                filter+='{"match":{"metadata.statoValidazioneCentro.values.delibNumIstrCEPositiva":"'+$("#IstruttoriaCE_DelibNum").val()+'"}}';
                anyFilter=true;
            }
            if($("#id-date-range-picker-5").val()!=""){
                var dates=$('#id-date-range-picker-5').val().split(" - ");
                date_gte=dates[0];
                date_lte=dates[1];
                if(anyFilter){
                    filter+=',';
                }
                filter+='{"range":{"metadata.DatiCentro.values.InizioDt":{"gte":"'+date_gte+'||/d","lte":"'+date_lte+'||/d","format":"dd/MM/yyyy"}}}';
                anyFilter=true;
            }
            if($("#id-date-range-picker-6").val()!=""){
                var dates=$('#id-date-range-picker-6').val().split(" - ");
                date_gte=dates[0];
                date_lte=dates[1];
                if(anyFilter){
                    filter+=',';
                }
                filter+='{"range":{"metadata.DatiCentro.values.FineDt":{"gte":"'+date_gte+'||/d","lte":"'+date_lte+'||/d","format":"dd/MM/yyyy"}}}';
                anyFilter=true;
            }

            if(!anyFilter){
            filter='{"match_all":{}}';
            }
var colNames=['Id Studio','Codice studio/protocollo assegnato dal CE:','Azienda sede dello studio','Unit&agrave; operativa','Principal investigator','Data prevista di inizio studio nel centro','Data prevista di fine studio nel centro'];//

            var colModel=[
            {name:'id',index:'UniqueIdStudio_id', width:20, sorttype:"int", firstsortorder:"desc",jsonmap:"parent.metadata.UniqueIdStudio.values.id"},
{name:'DelibNumCE',index:'statoValidazioneCentro_delibNumIstrCEPositiva',width:30,jsonmap:"metadata.statoValidazioneCentro.values.delibNumIstrCEPositiva"},
            {name:'IdCentro_Struttura',index:'IdCentro_Struttura', width:80, jsonmap:"metadata.IdCentro.values.Struttura"},
            {name:'IdCentro_UO',index:'IdCentro_UO',width:80,jsonmap:"metadata.IdCentro.values.UO"},
            {name:'IdCentro_PI',index:'IdCentro_PI',formatter:toLength,  width:70,jsonmap:"metadata.IdCentro.values.PINomeCognome"},
            {name:'DatiCentro_InizioDt',index:'DatiCentro_InizioDt', width:30,formatter:TSToDate,jsonmap:"metadata.DatiCentro.values.InizioDt"},
            {name:'DatiCentro_FineDt',index:'DatiCentro_FineDt', width:30,formatter:TSToDate,jsonmap:"metadata.DatiCentro.values.FineDt"}
            ];
            var caption = "Risultati della ricerca";
            fields="createdBy,metadata.IdCentro.values.Struttura";
            setupGridElk(grid_selector, pager_selector, url, filter, colModel,colNames, caption,null, fields);
        
            return false;
        });
        //$('#datiStudio_tipoStudio_eq').select2();
       
        $('input[name^="date-range-picker"]').daterangepicker({
            format: 'DD/MM/YYYY',
             locale: {
                cancelLabel: 'Annulla',
                applyLabel: 'Applica'
             }
            });
        $('input[name^=date-range-picker]').daterangepicker().prev().on(ace.click_event, function(){
            $(this).next().focus();
        });

var resize=function(grid_selector){
jQuery(grid_selector).setGridWidth(((jQuery(grid_selector).closest('.home-container').width())-40));
}    ;
</@script>


