<style>
.form-horizontal .form-group{
	margin:0px;
}
label,#StatoPaziente-StatoPaziente_Stato div{
	padding-left:0px!important;
	margin-left:0px!important;
}
#StatoPaziente-StatoPaziente_Stato div{
	padding-bottom:20px;
}
.clearfix:after {
		    content: ".";
		    display: block;
		    height: 0;
		    clear: both;
		    visibility: hidden;
	    }
		
		.clearfix {
		    clear: both;
	    }
fieldset.specchietto {
		    border: 1px solid #336EA9!important;
		    border-radius: 10px!important;
		    padding: 1em!important;
		    font-size:12px;
		    
		    font-weight:bold;
		    font-family:arial;
		    width:90%;
		    float:left;
		    margin:10px;
		}
fieldset.specchietto * {
font-size:12px;

}		


.clearfix:after {
    content: ".";
    display: block;
    height: 0;
    clear: both;
    visibility: hidden;
    }

.clearfix {
    clear: both;
    }
    
.vs{
float: left;
    width: 50%;
    height:150px;
}
.vs label{
	width:30%;
}

.re{
float: left;
    width: 40%;
    height:150px;
}
.re label{
	width:55%;
}

.ri{
float: left;
    width: 80%;
}
.ri label{
	width:55%;
}

.vl{
float: left;
    width: 45%;
}
.vl label{
	width:55%;
}

.ui-autocomplete.ui-menu{
	z-index:9999!important;
}

.view-mode label {
    background-color: #FFFFFF;
    font-weight: normal !important;
    margin: 0;
    padding: 0.25em 0.5em;
    width: 15em;
}

.list-table a:hover {
    color: #000000;
    text-decoration: none;
}
.list-table a:visited {
    color: #000000;
    text-decoration: none;
}
.list-table a {
    color: #000000;
    text-decoration: none;
}
.home-fieldset {
    background-color: #DFEFFC;
    border: 1px solid #8AB8DA;
    border-radius: 10px;
    margin-bottom: 20px;
    padding: 5px;
    width: 90%;
}
.home-legend {
    background-color: #4084CA;
    border: 1px solid #8AB8DA;
    border-radius: 10px;
    color: #FFFFFF;
    padding: 5px;
}
.highlightRow {
    color: #438DD7 !important;
    font-weight: bold;
}
.list-table {
}
.list-table th {
    background-color: #FFFFFF;
    border-bottom: 1px solid #4D80B4;
    border-left: 1px ridge #4D80B4;
    color: #5D8DBE;
    font-size: 12px;
    font-weight: bold;
}
.list-table td {
    font-size: 12px;
    padding-left: 2px;
    padding-right: 2px;
    text-align: left;
}
.list-table tr:nth-child(2n+1) td {
    background-color: #F0FFFF;
}
.list-table tr:nth-child(2n) td {
    background-color: #F5FFFA;
}
.select2-container {
	min-width:130px!important;
}
</style>
<@script>
var loadedBraccio=false;
	$('label').removeAttr('class');
</@script>

<#include "../helpers/MetadataTemplate.ftl"/>
 <div class="row">
   		<div class="col-xs-10">
<#assign parentEl=el/>


<div id='centerElement' style='position:fixed;top:50vh;left:50vw;z-index:-100;opacity:0'></div>
<div id="monitoraggio" style="margin-top:20px;" ></div>

<div id="tp-dialog-form" title="Fattura visita">
    <form>
    <input type='hidden' name='col' />
    <fieldset>
    <label for="TimePoint_Descrizione">Descrizione</label>
    <div id='TimePoint_Descrizione' ></div>
    <br/>
    <label for="DatiMonTimePoint_Fatturabile" style="display:inline">Completa:</label>
    <input type="checkbox" name="DatiMonTimePoint_Fatturabile" id="DatiMonTimePoint_Fatturabile"  style="display:inline" value="1" class="text ui-widget-content ui-corner-all"/>
    <div class="clearfix"></div>
    <label for="DatiMonTimePoint_DataVisita">Data della visita:</label><br>
    <@datePickerNoLabel "DatiMonTimePoint_DataVisita" "DatiMonTimePoint_DataVisita" "label" />
    <div class="clearfix">
    <button class="btn btn-primary"  onclick="selezionaTutti(this);" type="button" >Seleziona tutte le prestazioni della visita</button>
    </div>
    </fieldset>
    </form>
