function populateAsPrevious(){
    var center=$('#esamForm [name=CENTER]').val();
    var pkServiceValue=$('#esamForm [name='+pkService+']').val();
    var esam=$('#esamForm [name=ESAM]').val();
    var progr=$('#esamForm [name=PROGR]').val()-1;
    var visitnum=$('#esamForm [name=VISITNUM]').val();
    var visitnum_progr=$('#esamForm [name=VISITNUM_PROGR]').val();
    var url='index.php?CENTER='+center+'&'+pkService+'='+pkServiceValue+'&VISITNUM='+visitnum+'&ESAM='+esam+'&PROGR='+progr+'&VISITNUM_PROGR='+visitnum_progr+'&getFormData=true';
    bootbox.dialog({message:"loading...", closeButton: false});
    $.getJSON(url, function (data){
        if (data.status!='OK') {
            bootbox.hideAll();
            bootbox.alert('Errore');
            return;
        }
        for (var key in data.data){
            if (key=='CODPAT' || key=='PROGR' || key=='VISITNUM_PROGR' || key=='ESAM' || key=='VISITNUM' || key=='INVIOCO') continue;
            var val=data.data[key];
            var form=$('#esamForm');
            if (val!=null){
                var field=form.find('[name='+key+']');
                if (field.length==0){
                    if (key.endsWith('_D'))
                        key=key.substr(0, key.length-2)+"D";
                    if (key.endsWith('_M'))
                        key=key.substr(0, key.length-2)+"M";
                    if (key.endsWith('_Y'))
                        key=key.substr(0, key.length-2)+"Y";
                    field=form.find('[name='+key+']');
                }
                if (field.attr('type')=='radio' || field.attr('type')=='checkbox'){
                    if (field.attr('type')=='radio'){
                        form.find('[name='+key+'][value="'+val+'"]').prop('checked', true);
                    }else {
                        if (val==1) field.prop('checked', true);
                        else field.prop('checked', false);
                    }
                }else {
                    console.log(field.attr('name'), val);
                    field.val(val);
                }
            }
        }
        bootbox.hideAll();
        cf();
    });
}

function buildModalSfoglia(token){
    $.getJSON('index.php?xcrfToken='+token+'&format=json', function(data) {
        var dlg = $('<div>');
        dlg.append('<h3>Sfoglia</h3>');
        dlg.append('Clicca sull\'icona "<i class="fa fa-level-down blue"></i>&nbsp;" per espandare il livello o sull\'icona "<i class="fa fa-pencil green"></i>&nbsp;" per compilare la form');
        explodeLevel(data, dlg);
        bootbox.dialog({
            message: dlg
        }).on('shown.bs.modal', function (e) {
            $('#sfogliaForm input')[0].focus();
        });
    });
}

function explodeLevel(data, container){
    var lUl=$('<ul>');
    if (data.results.length==0){
        var lvlLi=$('<li>');
        lvlLi.html("nessun risultato");
        lUl.append(lvlLi);
    }
    for (var i=0;i<data.results.length;i++){
        var lvl1itm=data.results[i];
        var lvlLi=$('<li>');
        var lvlValue=lvl1itm['THIS_LEVEL'];
        lvlLi.attr('data-level-value',lvlValue);
        lvlLi.html(lvlValue);
        if (data.selectable){
            lvlLi.append('&nbsp;');
            var fillFormLink=$('<a>');
            fillFormLink.attr('href','#');
            fillFormLink.html('<i class="fa fa-pencil green"></i>&nbsp;');
            var action=data.action+"&L"+data.nextLevel+"="+encodeURIComponent(lvl1itm['THIS_LEVEL']);
            (function (link, itm, data) {
                link.click(function (event) {
                    event.preventDefault();
                    for (var k in data.mapFields) {
                        $('#esamForm [name=' + data.mapFields[k] + ']').val(itm[k]);
                    }
                    bootbox.hideAll();
                    return false;
                });
            })(fillFormLink, lvl1itm, data);
            lvlLi.append(fillFormLink);
        }
        if (data.action){
            lvlLi.append('&nbsp;');
            var explodeLink=$('<a>');
            explodeLink.attr('href','#');
            explodeLink.html('<i class="fa fa-level-down blue"></i>&nbsp;');
            var action=data.action+"&L"+data.nextLevel+"="+encodeURIComponent(lvl1itm['THIS_LEVEL']);
            (function(action, lvlValue){
                explodeLink.click(function(event){
                    event.preventDefault();
                    $.getJSON(action, function(data){explodeLevel(data, $('li[data-level-value="'+lvlValue+'"]'))});
                });
            })(action, lvlValue);
            lvlLi.append(explodeLink);
        }
        lUl.append(lvlLi);
    }
    container.append(lUl);
}



