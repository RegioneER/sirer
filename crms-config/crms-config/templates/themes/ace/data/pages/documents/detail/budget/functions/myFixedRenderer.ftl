//funzione non usata da cancellare
var myFixedRenderer = function (instance, td, row, col, prop, value, cellProperties) {         
          Handsontable.TextCell.renderer.apply(this, arguments);         
          $(td).html('<div style="height: 30px; overflow:hidden;">'+$(td).html()+'</div');
        };
