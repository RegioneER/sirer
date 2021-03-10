setInterval(function(){
    var totali=$('.totaleCTC');
    totali.each(function(){$(this).parent().append(this);});
},1500);

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
        clearSingleNotification('success');
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
    $.axmr.resetUpdated=function(){
        return (updatedElements={});
    };
})(jQuery);
Number.prototype.formatMoney = function(c, d, t, v){
    var n = this,
        c = isNaN(c = Math.abs(c)) ? 2 : c,
        d = d == undefined ? "," : d,
        t = t == undefined ? "." : t,
        v = v == undefined ? "&euro;" : v,
        s = n < 0 ? "-" : "",
        i = parseInt(n = Math.abs(+n || 0).toFixed(c)) + "",
        j = (j = i.length) > 3 ? j % 3 : 0;
    return v+ " " + s + (j ? i.substr(0, j) + t : "") + i.substr(j).replace(/(\d{3})(?=\d)/g, "$1" + t) + (c ? d + Math.abs(n - i).toFixed(c).slice(2) : "");
};

String.prototype.formatMoney = function(c, d, t, v){
    var n = parseFloat(this);
    if(isNaN(n)) return this;
    return n.formatMoney(c, d, t, v);
};

String.prototype.unformatMoney = function(){
    var n = this.replace("&euro;",'');
    n = n.replace("€",'');
    n = n.replace(/\./g,'')
    n = n.replace(",",'.');;
    n = parseFloat(n);
    if(isNaN(n)) return this;
    return n;
};
var cantDelete=false;
var delayedCalcolaTotali;
var isClosed=false;
var lastCostRow, lastCostCol;
var markup=0;
var pazienti=0;
var quickSave=false;
var approvedMetadata=new Array('Prestazioni_CDC','Prestazioni_UOC','Tariffario_Solvente','Tariffario_SSN','TimePoint_Descrizione','TimePoint_NumeroVisita','TimePoint_Tempi','TimePoint_DurataCiclo','Ricovero_Ordinario','Ricovero_Straordinario','Ricovero_Ambulatoriale','Ricovero_Telefonico','TimePoint_Note','tp-p_Checked','tp-p_TimePoint','tp-p_Prestazione','Rimborso_Rimborsabilita');
var costiInit=false;
var tariffarioAlpi=new Array();
var tariffarioSSN=new Array();
var dizPrestazioni=new Array();

var folderTp=null;
var folderPrestazioni=null;
var folderTpxp=null;
var folderPxp=null;
var folderPxs=null;
var folderBudgetStudio=null;
var folderPxsCTC=null;
var folderPxpCTC=null;
var folderPassthroughCTC=null;
var folderBracci=null;
var rowAltro=null;
var totalePaziente=0;
var totaleStudio=0;

var timer;

function updateIds(map){
    var currElement;
    if(map &&  ($.isArray(map) || $.isPlainObject(map))){
        $.each(map, function(guid,id){
            currElement=$.axmr.guid(guid);
            if(currElement &&  ($.isPlainObject(currElement) || $.isArray(currElement))){
                currElement.id=id;
            }
        });
    }
    $.axmr.resetUpdated();
}
var resizeSingleGrid=function(that){
    var HOT=$(that).handsontable('getInstance');
    var oldSettings=HOT.getSettings();
    width=$(that).parent().width();
    if(width!=oldSettings.width){
        console.log('aggiorno',oldSettings.width,width,that);
        update={width:width};
        HOT.updateSettings(update);
    }
    else{
        console.log('non aggiorno',width,that);
    };

};
var resizeGrids=function(){
    $('.handsontable:visible').each(function(){var that=this;resizeSingleGrid(that)});
}

var hidebutton=function(){
    if($("#dizionario").val()){
        $('#Prestazioni_Altro').hide();
    }
    else{
        $('#Prestazioni_Altro').show();
    }

};

$(document).ready(function(){
    $('input[type=text]').on('keyup',function (ev){

        var original=$(this).val();
        var replaced=$.trim(original).replace(/,/,'.');
        if(isNaN(original) && !isNaN(replaced)){
            $(this).val(replaced);
        }
    });
    $('#Prestazioni_prestazione').change(
        hidebutton
    ).keypress(hidebutton);
    $('#Prestazioni_CDC').change(
        hidebutton
    ).keypress(hidebutton);
    $('#Prestazioni_Altro').hide();
    $('#tabs li').click(function(){
        if(timer){
            clearTimeout(timer);
        }
        timer=setTimeout(resizeGrids,100);
    });
    $(window).resize(function() {
        if(timer){
            clearTimeout(timer);
        }
        timer=setTimeout(resizeGrids,400);
    });
    setTimeout(resizeGrids,100);
});

function newBudgetStudio(form){
    var element=$.extend(true,{},emptyBudgetCTC);
    //element=formToElement(form,element);
    loadingScreen("Salvataggio in corso...", "/CPRMS/app/int/images/loading.gif");
    $.when(saveElement(element,folderBudgetStudio)).then(function(data){
        window.location.href='../custom/budget_studio/'+data.ret;
    });
}

function compareBudgetStudio(){
    var confronto1=$('[name=confronto1]:checked').val();
    var confronto2=$('[name=confronto2]:checked').val();
    if(!confronto1 || !confronto2 || confronto1==confronto2){
        alert('Selezionare i budget da confrontare');
        return;
    }
    location.href='../custom/budgetcompare/'+folderBudgetStudio+'?confronto1='+confronto1+'&confronto2='+confronto2;
}

function openClone(id,toClone){
    if(toClone){
        $('#clone_id2').val(id);
        $('#clone2-dialog-form').dialog('open');
    }
    else{
        $('#clone_id').val(id);
        $('#clone-dialog-form').dialog('open');
    }
}

function openCloneOtherStudy(id){
    $('#clone_id3').val(id);
    $('#clone3-dialog-form').dialog('open');
}

function cloneObj(id,data,toClone){



    loadingScreen("Salvataggio in corso...", "${baseUrl}/int/images/loading.gif");

    var actionUrl="../../rest/documents/"+id+"/budgetClone";

    console.log(data);

    $.ajax({
        type: "GET",
        url: actionUrl,
        data:data,
        success: function(obj){
            if (obj.result=="OK") {
                if ($('#container:checked').size()>0) $('#isContainer').show();
                else $('#isContainer').hide();
                loadingScreen("Clonazione effettuata", baseUrl+"/int/images/green_check.jpg",2000);
                if (obj.redirect){
                    if(toClone )
                        window.location.href=obj.redirect;
                    else
                        window.location.href='../custom/budget_studio/'+obj.ret;
                }
            }else {
                loadingScreen("Errore clonazione!", baseUrl+"/int/images/alerta.gif", 3000);
            }
        },
        error: function(){
            loadingScreen("Errore clonazione!", baseUrl+"/int/images/alerta.gif", 3000);
        }
    });
}
function cloneObjOtherStudy(id,data,toClone,idStudio){

    loadingScreen("Salvataggio in corso...", "${baseUrl}/int/images/loading.gif");

    var actionUrl="../../rest/documents/"+id+"/budgetClone/"+idStudio;

    console.log(data);

    $.ajax({
        type: "GET",
        url: actionUrl,
        data:data,
        success: function(obj){
            if (obj.result=="OK") {
                if ($('#container:checked').size()>0) $('#isContainer').show();
                else $('#isContainer').hide();
                loadingScreen("Clonazione effettuata", baseUrl+"/int/images/green_check.jpg",2000);
                if (obj.redirect){
                    if(toClone )
                        window.location.href=obj.redirect;
                    else
                        window.location.href='../custom/budget_studio/'+obj.ret;
                }
            }else {
                loadingScreen("Errore clonazione!", baseUrl+"/int/images/alerta.gif", 3000);
            }
        },
        error: function(){
            loadingScreen("Errore clonazione!", baseUrl+"/int/images/alerta.gif", 3000);
        }
    });
}

function salvaPrestazione(button){
    var data={};
    var inputs=$(button).closest('form').find(':input');
    inputs.each(function(){
        data[this.name]=this.value;
    });
    data['new']='true';
    data['Prestazioni_Altro']='Salva prestazione nel dizionario';
    $.ajax(
        {
            method:'post',
            url:'/dizionari/prestazioni.php',
            data:data
        }
    ).done(function(){
        console.log('ok');
        alert('Prestazione salvata');
    }).fail(function(){
        console.log('no ok');
        alert('Errore nel salvataggio provare più tardi.');
    });

}

function prepareElementForPost(element){
    element=$.extend(true,{},element);
    $.each(element, function(property,value){
        if(value===null || value===undefined) element[property]="";
        else if(!$.isPlainObject(value) &&  !$.isArray(value) ) element[property]=value.toString();
    });
    if(element.metadata)element.metadata=prepareMetadataForPost(element.metadata);
    return element;
}

function saveGrid(grid,url,bulk){
    grid = grid || '#example';
    url = url || '../../rest/documents/updateGrid';
    var layout=$.extend(true,[],$(grid).data('handsontable').getData());
    var elements=$.extend(true,{},$.axmr.getAllElements());
    var additionals=$.extend(true,{},$.axmr.getAllAdditionals());
    var folders={};
    var coordinates={"x":"tp-p_TimePoint","y":"tp-p_Prestazione","row":"Prestazioni_row","col":"TimePoint_col"};
    var updatedElementsCount=$.axmr.countUpdated()+"";
    folders[emptyTimePoint.type.id]=folderTp;
    folders[emptyPrestazione.type.id]=folderPrestazioni;
    folders[emptytpxp.type.id]=folderTpxp;
    folders[emptyCostoAggiuntivo.type.id]=folderCostiAggiuntivi;
    $.each(layout, function (row,cols){
        $.each(cols,function(col,value){
            if(value)layout[row][col]=value.toString();
        });
    });

    $.each(elements,function(idx,element){
        elements[idx]=prepareElementForPost(element);
    });
    $.each(additionals,function(idx,element){
        additionals[idx]=prepareElementForPost(element);
    });
    if(bulk){
        additionals=$.extend(true,additionals,elements);
        elements={};
    }

    folders=prepareElementForPost(folders);
    var grid=$.extend(true,{},{"layout":layout,"elements":elements,"additionals":additionals,"folders":folders,"coordinates":coordinates,"updatedElementsCount":updatedElementsCount});
    var data={"grid":JSON.stringify(grid)};
    return $.ajax({
        method:'POST',
        url:url,
        data:data
    });
}
function saveBulk(){
    return saveGrid('#costi','../../../rest/documents/updateGrid',true);
}

function saveBulkElements(url){

    url = url || '../../rest/documents/updateGrid';

    var elements=$.extend(true,{},$.axmr.getAllElements());
    var additionals=$.extend(true,{},$.axmr.getAllAdditionals());
    var folders={};
    var coordinates={"x":"tp-p_TimePoint","y":"tp-p_Prestazione","row":"Prestazioni_row","col":"TimePoint_col"};
    var updatedElementsCount=$.axmr.countUpdated()+"";



    $.each(elements,function(idx,element){
        elements[idx]=prepareElementForPost(element);
    });
    $.each(additionals,function(idx,element){
        additionals[idx]=prepareElementForPost(element);
    });

    additionals=$.extend(true,additionals,elements);
    elements={};


    folders=prepareElementForPost(folders);
    var grid=$.extend(true,{},{"layout":[],"elements":elements,"additionals":additionals,"folders":folders,"coordinates":coordinates,"updatedElementsCount":updatedElementsCount});
    var data={"grid":JSON.stringify(grid)};
    return $.ajax({
        method:'POST',
        url:url,
        data:data
    });
}

function prepareTargetForm(open){
    var result='';
    var currTarget;
    if(open) {
        if($.isArray(docObj.elements.budgetStudio.metadata['BudgetCTC_TipoTarget'])) {
            currTarget=docObj.elements.budgetStudio.metadata['BudgetCTC_TipoTarget'][0];
        }
        else{
            currTarget=docObj.elements.budgetStudio.metadata['BudgetCTC_TipoTarget'];
        }
        if(!currTarget)currTarget=1;
        $('#target').val(currTarget);
    }
    else{
        currTarget=$('#target').val();
    }
    currTarget+='';
    switch(currTarget){
        case '1':
            $.each(docObj.elements.tp,function(key,val){
                var value='';
                var label='';
                var target;
                if(docObj.elements.target[val.id]) target=docObj.elements.target[val.id];
                else {
                    target=$.extend(true,{},emptyPrezzoPrestazione);
                    target.metadata['PrezzoFinale_Prestazione'][0]=val;
                    docObj.elements.target[val.id]=target;
                }

                if($.isArray(target.metadata['PrezzoFinale_Prezzo'])) {
                    value=target.metadata['PrezzoFinale_Prezzo'][0];
                }
                else{
                    value=target.metadata['PrezzoFinale_Prezzo'];
                }
                if($.isArray(val.metadata['TimePoint_NumeroVisita'])) {
                    label='Visita '+val.metadata['TimePoint_NumeroVisita'][0];
                }
                else{
                    label=val.metadata['TimePoint_NumeroVisita'];
                }
                if(value==undefined) value='';
                if(label==undefined) label='';
                label="<label>"+label+"</label>";
                result+=label+'<input type="text" value="'+value+'" name="target_tp_'+key+'" />';
            });
            break;
        case '2':
            var value='';

            if($.isArray(docObj.elements.budgetStudio.metadata['BudgetCTC_TargetPaziente'])) {
                value=docObj.elements.budgetStudio.metadata['BudgetCTC_TargetPaziente'][0];
            }
            else{
                value=docObj.elements.budgetStudio.metadata['BudgetCTC_TargetPaziente'];
            }

            if(value==undefined) value='';
            result='<input type="text" value="'+value+'" name="targetPrezzo" />';
            break;
        case '3':
            if($.isArray(docObj.elements.budgetStudio.metadata['BudgetCTC_TargetStudio'])) {
                value=docObj.elements.budgetStudio.metadata['BudgetCTC_TargetStudio'][0];
            }
            else{
                value=docObj.elements.budgetStudio.metadata['BudgetCTC_TargetStudio'];
            }

            if(value==undefined) value='';
            result='<input type="text" value="'+value+'" name="targetPrezzo" />';
            break;
    }
    $('#target-form').html(result);
}
function applyTargetForm(){
    if($.isArray(docObj.elements.budgetStudio.metadata['BudgetCTC_TipoTarget'])) {
        docObj.elements.budgetStudio.metadata['BudgetCTC_TipoTarget'][0]=$('#target').val();
    }
    else{
        docObj.elements.budgetStudio.metadata['BudgetCTC_TipoTarget']=$('#target').val();
    }
    $.axmr.setUpdated(docObj.elements.budgetStudio);
    if($('#target').val()!='1'){
        var target={};
        target=$.extend(true,target,docObj.elements.target);
        docObj.elements.target=target;
        $.each(docObj.elements.target,function(key,val){
            if(val){
                $.axmr.setUpdated(val,folderTarget);
            }
            if(val && $.isArray(val.metadata['PrezzoFinale_Prezzo'])) {
                val.metadata['PrezzoFinale_Prezzo'][0]='';
            }
            else if(val){
                val.metadata['PrezzoFinale_Prezzo']='';
            }
        });
    }

    if($('#target').val()!='2'){
        if($.isArray(docObj.elements.budgetStudio.metadata['BudgetCTC_TargetPaziente'])) {
            docObj.elements.budgetStudio.metadata['BudgetCTC_TargetPaziente'][0]='';
        }
        else{
            docObj.elements.budgetStudio.metadata['BudgetCTC_TargetPaziente']='';
        }
    }
    if($('#target').val()!='3'){
        if($.isArray(docObj.elements.budgetStudio.metadata['BudgetCTC_TargetStudio'])) {
            docObj.elements.budgetStudio.metadata['BudgetCTC_TargetStudio'][0]='';
        }
        else{
            docObj.elements.budgetStudio.metadata['BudgetCTC_TargetStudio']='';
        }
    }
    switch($('#target').val()){
        case '1':
            $.each(docObj.elements.tp,function(key,val){
                var target;
                if(docObj.elements.target[val.id]) target=docObj.elements.target[val.id];
                else {
                    target=$.extend(true,{},emptyPrezzoPrestazione);
                    target.metadata['PrezzoFinale_Prestazione'][0]=val;
                    docObj.elements.target[val.id]=target;
                }
                if($.isArray(target.metadata['PrezzoFinale_Prezzo'])) {
                    target.metadata['PrezzoFinale_Prezzo'][0]=$('input[name=target_tp_'+key+']').val();
                }
                else{
                    target.metadata['PrezzoFinale_Prezzo']=$('input[name=target_tp_'+key+']').val();;
                }
                if(target){
                    $.axmr.setUpdated(target,folderTarget);
                }
            });
            break;
        case '2':
            if($.isArray(docObj.elements.budgetStudio.metadata['BudgetCTC_TargetPaziente'])) {
                docObj.elements.budgetStudio.metadata['BudgetCTC_TargetPaziente'][0]=$('input[name=targetPrezzo]').val();
            }
            else{
                docObj.elements.budgetStudio.metadata['BudgetCTC_TargetPaziente']=$('input[name=targetPrezzo]').val();
            }
            break;
        case '3':
            if($.isArray(docObj.elements.budgetStudio.metadata['BudgetCTC_TargetStudio'])) {
                docObj.elements.budgetStudio.metadata['BudgetCTC_TargetStudio'][0]=$('input[name=targetPrezzo]').val();
            }
            else{
                docObj.elements.budgetStudio.metadata['BudgetCTC_TargetStudio']=$('input[name=targetPrezzo]').val();
            }
            break;
    }
}


