<div class="home-container" >

		<style>
		
		.ui-jqgrid tr.jqgrow td {
			white-space:normal;
		}
		.ui-jqgrid .ui-jqgrid-htable th div {
			white-space:normal;
			height:auto;
			margin-bottom:3px;
		}
	
		
		.home-table .ui-jqgrid{
			margin:10px;
			
		}
		
		tr.jqgrow{
			cursor:pointer;
		}
		
		.home-table {
			float:left;
		}
		
		
		</style>
<@script>
var typeId='${model['rootElements'][0].type.typeId}';
</@script>

<table id="list-grid-table" class="grid-table" ></table>
<div id="list-grid-pager"></div>
		

</div>