<?
/**
 * Linker
 * @package Reporting
 * 
 */
if(!defined('TABLE_UTENTI_GRUPPIU'))define('TABLE_UTENTI_GRUPPIU','UTENTI_GRUPPIU');
if(!defined('TABLE_ANA_GRUPPIU'))define('TABLE_ANA_GRUPPIU','ANA_GRUPPIU');
if(!defined('TABLE_GRUPPIU'))define('TABLE_GRUPPIU','GRUPPIU');

/**
 * Label
 *
 * Classe statica con le traduzioni
 * @package Reporting
 *
 */
class Label {
	static function testo($label,$lang) {
		switch(strtolower($lang)) {
			case 'it':
			default:
			$testi["Crea un nuovo report"]="Crea un nuovo report";
			$testi["Lista dei link"]="Lista dei link";
			$testi["Default"]="Default";
			$testi["Aggiornamento dati"]="Aggiornamento dati";
			$testi["Messaggio Utente"]="Messaggio Utente";
			$testi["Preview"]="Preview";
			$testi["Esci dalla preview"]="Esci dalla preview";
			$testi["Testo del link"]="Testo del link";
			$testi["HREF"]="HREF";
			$testi["Target"]="Target";
			$testi["Sezione"]="Sezione";
			$testi["Tipologia"]="Tipologia";
			$testi["Abilitazione"]="Abilitazione";
			$testi["Abilitato"]="Abilitato";
			$testi["Disabilitato"]="Disabilitato";
			$testi["Invia"]="Invia";
			$testi["Gruppo Abilitato"]="Gruppo Abilitato";
			$testi["Gruppo Prec. Abilitato"]="Il gruppo era già precedentemente abilitato";
			$testi["Gruppo Disabilitato"]="Gruppo Disabilitato";
			$testi["Gruppo Prec. Disabilitato"]="Il gruppo era già precedentemente disabilitato";
			$testi["Default per gruppo"]="Default per gruppo";
			$testi["LK_DEFAULT_PAGE_LABEL"]="In quest'area è possbile configurare l'url della pagina iniziale del servizio per il gruppo selezionato.";
			$testi["LK_ENV_INFO_LABEL"]="In quest'area è possbile configurare un messaggio che utilizzi variabili d'ambiente a disposizione dell'applicativo (es. per visualizzare il nome e cognome usare [NOME] [COGNOME],...).";
			$testi["UPDATE_STR_FORM_LABEL"]="In quest'area è possbile configurare la query sql per definire a che data sono aggiornati i dati.<br>
				N.B.<br>Se più campi sono presenti nella query tali campi verranno concatenati.<br>
				Se si vuole far apparire un testo (es.: 'Dati aggiornati al..') bisogna inserirlo nella query";
			$testi["utenti"]="Utenti";
			$testi["Administration group"]="Administration group";
			$testi["Elimina"]="elimina";
			$testi["Ordina"]="ordina";
			break;

			case 'en':
			$testi["Crea un nuovo report"]="New report";
			$testi["Lista dei link"]="Report links";
			$testi["Default"]="Default";
			$testi["Aggiornamento dati"]="Data update";
			$testi["Messaggio Utente"]="User message";
			$testi["Preview"]="Preview";
			$testi["Esci dalla preview"]="Exit from preview";
			$testi["Testo del link"]="Link text";
			$testi["HREF"]="HREF";
			$testi["Target"]="Target";
			$testi["Sezione"]="Section";
			$testi["Tipologia"]="Type";
			$testi["Abilitazione"]="Enabling";
			$testi["Abilitato"]="Enable";
			$testi["Disabilitato"]="Disable";
			$testi["Invia"]="Send";
			$testi["Gruppo Abilitato"]="Group enabled";
			$testi["Gruppo Prec. Abilitato"]="This group was already enabled";
			$testi["Gruppo Disabilitato"]="Group disabled";
			$testi["Gruppo Prec. Disabilitato"]="This group was already disabled";
			$testi["Default per gruppo"]="Default for group";
			$testi["LK_DEFAULT_PAGE_LABEL"]="In this area it's possible to configure the url of the start page of the service for the group selected.";
			$testi["LK_ENV_INFO_LABEL"]="In this area it's possible to configure a message that with the envorimental variables<br/>provided by the application (for example to show the first and last name use [FIRST NAME] [LAST NAME],...).";
			$testi["UPDATE_STR_FORM_LABEL"]="In this area it's possible to configure the sql query that defines at which date and time the data are updated.<br>
				Please note that:<br>If there are more fields, these fields will be concatenated.<br>
				If it's necessary to show a label (for example 'Data updated at..') it must be inserted in to the query";
			$testi["utenti"]="Users";
			$testi["Administration group"]="Administration group";
			$testi["Elimina"]="delete";
			$testi["Ordina"]="sort";

			break;
		}
		return $testi[$label];
	}
}
 

/**
 * Link
 * 
 * Classe per gestire i singoli link
 *@package Reporting
 */
class Link {
	/**
	 * Identificativo del link
	 * 
	 * @var string
	 */
	var $id;
	/**
	 * Dati relativi al link
	 *
	 * @var array
	 */
	var $data;
	/**
	 * Dati relativi al link dopo l'escape html
	 *
	 * @var array
	 */
	var $escapedData;
	/**
	 * Connessione alla banca dati
	 *
	 * @var dbconn
	 */
	var $conn;
	/**
	 * Lingua
	 *
	 * @var lang
	 */
	var $lang;
    /**
     * Configurazioni di servizio
     *
     * @var config_service
     */
    var $config_service;

