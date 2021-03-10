document.onmousemove = mouseMove;
document.onmouseup = mouseUp;
var dragObject     = null;
var mouseOffset = null;
var nextDiv;
var nextZIndex;
var canvas;
var tab='';
//var mouseDown;
document.onResize=function(){alert('resize');};
canvas=new Array();
nextDiv=0;
nextZIndex=2;
var ajaxQueue;
ajaxQueue=new Array();
var fading;
fading=new Array();
var canvasToMove;
canvasToMove=new Array();
var canvasToResize;
canvasToResize=new Array();
var maximized;
/*.captureEvents=function(){
alert(event.type);
}*/
var Ajax = function(  params, id, waiting, response, method ,target, sync)

{
	// Properties

	this.target			= target		|| 'ajax.php';

	this.method			= method		|| 'POST' ;

	this.params			= params+'&ajax_new=true';

	this.id				= id			|| 'resultDiv' ;

	this.result			= null;

	this.updating		= false;

	this.response		= response		|| 1;

	this.waiting		= waiting		|| 1;

	this.debugging		= true;

	this.sync			= sync			|| true;

	canvas[this.id]=this;
	
	if(this.method=='GET')

	this.getRequest();

	else

	this.postRequest();

}



Ajax.prototype.createRequest = function()

{
	XHR = null,
	browserUtente = navigator.userAgent.toUpperCase();
	if(typeof(XMLHttpRequest) === "function" || typeof(XMLHttpRequest) === "object"){
		XHR = new XMLHttpRequest();

	}
	else if(window.ActiveXObject &&	browserUtente.indexOf("MSIE 4") < 0) {
		if(browserUtente.indexOf("MSIE 5") < 0)
		XHR = new ActiveXObject("Msxml2.XMLHTTP");
		else
		XHR = new ActiveXObject("Microsoft.XMLHTTP");
	}
	return XHR;
}

Ajax.prototype.debug = function(bug)

{
	if(this.debugging){
		alert('Error '+bug+' / '+this.response+' / '+this.id+' : ajax call stopped.');
	}
}

Ajax.prototype.answer = function()

{
	if(document.getElementById(this.id) && document.getElementById(this.id).style.cursor=='wait')document.getElementById(this.id).style.cursor='auto';
	if(document.body.style.cursor=='wait')document.body.style.cursor='auto';
	switch(this.response){
		
		
		case 7:

		if(!document.getElementById(this.id)){
			ajaxQueue.push(this);
			setTimeout('var temp; temp= ajaxQueue.shift(); temp.answer();',400);
			break;
		}
		case 1:
		//classico: valorizza il contenuto di un tag
		if(this.id!=null){
			if(document.getElementById(this.id))
			{
				if(document.getElementById(this.id).style.display!=''){
					document.getElementById(this.id).style.display='';
				}
				document.getElementById(this.id).innerHTML = this.result;
				document.getElementById(this.id).style.cursor='auto';
			}else{
				this.debug(3);
			}

		}else{
			this.debug(2);
		}
		break;
		case 2:
		//refresh
		location.reload();
		break;
		case 3:
		//redirect
		location.href=this.result;
		break;
		case 6:
		if(!document.getElementById(this.id)){
			ajaxQueue.push(this);
			setTimeout('var temp; temp= ajaxQueue.shift(); temp.answer();',400);
			break;
		}


		case 4:


		document.body.style.cursor='auto';

		case 5:
		// valorizza il contenuto di un tag che mostra gradualmente
		if(this.id!=null){
			if(document.getElementById(this.id))
			{

				document.getElementById(this.id).innerHTML = this.result;
				fadeIn(this.id);

				document.body.style.cursor='';
			}else{
				this.debug(30);
			}

		}else{
			this.debug(20);
		}
		break;
		case 9:
		document.body.style.cursor='auto';
		//alertContents
		case 8:
		if (this.result.match("link_to:")){
			resp=this.result.split(":");
			//if (resp[1]!='') window.location.href=resp[1];
			document.forms[0].submit();
		}
		else if (this.result.match("Error:")){
			resp=this.result.split(":");
			var resp2;
			resp2=resp[1].split("#error#");
			alert(resp2[1]);
			if (document.forms[0].elements[resp2[0]]) {
				document.forms[0].elements[resp2[0]].focus();
				document.forms[0].elements[resp2[0]].select();
			}
			else
			return false;
			//            	document.forms[0].elements[resp2[0]][0].select();
			//            	document.forms[0].elements[resp2[0]][0].select();
		}
		break;
		// apre una "finestra" di dialogo 
		case 10:
		var canv;
		canv=new Canvas();
		canv.innerHTML(this.result,true);
		canv.maximize(true);
		canv.show();
		break;
		default:
		this.debug(10);
		break;
	}
}

