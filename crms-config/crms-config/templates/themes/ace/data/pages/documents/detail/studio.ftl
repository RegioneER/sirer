<#assign type=model['docDefinition']/>
<#global page={
	"content": path.pages+"/"+mainContent,
	"styles" : ["jquery-ui-full", "datepicker","pages/studio.css","x-editable","jqgrid"],
	"scripts" : ["jquery-ui-full","datepicker","bootbox", "token-input" ,"common/elementEdit.js","x-editable","jqgrid","pages/home.js","xCDM-modal"],
	"inline_scripts":[],
	"title" : "Dettaglio studio",
 	"description" : "Dettaglio studio"
} />
<#assign elStudio=el />
<#include "../../partials/navigation/navigazione_studio.ftl">
<#include "../../partials/form-elements/elementSpecific.ftl">
<#include "../../partials/form-elements/select.ftl" />
<@breadcrumbsData el />

<#--assign json="{}" /-->
<#--assign loadedJson="{}" /-->

<#assign json=el.type.getDummyJson() />
<#assign loadedJson=el.getElementCoreJsonToString(userDetails) />




<#--LUIGI controllo per evitare di lanciare javascript a scheda chiusa-->
<#assign updating=elStudio.getUserPolicy(userDetails).isCanUpdate()/>
<#list elStudio.getElementTemplates() as elementTemplate>
	<#if elementTemplate.getMetadataTemplate().getName()=='datiStudio'>
		<#assign updating=(updating && elementTemplate.getUserPolicy(userDetails, elStudio).isCanUpdate())>
	</#if>
</#list>



<@script>
$('label.col-sm-3').removeClass('col-sm-3');
	$('.col-sm-9').removeClass('col-sm-9');
	$('.col-sm-12').removeClass('col-sm-12');
	$.fn.editable.defaults.mode = 'inline';

 	var loadedElement=${loadedJson};
 	var dummy=${json};
 	var empties=new Array();

 	empties[dummy.type.id]=dummy;
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

//Hack da cercare//
	<#--LUIGI controllo per evitare di lanciare javascript a scheda chiusa e controllo se ci sono emendamenti in corso-->
	var updating=<#if updating >true<#else>false</#if>;
	<#if userDetails.getEmeSessionId()??>
		updating=true;
	</#if>

	if (updating){
		$('#datiStudio_tipoStudio-select').change(function(){gestFase();});
		gestFase("${el.getfieldData("datiStudio", "tipoStudio")[0]!""}");

		//$('#datiStudio_SPTipoPop[value="6###Altro - specificare"]').change(function(){gestPop();});//STSANPRJS-1108
		$('#datiStudio_SPTipoPop[value="1###Volontari sani"]').change(function(){gestPop2();});


		$('#datiStudio_Intervento[value="8###altro"]').change(function(){gestInt();});

		$('#datiStudio_OSFarmaco-select').change(function(){gestRSO();});

		$('[id=datiStudio_SPControllato]').change(function(){gestCont();});

		$('[id=datiStudio_SPMascheramento').change(function(){gestMascheramento();});//STSANPRJS-1108

		$('[id=datiStudio_SPRandomizzazione]').change(function(){gestRand();});

		$('[id=datiStudio_Multicentrico]').change(function(){gestMulticentro();});

		$('[id=datiStudio_profit]').change(function(){gestProfit();});

		$('[id=datiStudio_NaturaDelloStudio]').change(function(){gestNoProfit();});
		$('[id=datiStudio_NoProfitFinanziato]').change(function(){gestNoProfitFin();});

		$('[id="datiCoordinatore_Disponibile"]').change(function(){gestCoordinatore()});
		$('#datiCoordinatore_Nazione-select').change(function(){gestCoordinatoreNazione()});
	}

function gestCoordinatore(){
	var value=false;
	value=$('#datiCoordinatore_Disponibile[value="1###Si"]').is(':checked');
	if(value){
		$('tr[id^="informations-datiCoordinatore"][id!="informations-datiCoordinatore_Disponibile"]').show();
		$('[id=informations-datiCoordinatore_NazioneSpec]').hide();
	}
	else{
		$('tr[id^="informations-datiCoordinatore"][id!="informations-datiCoordinatore_Disponibile"]').hide();
	}
}
<#-- [STSANSVIL-3385] Nazione=Italia ==> Specificare -->
function gestCoordinatoreNazione(){
	var value=false;
	value=$('#datiCoordinatore_Nazione-select').val();
	<#-- console.log("Sono qui: - value "+value); -->

	if (value.indexOf('1###')==0 && $('#datiCoordinatore_Nazione-select').is(':visible')){
		$('[id=informations-datiCoordinatore_NazioneSpec]').show();
	} else {
		$('[id=informations-datiCoordinatore_NazioneSpec]').hide();
		$('[id=datiCoordinatore_NazioneSpec]').val(''); //se nascondo sbianco il valore!
	}
}

function gestMulticentro(){
	value=$('#datiStudio_Multicentrico[value="2###No"]').is(':checked');

	if (value==true){
		$('[id=datiStudio_NumCentri]').val('1');
	}
}