	private $envInfo;
    
    
	/**
	 * Costrutture
	 *
	 * @param dbconn $conn
	 * @param string $id
	 * @param array $data
	 * @return Link
	 */
	function __construct($conn=null,$id=null,$data=null,$lang=null,$config_service=null){
		$this->conn=$conn;
        $this->config_service=$config_service;
		if(is_numeric($id))$this->id=$id;
		if(is_array($data))$this->data=$data;
		if($lang!='') $this->lang=$lang;
		if($this->id!='' && !$this->data){
			$str="select * from ".LK_TABLE_LINKS." where id=:id and GROUP_LINK=".LK_GROUP_LINK;
			$bind['ID']=$this->id;
			$query=new query($conn);
			$query->exec($str,$bind);//binded
			$query->get_row();
			$this->data=$query->row;
			$bind['ID']=$this->id;
			$bind['GROUP_LINK']=LK_GROUP_LINK;
			$str_gruppi="select ID_GRUPPOU from ".LK_TABLE_LINK_GRUPPIU." where id_link=:id and group_link=:group_link";
			$query=new query($conn);
			$query->exec($str_gruppi,$bind);//binded
			while ($query->get_row()) {
				$this->data['GRUPPIU'][$query->row['ID_GRUPPOU']]=1;
			}
		}
		if(is_array($this->data)){
			foreach ($this->data as $key => $value){
				$this->escapedData[$key]=htmlentities($value,ENT_QUOTES);
			}
		}
	}
	/**
	 * Load
	 * 
	 * Carica i dati dalla bancadati a partire dall'id
	 *
	 */
	function load(){}
	/**
	 * Form
	 * 
	 * Crea la Form di inserimento/modifica del link
	 *
	 * @return string
	 */
	function form(){
		$str_idref="select * from ".LK_TABLE_LINKS." where tipologia=1 and GROUP_LINK=".LK_GROUP_LINK." order by order_col";
		$query=new query($this->conn);
		$query->exec($str_idref);//non richiede binding
		$options_ref="<option></option>";
		while($query->get_row()){
			if($this->data['ID_REF']==$query->row['ID'])$selected="selected='selected'";
			$options_ref.="<option value='{$query->row['ID']}' $selected >{$query->row['TESTO']}</value>";
			$selected="";
		}
		if($this->data['TIPOLOGIA']=='2') $selected_link="selected='selected'";
		else $selected_header="selected='selected'";
		if($this->data['ABILITATO']=='2') $selected_disabilitato="selected='selected'";
		else $selected_abilitato="selected='selected'";

		$select_refs="<select name='ID_REF'>$options_ref</select> ";

		$gruppi=ianus::getGroups($this->conn); 
		//Logger::send($gruppi); 
		foreach ($gruppi as $id => $testo){ if($this->data['GRUPPIU'][$id]){ $status="on"; 
		$value=1; } else{ $status='off'; $value=0; } $listaGruppi.=" 
		<tr><td>".$testo.":</td><td> <div 
		class=\"container\">

				 <span class=\"left\" id=\"gruppo{$id}\"></span>
			 				 <span 
		class=\"ajax\"></span> <span class=\"clear\"></span> <input type='hidden' 
		name='GRUPPIU[{$id}]' id='SWITCH_{$id}' value='{$value}' > <script 
		type=\"text/javascript\">

				    $('#gruppo{$id}').iphoneSwitch(\"$status\", 
				   				     function() 
		{ document.getElementById('SWITCH_{$id}').value=1; }, function() { 
		document.getElementById('SWITCH_{$id}').value=0; }, { 
		switch_on_container_path: 'libs/std_images/iphone_switch_container_off.png' 
		}); </script> </div></td></tr>";
}

		$html_form="<form name='link_form'>
		<input type='hidden' name='rep_link' value='true' >
		<input type='hidden' name='REQUEST' value='SAVE_LINK' >
		<input type='hidden' name='ID' value='{$this->data['ID']}' >
		<table cellpadding=0 cellspacing=0 border=0 >
		<!- $this->lang -->
		<tr><td>".Label::testo('Testo del link',$this->lang).": </td><td><input type='text' name='TESTO' id='TESTO' value='{$this->escapedData['TESTO']}' ></td></tr>
		<tr><td>".Label::testo('HREF',$this->lang).": </td><td><input type='text' name='HREF' id='HREF' value='{$this->data['HREF']}' ></td></tr>
		<tr><td>".Label::testo('Target',$this->lang).": </td><td><input type='text' name='TARGET' id='TARGET' value='{$this->data['TARGET']}' ></td></tr>
		<tr><td>".Label::testo('Sezione',$this->lang).": </td><td>$select_refs</td></tr>
		<tr><td>".Label::testo('Tipologia',$this->lang).": </td><td><select name='TIPOLOGIA' id='TIPOLOGIA' ><option value='1' $selected_header >Header</option><option value='2' $selected_link >Link</option></select></td></tr>
		<!--tr><td>".Label::testo('Abilitazione',$this->lang).": </td><td><select name='ABILITATO' id='ABILITATO' ><option value='1' $selected_abilitato >".Label::testo('Abilitato',$this->lang)."</option><option value='2' $selected_disabilitato >".Label::testo('Disabilitato',$this->lang)."</option></select></td></tr-->
		$listaGruppi
		<tr><td><input type='submit' name='INVIA_LINK' id='INVIA_LINK' value='".Label::testo('Invia',$this->lang)."' ></td></tr>
		</table>
		<form>
		
		";


		$html=$html_form;
		return $html;
	}
	/**
	 * save
	 * 
	 * salva il link in bancadati
	 *
	 * @param array $data
	 * @param dbconn $conn
	 */
	static function save($data,$conn){
		if(isset($data['ID'])){
			$bind['ID']=$data['ID'];
			$bind['GROUP_LINK']=LK_GROUP_LINK;
			$str_check="select count(*) conto from ".LK_TABLE_LINKS." where id=:id and group_link=:group_link";
			$sql=new query($conn);
			$sql->exec($str_check,$bind);//non richiede binding
			$sql->get_row();
			if($sql->row['CONTO']>0) {
				$new=false;
			}
			else {
				$new=true;
			}
		}else {
			$new=true;
		}
		if(isset($data['TARGET'])){
		    $str="select count(*) conto from user_tab_columns where table_name='".LK_TABLE_LINKS."' and column_name='TARGET'";
            $query=new query($conn);
            $query->get_row($str);//non richiede binding
            
		    if($query->row['CONTO']=='0'){
    		    $str="alter table ".LK_TABLE_LINKS." add target varchar2(1000)";
                $query=new query($conn);
                $query->set_sql($str);
                $query->ins_upd();//non richiede binding
            }
            $values['TARGET']=$data['TARGET'];
		}

		$values['ID_REF']=$data['ID_REF'];
		$values['GROUP_LINK']=LK_GROUP_LINK;
		$values['TIPOLOGIA']=$data['TIPOLOGIA'];
		$values['TESTO']=$data['TESTO'];
		$values['HREF']=$data['HREF'];
		$values['ABILITATO']=$data['ABILITATO'];
		if($new){
			$values['ID']=LK_SEQUENCE.".nextval";
			$sql->insert($values,LK_TABLE_LINKS,$pk);
			$get_id="select ".LK_SEQUENCE.".currval ID from dual";
			$sql->get_row($get_id);
			$data['ID']=$sql->row['ID'];
		}
		else {
			$pk['ID']=$data['ID'];
			$sql->update($values,LK_TABLE_LINKS,$pk);
		}
		foreach ($data['GRUPPIU'] as $id_gruppo => $abilitato ){
			if($abilitato) Link::abilitaGruppo($data['ID'],$id_gruppo,$conn);
			else Link::disabilitaGruppo($data['ID'],$id_gruppo,$conn);
		}
		$conn->commit();
	}
	/**
	 * delete
	 * 
	 * cancella il link in bancadati
	 *
	 * 
	 * @param number $id
	 * @param dbconn $conn
	 * @param object $user
	 */
	function delete($id,$conn,$user){
		if($user->isAmmin()){
			$bind['ID_LINK']=$id;
			$bind['GROUP_LINK']=LK_GROUP_LINK;
			$str="delete from ".LK_TABLE_LINK_GRUPPIU." where ID_LINK=:id_link and group_link=:group_link" ;
			$sql=new query($conn);
			$sql->set_sql($str);
			$sql->ins_upd($str,$bind);//binded

			$str="delete from ".LK_TABLE_LINKS." where ID=:id_link and group_link=:group_link" ;
			$sql=new query($conn);
			$sql->set_sql($str);
			$sql->ins_upd($str,$bind);//binded

			$str="update  ".LK_TABLE_LINKS." set ID_REF='' where id_ref=:id_link and group_link=:group_link" ;
			$sql=new query($conn);
			$sql->set_sql($str);
			$sql->ins_upd($str,$bind);//binded

			$conn->commit();
		}
	}

