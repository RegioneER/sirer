<?php
	
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
	
	//Prefisso del servizio
	$xml = simplexml_load_file("study.xml") or die("study.xml not loading");
	$study_prefix=$xml->configuration->prefix;
	$study_name=$xml->workflow->nome;
	$study_dir_name = preg_replace("/\/http\/www\//", "", preg_replace("/\/html\/uxmr/", "", $xml->dir_base)); 


	// DEV
	include_once "/siss-devel/http/servizi/PIERREL/".$study_dir_name."/html/uxmr/libs/db.inc";
	$conn= new dbconn();
	
	// Trovo le tablelle
	$study_tables = array();
	$query = new query ( $conn );
	// Controllo se la tabella esiste
	$query_list_tables = "select * from user_tables order by table_name";
	$query->set_sql ( $query_list_tables );
	$query->exec();
	while ( $query->get_row () ) {
		$study_tables[] = strtoupper($query->row ['TABLE_NAME']);
	}
	
	var_dump($study_tables);

	// PREP (test)
	include_once "/sissprep/http/servizi/PIERREL/".$study_dir_name."/html/uxmr/libs/db.inc";
	$conn= new dbconn();
		
	// Trovo le tablelle
	$study_tables2 = array();
	$query = new query ( $conn );
	// Controllo se la tabella esiste
	$query_list_tables = "select * from user_tables order by table_name";
	$query->set_sql ( $query_list_tables );
	$query->exec();
	while ( $query->get_row () ) {
		$study_tables2[] = strtoupper($query->row ['TABLE_NAME']);
	}
	
	var_dump($study_tables2);
	die();
	
	
	// PROD (test)
	include_once "/sissprod/http/servizi/PIERREL/".$study_dir_name."/html/uxmr/libs/db.inc";
	$conn= new dbconn();
		
	// Trovo le tablelle
	$study_tables£ = array();
	$query = new query ( $conn );
	// Controllo se la tabella esiste
	$query_list_tables = "select * from user_tables order by table_name";
	$query->set_sql ( $query_list_tables );
	$query->exec();
	while ( $query->get_row () ) {
		$study_tables3[] = strtoupper($query->row ['TABLE_NAME']);
	}
	
	var_dump($study_tables3);

	die();
	
	// Costruisco le queries per le tabelle del servizio
	$study_tables_name = array();
	foreach ($study_tables_to_delete as $table)
	{
		$study_tables_name[] = preg_replace("/\[\[:study_prefix:\]\]/", $study_prefix, $table);
	}
	
	
	// Trovo le tabelle relative alle schede	
	$xml = simplexml_load_file("xml/visite_exams.xml") or die("visite_exams.xml not loading");
	$study_schede = array();
	$study_schede_tables_name = array();
	foreach ($xml->group as $group)
	{
		foreach ($group->visit as $visit)
		{
			foreach ($visit->exam as $exam)
			{
				$scheda = (string) $exam->attributes()->xml;
				$xml_scheda = simplexml_load_file("xml/".$scheda) or die($scheda." not loading");
				$table = (string) $xml_scheda->attributes()->table;
				$study_schede[] =  $table;
				//Costruisco le queries per le tabelle relative alle schede
				foreach ($each_scheda_tables_to_delete as $scheda_table)
				{
					$study_schede_tables_name[] = preg_replace("/\[\[:study_prefix:\]\]/", $study_prefix,
						preg_replace("/\[\[:scheda_name:\]\]/", $table, $scheda_table));
				}
			}
		}
	}
	// Rimuovo i duplicati
	$study_schede_tables_name = array_unique($study_schede_tables_name);
	
	// Costruisco le queries per le tabelle del servizio
	$substudy_tables_name = array();
	foreach ($substudy_tables_to_delete as $substudy_name => $substudy)
	{
		foreach ($substudy as $table)
		{
			$substudy_tables_name[] = preg_replace("/\[\[:substudy_name:\]\]/", $substudy_name, $table);
		}
	}
	
	// Costruisco la tabella delle queries
	$all_tables = array_merge($study_tables_name, $study_schede_tables_name, $substudy_tables_name);
	
	// Tabelle di sistema
	$this_study_tables_to_delete = array_intersect($study_tables_name, $study_tables);
	if (count($this_study_tables_to_delete) > 0) {
		$queries .= output_table("Tabelle base dello studio", "study_tables", $this_study_tables_to_delete);
	}	
	
	// Tabelle delle schede
	$this_study_schede_tables_to_delete = array_intersect($study_schede_tables_name, $study_tables);
	if (count($this_study_schede_tables_to_delete) > 0)
	{
		$queries .= output_table("Tabelle delle schede dello studio", "study_schede_tables", $this_study_schede_tables_to_delete, "DELETE FROM ", "DROP TABLE ");
	}
	
	// Tabelle dei sottostudy
	$this_substudy_tables_name = array_intersect($substudy_tables_name, $study_tables);
	if (count($this_substudy_tables_name) > 0)
	{
		$queries .= output_table("Tabelle base dei sottostudi", "substudy_tables", $this_substudy_tables_name);
	}	
	
	// Tabelle delle schede vecchie
	$this_study_table_left = array_diff($study_tables, $all_tables);
	$this_study_old_schede_tables_name = array();
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
					$this_study_old_schede_tables_name[] = $temp_table;
				}
			} 	
		}
	}

	if (count($this_study_old_schede_tables_name) > 0)
	{
		$queries .= output_table("Tabelle delle vecchie schede", "study_old_schede_tables", $this_study_old_schede_tables_name, "DROP TABLE ");
	}	
	
