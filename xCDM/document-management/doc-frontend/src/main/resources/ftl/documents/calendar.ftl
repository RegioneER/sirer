
<link href='${baseUrl}/int/css/fullcalendar.css' rel='stylesheet' />
<link href='${baseUrl}/int/css/fullcalendar.print.css' rel='stylesheet' media='print' />
<script src='${baseUrl}/int/js/fullcalendar.min.js'></script>

<script>

    var hiddenCalendars=new Array();

    $(document).ready(function() {

        $('#calendar').fullCalendar({
            theme: true,
            header: {
                left: 'prev,next today',
                center: 'title',
                right: 'month,agendaWeek,agendaDay'
            },
            editable: false,
            events: '${baseUrl}/app/rest/calendar/getEvents',
            loading: function(isLoading){
                if (isLoading) {
                    console.log("caricamento...");
                }else{
                    console.log("caricato");
                    for (i=0;i<hiddenCalendars.length;i++){
                        $('#calendar').fullCalendar('removeEvents', hiddenCalendars[i]);
                    }
                }
            },
            dayClick: function(day){
                console.log(day);
                $('#calendar').fullCalendar( 'changeView', 'agendaDay' );
                $('#calendar').fullCalendar( 'gotoDate', day );
            }
        });
        $('.calendar-submit').click(function(){
            $('#calendar-form').submit();
        });
        $('.calendar-checkbox input').each(function(){
          this.checked=true;
        });
        $('.calendar-checkbox').click(function(){
            $(this).find("input").each(function(){
                this.checked=!this.checked;
                if (!this.checked) {
                    hiddenCalendars[hiddenCalendars.length]=$(this).val();
                    $('#calendar').fullCalendar('removeEvents', $(this).val());
                }else {
                    console.log($('#calendar').fullCalendar( 'clientEvents',$(this).val()));
                    $('#calendar').fullCalendar('refetchEvents');
                    idx=hiddenCalendars.indexOf($(this).val());
                    hiddenCalendars.splice(idx, 1);
                    for (i=0;i<hiddenCalendars.length;i++){
                        console.log(i+" - elimino - "+hiddenCalendars[i]);
                        $('#calendar').fullCalendar('removeEvents', hiddenCalendars[i]);
                    }

                }
            });
        });
        /*
        $('.calendar-checkbox input').change(function(){
            if (!this.checked) {
                hiddenCalendars[hiddenCalendars.length]=$(this).val();
                   $('#calendar').fullCalendar('removeEvents', $(this).val());
            }else {
                console.log($('#calendar').fullCalendar( 'clientEvents',$(this).val()));
                $('#calendar').fullCalendar('refetchEvents');
                idx=hiddenCalendars.indexOf($(this).val());
                hiddenCalendars.splice(idx, 1);
                for (i=0;i<hiddenCalendars.length;i++){
                    console.log(i+" - elimino - "+hiddenCalendars[i]);
                    $('#calendar').fullCalendar('removeEvents', hiddenCalendars[i]);
                }

            }
        });
        */
    });

</script>

<div class="mainContent">
    <form id="calendar-form" method="POST" action="calendar">
    <fieldset class="calendar-list">
        <legend>Calendari</legend>
        <#list model['calendars'] as cal>
            <li class="calendar-checkbox" style="background-color:#${cal.calendarColor}">
                <input  type="checkbox" name="calendars" value="${cal.id}" disabled>
                ${cal.calendarName}</li>
        </#list>
    </fieldset>
    </form>

    <div id='calendar' class="calendar"></div>

</div>