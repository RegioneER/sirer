<?

include_once "field.inc";

/**
 * Classe per la gestione dei campi di tipo textbox
 *
 * @package CRO
 */
class field_sdvsign extends field{
	function __construct($conn=null, $xml_form=null,$i=null,$session_vars=null, $db_vars=null, $service=null, $errors=null){
		parent::field($conn, $xml_form,$i,$session_vars, $db_vars, $service, $errors);
		if($this->attributes['SHOW_CRF']=='yes' && isset($_GET['CRF_BLANK'])){
			unset($this->attributes['HIDE']);
		}
		$this->testo=str_replace("*","",$this->testo);

	}
	var $max_js;
	var $min_js;
	
	/**
	 * Costruisce il codice html del campo in visualizzazione
	 *
	 * @param String $value
	 */
	function close_($value) {
        $input_html=null;
		//		global $in;
		$sdv=new SDV_module($this->conn,$this->session_vars,$this->xml_form->config_service,$this->xml_form->config_service['service'],null);
		$value=$sdv->before_signsdv_close_($this);
		if ($this->attributes ['VAR_TYPE'] != 'text' && $this->attributes ['FM_CODE'])
		{
				if ($value  == -9911) $value = "NA";
				if ($value  == -9922) $value = "NK";
				if ($value  == -9933) $value = "ND";
				if ($value  == -9944) $value = "NP";
				if ($value  == -9955) $value = "TE";
				if ($value  == -9900) $value = "OT";
				
		} 
		$in = $this->session_vars;
		$ret = '<tr id="' . $this->attributes ['VAR'] . '" style="display:">';
		$txt = $this->testo;
		if ($in ['USER_TIP'] != 'DE' and $this->attributes ['CRYPTO'] == 'yes')
			$input_html .= '***';
		else
			$input_html .= $value;
		if ($input_html == '')
			$input_html .= '&nbsp;';
		
		if($this->deleted==2 && $this->attributes['MAIN']!="yes"){
			$input_html="<span style='text-decoration:line-through;'>$input_html</span>";
		}
		if (isset($in['AUDIT_TRAIL']) && $in['AUDIT_TRAIL']!='') {
			$audit_trail =  new audit_trail($this->service,$this->conn,$this->config_service,$this->attributes,$this->xml_form);
			$input_html.= $audit_trail->audit_trail_popup($in);
		}
			
		$db=$this->attributes['VAR'];
		if(isset ( $_GET ['CRF_ANNOTE'] )){
			$input_html .= $this->xml_form->form['TABLE'].'.'.$db;
		}
		
		$this->input_txt = $txt;
		if(!isset($_GET['CRF_BLANK'])){
			$this->input_field = '<span class="textfield"><b><i><font color="#333300"><u>' . $input_html . '</span></u></font></i></b>' . $this->attributes ['DEF'];
		}
		else{
			$this->input_field = '<span class="textfield"><b><i><font color="#333300"><u>' . $input_html . '___________</span></u></font></i></b>&nbsp;' . $this->attributes ['DEF'];
		}
		if (isset ( $this->attributes ['COLSPAN'] ) and $this->cols_form > 1){
			$ret .= '<td  class="input_txt" colspan="' . $this->cols_form . '">' . $txt . $input_html . '';
			}
		else{
			$ret .= '<td class="destra">' . $txt . '</td><td class="input"><b><i><font color="#333300"><span class="textfield">' . $input_html . '</span></font></i></b>';
		}
		#return $ret;
		
	}
	
	/**
	 * Costruisce il codice html del campo in compilazione
	 *
	 * @param String $value
	 */
	function open_($value){
		
		return $this->close_($value);
	}
	
				
}

?>