function buildTpDescription(tp){
    var metadata=prepareMetadataForPost(tp.metadata);
    var ricoveri=new Array();
    ricoveri['Ricovero_Ordinario']='ORD.';
    ricoveri['Ricovero_Straordinario']='EXTRA.';
    ricoveri['Ricovero_Ambulatoriale']='AMB.';
    ricoveri['Ricovero_Telefonico']='TEL.';
    var ricoveriStr='';
    for(var curr in ricoveri){
        if(metadata[curr])ricoveriStr+=ricoveri[curr]+'\n';
    }
    var description='';
    if(metadata['TimePoint_Descrizione']) {
        description=''+metadata['TimePoint_Descrizione']+' ';
        if(metadata['TimePoint_Tempi'])description+='\n'+metadata['TimePoint_Tempi']+' ';
    }
    else {
        description='';
        if(metadata['TimePoint_Tempi'])description+=''+metadata['TimePoint_Tempi']+' ';
    }
    if(metadata['TimePoint_DescrizioneSelect']) description+=metadata['TimePoint_DescrizioneSelect'].split('###')[1]+'\n';
    else description+='\n';
    if(metadata['TimePoint_NumeroVisita']) description='Visita '+metadata['TimePoint_NumeroVisita']+' \n '+description;
    else description+="\n"
    if(metadata['TimePoint_Tempi'] && metadata['TimePoint_TempiSelect']) description+='Tempo: '+metadata['TimePoint_Tempi']+' '+metadata['TimePoint_TempiSelect'].split('###')[1]+'\n';
    else description+="\n"
    if(metadata['TimePoint_DurataSelect'] && metadata['TimePoint_DurataSelect']) description+='Durata: '+metadata['TimePoint_DurataCiclo']+' '+metadata['TimePoint_DurataSelect'].split('###')[1]+'\n';
    else description+="\n"
    if(metadata['TimePoint_RicoveroSelect'] )description+='Ricovero: '+metadata['TimePoint_RicoveroSelect'].split('###')[1]    ;
    else description+="\n"
    if(metadata['TimePoint_Note'] ){
        description+='Note:\n'+metadata['TimePoint_Note'].substring(0,12);
        if(metadata['TimePoint_Note'].length>12)description+='...';
    }
    return description;
}
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

function loadData(data,costi,instance) {
    $('#TPS').empty();
    $('#COSTS').empty();
    if(instance){
        docObj=instance;
    }
    //var data = dataInput.slice(0);
    //console.log('qui');
    //data=removeEmpty(data);
    var waitingLiTP = '';
    var waitingLiCost = '';
    for(var i = 0; i < data.length; i++) {
        if(i == 0) {
            for(var k = 0; k < data[0].length; k++) {
                if(k != 0) {
                    var label = data[0][k];
                    if(label === undefined || label === null || label === '') {
                        label = 'Timepoint non specificato';
                        waitingLiTP += '<li class="ui-state-default"><span class="ui-icon ui-icon-arrowthick-2-n-s"></span>' + label + '<input type="hidden" name="position_col[]" value="' + k + '"></li>';
                    } else {
                        var li = waitingLiTP + '<li class="ui-state-default"><span class="ui-icon ui-icon-arrowthick-2-n-s"></span>' + label + '<input type="hidden" name="position_col[]" value="' + k + '"></li>';
                        waitingLiTP = '';
                        $('#TPS').append(li);
                    }
                }
            }
        } else {
            var label = data[i][0];
            if(label === undefined || label === null || label === '') {
                label = 'Costo non specificato';
                waitingLiCost += '<li class="ui-state-default"><span class="ui-icon ui-icon-arrowthick-2-n-s"></span>' + label + '<input type="hidden" name="position_row[]" value="' + i + '"></li>';

            } else {
                var li = waitingLiCost + '<li class="ui-state-default"><span class="ui-icon ui-icon-arrowthick-2-n-s"></span>' + label + '<input type="hidden" name="position_row[]" value="' + i + '"></li>';
                waitingLiCost = '';
                $('#COSTS').append(li);
            }
        }
    }
    var handsontable = $('#example').data('handsontable');
    if(handsontable)handsontable.loadData(data);
    if(costi && docObj.elements.tpxp.length>0){
        costiInit=true;
        var migrated=migrateData(data);
        var handsontable2 =  $('#costi').data('handsontable');

        if(handsontable2){
            handsontable2.loadData(migrated);
            if(handsontable)loadCosti();//carico i costi per studio e per paziente
            else loadPrezzi();
        }
        loadBracci(instance);
    }
    else if (costi){
        loadCosti();
        loadBracci(instance);
    }
}

function loadBracci(instance){
    $.each(instance.elements.bracci,function(i,element){
        if(element.metadata['Base_Nome'] ){
            var elementId=i;
            var value=getDato(element.metadata['Base_Nome']);
            var oldValue=$('#braccio'+elementId).text();
            $('#braccio'+elementId).remove();
            $('#braccioCheck'+elementId).remove();
            $('#braccioPatients'+elementId).remove();
            $('#nobracci').remove();
            $('#bracciList').append('<button id="braccio'+elementId+'" name="'+elementId+'" class="btn btn-info" style="margin:3px;" >'+value+'</span>');
            $('#bracciChecks').append('<span id="braccioCheck'+elementId+'" name="'+elementId+'" style="margin:3px;" ><input type="checkbox" onclick="$(\'#tuttiBracci\').each(function(){this.checked=false;});" id="braccioInputCheck'+elementId+'" name="braccioInputCheck" value="'+value+'"><label for="braccioInputCheck'+elementId+'"  style="display:inline" >'+value+'</label></span>');
            $('#bracciPatList').append('<div id="braccioPatients'+elementId+'" name="'+elementId+'" style="margin:3px;" ><label>'+value+'</label><input  class="text ui-widget-content ui-corner-all" type="text" value="'+pazienti+'" name="Braccio_NumeroPazienti" id="Braccio_NumeroPazienti'+elementId+'" ></div>');

            $('#braccio'+elementId).button().click(function(){

                $('#bracci-dialog-form').find('[name=elementId]').val(elementId);
                elementToForm(element,"bracci-dialog-form");
                $("#bracci-dialog-form").dialog("open");
            });
        }
    });

}

function migrateData(array) {
    var newArray = clone(array);
    var totCols = new Array();
    var totRows = new Array();
    var Total = 0;
    var lastCol = 0;
    var lastRow = 0;
    //totCols[0] = 'Totale per visita';
    //totRows[0] = 'Totale per prestazione';
    for(var i = 1; i < newArray.length; i++) {
        var totRow = 0;
        if(newArray[i][0] !== undefined && newArray[i][0] !== null && $.trim(newArray[i][0]) != '')
            lastRow = i;
        for(var k = 1; k < newArray[i].length; k++) {
            var value = $.trim(newArray[i][k]);
            if(value && value != 'false') {

                if(docObj.elements.tpxp2update[i] && docObj.elements.tpxp2update[i][k]){
                    newArray[i][k] = docObj.elements.tpxp2update[i][k].metadata['Costo_TransferPrice'];
                }
                if(totRows[i] === null || totRows[i] === undefined)
                    totRows[i] = 0;
                if(!isNaN(newArray[i][k]))totRows[i] += parseFloat(newArray[i][k]);
                if(k > lastCol)
                    lastCol = k;
                if(totCols[k] === null || totCols[k] === undefined)
                    totCols[k] = 0;
                if(!isNaN(newArray[i][k]))totCols[k] += parseFloat(newArray[i][k]);

            } else {
                newArray[i][k] = "";
            }
        }

    }
    /*lastCol = lastCol + 1;
     lastRow = lastRow + 1;
     for(var z = 0; z < lastRow; z++) {
     newArray[z][lastCol] = totRows[z];
     if(!isNaN(totRows[z]))
     Total += totRows[z];
     }
     totCols[lastCol] = Total;
     newArray[lastRow] = totCols;  */
    return newArray;
}

function mergeData(preArray,array) {
    var newArray = clone(array);
    var oldArray = clone(preArray);
    var totCols = new Array();
    var totRows = new Array();
    var Total = 0;
    var lastCol = 0;
    var lastRow = 0;
    totCols[0] = 'Totale per visita';
    totRows[0] = 'Totale per prestazione';
    totCounts[0] = 'Totale occorrenze';
    for(var i = 1; i < newArray.length; i++) {
        var totRow = 0;
        var totCount = 0;
        if(newArray[i][0] !== undefined && newArray[i][0] !== null && $.trim(newArray[i][0]) != '')
            lastRow = i;
        for(var k = 1; k < newArray[i].length; k++) {
            var value = $.trim(newArray[i][k]);
            if(value && value != 'false') {
                totCount++;
                newArray[i][k] = "0";
                if(totRows[i] === null || totRows[i] === undefined)
                    totRows[i] = 0;
                if(!isNaN(newArray[i][k]))totRows[i] += parseFloat(newArray[i][k]);
                if(k > lastCol)
                    lastCol = k;
                if(totCols[k] === null || totCols[k] === undefined)
                    totCols[k] = 0;
                if(!isNaN(newArray[i][k]))totCols[k] += parseFloat(newArray[i][k]);

            } else {
                newArray[i][k] = "";
            }
        }
        totCounts[i]=totCount;
    }
    lastCol = lastCol + 1;
    lastRow = lastRow + 1;
    for(var z = 0; z < lastRow; z++) {
        newArray[z][lastCol] = totRows[z];
        newArray[z][lastCol+1] = totRows[z];
        if(!isNaN(totRows[z]))
            Total += totRows[z];
    }
    totCols[lastCol] = Total;
    newArray[lastRow] = totCols;
    return newArray;
}

function totaleSSN(){
    var tot=0;
    $.each(docObj.elements.tpxp2update,function(aKey,aVal){
        if(aVal) {
            $.each(aVal,function(key,val){
                if(val && val.metadata && val.metadata['Rimborso_Rimborsabilita']){
                    if(($.isArray(val.metadata['Rimborso_Rimborsabilita']) && val.metadata['Rimborso_Rimborsabilita'][0]==2) || val.metadata['Rimborso_Rimborsabilita']==2){
                        if($.isArray(val.metadata['tp-p_Prestazione'])){
                            if($.isArray(docObj.elements.prestazioni[val.metadata['tp-p_Prestazione'][0]].metadata['Base_Nome'])){
                                var transfer=tariffarioSSN[docObj.elements.prestazioni[val.metadata['tp-p_Prestazione'][0]].metadata['Base_Nome'][0]];
                            }
                            else{
                                var transfer=tariffarioSSN[docObj.elements.prestazioni[val.metadata['tp-p_Prestazione'][0]].metadata['Base_Nome']];
                            }
                        }
                        else{
                            var transfer=tariffarioSSN[val.metadata['tp-p_Prestazione']];
                        }
                        tot+=parseFloat(transfer);
                    }
                }
            });
        }
    });
    tot=tot.toFixed(2);
}

function mostraTotCTC(totFlow,totFlowCTC,totTip1,totTip1CTC,totTip2,totTip2CTC  ,totTip3,totTip3CTC,totTip4,totTip4CTC  ,totTip5,totTip5CTC){
    console.log(arguments);
    $('#table-tot tbody').empty();
    if(isNaN(totTip1)){
        totTip1=0;
        totTip1CTC=0;
    }
    if(isNaN(totTip2)){
        totTip2=0;
        totTip2CTC=0;
    }
    if(isNaN(totTip3)){
        totTip3=0;
        totTip3CTC=0;
    }
    if(isNaN(totTip4)){
        totTip4=0;
        totTip4CTC=0;
    }
    if(isNaN(totTip5)){
        totTip5=0;
        totTip5CTC=0;
    }

    var totPat=parseFloat(totFlow)  ;
    var totPatCTC=parseFloat(totFlowCTC)  ;

    totalePaziente=totPat;

    if(pazienti>0){
        var totStudio= (totPat*pazienti)+parseFloat(totTip2)+parseFloat(totTip4);
        var totStudioCTC= (totPatCTC*pazienti)+parseFloat(totTip2CTC)+parseFloat(totTip4CTC);
        totStudioCTC=totStudioCTC.toFixed(2);
        totaleStudio= totStudio;
    }
    else{
        var totStudio= 'Definire il numero di pazienti';
        var totStudioCTC= 'Definire il numero di pazienti';
    }
    if($('#totBracci').size()>0){
        var totBracci=$('#totBracci').val();
        var totBracciCTC=$('#totBracciCTC').val();
        totBracci=parseFloat(totBracci)+parseFloat(totTip2)+parseFloat(totTip4);
        totBracciCTC=parseFloat(totBracciCTC)+parseFloat(totTip2CTC)+parseFloat(totTip4CTC);
        $('#totaleBracci').html(totBracci.formatMoney());
        $('#totaleBracciCTC').html(totBracciCTC.formatMoney());
    }
    if (totFlow!=0) docObj.elements.budgetStudio.metadata['BudgetCTC_TotaleFlowchart'][0]=totFlow.formatMoney().unformatMoney();
    if (totFlowCTC!=0) docObj.elements.budgetStudio.metadata['BudgetCTC_TotaleFlowchartCTC'][0]=totFlowCTC.formatMoney().unformatMoney();
    if (totPat!=0) docObj.elements.budgetStudio.metadata['BudgetCTC_TotalePaziente'][0]=totPat.formatMoney().unformatMoney();
    if (totPatCTC!=0) docObj.elements.budgetStudio.metadata['BudgetCTC_TotalePazienteCTC'][0]=totPatCTC.formatMoney().unformatMoney();
    if (totStudio!=0) docObj.elements.budgetStudio.metadata['BudgetCTC_TotaleStudio'][0]=totStudio.formatMoney().unformatMoney();
    if (totStudioCTC!=0) docObj.elements.budgetStudio.metadata['BudgetCTC_TotaleStudioCTC'][0]=totStudioCTC.formatMoney().unformatMoney();

    var html='';

    html+="<tr><td>Budget totale per paziente</td><td></td><td>"+docObj.elements.budgetStudio.metadata['BudgetCTC_TotalePaziente'][0].formatMoney()+"</td><td>"+docObj.elements.budgetStudio.metadata['BudgetCTC_TotalePazienteCTC'][0].formatMoney()+"</td><td></td></tr>";
    html+="<tr><td>Budget totale per studio</td><td></td><td>"+docObj.elements.budgetStudio.metadata['BudgetCTC_TotaleStudio'][0].formatMoney()+"</td><td>"+docObj.elements.budgetStudio.metadata['BudgetCTC_TotaleStudioCTC'][0].formatMoney()+"</td><td></td></tr>";
    //html+="<tr><td>Totale SSN</td><td>"+totaleSSN()+"</td><td>N.A.</td></tr>";
    var markup1,markup2;
    markup=getDato(docObj.elements.budgetStudio.metadata['BudgetCTC_Markup']);
    /*if(isNaN(markup)){
		markup=0;
	}else{
		markup1=getDato(docObj.elements.budgetStudio.metadata['BudgetCTC_Markup1']);
		markup2=getDato(docObj.elements.budgetStudio.metadata['BudgetCTC_Markup2']);
	}*/
    markup1=markup1||0;
    markup2=markup2||0;
    $('#table-tot tbody').html(html);
    if(budgetCTC){
        for(var i=1;i<=5;i++){
            var tr='';
            if(i<=2){
                tr='<tr class="totaleCTC" ><td>Totale prezzo</td><td>'+eval('totTip'+i+'CTC.formatMoney()')+'</td><td>&nbsp;</td></tr>';
            }else if(i<=4){
                tr='<tr class="totaleCTC"><td>Totale prezzo</td><td>&nbsp;</td><td>'+eval('totTip'+i+'CTC.formatMoney()')+'</td><td>&nbsp;</td><td>&nbsp;</td></tr>';
            }
            else if (i==5){
                tr='<tr class="totaleCTC"><td>Totale prezzo</td><td>'+eval('totTip'+i+'CTC.formatMoney()')+'</td><td>&nbsp;</td><td>&nbsp;</td></tr>';
            }
            if(i>=3 ){
                $('table#costs-'+i).find('.tot-costi').remove();
            }
            $('table#costs-'+i).find('.totaleCTC').remove();
            $('table#costs-'+i).find('tbody').append(tr);
        }
    }
    $('#markup-ins').html(markup+'%');
}

