<#include "../helpers/MetadataTemplate.ftl"/>
<style>


    .prezzo {
        text-align: right;
    }
</style>
<div>
    <fieldset>
        <legend>Informazioni</legend>
        <#if el.getUserPolicy(userDetails).isCanUpdate() >
            <#assign editable=true />
            <#else>
                <#assign editable=false />
        </#if>
        <@tableTemplateForm "DatiRibaltamento" el userDetails false/>
        <br style="clear:both">

            <#assign prezzoTotale=0 />
            <#assign ctcTotale=0 />
            <#assign transferTotale=0 />
            <#assign SSNTotale=0 />
            <#assign ribaltamentoTotale=0 />
            <#assign totalePercentualeFeas=0 />

            <table class="table table-striped table-bordered table-hover">
                <thead>
                <tr>

                    <th>Tipologia attivit&agrave;</th>
                    <th>Prezzo</th>
                    <!--th>SSN</th-->
                    <th>Transfer Price</th>
                    <th>${messages["CDCSummary.Ribaltamento"]!"CDCSummary.Ribaltamento"}</th>
                </tr>
                </thead>
                <#list el.getChildrenByType("CDCRibaltamento") as subEl>

                    <#assign ctc=subEl.getfieldData("CDCSummary", "Prezzo")[0]?number-subEl.getfieldData("CDCSummary", "TransferPrice")[0]?replace(",", ".")?number />
                    <#assign prezzo=subEl.getfieldData("CDCSummary", "Prezzo")[0]?replace(",", ".")?number />
                    <#assign transfer=subEl.getfieldData("CDCSummary", "TransferPrice")[0]?replace(",", ".")?number />
                    <#assign SSN=(subEl.getfieldData("CDCSummary", "SSN")[0]!0)?replace(",", ".")?number />
                    <#if subEl.getFieldDataString("CDCSummary", "Ribaltamento")!="" >
                        <#assign ribaltamento=(subEl.getFieldDataString("CDCSummary", "Ribaltamento"))?replace(",", ".")?number />
                    <#elseif subEl.getFieldDataString("CDCSummary", "CDCCode")=="0" || subEl.getFieldDataString("CDCSummary", "CDCCode")=="99">
                            <#assign ribaltamento=prezzo />
                            <#else>
                                <#assign ribaltamento=prezzo-transfer />
                    </#if>


                    <#assign prezzoTotale=prezzoTotale+prezzo />
                    <#assign ctcTotale=ctcTotale+ctc />
                    <#assign transferTotale=transferTotale+transfer />
                    <#assign SSNTotale=SSNTotale+SSN />


                    <tr>
                        <td>${subEl.getFieldDataString("CDCSummary", "CDCDecode")}</td>
                        <td class="prezzo">${prezzo?string(",##0.00")} &euro;</td>
                        <!--td class="prezzo">${SSN?string(",##0.00")} &euro;</td-->
                        <td class="prezzo">${transfer?string(",##0.00")} &euro;</td>
                        <td class="prezzo">
                            <#if editable ><input type="text" class="cdc" name="CDCSummary_Ribaltamento" id="${subEl.id}"
                                value="${ribaltamento?string("##0.00")?replace(",",".")}"  style="text-align:right"/>
                                <#else>${ribaltamento?string(",##0.00")} &euro;
                            </#if>
                        </td>
                    </tr>
                    <#assign ribaltamentoTotale=ribaltamentoTotale+ribaltamento />

    </fieldset>


    </#list>
    <form name="CDCForm" onsubmit="return false;"  method="POST" action="${baseUrl}/app/rest/documents/update/">
    <tr>
        <td><b>Totale</b></td>
        <td class="prezzo"><b>${prezzoTotale?string(",##0.00")} &euro;</b></td>
        <td class="prezzo"><b>${transferTotale?string(",##0.00")} &euro;</b></td>
        <td class="prezzo" name="ribaltamentoTotale" style="font-weight: bold">
            <!--
            <#if !editable ><b>${ribaltamentoTotale?string(",##0.00")} &euro;</b></#if>
            -->
            ${ribaltamentoTotale?string(",##0.00")} &euro;
        </td>
        </tr>

        </table>
        <#if editable>
            <!--button class="btn btn-primary" onclick="calcolaRiversamentoDaPercentuali();">Calcola riversamento nei fondi da valori percentuali</button>
            <button class="btn btn-primary" onclick="calcolaRiversamentoDaValori();">Calcola valori percentuali da valori riversamento</button-->
            <br/><br/>
            <table id="dataTable" class="table table-striped table-bordered table-hover">

                <thead>
                <tr>
                    <th colspan="6">Riversamento attivit&agrave;/prestazioni</th>
                </tr>
                </thead>
                <thead>
                <tr>
                    <th>Fondo</th>
                    <th>Percentuale inserita in Fattibilit&agrave;</th>
                    <th>Percentuale da riversare</th>
                    <th>Valore da riversare &euro;</th>
                    <th>Percentuale riversata</th>
                    <th>Valore da riversato &euro;</th>
                </tr>
                </thead>
                <tr>
                    <td>Importi trattenuti dall'Azienda sanitaria come overhead</td>
                    <td class="prezzo"><input type="text" name="RibaltamentoFondi_valorePerc6Feas" disabled="disabled" value='${el.getFieldDataString("RibaltamentoFondi_valorePerc6Feas")}' style="text-align:right"></td>
                    <td class="prezzo"><input type="text" <#if getUserGroups(userDetails)?starts_with('UR_')>disabled="disabled"</#if> name="RibaltamentoFondi_valorePerc6" value='<#if el.getFieldDataString("RibaltamentoFondi_valorePerc6")!="">${el.getFieldDataString("RibaltamentoFondi_valorePerc6")}<#else>${el.getFieldDataString("RibaltamentoFondi_valorePerc6Feas")}</#if>' style="text-align:right"></td>
                    <td class="prezzo"><input type="text" <#if getUserGroups(userDetails)?starts_with('UR_')>disabled="disabled"</#if> name="RibaltamentoFondi_valorePerc6Riversato" value="<#if el.getFieldDataString("RibaltamentoFondi_valorePerc6Riversato")!="">${el.getFieldDataString("RibaltamentoFondi_valorePerc6Riversato")}</#if>" style="text-align:right"></td>
                    <td class="prezzo"><input type="text" <#if getUserGroups(userDetails)?starts_with('CTO_')>disabled="disabled"</#if> name="RibaltamentoFondi_valorePerc6UR" value='<#if el.getFieldDataString("RibaltamentoFondi_valorePerc6UR")!="">${el.getFieldDataString("RibaltamentoFondi_valorePerc6UR")}<#else>${el.getFieldDataString("RibaltamentoFondi_valorePerc6")}</#if>' style="text-align:right"></td>
                    <td class="prezzo"><input type="text" <#if getUserGroups(userDetails)?starts_with('CTO_')>disabled="disabled"</#if> name="RibaltamentoFondi_valorePerc6RiversatoUR" value="<#if el.getFieldDataString("RibaltamentoFondi_valorePerc6RiversatoUR")!="">${el.getFieldDataString("RibaltamentoFondi_valorePerc6RiversatoUR")}</#if>" style="text-align:right"></td>
                    <#if el.getFieldDataString("RibaltamentoFondi_valorePerc6Feas")!="">
                        <#assign totalePercentualeFeas=totalePercentualeFeas+el.getFieldDataString("RibaltamentoFondi_valorePerc6Feas")?number />
                    </#if>
                </tr>
                <tr>
                    <td>Compensi al personale medico coinvolto nello studio clinico<br/>
                        <label><b>note da Fattibilit&agrave;:</b> ${el.getFieldDataString("RibaltamentoFondi_noteCompensiDirigenteFeas")}</label><br/>
                        <textarea <#if getUserGroups(userDetails)?starts_with('UR_')>disabled="disabled"</#if> name="RibaltamentoFondi_noteCompensiDirigente" id="RibaltamentoFondi_noteCompensiDirigente" cols="20" rows="4"  class="text ui-widget-content ui-corner-all">${el.getFieldDataString("RibaltamentoFondi_noteCompensiDirigente")}</textarea>
                    </td>
                    <td class="prezzo"><input type="text" name="RibaltamentoFondi_compensiDirigenteFeas" disabled="disabled" value='${el.getFieldDataString("RibaltamentoFondi_compensiDirigenteFeas")}' style="text-align:right"></td>
                    <td class="prezzo"><input type="text" <#if getUserGroups(userDetails)?starts_with('UR_')>disabled="disabled"</#if> name="RibaltamentoFondi_compensiDirigente" value='<#if el.getFieldDataString("RibaltamentoFondi_compensiDirigente")!="">${el.getFieldDataString("RibaltamentoFondi_compensiDirigente")}<#else>${el.getFieldDataString("RibaltamentoFondi_compensiDirigenteFeas")}</#if>' style="text-align:right"></td>
                    <td class="prezzo"><input type="text" <#if getUserGroups(userDetails)?starts_with('UR_')>disabled="disabled"</#if> name="RibaltamentoFondi_compensiDirigenteRiversato" value="<#if el.getFieldDataString("RibaltamentoFondi_compensiDirigenteRiversato")!="">${el.getFieldDataString("RibaltamentoFondi_compensiDirigenteRiversato")}</#if>" style="text-align:right"></td>
                    <td class="prezzo"><input type="text" <#if getUserGroups(userDetails)?starts_with('CTO_')>disabled="disabled"</#if> name="RibaltamentoFondi_compensiDirigenteUR" value='<#if el.getFieldDataString("RibaltamentoFondi_compensiDirigenteUR")!="">${el.getFieldDataString("RibaltamentoFondi_compensiDirigenteUR")}<#else>${el.getFieldDataString("RibaltamentoFondi_compensiDirigente")}</#if>' style="text-align:right"></td>
                    <td class="prezzo"><input type="text" <#if getUserGroups(userDetails)?starts_with('CTO_')>disabled="disabled"</#if> name="RibaltamentoFondi_compensiDirigenteRiversatoUR" value="<#if el.getFieldDataString("RibaltamentoFondi_compensiDirigenteRiversatoUR")!="">${el.getFieldDataString("RibaltamentoFondi_compensiDirigenteRiversatoUR")}</#if>" style="text-align:right"></td>
                    <#if el.getFieldDataString("RibaltamentoFondi_compensiDirigenteFeas")!="">
                        <#assign totalePercentualeFeas=totalePercentualeFeas+el.getFieldDataString("RibaltamentoFondi_compensiDirigenteFeas")?number />
                    </#if>
                </tr>
                <tr>
                    <td>Compensi al personale non medico coinvolto nello studio clinico<br/>
                        <label><b>note da Fattibilit&agrave;:</b> ${el.getFieldDataString("RibaltamentoFondi_noteCompensiRepartoFeas")}</label><br/>
                        <textarea <#if getUserGroups(userDetails)?starts_with('UR_')>disabled="disabled"</#if> name="RibaltamentoFondi_noteCompensiReparto" id="RibaltamentoFondi_noteCompensiReparto" cols="20" rows="4"  class="text ui-widget-content ui-corner-all">${el.getFieldDataString("RibaltamentoFondi_noteCompensiReparto")}</textarea>
                    </td>
                    <td class="prezzo"><input type="text" name="RibaltamentoFondi_compensiRepartoFeas" disabled="disabled" value='${el.getFieldDataString("RibaltamentoFondi_compensiRepartoFeas")}' style="text-align:right"></td>
                    <td class="prezzo"><input type="text" <#if getUserGroups(userDetails)?starts_with('UR_')>disabled="disabled"</#if> name="RibaltamentoFondi_compensiReparto" value='<#if el.getFieldDataString("RibaltamentoFondi_compensiReparto")!="">${el.getFieldDataString("RibaltamentoFondi_compensiReparto")}<#else>${el.getFieldDataString("RibaltamentoFondi_compensiRepartoFeas")}</#if>' style="text-align:right"></td>
                    <td class="prezzo"><input type="text" <#if getUserGroups(userDetails)?starts_with('UR_')>disabled="disabled"</#if> name="RibaltamentoFondi_compensiRepartoRiversato" value="<#if el.getFieldDataString("RibaltamentoFondi_compensiRepartoRiversato")!="">${el.getFieldDataString("RibaltamentoFondi_compensiRepartoRiversato")}</#if>" style="text-align:right"></td>
                    <td class="prezzo"><input type="text" <#if getUserGroups(userDetails)?starts_with('CTO_')>disabled="disabled"</#if> name="RibaltamentoFondi_compensiRepartoUR" value='<#if el.getFieldDataString("RibaltamentoFondi_compensiRepartoUR")!="">${el.getFieldDataString("RibaltamentoFondi_compensiRepartoUR")}<#else>${el.getFieldDataString("RibaltamentoFondi_compensiReparto")}</#if>' style="text-align:right"></td>
                    <td class="prezzo"><input type="text" <#if getUserGroups(userDetails)?starts_with('CTO_')>disabled="disabled"</#if> name="RibaltamentoFondi_compensiRepartoRiversatoUR" value="<#if el.getFieldDataString("RibaltamentoFondi_compensiRepartoRiversatoUR")!="">${el.getFieldDataString("RibaltamentoFondi_compensiRepartoRiversatoUR")}</#if>" style="text-align:right"></td>
                    <#if el.getFieldDataString("RibaltamentoFondi_compensiRepartoFeas")!="">
                        <#assign totalePercentualeFeas=totalePercentualeFeas+el.getFieldDataString("RibaltamentoFondi_compensiRepartoFeas")?number />
                    </#if>
                </tr>
                <tr>
                    <td>Compensi destinati a fondo di U.O.<br/>
                        <label><b>note da Fattibilit&agrave;:</b> ${el.getFieldDataString("RibaltamentoFondi_valorePerc1NoteFeas")}</label><br/>
                        <textarea <#if getUserGroups(userDetails)?starts_with('UR_')>disabled="disabled"</#if> name="RibaltamentoFondi_valorePerc1Note" id="RibaltamentoFondi_valorePerc1Note" cols="20" rows="4"  class="text ui-widget-content ui-corner-all">${el.getFieldDataString("RibaltamentoFondi_valorePerc1Note")}</textarea></td>
                    <td class="prezzo"><input type="text" name="RibaltamentoFondi_valorePerc1Feas" disabled="disabled" value='${el.getFieldDataString("RibaltamentoFondi_valorePerc1Feas")}' style="text-align:right"></td>
                    <td class="prezzo"><input type="text" <#if getUserGroups(userDetails)?starts_with('UR_')>disabled="disabled"</#if> name="RibaltamentoFondi_valorePerc1" value='<#if el.getFieldDataString("RibaltamentoFondi_valorePerc1")!="">${el.getFieldDataString("RibaltamentoFondi_valorePerc1")}<#else>${el.getFieldDataString("RibaltamentoFondi_valorePerc1Feas")}</#if>' style="text-align:right"></td>
                    <td class="prezzo"><input type="text" <#if getUserGroups(userDetails)?starts_with('UR_')>disabled="disabled"</#if> name="RibaltamentoFondi_valorePerc1Riversato" value="<#if el.getFieldDataString("RibaltamentoFondi_valorePerc1Riversato")!="">${el.getFieldDataString("RibaltamentoFondi_valorePerc1Riversato")}</#if>" style="text-align:right"></td>
                    <td class="prezzo"><input type="text" <#if getUserGroups(userDetails)?starts_with('CTO_')>disabled="disabled"</#if> name="RibaltamentoFondi_valorePerc1UR" value='<#if el.getFieldDataString("RibaltamentoFondi_valorePerc1UR")!="">${el.getFieldDataString("RibaltamentoFondi_valorePerc1UR")}<#else>${el.getFieldDataString("RibaltamentoFondi_valorePerc1")}</#if>' style="text-align:right"></td>
                    <td class="prezzo"><input type="text" <#if getUserGroups(userDetails)?starts_with('CTO_')>disabled="disabled"</#if> name="RibaltamentoFondi_valorePerc1RiversatoUR" value="<#if el.getFieldDataString("RibaltamentoFondi_valorePerc1RiversatoUR")!="">${el.getFieldDataString("RibaltamentoFondi_valorePerc1RiversatoUR")}</#if>" style="text-align:right"></td>
                    <#if el.getFieldDataString("RibaltamentoFondi_valorePerc1Feas")!="">
                        <#assign totalePercentualeFeas=totalePercentualeFeas+el.getFieldDataString("RibaltamentoFondi_valorePerc1Feas")?number />
                    </#if>
                </tr>
                <tr>
                    <td>Compensi destinati all'Universit&agrave;</td>
                    <td class="prezzo"><input type="text" name="RibaltamentoFondi_valorePerc2Feas" disabled="disabled" value='${el.getFieldDataString("RibaltamentoFondi_valorePerc2Feas")}' style="text-align:right"></td>
                    <td class="prezzo"><input type="text" <#if getUserGroups(userDetails)?starts_with('UR_')>disabled="disabled"</#if> name="RibaltamentoFondi_valorePerc2" value='<#if el.getFieldDataString("RibaltamentoFondi_valorePerc2")!="">${el.getFieldDataString("RibaltamentoFondi_valorePerc2")}<#else>${el.getFieldDataString("RibaltamentoFondi_valorePerc2Feas")}</#if>' style="text-align:right"></td>
                    <td class="prezzo"><input type="text" <#if getUserGroups(userDetails)?starts_with('UR_')>disabled="disabled"</#if> name="RibaltamentoFondi_valorePerc2Riversato" value="<#if el.getFieldDataString("RibaltamentoFondi_valorePerc2Riversato")!="">${el.getFieldDataString("RibaltamentoFondi_valorePerc2Riversato")}</#if>" style="text-align:right"></td>
                    <td class="prezzo"><input type="text" <#if getUserGroups(userDetails)?starts_with('CTO_')>disabled="disabled"</#if> name="RibaltamentoFondi_valorePerc2UR" value='<#if el.getFieldDataString("RibaltamentoFondi_valorePerc2UR")!="">${el.getFieldDataString("RibaltamentoFondi_valorePerc2UR")}<#else>${el.getFieldDataString("RibaltamentoFondi_valorePerc2")}</#if>' style="text-align:right"></td>
                    <td class="prezzo"><input type="text" <#if getUserGroups(userDetails)?starts_with('CTO_')>disabled="disabled"</#if> name="RibaltamentoFondi_valorePerc2RiversatoUR" value="<#if el.getFieldDataString("RibaltamentoFondi_valorePerc2RiversatoUR")!="">${el.getFieldDataString("RibaltamentoFondi_valorePerc2RiversatoUR")}</#if>" style="text-align:right"></td>
                    <#if el.getFieldDataString("RibaltamentoFondi_valorePerc2Feas")!="">
                        <#assign totalePercentualeFeas=totalePercentualeFeas+el.getFieldDataString("RibaltamentoFondi_valorePerc2Feas")?number />
                    </#if>
                </tr>
                <tr>
                    <td>Importo accantonato nel fondo Clinical Trial Office (CTO)/Task Force Aziendale (TFA)</td>
                    <td class="prezzo"><input type="text" name="RibaltamentoFondi_valorePerc3Feas" disabled="disabled" value='${el.getFieldDataString("RibaltamentoFondi_valorePerc3Feas")}' style="text-align:right"></td>
                    <td class="prezzo"><input type="text" <#if getUserGroups(userDetails)?starts_with('UR_')>disabled="disabled"</#if> name="RibaltamentoFondi_valorePerc3" value='<#if el.getFieldDataString("RibaltamentoFondi_valorePerc3")!="">${el.getFieldDataString("RibaltamentoFondi_valorePerc3")}<#else>${el.getFieldDataString("RibaltamentoFondi_valorePerc3Feas")}</#if>' style="text-align:right"></td>
                    <td class="prezzo"><input type="text" <#if getUserGroups(userDetails)?starts_with('UR_')>disabled="disabled"</#if> name="RibaltamentoFondi_valorePerc3Riversato" value="<#if el.getFieldDataString("RibaltamentoFondi_valorePerc3Riversato")!="">${el.getFieldDataString("RibaltamentoFondi_valorePerc3Riversato")}</#if>" style="text-align:right"></td>
                    <td class="prezzo"><input type="text" <#if getUserGroups(userDetails)?starts_with('CTO_')>disabled="disabled"</#if> name="RibaltamentoFondi_valorePerc3UR" value='<#if el.getFieldDataString("RibaltamentoFondi_valorePerc3UR")!="">${el.getFieldDataString("RibaltamentoFondi_valorePerc3UR")}<#else>${el.getFieldDataString("RibaltamentoFondi_valorePerc3")}</#if>' style="text-align:right"></td>
                    <td class="prezzo"><input type="text" <#if getUserGroups(userDetails)?starts_with('CTO_')>disabled="disabled"</#if> name="RibaltamentoFondi_valorePerc3RiversatoUR" value="<#if el.getFieldDataString("RibaltamentoFondi_valorePerc3RiversatoUR")!="">${el.getFieldDataString("RibaltamentoFondi_valorePerc3RiversatoUR")}</#if>" style="text-align:right"></td>
                    <#if el.getFieldDataString("RibaltamentoFondi_valorePerc3Feas")!="">
                        <#assign totalePercentualeFeas=totalePercentualeFeas+el.getFieldDataString("RibaltamentoFondi_valorePerc3Feas")?number />
                    </#if>
                </tr>
                <tr>
                    <td>Importo accantonato nel fondo per gli studi no profit</td>
                    <td class="prezzo"><input type="text" name="RibaltamentoFondi_valorePerc4Feas" disabled="disabled" value='${el.getFieldDataString("RibaltamentoFondi_valorePerc4Feas")}' style="text-align:right"></td>
                    <td class="prezzo"><input type="text" <#if getUserGroups(userDetails)?starts_with('UR_')>disabled="disabled"</#if> name="RibaltamentoFondi_valorePerc4" value='<#if el.getFieldDataString("RibaltamentoFondi_valorePerc4")!="">${el.getFieldDataString("RibaltamentoFondi_valorePerc4")}<#else>${el.getFieldDataString("RibaltamentoFondi_valorePerc4Feas")}</#if>' style="text-align:right"></td>
                    <td class="prezzo"><input type="text" <#if getUserGroups(userDetails)?starts_with('UR_')>disabled="disabled"</#if> name="RibaltamentoFondi_valorePerc4Riversato" value="<#if el.getFieldDataString("RibaltamentoFondi_valorePerc4Riversato")!="">${el.getFieldDataString("RibaltamentoFondi_valorePerc4Riversato")}</#if>" style="text-align:right"></td>
                    <td class="prezzo"><input type="text" <#if getUserGroups(userDetails)?starts_with('CTO_')>disabled="disabled"</#if> name="RibaltamentoFondi_valorePerc4UR" value='<#if el.getFieldDataString("RibaltamentoFondi_valorePerc4UR")!="">${el.getFieldDataString("RibaltamentoFondi_valorePerc4UR")}<#else>${el.getFieldDataString("RibaltamentoFondi_valorePerc4")}</#if>' style="text-align:right"></td>
                    <td class="prezzo"><input type="text" <#if getUserGroups(userDetails)?starts_with('CTO_')>disabled="disabled"</#if> name="RibaltamentoFondi_valorePerc4RiversatoUR" value="<#if el.getFieldDataString("RibaltamentoFondi_valorePerc4RiversatoUR")!="">${el.getFieldDataString("RibaltamentoFondi_valorePerc4RiversatoUR")}</#if>" style="text-align:right"></td>
                    <#if el.getFieldDataString("RibaltamentoFondi_valorePerc4Feas")!="">
                        <#assign totalePercentualeFeas=totalePercentualeFeas+el.getFieldDataString("RibaltamentoFondi_valorePerc4Feas")?number />
                    </#if>
                </tr>
                <tr>
                    <td>Importo accantonato nel fondo per la Sezione del CER (se applicabile)</td>
                    <td class="prezzo"><input type="text" name="RibaltamentoFondi_valorePerc7Feas" disabled="disabled" value='${el.getFieldDataString("RibaltamentoFondi_valorePerc7Feas")}' style="text-align:right"></td>
                    <td class="prezzo"><input type="text" <#if getUserGroups(userDetails)?starts_with('UR_')>disabled="disabled"</#if> name="RibaltamentoFondi_valorePerc7" value='<#if el.getFieldDataString("RibaltamentoFondi_valorePerc7")!="">${el.getFieldDataString("RibaltamentoFondi_valorePerc7")}<#else>${el.getFieldDataString("RibaltamentoFondi_valorePerc7Feas")}</#if>' style="text-align:right"></td>
                    <td class="prezzo"><input type="text" <#if getUserGroups(userDetails)?starts_with('UR_')>disabled="disabled"</#if> name="RibaltamentoFondi_valorePerc7Riversato" value="<#if el.getFieldDataString("RibaltamentoFondi_valorePerc7Riversato")!="">${el.getFieldDataString("RibaltamentoFondi_valorePerc7Riversato")}</#if>" style="text-align:right"></td>
                    <td class="prezzo"><input type="text" <#if getUserGroups(userDetails)?starts_with('CTO_')>disabled="disabled"</#if> name="RibaltamentoFondi_valorePerc7UR" value='<#if el.getFieldDataString("RibaltamentoFondi_valorePerc7UR")!="">${el.getFieldDataString("RibaltamentoFondi_valorePerc7UR")}<#else>${el.getFieldDataString("RibaltamentoFondi_valorePerc7")}</#if>' style="text-align:right"></td>
                    <td class="prezzo"><input type="text" <#if getUserGroups(userDetails)?starts_with('CTO_')>disabled="disabled"</#if> name="RibaltamentoFondi_valorePerc7RiversatoUR" value="<#if el.getFieldDataString("RibaltamentoFondi_valorePerc7RiversatoUR")!="">${el.getFieldDataString("RibaltamentoFondi_valorePerc7RiversatoUR")}</#if>" style="text-align:right"></td>
                    <#if el.getFieldDataString("RibaltamentoFondi_valorePerc7Feas")!="">
                        <#assign totalePercentualeFeas=totalePercentualeFeas+el.getFieldDataString("RibaltamentoFondi_valorePerc7Feas")?number />
                    </#if>
                </tr>
                <tr>
                    <td>Fondo Centro Farmacologia clinica</td>
                    <td class="prezzo"><input type="text" name="RibaltamentoFondi_valorePercFarmacologiaFeas" disabled="disabled" value='${el.getFieldDataString("RibaltamentoFondi_valorePercFarmacologiaFeas")}' style="text-align:right"></td>
                    <td class="prezzo"><input type="text" <#if getUserGroups(userDetails)?starts_with('UR_')>disabled="disabled"</#if> name="RibaltamentoFondi_valorePercFarmacologia" value='<#if el.getFieldDataString("RibaltamentoFondi_valorePercFarmacologia")!="">${el.getFieldDataString("RibaltamentoFondi_valorePercFarmacologia")}<#else>${el.getFieldDataString("RibaltamentoFondi_valorePercFarmacologiaFeas")}</#if>' style="text-align:right"></td>
                    <td class="prezzo"><input type="text" <#if getUserGroups(userDetails)?starts_with('UR_')>disabled="disabled"</#if> name="RibaltamentoFondi_valorePercFarmacologiaRiversato" value="<#if el.getFieldDataString("RibaltamentoFondi_valorePercFarmacologiaRiversato")!="">${el.getFieldDataString("RibaltamentoFondi_valorePercFarmacologiaRiversato")}</#if>" style="text-align:right"></td>
                    <td class="prezzo"><input type="text" <#if getUserGroups(userDetails)?starts_with('CTO_')>disabled="disabled"</#if> name="RibaltamentoFondi_valorePercFarmacologiaUR" value='<#if el.getFieldDataString("RibaltamentoFondi_valorePercFarmacologiaUR")!="">${el.getFieldDataString("RibaltamentoFondi_valorePercFarmacologiaUR")}<#else>${el.getFieldDataString("RibaltamentoFondi_valorePercFarmacologia")}</#if>' style="text-align:right"></td>
                    <td class="prezzo"><input type="text" <#if getUserGroups(userDetails)?starts_with('CTO_')>disabled="disabled"</#if> name="RibaltamentoFondi_valorePercFarmacologiaRiversatoUR" value="<#if el.getFieldDataString("RibaltamentoFondi_valorePercFarmacologiaRiversatoUR")!="">${el.getFieldDataString("RibaltamentoFondi_valorePercFarmacologiaRiversatoUR")}</#if>" style="text-align:right"></td>
                    <#if el.getFieldDataString("RibaltamentoFondi_valorePercFarmacologiaFeas")!="">
                        <#assign totalePercentualeFeas=totalePercentualeFeas+el.getFieldDataString("RibaltamentoFondi_valorePercFarmacologiaFeas")?number />
                    </#if>
                </tr>
                <tr>
                    <td>Compenso per progetto universitario</td>
                    <td class="prezzo"><input type="text" name="RibaltamentoFondi_valorePercUniversitarioFeas" disabled="disabled" value='${el.getFieldDataString("RibaltamentoFondi_valorePercUniversitarioFeas")}' style="text-align:right"></td>
                    <td class="prezzo"><input type="text" <#if getUserGroups(userDetails)?starts_with('UR_')>disabled="disabled"</#if> name="RibaltamentoFondi_valorePercUniversitario" value='<#if el.getFieldDataString("RibaltamentoFondi_valorePercUniversitario")!="">${el.getFieldDataString("RibaltamentoFondi_valorePercUniversitario")}<#else>${el.getFieldDataString("RibaltamentoFondi_valorePercUniversitarioFeas")}</#if>' style="text-align:right"></td>
                    <td class="prezzo"><input type="text" <#if getUserGroups(userDetails)?starts_with('UR_')>disabled="disabled"</#if> name="RibaltamentoFondi_valorePercUniversitarioRiversato" value="<#if el.getFieldDataString("RibaltamentoFondi_valorePercUniversitarioRiversato")!="">${el.getFieldDataString("RibaltamentoFondi_valorePercUniversitarioRiversato")}</#if>" style="text-align:right"></td>
                    <td class="prezzo"><input type="text" <#if getUserGroups(userDetails)?starts_with('CTO_')>disabled="disabled"</#if> name="RibaltamentoFondi_valorePercUniversitarioUR" value='<#if el.getFieldDataString("RibaltamentoFondi_valorePercUniversitarioUR")!="">${el.getFieldDataString("RibaltamentoFondi_valorePercUniversitarioUR")}<#else>${el.getFieldDataString("RibaltamentoFondi_valorePercUniversitario")}</#if>' style="text-align:right"></td>
                    <td class="prezzo"><input type="text" <#if getUserGroups(userDetails)?starts_with('CTO_')>disabled="disabled"</#if> name="RibaltamentoFondi_valorePercUniversitarioRiversatoUR" value="<#if el.getFieldDataString("RibaltamentoFondi_valorePercUniversitarioRiversatoUR")!="">${el.getFieldDataString("RibaltamentoFondi_valorePercUniversitarioRiversatoUR")}</#if>" style="text-align:right"></td>
                    <#if el.getFieldDataString("RibaltamentoFondi_valorePercUniversitarioFeas")!="">
                        <#assign totalePercentualeFeas=totalePercentualeFeas+el.getFieldDataString("RibaltamentoFondi_valorePercUniversitarioFeas")?number />
                    </#if>
                </tr>
                <tr>
                    <td>Altro<br/>
                        <label><b>note da Fattibilit&agrave;:</b> ${el.getFieldDataString("RibaltamentoFondi_notePerc5Feas")}</label><br/>
                        <textarea <#if getUserGroups(userDetails)?starts_with('UR_')>disabled="disabled"</#if> name="RibaltamentoFondi_notePerc5" id="RibaltamentoFondi_notePerc5" cols="20" rows="4"  class="text ui-widget-content ui-corner-all">${el.getFieldDataString("RibaltamentoFondi_notePerc5")}</textarea></td>
                    <td class="prezzo"><input type="text" name="RibaltamentoFondi_valorePerc5Feas" disabled="disabled" value='${el.getFieldDataString("RibaltamentoFondi_valorePerc5Feas")}' style="text-align:right"></td>
                    <td class="prezzo"><input type="text" <#if getUserGroups(userDetails)?starts_with('UR_')>disabled="disabled"</#if> name="RibaltamentoFondi_valorePerc5" value='<#if el.getFieldDataString("RibaltamentoFondi_valorePerc5")!="">${el.getFieldDataString("RibaltamentoFondi_valorePerc5")}<#else>${el.getFieldDataString("RibaltamentoFondi_valorePerc5Feas")}</#if>' style="text-align:right"></td>
                    <td class="prezzo"><input type="text" <#if getUserGroups(userDetails)?starts_with('UR_')>disabled="disabled"</#if> name="RibaltamentoFondi_valorePerc5Riversato" value="<#if el.getFieldDataString("RibaltamentoFondi_valorePerc5Riversato")!="">${el.getFieldDataString("RibaltamentoFondi_valorePerc5Riversato")}</#if>" style="text-align:right"></td>
                    <td class="prezzo"><input type="text" <#if getUserGroups(userDetails)?starts_with('CTO_')>disabled="disabled"</#if> name="RibaltamentoFondi_valorePerc5UR" value='<#if el.getFieldDataString("RibaltamentoFondi_valorePerc5UR")!="">${el.getFieldDataString("RibaltamentoFondi_valorePerc5UR")}<#else>${el.getFieldDataString("RibaltamentoFondi_valorePerc5")}</#if>' style="text-align:right"></td>
                    <td class="prezzo"><input type="text" <#if getUserGroups(userDetails)?starts_with('CTO_')>disabled="disabled"</#if> name="RibaltamentoFondi_valorePerc5RiversatoUR" value="<#if el.getFieldDataString("RibaltamentoFondi_valorePerc5RiversatoUR")!="">${el.getFieldDataString("RibaltamentoFondi_valorePerc5RiversatoUR")}</#if>" style="text-align:right"></td>
                    <#if el.getFieldDataString("RibaltamentoFondi_valorePerc5Feas")!="">
                        <#assign totalePercentualeFeas=totalePercentualeFeas+el.getFieldDataString("RibaltamentoFondi_valorePerc5Feas")?number />
                    </#if>
                </tr>
                <tr>
                    <td><b>Totale</b></td>
                    <td class="prezzo"><span name="totalePercentualeFeas" style="font-weight: bold;">${totalePercentualeFeas}</span></td>
                    <td class="prezzo"><span name="totalePercentuale" style="font-weight: bold;"></span></td>
                    <td class="prezzo"><span name="totaleRiversato" style="font-weight: bold;"></span></td>
                    <td class="prezzo"><span name="totalePercentualeUR" style="font-weight: bold;"></span></td>
                    <td class="prezzo"><span name="totaleRiversatoUR" style="font-weight: bold;"></span></td>
                </tr>
                <tr>
                    <th colspan="2"></th>
                    <th  class="prezzo"><#if getUserGroups(userDetails)?starts_with('CTO_')><button class="btn btn-primary" onclick="calcolaRiversamentoDaValori('');">Calcola da valori</button></#if></th>
                    <th  class="prezzo"><#if getUserGroups(userDetails)?starts_with('CTO_')><button class="btn btn-primary" onclick="calcolaRiversamentoDaPercentuali('');">Calcola da percentuali</button></#if></th>
                    <th  class="prezzo"><#if getUserGroups(userDetails)?starts_with('UR_')><button class="btn btn-primary" onclick="calcolaRiversamentoDaValori('UR');">Calcola da valori</button></#if></th>
                    <th  class="prezzo"><#if getUserGroups(userDetails)?starts_with('UR_')><button class="btn btn-primary" onclick="calcolaRiversamentoDaPercentuali('UR');">Calcola da percentuali</button></#if></th>
                </tr>
                <tr>
                    <th colspan="6">
                        <span><b>Note CTO/TFA:</b>&nbsp;
                        <!--input type="text" <#if getUserGroups(userDetails)?starts_with('UR_')>disabled="disabled"</#if> size="100" name="RibaltamentoFondi_noteCTO" value='${el.getFieldDataString("RibaltamentoFondi_noteCTO")}' style="text-align:left"-->
                        <textarea <#if getUserGroups(userDetails)?starts_with('UR_')>disabled="disabled"</#if> name="RibaltamentoFondi_noteCTO" id="RibaltamentoFondi_noteCTO" cols="100" rows="6"  class="text ui-widget-content ui-corner-all">${el.getFieldDataString("RibaltamentoFondi_noteCTO")}</textarea>
                </span>

                    </th>
                </tr>
            </table>
            <br/><br/>
            <#else>
                <table class="table table-striped table-bordered table-hover">

                    <thead>
                    <tr>
                        <th colspan="6">Riversamento attivit&agrave;/prestazioni</th>
                    </tr>
                    </thead>
                    <thead>
                    <tr>
                        <th>Fondo</th>
                        <th>Percentuale inserita in Fattibilit&agrave;</th>
                        <th>Percentuale da riversare</th>
                        <th>Valore da riversare &euro;</th>
                        <th>Percentuale riversata</th>
                        <th>Valore riversato &euro;</th>
                    </tr>
                    </thead>
                    <tr>
                        <td>Importi trattenuti dall'Azienda sanitaria come overhead</td>
                        <td>${el.getFieldDataString("RibaltamentoFondi_valorePerc6Feas")}</td>
                        <td>${el.getFieldDataString("RibaltamentoFondi_valorePerc6")}</td>
                        <td>${el.getFieldDataString("RibaltamentoFondi_valorePerc6Riversato")}</td>
                        <td>${el.getFieldDataString("RibaltamentoFondi_valorePerc6UR")}</td>
                        <td>${el.getFieldDataString("RibaltamentoFondi_valorePerc6RiversatoUR")}</td>
                    </tr>
                    <tr>
                        <td>Compensi al personale medico coinvolto nello studio clinico<br/>
                            <label><b>note da Fattibilit&agrave;:</b> ${el.getFieldDataString("RibaltamentoFondi_noteCompensiDirigenteFeas")}</label><br/>
                            <label><b>note CTO/TFA:</b> ${el.getFieldDataString("RibaltamentoFondi_noteCompensiDirigente")}</label>
                        </td>
                        <td>${el.getFieldDataString("RibaltamentoFondi_compensiDirigenteFeas")}</td>
                        <td>${el.getFieldDataString("RibaltamentoFondi_compensiDirigente")}</td>
                        <td>${el.getFieldDataString("RibaltamentoFondi_compensiDirigenteRiversato")}</td>
                        <td>${el.getFieldDataString("RibaltamentoFondi_compensiDirigenteUR")}</td>
                        <td>${el.getFieldDataString("RibaltamentoFondi_compensiDirigenteRiversatoUR")}</td>
                    </tr>
                    <tr>
                        <td>Compensi al personale non medico coinvolto nello studio clinico<br/>
                            <label><b>note da Fattibilit&agrave;:</b> ${el.getFieldDataString("RibaltamentoFondi_noteCompensiRepartoFeas")}</label><br/>
                            <label><b>note CTO/TFA:</b> ${el.getFieldDataString("RibaltamentoFondi_noteCompensiReparto")}</label>
                        </td>
                        <td>${el.getFieldDataString("RibaltamentoFondi_compensiRepartoFeas")}</td>
                        <td>${el.getFieldDataString("RibaltamentoFondi_compensiReparto")}</td>
                        <td>${el.getFieldDataString("RibaltamentoFondi_compensiRepartoRiversato")}</td>
                        <td>${el.getFieldDataString("RibaltamentoFondi_compensiRepartoUR")}</td>
                        <td>${el.getFieldDataString("RibaltamentoFondi_compensiRepartoRiversatoUR")}</td>
                    </tr>
                    <tr>
                        <td>Compensi destinati a fondo di U.O.<br/>
                            <label><b>note da Fattibilit&agrave;:</b> ${el.getFieldDataString("RibaltamentoFondi_valorePerc1NoteFeas")}</label><br/>
                            <label><b>note CTO/TFA:</b> ${el.getFieldDataString("RibaltamentoFondi_valorePerc1Note")}</label></td>
                        <td>${el.getFieldDataString("RibaltamentoFondi_valorePerc1Feas")}</td>
                        <td>${el.getFieldDataString("RibaltamentoFondi_valorePerc1")}</td>
                        <td>${el.getFieldDataString("RibaltamentoFondi_valorePerc1Riversato")}</td>
                        <td>${el.getFieldDataString("RibaltamentoFondi_valorePerc1UR")}</td>
                        <td>${el.getFieldDataString("RibaltamentoFondi_valorePerc1RiversatoUR")}</td>
                    </tr>
                    <tr>
                        <td>Compensi destinati all'Universit&agrave;</td>
                        <td>${el.getFieldDataString("RibaltamentoFondi_valorePerc2Feas")}</td>
                        <td>${el.getFieldDataString("RibaltamentoFondi_valorePerc2")}</td>
                        <td>${el.getFieldDataString("RibaltamentoFondi_valorePerc2Riversato")}</td>
                        <td>${el.getFieldDataString("RibaltamentoFondi_valorePerc2UR")}</td>
                        <td>${el.getFieldDataString("RibaltamentoFondi_valorePerc2RiversatoUR")}</td>
                    </tr>
                    <tr>
                        <td>Importo accantonato nel fondo Clinical Trial Office (CTO)/Task Force Aziendale (TFA)</td>
                        <td>${el.getFieldDataString("RibaltamentoFondi_valorePerc3Feas")}</td>
                        <td>${el.getFieldDataString("RibaltamentoFondi_valorePerc3")}</td>
                        <td>${el.getFieldDataString("RibaltamentoFondi_valorePerc3Riversato")}</td>
                        <td>${el.getFieldDataString("RibaltamentoFondi_valorePerc3UR")}</td>
                        <td>${el.getFieldDataString("RibaltamentoFondi_valorePerc3RiversatoUR")}</td>
                    </tr>
                    <tr>
                        <td>Importo accantonato nel fondo per gli studi no profit</td>
                        <td>${el.getFieldDataString("RibaltamentoFondi_valorePerc4Feas")}</td>
                        <td>${el.getFieldDataString("RibaltamentoFondi_valorePerc4")}</td>
                        <td>${el.getFieldDataString("RibaltamentoFondi_valorePerc4Riversato")}</td>
                        <td>${el.getFieldDataString("RibaltamentoFondi_valorePerc4UR")}</td>
                        <td>${el.getFieldDataString("RibaltamentoFondi_valorePerc4RiversatoUR")}</td>
                    </tr>
                    <tr>
                        <td>Importo accantonato nel fondo per la Sezione del CER (se applicabile)</td>
                        <td>${el.getFieldDataString("RibaltamentoFondi_valorePerc7Feas")}</td>
                        <td>${el.getFieldDataString("RibaltamentoFondi_valorePerc7")}</td>
                        <td>${el.getFieldDataString("RibaltamentoFondi_valorePerc7Riversato")}</td>
                        <td>${el.getFieldDataString("RibaltamentoFondi_valorePerc7UR")}</td>
                        <td>${el.getFieldDataString("RibaltamentoFondi_valorePerc7RiversatoUR")}</td>
                    </tr>
                    <tr>
                        <td>Fondo Centro Farmacologia clinica</td>
                        <td>${el.getFieldDataString("RibaltamentoFondi_valorePercFarmacologiaFeas")}</td>
                        <td>${el.getFieldDataString("RibaltamentoFondi_valorePercFarmacologia")}</td>
                        <td>${el.getFieldDataString("RibaltamentoFondi_valorePercFarmacologiaRiversato")}</td>
                        <td>${el.getFieldDataString("RibaltamentoFondi_valorePercFarmacologiaUR")}</td>
                        <td>${el.getFieldDataString("RibaltamentoFondi_valorePercFarmacologiaRiversatoUR")}</td>
                    </tr>
                    <tr>
                        <td>Compenso per progetto universitario</td>
                        <td>${el.getFieldDataString("RibaltamentoFondi_valorePercUniversitarioFeas")}</td>
                        <td>${el.getFieldDataString("RibaltamentoFondi_valorePercUniversitario")}</td>
                        <td>${el.getFieldDataString("RibaltamentoFondi_valorePercUniversitarioRiversato")}</td>
                        <td>${el.getFieldDataString("RibaltamentoFondi_valorePercUniversitarioUR")}</td>
                        <td>${el.getFieldDataString("RibaltamentoFondi_valorePercUniversitarioRiversatoUR")}</td>
                    </tr>
                    <tr>
                        <td>Altro<br/>
                            <label><b>note da Fattibilit&agrave;:</b> ${el.getFieldDataString("RibaltamentoFondi_notePerc5Feas")}</label><br/>
                            <label><b>note CTO/TFA:</b> ${el.getFieldDataString("RibaltamentoFondi_notePerc5")}</label></td>
                        <td>${el.getFieldDataString("RibaltamentoFondi_valorePerc5Feas")}</td>
                        <td>${el.getFieldDataString("RibaltamentoFondi_valorePerc5")}</td>
                        <td>${el.getFieldDataString("RibaltamentoFondi_valorePerc5Riversato")}</td>
                        <td>${el.getFieldDataString("RibaltamentoFondi_valorePerc5UR")}</td>
                        <td>${el.getFieldDataString("RibaltamentoFondi_valorePerc5RiversatoUR")}</td>
                    </tr>
                    <tr>
                        <td colspan="6"><span><b>Note CTO/TFA:</b>&nbsp;${el.getFieldDataString("RibaltamentoFondi_noteCTO")}</span></td>
                    </tr>
                </table>

        </#if>
        </form>
        <br>
        <div id="task-Actions"></div>
    <#if editable >
        <!--input  class="round-button blue" type="button" value="Salva modifiche" onclick="javascript:saveAll();"-->
    </#if>

</div>