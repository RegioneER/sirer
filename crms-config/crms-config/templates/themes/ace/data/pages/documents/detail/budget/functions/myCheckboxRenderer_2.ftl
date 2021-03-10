
var myCheckboxRenderer = function (instance, td, row, col, prop, value, cellProperties) {
  var test=$.axmr.label(value);
  $(td).off('click');
  $(td).off('dblclick')
  if(arguments[5]!== undefined &&  arguments[5]!== null &&  ($.trim(test.toString()).match(/^x$/i) || test===true || test==1))arguments[5]=true;
  else if(arguments[5]!==null && arguments[5]!='true' && arguments[5]!==true ){
      arguments[5]=false;
  }
  cellProperties.readOnly=true;
  Handsontable.CheckboxCell.renderer.apply(this, arguments);
  
  /*$(td).css({
    background: 'yellow'
  });*/
};
        