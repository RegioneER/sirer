			<div id="dialog-form-ca" title="Costi studio-specifici">
                <form class="form-horizontal">
                
                <input type="hidden" name="costoIdx" id="costoIdx" />
                <span class="">
                <@SingleFieldByType "CostoAggiuntivo" "Tipologia" availableTypes.CostoAggiuntivo userDetails true />
                Assicurazione solo per studi no-profit con assicurazione a carico della struttura di riferimento
                </span>
                <span class="">
                <@SingleFieldByType "CostoAggiuntivo" "OggettoPrincipale" availableTypes.CostoAggiuntivo userDetails true />
                </span>
                <span class="">
                <@SingleFieldByType "CostoAggiuntivo" "Quantita" availableTypes.CostoAggiuntivo userDetails true />
                </span><span class="">
                <@SingleFieldByType "CostoAggiuntivo" "Costo" availableTypes.CostoAggiuntivo userDetails true />
                </span><span class="">
                <@SingleFieldByType "CostoAggiuntivo" "Copertura" availableTypes.CostoAggiuntivo userDetails true />
                </span>
                </form>
            </div>