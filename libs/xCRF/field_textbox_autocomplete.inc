<?

include_once "libs/field_textbox.inc";

/**
 * Classe per la gestione dei campi di tipo textbox
 *
 * @package Fields
 */
class field_textbox_autocomplete extends field_textbox {
	/**
	 * Costruisce il codice html del campo in compilazione
	 *
	 * @param String $value
	 */
	function open_($value) {
		$in = $this->session_vars;
		//		echo $in['USER_TIP'];
		//		global $inputval;
		$inputval = $this->db_vars;
		$txt = $this->testo;
		if ($this->attributes ['CHECK'] == '')
			$this->attributes ['CHECK'] = "text";

		if ($this->attributes ['SIZE'] == '')
			$this->attributes ['SIZE'] = '20';

		if ($this->attributes ['ONCHANGE'] != '')
			$onchange = "{$this->attributes['ONCHANGE']};";

		if (isset ( $this->values ) && is_array ( $this->values ))
			foreach ( $this->values as $key => $val )
				$value = $val;
		if ($inputval [$this->attributes ['VAR']] != '')
			$value = $inputval [$this->attributes ['VAR']];
		if ($in [$this->attributes ['VAR']] != '')
			$value = $in [$this->attributes ['VAR']];

		if ($this->attributes ['VAR_TYPE'] != 'text' && $this->attributes ['FM_CODE']) {
		    if(strtoupper($this->config_service['lang'])=='IT'){
                 
                if ($value == - 9911)
                    $value = "NA";
                if ($value == - 9922)
                    $value = "NN";
                if ($value == - 9933)
                    $value = "ND";
                if ($value == - 9944)
                    $value = "NP";
                if ($value == - 9955)
                    $value = "TE";
                if ($value == - 9900)
                    $value = "OT";
                  
            }
            else{
    			if ($value == - 9911)
    				$value = "NA";
    			if ($value == - 9922)
    				$value = "NK";
    			if ($value == - 9933)
    				$value = "ND";
    			if ($value == - 9944)
    				$value = "NP";
    			if ($value == - 9955)
    				$value = "TE";
    			if ($value == - 9900)
    				$value = "OT";
            }

		}
		/*
		if($this->attributes['AUTOCOMPLETE']){
		    global $autocomplete;
            if(!$autocomplete){             
                $this->script.=$this->autocomplete_js();
                $autocomplete=true;
            }
            
            $add_jquery=$this->autocomplete_js_field();     
        }
        */
		$addfilter = '';
		if ($this->attributes ['AC_FILTERFIELD'] && $this->attributes ['AC_FILTERCOLUMN']){
			$addfilter = '&filtervalue="+$(\'[name="'.$this->attributes ['AC_FILTERFIELD'].'"]\').val()';
			$addfilter .= '+"&filtercolumn='.$this->attributes ['AC_FILTERCOLUMN'].'';
		}
        $add_jquery='
        <script type="text/javascript">
        	function initAutocomplete_'.$this->attributes ['VAR'].'(){
		        $(function() {
				    $("#ID_'.$this->attributes ['VAR'].'").autocomplete({
				        source: "ajaxsearch.php?table='.$this->attributes ['AC_TABLE'].$addfilter.'",
				        minLength: 2,
				        select: function(event, ui) {
				            //document.getElementById("#ID_'.$this->attributes ['VAR'].'").value = ui.item.value;
				            $("#ID_'.$this->attributes ['VAR'].'").val(ui.item.value);
				            //document.getElementById("#ID_'.$this->attributes ['VAR'].'").form.submit();
				        }
				    });
				});
			}
			initAutocomplete_'.$this->attributes ['VAR'].'();
		</script>
        ';
	//modifica by G.Tufano 19/11/2010:
    //controllo che un numero reale non sia tra 0 e 1, altrimenti appare tipo '.32' nella casella di testo
        if ($this->attributes ['VAR_TYPE'] == 'number' && (abs($value) > 0 && abs($value) < 1)){
            if ($value > 0)
                $value = abs($value);
            else $value = "-". abs($value);
        }
		
		
		$disabled = "";
		if ($this->attributes ['DISABLED'] != '') {
			if ($value != '')
				$disabled = "disabled=\"disabled\"";
			$this->check_js .= "
				if (document.forms[0].{$this->id}.value!='') document.forms[0].{$this->id}.disabled=true;
			";
		}
		if( $this->attributes['BLOCK_VALUE']=='yes' && $this->db_vars[$this->attributes['VAR']]!="") {
	  		$disabled = "disabled=\"disabled\"";
	  	}
		$action = "";

		if ($this->attributes ['ON_ACTION'] != '' && $this->attributes ['ACTION_TYPE'] != '') {
			$action = $this->attributes ['ACTION_TYPE'] . "=\"" . $this->attributes ['ON_ACTION'] . "\"";
			//         echo "$action<hr>";
		}

		if ($in ['USER_TIP'] != 'DE' && $this->attributes ['CRYPTO'] == 'yes') {
			$html_parser = new HTML_Parser ( );
			$html_parser->setAttribute ( "type", "hidden" ); 
			$html_parser->setAttribute ( "name", $this->attributes ['VAR'] );
            $html_parser->setContent ( 'XXXXXXXXXXXXXXXX' );
			$html_parser->setType ( "INPUT" );
			$this->input_field = '***' . $html_parser->print_ ();
		} else {
			if ($this->attributes ['EMAIL'] != '') {
				$val_email = split ( "@", $value );
				$this->input_field = "<input type=\"text\" name=\"{$this->attributes['VAR']}_0\" value=\"{$val_email[0]}\">@<input type=\"text\" size='20' name=\"{$this->attributes['VAR']}_1\" value=\"{$val_email[1]}\" onblur=\"document.forms[0].{$this->attributes['VAR']}.value=document.forms[0].{$this->attributes['VAR']}_0.value+'@'+document.forms[0].{$this->attributes['VAR']}_1.value\"><input type=\"hidden\" name=\"{$this->attributes['VAR']}\" value=\"{$value}\">";
			} else {
				//          echo "$action<hr>";
				if ($this->attributes ['CALL_CF'] != '')
					$cf_call = "cf();";
				if ($this->attributes ['ON_BLUR'] != '') {
					//echo "<hr>{$this->id}<hr>";
					$var = $this->id;
					$vars = split ( "_PROGR_", $var );
					$js_on_blur = preg_replace ( "/document\.forms\[0\]\.(.*?)\.value/i", "document.forms[0].\\1_PROGR_{$vars[1]}.value", $this->attributes ['ON_BLUR'] );
					//print_r($this->attributes);
					$cf_call .= "{$js_on_blur};";
					//echo "<li>$js_on_blur</li>";
				}

				$value = str_replace ( "\"", "&quot;", $value );
				$html_parser = new HTML_Parser ( );
				$html_parser->setAttribute ( "type", "text" );
				$html_parser->setAttribute ( "maxlength", $this->attributes ['VAR_SIZE'] );
				$html_parser->setAttribute ( "size", $this->attributes ['SIZE'] );
				$html_parser->setAttribute ( "name", $this->attributes ['VAR'] );
				$html_parser->setAttribute ( "onblur", $cf_call );
				if($this->attributes['ONCHANGE']!='')
					$html_parser->setAttribute ( "onchange", $onchange );
				$html_parser->setAttribute ( $disabled, "" );
				$html_parser->setAttribute ( $action, "" );
				//add id
				$html_parser->setAttribute ( "id", "ID_".$this->attributes ['VAR'] );
				$html_parser->setContent ( $value );
				$html_parser->setType ( "INPUT" );
				$this->input_field = $html_parser->print_ () . $this->attributes ['DEF'] . $agg_;
				/*
				$this->input_field='<input  type="text" maxlength="'.$this->attributes['VAR_SIZE'].'" size="'.$this->attributes['SIZE'].'"
				name="'.$this->attributes['VAR'].'" value="'.$value.'"
				onblur="'.$cf_call.'" '.
				$disabled.
				$action.'>'.$this->attributes['DEF'].''.$agg_;
				*/

			}
		}
		$this->input_txt = $txt;
		if ($this->attributes ['TEXTONLY'] == "yes") {
			$this->input_txt = $value;
			$this->input_field = '';
		}
        $this->input_field.=$add_jquery;
		//if ($this->attributes['DISABLED']!='') $this->input_field='<input type=\'hidden\' name="'.$this->attributes['VAR'].'" value="'.$value.'"><b>'.$value.'</b>';
	}
	
}

?>
