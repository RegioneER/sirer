<?
/**
 * @package Fields
 */
include_once "field.inc";

class field_data_dropdown extends field{
	/************************************
	 *
	 * Libreria Data di tipo drop down sui mesi.
	 * Molto simile alla data standard in XMR , con calendario e select sui mesi
	 * con relativa decodifica.
	 *
	 * TODO:
	 *
	 *** Funzionamento:
	 * 1- includere nel template.htm del servizio le librerie:
	 * <script type="text/javascript" src="libs/js_tooltip/calendar.js"></script>
	 * <link  href="libs/js_tooltip/calendar.css" rel="stylesheet" type="text/css" />
	 * 2- verificare che l'immagine Calendario2.jpg si prensente nella cartella (o link).
	 * [nomeservizio]/html/images/
	 *
	 *** Lingua:
	 * Default: Italiano.
	 * Per settare l'inglese , aggiungere:
	 * nel file config.inc: $config_service['lang']='en';
	 * nel file template.htm: <script type="text/javascript" src="libs/js_tooltip/calendar_en.js"></script>
	 *
	 * Per info: Andrea Colabufalo.
	 * **********************************/

	/**
	 * open_
	 * Costruisce il codice html del campo in compilazione
	 *
	 * @param string $value
	 */
	function open_($value){
		if($this->attributes['SAVE']=="") {
			$this->attributes['SAVE']="facoltativo";
		}
//		print_r($this->xml_form->salva_js);
//		$this->xml_form->salva_js='';
//		$this->xml_form->check_js='';
//		print_r($this);
		$in=$this->session_vars;
		$inputval=$this->db_vars;
//		print_r ($inputval);
//		echo $this->attributes['VAR']."<hr>";
		if ($this->attributes['ONBLUR']!='')
		{
			$check_fn='onchange="'.$this->attributes['ONBLUR'].'"';
		}
		$add_cal='
<script type="text/javascript" src="libs/js_tooltip/calendar.js"></script>
<script type="text/javascript" src="libs/js_tooltip/calendar_en.js"></script>
<link  href="libs/js_tooltip/calendar.css" rel="stylesheet" type="text/css" />

		<script>
		 var '.$this->attributes['VAR'].'_cal=new CalendarPopup(\''.$this->attributes['VAR'].'_cal_div\');
		 '.$this->attributes['VAR'].'_cal.showNavigationDropdowns();
		 '.$this->attributes['VAR'].'_cal.setReturnFunction("setMultipleValues_'.$this->attributes['VAR'].'");
		 function setMultipleValues_'.$this->attributes['VAR'].' (y,m,d) {
	     if (document.forms[0].'.$this->attributes['VAR'].'M.disabled||document.forms[0].'.$this->attributes['VAR'].'Y.disabled||document.forms[0].'.$this->attributes['VAR'].'D.disabled) return;
	     document.forms[0].'.$this->attributes['VAR'].'Y.value=y;
 		     if(m<10 && m>0){m=\'0\'+m;}
			   document.forms[0].'.$this->attributes['VAR'].'M.value=m;
		     document.forms[0].'.$this->attributes['VAR'].'D.value=d;'.$this->attributes['ONBLUR'].
		     ';
    	 }
    	 document.write(\'<a href="#" name="'.$this->attributes['VAR'].'_cal_anchor" id="'.$this->attributes['VAR'].'_cal_anchor" onclick="'.$this->attributes['VAR'].'_cal.showCalendar(\\\''.$this->attributes['VAR'].'_cal_anchor\\\');return false;" >&nbsp;<img width="20"  height="20" src="/images/Calendario2.jpg"></a><span id="'.$this->attributes['VAR'].'_cal_div" STYLE="position:absolute;visibility:hidden;background-color:white;layer-background-color:white;"></span>\');
    	 </script>

		 ';

		 $disabled = "";
		if ($this->attributes ['DISABLED'] != ''||$this->attributes ['DISABLED_ALWAYS'] != '') {
			$disabled = "disabled='disabled'";
			$add_cal='';
		}




		$txt=$this->testo;
		$keys=array_keys($this->values);
		$value_init=$keys[0];
		if ($value_init=='sysdate') $value=date("dmY");
		if ($value=='') $value=$value_init;
		if (preg_match("/\//", $value)){
			$dd=substr($value,0,2);
			$mm=substr($value,3,2);
			$yyyy=substr($value,6,4);
		}
		else {
			$dd=substr($value,0,2);
			$mm=substr($value,2,2);
			$yyyy=substr($value,4,4);
		}

		/**  Gestione NA e NK salvati in Db con form in compilazione **/
		if(!isset($this->attributes['NOT_NA'])) {
			$months_nn['NA']=-9911;
			$months_nn['NK']=-9922;

			if(substr($this->db_vars[$this->attributes['VAR'].'RC'], 0,2)!='OK')$dd=substr($this->db_vars[$this->attributes['VAR'].'RC'],0,2);
			else $dd=substr($value, 0,2);
			if(substr($this->db_vars[$this->attributes['VAR'].'RC'], 2,2)!='OK')$mm=$months_nn[substr($this->db_vars[$this->attributes['VAR'].'RC'],2,2)];
			else $mm=substr($value,2,2);
			if(substr($this->db_vars[$this->attributes['VAR'].'RC'], 4,2)!='OK')$yyyy=substr($this->db_vars[$this->attributes['VAR'].'RC'],4,2);
			else $yyyy=substr($value,4,4);
		/**  Fine Gestione NA e NK salvati in Db con form in compilazione **/
		}

		 $select_months="<select id='{$this->attributes['VAR']}M' name='{$this->attributes['VAR']}M' $disabled $check_fn>  ";
		 $months['']='';

		if($this->config_service['lang']=='en'){
		 $months['01']='jan';
		 $months['02']='feb';
		 $months['03']='mar';
		 $months['04']='apr';
		 $months['05']='may';
		 $months['06']='jun';
		 $months['07']='jul';
		 $months['08']='aug';
		 $months['09']='sep';
		 $months['10']='oct';
		 $months['11']='nov';
		 $months['12']='dec';
		 $date_def='(DD MM YYYY)';
		}
		else{
		 $months['01']='gen';
		 $months['02']='feb';
		 $months['03']='mar';
		 $months['04']='apr';
		 $months['05']='mag';
		 $months['06']='giu';
		 $months['07']='lug';
		 $months['08']='ago';
		 $months['09']='set';
		 $months['10']='ott';
		 $months['11']='nov';
		 $months['12']='dic';
		 $date_def='(GG MM AAAA)';
		}
		if(!isset($this->attributes['NOT_NA'])) {
			$months['-9911']='NA';
			$months['-9922']='NK';
		}

		 $option="";

		foreach($months as $key=>$val){
			if($mm==$key)$selected=" selected=\"selected\"";
			else $selected="";
			$option.="<option $selected value=\"$key\">$val</option>";
		}
		 $select_months.=$option."</select>";
		 	if ($in[$this->attributes['VAR'].'D']!='' && $in[$this->attributes['VAR'].'M']!='' && $in[$this->attributes['VAR'].'Y']!=''){
			if ($in[$this->attributes['VAR'].'D']!='') {
				$in[$this->attributes['VAR'].'D']='0'.$in[$this->attributes['VAR'].'D'];
				$in[$this->attributes['VAR'].'D']=substr($in[$this->attributes['VAR'].'D'],strlen($in[$this->attributes['VAR'].'D'])-2,2);
			}
			if ($in[$this->attributes['VAR'].'M']!='') {
				$in[$this->attributes['VAR'].'M']='0'.$in[$this->attributes['VAR'].'M'];
				$in[$this->attributes['VAR'].'M']=substr($in[$this->attributes['VAR'].'M'],strlen($in[$this->attributes['VAR'].'M'])-2,2);
			}
			$value=$in[$this->attributes['VAR']]=$in[$this->attributes['VAR'].'D'].$in[$this->attributes['VAR'].'M'].$in[$this->attributes['VAR'].'Y'];
			$in[$this->attributes['VAR'].'D']+=0;
			$in[$this->attributes['VAR'].'M']+=0;
		}

		$this->validata=true;
		if (isset($in['salva']) and $this->attributes['SAVE']=='obbligatorio'){
			if (!checkdate($mm,$dd,$yyyy)) {
				$txt.="<br/><font color=red size=\"-1\">Error! Date not valid</font>";
				$this->validata=false;
			}
		}
		if (isset($in['invia']) and $this->attributes['SEND']=='obbligatorio' && $this->$condition_passed){
			if (!checkdate($mm,$dd, $yyyy)) {
				//echo "<hr>Campo non validato {$this->id}<hr>";
				$txt.="<br/><font color=red size=\"-1\">Error! Date not valid</font>";
				$this->validata=false;
			}
		}
		$check_onblur='';
		if ($this->attributes['ONBLUR']!='')
		{
			$check_fn='onchange="'.$this->attributes['ONBLUR'].'"';
		}
		if ($this->attributes['CHECK_ONBLUR']!='')
		{
			$check_onblur='onblur="el=f.elements;specifiche=\'A=ON&L=0&F=0\';c1=\'<<fd00###'.$this->attributes['VAR'].'###Data errata>>\';rc=contr(c1,specifiche);if (rc) {return false}"';
		}
		$rc=$this->attributes['VAR'].'RC';
		if ($this->attributes['NDAY']!='yes')
		{

			$input_html.='<input onblur="this.value=document.forms[0].'.$this->attributes['VAR'].'D.value.toUpperCase();" type="text" name="'.$this->attributes['VAR'].'D" value="'.$dd.'" size=2 maxlength=2 '.$check_fn.' '.$disabled.'/>&nbsp;';
		}
		else
		{
//Ho messo un .= in input_html qui altrimneti non mi inseriva nell'html la hidden con la description
			$this->check_js.="
				if (f.{$this->attributes['VAR']}M.value=='' && f.{$this->attributes['VAR']}Y.value==''){
					f.{$this->attributes['VAR']}D.value='';
				}
				else f.{$this->attributes['VAR']}D.value='15';
			";
			$input_html.='<input type="hidden" name="'.$this->attributes['VAR'].'D" value="15" >';
		}
		$input_html.=$select_months.'
                     <input type="text" name="'.$this->attributes['VAR'].'Y" value="'.$yyyy.'" size=4 maxlength=4 '.$check_onblur.$check_fn.' '.$disabled.' />
                     <input type="hidden" name="'.$this->attributes['VAR'].'" value="'.$dd.$mm.$yyyy.'"/>
                     <input type="hidden" name="'.$this->attributes['VAR'].'RC" />';
		if ($inputval[$rc]=='CONTIN')
		{
			$input_html='<input type="text" name="'.$this->attributes['VAR'].'D" value="" size=2 maxlength=2 />'.$select_months.'

                     <input type="text" name="'.$this->attributes['VAR'].'Y" value="CONT" size=4 maxlength=4 '.$check_onblur.' '.$disabled.'/>
                     <input type="hidden" name="'.$this->attributes['VAR'].'" value=""/>
                     <input type="hidden" name="'.$this->attributes['VAR'].'RC" value="CONTIN"/>';
		}
		$input_html.=$add_cal;
	//	echo $input_html."<hr>";
		if ($this->attributes['DEF']!='') $input_html.='<br />'.$this->attributes['DEF'];
		$this->input_field=$input_html;
		$this->input_txt=$txt;
		if (isset($this->attributes['COLSPAN']) and $this->cols_form>1) $ret.='<td  class="input" colspan="'.$this->cols_form.'">'.$txt.':'.$input_html.'</td>';
		else $ret.='<td class="destra">'.$txt.':</td><td class="input">'.$input_html.$date_def.'</td>';

		$this->session_vars=$in;
	}

	/**
	 * close_
	 * Costruisce il codice html del campo in visualizzazione
	 *
	 * @param string $value
	 * @return string
	 */
	function close_($value){
		$inputval=$this->session_vars;
		$ret='<tr id="'.$this->attributes['VAR'].'" style="display:">';
		$txt=$this->testo;
//		echo $value;
//		print_r($this->db_vars[$this->attributes['VAR'].'RC']);
		if(substr($this->db_vars[$this->attributes['VAR'].'RC'], 0,6)=='CONTIN')
		{
			$dd='';
			$mm='';
			$yyyy='CONT';
			}
		else
		{
		if(substr($this->db_vars[$this->attributes['VAR'].'RC'], 0,2)!='OK')$dd=substr($this->db_vars[$this->attributes['VAR'].'RC'],0,2);
		else $dd=substr($value, 0,2);
		if(substr($this->db_vars[$this->attributes['VAR'].'RC'], 2,2)!='OK')$mm=substr($this->db_vars[$this->attributes['VAR'].'RC'],2,2);
		else $mm=substr($value,2,2);
		if(substr($this->db_vars[$this->attributes['VAR'].'RC'], 4,2)!='OK')$yyyy=substr($this->db_vars[$this->attributes['VAR'].'RC'],4,2);
		else $yyyy=substr($value,4,4);

		$months['']='';

		if($this->config_service['lang']=='en'){
		 $months[1]='jan';
		 $months[2]='feb';
		 $months[3]='mar';
		 $months[4]='apr';
		 $months[5]='may';
		 $months[6]='jun';
		 $months[7]='jul';
		 $months[8]='aug';
		 $months[9]='sep';
		 $months[10]='oct';
		 $months[11]='nov';
		 $months[12]='dec';
		}
		else{
		 $months[1]='gen';
		 $months[2]='feb';
		 $months[3]='mar';
		 $months[4]='apr';
		 $months[5]='mag';
		 $months[6]='giu';
		 $months[7]='lug';
		 $months[8]='ago';
		 $months[9]='set';
		 $months[10]='ott';
		 $months[11]='nov';
		 $months[12]='dic';
		}
		foreach($months as $key=> $val){
				if($mm==$key && ($mm!='NK' || $mm!='NA')) $mm=$val;
			}
		}
		if ($this->attributes['NDAY']!='yes')
		{
			$input_html=$dd.' '.$mm.' '.$yyyy;
			if($this->config_service['lang']=='en'){
				$sstr='(DD MMM YYYY)';
			}
			else{
				$sstr='(GG MMM AAAA)';
			}
		}
		else
		{
			$input_html=$mm.' '.$yyyy;
			if($this->config_service['lang']=='en')
				$sstr='(MMM YYYY)';
			else
				$sstr='(MMM AAAA)';
		}
		$rc=$this->attributes['VAR'].'RC';
		if ($inputval[$rc]=='CONTIN')
		{
			$input_html='CONT';
			$sstr=' ';
		}
//		print_r($inputval);
		if (isset($inputval['AUDIT_TRAIL']) && $inputval['AUDIT_TRAIL']!='') {
			$audit_trail =  new audit_trail($his->service,$this->conn,$this->config_service,$this->attributes,$this->xml_form);
			$input_html.= $audit_trail->audit_trail_popup($inputval);

		}

		$this->input_txt=$txt;
		if(isset ( $_GET ['CRF_ANNOTE'] )){
			$db=$this->attributes['VAR'];
			$this->input_field='<span class="textfield">'.$this->xml_form->form['TABLE'].'.'.$input_html.$db.'&nbsp;&nbsp;</span>'. $sstr;
		}
		else {
			$db="";$this->input_field='<b><i><font color="#333300"><span class="textfield">'.$input_html.'&nbsp;&nbsp;</span></font></i></b>'. $sstr;
			}

		if (isset($this->attributes['COLSPAN']) and $this->cols_form>1) $ret.='<td  class="input" colspan="'.$this->cols_form.'">'.$txt.':'.$input_html.'</td>';
		else
		$ret.='<td class="destra">'.$txt.'</td><td class="input"><b><i><font color="#333300"><span class="textfield">'.$input_html.'</span></font></i></b>'. $sstr.'</td></tr>';
		#return $ret;
	}

	/**
	 * Popola le propriet? "field_stmt" e "value_stmt" necessarie alla costruzione degli stmt di inserimento/update
	 *
	 */
	function insert_stmt($insert=true){
	//echo "<hr>entra en la funcion";
		$in=$this->session_vars;
		$conn=$this->conn;
		if($this->attributes['NNDAYVALUE']==''){$this->attributes['NNDAYVALUE']='01';}
		if($this->attributes['NNMONTHVALUE']==''){$this->attributes['NNMONTHVALUE']='01';}

		if(isset($this->attributes['FORMAT'])) $format=$this->attributes['FORMAT'];
		else $format='DDMMYYYY';
		$sql=new query($conn);
		$sql->ins_upd("ALTER SESSION SET NLS_DATE_FORMAT = '{$format}'");  //bind non necessario
		if (!$insert){
			$this->field_stmt[0]="{$this->attributes['VAR']}";
			$this->field_stmt[1]="{$this->attributes['VAR']}RC";
			return;
		}
		if ($this->attributes['TB']!='no'){
			$this->field_stmt[0]="{$this->attributes['VAR']}";
			$this->field_stmt[1]="{$this->attributes['VAR']}RC";
			$this->value_stmt[0]="{$in[$this->attributes['VAR']]}";
			$this->value_stmt[1]=$in[$this->attributes['VAR'].'RC'];
		}


		/**Aggiunta controllo NA e NK **/
		if($in[$this->attributes['VAR'].'D']=='NA' || $in[$this->attributes['VAR'].'D']=='NK'){
			$this->value_stmt[0]="{$this->attributes['NNDAYVALUE']}"."{$in[$this->attributes['VAR'].'M']}"."{$in[$this->attributes['VAR'].'Y']}";
			if($in[$this->attributes['VAR'].'D']=='NA')$this->value_stmt[1]='NAOKOK';
			if($in[$this->attributes['VAR'].'D']=='NK')$this->value_stmt[1]='NKOKOK';
		}
		if($in[$this->attributes['VAR'].'M']=='-9911' || $in[$this->attributes['VAR'].'M']=='-9922'){
			$this->value_stmt[0]="{$this->attributes['NNDAYVALUE']}"."{$this->attributes['NNMONTHVALUE']}"."{$in[$this->attributes['VAR'].'Y']}";
			if($in[$this->attributes['VAR'].'M']=='-9911')$this->value_stmt[1]='NANAOK';
			if($in[$this->attributes['VAR'].'M']=='-9922')$this->value_stmt[1]='NKNKOK';
		}
		if($in[$this->attributes['VAR'].'Y']=='NA' || $in[$this->attributes['VAR'].'Y']=='NK'){
			$this->value_stmt[0]="{$this->attributes['NNDAYVALUE']}"."{$this->attributes['NNMONTHVALUE']}"."1666";
			if($in[$this->attributes['VAR'].'Y']=='NA')$this->value_stmt[1]='NANANA';
			if($in[$this->attributes['VAR'].'Y']=='NK')$this->value_stmt[1]='NKNKNK';
		}
		if($in[$this->attributes['VAR'].'D']=='' && $in[$this->attributes['VAR'].'M']=='' && $in[$this->attributes['VAR'].'Y']=='')
			{
				$this->value_stmt[1]='OKOKOK';
				$this->value_stmt[0]='';
			}
//		echo "<hr>ESTO ES LO QUE SE INSERTA!";
//		print_r($this->value_stmt);
//		echo "<hr>";
//
		return;
	}

	/**
	 * allinea_db
	 * Costruisce l'array dei campi necessari da creare in DB	 *
	 *
	 * @return array
	 */
	function allinea_db(){
		if ($this->attributes['TB']!='no'){
			$ret[0]="{$this->attributes['VAR']} DATE";
			$ret[1]="{$this->attributes['VAR']}RC VARCHAR2(8)";
			return $ret;
		}
		else return ;
	}

	/**
	 * open_condition
	 * Costruisce i controlli js e lato server per i campi condizionati
	 *
	 * @param string $val
	 */
	function open_condition($val){
		$in=$this->session_vars;
		$inputval=$this->db_vars;
		$var_cond=$val;
		$this->condition_passed=false;
		$val_cond=$this->attributes['CONDITION_VALUE'];
		if ($this->attributes['HIDE']=='yes' && $this->attributes['SHOW_HIDE']!='yes' && !isset($in['CRF_BLANK']) ) {

			if (preg_match("/,/", $val_cond)){
				$this->check_js.="
	if (document.getElementById('".$this->id."'))
	document.getElementById('".$this->id."').style.display='none';
	";
				$vals=explode(",",$val_cond);
				foreach ($vals as $key => $value){
					if (isset($in['INVIOCO'])) $value_to_control=$in[$var_cond];
					else $value_to_control=$inputval[$var_cond];
					if ($value_to_control==$value) {
						$this->condition_passed=true;
					}
					$this->check_js.=" \n
		value=value_of('$var_cond', '0');
		if (value=='$value')
		{
		document.forms[0].".$this->id."D.value='';
		document.forms[0].".$this->id."M.value='';
		document.forms[0].".$this->id."Y.value='';
		if (document.getElementById('tr_".$this->id."'))
		document.getElementById('tr_".$this->id."').style.display='';
		}
		";
				}
			}
			else {
				$op ='!=';
				if (preg_match("/\!/", $val_cond)) {
					$val_cond=str_replace("!", "",$val_cond);
					$op='==';
				}
				if (isset($in['INVIOCO'])) $value_to_control=$in[$var_cond];
				else $value_to_control=$inputval[$var_cond];
				if ($op=='==') $this->condition_passed=($value_to_control!=$val_cond);
				else $this->condition_passed=($value_to_control==$val_cond);
				$this->check_js=" \n
	value=value_of('$var_cond', '0');
	if (document.forms[0].".$this->id."D.value!='') {$this->id}D_val=document.forms[0].".$this->id."D.value;
	if (document.forms[0].".$this->id."M.value!='') {$this->id}M_val=document.forms[0].".$this->id."M.value;
	if (document.forms[0].".$this->id."Y.value!='') {$this->id}Y_val=document.forms[0].".$this->id."Y.value;
	if (value{$op}'$val_cond')
	{

	document.forms[0].".$this->id."D.value='';
	document.forms[0].".$this->id."M.value='';
	document.forms[0].".$this->id."Y.value='';
	";
				//foreach ($this->values as $key => $decode) $this->check_js.=" \n	document.forms[0].".$this->id."[".($key-1)."].checked=false;";
				$this->check_js.=" \n
	if (document.getElementById('tr_".$this->id."'))
	document.getElementById('tr_".$this->id."').style.display='none';
	}
	else{
	if (typeof({$this->id}D_val)!= \"undefined\" && {$this->id}D_val) document.forms[0].".$this->id."D.value={$this->id}D_val;
	if (typeof({$this->id}M_val)!= \"undefined\" && {$this->id}M_val) document.forms[0].".$this->id."M.value={$this->id}M_val;
	if (typeof({$this->id}Y_val)!= \"undefined\" && {$this->id}Y_val) document.forms[0].".$this->id."Y.value={$this->id}Y_val;
	if (document.getElementById('tr_".$this->id."'))
	document.getElementById('tr_".$this->id."').style.display='';
	}";
			}
		}
		else{
			$op ='!=';
			if (preg_match("/\!/", $val_cond)) {
				$val_cond=str_replace("!", "",$val_cond);
				$op='==';
			}
			//echo "<li>{$in[$var_cond]} - $var_cond - $val_cond</li>";
			/*foreach ($this->xml_form->fields as $key => $val){
			 if ($val['TYPE']=='checkbox') {
			 foreach ($val['VALUE'] as $key => $val){
			 //echo "<li>$key</li>";
			 if (!isset($in[$key])) $in[$key]='0';
			 }
			 }
				}*/
			//echo "<li>$var_cond - {$in[$var_cond]} - {$val_cond}</li>";
			if ($op=='==') $this->condition_passed=($in[$var_cond]!=$val_cond);
			else $this->condition_passed=($in[$var_cond]==$val_cond);

			$this->check_js.=" \n
					value=value_of('$var_cond', '0');

					if (value $op '$val_cond')
					{
						";
			$this->check_js.="
					if (document.forms[0].".$this->id."D && document.forms[0].".$this->id."M && document.forms[0].".$this->id."Y)
						{

						 	document.forms[0].".$this->id."D.value='';
							document.forms[0].".$this->id."M.value='';
							document.forms[0].".$this->id."Y.value='';
						}


					}
					else{
	if (document.getElementById('tr_".$this->id."'))
	document.getElementById('tr_".$this->id."').style.display='';}
	";
		}
		/*$this->check_js.="
			}
			if (document.getElementById('".$this->id."'))
			document.getElementById('tr_".$this->id."').style.display='';";*/
		$this->html="<tr id='tr_".$this->id."' style=\"display:none\">".$this->html."</tr>";

	}

	/**
	 * Gestisce la compilazione automatica del campo
	 *
	 * @param String $value
	 */
	function open_compila($value){
		#echo "<hr>$value";
		$this->check_js.="
					if (document.forms[0].".$this->attributes['COMPILA_CONDITION_VAR'].".value==".$this->attributes['COMPILA_CONDITION_VALUE']."){
						compila_value=document.forms[0].".$this->attributes['COMPILA'].".value;
						if (compila_value>0){
							document.forms[0].".$this->id."D.value=compila_value.substr(0,2);
							document.forms[0].".$this->id."M.value=compila_value.substr(2,2);
							document.forms[0].".$this->id."Y.value=compila_value.substr(4,4);
							document.forms[0].".$this->id."D.disabled=true;
							document.forms[0].".$this->id."M.disabled=true;
							document.forms[0].".$this->id."Y.disabled=true;
							document.forms[0].".$this->id.".value=compila_value;
						}
					}
			";
	}

	/**
	 * Controlli sul valore della data (maggiore o uguale)
	 *
	 * @param String $value
	 */
	function open_max_eq($value){
		$in=$this->session_vars;
		$inputval=$this->db_vars;
		if (preg_match("/,/",$value)){
			$values=explode(",", $value);
			foreach ($values as $key => $value){
				if (preg_match("/\[/", $value)){
					$value_field=preg_replace("/\[(.*?)\]/", "$1", $value);
					$value=$inputval[$value_field];
					foreach ($this->xml_form->fields as $key=>$val){
						if ($value_field==$val['VAR']) {
							$i=$key;
						}
					}
					$cond_obj=new field($this->xml_form, $i);
					$testo_var_condizione=$cond_obj->testo;
					//		echo "$testo_var_condizione<hr>";
					if ($in[$value_field]!='') $value=$in[$value_field];
				}
				if ($value=='today'||$value=='sysdate') $value=date("dmY", time());
				$value=str_replace("/", "", $value);
				$value=substr($value,4,4).substr($value,2,2).substr($value,0,2);
				$data=$inputval[$this->attributes['VAR']];
				if ($in[$this->attributes['VAR']]!='') $data=$in[$this->attributes['VAR']];
				$data=substr($data,4,4).substr($data,2,2).substr($data,0,2);
				$value_txt=substr($value,6,2)."/".substr($value,4,2)."/".substr($value,0,4);
				if ($testo_var_condizione!='' && $this->config_service['lang']!="en") $value_txt="alla ".$testo_var_condizione;
				else if($this->config_service['lang']!="en") $value_txt="al ".$value_txt;
				if ($testo_var_condizione!='' && $this->config_service['lang']=="en") $value_txt=$testo_var_condizione;
				else if($this->config_service['lang']=="en") $value_txt=$value_txt;
				$rc=$this->attributes['VAR'].'RC';
				$vrc=$inputval[$rc];
				if ($in[$rc]!='') $vrc=$in[$rc];
				if ($data<=$value && $data!='' && $value!='' && ($vrc=='OKOKOK' || $vrc=='')) {
					$this->validata=false;
					if ($data!='')
					$this->input_txt.="<br><font color=red>

					La Data deve essere successiva a $value_txt&nbsp;";
				}
				$giorno=substr($data,6,2)+0;
				$mese=substr($data,4,2)-1;
				$anno=substr($data,0,4)+0;
				$this->controlli.=" if (document.forms[0].".$this->attributes['VAR']."D && document.forms[0].".$this->attributes['VAR']."D.value!='' && document.forms[0].".$this->attributes['VAR']."M.value!=
				 && document.forms[0].".$this->attributes['VAR']."Y.value!='')
				  {
						var data=new Date();
						giorno=document.forms[0].".$this->attributes['VAR'].".value.substr(0,2);
						mese=document.forms[0].".$this->attributes['VAR'].".value.substr(2,2)-1;
						anno=document.forms[0].".$this->attributes['VAR'].".value.substr(4,4);
						data.setFullYear(anno,mese,giorno);
						var value=new Date();
						";
				if ($value_field!='')
				{
					$this->controlli.="
					 	vgiorno=document.forms[0].".$value_field.".value.substr(0,2);
						vmese=document.forms[0].".$value_field.".value.substr(2,2)-1;
						vanno=document.forms[0].".$value_field.".value.substr(4,4);
						if (vmese>0)
							value.setFullYear(vanno,vmese,vgiorno);
						else value=0;
					 	";

				}
				else {
					$vgiorno=substr($value,6,2)+0;
					$vmese=substr($value,4,2)-1;
					$vanno=substr($value,0,4)+0;

					$this->controlli.="
						value.setFullYear(".$vanno.",".$vmese.",".$vgiorno.");
						";
				}
				if ($testo_var_condizione!='' && $this->config_service['lang']!="en") $value_txt="alla ".$testo_var_condizione;
				elseif($this->config_service['lang']!="en") $value_txt="al ".$value_txt;
				if ($testo_var_condizione!='' && $this->config_service['lang']=="en") $value_txt=$testo_var_condizione;
				else if($this->config_service['lang']=="en") $value_txt=$value_txt;
				$testo_js=make_js($this->testo);

				//traduzione del messaggio di alert in inglese
				if($this->config_service['lang']=="en")
				$alert_msg="{$testo_js} must be after $value_txt";
				else
				$alert_msg="La {$testo_js} deve essere successiva $value_txt";

				$this->controlli.="

						if (data<=value && value) {
								alert('$alert_msg');
								document.forms[0].".$this->attributes['VAR']."Y.focus();
								return false;
							}
						}
					";
			}
		}
		else {
			if (preg_match("/\[/", $value)){
				$value_field=preg_replace("/\[(.*?)\]/", "$1", $value);
				$value=$inputval[$value_field];
				foreach ($this->xml_form->fields as $key=>$val){
					if ($value_field==$val['VAR']) {
						$i=$key;
					}
				}
				$cond_obj=new field($this->xml_form, $i);
				$testo_var_condizione=$cond_obj->testo;
				if ($in[$value_field]!='') $value=$in[$value_field];
			}
			if ($value=='today'||$value=='sysdate') $value=date("dmY", time());
			$value=str_replace("/", "", $value);
			$value=substr($value,4,4).substr($value,2,2).substr($value,0,2);
			$data=$inputval[$this->attributes['VAR']];
			if ($in[$this->attributes['VAR']]!='') $data=$in[$this->attributes['VAR']];
			$data=substr($data,4,4).substr($data,2,2).substr($data,0,2);
			$value_txt=substr($value,6,2)."/".substr($value,4,2)."/".substr($value,0,4);
			if ($testo_var_condizione!='' && $this->config_service['lang']!="en") $value_txt="alla ".$testo_var_condizione;
			elseif($this->config_service['lang']!="en") $value_txt="al ".$value_txt;
			if ($testo_var_condizione!='' && $this->config_service['lang']=="en") $value_txt=$testo_var_condizione;
			else if($this->config_service['lang']=="en") $value_txt=$value_txt;
			$rc=$this->attributes['VAR'].'RC';
			$vrc=$inputval[$rc];
			if ($in[$rc]!='') $vrc=$in[$rc];
			if ($data<=$value && $data!='' && $value!='' && ($vrc=='OKOKOK' || $vrc=='')) {
				$this->validata=false;
				if ($data!='')
				$this->input_txt.="<br><font color=red>

				$data - $value
				La Data deve essere successiva a $value_txt&nbsp;";
			}
			$giorno=substr($data,6,2)+0;
			$mese=substr($data,4,2)-1;
			$anno=substr($data,0,4)+0;
			$this->controlli.=" if (document.forms[0].".$this->attributes['VAR']."D && document.forms[0].".$this->attributes['VAR']."D.value!='' && document.forms[0].".$this->attributes['VAR']."M.value!='' && document.forms[0].".$this->attributes['VAR']."Y.value!='')
			  {
					var data=new Date();
					giorno=document.forms[0].".$this->attributes['VAR'].".value.substr(0,2);
					mese=document.forms[0].".$this->attributes['VAR'].".value.substr(2,2)-1;
					anno=document.forms[0].".$this->attributes['VAR'].".value.substr(4,4);
					data.setFullYear(anno,mese,giorno);
					var value=new Date();
					";
			if ($value_field!='')
			{
				$this->controlli.="
				{$value_field}_=document.forms[0].".$value_field.".value;
				{$value_field}_={$value_field}_.replace('/','');
				{$value_field}_={$value_field}_.replace('/','');
					vgiorno={$value_field}_.substr(0,2);
					vmese={$value_field}_.substr(2,2)-1;
					vanno={$value_field}_.substr(4,4);
					value.setFullYear(vanno,vmese,vgiorno);
					";

			}
			else {
				$vgiorno=substr($value,6,2)+0;
				$vmese=substr($value,4,2)-1;
				$vanno=substr($value,0,4)+0;

				$this->controlli.="
					value.setFullYear(".$vanno.",".$vmese.",".$vgiorno.");
					";
			}
			if ($testo_var_condizione!='' && $this->config_service['lang']!="en") $value_txt="alla ".$testo_var_condizione;
			else if($this->config_service['lang']!="en") $value_txt="al ".$value_txt;
			if ($testo_var_condizione!='' && $this->config_service['lang']=="en") $value_txt=$testo_var_condizione;
			else if($this->config_service['lang']=="en") $value_txt=$value_txt;
			$value_txt=make_js($value_txt);
			$testo_js=make_js($this->testo);

			//traduzione del messaggio di alert in inglese
			if($this->config_service['lang']=="en")
			$alert_msg="{$testo_js} must be after $value_txt";
			else
			$alert_msg="La {$testo_js} deve essere successiva $value_txt";

			$this->controlli.="
						if (data<=value) {
								alert('$alert_msg');
								document.forms[0].".$this->attributes['VAR']."Y.focus();
								return false;
						}

					}
				";
		}
	}

	/**
	 * Controlli sul valore della data (maggiore)
	 *
	 * @param String $value
	 */
	function open_max($value){
		$in=$this->session_vars;
		$inputval=$this->db_vars;

		if (preg_match("/,/",$value)){
			$values=explode(",", $value);
			foreach ($values as $key => $value){
				if (preg_match("/\[/", $value)){
					$value_field=preg_replace("/\[(.*?)\]/", "$1", $value);
					$value=$inputval[$value_field];
					foreach ($this->xml_form->fields as $key=>$val){
						if ($value_field==$val['VAR']) {
							$i=$key;
						}
					}
					$cond_obj=new field($this->xml_form, $i);
					$testo_var_condizione=$cond_obj->testo;
					//		echo "$testo_var_condizione<hr>";
					if ($in[$value_field]!='') $value=$in[$value_field];
				}
				if ($value=='today'||$value=='sysdate') $value=date("dmY", time());
				$value=substr($value,4,4).substr($value,2,2).substr($value,0,2);
				$data=$inputval[$this->attributes['VAR']];
				if ($in[$this->attributes['VAR']]!='') $data=$in[$this->attributes['VAR']];
				$data=substr($data,4,4).substr($data,2,2).substr($data,0,2);
				$value_txt=substr($value,6,2)."/".substr($value,4,2)."/".substr($value,0,4);
				if ($testo_var_condizione!='' && $this->config_service['lang']!="en") $value_txt="alla ".$testo_var_condizione;
				else if($this->config_service['lang']!="en") $value_txt="al ".$value_txt;
				if ($testo_var_condizione!='' && $this->config_service['lang']=="en") $value_txt=$testo_var_condizione;
				else if($this->config_service['lang']=="en") $value_txt=$value_txt;
				$rc=$this->attributes['VAR'].'RC';
				$vrc=$inputval[$rc];
				if ($in[$rc]!='') $vrc=$in[$rc];
				if ($data<$value && $data!='' && $value!='' && ($vrc=='OKOKOK' || $vrc=='')) {
					$this->validata=false;
					if ($data!='')
					$this->input_txt.="<br><font color=red>

					La Data deve essere successiva a $value_txt&nbsp;";
				}
				$giorno=substr($data,6,2)+0;
				$mese=substr($data,4,2)-1;
				$anno=substr($data,0,4)+0;
				$this->controlli.=" if (document.forms[0].".$this->attributes['VAR']."D && document.forms[0].".$this->attributes['VAR']."D.value!='' && document.forms[0].".$this->attributes['VAR']."M.value!='' && document.forms[0].".$this->attributes['VAR']."Y.value!='')
				  {
						var data=new Date();
						giorno=document.forms[0].".$this->attributes['VAR'].".value.substr(0,2);
						mese=document.forms[0].".$this->attributes['VAR'].".value.substr(2,2)-1;
						anno=document.forms[0].".$this->attributes['VAR'].".value.substr(4,4);
						data.setFullYear(anno,mese,giorno);
						var value=new Date();
						";
				if ($value_field!='')
				{
					$this->controlli.="
					 	vgiorno=document.forms[0].".$value_field.".value.substr(0,2);
						vmese=document.forms[0].".$value_field.".value.substr(2,2)-1;
						vanno=document.forms[0].".$value_field.".value.substr(4,4);
						if (vmese>0)
							value.setFullYear(vanno,vmese,vgiorno);
						else value=0;
					 	";

				}
				else {
					$vgiorno=substr($value,6,2)+0;
					$vmese=substr($value,4,2)-1;
					$vanno=substr($value,0,4)+0;

					$this->controlli.="
						value.setFullYear(".$vanno.",".$vmese.",".$vgiorno.");
						";
				}
				if ($testo_var_condizione!='' && $this->config_service['lang']!="en") $value_txt="alla ".$testo_var_condizione;
				else if($this->config_service['lang']!="en") $value_txt="al ".$value_txt;
				if ($testo_var_condizione!='' && $this->config_service['lang']=="en") $value_txt=$testo_var_condizione;
				else if($this->config_service['lang']=="en") $value_txt=$value_txt;
				$testo_js=make_js($this->testo);

				//traduzione del messaggio di alert in inglese
				if($this->config_service['lang']=="en")
				$alert_msg="{$testo_js} must be after $value_txt";
				else
				$alert_msg="La {$testo_js} deve essere successiva $value_txt";

				$this->controlli.="
						if (data<value && value) {
								alert('$alert_msg');
								document.forms[0].".$this->attributes['VAR']."Y.focus();
								return false;
							}
						}
					";
			}
		}
		else {
			if (preg_match("/\[/", $value)){
				$value_field=preg_replace("/\[(.*?)\]/", "$1", $value);
				$value=$inputval[$value_field];
				foreach ($this->xml_form->fields as $key=>$val){
					if ($value_field==$val['VAR']) {
						$i=$key;
					}
				}

				$cond_obj=new field($this->xml_form, $i);
				$testo_var_condizione=$cond_obj->testo;
				if ($in[$value_field]!='') $value=$in[$value_field];
			}
			if ($value=='today'||$value=='sysdate') $value=date("dmY", time());
			$value=str_replace("/", "", $value);
			$value=substr($value,4,4).substr($value,2,2).substr($value,0,2);
			$data=$inputval[$this->attributes['VAR']];
			if ($in[$this->attributes['VAR']]!='') $data=$in[$this->attributes['VAR']];
			$data=substr($data,4,4).substr($data,2,2).substr($data,0,2);
			$value_txt=substr($value,6,2)."/".substr($value,4,2)."/".substr($value,0,4);
			if ($testo_var_condizione!='' && $this->config_service['lang']!="en") $value_txt="alla ".$testo_var_condizione;
			else if($this->config_service['lang']!="en") $value_txt="al ".$value_txt;
			if ($testo_var_condizione!='' && $this->config_service['lang']=="en") $value_txt=$testo_var_condizione;
			else if($this->config_service['lang']=="en") $value_txt=$value_txt;
			$rc=$this->attributes['VAR'].'RC';
			$vrc=$inputval[$rc];
			if ($in[$rc]!='') $vrc=$in[$rc];
//			echo $value;
			if ($data<$value && $data!='' && $value!='' && ($vrc=='OKOKOK' || $vrc=='')) {
				$this->validata=false;
				if ($data!='')
				$this->input_txt.="<br><font color=red>

				$data - $value
				La Data deve essere successiva a $value_txt&nbsp;";
			}
			$giorno=substr($data,6,2)+0;
			$mese=substr($data,4,2)-1;
			$anno=substr($data,0,4)+0;
			$this->controlli.=" if (document.forms[0].".$this->attributes['VAR']."D && document.forms[0].".$this->attributes['VAR']."D.value!='' && document.forms[0].".$this->attributes['VAR']."M.value!='' && document.forms[0].".$this->attributes['VAR']."Y.value!='')
			  {
					var data=new Date();
					if (document.forms[0]." . $this->attributes ['VAR'] . "M.value=='-9911' || document.forms[0]." . $this->attributes ['VAR'] . "M.value=='-9922' )
						{mese='12';}
					else{mese=document.forms[0].".$this->attributes['VAR']."M.value-1;}
					anno=document.forms[0].".$this->attributes['VAR']."Y.value;
					if (document.forms[0]." . $this->attributes ['VAR'] . "D.value=='NA' || document.forms[0]." . $this->attributes ['VAR'] . "D.value=='NK' )
						{giorno=daysInMonth(mese,anno);}
					else{giorno=document.forms[0].".$this->attributes['VAR']."D.value;}
					data.setFullYear(anno,mese,giorno);
					var value=new Date();
					";
			if ($value_field!='')
			{
				$this->controlli.="
				{$value_field}_=document.forms[0].".$value_field.".value;
				{$value_field}_={$value_field}_.replace('/','');
				{$value_field}_={$value_field}_.replace('/','');
					vgiorno={$value_field}_.substr(0,2);
					vmese={$value_field}_.substr(2,2)-1;
					vanno={$value_field}_.substr(4,4);
					value.setFullYear(vanno,vmese,vgiorno);
					";

			}
			else {
				$vgiorno=substr($value,6,2)+0;
				$vmese=substr($value,4,2)-1;
				$vanno=substr($value,0,4)+0;

				$this->controlli.="
					value.setFullYear(".$vanno.",".$vmese.",".$vgiorno.");
					";
			}
			if ($testo_var_condizione!='' && $this->config_service['lang']!="en") $value_txt="alla ".$testo_var_condizione;
			else if($this->config_service['lang']!="en")$value_txt="al ".$value_txt;
			if ($testo_var_condizione!='' && $this->config_service['lang']=="en") $value_txt=$testo_var_condizione;
			else if($this->config_service['lang']=="en") $value_txt=$value_txt;
			$value_txt=make_js($value_txt);
			$testo_js=make_js($this->testo);

			//traduzione del messaggio di alert in inglese
			if($this->config_service['lang']=="en")
			$alert_msg="{$testo_js} must be after $value_txt";
			else
			$alert_msg="La {$testo_js} deve essere successiva $value_txt";


			$this->controlli.="
						if (data<value) {
								alert('$alert_msg');
								document.forms[0].".$this->attributes['VAR']."Y.focus();
								return false;
						}

					}
				";
		}
	}

	/**
	 * Controlli sul valore della data (minore o uguale)
	 *
	 * @param String $value
	 */
	function open_min_eq($value){
		$in=$this->session_vars;
		$inputval=$this->db_vars;
		if (preg_match("/,/",$value)){
			$values=explode(",",$value);
			foreach ($values as $key=>$value){
				if (preg_match("/\[/", $value)){
					$value_field=preg_replace("/\[(.*?)\]/", "$1", $value);
					$value=$inputval[$value_field];
					foreach ($this->xml_form->fields as $key=>$val){
						if ($value_field==$val['VAR']) {
							$i=$key;
						}
					}
					$cond_obj=new field($this->xml_form, $i);
					$testo_var_condizione=$cond_obj->testo;
					//		echo "$testo_var_condizione<hr>";
					if ($in[$value_field]!='') $value=$in[$value_field];
				}
				/*lato server*/
				if ($value=='today'||$value=='sysdate') $value=date("dmY", time());
				$value=str_replace("/","", $value);
				$value=substr($value,4,4).substr($value,2,2).substr($value,0,2);
				$data=$inputval[$this->attributes['VAR']];
				if ($in[$this->attributes['VAR']]!='') $data=$in[$this->attributes['VAR']];
				#echo "<hr>$data";
				$data=substr($data,4,4).substr($data,2,2).substr($data,0,2);
				$value_txt=substr($value,6,2)."/".substr($value,4,2)."/".substr($value,0,4);
				if ($testo_var_condizione!='' && $this->config_service['lang']!="en") $value_txt="alla ".$testo_var_condizione;
				else if($this->config_service['lang']!="en") $value_txt="al ".$value_txt;
				if ($testo_var_condizione!='' && $this->config_service['lang']=="en") $value_txt=$testo_var_condizione;
				else if($this->config_service['lang']=="en") $value_txt=$value_txt;
				#echo "<hr>$value";
				$rc=$this->attributes['VAR'].'RC';
				$vrc=$inputval[$rc];
				if ($in[$rc]!='') $vrc=$in[$rc];
				if ($data>=$value && $data!='' && $value!='' && ($vrc=='OKOKOK' || $vrc=='')) {
					$this->validata=false;
					#echo "<hr>$value";
					if ($data!='')
					$this->input_txt.="<br><font color=red>La Data deve essere precedente $value_txt&nbsp;";
				}
				/*lato client*/
				$giorno=substr($data,6,2)+0;
				$mese=substr($data,4,2)-1;
				$anno=substr($data,0,4)+0;
				$this->controlli.=" if (document.forms[0].".$this->attributes['VAR']."D && document.forms[0].".$this->attributes['VAR']."D.value!='' && document.forms[0].".$this->attributes['VAR']."M.value!='' && document.forms[0].".$this->attributes['VAR']."Y.value!='')
				  {
						var data=new Date();
						giorno=document.forms[0].".$this->attributes['VAR'].".value.substr(0,2);
						mese=document.forms[0].".$this->attributes['VAR'].".value.substr(2,2)-1;
						anno=document.forms[0].".$this->attributes['VAR'].".value.substr(4,4);
						data.setFullYear(anno,mese,giorno);
						var value=new Date();
						";
				if ($value_field!='')
				{
					$this->controlli.="
					 	vgiorno=document.forms[0].".$value_field.".value.substr(0,2);
						vmese=document.forms[0].".$value_field.".value.substr(2,2)-1;
						vanno=document.forms[0].".$value_field.".value.substr(4,4);
						if (vmese>0)
							value.setFullYear(vanno,vmese,vgiorno);
						else value=0;
					 	";

				}
				else {
					$vgiorno=substr($value,6,2)+0;
					$vmese=substr($value,4,2)-1;
					$vanno=substr($value,0,4)+0;

					$this->controlli.="
						value.setFullYear(".$vanno.",".$vmese.",".$vgiorno.");
						";
				}
				$testo_js=make_js($this->testo);

				//traduzione del messaggio di alert in inglese
				if($this->config_service['lang']=="en")
				$alert_msg="{$testo_js} must be before $value_txt";
				else
				$alert_msg="La {$testo_js} deve essere precedente $value_txt";

				$this->controlli.="
						if (data>=value && value) {
								alert('$alert_msg');
								document.forms[0].".$this->attributes['VAR']."Y.focus();
								return false;
						}
						}
					";
			}
		}
		else {
			if (preg_match("/\[/", $value)){
				$value_field=preg_replace("/\[(.*?)\]/", "$1", $value);
				$value=$inputval[$value_field];
				foreach ($this->xml_form->fields as $key=>$val){
					if ($value_field==$val['VAR']) {
						$i=$key;
					}
				}
				$cond_obj=new field($this->xml_form, $i);
				$testo_var_condizione=$cond_obj->testo;
				//		echo "$testo_var_condizione<hr>";
				if ($in[$value_field]!='') $value=$in[$value_field];
			}
			/*lato server*/
			if ($value=='today'||$value=='sysdate') $value=date("dmY", time());

			$value=str_replace("/","", $value);
			$value=substr($value,4,4).substr($value,2,2).substr($value,0,2);
			$data=$inputval[$this->attributes['VAR']];
			if ($in[$this->attributes['VAR']]!='') $data=$in[$this->attributes['VAR']];
			#echo "<hr>$data";
			$data=substr($data,4,4).substr($data,2,2).substr($data,0,2);
			$value_txt=substr($value,6,2)."/".substr($value,4,2)."/".substr($value,0,4);
			if ($testo_var_condizione!='' && $this->config_service['lang']!="en") $value_txt="alla ".$testo_var_condizione;
			else if($this->config_service['lang']!="en") $value_txt="al ".$value_txt;
			if ($testo_var_condizione!='' && $this->config_service['lang']=="en") $value_txt=$testo_var_condizione;
			else if($this->config_service['lang']=="en") $value_txt=$value_txt;
			$rc=$this->attributes['VAR'].'RC';
			$vrc=$inputval[$rc];
			if ($in[$rc]!='') $vrc=$in[$rc];
			if ($data>=$value && $data!='' && $value!='' && ($vrc=='OKOKOK' || $vrc=='')) {

				//		if ($data>$value && $data!='') {
				$this->validata=false;
				#echo "<hr>$value";
				if ($data!='')
				$this->input_txt.="<br><font color=red>La Data deve essere precedente $value_txt&nbsp;";
			}
			/*lato client*/
			$giorno=substr($data,6,2)+0;
			$mese=substr($data,4,2)-1;
			$anno=substr($data,0,4)+0;
			$this->controlli.=" if (document.forms[0].".$this->attributes['VAR']."D && document.forms[0].".$this->attributes['VAR']."D.value!='' && document.forms[0].".$this->attributes['VAR']."M.value!='' && document.forms[0].".$this->attributes['VAR']."Y.value!='')
			  {
					var data=new Date();
					giorno=document.forms[0].".$this->attributes['VAR'].".value.substr(0,2);
					mese=document.forms[0].".$this->attributes['VAR'].".value.substr(2,2)-1;
					anno=document.forms[0].".$this->attributes['VAR'].".value.substr(4,4);
					data.setFullYear(anno,mese,giorno);
					var value=new Date();
					";
			if ($value_field!='')
			{
				$this->controlli.="
				 	vgiorno=document.forms[0].".$value_field.".value.substr(0,2);
					vmese=document.forms[0].".$value_field.".value.substr(2,2)-1;
					vanno=document.forms[0].".$value_field.".value.substr(4,4);
					value.setFullYear(vanno,vmese,vgiorno);
				 	";

			}
			else {
				$vgiorno=substr($value,6,2)+0;
				$vmese=substr($value,4,2)-1;
				$vanno=substr($value,0,4)+0;

				$this->controlli.="
					value.setFullYear(".$vanno.",".$vmese.",".$vgiorno.");
					";
			}
			$testo_js=make_js($this->testo);

			//traduzione del messaggio di alert in inglese
			if($this->config_service['lang']=="en")
			$alert_msg="{$testo_js} must be before $value_txt";
			else
			$alert_msg="La {$testo_js} deve essere precedente $value_txt";

			$this->controlli.="
					if (data>=value) {
							alert('$alert_msg');
							document.forms[0].".$this->attributes['VAR']."Y.focus();
							return false;
					}
					}
				";
		}
	}


	function open_min($value) {
		$in = $this->session_vars;
		$inputval = $this->db_vars;
//		print_r($inputval);

		if (preg_match ( "/,/", $value )) {
			$this->controlli .= "
//							alert('if');
//							return false;
				";
			$values = explode ( ",", $value );
			foreach ( $values as $key => $value ) {
				if (preg_match ( "/\[/", $value )) {
					$value_field = preg_replace ( "/\[(.*?)\]/", "$1", $value );
					$value = $inputval [$value_field];
					foreach ( $this->xml_form->fields as $key => $val ) {
						if ($value_field == $val ['VAR']) {
							$i = $key;
						}
					}
					$cond_obj = new field ( $this->xml_form, $i );
					$testo_var_condizione = $cond_obj->testo;
					//		echo "$testo_var_condizione<hr>";
					if ($in [$value_field] != '')
						$value = $in [$value_field];
				}
				/*lato server*/
				if ($value == 'today' || $value == 'sysdate')
					$value = date ( "dmY", time () );
				$value = str_replace ( "/", "", $value );
				$value = substr ( $value, 4, 4 ) . substr ( $value, 2, 2 ) . substr ( $value, 0, 2 );
				$data = $inputval [$this->attributes ['VAR']];

				if ($in [$this->attributes ['VAR']] != '')
					$data = $in [$this->attributes ['VAR']];
					#echo "<hr>$data";
				$data = substr ( $data, 4, 4 ) . substr ( $data, 2, 2 ) . substr ( $data, 0, 2 );
				$value_txt = substr ( $value, 6, 2 ) . "/" . substr ( $value, 4, 2 ) . "/" . substr ( $value, 0, 4 );
				if ($testo_var_condizione != '' && $this->config_service ['lang'] != "en")
					$value_txt = "alla " . $testo_var_condizione;
				else if ($this->config_service ['lang'] != "en")
					$value_txt = "al " . $value_txt;
				if ($testo_var_condizione != '' && $this->config_service ['lang'] == "en")
					$value_txt = $testo_var_condizione;
				else if ($this->config_service ['lang'] == "en")
					$value_txt = $value_txt;
					#echo "<hr>$value";
				$rc = $this->attributes ['VAR'] . 'RC';
				$vrc = $inputval [$rc];
				if ($in [$rc] != '')
					$vrc = $in [$rc];
				if ($data > $value && $data != '' && $value != '' && ($vrc == 'OKOKOK' || $vrc == '')) {
					$this->validata = false;
					#echo "<hr>$value";

					if ($data != ''){
						if ($this->config_service ['lang'] == "en"){
							$this->input_txt .= "<br><font color=red>Date must be before $value_txt&nbsp;";
						}else{
							$this->input_txt .= "<br><font color=red>La Data deve essere precedente $value_txt&nbsp;";
						}
					}
				}
				/*lato client*/
				$giorno = substr ( $data, 6, 2 ) + 0;
				$mese = substr ( $data, 4, 2 ) - 1;
				$anno = substr ( $data, 0, 4 ) + 0;
				$this->controlli .= "

					if (document.forms[0]." . $this->attributes ['VAR'] . "D && document.forms[0]." . $this->attributes ['VAR'] . "D.value!='' && document.forms[0]." . $this->attributes ['VAR'] . "M.value!='' && document.forms[0]." . $this->attributes ['VAR'] . "Y.value!='')
				  {
						var data=new Date();
						giorno=document.forms[0]." . $this->attributes ['VAR'] . ".value.substr(0,2);
						mese=document.forms[0]." . $this->attributes ['VAR'] . ".value.substr(2,2)-1;
						anno=document.forms[0]." . $this->attributes ['VAR'] . ".value.substr(4,4);
						data.setFullYear(anno,mese,giorno);
						var value=new Date();
						";
				if ($value == '' && $value_field != '') {
					$this->controlli .= "
					 	vgiorno=document.forms[0]." . $value_field . ".value.substr(0,2);
						vmese=document.forms[0]." . $value_field . ".value.substr(2,2)-1;
						vanno=document.forms[0]." . $value_field . ".value.substr(4,4);
						if (vmese>0)
							value.setFullYear(vanno,vmese,vgiorno);
						else value=0;
					 	";

				} else {
					$vgiorno = substr ( $value, 6, 2 ) + 0;
					$vmese = substr ( $value, 4, 2 ) - 1;
					$vanno = substr ( $value, 0, 4 ) + 0;

					$this->controlli .= "
						value.setFullYear(" . $vanno . "," . $vmese . "," . $vgiorno . ");
						";
				}
				$testo = make_js ( $this->testo );

				/* Nicola 20/01/2010
				 * Se presente l'attributo LABEL_JS non considera l'elemento txt_value (anche se presente) negli alert JS
				 */
				if($this->attributes['LABEL_JS'] != ""){
					$testo=$this->attributes['LABEL_JS'];
				}

				if($this->attributes['LABEL_JS_COND'] != ""){
					$value_txt=$this->attributes['LABEL_JS_COND'];
				}
				//traduzione del messaggio di alert in inglese
				if ($this->config_service ['lang'] == "en")
					$alert_msg = "{$testo} must be before $value_txt";
				else
					$alert_msg = "La {$testo} deve essere precedente $value_txt";

				$this->controlli .= "
						//alert (data+' - '+value);
						if (data>value && value) {
								alert('$alert_msg');
								document.forms[0]." . $this->attributes ['VAR'] . "Y.focus();
								return false;
						}
						}
					";
			}
		} else {
			if (preg_match ( "/\[/", $value )) {
				$value_field = preg_replace ( "/\[(.*?)\]/", "$1", $value );
				$value = $inputval [$value_field];
				foreach ( $this->xml_form->fields as $key => $val ) {
					if ($value_field == $val ['VAR']) {
						$i = $key;
					}
				}
				$cond_obj = new field ( $this->xml_form, $i );
				$testo_var_condizione = $cond_obj->testo;
				//		echo "$testo_var_condizione<hr>";
				if ($in [$value_field] != '')
					$value = $in [$value_field];
			}
			/*lato server*/
			if ($value == 'today' || $value == 'sysdate')
				$value = date ( "dmY", time () );
			$value = str_replace ( "/", "", $value );
			$value = substr ( $value, 4, 4 ) . substr ( $value, 2, 2 ) . substr ( $value, 0, 2 );
			$data = $inputval [$this->attributes ['VAR']];



			if ($in [$this->attributes ['VAR']] != ''){
				$data = $in [$this->attributes ['VAR']];
			}
				#echo "<hr>$data";
			$data = substr ( $data, 4, 4 ) . substr ( $data, 2, 2 ) . substr ( $data, 0, 2 );
			$value_txt = substr ( $value, 6, 2 ) . "/" . substr ( $value, 4, 2 ) . "/" . substr ( $value, 0, 4 );


			if ($testo_var_condizione != '' && $this->config_service ['lang'] != "en")
				$value_txt = "alla " . $testo_var_condizione;
			else if ($this->config_service ['lang'] != "en")
				$value_txt = "al " . $value_txt;
			if ($testo_var_condizione != '' && $this->config_service ['lang'] == "en")
				$value_txt = $testo_var_condizione;
			else if ($this->config_service ['lang'] == "en")
				$value_txt = $value_txt;
			$rc = $this->attributes ['VAR'] . 'RC';
			$vrc = $inputval [$rc];



			if ($in [$rc] != '')
				$vrc = $in [$rc];
			if ($data > $value && $data != '' && $value != '' && ($vrc == 'OKOKOK' || $vrc == '')) {

				//		if ($data>$value && $data!='') {
				$this->validata = false;
				#echo "<hr>$value";
				if ($data != ''){
					if ($this->config_service ['lang'] == "en"){
						$this->input_txt .= "<br><font color=red>Date must be before $value_txt&nbsp;";
					}else{
						$this->input_txt .= "<br><font color=red>La Data deve essere precedente $value_txt&nbsp;";
					}
				}
			}
			/*lato client*/
			$this->controlli .= "
							if (document.forms[0]." . $this->attributes ['VAR'] . "D.value=='NA' || document.forms[0]." . $this->attributes ['VAR'] . "D.value=='NK' )
							  {	giorno=01;}";
			$giorno = substr ( $data, 6, 2 ) + 0;
			$mese = substr ( $data, 4, 2 ) - 1;
			$anno = substr ( $data, 0, 4 ) + 0;
			$this->controlli .= " if (document.forms[0]." . $this->attributes ['VAR'] . "D && document.forms[0]." . $this->attributes ['VAR'] . "D.value!='' && document.forms[0]." . $this->attributes ['VAR'] . "M.value!='' && document.forms[0]." . $this->attributes ['VAR'] . "Y.value!='')
			  {
					var data=new Date();
					if (document.forms[0]." . $this->attributes ['VAR'] . "D.value=='NA' || document.forms[0]." . $this->attributes ['VAR'] . "D.value=='NK' )
						{giorno='01';}
					else{giorno=document.forms[0]." . $this->attributes ['VAR'] . ".value.substr(0,2);}
					if (document.forms[0]." . $this->attributes ['VAR'] . "M.value=='NA' || document.forms[0]." . $this->attributes ['VAR'] . "M.value=='NK' )
						{mese='01';}
					else{mese=document.forms[0]." . $this->attributes ['VAR'] . "M.value-1;}
					anno=document.forms[0]." . $this->attributes ['VAR'] . "Y.value;
					data.setFullYear(anno,mese,giorno);
					var value=new Date();
					";
			if ($value == '' && $value_field != '') {
				//Se non setto niente dentro l'attributo min, dovrebbe essere ok.
				$this->controlli .= "
				 	vgiorno=document.forms[0]." . $value_field . ".value.substr(0,2);
					vmese=document.forms[0]." . $value_field . ".value.substr(2,2)-1;
					vanno=document.forms[0]." . $value_field . ".value.substr(4,4);
					value.setFullYear(vanno,vmese,vgiorno);
				 	";

			} else {
				// Se metto qualcs gli do il formato full year
				$vgiorno = substr ( $value, 6, 2 ) + 0;
				$vmese = substr ( $value, 4, 2 ) - 1;
				$vanno = substr ( $value, 0, 4 ) + 0;

				$this->controlli .= "
					value.setFullYear(" . $vanno . "," . $vmese . "," . $vgiorno . ");
					";
			}
			$testo = make_js ( $this->testo );

			/* Nicola 20/01/2010
			 * Se presente l'attributo LABEL_JS non considera l'elemento txt_value (anche se presente) negli alert JS
			 */
				if($this->attributes['LABEL_JS'] != ""){
					$testo=$this->attributes['LABEL_JS'];
				}

				if($this->attributes['LABEL_JS_COND'] != ""){
					$value_txt=$this->attributes['LABEL_JS_COND'];
				}
			//traduzione del messaggio di alert in inglese
			if ($this->config_service ['lang'] == "en")
				$alert_msg = "{$testo} must be before $value_txt";
			else
				$alert_msg = "La {$testo} deve essere precedente $value_txt";

			$this->controlli .= "
					if (data>value) {
							alert('$alert_msg');
							document.forms[0]." . $this->attributes ['VAR'] . "Y.focus();
							return false;
					}
				}
				";
		}
	}

	/**
	 * open_save
	 * Costruisce i controlli javascript e lato server per il salvataggio della scheda
	 *
	 * @param string $val
	 */
	function open_save($val){
		#echo "<hr>{$this->testo}";
		$testo=make_js($this->testo);
		$dcod='00';
//		echo $val;
		if ($this->attributes['DCONT']=='yes') $dcod='16';
	if ($this->attributes['DSPEC']=='yes') {$dcod='03';}
			if ($this->attributes['DCONT']=='yes'&& $this->attributes['DSPEC']=='yes') $dcod='31';
		if($val="facoltativo"){$valcod="f";}
		if (!isset($this->attributes['CONDITION'])){
			/**
				 * Condizioni per effettuare i controlli standard:
				 *
				 * 1- Giorno e mese non sono valorizzati entrambi a NA o NK
				 * 		(permessi: NA 08 2010  , NK NK 2010);
				 * 2- Uno tra mese, giorno e anno è vuoto (obbligatorietà gestita da fmweb.js);
				 * 3- Giorno o mese non sono interi (xx xx 2010 non permesso);
				 * 4- Anno settato a NA ( 15 08 NK non permesso);
				 *
				 * 5- Passati i precedenti , se giorno e anno sono interi e diversi da NA o NK ,
				 * 		ma il mese è NA o NK ( 15 NK 2007 non permesso). ;
				 */
			$this->salva_js="
			//	alert('".$this->attributes['VAR']."D'+f.{$this->attributes['VAR']}D.value);
			//  alert(IsNumericCal(f.{$this->attributes['VAR']}D.value));
			//	alert('".$this->attributes['VAR']."M'+f.{$this->attributes['VAR']}M.value);
			//  alert(IsNumericCal(f.{$this->attributes['VAR']}M.value));
			//	alert('".$this->attributes['VAR']."Y'+f.{$this->attributes['VAR']}Y.value);
			//  alert(IsNumericCal(f.{$this->attributes['VAR']}Y.value));
			//	alert(f.{$this->attributes['VAR']}Y.value);
						if(
						(f.{$this->attributes['VAR']}D.value!='NA' && f.{$this->attributes['VAR']}D.value!='NK' &&
					   	 f.{$this->attributes['VAR']}M.value!='-9911' && f.{$this->attributes['VAR']}M.value!='-9922' &&
					   	 f.{$this->attributes['VAR']}Y.value!='NA' && f.{$this->attributes['VAR']}Y.value!='NK'
						)
						|| f.{$this->attributes['VAR']}D.value==''
						|| f.{$this->attributes['VAR']}M.value==''
						|| f.{$this->attributes['VAR']}Y.value==''
						|| IsNumericCal(f.{$this->attributes['VAR']}D.value)==false
						|| IsNumericCal(f.{$this->attributes['VAR']}Y.value)==false
						)
						{";
				   		if($this->attributes['SAVE']=='facoltativo') {
						   $this->salva_js.="c1+='<<fd".$dcod."###".$this->attributes['VAR']."###".$testo.">>';";
					    } else {
						   $this->salva_js.="c1+='<<d".$dcod."###".$this->attributes['VAR']."###".$testo.">>';";
					   	}
				     $this->salva_js.="}
						// Se il giorno è diverso da vuoto, ma il mese è NA , blocco
						if(	f.{$this->attributes['VAR']}D.value!='NA' && f.{$this->attributes['VAR']}D.value!='NK'){
							if(f.{$this->attributes['VAR']}M.value=='-9911' || f.{$this->attributes['VAR']}M.value=='-9922'){
								alert('".$testo." : Invalid date');return false;
							}
						}

				";
		}else
		{
			$oper="==";
			if (preg_match("/!/",$this->attributes['CONDITION_VALUE'])) 
			{
			 $oper="!=";//$this->attributes['CONDITION_VALUE']=substr($this->attributes['CONDITION_VALUE'], 1);}
       $val_cond=substr($this->attributes['CONDITION_VALUE'], 1);
      }
      else
	  		$val_cond=$this->attributes['CONDITION_VALUE'];
			//$val_cond=substr($this->attributes['CONDITION_VALUE'], 1);
			//echo "$val_cond<br>";
			$vals=explode(",",$val_cond);$loc_js="if (";
			for ($i=0;$i<count($vals);$i++){
				if ($i!=0) $loc_js.="||";
				$loc_js.="
		      value_of('{$this->attributes['CONDITION']}')$oper'{$vals[$i]}'";
			}
			$loc_js.=")";
			// echo "$loc_js<br>";
			$this->salva_js="
			$loc_js
					c1+='<<d".$dcod."###".$this->attributes['VAR']."###".$testo.">>';
					else {
					  c1+='<<fd".$dcod."###".$this->attributes['VAR']."###".$testo.">>';
						c1+='<<b###".$this->attributes['VAR']."Y###".$testo.">>';
						}

				";

		}

		$in=$this->session_vars;
		$insert_errors=$this->errors;
		if ($in['invia']!='' || $in['INVIOCO']=='0'){
			if ($this->condition_passed){
				if ($in[$this->attributes['VAR']]==''&&$this->attributes['SAVE']!='facoltativo') {
					$this->validata=false;
					$testo_js=make_js($this->testo);
					$this->errors[$this->attributes['VAR']]="Il campo ? obbligatorio";
				}
			}
			else {
				if ($in[$this->attributes['VAR']]!='') {
					$this->validata=false;
					$testo_js=make_js($this->testo);
					$this->errors[$this->attributes['VAR']]="Il campo deve essere vuoto";
				}
			}
		}
	}

	/**
	 * open_send
	 * Costruisce i controlli javascript e lato server per l'invio della scheda
	 *
	 * @param string $val
	 * @return bool
	 */
	function open_send($val){
		#echo "<hr>{$this->testo}";
		$testo=make_js($this->testo);
		$dcod='00';
//		echo $val;
		if ($this->attributes['DCONT']=='yes') $dcod='16';
		if ($this->attributes['DSPEC']=='yes') $dcod='03';
			if ($this->attributes['DCONT']=='yes'&& $this->attributes['DSPEC']=='yes') $dcod='31';

			/**Aggiunta controllo NA e NK **/
			if (!isset($this->attributes['CONDITION'])){
				/**
				 * Condizioni per effettuare i controlli standard:
				 *
				 * 1- Giorno e mese non sono valorizzati entrambi a NA o NK
				 * 		(permessi: NA 08 2010  , NK NK 2010);
				 * 2- Uno tra mese, giorno e anno è vuoto (obbligatorietà gestita da fmweb.js);
				 * 3- Giorno o mese non sono interi (xx xx 2010 non permesso);
				 * 4- Anno settato a NA ( 15 08 NK non permesso);
				 *
				 * 5- Passati i precedenti , se giorno e anno sono interi e diversi da NA o NK ,
				 * 		ma il mese è NA o NK ( 15 NK 2007 non permesso). ;
				 */
				$this->invia_js="
//				alert(IsNumericCal(f.{$this->attributes['VAR']}D.value));
				if(
				(f.{$this->attributes['VAR']}D.value!='NA' && f.{$this->attributes['VAR']}D.value!='NK' &&
			   	 f.{$this->attributes['VAR']}M.value!='-9911' && f.{$this->attributes['VAR']}M.value!='-9922' &&
			   	 f.{$this->attributes['VAR']}Y.value!='NA' && f.{$this->attributes['VAR']}Y.value!='NK'
					)
				|| f.{$this->attributes['VAR']}D.value==''
				|| f.{$this->attributes['VAR']}M.value==''
				|| f.{$this->attributes['VAR']}Y.value==''
				|| IsNumericCal(f.{$this->attributes['VAR']}D.value)==false
				|| IsNumericCal(f.{$this->attributes['VAR']}Y.value)==false
				){";
				if ($this->attributes['SEND']=='facoltativo')
				{
     
						$this->invia_js.="c1+='<<fd".$dcod."###".$this->attributes['VAR']."###".$testo.">>';";
					}else{
						$this->invia_js.="c1+='<<d".$dcod."###".$this->attributes['VAR']."###".$testo.">>';";
					}
				$this->invia_js.="}
				if(	f.{$this->attributes['VAR']}D.value!='NA' && f.{$this->attributes['VAR']}D.value!='NK'){
					if(f.{$this->attributes['VAR']}M.value=='-9911' || f.{$this->attributes['VAR']}M.value=='-9922'){
						alert('".$testo." : Invalid date');return false;
					}
				}
					";

			}
			else
			{

				$oper="==";
				if (preg_match("/!/",$this->attributes['CONDITION_VALUE'])) 
				{
				 $oper="!=";//$this->attributes['CONDITION_VALUE']=substr($this->attributes['CONDITION_VALUE'], 1);}
				 $val_cond=substr($this->attributes['CONDITION_VALUE'], 1);
        }
        else
  				$val_cond=$this->attributes['CONDITION_VALUE'];
				$vals=explode(",",$val_cond);$loc_js="if (";
				for ($i=0;$i<count($vals);$i++){
					if ($i!=0) $loc_js.="||";
					$loc_js.="
			      value_of('{$this->attributes['CONDITION']}')$oper'{$vals[$i]}'";
				}
				$loc_js.=")";
				// echo "$loc_js<br>";
				$this->invia_js="
				$loc_js
						c1+='<<d".$dcod."###".$this->attributes['VAR']."###".$testo.">>';
						else {
						  c1+='<<fd".$dcod."###".$this->attributes['VAR']."###".$testo.">>';
							c1+='<<b###".$this->attributes['VAR']."Y###".$testo.">>';
							}

					";

			}

		$in=$this->session_vars;
		$insert_errors=$this->errors;
		if ($in['invia']!='' || $in['INVIOCO']=='1'){
			if ($this->condition_passed){
				if ($in[$this->attributes['VAR']]==''&&$this->attributes['SEND']!='facoltativo') {
					$this->validata=false;
					$testo_js=make_js($this->testo);
					$this->errors[$this->attributes['VAR']]="Il campo ? obbligatorio";
				}
			}
			else {
				if ($in[$this->attributes['VAR']]!='') {
					$this->validata=false;
					$testo_js=make_js($this->testo);
					$this->errors[$this->attributes['VAR']]="Il campo deve essere vuoto";
				}
			}
		}


	}

	/**
	 * Gestione della disabilitazione del campo
	 *
	 * @param String $value
	 */
	function open_disabled($value){
		$this->check_js.="
				if(document.forms[0].".$this->id."D && document.forms[0].".$this->id."D.value!='')
					document.forms[0].".$this->id."D.disabled=true;
			";
		$this->check_js.="
				if(document.forms[0].".$this->id."M && document.forms[0].".$this->id."M.value!='')
					document.forms[0].".$this->id."M.disabled=true;
			";
		$this->check_js.="
				if(document.forms[0].".$this->id."Y && document.forms[0].".$this->id."Y.value!='')
					document.forms[0].".$this->id."Y.disabled=true;
			";
	}


	/**
	 * Visualizzazione nella modalità progressiva
	 *
	 * @param String $var
	 * @param number $i
	 * @param array $row
	 * @param boolean $this_closed
	 * @return String
	 */
	function all_in($var, $i, $row, $this_closed) {
		$add_cal='
		<script>
		 var '.$var.'_PROGR_'.$i.'_cal=new CalendarPopup(\''.$var.'_PROGR_'.$i.'_cal_div\');
		 '.$var.'_PROGR_'.$i.'_cal.showNavigationDropdowns();
		 '.$var.'_PROGR_'.$i.'_cal.setReturnFunction("setMultipleValues_'.$var.'_PROGR_'.$i.'");
		 function setMultipleValues_'.$var.'_PROGR_'.$i.' (y,m,d) {
		     document.forms[0].'.$var.'_PROGR_'.$i.'Y.value=y;
 		     document.forms[0].'.$var.'_PROGR_'.$i.'M.value=m;
		     document.forms[0].'.$var.'_PROGR_'.$i.'D.value=d;
    	 }
    	 document.write(\'<a href="#" name="'.$this->attributes['VAR'].'_cal_anchor" id="'.$var.'_PROGR_'.$i.'_cal_anchor" onclick="'.$var.'_PROGR_'.$i.'_cal.showCalendar(\\\''.$var.'_PROGR_'.$i.'_cal_anchor\\\');return false;" >&nbsp;<img width="25"  height="25" src="../images/Calendario2.jpg"></a><span id="'.$var.'_PROGR_'.$i.'_cal_div" STYLE="position:absolute;visibility:hidden;background-color:white;layer-background-color:white;"></span>\');
		 </script>

		 ';



		 $select_months="<select id='{$var}_PROGR_{$i}M' name='{$var}_PROGR_{$i}M' $disabled> ";
		 $months['']='';

		if($this->config_service['lang']=='en'){
		 $months[1]='jan';
		 $months[2]='feb';
		 $months[3]='mar';
		 $months[4]='apr';
		 $months[5]='may';
		 $months[6]='jun';
		 $months[7]='jul';
		 $months[8]='aug';
		 $months[9]='sep';
		 $months[10]='oct';
		 $months[11]='nov';
		 $months[12]='dec';
		 $date_def='(DD MM YYYY)';
		}
		else{
		 $months[1]='gen';
		 $months[2]='feb';
		 $months[3]='mar';
		 $months[4]='apr';
		 $months[5]='mag';
		 $months[6]='giu';
		 $months[7]='lug';
		 $months[8]='ago';
		 $months[9]='set';
		 $months[10]='ott';
		 $months[11]='nov';
		 $months[12]='dic';
		 $date_def='(GG MM AAAA)';
		}
		 $option="";
		if ($row[$var] != '') {
				if ( preg_match("/\//", $row [$var]))
				{$date[0]=substr($row[$var], 0,2);
					$date[1]=substr($row[$var], 3,2);
					$date[2]=substr($row[$var], 6,4);}
				else {
					$date[0]=substr($row[$var], 0,2);
					$date[1]=substr($row[$var], 2,2);
					$date[2]=substr($row[$var], 4,4);
				}
			} else{
				$date = '';
			}

			foreach($months as $key=>$val){
				if($date[1]==$key){$selected=" selected=\"selected\" "; }
				else $selected="";
				$option.="<option $selected value=\"$key\">$val</option>";
			}
			$select_months.=$option."</select>";

		if ($this_closed){
			if($this->config_service['eQuery']=='1' && (isset($_GET['ABILITA_EQ_DE']) || isset($_GET['ABILITA_EQ_DM'])) ){
					$eQ_content="<input type='text' name='{$var}_PROGR_{$i}D' size=\"2\" value=\"{$date[0]}\" >/
								$select_months/
								<input type='text' name='{$var}_PROGR_{$i}Y' size=\"4\" value=\"{$date[2]}\" >
								<input type=\"hidden\" name=\"{$var}_PROGR_{$i}\" value=\"\"/>
					            <input type=\"hidden\" name=\"{$var}_PROGR_{$i}RC\" />$add_cal ";

					$c1_agg .= "c1+='<<fd00###{$var}_PROGR_{$i}###>>'";

					$eQ= $this->eQ_all_in($var, $i, $row, $this_closed);
			}
			if (isset($this->session_vars['AUDIT_TRAIL']) && $this->session_vars['AUDIT_TRAIL']!='' && $i!="") {
				$audit_trail =  new audit_trail($his->service,$this->conn,$this->config_service,$this->attributes,$this->xml_form);
				$at = $audit_trail->audit_trail_popup($this->session_vars, $i );
			}
			elseif(isset($_GET['CRF_ANNOTE'])){
					$db=$this->attributes['VAR'];
					$table=$this->xml_form->form['TABLE'];
					$annote = "<b><br><u>$table.$db</u></b>";
			}
			$ret['body']="
			<td class=sc4bis id=".$var.'_PROGR_'.$i." >&nbsp;
			<span id='view_field_{$var}_PROGR_{$i}'>{$row[$var]} </span>  $at $annote
			<span id='mod_field_{$var}_PROGR_{$i}' style=\"display:none\">$eQ_content</span> $eQ
			</td>
			";
			return $ret;
		}
		else {


			$ret['body']= "
				<td class=sc4bis>
				<input type='text' name='{$var}_PROGR_{$i}D' size=\"2\" value=\"{$date[0]}\" >/
				$select_months/
				<input type='text' name='{$var}_PROGR_{$i}Y' size=\"4\" value=\"{$date[2]}\" >
				<input type=\"hidden\" name=\"{$var}_PROGR_{$i}\" value=\"\"/>
	            <input type=\"hidden\" name=\"{$var}_PROGR_{$i}RC\" />$add_cal $eQ
				</td>";
			$c1_agg .= "
				c1+='<<fd00###{$var}_PROGR_{$i}###>>';
			";
			$ret['c1_agg']=$c1_agg;
			return $ret;
		}
	}

	/**
	 * Visualizzazione nella modalità progressiva (header)
	 *
	 * @param String $var
	 * @param number $i
	 * @param array $row
	 * @param boolean $this_closed
	 * @return String
	 */
	static function S_all_in($field, $m_p, $xml_form){
		$select_field .= "to_char($field,'DD/MM/YYYY') as $field,";
		if ($xml_form->form ['TOT_NOT_ENABLED'] != 'yes') {
			$onclick_action = "";
			for($i = 1; $i <= $m_p; $i ++) {
				$onclick_action .= "
					if (document.forms['ALL_IN_FORMS'].{$field}_PROGR_{$i}D)
					document.forms['ALL_IN_FORMS'].{$field}_PROGR_{$i}D.value=document.forms['ALL_IN_FORMS'].{$field}_TOT_D.value;
					if (document.forms['ALL_IN_FORMS'].{$field}_PROGR_{$i}M)
					document.forms['ALL_IN_FORMS'].{$field}_PROGR_{$i}M.value=document.forms['ALL_IN_FORMS'].{$field}_TOT_M.value;
					if (document.forms['ALL_IN_FORMS'].{$field}_PROGR_{$i}Y)
					document.forms['ALL_IN_FORMS'].{$field}_PROGR_{$i}Y.value=document.forms['ALL_IN_FORMS'].{$field}_TOT_Y.value;
				";

			}
			$field_tot .= "
					<input type='text' name='{$field}_TOT_D' size=\"2\">/
					<input type='text' name='{$field}_TOT_M' size=\"2\">/
					<input type='text' name='{$field}_TOT_Y' size=\"4\"><br>
					<!--input type='button' value='applica a tutti' onclick=\"
					$onclick_action
					\"-->
					<button class=\"btn btn-xs btn-warning\" type=\"button\" onclick=\"$onclick_action\">
						applica a tutti
					</button>
				";
				$tr_agg .= "<td class=int>$field_tot &nbsp;</td>";
		}
		return $tr_agg;
	}


}


?>
