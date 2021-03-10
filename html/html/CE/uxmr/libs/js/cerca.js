function cerca(pattern){
	if (pattern!='') 
	{document.getElementById('pattern_cercato').innerHTML='Il testo cercato &egrave;: <b>'+pattern+'</b>';

		var tabella=document.getElementById('table1');
		var tr_elems=tabella.getElementsByTagName('TR');
		for (i=1;i<tr_elems.length;i++){
			var td_elems=tr_elems[i].cells;
			tr_elems[i].style.display='';
			trovato=false;
			for (c=0;c<td_elems.length;c++){
				cell_html = new String(td_elems[c].innerHTML);
				span_RE=new RegExp("<span>", "ig");
				span_RE_c=new RegExp("</span>", "ig");
				cell_html=cell_html.replace(span_RE, '');
				cell_html=cell_html.replace(span_RE_c, '');
				//if (!confirm(cell_html)) return false;
				cell_html=cell_html.replace(/&nbsp;/,'');
				not_tag='';
				tag='';
				tag_RE_1=new RegExp("<(.*?)>");
				tag_RE=new RegExp("<(.*?)>", "g");
				not_tag=cell_html.replace(tag_RE, " -tag- ");
				not_tag=not_tag.split(" -tag- ");
				tag_presenti=false;
				if (tag=cell_html.match(tag_RE)) tag_presenti=true;
				stringa='';
				for (nt=0;nt<not_tag.length || (tag_presenti && nt<tag.length);nt++){ 
						myRE = new RegExp(pattern, "ig");
						//if (tag && tag[nt]) if (!confirm('TAG '+nt+':'+tag[nt])) return false;	
						//if (not_tag && not_tag[nt]) if (!confirm('NOT TAG '+nt+':'+not_tag[nt])) return false;	
						if (not_tag[nt]) {
						if (str_match=not_tag[nt].match(myRE)){
							//alert (cell_html);
							for (p=0;p<str_match.length;p++) {
								//alert (str_match[p]);
								str_RE= new RegExp (str_match[p], "g");
								rem_RE= new RegExp ("<span>"+str_match[p]+"</span>", "g");
								not_tag[nt]=not_tag[nt].replace(rem_RE, str_match[p]);
								not_tag[nt]=not_tag[nt].replace(str_RE, '<span>'+str_match[p]+'</span>');
							}
							trovato=true;
						}			
					}
					if (not_tag[nt]) stringa+=not_tag[nt];
					if (tag_presenti && tag[nt]) stringa+=tag[nt];
					//if (not_tag[nt]) stringa+=not_tag[nt];
				}
				//if (!confirm(stringa)) return false;
				td_elems[c].innerHTML=stringa;	
			}
			if (pattern=='') trovato=false;
				if (trovato) {
					if (!document.forms[0].escludi.checked) tr_elems[i].bgColor='yellow'; 
					else  tr_elems[i].bgColor=''; 
				}
				else {
					tr_elems[i].bgColor=''; 
					if (document.forms[0].escludi.checked && pattern!='') tr_elems[i].style.display='none';
				}
		}
	}
		else {
			document.getElementById('pattern_cercato').innerHTML='';
			var tabella=document.getElementById('table1');
			var tr_elems=tabella.getElementsByTagName('TR');
			for (i=1;i<tr_elems.length;i++) tr_elems[i].bgColor=''; 
			
		}
	}