function gestRSO(){
	if($('#datiStudio_OSFarmaco-select')!==undefined && $('#datiStudio_OSFarmaco-select').val()!==undefined){
		var value=$('#datiStudio_OSFarmaco-select').val();

		if (value.indexOf("1###")==0 && $('#datiStudio_OSFarmaco-select').is(':visible')){
			$('[id=informations-datiStudio_CodiceRSO]').show();
		}
		else {
			$('[id=informations-datiStudio_CodiceRSO]').hide();
			$('[id=datiStudio_CodiceRSO]').val('');
		}
	}
}




function gestCont(){
	value=$('#datiStudio_SPControllato[value="1###Sì"]').is(':checked');
	//alert(value);

	if (value==true && $('#datiStudio_SPControllato').is(':visible')){
		$('[id=informations-datiStudio_SPConfronto]').show();
		$('[id=informations-datiStudio_SPModalitaConfronto]').show();
	}
	else {
		$('[id=informations-datiStudio_SPConfronto]').hide();
		$('[name=datiStudio_SPConfronto-select]').val('');
		$('[name=datiStudio_SPConfronto-select]').trigger('change');

		$('[id=informations-datiStudio_SPModalitaConfronto]').hide();
		$('[id=datiStudio_SPModalitaConfronto').prop('checked', false);
	}
}




function gestRand(){
	value=$('#datiStudio_SPRandomizzazione[value="1###Sì"]').is(':checked');
	//alert(value);

	if (value==true && $('#datiStudio_SPRandomizzazione').is(':visible')){
		$('[id=informations-datiStudio_SPTipoRand]').show();
	}
	else {
		$('[id=informations-datiStudio_SPTipoRand]').hide();
		$('[name=datiStudio_SPTipoRand-select]').val('');
		$('[name=datiStudio_SPTipoRand-select]').trigger('change');
	}
}


//[STSANSVIL-3794] Nascosto campo NaturaDelloStudio('Solo se no profit') e trigger associati
function gestProfit(){
	gestNoProfit();
}

//[STSANSVIL-3794] Nascosto campo NaturaDelloStudio('Solo se no profit') e trigger associati

function gestNoProfit(){
	$('[id=informations-datiStudio_NoProfitFinanziatoTerzi]').hide();
	value=$('#datiStudio_profit[value="2###No Profit"]').is(':checked');
	if (value==true){
		$('[id=informations-datiStudio_NoProfitFinanziato]').show();
		$('[id=informations-datiStudio_NaturaDelloStudio]').show();
	}
	else {
		$('[id=informations-datiStudio_NoProfitFinanziato]').hide();
		$('[id=informations-datiStudio_NaturaDelloStudio]').hide();
		$('[id=datiStudio_NaturaDelloStudio]').prop('checked', false);
		$('[id=datiStudio_NoProfitFinanziato').prop('checked', false); //se nascondo sbianco il valore!
	}
	gestNoProfitFin();
}


// STSANSVIL-3436 No profit finanziato=Si ==> Finanziamento da terzi
function gestNoProfitFin(){
	value=$('#datiStudio_NoProfitFinanziato[value="1###Sì"]').is(':checked');
	if (value==true && $('#datiStudio_NoProfitFinanziato').is(':visible')){
		$('[id=informations-datiStudio_NoProfitFinanziatoTerzi]').show();
	}
	else {
		$('[id=informations-datiStudio_NoProfitFinanziatoTerzi]').hide();
		$('[id=datiStudio_NoProfitFinanziatoTerzi').prop('checked', false); //se nascondo sbianco il valore!
	}
}

/*STSANPRJS-1108
function gestPop(){
	value=$('#datiStudio_SPTipoPop[value="6###Altro - specificare"]').is(':checked');
	//alert(value);

	if (value==true && $('#datiStudio_SPTipoPop').is(':visible')){
		$('[id=informations-datiStudio_PopolazioneVulnerabile]').show();
	}
	else {
		$('[id=informations-datiStudio_PopolazioneVulnerabile]').hide();
		$('[id=datiStudio_PopolazioneVulnerabile]').val('');
	}
}*/

function gestMascheramento(){
	value=$('#datiStudio_SPMascheramento[value="1###Sì"]').is(':checked');
	//alert(value);

	if (value==true && $('#datiStudio_SPMascheramento').is(':visible')){
		$('[id=informations-datiStudio_SPMascheramentoTipo]').show();
	}
	else {
		$('[id=informations-datiStudio_SPMascheramentoTipo]').hide();
		$('[id=datiStudio_SPMascheramentoTipo').prop('checked', false);//se nascondo sbianco il valore!
	}

}

function gestPop2(){
	value=$('#datiStudio_SPTipoPop[value="1###Volontari sani"]').is(':checked');
	//alert(value);

	if (value==true && $('#datiStudio_SPTipoPop').is(':visible')){
		$('[id=informations-datiStudio_VolontariSani]').show();
	}
	else {
		$('[id=informations-datiStudio_VolontariSani]').hide();
		$('[id=datiStudio_VolontariSani]').val('');
	}
}


function gestInt(){
	value=$('#datiStudio_Intervento[value="8###altro"]').is(':checked');
	//alert(value);

	if (value==true && $('#datiStudio_Intervento').is(':visible')){
		$('[id=informations-datiStudio_InterventoSpec]').show();
	}
	else {
		$('[id=informations-datiStudio_InterventoSpec]').hide();
		$('[id=datiStudio_InterventoSpec]').val('');
	}
}