function mostraTotCTCBracci(totFlow,totFlowCTC,totFlowBracci,totFlowBracciCTC,totTip1,totTip1CTC,totTip2,totTip2CTC  ,totTip3,totTip3CTC,totTip4,totTip4CTC  ,totTip5,totTip5CTC){
    console.log(arguments);
    var totalAllPatients=0;
    var totalAllPatientsCTC=0;
    $('#table-tot tbody').empty();
    if(isNaN(totTip1)){
        totTip1=0;
        totTip1CTC=0;
    }
    if(isNaN(totTip2)){
        totTip2=0;
        totTip2CTC=0;
    }
    if(isNaN(totTip3)){
        totTip3=0;
        totTip3CTC=0;
    }
    if(isNaN(totTip4)){
        totTip4=0;
        totTip4CTC=0;
    }
    if(isNaN(totTip5)){
        totTip5=0;
        totTip5CTC=0;
    }

    var totPat=parseFloat(totFlow) ;
    var totPatCTC=parseFloat(totFlowCTC)  ;
    var numBracciPaz=0;
    var html='';
    $.each(docObj.elements.bracci, function(i,braccio){
        numBracciPaz+=getDato(braccio.metadata['Braccio_NumeroPazienti'])-0;
        var totPatBraccio=totPat+totFlowBracci[i];
        var totPatBraccioCTC=totPatCTC+totFlowBracciCTC[i];
        docObj.elements.bracci[i].metadata['Braccio_TotaleBudgetPaziente']=totPatBraccio;
        totalAllPatients+=(totPatBraccio*getDato(braccio.metadata['Braccio_NumeroPazienti']));
        totalAllPatientsCTC+=(totPatBraccioCTC*getDato(braccio.metadata['Braccio_NumeroPazienti']));
        html+="<tr><td>Budget totale per paziente ("+getDato(braccio.metadata['Base_Nome'])+")</td><td></td><td>"+totPatBraccio.formatMoney()+"</td><td>"+totPatBraccioCTC.formatMoney()+"</td><td></td></tr>";
    });

    totalePaziente=totPat;

    if(pazienti>0 && (docObj.elements.bracci.length==0 || numBracciPaz==pazienti)){
        totPat=totalePaziente=totalAllPatients/pazienti;
        totPatCTC=totalAllPatientsCTC/pazienti;
        var totStudio= totalAllPatients+parseFloat(totTip2)+parseFloat(totTip4);
        var totStudioCTC= totalAllPatientsCTC+parseFloat(totTip2CTC)+parseFloat(totTip4CTC);
        totStudioCTC=totStudioCTC.toFixed(2);
        totaleStudio= totStudio;
    }
    else{
        var totStudio= 'Definire il numero di pazienti';
        var totStudioCTC= 'Definire il numero di pazienti';
    }

    docObj.elements.budgetStudio.metadata['BudgetCTC_TotaleFlowchart']=totFlow.formatMoney().unformatMoney();
    docObj.elements.budgetStudio.metadata['BudgetCTC_TotaleFlowchartCTC']=totFlowCTC.formatMoney().unformatMoney();
    docObj.elements.budgetStudio.metadata['BudgetCTC_TotalePaziente']=totPat.formatMoney().unformatMoney();
    docObj.elements.budgetStudio.metadata['BudgetCTC_TotalePazienteCTC']=totPatCTC.formatMoney().unformatMoney();
    docObj.elements.budgetStudio.metadata['BudgetCTC_TotaleStudio']=totStudio.formatMoney().unformatMoney();
    docObj.elements.budgetStudio.metadata['BudgetCTC_TotaleStudioCTC']=totStudioCTC.formatMoney().unformatMoney();



    html+="<tr><td>Budget totale per studio</td><td></td><td>"+totStudio.formatMoney()+"</td><td>"+totStudioCTC.formatMoney()+"</td><td></td></tr>";
    //html+="<tr><td>Totale SSN</td><td>"+totaleSSN()+"</td><td>N.A.</td></tr>";
    markup=getDato(docObj.elements.budgetStudio.metadata['BudgetCTC_Markup']);
    $('#table-tot tbody').html(html);
    if(budgetCTC){
        for(var i=1;i<=5;i++){
            var tr='';
            if(i<=2){
                tr='<tr class="totaleCTC" ><td>Totale prezzo</td><td>'+eval('totTip'+i+'CTC.formatMoney()')+'</td><td>&nbsp;</td></tr>';
            }else if(i<=4){
                tr='<tr class="totaleCTC"><td>Totale prezzo</td><td>&nbsp;</td><td>'+eval('totTip'+i+'CTC.formatMoney()')+'</td><td>&nbsp;</td><td>&nbsp;</td></tr>';
            }else if (i==5){
                tr='<tr class="totaleCTC"><td>Totale prezzo</td><td>'+eval('totTip'+i+'CTC.formatMoney()')+'</td><td>&nbsp;</td><td>&nbsp;</td></tr>';
            }
            if(i>=3){
                $('table#costs-'+i).find('.tot-costi').remove();
            }
            $('table#costs-'+i).find('.totaleCTC').remove();
            $('table#costs-'+i).find('tbody').append(tr);
        }
    }
    $('#markup-ins').html(markup+'%');
}


function rimuoviTotali(){
    var handsontable2 =  $('#costi').data('handsontable');
    if(handsontable2) var array=handsontable2.getData();
    else {
        var array=baseData;
    }
    var newArray = clone(array);
    var totCols = new Array();
    var totRows = new Array();
    var Total = 0;
    var lastCol = 0;
    var lastRow = 0;
    var lastColFound=false;
    var lastRowFound=false;
    totCols[0] = 'Totale per visita';
    totRows[0] = 'Totale per prestazione';
    for(var i = 1; i < newArray.length; i++) {
        var totRow = 0;
        if(newArray[i][0] == 'Totale per visita')  {
            lastRowFound=true;
            lastRow = i;
        }
        for(var k = 1; k < newArray[i].length; k++) {
            var value = $.trim(newArray[i][k]);
            if((k<lastCol || lastCol==0) && (i<lastRow || lastRow==0)){
                if(value && value != 'false') {

                    if(newArray[0][k]=='Totale per prestazione')  {
                        lastColFound = true;
                        lastCol = k;
                        continue;
                    }

                }
            }
        }


    }
    //lastCol = lastCol + 1;
    //lastRow = lastRow + 1;
    if(lastColFound){
        for(var z = 0; z < newArray.length; z++) {
            if(newArray[z][lastCol])newArray[z][lastCol] = '';
            if(newArray[z][lastCol+1])newArray[z][lastCol+1] = '';

        }
    }
    if(lastRowFound){
        newArray[lastRow] = new Array();
        newArray[lastRow+1] = new Array();
        newArray[lastRow+2] = new Array();
        newArray[lastRow+3] = new Array();
    }
    if(handsontable2)handsontable2.loadData(newArray);
    $('.tot-costi').remove();
    return true;
}

function cleanCost(element){
    $.each(element.metadata,function(key,val){
        if(key.match(/^costo_/i)){
            if($.isArray(val)){
                val[0]='';
            }else{
                element.metadata[key]='';
            }
        }
    });
    $.axmr.guid(element,undefined,'');
}

function updatePrezzi(markup){
    array=baseData;
    var newArray = clone(array);
    for(var i = 1; i < newArray.length; i++) {
        var totRow = 0;

        for(var k = 1; k < newArray[i].length; k++) {

            var currElement=$.axmr.guid(newArray[i][k]);


            if($.isPlainObject(currElement)){
                var value = getDato(getDato(currElement.metadata['PrezzoFinale_Prestazione']).metadata['Costo_TransferPrice'])-0;
                value=value+(value*markup/100);
                value=value.formatMoney().unformatMoney();
                currElement.metadata['PrezzoFinale_Prezzo']=value;
                $.axmr.setUpdated(currElement,folderPrezzi);
                newArray[i][k]=$.axmr.guid(currElement,1,value);
            }
        }


    }
    $.each(docObj.elements.prezzi,function(i,prezzo){
        var type=getDato(prezzo.metadata['PrezzoFinale_Prestazione']).type.typeId;
        switch(type){
            case 'tpxp':
                break;
            case 'PrestazioneXStudio':
            case 'PrestazioneXPaziente':
                var value=getDato(getDato(prezzo.metadata['PrezzoFinale_Prestazione']).metadata['Costo_TransferPrice'])-0;
                value=value+(value*markup/100);
                value=value.formatMoney().unformatMoney();
                prezzo.metadata['PrezzoFinale_Prezzo']=value;
                $.axmr.setUpdated(prezzo,folderPrezzi);
                if(type=='PrestazioneXPaziente'){
                    var tipologia=1;
                }
                else{
                    var tipologia=2;
                }
                updatePrezzoTD(value,i,tipologia);
                break;
        }
    });
    var handsontable2 =  $('#costi').data('handsontable');
    handsontable2.loadData(newArray);
}

function getTpTarget(tp){
    var target;
    if(docObj.elements.target[tp.id]) target=docObj.elements.target[tp.id];
    else {
        target=$.extend(true,{},emptyPrezzoPrestazione);
        target.metadata['PrezzoFinale_Prestazione'][0]=val;
        docObj.elements.target[tp.id]=target;
    }
    return getDato(target.metadata['PrezzoFinale_Prezzo']);
}

function addTotDiBraccio(element,value,totali){
    value=parseFloat(value);
    if(!isNaN(value)){
        var bracci=getDato(element.metadata['Costo_Braccio']);
        if(bracci && !bracci.match(/^\s*$/)){
            $.each(docObj.elements.bracci, function(i,braccio){
                if(inBraccio(bracci,getDato(braccio.metadata['Base_Nome']))){
                    totali[i]+=value;
                }
            });

        }
    }
    return totali;
}

function addTotGenerale(element,value,totaleGenerale){
    value=parseFloat(value);
    if(!isNaN(value)){
        var bracci=getDato(element.metadata['Costo_Braccio']);
        if(!bracci){
            totaleGenerale+=value;
        }
    }
    return totaleGenerale;
}

function inBraccio(bracciElemento,braccio){
    var match='\\|'+braccio+'\\|';
    return bracciElemento.match(match);
}

function calcolaTotaliDelayed(delay){
    delay=delay?delay:200;
    if(delayedCalcolaTotali){
        clearTimeout(delayedCalcolaTotali);
    }
    delayedCalcolaTotali=setTimeout(calcolaTotali,delay);
}

