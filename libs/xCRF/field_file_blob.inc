<?

include_once "field.inc";
//include_once "/http/lib/XMR/v2.1/libs/field.inc";
class field_file_blob extends field{

	function open_($value){
		global $in;
//		global $inputval;
		$inputval=$this->db_vars;
		//print_r($inputval);
		$file_uploaded="";
		$pk_service=$this->xml_form->config_service['PK_SERVICE'];
		
		if ($value!=''){
			$file_name=$inputval[$this->attributes['VAR']];
			$file_uploaded="Download file: <a href=\"?DOWNLOAD=1&VAR={$this->attributes['VAR']}&{$pk_service}={$in[$pk_service]}&VISITNUM={$in['VISITNUM']}&ESAM={$in['ESAM']}&PROGR={$in['PROGR']}\">$file_name</a>";
		}
				
		if ($this->attributes['COMPILA_FIELD']!=''){
			if ($this->attributes['COMPILA_VALUE']!='')
			$this->check_js.="
				if (document.forms[0].{$this->attributes['VAR']}.value!=''){
					document.forms[0].{$this->attributes['COMPILA_FIELD']}.value='{$this->attributes['COMPILA_VALUE']}';
				}
			";
			if ($this->attributes['COMPILA_VALUE_ADD']!='')
			$this->check_js.="
				if (document.forms[0].{$this->attributes['VAR']}.value!=''){
					document.forms[0].{$this->attributes['COMPILA_FIELD']}.value+='{$this->attributes['COMPILA_VALUE']}';
				}
			";
			$onblur_agg="cf();";
			$onchange=" onchange=\"cf();\"";
		}
		
		$txt=$this->testo;
		$input_html="
			<input type=\"file\" name=\"{$this->attributes['VAR']}\" size=\"80\"
			
			onblur=\"
			$onblur_agg
			\"
			$onchange/>
			$file_uploaded";
		$this->input_txt=$txt;
		$this->input_field=$input_html;
	}

	function open_send($value){
		//traduzione del messaggio di alert in inglese
		if($this->config_service['lang']=="en")
			$alert_msg="Warning!! It\\'s necessary to attach a file in the box ";
		else
			$alert_msg="Attenzione!!!E\\' necessario allegare un file nel campo:\\n ";
			
		$js_txt=make_js($this->testo);
		$this->invia_js="
			if (document.forms[0].{$this->attributes['VAR']}.value==''&&document.getElementById('tr_{$this->attributes['VAR']}').style.display=='') {
				alert('".$alert_msg." \"".$js_txt."\"');
				document.forms[0].{$this->attributes['VAR']}.focus();
				return false;			
			}
		";		
	}
	
	function open_save($value){
		//traduzione del messaggio di alert in inglese
		if($this->config_service['lang']=="en")
			$alert_msg="Warning!! It\\'s necessary to attach a file in the box ";
		else
			$alert_msg="Attenzione!!!E\\' necessario allegare un file nel campo:\\n ";
			
		$js_txt=make_js($this->testo);
		
		$this->salva_js="
			if (document.forms[0].{$this->attributes['VAR']}.value==''&&document.getElementById('tr_{$this->attributes['VAR']}').style.display=='') {
				alert('".$alert_msg." \"".$js_txt."\"');
				document.forms[0].{$this->attributes['VAR']}.focus();
				return false;			
			}
		";	
		die("SON QUA");	
	}

	function close_($value){
		global $in;
		//global $inputval;
		$inputval=$this->db_vars;
		//print_r($inputval);
		$pk_service=$this->xml_form->config_service['PK_SERVICE'];
		
		$file_uploaded="";
		if ($value!=''){
			$file_name=$inputval[$this->attributes['VAR']];
			$file_uploaded="<a  href=\"?DOWNLOAD=1&VAR={$this->attributes['VAR']}&{$pk_service}={$in[$pk_service]}&VISITNUM={$in['VISITNUM']}&ESAM={$in['ESAM']}&PROGR={$in['PROGR']}\">$file_name</a>";
		}
		$txt=$this->testo;
		$input_html="$file_uploaded";
		$this->input_txt=$txt;
		$this->input_field=$input_html;
	}

