<?
class equery_prototype{
	var $id;
	var $user_abilitato=false;
	var $config;
	var $testi;
	var $conn;
	var $session_vars;
	var $config_service;
	var $workflow;
	var $vlist;
	var $service;
	var $pk_service;
	var $script;
	var $onload;
	var $identifier;
	var $href;
	function equery_prototype($identifier,$conn,$session_vars,$config_service,$workflow,$vlist,$service,$xml_dir,$pk_service){
        $id=null;
		$this->conn=$conn;
		$this->session_vars=$session_vars;
		$this->config_service=$config_service;
		$this->id=$id;
		$this->workflow=$workflow;
		$this->vlist=$vlist;
		$this->service=$service;
		$this->xml_dir=$xml_dir;
		$this->pk_service='ID_PRAT';
		$this->identifier=$identifier;
		$this->configura();
		$this->allinea_db();
	}

	/**
	 * Enter description here...
	 *
	 */
	function allinea_db(){
		$check_str="select count(*) EXIST from user_tables where table_name='{$this->config['table_equery']}'";
		$sql_table_equery_exist=new query($this->conn);
		$sql_table_equery_exist->get_row($check_str);
		if(!$sql_table_equery_exist->row['EXIST']){
			$tables_to_create[]="

create table {$this->config['table_equery']}
(
  ID             NUMBER not null,
  CENTER         VARCHAR2(10),
  STUDY          VARCHAR2(50),
  CODPAT         NUMBER,
  VISITNUM       NUMBER,
  ESAM           NUMBER,
  PROGR          NUMBER,
  Q_USERID       VARCHAR2(32 CHAR),
  QUESTION       VARCHAR2(4000),
  QUEST_DT       DATE,
  TO_BE_VALIDATE NUMBER,
  ANSWER         VARCHAR2(4000),
  ANS_DT         DATE,
  A_USERID       VARCHAR2(32 CHAR),
  VALIDATA       NUMBER,
  CHIUSA         NUMBER,
  VAL_DT         DATE,
  VAL_USERID     VARCHAR2(32 CHAR),
  VISITNUM_PROGR NUMBER,
  CHIUSA_DT      DATE,
  REGISTRY       VARCHAR2(20)
)
;

alter table {$this->config['table_equery']}
  add constraint PK_{$this->config['table_equery']} primary key (ID)
  using index 
  ;
			";
		}

		$check_str="select count(*) EXIST from user_tables where table_name='{$this->config['table_data']}'";
		$sql_table_data_exist=new query($this->conn);
		$sql_table_data_exist->get_row($check_str);
		if(!$sql_table_data_exist->row['EXIST']){
			$tables_to_create[]="
create table {$this->config['table_data']}
(
  CODPAT            NUMBER not null,
  ESAM              NUMBER not null,
  PROGR             NUMBER not null,
  VISITNUM          NUMBER not null,
  VISITNUM_PROGR    NUMBER not null,
  CENTER            VARCHAR2(40),
  ID                NUMBER not null,
  NOMETAB           VARCHAR2(40),
  VAL_NEW           VARCHAR2(40),
  VAL_OLD           VARCHAR2(40),
  FIELD             VARCHAR2(40),
  VAR               VARCHAR2(40) not null,
  EQUERY_IDENTIFIER VARCHAR2(40)
)
;
alter table MED_EQUERY_MODFIELD
  add constraint MED_EQ_FIELD_PK primary key (VISITNUM, VISITNUM_PROGR, PROGR, ESAM, CODPAT, ID, VAR)
  ;

			";
		}
	}
	function save_data_and_equery(){
		global $filetxt;
		global $body;
		//		global $service;
		//		global $config_service;
		global $from_service_email;
		if($this->check_creation_grants() && $this->check_data_mod_grants()){
			$in=$this->session_vars;
			$service=$this->service;
			$config_service=$this->config_service;

			$xml_dir=$this->xml_dir;
			$form=$in['form'];
			$in['INVIOCO']='1';
			$xml_form=new xml_form();
			$xml_form->xml_form_by_file($xml_dir.'/'.$form);
			$xml_form->valida();
			if ($xml_form->validata){
				$differences=$xml_form->differences();
				if(count($differences)>0){
					$str_id_equery="select ".$this->service."_E_SEQ.nextval ID from dual";
					$sql=new query($this->conn);
					$sql->get_row($str_id_equery);
					$id_equery=$sql->row['ID'];
					$equery['ID']=$id_equery;
					$equery['STUDY']=$this->service;
					$equery['CODPAT']=$this->session_vars['CODPAT'];
					$equery['CENTER']=$this->session_vars['CENTER'];
					$equery['ESAM']=$this->session_vars['ESAM'];
					$equery['VISITNUM']=$this->session_vars['VISITNUM'];
					$equery['VISITNUM_PROGR']=$this->session_vars['VISITNUM_PROGR'];
					$equery['PROGR']=$this->session_vars['PROGR'];
					$equery['Q_USERID']=$this->session_vars['remote_userid'];
					$equery['QUESTION']=$this->session_vars['EQUERY_QUESTION'];
					$equery['QUEST_DT']="sysdate";
					$equery['TO_BE_VALIDATE']=1;
					$equery['ANSWER']=1;
					$sql->insert($equery,$this->config['table_equery']);
					foreach ($differences as $curr_difference){
						unset($values);
						//					print_r($curr_difference);
						$values=$curr_difference;
						$values['ID']=$id_equery;
						$values['CODPAT']=$this->session_vars['CODPAT'];
						$values['ESAM']=$this->session_vars['ESAM'];
						$values['VISITNUM']=$this->session_vars['VISITNUM'];
						$values['VISITNUM_PROGR']=$this->session_vars['VISITNUM_PROGR'];
						$values['PROGR']=$this->session_vars['PROGR'];
						$values['CENTER']=$this->session_vars['CENTER'];
						$values['EQUERY_IDENTIFIER']=$this->identifier;
						$sql->insert($values,$this->config['table_data']);

					}

				}
				else{
					error_page($this->session_vars['remote_userid'],'Nessuna modifica effettuata');
				}
				$this->conn->commit();
				header("location:".$this->href('visualizza_form'));
				die();
			}

		}else {
			error_page($this->session_vars['remote_userid'],"privilegi insufficienti per l'operazione richiesta");
		}

	}