Ajax.prototype.wait = function()

{
	switch(this.waiting){
		case 1:
		//classico: valorizza il contenuto di un tag con loading.gif
		if(this.id!=null){

			if(document.getElementById(this.id)){

				document.getElementById(this.id).innerHTML='<img src="images/loading.gif">';
				document.getElementById(this.id).style.cursor='wait';

			}
			else{
				this.debug(3);
			}
		}else{
			this.debug(2);
		}
		break;
		case 2:
		//Do nothing but change cursor
		document.body.style.cursor='wait';
		break;
		case 3:
		//Do nothing
		break;
		case 4:
		document.body.style.cursor='wait';

		case 5:
		fadeOut(this.id);
		break;
		default:
		this.debug(1);
		break;
		case 6:
		//change cursor and empty response container
		document.body.style.cursor='wait';
		document.getElementById(this.id).innerHTML='';
	}

}


Ajax.prototype.postRequest = function()

{
	if(!this.updating){

		this.updating=true;
		this.wait();
		var currAjax;
		var currRequest;
		currAjax=this;
		currRequest=this.createRequest();

		currRequest.open(this.method, this.target,this.sync)
		currRequest.setRequestHeader("Content-type", "application/x-www-form-urlencoded");
		currRequest.setRequestHeader("Content-length", this.params.length);
		currRequest.setRequestHeader("Connection", "close");
		currRequest.onreadystatechange = function()

		{

			if(currRequest.readyState == 4){
				currAjax.result = currRequest.responseText;
				currAjax.answer();
				currAjax.updating=false;
			}

		}
		currRequest.send(this.params);

	}

	else{
		return false;
	}

}





Ajax.prototype.getRequest = function()

{
	if(!this.updating){
		this.updating=true;
		this.wait();
		var currAjax;
		currAjax=this;
		var currRequest;
		currRequest=this.createRequest();

		currRequest.open(this.method, this.target+"?"+this.params,this.sync)

		currRequest.onreadystatechange = function()

		{

			if(currRequest.readyState == 4){
				currAjax.result = currRequest.responseText;
				currAjax.answer();
				currAjax.updating=false;
			}

		}

		currRequest.send(this.params);

	}
	else{
		return false;

	}


}

function fadeIn(id,opacity){
	var currOpacity = opacity || 0;

	if(document.getElementById(id)){
		if(fading[id]!='out'){
			fading[id]='in';
			if(currOpacity < 10) currOpacity++;
			document.getElementById(id).style.display='';
			document.getElementById(id).style.opacity = currOpacity/10;
			document.getElementById(id).style.filter = 'alpha(opacity=' + currOpacity*10 + ')';

			if(currOpacity<10){

				setTimeout('fadeIn("'+id+'",'+currOpacity+');',80);
			}
			else fading[id]='';
		}
		else{
			setTimeout('fadeIn("'+id+'",'+currOpacity+');',80);
		}


	}
	else return false;
}

function fadeOut(id,opacity,target){
	var currOpacity = opacity || 10;

	if(document.getElementById(id)){
		if(fading[id]!='in'){
			fading[id]='out';
			if(currOpacity > 0) currOpacity--;
			document.getElementById(id).style.opacity = currOpacity/10;
			document.getElementById(id).style.filter = 'alpha(opacity=' + currOpacity*10 + ')';
			if(currOpacity>0 && (!target || currOpacity>target)) {

				setTimeout('fadeOut("'+id+'",'+currOpacity+','+target+');',80);
			}
			else if(!target) {
				document.getElementById(id).style.display='none';

				fading[id]='';
			}
			else{
				fading[id]='';
			}
		}
		else setTimeout('fadeOut("'+id+'",'+currOpacity+','+target+');',80);
	}
}

