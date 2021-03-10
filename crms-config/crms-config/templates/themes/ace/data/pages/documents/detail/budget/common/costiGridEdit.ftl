
$('#costi').handsontable({
  width: 1200,
  height:650,
  minSpareRows:1,
  minSpareCols:1,
  colHeaders:fixColHeaders2,
  rowHeaders:fixRowHeaders2,
  minCols: 5,
  minRows: 15,
  contextMenu: false,
  manualColumnResize:true,
  cells: function (row, col, prop) {
    var cellProperties = {}
    cellProperties.readOnly=!updating;
    if(row==0 || col==0){
    	
    	//cellProperties.type='text';
    	cellProperties.renderer=myTranslateRender;
    } 
    if(row!=0 && col!=0)cellProperties.renderer=myForm3Renderer;  
    return cellProperties;
  }
  
});
				          