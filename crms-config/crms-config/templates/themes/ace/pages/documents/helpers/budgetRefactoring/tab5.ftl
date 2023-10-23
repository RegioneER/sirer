
<#assign elType= budgetStudio.type />

<#assign markup='0' />
<#assign markup_numerico='0' />
<#if budgetStudio?? && budgetStudio.getFieldDataString("BudgetCTC","Markup")?? && budgetStudio.getFieldDataString("BudgetCTC","Markup")!="" >
	<#assign markup_numerico=budgetStudio.getFieldDataString("BudgetCTC","Markup") />
	<#assign markup="&euro; "+budgetStudio.getFieldDataString("BudgetCTC","Markup") />
</#if>
<#assign numero_pazienti='0' />
<#if budgetStudio?? && budgetStudio.getFieldDataString("BudgetCTC","NumeroPazienti")?? && budgetStudio.getFieldDataString("BudgetCTC","NumeroPazienti")!="" >
	<#assign numero_pazienti=budgetStudio.getFieldDataString("BudgetCTC","NumeroPazienti") />
</#if>
<#assign proposta_promotore='0' />
<#assign proposta_numerica='0' />
<#if budgetStudio?? && budgetStudio.getFieldDataString("BudgetCTC","TipoTarget")?? >
	<#if budgetStudio.getFieldDataString("BudgetCTC","TipoTarget")=="2" >
		<#assign proposta_promotore="&euro; " + budgetStudio.getFieldDataString("BudgetCTC","TargetPaziente") />
		<#assign proposta_numerica=budgetStudio.getFieldDataString("BudgetCTC","TargetPaziente") />
	<#elseif budgetStudio.getFieldDataString("BudgetCTC","TipoTarget")=="3" >
		<#assign proposta_promotore=" &euro; " +budgetStudio.getFieldDataString("BudgetCTC","TargetStudio")+" per intero studio" />
		<#assign proposta_numerica=budgetStudio.getFieldDataString("BudgetCTC","TargetStudio") />
	</#if>
	<#assign totPricePaz=0/>
	<#assign totPerPaz=proposta_numerica?number+totPricePaz?number />
	<#assign totPerPaz=" &euro; " +totPerPaz/>
	<#assign totPerPaz=proposta_numerica?number+totPricePaz?number />
	<#assign totPerStudio=numero_pazienti?number*totPerPaz?number />
	<#assign totPerPaz=" &euro; " +totPerPaz/>
	<#assign totPerStudio=" &euro; " +totPerStudio/>
</#if>
<@script>
var numero_pazienti_tmp=${numero_pazienti};
var proposta_promotore=${proposta_numerica};
var proposta_promotore_tmp=${proposta_numerica};

var markup_tmp=${markup_numerico};
var loadedElement=${elementJson};
var loadedBudget=${budgetJson};
var loadedBudgetStudio=${budgetStudioJson};

//confronta
var empties=new Array();
var emptiesTmp=new Array();
//voce typeId in prod: 67 in locale : 8

var emptyVoce={"id":null,"type":{"id":"67","typeId":"VocePrestazione"},"children":null,"metadata":{"PrestazioniDizionario_CodiceBranca3":[""],"PrestazioniDizionario_Descrizione":[""],"PrestazioniDizionario_CodiceBranca4":[""],"PrestazioniDizionario_CodiceBranca1":[""],"PrestazioniDizionario_CodiceBranca2":[""],"PrestazioniDizionario_Codice":[""],"PrestazioniDizionario_Tipo":[""],"PrestazioniDizionario_Nota":[""],"PrestazioniDizionario_TariffaALPI":[""],"PrestazioniDizionario_TariffaSSN":[""]},"title":""};
<#list elType.getAllowedChilds() as myType>

<#assign json=myType.getDummyJson() />
empty${myType.typeId}=${json};
<#list myType.getAllowedChilds() as childType>
<#assign json=childType.getDummyJson() />
empty${childType.typeId}=${json};
</#list>
</#list>

<#list budget.type.getAllowedChilds() as myType>
	<#assign json=myType.getDummyJson() />
		empty${myType.typeId}=${json};
		<#list myType.getAllowedChilds() as childType>
			<#assign json=childType.getDummyJson() />
				empty${childType.typeId}=${json};
		</#list>
</#list>

emptiesTmp[emptiesTmp.length]=emptyFolderTimePoint;
emptiesTmp[emptiesTmp.length]=emptyFolderPrestazioni;
emptiesTmp[emptiesTmp.length]=emptyFolderTpxp;
emptiesTmp[emptiesTmp.length]=emptyTimePoint;
emptiesTmp[emptiesTmp.length]=emptyPrestazione;
emptiesTmp[emptiesTmp.length]=emptytpxp;
emptiesTmp[emptiesTmp.length]=emptyFolderPXP;
emptiesTmp[emptiesTmp.length]=emptyFolderPXS;
emptiesTmp[emptiesTmp.length]=emptyPrestazioneXPaziente;
emptiesTmp[emptiesTmp.length]=emptyPrestazioneXStudio;
emptiesTmp[emptiesTmp.length]=emptyFolderBudgetStudio;
emptiesTmp[emptiesTmp.length]=emptyBudgetCTC;
emptiesTmp[emptiesTmp.length]=emptyVoce;
emptiesTmp[emptiesTmp.length]=emptyFolderPXPCTC;
emptiesTmp[emptiesTmp.length]=emptyFolderPXSCTC;
emptiesTmp[emptiesTmp.length]=emptyFolderPassthroughCTC;
emptiesTmp[emptiesTmp.length]=emptyPrezzoPrestazione;
emptiesTmp[emptiesTmp.length]=emptyFolderBracci;
emptiesTmp[emptiesTmp.length]=emptyBraccio;
$.each(emptiesTmp,function(ie,currEmpty){
empties[currEmpty.type.id]=currEmpty;
});
</@script>