var Canvas = function(type,id,width,height,top,left,zIndex,display)

{
	// Properties
	this.type			= type		|| 1;

	this.id				= id		|| 'auto_canvas_'+nextDiv++;

	this.widthProp		= width		|| '300px';

	this.heightProp		= height	|| '150px';

	this.topProp		= top		|| '200px';

	this.leftProp		= left		|| '400px';

	this.zIndexProp		= zIndex	|| nextZIndex++;

	this.contentProp	= '';

	this.maximized=false;

	this.temp;

	this.temp=new Array();

	this.draggable=true;

	canvas[this.id]=this;

	display= display || 'none';

	if(display!='none') this.displayProp='';
	else this.displayProp=display;

	if(document.getElementById(this.id)) {
		this.Canvas=document.getElementById(this.id);
		this.created=false;
	}else{
		this.New();
		this.Canvas=document.getElementById(this.id);
		this.created=true;
	}
	makeDraggable(this);

}

Canvas.prototype.block = function()
{
	this.draggable=false;
	document.getElementById(this.id).onmousedown=null;
	return true;
}

Canvas.prototype.unblock = function()
{
	this.draggable=true;
	makeDraggable(this);
	return true;
}


Canvas.prototype.New = function()
{
	var canvas;

	canvas="<table cellpadding=0 cellspacing=0 border=0  style='width:"+this.width()+";height:"+this.height()+";top:"+this.top()+";left:"+this.left()+";z-index:"+this.zIndex()+";position:absolute;display:"+this.display()+";' id='"+this.id+"'>	<tr><td>	<table cellpadding=0 cellspacing=0 border=0 width='100%' height='20px'>	<tr style='background-color:#CCCCCC;border:solid 1px #CCCCCC;'>	<td width='100%' height='100%'></td><td><a <a href='#' onclick='canvas[\""+this.id+"\"].maximize();return false;' class=button_link style='text-decoration:none;color:white'></a></td><td ><a href='#' onclick='canvas[\""+this.id+"\"].destroy();return false;' class=button_link style='text-decoration:none;color:white;padding-right:5px;'>CLOSE WINDOW&nbsp;</a></td></tr></table></td></tr><tr><td id=\""+this.id+"_content\" width='100%' height='100%' align=center style='background-color:white;border:solid 1px #CCCCCC;heigth:20px'>&nbsp;</td></table>";
	document.body.innerHTML+=canvas;
}

Canvas.prototype.show = function()
{
	fadeIn(this.id);
}

Canvas.prototype.hide = function()
{
	fadeOut(this.id);
}
Canvas.prototype.destroy = function()
{
	fadeOut(this.id);
	if(this.maximized){
		maximized=null;
		window.onscroll=null;
		document.body.style.overflow='auto';
	}
	delete canvas[this.id];
	delete canvasToMove[this.id];
	delete canvasToResize[this.id];
}

Canvas.prototype.width = function(width)
{
	if(width){
		if(document.getElementById(this.id)){
			document.getElementById(this.id).style.width=width;
		}else{

			this.widthProp=width;
		}
	}else{
		if(document.getElementById(this.id)){
			return document.getElementById(this.id).offsetWidth;
		}else{
			return this.widthProp;
		}
	}
}

Canvas.prototype.height = function(height)
{
	if(height){
		if(document.getElementById(this.id)){
			document.getElementById(this.id).style.height=height;
		}else{
			this.heightProp=height;
		}
	}else{
		if(document.getElementById(this.id)){
			return document.getElementById(this.id).offsetHeight;
		}else{
			return this.heightProp;
		}
	}
}

