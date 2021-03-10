<h1>Stato indici elastic</h1>

<script>
bootbox.dialog({ 
	message: '<div class="text-center"><i class="fa fa-spin fa-spinner"></i> Caricamento in corso...</div>',
	closeButton: false,
	onEscape: false
	  });
</script>
<@script>
function formatDate(ts) {
    var dt = new Date(ts);
    var months = ['01', '02', '03', '04', '05', '06', '07', '08', '09', '10', '11', '12'];
    var days = ['Sun', 'Mon', 'Tue', 'Wed', 'Thu', 'Fri', 'Sat'];
    var curWeekDay = days[dt.getDay()];
    var curDay = dt.getDate();
    var curMonth = months[dt.getMonth()];
    var curYear = dt.getFullYear();
    if (curDay<10) curDay="0"+curDay;
    var date = curDay+"/"+curMonth+"/"+curYear; //curWeekDay+", "+
    return date;
}
function loadIndexStatus(){
	$.getJSON('${baseUrl}/app/rest/elk/idxStatus', function(data){
		var idxs={};
		for (var i=0;i<data.resultMap.lista.length;i++){
			var idx=data.resultMap.lista[i];
			if (!idxs[idx.objType]) idxs[idx.objType]={};
			if (!idxs[idx.objType][idx.idxName]) idxs[idx.objType][idx.idxName]={};
			idxs[idx.objType][idx.idxName].lastUpdateDt=idx.lastUpdateDt;
			idxs[idx.objType][idx.idxName].indexed=idx.indexed;
			idxs[idx.objType][idx.idxName].toBeUpdated=idx.toBeUpdated;
			idxs[idx.objType][idx.idxName].missing=idx.missing;
		}
		console.log(idxs);
		container=$('#idxContentTable');
		container.html("");
		for (var obj in idxs) {
		    var rowspan=0;
		    if (idxs[obj].fields) rowspan++;
		    if (idxs[obj].full) rowspan++;
		    if (idxs[obj].simple) rowspan++;
		    var trMain=$('<tr>');
		    container.append(trMain);
		    var td1=new $('<td>');
		    trMain.append(td1);
		    td1.html(obj);
		    td1.attr('rowspan',rowspan);
		    var firstRow=true;
		    
		    for (var idxType in idxs[obj]) {
			    if (!firstRow) var tr=$('<tr>');
		    	var td2=$('<td>');
		    	if (idxType=='full'){
		    		var ico=$('<i>');
		    		ico.addClass('fa fa-sitemap');
		    		td2.append(ico);
		    	}
		    	if (idxType=='fields'){
		    		var ico=$('<i>');
		    		ico.addClass('fa fa-tags');
		    		td2.append(ico);
		    	}
		    	if (idxType=='simple'){
		    		var ico=$('<i>');
		    		ico.addClass('fa fa-leaf');
		    		td2.append(ico);
		    	}
		    	td2.append('&nbsp;');
		    	td2.append(idxType);
		    	
		    	var td3=$('<td>');
		    	td3.html(formatDate(idxs[obj][idxType].lastUpdateDt));
		    	var td4=$('<td>');
		    	td4.html(idxs[obj][idxType].indexed);
		    	var td5=$('<td>');
		    	td5.html(idxs[obj][idxType].toBeUpdated);
		    	td5.append('&nbsp;');
		    	var greenCheck=$('<i>');
			    greenCheck.addClass('fa fa-check green');
			    var warning=$('<i>');
			    warning.addClass('fa fa-exclamation-triangle orange');

		    	if (idxs[obj][idxType].toBeUpdated>0){
		    		td5.append(warning);
		    	}else {
		    		td5.append(greenCheck);
		    	}
		    	var td6=$('<td>');
		    	td6.html(idxs[obj][idxType].missing);
		    	td6.append('&nbsp;');
		    	var greenCheck=$('<i>');
			    greenCheck.addClass('fa fa-check green');
			    var warning=$('<i>');
			    warning.addClass('fa fa-exclamation-triangle orange');

		    	if (idxs[obj][idxType].missing>0){
		    		td6.append(warning);
		    	}else {
		    		td6.append(greenCheck);
		    	}
		    	var td7=$('<td>');
		    	var doIndexButton=$('<button>');
		    	doIndexButton.addClass('btn btn-xs btn-info');
		    	var reload=$('<i>');
			    reload.addClass('fa fa-refresh');
		    	doIndexButton.append(reload);
		    	doIndexButton.append('&nbsp;');
		    	doIndexButton.append('Forza indicizzazione');
		    	(function(idxBtn, obj, idx){
		    		idxBtn.click(function(){
		    			bootbox.dialog({ 
							message: '<div class="text-center"><i class="fa fa-spin fa-spinner"></i> Caricamento in corso...</div>',
							closeButton: false,
							onEscape: false
						});	
						if(idx=='simple') url='${baseUrl}/app/rest/elk/index/'+obj;
						if(idx=='full') url='${baseUrl}/app/rest/elk/fullIndex/'+obj;
						if(idx=='fields') url='${baseUrl}/app/rest/elk/fieldsIndex/'+obj;
						$.getJSON(url, function(data){
							loadIndexStatus();
						});
		    		});
		    	})(doIndexButton, obj, idxType);
		    	
		    	td7.append(doIndexButton);
		    	if (firstRow) {
		    		trMain.append(td2);
		    		trMain.append(td3);
		    		trMain.append(td4);
		    		trMain.append(td5);
		    		trMain.append(td6);
		    		trMain.append(td7);
		    	}else {
		    		tr.append(td2);
		    		tr.append(td3);
		    		tr.append(td4);
		    		tr.append(td5);
		    		tr.append(td6);
		    		tr.append(td7);
		    		container.append(tr);
		    	}
		    	firstRow=false;
		    }
		    	           
		}
		bootbox.hideAll();
	});
}

loadIndexStatus();

</@script>

<div class="row">

	<div class="col-sm-12>
		
		<div class="table-responsive">
		
			<table class="table table-striped table-bordered table-hover">
				<thead>
					<tr>
						<th>Tipo oggetto</th>
						<th>Tipo indice</th>
						<th>Ultima indicizzazione</th>
						<th>Elementi indicizzati</th>
						<th>Elementi da aggiornare</th>
						<th>Elementi non indicizzati</th>
						<th>Azioni</th>					
					</tr>
				</thead>
				<tbody id='idxContentTable'>
				
				</body>
			
			</table>
			
		</div>	
	
	</div>

<div>