function buildModalCerca(token){
    $.getJSON('index.php?xcrfToken='+token+'&format=json', function(data) {
        var dlg = $('<div>');
        dlg.append('<h3>Cerca</h3>');
        if (data.form) {
            var f = $('<form>');
            f.attr('id', 'cercaForm');
            for (var i = 0; i < data.form.fields.length; i++) {
                var fEl = data.form.fields[i];
                var field = $('<input>');
                field.attr('type', fEl.type);
                field.attr('placeholder', fEl.label);
                field.attr('name', fEl.name);
                f.append(field);
            }
            var btn = $('<button>');
            btn.addClass('btn btn-xs btn-info');
            btn.html('Cerca');
            btn.attr('type', 'submit');
            f.attr('action', data.form.action);
            f.append('&nbsp;');
            f.attr('method', 'POST');
            f.append(btn);
            f.submit(function (event) {
                event.preventDefault();
                var form = $(this);
                postData = form_to_json(form);
                var action=$(this).attr('action');
                (function(action, postData){
                    cercaSubmit(action, postData);
                })(action, postData);

            });
            var resTb = $('<div>');
            resTb.attr('id', 'resContainer');
            var pagingBar=$('<div>');
            pagingBar.attr('id', 'cercaPagingContainer');

            dlg.append(f);
            dlg.append(pagingBar);
            dlg.append(resTb);
        }
        bootbox.dialog({
            message: dlg
        }).on('shown.bs.modal', function (e) {
            $('#cercaForm input')[0].focus();
        });
    });
}

function cercaSubmit(action, postData){
    $('#cercaPagingContainer').html("");
    $('#resContainer').html("<i class='fa fa-spin fa-spinner'></i> ...");
    $.post(action, postData, function (data) {
        $('#resContainer').html("");
        data.total -= 0;
        if (data.total > 0) {
            var tbRes = $('<table>');
            tbRes.addClass('table table-bordered table-hover table-striped');
            for (var i = 0; i < data.results.length; i++) {
                var header = $('<thead>');
                headerRow = $('<tr>');
                header.append(headerRow);
                var itm = data.results[i];
                for (var k in itm) {
                    var th = $('<th>');
                    th.html(k);
                    headerRow.append(th);
                }
                var th = $('<th>');
                headerRow.append(th);

                var resRow = $('<tr>');
                for (var k in itm) {
                    var td = $('<th>');
                    td.html(itm[k]);
                    resRow.append(td);
                }
                var td = $('<td>');
                var link = $('<a>');
                link.attr('href', '#');
                link.addClass('btn btn-xs btn-info');
                link.html('<i class="fa fa-angle-double-right"></i>&nbsp;');
                td.html(link);
                (function (link, itm, data) {
                    link.click(function (event) {
                        event.preventDefault();
                        for (var k in data.mapFields) {
                            $('#esamForm [name=' + data.mapFields[k] + ']').val(itm[k]);
                        }
                        bootbox.hideAll();
                        return false;
                    });
                })(link, itm, data);
                resRow.append(td);
                tbRes.append(resRow);


            }
            tbRes.append(header);
            $('#resContainer').html('Clicca sul pulsante "<i class="fa fa-angle-double-right"></i>" per compilare la form');
            $('#resContainer').append(tbRes);

            var pagingBarContainer=$('<div>');
            pagingBarContainer.addClass('row');
            pagingBarContainer.css("text-align", "center");
            var pagingBar=$('<nav>');
            pagingBarContainer.append(pagingBar);
            var pgUl=$('<ul>');
            pgUl.addClass('pagination');
            pagingBar.append(pgUl);

            pgUl.append(getPagingItem('|&laquo;', 1 , (data.page==1), false, action, postData));
            pgUl.append(getPagingItem('&laquo;', data.page-1 , (data.page==1), false, action, postData));
            var delta=3;
            var start=data.page-delta;
            if (start<1) start=1;
            var end=start+(2*delta)+1;
            if (start>1){
                pgUl.append(getPagingItem("...", start-delta , false, false, action, postData));
            }
            for (var i=start;i<=end;i++){
                pgUl.append(getPagingItem(i, i , (data.page==i), (data.page==i), action, postData));
            }
            if (end<data.pages){
                pgUl.append(getPagingItem("...", end+delta , false, false, action, postData));
            }
            pgUl.append(getPagingItem('&raquo;', data.page+1 , (data.page==data.pages), false, action, postData));
            pgUl.append(getPagingItem('&raquo;|', data.pages , (data.page==data.pages), false, action, postData));
            $('#cercaPagingContainer').append(pagingBarContainer);
        } else {
            $('#resContainer').html("Nessun risultato trovato");
        }
    });
}