Canvas.prototype.top = function(top)
{
	if(top!=undefined){
		if(document.getElementById(this.id)){
			document.getElementById(this.id).style.top=top;
		}else{
			this.topProp=top;
		}
	}else{
		if(document.getElementById(this.id)){
			return parseInt(document.getElementById(this.id).style.top);
		}else{
			return this.topProp;
		}
	}
}

Canvas.prototype.left = function(left)
{
	if(left!=undefined){
		if(document.getElementById(this.id)){
			document.getElementById(this.id).style.left=left;
		}else{
			this.leftProp=left;
		}
	}else{
		if(document.getElementById(this.id)){
			return parseInt(document.getElementById(this.id).style.left);
		}else{
			return this.leftProp;
		}
	}
}

Canvas.prototype.zIndex = function(zIndex)
{
	if(zIndex){
		if(document.getElementById(this.id)){
			document.getElementById(this.id).style.zIndex=zIndex;
		}else{
			this.zIndexProp=zIndex;
		}
	}else{
		if(document.getElementById(this.id)){
			return document.getElementById(this.id).style.zIndex;
		}else{
			return this.zIndexProp;
		}
	}
}

Canvas.prototype.display = function(display)
{
	if(display || display===''){
		if(document.getElementById(this.id)){
			document.getElementById(this.id).style.display=display;
		}else{
			this.displayProp=display;
		}
	}else{
		if(document.getElementById(this.id)){
			return document.getElementById(this.id).style.display;
		}else{
			return this.displayProp;
		}
	}
}

Canvas.prototype.innerHTML = function(content,close)
{
	close=close || false;
	if(close){
		content+="<a href='#' onclick='canvas[\""+this.id+"\"].destroy();return false;' class=button_link style='text-decoration:none;'>CLOSE&nbsp;WINDOW&nbsp;</a>";
	}
	content=content.replace(/\/\/chiudi_canvas/g,"canvas['"+this.id+"'].destroy();");
	if(content || content==='' || content===0){
		if(document.getElementById(this.id+'_content')){
			document.getElementById(this.id+'_content').innerHTML=content;
		}else{
			this.contentProp=content;
		}
	}else{
		if(document.getElementById(this.id+'_content')){
			return document.getElementById(this.id+'_content').innerHTML;
		}else{
			return this.contentProp;
		}
	}
}

Canvas.prototype.place = function(to){
	if(to!=undefined){
		this.left(to.x);
		this.top(to.y);
		return true;
	}
	return false;
}
Canvas.prototype.focus = function(){
	this.zIndex(nextZIndex++);
	return true;
}

Canvas.prototype.move = function(to,time,speed){
	var currCanvas=this;
	speed=speed||20;
	time= time || 1200;
	var diffX;
	diffX=parseInt(to.x)-parseInt(this.left());
	var diffY;
	diffY=parseInt(to.y)-parseInt(this.top());
	var diffXParz;
	var diffYParz;
	diffXParz=Math.round(diffX*speed/time);
	diffYParz=Math.round(diffY*speed/time);
	var newX;
	var newY;
	newX=parseInt(this.left())+diffXParz;
	newY=parseInt(this.top())+diffYParz;
	this.place({x:newX,y:newY});
	time-=speed;
	if(diffXParz!=0 || diffYParz!=0){
		canvasToMove[this.id]=function (){
			currCanvas.move(to,time);
		}
		setTimeout('canvasToMove["'+this.id+'"]();',20);
	}else{
		canvasToMove[this.id]=null;
	}

}