function calcolaTotali(){
    console.log('Sono qui!!!!');

    //funzione che aggiunge totali nel tab di budget
    var handsontable2 =  $('#costi').data('handsontable');
    var handsontable1 =  $('#example').data('handsontable');
    if(handsontable1){
        var array=handsontable1.getData();
    }
    else if(baseData){
        array=baseData;
    }else{
        array=new Array();
        array[0]=new Array();
    }
    var newArray = clone(array);
    var totCols = new Array();
    var totRows = new Array();
    var totCounts = new Array();
    var Total = 0;
    var lastCol = 0;
    var lastRow = 0;
    var lastRowFound=false;
    var lastColFound=false;
    var tpTransferTotFlow=0;
    var tpPrezzoTotFlow=0;
    var tpTransferTotal=new Array();
    var tpPrezzoTotal=new Array();
    var totalPrezzoFlowBraccio=new Array();
    var totalPrezzoFlowComune=0;
    var totalTransferFlowBraccio=new Array();
    var totalTransferFlowComune=0;

    $.each(docObj.elements.bracci,function(i,braccio){
        totalPrezzoFlowBraccio[i]=0;
        totalTransferFlowBraccio[i]=0;
    });

    markup=0;
    if(docObj.elements.budgetStudio.metadata){

        markup=docObj.elements.budgetStudio.metadata['BudgetCTC_Markup'];
        if(getDato(docObj.elements.budgetStudio.metadata['BudgetCTC_NumeroPazienti'])!=pazienti && getDato(docObj.elements.budgetStudio.metadata['BudgetCTC_NumeroPazienti'])>0){
            pazienti=getDato(docObj.elements.budgetStudio.metadata['BudgetCTC_NumeroPazienti']);
        }else if(getDato(docObj.elements.budgetStudio.metadata['BudgetCTC_NumeroPazienti'])!=pazienti){
            $.axmr.setUpdated(docObj.elements.budgetStudio);
        }
        docObj.elements.budgetStudio.metadata['BudgetCTC_NumeroPazienti']=pazienti;

    }

    elementToForm(docObj.elements.budgetStudio,'dialog-form-CTC');
    elementToForm(docObj.elements.budgetStudio,'dialog-form-n-pat');
    totCols[0] = 'Totale per visita';
    totRows[0] = 'Totale per prestazione';
    totCounts[0] = 'Totale occorrenze';
    if(budgetCTC)var currTarget=getDato(docObj.elements.budgetStudio.metadata['BudgetCTC_TipoTarget']);
    else budgetCTC=false;
    if(currTarget){
        currTarget+='';
        $('#target').val(currTarget)
        var targetTot=0;
        var value=0;
        var confrontValue=0;
        var advisedMarkup=0;
        var tipologia='';
        switch($('#target').val()){
            case '1':
                tipologia='Per visita';
                $.each(docObj.elements.tp,function(key,val){
                    var target;
                    if(docObj.elements.target[val.id]) target=docObj.elements.target[val.id];
                    else {
                        target=$.extend(true,{},emptyPrezzoPrestazione);
                        target.metadata['PrezzoFinale_Prestazione'][0]=val;
                        docObj.elements.target[val.id]=target;
                    }
                    if($.isArray(target.metadata['PrezzoFinale_Prezzo'])) {
                        value=target.metadata['PrezzoFinale_Prezzo'][0];
                    }
                    else{
                        value=target.metadata['PrezzoFinale_Prezzo'];
                    }
                    if(!isNaN(parseFloat(value)))targetTot+=parseFloat(value);
                });

                break;
            case '2':
                tipologia='Per paziente';
                if($.isArray(docObj.elements.budgetStudio.metadata['BudgetCTC_TargetPaziente'])) {
                    value=docObj.elements.budgetStudio.metadata['BudgetCTC_TargetPaziente'][0];
                }
                else{
                    value=docObj.elements.budgetStudio.metadata['BudgetCTC_TargetPaziente'];
                }
                targetTot=value;

                break;
            case '3':
                tipologia='Per studio';
                if($.isArray(docObj.elements.budgetStudio.metadata['BudgetCTC_TargetStudio'])) {
                    value=docObj.elements.budgetStudio.metadata['BudgetCTC_TargetStudio'][0];
                }
                else{
                    value=docObj.elements.budgetStudio.metadata['BudgetCTC_TargetStudio'];
                }
                if(!isNaN(parseFloat(value)))targetTot=parseFloat(value);

                break;
        }


    }

    for(var i = 1; i < newArray.length; i++) {
        var totRow = 0;
        var totCount = 0;
        if(newArray[i][0] == 'Totale per visita'){
            lastRow = i;
            lastRowFound=true;
        }
        for(var k = 1; k < newArray[i].length; k++) {

            var currElement=$.axmr.guid(newArray[i][k]);
            var value = $.trim($.axmr.label(newArray[i][k],2));
            if(currElement && budgetCTC){
                if(!tpTransferTotal[k]){
                    tpTransferTotal[k]=0;
                }
                if(!tpPrezzoTotal[k]){
                    tpPrezzoTotal[k]=0;
                }
                var currTransfer=parseFloat(getDato(getDato(currElement.metadata['PrezzoFinale_Prestazione']).metadata['Costo_TransferPrice']));
                if(!isNaN(currTransfer)){
                    tpTransferTotal[k]+=currTransfer;
                    tpTransferTotFlow+=currTransfer;

                    totalTransferFlowComune=addTotGenerale(getDato(currElement.metadata['PrezzoFinale_Prestazione']),currTransfer,totalTransferFlowComune);
                    totalTransferFlowBraccio=addTotDiBraccio(getDato(currElement.metadata['PrezzoFinale_Prestazione']),currTransfer,totalTransferFlowBraccio);

                }
                if(!isNaN(value)){
                    tpPrezzoTotal[k]+=value;
                    tpPrezzoTotFlow+=value;

                    totalPrezzoFlowComune=addTotGenerale(getDato(currElement.metadata['PrezzoFinale_Prestazione']),value,totalPrezzoFlowComune);
                    totalPrezzoFlowBraccio=addTotDiBraccio(getDato(currElement.metadata['PrezzoFinale_Prestazione']),value,totalPrezzoFlowBraccio);
                }
            }


            if((k<lastCol || lastCol==0) && (i<lastRow || lastRow==0)){
                if(value && value != 'false') {
                    totCount++;
                    if(currElement && getDato(currElement.metadata['Rimborso_Rimborsabilita'])=='2') {
                        cleanCost(currElement);
                        value=0;
                    }

                    if(totRows[i] === null || totRows[i] === undefined)
                        totRows[i] = 0;
                    if(newArray[0][k]=='Totale per prestazione')  {
                        lastCol = k;
                        lastColFound=true;
                        continue;
                    }
                    if(!isNaN(value))totRows[i] += parseFloat(value);

                    if(totCols[k] === null || totCols[k] === undefined)
                        totCols[k] = 0;
                    if(!isNaN(parseFloat(value)))totCols[k] += parseFloat(value);
                }else if (currElement){
                    console.log("count");
                    totCount++;
                }
            }
        }
        totCounts[i]=totCount;


    }
    if(!lastRowFound){
        for(var ii = 1; ii < newArray.length; ii++){
            var currLabel=$.trim($.axmr.label(newArray[ii][0]));
            if (newArray[ii+1] && newArray[ii+1][0])var currLabel2=$.trim($.axmr.label(newArray[ii+1][0]));
            else{
                var currLabel2='';
            }
            if( currLabel!='' && currLabel2=='') {
                lastRow=ii+1;
            }
        }
    }
    if(!lastColFound){
        for(var kk = 1; kk < newArray[0].length; kk++){
            var currLabel=$.trim($.axmr.label(newArray[0][kk]));
            if(newArray[0] && newArray[0][kk+1])var currLabel2=$.trim($.axmr.label(newArray[0][kk+1]));
            else{
                var currLabel2='';
            }
            if(currLabel!='' && currLabel2=='') {
                lastCol=kk+1;
            }
        }
    }
    //lastCol = lastCol + 1;
    //lastRow = lastRow + 1;

    for(var z = 0; z < lastRow; z++) {
        if(totRows[z]>0){
            var currText=(parseFloat(totRows[z])).toFixed(2);
        }else{
            var currText=totRows[z];
        }
        newArray[z][lastCol] = currText;
        newArray[z][lastCol+1] = totCounts[z];
        if(!isNaN(totRows[z]))
            Total += totRows[z];
    }

    totCols[lastCol] = Total.toFixed(2);
    newArray[lastRow] = totCols;

    markup=parseFloat(markup);
    var targetVisita=(currTarget && $('#target').val()==1 && (!docObj.elements.bracci || !docObj.elements.bracci.length ));
    if(!newArray[lastRow+1])newArray[lastRow+1]=new Array();
    if(!newArray[lastRow+2])newArray[lastRow+2]=new Array();
    if(!newArray[lastRow+3])newArray[lastRow+3]=new Array();
    if(markup>0 && budgetCTC && false){

        newArray[0][lastCol+1] ='Valore con markup';
        newArray[lastRow+1][0] ='Valore con markup';
        if(targetVisita) {
            newArray[lastRow+2][0] ='Proposta sponsor';
            newArray[lastRow+3][0] ='TP/Proposta sponsor';
        }
        for (var ii=1;ii<lastRow;ii++){
            if(newArray[ii][lastCol]>0)newArray[ii][lastCol+1] = (newArray[ii][lastCol]*((100+markup)/100)).toFixed(2);

        }

        for (var kk=1;kk<lastCol;kk++){
            if(newArray[lastRow][kk]>0)newArray[lastRow+1][kk] = (newArray[lastRow][kk]*((100+markup)/100)).toFixed(2);
            if( targetVisita){
                var target=parseFloat(getTpTarget(docObj.elements.tp[kk-1]));
                var currTpTransfer=tpTransferTotal[kk];
                if(newArray[lastRow][kk]>0){
                    newArray[lastRow+2][kk] = target;
                    newArray[lastRow+3][kk] = ((target-currTpTransfer)*100 / currTpTransfer).toFixed(2);
                }else{
                    newArray[lastRow+2][kk] = target;
                    newArray[lastRow+3][kk] = 'N.A.';
                }
            }
            else{
                newArray[lastRow+2][kk] = '';
                newArray[lastRow+3][kk] = '';
            }
        }
        if(newArray[lastRow][lastCol]>0){
            var totFlow=  tpTransferTotFlow;
            var totFlowCTC=newArray[lastRow][lastCol+1]=newArray[lastRow+1][lastCol]= tpPrezzoTotFlow.toFixed(2);
            if(targetVisita){
                newArray[lastRow+2][lastCol]= targetTot;
                if(totFlow>0)newArray[lastRow+3][lastCol]= ((targetTot-tpPrezzoTotFlow)*100 / tpPrezzoTotFlow).toFixed(2);
                else newArray[lastRow+3][lastCol]='N.A.';
            }
            else{
                newArray[lastRow+2][lastCol]= targetTot;

            }
        }
        else{
            var totFlow=  0;
            var totFlowCTC=0;
        }
        var totTip=new Array();
        var totTipCTC=new Array();
        for(var tip=1;tip<=5;tip++){
            var tot=totTip[tip]=parseFloat($('#tot_costi_'+tip).html());

            $('#costo-ctc-mu-'+tip).remove();
            if(tot>0 && tip!=5){

                var totCTC=totTipCTC[tip]=(tot*((100+markup)/100)).toFixed(2);
                if(tip==3 || tip==4){
                    categoriaTot='<td></td>';
                }
                else{
                    categoriaTot='';
                }
                $('#costs-'+tip+' tbody').append("<tr id='costo-ctc-mu-"+tip+"'>" +"<td>Totale con markup</td>" +categoriaTot + "<td>" + totCTC.formatMoney() + "</td><td></td>" + "</tr>");
            } else{
                totTipCTC[tip]=tot;
            }
        }
    }
    else{
        newArray[0][lastCol+1] =totCounts[0];
        newArray[lastRow+1][0] ='';

        if(targetVisita) {
            newArray[lastRow+1][0] ='Proposta sponsor';
            newArray[lastRow+2][0] ='TP/Proposta sponsor';
        }
        for (var ii=1;ii<lastRow;ii++){
            if(newArray[ii][lastCol]>0)newArray[ii][lastCol+1] = totCounts[ii];
        }
        for (var kk=1;kk<lastCol;kk++){
            if(newArray[lastRow][kk]>0){
                newArray[lastRow][kk]=newArray[lastRow][kk].toFixed(2);
                newArray[lastRow+1][kk] = '';
            }
            if( targetVisita ){
                var target=parseFloat(getTpTarget(docObj.elements.tp[kk-1]));
                if(newArray[lastRow][kk]>0){
                    newArray[lastRow+1][kk] = target;
                    newArray[lastRow+2][kk] = ((target-tpTransferTotal[kk])*100 / tpTransferTotal[kk]).toFixed(2);
                }
                else{
                    newArray[lastRow+1][kk] = target;
                    newArray[lastRow+2][kk] ='N.A.';
                }
            }
            else{
                //newArray[lastRow+1][kk] = '';
                newArray[lastRow+2][kk] = '';
            }
        }
        if(newArray[lastRow][lastCol]>0){
            newArray[lastRow][lastCol+1]=newArray[lastRow+1][lastCol]= '';
        }
        var totTip=new Array();
        var totTipCTC=new Array();
        for(var tip=1;tip<=5;tip++){
            //$('#costo-ctc-mu-'+tip).remove();

            totTip[tip]=totTipCTC[tip]=0;

        }
        //totTip[5]=totTipCTC[5];
        var totFlowCTC,totFlow;
        totFlow=0;
        totFlowCTC=0;
        if(docObj.elements.prezzi){
            $.each(docObj.elements.prezzi,function(i,prezzo){
                var prestazione=getDato(prezzo.metadata['PrezzoFinale_Prestazione']);
                var type=getDato(prezzo.metadata['PrezzoFinale_Prestazione']).type.typeId;
                var prezzoVal=getDato(prezzo.metadata['PrezzoFinale_Prezzo']);
                prezzoVal=parseFloat(prezzoVal);
                if(prestazione){
                    switch(type){
                        case 'tpxp':
                            var tpVal=getDato(prestazione.metadata['Costo_TransferPrice']);
                            tpVal=parseFloat(tpVal);

                            if(!isNaN(tpVal))totFlow+=tpVal;
                            if(!isNaN(prezzoVal)){
                                totFlowCTC+=prezzoVal;
                            }
                            else if(!isNaN(tpVal)){
                                totFlowCTC+=tpVal;
                            }
                            break;
                        case 'PrestazioneXStudio':
                            if(getDato(prestazione.metadata['Costo_TransferPrice'])){
                                var tpVal=getDato(prestazione.metadata['Costo_TransferPrice']);
                                tpVal=parseFloat(tpVal);

                                if(!isNaN(tpVal))totTip[2]+=parseFloat(tpVal);
                                if(!isNaN(prezzoVal)){
                                    totTipCTC[2]+=prezzoVal;
                                }
                                else if(!isNaN(tpVal)){
                                    totTipCTC[2]+=tpVal;
                                }
                            }
                            break;
                        case 'PrestazioneXPaziente':
                            var tpVal=getDato(prestazione.metadata['Costo_TransferPrice']);
                            tpVal=parseFloat(tpVal);

                            if(!isNaN(tpVal))totTip[1]+=parseFloat(tpVal);
                            if(!isNaN(prezzoVal)){
                                totTipCTC[1]+=prezzoVal;
                            }
                            else if(!isNaN(tpVal)){
                                totTipCTC[1]+=tpVal;
                            }
                            break;
                    }
                }
            });
        }
        if(docObj.elements.pxpCTC){
            $.each(docObj.elements.pxpCTC,function(i,prestazione){
                if(prestazione){
                    var tpVal=parseFloat(getDato(prestazione.metadata['Costo_Costo']));
                    var prezzoVal=parseFloat(getDato(prestazione.metadata['Costo_Prezzo']));
                    //console.log(tpVal);
                    if(!isNaN(tpVal))totTip[3]+=tpVal;
                    if(!isNaN(prezzoVal))totTipCTC[3]+=prezzoVal;
                }
            });
        }
        if(docObj.elements.pxsCTC){
            $.each(docObj.elements.pxsCTC,function(i,prestazione){
                if(prestazione){
                    var tpVal=parseFloat(getDato(prestazione.metadata['Costo_Costo']));
                    var prezzoVal=parseFloat(getDato(prestazione.metadata['Costo_Prezzo']));

                    if(!isNaN(tpVal))totTip[4]+=tpVal;
                    if(!isNaN(prezzoVal))totTipCTC[4]+=prezzoVal;
                }
            });
        }
        if(docObj.elements.passthroughCTC){
            $.each(docObj.elements.passthroughCTC,function(i,prestazione){
                if(prestazione){

                    var prezzoVal=parseFloat(getDato(prestazione.metadata['Costo_Prezzo']));

                    if(!isNaN(prezzoVal))totTip[5]+=prezzoVal;
                    if(!isNaN(prezzoVal))totTipCTC[5]+=prezzoVal;
                }
            });
        }
        if(targetVisita){
            newArray[lastRow+1][lastCol]= targetTot;
            if( newArray[lastRow][kk]>0)newArray[lastRow+2][lastCol]= ((targetTot-tpTransferTotFlow)*100 / tpTransferTotFlow).toFixed(2);
            else newArray[lastRow+2][lastCol]= 'N.A.';
        }
    }
    if(budgetCTC){
        if(!docObj.elements.bracci || !docObj.elements.bracci.length ){
            mostraTotCTC((parseFloat(totFlow)).toFixed(2),(parseFloat(totFlowCTC)).toFixed(2),(parseFloat(totTip[1])).toFixed(2),(parseFloat(totTipCTC[1])).toFixed(2),(parseFloat(totTip[2])).toFixed(2),(parseFloat(totTipCTC[2])).toFixed(2)  ,(parseFloat(totTip[3])).toFixed(2),(parseFloat(totTipCTC[3])).toFixed(2)  ,(parseFloat(totTip[4])).toFixed(2),(parseFloat(totTipCTC[4])).toFixed(2)  ,(parseFloat(totTip[5])).toFixed(2),(parseFloat(totTipCTC[5])).toFixed(2));
        }else{
            mostraTotCTCBracci(parseFloat(totalTransferFlowComune),parseFloat(totalPrezzoFlowComune),totalTransferFlowBraccio,totalPrezzoFlowBraccio,(parseFloat(totTip[1])).toFixed(2),(parseFloat(totTipCTC[1])).toFixed(2),(parseFloat(totTip[2])).toFixed(2),(parseFloat(totTipCTC[2])).toFixed(2)  ,(parseFloat(totTip[3])).toFixed(2),(parseFloat(totTipCTC[3])).toFixed(2)  ,(parseFloat(totTip[4])).toFixed(2),(parseFloat(totTipCTC[4])).toFixed(2)  ,(parseFloat(totTip[5])).toFixed(2),(parseFloat(totTipCTC[5])).toFixed(2));
        }
    }

    if(currTarget){
        currTarget+='';

        switch($('#target').val()){
            case '1':

                confrontValue=tpTransferTotFlow;
                break;
            case '2':

                confrontValue=totalePaziente;
                break;
            case '3':

                confrontValue=totaleStudio;
                break;
        }
        if( docObj.elements.bracci.length>0 && $('#target').val()!="3"){
            confrontValue=totaleStudio;
            targetTot=targetTot*pazienti;
        }
        advisedMarkup=(targetTot-confrontValue)*100/confrontValue;
        if(!isNaN(targetTot) && !isNaN(advisedMarkup)){
            /*var rowMarkup='';
             rowMarkup='<tr><td>'+tipologia+'</td><td>'+targetTot.formatMoney()+'</td><td>'+confrontValue.formatMoney()+'</td><td>'+advisedMarkup.toFixed(2)+'</td></tr>';
             $('#table-advised-markup tbody').html(rowMarkup);*/
            if($('#target').val()==3 || docObj.elements.bracci.length>0){
                var targetRow='#table-tot tr:last ';
            }else{
                var targetRow='#table-tot tr:nth-child(1) ';
            }
            $(targetRow+' td:nth-child(2)').html(targetTot.formatMoney());
            $(targetRow+' td:nth-child(5)').html(advisedMarkup.toFixed(2));

        }
    }else {
        var targetRow='#table-tot tr:nth-child(1) ';
        $(targetRow+' td:nth-child(5)').html(markup.toFixed(2));
    }
    console.log('After - 5');
    for(var propt in docObj.elements.budgetStudio.metadata){
        console.log(' - calcolaTotali - '+propt + ': ' + docObj.elements.budgetStudio.metadata[propt]);
    }
    if(handsontable2 && handsontable2.loadData)handsontable2.loadData(newArray);
    return newArray;
}

