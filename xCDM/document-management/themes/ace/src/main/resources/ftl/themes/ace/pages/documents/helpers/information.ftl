<#include "MetadataTemplate.ftl"/>
<#assign editable=false/>
<#if userPolicy.canUpdate && !el.locked>
    <#assign editable=true/>
</#if>
<#if userPolicy.canUpdate && el.locked && el.lockedFromUser==userDetails.username>
    <#assign editable=true/>
</#if>


<#assign json=el.type.getDummyJson() />
<#assign loadedJson=el.getElementCoreJsonToString(userDetails) />

<@script>
	$.fn.editable.defaults.mode = 'inline';
	$('.field-inline-anchor').editable({
	    params: function(params) {
		    var metadata={};
		    metadata[params.name]=params.value
		   
		    return metadata;
	    },
	    emptytext :"Valore mancante"	
	});
 	var loadedElement=${loadedJson};
 	var dummy=${json};
 	var empties=new Array();
 	
 	empties[dummy.type.id]=dummy;
</@script>
<@script>

    function valueOfField(idField){
      	console.log("valueOfField - "+idField);
    	console.log(idField);
    	field=$('#'+idField);
    	 if (field.attr('istokeninput')=='true'){
			value=field.tokenInput("get");
			console.log(value);
			if (value.length>0)
			return value[0].id;
			else return "";
			}
    	if (field.attr('type')=='radio'){
		return $('#'+idField+':checked').attr('title');
		}else if (field.prop('tagName')=='SELECT'){
		    return field.find('option:selected').text();
		}else {
			return field.val();
		}	
}	

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

        
        </#if>
   

</@script>
<#if elType.enabledTemplates?? && elType.enabledTemplates?size gt 0>
			
<div class="widget-box">
	<div class="widget-header">
		<h4><i class="fa fa-info"></i> Metadati</h4>
			<div class="widget-toolbar no-border">
				<ul id="myTab" class="nav nav-tabs">
					<#assign first=true/>
						<#list el.templates as template>
			        		<#if template.fields??>
					    		<li>
									<a href="#t-${template.id}" <#if first>class="active"</#if> data-toggle="tab"><@msg "template."+template.name/></a>
								</li>
			    				<#assign first=false/>
			        		</#if>
			    		</#list>
			    </ul>
			</div>
	</div>
	<div class="widget-body">
		<div class="widget-main padding-6">
			<div class="tab-content">
		    <#assign first=true/>
		    <#list el.templates as template>
		        <div id="t-${template.id}" class="tab-pane <#if first>in active</#if>">
			        <#assign first=false/>
			        <#if template.fields??>
			        	<@TemplateForm template.name el userDetails true />
			        </#if>
		        </div>
		    </#list>
		    </div>
		</div>
		</div>
</div>
</#if>
