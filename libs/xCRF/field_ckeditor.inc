<?
/**
 * @package Fields
 */
include_once "libs/field_textarea.inc";

//ATTENZIONEATTENZIONEATTENZIONEATTENZIONEATTENZIONEATTENZIONE

//ATTENZIONE: personalizzato per CHECKPOINT

//utilizzare il piu generico field_rich_editor.inc

class field_ckeditor extends field_textarea{

	function open_($value){
		global $conn;
		$file_original=$this->attributes['FILE_TEMPLATE'];
		$file_template=$this->attributes['FILE_TEMPLATE'];
		$today=date("d/m/Y");
		

		$sql_query_vista = "select * from {$this->xml_form->prefix}_{$this->attributes['VISTA_SUBST']} where ID_PRAT={$this->session_vars['ID_PRAT']}";
		$sql_vista = new query ( $this->conn );
		$sql_vista->exec ( $sql_query_vista );
		$sql_vista->get_row ();
		if(isset($_GET['PROGR']))
		$progr=$_GET['PROGR'];
		else $progr=1;

		$sql_query = "select * from {$this->xml_form->form['TABLE']} where ID_PRAT={$this->session_vars['ID_PRAT']}  
		and template_type='{$this->attributes['TEMPLATE_TYPE']}' and ESAM={$this->session_vars['ESAM']} 
		and VISITNUM={$this->session_vars['VISITNUM']} and PROGR=$progr";
		$sql = new query ( $this->conn );
		$sql->exec ( $sql_query );
		$sql->get_row ();
		$sql_query_c = "select COUNTRY from {$this->xml_form->prefix}_rec where id_prat = {$this->session_vars['ID_PRAT']}";
		$sql_c = new query ( $this->conn );
		$sql_c->exec ( $sql_query_c );
		$sql_c->get_row ();

		if($sql_c->row['COUNTRY']==20 && 
		$this->attributes['TEMPLATE_TYPE']!="annullgu" && 
		$this->attributes['TEMPLATE_TYPE']!="stampati" && 
		$this->attributes['TEMPLATE_TYPE']!="stampati2" &&
		$this->attributes['TEMPLATE_TYPE']!="stampati3" &&  
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
		if($sql_->row['TIPO_VAR1']==1 && ($this->attributes['TEMPLATE_TYPE']=="valid" || $this->attributes['TEMPLATE_TYPE']=="notvalid")) {
			$file_template=str_replace("_eng.htm","_eng_single.htm",$file_template);
			if(preg_match("/IA/",$sql_->row['TYPES'])) {
				$file_template=str_replace("_eng_single.htm","_eng_single_IA.htm",$file_template);
			} else if(preg_match("/IB/",$sql_->row['TYPES']) ) {
				$file_template=str_replace("_eng_single.htm","_eng_single_IB.htm",$file_template);
			}
		} else if($sql_->row['TIPO_VAR1']==2 && ($this->attributes['TEMPLATE_TYPE']=="valid" || $this->attributes['TEMPLATE_TYPE']=="notvalid")) {
			$file_template=str_replace("_eng.htm","_eng_grouped.htm",$file_template);
		}
		if($sql_->row['TIPO_VAR']==1 && $this->attributes['TEMPLATE_TYPE']=="cts" && preg_match("/CP_II/",$_SERVER['REQUEST_URI'])) {
			$file_template=str_replace(".htm","_mr.htm",$file_template);
		} else if($sql_->row['TIPO_VAR']==2 && $this->attributes['TEMPLATE_TYPE']=="cts" && preg_match("/CP_II/",$_SERVER['REQUEST_URI'])) {
			$file_template=str_replace(".htm","_naz.htm",$file_template);
		}
		if($this->session_vars['azzera']=="yes" || ($this->attributes['NO_FEEDBACK']!="" && $sql->numrows==0) || $value=="") {
			$value=file_get_contents("../".$file_template);
			$sott_array=$this->sottotipo($this->session_vars['ID_PRAT']);
			$sott=implode(", ",$sott_array);
			$value=preg_replace("/<--TYPES_CHECKLIST-->/",$sott,$value);
			preg_match_all("!\<--(.*?)--\>!e", $value, $matches);
//print_r($matches);
			foreach ($matches[1] as $key=>$val){
				$splits=preg_split("!\.!", $val);
				if (count($splits)>1)
				$field[$splits[0]][]=$splits[1];
			}
			foreach ($field as $key=>$val){
				$sql_query="select ";
				$fields='';
				foreach ($val as $k=>$fname){
					if ($fields!='') $fields.=",";
					$fields.=" $fname";
					$data[$key.".".$fname]='n.d.';
				}
				if ($key=='DUAL') $sql_query.=$fields." from {$key}";
				else $sql_query.=$fields." from {$key} where id_prat={$this->session_vars['ID_PRAT']}";
				//echo "<li>$sql_query</li>";
				$sql_dati = new query ( $this->conn );
				$sql_dati->ins_upd("alter session set nls_date_format = 'DD/MM/YYYY'");
				$sql_dati->exec ( $sql_query );
				if ($sql_dati->numrows==1) {
					$sql_dati->get_row();
					foreach ($sql_dati->row as $fname=>$valore){
						$data[$key.".".$fname]=$valore;
					}
				}else {
						
						$data[$key.".".$fname]='';
					while ($sql_dati->get_row()){
						foreach ($sql_dati->row as $fname=>$valore){
						$data[$key.".".$fname].="$valore<br/>";
					}
					}
				}
			}
			foreach ($data as $fname=>$val){
					$value=preg_replace("/<--$fname-->/",$val,$value);
			}
			//foreach($sql_vista->row as $key => $val) {
			//		$value=preg_replace("/<--$key-->/",$val,$value);
			//}
			$value=preg_replace("/<hr>/i","<hr break>",$value);
			$alert="<h3 style=\"color:red;\">La lettera non è mai stata salvata</h3>";
		} else if($sql->numrows!=0){
			$value=$sql->row[$this->attributes['VAR']];
			$alert="<h3 style=\"color:green;\">La lettera è salvata</h3>";
		} else {
			$alert="";
		}
		$alert=$alert_rms;
		echo "<!--".$file_template."-->";

		$ret='<tr id="'.$this->attributes['VAR'].'" style="display:">';
		$txt=$this->testo;
		foreach ($this->xml_form->fields as $key => $val){
			if ($this->attributes['VAR']==$val['CONDITION']) $onblur="onblur=\"cf();\"";
		}
		$height=$width="";
		if($this->attributes['HEIGHT']!="") $height=$this->attributes['HEIGHT'];
		else $height="100%";
		if(!isset($this->session_vars['PROGR']))
		$progr=1;
		else
		$progr=$this->session_vars['PROGR'];

		$disabled_all_mail="";
		$disabled_all="";
		if($sql->numrows==0) {
			$disabled_all="style=\"color:gray !important;\" onclick=\"alert('Salvare la lettera prima di effettuare operazioni');return false;\"";
		}
		if(($this->attributes['TEMPLATE_TYPE']=='rev_tecnica' && $sql->row['TEMPLATE_FILE']!='')||($this->attributes['TEMPLATE_TYPE']=='rev' && $sql->row['TEMPLATE_FILE']!='')) {
			if($disabled_all=="") { 
				//$disabled_all_mail="style=\"color:gray !important;\" onclick=\"alert('Non è possibile richiedere più di una richiesta integrazione all\'azienda');return false;\"";
			} else {
				$disabled_all_mail=$disabled_all;
			}
		}
		$alert_atto="";
		if($this->attributes['ATTO']!="") {
			
			if($this->attributes['ATTO']=="DETERMINA") {
			
				$sql_close="select NUMERO_ATTO, to_char(DET_DEF_DT,'DD/MM/YYYY') as DET_DEF_DT from CP_II_ASSEGNA_DET where id_prat={$this->session_vars['ID_PRAT']}";
				$sql2=new query($this->conn);
				$sql2->exec($sql_close);
				$sql2->get_row();
				$data_atto_bd=$sql2->row['DET_DEF_DT'];
				$disabled="";
				$num_atto=$sql2->row['NUMERO_ATTO'];
				$num_data_atto=$num_atto." del ".$data_atto_bd;
				$genera_button="<input style=\"color:blue;\" $disabled_gen type=\"button\" value=\"Genera numerazione atto\"  onclick=\"show_hide('gen_atti_div');\" />";
				if($num_atto!="") {
					$genera_button="<b>Atto generato: $num_atto del $data_atto_bd</b><br />";
				} else {
					$disabled_pop="onclick=\"alert('Attenzione, la numerazione non è stata generata. Generarla tramite l\'apposito bottone e in seguito popolare la determina');return false;\"";
				}
				
			} else if($this->attributes['ATTO']=="DINIEGO") {
			
				$sql_close="select NUMERO_ATTO, to_char(DET_DEF_DT,'DD/MM/YYYY') as DET_DEF_DT from CP_II_ASSEGNA_DINIEGO where id_prat={$this->session_vars['ID_PRAT']}";
				$sql2=new query($this->conn);
				$sql2->exec($sql_close);
				$sql2->get_row();
				$data_atto_bd=$sql2->row['DET_DEF_DT'];
				$disabled="";
				$num_atto=$sql2->row['NUMERO_ATTO'];
				$num_data_atto="<b>Numero atto: ".$num_atto." del ".$data_atto_bd."</b>";
				$genera_button="<input style=\"color:blue;\" $disabled_gen type=\"button\" value=\"Genera numerazione atto\"  onclick=\"show_hide('gen_atti_div');\" />";
				if($num_atto!="") {
					$genera_button="<b>Atto generato: $num_atto del $data_atto_bd</b><br />";
				} else {
					$disabled_pop="onclick=\"alert('Attenzione, la numerazione non è stata generata. Generarla tramite l\'apposito bottone e in seguito popolare la determina');return false;\"";
				}
				
			} else if($this->attributes['ATTO']=="PROROGHE") {
			
				$sql_close="select NUMERO_ATTO, to_char(DET_DEF_DT,'DD/MM/YYYY') as DET_DEF_DT from CP_II_ASSEGNA_PROROGA where id_prat={$this->session_vars['ID_PRAT']}";
				$sql2=new query($this->conn);
				$sql2->exec($sql_close);
				$sql2->get_row();
				$data_atto_bd=$sql2->row['DET_DEF_DT'];
				$disabled="";
				$num_atto=$sql2->row['NUMERO_ATTO'];
				$num_data_atto="<b>Numero atto: ".$num_atto." del ".$data_atto_bd."</b>";
				$genera_button="<input style=\"color:blue;\" $disabled_gen type=\"button\" value=\"Genera numerazione atto\"  onclick=\"show_hide('gen_atti_div');\" />";
				if($num_atto!="") {
					$genera_button="<b>Atto generato: $num_atto del $data_atto_bd</b><br />";
				} else {
					$disabled_pop="onclick=\"alert('Attenzione, la numerazione non è stata generata. Generarla tramite l\'apposito bottone e in seguito popolare la determina');return false;\"";
				}
				
			} else if($this->attributes['ATTO']=="RETTIFICHE") {
			
				$sql_close="select NUMERO_ATTO, to_char(DET_DEF_DT,'DD/MM/YYYY') as DET_DEF_DT from CP_II_ASSEGNA_RETTIF where id_prat={$this->session_vars['ID_PRAT']}";
				$sql2=new query($this->conn);
				$sql2->exec($sql_close);
				$sql2->get_row();
				$data_atto_bd=$sql2->row['DET_DEF_DT'];
				$disabled="";
				$num_atto=$sql2->row['NUMERO_ATTO'];
				$num_data_atto="<b>Numero atto: ".$num_atto." del ".$data_atto_bd."</b>";
				$genera_button="<input style=\"color:blue;\" $disabled_gen type=\"button\" value=\"Genera numerazione atto\"  onclick=\"show_hide('gen_atti_div');\" />";
				if($num_atto!="") {
					$genera_button="<b>Atto generato: $num_atto del $data_atto_bd</b><br />";
				} else {
					$disabled_pop="onclick=\"alert('Attenzione, la numerazione non è stata generata. Generarla tramite l\'apposito bottone e in seguito popolare la determina');return false;\"";
				}
				
			}
			
			$url="https://".$_SERVER['SERVER_NAME'].$_SERVER['SCRIPT_NAME']."?ID_PRAT={$this->session_vars['ID_PRAT']}&VISITNUM={$this->session_vars['VISITNUM']}&ESAM={$this->session_vars['ESAM']}&PROGR={$progr}";
			$atto_buttons="<table style=\"margin:auto;text-align:center;\"><tr><td>
				$genera_button
				<div id=\"gen_atti_div\" style=\"margin:auto;display:none;text-align:center;\">
					<script>DateInput('data_atto', true, 'DD/MM/YYYY', '$today');</script>
					<input style=\"color:blue;font-weight:bolder;\" type=\"button\" value=\"Genera\"  onclick=\"window.location.href = '$url&genera={$this->attributes['ATTO']}&data_atto='+document.forms[0].data_atto.value;\" />
				</div>	
				</td>
				<!--td>
					<input style=\"color:blue;\" $disabled_pop $disabled_all type=\"button\" value=\"Popola con numerazione atto\" onclick=\"window.location.href = '$url&popola={$this->attributes['ATTO']}';\" />
				</td-->

			</tr>
			</table>
			";
			if($data_atto_bd!="" && $num_atto!="") {
				if(preg_match("/<!--NUMERO_DATA_ATTO-->/",$value)) {
					//se è la prima volta che sostituisce num-data atto, c'è bisogno di salvare per fissarlo alla lettera
					$alert_atto='<div style="color:red;font-weight:bold;text-align:center;font-size:13px;margin:0 auto;">Il numero di protocollo è stato aggiunto alla lettera. Salvarla prima di uscire dalla pagina o di inviare la mail. </div>';
					$value=preg_replace("/<!--NUMERO_DATA_ATTO-->/",$num_data_atto,$value);
				}

			}
		}
		
		$url="https://".$_SERVER['SERVER_NAME'].$_SERVER['SCRIPT_NAME']."?ID_PRAT={$this->session_vars['ID_PRAT']}&VISITNUM={$this->session_vars['VISITNUM']}&ESAM={$this->session_vars['ESAM']}&PROGR={$progr}";
		$this->input_field=$alert.' '.$alert_atto.'
		<textarea '.$onblur.' id=\''.$this->id.'\' name="'.$this->attributes['VAR'].'"
		cols="'.$this->attributes['TCOLS'].'" rows="'.$this->attributes['ROWS'].'"
		>'.$value.'</textarea>
		';
		if ($this->attributes['NOMAIL']=="yes"){
			$mailButton="";
		}else $mailButton='
		<input '.$disabled_all_mail.' type="button" style="color:green;" value="Invia Mail" onclick="if(confirm(\'Attenzione: verrà inviata una mail all\\\'azienda contenente la lettera\')) window.location.href = \''.$url.'&tb='.$this->xml_form->form['TABLE'].'&mail_template=yes&TEMPLATE_TYPE='.$this->attributes['TEMPLATE_TYPE'].'\';" />
		
		'; 
		$this->input_field.='<p align="center"><input type="button" style="color:red;"	value="Azzera template" onclick="window.location.href = \''.$url.'&azzera=yes\';" />
		<input '.$disabled_all.' type="button" value="Stampa" onclick="window.open(\''.$url.'&tb='.$this->xml_form->form['TABLE'].'&TEMPLATE_TYPE=&stampa_template=yes&TEMPLATE_TYPE='.$this->attributes['TEMPLATE_TYPE'].'\',\'_blank\');" />
		<input '.$disabled_all.' type="button" value="Stampa PDF" onclick="window.open(\''.$url.'&tb='.$this->xml_form->form['TABLE'].'&stampa_template=pdf&TEMPLATE_TYPE='.$this->attributes['TEMPLATE_TYPE'].'\',\'_blank\');" />
		'.$mailButton.'<br /><span style="color:#ff0000 !important;font-weight:bold;">ATTENZIONE: salvare la lettera prima di stampare o inviare la mail o chiudere la valutazione.</span>
		<br />'.
		$atto_buttons
		.'</p>';
		//se la lettera riguarda un atto, se è stata già salvata, se è la prima volta che sostituisce la data-num. atto nel template
		//SI DEVE SALVARE PRIMA DI INVIARE MAIL O USCIRE
		if($this->attributes['ATTO']!="") {
			$this->input_field.=$alert_atto;
		}
		$this->input_field.='
		<script type="text/javascript">
			CKEDITOR.replace( \''.$this->id.'\', {
			toolbar : \'Full\',
			height: \''.$height.'\'
    	});
		</script>';
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
						
						$testo_js=make_js($this->testo);
						$this->errors[$this->attributes['VAR']]="Il campo ï¿½ obbligatorio";
					}
				}
			}
			else {
				if ($in[$this->attributes['VAR']]!='' && $val=='obbligatorio') {
					$this->validata=false;
					
					$testo_js=make_js($this->testo);
					$this->errors[$this->attributes['VAR']]="Il campo deve essere vuoto";
				}
			}
		}
		$this->session_vars=$in;
	}

	function insert_stmt(){
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
		$sql_query = "select * from {$this->xml_form->form['TABLE']} where ID_PRAT={$this->session_vars['ID_PRAT']}  and template_type='{$this->attributes['TEMPLATE_TYPE']}'
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
		if(count($result)==0) {
			$sql_=new query($this->conn);
			$service=str_replace("_","",$this->service);
			$query_prima="SELECT {$service}TYPES_CHECKLIST($id_prat) as A from dual";
			$sql_->exec($query_prima);
			$sql_->get_row();
			$result[]=$sql_->row['A'];
		}
//		$result=rtrim($result," ");
//		$result=rtrim($result,",");

		return $result;
	}
	
		/**
	 * Costruisce il codice html del campo in visualizzazione
	 *
	 * @param boolean $equery
	 */
	function make_close_html($equery=false){
		if (isset($this->attributes['VAR'])) $this->html='<tr id='.$this->attributes['VAR'].' style="display:">';
		$function_to_call='close_';
		$in=$this->session_vars;
		$inputval=$this->db_vars;
		if($this->config_service['lang']=="en")
			{
				$value_changed_msg="Value is changed ";
				$old_sel_msg="old selection/value ";
			}
		else
			{
				$value_changed_msg="Il valore è cambiato ";
				$old_sel_msg="vecchia selezione/valore ";
			}
		if (isset($inputval[$this->attributes['VAR']])) $value=$inputval[$this->attributes['VAR']];
		if ($this->attributes['BYTB']!='') $this->fields_value_bytb($this->attributes['BYTB']);
		if (method_exists($this,$function_to_call)) $this->{$function_to_call}($value);
		$cols=$this->attributes['COLS']+0;
		if ($cols==0) $cols=1;
		$this->input_txt=preg_replace("/<a(.*?)<\/a>/","",$this->input_txt);
		$this->input_txt=str_replace("<font color=red>*</font>", "", $this->input_txt);
		if ($this->attributes['ONLY_AF']!='') $this->attributes['COLSPAN']="2";
		
		if ($equery){

			$query="select STATO,EQUERY_INT from {$this->service}_eq where {$this->config_service['PK_SERVICE']}={$in[$this->config_service['PK_SERVICE']]} and equery_int=(select max(equery_int) from {$this->service}_eq where {$this->config_service['PK_SERVICE']}={$in[$this->config_service['PK_SERVICE']]})";
			$sql=new query($this->conn);
			$sql->get_row($query);
			$stato=$sql->row['STATO'];
			$eq_int=$sql->row['EQUERY_INT'];

			if ($this->input_field!='' && $this->attributes['TYPE']!='hidden'){
				$testo_changed='';
				$img_eq='';
				if ($this->xml_form->old_values[$this->id]!=$this->xml_form->tb_vals[$this->id] && $stato==2){
					if($this->attributes['TYPE']=='file_doc') {
						if($this->xml_form->old_values_docs_nomi[$this->id]!="")
						$old_spec="<br /><a class=\"normal_link\" href=\"WCA/download.php?id={$this->xml_form->old_values[$this->id]}\"><span><img src=\"../images/word.gif\" alt=\"documento vecchio \" />{$this->xml_form->old_values_docs_nomi[$this->id]}</span></a>";
						else
						$old_spec="<h3 style=\"display:inline;text-decoration:underline;\">Valore aggiunto: Non era presente un allegato</h3>";
					} else				
					
					if (isset($this->xml_form->old_values['D_'.$this->id])){
						$old_spec=$this->xml_form->old_values['D_'.$this->id];
					}
					else $old_spec=$this->xml_form->old_values[$this->id];

					$img_eq="<i class=\"fa fa-comments\" style=\"font-size:1.2em;\"></i>";
					$str_testo_agg="Valore aggiunto";
					$str_testo_change="<h3 style=\"display:inline;text-decoration:underline;\">$value_changed_msg </h3><br />$old_sel_msg:<br /> $old_spec";
					if ($old_spec==''){
						$testo_changed="<br/><span style='color:blue;font-weight:bold'><br/>$str_testo_agg</span>";
					} else {
						$testo_changed="<br/><span style='color:red;font-weight:bold'><br/>$str_testo_change</span>";
					}
				} else if($this->xml_form->old_values[$this->id]==$this->xml_form->tb_vals[$this->id]) {
					$testo_changed="";
				}
			$this->close_($value);
			$this->input_txt.=$testo_changed;

		    $this->input_txt="
		    <table width=\"100%\" border=0>
				<tr>
					<td valign=top align=left>
					$img_eq
					</td>
					<td valign=top align=right>
					{$this->input_txt}
					</td>
				</tr>
			</table>
		    ";
			}

		}

		if ((isset($this->attributes['COLSPAN']) || !isset($this->attributes['VAR'])) && $this->attributes['HIDEVIS']!='yes') {
			$colspan=$cols*$this->attributes['COLSPAN'];
			if ($this->input_field=='') $this->html=$this->input_txt;
			else {
				$this->html='<td  class="input" colspan="'.$colspan.'">'.$this->input_txt.$this->input_field.'</td>';
			}
		}
		else
		if ($this->attributes['TYPE']!='hidden') {
			if (
			(( $this->attributes['HIDEVIS']!='yes' && ($this->condition_passed || $this->attributes['HIDE']!='yes' )) || $this->attributes['SHOW_VIS']=='yes')
			){

				$this->html='<td colspan="'.$cols.'" class="destra">'.$this->input_txt.'</td><td colspan="'.$cols.'" class="input">'.$this->input_field.'</td>';
			}
			if ($this->attributes['HIDE_THIS']!='' && $inputval[$this->attributes['VAR']]=='') $this->html='';
		}
		if ($this->attributes['TYPE']=='hidden') $this->html='';#<tr id="'.$this->attributes['VAR'].'" style="display:none">'.$this->input_field.'</tr>';

	}
	

}


?>
