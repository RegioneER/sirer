<#global page=page + {"scripts": page.scripts + ["select2"], "styles": page.styles + ["select2"]} />
<@script>
$('select').not('#DatiTeamDiStudio_NomeCognome-select').select2({containerCssClass:'select2-ace',allowClear: true});
$('#DatiTeamDiStudio_NomeCognome-select').hide();
try{
    $('#DatiTeamDiStudio_NomeCognome').select2({
        containerCssClass:'select2-ace',allowClear: true,
        placeholder:"Iniziare a scrivere il Nome e Cognome",
        minimumInputLength:3 ,
        formatInputTooShort: function () {
            return "Iniziare a scrivere il Nome e Cognome";
        },
        ajax:{
            url:buildScriptUrl_DatiTeamDiStudio_NomeCognome,
            dataType:'json',
            data: function(term,page){
                    return {term:term}
                },
            results:function(data,page){
                return {
                    results:data.items
                    };
                }
            }
        });
    }
catch(ex1){}
function piChange2(){
try{
if(loadedElement !== undefined && loadedElement && loadedElement.metadata['DatiTeamDiStudio_NomeCognome'] && loadedElement.metadata['DatiTeamDiStudio_NomeCognome'][0]){
var text=loadedElement.metadata['DatiTeamDiStudio_NomeCognome'][0].split('###')[1];
$('#DatiTeamDiStudio_NomeCognome').select2('data',{id:loadedElement.metadata['DatiTeamDiStudio_NomeCognome'][0],text:text});
}
}catch(ex){
}

}
piChange2();

</@script>
