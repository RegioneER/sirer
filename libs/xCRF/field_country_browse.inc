<?
/**
 * @package Fields
 */
	include_once "field.inc";

	class field_country_browse extends field{
	
		function open_($value){
		    global $in;
//    		global $inputval;
    		$inputval=$this->db_vars;
        $ret='<tr id="'.$this->attributes['VAR'].'" style="display:">';
        $txt=$this->testo;
        if ($in['salva']!='' && $this->attributes['SAVE']=='obbligatorio' && ($this->attributes['CONDITION']=='' || ($this->attributes['CONDITION']!='' && $in[$this->attributes['CONDITION']]==$this->attributes['CONDITION_VALUE']) )) {
        	if ($this->attributes['CONTROLLO']=='testo') {
        		if ($in[$this->attributes['VAR']]=='') {
        			$this->validata=false;
        			$txt.="<br/><font size='-1' color='red'>Errore!!!Il campo deve essere testuale e non vuoto</font>";
        		}
        	}
        	if ($this->attributes['CONTROLLO']=='numerico') {
        		$this->validata=false;
        		$txt.="<br/><font size='-1' color='red'>Errore!!!Il campo deve essere numerico e non nullo</font>";
        	}
        }
        $value=$inputval[$this->attributes['VAR']];
        if ($in[$this->attributes['VAR']]!='') $value=$in[$this->attributes['VAR']];
        $this->input_txt=$txt;
        $input_html='
        <input type="hidden" name="RET" value="DESCR"/><input type="hidden" name="sfoglia_table" value="PAESI_ISO" />
        <input name="'.$this->attributes['VAR'].'" type="text" value="'.$value.'" />&nbsp;
				<input type="submit" name="SFOGLIA" value="Search"  onClick="url_sfoglia=build_sfoglia_url(\'Cerca\',\'DESCR\',\'PAESI_ISO\');apri_window(url_sfoglia);return false;"/>
				&nbsp;&nbsp;
				<input type="submit" name="SFOGLIA" value="Explore"  onClick="url_sfoglia=build_sfoglia_url(\'Sfoglia\',\'DESCR\',\'PAESI_ISO\');apri_window(url_sfoglia);return false;"/>';
         $this->input_field=$input_html;
        if (isset($this->attributes['COLSPAN']) and $this->cols_form>1) $ret.='<td  class="input_txt" colspan="'.$this->cols_form.'">'.$txt.$input_html.'</td>';
        else $ret.='<td class="destra">'.$txt.'</td><td class="input">'.$input_html.'</td></tr>';
     
		}
		
		function close_($value){
	   	global $in;
	    $ret='<tr id="'.$this->attributes['VAR'].'" style="display:">';
	    $txt=$this->testo;
	    $input_html='<b><i><font color="#333300"><span class="textfield">'.$value.'</span></font></i></b>';
	    $this->input_txt=$txt;
	    $this->input_field=$input_html;
	    if (isset($this->attributes['COLSPAN']) and $this->cols_form>1) $ret.='<td  class="input_txt" colspan="'.$this->cols_form.'">'.$txt.$input_html.'</td>';
	    else $ret.='<td class="destra">'.$txt.'</td><td class="input"><b><i><font color="#333300"><span class="textfield">'.$input_html.'</span></font></i></b></td></tr>';
		}

	}
	

?>