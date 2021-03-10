var approvedMetadata, quickSave;

if(!console) {
	var console = {
		log : function() {
		}
	};
}
function alertError() {
	console.log('Errore nel caricamento');
}

function pad(n, width, z) {
  z = z || '0';
  n = n + '';
  return n.length >= width ? n : new Array(width - n.length + 1).join(z) + n;
}


(function ($, window) {
    var guid=100000000000000;
    var elements=[];
    var additionals=[];
    var updatedElements={};
    var labels=[];
    labels[1]=[];
    labels[2]=[];
    var ids=[];

    $.axmr={};
    $.axmr.guid=function(incoming,label,label2,additionalFlag){

        if($.isPlainObject(incoming) || $.isArray(incoming)){
        	currGuid=-1;
        	if(incoming.guid){
        		currGuid=incoming.guid;
        		if(!additionalFlag && elements[currGuid]){
        			elements[currGuid]=incoming;
        			delete additionals[currGuid];
        		}
        	}
        	else{
	        	var search=function(obj,idx){
	        		currGuid=idx;
	    			return (obj===incoming) ;
	    		}
	    		$.grep(elements,search);
    		}
            
            if(currGuid==-1){
                currGuid=++guid;
                incoming.guid=currGuid;
                if(additionalFlag){
                	additionals[currGuid]=incoming;
                }else{
                elements[currGuid]=incoming;
            }
                
            }
            if(incoming['id']){
                ids[incoming['id']]=currGuid;
            }
            if(label!==undefined){
                labels[1][currGuid]=label;
            }
            if(label2!==undefined){
                labels[2][currGuid]=label2;
            }
            return currGuid;
        }else{
        	if(elements[incoming]){
            return elements[incoming];
        	}else if(additionals[incoming]){
        		return additionals[incoming];
        	}else{
        		return undefined;
        }
        }
    };
    $.axmr.guidAdditional=function(incoming,label,label2){
    	return this.guid(incoming,label,label2,true);
    };
    $.axmr.getAllElements=function(){
        return elements;
    };
    $.axmr.getAllAdditionals=function(){
        return additionals;
    };
    $.axmr.label=function(incoming,index){
        if(!elements[incoming]){
            return incoming;
        }
        if(!index){
           index=1;
        }
        if(labels[index][incoming]===undefined) return "";
        return labels[index][incoming];
    };
    $.axmr.searchById=function(id){
         return ids[id];
    };
    $.axmr.getById=function(id){
         return elements[ids[id]];
    };
    $.axmr.deselectGrid=function(id){
        $(id).handsontable('deselectCell');
        setTimeout(function(){$(id).handsontable('deselectCell');},500);
    };
    $.axmr.setUpdated=function(incoming, parent){
    	var obj;
    	if($.isPlainObject(incoming) || $.isArray(incoming)){
    		if(!incoming.guid){
    			this.guidAdditional(incoming);
    		}
    		obj=incoming;
    	}
    	else{
    		obj=this.guid(incoming);
    	}
    	if(parent && !obj.parent){
    		obj.parent=parent;
    	}
    	obj.updateCheck=1;
    	updatedElements[obj.guid]=true;
    	notifySingle('budgetChange','Attenzione, le modifiche effettuate saranno valide solo dopo aver salvato i dati','warning','icon-warning-sign');
    	return obj;
    };
    $.axmr.setDeleted=function(incoming){
    	var obj;
    	obj=this.setUpdated(incoming);
    	obj.deleted="1";
    	return obj;
    };
    $.axmr.countUpdated=function(){    	
    	return Object.keys(updatedElements).length;
    };
})(jQuery);

function clone(src) {
	function mixin(dest, source, copyFunc) {
		var name, s, i, empty = {};
		for(name in source) {
			// the (!(name in empty) || empty[name] !== s) condition avoids copying properties in "source"
			// inherited from Object.prototype.  For example, if dest has a custom toString() method,
			// don't overwrite it with the toString() method that source inherited from Object.prototype
			s = source[name];
			if(!( name in dest) || (dest[name] !== s && (!( name in empty) || empty[name] !== s))) {
				dest[name] = copyFunc ? copyFunc(s) : s;
			}
		}
		return dest;
	}

	if(!src || typeof src != "object" || Object.prototype.toString.call(src) === "[object Function]") {
		// null, undefined, any non-object, or function
		return src;
		// anything
	}
	if(src.nodeType && "cloneNode" in src) {
		// DOM Node
		return src.cloneNode(true);
		// Node
	}
	if( src instanceof Date) {
		// Date
		return new Date(src.getTime());
		// Date
	}
	if( src instanceof RegExp) {
		// RegExp
		return new RegExp(src);
		// RegExp
	}
	var r, i, l;
	if( src instanceof Array) {
		// array
		r = [];
		for( i = 0, l = src.length; i < l; ++i) {
			if( i in src) {
				r.push(clone(src[i]));
			}
		}
		// we don't clone functions for performance reasons
		//      }else if(d.isFunction(src)){
		//          // function
		//          r = function(){ return src.apply(this, arguments); };
	} else {
		// generic objects
		r = src.constructor ? new src.constructor() : {};
	}
	return mixin(r, src, clone);

}