function initPreventivo(array){
    var newArray = clone(array);
    var totCols = new Array();
    var totRows = new Array();
}
function  deletePxp(idx){
    $.axmr.setDeleted(docObj.elements.pxp[idx]);
    //docObj.elements.pxp2delete[docObj.elements.pxp2delete.length]=$.extend(true,{},docObj.elements.pxp[idx]);
    delete docObj.elements.pxp[idx];
    updateListaCosti(1);
    calcolaTotali();
}
function  deletePxs(idx){
    $.axmr.setDeleted(docObj.elements.pxs[idx]);
    //docObj.elements.pxs2delete[docObj.elements.pxs2delete.length]=$.extend(true,{},docObj.elements.pxs[idx]);
    delete docObj.elements.pxs[idx];
    updateListaCosti(2);
    calcolaTotali();
}



function  deletePxpCTC(idx){
    $.axmr.setDeleted(docObj.elements.pxpCTC[idx]);
    //docObj.elements.pxp2delete[docObj.elements.pxp2delete.length]=$.extend(true,{},docObj.elements.pxpCTC[idx]);
    delete docObj.elements.pxpCTC[idx];
    updateListaCosti(3);
    calcolaTotali();
}

function  deletePxsCTC(idx){
    $.axmr.setDeleted(docObj.elements.pxsCTC[idx]);
    //docObj.elements.pxs2delete[docObj.elements.pxs2delete.length]=$.extend(true,{},docObj.elements.pxsCTC[idx]);
    delete docObj.elements.pxsCTC[idx];
    updateListaCosti(4);
    calcolaTotali();
}

function  deletePassthroughCTC(idx){
    $.axmr.setDeleted(docObj.elements.passthroughCTC[idx]);
    //docObj.elements.pxs2delete[docObj.elements.pxs2delete.length]=$.extend(true,{},docObj.elements.passthroughCTC[idx]);
    delete docObj.elements.passthroughCTC[idx];
    updateListaCosti(5);
    calcolaTotali();
}

function addPrezzo(descrizione,tipologia,transfer,categoria,prezzo,idx,update){
    addCosto(descrizione,tipologia,transfer,categoria,idx,prezzo,update)
}

function updateCosto(descrizione,tipologia,transfer,idx,update){
    addCosto(descrizione,tipologia,transfer,undefined,idx,undefined,update)
}

function addCosto(descrizione,tipologia,transfer,categoria,idx,prezzo,update){
    var categoriaStr='';
    var categoriaStrValue='';
    var categoriaTot='';

    if(categoria!==null && categoria!==undefined){
        categoria+='';
        console.log(categoria);
        switch(categoria){
            case '1':
                categoriaStr='<td class=\'tip-categoria\'>Interno</td>';
                categoriaStrValue='Interno';
                break;
            case '2':
                categoriaStr='<td class=\'tip-categoria\'>Esterno</td>';
                categoriaStrValue='Esterno';
                break;
            default:
                categoriaStr='<td class=\'tip-categoria\'>N.A.</td>'
                categoriaStrValue='N.A.';
                break;
        }
        categoriaTot='<td></td>';
    }
    if(tipologia==1){
        if(idx==undefined){
            var idx=docObj.elements.pxp.length;
            docObj.elements.pxp[idx]=$.extend(true,{},emptyPrestazioneXPaziente);
            docObj.elements.pxp[idx]=formToElement('dialog-form',docObj.elements.pxp[idx],folderPxp);
        }else if(update){
            docObj.elements.pxp[idx]=formToElement('dialog-form',docObj.elements.pxp[idx],folderPxp);
        }

        var remove="deletePxp("+idx+");";
    }
    else if(tipologia==2){
        if(idx==undefined){
            var idx=docObj.elements.pxs.length;
            docObj.elements.pxs[idx]=$.extend(true,{},emptyPrestazioneXStudio);
            docObj.elements.pxs[idx]=formToElement('dialog-form',docObj.elements.pxs[idx],folderPxs);
        }else if(update){
            docObj.elements.pxs[idx]=formToElement('dialog-form',docObj.elements.pxs[idx],folderPxs);
        }
        var remove="deletePxs("+idx+");";
    }
    else if(tipologia==3){
        if(idx==undefined){
            var idx=docObj.elements.pxpCTC.length;
            docObj.elements.pxpCTC[idx]=$.extend(true,{},emptyPrestazioneXPaziente);
            docObj.elements.pxpCTC[idx]=formToElement('dialog-form-cost-2',docObj.elements.pxpCTC[idx],folderPxpCTC);
        }else if(update){
            docObj.elements.pxpCTC[idx]=formToElement('dialog-form-cost-2',docObj.elements.pxpCTC[idx],folderPxpCTC);
        }

        var remove="deletePxpCTC("+idx+");";
    }
    else if(tipologia==4){
        if(idx==undefined && docObj){
            var idx=docObj.elements.pxsCTC.length;
            docObj.elements.pxsCTC[idx]=$.extend(true,{},emptyPrestazioneXStudio);
            docObj.elements.pxsCTC[idx]=formToElement('dialog-form-cost-2',docObj.elements.pxsCTC[idx],folderPxsCTC);
        }
        else if(update){
            docObj.elements.pxsCTC[idx]=formToElement('dialog-form-cost-2',docObj.elements.pxsCTC[idx],folderPxsCTC);
        }
        var remove="deletePxsCTC("+idx+");";
    }
    else if(tipologia==5){
        if(idx==undefined && docObj){
            var idx=docObj.elements.passthroughCTC.length;
            docObj.elements.passthroughCTC[idx]=$.extend(true,{},emptyPrestazioneXStudio);
            docObj.elements.passthroughCTC[idx]=formToElement('dialog-form-cost-2',docObj.elements.passthroughCTC[idx],folderPassthroughCTC);
        }
        else if(update){
            docObj.elements.pxpCTC[idx]=formToElement('dialog-form-cost-2',docObj.elements.passthroughCTC[idx],folderPassthroughCTC);
        }
        var remove="deletePassthroughCTC("+idx+");";
    }
    var id="#costs-" + tipologia ;
    $("#costo-ctc-mu-"+tipologia).remove();
    $(id+" tbody .tot-costi").remove();
    var delCol='<td></td>';
    var idTr='';
    var idTrSearch='';
    idTr=" id='tr-tip"+tipologia+"-"+idx+"' ";
    idTrSearch="#tr-tip"+tipologia+"-"+idx;
    if(!isClosed && !((tipologia==1 || tipologia==2) && prezzo!==undefined)){
        delCol="<td style='text-align:center;' ><a href='#' onclick=\" formPrezzo('"+tipologia+"','"+idx+"');return false;\"><img src='/img/edit.png' width='30px' alt='Modifica' /></a></td>";
        if(cantDelete==undefined ||!cantDelete){
            delCol+="<td style='text-align:center;' ><a href='#' onclick=\" $(this).closest('tr').remove();"+remove+"return false;\"><img src='/img/trash.png'  width='30px'  alt='X' /></a></td>";
        }else{
            delCol+="<td>&nbsp;</td>";
        }
    }else if (prezzo!==undefined){

        delCol="<td	 style='text-align:center;' ><a href='#' onclick=\" formPrezzo('"+tipologia+"','"+idx+"');return false;\"><img src='/img/edit.png' width='30px'  alt='Modifica' /></a></td>";
        //idTr=" id='costs-tr-" + idx+"'";
        //idTrSearch="#costs-tr-" + idx;
    }
    var emptyCol='';
    if(delCol){
        emptyCol='<td>&nbsp;</td>';
    }
    if(prezzo)transfer=prezzo;
    if(!update){
        $(id + " tbody").append("<tr "+idTr+" >" + "<td class='tip-descrizione' >" + descrizione + "</td>" +categoriaStr+ "<td class='tip-transfer'>" + transfer.formatMoney() + "</td>"+ delCol + "</tr>");
    }
    else{
        categoriaStrValue
        $(idTrSearch).find('.tip-descrizione').html(descrizione);
        $(idTrSearch).find('.tip-categoria').html(categoriaStrValue);
        $(idTrSearch).find('.tip-transfer').html(transfer.formatMoney());
    }
    var tot=0;
    if(tipologia==4 || tipologia==3){
        $(id+" tbody tr td:nth-child(3)").each(function(){
            console.log($(this));
            tot+=parseFloat($(this).html().unformatMoney());
        })
    }
    else{
        $(id+" tbody tr td:nth-child(2)").each(function(){
            console.log($(this));
            tot+=parseFloat($(this).html().unformatMoney());
        });
    }
    //tot=tot.toFixed(2);
    if(tipologia==5){
        totaleTH='Totale';
    }else{
        totaleTH='Totale transfer price';
    }
    if(!budgetCTC)$(id + " tbody").append("<tr class='tot-costi'>" + "<td>"+totaleTH+"</td>" +categoriaTot+ "<td id='tot_costi_"+tipologia+"'>" + tot.formatMoney() + "</td><td></td>" +emptyCol+ "</tr>");


    if(update)calcolaTotali();


}

function calcolaTotPerTipo(tipologia){
    var id="#costs-" + tipologia ;
    $(id+" .tot-costi").remove();

    var categoriaTot='';


    var tot=0;
    if(tipologia==4 || tipologia==3){
        categoriaTot='<td></td>';
        $(id+" tbody tr td:nth-child(3)").each(function(){
            console.log($(this));
            tot+=parseFloat($(this).html().unformatMoney());
        })
    }
    else{
        $(id+" tbody tr[id^=tr-tip"+tipologia+"] td:nth-child(2)").each(function(){
            console.log($(this));
            tot+=parseFloat($(this).html().unformatMoney());
        });
    }
    if(tipologia==5){
        var totaleTH='Totale';
    }else{
        var totaleTH='Totale transfer price';
    }
    //tot=tot.toFixed(2);
    $(id + " tbody").find('.tot-costi').remove();
    if(tipologia<=2 || tipologia==5)$(id + " tbody").append("<tr class='tot-costi'>" + "<td>"+totaleTH+"</td>" +categoriaTot+ "<td id='tot_costi_"+tipologia+"'>" + tot.formatMoney() + "</td><td></td>" + "</tr>");

}
function calcolaTotTabelle(){
    for(var i=1;i<=5;i++){
        calcolaTotPerTipo(i)
    }
}

function updateListaCosti(tipologia){
    var id="#costs-" + tipologia ;
    $("#costo-ctc-mu-"+tipologia).remove();
    $(id+" tbody .tot-costi").remove();
    var tot=0;
    $(id+" tbody tr td:nth-child(2)").each(function(){
        console.log($(this));
        tot+=parseFloat($(this).html().unformatMoney());
    });
    tot=tot;
    var categoria='';
    if( tipologia==4 && tipologia==3){
        categoria='<td>&nbsp;</td>';
    }
    if(tipologia==5){
        totaleTH='Totale';
    }else{
        totaleTH='Totale transfer price';
    }
    $(id + " tbody").find('.tot-costi').remove();
    if(tipologia<=2 || tipologia==5)$(id + " tbody").append("<tr class='tot-costi'>" + "<td>"+totaleTH+"</td>"+categoria + "<td id='tot_costi_"+tipologia+"'>" + tot.formatMoney() + "</td><td></td>" + "</tr>");
    calcolaTotali();
}

function loadCosti(){
    $.each(docObj.elements.pxp,function(i,element){
        if(element.metadata['Base_Nome'] && element.metadata['Costo_TransferPrice']){
            addCosto(element.metadata['Base_Nome'][0],1,element.metadata['Costo_TransferPrice'][0],null,i);
        }
    });
    $.each(docObj.elements.pxs,function(i,element){
        if(element.metadata['Base_Nome'] && element.metadata['Costo_TransferPrice']){
            addCosto(element.metadata['Base_Nome'][0],2,element.metadata['Costo_TransferPrice'][0],null,i);
        }
    });
    $.each(docObj.elements.pxpCTC,function(i,element){
        if(element.metadata ){
            if(!element.metadata['Costo_Categoria'][0])element.metadata['Costo_Categoria'][0]='';
            addCosto(element.metadata['Base_Nome'][0],3,element.metadata['Costo_Prezzo'][0],element.metadata['Costo_Categoria'][0],i);
        }
    });
    $.each(docObj.elements.pxsCTC,function(i,element){
        if(element.metadata){
            if(!element.metadata['Costo_Categoria'][0])element.metadata['Costo_Categoria'][0]='';
            addCosto(element.metadata['Base_Nome'][0],4,element.metadata['Costo_Prezzo'][0],element.metadata['Costo_Categoria'][0],i);
        }
    });
    $.each(docObj.elements.passthroughCTC,function(i,element){
        if(element.metadata['Base_Nome'] && element.metadata['Costo_TransferPrice']){
            addCosto(element.metadata['Base_Nome'][0],5,element.metadata['Costo_TransferPrice'][0],null,i);
        }
    });
    if (budgetCTC){
        if(getDato(docObj.elements.budgetStudio.metadata['BudgetCTC_NumeroPazienti'])!=pazienti && getDato(docObj.elements.budgetStudio.metadata['BudgetCTC_NumeroPazienti'])>0){
            pazienti=getDato(docObj.elements.budgetStudio.metadata['BudgetCTC_NumeroPazienti']);
        }else if(getDato(docObj.elements.budgetStudio.metadata['BudgetCTC_NumeroPazienti'])!=pazienti){
            $.axmr.setUpdated(docObj.elements.budgetStudio);
        }

        docObj.elements.budgetStudio.metadata['BudgetCTC_NumeroPazienti']=pazienti;
        $('#show-n-pat').html(pazienti);
    }
    //$('#markup-ins').html(markup);
    //updateListaCosti(1);

    //updateListaCosti(2);

}

