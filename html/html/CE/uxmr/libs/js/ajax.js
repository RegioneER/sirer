

function pageWidth() {return window.innerWidth != null? window.innerWidth : document.documentElement && document.documentElement.clientWidth ?       document.documentElement.clientWidth : document.body != null ? document.body.clientWidth : null;} 
function pageHeight() {return  window.innerHeight != null? window.innerHeight : document.documentElement && document.documentElement.clientHeight ?  document.documentElement.clientHeight : document.body != null? document.body.clientHeight : null;} 
function posLeft() {return typeof window.pageXOffset != 'undefined' ? window.pageXOffset :document.documentElement && document.documentElement.scrollLeft ? document.documentElement.scrollLeft : document.body.scrollLeft ? document.body.scrollLeft : 0;} 
function posTop() {return typeof window.pageYOffset != 'undefined' ?  window.pageYOffset : document.documentElement && document.documentElement.scrollTop ? document.documentElement.scrollTop : document.body.scrollTop ? document.body.scrollTop : 0;} 
function posRight() {return posLeft()+pageWidth();} 
function posBottom() {return posTop()+pageHeight();}


	function IsNumeric(sText)
		{
		   var ValidChars = "0123456789.";
		   var IsNumber=true;
		   var Char;
		
		 
		   for (i = 0; i < sText.length && IsNumber == true; i++) 
		      { 
		      Char = sText.charAt(i); 
		      if (ValidChars.indexOf(Char) == -1) 
		         {
		         IsNumber = false;
		         }
		      }
		   return IsNumber;
		   
		   }
	
function createRequestObject() {
			var ro;
			var browser = navigator.appName;
			if(browser == "Microsoft Internet Explorer"){
				ro = new ActiveXObject("Microsoft.XMLHTTP");
			}else{
				ro = new XMLHttpRequest();
			}
			return ro;
		}
		var ritorno=true;
		var http = createRequestObject();
		
		function show_hide(id_tag){
			if (document.getElementById(id_tag).style.display!='') document.getElementById(id_tag).style.display='';
			else document.getElementById(id_tag).style.display='none';
		}
		
		function ajax_call(html_id, param) {
			if (ritorno){
			ritorno=false;
			
			call='ajax.php?HTML_ID='+html_id+'&'+param;
			//alert(call);
			//document.getElementById('debug').innerHTML+=document.write('<a href="'+call+'" target="_new">debug<\/a>');
			
			document.getElementById(html_id).innerHTML="<img src=\"/images/loading.gif\">";
			http.open('get', call);
			http.onreadystatechange = handleResponse;
			http.send(null);
			 } else {
	      setTimeout('ajax_call("'+html_id+'", "'+param+'")', 10);
	   }
		}
		
		
		function ajax_send_form(form_id) {
				
				ritorno=false;
				//call='ajax.php?HTML_ID='+html_id+'&'+param;
				//alert(call);
				//alert (pageHeight()+' - '+posBottom());
				if (document.getElementById('saving')){
					var top=posBottom()-(pageHeight()/2)-40;
					left=(pageWidth()/2)-100;
					document.getElementById('saving').style.left=''+left+'px';
					document.getElementById('saving').style.top=''+top+'px';
					
					document.getElementById('saving').style.display='';
					
				}
				//document.getElementById('debug').innerHTML+=document.write('<a href="'+call+'" target="_new">debug<\/a>');
				el=document.forms[form_id].elements;
				var str='';
				for (i=0;i<el.length;i++){
					if (el[i].name!='salva' && el[i].name!='invia'){
						
						if (el[i].length>0 && el[i].type!='select-one') {
							//alert (i+' - '+el[i].name+' - '+el[i].type);
							for (c=0;i<el[i].length;c++){
								//alert (c+' - '+el[i].name+' - '+el[i].type);
								if (el[i][c].checked) str+=el[i].name+'='+el[i][c].value+'&';
							}
						}
						else {
							//alert (i+' - '+el[i].name+' - '+el[i].type);
							if (el[i].type=='checkbox' || el[i].type=='radio') {
								//alert (i+' - '+el[i].name+' - '+el[i].type);
								if (el[i].checked) {
									//alert (el[i].name+' - '+el[i].value+' - '+el[i].checked);
									str+=el[i].name+'='+el[i].value+'&'; 
								}
								else {
									if (el[i].type=='checkbox')	str+=el[i].name+'=0&'; 
								}
								
							}
							else str+=el[i].name+'='+el[i].value+'&';
						}
					}
					//alert (i+' - '+el[i].name+' - '+el[i].type);
				}
				//return false;
				
				url='index.php';
				//document.getElementById('debug').innerHTML+=document.write('<a href="'+call+'" target="_new">debug<\/a>');
				//return false;
				//document.getElementById(html_id).innerHTML=document.write('<img src="/images/loading.gif">');

				str+='&ajax_call=yes';		
				call=url+'?'+str;
				document.getElementById('debug').innerHTML+='<a href="'+call+'" target="_new">debug<\/a>';
				//return false;
				http.onreadystatechange = alertContents;
			    http.open('POST', url, true);
			    
			    http.setRequestHeader("Content-type", "application/x-www-form-urlencoded");
			    http.setRequestHeader("Content-length", str.length);
			    http.setRequestHeader("Connection", "close");
			    http.send(str);
   }

   function alertContents() {
      if (http.readyState == 4) {
         if (http.status == 200) {
            //alert(http.responseText);
            //return false;
            var result = http.responseText;
            if (result.match("link_to:")){
            	resp=result.split(":");
            	//if (resp[1]!='') window.location.href=resp[1];
            	document.forms[0].submit();
            }
            if (result.match("Error:")){
            	resp=result.split(":");
            	resp2=resp[1].split("#error#");
            	document.getElementById('saving').style.display='none';
            	if (resp2[1])
            	alert('Errore:'+resp2[1]);
            	if (document.forms[0].elements[resp2[0]]) {
            		document.forms[0].elements[resp2[0]].focus();
            		document.forms[0].elements[resp2[0]].select();
            	}
            	//else 
            	//document.forms[0].elements[resp2[0]][0].select();
            }
            //document.getElementById('myspan').innerHTML = result;            
            //alert(result);
         } else {
            alert('There was a problem with the request.');
         }
      }
   }
	
		
		function handleResponse() {
			if(http.readyState == 4){
				var response = http.responseText;
				if (response.match("#DIV#")){
					resp=response.split("#DIV#");
					resp[0]=resp[0].replace('\n','');
					document.getElementById(resp[0]).innerHTML = resp[1];
				}
				ritorno=true;
				}
		}
		
		 
	
