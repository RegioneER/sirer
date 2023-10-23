
<div class="col-sm-9">
<div id='calendar' class="calendar"></div>
</div>
<div class="col-sm-3">
	
<form id="calendar-form" method="POST" action="calendar">
     <legend>Calendari</legend>
     <ul style=" list-style-type: none;">
     <#list model['calendars'] as cal>
         <li class="calendar-checkbox" >
             <input  type="checkbox" name="calendars" value="${cal.id}">
             <span style="background-color:#${cal.backgroundColor}">&nbsp;&nbsp;&nbsp;&nbsp;</span> ${cal.name}</li>
    </#list>
    </li>
</form>
</div>