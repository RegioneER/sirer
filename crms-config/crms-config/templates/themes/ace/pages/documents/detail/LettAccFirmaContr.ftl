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
 <div class="col-sm-7">
 	<button class="btn btn-xs btn-warning" onclick="window.location.href='${baseUrl}/app/documents/detail/${el.parent.id}';"><i class="icon-reply"> </i>Torna indietro </button>
 </div>