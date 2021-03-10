<?

include_once "libs/field_textarea.inc";

class field_ckeditor_gen extends field_textarea{

	function open_($value){
		global $conn;

		$file_original=$this->attributes['FILE_TEMPLATE'];
		$file_template=$this->attributes['FILE_TEMPLATE'];

		/*
		//$sql_query_vista = "select * from {$this->xml_form->prefix}_{$this->attributes['VISTA_SUBST']} where ID_PRAT={$this->session_vars['ID_PRAT']}";
		$sql_query_vista = "select * from {$this->xml_form->prefix}_{$this->attributes['VISTA_SUBST']} where {$this->config_service['PK_SERVICE']}={$this->session_vars[$this->config_service['PK_SERVICE']]}";
		$sql_vista = new query ( $this->conn );
		$sql_vista->exec ( $sql_query_vista );
		$sql_vista->get_row ();
//		echo $sql_query_vista;
		if(isset($_GET['PROGR']))
		$progr=$_GET['PROGR'];
		else $progr=1;
		*/
		$progr=1;
		$sql_query = "select * from {$this->xml_form->form['TABLE']} where {$this->config_service['PK_SERVICE']}={$this->session_vars[$this->config_service['PK_SERVICE']]}  
		and template_type='{$this->attributes['TEMPLATE_TYPE']}' and ESAM={$this->session_vars['ESAM']} 
		and VISITNUM={$this->session_vars['VISITNUM']} and PROGR=$progr";
		$sql = new query ( $this->conn );
		$sql->exec ( $sql_query );
		$sql->get_row ();
		//echo $sql_query;

		/*
		$sql_query_c = "select COUNTRY from {$this->xml_form->prefix}_rec where {$this->config_service['PK_SERVICE']} = {$this->session_vars[$this->config_service['PK_SERVICE']]}";
		$sql_c = new query ( $this->conn );
		$sql_c->exec ( $sql_query_c );
		$sql_c->get_row ();
		*/
		
		
		/*
		if($sql_c->row['COUNTRY']==20 && 
		$this->attributes['TEMPLATE_TYPE']!="annullgu" && 
		$this->attributes['TEMPLATE_TYPE']!="stampati" && 
		!preg_match("/_it_rms$/i",$this->attributes['TEMPLATE_TYPE'])
		&& preg_match("/CP_VI/",$_SERVER['REQUEST_URI'])) {
			$alert_rms="<p style=\"font-size:14px;color:blue;\">Italy RMS (template in eng)</p>";
			$file_template=str_replace(".htm","_eng.htm",$file_template);
		}

		$sql_query_ = "select * from {$this->xml_form->prefix}_LISTA where ID_PRAT={$this->session_vars['ID_PRAT']}";
		$sql_ = new query ( $this->conn );
		$sql_->exec ( $sql_query_ );
		$sql_->get_row ();

		$single_grouped="";
		//single
		if($sql_->row['TIPO_VAR1']==1 && ($this->attributes['TEMPLATE_TYPE']=="valid" || $this->attributes['TEMPLATE_TYPE']=="notvalid")) {
			$file_template=str_replace("_eng.htm","_eng_single.htm",$file_template);
			if(preg_match("/IA/",$sql_->row['TYPES'])) {
				$file_template=str_replace("_eng_single.htm","_eng_single_IA.htm",$file_template);
			} else if(preg_match("/IB/",$sql_->row['TYPES']) ) {
				$file_template=str_replace("_eng_single.htm","_eng_single_IB.htm",$file_template);
			}
		} else if($sql_->row['TIPO_VAR1']==2 && ($this->attributes['TEMPLATE_TYPE']=="valid" || $this->attributes['TEMPLATE_TYPE']=="notvalid")) {
			//grouped
			$file_template=str_replace("_eng.htm","_eng_grouped.htm",$file_template);
		}

		echo "<!--".$file_template."-->";
//		if(!file_exists($file_template)) $file_template=$file_original;

		if($this->session_vars['azzera']=="yes" || ($this->attributes['NO_FEEDBACK']!="" && $sql->numrows==0) || $value=="") {
			if($this->attributes['TEMPLATE_CONDITIONATED']=="yes") {	
				if($sql_->row['TIPO_VAR']==1) {
					$type="_mr";
				} else if($sql_->row['TIPO_VAR']==2) {
					$type="_naz";
				}			
				$file_template=str_replace(".htm",$type.".htm",$file_template);
			}
			$value=file_get_contents("../".$file_template);
			$sott_array=$this->sottotipo($this->session_vars['ID_PRAT']);
//			print_r($sott_array);
			$sott=implode(", ",$sott_array);
			$value=preg_replace("/<--TYPES_CHECKLIST-->/",$sott,$value);

			foreach($sql_vista->row as $key => $val) {
				if($val!="" && $this->attributes['TEMPLATE_TYPE']=='conformita_doc')
					$value=preg_replace("/<--$key-->/",$val,$value);
				else
					$value=preg_replace("/<--$key-->/",$val,$value);
			}
			$value=preg_replace("/<hr>/i","<hr break>",$value);
			$alert="<h3 style=\"color:red;\">La lettera non è mai stata salvata</h3>";
		} else if($sql->numrows!=0){
			$value=$sql->row[$this->attributes['VAR']];
			$alert="<h3 style=\"color:green;\">La lettera è salvata</h3>";
		} else {
			$alert="";
		}
		$alert=$alert_rms;

		$ret='<tr id="'.$this->attributes['VAR'].'" style="display:">';
		$txt=$this->testo;
		//print_r($this);
		foreach ($this->xml_form->fields as $key => $val){
			//echo "<li>{$this->attributes['VAR']} - {$val['CONDITION']}</li>";
			if ($this->attributes['VAR']==$val['CONDITION']) $onblur="onblur=\"cf();\"";
		}
		$height=$width="";
		if($this->attributes['HEIGHT']!="") $height=$this->attributes['HEIGHT'];
		else $height="100%";

		//if esam = 38
		//Per stampare le "lettere modifica stampati" ciascuna su pagina singola, è necessario utilizzare la funzione "stampa pdf" dopo aver preventivamente salvato la lettera.

//		if($this->attributes['WIDTH']!="") $width=$this->attributes['WIDTH'];
		if(!isset($this->session_vars['PROGR']))
		$progr=1;
		else
		$progr=$this->session_vars['PROGR'];

		$url="https://".$_SERVER['SERVER_NAME'].$_SERVER['SCRIPT_NAME']."?ID_PRAT={$this->session_vars['ID_PRAT']}&VISITNUM={$this->session_vars['VISITNUM']}&ESAM={$this->session_vars['ESAM']}&PROGR={$progr}";
		$this->input_field=$alert.'
		<textarea '.$onblur.' id=\''.$this->id.'\' name="'.$this->attributes['VAR'].'"
		cols="'.$this->attributes['TCOLS'].'" rows="'.$this->attributes['ROWS'].'"
		>'.$value.'</textarea>
		';
		$this->input_field.='<p align="center"><input type="button" style="color:red;"	value="Azzera template" onclick="window.location.href = \''.$url.'&azzera=yes\';" />
		<input type="button" value="Stampa" onclick="window.open(\''.$url.'&tb='.$this->xml_form->form['TABLE'].'&TEMPLATE_TYPE=&stampa_template=yes&TEMPLATE_TYPE='.$this->attributes['TEMPLATE_TYPE'].'\',\'_blank\');" />
		<input type="button" value="Stampa PDF" onclick="window.open(\''.$url.'&tb='.$this->xml_form->form['TABLE'].'&stampa_template=pdf&TEMPLATE_TYPE='.$this->attributes['TEMPLATE_TYPE'].'\',\'_blank\');" />
		<input type="button" style="color:green;" value="Invia Mail" onclick="window.location.href = \''.$url.'&tb='.$this->xml_form->form['TABLE'].'&mail_template=yes&TEMPLATE_TYPE='.$this->attributes['TEMPLATE_TYPE'].'\';" />
		<br /><span style="color:#ff0000 !important;font-weight:bold;">ATTENZIONE: salvare la lettera prima di stampare o inviare la mail o chiudere la valutazione.</span>
		</p>';
		$this->input_field.='
		<script type="text/javascript">
			CKEDITOR.replace( \''.$this->id.'\', {
			toolbar : \'Full\',
			height: \''.$height.'\'
    	});
		</script>';
		//toolbar : \'AIFA\',
		$this->input_txt="<p align=\"center\">".$txt."</p>";
		if (isset($this->attributes['COLSPAN']) && $this->cols_form>1) $ret.='<td  class="input" colspan="'.$this->cols_form.'">'.$txt.' '.$input_html.'</td>';
		else $ret.='<td class="destra" colspan=2>'.$txt.' '.$input_html.'</td></tr>';
		#return $ret;
		*/
		if($this->session_vars['azzera']==$this->attributes['AZZERA'] || ($this->attributes['NO_FEEDBACK']!="" && $sql->numrows==0) || $value=="") {
		//echo "{$this->session_vars['azzera']}";
		//echo "{$this->attributes['AZZERA']}";
			/*
			$value=file_get_contents($file_template);

			foreach($sql_vista->row as $key => $val) {
					$value=preg_replace("/<--$key-->/",$val,$value);
			}
			$value=preg_replace("/<hr>/i","<hr break>",$value);
			*/
			//echo $this->xml_form->crea_ODG();
			//print_r($this);
			//die();
			$azzera = $this->attributes['AZZERA'];
			//$output .= get_include_contents('main.php');
			//$url="https://".$_SERVER['SERVER_NAME'].$_SERVER['SCRIPT_NAME']."?{$this->config_service['PK_SERVICE']}={$this->session_vars[$this->config_service['PK_SERVICE']]}&VISITNUM={$this->session_vars['VISITNUM']}&ESAM={$this->session_vars['ESAM']}&PROGR={$progr}&azzera_fcn=$azzera";
			//echo "$url<br/>";
			//$output = $this->curl_get($url);
			//$output = get_include_contents($url);
			global $study_;
			//echo $azzera;
			$output = $study_->$azzera();
			//die ($output);
			$value = $output;
			
		} else if($sql->numrows!=0){
			$value=$sql->row[$this->attributes['VAR']];
		} else {
			$alert="";
		}
		$alert=$alert_rms;
//		echo "<!--".$file_template."-->";

		$ret='<tr id="'.$this->attributes['VAR'].'" style="display:">';
		$txt=$this->testo;
		foreach ($this->xml_form->fields as $key => $val){
			if ($this->attributes['VAR']==$val['CONDITION']) $onblur="onblur=\"cf();\"";
		}
		$height=$width="";
		if($this->attributes['HEIGHT']!="") $height=$this->attributes['HEIGHT'];
		else $height="100%";
		if($this->attributes['WIDTH']!="") $width=$this->attributes['WIDTH'];
		else $width="100%";

		if(!isset($this->session_vars['PROGR']))
		$progr=1;
		else
		$progr=$this->session_vars['PROGR'];
		
		$url="https://".$_SERVER['SERVER_NAME'].$_SERVER['SCRIPT_NAME']."?{$this->config_service['PK_SERVICE']}={$this->session_vars[$this->config_service['PK_SERVICE']]}&VISITNUM={$this->session_vars['VISITNUM']}&ESAM={$this->session_vars['ESAM']}&PROGR={$progr}";
//		echo $url;
		$this->input_field=$alert.'
		<textarea '.$onblur.' class="ckeditor" id=\''.$this->id.'\' name="'.$this->attributes['VAR'].'"
		cols="'.$this->attributes['TCOLS'].'" rows="'.$this->attributes['ROWS'].'"
		>'.$value.'</textarea>
		';
		$disabled_all_mail="";
		$disabled_all="";


		//$this->input_field.='<p align="center"><input type="button" style="color:red;"	value="Ricarica modello2" onclick="window.location.href = \''.$url.'&azzera=yes\';" />'; //&azzera_fcn=$this->attributes['AZZERA']\';" />';
		$this->input_field.='
								<button class="btn btn-purple" type="button" name="salva" onclick="window.location.href = \''.$url.'&azzera='.$this->attributes['AZZERA'].'\';">
									<i class="fa fa-refresh bigger-110"></i>
									Ricarica modello
								</button>';
		
		//$this->input_field.='<p align="center"><input type="button" style="color:blue;"	value="Stampa" onclick="CKEDITOR.tools.callFunction(11, this); return false;" />';
//		$this->input_field.='<input '.$disabled_all.' type="button" value="Stampa" onclick="window.open(\''.$url.'&tb='.$this->xml_form->form['TABLE'].'&TEMPLATE_TYPE=&stampa_template=yes&TEMPLATE_TYPE='.$this->attributes['TEMPLATE_TYPE'].'\',\'_blank\');" />
//		<input '.$disabled_all.' type="button" value="Stampa PDF" onclick="window.open(\''.$url.'&tb='.$this->xml_form->form['TABLE'].'&stampa_template=pdf&TEMPLATE_TYPE='.$this->attributes['TEMPLATE_TYPE'].'\',\'_blank\');" />
//		<input '.$disabled_all_mail.' type="button" style="color:green;" value="Invia Mail" onclick="window.location.href = \''.$url.'&tb='.$this->xml_form->form['TABLE'].'&mail_template=yes&TEMPLATE_TYPE='.$this->attributes['TEMPLATE_TYPE'].'\';" />
//		<br /><span style="color:#ff0000 !important;font-weight:bold;">ATTENZIONE: salvare la lettera prima di stampare o inviare la mail o chiudere la valutazione.</span>
//		</p>';

		if ($this->attributes['TOOLBAR'] != '')
			$toolbar = $this->attributes['TOOLBAR'];
		else 
			$toolbar = 'Full';
		
		//qui definisco i parametri dell'editor (toolbar, stile e altro)
		//gli stili vanno definiti dentro il file config.js nella cartella di ckeditor
		$this->input_field.="
		<script type='text/javascript'> 
			CKEDITOR.replace( '".$this->id."', {
			toolbar : '".$toolbar."',
			height: '".$height."',
			width: '".$width."'
    	});
		</script>";
		
		//toolbar : \'AIFA\',
		$this->input_txt=$txt;
		if (isset($this->attributes['COLSPAN']) && $this->cols_form>1) $ret.='<td  class="input" colspan="'.$this->cols_form.'">'.$txt.' '.$input_html.'</td>';
		else $ret.='<td class="destra" colspan=2>'.$txt.' '.$input_html.'</td></tr>';
		#return $ret;
	}

