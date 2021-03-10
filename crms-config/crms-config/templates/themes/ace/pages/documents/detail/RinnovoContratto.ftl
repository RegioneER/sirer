    <#include "../helpers/title.ftl"/>
    </b>
    <br/>
        <div style="display: block">
            <div style="float: right">
            <#include "../helpers/attached-file.ftl"/>
        </div>
        <#include "../helpers/information.ftl"/>
    </div>
    <#include "../helpers/comments.ftl"/>
 <br>
 <input type="button" class="submitButton round-button blue" onclick="window.location.href='${baseUrl}/app/documents/detail/${el.parent.id}';" value="Torna indietro">