?>
			
<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.0 Transitional//EN">
<html>
<head>
<title>Clean service</title>
<meta http-equiv=Content-Type content="text/html; charset="utf-8">
<link href="/css/hyperstudy_v01.css" type="text/css" rel="stylesheet" />
<script src="libs/js/jquery/jquery-1.5.js" type="text/javascript"></script>
<script src="libs/js/jquery/jquery.scrollTo-1.4.2-min.js" type="text/javascript"></script>
<script src="libs/js/jquery/jquery.qtip-1.0.0-rc3.min.js" type="text/javascript"></script>
<meta content="MSHTML 6.00.2800.1226" name=GENERATOR>
<style type="text/css">

/* 
	Web20 Table Style
	written by Netway Media, http://www.netway-media.com
*/
table {
  border-collapse: collapse;
  border: 1px solid #666666;
  font: normal 11px verdana, arial, helvetica, sans-serif;
  color: #363636;
  background: #f6f6f6;
  text-align:left;
  }
caption {
  text-align: center;
  font: bold 16px arial, helvetica, sans-serif;
  background: transparent;
  padding:6px 4px 8px 0px;
  color: #CC00FF;
  text-transform: uppercase;
}
thead, tfoot {
background:url(bg1.png) repeat-x;
text-align:left;
height:30px;
}
thead th, tfoot th {
padding:5px;
}
table a {
color: #333333;
text-decoration:none;
}
table a:hover {
text-decoration: none;
}
tr.odd {
background: #f1f1f1;
}
tbody th, tbody td {
padding:5px;
}

a {
text-decoration:none;
}
a:hover {
text-decoration:underline;
}

.SenzaBordosup {
	border-right-width: thin;
	border-bottom-width: thin;
	border-left-width: thin;
	border-top-style: none;
	border-right-style: solid;
	border-bottom-style: solid;
	border-left-style: solid;
	border-top-width: 0px;
	border-top-color: #FFFFFF;
	border-right-color: #000000;
	border-bottom-color: #000000;
	border-left-color: #000000;
}

td.page_title {
/*  background-color: #00CCFF;*/
	background-color: #878555;
/*	background-color: #454490;*/
	font-size: medium;
}
span.queries {
	font-family: 'Courier New', Courier, monospace;
}

td.queries {
/*	background-color: #FFFFC8;*/
/*	background-color: #DEF5ED;*/
}

td.queries-selected {
	background-color: #FFFFC8;
}

td.queries-drop-selected {
	background-color: #FFD863;
}
td.queries_title {
/*	background-color: #02E0F4;*/
	background-color: #88A598;
/*	background-color: #394748; */
	font-size: medium;
}

td.queries_drop_title {
	background-color: #FFD863;
}
td.queries-right {
	text-align: center;
	width: 55px;
}