	/**
	 * Costruisce i controlli al salvataggio
	 *
	 * @param String $val
	 */
	function open_save($val){
		$this->testo=$this->input_txt;
		$in=$this->session_vars;
//		if ($this->attributes['VAR_TYPE']=='text' || $this->attributes['VAR_TYPE']=='clob')
		$controllo="t";

		$testo_js=make_js($this->testo);
		if ($testo_js=='') $testo_js=$this->attributes['LABEL_JS'];
		if (($val=='obbligatorio' && $this->attributes['CONDITION']=='')||($this->attributes['VAR_TYPE']!='text' && $val=='facoltativo')||($this->attributes['VAR_TYPE']!='clob' && $val=='facoltativo')){
			$this->salva_js.="
				c1+='<<".$controllo."###".$this->attributes['VAR']."###".$testo_js.">>';\n";
		}
		/*aggiorno con la possibilità di utilizzare più valori divisi da virgola in condition_value da testare approfonditamente (Giorgio Delsignore 14/06/2010)
		if ($val=='obbligatorio' && $this->attributes['CONDITION']!=''){
			$this->salva_js.="
			var value_{$this->attributes['CONDITION']}=value_of('{$this->attributes['CONDITION']}','0');
			if(value_{$this->attributes['CONDITION']}=='{$this->attributes['CONDITION_VALUE']}')c1+='<<".$controllo."###".$this->attributes['VAR']."###".$testo_js.">>';
			";

		}*/
		if ($val=='obbligatorio' && $this->attributes['CONDITION']!=''){
			$this->salva_js.="
				".$this->attributes['CONDITION']."_setted=false;
				";
			if (preg_match("/,/",$this->attributes['CONDITION_VALUE'])){
				$vals=explode(",", $this->attributes['CONDITION_VALUE']);
				foreach ($vals as $key => $value)
				$this->salva_js.="
						value=value_of('{$this->attributes['CONDITION']}', '0');
						if (value=='".$value."') {
								".$this->attributes['CONDITION']."_setted=true;
								c1+='<<".$controllo."###".$this->attributes['VAR']."###".$testo_js.">>';
								}
						";
			}
			else
			{
				$oper="==";
				if (preg_match("/!/",$this->attributes['CONDITION_VALUE'])) {$oper="!=";$this->attributes['CONDITION_VALUE']=substr($this->attributes['CONDITION_VALUE'], 1);}
				$this->salva_js.="
						value=value_of('{$this->attributes['CONDITION']}', '0');
						if (value $oper'".$this->attributes['CONDITION_VALUE']."') {
						c1+='<<".$controllo."###".$this->attributes['VAR']."###".$testo_js.">>';
						".$this->attributes['CONDITION']."_setted=true;
					}
					";
			}
			$this->salva_js.="
					if (!".$this->attributes['CONDITION']."_setted) {c1+='<<$controllo###".$this->attributes['VAR']."###".$testo_js.">>';}
				";
		}
		$this->session_vars=$in;
	}

