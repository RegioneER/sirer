<?
/**
 * @package FileAllegati
 */
include_once "field.inc";

class field_file_doc extends field {

	var $input_field_rev;
	var $id_rev;

	function gestDelete($conn=null){
        $in=null; //TODO: mi sembra errore!!!
        $agg_progr=null;
		global $xml_dir;
		if (!isset($conn)) $conn=$this->conn;
		if (isset($this->xml_form->config_service['PRJ']))
		$id_area = $in [$this->xml_form->config_service['PK_SERVICE']] + (100000*$this->xml_form->config_service['PRJ']);
		else $id_area = $in [$this->xml_form->config_service['PK_SERVICE']] + 100000;
		if ($this->db_vars['VISITNUM_PROGR']>0) $this->agg_progr="_".$this->db_vars['PROGR']."_".$this->db_vars['VISITNUM_PROGR'];
		else if ($this->db_vars['PROGR']>1) $this->agg_progr="_".$this->db_vars['PROGR'];
		$sql_update_docs="update docs set tipo_doc='Trash' where id_tipo_ref={$id_area} and keywords='".$this->id.$agg_progr."'";
		$sql=new query($conn);
		$sql->ins_upd($sql_update_docs);
		return;
	}
	
	function gestChangeProgr($conn, $fromProgr){
        $in=null; //TODO: mi sembra errore!!!
		global $xml_dir;
		$sql=new query($conn);
		Logger::send(__CLASS__." - gestChangeProgr");
		if (!isset($conn)) $conn=$this->conn;
		if (isset($this->xml_form->config_service['PRJ']))
		$id_area = $in [$this->xml_form->config_service['PK_SERVICE']] + (100000*$this->xml_form->config_service['PRJ']);
		else $id_area = $in [$this->xml_form->config_service['PK_SERVICE']] + 100000;
		if ($this->db_vars['VISITNUM_PROGR']>0) $agg_progr="_".$this->db_vars['PROGR']."_".$this->db_vars['VISITNUM_PROGR'];
		else if ($this->db_vars['PROGR']>1) $agg_progr="_".$this->db_vars['PROGR'];
		$sql_update_docs="update docs set tipo_doc='Trash' where id_tipo_ref={$id_area} and keywords='".$this->id.$agg_progr."'";
		Logger::send($sql_update_docs);
		$sql->ins_upd($sql_update_docs);
		$bind['pk_service'] = $this->db_vars[$this->config_service['PK_SERVICE']];
		$bind['visitnum'] = $this->db_vars['VISITNUM'];
		$bind['visitnum_progr'] = $this->db_vars['VISITNUM_PROGR'];
		$bind['esam'] = $this->db_vars['ESAM'];
		$bind['progr'] = $this->db_vars['PROGR'];
		$sql_query="select visitnum_progr, progr from {$this->xml_form->form['TABLE']} where {$this->config_service['PK_SERVICE']}=:pk_service and
							VISITNUM=:visitnum and
										VISITNUM_PROGR=:visitnum_progr and 
										ESAM=:esam and 
										PROGR>:progr";
		Logger::send($sql_query);
		Logger::send($bind);
		$sql->exec($sql_query, $bind);
		while ($sql->get_row()){
			if ($sql->row['VISITNUM_PROGR']>0) {
				$progr_orig=$sql->row['PROGR'];
				$progr_dest=$progr_orig-1;
				$keywords_orig=$this->id."_".$progr_orig."_".$sql->row['VISITNUM_PROGR'];
				$keywords_dest=$this->id."_".$progr_dest."_".$sql->row['VISITNUM_PROGR'];
				$sql_update_docs_[]="update docs set keywords='$keywords_dest' where keywords='$keywords_orig' and id_tipo_ref={$id_area} and tipo_doc='Doc_Area'";
			}
			else if ($sql->row['PROGR']>1){
				$progr_orig=$sql->row['PROGR'];
				$progr_dest=$progr_orig-1;
				$keywords_orig=$this->id."_".$progr_orig;
				$keywords_dest=$this->id."_".$progr_dest;
				$sql_update_docs_[]="update docs set keywords='$keywords_dest' where keywords='$keywords_orig' and id_tipo_ref={$id_area} and tipo_doc='Doc_Area'";
			}
	
		}
		foreach ($sql_update_docs_ as $key=>$val){
			Logger::send($val);
			$sql->ins_upd($val);
		}
		Logger::send("FINE: ".__CLASS__." - gestChangeProgr");
		return;
	}
	
