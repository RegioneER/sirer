<#ftl encoding="utf-8">
<#include "../../themes/ace/macros.ftl">
<#setting number_format="0.##">
<#assign el=element/>
<#assign elStudio=element.getParent()/>
<#assign budgetId=el.getFieldDataString("statoValidazioneCentro","idBudgetApproved") />

	<#assign personeCoinvolte={}   />
	<#assign costiAggiuntivi=[]  /> 
	<#assign farmacologico=[]   /> 
	<#assign dispositivo=[]   />
	<#assign beni=[]   />
	<#assign materiali=[]   />
	<#assign attrezzature=[]   />
	<#assign altro=[]   />
	<#assign attivitaServizi={} />
	
	
	<#-- VERSIONE E DATA -->
	<#assign versione=0 />
	<#assign uploadDt=0 />
	<#assign data_prot=""/>
	<#list elStudio.getChildrenByType("allegato") as allegato >
	
	   <#if allegato.getFieldDataCode("DocGenerali","DocGen")=="2" >
	       
	       <#if (uploadDt==0) > <#-- uploadDt non ancora assegnato -->
	           <#assign versione=allegato.file.version />
	           <#assign uploadDt=allegato.file.uploadDt.getTimeInMillis() />
	           <#assign data_prot=allegato.file.date.time?date?string("dd/MM/yyyy") />
	       <#elseif (allegato.file.uploadDt.getTimeInMillis() > uploadDt) /> <#-- prendo sempre il documento piu' recente -->
	           <#assign versione=allegato.file.version />
               <#assign uploadDt=allegato.file.uploadDt.getTimeInMillis() />
               <#assign data_prot=allegato.file.date.time?date?string("dd/MM/yyyy") />
	       </#if>
	   </#if>
	</#list>
	
	
	<#-- FARMACI DISPOSITIVI E MATERIALI -->
	<#assign farmaci_disp_cat1_list=[] />
	<#assign farmaci_disp_cat2_list=[] />
	<#assign farmaci_disp_cat3_list=[] />
	<#assign materiali_comodato_list=[] />
	<#assign costo_cat1=0 />
	<#assign costo_cat2=0 />
	<#assign costo_cat3=0 />
	<#assign costo_comodato=0 />
	<#list elStudio.getChildrenByType("Farmaco") as farmaco >
    	<#if farmaco.getFieldDataCode("Farmaco","tipo")=="1" > <#-- FARMACI -->
        	<#if farmaco.getFieldDataCode("Farmaco","categoria")=="1" >
                <#assign farmaci_disp_cat1_list=farmaci_disp_cat1_list+[farmaco] />
                <#if farmaco.getFieldDataString("Farmaco","totaleValore")?? && farmaco.getFieldDataString("Farmaco","totaleValore") != "" >
                    <#assign costo_cat1=costo_cat1+farmaco.getFieldDataString("Farmaco","totaleValore")?number />
                </#if>
            <#elseif farmaco.getFieldDataCode("Farmaco","categoria")=="2" >
                <#assign farmaci_disp_cat2_list=farmaci_disp_cat2_list+[farmaco] />
                <#if farmaco.getFieldDataString("Farmaco","totaleValore")?? && farmaco.getFieldDataString("Farmaco","totaleValore") != "" >
                    <#assign costo_cat2=costo_cat2+farmaco.getFieldDataString("Farmaco","totaleValore")?number />
                </#if>
            <#elseif farmaco.getFieldDataCode("Farmaco","categoria")=="3" >
                <#assign farmaci_disp_cat3_list=farmaci_disp_cat3_list+[farmaco] />
                <#if farmaco.getFieldDataString("Farmaco","totaleValore")?? && farmaco.getFieldDataString("Farmaco","totaleValore")!="" >
                    <#assign costo_cat3=costo_cat3+farmaco.getFieldDataString("Farmaco","totaleValore")?number />
                </#if>
            </#if>
        <#elseif farmaco.getFieldDataCode("Farmaco","tipo")=="2" > <#-- DISPOSITIVI -->
            <#if farmaco.getFieldDataCode("Farmaco","categoriaDisp")=="1" >
                <#assign farmaci_disp_cat1_list=farmaci_disp_cat1_list+[farmaco] />
                <#if farmaco.getFieldDataString("Farmaco","totaleValore")?? && farmaco.getFieldDataString("Farmaco","totaleValore")!="" >
                    <#assign costo_cat1=costo_cat1+farmaco.getFieldDataString("Farmaco","totaleValore")?number />
                </#if>
            <#elseif farmaco.getFieldDataCode("Farmaco","categoriaDisp")=="2" >
                <#assign farmaci_disp_cat2_list=farmaci_disp_cat2_list+[farmaco] />
                <#if farmaco.getFieldDataString("Farmaco","totaleValore")?? && farmaco.getFieldDataString("Farmaco","totaleValore")!="" >
                    <#assign costo_cat2=costo_cat2+farmaco.getFieldDataString("Farmaco","totaleValore")?number />
                </#if>
            <#elseif farmaco.getFieldDataCode("Farmaco","categoriaDisp")=="3" >
                <#assign farmaci_disp_cat3_list=farmaci_disp_cat3_list+[farmaco] />
                <#if farmaco.getFieldDataString("Farmaco","totaleValore")?? && farmaco.getFieldDataString("Farmaco","totaleValore")!="" >
                    <#assign costo_cat3=costo_cat3+farmaco.getFieldDataString("Farmaco","totaleValore")?number />
                </#if>
            </#if>
        <#elseif farmaco.getFieldDataCode("Farmaco","tipo")=="3" > <#-- MATERIALI IN COMODATO -->
            <#assign materiali_comodato_list=materiali_comodato_list+[farmaco] />
            <#if farmaco.getFieldDataString("Farmaco","totaleValore")?? && farmaco.getFieldDataString("Farmaco","totaleValore")!="" >
                <#assign costo_comodato=costo_comodato+farmaco.getFieldDataString("Farmaco","totaleValore")?number />
            </#if>
        </#if>
	</#list>
	
	
	
	
	
	<#-- FASE -->
    <#assign fase="" />
    <#if elStudio.getFieldDataCode("datiStudio","tipoStudio")=="1" >
        <#assign fase=elStudio.getFieldDataDecode("datiStudio","fase") />
    <#elseif elStudio.getFieldDataCode("datiStudio","tipoStudio")=="3">
        <#assign fase=elStudio.getFieldDataDecode("datiStudio","faseDisp") />
    </#if>
    
    <#-- PROMOTORE -->
    <#assign promotore="" />
    <#assign ente_conduzione_studio=""/>
    <#assign datiPromotoreCRO="" />
    <#if elStudio.getFieldDataElement("datiPromotore","promotore")?? && elStudio.getFieldDataElement("datiPromotore","promotore")[0]?? >
        <#assign promotore=elStudio.getFieldDataElement("datiPromotore","promotore")[0] />
        <#assign ente_conduzione_studio=promotore.getFieldDataString("DatiPromotoreCRO","denominazione") >
        <#assign datiPromotoreCRO=promotore.getFieldDataString("DatiPromotoreCRO","denominazione") >
    </#if>
    
    
    <#assign profit=elStudio.getFieldDataCode("datiStudio","Profit")>
    <#if profit=="2" > <#-- NO PROFIT -->
        <#assign finanziato_da_ente=elStudio.getFieldDataCode("datiStudio","fonteFinTerzi")>
        <#assign fonteFin="">
        <#assign fonteFin2="">
        <#if finanziato_da_ente=="1">
            <#assign fonteFin=elStudio.getFieldDataDecode("datiStudio","fonteFinSpec") />
            <#assign fonteFin2=elStudio.getFieldDataDecode("datiStudio","fonteFinSpec2") />
            <#assign ente_conduzione_studio= fonteFin+ " - "+ fonteFin2>
        </#if>
    </#if>
    
    
    <#-- CRO -->
    
    <#if elStudio.getFieldDataElement("datiCRO","denominazione")?? && elStudio.getFieldDataElement("datiCRO","denominazione")[0]?? >
        <#assign cro=elStudio.getFieldDataElement("datiCRO","denominazione")[0] />
    </#if>
    
    <#-- PERSONALE -->
    <#assign personale_dipendente=[]/>
    <#assign personale_non_dipendente=[]/>
    <#list el.getChildrenByType("TeamDiStudio") as currTeam >
     <#if currTeam.getFieldDataCode("DatiTeamDiStudio","TipoPersonale")=="1" >
        <#assign personale_dipendente = personale_dipendente + [ currTeam ] />
     <#else>
        <#assign personale_non_dipendente = personale_non_dipendente + [ currTeam ] />
     </#if>
    
    
    </#list>


    <#-- PRESTAZIONI -->


    
<#if budgetId?? && budgetId!="" >
	
	<#list el.getChildrenByType("Budget") as currBudget >
		<#if currBudget.id?string==budgetId >
			<#assign budget=currBudget />
			<#list budget.getChildrenByType("FolderBudgetStudio")[0].getChildren() as currBudgetStudio >
				<#if (currBudgetStudio.getFieldDataString("BudgetCTC","Definitivo")=="1") >
					<#assign budgetStudio=currBudgetStudio/>
				</#if>
			</#list>
		</#if>
	</#list>
	<#assign totalePaziente=budgetStudio.getFieldDataString("BudgetCTC","TotalePazienteCTC")?number /> 
	<#attempt>
	
	<#assign numeroPazienti=budgetStudio.getFieldDataString("BudgetCTC","NumeroPazienti")?number /> 
	<#assign totaleStudio=budgetStudio.getFieldDataString("BudgetCTC","TotaleStudioCTC")?number /> 
	<#recover>
	
	<#assign numeroPazienti=0 /> 
	<#assign totaleStudio=0 /> 
	</#attempt>
	<#assign targetPaziente="0" />
	<#if budgetStudio.getFieldDataString("BudgetCTC","TargetPaziente")?? && budgetStudio.getFieldDataString("BudgetCTC","TargetPaziente")?string !="" >
	   <#assign targetPaziente=budgetStudio.getFieldDataString("BudgetCTC","TargetPaziente") />
    </#if>
	<#assign totaleFlow= (totalePaziente * numeroPazienti)  /> 
	<#assign sommeAggiuntive=(totaleStudio - totaleFlow)  /> 
	<#assign rowsFlowchart=[] + budget.getChildrenByType("FolderPrestazioni")[0].getChildren()  /> 
	<#assign colsFlowchart=[] + budget.getChildrenByType("FolderTimePoint")[0].getChildren()  />
	<#assign prestazioniFlowchart=[] + budget.getChildrenByType("FolderTpxp")[0].getChildren()  /> 
	<#assign prestazioniCliniche=[] + budget.getChildrenByType("FolderPXP")[0].getChildren()  /> 
	<#assign prestazioniCTC=[] + budgetStudio.getChildrenByType("FolderPXPCTC")[0].getChildren()  /> 
	<#assign passthrough=[] + budgetStudio.getChildrenByType("FolderPassthroughCTC")[0].getChildren()  /> 
	<#assign prestazioni=[] + prestazioniCliniche + prestazioniCTC  /> 
	<#assign personale=[] + prestazioniFlowchart + prestazioni + passthrough   />
	<#assign personeCoinvolte={}   />
	<#assign costiAggiuntivi=[] + budget.getChildrenByType("FolderCostiAggiuntivi")[0].getChildren()  /> 
	<#assign farmacologico=[]   /> 
	<#assign dispositivo=[]   />
	<#assign beni=[]   />
	<#assign materiali=[]   />
	<#assign attrezzature=[]   />
	<#assign altro=[]   />
	<#assign attivitaServizi={} />
	<#assign prestazioniRoutine=[] />
	<#assign totaleRoutine=0 />
	<#assign totaleExtraRoutine=0 />
	<#assign prestazioniExtraRoutine=[] />
	<#assign coperture=["NumExtraRoutineA","NumExtraRoutineB","NumExtraRoutineC","NumExtraRoutineD"] />
	<#assign totaleVisite=0 />
	<#assign totaleCostiAggiuntivi=0 />
	<#list rowsFlowchart as currPrestazione>
	         
		<#if currPrestazione.getFieldDataString("InfoBudgetPDF","NumSSNRoutine")!='' && currPrestazione.getFieldDataString("InfoBudgetPDF","NumSSNRoutine")?number gt 0 >
		     <#assign prestazioniRoutine = prestazioniRoutine + [ currPrestazione ] />  
		</#if>
	
		
		<#if currPrestazione.getFieldDataString("InfoBudgetPDF","NumExtraRoutine")!='' && currPrestazione.getFieldDataString("InfoBudgetPDF","NumExtraRoutine")?number gt 0 >
             <#assign prestazioniExtraRoutine = prestazioniExtraRoutine + [ currPrestazione ] />  
        </#if>
        
		
		
		
		
		<#--assign currServ=currPrestazione.getFieldDataString("Prestazioni","UOC") />
		<#if (currServ?contains("SERV")) >
			<#if attivitaServizi[currServ]?? >
				<#assign attivitaServizi=attivitaServizi+{currServ:attivitaServizi[currServ]+[currPrestazione]} />
			<#else>
				<#assign attivitaServizi=attivitaServizi+{currServ:[]+[currPrestazione]} />
			</#if>				
		</#if-->
		
	</#list>
	
	<#list personale as persona>
		<#assign currPersona={"Nome":"","Matricola":"","TempoMinTot":0,"Tempo":"0:00"} />
		<#assign currNome=persona.getFieldDataDecode("Costo","Personale")!"" />
		<#assign currMatricola=persona.getFieldDataString("Costo","PersonaleMatricola") />
		<#if (currNome!="") >
			<#if personeCoinvolte[currNome]?? >
				<#assign currPersona=personeCoinvolte[currNome] />
			<#else>
				<#assign currPersona=currPersona+{"Nome":currNome,"Matricola":currMatricola} />
				
			</#if>
			<#assign currMin=0 />
			<#assign currOre=0 />
			<#assign currMinStr=persona.getFieldDataString("Costo","MinutiUomo") />
			<#assign currOreStr=persona.getFieldDataString("Costo","OreUomo") />
			${currOreStr} giorgio
			<#attempt>
				<#assign currMin=currMinStr?number />
			<#recover>
			</#attempt>
			<#attempt>
				<#assign currOre=currOreStr?number />
				<#assign currMin=(currMin+(currOre*60)) />
			<#recover>
			</#attempt>
			<#assign personaTotMin=currMin+currPersona.TempoMinTot />
			<#assign personaPartOre=(personaTotMin/60)?floor />
			<#assign personaPartMin=personaTotMin-(personaPartOre*60) />
			<#assign personaTempoStr=personaPartOre?string+":" />
			<#if (personaPartMin < 10 ) >
				<#assign personaTempoStr=personaTempoStr+"0" />
			</#if>
			<#assign personaTempoStr=personaTempoStr+personaPartMin />
			<#assign currPersona=currPersona+{"Tempo":personaTempoStr} />
			
			
			<#assign personeCoinvolte=personeCoinvolte+{currNome:currPersona} />
		</#if>
	</#list>
	
	<#list costiAggiuntivi as currCostoAgg >
		<#switch currCostoAgg.getFieldDataCode("CostoAggiuntivo","Tipologia") >
		  <#case "1">
		    <#assign farmacologico=farmacologico+[currCostoAgg]   /> 
		    <#break>
		  <#case "2">
		    <#assign dispositivo=dispositivo+[currCostoAgg]   /> 
		    <#break>
		  <#case "3">
		    <#assign beni=beni+[currCostoAgg]   /> 
		    <#break>
		  <#case "4">
		    <#assign materiali=materiali+[currCostoAgg]   /> 
		    <#break>
		  <#case "5">
		    <#assign attrezzature=attrezzature+[currCostoAgg]   /> 
		    <#break>
		  <#default>
		    <#assign altro=altro+[currCostoAgg]   />
		</#switch>
	</#list>
	<#assign varie=beni+materiali+attrezzature+altro   />
