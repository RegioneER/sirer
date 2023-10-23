<?

include_once "field_textarea.inc";

class field_richeditor extends field_textarea {

	function open_($value){
		global $conn;
		$file_original=$this->attributes['FILE_TEMPLATE'];
		$file_template=$this->attributes['FILE_TEMPLATE'];
		
		if ($this->attributes['VISTA_SUBST'] != '') {
			$sql_query_vista = "select * from {$this->xml_form->prefix}_{$this->attributes['VISTA_SUBST']} where {$this->config_service['PK_SERVICE']}={$this->session_vars[$this->config_service['PK_SERVICE']]} and progr={$this->session_vars['PROGR']} and esam={$this->session_vars['ESAM']} and visitnum={$this->session_vars['VISITNUM']} and visitnum_progr={$this->session_vars['VISITNUM_PROGR']}"; 
			
			$sql_vista = new query ( $this->conn );
			$sql_vista->exec ( $sql_query_vista );
			$sql_vista->get_row ();
		}
//		echo $sql_query_vista."<br />";
		if(isset($_GET['PROGR']))
		$progr=$_GET['PROGR'];
		else $progr=1;

		if ($_GET[$this->config_service['PK_SERVICE']] != '') {
			$sql_query = "select * from {$this->xml_form->form['TABLE']} where {$this->config_service['PK_SERVICE']}={$this->session_vars[$this->config_service['PK_SERVICE']]}
			and template_type='{$this->attributes['TEMPLATE_TYPE']}' and ESAM={$this->session_vars['ESAM']} 
			and VISITNUM={$this->session_vars['VISITNUM']} and VISITNUM_PROGR={$this->session_vars['VISITNUM_PROGR']} and PROGR=$progr";
			$sql = new query ( $this->conn );
			$sql->exec ( $sql_query );
			$sql->get_row ();
		}
//		echo $sql_query;

//		$sql_query_c = "select COUNTRY from {$this->xml_form->prefix}_rec where id_prat = {$this->session_vars['ID_PRAT']}";
//		$sql_c = new query ( $this->conn );
//		$sql_c->exec ( $sql_query_c );
//		$sql_c->get_row ();
		
//		if(!file_exists($file_template)) $file_template=$file_original;

		if($this->session_vars['azzera']=="yes" || ($this->attributes['NO_FEEDBACK']!="" && $sql->numrows==0) || $value=="") {

			$value=file_get_contents($file_template);

			foreach($sql_vista->row as $key => $val) {
					$value=preg_replace("/<--$key-->/",$val,$value);
			}
			$value=preg_replace("/<hr>/i","<hr break>",$value);
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

		if(!isset($this->session_vars['PROGR']))
		$progr=1;
		else
		$progr=$this->session_vars['PROGR'];
		
		$url="https://".$_SERVER['SERVER_NAME'].$_SERVER['SCRIPT_NAME']."?{$this->config_service['PK_SERVICE']}={$this->session_vars[$this->config_service['PK_SERVICE']]}&VISITNUM={$this->session_vars['VISITNUM']}&ESAM={$this->session_vars['ESAM']}&PROGR={$progr}";
//		echo $url;
		$this->input_field=$alert.'
		<textarea '.$onblur.' id=\''.$this->id.'\' name="'.$this->attributes['VAR'].'"
		cols="'.$this->attributes['TCOLS'].'" rows="'.$this->attributes['ROWS'].'"
		>'.$value.'</textarea>
		';
		$disabled_all_mail="";
		$disabled_all="";

		
//		$this->input_field.='<p align="center"><input type="button" style="color:red;"	value="Azzera template" onclick="window.location.href = \''.$url.'&azzera=yes\';" />';
//		$this->input_field.='<p align="center"><input type="button" style="color:blue;"	value="Stampa" onclick="CKEDITOR.tools.callFunction(11, this); return false;" />';
//		$this->input_field.='<input '.$disabled_all.' type="button" value="Stampa" onclick="window.open(\''.$url.'&tb='.$this->xml_form->form['TABLE'].'&TEMPLATE_TYPE=&stampa_template=yes&TEMPLATE_TYPE='.$this->attributes['TEMPLATE_TYPE'].'\',\'_blank\');" />
//		<input '.$disabled_all.' type="button" value="Stampa PDF" onclick="window.open(\''.$url.'&tb='.$this->xml_form->form['TABLE'].'&stampa_template=pdf&TEMPLATE_TYPE='.$this->attributes['TEMPLATE_TYPE'].'\',\'_blank\');" />
//		<input '.$disabled_all_mail.' type="button" style="color:green;" value="Invia Mail" onclick="window.location.href = \''.$url.'&tb='.$this->xml_form->form['TABLE'].'&mail_template=yes&TEMPLATE_TYPE='.$this->attributes['TEMPLATE_TYPE'].'\';" />
//		<br /><span style="color:#ff0000 !important;font-weight:bold;">ATTENZIONE: salvare la lettera prima di stampare o inviare la mail o chiudere la valutazione.</span>
//		</p>';

		if ($this->attributes['TOOLBAR'] != '')
			$toolbar = $this->attributes['TOOLBAR'];
		else 
			$toolbar = 'Full';
		
		if (file_exists($_SERVER['DOCUMENT_ROOT']."/uxmr/ckeditor_config.js"))
		{
			$custom_config_file = "/uxmr/ckeditor_config.js";
		}	
		//qui definisco i parametri dell'editor (toolbar, stile e altro)
		//gli stili vanno definiti dentro il file config.js nella cartella di ckeditor
		$this->input_field.="
		<script type='text/javascript'> 
			CKEDITOR.replace( '".$this->id."', {"
			.($custom_config_file != "" ? "customConfig : '".$custom_config_file."', " : "")
			."toolbar : '".$toolbar."',
			height: '".$height."'
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
			$this->field_stmt[1]='TEMPLATE_TYPE';
			
			$value=$in[$this->attributes['VAR']];

			$this->value_stmt[0]=$value;
			$this->value_stmt[1]=$this->attributes['TEMPLATE_TYPE'];
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
			$ret[1]="TEMPLATE_TYPE VARCHAR2(50)";
			
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
// 		$sql_query = "select * from {$this->xml_form->form['TABLE']} where {$this->config_service['PK_SERVICE']}={$this->session_vars[$this->config_service['PK_SERVICE']]}
// 		and template_type='{$this->attributes['TEMPLATE_TYPE']}'
// 		and ESAM={$this->session_vars['ESAM']} and VISITNUM={$this->session_vars['VISITNUM']} and PROGR=$progr";
		$sql_query = "select * from {$this->xml_form->form['TABLE']} where {$this->config_service['PK_SERVICE']}={$this->session_vars[$this->config_service['PK_SERVICE']]}
		--and template_type='{$this->attributes['TEMPLATE_TYPE']}'
		and ESAM={$this->session_vars['ESAM']} and VISITNUM={$this->session_vars['VISITNUM']} and PROGR=$progr";
		$sql = new query ( $this->conn );
		$sql->exec ( $sql_query );
		$sql->get_row ();
		$value=$sql->row[$this->attributes['VAR']];
		$input_html='<script>
		$(document).ready(function() {$("div#div_print").click(function(){
    $("#area_stampa").printArea({mode: "popup",popClose: false, popHt: 600, popWd: 800, popTitle: \'Lettera paziente\'});
});});</script>



<span style="background-color:white;text-align:left; padding:10px;" id="area_stampa">'.$value.'</span>';
		$this->input_txt=$txt;
		//$this->input_field='<div align="right" id="div_print"><font style="font-size: medium;color: red;">Stampa</font></div><div style="background-color:white;text-align:left;margin:10px;padding:10px;">&nbsp;'.$input_html."</div>";
		$this->input_field='<div style="background-color:white;text-align:left;margin:10px;padding:10px;">&nbsp;'.$input_html."</div>";
		if (isset($this->attributes['COLSPAN'])) $ret.='<td class="input_txt" colspan="'.$this->attributes['COLSPAN'].'">'.$txt.' '.$input_html.'</td>';
		else $ret.='<td class="destra">'.$txt.'</td><td class="input">'.$input_html.'</td></tr>';
		#return $ret;
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

					$img_eq="<img src=\"images/eq_img.png\">";
					$str_testo_agg="Valore aggiunto";
					$str_testo_change="<h3 style=\"display:inline;text-decoration:underline;\">$value_changed_msg </h3><br />$old_sel_msg:<br /> $old_spec";

//					if ($this->xml_form->old_values[$this->id]!=$this->xml_form->tb_vals[$this->id]  && $this->xml_form->old_values[$this->id]=="" && $this->attributes['TYPE']=='file_doc') {
//						$testo_changed="<br/><span style='color:blue;font-weight:bold'><br/>FILE AGGIUNTO</span>";
//					} else 
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

//			}

			}

		}

		if ((isset($this->attributes['COLSPAN']) || !isset($this->attributes['VAR'])) && $this->attributes['HIDEVIS']!='yes') {
			$colspan=$cols*$this->attributes['COLSPAN'];
			if ($this->input_field=='') $this->html=$this->input_txt;
			else {
//				if ($this->input_txt!='') $this->input_txt.=":";
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
