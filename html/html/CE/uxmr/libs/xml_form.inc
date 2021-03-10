<?
//ATTENZIONE LEGGERE ATTENTAMENTE:
/**
 * Il seguente file è DEPRECATO, il nuovo file da utilizzare è form.inc 
 * per generare oggetti xml_form! 
 */

###class xml_form###
/*
<b>Autore Carlo Contino</b>
    Data 26/04/2006
    Questa libreria ? costruita sul prototipo di form xml concepito e utilizzato per il servizio di Protocol Development;
    quindi un file xml con struttura radicalmente diversa da tale prototipo risulta inutilizzabile.
    Per trovare i riferimenti sulla struttura xml dei file di form leggere il documento "<a href='/docs/struttura_xml.htm' target='blank'>Struttura file di configurazione</a>" presente nell'area documentale

    <b>Sintassi costruttore:</b>
        $nome_oggetto=new <b>xml_form</b>()
    <b>Variabili:</b>
        <b>$form:</b> attributi della form;
        <b>$fields:</b> contenuto informativo dei campi presenti nella form;
        <b>$vars:</b> Indice delle variabili oracle della form;
        <b>$buttons:</b> Contenuto informativo dei bottoni;
        <b>$salva_js:</b> funzione di controllo per il salvataggio;
        <b>$invia_js:</b> funzione di controllo per l'invio;
        <b>$check_js:</b> funzione di controllo dipendenze;
        <b>$body:</b> Stringa contente il body della pagina html in codice html;
        <b>$onload:</b> Funzioni javascript da chiamare all'onload della pagina;
        <b>$validata:</b>Mi inidica se tutti i valori passati tramite GET o POST sono coretti e sufficenti per il salvataggio della scheda;
    <b>Metodi:</b>
        <b>xml_form_by_vals($vals as array) as void:</b>   inizializza le variabili interne leggendo il contenuto dell'array passato dal parser xml;
        <b>xml_form_by_obj($xml as my_xml_parser object) as void:</b>   inizializza le variabili interne leggendo il contenuto dell'oggetto my_xml_parser;
        <b>xml_form_by_file($xml_file as string) as void:</b>  inizializza le variabili interne leggendo il contenuto del file xml $xml_file;
        <b>make_html() as void:</b> inizializza la variabile interna $body con il codice html della form (come css vengono utilizzate tre classi: <b>titolo_form</b> come classe per il titolo della form, <b>input_txt</b> come classe per il testo della domanda, <b>input_var</b> come classe per la cella di inserimento);

*/
###endclass###
class xml_form{

    var $form;
    var $fields;
    var $vars;
    var $buttons;
    var $enable;
    var $query_enable;
    var $salva_js='';
    var $invia_js='';
    var $check_js='';
    var $body='';
    var $onload='';
    var $validata=true;
    var $sql_query;
    var $sql_query_storico;
    var $sql_query_coordinate;
    var $progr;
    var $equery_table;
    var $equery_coordinate;

###sub xml_form_by_obj($xml as my_xml_parser object) as void###
    function xml_form_by_obj($xml){
        $this->xml_form_by_vals($xml->vals);
    }
###endsub###


	function query_coordinate($new_insert){
		global $in;
		global $conn;
		$query="select count(*) as c from ".$GLOBALS['service']."_coordinate where codpat='".$in['CODPAT']."' and esam='".$in['ESAM']."' and visitnum='".$in['VISITNUM']."' and progr='".$this->progr."'";
		#echo "<hr>$query";
		$sql=new query($conn);
		$sql->set_sql($query);
		$sql->exec();//obsoleto trovare dove testare
		$sql->get_row();
		$visitclose='0';
		if ($this->progr=='0') $this->progr=1;
		//if ($in['VISITNUM']=='0') $visitclose='1';
		if ($sql->row['C']!='1') $this->sql_query_coordinate="insert into ".$GLOBALS['service']."_coordinate (codpat, visitnum, esam, progr, inizio, fine, insertdt, userid, abilitato, visitclose) values ('".$in['CODPAT']."','".$in['VISITNUM']."','".$in['ESAM']."','".$this->progr."','1','".$in['INVIOCO']."',sysdate,'".$in['remote_userid']."','1',$visitclose)";
		else {
			if ($new_insert) $this->sql_query_coordinate="update ".$GLOBALS['service']."_coordinate set visitclose=$visitclose, insertdt=sysdate, userid='".$in['remote_userid']."', inizio='1', fine='".$in['INVIOCO']."' where codpat='".$in['CODPAT']."' and esam='".$in['ESAM']."' and visitnum='".$in['VISITNUM']."' and progr='".$this->progr."'";
			else $this->sql_query_coordinate="update ".$GLOBALS['service']."_coordinate set visitclose=$visitclose, moddt=sysdate, fine='".$in['INVIOCO']."', inizio='1' where codpat='".$in['CODPAT']."' and esam='".$in['ESAM']."' and visitnum='".$in['VISITNUM']."' and progr='".$this->progr."'";
		}
	}

	function pk_key(){
		global $in;
		#echo "<hr>pk_key";
		$c=0;
		for ($i=0;$i<count($this->fields);$i++){
			#echo "<hr>".$this->fields[$i]['PK'];
			if ($this->fields[$i]['PK']=='yes') {
				#echo "<hr>".$this->fields[$i]['VAR'];
				$pk_key[$c]=$this->fields[$i]['VAR'];
				$c++;
			}
		}
		return $pk_key;
	}

	function pk_where(){
		#echo "<hr>pk_where<hr>";
		global $in;
		$pk_key=$this->pk_key();
		#echo $pk_key;
		for ($i=0;$i<count($pk_key);$i++){
			if ($in[$pk_key[$i]]!='next') {
				if ($where!='') $where.=' and ';
				$where.=$pk_key[$i]."='".$in[$pk_key[$i]]."'";
			}
		}
		#echo "<hr>pk_where $where";
		return $where;
	}

	function query_storico($new_insert){
		global $in;
		$where=$this->pk_where();
		if (!$new_insert && !isset($in['ID_QUERY'])) $this->sql_query_storico="insert into S_".$this->form['TABLE']." select '".$in['remote_userid']."', sysdate, storico_id.nextval, 'V', '',  ".$this->form['TABLE'].".* from ".$this->form['TABLE']." where $where";
		if (!$new_insert && isset($in['ID_QUERY'])) $this->sql_query_storico="insert into S_".$this->form['TABLE']." select '".$in['remote_userid']."', sysdate, storico_id.nextval, 'E', '".$in['ID_QUERY']."',  ".$this->form['TABLE'].".* from ".$this->form['TABLE']." where $where";

	}

	function query_equery(){
		global $in;
		global $conn;
		for ($i=0;$i<count($this->fields);$i++){
					$where='';
					if ($this->fields[$i]['TB']!='no' && count($this->fields[$i])>0){
						$field=new field($this, $i);
						#print_r($field->values);
						switch($this->fields[$i]['TYPE']):
		                case "data":
			                	if ($in[$this->fields[$i]['VAR']]!=''){
			                		if ($fields!='') $fields.=',';
													if ($values!='') $values.=',';
			                		$fields.=$this->fields[$i]['VAR'];
			                    $values.="to_date('".$in[$this->fields[$i]['VAR']]."','DDMMYYYY')";
			                  }
		                    break;
		                case "checkbox":
		                   	foreach ($field->values as $nomec => $nome) {
		                   		if ($in[$nomec]!='') {
		                   			if ($fields!='') $fields.=',';
														if ($values!='') $values.=',';
		                   			$values.="'".$in[$nomec]."'";
		                   			$fields.=$nomec;
		                   		}
		                   	}
		                    break;
		                case "radio":
		                		foreach ($field->values as $nomec => $nome) {
		                			if ($nomec==$in[$this->fields[$i]['VAR']])
		                			{
		                				if ($fields!='') $fields.=',';
												 		if ($values!='') $values.=',';
												 		$nome=preg_replace("/'/", "''", $nome);
												 		$fields.=$this->fields[$i]['VAR'].",";
												 		$fields.="D_".$this->fields[$i]['VAR'];
												 		$values.="'".$in[$this->fields[$i]['VAR']]."',";
												 		$values.="'$nome'";
		                				#echo "<br>D_".$this->fields[$i]['VAR']."=$nome<br>";
		                			}
		                		}
		                		break;
		                case "radio_select":
		                		if (!$radio_exist[$this->fields[$i]['RADIO']])
		                		 {
		                				$fields.=",".$this->fields[$i]['RADIO']."";
												 		$values.=",'".$in[$this->fields[$i]['RADIO']]."'";
												 		$radio_exist[$this->fields[$i]['RADIO']]=true;
		                		}
		                		foreach ($field->values as $nomec => $nome) {
		                			if ($nomec==$in[$this->fields[$i]['VAR']])
		                			{
		                				if ($fields!='') $fields.=',';
												 		if ($values!='') $values.=',';
												 		$nome=preg_replace("/'/", "''", $nome);
												 		$fields.=$this->fields[$i]['VAR'].",";
												 		$fields.="D_".$this->fields[$i]['VAR'];
												 		$values.="'".$in[$this->fields[$i]['VAR']]."',";
												 		$values.="'$nome'";
		                				#echo "<br>D_".$this->fields[$i]['VAR']."=$nome<br>";
		                			}
		                		}
		                		break;
		                case "check_select":
		                		$fields.=",".$this->fields[$i]['CHECK']."";
												$values.=",'".$in[$this->fields[$i]['CHECK']]."'";
		                		foreach ($field->values as $nomec => $nome) {
		                			if ($nomec==$in[$this->fields[$i]['VAR']])
		                			{
		                				if ($fields!='') $fields.=',';
												 		if ($values!='') $values.=',';
												 		$nome=preg_replace("/'/", "''", $nome);
												 		$fields.=$this->fields[$i]['VAR'].",";
												 		$fields.="D_".$this->fields[$i]['VAR'];
												 		$values.="'".$in[$this->fields[$i]['VAR']]."',";
												 		$values.="'$nome'";
		                			}
		                		}
		                		break;
		                case "select":
		                		foreach ($field->values as $nomec => $nome) {
		                			if ($nomec==$in[$this->fields[$i]['VAR']])
		                			{
		                				if ($fields!='') $fields.=',';
												 		if ($values!='') $values.=',';
												 		$nome=preg_replace("/'/", "''", $nome);
												 		$fields.=$this->fields[$i]['VAR'].",";
												 		$fields.="D_".$this->fields[$i]['VAR'];
												 		$values.="'".$in[$this->fields[$i]['VAR']]."',";
												 		$values.="'$nome'";
		                				#echo "<br>D_".$this->fields[$i]['VAR']."=$nome<br>";
		                			}
		                		}
		                		break;
		                case "time":
		                				$fields.=$this->fields[$i]['VAR']."_H,";
												 		$fields.=$this->fields[$i]['VAR']."_M";
												 		$values.="'".$in[$this->fields[$i]['VAR'].'_H']."',";
												 		$values.="'".$in[$this->fields[$i]['VAR'].'_M']."'";
		                		break;
		                default:
		                	 if ($in[$this->fields[$i]['VAR']]!=''){
			                	 if ($fields!='') $fields.=',';
												 if ($values!='') $values.=',';
												 $fields.=$this->fields[$i]['VAR'];
												 if ($in[$this->fields[$i]['VAR']]=='next'){
												 	if ($this->fields[$i]['WHERE']!='') $where="where ".$this->fields[$i]['WHERE'];
													//$where=preg_replace("/\[(.*?)\]/e","var_glob('\\1')" , $where);
													$where=preg_replace_callback ( "/\[(.*?)\]/", function($matches){return var_glob($matches[1]);}, $where );
												 	$query="select max(".$this->fields[$i]['VAR'].") as max from ".$this->form['TABLE']." $where";
												 	#echo $query;
												 	$sql=new query($conn);
												 	$sql->set_sql($query);
												 	$sql->exec();//obsoleto trovare dove testare
												 	$sql->get_row();
												 	$in[$this->fields[$i]['VAR']]=$sql->row['MAX']+1;
												 }
												 $values.="'".$in[$this->fields[$i]['VAR']]."'";
			                  }
		                   break;
		            endswitch;
					}
				}
				$query="select max(id) as max_id from ".$GLOBALS['service']."_equery";
				$sql=new query($conn);
				$sql->set_sql($query);
				$sql->exec();//obsoleto trovare dove testare
				if ($sql->get_row()) $max=$sql->row['MAX_ID']+1;
				else $max=0;
				$fields.=",COMMENTO,ID";
				$values.=",'".$in['COMMENTO']."','$max'";
				$this->equery_table="insert into eq_".$this->form['TABLE']." ($fields) values ($values)";
                if ($in['PROGR']=='') $in['PROGR']=0;
				$this->equery_coordinate="insert into ".$GLOBALS['service']."_equery (q_userid,id,center,codpat,visitnum,esam,progr,question,quest_dt,to_be_validate) values ('".$in['remote_userid']."','".$max."','".$in['CENTER']."','".$in['CODPAT']."','".$in['VISITNUM']."','".$in['ESAM']."','".$in['PROGR']."', '".$in['COMMENTO']."', sysdate,1)";
	}

