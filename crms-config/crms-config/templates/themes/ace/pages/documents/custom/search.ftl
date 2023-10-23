<style>
        
        .ui-jqgrid tr.jqgrow td {
            white-space:normal;
        }
        .ui-jqgrid .ui-jqgrid-htable th div {
            white-space:normal;
            height:auto;
            margin-bottom:3px;
        }
    
        
        .home-table .ui-jqgrid{
            margin:10px;
            
        }
        
        tr.jqgrow{
            cursor:pointer;
        }
        
        .home-table {
            float:left;
        }
        .infobox {
            cursor:pointer;
        }
        
        </style>
<div class="home-container">
        <div id="metadataTemplate-tabs" class="tabbable">
            <ul class="nav nav-tabs">
                 <li><a href="#metadataTemplate-cercaStudio" data-toggle="tab">Cerca Studio</a></li>
                 <li><a href="#metadataTemplate-cercaCentro" data-toggle="tab">Cerca Centro</a></li>
            </ul>
    
    <div class="tab-content">
        <div id="metadataTemplate-cercaStudio" class="tab-pane">
            <form id="advancedSearchForm" name="advancedSearchForm" class="form-horizontal" action="${baseUrl}/app/rest/documents/advancedSearch/Studio">
              <div class="form-group">
              <label class="col-sm-2 control-label no-padding-right" for="UniqueIdStudio_id_like">Id studio<sup>*</sup>:</label>
                <div class="col-sm-8">
                        <input type="text" name="UniqueIdStudio_id_like" id="UniqueIdStudio_id_like"/>
                </div>
              </div>
              <div class="form-group">
              <label class="col-sm-2 control-label no-padding-right" for="IDstudio_CodiceProt_eq">Codice protocollo<sup>*</sup>:</label>
                <div class="col-sm-8">
                        <input type="text" name="IDstudio_CodiceProt_eq" id="IDstudio_CodiceProt_eq"/>
                </div>
              </div>
              <div class="form-group">
              <label class="col-sm-2 control-label no-padding-right" for="IDstudio_TitoloProt_eq">Titolo studio<sup>*</sup>:</label>
                <div class="col-sm-8">
                        <input type="text" name="IDstudio_TitoloProt_eq" id="IDstudio_TitoloProt_eq"/>
                </div>
              </div>
              <div class="form-group">
                <label class="col-sm-2 control-label no-padding-right" for="datiPromotore_promotore_eq">Denominazione promotore:</label>
                <div class="col-sm-8">
                    <@script>
                        if (!fieldTypes) var fieldTypes=new Object();
                        fieldTypes["datiPromotore_promotore_eq"]="ELEMENT_LINK";
                    </@script>
                    <input type="text" id="datiPromotore_promotore_eq" class="randomClass-1" name="datiPromotore_promotore_eq"/>
                    <@script>
                        $("#datiPromotore_promotore_eq.randomClass-1").attr('isTokenInput',true);
                            $("#datiPromotore_promotore_eq.randomClass-1").tokenInput("${baseUrl}/app/rest/documents/getLinkableElements/370", {
                                queryParam: "term",
                                hintText: "Digitare almeno 2 caratteri",
                                minChars: 2,
                                searchingText: "ricerca in corso...",
                                noResultsText: "Nessun risultato",
                                tokenLimit: 1,
                                theme: 'facebook',
                                preventDuplicates: true,
                                prePopulate: [
                
                
                                ],
                                onResult: function (results) {
                                    $.each(results, function (index, value) {
                                        value.name = value.title;
                                        value.id=value.id;
                
                                    });
                
                                    return results;
                                }
                            });
                        
                    </@script>
                    </div>
                </div>
                <div class="form-group">
                <label class="col-sm-2 control-label no-padding-right" for="datiCRO_denominazione_eq">Denominazione CRO:</label>
                <div class="col-sm-8">
                    <@script>
                        if (!fieldTypes) var fieldTypes=new Object();
                        fieldTypes["datiCRO_denominazione_eq"]="ELEMENT_LINK";
                    </@script>
                    <input type="text" id="datiCRO_denominazione_eq" class="randomClass-1" name="datiCRO_denominazione_eq"/>
                    <@script>
                        $("#datiCRO_denominazione_eq.randomClass-1").attr('isTokenInput',true);
                            $("#datiCRO_denominazione_eq.randomClass-1").tokenInput("${baseUrl}/app/rest/documents/getLinkableElements/183", {
                                queryParam: "term",
                                hintText: "Digitare almeno 2 caratteri",
                                minChars: 2,
                                searchingText: "ricerca in corso...",
                                noResultsText: "Nessun risultato",
                                tokenLimit: 1,
                                theme: 'facebook',
                                preventDuplicates: true,
                                prePopulate: [
                
                
                                ],
                                onResult: function (results) {
                                    $.each(results, function (index, value) {
                                        value.name = value.title;
                                        value.id=value.id;
                
                                    });
                
                                    return results;
                                }
                
                            });
            
                    </@script>
                  </div>
                </div>
                <div class="form-group">
                <label class="col-sm-2 control-label no-padding-right" for="datiStudio_AreaTematicaPrincipale_eq">Area Tematica principale:</label>
                <div class="col-sm-8">
                    <select  id="datiStudio_AreaTematicaPrincipale_eq" class="randomClass-11" name="datiStudio_AreaTematicaPrincipale_eq">
                        <option></option>
                        <option value="1">Apparato muscolo-scheletrico</option>
                        <option value="2">Apparato respiratorio</option>
                        <option value="3">Cardiovascolare</option>
                        <option value="4">Cavo orale a apparato digerente</option>
                        <option value="5">Cerebrovascolare</option>
                        <option value="6">Cute e derma</option>
                        <option value="7">Disturbi congeniti</option>
                        <option value="8">Ematologia (escluso tumori)</option>
                        <option value="9">Incidenti e traumi</option>
                        <option value="10">Infezioni</option>
                        <option value="11">Infiammazione e sistema immunitario</option>
                        <option value="12">Metabolismo e sistema endocrino</option>
                        <option value="13">Neurologia</option>
                        <option value="14">Occhio</option>
                        <option value="15">Orecchio</option>
                        <option value="16">Reni e apparato urogenitale</option>
                        <option value="17">Salute della riproduzione e gravidanza</option>
                        <option value="18">Salute mentale</option>
                        <option value="19">Tumori, inclusi tumori del sangue</option>
                        <option value="20">Aspetti generali relativi alla salute ed il benessere</option>
                        <option value="21">Altro</option>
                    </select>
                    <@script>
                    $("#datiStudio_AreaTematicaPrincipale_eq").select2({containerCssClass:'select2-ace',allowClear: true})
                </@script>
                </div>
                </div>
                <div class="form-group">
                <label class="col-sm-2 control-label no-padding-right" for="datiStudio_tipoStudio_eq">Tipologia studio:</label>
                <div class="col-sm-8">
                <select id="datiStudio_tipoStudio_eq" name="datiStudio_tipoStudio_eq">
                    <option></option>
                    <option value="1">Sperimentale con farmaco</option>
                    <option value="2">Indagine clinica con Dispositivo pre-marketing</option>
                    <option value="3">Indagine clinica con Dispositivo post-marketing</option>
                    <option value="4">Studio interventistico (senza dispositivi e senza farmaci)</option>
                    <option value="5">Osservazionale</option>
                    <option value="6">Studio esclusivamente su materiali biologici</option>
                </select>
                <@script>
                    $("#datiStudio_tipoStudio_eq").select2({containerCssClass:'select2-ace',allowClear: true})
                    $("#datiStudio_tipoStudio_eq").bind("change",function(){
                        if($(this).val()=="1"){
                             $("#eudractContainer").show();
                        }
                        else{
                             $("#eudractContainer").hide();
                        }
                    });
                </@script>
                </div>
                </div>
                <div class="form-group" id="eudractContainer">
                    <label class="col-sm-2 control-label no-padding-right" for="datiStudio_eudractNumber_eq">EudraCT Number:</label>
                    <div class="col-sm-8">
                            <input type="text" name="datiStudio_eudractNumber_eq" id="datiStudio_eudractNumber_eq"/>
                    </div>
                </div>
                <@script>
                $("#eudractContainer").hide();
                </@script>
                <div class="form-group">
                    <label class="col-sm-2 control-label no-padding-right"  for="obj_creationDt_gteq">Registrato:</label>
                    <div class="col-sm-8">
                        <div class="input-group">
                            <span class="input-group-addon">
                                <i class="icon-calendar bigger-110"></i>
                            </span>
                            <input class="form-control" type="text" name="date-range-picker" id="id-date-range-picker-1" />
                        </div>
                    </div>
                </div>
                <input type="hidden" name="obj_creationDt_gteq" id="obj_creationDt_gteq"/>
                <input id="obj_creationDt_lteq" type="hidden" name="obj_creationDt_lteq">
                <!--
                    <input type="text" class="datePicker" name="obj_creationDt_gteq" id="obj_creationDt_gteq"/>
                    <input type="text" class="datePicker" name="obj_creationDt_lteq" id="obj_creationDt_lteq"/>
                -->
                <div class="form-group">
                <div class="col-sm-2">&nbsp;</div>
                <div class="col-sm-8">
                <button id="button-search" class="btn btn-purple btn-sm" type="submit">
                    <span id="std-label"><i class="icon-search"></i> Avvia la ricerca</span>
                    <span id="searching-label" style="display:none"><i class="icon-spinner icon-spin"></i> ricerca in corso...</span>
                </button>
                </div>
                
            <br/><br/>
            <sup>*</sup> E' possibile ricercare anche per chiave parziale
            <br/><br/>
            
            <!--div class="table-header"> Risultati ricerca </div>
            <div class="table-responsive">
            <table class="table table-striped table-bordered table-hover">
            <thead>
                <tr>
                    <th>Id</th>
                    <th>Codice</th>
                    <th>Titolo</th>
                    <th>Promotore</th>
                    <th>Data Creazione</th>
                    <th>Data Ultima modifica</th>
                </tr>
            </thead>
            <tbody id="studi-list">
            </tbody>
            </table>
            </div-->
            </form>
            <span class="studi-list-table" >
                <table id="studi-list-grid-table" class="grid-table" ></table>
                <div id="studi-list-grid-pager"></div>
            </span>
        </div>
    </div>
    <div id="metadataTemplate-cercaCentro" class="tab-pane">
            <form id="advancedSearchFormCentro" name="advancedSearchFormCentro" class="form-horizontal" action="${baseUrl}/app/rest/documents/advancedSearch/Centro">
                <div class="form-group">
                    <label class="col-sm-3 control-label no-padding-right" for="IstruttoriaCE_DelibNum_eq">Codice studio/protocollo assegnato dal CE:<sup>*</sup>:</label>
                    <div class="col-sm-7">
                        <input type="text" name="IstruttoriaCE_DelibNum_eq" id="IstruttoriaCE_DelibNum_eq"/>
                    </div>
                </div>

                <div class="form-group">
                <label class="col-sm-3 control-label no-padding-right" for="IdCentro_Struttura_eq">Azienda sede dello studio:</label>
                <div class="col-sm-7">
                    <@script>
                        if (!fieldTypes) var fieldTypes=new Object();
                        fieldTypes["IdCentro_Struttura_eq"]="EXT_DICTIONARY";
                        var IdCentro_Struttura_addFilters="L=1";
                        if (!dependency) var dependency=new Object();
                    </@script>
                    <select id="IdCentro_Struttura_eq" name="IdCentro_Struttura_eq" tabindex="-1" >
                    </select>
                    <@script>
                       $('#IdCentro_Struttura_eq').select2({containerCssClass:'select2-ace',allowClear: true});
                       if (IdCentro_Struttura_addFilters && IdCentro_Struttura_addFilters!=""){
                            console.log(IdCentro_Struttura_addFilters);
                            filters=IdCentro_Struttura_addFilters.split(",");
                            console.log(filters);
                            var addedParam="";
                            for (l=0;l<filters.length;l++){
                                secondSplit=filters[l].split("=");
                                console.log(secondSplit);
                                var re = new RegExp("^\\[(.*)\\]$");
                                if (secondSplit[1].match(re)) {
                                    idField=secondSplit[1].replace("\[","");
                                    idField=idField.replace("\]","");
                                    if (!dependency[idField]) dependency[idField]=new Array();
                                    dependency[idField][dependency[idField].length]='IdCentro_Struttura_eq';
                                }
                            }
                        }
                        
                    
                    
                        $('#IdCentro_Struttura_eq').change(function(){
                            if ($(this).val().indexOf('-9999###')==0){
                                $('#IdCentro_Struttura-altro').show();
                                $('#IdCentro_Struttura-altro').focus();
                            }else {
                                $('#IdCentro_Struttura-altro').hide();  
                                $('#IdCentro_Struttura_eq').val($('#IdCentro_Struttura_eq').val());
                            }
                            if (dependency['IdCentro_Struttura_eq'])
                                for(var index in dependency['IdCentro_Struttura_eq']) {
                                  setTimeout('populateSelect_'+dependency['IdCentro_Struttura_eq'][index]+'()',50);
                                }   
                        });
                        populateSelect_IdCentro_Struttura();
                
                    
                        function buildScriptUrl_IdCentro_Struttura(){
                            var addedParam="";
                            if (IdCentro_Struttura_addFilters && IdCentro_Struttura_addFilters!=""){
                            filters=IdCentro_Struttura_addFilters.split(",");
                            
                            for (l=0;l<filters.length;l++){
                                secondSplit=filters[l].split("=");
                                var re = new RegExp("^\\[(.*)\\]$");
                                if (secondSplit[1].match(re)) {
                                    idField=secondSplit[1].replace("\[","");
                                    idField=idField.replace("\]","");
                                    if (addedParam!="") addedParam+="&";
                                    if (!valueOfField(idField)) return "";
                                    addedParam+=secondSplit[0]+"="+encodeURIComponent(valueOfField(idField));
                                }else {
                                    addedParam+=secondSplit[0]+"="+encodeURIComponent(secondSplit[1]);
                                }
                                addedParam+="&";
                            }
                            }
                            console.log("QUI buildScriptUrl_IdCentro_Struttura "+addedParam);
                            return '/IdCentroStudioSfoglia.php?'+addedParam;
                        }
                    
                        function populateSelect_IdCentro_Struttura(){
                            $('#IdCentro_Struttura_eq').select2("val", "");
                            $('#IdCentro_Struttura_eq').html("");
                            $('#IdCentro_Struttura_eq').append("<option></option>");
                            
                            var url=buildScriptUrl_IdCentro_Struttura();
                            var valorizza=function(){
                                console.log('niente da valorizzare');
                                return false;
                            };
                            if (url!=""){
                            $.getJSON(url,function(result){
                
                               $.each(result, function(i, field){
                                 var val=field.id;//+"###"+field.title;  
                                 var code=field.id+"###";
                                 var selected="";
                                 var decode="";
                                
                                if (selected!="") {
                                    
                                    $('#IdCentro_Struttura_eq').val(val);
                                    if (val.indexOf('-9999###')==0) {
                                        $('#IdCentro_Struttura_eq').select2("val",altroValue);
                                        $('#IdCentro_Struttura-altro').show();
                                        $('#IdCentro_Struttura-altro').val(decode);
                                    }
                                }
                                if(val.indexOf('-9999###')){
                                    var altroValue=$('#IdCentro_Struttura_eq option[value^=-9999###]').val();
                                    $('#IdCentro_Struttura_eq').select2("val",altroValue);
                                }
                                
                                $('#IdCentro_Struttura_eq').append("<option value=\""+val+"\" "+selected+">"+field.title+"</option>");
                                if(result.length==1){
                                    $('#IdCentro_Struttura_eq').select2("val",val);
                                } 
                               });
                               valorizza();    
                               if (dependency['IdCentro_Struttura_eq'])
                                for(var index in dependency['IdCentro_Struttura_eq']) {
                                  setTimeout('populateSelect_'+dependency['IdCentro_Struttura_eq'][index]+'()',50);
                                }
                                
                              });      
                            }
                        } 
                    </@script>
                 </div>
                </div>
                
                <div class="form-group">
                <label class="col-sm-3 control-label no-padding-right" for="IdCentro_UO_eq">Unit&agrave; Operativa</label>
                <div class="col-sm-7">
                    <@script>
                        if (!fieldTypes) var fieldTypes=new Object();
                        fieldTypes["IdCentro_Struttura"]="EXT_DICTIONARY";
                        
                        var IdCentro_UO_addFilters="L=4,L1=[IdCentro_Struttura_eq]";
                        if (!dependency) var dependency=new Object();
                    </@script>
                    <select id="IdCentro_UO_eq" name="IdCentro_UO_eq" tabindex="-1" >
                    </select>
                    <@script>
                       $('#IdCentro_UO_eq').select2({containerCssClass:'select2-ace',allowClear: true});
                       if (IdCentro_UO_addFilters && IdCentro_UO_addFilters!=""){
                            console.log(IdCentro_UO_addFilters);
                            filters=IdCentro_UO_addFilters.split(",");
                            console.log(filters);
                            var addedParam="";
                            for (l=0;l<filters.length;l++){
                                secondSplit=filters[l].split("=");
                                console.log(secondSplit);
                                var re = new RegExp("^\\[(.*)\\]$");
                                if (secondSplit[1].match(re)) {
                                    idField=secondSplit[1].replace("\[","");
                                    idField=idField.replace("\]","");
                                    if (!dependency[idField]) dependency[idField]=new Array();
                                    dependency[idField][dependency[idField].length]='IdCentro_UO_eq';
                                }
                            }
                        }
                        
                        $('#IdCentro_UO-altro').change(function(){
                            if ($('#IdCentro_UO_eq').val().indexOf('-9999###')==0){
                                $('#IdCentro_UO_eq').val('-9999###'+$('#IdCentro_UO-altro').val());    
                            }
                        });
                        
                        
                        $('#IdCentro_UO_eq').change(function(){
                            if ($(this).val().indexOf('-9999###')==0){
                                $('#IdCentro_UO-altro').show();
                                $('#IdCentro_UO-altro').focus();
                            }else {
                                $('#IdCentro_UO-altro').hide(); 
                                $('#IdCentro_UO_eq').val($('#IdCentro_UO_eq').val());
                            }
                            if (dependency['IdCentro_UO_eq'])
                                for(var index in dependency['IdCentro_UO_eq']) {
                                  setTimeout('populateSelect_'+dependency['IdCentro_UO_eq'][index]+'()',50);
                                }   
                        });
                        populateSelect_IdCentro_UO_eq();
                    
                        
                        function buildScriptUrl_IdCentro_UO(){
                            var addedParam="";
                            if (IdCentro_UO_addFilters && IdCentro_UO_addFilters!=""){
                            filters=IdCentro_UO_addFilters.split(",");
                            
                            for (l=0;l<filters.length;l++){
                                secondSplit=filters[l].split("=");
                                var re = new RegExp("^\\[(.*)\\]$");
                                if (secondSplit[1].match(re)) {
                                    idField=secondSplit[1].replace("\[","");
                                    idField=idField.replace("\]","");
                                    if (addedParam!="") addedParam+="&";
                                    if (!valueOfField(idField)) return "";
                                    addedParam+=secondSplit[0]+"="+encodeURIComponent(valueOfField(idField));
                                }else {
                                    addedParam+=secondSplit[0]+"="+encodeURIComponent(secondSplit[1]);
                                }
                                addedParam+="&";
                            }
                            }
                            console.log("QUI buildScriptUrl_IdCentro_UO"+addedParam);
                            return '/IdCentroStudioSfoglia.php?'+addedParam;
                        }
                        
                        function populateSelect_IdCentro_UO_eq(){
                            $('#IdCentro_UO_eq').select2("val", "");
                            $('#IdCentro_UO_eq').html("");
                            $('#IdCentro_UO_eq').append("<option></option>");
                            
                            var url=buildScriptUrl_IdCentro_UO();
                            var valorizza=function(){
                                console.log('niente da valorizzare');
                                return false;
                            };
                            if (url!=""){
                            $.getJSON(url,function(result){
                
                               $.each(result, function(i, field){
                                 var val=field.id;//+"###"+field.title;  
                                 var code=field.id+"###";
                                 var selected="";
                                 var decode="";
                
                                if (selected!="") {
                                    
                                    $('#IdCentro_UO_eq').val(val);
                                    if (val.indexOf('-9999###')==0) {
                                        $('#IdCentro_UO_eq').select2("val",altroValue);
                                        $('#IdCentro_UO-altro').show();
                                        $('#IdCentro_UO-altro').val(decode);
                                    }
                                }
                                if(val.indexOf('-9999###')){
                                    var altroValue=$('#IdCentro_UO_eq option[value^=-9999###]').val();
                                    $('#IdCentro_UO_eq').select2("val",altroValue);
                                }
                                
                                $('#IdCentro_UO_eq').append("<option value=\""+val+"\" "+selected+">"+field.title+"</option>");
                                    
                               });
                               valorizza();    
                               if (dependency['IdCentro_UO_eq'])
                                for(var index in dependency['IdCentro_UO_eq']) {
                                  setTimeout('populateSelect_'+dependency['IdCentro_UO_eq'][index]+'()',50);
                                }
                                
                              });       
                            }
                        }
                    </@script>
                 </div>
                </div>
                
                <div class="form-group">
                <label class="col-sm-3 control-label no-padding-right" for="IdCentro_UO_eq">Principal investigator:</label>
                <div class="col-sm-7">
                    <@script>
                        if (!fieldTypes) var fieldTypes=new Object();
                        fieldTypes["IdCentro_PI_eq"]="EXT_DICTIONARY"; 
                       
                        var IdCentro_PI_addFilters="L1=[IdCentro_Struttura_eq]";

                        if (!dependency) var dependency=new Object();
                    </@script>
                    <input id="IdCentro_PI_eq" name="IdCentro_PI_eq" tabindex="-1" />
                    
                    <@script>
                        $('#IdCentro_PI_eq').select2({
                            containerCssClass:'select2-ace',allowClear: true,
                            placeholder:"Selezionare il Principal Investigator",
                            minimumInputLength: 1,
                            formatInputTooShort: function () {
                                        return "Iniziare a scrivere il nome del Principal Investigator";
                                },
                            ajax:{
                                    url:buildScriptUrl_IdCentro_PI,
                                    dataType:'json',
                                    data: function(term,page){return {term:term}},
                                    //results:function(data,page){return {results:data};}
                                    results: function (data, page) { 
                                        return {
                                            results: $.map(data, function (item) {
                                                var my_id=item.id.replace(/###.*$/,"");
                                                var my_text=item.title;
                                                return {
                                               id: my_id,
                                               text: my_text
                                                };
                                            })
                                        };
                                    }
                                }
                        });
                       if (IdCentro_PI_addFilters && IdCentro_PI_addFilters!=""){
                            <#-- console.log(IdCentro_PI_addFilters); -->
                            filters=IdCentro_PI_addFilters.split(",");
                            <#-- console.log(filters); -->
                            var addedParam="";
                            for (l=0;l<filters.length;l++){
                                secondSplit=filters[l].split("=");
                                <#-- console.log(secondSplit); -->
                                var re = new RegExp("^\\[(.*)\\]$");
                                if (secondSplit[1].match(re)) {
                                    idField=secondSplit[1].replace("\[","");
                                    idField=idField.replace("\]","");
                                    if (!dependency[idField]) dependency[idField]=new Array();
                                    dependency[idField][dependency[idField].length]='IdCentro_PI_eq';
                                }
                            }
                        }
                        
                        $('#IdCentro_PI-altro').change(function(){
                            if ($('#IdCentro_PI_eq').val().indexOf('-9999###')==0){
                                $('#IdCentro_PI_eq').val('-9999###'+$('#IdCentro_PI-altro').val());    
                            }
                        });
                        
                        
                        $('#IdCentro_PI_eq').change(function(){
                            if ($(this).val().indexOf('-9999###')==0){
                                $('#IdCentro_PI-altro').show();
                                $('#IdCentro_PI-altro').focus();
                            }else {
                                $('#IdCentro_PI-altro').hide(); 
                                $('#IdCentro_PI_eq').val($('#IdCentro_PI_eq').val());
                            }
                            if (dependency['IdCentro_PI_eq'])
                                for(var index in dependency['IdCentro_PI_eq']) {
                                  setTimeout('populateSelect_'+dependency['IdCentro_PI_eq'][index]+'()',50);
                                }   
                        });
                        populateSelect_IdCentro_PI_eq();
                    
                        
                        function buildScriptUrl_IdCentro_PI(){
                            var addedParam="";
                            if (IdCentro_PI_addFilters && IdCentro_PI_addFilters!=""){
                            filters=IdCentro_PI_addFilters.split(",");
                            
                            for (l=0;l<filters.length;l++){
                                secondSplit=filters[l].split("=");
                                var re = new RegExp("^\\[(.*)\\]$");
                                if (secondSplit[1].match(re)) {
                                    idField=secondSplit[1].replace("\[","");
                                    idField=idField.replace("\]","");
                                    if (addedParam!="") addedParam+="&";
                                    if (!valueOfField(idField)) return "";
                                    addedParam+=secondSplit[0]+"="+encodeURIComponent(valueOfField(idField));
                                }else {
                                    addedParam+=secondSplit[0]+"="+encodeURIComponent(secondSplit[1]);
                                }
                                addedParam+="&";
                            }
                            }
                            <#-- console.log("QUI buildScriptUrl_IdCentro_PI "+addedParam); -->
                            return '/sfoglia_PI.php?'+addedParam;
                        }
                        
                        function populateSelect_IdCentro_PI_eq(){
                            $('#IdCentro_PI_eq').select2("val", "");
                            $('#IdCentro_PI_eq').html("");
                            $('#IdCentro_PI_eq').append("<option></option>");
                            
                            var url=buildScriptUrl_IdCentro_PI();
                            var valorizza=function(){
                                console.log('niente da valorizzare');
                                return false;
                            };
                            if (url!=""){
                            $.getJSON(url,function(result){
                
                               $.each(result, function(i, field){
                                 var val=field.id;//+"###"+field.title;  
                                 var code=field.id+"###";
                                 var selected="";
                                 var decode="";
                
                                if (selected!="") {
                                    
                                    $('#IdCentro_PI_eq').val(val);
                                    if (val.indexOf('-9999###')==0) {
                                        $('#IdCentro_PI_eq').select2("val",altroValue);
                                        $('#IdCentro_PI-altro').show();
                                        $('#IdCentro_PI-altro').val(decode);
                                    }
                                }
                                if(val.indexOf('-9999###')){
                                    var altroValue=$('#IdCentro_PI_eq option[value^=-9999###]').val();
                                    $('#IdCentro_PI_eq').select2("val",altroValue);
                                }
                                
                                $('#IdCentro_PI_eq').append("<option value=\""+val+"\" "+selected+">"+field.title+"</option>");
                                    
                               });
                               valorizza();    
                               if (dependency['IdCentro_PI_eq'])
                                for(var index in dependency['IdCentro_PI_eq']) {
                                  setTimeout('populateSelect_'+dependency['IdCentro_PI_eq'][index]+'()',50);
                                }
                                
                              });       
                            }
                        }  
                    </@script>
                 </div>
                </div>
                
                <div class="form-group">
                    <label class="col-sm-3 control-label no-padding-right"  for="DatiCentro_InizioDt_gteq">Data prevista di inizio studio nel centro:</label>
                    <div class="col-sm-7">
                        <div class="input-group">
                            <span class="input-group-addon">
                                <i class="icon-calendar bigger-110"></i>
                            </span>
                            <input class="form-control" type="text" name="date-range-picker-5" id="id-date-range-picker-5" />
                        </div>
                    </div>
                </div>
                <input type="hidden" name="DatiCentro_InizioDt_gteq" id="DatiCentro_InizioDt_gteq"/>
               <input type="hidden" name="mode" id="mode" value="single-with-parent"/>
                <input id="DatiCentro_InizioDt_lteq" type="hidden" name="DatiCentro_InizioDt_lteq">
                <!--
                    <input type="text" class="datePicker" name="DatiCentro_InizioDt_gteq" id="DatiCentro_InizioDt_gteq"/>
                    <input type="text" class="datePicker" name="DatiCentro_InizioDt_lteq" id="DatiCentro_InizioDt_lteq"/>
                -->
                <div class="form-group">
                    <label class="col-sm-3 control-label no-padding-right"  for="DatiCentro_FineDt_gteq">Data prevista di fine studio nel centro:</label>
                    <div class="col-sm-7">
                        <div class="input-group">
                            <span class="input-group-addon">
                                <i class="icon-calendar bigger-110"></i>
                            </span>
                            <input class="form-control" type="text" name="date-range-picker-6" id="id-date-range-picker-6" />
                        </div>
                    </div>
                </div>
                <input type="hidden" name="DatiCentro_FineDt_gteq" id="DatiCentro_FineDt_gteq"/>
                <input id="DatiCentro_FineDt_lteq" type="hidden" name="DatiCentro_FineDt_lteq">
                <!--
                    <input type="text" class="datePicker" name="DatiCentro_FineDt_gteq" id="DatiCentro_FineDt_gteq"/>
                    <input type="text" class="datePicker" name="DatiCentro_FineDt_lteq" id="DatiCentro_FineDt_lteq"/>
                -->

                <div class="form-group">
                <div class="col-sm-3">&nbsp;</div>
                <div class="col-sm-7">
                <button id="button-searchCentro" class="btn btn-purple btn-sm" type="submit">
                    <span id="std-label"><i class="icon-search"></i> Avvia la ricerca</span>
                    <span id="searching-label" style="display:none"><i class="icon-spinner icon-spin"></i> ricerca in corso...</span>
                </button>
                </div>
                
            <br/><br/>
            <sup>*</sup> E' possibile ricercare anche per chiave parziale
            <br/><br/>
            
            <!--div class="table-header"> Risultati ricerca </div>
            <div class="table-responsive">
            <table class="table table-striped table-bordered table-hover">
            <thead>
                <tr>
                    <th>Id Studio</th>
                    <th>Azienda sede dello studio</th>
                    <th>Unit&agrave; operativa</th>
                    <th>Principal investigator</th>
                    <th>Data prevista di inizio studio nel centro</th>
                    <th>Data prevista di fine studio nel centro</th>
                </tr>
            </thead>
            <tbody id="centri-list">
            </tbody>
            </table>
            </div-->
            </form>
            <span class="centri-list-table" >
                <table id="centri-list-grid-table" class="grid-table" ></table>
                <div id="centri-list-grid-pager"></div>
            </span>
            </div>
       </div>
    </div>
</div>