function getPagingItem(text, page, disabled, active, action, postData){
    var previous=$('<li>');
    previous.addClass('page-item');
    if (disabled){
        previous.addClass('disabled');
    }
    if (active){
        previous.addClass('active');
    }
    var pLink=$('<a>');
    pLink.attr('href','#');
    pLink.attr('data-page', page);
    pLink.html(text);
    (function(action, postData, pLink){
        pLink.click(function(){
            postData.page=page;
            cercaSubmit(action, postData);
        });
    })(action, postData, pLink);
    previous.append(pLink);
    return previous;
}

function form_to_json (selector) {
    var ary = $(selector).serializeArray();
    var obj = {};
    for (var a = 0; a < ary.length; a++) obj[ary[a].name] = ary[a].value;
    return obj;
}

$(document).ready(function(){
    $('.show_groupped').click(function(){
        var esam=$(this).attr('data-esam');
        var visitnum=$(this).attr('data-visitnum');
        var visitnum_progr=$(this).attr('data-visitnum-progr');
        $(this).hide();
        $('.hide_groupped[data-esam='+esam+'][data-visitnum='+visitnum+'][data-visitnum-progr='+visitnum_progr+']').show();
        $('.submitted[data-esam='+esam+'][data-visitnum='+visitnum+'][data-visitnum-progr='+visitnum_progr+'][data-esam-new=false]').show();
        //$('.esam-label[data-esam='+esam+'][data-visitnum='+visitnum+'][data-visitnum-progr='+visitnum_progr+'][data-esam-new=false]').show();
        return;
    });
    $('.hide_groupped').click(function(){
        var esam=$(this).attr('data-esam');
        var visitnum=$(this).attr('data-visitnum');
        var visitnum_progr=$(this).attr('data-visitnum-progr');
        $(this).hide();
        $('.show_groupped[data-esam='+esam+'][data-visitnum='+visitnum+'][data-visitnum-progr='+visitnum_progr+']').show();
        $('.submitted[data-esam='+esam+'][data-visitnum='+visitnum+'][data-visitnum-progr='+visitnum_progr+'][data-esam-new=false]').hide();
        //$('.esam-label[data-esam='+esam+'][data-visitnum='+visitnum+'][data-visitnum-progr='+visitnum_progr+'][data-esam-new=false]').hide();

        return;
    });
});

function focusFirstField() {
    $('form :input:visible:enabled').first().focus();
}


$(document).ready(function () {

    if (window.location.hash == '#write' && window.location.search == '?inbox') {
        inbox_nuovomessaggio();
    } else if (window.location.search == '?inbox') {
        inbox_pannello('bacheca');
    }
    $('.i18n_inline').on("hover", function () {
        console.log("sono io????");
    });
    $('[data-rel=popover]').popover({
        container: 'body',
        html: true,
        content: function () {
            return $('#' + $(this).attr('id') + '-content').html();
        }
        //selector:'testdiv'
    });
    height = $(window).height() - 130;
    $('#fullHeightContainer').css('height', height + 'px').css('border', 0);
    $('.fullHeightContainer').css('height', height + 'px').css('border', 0);

    var $head = $("#fullHeightContainer").contents().find("head");
    var $head2 = $(".fullHeightContainer").contents().find("head");

    $head.append($("<link/>",
        { rel: "stylesheet", href: "style.css", type: "text/css" }
    ));
    $head2.append($("<link/>",
        { rel: "stylesheet", href: "style.css", type: "text/css" }
    ));
    setTimeout("focusFirstField()", 500);


});


$(window).resize(function () {
    height = $(window).height() - 130;
    $('#fullHeightContainer').css('height', height + 'px');
    $('.fullHeightContainer').css('height', height + 'px');
});
function showAudit(title) {
    bootbox.dialog({
        message: $('#form_a_t').html(),
        title: "<i class='fa fa-eye'></i> " + title
    });
}

