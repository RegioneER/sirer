<?php
	
	/**
	 *  Clean service
	 * 
	 * 	Script to clean (most of) the tables
	 * 	for Pierrel clinical trial.
	 * 
	 * 	by Mauro Verrocchio
	 * 	April 2011
	 * 
	 */

	require_once "/http/lib/php_utils/smarty/Smarty.class.php";

	$template = new Smarty();
	
	if(strtolower($_SERVER['REMOTE_USER']) != 'admin') {
        die("USER NOT ALLOWED!");
	}
	

	function isAjax()
	{
		if (isset($_SERVER['HTTP_X_REQUESTED_WITH']) && $_SERVER['HTTP_X_REQUESTED_WITH'] == "XMLHttpRequest")
  			return true;
   		return false;
  	}
	function error_page()
	{
		if (isAjax()) {
			echo json_encode(array("sstatus" => "ko"));
			die();
		}
	}
	
	function output_table($title, $elements_prefix, $table_array, $query_prefix = "DELETE FROM ", $alternate_query_prefix = "")
	{
		$output_table_html .= '
	       <tr> 
	         <td class="queries_title">'.$title.'</td>
	         <td class="queries_title" width="70" align="center">
	         	<input type="checkbox" id="'.$elements_prefix.'" />&nbsp;
				<input type="hidden" id="hidden_'.$elements_prefix.'" value="'.$query_prefix.'"/>
       	';
		if ($alternate_query_prefix != "") {
			$output_table_html .= '<span style="font-size: xx-small;">(<input type="checkbox" id="'.$elements_prefix.'_alt" />alt.)</span>
			<input type="hidden" id="hidden_'.$elements_prefix.'_alt" value="'.$alternate_query_prefix.'"/>
			';
		}
		$output_table_html .= '
				<!--<img id="imgloading_'.$elements_prefix.'_'.$table.'" src="libs/images/waiting_animatedCircle.gif" width="18" height="18" border="0" />-->
         	</td>
	       </tr>
       	';
		foreach ($table_array as $table)
		{
			if (is_array($table)) {
				$table_id = $table[0];
				$table_text = $table[1];
			} else {
				$table_id = $table;
				$table_text = $table;
			}
			$query_text = $query_prefix.$table_text;
			$output_table_html .= '
		      <tr> 
		        <td class="queries"><span class="queries" id="querytext_'.$elements_prefix.'_'.$table_id.'">'.$query_text.';</span></td>
		        <td class="queries queries-right">
		        	<input type="hidden" id="hidden_'.$elements_prefix.'_'.$table_id.'" name="hidden_'.$elements_prefix.'_'.$table_id.'" value="'.$query_text.'" />
		        	<input type="checkbox" id="checkbox_'.$elements_prefix.'_'.$table_id.'" name="checkbox_'.$elements_prefix.'_'.$table_id.'" />
					&nbsp;
		        	<!--<img id="imgloading_'.$elements_prefix.'_'.$table_id.'" src="libs/images/waiting_animatedCircle.gif" width="18" height="18" border="0" style="vertical-align: middle; visibility: hidden;" />-->
				</td>
		      </tr>
		      ';
		}
		
		return $output_table_html;
	}

	
	/** Require della libreria per l'interfacciamento al DB del servizio. */
	include_once "libs/db.inc";
	$conn= new dbconn();
	
	if (isAjax()) {
//		print_r($_POST);
//		die();
		foreach($_POST as $key => $value)
		{
			$query = new query ( $conn );
			// eseguo la query
			$query->set_sql ( $value );
			$query->exec();
		}
		$conn->commit();
		
		echo json_encode(array("sstatus" => "ok"));
		die();
	}
	
	//Prefisso del servizio
	$xml = simplexml_load_file("study.xml") or die("study.xml not loading");
	$study_prefix=$xml->configuration->prefix;
	$study_name=$xml->workflow->nome;
	
	// Trovo le tabelle
	$study_tables = array();
	$query = new query ( $conn );
	// Controllo se la tabella esiste
	$query_list_tables = "select * from user_tables order by table_name";
	$query->set_sql ( $query_list_tables );
	$query->exec();
	while ( $query->get_row () ) {
		$study_tables[] = strtoupper($query->row ['TABLE_NAME']);
	}

	// Tabelle dello studio da DELETEare
	$study_tables_to_delete = array (
		'[[:study_prefix:]]_COORDINATE',
		'[[:study_prefix:]]_EQ',
		'[[:study_prefix:]]_EQUERY',
		'[[:study_prefix:]]_EQFIELD',
		'CRA_CENTER',
		'CMM_CENTER',
		'CMM_USERS',
		'CMM_LANGUAGES',
		'CMM_RANDOMISATION',
		'SIRE_FIRMA_UTENTI_CENTRI',

		'S_CRA_CENTER',
		'S_CMM_CENTER',
		'S_CMM_USERS',
		'S_CMM_LANGUAGES',
		'S_CMM_RANDOMISATION',

		'S_X_CRA_CENTER',
		'S_X_CMM_CENTER',
		'S_X_CMM_USERS',
		'S_X_CMM_LANGUAGES',
		'S_X_CMM_RANDOMISATION',
	);	
	
	// Tabelle per ogni form dello studio da DELETEare
	$each_form_tables_to_delete = array (
		'EQ_[[:study_prefix:]]_[[:scheda_name:]]',
		'[[:study_prefix:]]_[[:scheda_name:]]',
		'S_[[:study_prefix:]]_[[:scheda_name:]]',
	);

	// Tabelle dei sottostudi dello studio da DELETEare
	$substudy_tables_to_delete = array (
		'RANGE' => array (
			'[[:substudy_name:]]_COORDINATE',
			'[[:substudy_name:]]_EQUERY',
			'[[:substudy_name:]]_EQFIELD',
			'[[:substudy_name:]]_LBPARAM',
		)
	);
	
	// Costruisco le queries per le tabelle dello studio
	$study_tables_name = array();
	foreach ($study_tables_to_delete as $table)
	{
		$study_tables_name[] = preg_replace("/\[\[:study_prefix:\]\]/", $study_prefix, $table);
	}
	
	// Trovo le tabelle relative alle forms	
	$xml = simplexml_load_file("xml/visite_exams.xml") or die("visite_exams.xml not loading");
	$study_forms = array();
	$study_forms_tables_name = array();
	$study_visit_and_exam_number = array();
	foreach ($xml->group as $group)
	{
		foreach ($group->visit as $visit)
		{
			$visit_number = (string) $visit->attributes()->number;
			$exam_numbers = array();
			foreach ($visit->exam as $exam)
			{
				$form = (string) $exam->attributes()->xml;
				$exam_numbers[] = (string) $exam->attributes()->number;
				$xml_form = simplexml_load_file("xml/".$form) or die($form." not loading");
				$table = (string) $xml_form->attributes()->table;
				$study_forms[] =  $table;
				//Costruisco le queries per le tabelle relative alle forms
				foreach ($each_form_tables_to_delete as $form_table)
				{
					$study_forms_tables_name[] = preg_replace("/\[\[:study_prefix:\]\]/", $study_prefix,
						preg_replace("/\[\[:scheda_name:\]\]/", $table, $form_table));
				}
			}
			$study_visit_and_exam_number[$visit_number] = $exam_numbers;
		}
	}
	// Rimuovo i duplicati
	$study_forms_tables_name = array_unique($study_forms_tables_name);
	
	// Costruisco le queries per le tabelle dello studio
	$substudy_tables_name = array();
	foreach ($substudy_tables_to_delete as $substudy_name => $substudy)
	{
		foreach ($substudy as $table)
		{
			$substudy_tables_name[] = preg_replace("/\[\[:substudy_name:\]\]/", $substudy_name, $table);
		}
	}
	
	// Se setto purge cancello solo gli esami non più in visite_exams.xml
	if (!isset($_GET['PURGE'])) {
		
		// Costruisco la tabella delle queries
		$all_tables = array_merge($study_tables_name, $study_forms_tables_name, $substudy_tables_name);
		
		// Tabelle di sistema
		$this_study_tables_to_delete = array_intersect($study_tables_name, $study_tables);
		if (count($this_study_tables_to_delete) > 0) {
			$queries .= output_table("Tabelle base dello studio", "study_tables", $this_study_tables_to_delete);
		}	
		
		// Tabelle delle forms
		$this_study_forms_tables_to_delete = array_intersect($study_forms_tables_name, $study_tables);
		if (count($this_study_forms_tables_to_delete) > 0)
		{
			$queries .= output_table("Tabelle delle forms dello studio", "study_forms_tables", $this_study_forms_tables_to_delete, "DELETE FROM ", "DROP TABLE ");
		}
		
		// Tabelle dei sottostudi
		$this_substudy_tables_name = array_intersect($substudy_tables_name, $study_tables);
		if (count($this_substudy_tables_name) > 0)
		{
			$queries .= output_table("Tabelle base dei sottostudi", "substudy_tables", $this_substudy_tables_name);
		}	
		
		// Tabelle delle forms vecchie
		$this_study_table_left = array_diff($study_tables, $all_tables);
		$this_study_old_forms_tables_name = array();
		foreach ($this_study_table_left as $temp_table)
		{
			if (!preg_match("/_SYS_/i", $temp_table) &&
				!preg_match("/_DBLOCK/i", $temp_table) &&
				true) {
					
				// Se le tabelle non sono di tipo _SYS_ e _DBLOCK
				foreach ($each_scheda_tables_to_delete as $temp_scheda_table)
				{
					$temp_scheda_table_name = preg_replace("/\[\[:study_prefix:\]\]/", $study_prefix,
						preg_replace("/\[\[:scheda_name:\]\]/", "", $temp_scheda_table));
					if (preg_match("/^".$temp_scheda_table_name."/i", $temp_table)) {
						$this_study_old_forms_tables_name[] = $temp_table;
					}
				} 	
			}
		}
	
		if (count($this_study_old_forms_tables_name) > 0)
		{
			$queries .= output_table("Tabelle delle vecchie forms", "study_old_forms_tables", $this_study_old_forms_tables_name, "DROP TABLE ");
		}	
		
	} else {

		// Esami non più in visite_exams.xml
		$where_query = "WHERE ";
		foreach ($study_visit_and_exam_number as $visit_number => $exams)
		{
			$temp_where = "NOT (VISITNUM={$visit_number} AND ESAM IN(";
			foreach ($exams as $i => $exam_number)
			{
				$temp_where .= $exam_number;
			 	if ($exam_number!=array_pop(array_values($exams))) {
			 		$temp_where .= ", ";
			 	}
			}
			$temp_where .= "))";
			
			$where_query .= $temp_where. " AND ";
		}
		$where_query .= " VISITNUM < 98";
		
		
		$this_study_exams_to_purge = array();
		$query = new query ( $conn );
		$query_exams_to_purge = "select VISITNUM, ESAM from {$study_prefix}_COORDINATE {$where_query} order by VISITNUM";
		if (isset($_GET['DEBUG'])) {
			$template->assign("query_exams_to_purge", $query_exams_to_purge);
		}
		$query->set_sql ( $query_exams_to_purge );
		$query->exec();
		while ( $query->get_row () ) {
			$this_study_exams_to_purge[] = array($query->row['VISITNUM']."_".$query->row['ESAM'], "WHERE VISITNUM={$query->row['VISITNUM']} AND ESAM={$query->row['ESAM']}");
		}
		
		if (count($this_study_exams_to_purge) > 0)
		{
			$queries .= output_table("Esami non più nella lista degli esami", "study_exams_to_purge", $this_study_exams_to_purge, "DELETE FROM {$study_prefix}_COORDINATE ");
		}	
	}
	
//	$template->debugging = true;
	$template->assign("study_name", ucfirst($study_name));
	$template->assign("queries", $queries);
	$template->assign("request_uri", $_SERVER["REQUEST_URI"]);
	$template->display(basename(__FILE__, ".php").".tpl");
		
?>
			
