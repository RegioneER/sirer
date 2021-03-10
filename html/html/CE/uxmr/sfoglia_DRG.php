<?
include_once "config.inc";

$conn = new dbconn ();

$body="<p class=int>Database DRG</p>";

$param['CODE1']="CODE1";
$param['CODE2']="CODE2";

$query['CODE1']="select 
	distinct 
	CODE1,
	CODE2, 
	CODE,
	CODE_POINT, 
	DECODE 
	from ICD9CM_ITA
	where CODE2 is null
	order by decode";
$query['CODE2']="select 
	distinct 
	CODE1,
	CODE2, 
	CODE, 
	CODE_POINT, 
	DECODE 
	from ICD9CM_ITA";


if ($_GET['MODE']=='SFOGLIA'){
	$action_link="sfoglia_DRG.php?MODE=SFOGLIA&CODE1={$_GET['CODE1']}&CODE2={$_GET['CODE2']}&CODE={$_GET['CODE']}&DECODE={$_GET['DECODE']}";

	$query_sql=$query['CODE1'];
	if (isset($_POST['CODE1']) && $_POST['CODE1']!='') $where['CODE1']="CODE1='{$_POST['CODE1']}'";
	if (isset($_POST['CODE1']) && $_POST['CODE1']!='') $query_sql=$query['CODE2'];
	foreach ($where as $key =>$val){
		if ($where_!='') $where_.=" and ";
		$where_.=$val;
	}
	//if ($where_!='') $query_sql.=" where $where_ order by CODE1,to_number(CODE2) asc nulls first";
	if ($where_!='') $query_sql.=" where $where_ order by decode";
	
	$res=tabella_risultati(0,$query_sql, $conn);
	$last_row=$res['last_row'];
	$tb_res=$res['tb'];
	$navigation_bar=navigation_bar($last_row, 0);
	$form_sfoglia=make_form(0,$action_link);	
	$tb_res="
		<br>
			<table class=\"table table-striped table-bordered table-hover\" width=\"95%\" border=\"0\" align=\"center\">
				<thead>
					<tr>
						<th>Codice1</th>
						<th>Codice2</th>
						<th>Descrizione</th>
						<th>Inserisci</th>
					</tr>
				</thead>
	".$tb_res."</table>";
	$body.=$navigation_bar;
	$body.=$form_sfoglia;
	$body.=$tb_res;
}
if ($_GET['MODE']=='CERCA'){
	$action_link="sfoglia_DRG.php?MODE=CERCA&CODE1={$_GET['CODE1']}&CODE2={$_GET['CODE2']}&CODE={$_GET['CODE']}&DECODE={$_GET['DECODE']}";
	$body.=make_form(0,$action_link,false);	
	if (isset($_POST['cerca']) && $_POST['PATTERN']!=''){
		$action_link="sfoglia_DRG.php?MODE=SFOGLIA&CODE1={$_GET['CODE1']}&CODE2={$_GET['CODE2']}&CODE={$_GET['CODE']}&DECODE={$_GET['DECODE']}";
		
			$i=1;
			$query_sql="select * from ({$query['CODE2']}) where upper(DECODE) like '%".strtoupper($_POST['PATTERN'])."%' order by to_number(CODE2) asc nulls first";
			//echo "<li>".$query_sql."</li><br>";
			$body.=make_form($i, $action_link);
			$res=tabella_risultati($i,$query_sql, $conn);
			$last_row=$res['last_row'];
			$tb_res.=$res['tb'];
			
		
		$tb_res="
		<br>
			<table class=\"table table-striped table-bordered table-hover\" width=\"95%\" border=\"0\" align=\"center\">
				<thead>
					<tr>
						<th>Codice1</th>
						<th>Codice2</th>
						<th>Descrizione</th>
						<th>Inserisci</th>
					</tr>
				</thead>
	".$tb_res."</table>";
		$body.=$tb_res;
	}
}
	$filetxt = str_replace ( "<!--body-->", $body, $filetxt );
	die ($filetxt);
	
	function make_form($idx, $action_link, $sfoglia=true){
		if ($sfoglia) return "
		<form method='POST' name='sfoglia_form_$idx' action=\"$action_link\">
			<input type='hidden' name='CODE1' value='{$_POST['CODE1']}'>
			<input type='hidden' name='CODE2' value='{$_POST['CODE2']}'>
		</form>
		";
		else return "
		<form method='POST' name='sfoglia_form_$idx' action=\"$action_link\">
			<div class=\"well well-sm\" style=\"margin-bottom: 0px;\">
				<table border=0 cellpadding=0 cellspacing=0 >
					<tr>
						<!-- Search: <input type='text' name='PATTERN' value=\"{$_POST['PATTERN']}\"-->
						<td align='left'>Cerca: &nbsp;&nbsp;</td>
						<td><input style=\"width: 297px;\" type='text' name='PATTERN' value='{$_POST['PATTERN']}' placeholder=\"ICD9\"></td>
					</tr>
					<tr>
						<td colspan=2 align='center'>
						<!--input type='submit' name='cerca' value='Send'-->
						<button title=\"Cerca in Banca Dati\" class=\"btn btn-purple btn-sm\" type=\"submit\" name=\"cerca\">
							<span id=\"std-label\"><i class=\"icon-search\"></i>Cerca</span>
						</button>
						<button class=\"btn btn-grey btn-sm\" type=\"reset\">
							<i class=\"icon-undo btn-sm\"></i>Annulla
						</button>
						</td>
					</tr>
				</table>
			</div>
			
		</form>
		";
	}
	
	function tabella_risultati($idx, $sql_query, $conn){
		$sql=new query($conn);
		$sql->exec($sql_query);
		
		while ($sql->get_row()){
			
			if ($sql->row['CODE2']!=''){
				$value="{$sql->row['DECODE']}";
				$value_="{$sql->row['CODE2']}";
			}
			
			else {
			$value="
				<a href=\"#\" onclick=\"
					{$onclick_plus}
					document.forms['sfoglia_form_$idx'].CODE1.value='{$sql->row['CODE1']}';
					document.forms['sfoglia_form_$idx'].submit();
				\">{$sql->row['DECODE']}</a>
				";
				
				$value_="&nbsp;";
			}
			$js_txt=str_replace("'", "\\'", $sql->row['DECODE']);
			$tb_res.="
			<tr>
				<td>{$sql->row['CODE1']}</td>
				<td>$value_</td>
				<td>$value</td>
				
				<td>
				
					<!--input type='button' value='&gt;&gt;' onclick=\"
					window.opener.document.forms[0].{$_GET['CODE1']}.value='{$sql->row['CODE1']}';
					window.opener.document.forms[0].{$_GET['CODE2']}.value='{$sql->row['CODE2']}';
					window.opener.document.forms[0].{$_GET['DECODE']}.value='{$js_txt}';
					window.opener.document.forms[0].{$_GET['CODE']}.value='{$sql->row['CODE_POINT']}';
					window.close();\"-->
					
					<button title=\"Inserisci\" class=\"btn btn-purple btn-sm\" type=\"button\" onclick=\"
					window.opener.document.forms[0].{$_GET['CODE1']}.value='{$sql->row['CODE1']}';
					window.opener.document.forms[0].{$_GET['CODE2']}.value='{$sql->row['CODE2']}';
					window.opener.document.forms[0].{$_GET['DECODE']}.value='{$js_txt}';
					window.opener.document.forms[0].{$_GET['CODE']}.value='{$sql->row['CODE_POINT']}';
					window.close();\">
					<i class=\"fa fa-plus\"></i>
				</button>
				
				</td>
				
			</tr>	
			";	
		}
		$res['tb']=$tb_res;
		$res['last_row']=$sql->row;
		return $res;
	}
	
	function navigation_bar($last_row, $idx){

		if ($_POST['CODE1']!=''){
		$navigation_bar.="<li>Level: <b>Code2</b></li>";	
		$navigation_bar.="<p align=center><a href=\"#\" onclick=\"
			document.forms['sfoglia_form_$idx'].CODE1.value='';
			document.forms['sfoglia_form_$idx'].submit();
			return false;
		\"
		>Torna al livello precedente</a></p>";

		return $navigation_bar;
	}
	}
?>