Canvas.prototype.resize = function(width,height,speed,time,timeout,maximize){


	if(!timeout)fadeOut(this.id,'10',9)
	var currCanvas=this;
	speed=speed||50;
	time= time || 1000;
	var diffW;
	diffW=width-this.width();
	var diffH;
	diffH=height-this.height();

	diffWParz=Math.round(((diffW/2)*speed)/time);
	diffHParz=Math.round(((diffH/2)*speed)/time);

	if(diffWParz==0 && diffW>0)diffWParz=0.5;
	if(diffWParz==0 && diffW<0)diffWParz=-0.5;
	if(diffHParz==0 && diffH>0)diffHParz=0.5;
	if(diffHParz==0 && diffH<0)diffHParz=-0.5;

	var newX;
	var newY;
	var newWidth;
	var newHeight;
	newX=parseInt(this.left())-diffWParz;
	newY=parseInt(this.top())-diffHParz;


	newWidth=this.width()+(diffWParz*2)
	newHeight=this.height()+(diffHParz*2)
	this.place({x:newX,y:newY});
	this.width(newWidth+'px');
	this.height(newHeight+'px');
	time-=speed;
	if(diffW!=0 || diffH!=0 ){

		canvasToResize[this.id]=function (){
			currCanvas.resize(width,height,speed,time,1,maximize);
		}
		setTimeout('canvasToResize["'+this.id+'"]();',30);
	}else{
		if(!maximize)this.unblock();
		if(maximize &&(newX!=this.temp['scrollWidth']||newY!=this.temp['scrollHeight']))this.place({x:this.temp['scrollWidth'],y:this.temp['scrollHeight']});
		canvasToResize[this.id]=null;
		fadeIn(this.id,9);
	}

}

Canvas.prototype.maximize = function(quickly){
	if(!this.maximized){
		document.body.style.overflow='hidden';
		//document.body.style.width=document.body.clientWidth;
		//document.body.style.height=document.body.clientHeight;
		this.block();
		this.temp['scrollWidth']=document.body.scrollLeft;
		this.temp['scrollHeight']=document.body.scrollTop;
		//		alert('height:'+this.temp['scrollHeight']+' width:'+this.temp['scrollWidth'] );
		this.temp['width']=this.width();
		this.temp['height']=this.height();
		this.temp['top']=this.top();
		this.temp['left']=this.left();
		this.maximized=true;
		//		window.scrollTo(0,0);
		maximized=this;
		window.onscroll=function(e){window.scrollTo(maximized.temp['scrollWidth'],maximized.temp['scrollHeight']);};
		this.maximized=true;
		if(!quickly)this.resize(document.body.clientWidth,document.body.clientHeight,null,null,false,true);
		else{
			this.width(document.body.clientWidth);
			this.height(document.body.clientHeight);
			this.place({x:this.temp['scrollWidth'],y:this.temp['scrollHeight']});
			
			
		}
	}
	else{
		this.restore();
	}
}
Canvas.prototype.restore = function(){
	this.maximized=false;	
	
	//	this.width(this.temp['width']);
	//	this.height(this.temp['height']);
	//	this.top(this.temp['top']);
	//	this.left(this.temp['left']);
	window.onscroll=null;
	//	maximized=null;
	this.resize(this.temp['width'],this.temp['height']);
	//	document.body.scrollTop=this.temp['scrollHeight'];
	//	document.body.scrollLeft=this.temp['scrollWidth'];
	//	alert('height:'+this.temp['scrollHeight']+' width:'+this.temp['scrollWidth'] );
	window.scrollTo(this.temp['scrollWidth'],this.temp['scrollHeight']);

}
//fine canvas
function makeDraggable(object){
	if(object.left || object.top){
		document.getElementById(object.id).onmousedown=function(ev){
			//			mouseDown=true;
			object.focus();
			mouseOffset= getMouseOffset(document.getElementById(object.id), ev);
			if(mouseOffset.y<20) {
				dragObject = object;

				return false;
			}
			else{
				dragObject = null;
				return true;
			}

		}
	}
	else{
		object.onmousedown = function(ev){
			//			mouseDown=true;
			dragObject = this;
			mouseOffset= getMouseOffset(this,ev);
			return false
		}
	}
}

function mouseUp(ev){
	dragObject = null;
	//	mouseDown=false;
	mouseOffset= null;
	for(var currCanv in canvas){
		if(canvas[currCanv].draggable)makeDraggable(canvas[currCanv]);
	}
}