	function open_($value) {
		global $in;
//		global $inputval;


		$inputval=$this->db_vars;
		$txt = $this->testo;

		if ($this->attributes ['EXT_ALLOWED'] != '')
			$txt .= "<br><font color=red>Attenzione: si prega di allegare solo file in formato {$this->attributes['EXT_ALLOWED']}</font>"; else
			$txt .= "<br><font color=red>Attenzione: si prega di allegare solo file in formato word, PDF e TIFF (per le immagini)</font>";
		$this->input_txt = $txt . ":<br>";
		if (isset($this->xml_form->config_service['PRJ']))
		$id_area = $in [$this->xml_form->config_service['PK_SERVICE']] + (100000*$this->xml_form->config_service['PRJ']);
		else $id_area = $in [$this->xml_form->config_service['PK_SERVICE']] + 100000;

		$topic = $this->attributes ['TOPIC'];
		$thread = $this->attributes ['THREAD'];

		$topic = preg_replace ( "/\[(.*?)\]/e", "var_glob('\\1')", $topic );
		$thread = preg_replace ( "/\[(.*?)\]/e", "var_glob('\\1')", $thread );
		global $config_service;
		$display = '';
		if (isset ( $config_service ['FILE_DOC_NA'] ) && $config_service ['FILE_DOC_NA']) {
			if ($inputval ["{$this->id}_FD_CK"] == 1)
				$display = "none";
		}
		if ($_GET['PROGR']>1) {
			$i=$_GET['PROGR'];
			$agg_progr="_".$_GET['PROGR'];
		}
		if ($_POST['PROGR']>1) {
			$i=$_POST['PROGR'];
			$agg_progr="_".$_GET['PROGR'];
		}
		
//		if ($this->attributes['BYTB']!='') $this->fields_value_bytb($this->attributes['BYTB']);
//		//EDO high experimental
//		if($this->id_bytd!="") {
//			$progr_1=$_GET['PROGR']-1;
//			$agg_progr="_".$progr_1;
//		}

		//MODIFICA PER PERMETTERE DI USARE I + DENTRO GLI ATTRIBUTI
		$thread=preg_replace("/\+/","%2B",$thread);
		$topic=preg_replace("/\+/","%2B",$topic);

		$this->input_field = "
		<iframe id='{$this->id}_file_doc' style=\"display:$display;width:500px\"
		frameborder=\"no\"
		src=\"WCA/index.php?AF=1&tab=3&id_area=$id_area&thread={$thread}&keywords={$this->id}{$agg_progr}&topic={$topic}\"
		width=\"100%\"
		height=\"150\"
		>Contenuto alternativo per i browser che non leggono gli iframe.
		</iframe>
		";
		/*
		if ($i>1){
			$keyword="{$this->id}_{$i}";
		$where_agg=" and keywords='{$this->id}_{$i}'";
		$agg_progr="_{$i}";
		}else {
			$keyword="{$this->id}";
			$where_agg=" and keywords='{$this->id}'";
		}
		
		
		$sql_query="
		select * from docs where id=(
		select max(id) from docs
		where id_tipo_ref=$id_area and topic='$topic' and titolo = '$thread'
		$where_agg
		)";
		$sql=new query($this->xml_form->conn);
		$sql->get_row($sql_query);
		$this->input_field="
		<a id=\"{$keyword}_link\" href=\"WCA/download.php?id={$sql->row['ID']}\">{$sql->row['NOME_FILE']}</a>
		<br/><div id=\"{$keyword}_new\" style=\"z-index:2;position:absolute;background-color:white;border:2px solid;display:none;\"></div>
		<input type='button' onclick=\"
		if (document.getElementById('{$keyword}_new')){
					var top=posBottom()-(pageHeight()/2)-40;
					left=(pageWidth()/2)-100;
					document.getElementById('{$keyword}_new').style.left=''+left+'px';
					document.getElementById('{$keyword}_new').style.top=''+top+'px';
					document.getElementById('{$keyword}_new').style.display='';
					document.getElementById('{$keyword}_new').innerHTML='<iframe id=\'{$keyword}_file_doc\' style=\'display:$display;width:400px\' frameborder=\'no\' src=\'WCA/index.php?AF=1&tab=3&id_area=$id_area&thread={$thread}&keywords={$this->id}{$agg_progr}&topic={$topic}\' width=\'100%\' height=\'120\'>Contenuto alternativo per i browser che non leggono gli iframe.</iframe>';
		}
		\" value=\"Allega file\">
		";
*/
		/*
		$this->input_field="
		<span id='{$this->id}_file_id'></span>
		<a href=\"#\" onclick=\"
		ajax_file_call('ajaxUpload','id_tipo_ref=$id_area&titolo=$thread&keywords={$this->id}&topic={$topic}');
		return false;\">Carica nuovo file</a>
		";
*/
		if (isset ( $config_service ['FILE_DOC_NA'] ) && $config_service ['FILE_DOC_NA']) {
			if ($inputval ["{$this->id}_FD_CK"] == 1)
				$checked = "checked"; else
				$checked = "";
				//echo "<li>{$this->id} - {$inputval["{$this->id}_FD_CK"]}</li>";
			$this->input_field .= "
			<input type='checkbox' $checked name='{$this->id}_FD_CK' value=\"1\" onclick=\"
			if (this.checked) document.getElementById('{$this->id}_file_doc').style.display='none';
			else document.getElementById('{$this->id}_file_doc').style.display='';
		\">Non applicabile
		";
		}

	}