	static function ordinaLink($ordine,$conn){

		$lista=explode('|',$ordine);
		foreach ($lista as $key => $id){
			$order=$key+1;
			$bind['ID_'.$order]=$id;
			$bind['DECODE_'.$order]=$order;
			$decode.=":id_{$order},:decode_{$order},";
			$ids_list.=":id_{$order},";
		}
		$ids_list=rtrim($ids_list,',');
		$decode=rtrim($decode,',');
		$decode="decode(id,{$decode})";
		$str="update ".LK_TABLE_LINKS." set order_col=$decode where id in ($ids_list)";
		//echo $str;
		$query=new query($conn);
		$query->ins_upd($str,$bind);//binded
		$conn->commit();

	}

	/**
	 * getHtml
	 * 
	 * Restituisce l'html del link per il menu
	 *
	 * @return string
	 */
	function getHtml(){
		if($this->config_service['analyzerPatchEnabled'] && $this->data['ID']){
		    if($this->data['HREF']!=''){
                $href= preg_replace_callback ( "/\[(.*?)\]/", function($matches){return var_glob($matches[0]);}, $this->data['HREF'] );
            }
            if($this->data['TARGET']!='') $target=$this->data['TARGET'];
            else $target="main";
            if ($target=='main'){
               $href="index.php?rep_link=true&SELECTED={$this->data['ID']}";
               $target='_top';
            }
            if($this->data['TIPOLOGIA']==="1") {
                //Logger::send("qui");
                //Logger::send($this->data);
                $href="#";
                $fake_link="onclick='return false;'";
            }
            return "<div class=\"menu_item\" id=\"item_{$this->data['ID']}\" ><a href=\"{$href}\" target=\"$target\" $fake_link  >".$this->data['TESTO']."</a></div>";
		}
        else{
    		if($this->data['HREF']!=''){
    			$href= preg_replace_callback ( "/\[(.*?)\]/", function($matches){return var_glob($matches[0]);}, $this->data['HREF'] );
    		}
    		if($this->data['TARGET']!='') $target=$this->data['TARGET'];
    		else $target="main";
    		if($this->data['TIPOLOGIA']==="1") {
    		    //Logger::send("qui");
    		    //Logger::send($this->data);
    		    $href="#";
    			$fake_link="onclick='return false;'";
				$add="<span class=\"arrow\"><i class=\"icon-angle-down\"></i></span>";
    		}
    		return "<div class=\"menu_item\" ><a href=\"{$href}\" target=\"$target\" $fake_link  >".$this->data['TESTO'].$add."</a></div>";
		}
	}
	/**
	 * getListHtml
	 * 
	 * Restituisce l'html del link al dettaglio/form di modifica dell'oggetto 
	 *
	 * @return string
	 */
	function getListHtml(){
		if($this->data['ID_REF']==''){
			$preview=1;
			$class_item="class_item_1";
			$reverse_class="class_item_2";
		}
		else {
			$preview=2;
			$class_item="class_item_2";
			$reverse_class="class_item_1";
		}

		$actions="<span class='item_actions'  ><a href=\"{$_SERVER['PHP_SELF']}?rep_link=true&REQUEST=LINK_FORM&ID={$this->data['ID']}\" target=\"main\" >edit</a></span><span class='item_actions'><a href=\"{$_SERVER['PHP_SELF']}?rep_link=true&REQUEST=LINK_DELETE&ID={$this->data['ID']}\" target=\"main\" >".Label::testo('Elimina',$this->lang)."</a> &nbsp;<a href='#' onclick='ordina(\"#item_{$this->data['ID']}\",$preview);return false;' >".Label::testo('Ordina',$this->lang)."</a></span><span class='item_order_text_box' style='display:none'><b>Posizione:</b><span class='item_order_text'  ></span></span><span class='item_order_input' style='display:none' ><b>Posizione:</b> <input type='text' name='order_{$this->data['ID']}' id='order_{$this->data['ID']}'  size=3 />  <a href='#' onclick='confirm_order(\"#item_{$this->data['ID']}\");return false;' >conferma</a></span><span class='item_input_id' ><input type='hidden' name='item_id_{$this->data['ID']}' value='{$this->data['ID']}' ></span>";
		if(strlen($this->data['HREF'])>80)$href="...".substr($this->data['HREF'],strlen($this->data['HREF'])-81);
		else $href=$this->data['HREF'];
		return "<div class=\"list_item $class_item\" id='item_{$this->data['ID']}' ><div class=\"item_preview{$preview}\" ><a href=\"{$_SERVER['PHP_SELF']}?rep_link=true&REQUEST=LINK_FORM&ID={$this->data['ID']}\" target=\"main\" >".$this->data['TESTO']."</a></div><div class=\"item_href\" >".$href."</div>$actions</div>";
	}
	/**
	 * abilitazione
	 * 
	 * Abilita/disabilita il Link
	 *
	 * 
	 */
	function abilitazione($abilitazione){}
	/**
	 * abilitaGruppo
	 * 
	 * abilitazione di un gruppo
	 * 
	 */
	static function abilitaGruppo($id,$gruppo,$conn){
		$values['ID_LINK']=$id;
		$values['ID_GRUPPOU']=$gruppo;
		$values['GROUP_LINK']=LK_GROUP_LINK;
		$str="select count(*) conto from ".LK_TABLE_LINK_GRUPPIU." where id_link=:id_link and id_gruppou=:id_gruppou and group_link=:group_link";
		$query= new query($conn);
		$query->exec($str,$values);//binded
		$query->get_row();
		if($query->row['CONTO']==0){
			$query->insert($values,LK_TABLE_LINK_GRUPPIU);
			$conn->commit();
			return Label::testo("Gruppo Abilitato");
		}
		else
		return Label::testo("Gruppo Prec. Abilitato");
	}
	/**
	 * disabilitaGruppo
	 * 
	 * disabilitazione di un gruppo
	 *
	 */
	static function disabilitaGruppo($id,$gruppo,$conn){
		$bind['ID_LINK']=$id;
		$bind['ID_GRUPPOU']=$gruppo;
		$bind['GROUP_LINK']=LK_GROUP_LINK;
		$str="select count(*) conto from ".LK_TABLE_LINK_GRUPPIU." where id_link=:id_link and id_gruppou=:id_gruppou";
		$query= new query($conn);
		$query->exec($str,$bind);//binded
		$query->get_row();
		if($query->row['CONTO']>0){
			$delete_str="delete from ".LK_TABLE_LINK_GRUPPIU." where id_link=:id_link and id_gruppou=:id_gruppou and group_link=:group_link";
			$query->set_sql($delete_str);
			$query->ins_upd($delete_str,$bind);//binded
			$conn->commit();
			return Label::testo("Gruppo Disabilitato");
		}
		else
		return Label::testo("Gruppo Prec. Disbilitato");
	}

}

/**
 * Link Module
 * 
 * Classe di gestione di link vari
 *@package Reporting
 */