</style>
<script type="text/javascript">

	$(document).ready(function() {
		$("form").bind('submit', function(){
			if (confirm ("Are you sure to clean the service <?php echo ucfirst($study_name); ?>?")) {
				$("input:checkbox :submit").each(function(){
					$(this).attr("disabled", "disabled");
				});
				$("input:checkbox:not([id$='_tables']):checked").each(function() {
					$(this).siblings("image").show();
				});
				
				$.ajax({
					type: "POST",
					url: <?php echo "\"".$_SERVER["REQUEST_URI"]."\""; ?>,
					data: $("input:checkbox:not([id$='_tables']):checked").siblings("input[type='hidden']").serializeArray(),
					dataType: "json",
			  		success: function(data) {
						if (data.sstatus == 'ok') {
							alert("Cleaning done!");
							location.reload();
						} else {
							alert("error!");

							$("input:checkbox:not([id$='_tables']):checked").each(function() {
								$(this).siblings("image").hide();
							});
							$("input:checkbox :submit").each(function(){
								$(this).removeAttr("disabled");
							});
						}
					}
				});
			}
			
			return false;
		});

		$("input:checkbox[id*='_tables_']:not([id$='_alt'])").change(function(){
			$(this).closest("tr").children("td").removeClass("queries-selected");
			$(this).closest("tr").children("td").removeClass("queries-drop-selected");
			if ($(this).is(":checked")) {
				if ($(this).siblings("input[type='hidden']").first().val().match("^DROP") == "DROP") {
					$(this).closest("tr").children("td").addClass("queries-drop-selected");
				} else {
					$(this).closest("tr").children("td").addClass("queries-selected");
				}
			}
		});

		$("input:checkbox[id$='_tables']").change(function(){
			var master_check = this;
			$("input:checkbox[id^='checkbox_"+$(this).attr("id")+"_']").each(function(){
				if ($(master_check).is(":checked")) {
					$(this).attr("checked", "true");
				} else {
					$(this).removeAttr("checked");
				}
				$(this).trigger("change");
			});
		});

		$("input:checkbox[id$='_tables_alt']").change(function(){
			var this_checkbox = this;
			var master_check = $("#"+$(this).attr("id").replace("_alt",""));
			var normal_query_prefix = $("#hidden_"+$(master_check).attr("id")).val();
			var alternate_query_prefix = $("#hidden_"+$(master_check).attr("id")+"_alt").val();
			$("input:checkbox[id^='checkbox_"+$(master_check).attr("id")+"_']").each(function(){
				var my_table = $(this).attr("id").replace("checkbox_"+$(master_check).attr("id")+"_", "");
				var my_query = my_table;
				if ($(this_checkbox).is(":checked")) {
					my_query = alternate_query_prefix+my_query;
				} else {
					my_query = normal_query_prefix+my_query;
				}
				$(this).siblings("input[type='hidden']").first().val(my_query);
				var my_query_html = my_query+';';
				$("#querytext_"+$(master_check).attr("id")+"_"+my_table).html(my_query_html);
			});
			if ($(master_check).is(":checked")) {
				$(master_check).trigger("change");
			}
		});

		$("input:checkbox[id$='_tables']").each(function(){
			$(this).attr("checked", "true");
			$(this).trigger("change");
		});
		$("input:checkbox[id$='_tables_alt']").each(function(){
			$(this).attr("checked", "true");
			$(this).trigger("change");
		});

		$("[id^='imgloading_']").each(function(){
			$(this).hide();
		});

	});
		
</script>

</head>

<body>
<center>
  <form id="clean_service" name="clean_service" method="post">
    <table id="queries" border="1" cellpadding="2" cellspacing="0" bordercolor="#000000">
      <tbody>
        <tr> 
          <td class="page_title" colspan="2">Clean service: <b><?php echo ucfirst($study_name); ?></b></td>
        </tr>
      <?php echo $queries ?>

      <tr> 
        <td colspan="2" align=center class="small">
        	<input type="submit" style="color:#050; font: bold 80% 'trebuchet ms',helvetica,sans-serif; cursor:pointer;" name="submit" value="Clean!" > 
        </td>
      </tr>
      </tbody>
    </table>
  </form>
  <p> 
  </p>
</center></body></html>