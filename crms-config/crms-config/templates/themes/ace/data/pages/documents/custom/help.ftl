<#global page={
    "content": path.pages+"/"+mainContent,
    "styles" : ["select2","jquery-ui-full", "datepicker", "jqgrid","daterangepicker"],
    "scripts" : ["select2","jquery-ui-full","bootbox" ,"datepicker", "daterangepicker", "jqgrid","pages/home.js","common/elementEdit.js", "chosen" , "spinner" , "datepicker" , "timepicker" , "daterangepicker" , "colorpicker" , "knob" , "autosize", "inputlimiter", "maskedinput", "tag", "tokenInput"],
    "inline_scripts":[],
    "title" : "Help",
    "description" : "Help" 
} />
<@style>
.select2-container {
    min-width:330px;
}

.infobox{
    width: 150px;
    height: 103px;
    text-align: center;
        //background-image: -moz-linear-gradient(bottom, #F2F2F2 0%, #FFFFFF 100%);
}

.infobox > .infobox-data {
    text-align: center;
    padding-left: 0px;
}

div#budget div{

}

.table-responsive tr {
    cursor:pointer;
}

</@style>
<#global breadcrumbs=
{
    "title":"<i class=\"icon-question\"></i> Help",
    "links":[]
}
/>