<div id="tabs-5" class="tab-pane">
	<div id="soloProfit">
		<div id='non-clinico'>
			<div style="float:right">
				<#if !(nobutton??) && !readonly >
				<button class="btn btn-primary"  id="add-n-pat"><b>Numero di pazienti previsto</b></button>
				<button class="btn btn-primary" id="create-target"><i class="icon-plus"></i><b>Corrispettivo contrattuale </b></button>
				<button class="btn btn-primary" id="add-CTC"><i class="icon-plus"></i><b>Overhead aziendale</b></button>
				</#if>
			</div>
		</div>

		<div style="clear: both"></div>
		<div id="advised-markup" class="ui-widget cost-table full-w" style="margin-top:20px">
			<fieldset>
			<table id="table-advised-markup" class="table table-striped table-bordered table-hover">
				<thead>
					<tr>
						<th colspan="2">
							Modulo riepilogativo aspetti economici
						</th>
					</tr>
				</thead>
				<tbody>
					<tr>
						<td><span id='global-pazienti'>N&deg; pazienti previsti nel centro</span></td>
						<td><span id='show-n-pat'>${numero_pazienti}</span></td>
					</tr>
					<tr>
						<td>Corrispettivo contrattuale (grant) per paziente </td>
						<td><span id='proposta_promotore'>${proposta_promotore}</span></td>
					</tr>
					<tr>
						<td>Corrispettivo delle prestazioni aggiuntive a paziente fuori dal grant </td>
						<td><span id='show-totPricePaz'></span></td>
					</tr>
					<tr>
						<td>Corrispettivo contrattuale totale a paziente </td>
						<td><span id='show-TotPerPaz'>${totPerPaz}</span></td>
					</tr>
					<tr>
						<td>GRANT totale </td>
						<td><span id='show-TotPerStudio'>${totPerStudio}</span></td>
					</tr>
					<tr>
						<td>Totale altri corrispettivi studio specifici </td>
						<td><span id='show-totCostiAgg'></span></td>
					</tr>
					<tr>
						<td>Overhead aziendale</td>
						<td><span id='markup-ins'>${markup}</span></td>
					</tr>
				</tbody>
			</table>
			</fieldset>
		</div>


		<div id="dialog-form-proto" title="Aggiungi proposta promotore" style="display:none;">

			<form>
				<fieldset>
					<label for="BudgetCTC_TipoTarget" class="col-sm-3" >Tipologia </label>
					<select  name="BudgetCTC_TipoTarget" id="BudgetCTC_TipoTarget" style="font-size: 14px" class="col-sm-9 text ui-widget-content ui-corner-all" />
					<!--option value="1">Per visita</option--> <#-- PER ORA COMMENTO vmazzeo 21.03.2018 -->
					<option value="2">Per paziente</option>
					<!--option value="3">Per studio</option--> <#-- PER ORA COMMENTO vmazzeo 21.03.2018 -->
					</select>
					<br  style="clear:both"/>
					<label for="targetPrezzo" class="col-sm-3">Importo </label>
					<input type="text" name="targetPrezzo" id="targetPrezzo" class="col-sm-9 text ui-widget-content ui-corner-all" value="${proposta_numerica}"/>
				</fieldset>
			</form>
		</div>
	<#assign NaturaDelloStudio=getCode("datiStudio","NaturaDelloStudio",center.parent) />
	<#if NaturaDelloStudio=="2" || NaturaDelloStudio=="3" >
		<div id="soloNoProfit">
			<#assign myEditable=!readonly && editable />
			<#list budgetStudio.templates as template>
				<#if template.name=="BudgetCTC">
					<#assign groupActive=false />
					<#list budgetStudio.elementTemplates as elementTemplate>
						<#if elementTemplate.metadataTemplate.name==template.name && elementTemplate.enabled>
							<#assign templatePolicy=elementTemplate.getUserPolicy(userDetails, el)/>
							<#if templatePolicy.canView>
								<#assign template=elementTemplate.metadataTemplate/>
								<#assign toClose=true />
								<div id="metadataTemplate-${template.name}">
									<#if myEditable && (templatePolicy.canCreate || templatePolicy.canUpdate)>
										<form name="${template.name}" style="display:" id="form-${template.name}" method="POST" action="${baseUrl}/app/rest/documents/update/" onsubmit="return false;">
									</#if>
								<table class="table table-bordered" id="checklist">
								<thead>
									<tr><th colspan="2">Previsione Impiego Finanziamento</th></tr>
								</thead>
									<#list template.fields as field>
									<#if field.name?starts_with("FIN")>
										<@SingleFieldTd template.name field.name budgetStudio userDetails myEditable />
									</#if>
									</#list>
								</table>
							</#if>
						</#if>
					</#list>
					<#if myEditable && (templatePolicy.canCreate || templatePolicy.canUpdate)>
						<div class="clearfix"></div>
							<button id="salvaForm-${template.name}" class="btn btn-warning" name="salvaForm-${template.name}" data-rel="#form-${template.name}" ><i class="icon-save bigger-160" ></i><b>Salva</b></span></button>
						</form>
					</#if>
				</#if>
			</#list>
						</div>
		</div>
	</#if>
</div>
</div>
<script src="/sirer-static/js/budget/tab5.js"></script>