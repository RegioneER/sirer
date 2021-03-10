<style>
#tabs .prestazioni li a{
	font-size: 100%;
	padding: 0 0;
}

.btn.applicagruppo{
	line-height: 1;
	margin-top: 0px !important;
}

#tabs .prestazioni ul {
    height: auto !important;
}
   
</style>
	
<div id="tabs-0" class="tab-pane">
	<h3>Gestione gruppi di prestazioni</h3>
	<button class="btn btn-xs btn-info creaGruppo"><i class='fa fa-plus'></i> Crea un nuovo gruppo di prestazioni</button>
	<button class="btn btn-xs btn-info caricaGruppo"><i class='fa fa-folder-open'></i> Carica un gruppo esistente</button>
	
	<div id='gruppiPrestazioni' class="prestazioni">
		<br/><br/>
		<ul id='prestazioniList'></ul>
	</div>
	
</div>


<@script>

var elementId=${el.id};
$('.creaGruppo').click(function(){
	creaGruppo();
});

$('.caricaGruppo').click(function(){
	showSfogliaGruppi(elementId);
});
$(document).ready(function(){
	loadGruppi();
});
</@script>
<script src="/sirer-static/js/budget/tab0.js"></script>
 