	function save_data($id_equery){
		global $conn;
		if($this->check_data_mod_grants()){
			$in=$this->session_vars;
			$service=$this->service;
			$config_service=$this->config_service;

			$xml_dir=$this->xml_dir;
			$form=$in['form'];
			$in['INVIOCO']='1';
			$xml_form=new xml_form();
			$xml_form->xml_form_by_file($xml_dir.'/'.$form);
			$xml_form->valida();
			if ($xml_form->validata){
				$differences=$xml_form->differences();
				if(count($differences)>0){

					foreach ($differences as $curr_difference){
						unset($values);
						//					print_r($curr_difference);
						$values=$curr_difference;
						$values['ID']=$id_equery;
						$values['CODPAT']=$this->session_vars['CODPAT'];
						$values['ESAM']=$this->session_vars['ESAM'];
						$values['VISITNUM']=$this->session_vars['VISITNUM'];
						$values['VISITNUM_PROGR']=$this->session_vars['VISITNUM_PROGR'];
						$values['PROGR']=$this->session_vars['PROGR'];
						$values['CENTER']=$this->session_vars['CENTER'];
						$values['EQUERY_IDENTIFIER']=$this->identifier;
					    $sql=new query($conn);
						$sql->insert($values,$this->config['table_data']);

					}

				}
				else{
					error_page($this->session_vars['remote_userid'],'Nessuna modifica effettuata');
				}
				$this->conn->commit();
				header("location:".$this->href('visualizza_form'));
				die();
			}

		}else {
			error_page($this->session_vars['remote_userid'],"privilegi insufficienti per l'operazione richiesta");
		}

	}