	function open_send() {
		global $insert_errors;
		global $conn;
		global $in;
		global $inputval;
		$thread = $this->attributes ['THREAD'];
		
		if ($in ['INVIOCO'] == 1) {
			if (isset ( $this->attributes ['CONDITION'] ) && $this->attributes ['CONDITION'] != '') {
				$conds_var = split ( ",", $this->attributes ['CONDITION'] );
				$conds_val = split ( ",", $this->attributes ['CONDITION_VALUE'] );
				$this->condition_passed = true;
				foreach ( $conds_var as $key => $var ) {
					$val = $conds_val [$key];
					if ($in [$var] != $val) {
						$this->condition_passed = false;
					}
				}
			}

			global $config_service;
			if ($this->condition_passed && isset ( $config_service ['FILE_DOC_NA'] ) && $config_service ['FILE_DOC_NA']) {
				if ($inputval ["{$this->id}_FD_CK"] == '1' || $in ["{$this->id}_FD_CK"] == '1'){
					$this->validata=true;
					return;
				}
			}

			$id_tipo_ref = 100000 + $in [$this->xml_form->config_service['PK_SERVICE']];
			if (isset($this->xml_form->config_service['PRJ']))
			$id_tipo_ref = $in [$this->xml_form->config_service['PK_SERVICE']] + (100000*$this->xml_form->config_service['PRJ']);
			if ($_GET['PROGR']>1) $agg_progr="_".$_GET['PROGR'];
			if ($_POST['PROGR']>1) $agg_progr="_".$_GET['PROGR'];
			$sql_query = "select count(*) as conto from docs where KEYWORDS=:keywords and id_tipo_ref=:id_tipo_ref";
			//echo $sql_query;
			unset($bind);
			$bind['KEYWORDS']="{$this->id}{$agg_progr}";
			$bind['ID_TIPO_REF']=$id_tipo_ref;
			$sql = new query ( $conn );
			//$sql->set_sql ( $sql_query );
			$sql->exec ($sql_query,$bind);//binded
			$sql->get_row ();
			if ($sql->row ['CONTO'] == 0 && $this->condition_passed) {
				$this->validata = false;
				$insert_errors [$this->id] = "Allegare file $thread";
			}
		}
	}

