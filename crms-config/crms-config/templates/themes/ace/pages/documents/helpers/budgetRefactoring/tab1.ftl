<style>

    ul.ui-autocomplete.ui-menu {
        z-index: 9999999999999 !important;
    }

	 #flowchartTable table thead th{
	 	font-weight: normal;
	 	white-space: nowrap;
		 min-width: 150px;
	 }
	 
	 #flowchartTable table thead th:nth-child(1){
	 	white-space: nowrap;
	 } 
	 
	 
	 
	 #flowchartTable table tbody td{
	 	white-space: nowrap;
	 	text-align: center;
	 	height: 45px;
	 }
	 
	 #flowchartTable table.data{
	 
	 }
	 
	 #flowchartTable table.headers{
	 
	 }
	 
	 #flowchartTable table.columns{
	 
	 }
	 
	 #flowchartTable table tbody td:nth-child(1){
	 	
	 	text-align: left !important;
	 	
	 }
	 /*
	 .crosscheck{
	 	display:inline-block;
	 	width:10px;height:10px;
	 	border:1px solid #a4a4a4;	
	 }
	 
	 .crosscheck.ssn{
	 	background-color:white;
	 }
	 
	 .crosscheck.extraSponsor{
	 	background-color:orange;
	 }
	 
	 .crosscheck.extraSSN{
	 	background-color:lightblue;
	 }
	*/
    .select2-drop{
        z-index: 999999999 !important;
    }

     .bootbox-body {
         font-size: 15px;
     }

    .flow-tp-action-container{
        max-height: 0px !important;
        text-align: right;
    }

     .flow-tp-action-container div {
         position: absolute;
         top: -3px;
         padding: 3px;
     }

    .flow-prestazioni-action-container{
        float: right;
        margin-top: -13px;
	}

	.flow-prestazioni-container{

	}

    table#flowchartTableId tbody td{
        background-color: #EEEEEE;
        min-width: 150px;
	}

    table#flowchartTableId tbody td.extraSSN{
		background-color: #ADD8E6;
	}

    table#flowchartTableId tbody td.extraSponsor{
        background-color: #FFA500;
    }

    table#flowchartTableId tbody td.ssn{
        background-color: #FFFFFF;
    }

</style>
	
<div id="tabs-1" class="tab-pane">
	 
	
	
	<button class="btn btn-xs btn-info addPrestazione"><i class='fa fa-plus'></i> Aggiungi prestazione</button>
	
	<button class="btn btn-xs btn-info addVisit"><i class='fa fa-plus'></i> Aggiungi visita</button>

	<button class="btn btn-xs btn-info applicaSSN"><i class='fa fa-euro'></i> Applica valori SSR </button>

	<div id="flowchartTable"></div>
	<div class='totalePaziente'><strong>Totale costo a paziente</strong>: <span id='patTotPrice'></span></div>

	<div id='legenda'
		<ul style="list-style: none">
			<li>
				<span style="display:inline-block;width:10px;height:10px;background-color:lightblue;border:1px solid #a4a4a4;"></span>
				<span style="display:inline-block;font-size:17px;font-weight:200;">&nbsp;&nbsp;prestazioni aggiuntive rimborsate dal promotore  &nbsp;&nbsp;</span>
			</li>
			<li>
				<span style="display:inline-block;width:10px;height:10px;background-color:orange;border:1px solid #a4a4a4;"></span>
				<span style="display:inline-block;font-size:17px;font-weight:200;">&nbsp;&nbsp;prestazioni routinarie ma nel caso specifico rimborsate dal promotore  &nbsp;&nbsp;</span>
			</li>
			<!--li>
				<span style="display:inline-block;width:10px;height:10px;background-color:white;border:1px solid #a4a4a4;"></span>
				<span style="display:inline-block;font-size:17px;font-weight:200;">&nbsp;&nbsp;prestazioni routinarie a carico SSN/SSR&nbsp;&nbsp;</span>
			</li-->
		</ul>
	</div>


    <div class="alert alert-block alert-info">
		<strong>Supporto alla compilazione flowchart</strong><br>
		La tabella della flowchart riporta una riga per ogni tipo di prestazione ed una colonna per ogni visita. 
		<li>Per aggiungere prestazioni e visite cliccare sui relativi pulsanti</li>
		<li>Per associare una prestazione alla visita cliccare nella cella grigia relativa</li>
		<li>Per modificare il regime di rimborsabilit&agrave; cliccare sul check nella cella corrispondente</li>
		<li>Per aggiungere i costi, dove previsto, cliccare "aggiungi costi"</li>
		 
	</div>
    <#include "../budget/formTimePoint.ftl" />
    <#include "../budget/prestazioniForm.ftl" />

</div>

<@script>

var elementId=${el.id};
var baseUrl='${baseUrl}';
var folderPrestazioniId=${el.getChildrenByType('FolderPrestazioni')[0].id};
var folderBudgetStudioId=${el.getChildrenByType('FolderBudgetStudio')[0].id};
var folderBudgetStudio=folderBudgetStudioId;
var folderCostiAggiuntivi=${el.getChildrenByType('FolderPrestazioni')[0].id};
var budgetStudioId=${el.getChildrenByType('FolderBudgetStudio')[0].getChildrenByType('BudgetCTC')[0].id};
var folderBudgetStudioTypeId=${el.getChildrenByType('FolderBudgetStudio')[0].type.id};
var folderTimePointId=${el.getChildrenByType('FolderTimePoint')[0].id};
var folderTpxpId=${el.getChildrenByType('FolderTpxp')[0].id};

loadFlow();


</@script>
<script src="/sirer-static/js/budget/tab1.js"></script>
 