	function query_tb($new_insert){
		global $in;
		global $conn;
		global $dir;

		$dir_file=$dir."/uploaded_file/";
		if ($new_insert){
				for ($i=0;$i<count($this->fields);$i++){
					$where='';
					if (($this->fields[$i]['TB']!='no')&& count($this->fields[$i])>0){
						$field=new field($this, $i);
//						print_r($field->values);
//						echo "<br>".$this->fields[$i]['VAR']." - ".$this->fields[$i]['TYPE']." valore: {$in[$this->fields[$i]['VAR']]}<br>";
						switch($this->fields[$i]['TYPE']):
		                case "data":
			                	if ($in[$this->fields[$i]['VAR']]!=''){
			                		if ($fields!='') $fields.=',';
													if ($values!='') $values.=',';
			                		$fields.=$this->fields[$i]['VAR'];
			                    $values.="to_date('".$in[$this->fields[$i]['VAR']]."','DDMMYYYY')";
			                		if ($fields!='') $fields.=',';
													if ($values!='') $values.=',';
				                	$rc=$this->fields[$i]['VAR'].'RC';
		                	    $fields.=$rc;
			                    $values.="'$in[$rc]'";
		                  }
		                    break;
		                     case "text":
		                	break;
		                case "checkbox":
		                   	foreach ($field->values as $nomec => $nome) {
		                   		if ($in[$nomec]!='') {
		                   			if ($fields!='') $fields.=',';
														if ($values!='') $values.=',';
		                   			$values.="'".$in[$nomec]."'";
		                   			$fields.=$nomec;
		                   		}
		                   	}
		                    break;
		                case "radio":
		                		foreach ($field->values as $nomec => $nome) {
		                			if ($nomec==$in[$this->fields[$i]['VAR']])
		                			{
		                				if ($fields!='') $fields.=',';
												 		if ($values!='') $values.=',';
												 		$nome=preg_replace("/'/", "''", $nome);
												 		$fields.=$this->fields[$i]['VAR'].",";
												 		$fields.="D_".$this->fields[$i]['VAR'];
												 		$values.="'".$in[$this->fields[$i]['VAR']]."',";
												 		$values.="'$nome'";
		                				#echo "<br>D_".$this->fields[$i]['VAR']."=$nome<br>";
		                			}
		                		}
		                		break;
		                case "radio_select":
		                		if (!$radio_exist[$this->fields[$i]['RADIO']])
		                		 {
		                				$fields.=",".$this->fields[$i]['RADIO']."";
												 		$values.=",'".$in[$this->fields[$i]['RADIO']]."'";
												 		$radio_exist[$this->fields[$i]['RADIO']]=true;
		                		}
		                		foreach ($field->values as $nomec => $nome) {
		                			if ($nomec==$in[$this->fields[$i]['VAR']])
		                			{
		                				if ($fields!='') $fields.=',';
												 		if ($values!='') $values.=',';
												 		$nome=preg_replace("/'/", "''", $nome);
												 		$fields.=$this->fields[$i]['VAR'].",";
												 		$fields.="D_".$this->fields[$i]['VAR'];
												 		$values.="'".$in[$this->fields[$i]['VAR']]."',";
												 		$values.="'$nome'";
		                				#echo "<br>D_".$this->fields[$i]['VAR']."=$nome<br>";
		                			}
		                		}
		                		break;
		                case "check_select":
		                		$fields.=",".$this->fields[$i]['CHECK']."";
												$values.=",'".$in[$this->fields[$i]['CHECK']]."'";
		                		foreach ($field->values as $nomec => $nome) {
		                			if ($nomec==$in[$this->fields[$i]['VAR']])
		                			{
		                				if ($fields!='') $fields.=',';
												 		if ($values!='') $values.=',';
												 		$nome=preg_replace("/'/", "''", $nome);
												 		$fields.=$this->fields[$i]['VAR'].",";
												 		$fields.="D_".$this->fields[$i]['VAR'];
												 		$values.="'".$in[$this->fields[$i]['VAR']]."',";
												 		$values.="'$nome'";
		                			}
		                		}
		                		break;
		                case "select":
		                		foreach ($field->values as $nomec => $nome) {
		                			if ($nomec==$in[$this->fields[$i]['VAR']])
		                			{
		                				if ($fields!='') $fields.=',';
												 		if ($values!='') $values.=',';
												 		$nome=preg_replace("/?/", "i'", $nome);
												 		$nome=preg_replace("/?/", "a'", $nome);
												 		$nome=preg_replace("/?/", "e'", $nome);
												 		$nome=preg_replace("/?/", "o'", $nome);
												 		$nome=preg_replace("/?/", "u'", $nome);
												 		$nome=preg_replace("/'/", "''", $nome);
												 		$fields.=$this->fields[$i]['VAR'].",";
												 		$fields.="D_".$this->fields[$i]['VAR'];
												 		$values.="'".$in[$this->fields[$i]['VAR']]."',";
												 		$values.="'$nome'";
		                				#echo "<br>D_".$this->fields[$i]['VAR']."=$nome<br>";
		                			}
		                		}
		                		break;
		                case "time":
		                				if ($fields!='') $fields.=',';
												 		if ($values!='') $values.=',';
		                				$fields.=$this->fields[$i]['VAR']."_H,";
												 		$fields.=$this->fields[$i]['VAR']."_M";
												 		$values.="'".$in[$this->fields[$i]['VAR'].'_H']."',";
												 		$values.="'".$in[$this->fields[$i]['VAR'].'_M']."'";
		                		break;
		                case "file":
		                				#echo "<hr>{$in[$this->fields[$i]['VAR']]}";
		                				if ($_FILES[$this->fields[$i]['VAR']]['name']!=''){
		                				$pk_key=$this->pk_key();
														$pk_keys_concat="FILE";
														if ($fields!='') $fields.=',';
												 		if ($values!='') $values.=',';
														foreach($pk_key as $keys => $val) $pk_keys_concat.="_{$in[$val]}";
														$filename=$_FILES[$this->fields[$i]['VAR']]['name'];
														$ext=explode(".", $filename);
														#$ext=$ext[1];
														$file_to_write=$pk_keys_concat.".".$ext[1];
														$in[$this->fields[$i]['VAR']]=$file_to_write;
														$file_to_write=$dir_file.$file_to_write;
														if (!move_uploaded_file($_FILES[$this->fields[$i]['VAR']]['tmp_name'], $file_to_write)) die("ERRORE COPIA FILE $file_to_write");
												 		$fields.=$this->fields[$i]['VAR'];
												 		$fields.=",D_".$this->fields[$i]['VAR'];
												 		$values.="'".$in[$this->fields[$i]['VAR']]."'";
												 		$vin="D_".$this->fields[$i]['VAR'];
												 		$in[$vin]=$_FILES[$this->fields[$i]['VAR']]['name'];
												 		$values.=",'".$_FILES[$this->fields[$i]['VAR']]['name']."'";
												 	}
		                		break;
		                default:
		                	 if ($in[$this->fields[$i]['VAR']]!=''){
			                	 if ($fields!='') $fields.=',';
												 if ($values!='') $values.=',';
												 $fields.=$this->fields[$i]['VAR'];
												 if ($in[$this->fields[$i]['VAR']]=='next'){
												 	if ($this->fields[$i]['WHERE']!='') $where="where ".$this->fields[$i]['WHERE'];
												 	//$where=preg_replace("/\[(.*?)\]/e","var_glob('\\1')" , $where);
													$where=preg_replace_callback ( "/\[(.*?)\]/", function($matches){return var_glob($matches[1]);}, $where );
												 	$query="select max(".$this->fields[$i]['VAR'].") as max from ".$this->form['TABLE']." $where";
												 	#echo $query;
												 	$sql=new query($conn);
												 	$sql->set_sql($query);
												 	$sql->exec();//obsoleto trovare dove testare
												 	$sql->get_row();
												 	$in[$this->fields[$i]['VAR']]=$sql->row['MAX']+1;
												 }
												 if ($in[$this->fields[$i]['VAR']]=='sysdate')
												  $values.=$in[$this->fields[$i]['VAR']];
		                     else
												  $values.="'".$in[$this->fields[$i]['VAR']]."'";
			              }
		                   break;
		            endswitch;
					}
				}

				$this->sql_query="insert into ".$this->form['TABLE']." ($fields) values ($values)";
		}
		else {
				for ($i=0;$i<count($this->fields);$i++){
					if (($this->fields[$i]['TB']!='no') && count($this->fields[$i])>0 && $this->fields[$i]['VAR']!=''){
						$field=new field($this, $i);

						switch($this->fields[$i]['TYPE']):
		                case "data":
			                		if ($fields!='') $fields.=',';
			                		$fields.=$this->fields[$i]['VAR']."=to_date('".$in[$this->fields[$i]['VAR']]."','DDMMYYYY')";
			                		if ($fields!='') $fields.=',';
			                		$rc=$this->fields[$i]['VAR'].'RC';
			                	 $fields.=$this->fields[$i]['VAR'].'RC'."='".$in[$rc]."'";
		                    break;
		                case "text":
		                	break;
		                case "checkbox":
		                   	foreach ($field->values as $nomec => $nome) {
		                   		if ($in[$nomec]!='') {
		                   			if ($fields!='') $fields.=',';
		                   			$fields.=$nomec."='".$in[$nomec]."'";
		                   		}
		                   	}
		                    break;
		                case "radio":
		                		foreach ($field->values as $nomec => $nome) {
		                			if ($nomec==$in[$this->fields[$i]['VAR']])
		                			{
		                				if ($fields!='') $fields.=',';
		                				$nome=preg_replace("/'/", "''", $nome);
												 		$fields.=$this->fields[$i]['VAR']."='".$in[$this->fields[$i]['VAR']]."',";
												 		$fields.="D_".$this->fields[$i]['VAR']."='$nome'";
		                			}
		                		}
		                		break;
		                case "radio_select":
		                		if (!isset($radio_exist[$this->fields[$i]['RADIO']]))
		                		 {
		                		 		if ($fields!='') $fields.=',';
		                				$fields.=$this->fields[$i]['RADIO']."='".$in[$this->fields[$i]['RADIO']]."'";
												 		$radio_exist[$this->fields[$i]['RADIO']]=true;
		                		}
		                		#echo $fields;
		                		foreach ($field->values as $nomec => $nome) {
		                			if ($nomec==$in[$this->fields[$i]['VAR']])
		                			{
		                				if ($fields!='') $fields.=',';
		                				$nome=preg_replace("/'/", "''", $nome);
												 		$fields.=$this->fields[$i]['VAR']."='".$in[$this->fields[$i]['VAR']]."',";
												 		$fields.="D_".$this->fields[$i]['VAR']."='$nome'";
		                			}
		                		}
		                		break;
		                case "check_select":
		                				if ($fields!='') $fields.=',';
		                				$fields.=$this->fields[$i]['CHECK']."='".$in[$this->fields[$i]['CHECK']]."'";
		                		foreach ($field->values as $nomec => $nome) {
		                			if ($nomec==$in[$this->fields[$i]['VAR']])
		                			{
		                				if ($fields!='') $fields.=',';
		                				$nome=preg_replace("/'/", "''", $nome);
												 		$fields.=$this->fields[$i]['VAR']."='".$in[$this->fields[$i]['VAR']]."',";
												 		$fields.="D_".$this->fields[$i]['VAR']."='$nome'";
		                			}
		                		}
		                		break;
		                case "select":
		                		foreach ($field->values as $nomec => $nome) {
		                			if ($nomec==$in[$this->fields[$i]['VAR']])
		                			{
		                				if ($fields!='') $fields.=',';
		                				$nome=preg_replace("/?/", "i'", $nome);
												 		$nome=preg_replace("/?/", "a'", $nome);
												 		$nome=preg_replace("/?/", "e'", $nome);
												 		$nome=preg_replace("/?/", "o'", $nome);
												 		$nome=preg_replace("/?/", "u'", $nome);
		                				$nome=preg_replace("/'/", "''", $nome);
												 		$fields.=$this->fields[$i]['VAR']."='".$in[$this->fields[$i]['VAR']]."',";
												 		$fields.="D_".$this->fields[$i]['VAR']."='$nome'";
		                			}
		                		}
		                		if ($in[$this->fields[$i]['VAR']]==''){
		                			if ($fields!='') $fields.=',';
		                			$fields.=$this->fields[$i]['VAR']."='".$in[$this->fields[$i]['VAR']]."',";
												 	$fields.="D_".$this->fields[$i]['VAR']."=''";
		                			}
		                		break;
		                 case "time":
		                 				if ($fields!='') $fields.=',';
		                				$fields.=$this->fields[$i]['VAR']."_H='".$in[$this->fields[$i]['VAR'].'_H']."',";
												 		$fields.=$this->fields[$i]['VAR']."_M='".$in[$this->fields[$i]['VAR'].'_M']."'";
												 		#$values.="'".$in[$this->fields[$i]['VAR'].'_H']."',";
												 		#$values.="'".$in[$this->fields[$i]['VAR'].'_M']."'";
		                		break;
		                 case "file":
		                # echo "<hr>{$this->fields[$i]['VAR']} - {$_FILES[$this->fields[$i]['VAR']]['name']}";
		                 if ($_FILES[$this->fields[$i]['VAR']]['name']!=''){
		                 				if ($fields!='') $fields.=',';
		                				$pk_key=$this->pk_key();
														$pk_keys_concat="FILE";
														foreach($pk_key as $keys => $val) $pk_keys_concat.="_{$in[$val]}";
														$filename=$_FILES[$this->fields[$i]['VAR']]['name'];
														$ext=explode(".", $filename);
														$file_to_write=$pk_keys_concat.".".$ext[1];
														$in[$this->fields[$i]['VAR']]=$file_to_write;
														$file_to_write=$dir_file.$file_to_write;
														#echo "<hr>".$file_to_write;
														if (!move_uploaded_file($_FILES[$this->fields[$i]['VAR']]['tmp_name'], $file_to_write)) die("ERRORE COPIA FILE");
												 		$fields.=$this->fields[$i]['VAR']."='".$in[$this->fields[$i]['VAR']]."'";
												 		$fields.=", D_".$this->fields[$i]['VAR']."='".$_FILES[$this->fields[$i]['VAR']]['name']."'";
												 	}
		                		break;
		                default:
			                	 if ($fields!='') $fields.=',';
												 $fields.=$this->fields[$i]['VAR']."='".$in[$this->fields[$i]['VAR']]."'";
		                   break;
		            endswitch;
					}
				}
				$where=$this->pk_where();
				if ($where!='') $where="where ".$where;
				#echo "<hr>$fields <hr>$where";
				$this->sql_query="update ".$this->form['TABLE']." set $fields $where";
		}
//echo "<hr> $this->sql_query <hr>";
	}

