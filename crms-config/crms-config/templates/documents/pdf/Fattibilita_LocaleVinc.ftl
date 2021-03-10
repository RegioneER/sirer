<#ftl encoding="utf-8">
	<#include "../../themes/ace/macros.ftl">
		<#setting number_format="0.##">
			<#assign el=element/>
			<#assign elStudio=element.getParent()/>
			<#assign cartaIntestata=elStudio.getFieldDataString("UniqueIdStudio","cto") />
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

					<#if allegato.getFieldDataCode("DocGenerali","DocGen")=="4" >

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
													<#assign fonteFin=elStudio.getFieldDataDecode("datiStudio","fonteFinSpec")+" "+elStudio.getFieldDataDecode("datiStudio","fonteFinSponsor")+"  "+elStudio.getFieldDataDecode("datiStudio","fonteFinFondazione")+"  "+elStudio.getFieldDataDecode("datiStudio","fonteFinAltro") />
													<#assign fonteFin2=elStudio.getFieldDataDecode("datiStudio","fonteFinSpec2")+" "+elStudio.getFieldDataDecode("datiStudio","fonteFinSponsor2")+"  "+elStudio.getFieldDataDecode("datiStudio","fonteFinFondazione2")+"  "+elStudio.getFieldDataDecode("datiStudio","fonteFinAltro2") />
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

												<#attempt>
													<#assign totalePaziente=budgetStudio.getFieldDataString("BudgetCTC","TotalePazienteCTC")?number />
													<#assign targetPaziente=budgetStudio.getFieldDataString("BudgetCTC","TargetPaziente") />
													<#assign numeroPazienti=budgetStudio.getFieldDataString("BudgetCTC","NumeroPazienti")?number />
													<#assign totaleStudio=budgetStudio.getFieldDataString("BudgetCTC","TotaleStudioCTC")?number />
													<#recover>
														<#assign totalePaziente=0 />
														<#assign numeroPazienti=0 />
														<#assign totaleStudio=0 />
														<#assign targetPaziente="0" />
												</#attempt>

												<#assign totaleFlow= (totalePaziente * numeroPazienti)  />
												<#assign sommeAggiuntive=(totaleStudio - totaleFlow)  />
												<#attempt>
													<#assign rowsFlowchart=[] + budget.getChildrenByType("FolderPrestazioni")[0].getChildren()  />
													<#assign colsFlowchart=[] + budget.getChildrenByType("FolderTimePoint")[0].getChildren()  />
													<#assign prestazioniFlowchart=[] + budget.getChildrenByType("FolderTpxp")[0].getChildren()  />
													<#assign prestazioniCliniche=[] + budget.getChildrenByType("FolderPXP")[0].getChildren()  />
													<#assign prestazioniCTC=[] + budgetStudio.getChildrenByType("FolderPXPCTC")[0].getChildren()  />
													<#assign passthrough=[] + budgetStudio.getChildrenByType("FolderPassthroughCTC")[0].getChildren()  />
													<#assign prestazioni=[] + prestazioniCliniche + prestazioniCTC  />
													<#assign personale=[] + prestazioniFlowchart + prestazioni + passthrough   />
													<#assign costiAggiuntivi=[] + budget.getChildrenByType("FolderCostiAggiuntivi")[0].getChildren()  />
													<#recover>
														<#assign rowsFlowchart=[]/>
														<#assign colsFlowchart=[]/>
														<#assign prestazioniFlowchart=[]/>
														<#assign prestazioniCliniche=[]/>
														<#assign prestazioniCTC=[]/>
														<#assign passthrough=[]/>
														<#assign prestazioni=[]/>
														<#assign personale=[]/>
														<#assign costiAggiuntivi=[]/>
												</#attempt>
												<#assign personeCoinvolte={}   />
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
												<#assign coperture=["A","B","C","D"] />
												<#assign totaleVisite=0 />
												<#assign totaleCostiAggiuntivi=0 />
												<#list rowsFlowchart as currPrestazione>

													<#if currPrestazione.getFieldDataString("InfoBudgetPDF","NumSSNRoutine")?? && currPrestazione.getFieldDataString("InfoBudgetPDF","NumSSNRoutine")!='' && currPrestazione.getFieldDataString("InfoBudgetPDF","NumSSNRoutine")?number gt 0 >
														<#assign prestazioniRoutine = prestazioniRoutine + [ currPrestazione ] />
													</#if>


													<#if currPrestazione.getFieldDataString("InfoBudgetPDF","NumExtraRoutine")?? && currPrestazione.getFieldDataString("InfoBudgetPDF","NumExtraRoutine")!='' && currPrestazione.getFieldDataString("InfoBudgetPDF","NumExtraRoutine")?number gt 0 >
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

																		<#if (attivitaServizi[currServAtt]??)>
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
																		<br/><b> 1. Sezione A:</b> Informazioni generali dello studio 
																		<br/><b> 2. Sezione B:</b> Modulo dei costi aggiuntivi correlati allo studio
																		<br/><b> 3. Sezione C:</b> Modulo riepilogativo aspetti economici 
																		<br/><b> 4. Sezione D:</b> Modulo di <u>previsione di impiego del finanziamento</u> per lo studio 
																				(da compilare nel caso sia previsto un finanziamento dedicato per la conduzione dello studio)
																		<br/><b> 5. Sezione E:</b> <u>Assunzione di responsabilita'</u> 
																		<br/><br/> <b>La raccolta dei dati e' a cura dello sperimentatore.</b>
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
															<table cellspacing="0" style="border-collapse: collapse;">
																<tr>
																	<td class="txtleft" style="border: 1px solid black; width: 1000px; ">
																		<b>Titolo dello studio </b>
																	</td>
																	<td class="txtleft" style="border: 1px solid black; width: 1000px; ">
																		${elStudio.getFieldDataString("IDstudio","TitoloProt")}
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
																		<b>Acronimo</b>
																	</td>
																	<td class="txtleft" style="border: 1px solid black; width: 1000px; ">
																		${elStudio.getFieldDataString("IDstudio","ACRONIMOALI")}
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
																		<b>Numero EuraMed</b> <em>(se previsto)</em>
																	</td>
																	<td class="txtleft" style="border: 1px solid black; width: 1000px; ">
																		${elStudio.getFieldDataString("datiStudio","NUMEROEURAMEDALI")}
																	</td>
																</tr>
																<tr>
																	<td class="txtleft" style="border: 1px solid black; width: 1000px; ">
																		<b>Numero RSO</b> <em>(se previsto)</em>
																	</td>
																	<td class="txtleft" style="border: 1px solid black; width: 1000px; ">
																		${elStudio.getFieldDataString("datiStudio","NUMERORSOALI")}
																	</td>
																</tr>
																<tr>
																	<td class="txtleft" style="border: 1px solid black; width: 1000px; ">
																		<b>Codice ClinicalTrial.gov</b> <em>(o simili, se previsti)</em>
																	</td>
																	<td class="txtleft" style="border: 1px solid black; width: 1000px; ">
																		${elStudio.getFieldDataString("datiStudio","CONICECLINICALTRIALALI")}
																	</td>
																</tr>
																<tr>
																	<td class="txtleft" style="border: 1px solid black; width: 1000px; ">
																		<b>Promotore dello studio: </b> <em>(indicare denominazione completa)</em>
																	</td>
																	<td class="txtleft" style="border: 1px solid black; width: 1000px; ">
																		<#if datiPromotoreCRO?? >
																			${datiPromotoreCRO}
																		</#if>
																	</td>
																</tr>
																<tr>
																	<td class="txtleft" style="border: 1px solid black; width: 1000px;">Studio profit: </td>
																	<td class="txtleft" style="width:50%;  padding:4px;">
																		&nbsp;${setCheckbox("Feasibility" "FC9" "1" el)}&nbsp; Si'
																&nbsp;		${setCheckbox("Feasibility" "FC9" "1" el)}&nbsp; No
																<br/></td>
																</tr>
																<tr>
																	<td class="txtleft" style="border: 1px solid black; width: 1000px;"><b>Studio no profit finalizzato al miglioramento della pratica clinica (art.1 D.M. 17.12.2004)</b>
																		<br/><em>Ad attestazione di cio', per le sperimentazioni cliniche con farmaci, allegare dichiarazione del Promotore rilasciata ai sensi dell'Allegato 1 al D.M. 17.12.2004</em>: </td>
																	<td class="txtleft" style="width:50%;  padding:4px;">
																		&nbsp;${setCheckbox("Feasibility" "FC9" "1" el)}&nbsp; Si'
																	&nbsp;${setCheckbox("Feasibility" "FC9" "1" el)}&nbsp; No
																<br/></td>
																</tr>
																<tr>
																	<td class="txtleft" style="border: 1px solid black; width: 1000px;"><b>Studio no profit NON finalizzato al miglioramento della pratica clinica (art.6 D.M. 17.12.2004)</b>
																	<br/><em>Ad attestazione di cio' allegare dichiarazione del Promotore rilasciata ai sensi dell'Allegato 1 al D.M. 17.12.2004</em> </td>
																	<td class="txtleft" style="width:50%;  padding:4px;">
																		&nbsp;${setCheckbox("Feasibility" "FC9" "1" el)}&nbsp; Si'
																	&nbsp;${setCheckbox("Feasibility" "FC9" "1" el)}&nbsp; No
																<br/></td>
																</tr>
																<tr>
																	<td class="txtleft" style="border: 1px solid black; width: 1000px;">Studio NOPROFIT finanziato : </td>
																	<td class="txtleft" style="width:50%;  padding:4px;">
																		&nbsp;${setCheckbox("Feasibility" "FC9" "1" el)}&nbsp; Si'
																	&nbsp;${setCheckbox("Feasibility" "FC9" "1" el)}&nbsp; No
																<br/></td>
																</tr>
																<tr>
																	<td class="txtleft" style="border: 1px solid black; width: 1000px; ">
																		<b>Se si', specificare i finanziatori (vedi tracciato record) senza importi</b>
																	</td>
																	<td class="txtleft" style="border: 1px solid black; width: 1000px; ">
																		${elStudio.getFieldDataString("datiStudio","FINANZIATORIALI")}
																	</td>
																</tr>
																<tr>
																	<td class="txtleft" style="border: 1px solid black; width: 1000px;">Studio co-sponsorizzato<sup>1</sup>: </td>
																	<td class="txtleft" style="width:50%;  padding:4px;">
																		&nbsp;${setCheckbox("Feasibility" "FC9" "1" el)}&nbsp; Si'
																	&nbsp;${setCheckbox("Feasibility" "FC9" "1" el)}&nbsp; No
																<br/></td>
																</tr>
															</table>
															<table cellspacing="0" style="border-collapse: collapse;">
																<tr>
																	<td class="txtleft" colspan="2" style="border: 1px solid black; width: 1000px; ">
																		<b>Tipologia dello studio:</b>
																	</td>
																</tr>
																<tr>
																	<td style="">&nbsp;${setCheckbox("Feasibility" "FC9" "1" el)}&nbsp; Sperimentale con farmaco</td>
																</tr>
																<tr>
																	<td class="txtleft" style="width:50%;  padding:4px;">Fasi:</td>
																	<td class="txtleft" style="width:50%;  padding:4px;">
																		&nbsp;${setCheckbox("Feasibility" "FC9" "1" el)}&nbsp; I
																		&nbsp;${setCheckbox("Feasibility" "FC9" "1" el)}&nbsp; II
																		&nbsp;${setCheckbox("Feasibility" "FC9" "1" el)}&nbsp; III
																		&nbsp;${setCheckbox("Feasibility" "FC9" "1" el)}&nbsp; IV
																<br/></td>
																</tr>
																<tr>
																	<td style="">&nbsp;${setCheckbox("Feasibility" "FC9" "1" el)}&nbsp; Indagine clinica con Dispositivo Medico pre-marketing</td>
																</tr>
																<tr>
																	<td style="">&nbsp;${setCheckbox("Feasibility" "FC9" "1" el)}&nbsp; Indagine clinica con Dispositivo Medico post-marketing</td>
																</tr>
																<tr>
																	<td class="txtleft" style="border: 1px solid black; width: 1000px;">Specificare se il dispositivo e' gia' in uso: </td>
																	<td class="txtleft" style="width:50%;  padding:4px;">
																		&nbsp;${setCheckbox("Feasibility" "FC9" "1" el)}&nbsp; Si'
																	&nbsp;${setCheckbox("Feasibility" "FC9" "1" el)}&nbsp; No
																<br/></td>
																</tr>
																<tr>
																	<td style="">&nbsp;${setCheckbox("Feasibility" "FC9" "1" el)}&nbsp; Studio interventistico (senza dispositivi e senza farmaci)</td>
																</tr>
																<tr>
																	<td class="txtleft" style="width:50%;  padding:4px;">Specificare il tipo di intervento</td>
																	<td class="txtleft" style="width:50%;  padding:4px;">
																		&nbsp;${setCheckbox("Feasibility" "FC9" "1" el)}&nbsp; Tecnica diagnostica
																		<br/>
																		&nbsp;${setCheckbox("Feasibility" "FC9" "1" el)}&nbsp; Procedure (es. chirurgica)
																		<br/>
																		&nbsp;${setCheckbox("Feasibility" "FC9" "1" el)}&nbsp; Medicina non convenzionale (es. agopuntura)
																		<br/>
																		&nbsp;${setCheckbox("Feasibility" "FC9" "1" el)}&nbsp; Vaccino/allergene
																		<br/>
																		&nbsp;${setCheckbox("Feasibility" "FC9" "1" el)}&nbsp; Omeopatico
																		<br/>
																		&nbsp;${setCheckbox("Feasibility" "FC9" "1" el)}&nbsp; Fitoterapico
																		<br/>
																		&nbsp;${setCheckbox("Feasibility" "FC9" "1" el)}&nbsp; Integratore alimentare
																		<br/>
																		&nbsp;${setCheckbox("Feasibility" "FC9" "1" el)}&nbsp; Altro (specificare)
																		<br/>
																	</td>
																</tr>
																<tr>
																	<td style="">&nbsp;${setCheckbox("Feasibility" "FC9" "1" el)}&nbsp; Ossservazionale farmacologico</td>
																</tr>
																<tr>
																	<td class="txtleft" style="width:50%;  padding:4px;">&nbsp;</td>
																	<td class="txtleft" style="width:50%;  padding:4px;">
																		&nbsp;${setCheckbox("Feasibility" "FC9" "1" el)}&nbsp; di coorte prospettico
																		<br/>
																		&nbsp;${setCheckbox("Feasibility" "FC9" "1" el)}&nbsp; di coorte retrospettivo
																		<br/>
																		&nbsp;${setCheckbox("Feasibility" "FC9" "1" el)}&nbsp; caso-controllo
																		<br/>
																		&nbsp;${setCheckbox("Feasibility" "FC9" "1" el)}&nbsp; studi solo su casi (descrittivo)
																		<br/>
																		&nbsp;${setCheckbox("Feasibility" "FC9" "1" el)}&nbsp; trasversale
																		<br/>
																		&nbsp;${setCheckbox("Feasibility" "FC9" "1" el)}&nbsp; di appropriatezza
																		<br/></td>
																</tr>
																<tr>
																	<td style="">&nbsp;${setCheckbox("Feasibility" "FC9" "1" el)}&nbsp; Ossservazionale non farmacologico</td>
																</tr>
																<tr>
																	<td class="txtleft" style="width:50%;  padding:4px;">&nbsp;</td>
																	<td class="txtleft" style="width:50%;  padding:4px;">
																		&nbsp;${setCheckbox("Feasibility" "FC9" "1" el)}&nbsp; di coorte prospettico
																		<br/>
																		&nbsp;${setCheckbox("Feasibility" "FC9" "1" el)}&nbsp; di coorte retrospettivo
																		<br/>
																		&nbsp;${setCheckbox("Feasibility" "FC9" "1" el)}&nbsp; caso-controllo
																		<br/>
																		&nbsp;${setCheckbox("Feasibility" "FC9" "1" el)}&nbsp; studi solo su casi (descrittivo)
																		<br/>
																		&nbsp;${setCheckbox("Feasibility" "FC9" "1" el)}&nbsp; trasversale
																		<br/>
																		&nbsp;${setCheckbox("Feasibility" "FC9" "1" el)}&nbsp; di appropriatezza
																		<br/></td>
																</tr>
																<tr>
																	<td style="">&nbsp;${setCheckbox("Feasibility" "FC9" "1" el)}&nbsp; Studio con impiego di campioni/tessuti umani in vitro</td>
																</tr>
																<tr>
																	<td class="txtleft" style="border: 1px solid black; width: 1000px; ">
																		<b>Specificare il tipo di campione/tessuto</b>
																	</td>
																	<td class="txtleft" style="border: 1px solid black; width: 1000px; ">
																		${elStudio.getFieldDataString("datiStudio","TESSUTOALI")}
																	</td>
																</tr>
																<tr>
																	<td style="">&nbsp;${setCheckbox("Feasibility" "FC9" "1" el)}&nbsp; Studio nazionale</td>
																</tr>
																<tr>
																	<td class="txtleft" style="width:50%;  padding:4px;">&nbsp;</td>
																	<td class="txtleft" style="width:50%;  padding:4px;">
																		&nbsp;${setCheckbox("Feasibility" "FC9" "1" el)}&nbsp; Studio Monocentrico
																		<br/>
																		&nbsp;${setCheckbox("Feasibility" "FC9" "1" el)}&nbsp; Studio Multicentrico
																		<br/></td>
																</tr>
																<tr>
																	<td class="txtleft" style="border: 1px solid black; width: 1000px; ">
																		<b>Se si', indicare il centro coordinatore</b>
																	</td>
																	<td class="txtleft" style="border: 1px solid black; width: 1000px; ">
																		${elStudio.getFieldDataString("datiStudio","TESSUTOALI")}
																	</td>
																</tr>
																<tr>
																	<td class="txtleft" style="border: 1px solid black; width: 1000px; ">
																		<b>Indicare il numero dei centri italiani</b>
																	</td>
																	<td class="txtleft" style="border: 1px solid black; width: 1000px; ">
																		${elStudio.getFieldDataString("datiStudio","TESSUTOALI")}
																	</td>
																</tr>
																<tr>
																	<td style="">&nbsp;${setCheckbox("Feasibility" "FC9" "1" el)}&nbsp; Studio internazionale</td>
																</tr>
																<tr>
																	<td class="txtleft" style="width:50%;  padding:4px;"><b>Durata dello studio nel centro</b></td>
																</tr>
																<tr>
																	<td class="txtleft" style="border: 1px solid black; width: 1000px; ">
																		Data prevista di inizio studio:
																	</td>
																	<td class="txtleft" style="border: 1px solid black; width: 1000px; ">
																	</td>
																</tr>
																<tr>
																	<td class="txtleft" style="border: 1px solid black; width: 1000px; ">
																		Data prevista di inizio arruolamento:
																	</td>
																	<td class="txtleft" style="border: 1px solid black; width: 1000px; ">
																	</td>
																</tr>
																<tr>
																	<td class="txtleft" style="border: 1px solid black; width: 1000px; ">
																		Data prevista di fine studio:
																	</td>
																	<td class="txtleft" style="border: 1px solid black; width: 1000px; ">
																	</td>
																</tr>
																<tr>
																	<td class="txtleft" style="width:50%;  padding:4px;"><b>Classificazione UKCRC</b></td>
																</tr>
																<tr>
																	<td class="txtleft" style="border: 1px solid black; width: 1000px; ">
																		Gruppo attivita' principale (codice)
																	</td>
																	<td class="txtleft" style="border: 1px solid black; width: 1000px; ">
																	</td>
																</tr>
																<tr>
																	<td class="txtleft" style="border: 1px solid black; width: 1000px; ">
																		Attivita' principale (codice)
																	</td>
																	<td class="txtleft" style="border: 1px solid black; width: 1000px; ">
																	</td>
																</tr>
																<tr>
																	<td class="txtleft" style="border: 1px solid black; width: 1000px; ">
																		Gruppo attivita' secondaria (codice)
																	</td>
																	<td class="txtleft" style="border: 1px solid black; width: 1000px; ">
																	</td>
																</tr>
																<tr>
																	<td class="txtleft" style="border: 1px solid black; width: 1000px; ">
																		Attivita' secondaria (codice)
																	</td>
																	<td class="txtleft" style="border: 1px solid black; width: 1000px; ">
																	</td>
																</tr>
																<tr>
																	<td class="txtleft" style="border: 1px solid black; width: 1000px; ">
																		Area tematica principale (codice)
																	</td>
																	<td class="txtleft" style="border: 1px solid black; width: 1000px; ">
																	</td>
																</tr>
																<tr>
																	<td class="txtleft" style="border: 1px solid black; width: 1000px; ">
																		Area tematica secondaria (codice)
																	</td>
																	<td class="txtleft" style="border: 1px solid black; width: 1000px; ">
																	</td>
																</tr>
															</table>
															<table cellspacing="0" style="border-collapse: collapse;">
																<tr>
																	<td class="txtleft" style="width:50%;  padding:4px;"><b>Popolazione dei soggetti dello Studio</b></td>
																</tr>
																<tr>
																	<td style="">&nbsp;${setCheckbox("Feasibility" "FC9" "1" el)}&nbsp; Sesso</td>
																</tr>
																<tr>
																	<td class="txtleft" style="width:50%;  padding:4px;">&nbsp;</td>
																	<td class="txtleft" style="width:50%;  padding:4px;">
																		&nbsp;${setCheckbox("Feasibility" "FC9" "1" el)}&nbsp; Maschile
																		<br/>
																		&nbsp;${setCheckbox("Feasibility" "FC9" "1" el)}&nbsp; Femminile
																		<br/>
																	</td>
																</tr>
																<tr>
																	<td style="">&nbsp;${setCheckbox("Feasibility" "FC9" "1" el)}&nbsp; Et&agrave;</td>
																</tr>
																<tr>
																	<td class="txtleft" style="width:50%;  padding:4px;">&nbsp;</td>
																	<td class="txtleft" style="width:50%;  padding:4px;">
																		&nbsp;${setCheckbox("Feasibility" "FC9" "1" el)}&nbsp; Inferiore a 18 anni
																		<br/>
																		&nbsp;${setCheckbox("Feasibility" "FC9" "1" el)}&nbsp; Adulti (18-64)
																		<br/>
																		&nbsp;${setCheckbox("Feasibility" "FC9" "1" el)}&nbsp; Anziani ( >= 65 anni)
																		<br/>
																	</td>
																</tr>
																<tr>
																	<td style="">&nbsp;${setCheckbox("Feasibility" "FC9" "1" el)}&nbsp; Tipologia dei Soggetti</td>
																</tr>
																<tr>
																	<td class="txtleft" style="width:50%;  padding:4px;">&nbsp;</td>
																	<td class="txtleft" style="width:50%;  padding:4px;">
																		&nbsp;${setCheckbox("Feasibility" "FC9" "1" el)}&nbsp; Volontari sani
																		<br/>
																		Specificare le modalit&agrave; di arruolamento (dove e come):
																		<br/>&nbsp;${setCheckbox("Feasibility" "FC9" "1" el)}&nbsp; Pazienti
																		<br/>
																		&nbsp;${setCheckbox("Feasibility" "FC9" "1" el)}&nbsp; Donne in gravidanza e in allattamento
																		<br/>
																		&nbsp;${setCheckbox("Feasibility" "FC9" "1" el)}&nbsp; Incapaci di intendere e di volere
																		<br/>
																		&nbsp;${setCheckbox("Feasibility" "FC9" "1" el)}&nbsp; Soggetti vulnerabili <sup>2</sup>
																		<br/>
																		&nbsp;${setCheckbox("Feasibility" "FC9" "1" el)}&nbsp; Altro - specificare
																		<br/>
																	</td>
																</tr>
																<tr>
																	<td class="txtleft" style="width:50%;  padding:4px;"><b><u>Dati relativi allo Sperimentatore responsabile:</u></b></td>
																</tr>
																<tr>
																	<td class="txtleft" style="border: 1px solid black; width: 1000px; ">
																		Nome e Cognome
																	</td>
																	<td class="txtleft" style="border: 1px solid black; width: 1000px; ">
																		<#if datiPromotoreCRO?? >
																		${datiPromotoreCRO}
																	</#if>
																	</td>
																</tr>
																<tr>
																	<td class="txtleft" style="border: 1px solid black; width: 1000px; ">
																		Qualificca professionale
																	</td>
																	<td class="txtleft" style="border: 1px solid black; width: 1000px; ">
																		<#if datiPromotoreCRO?? >
																		${datiPromotoreCRO}
																	</#if>
																	</td>
																</tr>
																<tr>
																	<td class="txtleft" style="border: 1px solid black; width: 1000px; ">
																		Unit&agrave; Operativa
																	</td>
																	<td class="txtleft" style="border: 1px solid black; width: 1000px; ">
																		<#if datiPromotoreCRO?? >
																		${datiPromotoreCRO}
																	</#if>
																	</td>
																</tr>
																<tr>
																	<td class="txtleft" style="border: 1px solid black; width: 1000px; ">
																		Dipartimento ad Attivit&agrave; Integrata
																	</td>
																	<td class="txtleft" style="border: 1px solid black; width: 1000px; ">
																		<#if datiPromotoreCRO?? >
																		${datiPromotoreCRO}
																	</#if>
																	</td>
																</tr>
																<tr>
																	<td class="txtleft" style="border: 1px solid black; width: 1000px; ">
																		Dipartimento Universitario
																	</td>
																	<td class="txtleft" style="border: 1px solid black; width: 1000px; ">
																		<#if datiPromotoreCRO?? >
																		${datiPromotoreCRO}
																	</#if>
																	</td>
																</tr>
																<tr>
																	<td>&nbsp; </td>
																</tr>
																<tr>
																	<td class="txtleft" style="width:50%;  padding:4px;"><b><u>Informazioni relative a PROMOTORE, CRO, FINANZIATORE / SUPPLIER </u></b> </td>
																</tr>
															</table>
															<table cellspacing="0" style="border-collapse: collapse;">
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
																<tr>
																	<td class="txtleft" style="border: 1px solid black; width: 1000px; ">
																		<b><em>PROMOTORE</em></b>
																	</td>
																	<td class="txtleft" style="border: 1px solid black; width: 1000px; ">
																		<b><em>&nbsp;</em></b>
																	</td>
																	<td class="txtleft" style="border: 1px solid black; width: 1000px; ">
																		<b>&nbsp;</b>
																	</td>
																	<td class="txtleft" style="border: 1px solid black; width: 1000px; ">
																		<b>&nbsp;</b>
																	</td>
																	<td class="txtleft" style="border: 1px solid black; width: 1000px; ">
																		<b>&nbsp;</b>
																	</td>
																</tr>
																<tr>
																	<td class="txtleft" style="border: 1px solid black; width: 1000px; ">
																		<b><em>CRO (se prevista)</em></b>
																	</td>
																	<td class="txtleft" style="border: 1px solid black; width: 1000px; ">
																		<b><em>&nbsp;</em></b>
																	</td>
																	<td class="txtleft" style="border: 1px solid black; width: 1000px; ">
																		<b>&nbsp;</b>
																	</td>
																	<td class="txtleft" style="border: 1px solid black; width: 1000px; ">
																		<b>&nbsp;</b>
																	</td>
																	<td class="txtleft" style="border: 1px solid black; width: 1000px; ">
																		<b>&nbsp;</b>
																	</td>
																</tr>
																<tr>
																	<td class="txtleft" style="border: 1px solid black; width: 1000px; ">
																		<b><em>FINANZIATORE/SUPPLIER (se previsto)</em></b>
																	</td>
																	<td class="txtleft" style="border: 1px solid black; width: 1000px; ">
																		<b><em>&nbsp;</em></b>
																	</td>
																	<td class="txtleft" style="border: 1px solid black; width: 1000px; ">
																		<b>&nbsp;</b>
																	</td>
																	<td class="txtleft" style="border: 1px solid black; width: 1000px; ">
																		<b>&nbsp;</b>
																	</td>
																	<td class="txtleft" style="border: 1px solid black; width: 1000px; ">
																		<b>&nbsp;</b>
																	</td>
																</tr>
															</table>
															<table cellspacing="0" style="border-collapse: collapse;">
															<tr>
																<td class="txtleft" style="border: 1px solid black; width: 1000px; ">
																	Specificare a chi e' affidata l'attivit&agrave; di monitoraggio clinico dello studio:<br/>
																	Nota: si ricorda che il monitoraggio dello studio e' a cura del Promotore, che lo puo' svolgere direttamente oppure delegando un terzo soggetto
																</td>
																<td class="txtleft" style="border: 1px solid black; width: 1000px; ">
																	<#if datiPromotoreCRO?? >
																		${datiPromotoreCRO}
																	</#if>
																</td>
															</tr>
															<tr>
																<td class="txtleft" style="width:50%;  padding:4px;"><b>Soggetti in regime:</b></td>
															</tr>
															<tr>
																<td class="txtleft" style="border: 1px solid black; width: 1000px;">Ambulatoriale </td>
																<td class="txtleft" style="width:50%;  padding:4px;">
																	&nbsp;${setCheckbox("Feasibility" "FC9" "1" el)}&nbsp; Si'
																	&nbsp;${setCheckbox("Feasibility" "FC9" "1" el)}&nbsp; No
																	<br/>
																</td>
															</tr>
															<tr>
																<td class="txtleft" style="border: 1px solid black; width: 1000px;">di Ricovero </td>
																<td class="txtleft" style="width:50%;  padding:4px;">
																	&nbsp;${setCheckbox("Feasibility" "FC9" "1" el)}&nbsp; Si'
																	&nbsp;${setCheckbox("Feasibility" "FC9" "1" el)}&nbsp; No
																	<br/>
																</td>
															</tr>
															<tr>
																<td class="txtleft" style="border: 1px solid black; width: 1000px;">Day Surgery/One Day Surgery </td>
																<td class="txtleft" style="width:50%;  padding:4px;">
																	&nbsp;${setCheckbox("Feasibility" "FC9" "1" el)}&nbsp; Si'
																	&nbsp;${setCheckbox("Feasibility" "FC9" "1" el)}&nbsp; No
																	<br/>
																</td>
															</tr>
															<tr>
																<td class="txtleft" style="border: 1px solid black; width: 1000px;">Day Service </td>
																<td class="txtleft" style="width:50%;  padding:4px;">
																	&nbsp;${setCheckbox("Feasibility" "FC9" "1" el)}&nbsp; Si'
																	&nbsp;${setCheckbox("Feasibility" "FC9" "1" el)}&nbsp; No
																	<br/>
																</td>
															</tr>
															<tr>
																<td class="txtleft" style="border: 1px solid black; width: 1000px;">Se non applicabile, specificare: </td>
																<td class="txtleft" style="width:50%;  padding:4px;"></td>
															</tr>
															<tr>
																<td>&nbsp; </td>
															</tr>
															<tr>
																<td class="txtleft" style="width:50%;  padding:4px;"><b>Personale direttamente coinvolto nel team dello studio</b>(compreso lo Sperimentatore Responsabile dello studio)<b> presso la struttura/UO proponente</b></td>
															</tr>
														</table>
														<table cellspacing="0" style="border-collapse: collapse;">
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
															<tr>
																<td class="txtleft" style="border: 1px solid black; width: 1000px; ">
																	<b><em>&nbsp;</em></b>
																</td>
																<td class="txtleft" style="border: 1px solid black; width: 1000px; ">
																	<b><em>&nbsp;</em></b>
																</td>
																<td class="txtleft" style="border: 1px solid black; width: 1000px; ">
																	<b>&nbsp;</b>
																</td>
																<td class="txtleft" style="border: 1px solid black; width: 1000px; ">
																	<b>&nbsp;</b>
																</td>
																<td class="txtleft" style="border: 1px solid black; width: 1000px; ">
																	<b>&nbsp;</b>
																</td>
																<td class="txtleft" style="border: 1px solid black; width: 1000px; ">
																	&nbsp;${setCheckbox("Feasibility" "FC9" "1" el)}Si'
																&nbsp;${setCheckbox("Feasibility" "FC9" "1" el)}No
																</td>
															</tr>
															<tr>
																<td class="txtleft" style="border: 1px solid black; width: 1000px; ">
																	<b><em>&nbsp;</em></b>
																</td>
																<td class="txtleft" style="border: 1px solid black; width: 1000px; ">
																	<b><em>&nbsp;</em></b>
																</td>
																<td class="txtleft" style="border: 1px solid black; width: 1000px; ">
																	<b>&nbsp;</b>
																</td>
																<td class="txtleft" style="border: 1px solid black; width: 1000px; ">
																	<b>&nbsp;</b>
																</td>
																<td class="txtleft" style="border: 1px solid black; width: 1000px; ">
																	<b>&nbsp;</b>
																</td>
																<td class="txtleft" style="border: 1px solid black; width: 1000px; ">
																	&nbsp;${setCheckbox("Feasibility" "FC9" "1" el)}Si'
																&nbsp;${setCheckbox("Feasibility" "FC9" "1" el)}No
																</td>
															</tr>
															<tr>
																<td class="txtleft" style="border: 1px solid black; width: 1000px; ">
																	<b><em>&nbsp;</em></b>
																</td>
																<td class="txtleft" style="border: 1px solid black; width: 1000px; ">
																	<b><em>&nbsp;</em></b>
																</td>
																<td class="txtleft" style="border: 1px solid black; width: 1000px; ">
																	<b>&nbsp;</b>
																</td>
																<td class="txtleft" style="border: 1px solid black; width: 1000px; ">
																	<b>&nbsp;</b>
																</td>
																<td class="txtleft" style="border: 1px solid black; width: 1000px; ">
																	<b>&nbsp;</b>
																</td>
																<td class="txtleft" style="border: 1px solid black; width: 1000px; ">
																	&nbsp;${setCheckbox("Feasibility" "FC9" "1" el)}Si'
																&nbsp;${setCheckbox("Feasibility" "FC9" "1" el)}No
																</td>
															</tr>
															<tr>
																<td class="txtleft" style="border: 1px solid black; width: 1000px; ">
																	<b><em>&nbsp;</em></b>
																</td>
																<td class="txtleft" style="border: 1px solid black; width: 1000px; ">
																	<b><em>&nbsp;</em></b>
																</td>
																<td class="txtleft" style="border: 1px solid black; width: 1000px; ">
																	<b>&nbsp;</b>
																</td>
																<td class="txtleft" style="border: 1px solid black; width: 1000px; ">
																	<b>&nbsp;</b>
																</td>
																<td class="txtleft" style="border: 1px solid black; width: 1000px; ">
																	<b>&nbsp;</b>
																</td>
																<td class="txtleft" style="border: 1px solid black; width: 1000px; ">
																	&nbsp;${setCheckbox("Feasibility" "FC9" "1" el)}Si'
																&nbsp;${setCheckbox("Feasibility" "FC9" "1" el)}No
																</td>
															</tr>
														</table>
														<table cellspacing="0" style="border-collapse: collapse;">
															<tr>
																<td class="txtleft" style="width:50%;  padding:4px;"><b>N.B.</b> Per lo svolgimento o la partecipazione alle attivit&agrave; cliniche dello studio e' sempre necessaria l'esistenza di un valido ed efficace titolo allo svolgimento dell'attivit&agrave; presso la struttura.</td>
															</tr>
															<tr>
																<td class="txtleft" style="width:50%;  padding:4px;"><b>*</b> Specificare se medico, infermiere, farmacista, biologo, data manager, etc.
																<br/> <b>**</b> Specificare se dipendente Ospedaliero, dipendendte universitario con integrazione assistenziale, medico in formazione, assegnista, libero professionista, dottorando, borsista, etc.</td>
															</tr>
														</table>
														<table cellspacing="0" style="border-collapse: collapse;">
															<tr>
																<td style="width:50%; font-weight: bold; padding-left:10px;">SEZIONE B: Modulo per l'analisi dei costi aggiuntivi correlati allo Studio</td>
															</tr>
															<tr>
																<td style="width:50%; font-weight: bold; padding-left:10px;">Altro personale coinvolto (dirigenza e comparto) presso strutture/UO diverse da quella proponente che collaborano con la UO proponente per lo svolgimento di prestazioni studio-specifiche.</td>
															</tr>
															<tr>
																<td class="txtleft" style="border: 1px solid black; width: 1000px;">Per l'espletamento del presente studio deve essere coinvolto altro personale? </td>
																<td class="txtleft" style="width:50%;  padding:4px;">
																	&nbsp;${setCheckbox("Feasibility" "FC9" "1" el)}&nbsp; Si'
																	&nbsp;${setCheckbox("Feasibility" "FC9" "1" el)}&nbsp; No
																	<br/>
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
															<tr>
																<td class="txtleft" style="border: 1px solid black; width: 1000px; ">
																	<b><em>1</em></b>
																</td>
																<td class="txtleft" style="border: 1px solid black; width: 1000px; ">
																	<b><em></em></b>
																</td>
																<td class="txtleft" style="border: 1px solid black; width: 1000px; ">
																	<b><em></em></b>
																</td>
															</tr>
															<tr>
																<td class="txtleft" style="border: 1px solid black; width: 1000px; ">
																	<b><em>2</em></b>
																</td>
																<td class="txtleft" style="border: 1px solid black; width: 1000px; ">
																	<b><em>&nbsp;</em></b>
																</td>
																<td class="txtleft" style="border: 1px solid black; width: 1000px; ">
																	<b>&nbsp;</b>
																</td>
															</tr>
															<tr>
																<td class="txtleft" style="border: 1px solid black; width: 1000px; ">
																	<b><em>3</em></b>
																</td>
																<td class="txtleft" style="border: 1px solid black; width: 1000px; ">
																	<b><em>&nbsp;</em></b>
																</td>
																<td class="txtleft" style="border: 1px solid black; width: 1000px; ">
																	<b>&nbsp;</b>
																</td>
															</tr>
															<tr>
																<td class="txtleft" style="border: 1px solid black; width: 1000px; ">
																	<b><em>...</em></b>
																</td>
																<td class="txtleft" style="border: 1px solid black; width: 1000px; ">
																	<b><em>&nbsp;</em></b>
																</td>
																<td class="txtleft" style="border: 1px solid black; width: 1000px; ">
																	<b>&nbsp;</b>
																</td>
															</tr>
														</table>
															<table cellspacing="0" style="border-collapse: collapse;">
															<tr>
																<td class="txtcenter" style="width:50%;  padding:4px;"><b>Allegare la dichiarazione di attestazione del coinvolgimento sottoscritta dal relativo Responsabile</b></td>
															</tr>
															<tr>
																<td class="txtcenter"><b>COSTI AGGIUNTIVI</b></td>
															</tr>
															<tr>
																<td class="txtleft" style="width:50%;  padding:4px;">"I medicinali sperimentali ed eventualmente i dispositivi udati per somministrarli sono forniti gratuitamente dal promotore dello studio profit; nessun costo aggiuntivo, per la conduzione e la gestione degli studi di cui al presente decreto deve gravare sulla finanza pubblica": decreto legislativo 24.06.2003, n.211 - art. 20, comma 2.
																<br/><br/>Relativamente agli studi no profit finalizati al miglioramento della pratica clinica ex art. 6 del D.M. 17/12/2004, i farmaci sono a carico del SSN, mentre le eventuali spese aggiuntive, comprese quelle per il farmaco sperimentale, qualora non coperte da fondi di ricerca ad hoc possono gravare sul Fondo della Ricerca di cui all'art. 2, comma 3 del citato Decreto, sempre che si tratti di studi promossi dalla Struttura.</td>
																<br/><br/>Relativamente agli studi no profit NON finalizzati al miglioramento della pratica clinica ex art. 6 del D.M. 17/12/2004, i promotori devono garantire la fornitura dei farmaci sperimentali, il rimborso dei farmaci con AIC se il relativo utilizzo &egrave; richiesto dal protocollo di studio e la copertura delle spese aggintive.
															</tr>
															<tr>
																<td class="txtcenter" style="width:50%;  padding:4px;"><b><u>Materiale Sperimentale </u></b></td>
															</tr>
															<tr>
																<td class="txtleft" style="width:50%;  padding:4px;"><b>Se trattasi di studio interventistico di farmaco</b></td>
															</tr>
															</table>
															<table cellspacing="0" style="border-collapse: collapse;">
																<tr style="background-color:#eee;">
																	<th class="txtcenter" style="border: 1px solid black; width: 1000px; ">
																		<b>Elenco Farmaci Sperimentali (IMP, PeIMP)</b>
																	</th>
																	<th class="txtcenter" style="border: 1px solid black; width: 1000px; ">
																		<b>ATC</b>
																	</th>
																	<th class="txtcenter" style="border: 1px solid black; width: 1000px; ">
																		<b>Codice modalit&agrave; copertura oneri finanziari (A, B, C, D)</b>
																	</th>
																</tr>
																<tr>
																	<td class="txtleft" style="border: 1px solid black; width: 1000px; ">
																		<b><em>&nbsp;</em></b>
																	</td>
																	<td class="txtleft" style="border: 1px solid black; width: 1000px; ">
																		<b><em>&nbsp;</em></b>
																	</td>
																	<td class="txtleft" style="border: 1px solid black; width: 1000px; ">
																		<b>&nbsp;</b>
																	</td>
																</tr>
																<tr>
																	<td class="txtleft" style="border: 1px solid black; width: 1000px; ">
																		<b><em>&nbsp;</em></b>
																	</td>
																	<td class="txtleft" style="border: 1px solid black; width: 1000px; ">
																		<b><em>&nbsp;</em></b>
																	</td>
																	<td class="txtleft" style="border: 1px solid black; width: 1000px; ">
																		<b>&nbsp;</b>
																	</td>
																</tr>
																<tr>
																	<td class="txtleft" style="border: 1px solid black; width: 1000px; ">
																		<b><em>&nbsp;</em></b>
																	</td>
																	<td class="txtleft" style="border: 1px solid black; width: 1000px; ">
																		<b><em>&nbsp;</em></b>
																	</td>
																	<td class="txtleft" style="border: 1px solid black; width: 1000px; ">
																		<b>&nbsp;</b>
																	</td>
																</tr>
																<tr>
																	<td class="txtleft" style="border: 1px solid black; width: 1000px; ">
																		<b><em>&nbsp;</em></b>
																	</td>
																	<td class="txtleft" style="border: 1px solid black; width: 1000px; ">
																		<b><em>&nbsp;</em></b>
																	</td>
																	<td class="txtleft" style="border: 1px solid black; width: 1000px; ">
																		<b>&nbsp;</b>
																	</td>
																</tr>
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
															<tr>
																<td class="txtleft" style="width:50%;  padding:4px;"><b>Se trattasi di indagine clinica di dispositivo medico</b></td>
															</tr>
															</table>
															<table cellspacing="0" style="border-collapse: collapse;">
																<tr style="background-color:#eee;">
																	<th class="txtcenter" style="border: 1px solid black; width: 1000px; ">
																		<b>Elenco DM Sperimentali (IMP, PeIMP)</b>
																	</th>
																	<th class="txtcenter" style="border: 1px solid black; width: 1000px; ">
																		<b>Marchio CE e N. Repertorio</b>
																	</th>
																	<th class="txtcenter" style="border: 1px solid black; width: 1000px; ">
																		<b>Impiego secondo destinazione d'uso</b>
																	</th>
																	<th class="txtcenter" style="border: 1px solid black; width: 1000px; ">
																		<b>Classe di rischio</b>
																	</th>
																	<th class="txtcenter" style="border: 1px solid black; width: 1000px; ">
																		<b>Fabbricante</b>
																	</th>
																	<th class="txtcenter" style="border: 1px solid black; width: 1000px; ">
																		<b>DM gi&agrave; in uso in Azienda?</b>
																	</th>
																	<th class="txtcenter" style="border: 1px solid black; width: 1000px; ">
																		<b>Codice modalit&agrave; copertura oneri finanziari (A, B, C, D)</b>
																	</th>
																</tr>
																<tr>
																	<td class="txtleft" style="border: 1px solid black; width: 1000px; ">
																		<b><em>&nbsp;</em></b>
																	</td>
																	<td class="txtleft" style="border: 1px solid black; width: 1000px; ">
																		<b><em>&nbsp;</em></b>
																	</td>
																	<td class="txtleft" style="border: 1px solid black; width: 1000px; ">
																		<b>&nbsp;</b>
																	</td>
																	<td class="txtleft" style="border: 1px solid black; width: 1000px; ">
																		<b><em>&nbsp;</em></b>
																	</td>
																	<td class="txtleft" style="border: 1px solid black; width: 1000px; ">
																		<b><em>&nbsp;</em></b>
																	</td>
																	<td class="txtleft" style="border: 1px solid black; width: 1000px; ">
																		<b><em>&nbsp;</em></b>
																	</td>
																	<td class="txtleft" style="border: 1px solid black; width: 1000px; ">
																		<b><em>&nbsp;</em></b>
																	</td>
																</tr>
																<tr>
																	<td class="txtleft" style="border: 1px solid black; width: 1000px; ">
																		<b><em>&nbsp;</em></b>
																	</td>
																	<td class="txtleft" style="border: 1px solid black; width: 1000px; ">
																		<b><em>&nbsp;</em></b>
																	</td>
																	<td class="txtleft" style="border: 1px solid black; width: 1000px; ">
																		<b>&nbsp;</b>
																	</td>
																	<td class="txtleft" style="border: 1px solid black; width: 1000px; ">
																		<b><em>&nbsp;</em></b>
																	</td>
																	<td class="txtleft" style="border: 1px solid black; width: 1000px; ">
																		<b><em>&nbsp;</em></b>
																	</td>
																	<td class="txtleft" style="border: 1px solid black; width: 1000px; ">
																		<b><em>&nbsp;</em></b>
																	</td>
																	<td class="txtleft" style="border: 1px solid black; width: 1000px; ">
																		<b><em>&nbsp;</em></b>
																	</td>
																</tr>
																<tr>
																	<td class="txtleft" style="border: 1px solid black; width: 1000px; ">
																		<b><em>&nbsp;</em></b>
																	</td>
																	<td class="txtleft" style="border: 1px solid black; width: 1000px; ">
																		<b><em>&nbsp;</em></b>
																	</td>
																	<td class="txtleft" style="border: 1px solid black; width: 1000px; ">
																		<b>&nbsp;</b>
																	</td>
																	<td class="txtleft" style="border: 1px solid black; width: 1000px; ">
																		<b><em>&nbsp;</em></b>
																	</td>
																	<td class="txtleft" style="border: 1px solid black; width: 1000px; ">
																		<b><em>&nbsp;</em></b>
																	</td>
																	<td class="txtleft" style="border: 1px solid black; width: 1000px; ">
																		<b><em>&nbsp;</em></b>
																	</td>
																	<td class="txtleft" style="border: 1px solid black; width: 1000px; ">
																		<b><em>&nbsp;</em></b>
																	</td>
																</tr>
																<tr>
																	<td class="txtleft" style="border: 1px solid black; width: 1000px; ">
																		<b><em>&nbsp;</em></b>
																	</td>
																	<td class="txtleft" style="border: 1px solid black; width: 1000px; ">
																		<b><em>&nbsp;</em></b>
																	</td>
																	<td class="txtleft" style="border: 1px solid black; width: 1000px; ">
																		<b>&nbsp;</b>
																	</td>
																	<td class="txtleft" style="border: 1px solid black; width: 1000px; ">
																		<b><em>&nbsp;</em></b>
																	</td>
																	<td class="txtleft" style="border: 1px solid black; width: 1000px; ">
																		<b><em>&nbsp;</em></b>
																	</td>
																	<td class="txtleft" style="border: 1px solid black; width: 1000px; ">
																		<b><em>&nbsp;</em></b>
																	</td>
																	<td class="txtleft" style="border: 1px solid black; width: 1000px; ">
																		<b><em>&nbsp;</em></b>
																	</td>
																</tr>
															</table>
															<table cellspacing="0" style="border-collapse: collapse;">
																<tr>
																	<td style="width:50%;  padding-left:10px;"><b>A=</b> a carico del Promotore in quanto non gi&agrave; in uso nel centro (art.2, comma 1 lettera t) punto 8 del D. Lgs. n.37 del 25/01/2010 "...Le spese ulteriori rispetto alla normale pratica clinica, derivanti dall'applicazione del presente comma, sono a carico del fabbricante. I dispositivi medici occorrenti per le indagini cliniche, che non sono gi&agrave; stati acuisiti nel rispetto delle ordinarie procedure di fornitura dei beni, sono altresi' a carico del fabbricante..."
																	<br/><b>B=</b> a carico di fondi della Unit&agrave; Operativa a disposizione dello Sperimentatore <sup>*</sup> - specificare il codice identificativo del fondo, se presente
																	<br/><b>C=</b> fornitura/finanziamento preoveniente da terzi (in tal caso allegare l'accordo tra Promotore e finanziatore terzo che regolamenta la fornitura/il contributo economico)
																	<br/><b>D=</b> a carico del Fondo Aziendale per la Ricerca, ove presente **</td>

																</tr>
																<tr>
																	<td style="width:50%;  padding-left:10px;">* Applicabile solo per studi no profit
																	<br/> ** Applicabile solo per studi no profit finalizzati al miglioramento della pratica clinica</td>
																</tr>
																<tr>
																	<td class="txtleft" style="border: 1px solid black; width: 1000px;"><b>Altro materiale sperimentale (specificare, ad es. integratore)</b></td>
																	<td class="txtleft" style="width:50%;  padding:4px;">
																		&nbsp;${setCheckbox("Feasibility" "FC9" "1" el)}&nbsp; Si'
																		&nbsp;${setCheckbox("Feasibility" "FC9" "1" el)}&nbsp; No
																		<br/>
																	</td>
																</tr>
																<tr>
																	<td style="width:50%;  padding-left:10px;">* Descrizione:</td>
																</tr>
																<tr>
																	<td class="txtcenter" style="width:50%;  padding:4px;"><b><u>Attrezzature a supporto e non oggetto di studio:</u></b></td>
																</tr>
																<tr>
																	<td class="txtleft" style="border: 1px solid black; width: 1000px;"><b>Fornitura di beni in comodato</b></td>
																	<td class="txtleft" style="width:50%;  padding:4px;">
																		&nbsp;${setCheckbox("Feasibility" "FC9" "1" el)}&nbsp; Si'
																		&nbsp;${setCheckbox("Feasibility" "FC9" "1" el)}&nbsp; No
																		<br/>
																	</td>
																</tr>
																<tr>
																	<td style="width:50%;  padding-left:10px;">* Descrizione:</td>
																</tr>
																<tr>
																	<td class="txtleft" style="border: 1px solid black; width: 1000px;">Marcato CE</td>
																	<td class="txtleft" style="width:50%;  padding:4px;">
																		&nbsp;${setCheckbox("Feasibility" "FC9" "1" el)}&nbsp; Si'
																		&nbsp;${setCheckbox("Feasibility" "FC9" "1" el)}&nbsp; No
																		&nbsp;${setCheckbox("Feasibility" "FC9" "1" el)}&nbsp; Non applicabile
																		<br/>
																	</td>
																</tr>
																<tr>
																	<td class="txtleft" style="border: 1px solid black; width: 1000px;"><b>Numero Repertorio generale dei dispositivi medici commercializzati in Italia (RDM)</b></td>
																	<td class="txtleft" style="width:50%;  padding:4px;">
																		&nbsp;${setCheckbox("Feasibility" "FC9" "1" el)}&nbsp; Si'
																		&nbsp;${setCheckbox("Feasibility" "FC9" "1" el)}&nbsp; No
																		&nbsp;${setCheckbox("Feasibility" "FC9" "1" el)}&nbsp; Non applicabile
																		<br/>
																	</td>
																</tr>
																<tr>
																	<td class="txtleft" style="border: 1px solid black; width: 1000px;"><b>Prestazioni aggiuntive studio-specifiche</b></td>
																	<td class="txtleft" style="width:50%;  padding:4px;">
																		&nbsp;${setCheckbox("Feasibility" "FC9" "1" el)}&nbsp; Si'
																		&nbsp;${setCheckbox("Feasibility" "FC9" "1" el)}&nbsp; No
																		<br/>
																	</td>
																</tr>
																<tr>
																	<td style="width:50%;  padding-left:10px;">Se lo studio prevede l'esecuzione di prestazioni specialistiche aggiuntive rispetto alla pratica clinica (es. ricoveri, visite, esami strumentali o di laboratorio), incluse quelle previste
																	per l'arruolamento, come da flow-chart dello studio, elencarle di seguito ed indicare per ognuna di esse la quantit&agrave;, la corrispondente tariffa come da
																	Nomenclatore Regionale, nonche' le modalit&agrave; proposte per la copertura del relativo costo, come da codici indicati:
																	<br/> <b>N.B.:</b> come previsto dalle Linee guida per la classificazione e conduzione degli studi osservazionali sui farmaci (Determina AIFA del 20/03/2008), nell'ambito di uno studio osservaionale <i> le procedure diagnostiche e valutative devono
																	corrispondere alla pratica clinica corrente.</i></td>
																</tr>
																<tr>
																	<td style="width:50%;  padding-left:10px;"><b>Prestazioni/attivit&agrave; aggiuntive della struttura ove si conduce lo studio e/o di altre strutture dell'Azienda</b> (E' possibile allegare una flow-chart come materiale integrativo alla tabella che va comunque compilata. Il numero di prestazioni e' previsionale, secondo protocollo)</td>
																</tr>
															</table>
															<table cellspacing="0" style="border-collapse: collapse;">
																<tr style="background-color:#eee;">
																	<th class="txtcenter" style="border: 1px solid black; width: 1000px; ">
																		<b>Servizi/Sezioni coinvolti (Struttura erogante) <sup>1</sup></b>
																	</th>
																	<th class="txtcenter" style="border: 1px solid black; width: 1000px; ">
																		<b>Codice Prestazione: (ICDX-CM)<sup>2</sup></b>
																	</th>
																	<th class="txtcenter" style="border: 1px solid black; width: 1000px; ">
																		<b>Descrizione</b>
																	</th>
																	<th class="txtcenter" style="border: 1px solid black; width: 1000px; ">
																		<b>Tariffa da nomenclatore <sup>3</sup></b>
																	</th>
																	<th class="txtcenter" style="border: 1px solid black; width: 1000px; ">
																		<b>Tariffa Prestazione</b>
																	</th>
																	<th class="txtcenter" style="border: 1px solid black; width: 1000px; ">
																		<b>N. Prest./Paziente</b>
																	</th>
																	<th class="txtcenter" style="border: 1px solid black; width: 1000px; ">
																		<b>Codice modalit&agrave; copertura oneri finanziari (A, B, C, D, E)</b>
																	</th>
																</tr>
																<tr>
																	<td class="txtleft" style="border: 1px solid black; width: 1000px; ">
																		<b><em>&nbsp;</em></b>
																	</td>
																	<td class="txtleft" style="border: 1px solid black; width: 1000px; ">
																		<b><em>&nbsp;</em></b>
																	</td>
																	<td class="txtleft" style="border: 1px solid black; width: 1000px; ">
																		<b>&nbsp;</b>
																	</td>
																	<td class="txtleft" style="border: 1px solid black; width: 1000px; ">
																		<b><em>&nbsp;</em></b>
																	</td>
																	<td class="txtleft" style="border: 1px solid black; width: 1000px; ">
																		<b><em>&nbsp;</em></b>
																	</td>
																	<td class="txtleft" style="border: 1px solid black; width: 1000px; ">
																		<b><em>&nbsp;</em></b>
																	</td>
																	<td class="txtleft" style="border: 1px solid black; width: 1000px; ">
																		<b><em>&nbsp;</em></b>
																	</td>
																</tr>
																<tr>
																	<td class="txtleft" style="border: 1px solid black; width: 1000px; ">
																		<b><em>&nbsp;</em></b>
																	</td>
																	<td class="txtleft" style="border: 1px solid black; width: 1000px; ">
																		<b><em>&nbsp;</em></b>
																	</td>
																	<td class="txtleft" style="border: 1px solid black; width: 1000px; ">
																		<b>&nbsp;</b>
																	</td>
																	<td class="txtleft" style="border: 1px solid black; width: 1000px; ">
																		<b><em>&nbsp;</em></b>
																	</td>
																	<td class="txtleft" style="border: 1px solid black; width: 1000px; ">
																		<b><em>&nbsp;</em></b>
																	</td>
																	<td class="txtleft" style="border: 1px solid black; width: 1000px; ">
																		<b><em>&nbsp;</em></b>
																	</td>
																	<td class="txtleft" style="border: 1px solid black; width: 1000px; ">
																		<b><em>&nbsp;</em></b>
																	</td>
																</tr>
																<tr>
																	<td class="txtleft" style="border: 1px solid black; width: 1000px; ">
																		<b><em>&nbsp;</em></b>
																	</td>
																	<td class="txtleft" style="border: 1px solid black; width: 1000px; ">
																		<b><em>&nbsp;</em></b>
																	</td>
																	<td class="txtleft" style="border: 1px solid black; width: 1000px; ">
																		<b>&nbsp;</b>
																	</td>
																	<td class="txtleft" style="border: 1px solid black; width: 1000px; ">
																		<b><em>&nbsp;</em></b>
																	</td>
																	<td class="txtleft" style="border: 1px solid black; width: 1000px; ">
																		<b><em>&nbsp;</em></b>
																	</td>
																	<td class="txtleft" style="border: 1px solid black; width: 1000px; ">
																		<b><em>&nbsp;</em></b>
																	</td>
																	<td class="txtleft" style="border: 1px solid black; width: 1000px; ">
																		<b><em>&nbsp;</em></b>
																	</td>
																</tr>
																<tr>
																	<td class="txtleft" style="border: 1px solid black; width: 1000px; ">
																		<b><em>&nbsp;</em></b>
																	</td>
																	<td class="txtleft" style="border: 1px solid black; width: 1000px; ">
																		<b><em>&nbsp;</em></b>
																	</td>
																	<td class="txtleft" style="border: 1px solid black; width: 1000px; ">
																		<b>&nbsp;</b>
																	</td>
																	<td class="txtleft" style="border: 1px solid black; width: 1000px; ">
																		<b><em>&nbsp;</em></b>
																	</td>
																	<td class="txtleft" style="border: 1px solid black; width: 1000px; ">
																		<b><em>&nbsp;</em></b>
																	</td>
																	<td class="txtleft" style="border: 1px solid black; width: 1000px; ">
																		<b><em>&nbsp;</em></b>
																	</td>
																	<td class="txtleft" style="border: 1px solid black; width: 1000px; ">
																		<b><em>&nbsp;</em></b>
																	</td>
																</tr>
															</table>
															<table cellspacing="0" style="border-collapse: collapse;">
																<tr>
																	<td style="width:50%;  padding-left:10px;"><sup>1</sup> propone l'elenco di strutture inserite in precedenza nella sezione B
																	<br/> <sup>2</sup> "ICDX-CM" da utilizzare solo per la USL/IRCSS di Reggio Emilia
																	<br/> <sup>3</sup> scegliendo il Codice Prestazione, vengono compilate Descrizione e Tariffa da nomenclatore in automatico</td>
																</tr>
																<tr>
																	<td style="width:50%;  padding-left:10px;"><b>A=</b> a carico del Promotore compreso nel corrispettivo offerto
																	<br/><b>B=</b> a carico del Promotore da addebitare in aggiunta al corrispettivo offerto
																	<br/><b>C=</b> a carico di fondi dell'Unit&agrave; Operativa a disposizione dello Sperimentatore *- <i>specificare il codice identificativo del fondo, se presente </i>
																	<br/><b>D=</b> finanziamento proveniente da terzi (in tal caso allegare l'accordo tra Promotore e finanziatore terzo che regolamenta il contributo economico)
																	<br/><b>E=</b> a carico del Fondo Aziendale per la Ricerca, ove presente **</td>

																</tr>
																<tr>
																	<td style="width:50%;  padding-left:10px;">* Applicabile solo per studi no profit
																	<br/> ** Applicabile solo per studi no profit finalizzati al miglioramento della pratica clinica</td>
																</tr>
																<tr>
																	<td style="width:50%;  padding-left:10px;"><b>Altri servizi aggiuntivi studio specifici, se presenti</b></td>
																</tr>
															</table>
															<table cellspacing="0" style="border-collapse: collapse;">
																<tr style="background-color:#eee;">
																	<th class="txtcenter" style="border: 1px solid black; width: 1000px; ">
																		<b>Descrizione</b>
																	</th>
																	<th class="txtcenter" style="border: 1px solid black; width: 1000px; ">
																		<b>Previsto (Si'/No)</b>
																	</th>
																	<th class="txtcenter" style="border: 1px solid black; width: 1000px; ">
																		<b>Codice Modalit&agrave; Copertura Oneri Finanziari (A, B, C, D)</b>
																	</th>
																	<th class="txtcenter" style="border: 1px solid black; width: 1000px; ">
																		<b>Importo totale</b>
																	</th>
																</tr>
																<tr>
																	<td class="txtleft" style="border: 1px solid black; width: 1000px; ">
																		<b><em>Collaudo dispositivi forniti in comodato d'uso</em></b>
																	</td>
																	<td class="txtleft" style="border: 1px solid black; width: 1000px; ">
																		<b><em>&nbsp;</em></b>
																	</td>
																	<td class="txtleft" style="border: 1px solid black; width: 1000px; ">
																		<b>&nbsp;</b>
																	</td>
																	<td class="txtleft" style="border: 1px solid black; width: 1000px; ">
																		<b><em>&nbsp;</em></b>
																	</td>
																</tr>
																<tr>
																	<td class="txtleft" style="border: 1px solid black; width: 1000px; ">
																		<b><em>Registrazione su CD anonimizzati di immagini di esami</em></b>
																	</td>
																	<td class="txtleft" style="border: 1px solid black; width: 1000px; ">
																		<b><em>&nbsp;</em></b>
																	</td>
																	<td class="txtleft" style="border: 1px solid black; width: 1000px; ">
																		<b>&nbsp;</b>
																	</td>
																	<td class="txtleft" style="border: 1px solid black; width: 1000px; ">
																		<b><em>&nbsp;</em></b>
																	</td>
																</tr>
																<tr>
																	<td class="txtleft" style="border: 1px solid black; width: 1000px; ">
																		<b><em>Assicurazione (solo per studi no-profit con assicurazione a carico della struttura di riferimento)</em></b>
																	</td>
																	<td class="txtleft" style="border: 1px solid black; width: 1000px; ">
																		<b><em>&nbsp;</em></b>
																	</td>
																	<td class="txtleft" style="border: 1px solid black; width: 1000px; ">
																		<b>&nbsp;</b>
																	</td>
																	<td class="txtleft" style="border: 1px solid black; width: 1000px; ">
																		<b><em>&nbsp;</em></b>
																	</td>
																</tr>
																<tr>
																	<td class="txtleft" style="border: 1px solid black; width: 1000px; ">
																		<b><em>Compenso Farmacia</em></b>
																	</td>
																	<td class="txtleft" style="border: 1px solid black; width: 1000px; ">
																		<b><em>&nbsp;</em></b>
																	</td>
																	<td class="txtleft" style="border: 1px solid black; width: 1000px; ">
																		<b>&nbsp;</b>
																	</td>
																	<td class="txtleft" style="border: 1px solid black; width: 1000px; ">
																		<b><em>&nbsp;</em></b>
																	</td>
																</tr>
																<tr>
																	<td class="txtleft" style="border: 1px solid black; width: 1000px; ">
																		<b><em>Utilizzo di laboratorio esterno in cui viene centralizzata la valutazione di parametri previsti dallo studio</em></b>
																	</td>
																	<td class="txtleft" style="border: 1px solid black; width: 1000px; ">
																		<b><em>&nbsp;</em></b>
																	</td>
																	<td class="txtleft" style="border: 1px solid black; width: 1000px; ">
																		<b>&nbsp;</b>
																	</td>
																	<td class="txtleft" style="border: 1px solid black; width: 1000px; ">
																		<b><em>&nbsp;</em></b>
																	</td>
																</tr>
																<tr>
																	<td class="txtleft" style="border: 1px solid black; width: 1000px; ">
																		<b><em>Utilizzo di laboratorio esterno in cui viene centralizzata la valutazione di parametri previsti dallo studio</em></b>
																	</td>
																	<td class="txtleft" style="border: 1px solid black; width: 1000px; ">
																		<b><em>&nbsp;</em></b>
																	</td>
																	<td class="txtleft" style="border: 1px solid black; width: 1000px; ">
																		<b>&nbsp;</b>
																	</td>
																	<td class="txtleft" style="border: 1px solid black; width: 1000px; ">
																		<b><em>&nbsp;</em></b>
																	</td>
																</tr>
																<tr>
																	<td class="txtleft" style="border: 1px solid black; width: 1000px; ">
																		<b><em>Spedizione materiale/campioni biologici</em></b>
																	</td>
																	<td class="txtleft" style="border: 1px solid black; width: 1000px; ">
																		<b><em>&nbsp;</em></b>
																	</td>
																	<td class="txtleft" style="border: 1px solid black; width: 1000px; ">
																		<b>&nbsp;</b>
																	</td>
																	<td class="txtleft" style="border: 1px solid black; width: 1000px; ">
																		<b><em>&nbsp;</em></b>
																	</td>																</tr>
																<tr>
																	<td class="txtleft" style="border: 1px solid black; width: 1000px; ">
																		<b><em>Materiali consumabili</em></b>
																	</td>
																	<td class="txtleft" style="border: 1px solid black; width: 1000px; ">
																		<b><em>&nbsp;</em></b>
																	</td>
																	<td class="txtleft" style="border: 1px solid black; width: 1000px; ">
																		<b>&nbsp;</b>
																	</td>
																	<td class="txtleft" style="border: 1px solid black; width: 1000px; ">
																		<b><em>&nbsp;</em></b>
																	</td>
																</tr>
																<tr>
																	<td class="txtleft" style="border: 1px solid black; width: 1000px; ">
																		<b><em>Calibrazione strumento</em></b>
																	</td>
																	<td class="txtleft" style="border: 1px solid black; width: 1000px; ">
																		<b><em>&nbsp;</em></b>
																	</td>
																	<td class="txtleft" style="border: 1px solid black; width: 1000px; ">
																		<b>&nbsp;</b>
																	</td>
																	<td class="txtleft" style="border: 1px solid black; width: 1000px; ">
																		<b><em>&nbsp;</em></b>
																	</td>
																</tr>
																<tr>
																	<td class="txtleft" style="border: 1px solid black; width: 1000px; ">
																		<b><em>Altro (specificare)</em></b>
																	</td>
																	<td class="txtleft" style="border: 1px solid black; width: 1000px; ">
																		<b><em>&nbsp;</em></b>
																	</td>
																	<td class="txtleft" style="border: 1px solid black; width: 1000px; ">
																		<b>&nbsp;</b>
																	</td>
																	<td class="txtleft" style="border: 1px solid black; width: 1000px; ">
																		<b><em>&nbsp;</em></b>
																	</td>
																</tr>
															</table>
															<table cellspacing="0" style="border-collapse: collapse;">
																<tr>
																	<td style="width:50%;  padding-left:10px;"><b>A=</b> a carico del Promotore PROFIT
																	<br/><b>B=</b> a carico di fondi dell'Unit&agrave; Operativa a disposizione dello Sperimentatore *- <i>specificare il codice identificativo del fondo, se presente </i>
																	<br/><b>C=</b> finanziamento proveniente da terzi (in tal caso allegare l'accordo tra Promotore e finanziatore terzo che regolamenta il contributo economico)
																	<br/><b>D=</b> a carico del Fondo Aziendale per la Ricerca, ove presente **</td>
																</tr>
																<tr>
																	<td style="width:50%;  padding-left:10px;">* Applicabile solo per studi no profit
																	<br/> ** Applicabile solo per studi no profit finalizzati al miglioramento della pratica clinica</td>
																</tr>
															</table>
															<table cellspacing="0" style="border-collapse: collapse;">
																<tr>
																	<td class="txtcenter"><b>COINVOLGIMENTO DELLA FARMACIA</b></td>
																</tr>
																<tr>
																	<td><em><u>Se si, barrare l'opzione pertinente</u></em></td>
																</tr>
																<tr>
																	<td>1. il coinvolgimento della Farmacia &egrave; richiesto per:
																	</td>
																</tr>
																<tr>
																	<td>&nbsp;&nbsp; La randomizzazione
																	</td>
																</tr>
																<tr>
																	<td>&nbsp;${setCheckbox("Feasibility" "FC31" "1" el)}&nbsp; lo stoccaggio a breve termine e la consegna del materiale sperimentale (farmaco/dispositivo medico)</td>
																</tr>
																<tr>
																	<td>&nbsp;${setCheckbox("Feasibility" "FC3" "1" el)}&nbsp; lo stoccaggio a lungo termine (farmaco/dispositivo medico)  <#if el.getFieldDataCode("Feasibility","FC3")?? && el.getFieldDataCode("Feasibility","FC3")=="1" >ed in particolare</#if>
																	</td>
																</tr>

																<tr>
																	<td style="padding-left: 20px;">&nbsp;${setCheckbox("Feasibility" "FC4" "1" el)}&nbsp; la preparazione del/i farmaco/i sperimentale/i (compreso il placebo) ed in particolare:</td>
																</tr>
																<tr>
																	<td style="padding-left: 20px;">&nbsp;${setCheckbox("Feasibility" "FC5" "1" el)}&nbsp; esecuzione di studio di fattibilita'/definizione della formulazione;
																	</td>
																</tr>
																<tr>
																	<td style="padding-left: 20px;">&nbsp;${setCheckbox("Feasibility" "FC6" "1" el)}&nbsp; allestimento del/i farmaco/i sperimentale/i;
																	</td>
																</tr>
																<tr>
																	<td style="padding-left: 20px;">&nbsp;${setCheckbox("Feasibility" "FC7" "1" el)}&nbsp; ricostituzione/diluizione, anche in dose personalizzata;
																	</td>
																</tr>
																<tr>
																	<td style="padding-left: 20px;">&nbsp;${setCheckbox("Feasibility" "FC7bis" "1" el)}&nbsp; confezionamento/mascheramento;
																	</td>
																</tr>
																<tr>
																	<td style="padding-left: 20px;">&nbsp;${setCheckbox("Feasibility" "FC8" "1" el)}&nbsp; Altro (specificare): ${getField("Feasibility","noteFC8",el)}
																	</td>
																</tr>
																<tr>
																	<td>
																		Tutte le attivit&agrave; di cui sopra sono richieste per (barrare la voce pertinente):
																	</td>
																</tr>
																<tr>
																	<td style="">&nbsp;${setCheckbox("Feasibility" "FC9" "1" el)}&nbsp; questo singolo centro;</td>
																</tr>
																<tr>
																	<td style="">&nbsp;${setCheckbox("Feasibility" "FC10" "1" el)}&nbsp; I seguenti centri partecipanti allo studio (fornire l'elenco completo): ${getField("Feasibility","noteFC10",el)}</td>
																</tr>
																<tr>
																	<td colspan="2">
																		<b>Se si', fornire il parere della Farmacia e dare evidenza che nella bozza di convenzione economica sia previsto il compenso concordato per l'esecuzione delle suddette attivita'.</b>
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
															<table cellspacing="0" style="border-collapse: collapse;">
																<tr>
																	<td class="txtleft" colspan="2">
																		<b>Sezione C: Modulo riepilogativo aspetti economici - STUDIO PROFIT a cura del Promotore</b>
																	</td>
																</tr>
																<tr>
																	<td class="txtleft" style="border: 1px solid black; width: 1000px; ">
																		<b><em>Numero pazienti previsti nel centro</em></b>
																	</td>
																	<td class="txtleft" style="border: 1px solid black; width: 1000px; ">
																		<b><em>n.</em></b>
																	</td>
																</tr>
																<tr>
																	<td class="txtleft" style="border: 1px solid black; width: 1000px; ">
																		<b><em>Corrispettivo contrattuale (grant) per paziente</em></b>
																	</td>
																	<td class="txtleft" style="border: 1px solid black; width: 1000px; ">
																		<b><em>&euro;</em></b>
																	</td>
																</tr>
																<tr>
																	<td class="txtleft" style="border: 1px solid black; width: 1000px; ">
																		<b><em>Corrispettivo delle prestazioni aggiuntive a paziente furoi dal grant 1) </em></b>
																	</td>
																	<td class="txtleft" style="border: 1px solid black; width: 1000px; ">
																		<b><em>&euro;</em></b>
																	</td>
																</tr>
																<tr>
																	<td class="txtleft" style="border: 1px solid black; width: 1000px; ">
																		<b><em>Corrispettivo contrattuale totale a paziente 2)</em></b>
																	</td>
																	<td class="txtleft" style="border: 1px solid black; width: 1000px; ">
																		<b><em>&euro;</em></b>
																	</td>
																</tr>
																<tr>
																	<td class="txtleft" style="border: 1px solid black; width: 1000px; ">
																		<b><em>Totale altri corrispettivi studio specifici 3)</em></b>
																	</td>
																	<td class="txtleft" style="border: 1px solid black; width: 1000px; ">
																		<b><em>&euro;</em></b>
																	</td>
																</tr>
																<tr>
																	<td class="txtleft" style="border: 1px solid black; width: 1000px; ">
																		<b><em>Overhead</em></b>
																	</td>
																	<td class="txtleft" style="border: 1px solid black; width: 1000px; ">
																		<b><em>&euro;</em></b>
																	</td>
																</tr>
																<tr>
																	<td class="txtleft" colspan="2">
																		1), 2), 3) compilati in automatico dal sistema
																	</td>
																</tr>
															</table>
															<table cellspacing="0" style="border-collapse: collapse;">
																<tr>
																	<td class="txtleft" colspan="2">
																		<b>Sezione D: Modulo di previsione di impiego del finanziamento dedicato per lo studio NO PROFIT finanziato</b>
																	</td>
																</tr>
																<tr>
																	<td>
																		<table>
																			<tr>
																				<td class="txtcenter" style="border: 1px solid black; width: 1000px;" colspan="2">
																					<b><em>PREVISIONE IMPIEGO FINANZIAMENTO</em></b>
																				</td>
																			</tr>
																			<tr>
																				<td class="txtleft" style="border: 1px solid black; width: 1000px; ">
																					<b><em>Entita' del finanziamento 1)</em></b>
																				</td>
																				<td class="txtleft" style="border: 1px solid black; width: 1000px; ">
																					<b><em>&euro;</em></b>
																				</td>
																			</tr>
																			<tr>
																				<td class="txtleft" style="border: 1px solid black; width: 1000px; ">
																					<b><em>Traferimento ad altre aziende</em></b>
																				</td>
																				<td class="txtleft" style="border: 1px solid black; width: 1000px; ">
																					<b><em>&euro;</em></b>
																				</td>
																			</tr>
																			<tr>
																				<td class="txtleft" style="border: 1px solid black; width: 1000px; ">
																					<b><em>Coordinamento </em></b>
																				</td>
																				<td class="txtleft" style="border: 1px solid black; width: 1000px; ">
																					<b><em>&euro;</em></b>
																				</td>
																			</tr>
																			<tr>
																				<td class="txtleft" style="border: 1px solid black; width: 1000px; ">
																					<b><em>Personale</em></b>
																				</td>
																				<td class="txtleft" style="border: 1px solid black; width: 1000px; ">
																					<b><em>&euro;</em></b>
																				</td>
																			</tr>
																			<tr>
																				<td class="txtleft" style="border: 1px solid black; width: 1000px; ">
																					<b><em>Attrezzature</em></b>
																				</td>
																				<td class="txtleft" style="border: 1px solid black; width: 1000px; ">
																					<b><em>&euro;</em></b>
																				</td>
																			</tr>
																			<tr>
																				<td class="txtleft" style="border: 1px solid black; width: 1000px; ">
																					<b><em>Servizi/prestazioni aggiuntive</em></b>
																				</td>
																				<td class="txtleft" style="border: 1px solid black; width: 1000px; ">
																					<b><em>&euro;</em></b>
																				</td>
																			</tr>
																			<tr>
																				<td class="txtleft" style="border: 1px solid black; width: 1000px; ">
																					<b><em>Materiale di consumo</em></b>
																				</td>
																				<td class="txtleft" style="border: 1px solid black; width: 1000px; ">
																					<b><em>&euro;</em></b>
																				</td>
																			</tr>
																			<tr>
																				<td class="txtleft" style="border: 1px solid black; width: 1000px; ">
																					<b><em>Meeting, convegni, viaggi</em></b>
																				</td>
																				<td class="txtleft" style="border: 1px solid black; width: 1000px; ">
																					<b><em>&euro;</em></b>
																				</td>
																			</tr>
																			<tr>
																				<td class="txtleft" style="border: 1px solid black; width: 1000px; ">
																					<b><em>Pubblicazioni</em></b>
																				</td>
																				<td class="txtleft" style="border: 1px solid black; width: 1000px; ">
																					<b><em>&euro;</em></b>
																				</td>
																			</tr>
																			<tr>
																				<td class="txtleft" style="border: 1px solid black; width: 1000px; ">
																					<b><em>Assicurazione</em></b>
																				</td>
																				<td class="txtleft" style="border: 1px solid black; width: 1000px; ">
																					<b><em>&euro;</em></b>
																				</td>
																			</tr>
																			<tr>
																				<td class="txtleft" style="border: 1px solid black; width: 1000px; ">
																					<b><em>Altro</em></b>
																				</td>
																				<td class="txtleft" style="border: 1px solid black; width: 1000px; ">
																					<b><em>&euro;</em></b>
																				</td>
																			</tr>
																			<tr>
																				<td class="txtleft" style="border: 1px solid black; width: 1000px; ">
																					<b><em>Spese genrali ("overhead")</em></b>
																				</td>
																				<td class="txtleft" style="border: 1px solid black; width: 1000px; ">
																					<b><em>&euro;</em></b>
																				</td>
																			</tr>
																			<tr>
																				<td class="txtleft" colspan="2">
																					1) Somma automatica
																				</td>
																			</tr>
																		</table>
																	</td>
																</tr>
																<tr>
																	<td class="txtleft" colspan="2">
																		<b>Sezione E: Assunzione di responsabilita' a cura dello Sperimentatore Responsabile dello Studio</b>
																	</td>
																</tr>
																<tr>
																	<td>
																		<table>
																			<tr>
																				<td>
																					<span style="text-align: justify">Il sottoscritto ..........................................................,
																					Responsabile dello studio,<b>ai sensi e per gli effetti delle disposizioni di cui al DPR 445/2000 e s.m.i., consapevole
																							delle sanzioni penali nel caso di falsita' in atti e dichiarazioni mendaci, sotto la propria responsabilita', dichiara che:</b></span>
																				</td>
																			</tr>
																			<tr>
																				<td>
																					<ol class="">
																						<li>visti i criteri per l'arruolamento dei pazienti previsti dal presente protocollo, essi non confliggono con i criteri di arruolamento di altri protocolli attivati presso l'Unit&agrave; Operativa;</li>
																						<li>il personale coinvolto (sperimentatore principale e collaboratori) &egrave; competente ed idoneo;</li>
																						<li>l'Unit&agrave; Operativa presso cui si svolge la ricerca &egrave; appropriata; </li>
																						<li>&egrave; garantita l'assenza di pregiudizi per l'attivit&agrave; assistenziale come previsto dall'articolo 7 della Legge Regionale n. 9 del 1/6/2017;</li>
																						<li>dispone di tempo e mezzi necessari per svolgere lo studio;</li>
																						<li>lo studio verr&agrave; condotto secondo il protocollo di studio, in conformit&agrave; ai principi della Buona Pratica Clinica, della Dichiarazione di Helsinki (versione 64th WMA General Assembly, Fortaleza, Brazil, October 2013) e nel rispetto delle normative vigenti</li>
																						<li>ai soggetti che parteciperanno allo studio, al fine di una consapevole espressione del consenso, verranno fornite tutte le informazioni necessarie, inclusi i potenziali rischi correlati allo studio;</li>
																						<li>l'inclusione del paziente nello studio sar&agrave; registrata sulla cartella clinica o su altro documento ufficiale, unitamente alla documentazione del consenso informato;</li>
																						<li>si assicurer&agrave; che ogni emendamento o qualsiasi altra modifica al protocollo che si dovesse verificare nel corso dello studio, rilevante per la conduzione dello stesso, verr&agrave; inoltrato al Comitato Etico da parte del Promotore;</li>
																						<li>comunicher&agrave; ogni evento avverso serio al Comitato Etico e al Promotore secondo normativa vigente secondo quanto indicato nel protocollo dello studio;</li>
																						<li>ai fini del monitoraggio e degli adempimenti amministrativi, verr&agrave; comunicato al Comitato Etico l'inizio e la fine dello studio nonch&eacute; inviato, almeno annualmente, il rapporto scritto sull'avanzamento dello studio e verranno forniti, se richiesto, rapporti ad interim sullo stato di avanzamento dello studio;</li>
																						<li>la documentazione inerente lo studio verr&agrave; conservata in conformit&agrave; a quanto stabilito dalle Norme di Buona Pratica Clinica e alle normative vigenti;</li>
																						<li>la ricezione del medicinale sperimentale (se previsto) utilizzato per lo studio avverr&agrave; attraverso la farmacia della struttura sanitaria e, successivamente, il medicinale stesso verr&agrave; conservato presso il centro sperimentale separatamente dagli altri farmaci;</li>
																						<li>non sussistono vincoli di diffusione e pubblicazione dei risultati dello studio nel rispetto delle disposizioni vigenti in tema di riservatezza dei dati  sensibili e di tutela brevettuale e, non appena disponibile, verr&agrave; inviata copia della relazione finale e/o della pubblicazione inerente;</li>
																						<li>(mantenere unicamente la dichiarazione pertinente tra le due opzioni) lo studio &egrave; coperto da specifica polizza assicurativa oppure non &egrave; necessaria spcifica copertura assicurativa in quanto ....................................................................................................................(specificare la motivazione per cui si ritiene non necessaria specifica copertura assicurativa - tale aspetto sar&agrave; comunque oggetto di valutazione da parte del Comitato Etico);</li>
																						<li>non percepisce alcun compenso diretto per lo svolgimento dello studio;</li>
																						<li>se studio profit la convenzione economica verr&agrave; stipulata tra .............................................................. e .........................................................;</li>
																						<li>se studio no profit, (mantenere unicamente la dichiarazione pertinente tra le due opzioni) non &egrave; previsto alcun finanziamento dedicato per la conduzione dello studio oppure le modalit&agrave; di impiego del finanziamento dedicato per la conduzione dello studio sono esplicitate nella specifica sezione D del presente documento ed il corrispondente accordo finanziario sar&agrave; stipulato tra ................................................................................... e .......................................................................;</li>
																						<li>se studio no profit, qualora successivamente all'approvazione del Comitato Etico si ravvisasse la necessit&agrave; di acquisire un finanziamento a copertura di costi per sopraggiunte esigenze legate alla conduzione dello studio, si impegna a sottoporre al Comitato Etico, tramite emendamento sostanziale, la documentazione comprovante l'entit&agrave; del finanziamento, il suo utilizzo nonch&egrave; il soggetto erogatore;</li>
																						<li>lo studio verr&agrave; avviato soltanto dopo la ricezione di formale comunicazione di parere favorevole del Comitato Etico, di autorizzazione delle Autorit&agrave; regolatorie (AIFA o Ministero della Salute) ove previsto, di espresso e motivato nullaosta del Direttore Generale della struttura sanitaria in cui &egrave; condotta l'attivit&agrave; ai sensi dell'articolo 7 della Legge Regionale n.9 del 1/6/2017 nonch&egrave;, ove previsto, stipula del relativo contratto;</li>
																						<li>lo studio verr&agrave; avviato soltanto dopo l'avvenuta nomina del responsabile e degli incaricati al trattamento dei dati richiesta dalla normativa del Garante Privacy (Decreto legislativo 30 giugno 2003, n.196)</li>
																					</ol>
																				</td>
																			</tr>
																			<tr>
																				<td><br/><br/>
																					Data: _______________
																				</td>
																			</tr>
																			<tr align="center">
																				<td class="txtcenter">
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
																				<td class="txtcenter">
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
																				<td class="txtcenter">
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
																				<td class="txtcenter">
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
																				<td class="txtcenter">
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
																				<td class="txtcenter">
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
																				<td class="txtcenter">
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