	function allinea_db(){
		if ($this->attributes['TB']!='no'){
			$ret[0]="{$this->attributes['VAR']}_DATA BLOB";
			$ret[1]="{$this->attributes['VAR']} VARCHAR2(1000 char)";
			return $ret;
		}
		else return ;
	}

	function insert_stmt($insert=true){
        $i=null;
		global $in;
		global $config_service;
		
		//echo "<hr>insert=$insert<hr>";
		
	
		if (!$insert){
			$this->field_stmt[0]="{$this->attributes['VAR']}_DATA";
			$this->field_stmt[1]="{$this->attributes['VAR']}";
			//die();
			return;
		}
		if ($this->attributes['TB']!='no' && $_FILES[$this->attributes['VAR']]['size']>0){
			//echo "<hr>".$this->attributes['VAR']."<hr>";
			$filename=$_FILES[$this->attributes['VAR']]['name'];
			$ext=explode(".", $filename);
			$pk_service=$this->xml_form->config_service['PK_SERVICE'];
			$unique_key=$pk_service."_".$in[$pk_service]."_PROGR_".$in['PROGR']."_VISITNUM_".$in['VISITNUM']."_ESAM_".$in['ESAM'];
			if ($config_service['VISITNUM_PROGR']=='1') $unique_key.="_VPROGR_".$in['VISITNUM_PROGR'];
			$file_to_write=$this->attributes['VAR']."_".$unique_key.".".$ext[1];
			$in[$this->fields[$i]['VAR']]=$file_to_write;
			//global $dir;
			$dir='';
			$paths=explode("/", $_SERVER['PATH_TRANSLATED']);

			for ($i=0;$i<count($paths)-1; $i++){
				$dir.=$paths[$i]."/";
			}

			//$dir_file=$dir."/uploaded_file/";
			//$nome_real_file=$file_to_write;
			//$file_to_write=$dir_file.$file_to_write;
			//echo "<hr>".$file_to_write;
			//$data = file_get_contents($_FILES[$this->attributes['VAR']]['tmp_name']);
			//if (!move_uploaded_file($_FILES[$this->attributes['VAR']]['tmp_name'], $file_to_write)) die("ERRORE COPIA FILE");
			//die($data);
			$this->field_stmt[0]="{$this->attributes['VAR']}";
			//$this->field_stmt[1]="{$this->attributes['VAR']}_data";
			$this->value_stmt[0]=$filename;
			//$this->value_stmt[1]=$data;
			
			/*
			 * 
			//Write BLOB in DB
			$c = $this->xml_form->conn->conn;

			$where = "{$pk_service}= {$in[$pk_service]} AND VISITNUM = {$in['VISITNUM']} AND VISITNUM_PROGR = {$in['VISITNUM_PROGR']} AND ESAM = {$in['ESAM']} AND PROGR = {$in['PROGR']}";
			//Inserimento in tabella coordinate se non esiste la riga
			//$this->xml_form->config_service
			$service = $config_service['service'];
			$sql_query="select * from {$service}_COORDINATE where $where";
			$sql=new query($this->xml_form->conn);
			$sql->set_sql ( $sql_query );
			$sql->exec ();
			if (!$sql->get_row ()){
				$sql_query="INSERT INTO {$service}_COORDINATE({$pk_service},VISITNUM,VISITNUM_PROGR,ESAM,PROGR,USERID,ABILITATO,VISITCLOSE) 
						VALUES ({$in[$pk_service]},{$in['VISITNUM']},{$in['VISITNUM_PROGR']},{$in['ESAM']},{$in['PROGR']},'{$in['USERID_INS']}',1,0)";
				$sql->set_sql ( $sql_query );
				$sql->exec ();		
				//echo "iNS COORDINATE!";		
			}
			//else{
				//echo "ESISTE!";
			//}
			
			//die();
			//SELECT {$pk_service}, VISITNUM, VISITNUM_PROGR, ESAM, PROGR
			//			  FROM {$this->xml_form->form['TABLE']}
			//			  WHERE dept_no =20) e
			//			ON (b.employee_id = e.employee_id)
			$sql_tb = "MERGE INTO {$this->xml_form->form['TABLE']} t
						USING (SELECT COUNT(*) cnt FROM {$this->xml_form->form['TABLE']}
							WHERE $where)
						ON (cnt= 1)
						WHEN MATCHED THEN
						  UPDATE SET t.{$this->attributes['VAR']}_DATA = :DATA WHERE $where 
						WHEN NOT MATCHED THEN
						  INSERT ({$pk_service},VISITNUM,VISITNUM_PROGR,ESAM,PROGR,{$this->attributes['VAR']}_DATA)
						  VALUES ({$in[$pk_service]},{$in['VISITNUM']},{$in['VISITNUM_PROGR']},{$in['ESAM']},{$in['PROGR']}, :DATA)
					";
			//die($sql_tb);
			$stmt=ociparse($c, $sql_tb);
			//print_r($stmt);
			$lob = oci_new_descriptor($c, OCI_D_LOB);
			oci_bind_by_name($stmt, ":DATA", &$lob, -1, OCI_B_BLOB);
			$lob->WriteTemporary($data,OCI_TEMP_BLOB);
			//$lob[$k]->write($v['DATA']);
			$rbool = ociexecute($stmt, OCI_DEFAULT);
			if ($rbool == false){
				$err = ocierror($stmt);
				$etx = $err['message'];
				echo("Errore QUERY: $q<br/>Errore Oracle: ".$etx);
				return FALSE;
			}
			oci_free_descriptor($lob);
			
			
			//print_r($this->value_stmt);
			//die("<hr>");
			
			*/
		}
		return;
	}
	
	
	function XML_OUTPUT($values){
		$tag="VAR";
		$out="
		<$tag NAME=\"{$this->attributes['VAR']}\">";
		
		if ($this->testo!='') $out.="
			<TESTO><![CDATA[{$this->testo}]]></TESTO>";
		$out.= "
			<VALORE><![CDATA[{$values[$this->id]}]]></VALORE>
			<DECODIFICA><![CDATA[{$values["D_".$this->id]}]]></DECODIFICA>
		</$tag>
		";
		return $out;
	}
	
