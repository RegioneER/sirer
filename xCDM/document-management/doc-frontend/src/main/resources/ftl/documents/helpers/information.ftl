
<#assign editable=false/>
<#if userPolicy.canUpdate && !el.locked>
    <#assign editable=true/>
</#if>
<#if userPolicy.canUpdate && el.locked && el.lockedFromUser==userDetails.username>
    <#assign editable=true/>
</#if>
<script>

    function DateFmt(fstr) {
        this.formatString = fstr

        var mthNames = ["Jan","Feb","Mar","Apr","May","Jun","Jul","Aug","Sep","Oct","Nov","Dec"];
        var dayNames = ["Sun","Mon","Tue","Wed","Thu","Fri","Sat"];
        var zeroPad = function(number) {
            return ("0"+number).substr(-2,2);
        }

        var twoDigit= function(string){
            return (string+'').substr(2,2);
        }

        var dateMarkers = {
            d:['getDate',function(v) { return zeroPad(v)}],
            m:['getMonth',function(v) { return zeroPad(v+1)}],
            n:['getMonth',function(v) { return mthNames[v]; }],
            w:['getDay',function(v) { return dayNames[v]; }],
            y:['getFullYear',function(v) { return twoDigit(v)}],
            H:['getHours',function(v) { return zeroPad(v)}],
            M:['getMinutes',function(v) { return zeroPad(v)}],
            S:['getSeconds',function(v) { return zeroPad(v)}],
            i:['toISOString']
        };

        this.format = function(date) {
            var dateTxt = this.formatString.replace(/%(.)/g, function(m, p) {
                var rv = date[(dateMarkers[p])[0]]()

                if ( dateMarkers[p][1] != null ) rv = dateMarkers[p][1](rv)

                return rv

            });

            return dateTxt
        }

    }
    
    function valueOfField(idField){
    	form=document.forms[idField];
    	field=$(form).find('#'+idField);
    	if (field.attr('type')=='radio'){
		return $('#'+idField+':checked').attr('title');
	}else if (field.prop('tagName')=='SELECT'){
	    return field.find('option:selected').text();
	}else {
		return field.val();
	}	
}

    function saveUpdateField(idField){
        loadingScreen("Salvataggio in corso...", "${baseUrl}/int/images/loading.gif");
        form=document.forms[idField];
        var formData=new FormData(form);
        var actionUrl=$(form).attr("action")+"${el.id}";
        field=$(form).find('#'+idField);
        var newValue=field.val();
        $.ajax({
            type: "POST",
            url: actionUrl,
            contentType:false,
            processData:false,
            async:false,
            cache:false,
            data: formData,
            success: function(obj){
                if (obj.result=="OK") {
                    loadingScreen("Salvataggio effettuato", "${baseUrl}/int/images/green_check.jpg",1000);
                    if (field.attr('istokeninput')=='true'){
			value=field.tokenInput("get");
			console.log(value[0].name);
			if (fieldTypes[idField]=="ELEMENT_LINK") 
			$('#'+idField+'_value').html("<a href='${baseUrl}/app/documents/detail/"+value[0].id+"'>"+value[0].name+"</a>");
			else $('#'+idField+'_value').html(value[0].name);
			}else if (field.attr('type')=='radio'){
			    $('#'+idField+'_value').html($('#'+idField+':checked').attr('title'));
			}else if (field.prop('tagName')=='SELECT'){
			    $('#'+idField+'_value').html(field.find('option:selected').text());
			}else {
			$('#'+idField+'_value').html(field.val());
	            }
                    if ($('#'+idField+'_audit')){
                    	auditTBody=$('#'+idField+'-audit-table');
	                    fmt = new DateFmt("%d/%m/%y %H.%M");
	                    auditTBody.append(' <tr><td>${userDetails.username}</td><td>'+fmt.format(new Date())+'</td><td>update</td><td>'+origValue+'</td><td>'+newValue+'</td></tr>');
					}
                }else {
                    loadingScreen("Errore salvataggio!", "${baseUrl}/int/images/alerta.gif", 3000);
                }
            },
            error: function(){
                loadingScreen("Errore salvataggio!", "${baseUrl}/int/images/alerta.gif", 3000);
            }
        });
        $('#'+idField).show();
        $('#form-'+idField).hide();
    }

    function onMouseOverEditable(obj){
        $(obj).addClass("editable-field");
        $(obj).find('.right-corner').show();

    }

    function onMouseOutEditable(obj){
        $(obj).removeClass("editable-field");
        $(obj).find('.right-corner').hide();
    }

	var origValue=null;

    $(document).ready(function(){
        <#if editable>
            $('.right-corner').hide();
            $('.save-buttons').button({
            icons: {
                primary: "ui-icon-check"
            },
            text: false});
            $('.cancel-buttons').button({
                icons: {
                primary: "ui-icon-cancel"
                },
            text: false});
            $('.cancel-buttons').click(function(){
                $('.view-mode').show();
                $('.edit-mode').hide();
            });

        $('.view-editable-field').mouseover(function(){
            onMouseOverEditable(this);
        });
        $('.view-editable-field').mouseout(function(){
            onMouseOutEditable(this);
        });
        $('.save-buttons').click(function(){
            idField=$(this).val();
            saveUpdateField(idField);
            $('#'+idField+"_value_view").show();
            $('#form-'+idField).hide();
        });
            $('.cancel-buttons').click(function(){
                $('.single-field-form').hide();
                $('.data-view-mode').show();
            });

            $('.view-editable-field').click(function(){
                idField=$(this).attr("id");
                idField=idField.replace("_value_view","");
                console.log(idField);
                $('.single-field-form').hide();
                $('.data-view-mode').show();
                $('#'+idField+"_value_view").hide();
                $('#form-'+idField).show();
                form=document.forms[idField];
                field=$(form).find('#'+idField);
                origValue=field.val();
        });
        </#if>
    });

</script>

<#if infoPanel=="main">
<fieldset id="child-box" class="child-box">
<#else>
<fieldset>
</#if>
    <legend>Informazioni<#if el.locked><img src="${baseUrl}/int/images/lock.png" width="36px"/></#if></legend>

<#if elType.enabledTemplates?? && elType.enabledTemplates?size gt 0>
    <#list el.templates as template>
        <#if template.fields??>
            <h3 class="metadata-template-title"><@msg "template.${template.name}"/></h3>
            <#list template.fields as field>
                <#assign vals=[]/>
                <#list el.data as data>
                    <#if data.template.id=template.id && data.field.id=field.id >
                        <#assign vals=data.getVals()/>
                    </#if>
                </#list>
                <#assign audit=[]/>
                <#list el.auditData as auditData>
                    <#if auditData.field.id==field.id>
                        <#assign audit=audit+[auditData]/>
                    </#if>
                </#list>
            <#if template.wfManaged>
                    <@mdFieldDetail template field vals false/>
                <#else>
                    <@mdFieldDetail template field vals editable audit/>
            </#if>

            </#list>
        </#if>
    </#list>
</#if>
</fieldset>