	function open_send($val){
		$this->testo=$this->input_txt;
		$in=$this->session_vars;
		if ($this->attributes['VAR_TYPE']=='text' || $this->attributes['VAR_TYPE']=='clob')
		$controllo="t";


		if ($val=='facoltativo') $controllo="f".$controllo;
		$testo_js=make_js($this->input_txt);
		if ($testo_js=='') $testo_js=$this->attributes['LABEL_JS'];
		$this->invia_js="
				c1+='<<".$controllo."###".$this->attributes['VAR']."###".$testo_js.">>';\n";
		if ($this->attributes['CONDITION']!=''){
			$this->invia_js="
				".$this->attributes['CONDITION']."_setted=false;
				";
			if (preg_match("/,/",$this->attributes['CONDITION_VALUE'])){
				$vals=explode(",", $this->attributes['CONDITION_VALUE']);
				foreach ($vals as $key => $value)
				$this->invia_js.="
						value=value_of('{$this->attributes['CONDITION']}', '0');
						if (value=='".$value."') {
								".$this->attributes['CONDITION']."_setted=true;
								c1+='<<".$controllo."###".$this->attributes['VAR']."###".$testo_js.">>';
								}
						";
			}
			else
			{
				$oper="==";
				if (preg_match("/!/",$this->attributes['CONDITION_VALUE'])) {$oper="!=";$this->attributes['CONDITION_VALUE']=substr($this->attributes['CONDITION_VALUE'], 1);}
				$this->invia_js.="
						value=value_of('{$this->attributes['CONDITION']}', '0');
						if (value $oper'".$this->attributes['CONDITION_VALUE']."') {
						c1+='<<".$controllo."###".$this->attributes['VAR']."###".$testo_js.">>';
						".$this->attributes['CONDITION']."_setted=true;
					}
					";
			}
			$this->invia_js.="
					if (!".$this->attributes['CONDITION']."_setted) {c1+='<<b###".$this->attributes['VAR']."###".$testo_js.">>';}
				";
		}
		$in=$this->session_vars;
		if ($in['invia']!='' || $in['INVIOCO']=='1'){
			if ($this->condition_passed){
				if ($in[$this->attributes['VAR']]=='') {
					if ($val=='obbligatorio'){
						$this->validata=false;
						$this->errors=$this->errors;
						$testo_js=make_js($this->testo);
						$this->errors[$this->attributes['VAR']]="Il campo è obbligatorio";
					}
				}
			}
			else {
				if ($in[$this->attributes['VAR']]!='' && $val=='obbligatorio') {
					$this->validata=false;
					$this->errors=$this->errors;
					$testo_js=make_js($this->testo);
					$this->errors[$this->attributes['VAR']]="Il campo deve essere vuoto";
				}
			}
		}
		$this->session_vars=$in;
	}