	function all_in($var, $i, $row, $this_closed) {
        $keyword=null;
		global $in;
		/*
		if ($i == 1){
			echo "<pre>";
		print_r($in);
		print_r($row);
			echo "</pre>";
		}
		*/
		$pk_service=$this->xml_form->config_service['PK_SERVICE'];
		/*
		$sql_query="
		select * from docs where id=(
		select max(id) from docs
		where id_tipo_ref=$id_area and topic='$topic' and titolo = '$thread' and tipo_doc= 'Doc_Area'
		$where_agg
		)";
		*/
		//echo $sql_query."<br/>";
		//echo "$i";
		//$sql=new query($this->xml_form->conn);
		$ret['body']="
			<td class=\"sc4bis\" align=\"center\" >
			";
		if ($row[$this->attributes['VAR']])
		{
			$ret['body'].="<a id=\"{$keyword}_link\" href=\"?DOWNLOAD=1&VAR={$this->attributes['VAR']}&{$pk_service}={$in[$pk_service]}&VISITNUM={$in['VISITNUM']}&ESAM={$in['ESAM']}&PROGR={$i}\"><img src=\"images/pdf.png\" border=\"0\" /><br/>&nbsp;{$row[$this->attributes['VAR']]}</a>";
		}else{
			$ret['body'].="Nessun allegato";
		}
		$ret['body'].="
		</td>
		";
		return $ret;
	}
	
	static function S_all_in($field, $m_p, $xml_form){
		$tr_agg = "<td class=int>&nbsp;</td>";
		return $tr_agg;
	}
	
