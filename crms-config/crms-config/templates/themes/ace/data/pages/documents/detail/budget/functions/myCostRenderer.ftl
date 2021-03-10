
var myCostRenderer = function (instance, td, row, col, prop, value, cellProperties) {         
  Handsontable.TextCell.renderer.apply(this, arguments);         
  var label=$.axmr.label(value,2);
  $(td).html(label);
  $(td).css({
    color: 'black'
  });
};
