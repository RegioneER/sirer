//enter your message in this part, including any html tags
var message='<!--<img src="../images/test.GIF">--><p><b><font size=4>Attenzione! Questo e\' un sito di TEST, i dati contenuti non sono da considerarsi in alcun modo reali.</font><br><font color=red>Questo sito non puo\' essere utilizzato per l\'inserimento delle schede dello studio.</font></b></p>'

//enter a color name or hex value to be used as the background color of the message. Don't use hash # sign
var backgroundcolor=""

///////////////do not edit below this line////////////////////////////////////////

<!-- script distributed by http://www.hypergurl.com




if (document.all){
document.write('<span id="topmsg" style="position:absolute;visibility:hidden">'+message+'</span>')
}


//###sub setmessage###
function setmessage(){
document.all.topmsg.style.left=document.body.offsetWidth/2-document.all.topmsg.offsetWidth/2
document.all.topmsg.style.top=0
document.all.topmsg.style.backgroundColor=backgroundcolor
document.all.topmsg.style.visibility="visible"
}
//###endsub###


//###sub stringaValida###
	function stringaValida(str) {
    var patternvalido = ".test.";
    var reg = new RegExp(patternvalido);
    return str.match(reg);
    //return false;
	 };
//###endsub###

if (stringaValida(window.location.href)) setmessage();

function popitup(url)
{
	newwindow=window.open(url,'help','height=200,width=150');
	if (window.focus) {newwindow.focus()}
	return false;
}

function guida(momento){
	var fup = new RegExp('Follow');
	var arr = new RegExp('Arruolamento');
	var reg = new RegExp('Registrazione');
	if (momento.match(fup)) window.open('../template/help_follow_up.htm','help','scrollbars=1, resizable=yes, height=600, width=600');
	if (momento.match(arr)) window.open('../template/help_arruolamento.htm','help','scrollbars=1, resizable=yes, height=600, width=600');
	if (momento.match(reg)) window.open('../template/help_registrazione.htm','help','scrollbars=1, resizable=yes, height=600, width=600');
}

//###sub href_build####
function href_build(dest){
	if (stringaValida(window.location.href)) window.location.href=dest;
	else window.location.href='https://iss.cineca.org/'+dest;
}
//###endsub###

//###sub staff_area###
function staff_area(){
	if (stringaValida(window.location.href)) document.write('<font color=gray>Staff Area</font>');
	else document.write('<a href="https://iss.cineca.org/staff">Staff Area</a>');
}
//###endsub###