<#else>
	<#assign totalePaziente="0" /> 
	<#assign numeroPazienti="0" /> 
	<#assign totaleStudio="0" /> 
	<#assign sommeAggiuntive="0"  /> 
	<#assign totaleFlow="0"  /> 
</#if>


<#assign UncheckedCheckbox>
	<img src="images/Unchecked-Checkbox-icon.png" width="10" height="10" />
</#assign>

<#assign CheckedCheckbox>
	<img src="images/Checked-Checkbox-icon.png" width="10" height="10" />
</#assign>

<#function setCheckbox templateName fieldName fieldVal element>
 	<#assign dataVal=getCode(templateName,fieldName,element) />
 	<#assign checkImage=UncheckedCheckbox />
 	<#if dataVal==fieldVal>
 		<#assign checkImage=CheckedCheckbox />
 	</#if>
	<#return checkImage />
</#function>


<#assign servizioCoinvolto="" />
<#assign listaServiziCoinvolti="" />
<#assign x=16>
<#list 1..x as i>
  <#assign currServ="FeasibilitySERV"+i />  
  <#assign currServAtt="SERV"+i />  
  <#list el.getChildrenByType(currServ) as elFeasServ>	
		<#assign servizioCoinvolto>
			<tr>
				<td class="txtleft"   style="border: 1px solid black;">${elFeasServ.getTitleString()}</td>
			  <td class="txtcenter" style="border: 1px solid black;">
			  
			  <#if (attivitaServizi[currServAtt]??)>
				  <#list attivitaServizi[currServAtt] as currPrestazione >
				  		${currPrestazione.getFieldDataString("Prestazioni","prestazione")}<br/>
				  </#list>
			  </#if>
			  &nbsp;</td>
			  <td class="txtcenter" style="border: 1px solid black;">&nbsp;</td>
			</tr>
	 	</#assign>
	 	<#assign listaServiziCoinvolti=listaServiziCoinvolti+servizioCoinvolto />
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
width:100%;
font-size: 10px;
font-family: Tahoma;
text-align: justify;
}

.border1{
border: 1px solid black;
}