class LinkModule{
	private $conn;
	private $session_vars;
	private $xmr;
	private $result;
	private $template;
	private $config_service;
	private $dir;
	private $user;
	private $table_link;
	private $table_link_params;
	private $table_ammin;
	private $table_seq;
	private $update_str;
	function __construct($conn,$xmr){
		$this->conn=$conn;
		$this->xmr=$xmr;
		if(is_array($this->xmr->config_service))$this->config_service=$this->xmr->config_service;
		else{
			global $config_service;
			$this->config_service=$config_service;
		}
        //deccomentare per abilitare patch
        //$this->config_service['analyzerPatchEnabled']=true;
		if(!defined('LK_GROUP_LINK'))define('LK_GROUP_LINK',0);
		if(!defined('LK_SERVICE'))define('LK_SERVICE',$this->config_service['service']);
		if(!defined('LK_TABLE_LINK_GRUPPIU'))define('LK_TABLE_LINK_GRUPPIU',LK_SERVICE.'_LINK_GRUPPIU');
		if(!defined('LK_TABLE_THEME'))define('LK_TABLE_THEME',LK_SERVICE.'_REP_LINKS_THEME');
		if(!defined('LK_TABLE_LINKS'))define('LK_TABLE_LINKS',LK_SERVICE.'_REP_LINKS');
		if(!defined('LK_TABLE_DEFAULT_PAGES'))define('LK_TABLE_DEFAULT_PAGES',LK_SERVICE.'_REP_DEFAULT_PAGES');
		//if(!defined('LK_TABLE_LINKS_PARAMS'))define('LK_TABLE_LINKS_PARAMS',LK_SERVICE.'_REP_LINKS_PARAMS');
		if(!defined('LK_TABLE_AMMINISTRATORI'))define('LK_TABLE_AMMINISTRATORI',LK_SERVICE.'_REP_AMMIN');
		if(!defined('LK_ANA_GRUPPIU'))define('LK_ANA_GRUPPIU','ANA_GRUPPIU');
		if(!defined('LK_SEQUENCE'))define('LK_SEQUENCE',LK_TABLE_LINKS.'_SEQ');
		if(!$this->isInitialized()){
			$this->initialize();
		}
		if(!$this->isUpdated()){
			$this->update();
		}
		$select_theme="select * from ".LK_TABLE_THEME." where group_link=".LK_GROUP_LINK;
		$query_theme=new query($this->conn);
		$query_theme->exec($select_theme);//non richiede binding
		while ($query_theme->get_row()){
			if(!defined($query_theme->row['CONSTANT'])) define($query_theme->row['CONSTANT'],$query_theme->row['VALUE']);
		}
		if(!defined('LK_UPDATE_STR'))define('LK_UPDATE_STR','rep_update_str.sql');
		$this->update_str=file_get_contents(LK_UPDATE_STR);
		if(!defined('LK_CSS'))define('LK_CSS','libs/css/linker.css');
		if(!defined('LK_TEMPLATE'))define('LK_TEMPLATE','template.htm');
		if(!defined('LK_HEIGHT'))define('LK_HEIGHT','120px');
        if(!defined('LK_WIDTH'))define('LK_WIDTH','230px,82%');

	}
	function controller($session_vars){
		$this->session_vars=$session_vars;
		$this->result="";
		$this->user=$this->getUser();
		foreach($this->user->utenteIanus->getGroups() as $user_group) {
			if(defined("LK_DEFAULT_PAGE_".$user_group) && constant("LK_DEFAULT_PAGE_".$user_group)!='') {
				$defaultPage=constant("LK_DEFAULT_PAGE_".$user_group);
				break;
			}
		}
		if ($defaultPage=='') {
			if(defined("LK_DEFAULT_PAGE")) {
				$defaultPage=LK_DEFAULT_PAGE;
			} else {
				$defaultPage='';
			}
		}
		if(preg_match("/msie/i",$_SERVER['HTTP_USER_AGENT']) ){
			$msie_css="<link media='screen' href='libs/css/msie.css' rel='stylesheet' type='text/css' />";
		}
    else
      $msie_css="";
        if($this->session_vars['SELECTED']!='' && $this->user->isAmmin() && $this->session_vars['REQUEST']=='MENU') {
            $this->session_vars['REQUEST']='PREVIEW';
        }
		switch($this->session_vars['REQUEST']){
			case 'LINK_FORM':
				$link=new Link($this->conn,$session_vars['ID'],null,$this->config_service['lang'],$this->config_service);
				$form=$link->form();
				$this->result=$form;
				break;
			case 'LINK_DELETE':
                if($this->user->isAmmin()){
				    Link::delete($_GET['ID'],$this->conn,$this->user);
                }
				ob_clean();
				header("Location: {$_SERVER['PHP_SELF']}?rep_link=true&REQUEST=LINK_LIST");
				die();
				break;
			case 'LINK_LIST':
				$this->result=$this->user->getLinksList();
				break;
			case 'SAVE_LINK':
				$this->result=$this->user->message("Salvataggio effettuato correttamente");
                if($this->user->isAmmin()){
				    Link::save($session_vars,$this->conn);
                }
				break;
			case 'DEFAULT_FORM':
				$this->result=$this->formDefault($this->session_vars['group_id']);
				break;
			case 'SAVE_DEFAULT':
				$this->result=$this->user->message("Salvataggio effettuato correttamente");
				if($this->user->isAmmin()){
				    $this->saveDefault();
                }
				break;
			case 'INFO_FORM':
				$this->result=$this->formEnvInfo();
				break;
			case 'SAVE_INFO':
				$this->result=$this->user->message("Salvataggio effettuato correttamente");
                if($this->user->isAmmin()){
				    $this->saveEnvInfo();
                }
				break;
			case 'MENU':   
                if($this->session_vars['SELECTED']!=''){
                    $js_show="$('#item_{$this->session_vars['SELECTED']}').closest('.menu_body').show();";
                }    
                if($this->user->isAmmin()){
                    $this->config_service['analyzerPatchEnabled']=false;
                }    
				$this->result=$this->updateInfo();
				$this->result.=$this->envInfo();
				$this->result.=$this->user->home();
				break;
			case 'PREVIEW':
                if($this->session_vars['SELECTED']!=''){
                    $js_show="$('#item_{$this->session_vars['SELECTED']}').closest('.menu_body').show();";
                } 
				$this->result=$this->updateInfo();
				$this->result.=$this->envInfo();
				$this->result.=$this->user->preview();

				break;
			case 'UPDATE_SETUP':
                if($this->user->isAmmin()){
				    $this->result=$this->updateStrForm();
                }

				break;
			case 'UPDATE_SAVE':
                if($this->user->isAmmin()){
				    $this->result=$this->updateStrSave();
                }
				break;
			case 'ABILITA_GRUPPO':
                if($this->user->isAmmin()){
				    $this->result=Link::abilitaGruppo($this->session_vars['ID'],$this->session_vars['ID_GRUPPOU'],$this->conn);
                }
				$no_template=true;
				break;
			case 'DISABILITA_GRUPPO':
                if($this->user->isAmmin()){
				    $this->result=Link::disabilitaGruppo($this->session_vars['ID'],$this->session_vars['ID_GRUPPOU'],$this->conn);
                }
				$no_template=true;
				break;
			case 'SORT_LINK':
                if($this->user->isAmmin()){
				    Link::ordinaLink($this->session_vars['ORDER'],$this->conn);
                }
				echo '{"success":true}';
				die();
				break;
			default:
                if($this->session_vars['SELECTED']!='') {
                    $this->user->loadLinks();
                    
                    if($this->user->links[$this->session_vars['SELECTED']]){
                        $link=$this->user->links[$this->session_vars['SELECTED']];     
                    }
                    else {
                        foreach($this->user->grouppedLinks as $group_id => $group_array){
                            foreach ($group_array as $link_id => $link_obj) {
                                if($link_id==$this->session_vars['SELECTED']){
                                    $link=$link_obj; 
                                    
                                    break 2;
                                }
                            }
                        }
                    }              
                    $defaultPage=$link->data['HREF'];
                    $selected="&SELECTED={$this->session_vars['SELECTED']}#item_{$this->session_vars['SELECTED']}";
                    //if($this->session_vars['PREVIEW']!='')$selected="&SELECTED={$this->session_vars['SELECTED']}&PREVIEW=true";
                    
                   
                }
				
				$filetxt = file_get_contents('template_rep.htm');
				echo $defaultPage;
				$body="<iframe src=\"$defaultPage\" name=\"main\" id=\"mannaggia\" frameborder=\"0\"  style=\"width: 100%; height: 100%;\"></iframe>";
				$links="<iframe src=\"{$_SERVER['PHP_SELF']}?rep_link=true&REQUEST=MENU{$selected}\" name=\"links\"  id=\"links\" frameborder=\"0\"  style=\"width: 100%; height: 1100px;\"></iframe>";
				$filetxt=preg_replace("/<!--body-->/", $body, $filetxt);
				$filetxt=preg_replace("/<!--links-->/", $links, $filetxt);
				$this->result=$filetxt;
				
				/* $this->result="
					<html>
					<head>
							
						<title>Reportistica</title>
					</head>
					<script>
						setInterval(function(){
							if(top && top.frames && top.frames['mannaggia'] && top.frames['mannaggia'].frames && top.frames['mannaggia'] && top.frames['mannaggia'].location){
								var url=top.frames['mannaggia'].location.href;
								var decoded=decodeURIComponent(url);
								if(url!=decoded){
									top.frames['mannaggia'].location.href=decoded;
								}
						 	}
						},50);
					function addListeners(){
						window.frames[0].onclick=bannerClick;
						}
					
					function bannerClick(e){
						var eventIsFiredFromElement;
						if(e==null)
						{
						// I.E.
						eventIsFiredFromElement = event.srcElement;
						}
						else
						{
						// Firefox
						eventIsFiredFromElement = e.target;
						}
						while (eventIsFiredFromElement.nodeName!='A' && eventIsFiredFromElement.nodeName!='HTML' ){
							eventIsFiredFromElement=eventIsFiredFromElement.parentNode;
						}
						if (eventIsFiredFromElement.nodeName=='HTML') return true;
						window.parent.location.href=eventIsFiredFromElement.href;
						return false;
					}
						

					
					function addEvent(obj, evType, fn){ 
					 if (obj.addEventListener){ 
					   obj.addEventListener(evType, fn, false); 
					   return true; 
					 } else if (obj.attachEvent){ 
					   var r = obj.attachEvent(\"on\"+evType, fn); 
					   return r; 
					 } else { 
					   return false; 
					 } 
					}
			
					addEvent(window, 'load', addListeners);
			
					</script>
						<frameset rows=\"".LK_HEIGHT.",100%\" frameborder=\"0\" >

							<frame src=\"".LK_TEMPLATE."\" name=\"banner\" style='overflow:hidden' >
						<frameset cols=\"".LK_WIDTH."\" frameborder=\"0\">
				   			<frame src=\"{$_SERVER['PHP_SELF']}?rep_link=true&REQUEST=MENU{$selected}\">
				   			<frame src=\"$defaultPage\" name=\"main\" id=\"mannaggia\" >
						</frameset>
						</frameset>
					
					</html>" ; */
				$no_template=true;
				break;
		}

		if(!$no_template)$this->result="<html><head><meta http-equiv='Content-Type' content='text/html; charset=UTF-8' /><link media='screen' href='".LK_CSS."' rel='stylesheet' type='text/css' />
				<script type=\"text/javascript\" src=\"libs/js/jquery/jquery.min.js\" ></script>
				<script type=\"text/javascript\" src=\"libs/js/jquery/jquery.iphone-switch.js\" ></script>
				<script>$(document).ready(function (){
				//$('.menu_body').hide();
				$('#menu4 .menu_header').each( function (){
						$(this).click(function (){
							$(this).next('div.menu_body').slideToggle('fast');
				
					});
				});
				$('#menu4 .menu_subheader').each( function (){
				        $(this).next('div.menu_body').hide();
                        $(this).click(function (){
                            $(this).next('div.menu_body').slideToggle('fast');
                
                    });
                });
				//segue hack per permettere la dashboard dell'analyzer di pentaho
				/* $('a[target=main]').click(function(e){
				   
				    if(!e) e=window.event;
				    if(e.preventDefault) e.preventDefault();
				    if(e.returnValue)e.returnValue = false;
				    if($(this).attr('href')==''|| $(this).attr('href')=='#') return;
                    
				    top.frames[2].location=$(this).attr('href');
                    return;
				    $(this).attr('target',top.frames[2].name);
					if((!top.frames['main'] || navigator.userAgent.match(/MSIE/) || navigator.userAgent.match(/Firefox/)) && top.frames[2].name!='main'){
					    $(this).attr('target',top.frames[2].name);
					 }
				}); */
                //se seleziono un linkmostro il menu esploso
				{$js_show}
				
				});
				
				function ordina(element,type){
					var different,element_class,reverse_class;
					if(type==1){
						different=2;
						element_class='.class_item_1';
						reverse_class='.class_item_2';
						curr_element=$(element);
						ordering_elements=$(element_class);
					}
					else{
						different=1;
						element_class='.class_item_2';
						reverse_class='.class_item_1';
						curr_element=$(element);
						ordering_elements=$(element).prevAll(reverse_class).first().nextUntil(reverse_class);
					}
					$(ordering_elements).each(function (index){
						var order=index+1;
						$(this).find('.item_order_text').html(order);
						$(this).find('.item_order_input input').val(order);
					});
					$(reverse_class).hide();
					$(element_class+' .item_actions').hide();
					$(element_class+' .item_actions').hide();
					$(element_class+' .item_href').hide();
					$(ordering_elements).not(curr_element).children('.item_order_text_box').show();
					$(curr_element).children('.item_order_input').show();
					
				}
				
				function confirm_order(element){
					var definitive_order=$(element).find('.item_order_input input').val();
					var string_order='';
					var curr_id=$(curr_element).find('.item_input_id input').val();
					
					if(definitive_order<1)definitive_order=1;
					
					$(ordering_elements).not(curr_element).each(function (index){
						if(index+1==definitive_order)string_order+=curr_id+'|';
						string_order+=$(this).find('.item_input_id input').val()+'|';
						
					});
					if(definitive_order>=$(ordering_elements).length)string_order+=curr_id+'|';	
					string_order=string_order.substring(0,string_order.length-1);
					var handler=function (data){
						if(data.success){
							location.reload();
						}
					};
					$.post('{$_SERVER['PHP_SELF']}','rep_link=true&REQUEST=SORT_LINK&ORDER='+string_order,handler,'json');
				}
				
				
				
				</script><style>
				.container {
				display:table-row;
				}
				.container span{
				display:table-cell;
				}
				</style>
				$msie_css
				<link rel=\"stylesheet\" href=\"assets/css/font-awesome.min.css\" />
				</head><body>
{$this->result}</body></html>";
		ob_clean();
		echo $this->result;
		die();
	}
	function getResult(){
		return $this->result;
	}
	function getHome(){
		$this->user=$this->getUser();
		return $this->user->home();
	}
	function formDefault($group_id){
		if ($group_id == "") $group_id = "-1";
		if(defined('LK_DEFAULT_PAGE_'.$group_id) && $group_id != "-1") {
			$defaultPage=constant("LK_DEFAULT_PAGE_".$group_id);
		} elseif ($group_id == "-1" && defined('LK_DEFAULT_PAGE')) {
			$defaultPage=LK_DEFAULT_PAGE;
		} else {
			$defaultPage="";
		}
		//Logger::send('qui');
		$text = "
		<p>".Label::testo("LK_DEFAULT_PAGE_LABEL",$this->config_service['lang'])."<br>
		</p>
		<form>
		<input type='hidden' name='REQUEST' value='SAVE_DEFAULT' >
		<input type='hidden' name='rep_link' value='true' >
		<div>
		<script type=\"text/javascript\">
		$(\"select[id='group_id']\").live('change', function() {
			location.href='{$_SERVER['PHP_SELF']}?rep_link=true&REQUEST=DEFAULT_FORM&group_id='+$(\"select[id='group_id'] option:selected\").val();
		});
		</script>
		".Label::testo("Default per gruppo",$this->config_service['lang']).": <select id=\"group_id\" name=\"group_id\">
		<option value=\"-1\"".($group_id == "-1" ? " selected=\"selected\"" : "").">GENERALE</option>
		";
		$gruppi=ianus::getGroups($this->conn);
		foreach ($gruppi as $key => $val) {
			$text .= "<option value=\"".$key."\"".($group_id == $key ? " selected=\"selected\"" : "").">".$val."</option>
			";
		}
		$text .= "</select>
		</div>
		<div>
		<textarea name='default' cols=60 rows=10 >".$defaultPage."</textarea>
		</div>
		<input type='submit' name='update_str_save' value='Salva'>
		</form>
		";
		
		return $text;
	}