function gestFase(value){
	if (value==null) value=$('#datiStudio_tipoStudio-select').val();
	console.log("Sono qui: - value "+value);
	$('[id^=informations-datiStudio_SP]').hide();
	$('[id^=informations-datiStudio_OS]').hide();
	$('[id^=informations-datiStudio_GE]').hide();
	$('[id=informations-datiStudio_CodiceEUDRACT]').hide();
	$('[id=informations-datiStudio_CodiceEUDAMED]').hide();
	$('[id=informations-datiStudio_GradoDiRischio]').hide();
	$('[id=informations-datiStudio_Fase]').hide();
	$('[id=informations-datiStudio_Intervento]').hide();
	$('[id=informations-datiStudio_OSAltriInterventi]').hide();
	$('[id=informations-datiStudio_malattiaRara]').hide();

	$('[id=informations-datiStudio_Sottostudi]').show();
	$('[id=informations-datiStudio_NumCentri]').show();
	$('[id=informations-datiStudio_GradoDiRischio]').show();

	$('[id=informations-datiStudio_inUsoDisp]').hide();


	if (value.indexOf("1###")==0 || value.indexOf("4###")==0 || value.indexOf("5###")==0){
		$('[id=informations-datiStudio_malattiaRara]').show();
	}
	else{
		$('[id=informations-datiStudio_malattiaRara]').hide();
		$('[id=datiStudio_malattiaRara').prop('checked', false);//se nascondo sbianco il valore!
	}
	if (value.indexOf("1###")==0 || value.indexOf("2###")==0 || value.indexOf("3###")==0 || value.indexOf("4###")==0){
		$('[id^=informations-datiStudio_SP]').show();

		$('[id^=informations-datiStudio_OS]').hide();
		$('[name=datiStudio_OSTipologia-select]').val('');//se nascondo sbianco il valore!
		$('[name=datiStudio_OSTipologia-select]').trigger('change');//se nascondo sbianco il valore!
		$('[id=datiStudio_OSDisegno').prop('checked', false);//se nascondo sbianco il valore!
		$('[id=datiStudio_OSAltriInterventi').prop('checked', false);//se nascondo sbianco il valore!
		$('[id=datiStudio_OSDirezionalita').prop('checked', false);//se nascondo sbianco il valore!
		$('[name=datiStudio_OSFarmaco-select]').val('');//se nascondo sbianco il valore!
		$('[name=datiStudio_OSFarmaco-select]').trigger('change');//se nascondo sbianco il valore!

		$('[id^=informations-datiStudio_GE]').hide();
		$('[id=datiStudio_GESpecificare]').val('');//se nascondo sbianco il valore!
		$('[name=datiStudio_GETipologia-select]').val('');//se nascondo sbianco il valore!
		$('[name=datiStudio_GETipologia-select]').trigger('change');//se nascondo sbianco il valore!
	}

	if (value.indexOf("5###")==0){
		$('[id^=informations-datiStudio_SP]').hide();
		$('[id=datiStudio_SPBracci]').val('');//se nascondo sbianco il valore!
		$('[name=datiStudio_SPFinalitaStudio-select]').val('');//se nascondo sbianco il valore!
		$('[name=datiStudio_SPFinalitaStudio-select]').trigger('change');//se nascondo sbianco il valore!
		$('[id=datiStudio_SPTipoPop').prop('checked', false);//se nascondo sbianco il valore!
		$('[id=datiStudio_SPControllato').prop('checked', false);//se nascondo sbianco il valore!
		$('[id=datiStudio_SPModalitaConfronto').prop('checked', false);//se nascondo sbianco il valore!
		$('[id=datiStudio_SPRandomizzazione').prop('checked', false);//se nascondo sbianco il valore!
		$('[name=datiStudio_SPConfronto-select]').val('');//se nascondo sbianco il valore!
		$('[name=datiStudio_SPConfronto-select]').trigger('change');//se nascondo sbianco il valore!
		$('[name=datiStudio_SPTipoRand-select]').val('');//se nascondo sbianco il valore!
		$('[name=datiStudio_SPTipoRand-select]').trigger('change');//se nascondo sbianco il valore!
		$('[id=datiStudio_SPMascheramento').prop('checked', false);//se nascondo sbianco il valore!
		$('[id=datiStudio_SPMascheramentoTipo').prop('checked', false);//se nascondo sbianco il valore!

		$('[id^=informations-datiStudio_OS]').show();
		$('[id=informations-datiStudio_GradoDiRischio]').hide();
		$('[name=datiStudio_GradoDiRischio-select]').val('');//se nascondo sbianco il valore!
		$('[name=datiStudio_GradoDiRischio-select]').trigger('change');//se nascondo sbianco il valore!

		$('[id^=informations-datiStudio_GE]').hide();
		$('[id=datiStudio_GESpecificare]').val('');//se nascondo sbianco il valore!
		$('[name=datiStudio_GETipologia-select]').val('');//se nascondo sbianco il valore!
		$('[name=datiStudio_GETipologia-select]').trigger('change');//se nascondo sbianco il valore!
	}

	if (value.indexOf("6###")==0){
		$('[id^=informations-datiStudio_SP]').hide();
		$('[id=datiStudio_SPBracci]').val('');//se nascondo sbianco il valore!
		$('[name=datiStudio_SPFinalitaStudio-select]').val('');//se nascondo sbianco il valore!
		$('[name=datiStudio_SPFinalitaStudio-select]').trigger('change');//se nascondo sbianco il valore!
		$('[id=datiStudio_SPTipoPop').prop('checked', false);//se nascondo sbianco il valore!
		$('[id=datiStudio_SPControllato').prop('checked', false);//se nascondo sbianco il valore!
		$('[id=datiStudio_SPModalitaConfronto').prop('checked', false);//se nascondo sbianco il valore!
		$('[id=datiStudio_SPRandomizzazione').prop('checked', false);//se nascondo sbianco il valore!
		$('[name=datiStudio_SPConfronto-select]').val('');//se nascondo sbianco il valore!
		$('[name=datiStudio_SPConfronto-select]').trigger('change');//se nascondo sbianco il valore!
		$('[name=datiStudio_SPTipoRand-select]').val('');//se nascondo sbianco il valore!
		$('[name=datiStudio_SPTipoRand-select]').trigger('change');//se nascondo sbianco il valore!
		$('[id=datiStudio_SPMascheramento').prop('checked', false);//se nascondo sbianco il valore!
		$('[id=datiStudio_SPMascheramentoTipo').prop('checked', false);//se nascondo sbianco il valore!
		$('[id^=informations-datiStudio_OS]').hide();
		$('[name=datiStudio_OSTipologia-select]').val('');//se nascondo sbianco il valore!
		$('[name=datiStudio_OSTipologia-select]').trigger('change');//se nascondo sbianco il valore!
		$('[id=datiStudio_OSDisegno').prop('checked', false);//se nascondo sbianco il valore!
		$('[id=datiStudio_OSAltriInterventi').prop('checked', false);//se nascondo sbianco il valore!
		$('[id=datiStudio_OSDirezionalita').prop('checked', false);//se nascondo sbianco il valore!
		$('[name=datiStudio_OSFarmaco-select]').val('');//se nascondo sbianco il valore!
		$('[name=datiStudio_OSFarmaco-select]').trigger('change');//se nascondo sbianco il valore!

		$('[id^=informations-datiStudio_GE]').show();

		$('[id=informations-datiStudio_Sottostudi]').hide();
		$('[name=datiStudio_Sottostudi-select]').val('');//se nascondo sbianco il valore!
		$('[name=datiStudio_Sottostudi-select]').trigger('change');//se nascondo sbianco il valore!

		//$('[id=informations-datiStudio_NumCentri]').hide();
		//$('[id=datiStudio_NumCentri]').val('');//se nascondo sbianco il valore!
	}

	if (value.indexOf("1###")==0){
		$('[id=informations-datiStudio_CodiceEUDRACT]').show();
		$('[id=informations-datiStudio_Fase]').show();
		$('[id=informations-datiStudio_GradoDiRischio]').show();
	}else{
		$('[id=informations-datiStudio_CodiceEUDRACT]').hide();
		$('[id=datiStudio_CodiceEUDRACT]').val('');//se nascondo sbianco il valore!

		$('[id=informations-datiStudio_Fase]').hide();
		$('[name=datiStudio_Fase-select]').val('');//se nascondo sbianco il valore!
		$('[name=datiStudio_Fase-select]').trigger('change');//se nascondo sbianco il valore!

		$('[id=informations-datiStudio_GradoDiRischio]').hide();
		$('[name=datiStudio_GradoDiRischio-select]').val('');//se nascondo sbianco il valore!
		$('[name=datiStudio_GradoDiRischio-select]').trigger('change');//se nascondo sbianco il valore!

	}

	if (value.indexOf("2###")==0 || value.indexOf("3###")==0){
		$('[id=informations-datiStudio_CodiceEUDAMED]').show();
		$('[id=informations-datiStudio_inUsoDisp]').show();
	}else{
		$('[id=informations-datiStudio_CodiceEUDAMED]').hide();
		$('[id=datiStudio_CodiceEUDAMED]').val('');//se nascondo sbianco il valore!
		$('[id=informations-datiStudio_inUsoDisp]').hide();
		$('[id=datiStudio_inUsoDisp]').prop('checked', false);//se nascondo sbianco il valore!
	}

	if (value.indexOf("4###")==0){
		$('[id=informations-datiStudio_Intervento]').show();

	}else{
		$('[id=informations-datiStudio_Intervento]').hide();
		$('[id=datiStudio_Intervento').prop('checked', false);//se nascondo sbianco il valore!


	}

	//gestPop();//STSANPRJS-1108

	gestPop2();
	gestMascheramento();//STSANPRJS-1108
	gestInt();
	gestRSO();
	gestCont();
	gestRand();
	gestProfit();
	gestNoProfit();
}





