
function moveBudget(target){
	if(target=='tabs-3'){
		budgetCTC=true;
		$('#add-n-pat').show();
		$('#global-pazienti').show();
	}
	else{
		budgetCTC=false;
		$('#add-n-pat').hide();
		$('#global-pazienti').hide();
	}
	var handsontable1 =  $('#example').data('handsontable'); 
    var handsontable2 =  $('#costi').data('handsontable');   
    var preMigration= handsontable2.getData()
    if(costiInit || preMigration[1][0]!==null || preMigration[0][1]!==null){
    	//var migrated=mergeData(preMigration,handsontable1.getData());
    	//handsontable2.loadData(preMigration);
    	//$('#costi').handsontable('render');
    	
    	var migrated=migrateData(handsontable1.getData());
    	handsontable2.loadData(migrated);
    	calcolaTotali();
    }
    else{
    costiInit=true;
    	var migrated=migrateData(handsontable1.getData());
    	var handsontable2 =  $('#costi').data('handsontable');   
    
    	handsontable2.loadData(migrated);
    }
	$('#clinico').prependTo('#'+target);
	$('#global-pazienti').appendTo('#pazienti-'+target);
	//rimuoviTotali();
	//calcolaTotali();
}
        