	function save_equery(){
		if($this->check_creation_grants()){
			$str_id_equery="select ".$this->service."_E_SEQ.nextval ID from dual";
			$sql=new query($this->conn);
			$sql->get_row($str_id_equery);
			$id_equery=$sql->row['ID'];
			$equery['ID']=$id_equery;
			$equery['STUDY']=$this->service;
			$equery['CODPAT']=$this->session_vars['CODPAT'];
			$equery['CENTER']=$this->session_vars['CENTER'];
			$equery['ESAM']=$this->session_vars['ESAM'];
			$equery['VISITNUM']=$this->session_vars['VISITNUM'];
			$equery['VISITNUM_PROGR']=$this->session_vars['VISITNUM_PROGR'];
			$equery['PROGR']=$this->session_vars['PROGR'];
			$equery['Q_USERID']=$this->session_vars['remote_userid'];
			$equery['QUESTION']=$this->session_vars['EQUERY_QUESTION'];
			$equery['QUEST_DT']="sysdate";
			$equery['TO_BE_VALIDATE']=1;
			$equery['ANSWER']=1;
			$sql->insert($equery,$this->config['table_equery']);
			$this->conn->commit();
			header("location:".$this->href('visualizza_form'));
		}else {
			error_page($this->session_vars['remote_userid'],"privilegi insufficienti per l'operazione richiesta");
		}

	}

	function save(){
		if($this->session_vars['ID_EQUERY']==''){
			if($this->session_vars['form']!=''){
				return $this->save_data_and_equery();
			}
			else{
				return $this->save_equery();
			}
		}
		else if($this->session_vars['form']!=''){
			return $this->save_data($this->session_vars['ID_EQUERY']);
		}
	}

	function save_definitive_data(){

	}





	function form($xml){
        $body=null;
        $equery_option=null;
		if($this->check_data_mod_grants()){
			$this->session_vars ['form'] = $xml;
			$vlist = $this->vlist;
			$in = $this->session_vars;
			$conn = $this->conn;
			$service = $this->service;
			$xml_form = new xml_form ( $this->conn, $this->service, $this->config_service, $this->session_vars, $this->uploaded_file_dir );
			$xml_form->xml_form_by_file ( $this->xml_dir . '/' . $xml );
			if (! $xml_form->allinea_db ()) {

				$body .= "<p align=center>";
				$body = $xml_form->body;
				$body .= "<form method=post align=center>";

				foreach ( $in as $key => $val )
				$body .= "<input type=\"hidden\" name=\"$key\" value=\"$val\">";
				$body .= "<input type=\"submit\" name=\"CREATE\" value=\"Update DB\"></form></p>";
			}
			else{
				/**
			 *  	$xml_form->make_html (	false, => $no_link_back
			 * 								false, => $closed
			 * 								true,  => $force_open : obbliga la visualizzazione della form in compilazione
			 * 								true   => $exclude_send_buttons : i bottoni salva,invia,annulla non vengono inseriti e la form non viene chiusa lasciando 
			 * 																  modo di gestirli nella funzione chiamante
			 * 							 );
			 */

				$xml_form->make_html (true,false,true,true);


				$body .= $xml_form->body;
				$this->script = "
				<script type=\"text/javascript\">
				" . $xml_form->salva_js . "
				" . $xml_form->invia_js . "
				" . $xml_form->check_js . "
				</script>
				";

				$sql = new query ( $this->conn );
				global $PROGR;
				$query = "select id , to_char(quest_dt,'DD/MM/YYYY') as data from {$this->config_service['service']}_equery where visitnum=:visitnum and esam=:esam and progr=:progr and {$this->pk_service}=:pk_service and validata is null --and to_be_validate=1";
				//			echo $query;
				unset($bind);
				$bind['VISITNUM']=$in['VISITNUM'];
				$bind['ESAM']=$in['ESAM'];
				$bind['PROGR']=$PROGR;
				$bind['PK_SERVICE']=$in[$this->pk_service];
				//$sql->set_sql ( $query );
				$sql->exec ( $query,$bind );//obsoleta?! binded
				while ( $sql->get_row () ) {
					$equery_option .= "<option value=\"{$sql->row['ID']}\">Equery number {$sql->row['ID']} Equery data {$sql->row['DATA']}</option>";
				}
				if($this->config_service['lang']=="en") {
					$reason="Reason for change:";
					$send="Send";
					$opt1="Documentation of change";
					$opt2="Data entry error";
					$alert_msg="WARNING!!! It\\'s necessary to choose a reason for the revision";
					$cancel="Cancel";
				} else {
					$reason="Motivo della modifica:";
					$send="Procedi";
					$opt1="Documentazione di cambiamento";
					$opt2="Errore inserimento dati";
					$alert_msg="ATTENZIONE!!! E\\' necessario scegliere un motivo della modifica";
					$cancel="Annulla";
				}

				$question=$this->reason_field();
				$invia="<input type=\"submit\" value=\"$send\" name=\"invia_dm\" onclick=\"
		  			invia_f();
		  			
		  			\"/>";
				$annulla= '
			<input type="hidden" name="EQUERY_OBJ" value="'.$this->session_vars['EQUERY_OBJ'].'"
		  <input type="reset" value="' . $cancel . '" name="annulla" />';
				$body .="<div style=\"text-align:center;\" >".$question.$invia.$annulla."</div>";


				$body.="</form>";
				$this->onload .= $xml_form->onload . ";";

			}
			return $body;
		}

	}

