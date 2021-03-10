			<div id="tp-dialog-form" title="Aggiungi visita">
                <form class="form-horizontal">
                <input type="hidden" name="parentId"/>
                <input type="hidden" name="TimePoint_col"/>
                <@SingleFieldByType "TimePoint" "DescrizioneSelect" availableTypes.TimePoint userDetails true />
                <@SingleFieldByType "TimePoint" "Descrizione" availableTypes.TimePoint userDetails true />
                <@SingleFieldByType "TimePoint" "NumeroVisita" availableTypes.TimePoint userDetails true />
                <@SingleFieldByType "TimePoint" "Opzionale" availableTypes.TimePoint userDetails true />
                <@SingleFieldByType "TimePoint" "TempiSelect" availableTypes.TimePoint userDetails true />
                <@SingleFieldByType "TimePoint" "Tempi" availableTypes.TimePoint userDetails true />
                <#--@SingleFieldByType "TimePoint" "DurataSelect" availableTypes.TimePoint userDetails true />
                <@SingleFieldByType "TimePoint" "DurataCiclo" availableTypes.TimePoint userDetails true /-->
                <@SingleFieldByType "TimePoint" "RicoveroSelect" availableTypes.TimePoint userDetails true />
                <@SingleFieldByType "TimePoint" "Note" availableTypes.TimePoint userDetails true />
                
              
                </form>
            </div>