	function post_stmt(){
        $q=null;
		global $in;
		global $config_service;
		
		//die("POST!");
		if ($this->attributes['TB']!='no' && $_FILES[$this->attributes['VAR']]['size']>0){
			//echo "<hr>".$this->attributes['VAR']."<hr>";
// 			die('ADDIOP');
			if (!$in['PROGR']){
				$in['PROGR']=1;
			}
			if (!$in['VISITNUM_PROGR']){
				$in['VISITNUM_PROGR']=0;
			}
			$pk_service=$this->xml_form->config_service['PK_SERVICE'];

			$data = file_get_contents($_FILES[$this->attributes['VAR']]['tmp_name']);
			
			//Write BLOB in DB
			$c = $this->xml_form->conn->conn;

			$where = "{$pk_service}= {$in[$pk_service]} AND VISITNUM = {$in['VISITNUM']} AND VISITNUM_PROGR = {$in['VISITNUM_PROGR']} AND ESAM = {$in['ESAM']} AND PROGR = {$in['PROGR']}";
			//Inserimento in tabella coordinate se non esiste la riga
			//$this->xml_form->config_service
			$service = $config_service['service'];
			$sql_query="select * from {$service}_COORDINATE where $where";
			$sql=new query($this->xml_form->conn);
			$sql->set_sql ( $sql_query );
			$sql->exec ();
			if (!$sql->get_row ()){
				$sql_query="INSERT INTO {$service}_COORDINATE({$pk_service},VISITNUM,VISITNUM_PROGR,ESAM,PROGR,USERID,ABILITATO,VISITCLOSE) 
						VALUES ({$in[$pk_service]},{$in['VISITNUM']},{$in['VISITNUM_PROGR']},{$in['ESAM']},{$in['PROGR']},'{$in['USERID_INS']}',1,0)";
				$sql->set_sql ( $sql_query );
				$sql->exec ();		
				//echo "INS COORDINATE!";		
			}
// 			else{
// 				echo "ESISTE!";
// 			}
			
// 			die();
			//SELECT {$pk_service}, VISITNUM, VISITNUM_PROGR, ESAM, PROGR
			//			  FROM {$this->xml_form->form['TABLE']}
			//			  WHERE dept_no =20) e
			//			ON (b.employee_id = e.employee_id)
			$sql_tb = "MERGE INTO {$this->xml_form->form['TABLE']} t
						USING (SELECT COUNT(*) cnt FROM {$this->xml_form->form['TABLE']}
							WHERE $where)
						ON (cnt= 1)
						WHEN MATCHED THEN
						  UPDATE SET t.{$this->attributes['VAR']}_DATA = :DATA WHERE $where 
						WHEN NOT MATCHED THEN
						  INSERT ({$pk_service},VISITNUM,VISITNUM_PROGR,ESAM,PROGR,{$this->attributes['VAR']}_DATA)
						  VALUES ({$in[$pk_service]},{$in['VISITNUM']},{$in['VISITNUM_PROGR']},{$in['ESAM']},{$in['PROGR']}, :DATA)
					";
			//die($sql_tb);
			$stmt=ociparse($c, $sql_tb);
			//print_r($stmt);
			$lob = oci_new_descriptor($c, OCI_D_LOB);
			oci_bind_by_name($stmt, ":DATA", $lob, -1, OCI_B_BLOB);
			$lob->WriteTemporary($data,OCI_TEMP_BLOB);
			//$lob[$k]->write($v['DATA']);
			$rbool = ociexecute($stmt, OCI_DEFAULT);
			if ($rbool == false){
				$err = ocierror($stmt);
				$etx = $err['message'];
				echo("Errore QUERY: $q<br/>Errore Oracle: ".$etx);
				return FALSE;
			}
			oci_free_descriptor($lob);
			
			$this->xml_form->conn->commit();
			//print_r($this->value_stmt);
			//die("<hr>");
		}
		return;
		
	}
	
	
}


?>