	function query_abilita(){
		global $in;
		global $conn;
			$query=new query($conn);
			$nq=0;
			for ($en=0;$en<count($this->enable);$en++){
				if (isset($in['invia']) || $in['INVIOCO']=='1' || $this->enable[$en]['ONSAVE']!='') {
					#echo "<hr>Controllo abilitazioni";
					if ($in['PROGR']=='') $in['PROGR']=1;
						$vis_num=$this->enable[$en]['VISITNUM'];
						$es_num=$this->enable[$en]['NUMBER'];
						if ($this->enable[$en]['PROGR']!='') $in['PROGR']=$this->enable[$en]['PROGR'];
						$cond_var=$this->enable[$en]['CONDITION_VAR'];
						$cond_val=$this->enable[$en]['CONDITION_VALUE'];
//						$condition_passed=($in[$cond_var]==$cond_val);
//						if (preg_math(",",$cond_val)) {
//							$cond_vals=explode(",", $cond_val);
//							for ($i=0;$i<count($cond_vals);$i++) if ($in[$cond_var]==$cond_vals[$i]) $condition_passed=true;
//						}
						if ($cond_var=='' || ($cond_var!='' && $in[$cond_var]==$cond_val)) {
							#echo "<hr>Controllo abilitazioni 1";
							$query_abil="select * from ".$GLOBALS['service']."_coordinate where visitnum='$vis_num' and esam='$es_num' and progr='".$in['PROGR']."' and codpat='".$in['CODPAT']."'";
							#echo "<hr>$query_abil<hr>";
							$query->set_sql($query_abil);
							$query->exec();//obsoleto trovare dove testare
							#echo "<hr>".$query->numrows;
							if (!($query->numrows>=1)) {
								$query_ins_abil="insert into ".$GLOBALS['service']."_coordinate (visitnum,esam,progr,codpat, abilitato) values ('$vis_num','$es_num','".$in['PROGR']."','".$in['CODPAT']."','1')";
								$this->query_enable[$nq]=$query_ins_abil;
								#echo "<br>$query_ins_abil[$nq]<hr>";
								$nq++;
							}
						}
				}
			}
	}


###sub query_builder() as void###
	function query_builder(){
		global $in;
		global $conn;
		global $dir;
		global $_FILES;
		$dir_file=$dir."/uploaded_file/";
		foreach ($in as $key => $value) $in[$key]=preg_replace("/'/", "''", $value);
		$sql= new query($conn);
		$this->progr=$in['PROGR'];
		if ($in['CODPAT']=='next') $this->progr=1;
		else {
			if ($this->progr=='next' || $this->progr==''){
				$query="select max(progr) as max from ".$GLOBALS['service']."_coordinate where codpat='".$in['CODPAT']."' and visitnum='".$in['VISITNUM']."' and esam='".$in['ESAM']."'";
				$sql->set_sql($query);
				$sql->exec();//obsoleto trovare dove testare
				$sql->get_row();
				if ($sql->row['MAX']!='') $this->progr='1';
				else $this->progr=$sql->row['MAX']+1;
			  $in['PROGR']=$this->progr;
			}
		}
		$pk_key=$this->pk_key();
		for ($i=0;$i<count($pk_key);$i++) {
			if ($in[$pk_key[$i]]=='next' || $in[$pk_key[$i]]=='progr') $new_insert=true;
		}
		if (!isset($new_insert)){
			$where=$this->pk_where();
			if ($where!='') $where="where ".$where;
			$query="select count(*) as c from ".$this->form['TABLE']." $where";
			#echo "<hr>$query<hr>";
			$sql->set_sql($query);
			$sql->exec();//obsoleto trovare dove testare
			$sql->get_row();
			if ($sql->row['C']!='1') $new_insert=true;
			else 	$new_insert=false;
		}
		$this->query_tb($new_insert);
		$this->query_coordinate($new_insert);
		$this->query_storico($new_insert);
		$this->query_abilita();

	}

###endsub###

