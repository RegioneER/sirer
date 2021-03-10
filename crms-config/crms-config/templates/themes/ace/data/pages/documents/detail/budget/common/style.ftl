<!--link rel="stylesheet" href="${baseUrl}/int/css/budget/themes/base/jquery.ui.base.css" /-->
<!--link rel="stylesheet" href="${baseUrl}/int/css/budget/themes/base/jquery.ui.css" /-->
<!--link rel="stylesheet" href="${baseUrl}/int/css/budget/jquery.handsontable.full.css" /-->
<!--link rel="stylesheet" href="${baseUrl}/int/css/budget/base.css" /-->
<@style>

#Prestazioni_Altro[type='button']{
    display:none !important;
}
/*

COMMENTATO TUTTO TOSCANA-187

VMAZZEO TOSCANA-135
 #added-ca tr th:nth-child(3) , #added-ca tr td:nth-child(3),#costs-3 tr td:nth-child(2),#costs-4 tr td:nth-child(2),#costs-3 tr th:nth-child(2),#costs-4 tr th:nth-child(2){
	display:none;
}

CAMBIATO CON:
 #added-ca tr th:nth-child(3) , #added-ca tr td:nth-child(3){
    display:none;
}
*/
#bracciChecks label{
display:inline!important;
margin-left:3px;
}
.htCore th, td[data-column=0]{
	max-width:30px;
}
.ui-dialog .ui-dialog-title {

    white-space: normal!important;
  
}
.ui-dialog-title{
	padding-right:35px!important;
}
.select2-container .select2-choice{
	width:330px!important;
}
#dialog-form-ca input[type=text]{
	width:250px;
}
#Prestazioni-Prestazioni_Attivita label,#Prestazioni-Prestazioni_Attivita .col-sm-9{
	clear: both;
    display: block;
    float: none;
    padding: 0;
}
#TimePoint_NumeroVisita{
	background-color:#fff!important;
}
.table{
	font-size:14px;
}
.main-content .buttons-studio button.btn{
	margin-top:3px!important;
	margin-bottom:20px!important;
}
#prestazione-diz-dialog input {
	width:400px;
	display:block;
}
#task-Actions{
	display:inline;
}
.main-content button.btn-warning,.main-content  button.btn-primary{
	margin-right:10px!important;
}
.widget-header .ui-dialog-title{
	padding-left:15px;
	font-weight:bold;
}
.status-bar{
		margin-top:20px;
	}
.tab-content{
 width:100%!important;
}
.tab-pane {
	padding:10px;
}
.nav-tabs{
	padding-bottom: 43px;
}
.handsontable .htCheckboxRendererInput.noValue {
    opacity: 1;
}
.ui-autocomplete.ui-menu{
	z-index:9999!important;
}
#Prestazioni_Altro{
	font-size:14px;
}
budget-studio {
	font-size:13px;	
	border-collapsed:collapsed;
}
.budget-studio th{
	background-color:#CCCCCC;
	padding:2px 8px;
}
.budget-studio td{
	
	padding:3px 12px;
}

.handsontable td{
	font-size: 13px;
	font-weight:200;
}
#tabs ul{
	height: 41px!important;
}
#tabs li a{
				font-size: 125%;
			    
			    padding: 0.8em 2em;
}
/*		input[type=text], select,option {
		    font-size: 1.2vw!important;
		    line-height: 1.3vw;
}
		#tp-dialog-form input[type=text], select,option {
		    font-size: 1vw!important;
		    line-height: 1.1vw;

}
input[type=checkbox]{
			display:inline-block;
}*/
/*label{
	font-size:1.3vw;
	line-height:1.6vw;
}
#tp-dialog-form label{
	font-size:1.1vw;
	line-height:1.4vw;
}*/
/*.ui-dialog button, button.ui-button {
	font-size:1.3vw!important;
}
#tp-dialog-form .ui-dialog button, button.ui-button {
	font-size:0.8vw!important;
}*/
button.ui-button  i{
	margin-right:5px;
}
/*fix modal form nuova grafica*/
.ui-dialog-content label{
	display:block!important;
}

.ui-dialog-content input[type=checkbox]{
	vertical-align: middle;
}

.ui-dialog-content .ui-autocomplete-input{
	width:350px;
}

.form-group, .field-editable {
    clear: both;
}

.tab-content{
	clear:both;
}

.dragdealer.horizontal,.dragdealer.horizontal .handle{
	height:17px;
}
.dragdealer.vertical,.dragdealer.vertical .handle{
	width:17px;
}
.handle{
	cursor:grab;
}
 .x-checkbox-input,.x-checkbox-input *{
 	padding:0px!important;
 }
  .x-checkbox-input{
  	padding-left:12px!important;
 	padding-bottom:10px!important;
 }
 button[onclick^="inviaServizi"], button[onclick^="compareBudgetStudio"], #versioniBudgetStudio tr th:nth-child(1) , #versioniBudgetStudio tr td:nth-child(1) , #versioniBudgetStudio tr td:nth-child(2)
{
	display:none!important;
}
</@style>


  <@script>
  var isUO=false;
  var isPI=false;
  var isCurrPI=false;
  var sidebarDefault='${el.getParent().getId()}#Budget-tab2';
  $(document).ready(function(){
  	$('.ui-widget-header').addClass('widget-header');
  	});
  $.extend(true,Pace.options,{"ajax":{"ignoreURLs": ["dizionari" ]}});
  Pace.start();
 </@script>