	function saveDefault(){
		if (isset($this->session_vars['group_id']) && $this->session_vars['group_id']!="-1") {
			$this->saveConstant('LK_DEFAULT_PAGE_'.$this->session_vars['group_id'],$this->session_vars['default']);
		} else {
			$this->saveConstant('LK_DEFAULT_PAGE',$this->session_vars['default']);
		}
	}
	function formEnvInfo(){
		if(defined('LK_ENV_INFO'))$envInfo=LK_ENV_INFO;
		return "
		<p>".Label::testo("LK_ENV_INFO_LABEL",$this->config_service['lang'])."<br>
		</p>
		<form>
		<input type='hidden' name='REQUEST' value='SAVE_INFO' >
		<input type='hidden' name='rep_link' value='true' >
		<div>
		<textarea name='ENV_INFO' cols=60 rows=10 >".$envInfo."</textarea>
		</div>
		<input type='submit' name='info_str_save' value='Salva'>
		</form>";
	}
	function saveEnvInfo(){
		$this->saveConstant('LK_ENV_INFO',$this->session_vars['ENV_INFO']);
	}
	function envInfo(){
		if($this->envInfo=='' && defined('LK_ENV_INFO')){
			$envInfo=LK_ENV_INFO;
			foreach ($this->session_vars as $key => $val){
				$search[]='['.$key.']';
				$replace[]=$val;
			}
			foreach ($this->user->getAnagrafica() as $key => $val){
				$search[]='['.$key.']';
				$replace[]=$val;
			}

			$envInfo=str_replace($search,$replace,$envInfo);
			$this->envInfo="<p>".$envInfo."</p>";
		}
		return $this->envInfo;
	}
	function saveConstant($constant,$value){
		$bind['CONSTANT']=$constant;
		$bind['GROUP_LINK']=LK_GROUP_LINK;
		$str="select count(*) conto from ".LK_TABLE_THEME." where constant=:constant and group_link=:group_link";
		$query=new query($this->conn);
		$query->exec($str,$bind);//binded
		$query->get_row();
		if($query->row['CONTO']==0){
			$values['CONSTANT']=$constant;
			$values['GROUP_LINK']=LK_GROUP_LINK;
			$values['VALUE']=$value;
			$query->insert($values,LK_TABLE_THEME);
		}
		elseif(preg_match("/LK_DEFAULT_PAGE/i",$constant) && $value==""){
			$str="DELETE FROM ".LK_TABLE_THEME." where constant=:constant and group_link=:group_link";
			$query=new query($this->conn);
			$query->exec($str,$bind);//binded
		}
		else {
			$values['VALUE']=$value;
			$query->update($values,LK_TABLE_THEME,$bind);
		}
		$this->conn->commit();
	}
	function updateStrForm(){
		return "
		<p>".Label::testo("UPDATE_STR_FORM_LABEL",$this->config_service['lang'])."</p>
		<form>
		<input type='hidden' name='REQUEST' value='UPDATE_SAVE' >
		<input type='hidden' name='rep_link' value='true' >
		<div>
		<textarea name='update_str' cols=60 rows=10 >".$this->update_str."</textarea>
		</div>
		<input type='submit' name='update_str_save' value='Salva'>
		</form>";
	}
	function updateInfo(){
		if($this->update_str!=''){
			$query=new query($this->conn);
			$query->exec($this->update_str);//non richiede binding
			$query->get_row();
			foreach ($query->row as $value){
				$update_str.=$value;
			}
		}
		return $update_str;
	}
	function updateStrSave(){
		$this->update_str=$this->session_vars['update_str'];
		$this->updateInfo();
		$file_config=fopen(LK_UPDATE_STR,"w");
		fwrite($file_config,$this->session_vars['update_str']);
		fclose($file_config);
		return "Salvataggio riuscito.";
	}
	function isInitialized(){
		$table_list.="'".LK_TABLE_LINKS."',";
		//$table_list.="'".LK_TABLE_LINKS_PARAMS."',";
		$table_list.="'".LK_TABLE_AMMINISTRATORI."'";
		$q_str_tables="select count(*) conto from user_tables where table_name in ($table_list)";
		//Logger::send($q_str_tables);
		$query=new query($this->conn);
		$query->get_row($q_str_tables);
		//Logger::send($query->row['CONTO']);
		if($query->row['CONTO']==2)
		return true;
		else
		return false;
	}
	function initialize(){
		$table_create[]="
			create table ".LK_TABLE_LINKS." (
				ID number,
				ID_REF number,
				GROUP_LINK number,
				TIPOLOGIA number,
				TESTO varchar (1000),
				HREF varchar2(1000),
				ABILITATO number,
				order_col number,
				target varchar2 (1000)
			)";
		
		/*$table_create[]="create table ".LK_TABLE_LINKS_PARAMS." (
		ID_REF number,
		GROUP_LINK number,
		PARAM varchar2(100),
		SESSION_VAR varchar2(100)
		)";*/
		$table_create[]="create table ".LK_TABLE_AMMINISTRATORI." (
				USERID varchar2(40) not null,
				GROUP_LINK number not null
			)
		";
		$table_create[]="create table ".LK_TABLE_LINK_GRUPPIU."
			(
			  ID_LINK    NUMBER not null,
			  GROUP_LINK NUMBER not null,
			  ID_GRUPPOU NUMBER not null
			 
			)
			
