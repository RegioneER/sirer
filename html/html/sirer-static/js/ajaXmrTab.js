

function sleep(milliseconds) {
    var start = new Date().getTime();
    for (var i = 0; i < 1e7; i++) {
        if ((new Date().getTime() - start) > milliseconds){
            break;
        }
    }
}

/*function loadingScreen(msg, img, timeout){
    $('body').addClass("loading");
    $('#modalMessage').html(msg);
    $('#modalImg').attr("src",img);
    if (timeout>0){
        setTimeout("toggleLoadingScreen()",timeout);
    }
}

function toggleLoadingScreen(){
    $('body').removeClass('loading');
}*/



function ajaXmrTab(options){

    this.elementName=options.elementName;
    this.baseUrl=options.baseUrl;
    this.saveOrUpdateUrl=options.saveOrUpdateUrl;
    this.listRow=options.listRow;
    this.listRowAppend=options.listRowAppend;
    this.getAllUrl=options.getAllUrl;
    this.getSingleElementUrl=options.getSingleElementUrl;
    this.deleteUrl=options.deleteUrl;
    this.postPopulateFunction = options.postPopulateFunction;
    this.postRefresh=options.postRefresh;
    this.dialogWidth=options.dialogWidth;
    this.dialogHeight=options.dialogHeight;
    this.postSave=options.postSave;
    this.editPage=options.editPage;
    this.listType=options.listType;
    this.cleaner=options.cleaner;
    this.postClearForm=options.postClearForm;




    this.init = function(){
        var currObj=this;
        var width=450;
        var height=450;
        if (this.listType==null) listType="br";
        if (this.dialogWidth!=null) width=this.dialogWidth;
        if (this.dialogHeight!=null) height=this.dialogHeight;
        /*
        $( "#"+this.elementName+"-dialog" ).dialog({
            autoOpen: false,
            height: height,
            width: width,
            modal: true,
            buttons: {
                Cancel: function() {
                    $( this ).dialog( "close" );
                }
            },
            close: function() {
            }
        });
        */
        $('#'+this.elementName+'-form-submit').click(function(){
            loadingScreen("Salvataggio in corso...", currObj.baseUrl+"/int/images/loading.gif");
            var formData=new FormData($('#'+currObj.elementName+'-form')[0]);
            $.ajax({
                type: "POST",
                url: currObj.saveOrUpdateUrl,
                contentType:false,
                processData:false,
                async:false,
                cache:false,
                data: formData,
                success: function(obj){
                    if (obj.result=="OK") {
                        loadingScreen("Salvataggio effettuato", currObj.baseUrl+"/int/images/green_check.jpg",2000);
                        $( "#"+currObj.elementName+"-dialog" ).modal( "hide" );

                    }else {
                        loadingScreen("Errore salvataggio!", currObj.baseUrl+"/int/images/alerta.gif", 3000);
                        $( "#"+currObj.elementName+"-dialog" ).modal( "hide" );
                    }
                    currObj.refreshList();
                },
                error: function(){
                    loadingScreen("Errore salvataggio!", currObj.baseUrl+"/int/images/alerta.gif", 3000);
                    $( "#"+currObj.elementName+"-dialog" ).modal( "hide" );
                }
            });
            if (currObj.postSave!=null) currObj.postSave();
        });
        $('#add-'+this.elementName).click(function(){
            currObj.clearFormFields();
            if (currObj.postClearForm!=null) currObj.postClearForm();
            $( "#"+currObj.elementName+"-dialog" ).modal();
        });
    }
    this.get=function(id, callback){
        var currObj=this;
        $.getJSON(currObj.getSingleElementUrl+"/"+id, function(data){
            callback(data);
        });

    }
    this.appendDeleteIcon=function(id, container){
        var currObj=this;
        if (currObj.deleteUrl!=null)
            $(container).append('<a href="#" class="'+currObj.elementName+'-delete" style="display: inline-block" title="elimina" data-id="'+id+'"><i class="icon icon-trash"></i> </a>');
        $('.'+currObj.elementName+'-delete').unbind("click");
        $('.'+currObj.elementName+'-delete').click(function(){
            if (confirm("Sei sicuro")){
                loadingScreen("Eliminazione in corso...", currObj.baseUrl+"/int/images/loading.gif");
                $.ajax({
                    type: "GET",
                    url: currObj.deleteUrl+'/'+$(this).attr('data-id'),
                    success: function(obj){
                        if (obj.result=="OK") {
                            loadingScreen("Eliminazione effettuata!", currObj.baseUrl+"/int/images/green_check.jpg",2000);
                            if (currObj.postSave!=null)  currObj.postSave();
                            currObj.refreshList();
                        } else {
                            loadingScreen("Errore salvataggio!", currObj.baseUrl+"/int/images/alerta.gif", 3000);
                        }
                    }
                });
            }
            return false;
        });

    }

    this.appendEditIcon=function(id, container){
        var currObj=this;
        if (currObj.getSingleElementUrl!=null) $(container).append('<a href="#" class="'+currObj.elementName+'-edit" style="display: inline-block" title="modifica" data-id="'+id+'"><i class="icon icon-pencil"></i> </a>');
        $('.'+currObj.elementName+'-edit').click(function(){
            if (currObj.editPage!=null && currObj.editPage!="") {
                window.location.href=currObj.editPage+'/'+$(this).attr('data-id');
                return;
            }
            $.getJSON(currObj.getSingleElementUrl+'/'+$(this).attr('data-id'), function(data) {
                currObj.populateFormFromJson(data);
                if (currObj.postPopulateFunction!=null)  currObj.postPopulateFunction(data);
            });
            return false;
        });
    }

    this.refreshList=function(){
        var currObj=this;
        if (currObj.cleaner!=null) currObj.cleaner();
        $('#'+currObj.elementName+'-list-availables').html("<img src='"+currObj.baseUrl+"/int/images/loading.gif'/>");
        $('.'+currObj.elementName+'-edit').unbind("click");
        $('.'+currObj.elementName+'-delete').unbind("click");
        var list="";
        $.getJSON(currObj.getAllUrl, function(data) {
            var items = [];

            for (i=0;i<data.length;i++){
                if (currObj.listType=='li') list+="<li>";
                if (currObj.listType=='tr') list+="<tr>";
                list+=currObj.listRow(data[i]);
                if ((currObj.getSingleElementUrl!=null || currObj.deleteUrl!=null) && currObj.listType=='tr') list+="<td>";
                if (currObj.getSingleElementUrl!=null) list+='<a href="#" class="'+currObj.elementName+'-edit" style="display: inline-block" title="modifica" data-id="'+data[i].id+'"><i class="icon icon-pencil"></i> </a> ';
                if (currObj.deleteUrl!=null)list+='<a href="#" class="'+currObj.elementName+'-delete" style="display: inline-block" title="elimina" data-id="'+data[i].id+'"><i class="icon icon-trash"></i> </a>';
                if ((currObj.getSingleElementUrl!=null || currObj.deleteUrl!=null) && currObj.listType=='tr') list+="</td>";
                if (currObj.listType=='li') list+="</li>";
                if (currObj.listType=='tr') list+="</tr>";
                if (currObj.listType=='br') list+='<br/>';
                if (currObj.listRowAppend!=null)  list+=currObj.listRowAppend(data[i]);
            }
            $('#'+currObj.elementName+'-list-availables').html(list);
            if (currObj.getSingleElementUrl!=null)
                $('.'+currObj.elementName+'-edit').click(function(){
                    if (currObj.editPage!=null && currObj.editPage!="") {
                        window.location.href=currObj.editPage+'/'+$(this).attr('data-id');
                        return;
                    }
                    $.getJSON(currObj.getSingleElementUrl+'/'+$(this).attr('data-id'), function(data) {
                        currObj.populateFormFromJson(data);
                        if (currObj.postPopulateFunction!=null)  currObj.postPopulateFunction(data);
                    });
                    return false;
                });

            if (currObj.deleteUrl!=null)
            $('.'+currObj.elementName+'-delete').click(function(){
                if (confirm("Sei sicuro")){
                    loadingScreen("Eliminazione in corso...", currObj.baseUrl+"/int/images/loading.gif");
                    $.ajax({
                        type: "GET",
                        url: currObj.deleteUrl+'/'+$(this).attr('data-id'),
                        success: function(obj){
                            if (obj.result=="OK") {
                                loadingScreen("Eliminazione effettuata!", currObj.baseUrl+"/int/images/green_check.jpg",2000);
                                if (currObj.postSave!=null)  currObj.postSave();
                                currObj.refreshList();
                            } else {
                                loadingScreen("Errore salvataggio!", currObj.baseUrl+"/int/images/alerta.gif", 3000);
                            }
                        }
                });
                }
                return false;
            });


            if (currObj.postRefresh!=null) currObj.postRefresh();
        });

    };

    this.populateFormFromJson=function(json){
        var currObj=this;
        var baseUrl=this.baseUrl;
        this.clearFormFields();
        $('#'+currObj.elementName+'-form :input').each(function(){
            for (var key in json) {
            	
                if ($(this).attr('name')==key){
                    if($(this).attr('type')=='checkbox'){
                        this.checked=json[key];
                    }
                    else if(this.type.match(/select/)){
                		$(this).select2("val",json[key]);
                	}
                    else{
                    	$(this).val(json[key]);
                    }
                    if(key=='typefilters' && json.typefilters){
                        var types=json.typefilters;
                        types=types.split(',');
                        $.each(types, function(i,type){
                            $.ajax({url: baseUrl+'/app/rest/admin/type/get/'+type }).done(function(data){
                                $('#typefilters').tokenInput('add',{"id":data.id,"name":data.typeId});
                            });
                        });

                    }
                    break;
                }
            }
        });
        if (currObj.postClearForm!=null) currObj.postClearForm();
        $( "#"+currObj.elementName+"-dialog" ).modal();
    }

    this.clearFormFields=function(){
        var currObj=this;
        $('#'+currObj.elementName+'-form :input').each(function(){

            if ($(this).attr('type')=='button') return true;
            if ($(this).attr('type')=='checkbox') {
               this.checked=false;
                return true;
            }
            if ($(this).attr('isTokenInput')!=null) $(this).tokenInput('clear');
            else $(this).val('');
        });

    };

    this.init();

}