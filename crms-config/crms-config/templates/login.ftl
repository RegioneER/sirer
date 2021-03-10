<script>

	//window.location.href='/change_password';
	$(document).ready(function() {
        $('#j_username').focus();
    });

</script>
<div id="login" class="login-box">
    <fieldset>
        <legend>Effettua il login</legend>
        <form method="POST" action="${baseUrl}/j_spring_security_check">
            <#if model['error']??>
                <div class="ui-state-error ui-corner-all" id='alert'>
                    <span class="ui-icon ui-icon-alert" style="float: left; margin-right: .3em;"></span>
                    <span id="alert-msg">Errore di autenticazione, verificare UserId e Password</span>
                </div>
            </#if>
            <br/>
            <div class="field-component">
            <@textbox "j_username" "j_username" "UserId" "" 20/>
            </div>
                <div class="field-component">

                <@password "j_password" "j_password" "Password"/>
</div>
            <input class="submitButton round-button blue" type="submit" value="Effettua il login"/>
        </form>
    </fieldset>
</div>
