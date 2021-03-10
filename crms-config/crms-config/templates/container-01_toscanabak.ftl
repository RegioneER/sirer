<#if userDetails??>
    <#if userDetails.authorities?size gt 0>
    <#setting locale="it_IT">
    <#setting number_format="computer">
    <#assign security=JspTaglibs["/WEB-INF/tld/spring-security.tld"] />
    <#include "lib/macros.ftl">
    
    
    <#include "themes/ace/structure.ftl" >
    <#else>
    <script type="text/javascript">
        window.location.href="/authzssl/httpError.php?code=401";
    </script>
    </#if>
<#else>
    <script type="text/javascript">
        //window.location.href="../../";
    </script>
    NON HO USERDETAILS!
</#if>