function deleteElement(element) {
	if(!((typeof element)=='object') && !$.isArray(element)){
		if(isNaN(parseInt(element))){
			bootbox.alert("Attenzione impossibile riconoscere l'elemento da eliminare");
			return;
		}else{
		return $.ajax({
			url : '../../rest/documents/delete/' + element,

		}).done(function() {
			console.log('DELETED');
			window.location.reload();
		});
	}

	}else if (!element || !element.id){
		bootbox.alert("Attenzione impossibile riconoscere l'elemento da eliminare");
		return;
	}
	else{
		return $.ajax({
			url : '../../rest/documents/delete/' + element.id,

		}).done(function() {
			console.log('DELETED');
			window.location.reload();
		});
	}
}

function stdString(str){
	if(str && str!="") return str;
	else return "Valore mancante";
}

function statoVisite(metadata){
	if(metadata && metadata.DatiCustomMonitoraggioAmministrativo_VisiteFatturate){
		return metadata.DatiCustomMonitoraggioAmministrativo_VisiteFatturabili[0]+'/'+metadata.DatiCustomMonitoraggioAmministrativo_VisiteTot[0];
	}else{
		return 'Informazione non disponibile';
	}
}

function TSToDate2(date){
	if(!date)return "Valore mancante";
	var fmt = new DateFmt("%d/%m/%y");
	return fmt.format(new Date(date));
}
 function decode(select){
	if(!select)return "Valore mancante";
	var decode = select.split('###')[1];
	return decode;
}