function drawPieChart(placeholder, data, position) {
    $.plot(placeholder, data, {
        series: {
            pie: {
                show: true,
                tilt: 0.8,
                highlight: {
                    opacity: 0.25
                },
                stroke: {
                    color: '#fff',
                    width: 2
                },
                startAngle: 2
            }
        },
        legend: {
            show: true,
            position: position || "ne",
            labelBoxBorderColor: null,
            margin: [-30, 15]
        },
        grid: {
            hoverable: true,
            clickable: true
        }
    })
}

function drawBarChart(placeholder, data, position) {
    var data = [
        {"label": "Clinician", "data": "50", "color": "#6A957D"},
        {"label": "Hospital Pharmacy", "data": "16.67", "color": "#0B37E0"},
        {"label": "National Data Quality", "data": "33.33", "color": "#3F90F0"}
    ];
    var data = [
        ["January", 10],
        ["February", 8],
        ["March", 4],
        ["April", 13],
        ["May", 17],
        ["June", 9]
    ];
    var d1 = [
        ["January", 3],
        ["February", 3],
        [2, 5],
        [3, 7],
        [4, 8],
        [5, 10],
        [6, 11],
        [7, 9],
        [8, 5],
        [9, 13]
    ];
    var d1_1 = [
        [1325376000000, 120],
        [1328054400000, 70],
        [1330560000000, 100],
        [1333238400000, 60],
        [1335830400000, 35]
    ];

    var d1_2 = [
        [1325376000000, 80],
        [1328054400000, 60],
        [1330560000000, 30],
        [1333238400000, 35],
        [1335830400000, 30]
    ];

    var d1_3 = [
        [1325376000000, 80],
        [1328054400000, 40],
        [1330560000000, 30],
        [1333238400000, 20],
        [1335830400000, 10]
    ];

    var d1_4 = [
        [1325376000000, 15],
        [1328054400000, 10],
        [1330560000000, 15],
        [1333238400000, 20],
        [1335830400000, 15]
    ];

    var data1 = [
        {
            label: "Product 1",
            data: d1_1,
            bars: {
                show: true,
                barWidth: 12 * 24 * 60 * 60 * 300,
                fill: true,
                lineWidth: 1,
                order: 1,
                fillColor: "#AA4643"
            },
            color: "#AA4643"
        },
        {
            label: "Product 2",
            data: d1_2,
            bars: {
                show: true,
                barWidth: 12 * 24 * 60 * 60 * 300,
                fill: true,
                lineWidth: 1,
                order: 2,
                fillColor: "#89A54E"
            },
            color: "#89A54E"
        },
        {
            label: "Product 3",
            data: d1_3,
            bars: {
                show: true,
                barWidth: 12 * 24 * 60 * 60 * 300,
                fill: true,
                lineWidth: 1,
                order: 3,
                fillColor: "#4572A7"
            },
            color: "#4572A7"
        },
        {
            label: "Product 4",
            data: d1_4,
            bars: {
                show: true,
                barWidth: 12 * 24 * 60 * 60 * 300,
                fill: true,
                lineWidth: 1,
                order: 4,
                fillColor: "#80699B"
            },
            color: "#80699B"
        }
    ];

    $.plot($(placeholder), data1, {
        xaxis: {
            axisLabel: 'Month',
            axisLabelUseCanvas: true,
            axisLabelFontSizePixels: 12,
            axisLabelFontFamily: 'Verdana, Arial, Helvetica, Tahoma, sans-serif',
            axisLabelPadding: 5
        },
        yaxis: {
            axisLabel: 'Value',
            axisLabelUseCanvas: true,
            axisLabelFontSizePixels: 12,
            axisLabelFontFamily: 'Verdana, Arial, Helvetica, Tahoma, sans-serif',
            axisLabelPadding: 5
        },
        grid: {
            hoverable: true,
            clickable: false,
            borderWidth: 1
        },
        legend: {
            labelBoxBorderColor: "none",
            position: "right"
        },
        series: {
            shadowSize: 1
        }
    });
}