		";

		$table_create[]="create table ".LK_TABLE_THEME."
			(
			  CONSTANT    varchar2(40) not null,
			  VALUE varchar2(200) not null,
			  GROUP_LINK NUMBER not null
			 
			)
			
		";


		$constraint_create[]="alter table ".LK_TABLE_LINKS."
 				 add constraint PK_".LK_TABLE_LINKS." primary key (ID,GROUP_LINK)
 				 using index ";
		/*$constraint_create[]="alter table ".LK_TABLE_LINKS_PARAMS."
		add constraint PK_".LK_TABLE_LINKS_PARAMS." primary key (ID_REF,PARAM)
		using index ";*/
		/*$constraint_create[]="alter table ".LK_TABLE_LINKS_PARAMS."
		add constraint FK_".LK_TABLE_LINKS_PARAMS."_LINKS foreign key (ID_REF,GROUP_LINK)
		references ".LK_TABLE_LINKS." (ID,GROUP_LINK) on delete cascade
		";*/
		$constraint_create[]="alter table ".LK_TABLE_AMMINISTRATORI."
				 add constraint PK_".LK_TABLE_AMMINISTRATORI." primary key (USERID, GROUP_LINK)
				 using index ";
		$constraint_create[]="alter table ".LK_TABLE_THEME."
 				 add constraint PK_".LK_TABLE_THEME." primary key (CONSTANT,GROUP_LINK)
 				 using index ";
		$constraint_create[]="alter table ".LK_TABLE_LINK_GRUPPIU."
				  add constraint PK_".LK_TABLE_LINK_GRUPPIU." primary key (ID_LINK, ID_GRUPPOU, GROUP_LINK)
				  using index
		";
		$constraint_create[]="alter table ".LK_TABLE_LINK_GRUPPIU."
				  add constraint FK_".LK_TABLE_LINK_GRUPPIU."_IDGU foreign key (ID_GRUPPOU)
				  references ".TABLE_GRUPPIU." (ID_GRUPPOU)
		";
		$constraint_create[]="alter table ".LK_TABLE_LINK_GRUPPIU."
				  add constraint FK_".LK_TABLE_LINK_GRUPPIU."_IDLINK foreign key (ID_LINK, GROUP_LINK)
				  references ".LK_TABLE_LINKS." (ID, GROUP_LINK)
		";
		$constraint_create[]="create sequence ".LK_SEQUENCE."
				 minvalue 1
				 start with 1
                 increment by 1
                 nocache";
		$values['USERID']=$this->session_vars['remote_userid'];
		$query=new query($this->conn);
		foreach ($table_create as $curr_sql){
			$query->set_sql($curr_sql);
			$query->ins_upd();//non richiede binding
		}
		foreach ($constraint_create as $curr_sql){
			$query->set_sql($curr_sql);
			$query->ins_upd();//non richiede binding
		}
	}
	function isUpdated(){
		//$str="select char_length from user_tab_cols where table_name='".LK_TABLE_THEME."' and column_name='VALUE'";
		$str="select count(*) conto from user_tab_cols where table_name='".LK_TABLE_LINKS."' and column_name='ORDER_COL'";
		$query=new query($this->conn);
		$query->exec($str);//non richiede binding
		$query->get_row();
		if ($query->row['CONTO']==0) {
			return false;
		}
		else {
			return true;
		}
	}
	function update(){
		$str="select count(*) conto from user_tab_cols where table_name='".LK_TABLE_LINKS."' and column_name='ORDER_COL'";
		$query=new query($this->conn);
		$query->exec($str);//non richiede binding
		$query->get_row();
		if ($query->row['CONTO']==0) {
			$str="alter table ".LK_TABLE_THEME." modify VALUE VARCHAR2(200)";
			$query=new query($this->conn);
			$query->set_sql($str);
			$query->ins_upd();//non richiede binding
			$str="alter table ".LK_TABLE_LINKS." add order_col number";
			$query=new query($this->conn);
			$query->set_sql($str);
			$query->ins_upd();//non richiede binding
			$str="update ".LK_TABLE_LINKS." set order_col=rownum where tipologia=1";
			$query=new query($this->conn);
			$query->set_sql($str);
			$query->ins_upd();//non richiede binding
			$str="update ".LK_TABLE_LINKS." set order_col=rownum where tipologia=2";
			$query=new query($this->conn);
			$query->set_sql($str);
			$query->ins_upd();//non richiede binding
			$this->conn->commit();
		}
	}
	function getUser(){
		$bind['USERID']=$this->session_vars['remote_userid'];
		$bind['ID_GROUP']=LK_GROUP_LINK;
		$str="select count(*) conto from ".LK_TABLE_AMMINISTRATORI." where userid=:userid and group_link=:id_group";
		$query=new query($this->conn);
		$query->exec($str,$bind);//non richiede binding
		$query->get_row();
		if($query->row['CONTO']==0){
			return new ClienteUser($this->conn,$this->session_vars,$this->config_service);
		}
		else{
			return new AmminUser($this->conn,$this->session_vars,$this->config_service);
		}
	}
}
/**
 * @package Reporting
 */