	function open_save() {
		global $insert_errors;
		global $conn;
		global $in;
		$thread = $this->attributes ['THREAD'];
		if ($in ['INVIOCO'] == 0) {
			if (isset ( $this->attributes ['CONDITION'] ) && $this->attributes ['CONDITION'] != '') {
				$conds_var = split ( ",", $this->attributes ['CONDITION'] );
				$conds_val = split ( ",", $this->attributes ['CONDITION_VALUE'] );
				$this->condition_passed = true;
				foreach ( $conds_var as $key => $var ) {
					$val = $conds_val [$key];
					if ($in [$var] != $val) {
						$this->condition_passed = false;
					}
				}
			}
			$id_tipo_ref = 100000 + $in [$this->xml_form->config_service['PK_SERVICE']];
			if (isset($this->xml_form->config_service['PRJ']))
			$id_tipo_ref = $in [$this->xml_form->config_service['PK_SERVICE']] + (100000*$this->xml_form->config_service['PRJ']);
			if ($_GET['PROGR']>1) $agg_progr="_".$_GET['PROGR'];
			if ($_POST['PROGR']>1) $agg_progr="_".$_GET['PROGR'];
			$sql_query = "select count(*) as conto from docs where KEYWORDS=:keywords and id_tipo_ref=:id_tipo_ref";
			unset($bind);
			$bind['KEYWORDS']="{$this->id}{$agg_progr}";
			$bind['ID_TIPO_REF']=$id_tipo_ref;
			$sql = new query ( $conn );
			//$sql->set_sql ( $sql_query );
			$sql->exec ($sql_query,$bind);//binded
			$sql->get_row ();
			if ($sql->row ['CONTO'] == 0 && $this->condition_passed)
				$insert_errors [$this->id] = "Allegare file $thread";
		}
	}

	function close_OLD($value) {
		global $in;
		global $inputval;
		$txt = $this->testo;

		$this->input_txt = $txt . ":<br>";
		//$id_area = $in ['ID_PRAT'] + 100000;
		//nuova tecnica per mettere suffisso alle id dei doc WCA
		if (isset($this->xml_form->config_service['PRJ']))
		$id_area = $in [$this->xml_form->config_service['PK_SERVICE']] + (100000*$this->xml_form->config_service['PRJ']);
		else $id_area = $in [$this->xml_form->config_service['PK_SERVICE']] + 100000;
		$topic = $this->attributes ['TOPIC'];
		$thread = $this->attributes ['THREAD'];
		$topic = preg_replace ( "/\[(.*?)\]/e", "var_glob('\\1')", $topic );
		$thread = preg_replace ( "/\[(.*?)\]/e", "var_glob('\\1')", $thread );
		global $config_service;
		$display = '';
		if (isset ( $config_service ['FILE_DOC_NA'] ) && $config_service ['FILE_DOC_NA']) {
			if ($inputval ["{$this->id}_FD_CK"] == 1) {
				$this->input_field = "<img src=\"/images/checkedcheck.gif\">Non applicabile";
				return;
			}
		}
		if ($_GET['PROGR']>1) $agg_progr="_".$_GET['PROGR'];
		if ($_POST['PROGR']>1) $agg_progr="_".$_GET['PROGR'];
		$this->input_field = "
		<iframe
		frameborder=\"no\"
		src=\"WCA/index.php?AF=2&tab=3&id_area=$id_area&thread={$thread}&keywords={$this->id}{$agg_progr}&topic={$topic}\"
		width=\"100%\"
		height=\"90\"
		>Vedi File Allegato
		</iframe>
		";

//		$sql_query = "select * from docs where id_tipo_ref=$id_area and approved is not null and keywords='{$this->id}{$agg_progr}'";
//		echo $sql_query."<br>";
//		$sql = new query ( $this->conn );
//		$sql->set_sql ( $sql_query );
//		$sql->exec ();//commentata
//		$sql->get_row ();
//		if($sql->numrows>0) {
//			$this->input_field_rev = "
//			<iframe
//			frameborder=\"no\"
//			src=\"WCA/index.php?AF=2&tab=3&id_area=$id_area&thread={$thread}&id={$sql->row['ID']}{$agg_progr}&topic={$topic}\"
//			width=\"100%\"
//			height=\"90\"
//			>Vedi File Allegato
//			</iframe>
//			";
//		}
	}
	