	function configura(){
		//1 - a livello di scheda
		//2 - a livello di campo
		$this->config['consistency']=2;
		//nome attore che pu modificare i dati per questa tipologia di equery
		$this->config['user_modifier']="DE";
		//nome attore che pu modificare i dati per questa tipologia di equery
		$this->config['user_creator']="DE";
		$this->config['user_approver']="DM";
		//nome attore con permesso di cancellazione di un'equery pendente
		$this->config['user_remover']="";
		//1 - blocca nuove equery
		//2 - integra nuove equery
		//3 - nuove equery parallele alle precedenti
		$this->config['collision_configuration']="1";
		//approvazione automatica della equery
		$this->config['auto_approve']=false;
		$this->config['table_equery']=$this->service."_EQUERY";
		$this->config['table_data']=$this->service."_EQUERY_MODFIELD";


	}
	function approval($approve_flag){}
	function view(){}
	function control_views(){}
	function controller(){}
	function testo($testo){
		if(!isset($this->testi[$testo])){
			if(strtolower($this->config_service['lang'])=='en'){
				$this->testi['nome_equery']='eQuery';
				$this->testi['nuovo']="Create a new ".$this->testo('nome_equery')." on this form";
			}
			else{
				$this->testi['nome_equery']='eQuery';
				$this->testi['nuovo']="Crea una nuova ".$this->testo('nome_equery')." per questa form";

			}
		}
		return $this->testi[$testo];
	}
	function href($href){
		if(!isset($this->href[$href])){
			$this->href['visualizza_form']="index.php?CENTER={$this->session_vars['CENTER']}&CODPAT={$this->session_vars['CODPAT']}&VISITNUM={$this->session_vars['VISITNUM']}&ESAM={$this->session_vars['ESAM']}&PROGR={$this->session_vars['PROGR']}&form={$this->session_vars['form']}";

		}
		return $this->href[$href];
	}
	function link($link){
		switch ($link){
			case 'nuovo':
				if($this->check_creation_grants()){
					$res_link="<a href=\"{$_SERVER['REQUEST_URI']}&EQUERY_OBJ={$this->identifier}\" >".$this->testo($link)."</a>";
				}
				else {
					$res_link="";
				}
				break;
			default:
				$res_link="";
				break;

		}
		return $res_link;
	}
	function check_creation_grants(){
		return true;
	}

	function check_data_mod_grants(){
		return true;
	}
	function check_approvation_grants(){
		return $this->session_vars['USER_TIP']==$this->config['user_approver'];
	}
	function lista(){}
	function reason_field(){
		if($this->config['user_creator']==$this->config['user_modifier'])
		$question="<div><span style=\"vertical-align:top\" ><b>Specifica il motivo dell'equery:</b></span> <textarea name=\"EQUERY_QUESTION\" cols=\"80\" ROWS=\"10\"></textarea></div>";
		return $question;
	}
}

?>