	function valida(){
		for ($i=0;$i<count($this->fields);$i++){
		      $field_obj=new field($this, $i);
		      $field_obj->open_field();
		      if (!$field_obj->validata) $this->validata=$field_obj->validata;
		  }
	}

###sub xml_form_by_vals($vals as array) as void###
function xml_form_by_vals($vals){
//	echo "qui <br>";
        $fn=0;
        $en=0;
        $newtag=true;
        $this_node=new xml_node();
        for ($i=0;$i<count($vals);$i++){
                $this_node->xml_node_by_array($vals[$i]);
                if ($this_node->type!='cdata'){
                    if ($this_node->tag=='FORM') if ($this_node->type=='open' or $this_node->type=='complete') $this->form=$this_node->attributes;
                    if ($this_node->tag=='FIELD') {
                        if ($this_node->type=='open' or $this_node->type=='complete') {
                            $this->fields[$fn]=$this_node->attributes;
                            $this->vars[$this_node->attributes['VAR']]=$fn;
                        }
                        if ($this_node->type!='open') {
                            $fn++;
                        }
                    }
                    if ($this_node->tag=='SEND') $this->buttons['INVIA']=$this_node->value;
                    if ($this_node->tag=='SUBMIT') $this->buttons['SUBMIT']=$this_node->value;
                    if ($this_node->tag=='SAVE') $this->buttons['SALVA']=$this_node->value;
                    if ($this_node->tag=='EQUERY_FORM') $this->buttons['EQUERY_FORM']=$this_node->value;
                    if ($this_node->tag=='CANCEL') $this->buttons['ANNULLA']=$this_node->value;
                    if ($this_node->tag=='EXAM') {$this->enable[$en]=$this_node->attributes;$en++; }
                    if ($this_node->tag=='TXT_VALUE') $this->fields[$fn]['TESTO']=$this_node->value;
                    if ($this_node->tag=='VALUE')
                    {
                    $this->fields[$fn]['VALUE'][$this_node->attributes['VAL']]=$this_node->value;
                    $this->fields[$fn]['VALUE_TXT'][$this_node->attributes['VAL']]=$this_node->attributes['TXT'];
                  }
                }
        }
        global $service;
        $this->form['TABLE']=strtoupper($service)."_". $this->form['TABLE'];
    }
###endsub###

###sub xml_form_by_file($xml_file as string) as void###
    function xml_form_by_file($xml_file){
//    	echo $xml_file."<br>";
        $xml=new my_xml_parser($xml_file);
        $this->xml_form_by_obj($xml);
    }
###endsub###

###sub equery_sql()###
	function equery_sql(){
		global $in;
		global $inputval;
		global $conn;
		global $original_value;
		$sql=new query($conn);
		foreach ($this->fields as $key => $val)
					{
						if ($val['TB']!='no'){
							if ($val['TYPE']=='checkbox'){
									foreach ($val['VALUE'] as $nomec => $nome) {
										if ($fields!='') $fields.=",";
										$fields.=$nomec;
									}
							}
							else {
								if ($fields!='' && $val['VAR']!='') $fields.=",";
								if ($val['TYPE']=='data') $fields.="to_char(".$val['VAR'].", 'DDMMYYYY') as ".$val['VAR']."";
								 else if ($val['VAR']!='') $fields.=$val['VAR'];
								if ($in[$val['VAR']]!=''){
									if ($where!='') $where.=' and ';
									$where.=$val['VAR']."='".$in[$val['VAR']]."'";
								}
							}
						}
					}
				$fields.=",ID,COMMENTO";
				$query="select $fields from eq_".$this->form['TABLE']." where id='".$in['ID']."'";
				#echo "<hr>$query";
				$sql->set_sql($query);
				$sql->exec();//obsoleto trovare dove testare
				if ($sql->numrows>1) error_page ($in['remote_userid'], "Query:\n $query\n results: ".$sql->numrows." records","");
				$sql->get_row();
				#echo $sql->tb_res();
				$original_value=$inputval;
				#foreach ($inputval as $key => $val) echo "<hr> $key $val";
				$inputval=$sql->row;
				#$in=$sql->row;
	}
###endsub###

###sub closed_form()###
	function closed_form(){
		global $in;
		global $inputval;
		global $conn;
		#$debug=true;
		#print_r($this);
//		echo $in['CODPAT']."<hr>";
		if ($in['CODPAT']=='next') return false;
		else $where="VISITNUM='".$in['VISITNUM']."' and ESAM='".$in['ESAM']."' and CODPAT='".$in['CODPAT']."'";
//		echo "PROGR ".$in['PROGR']."<hr>";
//		echo "W= ".$where."<hr>";
//		if ($in['PROGR']=='next') return false;
		if ($in['PROGR']!='') $where.="  and PROGR='".$in['PROGR']."'";
//		echo "Q= ".$where."<hr>";
		$query="select fine from ".$GLOBALS['service']."_coordinate where $where";
//		echo "<hr>$query<hr>";
		$sql=new query($conn);
		$sql->set_sql($query);
		$sql->exec();//obsoleto trovare dove testare
		if ($sql->get_row() || $in['equery_vis']!='' || $in['equery_view']!='' || $in['eform']!='' || $in['TB_COLL']!='') {
			if ($sql->row['FINE']==1) $ret=true;
			else $ret=false;
			$sql_query="select column_name from all_col_comments where table_name='".strtoupper($this->form['TABLE'])."'";
				#if ($debug) echo "<hr>$sql_query<hr>";
				$where='';
				foreach ($this->fields as $key => $val)
					{
						if ($val['TB']!='no'){
							if ($val['TYPE']=='checkbox'){
									foreach ($val['VALUE'] as $nomec => $nome) {
										if ($fields!='') $fields.=",";
										$fields.=$nomec;
									}
							}
							else {
								if ($val['TYPE']=='radio_select'){
										if ($fields!='') $fields.=",";
										$fields.=$val['VAR'];
										$fields.=",".$val['RADIO'];
							}
							if ($val['TYPE']=='check_select'){
										if ($fields!='') $fields.=",";
										$fields.=$val['VAR'];
										$fields.=",".$val['CHECK'];
							}
								if ($fields!='' && $val['VAR']!='') $fields.=",";
								if ($val['TYPE']=='data')
								{
								$fields.="to_char(".$val['VAR'].", 'DDMMYYYY') as ".$val['VAR']."";
								$fields.=",".$val['VAR']."RC  as ".$val['VAR']."RC";
							  }
								else if ($val['VAR']!='') $fields.=$val['VAR'];
								if ($val['TYPE']=='file') $fields.=",D_".$val['VAR']."";
								if ($in[$val['VAR']]!=''){
									if ($where!='') $where.=' and ';
									$where.=$val['VAR']."='".$in[$val['VAR']]."'";
								}
							}
						}
					}
				$sql_pk="select column_name from user_cons_columns where table_name='".$this->form['TABLE']."' and constraint_name=(select constraint_name from user_constraints where table_name='".$this->form['TABLE']."' and constraint_type='P')";
//				echo $sql_pk."<br>";
				$query=new query($conn);
				$query->set_sql($sql_pk);
				$query->exec();//obsoleto trovare dove testare
				$new_insert=false;
				$where='';
				while ($query->get_row())
				{
					if ($in[$query->row['COLUMN_NAME']]!='') {
						if ($where!='') $where.=" and ";
						$where.=$query->row['COLUMN_NAME']."='".$in[$query->row['COLUMN_NAME']]."'";
					}
				}
				$query="select $fields from ".$this->form['TABLE'];
//				echo $query."<br>";
				if ($where!='') $query.=" where $where";
				$sql->set_sql($query);
				#echo "<hr>$query";
				#if ($debug) echo "<hr>$query";
				$sql->exec();//obsoleto trovare dove testare
				if ($sql->numrows>1) error_page ($in['remote_userid'], "Query:\n $query\n results: ".$sql->numrows." records","");
				$sql->get_row();
				$inputval=$sql->row;
//				foreach ($inputval as $key => $val) echo "$key = $val <br>";
//				if ($debug) foreach ($sql->row as $key => $val) echo "$key - $in[$key]=$val <br>";
				return $ret;
		}
		else return false;
	}
###endsub###

function tb_coll_open_form(){
	global $in;
	for ($i=0;$i<$colonne;$i++) $this->body.="<td width=\"".$width."%\">&nbsp;</td><td width=\"".$width."%\">&nbsp;</td>";
		  #$this->body.="</tr>";
		  $c=0;
		  #echo "<hr>colonne= $colonne<hr>";
		  for ($i=0;$i<count($this->fields);$i++){
		      $field_obj=new field($this, $i);
		      $field_obj->open_field();
		      if ($field_obj->attributes['TYPE']!='hidden' && $field_obj->attributes['TYPE']!='') {
		      	 $this->body.="\n<td>".$field_obj->input_field."</td>";
		      }
		      else $this->body.="\n".$field_obj->input_field;
		      $this->salva_js.=$field_obj->salva_js;
		      $this->check_js.=$field_obj->check_js;
		      $this->invia_js.=$field_obj->invia_js;
		      if (!$field_obj->validata) $this->validata=$field_obj->validata;
		      $controlli.=$field_obj->controlli;
		  }
		  $this->body.="
		  <!--FINE CAMPI-->
		  ";
}

function tb_coll_closed_form(){
	global $in;
	for ($i=0;$i<$colonne;$i++) $this->body.="<td width=\"".$width."%\">&nbsp;</td><td width=\"".$width."%\">&nbsp;</td>";
		  #$this->body.="</tr>";
		  $c=0;
		  #echo "<hr>colonne= $colonne<hr>";
		  for ($i=0;$i<count($this->fields);$i++){
		      $field_obj=new field($this, $i);
		      $field_obj->close_field();
		      if ($field_obj->attributes['TYPE']!='hidden' && $field_obj->attributes['TYPE']!='') {
		      	 $this->body.="\n<td>".$field_obj->input_field."</td>";
		      }
		      else $this->body.="\n".$field_obj->input_field;
		  }
		  $this->body.="
		  <!--FINE CAMPI-->
		  ";
}

function tb_coll_header(){
	global $in;
	for ($i=0;$i<$colonne;$i++) $this->body.="<td width=\"".$width."%\">&nbsp;</td><td width=\"".$width."%\">&nbsp;</td>";
		  #$this->body.="</tr>";
		  $c=0;
		  #echo "<hr>colonne= $colonne<hr>";
		  for ($i=0;$i<count($this->fields);$i++){
		      $field_obj=new field($this, $i);
		      $field_obj->open_field();
		      if ($field_obj->attributes['TYPE']!='hidden' && $field_obj->attributes['TYPE']!='') {
		      	 $this->body.="\n<td><b>".$field_obj->input_txt."</b></td>";
		      }
		      else $this->body.="\n".$field_obj->input_txt;
		      $this->salva_js.=$field_obj->salva_js;
		      $this->check_js.=$field_obj->check_js;
		      $this->invia_js.=$field_obj->invia_js;
		      if (!$field_obj->validata) $this->validata=$field_obj->validata;
		      $controlli.=$field_obj->controlli;
		  }
		  $this->body.="
		  <!--FINE CAMPI-->
		  ";
}


###sub open_form() as void###
	function open_form(){
			global $percorso;
		  global $in;
		  global $conn;
      global $inputval;
      $this->salva_js="
		  		function salva_f(){
		  		f=document.forms[0];
					el=f.elements;

					specifiche='A=ON&L=0&F=0';
		  		c1='';
		  		";
		  $this->invia_js="
		  		function invia_f(){
		  		f=document.forms[0];
					el=f.elements;
					specifiche='A=ON&L=0&F=0';
		  		c1='';
		  		";
		  $this->check_js='
		  		function cf(){
		  		f=document.forms[0];
					el=f.elements;
					//alert (el.length);
		  		document.forms[0].action=\'\';
		  		'
		  		;
			  #echo $percorso;
			  $colonne=$this->form['COLS'];
			  $sysdate=date("dmY");
			  $percorso.="&nbsp;&gt;&nbsp;<b>".$this->form['TITOLO']."</b>";
			  if ($in['ESAM']!=0) $patient_table=patient_table();
		 		 $this->body='<form method=post  enctype="multipart/form-data"  onsubmit="return false;" onKeypress="if (event.keyCode==13) return false;">
		               <input type="hidden" name="'.$this->form['TABLE'].'"/>
		               <table class="sf" align="center" border="0" cellpadding="2" cellspacing="2" width="98%">
									  <tbody>
									 '.$patient_table.'
		       				 <table class="sf" align="center" border="0" cellpadding="2" cellspacing="2" width="80%"><tr>
		       				 <!-- CAMPI -->';
		  $width=100/($colonne*2);
		  for ($i=0;$i<$colonne;$i++) $this->body.="<td width=\"".$width."%\">&nbsp;</td><td width=\"".$width."%\">&nbsp;</td>";
		  #$this->body.="</tr>";
		  $c=0;
		  #echo "<hr>colonne= $colonne<hr>";
		  for ($i=0;$i<count($this->fields);$i++){
		      $field_obj=new field($this, $i);
		      #print_r($field_obj);
		      if ($field_obj->attributes['HIDE']=='yes') {
		      	if (isset($field_obj->attributes['NAME']) && $field_obj->attributes['NAME']!='') $this->body.="</tr>\n<tr id='{$field_obj->attributes['NAME']}'>";
		      	else $this->body.="</tr>\n<tr id='{$field_obj->attributes['VAR']}'>";
		      	$c=0;
		      }
		      $field_obj->open_field();
		      #echo "<br>{$field_obj->attributes['VAR']} {$field_obj->attributes['TYPE']} - $colonne - $c -post ";

		      if ($colonne == $c) {
		      		$this->body.="</tr>\n<tr>";
		      		$c=0;
		      	}
		      	#echo $c;
		      if ($field_obj->attributes['TYPE']!='hidden' && $field_obj->attributes['TYPE']!='') {
		      	if ($field_obj->attributes['COLS']=='') $c++;
		      	else {
		      		$c+=$field_obj->attributes['COLS'];

		      	}
		      }
		      $this->body.="\n".$field_obj->html;
		      $this->salva_js.=$field_obj->salva_js;
		      $this->check_js.=$field_obj->check_js;
		      $this->invia_js.=$field_obj->invia_js;
		      if (!$field_obj->validata) $this->validata=$field_obj->validata;
		      $controlli.=$field_obj->controlli;
		  }
		  $js_function_on_send=$this->form['JS_FUNCTION'];
		  $js_function_on_load=$this->form['LOAD'];
		  $this->body.="
		  <!--FINE CAMPI-->
		  ";
		  $this->onload=$js_function_on_load;
		  $this->onload.='cf()';
		  $this->check_js.='
		  }'
		  ;
		  $this->salva_js.='
		  rc=contr(c1,specifiche);
			if (rc) {return false}
			'.$controlli.'
		  if (!rc){
		   document.forms[0].INVIOCO.value=\'0\';
		   document.forms[0].action=\'index.php\';
		    el=document.getElementsByTagName(\'TR\')
		   for (i=0;i<el.length;i++) el[i].style.display=\'\';
		   f=document.forms[0];
			 el=f.elements;
		   for (i=0;i<el.length;i++) el[i].disabled=false;
		   document.forms[0].submit();
		   }
		  }'
		  ;
		   $this->invia_js.='
		   // alert (c1);
		    rc=contr(c1,specifiche);
				if (rc) {return false}
		   '.$controlli.'
		   if (!rc){
			   '.$js_function_on_send.'
			   document.forms[0].INVIOCO.value=\'1\';
			   document.forms[0].action=\'index.php\';
			    el=document.getElementsByTagName(\'TR\')
		   		for (i=0;i<el.length;i++) el[i].style.display=\'\';
			   f=document.forms[0];
				 el=f.elements;
			   for (i=0;i<el.length;i++) el[i].disabled=false;
			   document.forms[0].submit();
			  }
		  }'
		  ;
		  $this->body.='</table><p align=center>';
		  if (isset($in['eform']) && $in['USER_TIP']!='DM') $this->body.='
		  <input type="submit" value="Vai alla form" name="equery" onclick="window.location.href=\'index.php?equery&amp;VISITNUM=\'+document.forms[0].VISITNUM.value+\'&amp;ESAM=\'+document.forms[0].VISITNUM.value+\'&amp;CODPAT=\'+document.forms[0].CODPAT.value+\'&amp;CENTER=\'+document.forms[0].CENTER.value+\'&amp;QUESTION=\'+document.forms[0].QUESTION.value+\'&amp;PROGR=\'+document.forms[0].PROGR.value;"/>
		  ';
		  if ($this->buttons['SALVA'] && ($in['USER_TIP']!='DM' || isset($in['eform']))) $this->body.='
		  <input type="submit" value="'.$this->buttons['SALVA'].'" name="salva" onclick="salva_f();"/>';
		   if ($this->buttons['SUBMIT']!='') $this->body.='
		  <input type="submit" value="'.$this->buttons['SUBMIT'].'" onclick="submit();"/>';
		  if ($this->buttons['INVIA'] && $in['USER_TIP']!='DM' || isset($in['FORM'])) $this->body.='
		  <input type="submit" value="'.$this->buttons['INVIA'].'" name="invia" onclick="invia_f();"/>';
		  //if ($this->buttons['INVIA'] && $in['USER_TIP']=='DM' && !isset($in['FORM']) && isset($in['ID'])) $this->body.='
		  //<input type="hidden" value="'.$in['ID'].'" name="ID_QUERY">
		  //<input type="submit" value="Modify the form for equery '.$in['ID'].'" name="invia_dm" onclick="invia_f();"/>';
		  if ($in['USER_TIP']=='DM' && !isset($in['FORM'])) {
		  	$sql=new query($conn);
		  	global $PROGR;
		  	#echo "<hr><hr><hr>{$PROGR}";
		  	$query="select id , to_char(quest_dt,'DD/MM/YYYY') as data from {$GLOBALS['service']}_equery where visitnum='{$in['VISITNUM']}' and esam='{$in['ESAM']}' and progr='$PROGR' and codpat='{$in['CODPAT']}' and validata is null and to_be_validate=1";
		  	#echo $query;
		  	$sql->set_sql($query);
		  	$sql->exec();//obsoleto trovare dove testare
		  	while ($sql->get_row()){
		  		$equery_option.="<option value=\"{$sql->row['ID']}\">Equery number {$sql->row['ID']} Equery data {$sql->row['DATA']}</option>";
		  	}
		  	if($this->config_service['lang']=="en") $reason="Reason for change:";
			else $reason="Motivo della modifica:";

		  	$this->body.="$reason
		  		<select name='ID_QUERY'>
		  			<option></option>
						<OPTION VALUE=\"-2\">Documentazione di cambiamento</option>
						$equery_option
		  		</select><br/>
		  		<input type=\"submit\" value=\"Procedi\" name=\"invia_dm\" onclick=\"
		  			if (document.forms[0].ID_QUERY.value!='') invia_f();
		  			else {alert ('ATTENZIONE!!! E\\' necessario scegliere un motivo della modifica');document.forms[0].ID_QUERY.focus(); return false;}
		  			\"/>
		  	";
			}
		  if ($this->buttons['ANNULLA']) $this->body.='
		  <input type="reset" value="'.$this->buttons['ANNULLA'].'" name="annulla" />';
		  #echo "<hr>".$this->buttons['ANNULLA'];
		  #if (preg_match("/.test./", $_SERVER['SERVER_NAME'])) $this->body.='&nbsp;<input type="button" value="VARS" name="VARS" onclick="show_values();"/>';
		  $this->body.='</p></table></form>';
		  if ($in['CODPAT']!='') $this->body.='
		  <p align=left><a href="index.php?exams=visite_exams.xml&amp;CENTER='.$in['CENTER'].'&amp;CODPAT='.$in['CODPAT'].'&amp;VISITNUM='.$in['VISITNUM'].'">&lt;&lt;Torna alle schede della visita</a></p>';
	    $href_alternativo="index.php?CENTER=".$in['CENTER']."&CODPAT=".$in['CODPAT']."&VISITNUM=".$in['VISITNUM']."&ESAM=".$in['ESAM']."&PROGR=".$in['PROGR']."&DOWN=1";
	    $this->body=preg_replace("/#HREF#/", $href_alternativo, $this->body);

	}
###endsub###

###sub equery_form() as void###
	function equery_form(){
			global $percorso;
		  global $in;
      global $inputval;
      $this->salva_js="
		  		function salva_f(){
		  		f=document.forms[0];
					el=f.elements;

					specifiche='A=ON&L=0&F=0';
		  		c1='';
		  		";
		  $this->invia_js="
		  		function invia_f(){
		  		f=document.forms[0];
					el=f.elements;
					specifiche='A=ON&L=0&F=0';
		  		c1='';
		  		";
		  $this->check_js='
		  		function cf(){
		  		f=document.forms[0];
					el=f.elements;
					//alert (el.length);
		  		document.forms[0].action=\'\';
		  		'
		  		;

			  #echo $percorso;
			  $percorso.="&gt;".$this->form['TITOLO'];
			  $colonne=$this->form['COLS']+0;
//			   if ($in['all_exams_view']!='') $percorso="";
//		  	 if ($in['FORM']!='') $percorso="";
		  $this->body='<form method=post action="index.php"  enctype=\"multipart/form-data\"  onsubmit="return false;">
		               <input type="hidden" name="EQ_'.$this->form['TABLE'].'"/>
		               ';
		  if ($in['ID']=='') $this->body.='<input type="hidden" name="ID" value="next"/>';
		  else $this->body.='<input type="hidden" name="ID" value="'.$in['ID'].'"/>';
		  $this->body.='
		                <input type="hidden" name="equery" value="'.$in['equery'].'"/>
		                <input type="hidden" name="INVIO_QUERY" value="1"/>
		               <table class="sf" align="center" border="0" cellpadding="2" cellspacing="2" width="98%">
									  <tbody>
									  <tr>
									    <td class="testo" colspan="2">'.$percorso.'</td></tr>
									  <tr>
									    <td colspan="2">
									      <!--table align="center" border="0" cellpadding="2" cellspacing="2" width="93%">
									        <tbody>
									        <tr>
									          <td class="int" colspan="2">'.$this->form['TITOLO'].'</td>
													</tr>
													</tbody>
												</table>
												<table border="0" cellpadding="2" cellspacing="2" width="98%">
												  <tbody>
												  <tr>
												  	<td class="centro" colspan="2" valign="bottom" width="55%"><a href="/help_demography.htm" target="_blank">Help</a></td></tr>
													</tbody>
												</table-->
		       				 <table class="sf" align="center" border="0" cellpadding="2" cellspacing="2" width="80%">
		       				 <tr>
		       				 <!-- CAMPI -->';

		 	$width=100/($colonne*2);
		  for ($i=0;$i<$colonne;$i++) $this->body.="<td width=\"".$width."%\">&nbsp;</td><td width=\"".$width."%\">&nbsp;</td>";
		  $this->body.="</tr>";
		  $c=0;
		  #echo "<hr>colonne= $colonne<hr>";
		  for ($i=0;$i<count($this->fields);$i++){
		      $field_obj=new field($this, $i);
		      $field_obj->open_field();
		      if ($colonne==$c) {
		      		$this->body.="</tr><tr>";
		      		$c=0;
		      	}
		      if ($field_obj->attributes['TYPE']!='hidden') {
		      	if ($field_obj->attributes['COLS']=='') $c++;
		      	else $c+=$field_obj->attributes['COLS'];
		      }
		      if ($field_obj->attributes['VAR']!='INVIOCO'){
		      $field_obj->open_field();
		      $this->body.="\n".$field_obj->html;
		      $this->salva_js.=$field_obj->salva_js;
		      $this->check_js.=$field_obj->check_js;
		      $this->invia_js.=$field_obj->invia_js;
		      if (!$field_obj->validata) $this->validata=$field_obj->validata;
		      $controlli.=$field_obj->controlli;
		    }
		  }
		  $this->body.="
		  <!--FINE CAMPI-->
		  ";
		  $this->onload='cf()';
		  $this->check_js.='
		  }'
		  ;
		  $this->salva_js.='
		  rc=contr(c1,specifiche);
			if (rc) {return false}
		  '.$controlli.'
		  if (!rc){
		   //document.forms[0].INVIOCO.value=\'0\';
		   document.forms[0].action=\'index.php\';
		    el=document.getElementsByTagName(\'TR\')
		   for (i=0;i<el.length;i++) el[i].style.display=\'\';
		   f=document.forms[0];
			 el=f.elements;
		   for (i=0;i<el.length;i++) el[i].disabled=false;
		   document.forms[0].submit();
		   }
		  }'
		  ;
		   $this->invia_js.='
		    //alert (c1);
		    rc=contr(c1,specifiche);
				if (rc) {return false}
		   '.$controlli.'
		   if (!rc){
			  //document.forms[0].INVIOCO.value=\'1\';
			   document.forms[0].action=\'index.php\';
			    el=document.getElementsByTagName(\'TR\')
		   		for (i=0;i<el.length;i++) el[i].style.display=\'\';
			   f=document.forms[0];
				 el=f.elements;
			   for (i=0;i<el.length;i++) el[i].disabled=false;
			   document.forms[0].submit();
			  }
		  }'
		  ;
		  $QUESTION=$in['QUESTION'];
		  $this->body.='</table><p align=center>
		  Insert a Comment:<br/><textarea name="COMMENTO" cols="60" rows="5">'.$QUESTION.'</textarea><br/>
		  <input type="submit" value="Invia eQuery" name="equery_send" onclick="invia_f();"/>
		  <input type="reset" value="Cancel" name="annulla" />';
		  if (preg_match("/.test./", $_SERVER['SERVER_NAME']))
		  $this->body.='&nbsp;<input type="button" value="VARS" name="VARS" onclick="show_values();"/>';
		  $this->body.='</p></table></form>';
	}
###endsub###

###sub close_form() as void###
	function close_form(){
		global $in;
		global $inputval;
		global $percorso;
		/*$percorso=explode(",", $this->form['PERCORSO']);
		  for ($p=0;$p<count($percorso);$p++){
		  	if ($inputval['D_PROTOCOL']=='' && $percorso[$p]=='D_PROTOCOL') $per.="EpSSG Registry";
		  	$per.=$inputval[$percorso[$p]]." &gt; ";
		  }
		  $per.=$this->form['TITOLO'];*/
		  $percorso.="&nbsp;&gt;&nbsp;<b>".$this->form['TITOLO']."</b>";
		  if ($in['all_exams_view']!='') $percorso="";
		  if ($in['FORM']!='') $percorso="";
		  if ($in['ESAM']!=0) $patient_table=patient_table();
		 $this->body='
		 <table class="sf" align="center" border="0" cellpadding="2" cellspacing="2" width="98%">
		  <tbody>
		  <tr>
		    <td class="testo" colspan="2">'.$percorso.'</td></tr>
		  <tr>
		    <td colspan="2">
		      <!--table align="center" border="0" cellpadding="2" cellspacing="2" width="98%">
		        <tbody>
		        <tr>
		          <td class="int" colspan="2">'.$this->form['TITOLO'].'</td>
						</tr>
						</tbody>
					</table>
					<table border="0" cellpadding="2" cellspacing="2" width="98%" align="center">
					  <tbody>
					  <tr>
					  	<td class="centro" colspan="2" valign="bottom" width="55%" align="center"><a href="/help.htm" target="_blank">Help</a></td>
					  </tr>
						</tbody>
					</table--></table>
		'.$patient_table.'
		     				 <table class="sf" align="center" border="0" cellpadding="2" cellspacing="2" width="80%"><tr>
		       				 <!-- CAMPI -->';
		  $colonne=$this->form['COLS'];
		  $width=100/($colonne*2);
		  for ($i=0;$i<$colonne;$i++) $this->body.="<td width=\"".$width."%\">&nbsp;</td><td width=\"".$width."%\">&nbsp;</td>";
		  $this->body.="</tr>";
		  $c=0;
		  #echo "<hr>colonne= $colonne<hr>";
		  for ($i=0;$i<count($this->fields);$i++){
		      $field_obj=new field($this, $i);
		      $field_obj->close_field();
		      #echo "<br/>{$field_obj->attributes['VAR']} {$field_obj->attributes['TYPE']} - $colonne - $c -post ";
		      if ($colonne == $c) {
		      		$this->body.="</tr><tr>";
		      		$c=0;
		      	}
		      	#echo $c;
		      if ($field_obj->attributes['TYPE']!='hidden' && $field_obj->attributes['TYPE']!='') {
		      		if ($field_obj->attributes['COLS']=='') $c++;
			      	else {
			      		$c+=$field_obj->attributes['COLS'];

			      	}

		      }
		      if ($field_obj->attributes['TYPE']!='hidden') $this->body.=$field_obj->html;
		      /*$this->salva_js.=$field_obj->salva_js;
		      $this->check_js.=$field_obj->check_js;
		      $this->invia_js.=$field_obj->invia_js;*/
		      if (!$field_obj->validata) $this->validata=$field_obj->validata;
		      $controlli.=$field_obj->controlli;
		  }
		  $this->body.="</table>
		  <!--FINE CAMPI-->
		  ";
		/*
		$this->body.='
		      <table class="sf" align="center" border="0" cellpadding="2" cellspacing="2" width="98%">
		      <tr><td width=50%>&nbsp;</td><td>&nbsp;</td></tr>';
		for ($i=0;$i<count($this->fields);$i++){
		    $field_obj=new field($this, $i);
		    $field_obj->close_field();
		    $this->body.="\n".$field_obj->html;
		}*/
		$this->onload='';
		#$this->body.='</table>';
		if (isset($in['ESAM'])&& $in['ESAM']==6)
		{
  	 $link_sae=Set_formAE($this->body);
		 $this->body.="<a href=\"$link_sae\">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<img border=\"0\" src=\"/images/pdf.gif\" >Stampa Scheda di segnalazione</a><br>";
    }
		if (isset($in['ESAM']) && $in['USER_TIP']!='RO')	$this->body.="<a href=\"index.php?CENTER=".$in['CENTER']."&amp;CODPAT=".$in['CODPAT']."&amp;VISITNUM=".$in['VISITNUM']."&amp;ESAM=".$in['ESAM']."&amp;PROGR=".$in['PROGR']."&amp;eform=equery.xml\">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Invia eQuery</a><br>";
		if ($in['all_exams_view']=='' && $in['equery_vis']=='' && $in['equery_view']=='' && $in['eform']=='' && $in['form']!='completa_autocert.xml')$this->body.='
		  <p align=left><a href="index.php?exams=visite_exams.xml&amp;CENTER='.$in['CENTER'].'&amp;CODPAT='.$in['CODPAT'].'&amp;VISITNUM='.$in['VISITNUM'].'">&lt;&lt;Torna alle schede della visita</a>';
		global $inputval;
		if ($in['equery_vis'] && $inputval['TO_BE_VALIDATE']=='1' && $inputval['VALIDATA']!='1') $this->body.=' <p align=left><a href="index.php?equery_view=vis&ID='.$in['ID'].'&amp;CODPAT='.$inputval['CODPAT'].'&amp;VISITNUM='.$inputval['VISITNUM'].'&amp;ESAM='.$inputval['ESAM'].'&amp;PROGR='.$inputval['PROGR'].'">&lt;&lt;Vai alla form di validazione</a>';
		if ($in['all_exams_view']=='') $this->body.="<br/><a href=\"javascript:history.back();\">&lt;&lt;{$this->config_service['Torna_lista_schede']}</a>";
		$this->body.="</p>";
		  $href_alternativo="index.php?CENTER=".$in['CENTER']."&CODPAT=".$in['CODPAT']."&VISITNUM=".$in['VISITNUM']."&ESAM=".$in['ESAM']."&PROGR=".$in['PROGR']."&DOWN=1";
	    $this->body=preg_replace("/#HREF#/", $href_alternativo, $this->body);
      $this->body=preg_replace("/<tr><\/tr>/", "",$this->body);

	}

###endsub###

###sub equery_closed_form() as void###
	function equery_closed_form(){
		global $in;
		global $percorso;
		global $inputval;
		global $conn;
		/*$percorso=explode(",", $this->form['PERCORSO']);
		  for ($p=0;$p<count($percorso);$p++){
		  	if ($inputval['D_PROTOCOL']=='' && $percorso[$p]=='D_PROTOCOL') $per.="EpSSG Registry";
		  	$per.=$inputval[$percorso[$p]]." &gt; ";
		  }
		  $per.=$this->form['TITOLO'];*/
		  $percorso.="&gt;".$this->form['TITOLO'];
		  if ($in['all_exams_view']!='') $percorso="";
		 $this->body='
		 <table class="sf" align="center" border="0" cellpadding="2" cellspacing="2" width="98%">
		  <tbody>
		  <tr>
		    <td class="testo" colspan="2">'.$percorso.'</td></tr>
		  <tr>
		    <td colspan="2">
		      <!--table align="center" border="0" cellpadding="2" cellspacing="2" width="93%">
		        <tbody>
		        <tr>
		          <td class="int" colspan="2">'.$this->form['TITOLO'].'</td>
						</tr>
						</tbody>
					</table>
					<table border="0" cellpadding="2" cellspacing="2" width="98%" align="center">
					  <tbody>
					  <tr>
					  	<td class="centro" colspan="2" valign="bottom" width="55%" align="center"><a href="/help_demography.htm" target="_blank">Help</a></td></tr>
						</tbody>
					</table-->
		     	<table class="sf" align="center" border="0" cellpadding="2" cellspacing="2" width="80%"><tr>
		       <!-- CAMPI -->';
		global $original_value;
		$colonne=$this->form['COLS'];
		  $width=100/($colonne*2);
		  for ($i=0;$i<$colonne;$i++) $this->body.="<td width=\"".$width."%\">&nbsp;</td><td width=\"".$width."%\">&nbsp;</td>";
		  $this->body.="</tr>";
		  $c=0;
		  #echo "<hr>colonne= $colonne<hr>";
		  for ($i=0;$i<count($this->fields);$i++){
		      $field_obj=new field($this, $i);
		      $field_obj->close_field();
		      #echo "<br/>{$field_obj->attributes['VAR']} {$field_obj->attributes['TYPE']} - $colonne - $c -post ";
		      if ($colonne == $c) {
		      		$this->body.="</tr><tr>";
		      		$c=0;
		      	}
		      	#echo $c;
		      if ($field_obj->attributes['TYPE']!='hidden' && $field_obj->attributes['TYPE']!='') {
		      	if ($field_obj->attributes['COLS']=='') $c++;
		      	else {
		      		$c+=$field_obj->attributes['COLS'];

		      	}
		      }
		      $this->body.="\n".$field_obj->html;
		      if ($inputval[$field_obj->attributes['VAR']]!=$original_value[$field_obj->attributes['VAR']]) $this->body.="<tr><td colspan=2 align=center><font color=red>Field modified by equery</font></td></tr>";
		}
		/*for ($i=0;$i<count($this->fields);$i++){
		    $field_obj=new field($this, $i);
		    $field_obj->close_field();
		    $this->body.="\n".$field_obj->html;
		    #echo "<hr>".$inputval[$field_obj->attributes['VAR']]." - ".$original_value[$field_obj->attributes['VAR']];
		    if ($inputval[$field_obj->attributes['VAR']]!=$original_value[$field_obj->attributes['VAR']]) $this->body.="<tr><td colspan=2 align=center><font color=red>Field modified by equery</font></td></tr>";
		}*/
		$this->onload='';
		$this->body.='</table></tr></table><p align=center>Comment: <b>'.$inputval['COMMENTO'].'</b></p>
		';
		if ($in['USER_TIP']=='DM') {
			$query=new query($conn);
			$sql="select VISITNUM, ESAM, PROGR, CODPAT from ".$GLOBALS['service']."_equery where id=".$in['ID']."";
			#echo "<hr>$sql";
			$query->set_sql($sql);
			$query->exec();//obsoleto trovare dove testare
			$query->get_row();
			#echo $query->row['VISITNUM'];
			$equery=$query->row;
			#foreach ($query->row as $key => $val) echo "<br/> $key -- $val";
			$this->body.='</table>
				<form method=post action="index.php" >
					<p align=center>
						<input type="hidden" name="ID" value="'.$in['ID'].'" />
						<input type="hidden" name="VISITNUM" value="'.$equery['VISITNUM'].'"/>
						<input type="hidden" name="ESAM" value="'.$equery['ESAM'].'"/>
						<input type="hidden" name="PROGR" value="'.$equery['PROGR'].'"/>
						<input type="hidden" name="CODPAT" value="'.$equery['CODPAT'].'"/>
						<input type=submit value="Validate" name="equery_validate"/>&nbsp;
						<input type="submit" value="Close without validation" name="equery_close"/>
					</p>
				</form>
		';
		}
		if ($in['all_exams_view']=='' && $in['equery_view']=='') $this->body.='
		  <p align=left><a href="index.php?exams=visite_exams.xml&amp;CODPAT='.$in['CODPAT'].'&amp;VISITNUM='.$in['VISITNUM'].'">&lt;&lt;List of surveys</a></p>';
	}

###endsub###


###sub make_html() as void###
    function make_html(){
        global $in;
        global $inputval;
        global $remote_userid;
        if ($in['USER_TIP']=='DE'){
        	if (!$this->closed_form()) $this->open_form();
			    else $this->close_form();
		  	}


		  	if ($in['USER_TIP']=='DM'){
	        if (!$this->closed_form()) $this->close_form();
			    else $this->open_form();
		  	}
		  	if ($in['USER_TIP']=='RO'){
	        $this->closed_form();
	        $this->close_form();
		  	}

    }
###endsub###

		function allinea_db(){
			global $in;
			global $conn;
			#echo "<hr>ALLINEAMENTO FORM<hr>";
			$tb_exist=false;
			$query="select column_name from all_col_comments where table_name='".$this->form['TABLE']."'";
			//echo $query."<hr>";
			$sql=new query($conn);
			$sql->set_sql($query);
			$sql->exec();//obsoleto trovare dove testare
			$r=0;
			$f=0;
			$all_field_exist=true;
			for ($i=0;$i<count($this->fields);$i++){
					if ($this->fields[$i]['TB']!='no' && $this->fields[$i]['TYPE']!=''){
						if ($this->fields[$i]['VAR_TYPE']=='text') {
							$vars[$f]['NAME'].=$this->fields[$i]['VAR'];
							$vars[$f]['TYPE'].="varchar2(".$this->fields[$i]['VAR_SIZE'].")";
						}
						if ($this->fields[$i]['VAR_TYPE']=='number') {
							$vars[$f]['NAME'].=$this->fields[$i]['VAR'];
							$vars[$f]['TYPE'].="number";
						}
						if ($this->fields[$i]['TYPE']=='select') {
							 $vars[$f]['NAME'].=$this->fields[$i]['VAR'];
							 $vars[$f]['TYPE'].='number';
							 $f++;
							 $vars[$f]['NAME'].="D_".$this->fields[$i]['VAR'];
							 $vars[$f]['TYPE'].='varchar2(300)';
						}
						if ($this->fields[$i]['TYPE']=='file') {
							 $vars[$f]['NAME'].=$this->fields[$i]['VAR'];
							 $vars[$f]['TYPE'].='varchar2(400)';
							 $f++;
							 $vars[$f]['NAME'].="D_".$this->fields[$i]['VAR'];
							 $vars[$f]['TYPE'].='varchar2(300)';
						}
						if ($this->fields[$i]['TYPE']=='radio_select') {
							 $vars[$f]['NAME'].=$this->fields[$i]['VAR'];
							 $vars[$f]['TYPE'].='number';
							 $f++;
							 $vars[$f]['NAME'].="D_".$this->fields[$i]['VAR'];
							 $vars[$f]['TYPE'].='varchar2(300)';
							 if(!$var_exist[$this->fields[$i]['RADIO']]) {
							 		 $f++;
							 		 $vars[$f]['NAME'].=$this->fields[$i]['RADIO'];
									 $vars[$f]['TYPE'].='number';
									 $f++;
									 $vars[$f]['NAME'].="D_".$this->fields[$i]['RADIO'];
									 $vars[$f]['TYPE'].='varchar2(300)';
									 $var_exist[$this->fields[$i]['RADIO']]=true;
							 }
						}
						if ($this->fields[$i]['TYPE']=='check_select') {
							 $vars[$f]['NAME'].=$this->fields[$i]['VAR'];
							 $vars[$f]['TYPE'].='number';
							 $f++;
							 $vars[$f]['NAME'].="D_".$this->fields[$i]['VAR'];
							 $vars[$f]['TYPE'].='varchar2(300)';
							 $f++;
							 $vars[$f]['NAME'].=$this->fields[$i]['CHECK'];
							 $vars[$f]['TYPE'].='number';
						}
						if ($this->fields[$i]['TYPE']=='time') {
							 $vars[$f]['NAME'].=$this->fields[$i]['VAR']."_H";
							 $vars[$f]['TYPE'].='number';
							 $f++;
							 $vars[$f]['NAME'].=$this->fields[$i]['VAR']."_M";
							 $vars[$f]['TYPE'].='number';
						}
						if ($this->fields[$i]['TYPE']=='data') {
							 $vars[$f]['NAME'].=$this->fields[$i]['VAR'];
							 $vars[$f]['TYPE'].='date';
							 $f++;
							 $vars[$f]['NAME'].=$this->fields[$i]['VAR']."RC";
							 $vars[$f]['TYPE'].='varchar2(8)';
						}
						if ($this->fields[$i]['TYPE']=='radio') {
							 $vars[$f]['NAME'].=$this->fields[$i]['VAR'];
							 $vars[$f]['TYPE'].='number';
							 $f++;
							 $vars[$f]['NAME'].="D_".$this->fields[$i]['VAR'];
							 $vars[$f]['TYPE'].='varchar2(300)';
						}
						if ($this->fields[$i]['TYPE']=='checkbox'){
							foreach ($this->fields[$i]['VALUE'] as $key => $val) {
								$vars[$f]['NAME'].=$key;
							 	$vars[$f]['TYPE'].='number';
							 	$f++;
							}
						}
						$vars[$f]['PK']=$this->fields[$i]['PK'];
						$f++;
					}
				}
			while ($sql->get_row()) {
				$res[$i]=$sql->row['COLUMN_NAME'];
				$i++;
			}
			if ($sql->numrows>0) $tb_exist=true;
			if ($tb_exist){
				$sql_pk="";
				$c=0;
				$all_field_exist=true;
				for ($f=0;$f<=count($vars);$f++){
					if ($vars[$f]['NAME']!=''){
						if ($vars[$f]['PK']=='yes') {
							if ($sql_pk_fields!='') $sql_pk_fields.=',';
							$sql_pk_fields.=$vars[$f]['NAME'];
						}
						$field_exist=false;
						foreach ($res as $key => $val) if ($val==$vars[$f]['NAME']) $field_exist=true;
						if (!$field_exist){
							$all_field_exist=false;
							$eq_sql_str[$c]="alter table EQ_".$this->form['TABLE']." add ".$vars[$f]['NAME']." ".$vars[$f]['TYPE'];
							$s_sql_str[$c]="alter table S_".$this->form['TABLE']." add ".$vars[$f]['NAME']." ".$vars[$f]['TYPE'];
							$sql_str[$c]="alter table ".$this->form['TABLE']." add ".$vars[$f]['NAME']." ".$vars[$f]['TYPE'];
							$c++;
							$this->body.="Field <b>".$vars[$f]['NAME']."</b> ".$vars[$f]['TYPE']." dosen't exist<br/>";
						}
					}
				}
				$sql_pk_drop="alter table ".$this->form['TABLE']." drop constraint PK_".$this->form['TABLE']." cascade";
				$sql_pk="alter table ".$this->form['TABLE']." add constraint PK_".$this->form['TABLE']." primary key ($sql_pk_fields)";
			}
			else {
				$this->body.="Table <b>".$this->form['TABLE']."</b> doesn't exist<br/>";
				$sql_str_ini="create table ".$this->form['TABLE'].'(';
				$sql_pk="alter table ".$this->form['TABLE']." add constraint PK_".$this->form['TABLE']." primary key (";
				for ($i=0;$i<count($this->fields);$i++){
					if ($this->fields[$i]['TB']!='no' && $this->fields[$i]['TYPE']!=''){
						if ($this->fields[$i]['PK']=='yes') {
							if ($sql_pk_keys!='') $sql_pk_keys.=",";
							$sql_pk_keys.=$this->fields[$i]['VAR'];
						}
						if ($sql_str!='') $sql_str.=",";
						if ($this->fields[$i]['VAR_TYPE']=='text') $sql_str.=$this->fields[$i]['VAR']." varchar2(".$this->fields[$i]['VAR_SIZE'].")";
						if ($this->fields[$i]['VAR_TYPE']=='number') $sql_str.=$this->fields[$i]['VAR']." number";
						if ($this->fields[$i]['TYPE']=='data') {
							$sql_str.=$this->fields[$i]['VAR']." date";
							$sql_str.=",".$this->fields[$i]['VAR']."RC varchar2(8)";
						}
						if ($this->fields[$i]['TYPE']=='select') {
							$sql_str.=$this->fields[$i]['VAR']." number";
							$sql_str.=",D_".$this->fields[$i]['VAR']." varchar2(300)";
						}
						if ($this->fields[$i]['TYPE']=='time') {
							$sql_str.=$this->fields[$i]['VAR']."_H number";
							$sql_str.=",".$this->fields[$i]['VAR']."_M number";
						}
						if ($this->fields[$i]['TYPE']=='radio_select') {
							$sql_str.=$this->fields[$i]['VAR']." number";
							$sql_str.=",D_".$this->fields[$i]['VAR']." varchar2(300)";
							if (!isset($radio_exist[$this->fields[$i]['RADIO']])){
								$sql_str.=",".$this->fields[$i]['RADIO']." number";
								$sql_str.=",D_".$this->fields[$i]['RADIO']." varchar2(300)";
								$radio_exist[$this->fields[$i]['RADIO']]=true;
							}
						}
						if ($this->fields[$i]['TYPE']=='check_select') {
							$sql_str.=$this->fields[$i]['VAR']." number";
							$sql_str.=",D_".$this->fields[$i]['VAR']." varchar2(300)";
							$sql_str.=",".$this->fields[$i]['CHECK']." number";
						}
						if ($this->fields[$i]['TYPE']=='radio_textbox') {
							if (!isset($radio_exist[$this->fields[$i]['RADIO']])){
								$sql_str.=",".$this->fields[$i]['RADIO']." number";
								$sql_str.=",D_".$this->fields[$i]['RADIO']." varchar2(300)";
								$radio_exist[$this->fields[$i]['RADIO']]=true;
							}
						}
						if ($this->fields[$i]['TYPE']=='radio') {
							$sql_str.=$this->fields[$i]['VAR']." number";
							$sql_str.=",D_".$this->fields[$i]['VAR']." varchar2(300)";
						}
						if ($this->fields[$i]['TYPE']=='file') {
							$sql_str.=$this->fields[$i]['VAR']." varchar2(400)";
							$sql_str.=",D_".$this->fields[$i]['VAR']." varchar2(300)";

						}
						if ($this->fields[$i]['TYPE']=='checkbox'){
							$first=true;
							foreach ($this->fields[$i]['VALUE'] as $key => $val) {
								if (!$first) $sql_str.=",";
								$first=false;
								$sql_str.="$key number";
							}
						}
					}
				}

			}

			#echo "<hr>in['CREATE'] :".$in['CREATE']."  in['CREATE_'".$this->form['TABLE']."]) :".$in['CREATE_'.$this->form['TABLE']];

			if (isset($in['CREATE']) || isset($in['CREATE_'.$this->form['TABLE']])) {
				#echo "<hr>PROCEDURA DI CREAZIONE ".$this->form['TABLE']."<hr>";
				if (!$tb_exist) {
					$sql_str_end=")";
					$query=$sql_str_ini.$sql_str.$sql_str_end;
					$sql->set_sql($query);
					$sql->ins_upd();//obsoleto
					$sql_pk.=$sql_pk_keys.")";
					#echo $sql_pk;
					$sql->set_sql($sql_pk);
					$sql->ins_upd();//obsoleto
					$eq_table="create table EQ_".$this->form['TABLE']." (ID NUMBER, COMMENTO varchar2(400),".$sql_str.$sql_str_end;
					$sql->set_sql($eq_table);
					$sql->ins_upd();//obsoleto
					$sql_str_ini="create table S_".$this->form['TABLE']."(USERID VARCHAR2(20),MODDT DATE,MODPROG NUMBER not null,FL_QUERY CHAR(1) not null,ID_QUERY NUMBER(6),";
					$query=$sql_str_ini.$sql_str.$sql_str_end;
					$sql->set_sql($query);
					$sql->ins_upd();//obsoleto
					$eq_pk="alter table EQ_".$this->form['TABLE']." add constraint EQ_PK_".$this->form['TABLE']." primary key (ID)";
					$sql->set_sql($eq_pk);
					$sql->ins_upd();//obsoleto
					$s_pk="alter table S_".$this->form['TABLE']." add constraint S_PK_".$this->form['TABLE']." primary key (MODPROG)";
					$sql->set_sql($s_pk);
					$sql->ins_upd();//obsoleto
				}
				if (!$all_field_exist){
					for ($c=0;$c<count($sql_str);$c++){
							$sql->set_sql($sql_str[$c]);
							#echo "<hr>".$sql_str[$c];
							$sql->ins_upd();//obsoleto
							$sql->set_sql($s_sql_str[$c]);
							$sql->ins_upd();//obsoleto
							$sql->set_sql($eq_sql_str[$c]);
							$sql->ins_upd();//obsoleto
					}
					if ($sql_pk!=''){
								$sql->set_sql($sql_pk_drop);
								$sql->ins_upd();//obsoleto
								$sql->set_sql($sql_pk);
								$sql->ins_upd();//obsoleto
							}
				}
				return true;
			}
			else return ($tb_exist && $all_field_exist);
		}


}





?>