function fileLink(file){
	return "<a href='../getAttach/"+file+"'><i class='icon icon-download bigger-160'></i></a> ";
}

//FINANZIAMENTO
if($('[name=datiStudio_Profit]').length>0){
	$('#informations-datiStudio_fonteFinTerzi').hide();
	$('#informations-datiStudio_fonteFinSpec').hide();
	$('#informations-datiStudio_fonteFinSponsor').hide();
	$('#informations-datiStudio_fonteFinFondazione').hide();
	$('#informations-datiStudio_fonteFinAltro').hide();
	//$('#informations-datiStudio_importoFin').hide();
	//VMAZZEO 02.09.2016 INIZIO TOSCANA-47 punto 3 ‘Fonte di finanziamento’: prevedere almeno due campi ‘Fonte di finanziamento’;
	$('#informations-datiStudio_fonteFinSpec2').hide();
	$('#informations-datiStudio_fonteFinSponsor2').hide();
	$('#informations-datiStudio_fonteFinFondazione2').hide();
	$('#informations-datiStudio_fonteFinAltro2').hide();
	//VMAZZEO 02.09.2016 FINE TOSCANA-47 punto 3 ‘Fonte di finanziamento’: prevedere almeno due campi ‘Fonte di finanziamento’;
	if($('[name=datiStudio_Profit]:checked').val()!=null && $('[name=datiStudio_Profit]:checked').val().split('###')[0]==2){
		$('#informations-datiStudio_fonteFinTerzi').show();
	}

	if($('[name=datiStudio_fonteFinTerzi]:checked').val()!=null && $('[name=datiStudio_fonteFinTerzi]:checked').val().split('###')[0]==1){
			$('#informations-datiStudio_fonteFinSpec').show();
			//$('#informations-datiStudio_importoFin').show();
			$('#informations-datiStudio_fonteFinSpec2').show();//VMAZZEO 02.09.2016 FINE TOSCANA-47 punto 3
		}
	changeFonteFinSpec();

	$('#datiStudio_fonteFinSpec-select').change(function(){
		changeFonteFinSpec();
	});
	$('#datiStudio_fonteFinSpec2-select').change(function(){
		changeFonteFinSpec2();
	});
	changeFonteFinSpec2();
}



function changeFonteFinSpec(){
	var selVal=-1;
 	if($('#datiStudio_fonteFinSpec-select').val()!==undefined){
		selVal=$('#datiStudio_fonteFinSpec-select').val().split('###')[0];
	}
	switch(selVal){
	case '4'://INDUSTRIA FARMACEUTICA
		$('#informations-datiStudio_fonteFinSponsor').show();
		$('#datiStudio_fonteFinFondazione').val("");
		$('#informations-datiStudio_fonteFinFondazione').hide();
		$('#datiStudio_fonteFinAltro').val("");
		$('#informations-datiStudio_fonteFinAltro').hide();
	break;

	case '5'://FONDAZIONE O ENTE BENEFICO
		$('#datiStudio_fonteFinSponsor-select').select2("val","");
		$('#informations-datiStudio_fonteFinSponsor').hide();
		$('#informations-datiStudio_fonteFinFondazione').show();
		$('#datiStudio_fonteFinAltro').val("");
		$('#informations-datiStudio_fonteFinAltro').hide();
	break;

	case '99'://ALTRO
		$('#datiStudio_fonteFinSponsor-select').select2("val","");
		$('#informations-datiStudio_fonteFinSponsor').hide();
		$('#datiStudio_fonteFinFondazione').val("");
		$('#informations-datiStudio_fonteFinFondazione').hide();
		$('#informations-datiStudio_fonteFinAltro').show();
	break;
	default:
		$('#informations-datiStudio_fonteFinSponsor').hide();
		$('#datiStudio_fonteFinSponsor-select').select2("val","");
		$('#informations-datiStudio_fonteFinFondazione').hide();
		$('#datiStudio_fonteFinFondazione').val("");
		$('#informations-datiStudio_fonteFinAltro').hide();
		$('#datiStudio_fonteFinAltro').val("");
		//$('#informations-datiStudio_importoFin').hide();
	break;
	}
}