	function close_($value) {
		global $in;
		global $inputval;
		$txt = $this->testo;

		$this->input_txt = $txt . ":<br>";
		//$id_area = $in ['ID_PRAT'] + 100000;
		//nuova tecnica per mettere suffisso alle id dei doc WCA
		if (isset($this->xml_form->config_service['PRJ']))
		$id_area = $in [$this->xml_form->config_service['PK_SERVICE']] + (100000*$this->xml_form->config_service['PRJ']);
		else $id_area = $in [$this->xml_form->config_service['PK_SERVICE']] + 100000;
		$topic = $this->attributes ['TOPIC'];
		$thread = $this->attributes ['THREAD'];
		$topic = preg_replace ( "/\[(.*?)\]/e", "var_glob('\\1')", $topic );
		$thread = preg_replace ( "/\[(.*?)\]/e", "var_glob('\\1')", $thread );
		global $config_service;
		$display = '';
		if (isset ( $config_service ['FILE_DOC_NA'] ) && $config_service ['FILE_DOC_NA']) {
			if ($inputval ["{$this->id}_FD_CK"] == 1) {
				$this->input_field = "<img src=\"/images/checkedcheck.gif\">Non applicabile";
				return;
			}
		}
		if ($_GET['PROGR']>1) $agg_progr="_".$_GET['PROGR'];
		if ($_POST['PROGR']>1) $agg_progr="_".$_GET['PROGR'];
		
//		$id_tipo_ref=$id_area;
//		$topic=preg_replace("/'/", "''", $topic);
//		if ($topic!='') $topic_where="topic='$topic'";
//		$thread=str_replace("à","%",$thread);
//		$thread=str_replace("è","%",$thread);
//		$thread=str_replace("ì","%",$thread);
//		$thread=str_replace("ò","%",$thread);
//		$thread=str_replace("ù","%",$thread);
//		$bind_array['TITOLO']=$thread;
//		
//		$sql_query="
//			select
//			   d.id,
//		       d.titolo,
//		       d.autore,
//		       d.data,
//		       d.approved,
//           	   d.approv_dt,
//		       (select
//		                count(*)
//		           from docs d1
//		        	where d1.tipo_doc='Doc_Area'
//		        	and d1.id_tipo_ref='{$id_tipo_ref}'
//		        	and d1.id_ref=d.id
//		        )-1 as n_rev,
//		        (select
//		            NOME_FILE
//		           from docs d1
//		        	where d1.tipo_doc='Doc_Area'
//		        	and d1.id_tipo_ref='{$id_tipo_ref}'
//		        	and d1.id=
//		         		(select max(d2.id) from docs d2
//		         			where d2.tipo_doc='Doc_Area'
//		        and d2.id_tipo_ref='{$id_tipo_ref}'
//		        and d2.id_ref=d.id)
//		        ) as nome_file,
//		        (
//		        select
//		          max(d2.data)
//		           from docs d2
//		        where d2.tipo_doc='Doc_Area'
//		        and d2.id_tipo_ref='{$id_tipo_ref}'
//		        and d2.id_ref=d.id
//		        ) as last_upd,
//		        (
//		        select
//		          max(d3.id)
//		           from docs d3
//		        where d3.tipo_doc='Doc_Area' and d3.id_tipo_ref='{$id_tipo_ref}' and d3.id_ref=d.id
//		        ) as last_ver
//
//		        from docs d
//		        where
//		        	tipo_doc='Doc_Area'
//		        	and id_tipo_ref='{$id_tipo_ref}'
//		        	and id=id_ref
//		        	and $topic_where
//					and d.titolo like :TITOLO
//		";
////		echo $sql_query;
//		$sql=new query($this->conn);
//		$sql->exec($sql_query, $bind_array);//commentata
//		$sql->get_row();
//		$this->input_field ="";
//		while ($sql->get_row()){
//			$this->input_field .= "<a href=\"download.php?id={$sql->row['ID']}\">{$sql->row['ID']}</a>"; 
//		
//		}
//		$query_eq="select id_prat,stato,equery_int from cp_vi_eq where equery_int =(SELECT max(EQUERY_INT) FROM {$this->service}_EQFIELD field, {$this->service}_eq eq
//		WHERE eq.id_prat=field.id_prat(+)
//		and EQ.ID_PRAT  = {$in [$this->xml_form->config_service['PK_SERVICE']]}
//		and EQ.EQUERY_INT=field.EQ_INT(+)
//		AND field.FIELD ='{$this->attributes ['VAR']}')";
//		$sql2=new query($this->conn);
//		$sql2->exec($query_eq);//commentata
//		$sql2->get_row();
//		if($sql2->row['STATO']==2) {
//			$this->input_field .= "<div><a href=\"download.php?id={$sql->row['ID']}\">{$sql->row['NOME_FILE']}</a><br /></div>"; 
//		}
 
			$this->input_field = "
			<iframe
			frameborder=\"no\"
			src=\"WCA/index.php?AF=2&tab=3&id_area=$id_area&thread={$thread}&keywords={$this->id}{$agg_progr}&topic={$topic}&VAR={$this->attributes ['VAR']}&SERVICE={$this->service}&PRJ={$this->xml_form->config_service['PRJ']}&USER_TIP={$this->session_vars['USER_TIP']}\"
			width=\"100%\"
			height=\"90\"
			>Vedi File Allegato
			</iframe>
			";
//		} else {
//			$this->input_field = "<div><a href=\"download.php?id={$sql->row['ID']}\">{$sql->row['NOME_FILE']}</a><br /></div>"; 
//		}
	}
	