	function insert_stmt(){
		if ($this->session_vars ['USER_TIP'] == 'DM' && ($this->attributes['NO_DM_CHANGE']!='' || $this->attributes['CRYPTO']!='')){
   		return;
 	 	}
		global $in;
		//echo "<hr>";
		//print_r($in);
		if ($this->attributes['TB']!='no'){
			$this->field_stmt[0]=$this->attributes['VAR'];
			$value=$in[$this->attributes['VAR']];
			//aggiungo l'urlencode
//			$value=urlencode($value);

			$this->value_stmt[0]=$value;
		}
//		print_r($this->value_stmt);
		return;
	}

	function allinea_db(){
		if ($this->attributes['TB']!='no'){
			if ($this->attributes['VAR_TYPE']=='number') $type_field='NUMBER';
			else if($this->attributes['VAR_TYPE']=='clob') $type_field="CLOB";
			else $type_field="VARCHAR2({$this->attributes['VAR_SIZE']})";
			$ret[0]="{$this->attributes['VAR']} {$type_field}";
			return $ret;
		}
		else return ;
	}

	function close_($value){
		$ret='<tr id="'.$this->attributes['VAR'].'" style="display:">';
		$txt=$this->testo;
		
		if(isset($_GET['PROGR']))
		$progr=$_GET['PROGR'];
		else $progr=1;
		$sql_query = "select * from {$this->xml_form->form['TABLE']} where {$this->config_service['PK_SERVICE']}={$this->session_vars[$this->config_service['PK_SERVICE']]}  and template_type='{$this->attributes['TEMPLATE_TYPE']}'
		and ESAM={$this->session_vars['ESAM']} and VISITNUM={$this->session_vars['VISITNUM']} and PROGR=$progr";
		$sql = new query ( $this->conn );
		$sql->exec ( $sql_query );
		$sql->get_row ();
		$value=$sql->row[$this->attributes['VAR']];
		$input_html='<span style=\"background-color:white;text-align:left;border:1px solid black;padding:10px;\" >'.$value.'</span>';
		$this->input_txt=$txt;
		$this->input_field="<div style=\"background-color:white;text-align:left;margin:10px;padding:10px;\">&nbsp;".$input_html."</div>";
		if (isset($this->attributes['COLSPAN'])) $ret.='<td class="input_txt" colspan="'.$this->attributes['COLSPAN'].'">'.$txt.' '.$input_html.'</td>';
		else $ret.='<td class="destra">'.$txt.'</td><td class="input">'.$input_html.'</td></tr>';
		#return $ret;
	}