//VMAZZEO 02.09.2016 INIZIO TOSCANA-47 punto 3 ‘Fonte di finanziamento’: prevedere almeno due campi ‘Fonte di finanziamento’;
function changeFonteFinSpec2(){
	var selVal=-1;
	if($('#datiStudio_fonteFinSpec2-select').val()!==undefined){
		selVal=$('#datiStudio_fonteFinSpec2-select').val().split('###')[0];
	}

	switch(selVal){
	case '4'://INDUSTRIA FARMACEUTICA
		$('#informations-datiStudio_fonteFinSponsor2').show();
		$('#datiStudio_fonteFinFondazione2').val("");
		$('#informations-datiStudio_fonteFinFondazione2').hide();
		$('#datiStudio_fonteFinAltro2').val("");
		$('#informations-datiStudio_fonteFinAltro2').hide();
	break;

	case '5'://FONDAZIONE O ENTE BENEFICO
		$('#datiStudio_fonteFinSponsor2-select').select2("val","");
		$('#informations-datiStudio_fonteFinSponsor2').hide();
		$('#informations-datiStudio_fonteFinFondazione2').show();
		$('#datiStudio_fonteFinAltro2').val("");
		$('#informations-datiStudio_fonteFinAltro2').hide();
	break;

	case '99'://ALTRO
		$('#datiStudio_fonteFinSponsor2-select').select2("val","");
		$('#informations-datiStudio_fonteFinSponsor2').hide();
		$('#datiStudio_fonteFinFondazione2').val("");
		$('#informations-datiStudio_fonteFinFondazione2').hide();
		$('#informations-datiStudio_fonteFinAltro2').show();
	break;
	default:
		$('#informations-datiStudio_fonteFinSponsor2').hide();
		$('#datiStudio_fonteFinSponsor2-select').select2("val","");
		$('#informations-datiStudio_fonteFinFondazione2').hide();
		$('#datiStudio_fonteFinFondazione2').val("");
		$('#informations-datiStudio_fonteFinAltro2').hide();
		$('#datiStudio_fonteFinAltro2').val("");
		//$('#informations-datiStudio_importoFin2').hide();
	break;
	}
}
//VMAZZEO 02.09.2016 FINE TOSCANA-47 punto 3 ‘Fonte di finanziamento’: prevedere almeno due campi ‘Fonte di finanziamento’;

$('[name=datiStudio_Profit]').click(function(){
	if($('[name=datiStudio_Profit]:checked').val().split('###')[0]==2){
		$('#informations-datiStudio_fonteFinTerzi').show();
	}else{
		clear1();
		clear2();
	}
});

$('#radioClear-datiStudio_Profit').click(function(){
		clear1();
		clear2();
});

$('[name=datiStudio_fonteFinTerzi]').click(function(){
	if($('[name=datiStudio_fonteFinTerzi]:checked').val().split('###')[0]==1){
		$('#informations-datiStudio_fonteFinSpec').show();
		$('#informations-datiStudio_fonteFinSpec2').show();//VMAZZEO 02.09.2016 TOSCANA-47 punto 3 ‘Fonte di finanziamento’: prevedere almeno due campi ‘Fonte di finanziamento’;
		//$('#informations-datiStudio_importoFin').show();
	}else{
		clear2();
	}
});

$('#radioClear-datiStudio_fonteFinTerzi').click(function(){
		clear2();
});

function clear1(){
	$('[name=datiStudio_fonteFinTerzi').prop('checked', false);
	$('#informations-datiStudio_fonteFinTerzi').hide();
}

function clear2(){
	$('#datiStudio_fonteFinSpec-select').select2("val","");
	$('#informations-datiStudio_fonteFinSpec').hide();
	$('#datiStudio_fonteFinSponsor-select').select2("val","");
	$('#datiStudio_fonteFinFondazione').val("");
	$('#datiStudio_fonteFinAltro').val("");
	//$('#datiStudio_importoFin').val("");
	//$('#informations-datiStudio_importoFin').hide();
	//VMAZZEO 02.09.2016 INIZIO TOSCANA-47 punto 3 ‘Fonte di finanziamento’: prevedere almeno due campi ‘Fonte di finanziamento’;
	$('#datiStudio_fonteFinSpec2-select').select2("val","");
	$('#informations-datiStudio_fonteFinSpec2').hide();
	$('#datiStudio_fonteFinSponsor2-select').select2("val","");
	$('#datiStudio_fonteFinFondazione2').val("");
	$('#datiStudio_fonteFinAltro2').val("");
	//$('#informations-datiStudio_importoFin').hide();
	//VMAZZEO 02.09.2016 FINE TOSCANA-47 punto 3 ‘Fonte di finanziamento’: prevedere almeno due campi ‘Fonte di finanziamento’;
};

