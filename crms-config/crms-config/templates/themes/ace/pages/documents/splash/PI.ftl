<style>

.circle{
	border-radius: 50%;
	height:180px;
	width:180px;
	padding-top: 20px;
	display:inline-block; vertical-align:middle
}

#splash-home .modal-footer {
    background-color: white !important;
    border-radius: 0 0 20px 20px !important;
}

#splash-home .modal-content {
    border-radius: 20px !important;
}

#splash-home h4{
	background: url('/gemelli-trasp.png');
	background-repeat: no-repeat;
	text-align: center;
	padding-left: 160px;
	height: 50px
}

#splash-home h4 span{
	color: #001e62;
    display: block;
    font-family: logo;
    font-size: 18px;
}



</style>
<div id="splash-main-body">
<div id='advSearch' style="float:right">
	<a href="${baseUrl}/app/documents/custom/search" style="margin:auto" class="btn btn-success circle">
	<i class="icon-search icon-4x"></i><br/>Cerca uno<br/>studio</a>
</div>
<div id='addStudio'>
	<a href="${baseUrl}/app/documents/new/21" class="btn btn-info circle">
	<i class="icon-folder-open icon-4x"></i><br/>
	Aggiungi un<br/>nuovo studio
	</a>
</div>



<div id='splash-dash' style="text-align:center">
	<a id='add-center-splash' href="#" onclick="alert('Funzione non ancora attiva');" class="btn btn-warning circle">
	<i class="icon-dashboard icon-4x"></i><br/>
	Dashboard</a>
</div>



</div>
