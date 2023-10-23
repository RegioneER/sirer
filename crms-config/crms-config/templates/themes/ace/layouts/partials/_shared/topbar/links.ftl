<!--
<li style="background-color: #931410; !important">
	<a class="not-yet-implemented" href="#" style="background-color: #931410; !important" onclick="alert('Funzione non ancora disponibile.'); return false;">
		<i class="icon-file-text"></i> 
		<span class="topbar-button-text hidden-900">Documenti</span>
	</a>
</li>
-->
<li style="background-color: #931410; !important" >
	<#assign linkrep=baseUrl+"/app/documents/reports" />
	<a href="${linkrep}" class="not-yet-implemented" style="background-color: #931410; !important">
	<!--<a href="#" class="not-yet-implemented" style="background-color: #931410; !important" onclick="alert('Funzione non ancora disponibile.'); return false;" >-->
		<i class="icon-dashboard"></i>
		<span class="topbar-button-text hidden-900">Reportistica</span>
	</a>
</li>

    <li style="background-color: #931410; !important" > <!--class="green"-->
  		<a href="/sedute" style="background-color: #931410; !important"> <!-- /uxmr -->
		<i class=" icon-group"></i> 
		<span  class="topbar-button-text hidden-900">Modulo riunioni</span>
	</a>
</li>
