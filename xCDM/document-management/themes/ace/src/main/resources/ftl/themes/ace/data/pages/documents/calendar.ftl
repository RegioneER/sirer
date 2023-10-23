<#global page={
	"content": path.pages+"/"+mainContent,
	"styles" : ["select2","jquery-ui-full", "datepicker", "jqgrid","fullcalendar"],
	"scripts" : ["fullcalendar","select2","jquery-ui-full","bootbox" ,"datepicker", "jqgrid","pages/home.js","common/elementEdit.js", "chosen" , "spinner" , "datepicker" , "timepicker" , "daterangepicker" , "colorpicker" , "knob" , "autosize", "inputlimiter", "maskedinput", "tag"],
	"inline_scripts":[],
	"title" : "Home page",
 	"description" : "Dynamic tables and grids using jqGrid plugin" 
} />

<@script>

    var hiddenCalendars=new Array();

    $(document).ready(function() {

        $('#calendar').fullCalendar({
            buttonText: {
                prev: '<i class="icon-chevron-left"></i>',
                next: '<i class="icon-chevron-right"></i>'
            },

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

    });

</@script>