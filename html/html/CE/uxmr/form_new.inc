<?php 

class xml_form_new extends form_int_prototype
{

	/**
	 * Costruisce il codice html della form in compilazione
	 *
	 * @param boolean $force_open
	 * @param boolean $exclude_send_buttons
	 * @param boolean $equery
	 */
	function open_form($force_open=false,$exclude_send_buttons=false, $equery=false) {

		$in = $this->session_vars;
		$conn = $this->conn;
		$inputval = $this->tb_vals;
		$service = $this->service;
		$config_service = $this->config_service;
		

//echo "Ruolo ".$this->config_service['eQuerySpec']['Integrazione']['ROLE']."<br>";
//echo "act ".$this->session_vars['WFact']."<br>";

		$template_form_html = '';
		if ($this->xmr) {
			if ($in [$config_service ['PK_SERVICE']] != 'next') {
				if (isset ( $in ['VISITNUM'] ) && isset ( $in ['ESAM'] )) {
					$sql_query = "select visitclose from {$service}_COORDINATE where VISITNUM={$in['VISITNUM']} and ESAM={$in['ESAM']} and VISITNUM_PROGR={$in['VISITNUM_PROGR']} and {$config_service['PK_SERVICE']}='{$in[$config_service['PK_SERVICE']]}'";
					$sql = new query ( $conn );
					$sql->set_sql ( $sql_query );
					$sql->exec ();
					$sql->get_row ();
					if ($sql->row ['VISITCLOSE'] == 1 && $in ['USER_TIP'] == 'DE' && !$force_open) {
						error_page ( $in ['remote_userid'], $this->testo("visitIsClosed"), "" );
					}
				}
			}
		}
		$editing = true;
		if($this->config_service['lang']=="en")$lang=1;
		else $lang=0;
		$this->salva_js = "
		  		function salva_f(){
		  		cf();
		  		f=document.forms[0];
					el=f.elements;

					specifiche='A=ON&L=$lang&F=0';
		  		c1='';
		  		";
		$this->invia_js = "
		  		function invia_f(ajax){
		  		cf();
		  		if (ajax==undefined) ajax=true;
		  		f=document.forms[0];
					el=f.elements;
					specifiche='A=ON&L=$lang&F=0';
		  		c1='';
		  		";
		$this->check_js = '
		  		function cf(){
		  		var el;
		  		var f;
		  		f=document.forms[0];
					el=f.elements;
		  		document.forms[0].action=\'\';
		  		';
		$colonne = $this->form ['COLS'];
		$sysdate = date ( "dmY" );
		if (isset($_GET['link_to']) && $_GET['link_to']!='') $this->form ['LINK_TO']=$_GET['link_to'];
		$this->percorso_agg= "&nbsp;&gt;&nbsp;<b>" . $this->form ['TITOLO'] . "</b>";
		if ($equery){
			$sql_query="select equery_int from {$this->service}_eq where stato in (0,2) and {$this->PK_SERVICE}={$in[$this->PK_SERVICE]}";
			$sql=new query($this->conn);
			if ($sql->get_row($sql_query)) $equery_int=$sql->row['EQUERY_INT'];
			else $equery_int=0;
			if ($equery_int!='') {

				if(strtolower($this->config_service['lang'])=='en'){
					$string_text="Warning! fields with the symbol <img src=\"images/eq_img.png\" width=20px> has been modified";
				}else{
					$string_text="Attenzione! i campi contrassegnati con il simbolo <img src=\"images/eq_img.png\" width=20px> hanno subito modifiche";
				}

				$note_eq="
				<div style='font-align:center;color:red;font-weight:bold'>
				$string_text
				</div>
				";
			}
		}
		$this->body = $note_eq.'
					   <form method="post" class="niceform" action="index.php" enctype="multipart/form-data"  onsubmit="return false;" onKeypress="if (event.keyCode==13) return false;">
		               <input type="hidden" name="' . $this->form ['TABLE'] . '"/>
		               <input type="hidden" name="form" value="' . $in ['form'] . '"/>
		               <input type="hidden" name="link_to" value="' . $this->form ['LINK_TO'] . '"/>
		               <table align="center" border="0" cellpadding="2" cellspacing="2" width="98%">
									  <tbody>
									  	<tr>
									  		<td>
									 ';

		$width = 100 / ($colonne * 2);
		if ($this->form ['TEMPLATE'] != '' && $in ['genera_template_html'] != "si")
		$template = file_get_contents ( "xml/{$this->form['TEMPLATE']}" );
		else {
			$this->body .= '
			       				 <table class="sf" align="center" border="0" cellpadding="2" cellspacing="2" width="100%"><tr>
			       				 <!-- CAMPI -->' . $testo_rev;
			$template_form_html = '
				<table class="sf" align="center" border="0" cellpadding="2" cellspacing="2" width="100%"><tr>
			       				 <!-- CAMPI -->';
			$template = '';
			for($i = 0; $i < $colonne; $i ++) {
				$this->body .= "<td width=\"" . $width . "%\">&nbsp;</td><td width=\"" . $width . "%\">&nbsp;</td>";
				$template_form_html .= "<td width=\"" . $width . "%\">&nbsp;</td><td width=\"" . $width . "%\">&nbsp;</td>";
			}
			$this->body .= "</tr>";
			$template_form_html .= "</tr>";

		}

		$c = 0;
		foreach ( $this->fields as $i => $val ) {
			if ($val ['CONDITION'] != '')
			$condition_array [count ( $condition_array )] = $val ['CONDITION'];
			if($val ['TYPE']=="file_doc") {
				$file_doc_eq['VAR']=$val['VAR'];
				$file_doc_eq['THREAD']=$val['THREAD'];
				$file_doc_eq['TOPIC']=$val['TOPIC'];
				$files_doc[]=$file_doc_eq;
				/*
			        [TYPE] => file_doc
				    [VAR] => COMUNICAZIONI_FILE
				    [THREAD] => Comunicazione
				    [TOPIC] => Communications to AIFA
				 */
			}
		}
		$condition_array = array_unique ( $condition_array );
		
		if ($equery){
			
			if($equery_int!="" || $equery_int!="0") {

			$_GET['VISITNUM_PROGR']-=0;

			if(isset($_GET['PROGR'])) $progr=$_GET['PROGR'];
			else $progr=1;

			$sql_query="select * from {$this->service}_eqfield where
				eq_int=$equery_int
				and esam={$_GET['ESAM']}
				and visitnum={$_GET['VISITNUM']}
				and visitnum_progr={$_GET['VISITNUM_PROGR']}
				and progr=$progr
				and {$this->PK_SERVICE}={$_GET[$this->PK_SERVICE]}
				";

//			echo( $equery_int."<br>");
			$sql->exec($sql_query);
			
			//------------------------------------
			$id_tipo_ref=$config_service['PRJ']*100000+$_GET[$this->PK_SERVICE];
			
//			print_r($files_doc);

			foreach($files_doc as $l=>$allegati) {
			
			$topic=preg_replace("/'/", "''", $allegati['TOPIC']);
			if ($topic!='') $topic_where="topic='$topic'";
			else $topic_where="topic is null";	
				
			$thread=$allegati['THREAD'];
			$thread=preg_replace("/'/", "''", $thread);

			$thread=str_replace("à","%",$thread);
			$thread=str_replace("è","%",$thread);
			$thread=str_replace("ì","%",$thread);
			$thread=str_replace("ò","%",$thread);
			$thread=str_replace("ù","%",$thread);
			$bind_array['TITOLO']=$thread;
			//PENULTIMO!!!
			$sql_query="
				select
				   d.id,
			       d.titolo as titolo,
			       d.autore,
			       d.data,
			       d.keywords as keywords,
			        (select
			            NOME_FILE
			           from docs d1
			        	where d1.tipo_doc='Doc_Area'
			        	and d1.id_tipo_ref='{$id_tipo_ref}'
			        	and d1.id=
			         		(select max(d2.id) from docs d2
			         			where d2.tipo_doc='Doc_Area'
			        and d2.id_tipo_ref='{$id_tipo_ref}'
			        and d2.id_ref=d.id and d2.id<(select
			          max(d99.id)
			           from docs d99
			        where d99.tipo_doc='Doc_Area'
			        and d99.id_tipo_ref='{$id_tipo_ref}'
			        and d99.id_ref=d.id
			        ))
			        ) as nome_file,
			       (
			        select
			          max(d3.id)
			           from docs d3
			        where d3.tipo_doc='Doc_Area' and d3.id_tipo_ref='{$id_tipo_ref}' and d3.id_ref=d.id and d3.id<(select
			          max(d99.id)
			           from docs d99
			        where d99.tipo_doc='Doc_Area'
			        and d99.id_tipo_ref='{$id_tipo_ref}'
			        and d99.id_ref=d.id
			        )
			        ) as last_ver
	
			        from docs d
			        where
			        	tipo_doc='Doc_Area'
			        	and id_tipo_ref='{$id_tipo_ref}'
			        	and id=id_ref
			        	and $topic_where
						and d.titolo like :TITOLO
					";
//			echo( "<br>".$sql_query."<br>");
			$sql2=new query($this->conn);
			$sql2->exec($sql_query, $bind_array);
			$sql2->get_row();
			//piccolo trick per i documenti allegati
			foreach($files_doc as $key => $val) {
				if($sql2->row['KEYWORDS']==$val['VAR']) {
					$this->old_values[$val['VAR']]=$sql2->row['LAST_VER'];
					$this->old_values_docs_nomi[$val['VAR']]=$sql2->row['NOME_FILE'];
				}
			}
			
			} //chiudo qua foreach $c
			//------------------------------------
			}
			
			foreach ($this->tb_vals as $k=>$v) $this->old_values[$k]=$v;

			while ($sql->get_row()){
				$this->tb_vals[$sql->row['FIELD']]=$sql->row['VALORE'];
			}
		}
		foreach ( $this->fields as $i => $val ) {
			if (isset ( $val ['TYPE'] ) && $val ['TYPE'] != '')
			$field_type = "field_{$val['TYPE']}";
			else
			$field_type = "field";
			if ($this->config_service['field_lib'] != '' && file_exists ( $this->config_service['field_lib'] . $field_type . ".inc" )) {
				include_once $this->config_service['field_lib'] . $field_type . ".inc";
			} else
			include_once "{$field_type}.inc";
			$field_obj = new $field_type ( $this, $i, $this->conn, $this->tb_vals, $this->session_vars, $this->service, $this->errors );
			if (isset($condition_array) && is_array($condition_array)) foreach ( $condition_array as $key => $val ) {
				if ($val == $field_obj->id)
				$field_obj->attributes ['CALL_CF'] = "yes";
			}
			if ($inputval [$this->form ['READONLY']] == 1 && $inputval [$field_obj->id] != '') {

				if ($field_obj->id != $this->form ['READONLY_COMM']) {

					$field_obj->attributes ['DISABLED'] = 'yes';
				}
			}
			$field_obj->make_open_html ($equery);
			if ($template == '') {
				if ($field_obj->attributes ['HIDE'] == 'yes') {
					if (isset ( $field_obj->attributes ['NAME'] ) && $field_obj->attributes ['NAME'] != '') {
						$template_form_html .= "</tr>\n<tr id='tr_{$field_obj->attributes['NAME']}'>";
						$this->body .= "</tr>\n<tr id='tr_{$field_obj->attributes['NAME']}'>";
					} else {
						$template_form_html .= "\n<tr id='tr_{$field_obj->attributes['VAR']}'>";
						$this->body .= "\n<tr id='tr_{$field_obj->attributes['VAR']}'>";
					}
					$c = 0;
				}

				if ($colonne == $c) {
					$template_form_html .= "</tr>\n";
					$this->body .= "</tr>\n";
					$c = 0;
				}
				if ($c == 0 && $field_type != 'field_hidden' && $field_obj->attributes ['HIDE'] != 'yes') {
					$this->body .= "<tr>";
					$template_form_html .= "<tr>";
				}
				#echo $c;
				if ($field_obj->attributes ['TYPE'] != 'hidden') {
					if ($field_obj->attributes ['COLS'] == '')
					$c ++;
					else {
						$c += $field_obj->attributes ['COLS'];

					}
				}
				if ($field_obj->attributes ['COLS'] == '')
				$field_obj->attributes ['COLS'] = 1;
				if ($field_obj->attributes ['COLSPAN'] == '')
				$field_obj->attributes ['COLSPAN'] = 1;
				$colspan = $field_obj->attributes ['COLS'] * $field_obj->attributes ['COLSPAN'];
				if ($field_obj->attributes ['TYPE'] != '') {
					if ($field_obj->attributes ['COLSPAN'] == 1) {
						if ($field_obj->attributes ['TYPE'] == 'hidden') {

							$template_form_html .= "<<{$field_obj->id}>>";
						} else
						$template_form_html .= "
				<td  class='destra' colspan=\"$colspan\" id=\"cell_{$field_obj->id}\"><<TESTO {$field_obj->id}>></td>
				<td  class='input' colspan=\"$colspan\" id=\"cell_input_{$field_obj->id}\"><<{$field_obj->id}>></td>
				";
					} else {
						if ($field_obj->attributes ['TYPE'] == 'hidden')
						$template_form_html .= "<<{$field_obj->id}>>";
						else
						$template_form_html .= "
					<td  class='input' colspan=\"$colspan\" id=\"cell_input_{$field_obj->id}\"><<TESTO {$field_obj->id}>><<{$field_obj->id}>></td>
					";
					}
				} else
				$template_form_html .= "\n" . $field_obj->html;

				$this->body .= "\n" . $field_obj->html;
			} else {
				$template = str_replace ( "<<{$field_obj->id}>>", $field_obj->input_field, $template );
				$template = str_replace ( "<<TESTO {$field_obj->id}>>", $field_obj->input_txt, $template );
			}
			$this->salva_js .= $field_obj->salva_js;
			$this->check_js .= $field_obj->check_js;
			$this->invia_js .= $field_obj->invia_js;
			$this->script_js .= $field_obj->script;
			if (! $field_obj->validata)
			$this->validata = $field_obj->validata;
			$controlli .= $field_obj->controlli;
		}
		$js_function_on_send = $this->form ['JS_FUNCTION'];
		if ($this->form ['JS_ONSAVE'] == "yes")
		$js_function_on_save = $this->form ['JS_FUNCTION'];
		else
		$js_function_on_save = $this->form ['JS_ONSAVE'];
		$js_function_on_load = $this->form ['LOAD'];
		if ($template == '') {
			$this->body .= "
		  <!--FINE CAMPI-->
		  ";
			$template_form_html .= "
			<!--FINE CAMPI-->
			</table>
			";
		}
		if ($in ['genera_template_html'] == "si") {
			die ( $template_form_html );
		}
		$this->onload = $js_function_on_load;
		$this->onload .= 'cf()';
		$this->check_js .= '
		  }';
		if($this->config_service['jquery']) $this->check_js .= '$(document).ready(function(){'.$this->script_js."
		});
		  ";
		$this->salva_js .= '
		  rc=contr(c1,specifiche);
			if (rc) {return false}
			' . $controlli . '
		  if (!rc){
		  ' . $js_function_on_save . '
		   document.forms[0].INVIOCO.value=\'0\';
		   document.forms[0].action=\'index.php\';
		    el=document.getElementsByTagName(\'TR\')
		   for (i=0;i<el.length;i++) el[i].style.display=\'\';
		   f=document.forms[0];
			 el=f.elements;
		   for (i=0;i<el.length;i++) el[i].disabled=false;
		   ajax_send_form(0);

		   }
		  }';
		  if($this->config_service['jquery2'])$contr="jContr";
		  else $contr="contr";
		$this->invia_js .= '
		   rc='.$contr.'(c1,specifiche);
				if (rc) {return false}
		   ' . $controlli . '
		   if (!rc){
			   ' . $js_function_on_send . '
			   document.forms[0].INVIOCO.value=\'1\';
			   document.forms[0].action=\'index.php\';
			    el=document.getElementsByTagName(\'TR\')
		   		for (i=0;i<el.length;i++) el[i].style.display=\'\';
			   f=document.forms[0];
				 el=f.elements;
			   for (i=0;i<el.length;i++) el[i].disabled=false;
			   if (document.forms[0].EQUERY_INT) {
			   	document.forms[0].submit();
			   		return;
				}
			   if (ajax) ajax_send_form(0);
			   else document.forms[0].submit();
			  }
		  }';
		if ($template == '')
		$this->body .= '</table><p align=center>';
		else
		$this->body .= $template . "<p align=center>";
		if (isset ( $in ['eform'] ) && $in ['USER_TIP'] != 'DM')
		$this->body .= '
		  <input type="submit" value="Vai alla form" name="equery" onclick="window.location.href=\'index.php?equery&amp;VISITNUM=\'+document.forms[0].VISITNUM.value+\'&amp;ESAM=\'+document.forms[0].VISITNUM.value+\'&amp;{$this->PK_SERVICE}=\'+document.forms[0].{$this->PK_SERVICE}.value+\'&amp;CENTER=\'+document.forms[0].CENTER.value+\'&amp;QUESTION=\'+document.forms[0].QUESTION.value+\'&amp;PROGR=\'+document.forms[0].PROGR.value;"/>
		  ';
		if ($equery){

			if(strtolower($this->config_service['lang'])=='en'){
					$integra_button_text="Integrate eQuery";
			}else{
					$integra_button_text="Integra Scheda";
			}

			$this->body .= '
			<input type="hidden" value="'.$equery_int.'" name="EQUERY_INT">
		  	<input type="submit" value="'.$integra_button_text.'" name="salva" onclick="invia_f();"/>';
			$exclude_send_buttons=true;
		}
		if(!$exclude_send_buttons){
			if ($this->buttons ['SALVA'] && ($in ['USER_TIP'] != 'DM' || isset ( $in ['eform'] )))
			$this->body .= '
		  	<input type="submit" value="' . $this->buttons ['SALVA'] . '" name="salva" onclick="salva_f();"/>';
			if ($this->buttons ['SUBMIT'] != '')
			$this->body .= '
		  	<input type="submit" value="' . $this->buttons ['SUBMIT'] . '" onclick="submit();"/>';

			/*else {
			 $this->body.='
			 <input type="hidden" value="1" name="eQuery_Integrazione_Send_">
			 <input type="submit" value="Salva Modifiche" name="eQuery_Integrazione_Send" onclick="invia_f(false);"/>';
			 }*/

			if ($this->buttons ['INVIA'] && $in ['USER_TIP'] != 'DM' || (isset ( $in ['FORM'] ) || isset ( $in ['SEARCH'] )))
			$this->body .= '
		  <input type="submit" value="' . $this->buttons ['INVIA'] . '" name="invia" onclick="invia_f();"/>';
			if ($in ['USER_TIP'] == 'DM' && ! isset ( $in ['FORM'] ) && ! isset ( $in ['SEARCH'] )) {
				$sql = new query ( $conn );
				global $PROGR;

				$query = "select id , to_char(quest_dt,'DD/MM/YYYY') as data from {$this->config_service['service_root']}_equery where visitnum='{$in['VISITNUM']}' and esam='{$in['ESAM']}' and progr='$PROGR' and {$this->PK_SERVICE}='{$in[$this->PK_SERVICE]}' and validata is null --and to_be_validate=1";
				// echo $query;
				$sql->set_sql ( $query );
				$sql->exec ();
				while ( $sql->get_row () ) {
					$equery_option .= "<option value=\"{$sql->row['ID']}\">Equery number {$sql->row['ID']} Equery data {$sql->row['DATA']}</option>";
				}
				if($this->config_service['lang']=="en") {
					$reason="Reason for change:";
					$send="Send";
					$opt1="Documentation of change";
					$opt2="Data entry error";
					$alert_msg="WARNING!!! It\\'s necessary to choose a reason for the revision";
				} else {
					$reason="Motivo della modifica:";
					$send="Procedi";
					$opt1="Documentazione di cambiamento";
					$opt2="Errore inserimento dati";
					$alert_msg="ATTENZIONE!!! E\\' necessario scegliere un motivo della modifica";
				}

				$this->body .= "$reason
		  		<select name='ID_QUERY'>
		  			<option></option>
						<OPTION VALUE=\"-2\">$opt1</option>
						<OPTION VALUE=\"-1\">$opt2</option>
						$equery_option
		  		</select><br/>
		  		<input type=\"submit\" value=\"$send\" name=\"invia_dm\" onclick=\"
		  			if (document.forms[0].ID_QUERY.value!='') invia_f();
		  			else {alert ('$alert_msg');document.forms[0].ID_QUERY.focus(); return false;}
		  			\"/>
		  	";
		}
		if ($this->buttons ['ANNULLA'])
		$this->body .= '
		  <input type="reset" value="' . $this->buttons ['ANNULLA'] . '" name="annulla" onclick="resetForm();return false;" />';
		if ($this->buttons ['CANCELLA'])
		$this->body .= '
		  <input type="button" value="' . $this->buttons ['CANCELLA'] . '" name="cancella" onclick="resetForm();return false;" />';
		}
		//*****
		//modifica in revisione all'azienda 9/9/10
		if ($this->buttons ['INREVISIONE'] && $in ['USER_TIP'] != 'DM' && !$equery ) {
			$this->body .= '
		  	<br /><input type="submit" value="' . $this->buttons ['INREVISIONE'] . '" name="inrevisione" style="color:red;" onclick="salva_f();document.forms[0].INREV.value=1;"/>';
		}
		//*****
		$this->body .= '</p></table>';
		if(!$exclude_send_buttons) $this->body .= '</form>';
		$config_service=$this->config_service;
		if ($config_service ['PK_SERVICE'] == '')
		$this->PK_SERVICE = 'CODPAT';
		else
		$this->PK_SERVICE = $config_service ['PK_SERVICE'];
		global $vlist;
		if (!isset($in['SEARCH']) && $in [$this->PK_SERVICE] != '' && ! isset ( $vlist->esams [$in ['VISITNUM']] [$in ['ESAM']] ['ALL_IN'] ) && !$exclude_send_buttons) {
			if($this->form['NO_JS_BACK']=="") $history="onclick=\"history.back(); return false;\"";
			$this->body .= '
		  <p align=left><a href="index.php?exams=visite_exams.xml&amp;CENTER=' . $in ['CENTER'] . '&amp;' . $this->PK_SERVICE . '=' . $in [$this->PK_SERVICE].'&VISITNUM='.$in ['VISITNUM'].'" '.$history.'>&lt;&lt;' . $config_service ['Torna_lista_schede'] . '</a></p>';
		}
		$href_alternativo = "index.php?CENTER=" . $in ['CENTER'] . "&{$this->PK_SERVICE}=" . $in [$this->PK_SERVICE] . "&VISITNUM=" . $in ['VISITNUM'] . "&ESAM=" . $in ['ESAM'] . "&PROGR=" . $in ['PROGR'] . "&DOWN=1";
		$this->body = preg_replace ( "/#HREF#/", $href_alternativo, $this->body );
	}

}

?>