function pageWidth() {
    return window.innerWidth != null ? window.innerWidth : document.documentElement && document.documentElement.clientWidth ? document.documentElement.clientWidth : document.body != null ? document.body.clientWidth : null;
}
function pageHeight() {
    return  window.innerHeight != null ? window.innerHeight : document.documentElement && document.documentElement.clientHeight ? document.documentElement.clientHeight : document.body != null ? document.body.clientHeight : null;
}
function posLeft() {
    return typeof window.pageXOffset != 'undefined' ? window.pageXOffset : document.documentElement && document.documentElement.scrollLeft ? document.documentElement.scrollLeft : document.body.scrollLeft ? document.body.scrollLeft : 0;
}
function posTop() {
    return typeof window.pageYOffset != 'undefined' ? window.pageYOffset : document.documentElement && document.documentElement.scrollTop ? document.documentElement.scrollTop : document.body.scrollTop ? document.body.scrollTop : 0;
}
function posRight() {
    return posLeft() + pageWidth();
}
function posBottom() {
    return posTop() + pageHeight();
}

$(document).ready(function () {


    $('.rich-editor').ace_wysiwyg({
        toolbar: [
            'font',
            'fontSize',
            {name: 'bold', className: 'btn-info'},
            {name: 'italic', className: 'btn-info'},
            {name: 'strikethrough', className: 'btn-info'},
            {name: 'underline', className: 'btn-info'},
            null,
            {name: 'foreColor', className: 'btn-info'}
        ],
        'wysiwyg': {
            fileUploadError: function () {
                alert('Not Supported')
            }
        }
    }).prev().addClass('rich-editor');

    $('#nav-search-input').keypress(function () {
        var value = $(this).val();
        if (value.length >= 2) {
            $('#search-icon').addClass('icon-spinner icon-spin blue');
        } else $('#search-icon').removeClass('icon-spinner icon-spin blue');
    });
    $('#nav-search-input').autocomplete({
        minLength: 2,
        source: "index.php?fastSearch",
        focus: function (event, ui) {
            $("#fast-search-input").val(ui.item.label);
            return false;
        },
        select: function (event, ui) {
            return false;
        }
    })
        .data("ui-autocomplete")._renderItem = function (ul, item) {
        $('#search-icon').removeClass('icon-spinner icon-spin blue');
        if (!item.link) return $("<p class='alert-warning'>")
            .append("<i class=\"fa fa-warning\"></i> " + item.label + "</a>")
            .appendTo(ul);
        else
            return $("<p class='alert-success'>")
                .append("<a href=\"" + item.link + "\"><i class='fa fa-user-md'></i> " + item.label + "</a>")
                .appendTo(ul);
    };
});

function applyEditor() {
    $('.rich-editor').ace_wysiwyg({
        toolbar: [
            'font',
            'fontSize',
            {name: 'bold', className: 'btn-info'},
            {name: 'italic', className: 'btn-info'},
            {name: 'strikethrough', className: 'btn-info'},
            {name: 'underline', className: 'btn-info'},
            null,
            {name: 'foreColor', className: 'btn-info'}
        ],
        'wysiwyg': {
            fileUploadError: function () {
                alert('Not Supported')
            }
        }
    }).prev().addClass('rich-editor');
}

function RichTextBox(targetId) {
    var text = $('#id_' + targetId).val();
    var content = "<div class=\"wysiwyg-editor rich-editor\" id=\"bootbox_editor_content\">" + text + "</div>";
    bootbox.confirm(content, function () {
        var oldString = $('#bootbox_editor_content').html();
        newString = oldString.substring(-4);
        $('#id_' + targetId).val(newString);
        setTimeout("updateLabel" + targetId + "()", 300);
    });
    setTimeout("applyEditor();", 1000);


}

function ShowMessage(message) {
    bootbox.dialog({
        message: message,
        closeButton: false
    });
}

function ShowConfirm(message) {
    bootbox.dialog({
        message: message,
        closeButton: true
    });
}

function HideMessage() {
    bootbox.hideAll();
}