function loadPrezzi(){
    //ciclo i prezzi
    var prezzi=new Array();
    var indici=new Array();
    var notInitiated=(!docObj.elements.pxp.length && !docObj.elements.pxs.length);
    $.each(docObj.elements.prezzi, function(i,currPrezzo){
        var currPrestazione=getDato(currPrezzo.metadata['PrezzoFinale_Prestazione']);
        indici[currPrestazione.id]=i;
        prezzi[currPrestazione.id]=currPrezzo;
        if(notInitiated){
            if(currPrestazione.type.typeId=='PrestazioneXPaziente'){
                docObj.elements.pxp[docObj.elements.pxp.length]=currPrestazione;
            }else if (currPrestazione.type.typeId=='PrestazioneXStudio'){
                docObj.elements.pxs[docObj.elements.pxs.length]=currPrestazione;
            }
        }
    });
    var prezzo;
    var indice;
    $.each(docObj.elements.pxp,function(i,element){
        if(element.metadata['Base_Nome'] && element.metadata['Costo_TransferPrice']){
            if(prezzi[element.id]){
                prezzo=getDato(prezzi[element.id].metadata['PrezzoFinale_Prezzo']);
                indice=indici[element.id];
            }
            else {
                indice=docObj.elements.prezzi.length;

                var newPrezzo=$.extend(true,{},emptyPrezzoPrestazione);
                newPrezzo.parent=folderPrezzi;
                newPrezzo.metadata['PrezzoFinale_Prestazione'][0]=element;
                docObj.elements.prezzi[indice]=newPrezzo;
                prezzo='';
            }
            addPrezzo(element.metadata['Base_Nome'][0],1,element.metadata['Costo_TransferPrice'][0],null,prezzo,indice);
        }
    });
    $.each(docObj.elements.pxs,function(i,element){
        if(element.metadata['Base_Nome'] && element.metadata['Costo_TransferPrice']){
            if(prezzi[element.id]){
                prezzo=getDato(prezzi[element.id].metadata['PrezzoFinale_Prezzo']);
                indice=indici[element.id];
            }
            else {
                indice=docObj.elements.prezzi.length;

                var newPrezzo=$.extend(true,{},emptyPrezzoPrestazione);
                newPrezzo.parent=folderPrezzi;
                newPrezzo.metadata['PrezzoFinale_Prestazione'][0]=element;
                docObj.elements.prezzi[indice]=newPrezzo;
                prezzo='';
            }
            addPrezzo(element.metadata['Base_Nome'][0],2,element.metadata['Costo_TransferPrice'][0],null,prezzo,indice);
        }
    });
    $.each(docObj.elements.pxpCTC,function(i,element){
        if(element.metadata){
            prezzo=getDato(element.metadata['Costo_Prezzo']);
            if(!getDato(element.metadata['Costo_Categoria'])){
                element.metadata['Costo_Categoria']=[];
                element.metadata['Costo_Categoria'][0]='';
            }
            addPrezzo(element.metadata['Base_Nome'][0],3,getDato(element.metadata['Costo_Prezzo']),getDato(element.metadata['Costo_Categoria']),prezzo,i);
        }
    });
    $.each(docObj.elements.pxsCTC,function(i,element){
        if(element.metadata){
            prezzo=getDato(element.metadata['Costo_Prezzo']);
            if(!element.metadata['Costo_Categoria'][0])element.metadata['Costo_Categoria'][0]='';
            addPrezzo(element.metadata['Base_Nome'][0],4,getDato(element.metadata['Costo_Prezzo']),getDato(element.metadata['Costo_Categoria']),prezzo,i);
        }
    });
    $.each(docObj.elements.passthroughCTC,function(i,element){
        if(element.metadata){
            prezzo=getDato(element.metadata['Costo_TransferPrice']);
            addPrezzo(element.metadata['Base_Nome'][0],5,element.metadata['Costo_Prezzo'][0],null,prezzo,i);
        }
    });
    docObj.elements.budgetStudio.metadata['BudgetCTC_NumeroPazienti']=pazienti;
    $('#show-n-pat').html(pazienti);
    //updateListaCosti(1);

    //updateListaCosti(2);

}


function bracciFromElementToForm(element){
    var bracciStr=getDato(element.metadata['Costo_Braccio']);
    var bracci;
    $('[name=braccioInputCheck]').each(function(){
        this.checked=false;
    });
    if(!bracciStr || bracciStr.match(/^\s*$/)){
        $('#tuttiBracci').each(function(){
            this.checked=true;
        });
    }else{

        $('#tuttiBracci').each(function(){
            this.checked=false;
        });
        bracciStr=bracciStr.replace(/^\|?/,'');
        bracciStr=bracciStr.replace(/\|?$/,'');
        bracci=bracciStr.split('||');
        $.each(bracci,function(i,key){
            $('[name=braccioInputCheck][value="'+key+'"]').each(function(){
                this.checked=true;
            });
        })
    }
}

function bracciFromFormToElement(element){
    var all=false;
    var value='';
    $('#tuttiBracci').each(function(){
        if(this.checked){
            all=true;
        }
    });
    if(all){
        element.metadata['Costo_Braccio']='';
        return element;
    }

    $('[name=braccioInputCheck]').each(function(){
        if(this.checked){
            value+='|'+this.value+'|';
        }
    });

    element.metadata['Costo_Braccio']=value;

    return element;
}

function deleteCA(idx){
    $.axmr.setDeleted(docObj.elements.costiAggiuntivi[idx]);

    delete docObj.elements.costiAggiuntivi[idx];

}
function formCostoAggiuntivo(idx){
    var form='dialog-form-ca';
    var myElement=docObj.elements.costiAggiuntivi[idx];



    elementToForm(myElement,form);
    $('#'+form).find('#costoIdx').val(idx);




    $("#"+form).dialog("open");
}

function addCostoToTable(form,idx){
    var myElement;
    var update=false;

    if(idx==undefined){
        var idx=docObj.elements.costiAggiuntivi.length;
        docObj.elements.costiAggiuntivi[idx]=$.extend(true,{},emptyCostoAggiuntivo);
        docObj.elements.costiAggiuntivi[idx]=formToElement(form,docObj.elements.costiAggiuntivi[idx],folderCostiAggiuntivi);
    }else if(form!='' && form!='load'){
        update=true;
        docObj.elements.costiAggiuntivi[idx]=formToElement(form,docObj.elements.costiAggiuntivi[idx],folderCostiAggiuntivi);
    }

    var remove="deleteCA("+idx+");";

    var id="#added-ca" ;

    //$(id+" tbody .tot-costi").remove();
    var delCol='<td>&nbsp;</td><td>&nbsp;</td>';
    var idTr='';
    var idTrSearch='';
    var prezzo=undefined;
    idTr=" id='tr-ca-"+idx+"' ";
    idTrSearch="#tr-ca-"+idx;
    if(!isClosed){
        delCol="<td style='text-align:center;' ><a href='#' onclick=\" formCostoAggiuntivo('"+idx+"');return false;\"><img src='/img/edit.png' width='30px' alt='Modifica' /></a></td>";
        if((cantDelete==undefined ||!cantDelete) && updating){
            delCol+="<td style='text-align:center;' ><a href='#' onclick=\" $(this).closest('tr').remove();"+remove+"return false;\"><img src='/img/trash.png'  width='30px'  alt='X' /></a></td>";
        }else{
            delCol+="<td>&nbsp;</td>";
        }
    }else if (prezzo!==undefined){

        delCol="<td	 style='text-align:center;' ><a href='#' onclick=\" formCostoAggiuntivo('"+idx+"');return false;\"><img src='/img/edit.png' width='30px'  alt='Modifica' /></a></td><td>&nbsp;</td>";
        //idTr=" id='costs-tr-" + idx+"'";
        //idTrSearch="#costs-tr-" + idx;
    }
    var myElement=docObj.elements.costiAggiuntivi[idx];
    var categoria=getDato(myElement.metadata['CostoAggiuntivo_Tipologia']).split('###')[1] || '';
    var descrizione=getDato(myElement.metadata['CostoAggiuntivo_OggettoPrincipale']) || '';
    var descrizioneControllo=getDato(myElement.metadata['CostoAggiuntivo_OggettoControllo']) || '';
    var quantita=getDato(myElement.metadata['CostoAggiuntivo_Quantita']) || '';
    quantita=quantita?quantita:'0';
    var costo=getDato(myElement.metadata['CostoAggiuntivo_Costo']) || '0.00';

    if(budgetCTC) delCol='';
    if(!costo){costo='0.00';}

    if(!update){
        //HDCRPMS-986
        //$(id + " tbody").append("<tr "+idTr+" >" + "<td class='categoria' >" + categoria + "</td>" +"<td class='descrizione' >" + descrizione + "</td>" +"<td class='descrizione-controllo' >" + descrizioneControllo + "</td>" +"<td class='quantita' >" + quantita + "</td>" +"<td class='costo' >" + costo.formatMoney() + "</td>"+ delCol + "</tr>");
        //cambiato con (tolto td descrizione-controllo)
        $(id + " tbody").append("<tr "+idTr+" >" + "<td class='categoria' >" + categoria + "</td>" +"<td class='descrizione' >" + descrizione + "</td>" +"<td class='quantita' >" + quantita + "</td>" +"<td class='costo' >" + costo.formatMoney() + "</td>"+ delCol + "</tr>");
    }
    else{

        $(idTrSearch).find('.categoria').html(categoria);
        $(idTrSearch).find('.descrizione').html(descrizione);
        //$(idTrSearch).find('.descrizione-controllo').html(descrizioneControllo);HDCRPMS-986
        $(idTrSearch).find('.quantita').html(quantita);
        $(idTrSearch).find('.costo').html(costo.formatMoney());

    }

}

