<@script>
function loadComments(){
	$('#comments-list').html('<i class="icon-spinner icon-spin icon-large"></i> caricamento commenti');
	<#if el.getUserPolicy(userDetails).canModerate>
	$('.comment-delete').unbind('click');
	</#if>
	$.ajax({
		url: "${baseUrl}/app/rest/documents/${el.id}/getComments",
	}).done(function(data){
	$('#comments-list').html('');
		if (data.length==0){
			$('#comments-list').html('Nessun commento presente');
		}
		for (i=0;i<data.length;i++){
			writeComment(data[i]);
		}
		<#if el.getUserPolicy(userDetails).canModerate>
		registerCommentDeleteAction();
		</#if>
	});;
}
<#if el.getUserPolicy(userDetails).canModerate>
function registerCommentDeleteAction(){
        $('.comment-delete').click(function(){
        	commentId=$(this).attr('href');
        	bootbox.confirm("Sei sicuro?", function(result){
        		console.log(result);
        		if (result){
        			$.ajax({
                    type: "GET",
                    url: "${baseUrl}/app/rest/documents/${el.id}/deleteComment/"+commentId,
                    success: function(obj){
	                        if (obj.result=="OK") {
	                            loadComments();
	                        } else {
	                        	bootbox.alert("Si sono verificati problemi con l'eliminazione del commento");    
	                        }
	                    }
                	});	
        		}
        		/*
        		 $.ajax({
                    type: "GET",
                    url: "${baseUrl}/app/rest/documents/${el.id}/deleteComment/"+$(this).attr('href'),
                    success: function(obj){
                        if (obj.result=="OK") {
                            loadComments();
                        } else {
                            
                        }
                    }
                });
                */
        	});
            return false;
        });
   }
 </#if>
 

function writeComment(item){
	var proto=$('#commentItemPrototype').html();
	proto=proto.replace(/__user__/g,item.userId);
	proto=proto.replace("__comment__",item.comment);
	var newDate = new Date();
    newDate.setTime(item.insDt);
    dateString = newDate.toUTCString();
    dateString=$.datepicker.formatDate('dd/mm/yy', newDate);
    dateString+=" "+ newDate.toLocaleTimeString();
    proto=proto.replace("__time__",dateString);
    <#if el.getUserPolicy(userDetails).canModerate>
		proto=proto.replace("__id__",item.id);			        
	</#if>
	$('#comments-list').append(proto);
}

$("#comment-form").submit(function() {
    var url = $("#comment-form").attr('action');
    $.ajax({
           type: "POST",
           url: url,
           data: $("#comment-form").serialize(),
           success: function(data)
           {
			   if (data.result!='OK'){
			   	bootbox.alert("Si e' verificato un problema");
			   }else {           		
               	$("#comment-form input#comment").val("");
               	loadComments();
               }
           }
         });
    return false;
});


loadComments();
</@script>
<#macro commentsBox>
	<div class="dialogs">
		<div id="comments-list" class="itemdiv dialogdiv"></div>
	</div>
	<form id="comment-form" method="POST" action="${baseUrl}/app/rest/documents/${el.id}/addComment">
		<div class="form-actions">
			<div class="input-group">
				<input placeholder="Scrivi qui il tuo commento ..." type="text" class="form-control" name="comment" id="comment" />
				<span class="input-group-btn">
					<button class="btn btn-sm btn-info no-radius" type="submit" style="font-size: 13px;margin-top: 0;">
						<i class="icon-share-alt"></i>
						Invia
					</button>
				</span>
			</div>
		</div>
	</form>
</#macro>
<div id="commentItemPrototype" style="display:none">
	<div class="itemdiv dialogdiv comment-box">
		<div class="user">
			<i class="icon-user icon-3x"></i>
		</div>
		<div class="body">
			<div class="time">
				<i class="icon-time"></i>
					<span class="green">__time__</span>
			</div>

			<div class="name">
				<a href="#" data-ref="__user__" data-type="replace-with-username">__user__</a>
			</div>
			<div class="text">__comment__</div>
				<div class="tools">
					<#if el.getUserPolicy(userDetails).canModerate>
			        	<a href="__id__"  class="btn btn-minier btn-info comment-delete" style="display: inline-block" title="elimina">
			        		<i class="icon-only icon-trash"></i>
			        	</a>
			        </#if>
				</div>
			</div>
		</div>
</div>
<#assign body>
	<@commentsBox/>		
</#assign>
<@widgetBox "Commenti" "icon-comment blue" body/>

