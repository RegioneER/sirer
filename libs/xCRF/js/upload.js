/*********
* Javascript for file upload demo
* Copyright (C) Tomas Larsson 2006
* http://tomas.epineer.se/

* Licence:
* The contents of this file are subject to the Mozilla Public
* License Version 1.1 (the "License"); you may not use this file
* except in compliance with the License. You may obtain a copy of
* the License at http://www.mozilla.org/MPL/
* 
* Software distributed under this License is distributed on an "AS
* IS" basis, WITHOUT WARRANTY OF ANY KIND, either express or
* implied. See the License for the specific language governing
* rights and limitations under the License.
*/
 var uploads_in_progress = 0;
 function beginAsyncUpload(ul,sid,postform,id_ret) {		
      ul.form.submit();
    	uploads_in_progress = uploads_in_progress + 1;
    	var pb = document.getElementById(ul.name + "_progress");
    	pb.parentNode.style.display='block';
    	new ProgressTracker(sid,{
    		progressBar: pb,
    		onComplete: function() {
    			var inp_id = pb.id.replace("_progress","");
    			uploads_in_progress = uploads_in_progress - 1;
    			var inp = document.getElementById(inp_id);
    			if(inp) {
    				inp.value = sid;
    			}
    			submitUpload(postform,id_ret);
    			pb.parentNode.style.display='none';
    		},
    		onFailure: function(msg) {
    			pb.parentNode.style.display='none';
    			alert(msg);
    			uploads_in_progress = uploads_in_progress - 1;
    		}
    	});
    	
    }
    
    function submitUpload(postform,id_ret) {
      if(uploads_in_progress > 0) {
       // alert("File upload in progress. Please wait until upload finishes and try again.");
      } else {
       el=document.forms[postform].elements;
				var str='';
				for (i=0;i<el.length;i++){
					if (el[i].name!='salva' && el[i].name!='invia'){
						
						if (el[i].length>0 && el[i].type!='select-one') {
							for (c=0;i<el[i].length;c++){
								if (el[i][c].checked) str+=el[i].name+'='+el[i][c].value+'&';
							}
						}
						else {
							if (el[i].type=='checkbox' || el[i].type=='radio') {
								if (el[i].checked) {
									str+=el[i].name+'='+el[i].value+'&'; 
								}
								else {
									if (el[i].type=='checkbox')	str+=el[i].name+'=0&'; 
								}
								
							}
							else str+=el[i].name+'='+el[i].value+'&';
						}
					}
				}
				str+='&HTML_ID='+id_ret;	
				url='ajax.php';
				call=url+'?'+str;
				http.open('POST', call);
				http.onreadystatechange = handleResponse;
				http.send(null);
				//http.onreadystatechange = handleResponse;
			    //http.open('POST', url, true);
			    //http.setRequestHeader("Content-type", "application/x-www-form-urlencoded");
			    //http.setRequestHeader("Content-length", str.length);
			    //http.setRequestHeader("Connection", "close");
			    //http.send(str);
      }
    }


function PeriodicalAjax(url, parameters, frequency, decay, onSuccess, onFailure) {
	function createRequestObject() {
		var xhr;
		try {
			xhr = new XMLHttpRequest();
		}
		catch (e) {
			xhr = new ActiveXObject("Microsoft.XMLHTTP");
		}
		return xhr;
	}
	
	function send() {
		if(!stopped) {
			xhr.open('post', url, true);
			xhr.setRequestHeader('Content-Type','application/x-www-form-urlencoded');
			xhr.onreadystatechange = function() { self.onComplete(); };
			xhr.send(parameters);
		}
	}
	
	this.stop = function() {
		stopped = true;
		clearTimeout(this.timer);
	}
	
	this.start = function() {
		stopped = false;
		this.onTimerEvent();
	}
	
	this.onComplete = function() {
		if(this.stopped) return false;
		if ( xhr.readyState == 4) {
			if(xhr.status == 200) {
				if(xhr.responseText == lastResponse) {
					decay = decay * originalDecay;
				} else {
					decay = 1;
				}
				lastResponse = xhr.responseText;
				if(onSuccess instanceof Function) {
					onSuccess(xhr);
				}
				this.timer = setTimeout(function() { self.onTimerEvent(); }, decay * frequency * 1000);
			} else {
				if(onFailure instanceof Function) {
					onFailure(xhr);
				}
			}
		}
	}
	
	this.getResponse = function() {
		if(xhr.responseText) {
			return xhr.responseText;
		}
	}
	
	this.onTimerEvent = function() {
		send();
	}
	
	var self = this;
	var stopped = false;
	var originalDecay = decay || 1.2;
	decay = originalDecay;
	var xhr = createRequestObject();
	var lastResponse = "";
	this.start();
}

function ProgressTracker(sid, options) {

	this.onSuccess = function(xhr) {
		if(parseInt(xhr.responseText) >= 100) {
			periodicalAjax.stop();
			if(options.onComplete instanceof Function) {
				options.onComplete();
			}
		} else if(xhr.responseText && xhr.responseText != lastResponse) {
			if(options.onProgressChange instanceof Function) {
				options.onProgressChange(xhr.responseText);
			}
			if(options.progressBar && options.progressBar.style) {
				options.progressBar.style.width = parseInt(xhr.responseText) + "%";
			}
		}
	}
	
	this.onFailure = function(xhr) {
		if(options.onFailure instanceof Function) {
			options.onFailure(xhr.responseText);
		} else {
			alert(xhr.responseText);
		}
		periodicalAjax.stop();
	}

	var self = this;
	var lastResponse = -1;
	options = options || {};
	var url = options.url || 'ajax.php';
	var frequency = options.frequency || 0.5;
	var decay = options.decay || 2;
	var periodicalAjax = new PeriodicalAjax(url, 'sid=' + sid + '&SHOW_PROGRESS_BAR=yes', frequency, decay, function(request){self.onSuccess(request);},function(request){self.onFailure(request);});
}