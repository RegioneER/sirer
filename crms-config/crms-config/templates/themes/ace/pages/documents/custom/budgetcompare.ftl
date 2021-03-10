
<#list el.getChilds() as child>
<#assign parameters=model["parameters"] />
	<#if parameters["confronto1"]+"" == child.id+"" >
		<#assign confronto1=child />
	<#elseif parameters["confronto2"]+"" == child.id+"" >	
		<#assign confronto2 = child />	
	</#if>	
</#list>
<#if (!confronto1?? || !confronto2??)>
	Budget non trovati
<#else>

	<@script>
		<#assign json1=confronto1.getElementJsonToString(userDetails) />
		<#assign json2=confronto2.getElementJsonToString(userDetails) />
		var loadedElement1=${json1};
		var loadedElement2=${json2};
		var prezzi1,prezzi2,pxp1,pxp2,pxs1,pxs2,pt1,pt2;
		
		function makeAssociative(array,property){
			var newArray={};
			$.each(array,function(i,element){
				newArray[element.metadata[property][0]]=element;
			});
			return newArray;
		}
		
		function makeAssociativePrezzo(array){
			var newArray={};
			$.each(array,function(i,element){
				newArray[element.metadata['PrezzoFinale_Prestazione'][0].id]=element;
			});
			return newArray;
		}

				
				$.each(loadedElement1.children,function(i,child){
					var type=child.type.typeId;			
					switch(type){
						case 'FolderPXPCTC':
							pxp1=makeAssociative(child.children,'Base_Nome');
						break;
						case 'FolderPXSCTC':
							pxs1=makeAssociative(child.children,'Base_Nome');
						break;
						case 'FolderPassthroughCTC':
							pt1=makeAssociative(child.children,'Base_Nome');
						break;
						case 'FolderPrezzi':
							prezzi1=makeAssociativePrezzo(child.children);
						break;
						case 'FolderTarget':
							target1=makeAssociativePrezzo(child.children);
						break;
					}
				});
				$.each(loadedElement2.children,function(i,child){
					var type=child.type.typeId;			
					switch(type){
						case 'FolderPXPCTC':
							pxp2=makeAssociative(child.children,'Base_Nome');
						break;
						case 'FolderPXSCTC':
							pxs2=makeAssociative(child.children,'Base_Nome');
						break;
						case 'FolderPassthroughCTC':
							pt2=makeAssociative(child.children,'Base_Nome');
						break;
						case 'FolderPrezzi':
							prezzi2=makeAssociativePrezzo(child.children);
						break;
						case 'FolderTarget':
							target2=makeAssociativePrezzo(child.children);
						break;
					}
				});
				
				compare(prezzi1,prezzi2);
				compare(pxp1,pxp2);
				compare(pxs1,pxs2);
				compare(pt1,pt2);
				var totali={
					"TotaleFlowchart":"Totale prestazioni da protocollo",			
					"TotalePaziente":"Totale per paziente",		
					"TotaleStudio":"Totale per studio"			
				};
				$.each(totali,function(key,identifier){
					var tp1=loadedElement1.metadata['BudgetCTC_'+key][0];
					var prezzo1=loadedElement1.metadata['BudgetCTC_'+key+'CTC'][0];
					var tp2=loadedElement2.metadata['BudgetCTC_'+key][0];
					var prezzo2=loadedElement2.metadata['BudgetCTC_'+key+'CTC'][0];
					if(prezzo1!=prezzo2 || tp1!=tp2 ){
						showDifference('Totale',identifier,tp1,tp2,prezzo1,prezzo2);
					}
				});
				
	
		
		function compare(array1,array2){
			if(array1)
			$.each(array1,function(key,element1){
				var type=getType(element1);
				var prezzo1=getPrezzo(element1,type);
				var tp1=getTp(element1,type);
				var identifier=getId(element1,type);
				if(!array2[key]){
					
					showDifference(type,identifier,tp1,"ND",prezzo1,"ND");
				}
				else{
					var element2=array2[key];
					var prezzo2=getPrezzo(element2,type);
					var tp2=getTp(element2,type);
					if(prezzo1!=prezzo2 || tp1!=tp2){
						showDifference(type,identifier,tp1,tp2,prezzo1,prezzo2);
					}
				}
			});
			if(array2)
			$.each(array2,function(key,element2){
				var type=getType(element2);
				var prezzo2=getPrezzo(element2,type);
				var tp2=getTp(element2,type);
				var identifier=getId(element2,type);
				if(!array1[key]){	
					showDifference(type,identifier,"ND",tp2,"ND",prezzo2);
				}
				
			});
			
		}
		function getType(element){
			var type=element.type.typeId;
			if(type=='PrezzoPrestazione'){
				
				switch(element.metadata['PrezzoFinale_Prestazione'][0].type.typeId){
					case 'tpxp':
						return 'tpxp';
						break;
					case 'PrestazioneXPaziente':
						return 'pxpClinico';
						break;
					case 'PrestazioneXStudio':
						return 'pxsClinico';
						break;
				}
				
			}
			else{
				switch(element.type.typeId){
					
					case 'PrestazioneXPaziente':
						return 'pxp';
						break;
					case 'PrestazioneXStudio':
						return 'pxs';
						break;
				}
			}
		}
		function getTypeDescr(type){
			
			switch(type){
				case 'tpxp':
					return 'Prestazione protocollo';
					break;
				case 'pxpClinico':
					return 'Prestazione clinica per paziente';
					break;
				case 'pxsClinico':
					return 'Prestazione clinica per studio';
					break;
				case 'pxp':
					return 'Prestazione per paziente';
					break;
				case 'pxs':
					return 'Prestazione per studio';
					break;
				default:
					return type;
					break;
			}
				
			
		}
		function getPrezzo(element, type){
			switch(type){
				case 'tpxp':
				case 'pxpClinico':
				case 'pxsClinico':
					var prezzo=element.metadata['PrezzoFinale_Prezzo'][0];
					if (!prezzo)
					prezzo=element.metadata['PrezzoFinale_Prestazione'][0].metadata['Costo_TransferPrice'];
					break;
				
				case 'pxs':	
				case 'pxp':
					var prezzo=element.metadata['Costo_Prezzo'][0];
					if (!prezzo)
					prezzo=element.metadata['Costo_TransferPrice'][0];
					break;
				
					
					
			}
			return prezzo;
		}
		function getTp(element, type){
			switch(type){
				case 'tpxp':
				case 'pxpClinico':
				case 'pxsClinico':
					
					var tp=element.metadata['PrezzoFinale_Prestazione'][0].metadata['Costo_TransferPrice'];
					break;
				
				case 'pxs':	
				case 'pxp':
					var tp=element.metadata['Costo_TransferPrice'][0];
					break;
				
					
					
			}
			return tp;
		}
		function getId(element,type){
			switch(type){
				case 'tpxp':
					var id=element.metadata['PrezzoFinale_Prestazione'][0].metadata['tp-p_TimePoint'][0].metadata['TimePoint_Descrizione'][0]+' - ' +element.metadata['PrezzoFinale_Prestazione'][0].metadata['tp-p_Prestazione'][0].metadata['Prestazioni_prestazione'][0];
					break;
				case 'pxpClinico':
				case 'pxsClinico':
					
					var id=element.metadata['PrezzoFinale_Prestazione'][0].metadata['Base_Nome'];
					break;
				
				case 'pxs':	
				case 'pxp':
					var id=element.metadata['Base_Nome'][0];
					break;				
			}
			return id;
		}
		function showDifference(type,identifier,tp1,tp2,prezzo1,prezzo2){
			if(isNaN(prezzo1)) prezzo1='ND';
			if(isNaN(prezzo2)) prezzo2='ND';
			if(isNaN(prezzo1) || isNaN(prezzo2)){
				var diff1='ND';
				var diff2='ND';
			}
			else{
			
				var diff1=prezzo2-prezzo1;
				var diff2=diff1*100/prezzo1;
				diff1=diff1.toFixed(2);
				diff2=diff2.toFixed(2);
			}
			if(prezzo1==prezzo2) return;
			type=getTypeDescr(type);
			$('#differences').append('<tr><td>'+type+'</td><td>'+identifier+'</td><td>'+prezzo1+'</td><td>'+prezzo2+'</td><td>'+diff1+'</td><td>'+diff2+'</td></tr>');
		}
	</@script> 
	
	<br>	

	<table class="table table-striped table-bordered table-hover">
	<thead><tr><th>Budget 1</th><th>Budget 2</th></tr></thead>
	<tr><td>
	
     v. <#if (confronto1.getfieldData("Budget","Versione")?size>0) >
    	 ${confronto1.getfieldData("Budget","Versione")[0]}
    	</#if><br>
    	<#if (confronto1.getfieldData("BudgetCTC","Tipologia")?size>0) >
			    	 ${getDecode("BudgetCTC","Tipologia",confronto1)}<br/>
		</#if>
    	<#if (confronto1.getfieldData("Budget","Note")?size>0) >
    	${confronto1.getfieldData("Budget","Note")[0]}
    	</#if>
	
	</td><td>
	
     v. <#if (confronto2.getfieldData("Budget","Versione")?size>0) >
    	 ${confronto2.getfieldData("Budget","Versione")[0]}
    	</#if><br>
    	<#if (confronto2.getfieldData("BudgetCTC","Tipologia")?size>0) >
			    	 ${getDecode("BudgetCTC","Tipologia",confronto2)}<br/>
		</#if>
    	<#if (confronto2.getfieldData("Budget","Note")?size>0) >
    	${confronto2.getfieldData("Budget","Note")[0]}
    	</#if>
	</td></tr>
	</table>

	<table class="table table-striped table-bordered table-hover" id='differences'>
	<thead><tr>
	<th>Tipologia</th>
	<th>Prestazione</th>
	
	<th>Prezzo budget 1</th>
	<th>Prezzo budget 2</th>
	
	<th>Differenza assoluta</th>
	<th>Differenza percentuale</th>
	</tr></thead>
	<tbody>
<tr>
<td colspan="6">Listato delle differenze trovate</td>
</tr>
	</tbody>
	</table>

</#if>  