function AddDrugAdminCode(text, visitnum, progr) {
    bootbox.dialog({
        title: text,
        message: "<form class='form-horizontal' action='index.php' style='padding:20px' id='add-drug-admin-code'><input type='hidden' name='CHECK_CU' value='OK'><div class='form-group'><label for='add-drug-admin-code-cu' class='col-sm-5' style='text-align:right'>" + messages.CUCode + ":</label><input class='col-sm-5' type='text' id='add-drug-admin-code-cu' name='CU'></div><div class='form-group'><label for='add-drug-admin-code-codpat' class=' col-sm-5' style='text-align:right'>" + messages.pkService + ":</label><input type='text' class=' col-sm-5' id='add-drug-admin-code-pkservice' name='PK_SERVICE'></div></form>",
        closeButton: true,
        buttons: {
            success: {
                label: messages.OK,
                className: "btn-success",
                callback: function () {
                    $.ajax({
                        type: 'post',
                        url: 'index.php',
                        data: $('#add-drug-admin-code').serialize(),
                        success: function (data) {
                            if (data.status == 'FOUND') window.location.href = data.link_to;
                            else {
                                if (data.status == 'NOT_FOUND') alert(messages.NOT_FOUND);
                                else if (data.status == 'ALREADY_INSERTED') alert(messages.ALREADY_INSERTED + " " + messages.BY + " " + data.insertedBy + " " + messages.ON + " " + data.insertedOn);
                            }
                        }
                    });
                }
            },
            main: {
                label: messages.CANCEL,
                className: "btn-reset",
                callback: function () {
                    bootbox.hideAll();
                }
            }
        }
    });
}

function ChangeProfile() {
    bootbox.dialog({
        title: messages.ProfileChangeTitle,
        message: "<span id='change-profile-content'><i class=\"icon-spinner icon-spin orange bigger-125\"></i> " + messages.ProfileLoadingAvailables + " ...</span>",
        closeButton: true
    });
    $.getJSON("index.php?getUserProfiles", function (data) {
        if (data.RETURN && data.RETURN == 'NULL') {
            $('#change-profile-content').html(messages['NoProfileAvailables']);
            return;
        }
        var items = [];
        $.each(data, function (idx, val) {
            items.push("<option value='" + idx + "'>" + val + "</option>");
        });
        var select = messages.ProfileChangeLabel + ": <select onchange=\"ApplyProfile(this.value)\"><option></option>";
        for (i = 0; i < items.length; i++) {
            select += items[i];
        }
        select += "</select>";
        $('#change-profile-content').html(select);
    });
}

function ApplyProfile(profileCode) {
    $('#change-profile-content').html("<i class=\"icon-spinner icon-spin orange bigger-125\"></i> " + messages.ProfileApply + " ...");
    $.getJSON("index.php?setUserProfile=" + profileCode, function (data) {
        if (data == 'OK') window.location.href = window.location.href;
    });
}


function ChooseLanguage() {
    bootbox.dialog({
        title: messages.LanguagesChooseTitle,
        message: "<span id='choose-language-content'><i class=\"icon-spinner icon-spin orange bigger-125\"></i> " + messages.LanguagesChooseLoadingAvailables + " ...</span>",
        closeButton: true
    });
    $.getJSON("index.php?getLanguages", function (data) {
        var items = [];
        $.each(data, function (idx, val) {
            if (idx == 'en') flag = 'gb';
            else flag = idx;
            items.push("<a onclick=\"ApplyLanguage('" + idx + "')\"><span class='flag-icon flag-icon-" + flag + "'></span> " + val + "</a>&nbsp;&nbsp;");
        });
        var select = messages.LanguagesChooseLabel + ": ";
        for (i = 0; i < items.length; i++) {
            select += items[i];
        }
        select += "</select>";
        $('#choose-language-content').html(select);
    });
}


function ApplyLanguage(lang) {
    $('#choose-language-content').html("<i class=\"icon-spinner icon-spin orange bigger-125\"></i> " + messages.LanguagesChooseApply)
    $.getJSON("index.php?setLanguage=" + lang, function (data) {
        if (data == 'OK') window.location.href = window.location.href;
    });
}


function AddForm(title, visit, esam) {
    bootbox.dialog({
        title: title,
        message: "<span id='AddForm-content'><i class=\"icon-spinner icon-spin orange bigger-125\"></i> Loading ...</span>",
        closeButton: true
    });
    $.getJSON("index.php?AddForm=" + visit + "." + esam, function (data) {
        var items = [];
        $.each(data, function (idx, val) {
            items.push("<option value='" + val.link + "'>" + val.code + "</option>");
        });
        //$('#generic-dialog').attr('title','Select Patient Code');
        //$('#generic-dialog').css('display','');
        //$("#generic-dialog").dialog('open');
        var select = "Select Patient: <select onchange=\"window.location.href=this.value\"><option></option>";
        for (i = 0; i < items.length; i++) {
            select += items[i];
        }
        select += "</select>";
        $('#AddForm-content').html(select);
    });
}