	function allinea_db() {
		global $config_service;
		if (isset ( $config_service ['FILE_DOC_NA'] ) && $config_service ['FILE_DOC_NA']) {
			$ret [0] = "{$this->id}_FD_CK NUMBER";
			return $ret;
		} else
			return;
	}

	function insert_stmt() {
		global $config_service;
		global $in;
		if (isset ( $config_service ['FILE_DOC_NA'] ) && $config_service ['FILE_DOC_NA']) {
			$this->field_stmt [0] = "{$this->id}_FD_CK";
			$this->value_stmt [0] = "{$in["{$this->id}_FD_CK"]}";
		} else
			return;
	}
	
	function all_in($var, $i, $row, $this_closed) {
        $display=null;
		global $in;
		if (isset($this->xml_form->config_service['PRJ']))
		$id_area = $in [$this->xml_form->config_service['PK_SERVICE']] + (100000*$this->xml_form->config_service['PRJ']);
		else $id_area = $in [$this->xml_form->config_service['PK_SERVICE']] + 100000;

		$topic = $this->attributes ['TOPIC'];
		$thread = $this->attributes ['THREAD'];
		if ($i>1){
			$keyword="{$this->id}_{$i}";
		$where_agg=" and keywords='{$this->id}_{$i}'";
		$agg_progr="_{$i}";
		}else {
			$keyword="{$this->id}";
			$where_agg=" and keywords='{$this->id}'";
		}
		$sql_query="
		select * from docs where id=(
		select max(id) from docs
		where id_tipo_ref=$id_area and topic='$topic' and titolo = '$thread' and tipo_doc= 'Doc_Area'
		$where_agg
		)";
		$sql=new query($this->xml_form->conn);
		$sql->get_row($sql_query);
		$ret['body']="
		<td class=sc4bis>
		<a id=\"{$keyword}_link\" href=\"WCA/download.php?id={$sql->row['ID']}\">{$sql->row['NOME_FILE']}</a>
		<br/><div id=\"{$keyword}_new\" style=\"z-index:2;position:absolute;background-color:white;border:2px solid;display:none;\"></div>
		<input type='button' onclick=\"
		if (document.getElementById('{$keyword}_new')){
					var top=posBottom()-(pageHeight()/2)-40;
					left=(pageWidth()/2)-100;
					document.getElementById('{$keyword}_new').style.left=''+left+'px';
					document.getElementById('{$keyword}_new').style.top=''+top+'px';
					document.getElementById('{$keyword}_new').style.display='';
					document.getElementById('{$keyword}_new').innerHTML='<iframe id=\'{$keyword}_file_doc\' style=\'display:$display;width:400px\' frameborder=\'no\' src=\'WCA/index.php?AF=1&tab=3&id_area=$id_area&thread={$thread}&keywords={$this->id}{$agg_progr}&topic={$topic}\' width=\'100%\' height=\'120\'>Contenuto alternativo per i browser che non leggono gli iframe.</iframe>';
		}
		\" value=\"Allega file\">&nbsp;&nbsp;
		<a title=\"visualizza storico\" target=\"_blank\" href=\"WCA/index.php?tab=3&id_area=$id_area&id_doc={$sql->row['ID']}&id_ref={$sql->row['ID_REF']}\"><img src=\"../images/copia.gif\"></a>
		</td>
		";
		return $ret;
	}
	
	static function S_all_in($field, $m_p, $xml_form){
		$tr_agg = "<td class=int>&nbsp;</td>";
		return $tr_agg;
	}

}

?>