$(function() {
    var tipologia = $("#tipologia"), descrizione = $("#descrizione"), costo = $("#costo-costo"), markupCosto =  $("#markup-costo"), transfer =  $("#transfer-costo"), allFields = $([]).add(tipologia).add(descrizione).add(costo), tips = $(".validateTips");
    function updateTips(t) {
        tips.text(t).addClass("ui-state-highlight");
        setTimeout(function() {
            tips.removeClass("ui-state-highlight", 1500);
        }, 500);
    }

    function checkLength(o, n, min, max) {
        if(o.val().length > max || o.val().length < min) {
            o.addClass("ui-state-error");
            updateTips("Length of " + n + " must be between " + min + " and " + max + ".");
            return false;
        } else {
            return true;
        }
    }

    function checkRegexp(o, regexp, n) {
        if(!(regexp.test(o.val()) )) {
            o.addClass("ui-state-error");
            updateTips(n);
            return false;
        } else {
            return true;
        }
    }

    function checkAll() {
        var result=true;
        for(var key in arguments){

            var o=arguments[key];
            if($.trim(o.val())=='' ) {
                o.addClass("ui-state-error");
                updateTips('Campo obbligatorio');
                result=false;
            }
        }
        return result;
    }




    $("#dialog-form").dialog({
        autoOpen : false,
        height : 400,
        width : 450,
        modal : true,
        position: { my: "center", at: "center top", of: document.getElementById('centerElement') },
        buttons : [
            {
                text:"Aggiungi costo",
                click: function() {
                    var bValid = true;
                    allFields.removeClass("ui-state-error");
                    bValid = bValid && checkAll(tipologia,descrizione,costo);
                    var idx=$("#idx").val();
                    var update=false;
                    if(isNaN(idx) || (!idx && idx!==0))idx=undefined;
                    else update=true;
                    if(tipologia.val()==''){
                        bootbox.alert('Attenzione scegliere un valore per il campo "Tipo di applicazione"');
                        return false;
                    }
                    else if(!$(this).find('[name=Prestazioni_CDC]').val()){
                        bootbox.alert('Attenzione scegliere un valore per il campo "Servizi/Sezioni coinvolti"');
                        return false;
                    }
                    else if(descrizione.val()==''){
                        bootbox.alert('Attenzione scegliere un valore per il campo "Descrizione"');
                        return false;
                    }
                    else if(!$(this).find('[name=Prestazioni_Attivita]').val()){
                        bootbox.alert('Attenzione scegliere un valore per il campo "Tipologia Attività"');
                        return false;
                    }
                    else if(!$(this).find('[name=Costo_Copertura]').val()){
                        bootbox.alert('Attenzione scegliere un valore per il campo "Copertura del costo"');
                        return false;
                    }
                    else if($(this).find('[name=Costo_Quantita]').is(":visible") && !$(this).find('[name=Costo_Quantita]').val()){
                        bootbox.alert('Attenzione scegliere un valore per il campo "Quantità a paziente"');
                        return false;
                    }
                    else if(!$(this).find('[name=Costo_TransferPrice]').val()){
                        bootbox.alert('Attenzione scegliere un valore per il campo "Importo (Tariffa) (€)"');
                        return false;
                    }
                    else  {
                        saveCosto($("#dialog-form form"));
                        /*
                        updateCosto(descrizione.val(),tipologia.val(),transfer.val(),idx,update);
                        */
                        $(this).dialog("close");
                    }
                },
                "class" : "btn btn-primary btn-xs"
            },
            {
                text: "Annulla",
                click: function() {
                    $(this).dialog("close");
                },
                "class" : "btn btn-xs"
            }
        ],
        open:function(){
            var that=this;
            var width=$(window).width()/100*80;
            var height=$(window).height()/100*80;
            //$(this).dialog('option',{width:width,height:height});
            $(this).dialog('option',{height:height});
            var setTransfer=function(){
                if($(that).find('select[id^=unita-markup]').val()==2){
                    var costo=parseFloat($(that).find('input[id^=costo]').val()-0);
                    var aggiunta=costo * parseFloat($(that).find('input[id^=markup]').val()-0) / 100;
                    var value=costo+aggiunta;
                } else{
                    var value=parseFloat($(that).find('input[id^=costo]').val()-0)+parseFloat($(that).find('input[id^=markup]').val()-0);
                }
                $(that).find('input[id^=transfer]').val(value);
            };
            var setMarkup=function(){
                if($(that).find('input[id^=transfer]').val()>0 && $(that).find('input[id^=costo]').val()>0){
                    $(that).find('select[id^=unita-markup]').val(1);
                    var value=parseFloat($(that).find('input[id^=transfer]').val())-parseFloat($(that).find('input[id^=costo]').val());
                    $(that).find('input[id^=markup]').val(value);
                }
            };
            $(this).find('input[id^=costo]').off('change').on('change',setTransfer);
            $(this).find('input[id^=markup]').off('change').on('change',setTransfer);
            $(this).find('select[id^=unita-markup]').off('change').on('change',setTransfer);
            $(this).find('input[id^=transfer]').off('change').on('change',setMarkup);
            if(!$('#descrizione').prop('disabled') &&  !$('#Costo_QuantitaNA').prop('checked')){
                $(this).find('#Costo_Quantita').prop('disabled',false);
                if ($(this).find('#Costo_Quantita').val()==''){
                    $(this).find('#Costo_Quantita').val('1');
                }
            }else{
                $(this).find('#Costo_Quantita').prop('disabled',true);
                if($('#Costo_QuantitaNA').prop('checked')){
                    $(this).find('#Costo_Quantita').val('0.00');
                }
            }

            changeTipologia();
        },
        close : function() {
            allFields.not('.dont-clear').val("").removeClass("ui-state-error");
        }
    });
    $("#create-cost").button().click(function() {
        $("#dialog-form").find(':input').not('.dont-clear').not(':radio').not(':checkbox').val('');
        $("#dialog-form").find(':radio').prop('checked',false);
        $("#dialog-form").find(':checkbox').prop('checked',false);
        $('#tipologia').removeAttr('disabled');
        $('#Costo_Quantita').removeAttr('disabled');
        $('#Costo_QuantitaNA').prop('checked',false);
        console.log('Eccomi');
        $('#unita-markup-costo').find('option').removeAttr('selected').prop('selected',false).first().prop('selected',true);
        $("#dialog-form").dialog("open");
        $('#dialog-form form').attr('data-type','create');
        $('#dialog-form form').attr('data-id','0');
    });

    $("#dialog-form-cost-2").dialog({
        autoOpen : false,
        height : 400,
        width : 450,
        modal : true,
        position: { my: "center", at: "center top", of: document.getElementById('centerElement') },
        buttons:[
            {
                text:"Aggiungi costo",
                click: function() {
                    var bValid = true;
                    var tipologia = $("#tipologia2"), descrizione = $("#Prestazioni_prestazione"), costo = $("#costo2"), markupCosto = $("#markup-costo2"), transfer = $("#transfer-costo2"), categoria = $("#interno_esterno"), allFields = $([]).add(tipologia).add(descrizione).add(costo), tips = $(".validateTips");
                    var idx=$("#idx").val();
                    var update=false;
                    if(isNaN(idx) || (!idx && idx!==0))idx=undefined;
                    else update=true;
                    allFields.removeClass("ui-state-error");
                    bValid = bValid && checkAll(tipologia,descrizione,costo);
                    /*bValid = bValid && checkLength(name, "username", 3, 16);
                     bValid = bValid && checkLength(email, "email", 6, 80);
                     bValid = bValid && checkLength(password, "password", 5, 16);
                     bValid = bValid && checkRegexp(name, /^[a-z]([0-9a-z_])+$/i, "Username may consist of a-z, 0-9, underscores, begin with a letter.");
                     // From jquery.validate.js (by joern), contributed by Scott Gonzalez: http://projects.scottsplayground.com/email_address_validation/
                     bValid = bValid && checkRegexp(email, /^((([a-z]|\d|[!#\$%&'\*\+\-\/=\?\^_`{\|}~]|[\u00A0-\uD7FF\uF900-\uFDCF\uFDF0-\uFFEF])+(\.([a-z]|\d|[!#\$%&'\*\+\-\/=\?\^_`{\|}~]|[\u00A0-\uD7FF\uF900-\uFDCF\uFDF0-\uFFEF])+)*)|((\x22)((((\x20|\x09)*(\x0d\x0a))?(\x20|\x09)+)?(([\x01-\x08\x0b\x0c\x0e-\x1f\x7f]|\x21|[\x23-\x5b]|[\x5d-\x7e]|[\u00A0-\uD7FF\uF900-\uFDCF\uFDF0-\uFFEF])|(\\([\x01-\x09\x0b\x0c\x0d-\x7f]|[\u00A0-\uD7FF\uF900-\uFDCF\uFDF0-\uFFEF]))))*(((\x20|\x09)*(\x0d\x0a))?(\x20|\x09)+)?(\x22)))@((([a-z]|\d|[\u00A0-\uD7FF\uF900-\uFDCF\uFDF0-\uFFEF])|(([a-z]|\d|[\u00A0-\uD7FF\uF900-\uFDCF\uFDF0-\uFFEF])([a-z]|\d|-|\.|_|~|[\u00A0-\uD7FF\uF900-\uFDCF\uFDF0-\uFFEF])*([a-z]|\d|[\u00A0-\uD7FF\uF900-\uFDCF\uFDF0-\uFFEF])))\.)+(([a-z]|[\u00A0-\uD7FF\uF900-\uFDCF\uFDF0-\uFFEF])|(([a-z]|[\u00A0-\uD7FF\uF900-\uFDCF\uFDF0-\uFFEF])([a-z]|\d|-|\.|_|~|[\u00A0-\uD7FF\uF900-\uFDCF\uFDF0-\uFFEF])*([a-z]|[\u00A0-\uD7FF\uF900-\uFDCF\uFDF0-\uFFEF])))\.?$/i, "eg. ui@jquery.com");
                     bValid = bValid && checkRegexp(password, /^([0-9a-zA-Z])+$/, "Password field only allow : a-z 0-9");*/
                    if(descrizione.val()!='' && $('#prezzo-add').val()!='') {
                        prezzo=$('#prezzo-add').val();
                        var categoriaVal=(tipologia.val()==3 || tipologia.val()==4)?categoria.val():undefined;
                        addPrezzo(descrizione.val(),tipologia.val(),transfer.val(),categoriaVal,prezzo,idx,update);
                        calcolaTotali();
                        $(this).dialog("close");
                    }else if(descrizione.val()==''){
                        bootbox.alert('Attenzione inserire la descrizione');
                    }
                    else if($('#prezzo-add').val()==''){
                        bootbox.alert('Attenzione inserire il prezzo');
                    }
                },
                "class" : "btn btn-primary btn-xs"
            },
            {
                text: "Annulla",
                click:function() {
                    $(this).dialog("close");
                },
                "class" : "btn btn-xs"
            }
        ],

        open:function(){
            var width=$(window).width()/100*80;
            var height=$(window).height()/100*80;
            //$(this).dialog('option',{width:width,height:height});
            $(this).dialog('option',{height:height});
            var that=this;
            var setTransfer=function(){
                if($(that).find('select[id^=unita-markup]').val()==2){
                    var costo=parseFloat($(that).find('input[id^=costo]').val()-0);
                    var aggiunta=costo * parseFloat($(that).find('input[id^=markup]').val()-0) / 100;
                    var value=costo+aggiunta;
                } else{
                    var value=parseFloat($(that).find('input[id^=costo]').val()-0)+parseFloat($(that).find('input[id^=markup]').val()-0);
                }
                $(that).find('input[id^=prezzo]').val(value);
            };
            var setMarkup=function(){
                if($(that).find('input[id^=prezzo]').val()>0 && $(that).find('input[id^=costo]').val()>0){
                    $(that).find('select[id^=unita-markup]').val(1);
                    var value=parseFloat($(that).find('input[id^=prezzo]').val())-parseFloat($(that).find('input[id^=costo]').val());
                    $(that).find('input[id^=markup]').val(value);
                }
            };
            $(this).find('input[id^=costo]').off('change').on('change',setTransfer);
            $(this).find('input[id^=markup]').off('change').on('change',setTransfer);
            $(this).find('select[id^=unita-markup]').off('change').on('change',setTransfer);
            $(this).find('input[id^=prezzo]').off('change').on('change',setMarkup);
            if(!$('#Prestazioni_prestazione').prop('disabled') &&  !$('#Costo_QuantitaNA').prop('checked')){
                $(this).find('#Costo_Quantita').prop('disabled',false);
            }else{
                $(this).find('#Costo_Quantita').prop('disabled',true);
                if($('#Costo_QuantitaNA').prop('checked')){
                    $(this).find('#Costo_Quantita').val('0.00');
                }
            }
        },
        close : function() {
            allFields.not('.dont-clear').val("").removeClass("ui-state-error");
        }
    });
    $("#create-cost-2").button().click(function() {
        $("#dialog-form-cost-2").find(':input').not('[type=radio]').not('.dont-clear').val('');
        $("#dialog-form-cost-2").find(':input[type=radio]').not('.dont-clear').prop('checked',false).removeAttr('checked');
        //$("#idx").val('');
        //$('#tipologia2').val('');
        $('#tipologia2').removeAttr('disabled');
        $('#unita-markup-costo2').find('option').removeAttr('selected').prop('selected',false).first().prop('selected',true);
        $("#dialog-form-cost-2").dialog("open");
        $('#Costo_Quantita').removeAttr('disabled');
        $('#Costo_QuantitaNA').prop('checked',false);
    });


    /*$("#CostoAggiuntivo_Tipologia-select").change(function(){
        var currSelection=this.value;
        if(currSelection.match('###')){
            currSelection=currSelection.split('###')[0];

            $("#dialog-form-ca").find('.input-hide-show').not('.show-tipo'+currSelection).hide();
            $("#dialog-form-ca").find('.input-hide-show').not('.show-tipo'+currSelection).find(':input').not(':radio').val('');
            $("#dialog-form-ca").find('.input-hide-show').not('.show-tipo'+currSelection).find(':radio').prop('checked',false);
            $('.show-tipo'+currSelection).show();
        }else{
            $("#dialog-form-ca").find('.input-hide-show').hide();
        }
    });*/

    $("#create-ca").button().click(function() {
        $("#dialog-form-ca").find('.input-hide-show').hide();
        $("#dialog-form-ca").find(':input').not(':radio').val('');
        $("#dialog-form-ca").find(':radio').prop('checked',false);
        //$('[name=CostoAggiuntivo_Tipologia]').removeAttr('disabled');

        //$('#unita-markup-costo').find('option').removeAttr('selected').prop('selected',false).first().prop('selected',true);
        $("#dialog-form-ca").dialog("open");
        $('#dialog-form-ca form').attr('data-type','create');
        $('#dialog-form-ca form').attr('data-id','0');
    });

    $("#dialog-form-ca").dialog({
        autoOpen : false,
        height : 300,
        width : 350,
        modal : true,
        position: { my: "center", at: "center top", of: document.getElementById('centerElement') },
        buttons:[
            {
                text:"Aggiungi costo",
                click: function() {
                    var bValid = true;
                    var tipologia = $("#CostoAggiuntivo_Tipologia-select"), descrizione = $("#CostoAggiuntivo_OggettoPrincipale"), costo = $("#costo2"), markupCosto = $("#markup-costo2"), transfer = $("#transfer-costo2"), categoria = $("#interno_esterno"), allFields = $([]).add(tipologia).add(descrizione).add(costo), tips = $(".validateTips");
                    var idx=$('#costoIdx').val();
                    var update=false;
                    if(isNaN(idx) || (!idx && idx!==0))idx=undefined;
                    else update=true;
                    allFields.removeClass("ui-state-error");
                    bValid = bValid && checkAll(tipologia,descrizione,costo);
                    /*bValid = bValid && checkLength(name, "username", 3, 16);
                    bValid = bValid && checkLength(email, "email", 6, 80);
                    bValid = bValid && checkLength(password, "password", 5, 16);
                    bValid = bValid && checkRegexp(name, /^[a-z]([0-9a-z_])+$/i, "Username may consist of a-z, 0-9, underscores, begin with a letter.");
                    // From jquery.validate.js (by joern), contributed by Scott Gonzalez: http://projects.scottsplayground.com/email_address_validation/
                    bValid = bValid && checkRegexp(email, /^((([a-z]|\d|[!#\$%&'\*\+\-\/=\?\^_`{\|}~]|[\u00A0-\uD7FF\uF900-\uFDCF\uFDF0-\uFFEF])+(\.([a-z]|\d|[!#\$%&'\*\+\-\/=\?\^_`{\|}~]|[\u00A0-\uD7FF\uF900-\uFDCF\uFDF0-\uFFEF])+)*)|((\x22)((((\x20|\x09)*(\x0d\x0a))?(\x20|\x09)+)?(([\x01-\x08\x0b\x0c\x0e-\x1f\x7f]|\x21|[\x23-\x5b]|[\x5d-\x7e]|[\u00A0-\uD7FF\uF900-\uFDCF\uFDF0-\uFFEF])|(\\([\x01-\x09\x0b\x0c\x0d-\x7f]|[\u00A0-\uD7FF\uF900-\uFDCF\uFDF0-\uFFEF]))))*(((\x20|\x09)*(\x0d\x0a))?(\x20|\x09)+)?(\x22)))@((([a-z]|\d|[\u00A0-\uD7FF\uF900-\uFDCF\uFDF0-\uFFEF])|(([a-z]|\d|[\u00A0-\uD7FF\uF900-\uFDCF\uFDF0-\uFFEF])([a-z]|\d|-|\.|_|~|[\u00A0-\uD7FF\uF900-\uFDCF\uFDF0-\uFFEF])*([a-z]|\d|[\u00A0-\uD7FF\uF900-\uFDCF\uFDF0-\uFFEF])))\.)+(([a-z]|[\u00A0-\uD7FF\uF900-\uFDCF\uFDF0-\uFFEF])|(([a-z]|[\u00A0-\uD7FF\uF900-\uFDCF\uFDF0-\uFFEF])([a-z]|\d|-|\.|_|~|[\u00A0-\uD7FF\uF900-\uFDCF\uFDF0-\uFFEF])*([a-z]|[\u00A0-\uD7FF\uF900-\uFDCF\uFDF0-\uFFEF])))\.?$/i, "eg. ui@jquery.com");
                    bValid = bValid && checkRegexp(password, /^([0-9a-zA-Z])+$/, "Password field only allow : a-z 0-9");*/
                    var passed=true;
                    if(tipologia.val()==''){
                        bootbox.alert('Attenzione inserire la tipologia');
                        passed=false;
                        return;
                    }
                    if(descrizione.val()=='') {
                        bootbox.alert('Attenzione inserire la descrizione');
                        passed=false;
                        return;
                    }
                    /*if($("input[name=CostoAggiuntivo_Previsto]:checked").val()===undefined){
                        bootbox.alert('Attenzione selezionare un\'opzione per Previsto');
                        passed=false;
                        return;
                    }*/
                    if($("#CostoAggiuntivo_Quantita").val()=='') {
                        bootbox.alert('Attenzione inserire la Quantità');
                        passed=false;
                        return;
                    }
                    if($("#CostoAggiuntivo_Costo").val()=='') {
                        bootbox.alert('Attenzione inserire il Totale Valore');
                        passed=false;
                        return;
                    }
                    if($("#CostoAggiuntivo_Copertura").val()===undefined || $("#CostoAggiuntivo_Copertura").val()=='') {
                        bootbox.alert('Attenzione inserire la Copertura oneri finanziari');
                        passed=false;
                        return;
                    }
                    if(passed){
                        //addCostoToTable("dialog-form-ca",idx);
                        saveCosto($("#dialog-form-ca form"));
                        //calcolaTotali();
                        $(this).dialog("close");
                    }
                },
                "class" : "btn btn-primary btn-xs"
            },
            {
                text: "Annulla",
                click:function() {
                    $(this).dialog("close");
                },
                "class" : "btn btn-xs"
            }
        ],

        open:function(){
            var width=$(window).width()/100*80;
            var height=$(window).height()/100*80;
            $(this).dialog('option',{width:width,height:height});
            var that=this;

        },
        close : function() {
            $('input.ui-state-error').removeClass("ui-state-error");
        }
    });
    $("#create-cost-2").button().click(function() {
        $("#dialog-form-cost-2").find(':input').not('[type=radio]').not('.dont-clear').val('');
        $("#dialog-form-cost-2").find(':input[type=radio]').not('.dont-clear').prop('checked',false).removeAttr('checked');
        //$("#idx").val('');
        //$('#tipologia2').val('');
        $('#Costo_Quantita').removeAttr('disabled');
        $('#tipologia2').removeAttr('disabled');
        $('#unita-markup-costo2').find('option').removeAttr('selected').prop('selected',false).first().prop('selected',true);
        $("#dialog-form-cost-2").dialog("open");
    });



    function creaPrestazione(value,row){
        var altro=$.extend(true,{},emptyVoce);
        altro.metadata['PrestazioniDizionario_Descrizione'][0]= value;
        saveElement(altro,folderDizionario);
        $('#example').handsontable('setDataAtCell',row,0,value);

    }

    $("#prestazione-dialog").dialog({
        autoOpen : false,
        height : 300,
        width : 450,
        modal : true,
        position: { my: "center", at: "center top", of: document.getElementById('centerElement') },
        buttons:[
            {
                text:"Nuova prestazione",
                click: function() {
                    var newValue=$('#Altro_Descrizione').val();
                    if(dizPrestazioni[newValue]){
                        alert('Prestazione già presente nel dizionario');
                    }else{
                        creaPrestazione(newValue,rowAltro);
                    }

                    $(this).dialog("close");

                },
                "class" : "btn btn-primary btn-xs"
            },
            {
                text: "Annulla",
                click:function() {
                    $(this).dialog("close");
                },
                "class" : "btn btn-xs"
            }
        ],

        open:function(){

        },
        close : function() {
            allFields.not('.dont-clear').val("").removeClass("ui-state-error");
        }
    });

    $('[name=TimePoint_DescrizioneSelect-select]').change(function(){
        var value=$(this).find('option:selected').val();
        if(value && value.match(/7###/)){
            $('#TimePoint-TimePoint_Descrizione').show();
        }else{
            $('#TimePoint-TimePoint_Descrizione').hide();
        }
    });
    $("#tp-dialog-form").dialog({
        autoOpen : false,
        height : 500,
        width : 550,
        modal : true,
        position: { my: "center", at: "center top", of: document.getElementById('centerElement') },
        buttons:[
            {
                text:"Aggiungi visita",
                click: function() {


                },
                "class" : "btn btn-primary btn-xs"
            },
            {
                text: "Annulla",
                click:function() {
                    $(this).dialog("close");
                },
                "class" : "btn btn-xs"
            }
        ],

        close : function() {
            allFields.not('.dont-clear').val("").removeClass("ui-state-error");
        }
    });
    $("#tp-button").button().click(function() {
        $("#tp-dialog-form").off('dialogopen').on('dialogopen',function(ev){
            var width=$(window).width()/100*80;
            var height=$(window).height()/100*80;
            //$(this).dialog('option',{width:width,height:height});
            ev=ev?ev:window.event;
            var that=this;
            $(this).find('input').not('.dont-clear').each(function(){
                $(this).val('');
            });


            $(this).find('input[id^=titolo]').focus();

            $(this).parent().find('button:contains(Aggiungi)').off('click').on('click',function(){
                var newData=new Array();
                var newValue='';
                $(that).find('input').each(function(){
                    newData[this.id]=$(this).val();
                    if(this.id.match(/^titolo/))newValue=$(this).val();
                });
                //console.log(newValue);


                var table=$('#example');
                //$(td).html($(that).find('input[id^=titolo]').val());
                $('#example').handsontable('deselectCell');
                if($(that).find('input[id=numero-tp]').val()>0)var index=  parseInt($(that).find('input[id=numero-tp]').val());
                else {
                    var index = parseInt($('#example').data('handsontable').getData()[0].length-10);
                }
                table.handsontable('alter','insert_col',(index-0));
                table.handsontable('setDataAtCell',0,(index-0),newValue);
                $("#tp-dialog-form").dialog('close');
            });


        });
        $("#tp-dialog-form").dialog("open");
    });
    $("#dialog-form-transfer").dialog({
        autoOpen : false,
        height : 400,
        width : 450,
        modal : true,
        position: { my: "center", at: "center top", of: document.getElementById('centerElement') },
        buttons:[
            {
                text:"Aggiungi transfer price",
                click: function() {
                    $(this).dialog("close");
                },
                "class" : "btn btn-primary btn-xs"
            },
            {
                text:"Applica alla riga intera",
                click: function() {
                    $(this).dialog("close");
                },
                "class" : "btn btn-primary btn-xs"
            },
            {
                text: "Annulla",
                click:function() {
                    $(this).dialog("close");
                },
                "class" : "btn btn-xs"
            }
        ],

        close : function() {
            allFields.not('.dont-clear').val("").removeClass("ui-state-error");
        }
    });
    $("#dialog-form-prezzo").dialog({
        autoOpen : false,
        height : 400,
        width : 450,
        modal : true,
        position: { my: "center", at: "center top", of: document.getElementById('centerElement') },
        buttons:[
            {
                text:"Aggiungi prezzo",
                click: function() {
                    $(this).dialog("close");
                },
                "class" : "btn btn-primary btn-xs"
            },
            {
                text: "Annulla",
                click:function() {
                    $(this).dialog("close");
                },
                "class" : "btn btn-xs"
            }
        ],
        close : function() {
            allFields.not('.dont-clear').val("").removeClass("ui-state-error");
        }
    });
    $("#prestazione-dialog-form").dialog({
        autoOpen : false,
        height : 400,
        width : 450,
        modal : true,

        position: { my: "center", at: "center top", of: document.getElementById('centerElement') },
        buttons:[
            {
                text:"Aggiungi prestazione",
                click: function() {

                },
                "class" : "btn btn-primary btn-xs"
            },
            {
                text: "Annulla",
                click:function() {
                    $(this).dialog("close");
                },
                "class" : "btn btn-xs"
            }
        ],

        open:function(){
            var width=$(window).width()/100*80;
            var height=$(window).height()/100*80;
            //$(this).dialog('option',{width:width,height:height});
        },
        close : function() {
            allFields.not('.dont-clear').val("").removeClass("ui-state-error");
        }
    });
    $("#prestazione-button").button().click(function() {
        $("#prestazione-dialog-form").dialog("open");
    });

    /*$("#dialog-form-CTC").dialog({
        autoOpen : false,
        height : 400,
        width : 450,
        modal : true,

        position: { my: "center", at: "center top", of: document.getElementById('centerElement') },
        buttons:[
            {
                text:"Aggiungi overhead",
                click:  function() {

                    //var totali=calcolaTotali();
                    //var handsontable2 =  $('#costi').data('handsontable');

                    //handsontable2.loadData(totali);
                    formToElement('dialog-form-CTC',docObj.elements.budgetStudio,folderBudgetStudio);
                    //docObj.elements.budgetStudio.metadata['BudgetCTC_Markup']=0;
                    var markup1=parseFloat(getDato(docObj.elements.budgetStudio.metadata['BudgetCTC_Markup1']));
                    var markup2=parseFloat(getDato(docObj.elements.budgetStudio.metadata['BudgetCTC_Markup2']));
                    if(!isNaN(markup1)) docObj.elements.budgetStudio.metadata['BudgetCTC_Markup']=markup1;
                    if(!isNaN(markup2)) docObj.elements.budgetStudio.metadata['BudgetCTC_Markup']+=markup2;
                    updatePrezzi(docObj.elements.budgetStudio.metadata['BudgetCTC_Markup']);
                    //calcolaTotTabelle();
                    calcolaTotali();
                    $(this).dialog("close");
                },
                "class" : "btn btn-primary btn-xs"
            },
            {
                text: "Annulla",
                click:function() {
                    $(this).dialog("close");
                },
                "class" : "btn btn-xs"
            }
        ],

        close : function() {
            allFields.not('.dont-clear').val("").removeClass("ui-state-error");
        }
    });
    $("#add-CTC").button().click(function() {
        elementToForm(docObj.elements.budgetStudio,'dialog-form-CTC');
        $("#dialog-form-CTC").dialog("open");
    });*/

    /*$("#dialog-form-n-pat").dialog({
        autoOpen : false,
        height : 400,
        width : 450,
        modal : true,

        position: { my: "center", at: "center top", of: document.getElementById('centerElement') },
        buttons:[
            {
                text:"Applica",
                click:  function() {
                    var totPat=pazienti;
                    var bracciTotPat=0;
                    var previsti='';
                    if((!totPat || isNaN(totPat)) && totPat!==0   && totPat!=='0'){
                        alert('Inserire totale numero di pazienti previsti');
                        return;
                    }
                    var bracciEnabled=false;
                    $(this).find('[name=Braccio_NumeroPazienti]').each(function(){
                        var bracciEnabled=true;
                        if(!isNaN(parseInt(this.value))){
                            bracciTotPat+=parseInt(this.value);
                        }
                    });
                    if(bracciEnabled && bracciTotPat!=totPat){
                        alert('Inserire numero di pazienti previsti per braccio congruo con i pazienti totali');
                        return;
                    }

                    formToElement('dialog-form-n-pat',docObj.elements.budgetStudio,folderBudgetStudio);
                    $.each(docObj.elements.bracci, function(i,braccio){
                        braccio=formToElement('braccioPatients'+i,braccio,folderBracci);
                        //previsti+=getDato(braccio.metadata['Base_Nome'])+' ('+getDato(braccio.metadata['Braccio_NumeroPazienti'])+') ';
                    });
                    if(previsti){
                        previsti=' ['+previsti+']';
                    }
                    var totali=calcolaTotali();
                    pazienti=getDato(docObj.elements.budgetStudio.metadata['BudgetCTC_NumeroPazienti']);

                    $('#show-n-pat').html(pazienti);
                    $(this).dialog("close");
                },
                "class" : "btn btn-primary btn-xs"
            },
            {
                text: "Annulla",
                click:function() {
                    $(this).dialog("close");
                },
                "class" : "btn btn-xs"
            }
        ],

        open:function(){
            //var width=$(window).width()/100*80;
            var height=$(window).height()/100*80;
            $(this).dialog('option',{height:height});

        },
        close : function() {
            allFields.not('.dont-clear').val("").removeClass("ui-state-error");
        }
    });
    $("#add-n-pat").button().click(function() {
        elementToForm(docObj.elements.budgetStudio,'dialog-form-n-pat');
        $.each(docObj.elements.bracci, function(i,braccio){
            $('#braccioPatients'+i).find('input').not('.dont-clear').val('');
            elementToForm(braccio,'braccioPatients'+i);
        });
        $("#dialog-form-n-pat").dialog("open");
    });*/

    /*$("#dialog-form-target").dialog({
        autoOpen : false,
        height : 400,
        width : 450,
        modal : true,
        position: { my: "center", at: "center top", of: document.getElementById('centerElement') },
        buttons:[
            {
                text:"Aggiungi proposta sponsor",
                click:  function() {
                    applyTargetForm();
                    calcolaTotali();
                    $(this).dialog("close");

                },
                "class" : "btn btn-primary btn-xs"
            },
            {
                text: "Annulla",
                click:function() {
                    $(this).dialog("close");
                },
                "class" : "btn btn-xs"
            }
        ],

        open:function(){
            var width=$(window).width()/100*80;
            var height=$(window).height()/100*80;
            //$(this).dialog('option',{width:width,height:height});
            prepareTargetForm(true);
        }

    });
    $("#create-target").button().click(function() {
        $("#dialog-form-target").dialog("open");
    });*/

    $("#clone-dialog-form").dialog({
        autoOpen : false,
        height : 400,
        width : 450,
        modal : true,
        position: { my: "center", at: "center top", of: document.getElementById('centerElement') },
        buttons:[
            {
                text:"Copia budget",
                click:  function() {

                    var data={};
                    $('#clone-dialog-form').find(':input').not('[name=clone_id]').each(function (){
                        data[$(this).attr('name')]=$(this).val();
                    });
                    cloneObj($('#clone_id').val(),data);
                    $(this).dialog("close");
                },
                "class" : "btn btn-primary btn-xs"
            },
            {
                text: "Annulla",
                click:function() {
                    $(this).dialog("close");
                },
                "class" : "btn btn-xs"
            }
        ],

        open:function(){
            var width=$(window).width()/100*80;
            var height=$(window).height()/100*80;
            //$(this).dialog('option',{width:width,height:height});
            prepareTargetForm(true);
        }

    });

    $("#clone3-dialog-form").dialog({
        autoOpen : false,
        height : 400,
        width : 450,
        modal : true,
        position: { my: "center", at: "center top", of: document.getElementById('centerElement') },
        buttons:[
            {
                text:"Copia budget in altro centro",
                click:  function() {

                    var data={};
                    $('#clone3-dialog-form').find(':input').not('[name=clone_id]').each(function (){
                        data[$(this).attr('name')]=$(this).val();
                    });
                    var idStudio=$("#inCentro").val();
                    cloneObjOtherStudy($('#clone_id3').val(),data,true,idStudio);
                    $(this).dialog("close");
                    $("#inCentro option").remove();

                },
                "class" : "btn btn-primary btn-xs"
            },
            {
                text: "Annulla",
                click:function() {
                    $(this).dialog("close");
                    $("#inCentro option").remove();
                },
                "class" : "btn btn-xs"
            }
        ],

        open:function(){
            var width=$(window).width()/100*40;
            var height=$(window).height()/100*80;
            $(this).dialog('option',{width:width,height:height});

            var actionUrl="../../rest/elk/query/jqgrid/full/centro";
            var data="filter=%7Bmatch_all%3A%7B%7D%7D&rows=2000&page=1";
            $.ajax({
                type: "POST",
                url: actionUrl,
                dataType : "json",
                data:data,
                success: function(obj){
                    if (obj.root!==undefined) {
                        $.each(obj.root,function(i,centro){
                            $("#inCentro").append('<option value='+centro.id+'>'+centro.parent.title+' ('+centro.title+')</option>');
                        });
                    }
                },
                error: function(){
                    loadingScreen("Errore nel caricamento dei centri!", baseUrl+"/int/images/alerta.gif", 3000);
                }
            });




            prepareTargetForm(true);
        }

    });

    $("#clone2-dialog-form").dialog({
        autoOpen : false,
        height : 400,
        width : 450,
        modal : true,
        position: { my: "center", at: "center top", of: document.getElementById('centerElement') },
        buttons:[
            {
                text:"Copia budget",
                click:  function() {

                    var data={};
                    $('#clone2-dialog-form').find(':input').not('[name=clone_id]').each(function (){
                        data[$(this).attr('name')]=$(this).val();
                    });
                    cloneObj($('#clone_id2').val(),data,true);
                    $(this).dialog("close");

                },
                "class" : "btn btn-primary btn-xs"
            },
            {
                text: "Annulla",
                click:function() {
                    $(this).dialog("close");
                },
                "class" : "btn btn-xs"
            }
        ],

        open:function(){
            var width=$(window).width()/100*80;
            var height=$(window).height()/100*80;
            //$(this).dialog('option',{width:width,height:height});
            prepareTargetForm(true);
        }

    });

    $("#newbudget-dialog-form").dialog({
        autoOpen : false,
        height : 400,
        width : 450,
        modal : true,
        position: { my: "center", at: "center top", of: document.getElementById('centerElement') },
        buttons:[
            {
                text:"Aggiungi nuovo",
                click:  function() {
                    if(!$('#Budget_Versione3').val()){
                        alert('Attenzione. Inserire una versione per il nuovo budget.');
                        return;
                    }
                    if(!$('#BudgetCTC_Tipologia').val()){
                        alert('Attenzione. Inserire una tipologia per il nuovo budget.');
                        return;
                    }
                    var data={};
                    $('#newbudget-dialog-form').find(':input').each(function (){
                        data[$(this).attr('name')]=$(this).val();
                    });
                    newBudgetStudio('newbudget-dialog-form');

                },
                "class" : "btn btn-primary btn-xs"
            },
            {
                text: "Annulla",
                click:function() {
                    $(this).dialog("close");
                },
                "class" : "btn btn-xs"
            }
        ],

        open:function(){
            var width=$(window).width()/100*80;
            var height=$(window).height()/100*80;
            //$(this).dialog('option',{width:width,height:height});
            prepareTargetForm(true);
        }

    });



});


function inviaServizi(id){
    var data={};
    $('#clone2-dialog-form').find(':input').not('[name=clone_id]').each(function (){
        data[$(this).attr('name')]="";
    });
    data["ApprovazioneClinica_InviaServizi"]="1";
    cloneObj(id,data,true);
}

function checkTP(){
    var ok=true;
    $.each(docObj.elements.tpxp,function(i,myElement){
        if($.isPlainObject(myElement)){
            var valoreTP=getDato(myElement.metadata['Costo_TransferPrice']);
            var valoreRimb=getDato(myElement.metadata['Rimborso_Rimborsabilita']);
            if(!valoreTP && valoreRimb!="2"){
                ok=false;
            }
        }

    });
    if(!ok){
        //notifySingle('checkTP','Attenzione, completare la flowchart con tutti i valori economici','warning','icon-warning-sign');
    }else{
        clearSingleNotification('checkTP');
    }
}
//$('#applicaSSN').click(applicaSSN);
//setInterval(checkTP,1500);