function IsNumeric(sText) {
    var ValidChars = "0123456789.";
    var IsNumber = true;
    var Char;


    for (i = 0; i < sText.length && IsNumber == true; i++) {
        Char = sText.charAt(i);
        if (ValidChars.indexOf(Char) == -1) {
            IsNumber = false;
        }
    }
    return IsNumber;

}

function createRequestObject() {
    var ro;
    var browser = navigator.appName;
    if (browser == "Microsoft Internet Explorer") {
        ro = new ActiveXObject("Microsoft.XMLHTTP");
    } else {
        ro = new XMLHttpRequest();
    }
    return ro;
}
var ritorno = true;
var http = createRequestObject();

function show_hide(id_tag) {
    if (document.getElementById(id_tag).style.display != '') document.getElementById(id_tag).style.display = '';
    else document.getElementById(id_tag).style.display = 'none';
}

function ajax_call(html_id, param) {
    if (ritorno) {
        ritorno = false;

        call = 'ajax.php?HTML_ID=' + html_id + '&' + param;
        //alert(call);
        //document.getElementById('debug').innerHTML+=document.write('<a href="'+call+'" target="_new">debug<\/a>');

        document.getElementById(html_id).innerHTML = "<img src=\"/images/loading.gif\">";
        http.open('get', call);
        http.onreadystatechange = handleResponse;
        http.send(null);
    } else {
        setTimeout('ajax_call("' + html_id + '", "' + param + '")', 10);
    }
}


function ajax_send_form(form_id) {

    ritorno = false;
    //call='ajax.php?HTML_ID='+html_id+'&'+param;
    //alert(call);
    //alert (pageHeight()+' - '+posBottom());
    if (document.getElementById('saving')) {
        var top = posBottom() - (pageHeight() / 2) - 40;
        left = (pageWidth() / 2) - 100;
        document.getElementById('saving').style.left = '' + left + 'px';
        document.getElementById('saving').style.top = '' + top + 'px';

        document.getElementById('saving').style.display = '';

    }
    //document.getElementById('debug').innerHTML+=document.write('<a href="'+call+'" target="_new">debug<\/a>');
    el = document.forms[form_id].elements;
    var str = '';
    for (i = 0; i < el.length; i++) {
        if (el[i].name != 'salva' && el[i].name != 'invia') {

            if (el[i].length > 0 && el[i].type != 'select-one') {
                //alert (i+' - '+el[i].name+' - '+el[i].type);
                for (c = 0; i < el[i].length; c++) {
                    //alert (c+' - '+el[i].name+' - '+el[i].type);
                    if (el[i][c].checked) str += el[i].name + '=' + el[i][c].value + '&';
                }
            }
            else {
                //alert (i+' - '+el[i].name+' - '+el[i].type);
                if (el[i].type == 'checkbox' || el[i].type == 'radio') {
                    //alert (i+' - '+el[i].name+' - '+el[i].type);
                    if (el[i].checked) {
                        //alert (el[i].name+' - '+el[i].value+' - '+el[i].checked);
                        str += el[i].name + '=' + el[i].value + '&';
                    }
                    else {
                        //if (el[i].type == 'checkbox') str += el[i].name + '=0&';
                    }

                }
                else str += el[i].name + '=' + encodeURIComponent(el[i].value) + '&';
            }
        }
        //alert (i+' - '+el[i].name+' - '+el[i].type);
    }
    //return false;

    url = 'index.php';
    str += '&ajax_call=yes';
    call = url + '?' + str;
    postStr=str;
    postUrl=url;
    document.getElementById('debug').innerHTML += '<a href="' + call + '" target="_new">debug<\/a>';

    http.onreadystatechange = alertContents;
    http.open('POST', url, true);

    http.setRequestHeader("Content-type", "application/x-www-form-urlencoded");
    http.setRequestHeader("Content-length", postStr.length);
    http.setRequestHeader("Connection", "close");
    http.send(postStr);
}

var postUrl;
var postStr;