</div>
<br><br>

	   	
	    <table class="table table-striped table-bordered table-hover " >
	    	<thead>
	    	<tr>
	    		<th>Descrizione</th>
	    		<th>Fatturate</th>
	    		<th>Da fatturare</th>
	    	</tr>
	    	</thead>
	    	<tbody>
	    	<tr><td colspan="3"><span class="help-button">?</span>Prestazioni a richiesta / altre prestazioni non cliniche per paziente</td></tr>
	    
	    <#list parentEl.getChildrenByType("FolderMonPxP") as subFolder>
		    <#list subFolder.getChilds() as subEl>	
		    	
		    	<#assign prestazione=subEl.getFieldDataElement("DatiMonPxP","BudgetLink")[0] />
		    		
		    	<tr>
		    		<td>${prestazione.getfieldData("Base","Nome")[0]}</td>
		    		<td><#if (subEl.getfieldData("DatiMonPxP","Fatturato")?? && subEl.getfieldData("DatiMonPxP","Fatturato")?size>0) >${subEl.getfieldData("DatiMonPxP","Fatturato")[0]}<#else>0</#if></td>
		    		<td><input <#if !editMonitoraggio>disabled="disabled"</#if> type="text" size="5" id="${subEl.getId()}" name="DatiMonPxP_Fatturabile" value="<#if (subEl.getfieldData("DatiMonPxP","Fatturabile")?? && subEl.getfieldData("DatiMonPxP","Fatturabile")?size>0) >${subEl.getfieldData("DatiMonPxP","Fatturabile")[0]}<#else>0</#if>" /></td>
		    	</tr>
		    	
		    	
		    </#list>	
	    </#list>
	    </tbody>
	  </table>
	 
	  <div class="clearfix"></div>
	  <button class="btn btn-warning" id="Salva"  onclick="saveAll();"><i class="icon-save"></i> <b>Salva</b></button>
 </div>
<div class="col-xs-2 sidebar-right">	
<div id="rightbar-toggle" class="btn btn-app btn-xs btn-info  ace-settings-btn open">
<i class="icon-chevron-right bigger-150"></i>
</div>	
<div class=" status-bar-content">
 <div class="col-xs-12 status-bar">
				<h2>Informazioni paziente</h2>
				

	<@TemplateForm "DatiPaziente" el userDetails false />
 	<div class="clearfix"></div>
 	<div class="field-component" style="padding-left:12px">
 	<@TemplateFormFastUpdate "StatoPaziente" el userDetails true />
	</div>
	
	
<#assign bracciOptions=""/>
<#assign currBraccio=[""] />
<#if (el.getFieldDataElement("DatiCustomPaziente","Braccio")?size gt 0) >
	<#assign braccioFilter=el.getFieldDataElement("DatiCustomPaziente","Braccio")[0].getFieldDataString("Base","Nome") />
	<#assign currBraccio=[el.getFieldDataElement("DatiCustomPaziente","Braccio")[0].getId()?string+"###"+braccioFilter] />
	<@script>
		var loadedBraccio='${el.getFieldDataElement("DatiCustomPaziente","Braccio")[0].getId()?string}';
		var braccioFilter="${braccioFilter}";
		$('#DatiCustomPaziente_Braccio-select').val(loadedBraccio);
	</@script>
<#else>
	<@script>
		var braccioFilter=false;
		
	</@script>
</#if>
<#list parentEl.getChildrenByType("FolderMonBracci") as subFolder>
	<#assign bracciLinkList=subFolder.getChildren() />
	<#assign bracciList=[] />
	<#list bracciLinkList as braccio>
		
		<#assign braccioEl=braccio.getFieldDataElement("DatiMonBraccio","Braccio")[0] />
		<#assign bracciList=bracciList+[braccioEl] />
		<#assign bracciOptions=bracciOptions+"<option value='"+braccioEl.getId()+"'>"+braccioEl.getFieldDataString("Base","Nome")+"</option>"/>
	</#list>
</#list>
<#if bracciOptions!="" >

<div class="clearfix field-inline-edit" style="padding-left:12px">
<label>Braccio:</label><br>
<#attempt>
	<@braccioField "DatiCustomPaziente" "Braccio" parentEl userDetails true bracciList currBraccio />
<#recover>
</#attempt>
	</div>
</#if>


		</div>
	</div>
  </div>
  </div>