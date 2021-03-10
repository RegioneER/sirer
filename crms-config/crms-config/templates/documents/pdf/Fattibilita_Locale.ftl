<#ftl encoding="utf-8">
<#include "../../themes/ace/macros.ftl">
<#setting number_format="0.##">
<#assign el=element/>
<#assign elStudio=element.getParent()/>
<#assign cartaIntestata=elStudio.getFieldDataString("UniqueIdStudio","cto") />
<#assign budgetId=el.getFieldDataString("statoValidazioneCentro","idBudgetApproved") /> <!--TODO: da gestire quando sapremo i WF budget -->

<#-- VERSIONE E DATA -->
<#assign versione=0 />
<#assign uploadDt=0 />
<#assign data_prot=""/>
<#list elStudio.getChildrenByType("allegato") as allegato >

<#if allegato.getFieldDataCode("DocGenerali","DocGen")=="4" >

	<#if uploadDt==0 > <#-- uploadDt non ancora assegnato -->
		<#assign versione=allegato.file.version />
		<#assign uploadDt=allegato.file.uploadDt.getTimeInMillis() />
		<#assign data_prot=allegato.file.date.time?date?string("dd/MM/yyyy") />
	<#elseif allegato.file?? && allegato.file.uploadDt?? && (allegato.file.uploadDt.getTimeInMillis() gt uploadDt) /> <#-- prendo sempre il documento piu' recente -->
		<#assign versione=allegato.file.version />
		<#assign uploadDt=allegato.file.uploadDt.getTimeInMillis() />
		<#assign data_prot=allegato.file.date.time?date?string("dd/MM/yyyy") />
	</#if>
</#if>
</#list>




<#-- PROMOTORE -->
<#assign datiPromotore="" />
<#list elStudio.getChildrenByType("PromotoreStudio") as currPromotore >
	<#if currPromotore.getFieldDataElement("datiPromotore","promotore")?? && currPromotore.getFieldDataElement("datiPromotore","promotore")[0]?? >
		<#assign promotore=currPromotore.getFieldDataElement("datiPromotore","promotore")[0] />
		<#assign datiPromotore=datiPromotore+"<li>"+promotore.titleString+"</li>" >
	</#if>
</#list>
<#if datiPromotore!= "" >
	<#assign datiPromotore="<ul>"+datiPromotore+"</ul><br/>" />
</#if>

<#-- FINANZIATORE -->
<#assign datiFinanziatore="" />
<#list elStudio.getChildrenByType("FinanziatoreStudio") as currFinanziatore >

<#assign finanziatore="Tipologia: "+currFinanziatore.getFieldDataDecode("datiFinanziatore","EnteFinanziatore")+" Denominazione: "+currFinanziatore.getFieldDataString("datiFinanziatore","NomeFinanziatore")/>
<#assign datiFinanziatore=datiFinanziatore+"<li>"+finanziatore+"</li>" >

</#list>
<#if datiFinanziatore!= "" >
<#assign datiFinanziatore="<ul>"+datiFinanziatore+"</ul><br/>" />
</#if>




<#-- PRESTAZIONI -->




<#list el.getChildrenByType("Budget") as currBudget >
	<#if currBudget.id??>
		<#assign budget=currBudget />
		<#list budget.getChildrenByType("FolderBudgetStudio")[0].getChildren() as currBudgetStudio >
			<#if currBudgetStudio.id?? >
				<#assign budgetStudio=currBudgetStudio/>
			</#if>
		</#list>
	</#if>
</#list>

<#assign prestazioniAggiuntive=[] />
<#assign costiAggiuntivi=[] />
<#if budget??>
	<#list budget.getChildrenByType("FolderPXP")[0].getChildren() as prestazione >
		<#assign prestazioniAggiuntive=prestazioniAggiuntive +[ prestazione ] />
	</#list>

	<#list budget.getChildrenByType("FolderCostiAggiuntivi")[0].getChildren() as costo >
		<#assign costiAggiuntivi=costiAggiuntivi + [ costo ] />
	</#list>
</#if>

<#assign UncheckedCheckbox>
<img src="images/Unchecked-Checkbox-icon.png" width="10" height="10" />
</#assign>

<#assign CheckedCheckbox>
<img src="images/Checked-Checkbox-icon.png" width="10" height="10" />
</#assign>

<#function setCheckbox templateName fieldName fieldVal element>
	<#assign checkImage=UncheckedCheckbox />
	<#if fieldVal=="T">
		<#assign checkImage=CheckedCheckbox />
	<#elseif fieldVal=="F">
		<#assign checkImage=UncheckedCheckbox />
	<#else>
		<#assign dataVals=element.getFieldDataCodes(templateName,fieldName) />
		<#list dataVals as dataVal>
			<#if dataVal?? && dataVal?split('###')[0]==fieldVal>
				<#assign checkImage=CheckedCheckbox />
			</#if>
		</#list>
	</#if>
	<#return checkImage />
</#function>


<#assign servizioCoinvolto="" />
<#assign listaServiziCoinvolti=[] />
<#assign x=39>
<#list 1..x as i>
<#assign currServ="FeasibilitySERV"+i />
<#assign currServAtt="SERV"+i />
<#list el.getChildrenByType(currServ) as elFeasServ>
<#-- assign servizioCoinvolto>
<tr>
	<td class="txtleft"   style="border: 1px solid black;">${elFeasServ.getTitleString()}</td>
	<td class="txtcenter" style="border: 1px solid black;">

		<#<#if attivitaServizi[currServAtt]??)>
		<#list attivitaServizi[currServAtt] as currPrestazione >
		${currPrestazione.getFieldDataString("Prestazioni","prestazione")}<br/>
	</#list>
</#if>
&nbsp;</td>
<td class="txtcenter" style="border: 1px solid black;">&nbsp;</td>
</tr>
</#assign -->
<#assign listaServiziCoinvolti=listaServiziCoinvolti + [elFeasServ] />
</#list>
</#list>


<style>

	td{
		padding: 5px;
		text-align:left;
		vertical-align:middle;
	}

	table{
		padding-top:10px;
		padding-bottom:10px;
		vertical-align:middle;
		width:1000px;
		font-size: 10px;
		font-family: Tahoma;
		text-align: justify;
	}

	.border1{
		border: 1px solid black;
	}

	.txtcenter{
		text-align:center;
		padding-bottom: 20px; padding-top: 20px;background-color: #eee;border:solid 1px black;
	}

	.txtleft{
		text-align:left;
	}

	.txtright{
		text-align:right;
	}
	ul {
		margin: 0;
	}
	ul.dashed {
		list-style-type: none;
	}
	ul.dashed > li {
		text-indent: -5px;
	}
	ul.dashed > li:before {
		content: "-";
		text-indent: -5px;
		margin-right: 5px;
	}
</style>

<!--INIZIO HTML-->
<!doctype html>
<html>
<head>
	<meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
	<title>Modulo di impatto aziendale</title>
</head>

<body style="font-size: 12pt; font-family: times new roman, verdana, sans-serif; text-align: justify;">

