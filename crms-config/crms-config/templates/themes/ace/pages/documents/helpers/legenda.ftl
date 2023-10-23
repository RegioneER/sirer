<div class="widget-header" style="margin-top:10px">
    <legend>Legenda</legend>
</div>
<#if legendaFarmaco?? && legendaFarmaco >
<div class="widget-body" style="padding:10px">
    <legend id="legendaFarmaco">Modalit&agrave; di fornitura/copertura dei costi</legend>
    <p><b>A</b> = a carico del Promotore</p>
    <p><b>B</b> = a carico di fondi della Unit&agrave; Operativa a disposizione dello Sperimentatore*</p>
    <p><b>C</b> = fornitura/finanziamento proveniente da terzi*</p>
    <p><b>D</b> = si propone a carico del Fondo Aziendale per la Ricerca, ove presente**</p>
    <p><b>E</b> = a carico dell'SSN</p>
    <p>* Applicabile solo per studi no profit</p>
    <p>** Applicabile solo per studi no profit </p>
</div>
</#if>
<#if legendaCosti ?? && legendaCosti >
<div class="widget-body" style="padding:10px">
    <legend id="legendaCosti">Codice modalit&agrave; copertura oneri finanziari</legend>
    <p><b>A</b> = a carico del Promotore</p>
    <p><b>B</b> = a carico di fondi della Unit&agrave; Operativa a disposizione dello Sperimentatore* - <em>specificare il codice identificativo del fondo, se presente</em></p>
    <p><b>C</b> = finanziamento proveniente da terzi (in tal caso allegare l'accordo tra Promotore e finanziatore terzo che regolamento il contributo economico)</p>
    <p><b>D</b> = a carico del Fondo Aziendale per la Ricerca, ove presente**</p>
    <p><b>E</b> = a carico del SSN</p>
    <p>* Applicabile solo per studi no profit</p>
    <p>** Applicabile solo per studi no profit </p>
</div>
</#if>