/*TOSCANA-165 VMAZZEO 15.06.2017*/
function dsurList(){
		var grid_selector = "#grid-dsur";
		var pager_selector = "#grid-dsury-pager";
		var url=baseUrl+"/app/rest/documents/jqgrid/advancedSearch/DSUR?parent_obj_id_eq=${el.getId()}";
		var colNames=['Titolo','Periodo di riferimento dal','al', 'Data relazione','Scarica'];
		var colModel=[
		  			{name:'codice',index:'DSUR_Titolo', formatter:stdString, width:30, sorttype:"string",jsonmap:"metadata.DSUR_Titolo.0"},
		  			{name:'codice1',index:'DSUR_PeriodoDal', formatter:TSToDate2, width:30, sorttype:"string",jsonmap:"metadata.DSUR_PeriodoDal.0"},
		  			{name:'codice2',index:'DSUR_PeriodoAl', formatter:TSToDate2, width:30, sorttype:"string",jsonmap:"metadata.DSUR_PeriodoAl.0"},
		  			{name:'codice2',index:'DSUR_DataRelazione', formatter:TSToDate2, width:30, sorttype:"string",jsonmap:"file.date"},
		  			{name:'id',index:'id', formatter:fileLink, width:30, jsonmap:"id"},

				];
		var caption = "DSUR";
		setupGrid(grid_selector, pager_selector, url, colModel,colNames, caption);
		var DataGrid = $(grid_selector);
 		DataGrid.jqGrid('setGridWidth', '1100');
	}
	$(window).bind('hashchange', function(e) {
		if(window.location.hash=='#dsur-tab'){


			$('a[href=#dsur-tab]').click();

			dsurList();
		}
	});
	setTimeout(dsurList,100);

/*TOSCANA-79 VMAZZEO 23.11.2016*/
function getDocCe(id){
        $.ajax({
            type: "POST",
            dataType: "html",
            cache: false,
            url: "/getDocCe.php",
            data: "codice="+id ,
            success: function(msg){
            $('#dialog').html(msg);
            $( document ).ready(function() {
                $( "#dialog" ).dialog({minWidth: 700, minHeight: 200});
                });
            }
        });
    }
	//TOSCANA-193 vmazzeo 06.11.2017 download documentazione centro in zip
	function getDocCeZip(id){
		window.location.href="/getDocCe.php?codice="+id+"&zip=true";
		return false;
	}


/*
STSANSVIL-1257 visualizzare nome e cognome utente che ha creato il documento
*/
$( document ).ready(function() {
	$("td[user-data]").each(function(){
		console.log($(this).html());
		userCreator=$(this).html();
		nomeCognome="";
		$.ajax({
			type: "GET",
			cache: false,
			url: baseUrl+"/uService/rest/user/searchUser?term="+userCreator,
			success: function(data){
				$(data).each(function(k,result){
					if(result.username==userCreator){
						nomeCognome=result.firstName+" "+result.lastName;
					}
				});
			}
		 });
		if(nomeCognome!=''){
			$(this).html(nomeCognome+" "+userCreator);
		}
	});
});
</@script>

<@style>
#metadataTemplate-datiStudio .col-sm-9,#metadataTemplate-datiStudio .col-sm-3{
	padding-left:0px!important;
}

#metadataTemplate-UniqueIdStudio .view-mode{
	padding-left:14px;
}
.ui-jqgrid tr.jqgrow td {
			white-space:normal;
		}
		.ui-jqgrid .ui-jqgrid-htable th div {
			white-space:normal;
			height:auto;
			margin-bottom:3px;
		}

		tr.jqgrow{
			cursor:pointer;
		}
</@style>