class AmminUser extends LinkerUser{
	function getLinksList(){
		$this->loadLinks(true);
		$list="<div class='list_box'>";
		foreach ($this->links as $id_link => $curr_link) {
			$list.=$curr_link->getListHtml();
			foreach ($this->grouppedLinks[$id_link] as $in_link ){
				$list.=$in_link->getListHtml();
                
                    if(count($this->grouppedLinks[$in_link->data['ID']])>0){
                        
                        foreach ($this->grouppedLinks[$in_link->data['ID']] as $in2_link ){
                            $list.=$in2_link->getListHtml();
                        }
                        
                    }
			}
		}
		$list.="</div>";
		return $list;
	}
	function home(){
		$this->links[]=new link($this->conn,null,array("TIPOLOGIA" => "LINK","TESTO" => Label::testo("Crea un nuovo report",$this->config_service['lang']),"HREF" => "?rep_link=true&REQUEST=LINK_FORM"),$this->config_service['lang'],$this->config_service);
		$this->links[]=new link($this->conn,null,array("TIPOLOGIA" => "LINK","TESTO" => Label::testo("Lista dei link",$this->config_service['lang']),"HREF" => "?rep_link=true&REQUEST=LINK_LIST"),$this->config_service['lang'],$this->config_service);
		$this->links[]=new link($this->conn,null,array("TIPOLOGIA" => "LINK","TESTO" => Label::testo("Default",$this->config_service['lang']),"HREF" => "?rep_link=true&REQUEST=DEFAULT_FORM"),$this->config_service['lang'],$this->config_service);
		$this->links[]=new link($this->conn,null,array("TIPOLOGIA" => "LINK","TESTO" => Label::testo("Aggiornamento dati",$this->config_service['lang']),"HREF" => "?rep_link=true&REQUEST=UPDATE_SETUP"),$this->config_service['lang'],$this->config_service);
		$this->links[]=new link($this->conn,null,array("TIPOLOGIA" => "LINK","TESTO" => Label::testo("Messaggio Utente",$this->config_service['lang']),"HREF" => "?rep_link=true&REQUEST=INFO_FORM"),$this->config_service['lang'],$this->config_service);
		$this->links[]=new link($this->conn,null,array("TIPOLOGIA" => "LINK","TESTO" => Label::testo("Preview",$this->config_service['lang']),"HREF" => "?rep_link=true&REQUEST=PREVIEW","TARGET" => '_self'),$this->config_service['lang'],$this->config_service);
		return $this->getMenu(true);
	}
	function link_details(){}
	function save_link(){}
	function abilitazione_link(){}
	function remove_link(){}
	function isAmmin(){
		return true;
	}
	function preview(){
		$this->links[]=new link($this->conn,null,array("TIPOLOGIA" => "LINK","TESTO" => Label::testo("Esci dalla preview",$this->config_service['lang']),"HREF" => "?rep_link=true&REQUEST=MENU","TARGET" => "_self"),$this->config_service['lang'],$this->config_service);
		return $this->getMenu();
	}
}
/**
 * @package Reporting
 */