function mouseMove(ev){
	ev           = ev || window.event;
	var mousePos = mouseCoords(ev);
	if(dragObject && dragObject.place)dragObject.place({x:mousePos.x - mouseOffset.x,y:mousePos.y - mouseOffset.y});
	else if(dragObject){
		dragObject.style.position = 'absolute';
		dragObject.style.top      = mousePos.y - mouseOffset.y;
		dragObject.style.left     = mousePos.x - mouseOffset.x;

	}
	return false;
}

function mouseCoords(ev){
	if(ev.pageX || ev.pageY){
		return {x:ev.pageX, y:ev.pageY};
	}
	return {
		x:ev.clientX + document.body.scrollLeft - document.body.clientLeft,
		y:ev.clientY + document.body.scrollTop  - document.body.clientTop
	};
}


function getMouseOffset(target, ev){
	ev = ev || window.event;
	var mousePos  = mouseCoords(ev);
	if(target.x){
		return {x:mousePos.x - target.x, y:mousePos.y - target.y};
	}
	else{
		var docPos    = getPosition(target);
		return {x:mousePos.x - docPos.x, y:mousePos.y - docPos.y};
	}
}

function getPosition(e){
	var left = 0;
	var top  = 0;

	while (e.offsetParent){
		left += e.offsetLeft;
		top  += e.offsetTop;
		e     = e.offsetParent;
	}

	left += e.offsetLeft;
	top  += e.offsetTop;

	return {x:left, y:top};
}

function getElementsByAttribute(oElm, strTagName, strAttributeName, strAttributeValue){
	var arrElements = (strTagName == "*" && document.all)? document.all : oElm.getElementsByTagName(strTagName);
	var arrReturnElements = new Array();
	var oAttributeValue = (typeof strAttributeValue != "undefined")? new RegExp("(^|\\s)" + strAttributeValue + "(\\s|$)") : null;
	var oCurrent;
	var oAttribute;
	for(var i=0; i<arrElements.length; i++){
		oCurrent = arrElements[i];
		if(strAttributeName!='class')oAttribute = oCurrent.getAttribute(strAttributeName);
		else oAttribute = oCurrent.className;

		if(typeof oAttribute == "string" && oAttribute.length > 0){
			if(typeof strAttributeValue == "undefined" || (oAttributeValue && oAttributeValue.test(oAttribute))){
				arrReturnElements.push(oCurrent);
			}
		}
	}
	return arrReturnElements;
}

function counterBlock(ta,e){
	if(!e || !e.keyCode)
	e=window.event;
	if(document.getElementById('LEFT_'+ta)) var stop=(parseInt(document.getElementById('LEFT_'+ta).innerHTML))==0;
	if(!e || !e.keyCode || (e.keyCode!=8 && e.keyCode!=46))
	if(stop) return true;
	return false;
}

function addCounter(ta,e,max,form){
	form= form || 0;
	maxChars= max || 4000;
	var ie=(navigator.userAgent.toUpperCase().indexOf('MSIE'))>=0;
	if(!ie && (e.keyCode==8 || e.keyCode==46)){
		setTimeout("addCounter('"+ta+"',{keyCode:-99},"+maxChars+",'"+form+"');",100);
		return true;
	}
	if(document.getElementById('LEFT_'+ta)){
		var textarea=document.forms[form].elements[ta];
		var left= maxChars - textarea.value.length;
		if(left<0)return false;
		document.getElementById('LEFT_'+ta).innerHTML=left;
	}
	else if(document.forms[form]){
		if(document.forms[form].elements[ta]){
			var textarea=document.forms[form].elements[ta];
			var left= maxChars - textarea.value.length;
			if(left<0)return false;
			insertHtmlAfter('<br>You have <b><span id="LEFT_'+ta+'">'+left+'</span></b> characters remaining',textarea);

		}

	}
	return true;
}

insertHtmlAfter = function( html, element )
{

	if (element && element.insertAdjacentHTML )	// IE
	element.insertAdjacentHTML( 'afterEnd', html ) ;
	else								// Gecko
	{
		var oRange = document.createRange() ;
		oRange.setStartAfter( element ) ;
		var oFragment = oRange.createContextualFragment( html );
		element.parentNode.insertBefore( oFragment, element.nextSibiling ) ;
	}
}