function alertContents() {
    //alert(http.readyState);
    //alert(http.status);
    if (http.readyState == 4) {
        if (http.status == 200) {
            //alert(http.responseText);
            //return false;
            result = http.responseText;
            if (result.match("link_to:")) {
                resp = result.split(":");
                //if (resp[1]!='') window.location.href=resp[1];
                document.forms[0].submit();
            }
            if (result.match("Error:")) {
                resp = result.split(":");
                resp2 = resp[1].split("#error#");
                //document.getElementById('saving').style.display='none';
                //alert(resp2[0]);
                //alert(resp2[1]);
                if (resp2[1]) {
                    alert('Error:' + resp2[1]);
                } else {
                    alert('Error on field ' + resp2[0]);
                }
                errel = document.forms[0].elements[resp2[0]];
                if (errel) {
                    //if (Array.isArray(errel)){
                    if (!(typeof errel.focus !== 'undefined' && $.isFunction(errel.focus))) {
                        errel = errel[0];
                    }
                    cf();
                    errel.focus();
                    errel.select();

                }
                //else
                //document.forms[0].elements[resp2[0]][0].select();
            }
            if (result.match("Confirm:")){
            	resp=result.split(":");
            	var confirmCheck=resp[1];
            	var msg=resp[2];
            	bootbox.confirm({
            		message: msg,
            	    buttons: {
            	        confirm: {
            	            label: 'Si',
            	            className: 'btn-success'
            	        },
            	        cancel: {
            	            label: 'No',
            	            className: 'btn-danger'
            	        }
            	    },
            		callback: function(result){
            			if (result) {
            				var url=postUrl;
            				postStr+='&'+confirmCheck+'=skip';
            				http.onreadystatechange = alertContents;
            			    http.open('POST', url, true);

            			    http.setRequestHeader("Content-type", "application/x-www-form-urlencoded");
            			    http.setRequestHeader("Content-length", postStr.length);
            			    http.setRequestHeader("Connection", "close");
            			    http.send(postStr);
            			}else {
            				bootbox.hideAll();
            				return false;
            			}
            		}
            	});

            }
            /*VMAZZEO FIX ERROR_PAGE SU RICHIETA AJAX SAVE/SEND 06.10.2014*/
            var json_res = jQuery.parseJSON(result);
            if (json_res.sstatus == 'ko') {
                HideMessage();
                if (!ShowConfirm('&nbsp;<i class="fa fa-warning orange bigger-125"></i>&nbsp;<br/>' + (json_res.detail).replace(',', ', '))){
                    cf();
                }
            }
            //document.getElementById('myspan').innerHTML = result;
            //alert(result);
        } else {
            alert('There was a problem with the request.');
            cf();
        }
    }
}


function handleResponse() {
    if (http.readyState == 4) {
        var response = http.responseText;
        if (response.match("#DIV#")) {
            resp = response.split("#DIV#");
            resp[0] = resp[0].replace('\n', '');
            document.getElementById(resp[0]).innerHTML = resp[1];
        }
        ritorno = true;
    }
}

function add_value(nome, descrizione, nomeform) {
    if (!nomeform) {
        nomeform = '0'
    }
    chiamante = window.parent.opener.document.forms[nomeform];
    elementi_chiamante = chiamante.elements;
    if (elementi_chiamante[descrizione]) {
        elementi_chiamante[descrizione].value = nome;
        if (window.parent && window.parent.opener && window.parent.opener.cf)window.parent.opener.cf();
        return 0;
    }
}

function sdv_check_all(me){
    ckels = $(':checkbox');
    for(i=0;i<ckels.size();i++){
        ckels[i].checked = me.checked;
    }

    $.each($(".SDVVote"),function(a,b) {
		if ($(b).attr("target")) {
			if (me.checked) {
				$(b).removeClass("sdv_no");
				$(b).addClass("sdv_ok");
				var sdvfield = $("#" + $(b).attr("target")).attr("name");
				var notename=sdvfield.replace("SDV_FIELDS","NOTE_FIELDS");
				$("#" + $(b).attr("target")).val("1");
				$("textarea[name='" + notename+"']").val("");
			}
			else {
				$(b).removeClass("sdv_ok");
				$(b).addClass("sdv_no");
				$("#" + $(b).attr("target")).val("");
				var notename = $("#" + $(b).attr("target")).attr("name");
				// var notename=sdvfield.replace("SDV_FIELDS","NOTE_FIELDS");
				$("textarea[name='" + notename+"']").val("");
			}
		}
	});

    /*
    if(me.checked){
//        $(':checkbox').attr('checked','checked');
        $(':checkbox').checked = true;
    } else {
//        $(':checkbox').removeAttr('checked');
        $(':checkbox').checked = false;
    }
    */
    return true;
}
   
    