.txtcenter{
text-align:center;
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
								<td class="txtcenter" style="padding-bottom: 10px; padding-top: 20px;">
									<b>ANALISI DI IMPATTO AZIENDALE</b>
								</td>
							</tr>
						</table>
						
						<table cellspacing="0" style="border-collapse: collapse;">
							<tr>
								<td class="txtleft" style="border: 1px solid black; width: 1000px; ">
									<b>Titolo dello studio clinico</b>
								</td>
								<td class="txtleft" style="border: 1px solid black; width: 1000px; ">
									${elStudio.getFieldDataString("IDstudio","TitoloProt")}
								</td>
							</tr>
							<tr>
								<td class="txtleft" style="border: 1px solid black; width: 1000px; ">
									<b>Numero Eudract</b> <em>(se applicabile)</em>
								</td>
								<td class="txtleft" style="border: 1px solid black; width: 1000px; ">
									${elStudio.getFieldDataString("datiStudio","eudractNumber")}
								</td>
							</tr>
							<tr>
								<td class="txtleft" style="border: 1px solid black; width: 1000px; ">
									<b>Fase dello studio <em>(se applicabile)</em></b>
								</td>
								<td class="txtleft" style="border: 1px solid black; width: 1000px; ">
									${fase}
								</td>
							</tr>
							<tr>
								<td class="txtleft" style="border: 1px solid black; width: 1000px; ">
									<b>Codice Protocollo</b>
								</td>
								<td class="txtleft" style="border: 1px solid black; width: 1000px; ">
									${elStudio.getFieldDataString("IDstudio","CodiceProt")}
								</td>
							</tr>
							<tr>
								<td class="txtleft" style="border: 1px solid black; width: 1000px; ">
									<b>Versione e data</b>
								</td>
								<td class="txtleft" style="border: 1px solid black; width: 1000px; ">
									v. ${versione}&nbsp;del&nbsp;${data_prot} 
								</td>
							</tr>
							<tr>
								<td class="txtleft" style="border: 1px solid black; width: 1000px; ">
									<b>Promotore</b>
								</td>
								<td class="txtleft" style="border: 1px solid black; width: 1000px; ">
								    <#if promotore?? >
								     ${ente_conduzione_studio}
								     </#if> 
								</td>
							</tr>
							<tr>
								<td class="txtleft" style="border: 1px solid black; width: 1000px; ">
									<b>CRO</b> <em>(se applicabile)</em>
								</td>
								<td class="txtleft" style="border: 1px solid black; width: 1000px; ">
								     <#if cro?? >
									   ${cro.getFieldDataString("DatiPromotoreCRO","denominazione")}
									</#if>
								</td>
							</tr>
							<tr>
								<td class="txtleft" style="border: 1px solid black; width: 1000px; ">
									<b>Sperimentatore Principale</b> <em>(indicare nominativo,struttura di appartenenza e contatti)</em>
								</td>
								<td class="txtleft" style="border: 1px solid black; width: 1000px; ">
									${el.getFieldDataDecode("IdCentro","PI")}<br/>
									${el.getFieldDataDecode("IdCentro","Struttura")}<br/>
									${el.getFieldDataDecode("IdCentro","UO")}<br/>
									${el.getFieldDataString("IdCentro","emailPI")}<br/>
									${el.getFieldDataString("IdCentro","telefonoPI")}<br/>
								</td>
							</tr>
							<tr>
								<td class="txtleft" style="border: 1px solid black; width: 1000px; ">
									<b>ELENCO STUDI IN CORSO PRESSO LA U.O.</b>
								</td>
								<td class="txtleft" style="padding:0;border: 1px solid black; width: 1000px; ">
									<table cellspacing="0" style="border-collapse: collapse;">
    									<tr>
    										<td class="txtleft" style="border: 1px solid black; width: 1000px; ">
    											<b>Titolo studio</b>
    										</td>
    										<td class="txtleft" style="border: 1px solid black; width: 1000px; ">
    											<b>N. soggetti totali da arruolare come target</b>
    										</td>
    									</tr>
    									<tr>
                                            <td class="txtleft" style="border: 1px solid black; width: 1000px; ">&nbsp;</td>
                                            <td class="txtleft" style="border: 1px solid black; width: 1000px; ">&nbsp;</td>
                                        </tr>
                                        <tr>
                                            <td class="txtleft" style="border: 1px solid black; width: 1000px; ">&nbsp;</td>
                                            <td class="txtleft" style="border: 1px solid black; width: 1000px; ">&nbsp;</td>
                                        </tr>
                                        <tr>
                                            <td class="txtleft" style="border: 1px solid black; width: 1000px; ">&nbsp;</td>
                                            <td class="txtleft" style="border: 1px solid black; width: 1000px; ">&nbsp;</td>
                                        </tr>
                                        <tr>
                                            <td class="txtleft" style="border: 1px solid black; width: 1000px; ">&nbsp;</td>
                                            <td class="txtleft" style="border: 1px solid black; width: 1000px; ">&nbsp;</td>
                                        </tr>
                                        <tr>
                                            <td class="txtleft" style="border: 1px solid black; width: 1000px; ">&nbsp;</td>
                                            <td class="txtleft" style="border: 1px solid black; width: 1000px; ">&nbsp;</td>
                                        </tr>
                                        <tr>
                                            <td class="txtleft" style="border: 1px solid black; width: 1000px; ">&nbsp;</td>
                                            <td class="txtleft" style="border: 1px solid black; width: 1000px; ">&nbsp;</td>
                                        </tr>
                                        <tr>
                                            <td class="txtleft" style="border: 1px solid black; width: 1000px; ">&nbsp;</td>
                                            <td class="txtleft" style="border: 1px solid black; width: 1000px; ">&nbsp;</td>
                                        </tr>
                                    </table>
								</td>
							</tr>
						</table>
						
						<br/><br/><br/>
						
						<table cellspacing="0" style="border-collapse: collapse;">
							<tr>
								<td style="width:50%; font-weight: bold; padding-left:10px;">SEZIONE A: MODULO PER L'ANALISI DEI COSTI CORRELATI ALLO STUDIO</td>
							</tr>
							<tr>
								<td style="width:50%; font-weight: bold; padding-left:10px;">SEZIONE B: MODULO RELATIVO AL COINVOLGIMENTO DEL PERSONALE </td>
							</tr>
							<tr>
								<td style="width:50%; font-weight: bold; padding-left:10px;">SEZIONE C: MODULO DI PREVISIONE DI IMPIEGO DEL FINANZIAMENTO ESTERNO </td>
							</tr>
							<tr>
								<td style="width:50%;text-align:justify; font-weight: bold; padding-left:10px;">SEZIONE D: ASSUNZIONE DI RESPONSABILIT&Agrave; E  NULLA OSTA AL RILASCIO DELLA FATTIBILIT&Agrave; LOCALE A CURA DELLO SPERIMENTATORE RESPONSABILE DELLO STUDIO , DEL DIRETTORE DELL'UNIT&Agrave; OPERATIVA E DEL DIRETTORE GENERALE DELLA STRUTTURA SANITARIA </td>
							</tr>
						</table>
						
						<div style="page-break-before: always">&nbsp;</div>
						
						<!--SEZIONE A-->
						<table>   
                            <tr>
                                <td class="txtcenter" style="padding-bottom: 10px; padding-top: 20px;">
                                    <b>SEZIONE A: MODULO PER L'ANALISI DEI COSTI CORRELATI ALLO STUDIO</b>
                                </td>
                            </tr>
                        </table>
						<table cellspacing="0" style="border-collapse: collapse;">
							<tr>
							    <td class="txtleft" style="width:50%;  padding:4px;"><b>Numero pazienti previsti per centro:</b><#if numeroPazienti?? && numeroPazienti?number gt 0>${numeroPazienti}<#else>&nbsp;${el.getFieldDataString("Feasibility","nrPazCentro")}</#if></td>
                                <td class="txtleft" style="width:50%;  padding:4px;">&nbsp;</td>
                            </tr>
							<tr>
								<td class="txtleft" style="width:50%;  padding:4px;">&nbsp;</td>
								<td class="txtleft" style="width:50%;  padding:4px;">
								    Volontari sani: &nbsp;<#if el.getFieldDataCode("Feasibility","volSani")?? && el.getFieldDataCode("Feasibility","volSani")=="1" >
								                          &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;SI&nbsp;${CheckedCheckbox}&nbsp;&nbsp;n.&nbsp;${el.getFieldDataString("Feasibility","volSaniNr")}
								                          <#else>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;NO&nbsp;${CheckedCheckbox}
								                          </#if><br/>
								    Pediatrici: &nbsp;<#if el.getFieldDataCode("Feasibility","pediatrici")?? && el.getFieldDataCode("Feasibility","pediatrici")=="1" >
                                                          &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;SI&nbsp;${CheckedCheckbox}&nbsp;&nbsp;n.&nbsp;${el.getFieldDataString("Feasibility","pediatriciNr")}
                                                          <#else>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;NO&nbsp;${CheckedCheckbox}
                                                          </#if><br/>
								    Adulti: &nbsp;<#if el.getFieldDataCode("Feasibility","adulti")?? && el.getFieldDataCode("Feasibility","adulti")=="1" >
                                                          &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;SI&nbsp;${CheckedCheckbox}&nbsp;&nbsp;n.&nbsp;${el.getFieldDataString("Feasibility","adultiNr")}
                                                          <#else>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;NO&nbsp;${CheckedCheckbox}
                                                          </#if><br/></td>
							</tr>
							<tr>
                                <td class="txtleft" style="width:50%;  padding:4px;"><b>Durata complessiva dello studio:</b>&nbsp;${elStudio.getFieldDataString("datiStudio","durataTot")}&nbsp;${elStudio.getFieldDataDecode("datiStudio","durataTotSelect")}</td>
                                <td class="txtleft" style="width:50%;  padding:4px;">&nbsp;</td>
                            </tr>
                            <tr>
                                <td class="txtleft" style="width:50%;  padding:4px;">
                                    <em>(Se applicabile dettagliare)</em><br/>
                                    &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<b>Durata del periodo di arruolamento:</b>&nbsp;${elStudio.getFieldDataString("datiStudio","durataArr")}&nbsp;${elStudio.getFieldDataDecode("datiStudio","durataArrSelect")}<br/>
                                    &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<b>Durata del trattamento:</b>&nbsp;${elStudio.getFieldDataString("datiStudio","durataTratt")}&nbsp;${elStudio.getFieldDataDecode("datiStudio","durataTrattSelect")}<br/>
                                    &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<b>Periodi previsto per Analisi dei dati:</b>&nbsp;${elStudio.getFieldDataString("datiStudio","analisiDati")}<br/>
                                    
                                </td>
                                <td class="txtleft" style="width:50%;  padding:4px;">&nbsp;</td>
                            </tr>
                            <tr>
                                <td class="txtleft" colspan="2" style="width:100%;  padding:4px;">
                                    <em>(Se applicabile)</em> <b>Corrispettivo a paziente proposto dal Promotore (Euro/paziente)+ IVA</b>&nbsp;<#if targetPaziente?? && targetPaziente!="0" >&euro;&nbsp;${targetPaziente?number?string("##0.00")}</#if>
                                </td>
                            </tr>
						</table>
						
						<br/>
						
						<table cellspacing="0" style="border-collapse: collapse;">
                            <tr>
                                <td class="txtleft" style="padding-bottom: 10px; padding-top: 20px;"><br/>
                                    <b>A.1 STRUTTURE/U.O. DEL CENTRO RICHIEDENTE COINVOLTE NELL'ESECUZIONE DELLO STUDIO </b><br/>
                                    <span style="text-align: justify">
                                    <em>Elencare, le strutture/U.O. coinvolte nel centro richiedente e le attivit&agrave; svolte nell'ambito del presente studio. <br/>
                                    Es. U.O. cardiologia per l'esecuzione di 2 ECG/paziente, U.O. radiologia per l'esecuzione di 1 TAC/paziente, laboratorio centralizzato per l'esecuzione di analisi ..., 1 biostatistico afferente a ... per l'analisi statistica, etc, 1 farmacista afferente a... per la Farmacovigilanza.</em>
                                    </span>
                                </td>
                            </tr>
                        </table>
                        <table cellspacing="0" style="border-collapse: collapse;">
                            <tr>
                                <td class="txtleft" style="border: 1px solid black; width: 1000px; ">
                                    <b>Struttura / U.O. coinvolta</b>
                                </td>
                                <td class="txtleft" style="border: 1px solid black; width: 1000px; ">
                                    <b>Attivit&agrave; svolta</b>
                                </td>
                                <td class="txtleft" style="border: 1px solid black; width: 1000px; ">
                                    <b>Data notifica al Responsabile della Struttura/U.O. coinvolta</b>
                                </td>
                            </tr>
                            <#if rowsFlowchart??>
                            <#list rowsFlowchart as currPrestazione>
                            <tr>
                                <td class="txtleft" style="border: 1px solid black; width: 1000px; ">
                                    &nbsp;${currPrestazione.getFieldDataString("Prestazioni","prestazione")}<#if currPrestazione.getFieldDataString("Prestazioni","prestazione")?length == 100>...</#if>
                                </td>
                                <td class="txtleft" style="border: 1px solid black; width: 1000px; ">
                                    &nbsp;${currPrestazione.getFieldDataString("Prestazioni","CDC")}
                                </td>
                                <td class="txtleft" style="border: 1px solid black; width: 1000px; ">
                                    &nbsp;<!--span style="color:red">TO DO </span-->
                                </td>
                            </tr>
                            </#list>
                            </#if>
                        </table>
						<br/>
						<table cellspacing="0" style="border-collapse: collapse;">
                            <tr>
                                <td class="txtleft" style="width:100%; font-weight: bold; padding:4px;">
                                    <b>STUDIO IN REGIME</b>
                                </td>
                            </tr>
                            <tr>
                                <td class="txtleft"  style="width:50%;padding:4px;">
                                    <ul>
                                        <li><span style="width:100px">Territoriale</span>
                                            <#if el.getFieldDataCode("Feasibility","regimeTerr")?? && el.getFieldDataCode("Feasibility","regimeTerr")=="1" >
                                            &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;SI&nbsp;${CheckedCheckbox}&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;NO&nbsp;${UncheckedCheckbox}
                                            <#else>
                                            &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;SI&nbsp;${UncheckedCheckbox}&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;NO&nbsp;${CheckedCheckbox}
                                            </#if>
                                        </li>
                                        <li>
                                            <span style="width:100px">Ospedaliero</span>
                                            <#if el.getFieldDataCode("Feasibility","regimeOsp")?? && el.getFieldDataCode("Feasibility","regimeOsp")=="1" >
                                            &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;SI&nbsp;${CheckedCheckbox}&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;NO&nbsp;${UncheckedCheckbox}
                                            <#else>
                                            &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;SI&nbsp;${UncheckedCheckbox}&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;NO&nbsp;${CheckedCheckbox}
                                            </#if>
                                        </li>
                                    </ul>
                                </td>
                            </tr>
                            <tr>
                                <td class="txtleft" style="width:100%; padding:4px;">
                                    Se in regime ospedaliero dettagliare:&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
                                    regime ambulatoriale&nbsp;
                                    <#if el.getFieldDataCode("Feasibility","regimeAmb")?? && el.getFieldDataCode("Feasibility","regimeAmb")=="1" >
                                        ${CheckedCheckbox}
                                    <#else>
                                    ${UncheckedCheckbox}
                                    </#if>    
                                    &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
                                    day-hospital/surgery&nbsp;
                                    <#if el.getFieldDataCode("Feasibility","regimeDHS")?? && el.getFieldDataCode("Feasibility","regimeDHS")=="1" >
                                        ${CheckedCheckbox}
                                    <#else>
                                    ${UncheckedCheckbox}
                                    </#if>
                                    &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
                                    ricovero&nbsp;
                                    <#if el.getFieldDataCode("Feasibility","regimeRicovero")?? && el.getFieldDataCode("Feasibility","regimeRicovero")=="1" >
                                        ${CheckedCheckbox}
                                    <#else>
                                    ${UncheckedCheckbox}
                                    </#if>
                                </td>
                            </tr>
                        </table>
                        <div style="page-break-before:always">&nbsp;</div>
                        <table cellspacing="0" style="border-collapse: collapse;">
                            <tr>
                                <td class="txtleft" style="padding-bottom: 10px; padding-top: 20px;"><br/>
                                    <b>A.2a PRESTAZIONI ROUTINARIE PREVISTE NELLO STUDIO CLINICO</b><br/>
                                    <span style="text-align: justify">
                                    <em>Elencare di seguito ed indicare per ognuna di esse la quantit&agrave;, la corrispondente tariffa come da Nomenclatore Regionale nonch&eacute; le modalit&agrave; proposte per la copertura del relativo costo delle prestazioni routinarie comprese nella normale pratica clinica previste dallo studio.</em>
                                    </span>
                                </td>
                            </tr>
                        </table>
                        <table cellspacing="0" style="border-collapse: collapse;">
                            <tr style="background-color:#eee;">
                                <th class="txtcenter" style="border: 1px solid black; width: 1000px; ">
                                    <b>Codice tariffario e descrizione della prestazione </b>
                                </th>
                                <th class="txtcenter" style="border: 1px solid black; width: 1000px; ">
                                    <b>Quantit&agrave;/paziente</b>
                                </th>
                                <th class="txtcenter" style="border: 1px solid black; width: 1000px; ">
                                    <b>Totale prestazioni previste</b>
                                </th>
                                <th class="txtcenter" style="border: 1px solid black; width: 1000px; ">
                                    <b>Tariffa</b><br/>
                                    (Nomenclatore Regionale)
                                </th>
                                <th class="txtcenter" style="border: 1px solid black; width: 1000px; ">
                                    <b>Totale valore + IVA</b><br/>(Euro)
                                </th>
                                
                            </tr>
                            <#if prestazioniRoutine??>
                                <#list prestazioniRoutine as currPrestazione >
                                <tr>
                                    <td class="txtleft" style="border: 1px solid black; width: 1000px; ">
                                       &nbsp;${currPrestazione.getFieldDataString("Prestazioni","prestazione")}<#if currPrestazione.getFieldDataString("Prestazioni","prestazione")?length == 100>...</#if>
                                    </td>
                                    <td class="txtleft" style="border: 1px solid black; width: 1000px; ">
                                        &nbsp;${currPrestazione.getFieldDataString("InfoBudgetPDF","NumSSNRoutine")}
                                    </td>
                                    <td class="txtleft" style="border: 1px solid black; width: 1000px; ">
                                        <#assign per_paziente= currPrestazione.getFieldDataString("InfoBudgetPDF","NumSSNRoutine")?number * numeroPazienti/>
                                       &nbsp;${per_paziente}
                                    </td>
                                    <td class="txtright" style="border: 1px solid black; width: 1000px; font-family: monospace;">
                                        &euro;&nbsp;${currPrestazione.getFieldDataString("Tariffario","SSN")?replace(',','.')?number?string("##0.00")}
                                    </td>
                                    <td class="txtright" style="border: 1px solid black; width: 1000px; font-family: monospace;">
                                        <#assign tariffa= per_paziente?number * currPrestazione.getFieldDataString("Tariffario","SSN")?replace(',','.')?number />
                                        <#assign totaleRoutine= totaleRoutine + tariffa />
                                        &euro;&nbsp;${tariffa?string("##0.00")}
                                    </td>
                                </tr>
                                </#list>
                            <#else>
                                <tr>
                                    <td class="txtleft" style="border: 1px solid black; width: 1000px; ">
                                       &nbsp;
                                    </td>
                                    <td class="txtleft" style="border: 1px solid black; width: 1000px; ">
                                        &nbsp;
                                    </td>
                                    <td class="txtleft" style="border: 1px solid black; width: 1000px; ">
                                       &nbsp;
                                    </td>
                                    <td class="txtright" style="border: 1px solid black; width: 1000px; font-family: monospace;">
                                        &nbsp;
                                    </td>
                                    <td class="txtright" style="border: 1px solid black; width: 1000px; font-family: monospace;">
                                        &nbsp;
                                    </td>
                                </tr>
                            </#if>
                            
                            <tr>
                                <td class="txtleft" colspan="4" style="border: 1px solid black; width: 1000px; ">
                                    <b><em>TOTALE</em></b>
                                </td>
                                <td class="txtright" colspan="1" style="border: 1px solid black; width: 1000px; background-color:#eee;font-family: monospace;">
                                    <b><#if totaleRoutine?? >&euro;&nbsp;${totaleRoutine?string("##0.00")}</#if></b>
                                </td>
                            </tr>
                        </table>
                        <div style="page-break-before:always">&nbsp;</div>
                        <table cellspacing="0" style="border-collapse: collapse;">
                            <tr>
                                <td class="txtleft" style="padding-bottom: 10px; padding-top: 20px;"><br/>
                                    <b>A.2b PRESTAZIONI AGGIUNTIVE PREVISTE NELLO STUDIO CLINICO</b><br/>
                                    <span style="text-align: justify">
                                    <em>Elencare di seguito ed indicare per ognuna di esse la quantit&agrave;, la corrispondente tariffa come da Nomenclatore Regionale nonch&eacute; le modalit&agrave; proposte per la copertura del relativo costo delle prestazioni aggiuntive rispetto alla normale pratica clinica previste dallo studio.</em>
                                    </span>
                                </td>
                            </tr>
                        </table>
                        <table cellspacing="0" style="border-collapse: collapse;">
                            <tr style="background-color:#eee;">
                                <th class="txtcenter" style="border: 1px solid black; width: 1000px; ">
                                    <b>Codice tariffario e descrizione della prestazione </b>
                                </th>
                                <th class="txtcenter" style="border: 1px solid black; width: 1000px; ">
                                    <b>Quantit&agrave;/paziente</b>
                                </th>
                                <th class="txtcenter" style="border: 1px solid black; width: 1000px; ">
                                    <b>Totale prestazioni previste</b>
                                </th>
                                <th class="txtcenter" style="border: 1px solid black; width: 1000px; ">
                                    <b>Tariffa</b><br/>
                                    (Nomenclatore Regionale)
                                </th>
                                <th class="txtcenter" style="border: 1px solid black; width: 1000px; ">
                                    <b>Totale valore + IVA</b><br/>(Euro)
                                </th>
                                <th class="txtcenter" style="border: 1px solid black; width: 1000px; ">
                                    <b>Copertura oneri finanziari</b><br/>(A, B, C, D)
                                </th>
                            </tr>
                            <#if prestazioniExtraRoutine??>
                                <#list prestazioniExtraRoutine as currPrestazione >
                                   <#list coperture as currCopertura > 
                                        <#assign conteggioCorrente=currPrestazione.getFieldDataString("InfoBudgetPDF",currCopertura) />
                                        <#if conteggioCorrente?? && conteggioCorrente!="0" && conteggioCorrente!="" >
                                            <tr>
                                                <td class="txtleft" style="border: 1px solid black; width: 1000px; ">
                                                   &nbsp;${currPrestazione.getFieldDataString("Prestazioni","prestazione")}<#if currPrestazione.getFieldDataString("Prestazioni","prestazione")?length == 100>...</#if>
                                                </td>
                                                <td class="txtleft" style="border: 1px solid black; width: 1000px; ">
                                                    &nbsp;${conteggioCorrente}
                                                </td>
                                                <td class="txtleft" style="border: 1px solid black; width: 1000px; ">
                                                    <#assign per_paziente= conteggioCorrente?number * numeroPazienti/>
                                                   &nbsp;${per_paziente}
                                                </td>
                                                <td class="txtright" style="border: 1px solid black; width: 1000px;font-family: monospace; ">
                                                    &euro;&nbsp;${currPrestazione.getFieldDataString("Tariffario","SSN")?replace(',','.')?number?string("##0.00")}
                                                </td>
                                                <td class="txtright" style="border: 1px solid black; width: 1000px;font-family: monospace; ">
                                                    <#assign tariffa= per_paziente?number * currPrestazione.getFieldDataString("Tariffario","SSN")?replace(',','.')?number  />
                                                    <#assign totaleExtraRoutine= totaleExtraRoutine + tariffa />
                                                    &euro;&nbsp;${tariffa?string("##0.00")}
                                                </td>
                                                <td class="txtright" style="border: 1px solid black; width: 1000px; ">
                                                    &nbsp;${currCopertura?replace("NumExtraRoutine","")}
                                                </td>
                                            </tr>
                                        </#if>
                                    </#list>
                                </#list>
                            <#else>
                                <tr>
                                    <td class="txtleft" style="border: 1px solid black; width: 1000px; ">
                                       &nbsp;
                                    </td>
                                    <td class="txtleft" style="border: 1px solid black; width: 1000px; ">
                                        &nbsp;
                                    </td>
                                    <td class="txtleft" style="border: 1px solid black; width: 1000px; ">
                                       &nbsp;
                                    </td>
                                    <td class="txtright" style="border: 1px solid black; width: 1000px;font-family: monospace; ">
                                        &nbsp;
                                    </td>
                                    <td class="txtright" style="border: 1px solid black; width: 1000px;font-family: monospace; ">
                                        &nbsp;
                                    </td>
                                    <td class="txtright" style="border: 1px solid black; width: 1000px; ">
                                        &nbsp;
                                    </td>
                                </tr>
                            </#if>
                            
                            <#if prestazioni??>
                                <#list prestazioni as currPrestazione >
                                        <tr>
                                            <td class="txtleft" style="border: 1px solid black; width: 1000px; ">
                                               &nbsp;${currPrestazione.getFieldDataString("Base","Nome")}<#if currPrestazione.getFieldDataString("Base","Nome")?length == 100>...</#if>
                                            </td>
                                            <td class="txtleft" style="border: 1px solid black; width: 1000px; ">
                                               &nbsp;${currPrestazione.getFieldDataString("Costo","Quantita")}
                                            </td>
                                            <td class="txtleft" style="border: 1px solid black; width: 1000px; ">
                                               <#assign prestazioneTotale= currPrestazione.getFieldDataString("Costo","Quantita")?number * numeroPazienti/>
                                               &nbsp;${prestazioneTotale}
                                            </td>
                                            <td class="txtright" style="border: 1px solid black; width: 1000px; font-family: monospace;">
                                                <#assign costoUnitario=0 />
                                                <#if currPrestazione.getFieldDataString("Tariffario","SSN")?? &&  currPrestazione.getFieldDataString("Tariffario","SSN") != "" >
                                                    <#assign costoUnitario=currPrestazione.getFieldDataString("Tariffario","SSN")?replace(",",".")?number />
                                                </#if>
                                               &euro;&nbsp;${costoUnitario?string("##0.00")}
                                            </td>
                                            <td class="txtright" style="border: 1px solid black; width: 1000px; font-family: monospace;">
                                                <#assign costoTotale=prestazioneTotale*costoUnitario/>
                                                <#assign totaleExtraRoutine=totaleExtraRoutine + costoTotale />
                                               &nbsp;${costoTotale?string("##0.00")}
                                            </td>
                                            <td class="txtright" style="border: 1px solid black; width: 1000px; ">
                                               &nbsp;${currPrestazione.getFieldDataDecode("Costo","Copertura")?string[0..0]}
                                            </td>
                                        </tr>
                                </#list>
                            <#else>
                                <tr>
                                    <td class="txtleft" style="border: 1px solid black; width: 1000px; ">
                                       &nbsp;
                                    </td>
                                    <td class="txtleft" style="border: 1px solid black; width: 1000px; ">
                                        &nbsp;
                                    </td>
                                    <td class="txtleft" style="border: 1px solid black; width: 1000px; ">
                                       &nbsp;
                                    </td>
                                    <td class="txtright" style="border: 1px solid black; width: 1000px;font-family: monospace; ">
                                        &nbsp;
                                    </td>
                                    <td class="txtright" style="border: 1px solid black; width: 1000px;font-family: monospace; ">
                                        &nbsp;
                                    </td>
                                    <td class="txtright" style="border: 1px solid black; width: 1000px; ">
                                        &nbsp;
                                    </td>
                                </tr>
                            </#if>
                            
                            
                            <tr>
                                <td class="txtleft" colspan="4" style="border: 1px solid black; width: 1000px; ">
                                    <b><em>TOTALE</em></b>
                                </td>
                                <td class="txtright" colspan="1" style="border: 1px solid black; width: 1000px; background-color:#eee;font-family: monospace;">
                                    <b><#if totaleExtraRoutine??>&euro;&nbsp;${totaleExtraRoutine?string("##0.00")}</#if></b>
                                </td>
                            </tr>
                        </table>
                        <br/>
                        <#assign visiteTable>
                        <table cellspacing="0" style="border-collapse: collapse;">
                            <tr style="background-color:#eee;">
                                <th class="txtcenter" style="border: 1px solid black; width: 1000px; ">
                                    <b>Visita</b>
                                </th>
                                <th class="txtcenter" style="border: 1px solid black; width: 1000px; ">
                                    <b>Compenso/paziente</b>
                                </th>
                            </tr>
                            <#if colsFlowchart??>
                                <#list colsFlowchart as currTimePoint>
                                    <tr>
                                        <td class="txtleft" style="border: 1px solid black; width: 1000px; ">
                                            Visita ${currTimePoint.getFieldDataString("TimePoint","NumeroVisita")}
                                        </td>
                                        <td class="txtright" style="border: 1px solid black; width: 1000px;font-family:monospace; ">
                                            <#if currTimePoint.getFieldDataString("InfoBudgetPDF","TotPrezzoExtraRoutine")!=''>
						<#assign totaleVisite=totaleVisite + currTimePoint.getFieldDataString("InfoBudgetPDF","TotPrezzoExtraRoutine")?number />
					    &euro;&nbsp;${currTimePoint.getFieldDataString("InfoBudgetPDF","TotPrezzoExtraRoutine")?number?string("##0.00")} + iva
					    <#else>
						<#assign totaleVisite=totaleVisite/>
					    </#if> 
                                        </td>
                                    </tr>
                                </#list>
                            <#else>
                                <tr>
                                    <td class="txtleft" style="border: 1px solid black; width: 1000px; ">
                                        &nbsp;
                                    </td>
                                    <td class="txtright" style="border: 1px solid black; width: 1000px;font-family:monospace; ">
                                        &nbsp;
                                    </td>
                                </tr>
                            </#if>
                            <tr>
                                <td class="txtleft" style="border: 1px solid black; width: 1000px; ">
                                    <b>TOTALE</b>
                                </td>
                                <td class="txtright" colspan="1" style="border: 1px solid black; width: 1000px;font-family:monospace;">
                                    <b><#if totaleVisite??>&euro; ${totaleVisite?number?string("##0.00")} + iva</#if></b>
                                </td>
                            </tr>
                        </table>
                        </#assign>
                        <table cellspacing="0" style="border-collapse: collapse;">
                            <tr>
                                <td class="txtleft" style="padding-bottom: 10px; border: 1px solid black;width: 2000px;">
                                    <b>A</b> = fondi della struttura sanitaria a disposizione dello Sperimentatore/Promotore (es. fondi di ricerca)<br/>
                                    <b>B</b> = finanziamento proveniente da terzi (<em>in tal caso si richiede una dichiarazione di disponibilit&agrave; a sostenere i costi connessi allo studio da parte del finanziatore</em>), da dettagliare nella Sezione B<br/>
                                    <b>C</b> = il costo di tali prestazioni si propone in carico al fondo aziendale non alimentato dal SSN, in dotazione all'Azienda Sanitaria (<em>come previsto dal D.M. 17/12/2004</em>)<br/>
                                    <b>D</b> = a carico del Promotore Profit (es. azienda farmaceutica o altri enti a fini di lucro)
                                </td>
                            </tr>
                            <tr>
                                <td class="txtleft" style="padding-bottom: 10px;"><br/>
                                    <em>
                                        <u>Si ricorda che:<br/></u>
                                        1. i medicinali sperimentali ed eventualmente i dispositivi in studio pre market sono forniti gratuitamente dal promotore della sperimentazione; nessun costo aggiuntivo, per la conduzione e la gestione delle sperimentazioni deve gravare sulla finanza pubblica (D.Lgs. 211/2003, art. 20).<br/>
                                        2. le spese aggiuntive, comprese quelle per il farmaco sperimentale, necessarie per le sperimentazioni cliniche, qualora non coperte da fondi di ricerca ad hoc possono gravare sul fondo costituito per le sperimentazioni dalla struttura sanitaria no-profit (D.M. 17/12/2004, art. 2).<br/> 
                                        3. per gli esami Radiodiagnostici si applicano le tariffe deliberate in base all'analisi dei costi per i diversi  fattori produttivi  (Allegato SE - Tariffe Radiologia)
                                    </em>
                                </td>
                            </tr>
                        </table>
                       <div style="page-break-before:always">&nbsp;</div>
                       <table cellspacing="0" style="border-collapse: collapse;">
                            <tr>
                                <td class="txtleft" style="width:100%; font-weight: bold; padding:4px;width:100%;">
                                    <em>(Se applicabile)</em> <b>Compenso a paziente completato:<#if totaleVisite??> &euro;${totaleVisite?number?string("##0.00")}+ iva</#if></b>
                                </td>
                            </tr>
                        </table>
                        ${visiteTable}
                        <div style="page-break-before:always">&nbsp;</div>
                        <table cellspacing="0" style="border-collapse: collapse;">
                            <tr>
                                <td class="txtleft" style="padding-bottom: 10px; padding-top: 20px;"><br/>
                                    <b>A.3 MATERIALI DI CONSUMO, ATTREZZATURE, SERVIZI E SPESE PER IL PERSONALE NECESSARI PER LO SVOLGIMENTO DELLO STUDIO</b><br/>
                                    <span style="text-align: justify">
                                    <em>Elencare ed indicare la quantit&agrave; e le modalit&agrave; proposte per la copertura del costo dei materiali/attrezzature/servizi studio-specifici, <b>non rientranti nel costo delle prestazioni</b>, come da codici indicati di seguito:</em>
                                    </span>
                                </td>
                            </tr>
                        </table>
                        <table cellspacing="0" style="border-collapse: collapse;">
                            <tr style="background-color:#eee;">
                                <th class="txtcenter" colspan="2" style="border: 1px solid black; width: 1000px; ">
                                    <b>Tipologia</b><br/><em>(1=materiale di consumo; 2=attrezzature; 3=servizi*; 4=personale**; 5=altro***)</em>
                                </th>
                                <th class="txtcenter" style="border: 1px solid black; width: 1000px; ">
                                    <b>Quantit&agrave;</b>
                                </th>
                                <th class="txtcenter" style="border: 1px solid black; width: 1000px; ">
                                    <b>Totale valore + IVA</b><br/>(Euro)
                                </th>
                                <th class="txtcenter" style="border: 1px solid black; width: 1000px; ">
                                    <b>Copertura oneri finanziari</b><br/>(A, B, C, D)
                                </th>
                            </tr>
                            <tr>
                                <td class="txtcenter" style="border: 1px solid black; width: 1000px; ">
                                    <b>CODICE</b>
                                </td>
                                <td class="txtcenter" style="border: 1px solid black; width: 1000px; ">
                                    <b>Descrizione</b>
                                </td>
                                <td class="txtright" style="border: 1px solid black; width: 1000px; ">
                                    &nbsp;
                                </td>
                                <td class="txtright" style="border: 1px solid black; width: 1000px; ">
                                    &nbsp;
                                </td>
                                <td class="txtright" style="border: 1px solid black; width: 1000px; ">
                                    &nbsp;
                                </td>
                            </tr>
                            <#if costiAggiuntivi??>
                                <#list costiAggiuntivi as currCosto>
                                    <tr>
                                        <td class="txtright" style="border: 1px solid black; width: 1000px; ">
                                        &nbsp;${currCosto.getFieldDataCode("CostoAggiuntivo","Tipologia")}
                                        </td>
                                        <td class="txtright" style="border: 1px solid black; width: 1000px; ">
                                            &nbsp;${currCosto.getFieldDataString("CostoAggiuntivo","OggettoPrincipale")}
                                        </td>
                                        <td class="txtright" style="border: 1px solid black; width: 1000px; ">
                                            &nbsp;${currCosto.getFieldDataString("CostoAggiuntivo","Quantita")}
                                        </td>
                                        <td class="txtright" style="border: 1px solid black; width: 1000px;font-family:monospace; ">
                                            <#assign currTotale=currCosto.getFieldDataString("CostoAggiuntivo","Quantita")?number * currCosto.getFieldDataString("CostoAggiuntivo","Costo")?number />
                                            <#assign totaleCostiAggiuntivi= totaleCostiAggiuntivi + currTotale />
                                            &nbsp;${currTotale?string("##0.00")}
                                        </td>
                                        <td class="txtright" style="border: 1px solid black; width: 1000px; ">
                                            &nbsp;${currCosto.getFieldDataDecode("CostoAggiuntivo","Copertura")?string[0..0]}
                                        </td>
                                    </tr>
                                </#list>
                            <#else>
                            </#if>
                            <tr>
                                <td class="txtright" colspan="3" style="border: 1px solid black; width: 1000px; ">
                                    <b><em>Totale</em></b>
                                </td>
                                <td class="txtright" style="border: 1px solid black; width: 1000px;font-family:monospace;background-color:#eee;">
                                    <b><em><#if totaleCostiAggiuntivi??>&nbsp;${totaleCostiAggiuntivi?string("##0.00")}</#if></em></b>
                                </td>
                                <td class="txtright" style="border: 1px solid black; width: 1000px; ">
                                    &nbsp;
                                </td>
                            </tr>
                        </table>
                        <br/>
                        <table cellspacing="0" style="border-collapse: collapse;">
                            <tr>
                                <td class="txtleft" style="padding-bottom: 10px;"><br/>
                                    <em>
                                        *   Nella voce servizi devono essere inseriti e quantificati (stima) anche l'organizzazione o la partecipazione a convegni, corsi di formazione o altre iniziative formative.<br/>
                                        **  Nella voce personale specificare descrivendo distintamente i costi relativi alle spese per il personale dipendente, quello non dipendente in forza allo studio mediante convenzioni o contratti o distacchi da altre pubbliche amministrazioni, per l'attivazione di borse di studio.<br />
                                        *** Per altro si intende tutto ci&ograve; che non pu&ograve; essere ricompreso nelle specifiche precedenti, come somministrazione di questionari, interviste, diari, scale di valutazione etc.<br />
                                    </em>
                                </td>
                            </tr>
                            <tr>
                                <td class="txtleft" style="padding-bottom: 10px; border: 1px solid black;">
                                    <b>A</b> = fondi della struttura sanitaria a disposizione dello Sperimentatore/Promotore (es. fondi di ricerca)<br/>
                                    <b>B</b> = finanziamento proveniente da terzi (<em>in tal caso si richiede una dichiarazione di disponibilit&agrave; a sostenere i costi connessi allo studio da parte del finanziatore</em>), da dettagliare nella Sezione B<br/>
                                    <b>C</b> = il costo di tali prestazioni si propone in carico al fondo aziendale non alimentato dal SSN, in dotazione all'Azienda Sanitaria (<em>come previsto dal D.M. 17/12/2004</em>)<br/>
                                    <b>D</b> = a carico del Promotore Profit (es. azienda farmaceutica o altri enti a fini di lucro)
                                </td>
                            </tr>
                        </table>
						<div style="page-break-before:always">&nbsp;</div>
						<table cellspacing="0" style="border-collapse: collapse;">
                            <tr>
                                <td class="txtleft" style="padding-bottom: 10px; padding-top: 20px;"><br/>
                                    <b>A.4 NEL CASO DI STUDI INTERVENTISTICI FARMACOLOGICI</b><br/>
                                    <span style="text-align: justify">
                                    <em>specifiche del DM n. 51 del 21.12.2007</em>
                                    </span>
                                </td>
                            </tr>
                        </table>
                        <table cellspacing="0" style="border-collapse: collapse;">
                            <tr style="background-color:#eee;">
                                <th class="txtcenter" rowspan="2" style="border: 1px solid black; width: 1000px; ">
                                    <b>Investigational medicinal product (IMP)</b>
                                </th>
                                <th class="txtcenter" colspan="2" style="border: 1px solid black; width: 1000px; ">
                                    <b>Non Investigational medicinal product (NIMP)</b>
                                </th>
                            </tr>
                            <tr style="background-color:#eee;">
                                <th class="txtcenter" style="border: 1px solid black; width: 1000px; ">
                                    <b>Regardless Trial NIMP (ReTNIMP)</b><br/>
                                </th>
                                <th class="txtcenter" style="border: 1px solid black; width: 1000px; ">
                                    <b>Products equivalent to the IMP (PeIMP)</b>
                                </th>
                            </tr>
                            <tr>
                                <td class="txtleft" style="border: 1px solid black; width: 1000px;">
                                    Farmaco in studio e farmaco di confronto, compreso placebo
                                </td>
                                <td class="txtleft" style="border: 1px solid black; width: 1000px;">
                                    <ul>
                                        <li>Farmaco non oggetto di  sperimentazione, con AIC in Italia, somministrato indipendentemente dalla partecipazione alla sperimentazione (terapie di background, terapie concomitanti, etc)</li>
                                        <li>Farmaco non oggetto di sperimentazione, con AIC in Italia, previsto dal protocollo per il trattamento dei casi di inefficacia dell'IMP (terapie di supporto)</li>
                                    </ul>
                                </td>
                                <td class="txtleft" style="border: 1px solid black; width: 1000px;">
                                    Farmaco non oggetto della sperimentazione  ma previsto dal protocollo che si pu&ograve; configurare come:
                                    <ol style="list-style-type: lower-alpha;">
                                        <li>farmaco con AIC in Italia, usato secondo le condizioni autorizzative dell'AIC, obbligatoriamente previsto dal protocollo come trattamento necessario per la corretta realizzazione della sperimentazione (es. prodotti impiegati per valutare l'end-point in una sperimentazione) inclusi gli eventuali trattamenti necessari per prevenire e curare reazioni connesse con l'IMP;</li>
                                        <li>Farmaco con AIC in Italia ma utilizzato al di fuori delle condizioni autorizzative;</li>
                                        <li>Farmaco senza AIC in Italia ma con AIC in un altro paese anche se utilizzato al fuori delle condizioni autorizzative</li>
                                        <li>Sostanze utilizzate per produrre reazioni fisiologiche necessarie alla realizzazione della sperimentazione e che possono anche essere senza AIC, purch&egrave; in uso consolidato nella prassi clinica.</li>
                                    </ol>
                                </td>
                            </tr>
                            <tr>
                                <td class="txtleft" style="border: 0px 1px 1px 1px solid black;width: 1000px;">
                                    <b>ONERI A CARICO DEL PROMOTORE</b>
                                </td>
                                <td class="txtleft" style="border: 0px 1px 1px 1px solid black;width: 1000px;">
                                    <b>ONERI A CARICO DEL SSN</b>
                                </td>
                                <td class="txtleft" style="border: 0px 1px 1px 1px solid black;width: 1000px;">
                                    <b>ONERI A CARICO DEL PROMOTORE</b>
                                </td>
                            </tr>
                        </table>
                        <br/>
                        <table cellspacing="0" style="border-collapse: collapse;">
                            <tr>
                                <td class="txtleft" style="padding-bottom: 10px; padding-top: 20px;"><br/>
                                    <b>A.4.1 DETTAGLIO FARMACI O DISPOSITIVI MEDICI SPERIMENTALI</b> (<em>in studio, di confronto, compreso placebo</em>)<br/>
                                </td>
                            </tr>
                        </table>
                        <br/>
                        <table cellspacing="0" style="border-collapse: collapse;">
                            <tr style="background-color:#eee;">
                                <th class="txtcenter"  style="border: 1px solid black; width: 1000px; ">
                                    <b>Descrizione</b><br/><em>(Indicare dosaggio e forma farmaceutica del farmaco/dettagli del dispositivo)</em>
                                </th>
                                <th class="txtcenter" style="border: 1px solid black; width: 1000px; ">
                                    <b>Costo compreso nel costo della prestazione</b><br/>(Si/No/n.a.)
                                </th>
                                <th class="txtcenter" style="border: 1px solid black; width: 1000px; ">
                                    <b>Unit&agrave; di misura</b>
                                </th>
                                <th class="txtcenter" style="border: 1px solid black; width: 1000px; ">
                                    <b>Numero unit&agrave; a paziente</b><br/><em>(stima)</em>
                                </th>
                                <th class="txtcenter" style="border: 1px solid black; width: 1000px; ">
                                    <b>Totale valore se quantificabile</b><br/>(Euro)
                                </th>
                                
                            </tr>
                            <#if farmaci_disp_cat1_list??>
                            <#list farmaci_disp_cat1_list as currFarmaco >
                            <tr>
                                <td class="txtleft" style="border: 1px solid black; width: 1000px; ">
                                   &nbsp;${currFarmaco.getFieldDataDecode("Farmaco","princAtt")}${currFarmaco.getFieldDataDecode("Farmaco","dispMed")}&nbsp;-&nbsp;${currFarmaco.getFieldDataString("Farmaco","descrizione")}
                                </td>
                                <td class="txtleft" style="border: 1px solid black; width: 1000px; ">
                                    &nbsp;${currFarmaco.getFieldDataDecode("Farmaco","costo")}
                                </td>
                                <td class="txtleft" style="border: 1px solid black; width: 1000px; ">
                                   &nbsp;${currFarmaco.getFieldDataString("Farmaco","unitaMisura")}
                                </td>
                                <td class="txtleft" style="border: 1px solid black; width: 1000px; ">
                                    &nbsp;${currFarmaco.getFieldDataString("Farmaco","numUnitaPaz")}
                                </td>
                                <td class="txtright" style="border: 1px solid black; width: 1000px; font-family:monospace;">
                                    <#if currFarmaco.getFieldDataString("Farmaco","totaleValore")?? && currFarmaco.getFieldDataString("Farmaco","totaleValore")!= "">
                                        &nbsp;${currFarmaco.getFieldDataString("Farmaco","totaleValore")?number?string("##0.00")}
                                    </#if>
                                </td>
                            </tr>
                            </#list>
                            <#else>
                            <tr>
                                <td class="txtleft" style="border: 1px solid black; width: 1000px; ">
                                   &nbsp;
                                </td>
                                <td class="txtleft" style="border: 1px solid black; width: 1000px; ">
                                    &nbsp;
                                </td>
                                <td class="txtleft" style="border: 1px solid black; width: 1000px; ">
                                   &nbsp;
                                </td>
                                <td class="txtleft" style="border: 1px solid black; width: 1000px; ">
                                    &nbsp;
                                </td>
                                <td class="txtright" style="border: 1px solid black; width: 1000px; font-family:monospace;">
                                    &nbsp;
                                </td>
                            </tr>
                            </#if>
                            <tr>
                                <td class="txtleft" colspan="4" style="border: 1px solid black; width: 1000px; ">
                                    <b><em>Totale</em></b>
                                </td>
                                <td class="txtright" colspan="1" style="border: 1px solid black; width: 1000px; background-color:#eee;font-family:monospace;">
                                    <b><em><#if costo_cat1?? >&nbsp;${costo_cat1?string("##0.00")}</#if></em></b>
                                </td>

                            </tr>
                        </table>
                        <div style="page-break-before:always">&nbsp;</div>
                        <table cellspacing="0" style="border-collapse: collapse;">
                            <tr>
                                <td class="txtleft" style="padding-bottom: 10px; padding-top: 20px;"><br/>
                                    <b>A.4.2 DETTAGLIO FARMACI O DISPOSTIVI MEDICI NON OGGETTO DI SPERIMENTAZIONE </b> (<em>previsti  dal protocollo ma non dalla pratica clinica: PeIMP</em>)<br/>
                                </td>
                            </tr>
                        </table>
                        <br/>
                        <table cellspacing="0" style="border-collapse: collapse;">
                            <tr style="background-color:#eee;">
                                <th class="txtcenter"  style="border: 1px solid black; width: 1000px; ">
                                    <b>Descrizione</b><br/><em>(Indicare dosaggio e forma farmaceutica del farmaco/dettagli del dispositivo)</em>
                                </th>
                                <th class="txtcenter" style="border: 1px solid black; width: 1000px; ">
                                    <b>Costo compreso nel costo della prestazione</b><br/>(Si/No/n.a.)
                                </th>
                                <th class="txtcenter" style="border: 1px solid black; width: 1000px; ">
                                    <b>Unit&agrave; di misura</b>
                                </th>
                                <th class="txtcenter" style="border: 1px solid black; width: 1000px; ">
                                    <b>Numero unit&agrave; a paziente</b><br/><em>(stima)</em>
                                </th>
                                <th class="txtcenter" style="border: 1px solid black; width: 1000px; ">
                                    <b>Totale valore se quantificabile</b><br/>(Euro)
                                </th>
                                
                            </tr>
                            <#list farmaci_disp_cat2_list as currFarmaco >
                            <tr>
                                <td class="txtleft" style="border: 1px solid black; width: 1000px; ">
                                   &nbsp;${currFarmaco.getFieldDataDecode("Farmaco","princAtt")}${currFarmaco.getFieldDataDecode("Farmaco","dispMed")}&nbsp;-&nbsp;${currFarmaco.getFieldDataString("Farmaco","descrizione")}
                                </td>
                                <td class="txtleft" style="border: 1px solid black; width: 1000px; ">
                                    &nbsp;${currFarmaco.getFieldDataDecode("Farmaco","costo")}
                                </td>
                                <td class="txtleft" style="border: 1px solid black; width: 1000px; ">
                                   &nbsp;${currFarmaco.getFieldDataString("Farmaco","unitaMisura")}
                                </td>
                                <td class="txtleft" style="border: 1px solid black; width: 1000px; ">
                                    &nbsp;${currFarmaco.getFieldDataString("Farmaco","numUnitaPaz")}
                                </td>
                                <td class="txtright" style="border: 1px solid black; width: 1000px;font-family:monospace; ">
                                    <#if currFarmaco.getFieldDataString("Farmaco","totaleValore")?? && currFarmaco.getFieldDataString("Farmaco","totaleValore")!="" >
                                        &nbsp;${currFarmaco.getFieldDataString("Farmaco","totaleValore")?number?string("##0.00")}
                                    </#if>
                                </td>
                            </tr>
                            </#list>
                            <tr>
                                <td class="txtleft" colspan="4" style="border: 1px solid black; width: 1000px; ">
                                    <b><em>Totale</em></b>
                                </td>
                                <td class="txtright" colspan="1" style="border: 1px solid black; width: 1000px;font-family:monospace; background-color:#eee;">
                                    <b><em>&nbsp;${costo_cat2?string("##0.00")}</em></b>
                                </td>

                            </tr>
                        </table>
                        <div style="page-break-before:always">&nbsp;</div>
                        <table cellspacing="0" style="border-collapse: collapse;">
                            <tr>
                                <td class="txtleft" style="padding-bottom: 10px; padding-top: 20px;"><br/>
                                    <b>A.4.3 DETTAGLIO FARMACI O DISPOSITIVI MEDICI NON OGGETTO DI SPERIMENTAZIONE</b> (<em>previsti dal protocollo e dalla pratica clinica: ReTNIMP</em>)<br/>
                                </td>
                            </tr>
                        </table>
                        <br/>
                        <table cellspacing="0" style="border-collapse: collapse;">
                            <tr style="background-color:#eee;">
                                <th class="txtcenter"  style="border: 1px solid black; width: 1000px; ">
                                    <b>Descrizione</b><br/><em>(Indicare dosaggio e forma farmaceutica del farmaco/dettagli del dispositivo)</em>
                                </th>
                                <th class="txtcenter" style="border: 1px solid black; width: 1000px; ">
                                    <b>Costo compreso nel costo della prestazione</b><br/>(Si/No/n.a.)
                                </th>
                                <th class="txtcenter" style="border: 1px solid black; width: 1000px; ">
                                    <b>Unit&agrave; di misura</b>
                                </th>
                                <th class="txtcenter" style="border: 1px solid black; width: 1000px; ">
                                    <b>Numero unit&agrave; a paziente</b><br/><em>(stima)</em>
                                </th>
                                <th class="txtcenter" style="border: 1px solid black; width: 1000px; ">
                                    <b>Totale valore se quantificabile</b><br/>(Euro)
                                </th>
                                
                            </tr>
                            <#list farmaci_disp_cat3_list as currFarmaco >
                            <tr>
                                <td class="txtleft" style="border: 1px solid black; width: 1000px; ">
                                   &nbsp;${currFarmaco.getFieldDataDecode("Farmaco","princAtt")}${currFarmaco.getFieldDataDecode("Farmaco","dispMed")}&nbsp;-&nbsp;${currFarmaco.getFieldDataString("Farmaco","descrizione")}
                                </td>
                                <td class="txtleft" style="border: 1px solid black; width: 1000px; ">
                                    &nbsp;${currFarmaco.getFieldDataDecode("Farmaco","costo")}
                                </td>
                                <td class="txtleft" style="border: 1px solid black; width: 1000px; ">
                                   &nbsp;${currFarmaco.getFieldDataString("Farmaco","unitaMisura")}
                                </td>
                                <td class="txtleft" style="border: 1px solid black; width: 1000px; ">
                                    &nbsp;${currFarmaco.getFieldDataString("Farmaco","numUnitaPaz")}
                                </td>
                                <td class="txtright" style="border: 1px solid black; width: 1000px;font-family:monospace; ">
                                    &nbsp;${currFarmaco.getFieldDataString("Farmaco","totaleValore")?number?string("##0.00")}
                                </td>
                            </tr>
                            </#list>
                            <tr>
                                <td class="txtleft" colspan="4" style="border: 1px solid black; width: 1000px; ">
                                    <b><em>Totale</em></b>
                                </td>
                                <td class="txtright" colspan="1" style="border: 1px solid black; width: 1000px;font-family:monospace; background-color:#eee;">
                                    <b><em>&nbsp;${costo_cat3?string("##0.00")}</em></b>
                                </td>

                            </tr>
                        </table>
                        <div style="page-break-before:always">&nbsp;</div>
                        <table cellspacing="0" style="border-collapse: collapse;">
                            <tr>
                                <td class="txtleft" style="padding-bottom: 10px; padding-top: 20px;"><br/>
                                    <b>A.4.4 DETTAGLIO MATERIALI IN COMODATO D'USO </b><br/>
                                </td>
                            </tr>
                        </table>
                        <br/>
                        <table cellspacing="0" style="border-collapse: collapse;">
                            <tr style="background-color:#eee;">
                                <th class="txtcenter"  style="border: 1px solid black; width: 1000px; ">
                                    <b>Descrizione</b>
                                </th>
                                <th class="txtcenter" style="border: 1px solid black; width: 1000px; ">
                                    <b>Costo compreso nel costo della prestazione</b><br/>(Si/No/n.a.)
                                </th>
                                <th class="txtcenter" style="border: 1px solid black; width: 1000px; ">
                                    <b>Unit&agrave; di misura</b>
                                </th>
                                <th class="txtcenter" style="border: 1px solid black; width: 1000px; ">
                                    <b>Numero unit&agrave; a paziente</b><br/><em>(stima)</em>
                                </th>
                                <th class="txtcenter" style="border: 1px solid black; width: 1000px; ">
                                    <b>Totale valore se quantificabile</b><br/>(Euro)
                                </th>
                                
                            </tr>
                            <#list materiali_comodato_list as currFarmaco >
                            <tr>
                                <td class="txtleft" style="border: 1px solid black; width: 1000px; ">
                                   &nbsp;${currFarmaco.getFieldDataString("Farmaco","descrizione")}
                                </td>
                                <td class="txtleft" style="border: 1px solid black; width: 1000px; ">
                                    &nbsp;${currFarmaco.getFieldDataDecode("Farmaco","costo")}
                                </td>
                                <td class="txtleft" style="border: 1px solid black; width: 1000px; ">
                                   &nbsp;${currFarmaco.getFieldDataString("Farmaco","unitaMisura")}
                                </td>
                                <td class="txtleft" style="border: 1px solid black; width: 1000px; ">
                                    &nbsp;${currFarmaco.getFieldDataString("Farmaco","numUnitaPaz")}
                                </td>
                                <td class="txtright" style="border: 1px solid black; width: 1000px;font-family:monospace; ">
                                    &nbsp;${currFarmaco.getFieldDataString("Farmaco","totaleValore")?number?string("##0.00")}
                                </td>
                            </tr>
                            </#list>
                            <tr>
                                <td class="txtleft" colspan="4" style="border: 1px solid black; width: 1000px; ">
                                    <b><em>Totale</em></b>
                                </td>
                                <td class="txtright" colspan="1" style="border: 1px solid black; width: 1000px;font-family:monospace; background-color:#eee;">
                                    <b><em>&nbsp;${costo_comodato?string("##0.00")}</em></b>
                                </td>

                            </tr>
                        </table>
                        <div style="page-break-before:always">&nbsp;</div>
                        <table cellspacing="0" style="border-collapse: collapse;">
                            <tr>
                                <td class="txtleft" style="padding-bottom: 10px; padding-top: 20px;"><br/>
                                    <b>A.5 COPERTURA ASSICURATIVA</b><br/>
                                </td>
                            </tr>
                        </table>
                        <table cellspacing="0" style="border-collapse: collapse;">
                            <tr>
                                <td class="txtleft" style="width:100%; font-weight: bold; padding:4px;">
                                    <b>Lo studio prevede una copertura assicurativa?</b>
                                    <#if el.getFieldDataCode("Feasibility","CopAss")?? && el.getFieldDataCode("Feasibility","CopAss")=="1" >
                                        &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;SI&nbsp;${CheckedCheckbox}&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;NO&nbsp;${UncheckedCheckbox}
                                        <#else>
                                        &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;SI&nbsp;${UncheckedCheckbox}&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;NO&nbsp;${CheckedCheckbox}
                                    </#if>
                                </td>
                            </tr>
                            <tr>
                                <td class="txtleft" style="width:100%; padding:4px;">
                                    <b>Per studio profit</b><br /><em>(Allegare la polizza assicurativa)</em>
                                </td>
                            </tr>
                            <tr>
                                <td class="txtleft" style="width:100%; padding:4px;">
                                    <b>Per studio no-profit</b><br /><em>(Allegare il preventivo assicurativo)<br/>
                                    e specificare se i costi sono coperti con:
                                    <#if el.getFieldDataCode("Feasibility","CopAssA")?? && el.getFieldDataCode("Feasibility","CopAssA")=="1" >
                                    &nbsp;<b>A</b>&nbsp;
                                    </#if>  
                                    <#if el.getFieldDataCode("Feasibility","CopAssB")?? && el.getFieldDataCode("Feasibility","CopAssB")=="1" >
                                    &nbsp;<b>B</b>&nbsp;
                                    </#if>  
                                    <#if el.getFieldDataCode("Feasibility","CopAssC")?? && el.getFieldDataCode("Feasibility","CopAssC")=="1" >
                                    &nbsp;<b>C</b>&nbsp;
                                    </#if>  
                                    (indicare come di seguito)</em><br/><br/>
                                </td>
                            </tr>
                            <tr>
                                <td class="txtleft" style="margin-top:10px;padding-bottom: 10px; border: 1px solid black;">
                                    <b>A</b> = fondi della struttura sanitaria a disposizione dello Sperimentatore/Promotore (es. fondi di ricerca)<br/>
                                    <b>B</b> = finanziamento proveniente da terzi (<em>in tal caso si richiede una dichiarazione di disponibilit&agrave; a sostenere i costi connessi allo studio da parte del finanziatore</em>), da dettagliare nella Sezione B<br/>
                                    <b>C</b> = fondo aziendale non alimentato dal SSN, in dotazione all'Azienda Sanitaria (<em>come previsto dal D.M. 17/12/2004</em>)
                                </td>
                            </tr>    
                        </table>
                        <table cellspacing="0" style="border-collapse: collapse;">
                            <tr>
                                <td colspan="2" class="txtleft" style="padding-bottom: 10px; padding-top: 20px;"><br/>
                                    <b>A.6 COINVOLGIMENTO DELLA FARMACIA</b><br/>
                                </td>
                            </tr>
                            <tr>
                            <td style="width:70%; ">
                                Lo studio prevede il coinvolgimento diretto della Farmacia?
                                <#if el.getFieldDataCode("Feasibility","FC1")?? && el.getFieldDataCode("Feasibility","FC1")=="1" >
                                    &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;SI&nbsp;${CheckedCheckbox}&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;NO&nbsp;${UncheckedCheckbox}
                                    <#else>
                                    &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;SI&nbsp;${UncheckedCheckbox}&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;NO&nbsp;${CheckedCheckbox}
                                </#if>
                            </td>
                          </tr>
                          <tr>
                            <td><em><u>Se si, barrare l'opzione pertinente</u></em></td>
                          </tr>
                        </table>
                        <table cellspacing="0" style="border-collapse: collapse;">
                            <tr>
                                <td>1. il coinvolgimento della Farmacia &egrave; richiesto per:</td>
                            </tr>
							<tr>
								<td>&nbsp;${setCheckbox("Feasibility" "FC2" "1" el)}&nbsp; La randomizzazione</td>
							</tr>
							<tr>
                                <td>&nbsp;${setCheckbox("Feasibility" "FC31" "1" el)}&nbsp; ricezione e verifica dei farmaci</td>
                            </tr>
							<tr>
								<td>&nbsp;${setCheckbox("Feasibility" "FC3" "1" el)}&nbsp; La preparazione del/i farmaco/i sperimentale/i (compreso il placebo) ed in particolare</td>
							</tr>
							<tr>
								<td style="padding-left: 20px;">&nbsp;${setCheckbox("Feasibility" "FC4" "1" el)}&nbsp; Esecuzione di studio di fattibilit&agrave;/definizione della formulazione</td>
							</tr>
							<tr>
								<td style="padding-left: 20px;">&nbsp;${setCheckbox("Feasibility" "FC5" "1" el)}&nbsp; Allestimento del/i farmaco/i sperimentale/i</td>
							</tr>
							<tr>
								<td style="padding-left: 20px;">&nbsp;${setCheckbox("Feasibility" "FC6" "1" el)}&nbsp; Ricostituzione/diluizione, anche in dose personalizzata</td>
							</tr>
							<tr>
								<td style="padding-left: 20px;">&nbsp;${setCheckbox("Feasibility" "FC7" "1" el)}&nbsp; Confezionamento/mascheramento</td>
							</tr>
							<tr>
                                <td style="padding-left: 20px;">&nbsp;${setCheckbox("Feasibility" "FC7bis" "1" el)}&nbsp; eventuale smaltimento farmaci residui o scaduti (<em>spesa a carico del promotore &euro; ${el.getFieldDataString("Feasibility","FC7ter")} </em>)</td>
                            </tr>
							<tr>
								<td style="padding-left: 20px;">&nbsp;${setCheckbox("Feasibility" "FC8" "1" el)}&nbsp; Altro (specificare): ${getField("Feasibility","noteFC8",el)}</td>
							</tr>
							<tr>
                                <td>2. 
                                    <#if el.getFieldDataCode("Feasibility","FC29")?? && el.getFieldDataCode("Feasibility","FC29")=="1" >
                                        &egrave; previsto un grant a copertura dei costi dell'U.O. per la somma complessiva di &euro; ${el.getFieldDataString("Feasibility","FC29bis")}
                                    <#else>
                                        non &egrave; previsto un grant a copertura dei costi dell'U.O.
                                    </#if>
                                </td>
                            </tr>
                            <tr>
                                <td>3. 
                                    <#if el.getFieldDataCode("Feasibility","FC30")?? && el.getFieldDataCode("Feasibility","FC30")=="1" >
                                        &egrave; previsto un grant a copertura del costo orario per l'attivit&agrave; aggiuntiva del farmacista coinvolto
                                    <#else>
                                        non &egrave; previsto a copertura del costo orario per l'attivit&agrave; aggiuntiva del farmacista coinvolto
                                    </#if>
                                </td>
                            </tr>
						</table>
						
						<table style="border-collapse: collapse;">
							<tr>
								<td>
									Tutte le attivit&agrave; di cui sopra sono richieste per:
								</td>
							</tr>
							<tr>
								<td style="">&nbsp;${setCheckbox("Feasibility" "FC9" "1" el)}&nbsp; Questo singolo centro;</td>
							</tr>
							<tr>
								<td style="">&nbsp;${setCheckbox("Feasibility" "FC10" "1" el)}&nbsp; I seguenti centri partecipanti allo studio: ${getField("Feasibility","noteFC10",el)}</td>
							</tr>
						</table>
						<br/>
						<table cellspacing="0" border="1" rules="none" frame="box" style="border-collapse: collapse;">
							<tr>
								<td colspan="2" class="txtleft" style="padding-top: 3px; width:100%; font-weight: bold;"><b>SEZIONE A CURA DEL FARMACISTA REFERENTE (se applicabile)</b></td>
							</tr>
							<tr>
								<td colspan="2">
									<b>Presa visione dell'impegno richiesto alla Farmacia da parte dello sperimentatore, si dichiara la disponibilit&agrave; nell'esecuzione delle attivit&agrave; di cui sopra.</b>
								</td>
							</tr>
							<tr>
						    <td colspan="2"><b>Compenso previsto ${UncheckedCheckbox}&nbsp;&nbsp;S&igrave;&nbsp; ${UncheckedCheckbox}&nbsp;&nbsp;No&nbsp;</b></td>
						  </tr>
						  <tr>
						    <td width="50%"><b>Data<br/>...............</b></td>
						    <td width="50%"><b>Il farmacista responsabile<br/>.............................................</b></td>
						  </tr>
						</table>
						<div style="page-break-before:always">&nbsp;</div>
						<table cellspacing="0" style="border-collapse: collapse;">
                            <tr>
                                <td colspan="2" class="txtleft" style="padding-bottom: 10px; padding-top: 20px;"><br/>
                                    <b>A.7 SINTESI RIASSUNTIVA DEL VALORE ECONOMICO DELLO STUDIO</b><br/>
                                </td>
                            </tr>
                        </table>
                        <table cellspacing="0" style="border-collapse: collapse;">
                            <tr style="background-color:#eee;">
                                <th class="txtleft" style="border: 1px solid black; width: 1000px; ">
                                    <b>Descrizione</b>
                                </th>
                                <th class="txtleft" style="border: 1px solid black; width: 1000px; ">
                                    <b>Totale (Euro)</b>
                                </th>
                            </tr>
                            <tr>
                                <td class="txtleft" style="border: 1px solid black; width: 1000px; ">
                                    <b>Prestazioni routinarie previste nello studio clinico</b><br/><em>(inserire totale tab. A.2a)</em>
                                </td>
                                <td class="txtright" style="border: 1px solid black; width: 1000px;font-family:monospace ">
                                   <#if totaleRoutine??> &euro;&nbsp;${totaleRoutine?string("##0.00")}</#if>
                                </td>
                            </tr>
                            <tr>
                                <td class="txtleft" style="border: 1px solid black; width: 1000px; ">
                                    <b>Prestazioni aggiuntive previste nello studio clinico</b><br/><em>(inserire totale tab. A.2b)</em>
                                </td>
                                <td class="txtright" style="border: 1px solid black; width: 1000px;font-family:monospace ">
                                   <#if totaleExtraRoutine??>&euro;&nbsp;${totaleExtraRoutine?string("##0.00")}</#if>
                                </td>
                            </tr>
                            <tr>
                                <td class="txtleft" style="border: 1px solid black; width: 1000px; ">
                                    <b>Materiali di consumo, attrezzature, servizi e spese per il personale </b><br/><em>(inserire totale tab. A.3)</em>
                                </td>
                                <td class="txtright" style="border: 1px solid black; width: 1000px;font-family:monospace ">
                                    <#if totaleCostiAggiuntivi??>&euro;&nbsp;${totaleCostiAggiuntivi?string("##0.00")}</#if>
                                </td>
                            </tr>
                            <tr>
                                <td class="txtleft" style="border: 1px solid black; width: 1000px; ">
                                    <b>Farmaci o dispositivi medici sperimentali </b><br/><em>(inserire totale tab. A.4.1)</em>
                                </td>
                                <td class="txtright" style="border: 1px solid black; width: 1000px;font-family:monospace ">
                                    <#if costo_cat1??>&euro;&nbsp;${costo_cat1?string("##0.00")}</#if>
                                </td>
                            </tr>
                            <tr>
                                <td class="txtleft" style="border: 1px solid black; width: 1000px; ">
                                    <b>Farmaci o dispostivi medici non oggetto di sperimentazione (previsti dal protocollo ma non dalla pratica clinica: PeIMP)</b><br/><em>(inserire totale tab. A.4.2)</em>
                                </td>
                                <td class="txtright" style="border: 1px solid black; width: 1000px;font-family:monospace ">
                                    <#if costo_cat2??>&euro;&nbsp;${costo_cat2?string("##0.00")}</#if>
                                </td>
                            </tr>
                            <tr>
                                <td class="txtleft" style="border: 1px solid black; width: 1000px; ">
                                    <b>Farmaci o dispositivi medici non oggetto di sperimentazione (previsti dal protocollo e dalla pratica clinica: ReTNIMP)</b><br/><em>(inserire totale tab. A.4.3)</em>
                                </td>
                                <td class="txtright" style="border: 1px solid black; width: 1000px;font-family:monospace ">
                                    <#if costo_cat3??>&euro;&nbsp;${costo_cat3?string("##0.00")}</#if>
                                </td>
                            </tr>
                            <tr>
                                <td class="txtleft" style="border: 1px solid black; width: 1000px; ">
                                    <b>Materiali in comodato d'uso </b><br/><em>(inserire totale tab. A.4.4)</em>
                                </td>
                                <td class="txtright" style="border: 1px solid black; width: 1000px;font-family:monospace ">
                                    <#if costo_comodato??>&euro;&nbsp;${costo_comodato?string("##0.00")}</#if>
                                </td>
                            </tr>
                            <tr>
                                <td class="txtleft" style="border: 1px solid black; width: 1000px; ">
                                    <b>Copertura assicurativa</b><em>(per studi no profit)</em><br/><em>(inserire totale tab. A.5)</em>
                                </td>
                                <td class="txtright" style="border: 1px solid black; width: 1000px; font-family:monospace">
                                    <#assign coperturaAssicurativa=0/>
                                    <#if el.getFieldDataString("Feasibility","CopAssPrezzo")?? &&el.getFieldDataString("Feasibility","CopAssPrezzo")!="">
                                       <#assign coperturaAssicurativa=el.getFieldDataString("Feasibility","CopAssPrezzo")?number/>
                                    </#if>
                                     &euro;&nbsp;${coperturaAssicurativa?string("##0.00")}
                                </td>
                            </tr>
                            <tr>
                                <td class="txtleft" style="border: 1px solid black; width: 1000px; ">
                                    <b>Totale</b>
                                </td>
                                <td class="txtright" style="border: 1px solid black; width: 1000px;font-family:monospace; ">
                                    <#assign totale=0 />
                                    <#if totaleRoutine??>
                                        <#assign totale= totale + totaleRoutine />
                                    </#if>
                                    <#if totaleExtraRoutine??>
                                        <#assign totale= totale + totaleExtraRoutine />
                                    </#if>
                                    <#if totaleCostiAggiuntivi??>
                                        <#assign totale= totale + totaleCostiAggiuntivi />
                                    </#if>
                                    <#if costo_cat1??>
                                        <#assign totale= totale + costo_cat1 />
                                    </#if>
                                    <#if costo_cat2??>
                                        <#assign totale= totale + costo_cat2 />
                                    </#if>
                                    <#if costo_cat3??>
                                        <#assign totale= totale + costo_cat3 />
                                    </#if>
                                    <#if costo_comodato??>
                                        <#assign totale= totale + costo_comodato />
                                    </#if>
                                    <#if coperturaAssicurativa??>
                                        <#assign totale= totale + coperturaAssicurativa />
                                    </#if>
                                    <#if totale??>&euro;&nbsp;${totale?string("##0.00")}</#if>
                                </td>
                            </tr>
                        </table>
                        <div style="page-break-before:always">&nbsp;</div>
                        <table>   
                            <tr>
                                <td class="txtcenter" style="padding-bottom: 10px; padding-top: 20px;">
                                    <b>SEZIONE B: MODULO RELATIVO AL COINVOLGIMENTO DEL PERSONALE</b>
                                </td>
                            </tr>
                            <tr> 
                                <td>
                                    <b>PERSONALE <u>DIPENDENTE/CONVENZIONATO</u> DEL SSR PRESSO LA STRUTTURA/U.O. PROPONENTE</b>
                                </td>
                            </tr>
                        </table>
                        <table cellspacing="0" style="border-collapse: collapse;">
                            <tr style="background-color:#eee;">
                                <th class="txtcenter" rowspan="2" style="border: 1px solid black; width: 1000px; ">
                                    <b>Cognome Nome</b>
                                </th>
                                <th class="txtcenter" rowspan="2" style="border: 1px solid black; width: 1000px; ">
                                    <b>Ruolo</b>
                                </th>
                                <th class="txtcenter" rowspan="1" colspan="2" style="border: 1px solid black; width: 1000px; ">
                                    <b>Attivit&agrave; di studio svolta:</b>
                                </th>
                                <th class="txtcenter" rowspan="2" style="border: 1px solid black; width: 1000px; ">
                                    <b>Firma</b>
                                </th>
                            </tr>
                            <tr style="background-color:#eee;">
                                <td class="txtcenter" rowspan="1" style="border: 1px solid black; width: 1000px; ">
                                    nell'orario di servizio* (in ore a paziente stimate)
                                </td>
                                <td class="txtcenter" rowspan="1" style="border: 1px solid black; width: 1000px; ">
                                    fuori dall'orario di servizio (in ore a paziente stimate)
                                </td>
                            </tr>
                            <#list personale_dipendente as currPersonale >
                            <tr>
                                <td class="txtleft" style="border: 1px solid black; width: 1000px; ">
                                    ${currPersonale.getFieldDataDecode("DatiTeamDiStudio","NomeCognome")}
                                </td>
                                <td class="txtleft" style="border: 1px solid black; width: 1000px; ">
                                    ${currPersonale.getFieldDataDecode("DatiTeamDiStudio","Ruolo")}
                                </td>
                                <td class="txtleft" style="border: 1px solid black; width: 1000px; ">
                                    ${currPersonale.getFieldDataString("DatiTeamDiStudio","attivitaDip1")}
                                </td>
                                <td class="txtleft" style="border: 1px solid black; width: 1000px; ">
                                    ${currPersonale.getFieldDataString("DatiTeamDiStudio","attivitaDip2")}
                                </td>
                                <td class="txtleft" style="border: 1px solid black; width: 1000px; ">
                                    &nbsp;
                                </td>
                            </tr>
                            </#list>
                        </table>
                        <br/>
                        <table>   
                            <tr> 
                                <td>
                                    * Se trattasi di studio profit, il compenso relativo all'attivit&agrave; del dipendente deve essere destinato al fondo di U.O.
                                </td>
                            </tr>
                        </table>
                        <br />
                        <table>   
                            <tr> 
                                <td>
                                    <b>PERSONALE <u>NON-DIPENDENTE/NON CONVENZIONATO</u> DEL SSR PRESSO LA STRUTTURA/U.O. PROPONENTE</b>
                                </td>
                            </tr>
                        </table>
                        <table cellspacing="0" style="border-collapse: collapse;">
                            <tr style="background-color:#eee;">
                                <th class="txtcenter" style="border: 1px solid black; width: 1000px; ">
                                    <b>Cognome Nome</b>
                                </th>
                                <th class="txtcenter" style="border: 1px solid black; width: 1000px; ">
                                    <b>Ruolo</b>
                                </th>
                                <th class="txtcenter" style="border: 1px solid black; width: 1000px; ">
                                    <b>Tipologia di rapporto lavorativo</b><br/><em>(libero professionale, consulente, borsista, ecc)</em>
                                </th>
                                <th class="txtcenter" style="border: 1px solid black; width: 1000px; ">
                                    <b>Ente di appartenenza</b>
                                </th>
                                <th class="txtcenter" style="border: 1px solid black; width: 1000px; ">
                                    <b>Attitit&agrave; studio specifica svolta</b><br />(ore a paziente stimate)
                                </th>
                                <th class="txtcenter" style="border: 1px solid black; width: 1000px; ">
                                    <b>Firma</b>
                                </th>
                            </tr>
                            <#list personale_non_dipendente as currPersonale >
                            <tr>
                                <td class="txtleft" style="border: 1px solid black; width: 1000px; ">
                                     ${currPersonale.getFieldDataString("DatiTeamDiStudio","AltroPersonale")}
                                </td>
                                <td class="txtleft" style="border: 1px solid black; width: 1000px; ">
                                     ${currPersonale.getFieldDataDecode("DatiTeamDiStudio","Ruolo")}
                                </td>
                                <td class="txtleft" style="border: 1px solid black; width: 1000px; ">
                                    ${currPersonale.getFieldDataDecode("DatiTeamDiStudio","rapLavNonDip")}
                                </td>
                                <td class="txtleft" style="border: 1px solid black; width: 1000px; ">
                                    ${currPersonale.getFieldDataString("DatiTeamDiStudio","EnteNonDip")}
                                </td>
                                <td class="txtleft" style="border: 1px solid black; width: 1000px; ">
                                    ${currPersonale.getFieldDataString("DatiTeamDiStudio","attivitaNonDip1")}
                                </td>
                                <td class="txtleft" style="border: 1px solid black; width: 1000px; ">
                                    &nbsp;
                                </td>
                            </tr>
                            </#list>
                        </table>
                        <div style="page-break-before:always">&nbsp;</div>
                        <table>   
                            <tr>
                                <td class="txtcenter" style="padding-bottom: 10px; padding-top: 20px;">
                                    <b>SEZIONE C: MODULO DI PREVISIONE DI IMPIEGO DEL FINANZIAMENTO ESTERNO</b>
                                </td>
                            </tr>
                            <tr> 
                                <td>
                                    <b>PREVISIONE IMPIEGO FINANZIAMENTO:</b>
                                </td>
                            </tr>
                            <tr> 
                                <td>
                                    Entit&agrave; del finanziamento: &euro;${totale?string("##0.00")}
                                </td>
                            </tr>
                            <tr> 
                                <td>
                                    Indicare l'Azienda profit/Ente/i che mette/mettono a disposizione il finanziamento per la conduzione dello studio:&nbsp;<b>${ente_conduzione_studio}</b>
                                </td>
                            </tr>
                        </table>
                        <table cellspacing="0" style="border-collapse: collapse;">
                            <tr style="background-color:#eee;">
                                <th class="txtcenter" style="border: 1px solid black; width: 1000px; ">
                                    &nbsp;
                                </th>
                                <th class="txtcenter" style="border: 1px solid black; width: 1000px; ">
                                    <b>Destinazioni</b>
                                </th>
                                <th class="txtcenter" style="border: 1px solid black; width: 1000px; ">
                                    <b>Valore percentuale (%)</b>
                                </th>
                            </tr>
                            <tr>
                                <td class="txtleft" style="border: 1px solid black; width: 1000px; ">
                                    a
                                </td>
                                <td class="txtleft" style="border: 1px solid black; width: 1000px; ">
                                    Importi trattenuti dall'Azienda sanitaria come overhead
                                </td>
                                <td class="txtleft" style="border: 1px solid black; width: 1000px; ">
                                    ${el.getFieldDataString("Feasibility","valorePerc6")}&nbsp;
                                </td>
                            </tr>
                            <tr>
                                <td class="txtleft" style="border: 1px solid black; width: 1000px; ">
                                    b
                                </td>
                                <td class="txtleft" style="border: 1px solid black; width: 1000px; ">
                                    Compensi al personale medico coinvolto nello studio clinico
                                </td>
                                <td class="txtleft" style="border: 1px solid black; width: 1000px; ">
                                    ${el.getFieldDataString("Feasibility","compensiDirigente")}&nbsp;
                                </td>
                            </tr>
                            <tr>
                                <td class="txtleft" style="border: 1px solid black; width: 1000px; ">
                                    c
                                </td>
                                <td class="txtleft" style="border: 1px solid black; width: 1000px; ">
                                    Compensi per il personale non medico coinvolto nello studio clinico
                                </td>
                                <td class="txtleft" style="border: 1px solid black; width: 1000px; ">
                                    ${el.getFieldDataString("Feasibility","compensiReparto")}&nbsp;
                                </td>
                            </tr>
                            <tr>
                                <td class="txtleft" style="border: 1px solid black; width: 1000px; ">
                                    d
                                </td>
                                <td class="txtleft" style="border: 1px solid black; width: 1000px; ">
                                    Compensi destinati a fondo di U.O.
                                </td>
                                <td class="txtleft" style="border: 1px solid black; width: 1000px; ">
                                    ${el.getFieldDataString("Feasibility","valorePerc1")}&nbsp;
                                </td>
                            </tr>
                            <tr>
                                <td class="txtleft" style="border: 1px solid black; width: 1000px; ">
                                    e
                                </td>
                                <td class="txtleft" style="border: 1px solid black; width: 1000px; ">
                                    Compensi destinati all'Universit&agrave;
                                </td>
                                <td class="txtleft" style="border: 1px solid black; width: 1000px; ">
                                    ${el.getFieldDataString("Feasibility","valorePerc2")}&nbsp;
                                </td>
                            </tr>
                            <tr>
                                <td class="txtleft" style="border: 1px solid black; width: 1000px; ">
                                    f
                                </td>
                                <td class="txtleft" style="border: 1px solid black; width: 1000px; ">
                                    Importo accantonato nel fondo Clinical Trial Office (CTO)/Task Force Aziendale (CTA)
                                </td>
                                <td class="txtleft" style="border: 1px solid black; width: 1000px; ">
                                    ${el.getFieldDataString("Feasibility","valorePerc3")}&nbsp;
                                </td>
                            </tr>
                            <tr>
                                <td class="txtleft" style="border: 1px solid black; width: 1000px; ">
                                    g
                                </td>
                                <td class="txtleft" style="border: 1px solid black; width: 1000px; ">
                                    Importo accantonato nel fondo per gli studi no profit
                                </td>
                                <td class="txtleft" style="border: 1px solid black; width: 1000px; ">
                                    ${el.getFieldDataString("Feasibility","valorePerc4")}&nbsp;
                                </td>
                            </tr>
                            <tr>
                                <td class="txtleft" style="border: 1px solid black; width: 1000px; ">
                                    h
                                </td>
                                <td class="txtleft" style="border: 1px solid black; width: 1000px; ">
                                    Importo accantonato nel forndo per la Sezione del CER (se applicabile)
                                </td>
                                <td class="txtleft" style="border: 1px solid black; width: 1000px; ">
                                    ${el.getFieldDataString("Feasibility","valorePerc7")}&nbsp;
                                </td>
                            </tr>
                            <tr>
                                <td class="txtleft" style="border: 1px solid black; width: 1000px; ">
                                    i
                                </td>
                                <td class="txtleft" style="border: 1px solid black; width: 1000px; ">
                                   Altro&nbsp;<b>${el.getFieldDataString("Feasibility","notePerc5")}</b>
                                </td>
                                <td class="txtleft" style="border: 1px solid black; width: 1000px; ">
                                    ${el.getFieldDataString("Feasibility","valorePerc5")}&nbsp;
                                </td>
                            </tr>
                            <tr>
                                <td class="txtleft" style="border: 1px solid black; width: 1000px; ">
                                    &nbsp;
                                </td>
                                <td class="txtleft" style="border: 1px solid black; width: 1000px; ">
                                    &nbsp;
                                </td>
                                <td class="txtleft" style="border: 1px solid black; width: 1000px; ">
                                    &nbsp;
                                </td>
                            </tr>
                        </table>
                        <div style="page-break-before: always">&nbsp;</div>
                        <table>   
                            <tr>
                                <td class="txtcenter" style="padding-bottom: 10px; padding-top: 20px;">
                                    <b><u>D: ASSUNZIONE DI RESPONSABILIT&Agrave; E NULLA OSTA AL RILASCIO DELLA FATTIBILIT&Agrave; LOCALE, A CURA DELLO SPERIMENTATORE RESPONSABILE DELLO STUDIO, DEL DIRETTORE DELL'UNIT&Agrave; OPERATIVA E DEL DIRETTORE GENERALE DELLA STRUTTURA SANITARIA</u></b>
                                </td>
                            </tr>
                            <tr> 
                                <td>
                                    <span style="text-align: justify">I sottoscritti Sperimentatore Responsabile, Direttore dell'Unit&agrave; Operativa della struttura sanitaria richiedente e Direttore Generale della struttura sanitaria, sotto la propria responsabilit&agrave; e per quanto di propria competenza, dichiarano che:</span>
                                </td>
                            </tr>
                            <tr>
                                <td>
                                <ul class="">
                                    <li>visti i criteri per l'arruolamento dei pazienti previsti dal presente protocollo, essi non confliggono con i criteri di arruolamento di altri protocolli attivati presso l'Unit&agrave; Operativa;</li>
                                    <li>il personale coinvolto (sperimentatore principale e collaboratori) &egrave; competente ed idoneo;</li>
                                    <li>l'Unit&agrave; Operativa presso cui si svolge la ricerca &egrave; idonea; </li>
                                    <li>la conduzione della sperimentazione non ostacoler&agrave; la pratica assistenziale;</li>
                                    <li>lo studio verr&agrave; condotto secondo il protocollo di studio, in conformit&agrave; ai principi della Buona Pratica Clinica (GCP) nell'ultima versione riconosciuta nella normativa italiana, della Dichiarazione di Helsinki e nel rispetto delle normative vigenti e pertinenti;</li>
                                    <li>lo sperimentazione si impegna a segnalare alla direzione aziendale, alla Sezione competente del Comitato Etico Regionale e al Promotore ogni deviazione critica dalle GCP, ogni deviazioni dal protocollo di studio o il venir meno dei requisiti sui quali &egrave; fondata l'idoneit&agrave; della struttura,  entro 7 giorni dal momento in cui ne viene a conoscenza e comunque a rispettare ogni disposizione normativa relativa a tali comunicazioni;</li>
                                    <li>ai soggetti che parteciperanno allo studio, al fine di una consapevole espressione del consenso, verranno fornite tutte le informazioni necessarie, inclusi i potenziali rischi correlati alla sperimentazione;</li>
                                    <li>l'inclusione del paziente nello studio sar&agrave; registrata sulla cartella clinica o su altro documento ufficiale, unitamente alla documentazione del consenso informato;</li>
                                    <li>si assicurer&agrave; che ogni emendamento o qualsiasi altra modifica al protocollo che si dovesse verificare nel corso dello studio, rilevante per la conduzione dello stesso, verr&agrave; inoltrato al Comitato Etico da parte del Promotore;</li>
                                    <li>sar&agrave; comunicato ogni evento avverso serio al Promotore secondo normativa vigente o secondo quanto indicato nel protocollo di studio;</li>
                                    <li>ai fini del monitoraggio e degli adempimenti amministrativi, verr&agrave; comunicato al Comitato Etico l'inizio e la fine dello studio nonch&eacute; inviato, almeno annualmente, il rapporto scritto sull'avanzamento dello studio e verranno forniti, se richiesto dal Comitato Etico, rapporti ad interim sullo stato di avanzamento dello studio;</li>
                                    <li>la documentazione inerente lo studio verr&agrave; conservata in conformit&agrave; a quanto stabilito dalle Norme di Buona Pratica Clinica e alle normative vigenti;</li>
                                    <li>la ricezione del medicinale sperimentale utilizzato per lo studio avverr&agrave; attraverso la farmacia della struttura sanitaria e, successivamente, il medicinale stesso verr&agrave; conservato presso il centro sperimentale separatamente dagli altri farmaci;</li>
                                    <li>non sussistono vincoli di diffusione e pubblicazione dei risultati dello studio nel rispetto delle disposizioni vigenti in tema di riservatezza dei dati  sensibili e di tutela brevettuale e, non appena disponibile, verr&agrave; inviata copia della relazione finale e/o della pubblicazione inerente;</li>
                                    <li>la copertura assicurativa &egrave; conforme alla normativa vigente;</li>
                                    <li><#if targetPaziente?? && targetPaziente!="0" >
                                            ${CheckedCheckbox} &egrave; previsto, ${UncheckedCheckbox} non &egrave; previsto
                                        <#else>
                                            ${UncheckedCheckbox} &egrave; previsto, ${CheckedCheckbox} non &egrave; previsto
                                        </#if>  un compenso a paziente arruolato per lo svolgimento dello studio;</li> 
                                    <li><em>(se trattasi di studio no profit) nel caso sia previsto un finanziamento dedicato per la conduzione dello studio, a qualunque titolo concesso da parte di terzi,</em> le condizioni dello stesso sono dichiarate nel corrispondente accordo finanziario stipulato tra (<em>Promotore</em>) ${datiPromotoreCRO} e (<em>Finanziatore terzo</em>) <#if cro?? > cro.getFieldDataString("DatiPromotoreCRO","denominazione")</#if>; le modalit&agrave; del suo impiego sono esplicitate nelle specifiche sezioni A e B e C del presente documento</li> 
                                    <li>qualora successivamente all'approvazione da parte del Comitato Etico si ravvisasse la necessit&agrave; di acquisire un finanziamento a copertura di costi per sopraggiunte esigenze legate alla conduzione dello studio, si impegnano a sottoporre al Comitato Etico, tramite emendamento sostanziale, la documentazione comprovante l'entit&agrave; del finanziamento, il suo utilizzo nonch&eacute; il soggetto erogatore;</li>
                                    <li>lo studio verr&agrave; avviato soltanto dopo la ricezione di formale comunicazione di parere favorevole del Comitato Etico;</li>
                                    <li>Lo sperimentatore dichiara di accettare il compenso a paziente proposto dal Promotore (&euro;&nbsp;<#if targetPaziente?? && targetPaziente!="0" >${targetPaziente?number?string("##0.00")}</#if> + IVA), in quanto ritenuta somma congrua considerate le  procedure previste dal protocollo di studio.</li>
                                    <li>hanno preso visione e approvano quanto dichiarato nelle sezioni precedenti.</li>
                                </ul>
                                </td>
                            </tr>
                            <tr> 
                                <td>
                                    Data: _______________
                                </td>
                            </tr>
                            <tr> 
                                <td>
                                   Firma dello Sperimentatore Responsabile<br/>
                                   ________________________________________________________________________
                                </td>
                            </tr>
                            <tr> 
                                <td>
                                   Firma del Direttore dell'Unit&agrave; Operativa/SOD<br/>
                                   ________________________________________________________________________
                                </td>
                            </tr>
                        </table>
                        <table cellspacing="0" style="background-color:#eee;border: 1px solid black;">
                            <tr style="background-color:#eee;">
                                <th style="text-align:justify;  width: 1000px; padding: 0px 10px;">
                                    <br/>VALUTATO QUANTO SOPRA RIPORTATO, NULLA OSTA AL RILASCIO DELLA FATTIBILIT&Agrave; LOCALE RELATIVA ALLO STUDIO IN OGGETTO IL QUALE  PU&Oacute; ESSERE PRESENTATO ALLA SEZIONE COMPETENTE DEL COMITATO ETICO PER L'ESPRESSIONE DEL PARERE<br/><br/>
                                </th>
                            </tr>
                            <tr style="background-color:#eee;">
                                <td style="text-align:justify;  width: 1000px; padding: 0px 10px;">    
                                    Data: _______________<br/><br/>
                                </td>
                            </tr>
                            <tr style="background-color:#eee;">
                                <td style="text-align:justify;  width: 1000px; padding: 0px 10px;">     
                                    Firma del Direttore della struttura sanitaria<br/>
                                   <em>(o Direttore delegato)</em><br/><br/>
                                   ________________________________________________________________________<br/><br/>
                                </td>
                            </tr>
                        </table>
                        <!--tutto qui dentro FINE-->
					</td>
					<td style="width:2%;"></td>
				</tr>
			</table>
	
		</body>
	</html>
