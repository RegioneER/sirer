<?

include_once "field.inc";


/**
 * Classe per la gestione di campi nascosti
 *
 * @package Fields
 */
class field_ext_farmaco extends field {

	function open_($value) {
		global $in;
		$param = $in['CODPAT'].','.$in['ESAM'].','.$in['VISITNUM'].','.$in['VISITNUM_PROGR'].','.$in['PROGR'];
		$audit_txt = "<br /><a id=\"{$this->attributes['VAR']}\" onclick=\"changes('{$this->xml_form->form['TABLE']}','{$this->attributes['VAR']}','{$param}');\"><span style=\"cursor:pointer;color:#4F5994;font-weight: bold;\">View changes</span></a>";
		if ($in['USER_TIP'] == 'DM') {
			$audit = true;
		} else {
			$audit = false;
		}
		$inputval = $this -> db_vars;
		$in = $this -> session_vars;
		//echo $this -> attributes['VAR'] . ":" . $value . "<hr>";
		if ($value == '') {
			if (count($this -> values) > 0)
				if (isset($this -> values) && is_array($this -> values))
					foreach ($this->values as $key => $val) {
						$value = $key;
						$inputval[$this -> attributes['VAR']] = $value;
					}
		}
		if ($in[$this -> attributes['VAR']] != '')
			$value = $in[$this -> attributes['VAR']];
		$value = str_replace("\"", "&quot;", $value);
		$varIncl = ($this -> attributes['ESCLUDI']?'1':'') . ($this -> attributes['INCLUDI']?'2':''); 
		$this -> input_field = '<input type="button" onclick="ext_farmaco(\'' . $this -> attributes['VAR'] . '\',\''. $this -> attributes['ESCLUDI'] . '\',\'' . $this -> attributes['INCLUDI'] . '\',\'' . $varIncl . '\');" name="' . $this -> attributes['VAR'] . '_BTN" value="' . ($value == '' ? 'Scegli ATC' : $value) . '"/>' . ($audit?$audit_txt:"");
		$this -> input_field .= '<input type="hidden" name="' . $this -> attributes['VAR'] . '" value="' . $value . '"/>';
	}

	function close_($value) {

		$in = $this -> session_vars;
		$ret = '<tr id="' . $this -> attributes['VAR'] . '" style="display:">';
		$txt = $this -> testo;

		$input_html = $value;
		if ($input_html == '')
			$input_html = '&nbsp;';
		$this -> input_txt = $txt;

		$this -> input_field = '<b><i><font color="#333300"><span class="textfield">' . $input_html . '</span></font></i></b>' . $this -> attributes['DEF'];
		if (isset($this -> attributes['COLSPAN']) and $this -> cols_form > 1)
			$ret .= '<td  class="input_txt" colspan="' . $this -> cols_form . '">' . $txt . $input_html . '';
		else
			$ret .= '<td class="destra">' . $txt . '</td><td class="input"><b><i><font color="#333300"><span class="textfield">' . $input_html . '</span></font></i></b>';

	}

}
?>