class ClienteUser extends LinkerUser{
	function home(){
		return $this->getMenu();
	}
}
/**
 * @package Reporting
 */
class LinkerUser{
	var $default_pages;
	var $links;
	var $result;
	var $conn;
	var $session_vars;
	var $grouppedLinks;
	var $utenteIanus;
	var $config_service;
	function __construct($conn,$session_vars,$config_service=null){
		$this->conn=$conn;
		$this->session_vars=$session_vars;
		$this->config_service=$config_service;
		$this->utenteIanus=new utenteIanus($conn,$session_vars['remote_userid']);
	}
	function getMenu($loaded=false){
		if(!$loaded) $this->loadLinks();
		$this->result.="
			<div class=\"menu_box\" id='menu4' > <ul>";
		foreach ($this->links as $id_link => $curr_link){
			$this->result.="<div class='menu_header' >";
			$this->result.=$curr_link->getHtml();
			$this->result.="</div>";
			if(count($this->grouppedLinks[$id_link])>0){
				$this->result.="<div class=\"menu_body\" ><div>";
				foreach ($this->grouppedLinks[$id_link] as $in_link ){
//				    Logger::send($in_link);
                    if(count($this->grouppedLinks[$in_link->data['ID']])>0){
                       $this->result.="<div class='menu_subheader' >";
					   $this->result.=$in_link->getHtml();
                       $this->result.="</div>";
                    }
                    else{
                        $this->result.=$in_link->getHtml();
                    }
                    if(count($this->grouppedLinks[$in_link->data['ID']])>0){
                        $this->result.="<div class=\"menu_body\" ><div>";
                        foreach ($this->grouppedLinks[$in_link->data['ID']] as $in2_link ){
                            $this->result.=$in2_link->getHtml();
                        }
                        $this->result.="</div></div>";
                    }
				}
				$this->result.="</div></div>";
			}
		}
		$this->result.="</ul></div>";
		return $this->result;
	}
	function loadLinks($all=false){
		#		$str="select * from ".LK_TABLE_LINKS." where group_link=".LK_GROUP_LINK;
		$groupsList=$this->utenteIanus->getGroupsList();
		if($groupsList!=''){
			if($all) $str="select * from ".LK_TABLE_LINKS." where group_link=".LK_GROUP_LINK." order by order_col";
			/*else $str="select lt.* from ".LK_TABLE_LINKS." lt, ".LK_TABLE_LINK_GRUPPIU." lg where lg.id_link=lt.id and id_gruppou in ($groupsList) and lg.group_link=".LK_GROUP_LINK;*/
			else $str="select lt.* from ".LK_TABLE_LINKS." lt where (lt.id) in (select id_link from ".LK_TABLE_LINK_GRUPPIU." lg where id_gruppou in ($groupsList) and lg.group_link=".LK_GROUP_LINK.")  order by order_col";
			$query=new query($this->conn);
			$query->exec($str);//non richiede binding
			while ($query->get_row()){
				if($query->row['ID_REF']=="")$this->links[$query->row['ID']]=new Link($this->conn,null,$query->row,$this->config_service['lang'],$this->config_service);
				else $this->grouppedLinks[$query->row['ID_REF']][$query->row['ID']]=new Link($this->conn,null,$query->row,$this->config_service['lang'],$this->config_service);
			}
		}
	}
	function getAnagrafica(){
		return $this->utenteIanus->getAnagrafica();
	}

	function message($message){
		return $message;
	}
	function isAmmin(){
		return false;
	}

}
/**
 * @package Reporting
 */
class utenteIanus{
	private $conn;
	private $user;
	private $groups;
	private $groupsList;
	private $anagrafica;
	function __construct($conn,$user){
		$this->conn=$conn;
		$this->user=$user;
	}
	function getGroupsList(){
		if($this->groupsList==''){
			$this->getGroups();
		}
		return $this->groupsList;
	}
	function getGroups(){
		if(count($this->groups)==0){
			$this->groupsList="";
			$bind_userid['USERID']=$this->user;
			$str="select ID_GRUPPOU from ".TABLE_UTENTI_GRUPPIU." where userid=:userid and abilitato=1";
			$query=new query($this->conn);
			$query->exec($str,$bind_userid);//binded
			while ($query->get_row()) {
				$this->groups[]=$query->row['ID_GRUPPOU'];
				$this->groupsList.=$query->row['ID_GRUPPOU'].',';
			}
			$this->groupsList=rtrim($this->groupsList,',');
		}
		return $this->groups;
	}
	function getAnagrafica(){
		if(!isset($this->anagrafica)){
			$this->loadAna();
		}
		return $this->anagrafica;
	}
	function loadAna(){
		$bind_userid['USERID']=$this->user;
		$select="select * from ana_utenti where userid=:userid";
		$query=new query($this->conn);
		$query->exec($select,$bind_userid);//binded
		$query->get_row();
		$this->anagrafica=$query->row;
		return true;
	}
}
/**
 * @package Reporting
 */
class ianus{
	static private $groups;
	static private $groupsList;
	static function getGroupsList($conn){
		if(self::$groupsList==""){
			self::getGroups($conn);
		}
		return self::$groupsList;
	}
	static function getGroups($conn){
		if(count(self::$groups)==0){
			self::$groupsList="";
			$str="select * from ".TABLE_ANA_GRUPPIU;
			$query=new query($conn);
			$query->exec($str);//non richiede binding
			while ($query->get_row()) {
				self::$groups[$query->row['ID_GRUPPOU']]=$query->row['NOME_GRUPPO'];
				self::$groupsList.=$query->row['ID_GRUPPOU'].',';
			}
			self::$groupsList=rtrim(self::$groupsList,',');
		}
		return self::$groups;
	}
}

?>