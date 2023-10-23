
<script>
    var comment;

    $(document).ready(function(){
        comment=new ajaXmrTab({
        elementName: "comment",
        baseUrl: "${baseUrl}",
        listRow:commentListRow,
        saveOrUpdateUrl: "${baseUrl}/app/rest/documents/${el.id}/addComment",
        getAllUrl: "${baseUrl}/app/rest/documents/${el.id}/getComments",
        listType: "br",
            postRefresh:registerCommentDeleteAction
        });
        comment.refreshList();
    });

    function registerCommentDeleteAction(){
        $('.comment-delete').click(function(){
            if (confirm("Sei sicuro")){
                loadingScreen("Eliminazione in corso...", "${baseUrl}/int/images/loading.gif");
                $.ajax({
                    type: "GET",
                    url: "${baseUrl}/app/rest/documents/${el.id}/deleteComment/"+$(this).html(),
                    success: function(obj){
                        if (obj.result=="OK") {
                            loadingScreen("Eliminazione effettuata!", "${baseUrl}/int/images/green_check.jpg",2000);
                            comment.refreshList();
                        } else {
                            loadingScreen("Errore salvataggio!", "${baseUrl}/int/images/alerta.gif", 3000);
                        }
                    }
                });
            }
            return false;
        });
    }

    function  commentListRow(jsonRow){
        $('.comment-delete').unbind("click");
        var ret='<div class="comment-box">';
        var newDate = new Date();
        newDate.setTime(jsonRow.insDt);
        dateString = newDate.toUTCString();
        dateString=$.datepicker.formatDate('dd/mm/yy', newDate);
        dateString+=" "+ newDate.toLocaleTimeString();
        ret+='<span class="comment-from">'+jsonRow.userId;
        <#if el.getUserPolicy(userDetails).canModerate>
        ret+='&nbsp; <a href="#" class="ui-icon ui-icon-trash comment-delete" style="display: inline-block" title="elimina">'+jsonRow.id+'</a>';
        </#if>
        ret+='<br>'+dateString+'</span>';
        ret+='<p class="triangle-border left">'+jsonRow.comment.replace(/</g,"&lt;").replace(/>/g,"&gt;")+'</p>';
        ret+='</div>';
        return ret;
    }

</script>
<fieldset>
    <legend>Commenti</legend>
    <input class="submitButton round-button blue" type="button" value="Aggiungi Commento" id="add-comment" name="add-comment"/>
    <div id="comment-list-availables">

    </div>
    <div id="comment-dialog" title="Aggiungi commento">
        <fieldset>
            <form id="comment-form" method="POST" action="${baseUrl}/app/rest/admin/type/save" enctype="multipart/form-data">
            <@hidden "id" "id" />
            <div class="field-component">
            <@textarea "comment" "comment" "Commento" 40 4/>
            </div>
            <br/>
            <input class="round-button blue" type="button" value="Salva" id="comment-form-submit"/>
            </form>

        </fieldset>
    </div>

</fieldset>