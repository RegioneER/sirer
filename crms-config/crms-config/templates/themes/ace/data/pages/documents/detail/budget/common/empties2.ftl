
var empties=new Array();
var emptiesTmp=new Array();
//voce typeId in prod: 67 in locale : 8
var emptyVoce={"id":null,"type":{"id":"67","typeId":"VocePrestazione"},"children":null,"metadata":{"PrestazioniDizionario_CodiceBranca3":[""],"PrestazioniDizionario_Descrizione":[""],"PrestazioniDizionario_CodiceBranca4":[""],"PrestazioniDizionario_CodiceBranca1":[""],"PrestazioniDizionario_CodiceBranca2":[""],"PrestazioniDizionario_Codice":[""],"PrestazioniDizionario_Tipo":[""],"PrestazioniDizionario_Nota":[""],"PrestazioniDizionario_TariffaALPI":[""],"PrestazioniDizionario_TariffaSSN":[""]},"title":""};


emptiesTmp[emptiesTmp.length]=emptyFolderTimePoint;
emptiesTmp[emptiesTmp.length]=emptyFolderPrestazioni;
emptiesTmp[emptiesTmp.length]=emptyFolderTpxp;
emptiesTmp[emptiesTmp.length]=emptyTimePoint;
emptiesTmp[emptiesTmp.length]=emptyPrestazione;
emptiesTmp[emptiesTmp.length]=emptytpxp;
emptiesTmp[emptiesTmp.length]=emptyFolderPXP;
emptiesTmp[emptiesTmp.length]=emptyFolderPXS;
emptiesTmp[emptiesTmp.length]=emptyPrestazioneXPaziente;
emptiesTmp[emptiesTmp.length]=emptyPrestazioneXStudio;
emptiesTmp[emptiesTmp.length]=emptyFolderBudgetStudio;
emptiesTmp[emptiesTmp.length]=emptyBudgetCTC;
emptiesTmp[emptiesTmp.length]=emptyVoce;
emptiesTmp[emptiesTmp.length]=emptyFolderBracci;
emptiesTmp[emptiesTmp.length]=emptyBraccio;
emptiesTmp[emptiesTmp.length]=emptyFolderCostiAggiuntivi;
emptiesTmp[emptiesTmp.length]=emptyCostoAggiuntivo;
//emptiesTmp[emptiesTmp.length]=emptyFolderPXPCTC;
//emptiesTmp[emptiesTmp.length]=emptyFolderPXSCTC;
//emptiesTmp[emptiesTmp.length]=emptyFolderPassthroughCTC;

$.each(emptiesTmp,function(ie,currEmpty){
	empties[currEmpty.type.id]=currEmpty;
});
        