<#-- PROTOCOLLAZIONE NON IN STUDIO, COMMENTO SOLTANTO PER TENERE TRACCIA DEL CODICE
<@script>
function protocollaElement(elementId, docFileName, studioId, fascicoloStudio) {
	<#assign userCF = userDetails.username />
	<#if userDetails.getAnaDataValue('CODICE_FISCALE')?? >
		<#assign userCF = userDetails.getAnaDataValue('CODICE_FISCALE') />
	</#if>
	var userCF = '${userCF}';//MSRRNT64S69A944K
	<#if userDetails.hasRole("CTC") || userDetails.hasRole("SGR") || userDetails.hasRole("UFFAMM") >
	var profileProtocollo=true;
	<#else>
	var profileProtocollo=false;
	</#if>

	if(!profileProtocollo){
	alert("Attenzione: la tua utenza non è abilitata all'invio di documenti al protocollo aziendale");
	return false;
	}
	<#assign userPROTOCOLLO = "" />
	<#if userDetails.getSiteDataValue('INTEGRAZIONE_PROTOCOLLO')?? >
		<#assign userPROTOCOLLO = userDetails.getSiteDataValue('INTEGRAZIONE_PROTOCOLLO') />
	</#if>
	var userPROTOCOLLO = '${userPROTOCOLLO}';

	<#assign userAZI = "" />
	<#if userDetails.getSiteDataValue('INTEGRAZIONE_COD_AZ')?? >
		<#assign userAZI = userDetails.getSiteDataValue('INTEGRAZIONE_COD_AZ') />
	</#if>
	var userAZI = '${userAZI}';

	<#assign userREGISTRO = "" />
	<#if userDetails.getSiteDataValue('INTEGRAZIONE_COD_REGISTRO')?? >
		<#assign userREGISTRO = userDetails.getSiteDataValue('INTEGRAZIONE_COD_REGISTRO') />
	</#if>
	var userREGISTRO = '${userREGISTRO}';

	if(userREGISTRO=='' || userPROTOCOLLO=='' || userAZI=='' ){
		alert('Attenzione: la procedura di integrazione con protocollo aziendale non è attiva per questo centro');
		return false;
	}

	var anno = new Date();
    //alert(elementId);
    //alert(studioId);
    //alert(fascicoloStudio);
	//alert(userCF);
	//alert(userPROTOCOLLO);
	//alert(userAZI);
	//alert(userREGISTRO);
	//alert(anno.getFullYear());
	//return false;

    if (!fascicoloStudio){
        $.ajax({
            type : "POST",
            cache: false,
			data : "AZIENDA="+userAZI+"&REGISTRO="+userREGISTRO+"&ANNO="+anno.getFullYear()+"&USERCF="+userCF+"&STUDIO_CODE="+studioId,
			url : '/xCDMProtocolloLib/'+userPROTOCOLLO+'/createFolder.php',
            async:false,

        }).done(function(result) {
            console.log(result);
            alert(result);
            if(result.includes('"code" : "500"')){
                alert("ERRORE INSERIMENTO FASCICOLO: "+result);
            }else{
                //Aggiorna oggetto studio
                $.ajax({
                    type: "POST",
                    cache: false,
                    url: baseUrl+"/app/rest/documents/update/"+studioId,
                    data: "IDstudio_ProtocolloFascicolo="+result ,
                    async: false,
                    success: function(msg){
                        //window.location.reload();
                        fascicoloStudio = result;
                    }
                });
                //window.location.reload();
            }
        });
    }
    //Inserisci documento effettivo
    if (fascicoloStudio){
        var attach="";
        $.ajax({
            type : "GET",
            cache: false,
            url : baseUrl+'/app/documents/getAttach/'+elementId
        }).done(function(content) {
            //alert(content);
            if (content){
                var attach=Base64.encode(content);
                $.ajax({
                    type : "POST",
                    cache: false,
					data : "AZIENDA="+userAZI+"&REGISTRO="+userREGISTRO+"&ANNO="+anno.getFullYear()+"&USERCF="+userCF+"&STUDIO_CODE="+studioId+"&STUDIO_FASCICOLO="+fascicoloStudio+"&DOCUMENTO_CODE="+elementId+"&DOCUMENTO_FILENAME="+docFileName+"&DOCUMENTO_BODY="+attach,
					url : '/xCDMProtocolloLib/'+userPROTOCOLLO+'/sendFileContentPEBody.php',

                }).done(function(result) {
                    console.log(result);
                    alert(result);
                    if(result.includes('"code" : "500"')){
                        alert("ERRORE INSERIMENTO DOCUMENTO: "+result);
                    }else{
                        //Aggiorna oggetto studio
                        $.ajax({
                            type: "POST",
                            cache: false,
                            url: baseUrl+"/app/rest/documents/update/"+elementId,
							data: "DocCentroSpec_ProtocolloNumero="+result+"&DocCentroSpec_ProtocolloRegistro="+userREGISTRO+"&DocCentroSpec_ProtocolloAzienda="+userAZI ,
                            success: function(msg){
                                window.location.reload();
                            }
                        });
                        //window.location.reload();
                    }
                });
            }else{
                alert("Contenuto file non disponibile.");
            }
        });
    }else{
        alert("Fascicolo per lo studio non presente.");
    }
    return false;
}

function vediProtocollo(codiceProtocollo) {
	<#assign userCF = userDetails.username />
	<#if userDetails.getAnaDataValue('CODICE_FISCALE')?? >
		<#assign userCF = userDetails.getAnaDataValue('CODICE_FISCALE') />
	</#if>
	var userCF = '${userCF}';//MSRRNT64S69A944K

	<#assign userPROTOCOLLO = "" />
	<#if userDetails.getSiteDataValue('INTEGRAZIONE_PROTOCOLLO')?? >
		<#assign userPROTOCOLLO = userDetails.getSiteDataValue('INTEGRAZIONE_PROTOCOLLO') />
	</#if>
	var userPROTOCOLLO = '${userPROTOCOLLO}';

	<#assign userAZI = "" />
	<#if userDetails.getSiteDataValue('INTEGRAZIONE_COD_AZ')?? >
		<#assign userAZI = userDetails.getSiteDataValue('INTEGRAZIONE_COD_AZ') />
	</#if>
	var userAZI = '${userAZI}';

	<#assign userREGISTRO = "" />
	<#if userDetails.getSiteDataValue('INTEGRAZIONE_COD_REGISTRO')?? >
		<#assign userREGISTRO = userDetails.getSiteDataValue('INTEGRAZIONE_COD_REGISTRO') />
	</#if>
	var userREGISTRO = '${userREGISTRO}';

	if(userREGISTRO=='' || userPROTOCOLLO=='' || userAZI=='' ){
		alert('Attenzione: la procedura di integrazione con protocollo aziendale non è attiva per questo centro');
		return false;
	}
    alert(codiceProtocollo);
    if (codiceProtocollo){
        var codiceSplit = codiceProtocollo.split('/');
        $.ajax({
            type : "POST",
            cache: false,
			data : "AZIENDA="+userAZI+"&REGISTRO="+userREGISTRO+"&ANNO="+codiceSplit[1]+"&NUMERO="+codiceSplit[0]+"&USERCF="+userCF,
			url : '/xCDMProtocolloLib/'+userPROTOCOLLO+'/retrieveFileList.php',

        }).done(function(result) {
            alert(result);
        });
    }
}
</@script>
-->