	/*
	function sottotipo($id_prat) {

		$sql=new query($this->conn);
		$query="select * from user_tab_cols where COLUMN_NAME like '%SOTTOTIPO%' and table_name='{$this->service}_CONDIZIONI'";
		$sql->exec($query);
		while($sql->get_row()) {
			$cols[]=$sql->row['COLUMN_NAME'];
		}

		foreach($cols as $key=>$val) {
			$sql=new query($this->conn);
			$q="select VARIAZIONE,".$val." from {$this->service}_CONDIZIONI where ID_PRAT=$id_prat";
//			echo $q.";<br>";
			$sql->exec($q);
			while($sql->get_row()) {
				if($sql->row[$val]!="") {
//					echo $sql->row[$val]." ";
					$val=strtolower(str_replace("SOTTOTIPO_","",$val));
					$val=".".substr($val,0,1).".".substr($val,1,2);
					$val=rtrim($val,".");
					$sql_=new query($this->conn);
					$query_prima="SELECT code1||NVL2(CODE2,'.'||CODE2, NULL)||NVL2(CODE3,'.'||CODE3, NULL)||NVL2(CODE4,'.'||code4, NULL) as TYPES_CHECKLIST FROM CP_VI_TIPOLOGIA_DOMANDA TIPOLOG, CP_VI_TIP_DOM TIP_DOM WHERE TIP_DOM.CODE=TIPOLOG.ID AND TIP_DOM.ID_PRAT=$id_prat
					and code1||NVL2(CODE2,'.'||CODE2, NULL) = '{$sql->row['VARIAZIONE']}'";
//					echo $query_prima;
					$sql_->exec($query_prima);
					$sql_->get_row();
//					echo $sql_->row['TYPES_CHECKLIST'];
					$result[]=$sql_->row['TYPES_CHECKLIST'].$val;
					//$result.="<br>";
				}
			}
		}
//		if(count($result)==0) {
//			$sql_=new query($this->conn);
//			$service=str_replace("_","",$this->service);
//			$query_prima="SELECT {$service}TYPES_CHECKLIST($id_prat) as A from dual";
//			$sql_->exec($query_prima);
//			$sql_->get_row();
//			$result[]=$sql_->row['A'];
//		}
//		$result=rtrim($result," ");
//		$result=rtrim($result,",");

		return $result;
	}
	*/
	
	
	function curl_get($url, array $get = NULL, array $options = array())
	{   
	    $defaults = array(
	        CURLOPT_URL => $url. (strpos($url, '?') === FALSE ? '?' : ''). http_build_query($get),
	        CURLOPT_HEADER => 0,
	        CURLOPT_RETURNTRANSFER => TRUE,
	        CURLOPT_TIMEOUT => 4
	    );
	   
	    $ch = curl_init();
	    curl_setopt_array($ch, ($options + $defaults));
	    if( ! $result = curl_exec($ch))
	    {
	        trigger_error(curl_error($ch));
	    }
	    curl_close($ch);
	    return $result;
	} 
}


?>
