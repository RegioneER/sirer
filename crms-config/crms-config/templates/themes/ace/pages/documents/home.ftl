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
        //prependSite='   {"match": {"metadata.IdCentro.values.PINomeCognome_CODESTRING": "${userCF}"}},'; <#--${userDetails.anaData.CODICE_FISCALE}-->//Userid? codice fiscale?
        //TENGO GLI STUDI STANDARD IN RELAZIONE ALL'AZIENDA //prependStudio='   {"match": {"children.Centro.metadata.IdCentro.values.PINomeCognome_CODESTRING": "RSLMFR61C41H769S"}},';
    }
    else if (flagSP>=0){ //STSANSVIL-742
        prependSite='{"match": {"createdBy": "${userDetails.username}"}},';
    }
    else{
	<#if userSitesCodesList?? && userSitesCodesList?size gt 0>
        prependSite='{"or":['+
		<#assign first=true/>
		<#list userSitesCodesList as site>
	        '   {"match": {"metadata.IdCentro.values.Struttura_CODESTRING": "${site}.0"}}<#if !site?is_last>,</#if>'+
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
           '   {"match": {"children.Centro.metadata.IdCentro.values.Struttura_CODESTRING": "${site}.0"}}<#if !site?is_last>,</#if>'+
        </#list>
        '  ]},';
        <#--
        prependStudio='{"bool":{ "should": ['+
        <#assign first=true/>
        <#list userSitesCodesList as site>
           
        '   {"term": {"children.Centro.metadata.IdCentro.values.Struttura_CODESTRING": "${site}.0"}}<#if !site?is_last>,</#if>'+
        </#list>
        '  ],'+
        '"minimum_should_match" : 1,'+
        '"boost" : 1.0'+
        '}},';
        -->
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



	function studyList(){
        if(flagDIR>=0){
            studyListReg();
        }
        else{
        var grid_selector = "#home-grid-table";
        var pager_selector = "#home-grid-pager";
        var url=baseUrl+"/app/rest/elk/query/jqgrid/full/studio";
        var filter='{"match_all":{}}';
        if(flagSP>=0){
            prependStudio=prependStudio.replace(",","");
            filter=prependStudio;
        }
        //var colNames=['Id','Codice','Promotore','CRO','Principal investigator'];
		var colNames=['Id','Codice','Principal investigator'];
        /*var colModel=[
                    {name:'id',index:'UniqueIdStudio_id', width:20, sorttype:"int", firstsortorder:"desc",jsonmap:"metadata.UniqueIdStudio.values.id"},
                        {name:'codice',index:'metadata.IDstudio.values.CodiceProt',width:30,jsonmap:"metadata.IDstudio.values.CodiceProt"},
                        {name:'sponsor',index:'metadata.datiPromotore.values.promotore', width:40,jsonmap:"metadata.datiPromotore.values.promotore"},
                        {name:'cro',index:'metadata.datiCRO.values.denominazione', width:40,jsonmap:"metadata.datiCRO.values.denominazione"},
                        {name:'centri',index:'centri',formatter:getCentri, width:40,jsonmap:"children.Centro"}
                ];*/
		var colModel=[
                    {name:'id',index:'UniqueIdStudio_id', width:20, sorttype:"int", firstsortorder:"desc",jsonmap:"metadata.UniqueIdStudio.values.id"},
                        {name:'codice',index:'metadata.IDstudio.values.CodiceProt',width:30,jsonmap:"metadata.IDstudio.values.CodiceProt"},
                        {name:'centri',index:'centri',formatter:getCentri, width:40,jsonmap:"children.Centro"}
                ];
        var caption = "Studi";
        fields="createdBy,metadata.IdCentro.values.Struttura";

        setupGridElk(grid_selector, pager_selector, url, filter, colModel,colNames, caption,null, fields);
    }
    }

    function getCentri(centerInput){
        if (centerInput==undefined) return "";
        idStudio='';
        centri='';
            $.each(centerInput,function(i,centro){
                if(centro.metadata.IdCentro!==undefined){
                    centri+=descrCentroElk(centro.metadata)+"<br/>";
                }
                else{
                    centri+=centro.title+"<br/>";
                }
                idStudio=centro.parent.id;
            });
            $('.placeholder_centri_'+idStudio).html(centri);
        return "<span class='placeholder_centri_"+idStudio+"'>"+centri+"</span>";
    }

    function genericCenterList(titolo, filter){
        var grid_selector = "#home-grid-table";
        var pager_selector = "#home-grid-pager";
        var url=baseUrl+"/app/rest/elk/query/jqgrid/full/centro";
        var filter=filter;
        //var colNames=['Principal Investigator','Codice studio (ID studio)','Promotore','CRO'];
        var colNames=['Principal Investigator','Codice studio (ID studio)'];
		/*var colModel=[
                        {name:'IdCentro_PI',index:'metadata.RegCentro.values.PI', width:80, formatter: descrCentroElk, sorttype:"int", jsonmap:"metadata"},
                        {name:'IDstudio_CodiceProt',index:'parent.metadata.IDstudio.values.CodiceProt',width:60,formatter:descrStudioElk,jsonmap:"parent.metadata"},
                        {name:'sponsor',index:'parent.metadata.datiPromotore.values.promotore', width:40,jsonmap:"parent.metadata.datiPromotore.values.promotore"},
                        {name:'cro',index:'parent.metadata.datiCRO.values.denominazione', width:40,jsonmap:"parent.metadata.datiCRO.values.denominazione"}
<#--{name:'created',index:'created', width:30,formatter:TSToDate, sorttype:"date",firstsortorder:"desc",jsonmap:"creationDt"},
{name:'updated',index:'lastUpdateDt', width:30,formatter:TSToDate, sorttype:"date",jsonmap:"lastUpdateDt" }-->
                    ];*/
        var colModel=[
                        {name:'IdCentro_PI',index:'metadata.IdCentro.values.PINomeCognome', width:80, sorttype:"int",formatter: descrCentroElk, jsonmap:"metadata"},
                        {name:'IDstudio_CodiceProt',index:'parent.metadata.IDstudio.values.CodiceProt',width:60,formatter:descrStudioElk,jsonmap:"parent.metadata"}
                    ];
        var caption = titolo;
        setupGridElk(grid_selector, pager_selector, url,filter, colModel,colNames, caption);

    }

    function genericProgettiList(titolo, filter){
        var grid_selector = "#home-grid-table";
        var pager_selector = "#home-grid-pager";
        var url=baseUrl+"/app/rest/elk/query/jqgrid/full/progetto";
        var filter=filter;
        var colNames=['Titolo progetto','Codice progetto', 'Strutture'];
        var colModel=[
                        {name:'Progetto_titolo',index:'metadata.Progetto.values.titolo', width:80, jsonmap:"metadata.Progetto.values.titolo"},
                        {name:'Progetto_codice',index:'metadata.Progetto.values.codice', width:80, sorttype:"int", jsonmap:"metadata.Progetto.values.codice"},
                        {name:'Progetto_Strutture',index:'metadata.Progetto.values.Strutture', width:80, jsonmap:"metadata.Progetto.values.Strutture"}
                    ];
        var caption = titolo;
        setupGridElk(grid_selector, pager_selector, url,filter, colModel,colNames, caption);

    }

///////// FILTRI ELK /////////////

	//HDCRPMS-142 13.04.2017 vmazzeo ***INIZIO***
    //var approvCeFilter='{"missing": {"field": "children.Contratto.metadata.ApprovDADSRETT.values"}},{"missing": {"field": "children.Contratto.metadata.ApprovDADSRETT2.values"}},{"match": {"children.ParereCe.metadata.ParereCe.values.esitoParere": "Parere favorevole"}}';
    var approvCeFilter=prependSite+'{"match" : { "metadata.statoValidazioneCentro.values.parereCEPositivo":1 }}';
    
   var approvCeFilter=prependSite+'{ "or" :[{"match" : { "metadata.statoValidazioneCentro.values.parereCEPositivo":1 }},{ "and" : [{"match" : { "children.ParereCe.metadata.ParereCe.values.ParereWFinviato":1 }},{"match" : { "children.ParereCe.metadata.ParereCe.values.esitoParere_CODE":4 }}]}]}';
    var sospesiCeFilter=prependSite+'{"missing" : { "field" : "metadata.statoValidazioneCentro.values.idParereCE" }},{"match" : { "children.ParereCe.metadata.ParereCe.values.ParereWFinviato":1 }}, {"match" : { "children.ParereCe.metadata.ParereCe.values.esitoParere_CODE":2 }}';
    var contrariCeFilter=prependSite+'{"exists" : { "field" : "metadata.statoValidazioneCentro.values.idParereCE" }},{"match" : { "metadata.statoValidazioneCentro.values.parereCEPositivo":0 }}';
    var chiusiFilter=prependSite+'{"range": {"children.ChiusuraCentro.metadata.DatiChiusuraCentro.values.dataConclusioneCentro": {"gte": "01/01/1970","format": "dd/MM/yyyy"}}}'
    var monitorFilter=prependSite+'{"exists" : { "field" : "children.AvvioCentro.metadata.DatiAvvioCentro.values.dataAperturaCentro" }},{"missing" : { "field" : "children.ChiusuraCentro.metadata.DatiChiusuraCentro.values.dataConclusioneCentro" }}';
    var fatturazioneFilter=prependSite+'{"match" : { "children.Fatturazione.metadata.StatoScheduling.values.Iniziato":1 }},{"missing" : { "field" : "metadata.RitiroCentroWF.values.dataChiusuraAmm" }}';
    var contrattoFilter=prependSite+'{"match": {"metadata.ValiditaCTC.values.val_CODE":1}},'+
          '{"missing": {"field": "children.Contratto.metadata.ApprovDADSRETT.values.dataFirma"}},'+
         '{"missing": {"field": "children.Contratto.metadata.ApprovDADSRETT2.values.dataFirma2"}},'+
         '{"exists": {"field": "children.Contratto"}}';

    var budgetFilter=prependSite+' {"or":['+
    '   {"exists": {"field": "children.Budget.id"}},'+
    '   {"exists": {"field": "children.BudgetBracci.id"}}'+
    '  ]},'+
    '  {"or":['+
    '   {"missing": {"field": "metadata.statoValidazioneCentro.values.idBudgetApproved"}},'+
    '   {"script":{'+
    '       "script": "if (doc[\'metadata.statoValidazioneCentro.values.idBudgetApproved\'].value==null) return (true) else return (doc[\'children.Budget.id\'].value>doc[\'metadata.statoValidazioneCentro.values.idBudgetApproved\'].value.toInteger())"'+
    '   }},'+
    '    {"script":{'+
    '       "script": "if (doc[\'metadata.statoValidazioneCentro.values.idBudgetApproved\'].value==null) return (true) else return (doc[\'children.BudgetBracci.id\'].value>doc[\'metadata.statoValidazioneCentro.values.idBudgetApproved\'].value.toInteger())"'+
    '   }}'+
    ' ]},'+
    '{"missing": {"field": "metadata.RitiroCentroWF.values.dataRitiro"}}';
	var userGroup="${getUserGroups(userDetails)}";
	userGroup=userGroup.replace(/[0-9]/g, '*').toLowerCase();
    //TEST QUI
    //var studiInsRegFilter=prependSite+'{"and" : [{"match_all":{}}]}'; //+'{"query": {"bool": {"must": [{ "wildcard": {"metadata.UniqueIdStudio.values.cto_NOTANALYZED": "'+userGroup+'"}}]}}}';
    //var studiInsRegFilter=prependStudio.replace(/(^,)|(,$)/g, ""); //prependSite+'{"and" : [{"match_all":{}}]}'; //+'{"query": {"bool": {"must": [{ "wildcard": {"metadata.UniqueIdStudio.values.cto_NOTANALYZED": "'+userGroup+'"}}]}}}';
    var studiInsRegFilter=prependStudio;
    if(flagSP>=0){
        studiInsRegFilter=studiInsRegFilter.replace(",","");
    }
    else {
        studiInsRegFilter+='{"and" : [{"match_all":{}}]}'; //+'{"query": {"bool": {"must": [{ "wildcard": {"metadata.UniqueIdStudio.values.cto_NOTANALYZED": "'+userGroup+'"}}]}}}';
    }

    var quarantenaFilter=prependSite+'{"and" : [{"match": {"metadata.statoValidazioneCentro.values.valCTC": "positiva"}} , {"missing": {"field" : "metadata.statoValidazioneCentro.values.idIstruttoriaCEPositiva"}}] }';

    var feasibilityFilter=prependSite+'{"missing": {"field" : "metadata.statoValidazioneCentro"}}';
    var ritiratiFilter=prependSite+'{"range": {"metadata.RitiroCentroWF.values.dataRitiro": {"gte": "01/01/1970","format": "dd/MM/yyyy"}}}';

    //var emendamentoFilter='{"range": {"metadata.RitiroCentroWF.values.dataRitiro": {"gte": "01/01/1970","format": "dd/MM/yyyy"}}}';
    var emendamentoFilter=prependSite+'{"exists": {"field": "children.Emendamento"}}';

    var tuttiCentriFilter = prependSite;
    if(flagSP>=0){
        tuttiCentriFilter=tuttiCentriFilter.replace(",","");
    }
    else {
        tuttiCentriFilter+='{match_all:{}}';
    }

//////////////////////////////////

    var tuttiProgettiFilter = '{match_all:{}}';
    if(flagSP>=0){
        prependSite=prependSite.replace(",","");
        tuttiProgettiFilter =  prependSite;
    }
    function progettiList(){
        genericProgettiList('Progetti', tuttiProgettiFilter);
    }
/////////////////////////////////










    function centriList(){
        genericCenterList('Centri', tuttiCentriFilter);
    }

    function feasabilityList(){
        genericCenterList('Feasibility', feasibilityFilter);
    }

    function budgetList(){
        genericCenterList('Centri con budget aperti', budgetFilter);
    }


    function contrattoList(){
        genericCenterList('Centri con contratti non firmati', contrattoFilter);
    }

    function approvatoCeList(){
        genericCenterList('Centri con appovazione CE', approvCeFilter);
    }

    function sospesoCeList(){
        genericCenterList('Centri con sospensione CE', sospesiCeFilter);
    }

    function nonapprovatoCeList(){
        genericCenterList('Centri non approvati da CE', contrariCeFilter);
    }

    function chiusiList(){
        genericCenterList('Centri chiusi', chiusiFilter);
    }


    function emendamentoList(){
        genericCenterList('Centri con emendamento', emendamentoFilter);
    }
    function ritiratiList(){
        genericCenterList('Centri ritirati', ritiratiFilter);
    }

    function studiFattList(){
        genericCenterList('Fatturazione', fatturazioneFilter);
    }


    function monitorList(){
        genericCenterList('Monitoraggio', monitorFilter);
    }


    function centriListIstruttoria(){
        genericCenterList('Quarantena', quarantenaFilter);
    }




    function studyListReg(){
        var grid_selector = "#home-grid-table";
        var pager_selector = "#home-grid-pager";
        var url=baseUrl+"/app/rest/elk/query/jqgrid/full/studio";
        var filter=studiInsRegFilter;
        var colNames=['Id','Codice','Principal investigator'];
        /*var colModel=[
                    {name:'id',index:'UniqueIdStudio_id', width:20, sorttype:"int", firstsortorder:"desc",jsonmap:"metadata.UniqueIdStudio.values.id"},
                        {name:'codice',index:'metadata.IDstudio.values.CodiceProt',width:30,jsonmap:"metadata.IDstudio.values.CodiceProt"},
                        {name:'sponsor',index:'metadata.datiPromotore.values.promotore', width:40,jsonmap:"metadata.datiPromotore.values.promotore"},
                        {name:'cro',index:'metadata.datiCRO.values.denominazione', width:40,jsonmap:"metadata.datiCRO.values.denominazione"},
                        {name:'centri',index:'centri',formatter:getCentri, width:40,jsonmap:"children.Centro"}
                ];*/
        var colModel=[
            {name:'id',index:'UniqueIdStudio_id', width:20, sorttype:"int", firstsortorder:"desc",jsonmap:"metadata.UniqueIdStudio.values.id"},
            {name:'codice',index:'metadata.IDstudio.values.CodiceProt',width:30,jsonmap:"metadata.IDstudio.values.CodiceProt"},
            {name:'centri',index:'centri',formatter:getCentri, width:40,jsonmap:"children.Centro"}
        ];
        var caption = "Studi";
        fields="createdBy,metadata.IdCentro.values.Struttura";

        setupGridElk(grid_selector, pager_selector, url, filter, colModel,colNames, caption,null, fields);
    }


	//HDCRPMS-142 13.04.2017 vmazzeo ***FINE***

	$('#addCenter').click(function(){AddCenter();});
	/*
	$('#select_study').modal();
	*/
	function AddCenter(){
		$('#modalAddCenter').modal();
	    setTimeout("$('#select_study').select2(\"open\");",500);
	}
    if($.isFunction('select2')){
    $('#select_study').select2({
			minimumInputLength: 1,
			maximumSelectionSize: 1,
			containerCssClass:'select2-ace',
			allowClear: true,
			ajax: {
					url:'${baseUrl}/app/rest/documents/advancedSearch/Studio',
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

	$('#select_study').on("select2-selecting", function(e) {
		window.location.href='${baseUrl}/app/documents/addChild/'+e.val+'/Centro';
	});

    if(flagSP>=0){
        prependStudio=prependStudio.replace(",","");
        ajaxCountPopulateElk($('#studi_ins .infobox-data-number'), 'Studio',prependStudio);
    }
    else if(flagDIR>=0){ //STSANSVIL-712
        ajaxCountPopulateElk($('#studi_ins .infobox-data-number'), 'Studio',studiInsRegFilter);
    }
    else{
        ajaxCountPopulateElk($('#studi_ins .infobox-data-number'), 'Studio');
    }
    ajaxCountPopulateElk($('#studi_ins_reg .infobox-data-number'), 'Studio',studiInsRegFilter);
    ajaxCountPopulateElk($('#centri_ins_istruttoria .infobox-data-number'), 'Centro',quarantenaFilter);
    ajaxCountPopulateElk($('#feasibility .infobox-data-number'), 'Centro', feasibilityFilter);
    ajaxCountPopulateElk($('#budget .infobox-data-number'), 'Centro', budgetFilter);
    ajaxCountPopulateElk($('#contratto .infobox-data-number'), 'Centro', contrattoFilter);
    ajaxCountPopulateElk($('#approvati_ce .infobox-data-number'), 'Centro', approvCeFilter);
    ajaxCountPopulateElk($('#sospesi_ce .infobox-data-number'), 'Centro', sospesiCeFilter);
    ajaxCountPopulateElk($('#nonapprovati_ce .infobox-data-number'), 'Centro', contrariCeFilter);
    ajaxCountPopulateElk($('#studi_fatt .infobox-data-number'), 'Centro', fatturazioneFilter);
    ajaxCountPopulateElk($('#tutti_centri .infobox-data-number'), 'Centro', tuttiCentriFilter);
    ajaxCountPopulateElk($('#centri_emendamento .infobox-data-number'), 'Centro', emendamentoFilter);
    ajaxCountPopulateElk($('#centri_ritirati .infobox-data-number'), 'Centro', ritiratiFilter);
    ajaxCountPopulateElk($('#centri_chiusi .infobox-data-number'), 'Centro', chiusiFilter);
    ajaxCountPopulateElk($('#centri_monitor .infobox-data-number'), 'Centro', monitorFilter);
    ajaxCountPopulateElk($('#progetti_totali .infobox-data-number'), 'Progetto',tuttiProgettiFilter);

	//HDCRPMS-142 13.04.2017 vmazzeo ***FINE***
	$('.infobox').removeClass('infobox-dark');

	$('#studi_ins').addClass('infobox-dark');
	studyList();

</@script>

<div class="home-container" >

		<style>
		
		.ui-jqgrid tr.jqgrow td {
			white-space:normal;
		}
		.ui-jqgrid .ui-jqgrid-htable th div {
			white-space:normal;
			height:auto;
			margin-bottom:3px;
		}
	
		
		.home-table .ui-jqgrid{
			margin:10px;
			
		}
		
		tr.jqgrow{
			cursor:pointer;
		}
		
		.home-table {
			float:left;
		}
		.infobox {
			cursor:pointer;
		}
		
		</style>
		<@script>
			var $path_base = "${path.base}";//this will be used in gritter alerts containing images
		</@script>
	<div class="col-sm-12 infobox-container">
		<@infobox "studi_ins" "icon icon-folder-open" "blue" "Studi in BD Regionale"  "Lista di tutti gli studi inseriti a livello regionale" />
		<@infobox "studi_ins_reg" "icon icon-folder-open" "blue" "Studi in BD Aziendale"  "Lista di tutti gli studi inseriti a livello aziendale" />
		<@infobox "tutti_centri" "icon icon-folder-open" "pink" "Centri coinvolti"  "Lista centri con coinvolgimento diretto" />
		<@infobox "feasibility" "icon icon-file-text" "green" "Fattibilit&agrave;" "Centri con fattibilit&agrave; non ancora inviata" />
		<@infobox "centri_ins_istruttoria" "icon icon-folder-open" "red" "Centri in Istruttoria"  "Lista dei centri in ISTRUTTORIA" />
		<#-- <@infobox "budget" "icon icon-signal" "orange" "Budget" "Centri con budget creato non ancora chiuso" /> -->
		<#-- <@infobox "contratto" "icon icon-legal" "red" "Contratto" "Centri con valutazione CTC inserita ma con contratto non ancora firmato" /> -->
		<#-- <@infobox "valutazione_ce" "icon icon-comments" "orange2" "Valutazione CE" "Centri inviati al CE ma con parere mancante o sospensivo" /> -->
		<@infobox "approvati_ce" "icon icon-group" "brown" "Approvati CE" "Centri con parere favorevole/favorevole a condizione/presa d'atto ma senza contratto firmato" />
		<@infobox "sospesi_ce" "icon icon-group" "orange" "Sospesi CE" "Centri con parere sospensivo" />
		<@infobox "nonapprovati_ce" "icon icon-group" "red" "Non approvati CE" "Centri con parere non favorevole" />
		<#-- <@infobox "studi_fatt" "icon icon-eur" "blue2" "Fatturazione"  "Centri con fatturazione attivata ma non ancora chiusi" /> -->
		<@infobox "centri_monitor" "icon icon-stethoscope" "purple" "Aperti" "Centri aperti ma non ancora chiusi"/>
		<@infobox "centri_emendamento" "icon icon-ban-circle" "orange" "Emendamento" "Centri con emendamento"/>
		<@infobox "centri_chiusi" "icon icon-ban-circle" "grey" "Chiusi" "Centri con chiusura amministrativa"/>
		<@infobox "centri_ritirati" "icon icon-lock" "black" "Ritirati" "Centri ritirati"/>
		<@infobox "progetti_totali" "icon icon-lock" "red" "Progetti" "Progetti totali"/>
	</div>
	<div class="col-sm-12">
        <div id="quarantena" class="alert alert-block alert-danger" style="display: none">
            <i class="fa fa-exclamation-circle red"></i> Sono presenti centri in quarantena!
        </div>	
    </div>
		
		
		<span class="home-table" >
		<table id="home-grid-table" class="grid-table" ></table>
			<div id="home-grid-pager"></div>
		</span>
		<@modalbox "modalAddCenter" "<i class='icon-hospital'></i> Aggiungi un nuovo centro" "Seleziona lo studio: <input id='select_study' name='select_study'/>" ""/>
		
	
		
<#assign title>
<span>Clinical Research Management System</span>
Benvenuto ${user.name}
</#assign>
<#assign body>
<#attempt>
	<#include "splash/${getUserGroups(userDetails)}.ftl"/>
	<#recover>
	<#include "splash/default.ftl"/>
</#attempt>
</#assign>


<#assign footer>
<button id='splash-close' class="btn btn-xs pull-left">Chiudi</button>
disattiva finestra di benvenuto
<input id="splash-disable" class="ace ace-switch ace-switch-6" type="checkbox" name="switch-field-1">
<span class="lbl"></span>
</#assign>

<@script>


$('#splash-close').click(function(){
	$('#splash-home').modal("hide");
	
});

if (document.cookie.indexOf("splashDisabled") >= 0) {
	  
}else {
	//$('#splash-home').modal();
}

$('#splash-disable').click(function(){
	//$('#splash-home').modal("hide");
	document.cookie = "splashDisabled=true; max-age=" + 60 * 60 * 24 * 365 * 2; // 60 seconds to a minute, 60 minutes to an hour, 24 hours to a day, and 10 days.
});


var inquarantena=ajaxCountPopulateRetVal('Centro','Quarantena_quarantena_eq=1###Si');
if(inquarantena>0){
   $('#quarantena').show(); 
}


</@script>

<@modalbox "splash-home" title body footer/>
		
		
 </div>
