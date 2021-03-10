var myTimer=null;
var myTime2r=null;
var rowHeaderWidth=40;
function GetExcelColumnName(columnNumber) {
    var dividend = columnNumber;
    var columnName = '';
    var modulo;

    while(dividend > 0) {
        modulo = (dividend - 1) % 26;
        columnName = String.fromCharCode(65 + modulo).toString() + columnName;
        dividend = parseInt((dividend - modulo) / 26);
    }

    return columnName;
}

function fixColHeaders(col,suffix){
  	var header=$.axmr.label(this.data[0][col]);
  	var stdHeader='';
  	if(col>0)  stdHeader=GetExcelColumnName(col);
  	if(header && header.replace){
  		header=header.replace(/\n/g,"<br>");
  	}else{
  		header='';
  		
  	}
  	myTimer=setTimeout(function(){
  		clearTimeout(myTimer);
  		if($('[data-row=0]:visible').size()>0){
  			$('.my-col-headers_'+suffix).hide();
  			$('.my-col-headers2_'+suffix).show();
  		}else{
  			$('.my-col-headers2_'+suffix).hide();
  			$('.my-col-headers_'+suffix).show();
  			
  		}
  	},200);
  	if($('[data-row=0]:visible').size()>0) {
  		var display=' style="display:none" ';
  		var display2=' style="display:inline" ';
  		}
  	else {
  		var display=' style="display:inline" ';
  		var display2=' style="display:none" ';
  	}
    return "<span class='my-col-headers_"+suffix+"' "+display+" data-colHeader='"+col+"' data-guid='"+this.data[0][col]+"' >"+header+"</span><span class='my-col-headers2_"+suffix+"' "+display2+" data-colHeader='"+col+"' data-guid='"+this.data[0][col]+"' >"+stdHeader+"</span>";
  }
  
  
  function fixRowHeaders(row,suffix){
      	var header=$.axmr.label(this.data[row][0]);
      	var stdHeader='';
  	    if(row>0)  stdHeader=row;
      	if(header && header.replace){
      		header=header.replace(/\n/g,"<br>");
      	}else{
      		header='';
      		
      	}
      	myTimer2=setTimeout(function(){
      	console.log('log');
      		clearTimeout(myTimer2);
      		if($('[data-column=0]:visible').size()>0){
      			$('.my-row-headers').hide();
      			$('.my-row-headers2').show();
      			$(".rowHeader").each(function(){
      				rowHeaderWidth=Math.max($(this).next().width(),rowHeaderWidth);
	          		$(this).css({"width": '22px'});
	          	});
      		}else{
      			$('.my-row-headers2').hide();
      			$('.my-row-headers').show();
      			$(".rowHeader").each(function(){
	          		$(this).css({"width": rowHeaderWidth});
	          	});
      		}
      	},200);
      	
      	if($('[data-column=0]:visible').size()>0) {
      		var display=' style="display:none" ';
      		var display2=' style="display:inline" ';
      	}
      	else {
      		var display2=' style="display:none" ';
      		var display=' style="display:inline" ';
      	}
        return "<span class='my-row-headers' "+display+" data-rowHeader='"+row+"' data-guid='"+this.data[row][0]+"' >"+header+"</span><span class='my-row-headers2' "+display2+" data-rowHeader='"+row+"' data-guid='"+this.data[row][0]+"' >"+stdHeader+"</span>";
      }
	      
	function fixColHeaders2(col,suffix){
	    suffix='2';
	  	var header=$.axmr.label(this.data[0][col]);
	  	var stdHeader='';
	  	if(col>0)  stdHeader=GetExcelColumnName(col);
	  	if(header && header.replace){
	  		header=header.replace(/\n/g,"<br>");
	  	}else{
	  		header='';
	  		
	  	}
	  	myTimer=setTimeout(function(){
	  		clearTimeout(myTimer);
	  		if($('[data-row=0]:visible').size()>0){
	  			$('.my-col-headers_'+suffix).hide();
	  			$('.my-col-headers2_'+suffix).show();
	  		}else{
	  			$('.my-col-headers2_'+suffix).hide();
	  			$('.my-col-headers_'+suffix).show();
	  			
	  		}
	  	},200);
	  	if($('[data-row=0]:visible').size()>0) {
	  		var display=' style="display:none" ';
	  		var display2=' style="display:inline" ';
	  		}
	  	else {
	  		var display=' style="display:inline" ';
	  		var display2=' style="display:none" ';
	  	}
	    return "<span class='my-col-headers_"+suffix+"' "+display+" data-colHeader='"+col+"' data-guid='"+this.data[0][col]+"' >"+header+"</span><span class='my-col-headers2_"+suffix+"' "+display2+" data-colHeader='"+col+"' data-guid='"+this.data[0][col]+"' >"+stdHeader+"</span>";
	  }
	  
	  
	  function fixRowHeaders2(row,suffix){
	  		suffix='2';
	      	var header=$.axmr.label(this.data[row][0]);
	      	var stdHeader='';
	  	    if(row>0)  stdHeader=row;
	      	if(header && header.replace){
	      		header=header.replace(/\n/g,"<br>");
	      	}else{
	      		header='';
	      		
	      	}
	      	myTimer2=setTimeout(function(){
	      	console.log('log');
	      		clearTimeout(myTimer2);
	      		if($('[data-column=0]:visible').size()>0){
	      			$('.my-row-headers').hide();
	      			$('.my-row-headers2').show();
	      			$(".rowHeader").each(function(){
	      				rowHeaderWidth=Math.max($(this).next().width(),rowHeaderWidth);
		          		$(this).css({"width": '22px'});
		          	});
	      		}else{
	      			$('.my-row-headers2').hide();
	      			$('.my-row-headers').show();
	      			$(".rowHeader").each(function(){
		          		$(this).css({"width": rowHeaderWidth});
		          	});
	      		}
	      	},200);
	      	
	      	if($('[data-column=0]:visible').size()>0) {
	      		var display=' style="display:none" ';
	      		var display2=' style="display:inline" ';
	      	}
	      	else {
	      		var display2=' style="display:none" ';
	      		var display=' style="display:inline" ';
	      	}
	        return "<span class='my-row-headers' "+display+" data-rowHeader='"+row+"' data-guid='"+this.data[row][0]+"' >"+header+"</span><span class='my-row-headers2' "+display2+" data-rowHeader='"+row+"' data-guid='"+this.data[row][0]+"' >"+stdHeader+"</span>";
	      }