<table>
	<tr>
		<td style="width:2%;"></td>
		<td style="width:96%;">

			<!--tutto qui dentro INIZIO-->
			<table>
				<tr>
					<td class="" style="padding-bottom: 10px; padding-top: 20px;">
						<!-- h1><b>CARTA INTESTATA ${cartaIntestata}</b></h1 -->
					</td>
				</tr>
			</table>
			<table>
				<tr>
					<td class="txtcenter" >
						<b>Informazioni per la valutazione locale dello studio e relative autodichiarazioni</b>
					</td>
				</tr>
			</table>
			<table>
				<tr>
					<td class="txtleft" style="padding-bottom: 10px; padding-top: 20px;">
						<b>Il presente modulo si compone di 5 sezioni:</b>
						<br/><b> 1. Sezione A:</b> Informazioni generali sullo studio
						<br/><b> 2. Sezione B:</b> Modulo per l'analisi dei costi aggiuntivi correlati allo studio
						<br/><b> 3. Sezione C:</b> Modulo riepilogativo aspetti economici
						<br/><b> 4. Sezione D:</b> Modulo di <u>previsione di impiego del finanziamento</u> per lo studio
						(<em>da compilare nel caso sia previsto un finanziamento dedicato per la conduzione dello studio</em>)
						<br/><b> 5. Sezione E:</b> <u>Assunzione di responsabilit&agrave; a cura dello Sperimentatore</u>
						<br/><br/> <b>N.B. La compilazione del presente documento è a cura dello Sperimentatore.</b>
					</td>
				</tr>
			</table>
			<table>
				<tr>
					<td class="txtcenter" style="padding-bottom: 10px; padding-top: 20px;">
						<b>Sezione A: Informazioni generali dello studio</b>
					</td>
				</tr>
			</table>
			<table cellspacing="0" style="border-collapse: collapse; border: 0px;">
				<tr>
					<td class="txtleft" style=" width: 1000px;" colspan="2">
						<b>Titolo dello studio </b>
						${elStudio.getFieldDataString("IDstudio","TitoloProt")}
					</td>
				</tr>
				<tr>
					<td class="txtleft" style=" width: 1000px; " colspan="2">
						<b>Codice Protocollo</b>
						${elStudio.getFieldDataString("IDstudio","CodiceProt")}
					</td>
				</tr>
				<tr>
					<td class="txtleft" style=" width: 1000px; " colspan="2">
						<b>Acronimo (se esistente)</b>
						${elStudio.getFieldDataString("IDstudio","Acronimo")}
					</td>
				</tr>
				<tr>
					<td class="txtleft" style=" width: 1000px; " colspan="2">
						<b>Numero Eudract</b> <em>(se applicabile)</em>
						${elStudio.getFieldDataString("datiStudio","CodiceEUDRACT")}
					</td>
				</tr>
				<tr>
					<td class="txtleft" style=" width: 1000px; " colspan="2">
						<b>Numero RSO</b> <em>(se previsto)</em>
						${elStudio.getFieldDataString("datiStudio","CodiceRSO")}
					</td>
				</tr>
				<tr>
					<td class="txtleft" style=" width: 1000px; " colspan="2">
						<b>Codice ClinicalTrial.gov</b> <em>(o simili, se previsti)</em>
						${elStudio.getFieldDataString("datiStudio","CodiceClinicalTrial")}
					</td>
				</tr>
				<tr>
					<td class="txtleft" style=" width: 1000px; " colspan="2">
						<b>Promotore dello studio: </b> <em>(indicare denominazione completa)</em>
						<#if datiPromotore?? >
							${datiPromotore}
						</#if>
					</td>
				</tr>
				<tr>
					<td class="txtleft" style="border: 1px solid black; width: 1000px;" colspan="2">
						Studio profit:
						<#if elStudio.getFieldDataCode("datiStudio","NaturaDelloStudio")=="1">
							&nbsp;${setCheckbox("datiStudio" "NaturaDelloStudio" "T" elStudio)}&nbsp; S&igrave;
							&nbsp;${setCheckbox("datiStudio" "NaturaDelloStudio" "F" elStudio)}&nbsp; No
						<#else>
							&nbsp;${setCheckbox("datiStudio" "NaturaDelloStudio" "F" elStudio)}&nbsp; S&igrave;
							&nbsp;${setCheckbox("datiStudio" "NaturaDelloStudio" "T" elStudio)}&nbsp; No
						</#if>
						<br/>
					</td>
				</tr>
				<tr>
					<td class="txtleft" style="border: 1px solid black; width: 1000px;" colspan="2">
						Studio no profit:
						<#if elStudio.getFieldDataCode("datiStudio","NaturaDelloStudio")=="1">
						&nbsp;${setCheckbox("datiStudio" "NaturaDelloStudio" "F" elStudio)}&nbsp; S&igrave;
						&nbsp;${setCheckbox("datiStudio" "NaturaDelloStudio" "T" elStudio)}&nbsp; No
						<#else>
						&nbsp;${setCheckbox("datiStudio" "NaturaDelloStudio" "T" elStudio)}&nbsp; S&igrave;
						&nbsp;${setCheckbox("datiStudio" "NaturaDelloStudio" "F" elStudio)}&nbsp; No
					</#if>
					<br/>
					<br/>Solo se no profit <em>con finanziamento</em> da parte di terzi:<br/><br/>
						<#if elStudio.getFieldDataCode("datiStudio","NaturaDelloStudio")=="2">
							&nbsp;${setCheckbox("datiStudio" "NaturaDelloStudio" "T" elStudio)}&nbsp; Finalizzato al miglioramento della pratica clinica (art. 1 D.M. 17.12.2004)<br/><br/>
							&nbsp;${setCheckbox("datiStudio" "NaturaDelloStudio" "F" elStudio)}&nbsp; NON Finalizzato al miglioramento della pratica clinica (art. 1 D.M. 17.12.2004)
						<#elseif elStudio.getFieldDataCode("datiStudio","NaturaDelloStudio")=="3">
							&nbsp;${setCheckbox("datiStudio" "NaturaDelloStudio" "F" elStudio)}&nbsp; Finalizzato al miglioramento della pratica clinica (art. 1 D.M. 17.12.2004)<br/><br/>
							&nbsp;${setCheckbox("datiStudio" "NaturaDelloStudio" "T" elStudio)}&nbsp; NON Finalizzato al miglioramento della pratica clinica (art. 1 D.M. 17.12.2004)
						<#else>
							&nbsp;${setCheckbox("datiStudio" "NaturaDelloStudio" "F" elStudio)}&nbsp; Finalizzato al miglioramento della pratica clinica (art. 1 D.M. 17.12.2004)<br/><br/>
							&nbsp;${setCheckbox("datiStudio" "NaturaDelloStudio" "F" elStudio)}&nbsp; NON Finalizzato al miglioramento della pratica clinica (art. 1 D.M. 17.12.2004)
						</#if>
					<br/>
					<br/><em>Ad attestazione di ci&ograve; allegare dichiarazione del Promotore rilasciata ai sensi dell'Allegato 1 al D.M. 17.12.2004</em>
					<br/>
						<br/>
					</td>
				</tr>
			</table>
			<div style="page-break-before: always">&nbsp;</div>
			<table cellspacing="0" style="border: 1px solid black; border-collapse: collapse;">
				<tr>
					<td class="txtleft" colspan="2" style=" width: 1000px; ">
						<b>Tipo di studio:</b>
					</td>
				</tr>
				<tr>
					<td style="">&nbsp;&nbsp;${setCheckbox("datiStudio" "tipoStudio" "1" elStudio)}&nbsp; Sperimentale con farmaco<br/>
					</td>
				</tr>
				<tr>
					<td class="txtleft" style="width:50%;  padding-left:40px;" colspan="2" >
						Fase (scelta multipla):
						&nbsp;${setCheckbox("datiStudio" "Fase" "1" elStudio)}&nbsp; I
						&nbsp;${setCheckbox("datiStudio" "Fase" "2" elStudio)}&nbsp; II
						&nbsp;${setCheckbox("datiStudio" "Fase" "3" elStudio)}&nbsp; III
						&nbsp;${setCheckbox("datiStudio" "Fase" "4" elStudio)}&nbsp; IV
						<br/>
					</td>
				</tr>
				<tr>
					<td class="txtleft" style="width:50%;  padding-left:40px;" colspan="2" >
						Nel caso di studi a fasi combinate specificare quale fase viene condotta presso <em>questo centro</em>
						<br/>(scelta multipla):
						&nbsp;${setCheckbox("Feasibility" "Fase" "1" el)}&nbsp; I
						&nbsp;${setCheckbox("Feasibility" "Fase" "2" el)}&nbsp; II
						&nbsp;${setCheckbox("Feasibility" "Fase" "3" el)}&nbsp; III
						&nbsp;${setCheckbox("Feasibility" "Fase" "4" el)}&nbsp; IV
						<br/>
					</td>
				</tr>
				<tr>
					<td style="">
						<#if  elStudio.getFieldDataCode("datiStudio","tipoStudio")=="2" || elStudio.getFieldDataCode("datiStudio","tipoStudio")=="3">
						&nbsp;	${setCheckbox("datiStudio" "tipoStudio" "T" elStudio)}
						<#else>
							${setCheckbox("datiStudio" "tipoStudio" "F" elStudio)}
						</#if>&nbsp; Indagine clininca con dispositivo medico<br/>
					</td>
				</tr>
				<tr>
					<td class="txtleft" style="width:50%;  padding-left:40px;" colspan="2" >
						&nbsp;${setCheckbox("datiStudio" "tipoStudio" "2" elStudio)}&nbsp; pre-marketing<br/>
						&nbsp;${setCheckbox("datiStudio" "tipoStudio" "3" elStudio)}&nbsp; post-marketing
						<br/><br/>
						&nbsp;Specificare se il dispositivo &egrave; gi&agrave; in uso:
						&nbsp;${setCheckbox("datiStudio" "FC9" "F" el)}&nbsp; S&igrave;<!--TODO! capire da dove prenderlo! -->
						&nbsp;${setCheckbox("datiStudio" "FC9" "F" el)}&nbsp; No
						<br/>
					</td>
				</tr>
				<tr>
					<td style="">&nbsp;${setCheckbox("datiStudio" "tipoStudio" "4" elStudio)}&nbsp; Studio interventistico (senza dispositivi e senza farmaci)</td>
				</tr>
				<tr>
					<td class="txtleft" style="width:50%;  padding-left:40px;" colspan="2">Specificare il tipo di intervento:<br/>
						&nbsp;${setCheckbox("datiStudio" "Intervento" "1" elStudio)}&nbsp; Procedura o tecnica di prevenzione (es.vaccinazioni, interventi basati su screening di popolazione, interventi educativi...)
						<br/>
						&nbsp;${setCheckbox("datiStudio" "Intervento" "2" elStudio)}&nbsp; Procedura o tecnica diagnostica
						<br/>
						&nbsp;${setCheckbox("datiStudio" "Intervento" "3" elStudio)}&nbsp; Procedura o tecnica terapeutica (es. chirurgia, radioterapia...)
						<br/>
						&nbsp;${setCheckbox("datiStudio" "Intervento" "4" elStudio)}&nbsp; Procedura o tecnica riabilitativa
						<br/>
						&nbsp;${setCheckbox("datiStudio" "Intervento" "5" elStudio)}&nbsp; Procedura infermieristica (es. medicazione)
						<br/>
						&nbsp;${setCheckbox("datiStudio" "Intervento" "6" elStudio)}&nbsp; Medicine non convenzionali (agopuntura, omeopatia, fitoterapia...)
						<br/>
						&nbsp;${setCheckbox("datiStudio" "Intervento" "7" elStudio)}&nbsp; Integratori alimentari
						<br/>
						&nbsp;${setCheckbox("datiStudio" "Intervento" "9" elStudio)}&nbsp; Cosmetici
						<br/>
						&nbsp;${setCheckbox("datiStudio" "Intervento" "8" elStudio)}&nbsp; Altro (specificare) ${elStudio.getFieldDataString("datiStudio","InterventoSpec")}
						<br/>
					</td>
				</tr>
				<tr>
					<td style="">&nbsp;
						&nbsp;${setCheckbox("datiStudio" "tipoStudio" "5" elStudio)}&nbsp; Studio Osservazionale
					</td>
				</tr>
				<tr>
					<td class="txtleft" style="width:50%;  padding-left:40px;" colspan="2">
					&nbsp;${setCheckbox("datiStudio" "OSFarmaco" "1" elStudio)} Osservazionale con farmaco<br/>
					&nbsp;${setCheckbox("datiStudio" "OSFarmaco" "2" elStudio)} Osservazionale senza farmaco<br/>
					</td>
				</tr>
				<tr>
					<td class="txtleft" style="width:50%;  padding-left:40px;" colspan="2">
						&nbsp;Sono previste indagini aggiuntive* per il paziente? ${setCheckbox("datiStudio" "OSAltriInterventi" "1" elStudio)} Si ${setCheckbox("datiStudio" "OSAltriInterventi" "2" elStudio)} No <br/>
						<em>&nbsp;(se con farmaco allegare attestazione della notifica ad AIFA da parte del Promotore dello studio per la registrazione nel registro degli studi osservazionali)</em>
						<br/>Disegno:
					</td>
				</tr>
				<tr>
					<td class="txtleft" style="width:50%;  padding-left:40px;" colspan="2">
						&nbsp;${setCheckbox("datiStudio" "OSDisegno" "1" elStudio)}&nbsp; trasversale
						<br/>
						&nbsp;${setCheckbox("datiStudio" "OSDisegno" "2" elStudio)}&nbsp; caso-controllo
						<br/>
						&nbsp;${setCheckbox("datiStudio" "OSDisegno" "3" elStudio)}&nbsp; di coorte prospettico
						<br/>
						&nbsp;${setCheckbox("datiStudio" "OSDisegno" "4" elStudio)}&nbsp; di coorte retrospettivo
						<br/>
						&nbsp;${setCheckbox("datiStudio" "OSDisegno" "5" elStudio)}&nbsp; descrittivo/fattibilit&agrave;
						<br/>
						&nbsp;${setCheckbox("datiStudio" "OSDisegno" "6" elStudio)}&nbsp; qualitativo
						<br/></td>
				</tr>
				<tr>
					<td style="">&nbsp;${setCheckbox("datiStudio" "tipoStudio" "6" elStudio)}&nbsp; Studio esclusivamente su materiali biologici</td>
				</tr>
				<tr>
					<td class="txtleft" style=" width: 1000px; ">
						Specificare il tipo di campione/tessuto:&nbsp;${elStudio.getFieldDataString("datiStudio","GESpecificare")}
					</td>
				</tr>
			</table>
			<br/>
			<table cellspacing="0" style="border: 0px solid black; border-collapse: collapse;">
				<tr>
					<td>
						*Per indagini aggiuntive si intendono procedure diagnostiche e/o di follow up aggiuntive rispetto alla pratica clinica, che non rappresentano l'oggetto di studio
					</td>
				</tr>
			</table>
			<div style="page-break-before: always">&nbsp;</div>
			<table cellspacing="0" style="border: 1px solid black; border-collapse: collapse;">
				<tr>
					<td class="txtleft" colspan="2" style=" width: 1000px; ">
						<b>Multicentricit&agrave;</b>
					</td>
				</tr>
				<tr>
					<td class="txtleft" style="width:100%; " colspan="2">
						&nbsp;${setCheckbox("datiStudio" "Multicentrico" "2" elStudio)}&nbsp; Studio Monocentrico
						<br/>
						&nbsp;${setCheckbox("datiStudio" "Multicentrico" "1" elStudio)}&nbsp; Studio Multicentrico
						<br/><br/>
						<b>Centro coordinatore italiano (per studi multicentrici)</b>
						${elStudio.getFieldDataString("datiCoordinatore","CentroCoordinatore")} PI: ${elStudio.getFieldDataString("datiCoordinatore","Nome")} ${elStudio.getFieldDataString("datiCoordinatore","Cognome")}
						<br/>
						<b>Numero di centri italiani</b>&nbsp; ${elStudio.getFieldDataString("datiStudio","NumCentri")}<br/>
					</td>
				</tr>
				<tr>
					<td style="">&nbsp;${setCheckbox("datiStudio" "Internazionale" "2" elStudio)}&nbsp; Studio nazionale<br/>
						&nbsp;${setCheckbox("datiStudio" "Internazionale" "1" elStudio)}&nbsp; Studio internazionale</td>
				</tr>
			</table>
			<br/>
			<table cellspacing="0" style="border: 1px solid black; border-collapse: collapse;">
				<tr>
					<td class="txtleft" style="width:50%;  padding:4px;"><b>Et&agrave;</b></td>
				</tr>
				<!--tr>
					<td style="" colspan="2">&nbsp;${setCheckbox("datiStudio" "Sesso" "F" elStudio)}&nbsp; Sesso</td>
				</tr>
				<tr>
					<td class="txtleft" style="width:50%;  padding-left:40px;" colspan="2">
						&nbsp;${setCheckbox("datiStudio" "Sesso" "1" elStudio)}&nbsp; Maschile
						<br/>
						&nbsp;${setCheckbox("datiStudio" "Sesso" "2" elStudio)}&nbsp; Femminile
						<br/>
					</td>
				</tr-->
				<tr>
					<td class="txtleft" style="width:50%;  padding-left: 40px;" colspan="2">

						&nbsp;${setCheckbox("datiStudio" "EtaMin" "1" elStudio)}&nbsp; In utero
						<br/>
						&nbsp;${setCheckbox("datiStudio" "EtaMin" "2" elStudio)}&nbsp; Neonati pre-termine(fino a un'et&agrave; gestazionale 37 settimane)
						<br/>
						&nbsp;${setCheckbox("datiStudio" "EtaMin" "3" elStudio)}&nbsp; Neonati (0-27 giorni)
						<br/>
						&nbsp;${setCheckbox("datiStudio" "EtaMin" "4" elStudio)}&nbsp; Lattanti e bambini piccoli (28 giorni-23 mesi)
						<br/>
						&nbsp;${setCheckbox("datiStudio" "EtaMin" "5" elStudio)}&nbsp; Bambini (2-11 anni)
						<br/>
						&nbsp;${setCheckbox("datiStudio" "EtaMin" "6" elStudio)}&nbsp; Adolescenti (12-17 anni)
						<br/>
						&nbsp;${setCheckbox("datiStudio" "EtaMin" "7" elStudio)}&nbsp; Adulti (18-44 anni)
						<br/>
						&nbsp;${setCheckbox("datiStudio" "EtaMin" "8" elStudio)}&nbsp; Adulti (45 - 65 anni)
						<br/>
						&nbsp;${setCheckbox("datiStudio" "EtaMin" "9" elStudio)}&nbsp; Anziani (da  65 anni)
						<br/>
					</td>
				</tr>
			</table>
			<br/>
			<table cellspacing="0" style="border: 1px solid black; border-collapse: collapse;">
				<tr>
					<td class="txtleft" style="width:50%;  padding:4px;"><b>Arruolamento di "categorie vulnerabili"</b></td>
				</tr>
				<tr>
					<td class="txtleft" style="width:50%;  padding-left: 40px;" colspan="2">
						&nbsp;${setCheckbox("datiStudio" "SPTipoPop" "7" elStudio)}&nbsp; Per et&agrave;
						<br/>
						&nbsp;${setCheckbox("datiStudio" "SPTipoPop" "1" elStudio)}&nbsp; Volontari sani
						<br/>
						&nbsp;${setCheckbox("datiStudio" "SPTipoPop" "2" elStudio)}&nbsp; Pazienti
						<br/>
						&nbsp;${setCheckbox("datiStudio" "SPTipoPop" "3" elStudio)}&nbsp; Donne in gravidanza e in allattamento
						<br/>
						&nbsp;${setCheckbox("datiStudio" "SPTipoPop" "5" elStudio)}&nbsp; Pazienti in situazioni di emergenza
						<br/>
						&nbsp;${setCheckbox("datiStudio" "SPTipoPop" "4" elStudio)}&nbsp; Incapaci di intendere e di volere
						<br/>
						&nbsp;${setCheckbox("datiStudio" "SPTipoPop" "6" elStudio)}&nbsp; Altre categorie vulnerabili  - specificare: ${elStudio.getFieldDataString("datiStudio","PopolazioneVulnerabile")}
						<br/><br/>
						<em>Specificare le modalit&agrave; di arruolamento (dove e come): ${elStudio.getFieldDataString("datiStudio","VolontariSani")}</em>
					</td>
				</tr>
			</table>
			<br/>
			<table cellspacing="0" style="border: 1px solid black; border-collapse: collapse;">
				<tr>
					<td class="txtleft" style="width:50%;  padding:4px;"><b><u>Dati relativi allo Sperimentatore responsabile:</u></b></td>
				</tr>
				<tr>
					<td class="txtleft" style=" width: 1000px; " colspan="2">
						Nome e Cognome: ${el.getFieldDataDecode("IdCentro","PINomeCognome")}
					</td>
				</tr>
				<tr>
					<td class="txtleft" style=" width: 1000px; " colspan="2">
						Qualifica professionale: ${el.getFieldDataDecode("IdCentro","Qualifica")}
					</td>
				</tr>
				<tr>
					<td class="txtleft" style=" width: 1000px; " colspan="2">
						Azienda/Ente: ${el.getFieldDataDecode("IdCentro","Struttura")}
					</td>
				</tr>
				<tr>
					<td class="txtleft" style=" width: 1000px; " colspan="2">
						Ospedale/Presidio: ${el.getFieldDataDecode("IdCentro","OspedalePresidio")}
					</td>
				</tr>
				<tr>
					<td class="txtleft" style=" width: 1000px; " colspan="2">
						Dipartimento: ${el.getFieldDataDecode("IdCentro","Dipartimento")}
					</td>
				</tr>
				<tr>
					<td class="txtleft" style=" width: 1000px; " colspan="2">
						Unit&agrave; Operativa: ${el.getFieldDataDecode("IdCentro","UO")}
					</td>
				</tr>
				<tr>
					<td>&nbsp; </td>
				</tr>
			</table>
			<br/>
			<table cellspacing="0" style="border: 1px solid black; border-collapse: collapse;">
				<tr>
					<td class="txtleft" colspan="5" style="width:50%;  padding:4px;"><b><u>Informazioni relative a PROMOTORE, CRO, FINANZIATORE / SUPPLIER </u></b> </td>
				</tr>

				<tr style="background-color:#eee;">
					<th class="txtcenter" style="border: 1px solid black; width: 1000px; ">
						<b>&nbsp; </b>
					</th>
					<th class="txtcenter" style="border: 1px solid black; width: 1000px; ">
						<b>Denominazione</b>
					</th>
					<th class="txtcenter" style="border: 1px solid black; width: 1000px; ">
						<b>Referente</b>
					</th>
					<th class="txtcenter" style="border: 1px solid black; width: 1000px; ">
						<b>Indirizzo</b>
					</th>
					<th class="txtcenter" style="border: 1px solid black; width: 1000px; ">
						<b>Recapito Mail e telefonico</b>
					</th>

				</tr>
			<#list elStudio.getChildrenByType("PromotoreStudio") as currPromotore >
				<#if currPromotore.getFieldDataElement("datiPromotore","promotore")?? && currPromotore.getFieldDataElement("datiPromotore","promotore")[0]?? >
				<tr>
					<#assign promotore=currPromotore.getFieldDataElement("datiPromotore","promotore")[0] />
					<td class="txtleft" style="border: 1px solid black; width: 1000px; ">
						<b><em>PROMOTORE</em></b>
					</td>
					<td class="txtleft" style="border: 1px solid black; width: 1000px; ">
						${promotore.titleString}
					</td>
					<td class="txtleft" style="border: 1px solid black; width: 1000px; ">
						${currPromotore.getFieldDataString("datiPromotore","RefNomeCognomeF")}
					</td>
					<td class="txtleft" style="border: 1px solid black; width: 1000px; ">
						${currPromotore.getFieldDataString("datiPromotore","RefIndirizzoF")}
					</td>
					<td class="txtleft" style="border: 1px solid black; width: 1000px; ">
						${currPromotore.getFieldDataString("datiPromotore","RefEmailF")} ${currPromotore.getFieldDataString("datiPromotore","RefTelF")}
					</td>
				</tr>
				</#if>
			</#list>
			<#list elStudio.getChildrenByType("CROStudio") as currCRO >
				<#if currCRO.getFieldDataElement("datiCRO","denominazione")?? && currCRO.getFieldDataElement("datiCRO","denominazione")[0]?? >
				<tr>
					<#assign cro=currCRO.getFieldDataElement("datiCRO","denominazione")[0] />
					<td class="txtleft" style="border: 1px solid black; width: 1000px; ">
						<b><em>CRO</em></b>
					</td>
					<td class="txtleft" style="border: 1px solid black; width: 1000px; ">
						${cro.titleString}
					</td>
					<td class="txtleft" style="border: 1px solid black; width: 1000px; ">
						${currCRO.getFieldDataString("datiCRO","RefNomeCognomeF")}
					</td>
					<td class="txtleft" style="border: 1px solid black; width: 1000px; ">
						${currCRO.getFieldDataString("datiCRO","RefIndirizzoF")}
					</td>
					<td class="txtleft" style="border: 1px solid black; width: 1000px; ">
						${currCRO.getFieldDataString("datiCRO","RefEmailF")} ${currCRO.getFieldDataString("datiCRO","RefTelF")}
					</td>
				</tr>
			</#if>
			</#list>
			<#list elStudio.getChildrenByType("FinanziatoreStudio") as currFIN >
				<tr>
					<td class="txtleft" style="border: 1px solid black; width: 1000px; ">
						<b><em>FINANZIATORE/SUPPLIER</em></b>
					</td>
					<td class="txtleft" style="border: 1px solid black; width: 1000px; ">
						${currFIN.getFieldDataString("datiFinanziatore","NomeFinanziatore")}
					</td>
					<td class="txtleft" style="border: 1px solid black; width: 1000px; ">
						${currFIN.getFieldDataString("datiFinanziatore","FinReferente")}
					</td>
					<td class="txtleft" style="border: 1px solid black; width: 1000px; ">
						${currFIN.getFieldDataString("datiFinanziatore","FinIndirizzo")}
					</td>
					<td class="txtleft" style="border: 1px solid black; width: 1000px; ">
						${currFIN.getFieldDataString("datiFinanziatore","FinEmail")} ${currFIN.getFieldDataString("datiFinanziatore","FinTelefono")}
					</td>
				</tr>
			</#list>
				<tr>
					<td class="txtleft" style="border: width:1000px; " colspan="5">
						Specificare a chi &egrave; affidata l'attivit&agrave; di monitoraggio clinico dello studio:<br/><!--TODO quale campo è? -->
						Nota: si ricorda che il monitoraggio dello studio &egrave; a cura del Promotore, che lo pu&ograve; svolgere direttamente oppure delegando un terzo soggetto
					</td>
				</tr>
			</table>
			<div style="page-break-before: always">&nbsp;</div>
			<table cellspacing="0" style="border: 1px solid black; border-collapse: collapse;">
				<tr>
					<td class="txtleft" style="width:50%;  padding:4px;"><b>Setting dello studio</b></td>
				</tr>
				<tr>
					<td class="txtleft" style=" width: 1000px;">Ambulatoriale </td>
					<td class="txtleft" style="width:50%;  padding:4px;">
						&nbsp;${setCheckbox("Feasibility" "regimeAmb" "1" el)}&nbsp; S&igrave;
						&nbsp;${setCheckbox("Feasibility" "regimeAmb" "2" el)}&nbsp; No
						<br/>
					</td>
				</tr>
				<tr>
					<td class="txtleft" style=" width: 1000px;">di Ricovero </td>
					<td class="txtleft" style="width:50%;  padding:4px;">
						&nbsp;${setCheckbox("Feasibility" "regimeRicovero" "1" el)}&nbsp; S&igrave;
						&nbsp;${setCheckbox("Feasibility" "regimeRicovero" "2" el)}&nbsp; No
						<br/>
					</td>
				</tr>
				<tr>
					<td class="txtleft" style=" width: 1000px;">Day Surgery/One Day Surgery </td>
					<td class="txtleft" style="width:50%;  padding:4px;">
						&nbsp;${setCheckbox("Feasibility" "regimeDHS" "1" el)}&nbsp; S&igrave;
						&nbsp;${setCheckbox("Feasibility" "regimeDHS" "2" el)}&nbsp; No
						<br/>
					</td>
				</tr>
				<tr>
					<td class="txtleft" style=" width: 1000px;">Day Service </td>
					<td class="txtleft" style="width:50%;  padding:4px;">
						&nbsp;${setCheckbox("Feasibility" "regimeDS" "1" el)}&nbsp; S&igrave;
						&nbsp;${setCheckbox("Feasibility" "regimeDS" "2" el)}&nbsp; No
						<br/>
					</td>
				</tr>
				<tr>
					<td class="txtleft" style=" width: 1000px;">Se non applicabile, specificare: </td>
					<td class="txtleft" style="width:50%;  padding:4px;">${el.getFieldDataString("Feasibility","regimeSpec")}</td>
				</tr>
			</table>
			<br/>
			<table cellspacing="0" style="border: 1px solid black; border-collapse: collapse;">
				<tr>
					<td class="txtleft" style="width:50%;  padding:4px;"><b>Durata dello studio nel centro</b></td>
				</tr>
				<tr>
					<td class="txtleft" style=" width: 1000px; " colspan="2">
						Data prevista di inizio studio: <#if el.getfieldData("DatiCentro","InizioDt")?? && el.getfieldData("DatiCentro","InizioDt")[0]??>${el.getfieldData("DatiCentro","InizioDt")[0].time?date?string("dd/MM/yyyy")}</#if>
					</td>
				</tr>
				<tr>
					<td class="txtleft" style=" width: 1000px; " colspan="2">
						Data prevista di inizio arruolamento: <#if el.getfieldData("DatiCentro","ArruolamentoDt")?? && el.getfieldData("DatiCentro","ArruolamentoDt")[0]?? >${el.getfieldData("DatiCentro","ArruolamentoDt")[0].time?date?string("dd/MM/yyyy")}</#if>
					</td>
				</tr>
				<tr>
					<td class="txtleft" style=" width: 1000px; " colspan="2">
						Data prevista di fine studio: <#if el.getfieldData("DatiCentro","FineDt")?? && el.getfieldData("DatiCentro","FineDt")[0]??>${el.getfieldData("DatiCentro","FineDt")[0].time?date?string("dd/MM/yyyy")}</#if>
					</td>
				</tr>
			</table>
			<br/>
			<table cellspacing="0" style="border: 1px solid black; border-collapse: collapse;">
				<tr>
					<td class="txtleft" style="width:50%;  padding:4px;"><b>Sottostudi</b></td>
				</tr>
				<tr>
					<td class="txtleft" style="width:50%;  padding-left: 40px;">
					&nbsp;${setCheckbox("datiStudio" "Sottostudi" "1" elStudio)}&nbsp; Farmacocinetica
					<br/>
					&nbsp;${setCheckbox("datiStudio" "Sottostudi" "2" elStudio)}&nbsp; Farmacodinamica
					<br/>
					&nbsp;${setCheckbox("datiStudio" "Sottostudi" "3" elStudio)}&nbsp; Farmacoeconomia
					<br/>
					&nbsp;${setCheckbox("datiStudio" "Sottostudi" "4" elStudio)}&nbsp; Farmacogenetica
					<br/>
					&nbsp;${setCheckbox("datiStudio" "Sottostudi" "5" elStudio)}&nbsp; Farmacogenomica
					<br/>
					&nbsp;${setCheckbox("datiStudio" "Sottostudi" "6" elStudio)}&nbsp; Indagine sui biomarcatori
					<br/>
					&nbsp;${setCheckbox("datiStudio" "Sottostudi" "7" elStudio)}&nbsp; Qualit&agrave; della vita
					<br/>
					&nbsp;${setCheckbox("datiStudio" "Sottostudi" "8" elStudio)}&nbsp; Nessuno
					<br/>
					&nbsp;${setCheckbox("datiStudio" "Sottostudi" "-9999" elStudio)}&nbsp; Altro
					</td>
				</tr>
			</table>
			<div style="page-break-before: always">&nbsp;</div>
			<table cellspacing="0" style="border-collapse: collapse;">
				<tr>
					<td  class="txtcenter" colspan="6" style="padding-bottom: 10px; padding-top: 20px;"><b>SEZIONE B: Modulo per l'analisi dei costi aggiuntivi correlati allo Studio</b></td>
				</tr>
				<tr>
					<td class="txtleft"  colspan="6" style="width:50%;  padding:4px;"><b>Personale direttamente coinvolto nel team dello studio</b>(compreso lo Sperimentatore Responsabile dello studio)<b> presso la struttura/UO proponente</b></td>
				</tr>

				<tr style="background-color:#eee;">
					<th class="txtcenter" style="border: 1px solid black; width: 1000px; ">
						<b>Nome e Cognome</b>
					</th>
					<th class="txtcenter" style="border: 1px solid black; width: 1000px; ">
						<b>Struttura di appartenenza</b>
					</th>
					<th class="txtcenter" style="border: 1px solid black; width: 1000px; ">
						<b>Recapito (Mail e telefono)</b>
					</th>
					<th class="txtcenter" style="border: 1px solid black; width: 1000px; ">
						<b>Qualifica professionale *</b>
					</th>
					<th class="txtcenter" style="border: 1px solid black; width: 1000px; ">
						<b>Rapporto di lavoro **</b>
					</th>
					<th class="txtcenter" style="border: 1px solid black; width: 1000px; ">
						<b>Integrazione ai fini assistenziali</b>
					</th>

				</tr>
				<#list el.getChildrenByType("TeamDiStudio") as personale >
				<tr>
					<td class="txtleft" style="border: 1px solid black; width: 1000px; ">
						<#if personale.getFieldDataCode("DatiTeamDiStudio","TipoPersonale")=="1">
							${personale.getFieldDataDecode("DatiTeamDiStudio","NomeCognome")}
						<#else>
							${personale.getFieldDataString("DatiTeamDiStudio","AltroPersonale")}
						</#if>
					</td>
					<td class="txtleft" style="border: 1px solid black; width: 1000px; ">
						<#if personale.getFieldDataCode("DatiTeamDiStudio","TipoPersonale")=="1">
							${personale.getFieldDataDecode("DatiTeamDiStudio","Struttura")}
						<#else>
							${personale.getFieldDataString("DatiTeamDiStudio","EnteNonDip")}
						</#if>
					</td>
					<td class="txtleft" style="border: 1px solid black; width: 1000px; ">
						${personale.getFieldDataString("DatiTeamDiStudio","Email")} ${personale.getFieldDataString("DatiTeamDiStudio","Telefono")}
					</td>
					<td class="txtleft" style="border: 1px solid black; width: 1000px; ">
						${personale.getFieldDataDecode("DatiTeamDiStudio","Qualifica")}
					</td>
					<td class="txtleft" style="border: 1px solid black; width: 1000px; ">
						${personale.getFieldDataDecode("DatiTeamDiStudio","Ruolo")}
					</td>
					<td class="txtleft" style="border: 1px solid black; width: 1000px; ">
						&nbsp;${setCheckbox("DatiTeamDiStudio" "IntegrazioneAssistenziale" "1" personale)}S&igrave;
						&nbsp;${setCheckbox("DatiTeamDiStudio" "IntegrazioneAssistenziale" "2" personale)}No
						&nbsp;${setCheckbox("DatiTeamDiStudio" "IntegrazioneAssistenziale" "3" personale)}NA
					</td>
				</tr>
				</#list>
			</table>
			<br/>
			<table cellspacing="0" style="border-collapse: collapse;">
				<tr>
					<td class="txtleft" style="width:50%;  padding:4px;"><b>N.B.</b> Per lo svolgimento o la partecipazione alle attivit&agrave; cliniche dello studio &egrave; sempre necessaria l'esistenza di un valido ed efficace titolo allo svolgimento dell'attivit&agrave; presso la struttura.</td>
				</tr>
				<tr>
					<td class="txtleft" style="width:50%;  padding:4px;"><b>*</b> Specificare se medico, infermiere, farmacista, biologo, data manager, etc.
						<br/> <b>**</b> Specificare se dipendente Ospedaliero, dipendendte universitario con integrazione assistenziale, medico in formazione, assegnista, libero professionista, dottorando, borsista, etc.</td>
				</tr>
			</table>
			<br/>
			<table cellspacing="0" style="border-collapse: collapse;">
				<tr>
					<td style="width:50%; font-weight: bold; padding-left:10px;">Altro personale coinvolto (dirigenza e comparto) presso strutture/UO diverse da quella proponente che collaborano con la UO proponente per lo svolgimento di prestazioni studio-specifiche.</td>
				</tr>
				<tr>
					<td class="txtleft" style="width: 1000px;">Per l'espletamento del presente studio deve essere coinvolto altro personale? <br/>
						<#if el.getChildrenByType("FeasibilityServiziRichiesta")?size gt 0 >
							&nbsp;${setCheckbox("datiStudio" "FC9" "T" elStudio)}&nbsp; S&igrave;
							&nbsp;${setCheckbox("datiStudio" "FC9" "F" elStudio)}&nbsp; No
						<#else>
							&nbsp;${setCheckbox("datiStudio" "FC9" "F" elStudio)}&nbsp; S&igrave;
							&nbsp;${setCheckbox("datiStudio" "FC9" "T" elStudio)}&nbsp; No
						</#if>
						<br/>
						Se sì, compilare di seguito
					</td>
				</tr>
			</table>
			<table cellspacing="0" style="border-collapse: collapse;">
				<tr style="background-color:#eee;">
					<th class="txtcenter" style="border: 1px solid black; width: 1000px; ">
						<b>&nbsp; </b>
					</th>
					<th class="txtcenter" style="border: 1px solid black; width: 1000px; ">
						<b>Servizi/Sezioni coinvolti</b>
					</th>
					<th class="txtcenter" style="border: 1px solid black; width: 1000px; ">
						<b>Figure coinvolte (ad es. radiologo, anatomo patologo, tecnico di radiologia, tecnico di laboratorio, etc.)</b>
					</th>
				</tr>
				<#assign servizioCnt=0 />
				<#list el.getChildrenByType("FeasibilityServiziRichiesta") as servizio >
				<#assign servizioCnt=servizioCnt+1 />
				<tr>
					<td class="txtleft" style="border: 1px solid black; width: 1000px; ">
						<b><em>${servizioCnt}</em></b>
					</td>
					<td class="txtleft" style="border: 1px solid black; width: 1000px; ">
						${servizio.getFieldDataString("FeasibilitySUO","Servizio")} - ${servizio.getFieldDataDecode("FeasibilitySUO","Struttura")} - ${servizio.getFieldDataDecode("FeasibilitySUO","Dipartimento")} - ${servizio.getFieldDataString("FeasibilitySUO","UO")}
					</td>
					<td class="txtleft" style="border: 1px solid black; width: 1000px; ">
						${servizio.getFieldDataString("FeasibilitySUO","FigureCoinvolte")}
					</td>
				</tr>
			</#list>
			<tr>
				<td class="" style="width:50%;  padding:4px;" colspan="3"><b>Allegare la dichiarazione di attestazione del coinvolgimento sottoscritta dal relativo Responsabile</b></td>
			</tr>
			</table>
			<div style="page-break-before: always">&nbsp;</div>
			<table cellspacing="0" style="border-collapse: collapse;">
				<tr>
					<td class="txtcenter"><b>COSTI AGGIUNTIVI</b></td>
				</tr>
				<tr>
					<td class="txtleft" style="width:50%;  padding:4px;">I medicinali sperimentali ed eventualmente i dispositivi udati per somministrarli sono forniti gratuitamente dal promotore dello studio profit; nessun costo aggiuntivo, per la conduzione e la gestione degli studi di cui al presente decreto deve gravare sulla finanza pubblica": decreto legislativo 24.06.2003, n.211 - art. 20, comma 2.
						<br/><br/>Relativamente agli studi no profit finalizati al miglioramento della pratica clinica ex art. 6 del D.M. 17/12/2004, i farmaci sono a carico del SSN, mentre le eventuali spese aggiuntive, comprese quelle per il farmaco sperimentale, qualora non coperte da fondi di ricerca ad hoc possono gravare sul Fondo della Ricerca di cui all'art. 2, comma 3 del citato Decreto, sempre che si tratti di studi promossi dalla Struttura.
						<br/><br/>Relativamente agli studi no profit NON finalizzati al miglioramento della pratica clinica ex art. 6 del D.M. 17/12/2004, i promotori devono garantire la fornitura dei farmaci sperimentali, il rimborso dei farmaci con AIC se il relativo utilizzo &egrave; richiesto dal protocollo di studio e la copertura delle spese aggintive.</td>
				</tr>
				<tr>
					<td class="" style="width:50%;text-align: center;  padding:4px;background-color: white;border: 0px;"><b><u>Materiale Sperimentale </u></b></td>
				</tr>
				<tr>
					<td class="txtleft" style="width:50%;  padding:4px;"><b>Se trattasi di studio interventistico di farmaco</b></td>
				</tr>
			</table>
			<table cellspacing="0" style="border-collapse: collapse;">
				<tr style="background-color:#eee;">
					<th class="txtcenter" style="border: 1px solid black; width: 1000px; ">
						<b>Elenco Farmaci Sperimentali</b>
					</th>
					<th class="txtcenter" style="border: 1px solid black; width: 1000px; ">
						<b>ATC</b>
					</th>
					<th class="txtcenter" style="border: 1px solid black; width: 1000px; ">
						<b>Codice modalit&agrave; copertura oneri finanziari (A, B, C, D)</b>
					</th>
				</tr>
			<#list el.getChildrenByType("DepotFarmaco") as depotFarmaco >
				<#if depotFarmaco.getFieldDataString("depotFarmaco","tipo")=="1" && depotFarmaco.getFieldDataElement("depotFarmaco","linkFarmaco")?? && depotFarmaco.getFieldDataElement("depotFarmaco","linkFarmaco")[0]?? >
					<#assign farmaco=depotFarmaco.getFieldDataElement("depotFarmaco","linkFarmaco")[0] />
					<#if farmaco?? >
					<tr>
						<td class="txtleft" style="border: 1px solid black; width: 1000px; ">
							${farmaco.titleString}
						</td>
						<td class="txtleft" style="border: 1px solid black; width: 1000px; ">
							${farmaco.getFieldDataString("Farmaco","CodiceATC")}
						</td>
						<td class="txtleft" style="border: 1px solid black; width: 1000px; ">
							${depotFarmaco.getFieldDataDecode("depotFarmaco","modalitaFornitura")}
						</td>
					</tr>
					</#if>
				</#if>
			</#list>
			</table>
			<table cellspacing="0" style="border-collapse: collapse;">
				<tr>
					<td style="width:50%;  padding-left:10px;"><b>A=</b> a carico del Promotore <i>(specificare la modalit&agrave; - ad es. fornitura diretta, pagamento anticipato, rimborso)</i>
						<br/><b>B=</b> a carico di fondi della Unit&agrave; Operativa a disposizione dello Sperimentatore <sup>*</sup> - specificare codice identificativo del fondo, se presente
						<br/><b>C=</b> fornitura/finanziamento preoveniente da terzi (in tal caso allegare l'accordo tra Promotore e finanziatore terzo che regolamenta la fornitura/il contributo economico) *
						<br/><b>D=</b> a carico del Fondo Aziendale per la Ricerca, ove presente **</td>

				</tr>
				<tr>
					<td style="width:50%;  padding-left:10px;">* Applicabile solo per studi no profit
						<br/> ** Applicabile solo per studi no profit finalizzati al miglioramento della pratica clinica</td>
				</tr>
			</table>
			<div style="page-break-before: always">&nbsp;</div>
			<table cellspacing="0" style="border-collapse: collapse;">
				<tr>
					<td colspan="5" class="txtleft" style="width:50%;  padding:4px;"><b>Se trattasi di indagine clinica di dispositivo medico</b></td>
				</tr>
				<tr style="background-color:#eee;">
					<th class="txtcenter" style="border: 1px solid black; width: 1000px; ">
						<b>Elenco DM Sperimentali<br/>(nome commerciale e modello)
						</b>
					</th>
					<th class="txtcenter" style="border: 1px solid black; width: 1000px; ">
						<b>Numero di registrazione in banca dati dispositivi medici/ repertorio dispositivi medici</b>
					</th>
					<!--th class="txtcenter" style="border: 1px solid black; width: 1000px; ">
						<b>Impiego secondo destinazione d'uso</b>
					</th -->
					<th class="txtcenter" style="border: 1px solid black; width: 1000px; ">
						<b>Classe di rischio</b>
					</th>
					<th class="txtcenter" style="border: 1px solid black; width: 1000px; ">
						<b>Fabbricante</b>
					</th>
					<!-- th class="txtcenter" style="border: 1px solid black; width: 1000px; ">
						<b>DM gi&agrave; in uso in Azienda?</b>
					</th -->
					<th class="txtcenter" style="border: 1px solid black; width: 1000px; ">
						<b>Codice modalit&agrave; copertura oneri finanziari (A, B, C, D)</b>
					</th>
				</tr>
				<#list el.getChildrenByType("DepotFarmaco") as depotFarmaco >
				<#if depotFarmaco.getFieldDataString("depotFarmaco","tipo")=="2" && depotFarmaco.getFieldDataElement("depotFarmaco","linkFarmaco")?? && depotFarmaco.getFieldDataElement("depotFarmaco","linkFarmaco")[0]?? >
					<#assign farmaco=depotFarmaco.getFieldDataElement("depotFarmaco","linkFarmaco")[0] />

					<#if farmaco?? >
					<tr>
						<td class="txtleft" style="border: 1px solid black; width: 1000px; ">
							${farmaco.titleString}
						</td>
						<td class="txtleft" style="border: 1px solid black; width: 1000px; ">
							${farmaco.getFieldDataString("Farmaco","numeroRepertorioDisp")}
						</td>
						<!-- td class="txtleft" style="border: 1px solid black; width: 1000px; ">
							${farmaco.getFieldDataDecode("Farmaco","ImpiegoDestUso")}
						</td -->
						<td class="txtleft" style="border: 1px solid black; width: 1000px; ">
							${farmaco.getFieldDataDecode("Farmaco","classeDiRischioDisp")}
						</td>
						<td class="txtleft" style="border: 1px solid black; width: 1000px; ">
							${farmaco.getFieldDataString("Farmaco","DittaProduttriceDisp")}
						</td>
						<!-- td class="txtleft" style="border: 1px solid black; width: 1000px; ">
							${depotFarmaco.getFieldDataDecode("depotFarmaco","GaraFornituraDisp")}
						</td -->
						<td class="txtleft" style="border: 1px solid black; width: 1000px; ">
							${depotFarmaco.getFieldDataDecode("depotFarmaco","modalitaFornitura")}
						</td>
					</tr>
					</#if>
				</#if>
				</#list>
			</table>
			<br/>
			<table cellspacing="0" style="border-collapse: collapse;">
				<tr>
					<td style="width:1000px;  padding-left:10px;" colspan="2"><b>A=</b> a carico del Promotore in quanto non gi&agrave; in uso nel centro (art.2, comma 1 lettera t) punto 8 del D. Lgs. n.37 del 25/01/2010 "...Le spese ulteriori rispetto alla normale pratica clinica, derivanti dall'applicazione del presente comma, sono a carico del fabbricante. I dispositivi medici occorrenti per le indagini cliniche, che non sono gi&agrave; stati acuisiti nel rispetto delle ordinarie procedure di fornitura dei beni, sono altreS&igrave; a carico del fabbricante..."
						<br/><b>B=</b> a carico di fondi della Unit&agrave; Operativa a disposizione dello Sperimentatore <sup>*</sup> - specificare il codice identificativo del fondo, se presente
						<br/><b>C=</b> fornitura/finanziamento preoveniente da terzi (in tal caso allegare l'accordo tra Promotore e finanziatore terzo che regolamenta la fornitura/il contributo economico)
						<br/><b>D=</b> a carico del Fondo Aziendale per la Ricerca, ove presente **</td>

				</tr>
				<tr>
					<td style="width:50%;  padding-left:10px;">* Applicabile solo per studi no profit
						<br/> ** Applicabile solo per studi no profit finalizzati al miglioramento della pratica clinica</td>
				</tr>
			</table>
			<table  cellspacing="0" style="border-collapse: collapse;">
				<tr><td>&nbsp;</td></tr>
					<#list el.getChildrenByType("DepotFarmaco") as depotFarmaco >
						<#if depotFarmaco.getFieldDataString("depotFarmaco","tipo")=="2" && depotFarmaco.getFieldDataElement("depotFarmaco","linkFarmaco")?? && depotFarmaco.getFieldDataElement("depotFarmaco","linkFarmaco")[0]?? >
							<#assign farmaco=depotFarmaco.getFieldDataElement("depotFarmaco","linkFarmaco")[0] />

							<#if farmaco?? >
							<tr>
								<td class="txtleft" >
									Nome commerciale e modello <b>${farmaco.titleString}</b>
									<br/>
									Presenza del Marchio CE? &nbsp;${setCheckbox("Farmaco" "MarchioCE" "1" farmaco)}&nbsp; S&igrave;	&nbsp;${setCheckbox("Farmaco" "MarchioCE" "2" farmaco)}&nbsp; No
									<ul>
										<li>
											se si, specificare per quali indicazioni: ${farmaco.getFieldDataString("Farmaco","IndicazioniDisp")}
										</li>
										<li>
											se no, &egrave; necessario presentare notifica di indagine clinica al Ministero, secondo quanto previsto dal decreto ministeriale della salute del 2 agosto 2005 (GU 201 del 9 settembre 205)
										</li>
									</ul>
									<br/>
									Nella sperimentazione l'impiego avviene secondo l'indicazione per cui &egrave; stata ottenuta la marcatura CE?
									<br/>
									&nbsp;${setCheckbox("Farmaco" "ImpiegoDestUso" "1" farmaco)}&nbsp; S&igrave;	&nbsp;${setCheckbox("Farmaco" "ImpiegoDestUso" "2" farmaco)}&nbsp; No
									<ul>
									<li>
										se no, è necessario presentare notifica di indagine clinica al Ministero, secondo quanto previsto dal decreto ministero della salute del 2 agosto 2005 (GU 210 del 9 settembre 2005)
									</li>
									</ul>
									<br/>
									Il dispositivo presenta tessuto animale a rischio di trasmissione di encefalopatia spongiforme (TSE)?
									<br/>
									&nbsp;${setCheckbox("Farmaco" "TessutoAnimaleDisp" "1" farmaco)}&nbsp; S&igrave;	&nbsp;${setCheckbox("Farmaco" "TessutoAnimaleDisp" "2" farmaco)}&nbsp; No
									<br/>
									Il dispositivo medico incorpora un medicinale:
									<br/>
									&nbsp;${setCheckbox("Farmaco" "IncorporaMedicinaleDisp" "1" farmaco)}&nbsp; S&igrave;	&nbsp;${setCheckbox("Farmaco" "IncorporaMedicinaleDisp" "2" farmaco)}&nbsp; No
									<br/>
									se si,
									<ul>
										<li>
											il medicinale e il DM sono integralmente uniti in un solo prodotto, destinato ad essere utilizzato esclusivamente in tale associazione e non riutilizzabile
											<br/>
											&nbsp;${setCheckbox("Farmaco" "MedicinaleUnitoDisp" "1" farmaco)}&nbsp; S&igrave;	&nbsp;${setCheckbox("Farmaco" "MedicinaleUnitoDisp" "2" farmaco)}&nbsp; No
										</li>
										<li>
											il medicinale ha azione accessoria a quella del DM
											<br/>
											&nbsp;${setCheckbox("Farmaco" "MedicinaleAccessioriDisp" "1" farmaco)}&nbsp; S&igrave;	&nbsp;${setCheckbox("Farmaco" "MedicinaleAccessioriDisp" "2" farmaco)}&nbsp; No
										</li>
									</ul>
									<br/>
									<u>Allegare</u> breve sintesi del profilo farmacologico, clinico e di sicurezza del medicinale quando utilizzato con azione accessoria a quella del DM (con riferimento alle pagine della documentazione tecnica in cui sono descritti i relativi dettagli)
									Il dispositivo è già presente in gara di fornitura in Area Vasta?&nbsp;${setCheckbox("depotFarmaco" "GaraFornituraDisp" "1" depotFarmaco)}&nbsp; S&igrave;	&nbsp;${setCheckbox("depotFarmaco" "GaraFornituraDisp" "2" depotFarmaco)}&nbsp; No
									<br/>
									A quale prezzo disponibile in commercio?&nbsp;${depotFarmaco.getFieldDataString("depotFarmaco","prezzoInCommercio")} &euro;
									<br/>
									Sede di utilizzo/impianto:&nbsp;${farmaco.getFieldDataString("Farmaco","SedeImpiantoDisp")}
									<br/>
								</td>
							</tr>
							<#else>
							<tr>
								<td></td>
							</tr>
							</#if>
						</#if>
					</#list>
			</table>
			<div style="page-break-before: always">&nbsp;</div>
			<table cellspacing="0" style="border-collapse: collapse;">
				<tr>
					<td class="txtleft" style="width: 1000px;"><b>Altro materiale sperimentale (specificare, ad es. integratore)</b>
				<#assign listaAltroMateriale="" />
				<#assign listaAltroMaterialeBool=false />
				<#assign listaAltroMateriale >
					<ul>
						<#list el.getChildrenByType("DepotFarmaco") as depotFarmaco >
							<#if depotFarmaco.getFieldDataString("depotFarmaco","tipo")=="5" && depotFarmaco.getFieldDataElement("depotFarmaco","linkFarmaco")?? && depotFarmaco.getFieldDataElement("depotFarmaco","linkFarmaco")[0]?? >
								<#assign farmaco=depotFarmaco.getFieldDataElement("depotFarmaco","linkFarmaco")[0] />
								<#if farmaco?? >
									<#assign listaAltroMaterialeBool=true />
									<li>${farmaco.titleString} - Codice Modalit&agrave; copertura oneri finanziari (A, B, C, D): ${depotFarmaco.getFieldDataDecode("depotFarmaco","modalitaFornitura")}</li>
								</#if>
							</#if>
						</#list>
					</ul>
				</#assign>
				<#if listaAltroMaterialeBool>
						&nbsp;${setCheckbox("datiStudio" "FC9" "T" elStudio)}&nbsp; S&igrave;
						&nbsp;${setCheckbox("datiStudio" "FC9" "F" elStudio)}&nbsp; No
				<#else>
						&nbsp;${setCheckbox("datiStudio" "FC9" "F" elStudio)}&nbsp; S&igrave;
						&nbsp;${setCheckbox("datiStudio" "FC9" "T" elStudio)}&nbsp; No
				</#if>
					<br/>
					</td>
				</tr>
				<tr>
					<td style="width:50%;  padding-left:10px;">
						<#if listaAltroMaterialeBool>
							Descrizione:
							${listaAltroMateriale}
						</#if>




					</td>
				</tr>
			</table>
			<table cellspacing="0" style="border-collapse: collapse;">
				<tr style="width:100%;  padding-left:10px;">
					<td style="width:1000px;  padding-left:10px;" colspan="7"><b>Prestazioni aggiuntive studio-specifiche</b>
						<#if prestazioniAggiuntive?size gt 0 >
							&nbsp;${setCheckbox("datiStudio" "FC9" "T" elStudio)}&nbsp; S&igrave;
							&nbsp;${setCheckbox("datiStudio" "FC9" "F" elStudio)}&nbsp; No
						<#else>
							&nbsp;${setCheckbox("datiStudio" "FC9" "F" elStudio)}&nbsp; S&igrave;
							&nbsp;${setCheckbox("datiStudio" "FC9" "T" elStudio)}&nbsp; No
						</#if>
						<br/>
					</td>
				</tr>
				<tr>
					<td style="width:100%;  padding-left:10px;" colspan="7">Se lo studio prevede l'esecuzione di prestazioni specialistiche aggiuntive rispetto alla pratica clinica (es. ricoveri, visite, esami strumentali o di laboratorio), incluse quelle previste
						per l'arruolamento, come da flow-chart dello studio, elencarle di seguito ed indicare per ognuna di esse la quantit&agrave;, la corrispondente tariffa come da
						Nomenclatore Regionale, nonch&egrave; le modalit&agrave; proposte per la copertura del relativo costo, come da codici indicati:
						<br/> <b>N.B.:</b> come previsto dalle Linee guida per la classificazione e conduzione degli studi osservazionali sui farmaci (Determina AIFA del 20/03/2008), nell'ambito di uno studio osservaionale <i> le procedure diagnostiche e valutative devono
							corrispondere alla pratica clinica corrente.</i></td>
				</tr>
				<tr>
					<td style="width:50%;  padding-left:10px;" colspan="7"><b>Prestazioni/attivit&agrave; aggiuntive della struttura ove si conduce lo studio e/o di altre strutture dell'Azienda</b> (&egrave; possibile allegare una flow-chart come materiale integrativo alla tabella che va comunque compilata. Il numero di prestazioni &egrave; previsionale, secondo protocollo)</td>
				</tr>
				<tr style="background-color:#eee;">
					<th class="txtcenter" style="border: 1px solid black; width: 1000px; ">
						<b>Servizi/Sezioni coinvolti (Struttura erogante) </b>
					</th>
					<th class="txtcenter" style="border: 1px solid black; width: 1000px; ">
						<b>Codice Prestazione: (SSR)</b>
					</th>
					<th class="txtcenter" style="border: 1px solid black; width: 1000px; ">
						<b>Descrizione</b>
					</th>
					<th class="txtcenter" style="border: 1px solid black; width: 1000px; ">
						<b>Tariffa da nomenclatore (SSR)</b>
					</th>
					<th class="txtcenter" style="border: 1px solid black; width: 1000px; ">
						<b>Tariffa Prestazione proposta dal Promotore (se disponibile)</b>
					</th>
					<th class="txtcenter" style="border: 1px solid black; width: 1000px; ">
						<b>N. Prest./Paziente</b>
					</th>
					<th class="txtcenter" style="border: 1px solid black; width: 1000px; ">
						<b>Opzionale (si/no) </b>
					</th>
					<th class="txtcenter" style="border: 1px solid black; width: 1000px; ">
						<b>Codice modalit&agrave; copertura oneri finanziari (A, B, C, D, E)</b>
					</th>
				</tr>
				<#assign totPrice=0 />
				<#assign totPricePaz=0 />
				<#list prestazioniAggiuntive as prestazione>
				<tr>
					<td class="txtleft" style="border: 1px solid black; width: 1000px; ">
						<#if prestazione.getFieldDataElement("Prestazioni","CDC")?? && prestazione.getFieldDataElement("Prestazioni","CDC")[0]?? >
							${prestazione.getFieldDataElement("Prestazioni","CDC")[0].titleString}
						<#else>
							${prestazione.getFieldDataString("Prestazioni","CDCCode")}
						</#if>
					</td>
					<td class="txtleft" style="border: 1px solid black; width: 1000px; ">
						<#if prestazione.getFieldDataString("Prestazioni","Codice")??>
							${prestazione.getFieldDataString("Prestazioni","Codice")}
						</#if>
					</td>
					<td class="txtleft" style="border: 1px solid black; width: 1000px; ">
						<#if prestazione.getFieldDataString("Base","Nome")?? >
						${prestazione.getFieldDataString("Base","Nome")}
					</#if>
					</td>
					<td class="txtright" style="border: 1px solid black; width: 1000px; ">
						<#assign tpriceSSN="" />
						<#if prestazione.getFieldDataString("Tariffario","SSN")?? && prestazione.getFieldDataString("Tariffario","SSN") !="">
							<#assign tpriceSSN="&euro; " +prestazione.getFieldDataString("Tariffario","SSN")?number?string("##0.00")>
						</#if>
						${tpriceSSN}
					</td>
					<td class="txtright" style="border: 1px solid black; width: 1000px; ">
						<#assign tprice=0>
						<#if prestazione.getFieldDataString("Costo","TransferPrice")?? >
							<#assign tprice=prestazione.getFieldDataString("Costo","TransferPrice")?number >
							<#assign totPrice+=tprice />
						</#if>
					&euro; ${tprice?string("##0.00")}
					</td>
					<td class="txtleft" style="border: 1px solid black; width: 1000px; ">
						<#assign quantitaPaz=0 />
						<#if prestazione.getFieldDataString("Costo","Quantita")?? && prestazione.getFieldDataString("Costo","Quantita")!="" >
							<#assign quantitaPaz=prestazione.getFieldDataString("Costo","Quantita") >
							<#assign totPricePaz+=tprice?number*quantitaPaz?number >
						</#if>
						${quantitaPaz}
					</td>
					<td class="txtleft" style="border: 1px solid black; width: 1000px; ">
						<#if prestazione.getFieldDataDecode("Prestazioni","Opzionale")?? >
						${prestazione.getFieldDataDecode("Prestazioni","Opzionale")}
					</#if>
					</td>
					<td class="txtleft" style="border: 1px solid black; width: 1000px; ">
						<#if prestazione.getFieldDataDecode("Costo","Copertura")?? >
							${prestazione.getFieldDataDecode("Costo","Copertura")}
						</#if>
					</td>
				</tr>
				</#list>
			</table>
			<table cellspacing="0" style="border-collapse: collapse; border:1px black solid;">
				<tr style="width:100%;  padding-left:10px;">
					<td class="" style="width:1000px;text-align: center;  padding:4px;" colspan="2"><b><u>Attrezzature a supporto e non oggetto di studio:</u></b></td>
				</tr>
				<tr>
					<td class="txtleft" style="width:1000px;  padding-left:10px;" colspan="2"><b>Fornitura di beni in comodato</b>
						<b>Sono presenti beni in comodato</b> ${setCheckbox("Feasibility" "FC27" "1" el)} S&igrave; ${setCheckbox("Feasibility" "FC27" "2" el)} No<br/><br/>
						<b>Descrizione:</b> ${el.getFieldDataString("Feasibility","FC27bis")}<br/><br/>
						<b>Marcato CE:</b> &nbsp;${setCheckbox("Feasibility" "FC27ter" "1" el)}&nbsp; S&igrave;
						&nbsp;${setCheckbox("Feasibility" "FC27ter" "2" el)}&nbsp; No
						&nbsp;${setCheckbox("Feasibility" "FC27ter" "3" el)}&nbsp; Non applicabile<br/><br/>
						<b>Numero Repertorio generale dei dispositivi medici:</b> ${setCheckbox("Feasibility" "FC27quar" "1" el)}&nbsp; S&igrave;
						&nbsp;${setCheckbox("Feasibility" "FC27quar" "2" el)}&nbsp; No
						&nbsp;${setCheckbox("Feasibility" "FC27quar" "3" el)}&nbsp; Non applicabile
						<br/>
					</td>
				</tr>
			</table>
			<table cellspacing="0" style="border-collapse: collapse;">
				<tr>
					<td style="width:50%;  padding-left:10px;"><b>Altri costi aggiuntivi, se presenti</b></td>
				</tr>
			</table>
			<table cellspacing="0" style="border-collapse: collapse;">
				<tr style="background-color:#eee;">
					<th class="txtcenter" style="border: 1px solid black; width: 1000px; ">
						<b>Descrizione</b>
					</th>
					<th class="txtcenter" style="border: 1px solid black; width: 1000px; ">
						<b>Previsto</b>
					</th>
					<th class="txtcenter" style="border: 1px solid black; width: 1000px; ">
						<b>Codice Modalit&agrave; Copertura Oneri Finanziari (A, B, C, D)</b>
					</th>
					<th class="txtcenter" style="border: 1px solid black; width: 1000px; ">
						<b>Importo totale</b>
					</th>
				</tr>
				<#assign totCostiAgg=0 />
				<#list costiAggiuntivi as costoAggiuntivo>
				<tr>
					<td class="txtleft" style="border: 1px solid black; width: 1000px; ">
						<#if costoAggiuntivo.getFieldDataDecode("CostoAggiuntivo","Tipologia")?? >
							${costoAggiuntivo.getFieldDataDecode("CostoAggiuntivo","Tipologia")}
						</#if>
					</td>
					<td class="txtleft" style="border: 1px solid black; width: 1000px; ">
						<#if costoAggiuntivo.getFieldDataDecode("CostoAggiuntivo","Previsto")?? >
							${costoAggiuntivo.getFieldDataDecode("CostoAggiuntivo","Previsto")}
						</#if>
					</td>
					<td class="txtleft" style="border: 1px solid black; width: 1000px; ">
						<#if costoAggiuntivo.getFieldDataDecode("CostoAggiuntivo","Copertura")?? >
							${costoAggiuntivo.getFieldDataDecode("CostoAggiuntivo","Copertura")}
						</#if>
					</td>
					<td class="txtright" style="border: 1px solid black; width: 1000px; ">
						<#assign tprice=0>
						<#if costoAggiuntivo.getFieldDataString("CostoAggiuntivo","Costo")?? >
						<#assign tprice=costoAggiuntivo.getFieldDataString("CostoAggiuntivo","Costo")?number >
						<#assign totCostiAgg+=tprice />
					</#if>
					&euro; ${tprice?string("##0.00")}
					</td>
				</tr>
			</#list>
			</table>
			<table cellspacing="0" style="border-collapse: collapse;">
				<tr>
					<td style="width:50%;  padding-left:10px;">
						<b>A=</b> a  carico del Promotore
						<br/><b>B=</b> a carico di fondi della Unità Operativa a disposizione dello Sperimentatore*
						<br/><b>C=</b> finanziamento proveniente da terzi (in tal caso allegare l'accordo tra Promotore e finanziatore terzo che regolamento il contributo economico)
						<br/><b>D=</b> a carico del Fondo Aziendale per la Ricerca, ove presente**
					</td>
				</tr>
				<tr>
					<td style="width:50%;  padding-left:10px;">
						* Applicabile solo per studi no profit<br/>
						** Applicabile solo per studi no profit finalizzati al miglioramento della pratica clinica
					</td>
				</tr>
			</table>
			<div style="page-break-before: always">&nbsp;</div>
			<table cellspacing="0" style="border-collapse: collapse;">
				<tr>
					<td class="txtcenter" colspan="2"><b>COINVOLGIMENTO DELLA FARMACIA</b></td>
				</tr>
				<tr>
					<td colspan="2">Lo studio prevede il coinvolgimento diretto della Farmacia? ${setCheckbox("Feasibility" "FC1" "1" el)} S&igrave;&nbsp;${setCheckbox("Feasibility" "FC1" "2" el)} No;
					</td>
				</tr>
				<tr>
					<td colspan="2">1. il coinvolgimento della Farmacia &egrave; richiesto per:
					</td>
				</tr>
				<tr>
					<td colspan="2">${setCheckbox("Feasibility" "FC2" "1" el)}&nbsp; La randomizzazione
					</td>
				</tr>
				<tr>
					<td colspan="2">${setCheckbox("Feasibility" "FC31" "1" el)}&nbsp; lo stoccaggio a breve termine e la consegna del materiale sperimentale (farmaco/dispositivo medico)</td>
				</tr>
				<tr><!--TODO NON C'E' QUESTO CAMPO! -->
					<td colspan="2">${setCheckbox("Feasibility" "FC31" "1" el)}&nbsp; lo stoccaggio a lungo termine (farmaco/dispositivo medico)  <#if el.getFieldDataCode("datiStudio","FC3")?? && el.getFieldDataCode("datiStudio","FC3")=="1" >ed in particolare</#if>
					</td>
				</tr>

				<tr>
					<td colspan="2" >${setCheckbox("Feasibility" "FC3" "1" el)}&nbsp; la preparazione del/i farmaco/i sperimentale/i (compreso il placebo) ed in particolare:</td>
				</tr>
				<tr>
					<td colspan="2" style="padding-left: 20px;">${setCheckbox("Feasibility" "FC4" "1" el)}&nbsp; esecuzione di studio di fattibilit&agrave;
					</td>
				</tr>
				<tr>
					<td colspan="2" style="padding-left: 20px;">${setCheckbox("Feasibility" "FC4bis" "1" el)}&nbsp; definizione della formulazione;
					</td>
				</tr>
				<tr>
					<td colspan="2" style="padding-left: 20px;">${setCheckbox("Feasibility" "FC5" "1" el)}&nbsp; allestimento del/i farmaco/i sperimentale/i;
					</td>
				</tr>
				<tr>
					<td colspan="2" style="padding-left: 20px;">${setCheckbox("Feasibility" "FC6" "1" el)}&nbsp; ricostituzione
					</td>
				</tr>
				<tr>
					<td colspan="2" style="padding-left: 20px;">${setCheckbox("Feasibility" "FC6bis" "1" el)}&nbsp; diluizione, anche in dose personalizzata
					</td>
				</tr>
				<tr>
					<td colspan="2" style="padding-left: 20px;">${setCheckbox("Feasibility" "FC7" "1" el)}&nbsp; confezionamento
					</td>
				</tr>
				<tr>
					<td colspan="2" style="padding-left: 20px;">${setCheckbox("Feasibility" "FC7bis" "1" el)}&nbsp; mascheramento
					</td>
				</tr>
				<tr>
					<td colspan="2">${setCheckbox("Feasibility" "FC8" "1" el)}&nbsp; Altro (specificare): ${getField("Feasibility","noteFC8",el)}
					</td>
				</tr>
				<tr>
					<td colspan="2">
						Tutte le attivit&agrave; di cui sopra sono richieste per (barrare la voce pertinente):
					</td>
				</tr>
				<tr>
					<td colspan="2" style="padding-left: 20px;">${setCheckbox("Feasibility" "FC9" "1" el)}&nbsp; questo singolo centro;</td>
				</tr>
				<tr>
					<td colspan="2" style="padding-left: 20px;">${setCheckbox("Feasibility" "FC10" "1" el)}&nbsp; I seguenti centri partecipanti allo studio (fornire l'elenco completo): ${getField("Feasibility","noteFC10",el)}</td>
				</tr>
				<tr>
					<td colspan="2">
						<b>Se S&igrave;, fornire il parere della Farmacia e dare evidenza che nella bozza di convenzione economica sia previsto il compenso concordato per l'esecuzione delle suddette attivit&agrave;.</b>
					</td>
				</tr>
				<tr><td>&nbsp;</td></tr>
				<tr>
					<td colspan="2"><b>Si esprime Parere Favorevole:</b>
					</td>
				</tr>
				<tr>
					<td width="50%"><b>Data<br/><br/>...............</b></td>
					<td width="50%"><b>Il Direttore del Dipartimento Farmaceutico</b> (se pertinente) <b> o suo referente</b><br/><br/>..........................................................................................................................<br/>(Timbro e firma per esteso)
					</td>
				</tr>
			</table>
			<div style="page-break-before: always">&nbsp;</div>
			<table cellspacing="0" style="border-collapse: collapse;">
				<tr>
					<td class="txtcenter" colspan="2" style="padding-bottom: 10px; padding-top: 20px;">
						<b>Sezione C: Modulo riepilogativo aspetti economici</b>
					</td>
				</tr>
				<#assign profit=false />
				<#if elStudio.getFieldDataCode("datiStudio","NaturaDelloStudio")=="1" >
					<#assign profit=true />
				</#if>
				<tr>
					<td><b>Studi profit</b></td>
				</tr>
				<tr>
					<td class="txtleft" style="border: 1px solid black; width: 1000px; ">
						<b><em>Numero pazienti previsti nel centro</em></b>
					</td>
					<td class="txtright" style="border: 1px solid black; width: 1000px; ">
						<#if profit && budgetStudio??>
							${budgetStudio.getFieldDataString("BudgetCTC","NumeroPazienti")}
						<#else>
						&nbsp;
						</#if>

					</td>
				</tr>
				<tr>
					<td class="txtleft" style="border: 1px solid black; width: 1000px; ">
						<b><em>Corrispettivo contrattuale (grant) per paziente</em></b>
					</td>
					<td class="txtright" style="border: 1px solid black; width: 1000px; ">
						<#assign proposta_promotore='0' />
						<#assign proposta_numerica='0' />
						<#if profit >
							<#if budgetStudio?? && budgetStudio.getFieldDataString("BudgetCTC","TipoTarget")?? >
								<#if budgetStudio.getFieldDataString("BudgetCTC","TipoTarget")=="2" >
									<#assign proposta_promotore="&euro; " + budgetStudio.getFieldDataString("BudgetCTC","TargetPaziente")?number?string("##0.00") />
									<#assign proposta_numerica=budgetStudio.getFieldDataString("BudgetCTC","TargetPaziente") />
								<#elseif budgetStudio.getFieldDataString("BudgetCTC","TipoTarget")=="3" >
									<#assign proposta_promotore=" &euro; " +budgetStudio.getFieldDataString("BudgetCTC","TargetStudio")?number?string("##0.00")+" per intero studio" />
									<#assign proposta_numerica=budgetStudio.getFieldDataString("BudgetCTC","TargetStudio") />
								</#if>
							</#if>
						<#else>
							<#assign proposta_promotore='&nbsp;' />
							<#assign proposta_numerica='&nbsp;' />
						</#if>

						${proposta_promotore}
					</td>
				</tr>
				<tr>
					<td class="txtleft" style="border: 1px solid black; width: 1000px; ">
						<b><em>Corrispettivo delle prestazioni aggiuntive a paziente </em></b>
					</td>
					<td class="txtright" style="border: 1px solid black; width: 1000px; ">
						<#if profit >
							&euro; ${totPricePaz?number?string("##0.00")}
						<#else>
						&nbsp;
						</#if>

					</td>
				</tr>
				<tr>
					<td class="txtleft" style="border: 1px solid black; width: 1000px; ">
						<b><em>Corrispettivo contrattuale totale a paziente</em></b>
					</td>
					<td class="txtright" style="border: 1px solid black; width: 1000px; ">
						<#if profit >
							<#assign totPaz=proposta_numerica?number+totPricePaz?number />
							&euro; ${totPaz?number?string("##0.00")}
						<#else>
							&nbsp;
						</#if>
					</td>
				</tr>
				<tr>
					<td class="txtleft" style="border: 1px solid black; width: 1000px; ">
						<b><em>Corrispettivo per le fees aggiuntive se previsto da regolamento del centro (attività amministrative/costi generali o di start-up, fee per il servizio farmaceutico, ecc)</em></b>
					</td>
					<td class="txtright" style="border: 1px solid black; width: 1000px; ">
						<#if profit >
							&euro; ${totCostiAgg?number?string("##0.00")}
						<#else>
							&nbsp;
						</#if>
					</td>
				</tr>
			</table>
			<br/>
			<table style="border: 1px solid black; border-collapse: collapse;">
				<tr><td><b>Studi no profit</b></td></tr>
				<tr>
					<td class="txtleft" style="width: 1000px;" colspan="2">Studio no profit finanziato
						&nbsp;${setCheckbox("datiStudio" "NoProfitFinanziato" "1" elStudio)}&nbsp; S&igrave;
						&nbsp;${setCheckbox("datiStudio" "NoProfitFinanziato" "2" elStudio)}&nbsp; No
						<br/>
					</td>
				</tr>
				<tr>
					<td class="txtleft" style="width: 1000px;" colspan="2">Studio no profit con finanziamento interno
						<#if !profit && budgetStudio??>
							&nbsp;${setCheckbox("BudgetCTC" "FINnoProfitFinanzInterno" "1" budgetStudio)}&nbsp; S&igrave;
							&nbsp;${setCheckbox("BudgetCTC" "FINnoProfitFinanzInterno" "2" budgetStudio)}&nbsp; No
						<#else>
							&nbsp;${setCheckbox("BudgetCTC" "FINnoProfitFinanzInterno" "F" elStudio)}&nbsp; S&igrave;
							&nbsp;${setCheckbox("BudgetCTC" "FINnoProfitFinanzInterno" "F" elStudio)}&nbsp; No
						</#if>
						<br/>
					</td>
				</tr>
				<tr>
					<td>N° pazienti previsti nel centro &nbsp;
						<#if !profit && budgetStudio??>
							${budgetStudio.getFieldDataString("BudgetCTC","NumeroPazienti")}
						</#if>
					</td>
				</tr>
				<tr>
					<td>Note:
						<#if !profit && budgetStudio??>
							&nbsp;${budgetStudio.getFieldDataString("BudgetCTC","FINNoteFinanziamento")}
						</#if>
					</td>
				</tr>
			</table>
			<table cellspacing="0" style="border-collapse: collapse;">
				<tr>
					<td  class="txtcenter" colspan="2" style="padding-bottom: 10px; padding-top: 20px;">
						<b>Sezione D: Modulo di previsione di impiego del finanziamento per lo studio (solo per studi no profit con finanziamento dedicato)</b>
					</td>
				</tr>
				<tr>
					<td>
						<table cellspacing="0" style="border-collapse: collapse;">
							<tr>
								<td class="txtcenter" style="border: 1px solid black; width: 1000px;" colspan="2">
									<b><em>PREVISIONE IMPIEGO FINANZIAMENTO</em></b>
								</td>
							</tr>
							<tr>
								<td class="txtleft" style="border: 1px solid black; width: 1000px; ">
									<b><em>Entit&agrave; del finanziamento, di cui</em></b>
								</td>
								<td class="txtright" style="border: 1px solid black; width: 1000px; ">
									<#if budgetStudio??>
									<b><em>&euro; ${budgetStudio.getFieldDataString("BudgetCTC","FINEntita")}</em></b>
									</#if>

								</td>
							</tr>
							<tr>
								<td class="txtleft" style="border: 1px solid black; width: 1000px; ">
									<b><em>Coordinamento </em></b>
								</td>
								<td class="txtright" style="border: 1px solid black; width: 1000px; ">
									<#if budgetStudio??>
									<b><em>&euro; ${budgetStudio.getFieldDataString("BudgetCTC","FINCoordinamento")}</em></b>
								</#if>
								</td>
							</tr>
							<tr>
								<td class="txtleft" style="border: 1px solid black; width: 1000px; ">
									<b><em>Personale</em></b>
								</td>
								<td class="txtright" style="border: 1px solid black; width: 1000px; ">
									<#if budgetStudio??>
									<b><em>&euro; ${budgetStudio.getFieldDataString("BudgetCTC","FINPersonale")}</em></b>
								</#if>
								</td>
							</tr>
							<tr>
								<td class="txtleft" style="border: 1px solid black; width: 1000px; ">
									<b><em>Attrezzature</em></b>
								</td>
								<td class="txtright" style="border: 1px solid black; width: 1000px; ">
									<#if budgetStudio??>
									<b><em>&euro; ${budgetStudio.getFieldDataString("BudgetCTC","FINAttrezzature")}</em></b>
								</#if>
								</td>
							</tr>
							<tr>
								<td class="txtleft" style="border: 1px solid black; width: 1000px; ">
									<b><em>Servizi</em></b>
								</td>
								<td class="txtright" style="border: 1px solid black; width: 1000px; ">
									<#if budgetStudio??>
									<b><em>&euro; ${budgetStudio.getFieldDataString("BudgetCTC","FINServizi")}</em></b>
								</#if>
								</td>
							</tr>
							<tr>
								<td class="txtleft" style="border: 1px solid black; width: 1000px; ">
									<b><em>Materiale di consumo</em></b>
								</td>
								<td class="txtright" style="border: 1px solid black; width: 1000px; ">
									<#if budgetStudio??>
									<b><em>&euro; ${budgetStudio.getFieldDataString("BudgetCTC","FINMateriale")}</em></b>
								</#if>
								</td>
							</tr>
							<tr>
								<td class="txtleft" style="border: 1px solid black; width: 1000px; ">
									<b><em>Meeting, convegni, viaggi</em></b>
								</td>
								<td class="txtright" style="border: 1px solid black; width: 1000px; ">
									<#if budgetStudio??>
									<b><em>&euro; ${budgetStudio.getFieldDataString("BudgetCTC","FINMeeting")}</em></b>
								</#if>
								</td>
							</tr>
							<tr>
								<td class="txtleft" style="border: 1px solid black; width: 1000px; ">
									<b><em>Pubblicazioni</em></b>
								</td>
								<td class="txtright" style="border: 1px solid black; width: 1000px; ">
									<#if budgetStudio??>
									<b><em>&euro; ${budgetStudio.getFieldDataString("BudgetCTC","FINPubblicazioni")}</em></b>
								</#if>
								</td>
							</tr>
							<tr>
								<td class="txtleft" style="border: 1px solid black; width: 1000px; ">
									<b><em>Assicurazione</em></b>
								</td>
								<td class="txtright" style="border: 1px solid black; width: 1000px; ">
									<#if budgetStudio??>
									<b><em>&euro; ${budgetStudio.getFieldDataString("BudgetCTC","FINAssicurazione")}</em></b>
								</#if>
								</td>
							</tr>
							<tr>
								<td class="txtleft" style="border: 1px solid black; width: 1000px; ">
									<b><em>Altro</em></b>
								</td>
								<td class="txtright" style="border: 1px solid black; width: 1000px; ">
									<#if budgetStudio??>
									<b><em>&euro; ${budgetStudio.getFieldDataString("BudgetCTC","FINAltro")}</em></b>
								</#if>
								</td>
							</tr>
							<tr>
								<td class="txtleft" style="border: 1px solid black; width: 1000px; ">
									<b><em>Spese generali ("overhead")</em></b>
								</td>
								<td class="txtright" style="border: 1px solid black; width: 1000px; ">
									<#if budgetStudio??>
									<b><em>&euro; ${budgetStudio.getFieldDataString("BudgetCTC","FINGenerali")}</em></b>
								</#if>
								</td>
							</tr>
						</table>
					</td>
				</tr>
				</table>
				<div style="page-break-before: always">&nbsp;</div>
				<table cellspacing="0" style="border-collapse: collapse;">
				<tr>
					<td  class="txtcenter" colspan="2" style="padding-bottom: 10px; padding-top: 20px;">
						<b>Sezione E: Assunzione di responsabilit&agrave; a cura dello Sperimentatore Responsabile dello Studio</b>
					</td>
				</tr>
				<tr>
					<td>
						<table >
							<tr>
								<td>
																					<span style="text-align: justify">Il sottoscritto ..........................................................,
																					Responsabile dello studio,<b>ai sensi e per gli effetti delle disposizioni di cui al DPR 445/2000 e s.m.i., consapevole
																							delle sanzioni penali nel caso di falsit&agrave; in atti e dichiarazioni mendaci, sotto la propria responsabilit&agrave;, dichiara che:</b></span>
								</td>
							</tr>
							<tr>
								<td>
										-&nbsp;visti i criteri per l'arruolamento dei pazienti previsti dal presente protocollo, essi non confliggono con i criteri di arruolamento di altri protocolli attivati presso l'Unit&agrave; Operativa;<br/>
										-&nbsp;il personale coinvolto (sperimentatore principale e collaboratori) &egrave; competente ed idoneo;<br/>
										-&nbsp;l'Unit&agrave; Operativa presso cui si svolge la ricerca &egrave; appropriata; <br/>
										-&nbsp;&egrave; garantita l'assenza di pregiudizi per l'attivit&agrave; assistenziale come previsto dall'articolo 7 della Legge Regionale n. 9 del 1/6/2017;<br/>
										-&nbsp;dispone di tempo e mezzi necessari per svolgere lo studio;<br/>
										-&nbsp;lo studio verr&agrave; condotto secondo il protocollo di studio, in conformit&agrave; ai principi della Buona Pratica Clinica, della Dichiarazione di Helsinki (versione 64th WMA General Assembly, Fortaleza, Brazil, October 2013) e nel rispetto delle normative vigenti<br/>
										-&nbsp;ai soggetti che parteciperanno allo studio, al fine di una consapevole espressione del consenso, verranno fornite tutte le informazioni necessarie, inclusi i potenziali rischi correlati allo studio;<br/>
										-&nbsp;l'inclusione del paziente nello studio sar&agrave; registrata sulla cartella clinica o su altro documento ufficiale, unitamente alla documentazione del consenso informato;<br/>
										-&nbsp;si assicurer&agrave; che ogni emendamento o qualsiasi altra modifica al protocollo che si dovesse verificare nel corso dello studio, rilevante per la conduzione dello stesso, verr&agrave; inoltrato al Comitato Etico da parte del Promotore;<br/>
										-&nbsp;comunicher&agrave; ogni evento avverso serio al Comitato Etico e al Promotore secondo normativa vigente secondo quanto indicato nel protocollo dello studio;<br/>
										-&nbsp;ai fini del monitoraggio e degli adempimenti amministrativi, verr&agrave; comunicato al Comitato Etico l'inizio e la fine dello studio nonch&eacute; inviato, almeno annualmente, il rapporto scritto sull'avanzamento dello studio e verranno forniti, se richiesto, rapporti ad interim sullo stato di avanzamento dello studio;<br/>
										-&nbsp;la documentazione inerente lo studio verr&agrave; conservata in conformit&agrave; a quanto stabilito dalle Norme di Buona Pratica Clinica e alle normative vigenti;<br/>
										-&nbsp;la ricezione del medicinale sperimentale (se previsto) utilizzato per lo studio avverr&agrave; attraverso la farmacia della struttura sanitaria e, successivamente, il medicinale stesso verr&agrave; conservato presso il centro sperimentale separatamente dagli altri farmaci;<br/>
										-&nbsp;non sussistono vincoli di diffusione e pubblicazione dei risultati dello studio nel rispetto delle disposizioni vigenti in tema di riservatezza dei dati  sensibili e di tutela brevettuale e, non appena disponibile, verr&agrave; inviata copia della relazione finale e/o della pubblicazione inerente;<br/>
										-&nbsp;(mantenere unicamente la dichiarazione pertinente tra le due opzioni) lo studio &egrave; coperto da specifica polizza assicurativa oppure non &egrave; necessaria spcifica copertura assicurativa in quanto ....................................................................................................................(specificare la motivazione per cui si ritiene non necessaria specifica copertura assicurativa - tale aspetto sar&agrave; comunque oggetto di valutazione da parte del Comitato Etico);<br/>
										-&nbsp;non percepisce alcun compenso diretto per lo svolgimento dello studio;<br/>
										-&nbsp;se studio profit la convenzione economica verr&agrave; stipulata tra .............................................................. e .........................................................;<br/>
										-&nbsp;se studio no profit, (mantenere unicamente la dichiarazione pertinente tra le due opzioni) non &egrave; previsto alcun finanziamento dedicato per la conduzione dello studio oppure le modalit&agrave; di impiego del finanziamento dedicato per la conduzione dello studio sono esplicitate nella specifica sezione D del presente documento ed il corrispondente accordo finanziario sar&agrave; stipulato tra ................................................................................... e .......................................................................;<br/>
										-&nbsp;se studio no profit, qualora successivamente all'approvazione del Comitato Etico si ravvisasse la necessit&agrave; di acquisire un finanziamento a copertura di costi per sopraggiunte esigenze legate alla conduzione dello studio, si impegna a sottoporre al Comitato Etico, tramite emendamento sostanziale, la documentazione comprovante l'entit&agrave; del finanziamento, il suo utilizzo nonch&egrave; il soggetto erogatore;<br/>
										-&nbsp;lo studio verr&agrave; avviato soltanto dopo la ricezione di formale comunicazione di parere favorevole del Comitato Etico, di autorizzazione delle Autorit&agrave; regolatorie (AIFA o Ministero della Salute) ove previsto, di espresso e motivato nullaosta del Direttore Generale della struttura sanitaria in cui &egrave; condotta l'attivit&agrave; ai sensi dell'articolo 7 della Legge Regionale n.9 del 1/6/2017 nonch&egrave;, ove previsto, stipula del relativo contratto;<br/>
										-&nbsp;lo studio verr&agrave; avviato soltanto dopo l'avvenuta nomina del responsabile e degli incaricati al trattamento dei dati richiesta dalla normativa del Garante Privacy (Decreto legislativo 30 giugno 2003, n.196)<br/>

								</td>
							</tr>
							<tr>
								<td><br/><br/>
									Data: _______________
								</td>
							</tr>
							<tr align="center">
								<td class="txtcenter" style="padding:10px">
									<b>Il Responsabile dello Studio</b><br/><br/>
									________________________________________________________________________
									<br/><br/> (Timbro e firma per esteso)
								</td>
							</tr>
							<tr>
								<td><br/><br/>
									<b>Si esprime Parere Favorevole</b>
								</td>
							</tr>
							<tr>
								<td><br/><br/>
									Data: _______________
								</td>
							</tr>
							<tr align="center">
								<td class="txtcenter" style="padding:10px">
									<b>Il Direttore della Struttura Complessa/Il Direttore di Programma</b><br/><br/>
									________________________________________________________________________
									<br/><br/> (Timbro e firma per esteso)
								</td>
							</tr>

							<tr>
								<td><br/><br/>
									<b>Si esprime Parere Favorevole</b>
								</td>
							</tr>
							<tr>
								<td><br/><br/>
									Data: _______________
								</td>
							</tr>
							<tr align="center">
								<td class="txtcenter" style="padding:10px">
									<b>Il Direttore del Dipartimento ad Attivit&agrave; Integrata</b><br/><br/>
									________________________________________________________________________
									<br/><br/> (Timbro e firma per esteso)
								</td>
							</tr>
							<tr>
								<td><br/><br/>
									<b>Si esprime Parere Favorevole</b>
								</td>
							</tr>
							<tr>
								<td><br/><br/>
									Data: _______________
								</td>
							</tr>
							<tr align="center">
								<td class="txtcenter" style="padding:10px">
									<b>Il Direttore Scientifico di IRCCS (se applicabile)</b><br/><br/>
									________________________________________________________________________
									<br/><br/> (Timbro e firma per esteso)
								</td>
							</tr>
							<tr>
								<td><br/><br/>
									<b>Si esprime Parere Favorevole</b>
								</td>
							</tr>
							<tr>
								<td><br/><br/>
									Data: _______________
								</td>
							</tr>
							<tr align="center">
								<td class="txtcenter" style="padding:10px">
									<b>Il Direttore Operativo di IRCCS (se applicabile)</b><br/><br/>
									________________________________________________________________________
									<br/><br/> (Timbro e firma per esteso)
								</td>
							</tr>
							<tr>
								<td><br/><br/>
									<b>Si esprime Parere Favorevole</b>
								</td>
							</tr>
							<tr>
								<td><br/><br/>
									Data: _______________
								</td>
							</tr>
							<tr align="center">
								<td class="txtcenter" style="padding:10px">
									<b>Il coordinatore infermieristico/tecnico (se pertinente)</b><br/><br/>
									________________________________________________________________________
									<br/><br/> (Timbro e firma per esteso)
								</td>
							</tr>
							<tr>
								<td><br/><br/>
									<b>Si esprime Parere Favorevole</b>
								</td>
							</tr>
							<tr>
								<td><br/><br/>
									Data: _______________
								</td>
							</tr>
							<tr align="center">
								<td class="txtcenter" style="padding:10px">
									<b>Il Direttore del Dipartimento Universitario <sup>3</sup></b><br/><br/>
									________________________________________________________________________
									<br/><br/> (Timbro e firma per esteso)
								</td>
							</tr>
							<tr>
								<td style="width:50%;  padding-left:10px;"><sup>3</sup> Richiesto sia per studi profit che per no-profit quando &egrave; previsto un contratto/accordo economico con il Dipartimento Universitario
									<br/>Versione del 08/03/2018
								</td>

							</tr>


						</table>

					</td>
				</tr>





			</table>
			<br/><br/><br/>
			<!--tutto qui dentro FINE-->
		</td>
		<td style="width:2%;"></td>
	</tr>
</table>

</body>
</html>