function prepareMetadataForPost(inMetadata) {

	var metadata = $.extend(true, {}, inMetadata);
	var quickMetadata = {};
	$.each(metadata, function(key, value) {
		if($.isPlainObject(value[0])) {
			metadata[key] = value[0].id.toString();
		} else {
			if($.isArray(value)) {
				if(value[0] === null || value[0] === undefined)
					metadata[key] = "";
				else
					metadata[key] = value[0].toString();
			} else {
				metadata[key] = value.toString();
			}
		}
		if(approvedMetadata && $.isArray(approvedMetadata) && $.inArray(key, approvedMetadata) > -1) {
			quickMetadata[key] = metadata[key];
		}
	});
	if(quickSave) {
		return quickMetadata;
	} else {
		return metadata;
	}
}

function prepareElementForPost(element) {
	element = $.extend(true, {}, element);
	$.each(element, function(property, value) {
		if(value === null || value === undefined)
			element[property] = "";
		else if(!$.isPlainObject(value) && !$.isArray(value))
			element[property] = value.toString();
	});
	if(element.metadata)
		element.metadata = prepareMetadataForPost(element.metadata);
	return element;
}
function updateElement(element) {
	var metadata = prepareMetadataForPost(element.metadata);

	return $.ajax({
		method : 'POST',
		url : '../../rest/documents/update/' + element.id,
		data : metadata
	});

}

function saveElement(element, parent) {
	if(element.id) {
		return updateElement(element);
	} else {
		var metadata = prepareMetadataForPost(element.metadata);
		metadata.parentId = parent;
		return $.ajax({
			method : 'POST',
			url : '../../rest/documents/save/' + element.type.id,
			data : metadata
		}).done(function(data) {
			element.id = data.ret;
		});
	}
}

function findElement(element, parent) {

	var metadata = prepareMetadataForPost(element.metadata);
	metadata.parentId = parent;
	return $.ajax({
		method : 'POST',
		url : '../../rest/documents/searchByExample/' + element.type.id,
		data : metadata
	}).done(function() {
		console.log('Found!!!');
	}).fail(function() {
		console.log('error', element);
	});
}

function deleteElement(element) {
	if(element && element.id)
		return $.ajax({
			url : '../../rest/documents/delete/' + element.id,

		}).done(function() {
			console.log('DELETED');
		}).fail(alertError);
}

function firstLine(testo) {
	testo = testo.replace(/(\n.*)*$/g, '');

	return $.trim(testo);
}

function getDato(dato) {
	if($.isArray(dato)) {
		return dato[0];
	} else {
		return dato;
	}
}

function formToElement(form,element){
	$('#'+form).find(':input').each(function (){
		var label=$(this).attr('name');
		//label=label.replace(/^[^_]*_/,'');
		if(empties[element.type.id].metadata[label]!=undefined){
			if($(this).attr('type')=='checkbox'){
				if(this.checked) element.metadata[label]=1;//$(this).val(); risulta vuoto indagare come mai viene svuotato
				else  element.metadata[label]='';
			}
			else{
				element.metadata[label]=$(this).val();
			}
		}
		else{
		console.log(label);
		console.log(empties[element.type.id].metadata[label]);
		}
		$.axmr.setUpdated(element);
		console.log("controlla",element);
	});
	return element;
}

function elementToForm(element, form) {
	$('#' + form).find(':input').each(function() {
		var label = $(this).attr('name');
		//label=label.replace(/^[^_]*_/,'');
		if($(this).attr('type') == 'checkbox') {
			if(getDato(element.metadata[label]))
				this.checked = true;
			else
				this.checked = false;
		} else {
			var dato = getDato(element.metadata[label]);
			if(dato !== undefined && dato !== null)
				$(this).val(dato);
			else if(element.metadata.hasOwnProperty(label))
				$(this).val('');
		}
	});
}

Number.prototype.formatMoney = function(c, d, t, v){
	var n = this, 
    c = isNaN(c = Math.abs(c)) ? 2 : c, 
    d = d == undefined ? "," : d, 
    t = t == undefined ? "." : t, 
    v = v == undefined ? "&euro;" : v, 
    s = n < 0 ? "-" : "", 
    i = parseInt(n = Math.abs(+n || 0).toFixed(c)) + "", 
    j = (j = i.length) > 3 ? j % 3 : 0;
   return s + (j ? i.substr(0, j) + t : "") + i.substr(j).replace(/(\d{3})(?=\d)/g, "$1" + t) + (c ? d + Math.abs(n - i).toFixed(c).slice(2) : "")+" "+v;
 };
 
 String.prototype.formatMoney = function(c, d, t, v){
	   var n = parseFloat(this);		
	   if(isNaN(n)) return this;
	   return n.formatMoney(c, d, t, v);
};