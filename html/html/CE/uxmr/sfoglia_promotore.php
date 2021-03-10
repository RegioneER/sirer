<?
include_once "config.inc";

$conn = new dbconn ( );
$page = $_POST ['Page'];
if ($page == '')
	$page = 1;

$body = "
<style>
	@media only screen and (max-width: 991px) {
		.page-content{
		padding-left:90px;
		}
	}
</style>

	<form method=\"POST\" name='cerca_form'>
	<div class=\"well well-sm\" style=\"margin-bottom: 0px;\">
		<table border=0 cellpadding=0 cellspacing=0 >
			<tr>
				<td align='left'>Cerca Promotore: &nbsp;&nbsp;</td>
				<td><input style=\"width: 297px;\" type='text' name='PATTERN' value='{$_POST['PATTERN']}' placeholder=\"Sponsor\"></td>
			</tr>
			<tr>
				<td colspan=2 align='center'>
					<input type='hidden' name='Page' value='$page'>
					<input type='hidden' name='Cerca' value='yes'>
					<br>
					<!--GC 23/11/2015 NUOVA_GRAFICA-->
					<!--input type='submit' name='Cerca1' value='Cerca' onclick=\"document.forms['cerca_form'].Page.value=1\">
					<input type='reset' name='Annulla' value='Annulla'-->
					
					<button title=\"Cerca Sponsor in Banca Dati\" id=\"button-search\" class=\"btn btn-purple btn-sm\" type=\"submit\" onclick=\"document.forms['cerca_form'].Page.value=1\">
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

if (isset ( $_POST ['Cerca'] )) {
	if ($_POST ['PATTERN'] != '') {
		
		$keyword=strtoupper($_POST['PATTERN']);
		$keyword=str_replace("'", "%", $keyword);
		
		$sql_where_clause="where (UPPER(DENOMINAZIONE) like '%".$keyword."%')";
		$sql_query="select * from CE_ELENCO_PROMOTORI $sql_where_clause";
		 //echo "$sql_query";
		$sql=new query($conn);
		$sql->exec($sql_query);
		$body.="<div style=\"margin-bottom: 0px;\">";
		if ($sql->numrows==0) $body.="
		<br>
		<table class=\"table table-striped table-bordered table-hover\" width=\"95%\" border=\"0\" align=\"center\">
					<tr>
						<td>La ricerca non ha prodotto risultati</td>
					</tr>
			</table>		
		";
		else {
			$body.="
				<ul class=\"pagination\">
			";
		
		$rpp=10;
		$nrows=$sql->numrows;
		$pages=ceil($nrows/$rpp);
		
		$paging_bar='';
		if ($page!=1){
			$paging_bar.="<li><a href=\"#\" onclick=\"document.forms['cerca_form'].Page.value=1;document.forms['cerca_form'].submit();return false;\"><i class=\"icon-double-angle-left\"></i></a>&nbsp;</li>";		
		}
		for ($i=1;$i<=$pages; $i++){
			if ($i==$page) $paging_bar.="<li class=\"active\"><a href=\"#\">$i&nbsp;</a></li>";
			else {
				$paging_bar.="<li><a href=\"#\" onclick=\"document.forms['cerca_form'].Page.value=$i;document.forms['cerca_form'].submit();return false;\">$i</a>&nbsp;</li>";
			}
		}
		if ($page!=$pages){
			$paging_bar.="<li><a href=\"#\" onclick=\"document.forms['cerca_form'].Page.value=$pages;document.forms['cerca_form'].submit();return false;\"><i class=\"icon-double-angle-right\"></i></a>&nbsp;</li>";		
		}
		$first_row=$rpp*($page-1)+1;
		$last_row=$rpp*($page);
		$sql_query="select * from (
			select t.*, rownum as n_r from ($sql_query) t
		) t1
		where t1.n_r between $first_row and $last_row
		";
		$body.="<p>$paging_bar</p><br>";
		$sql->exec($sql_query);
		$body.="
			<table class=\"table table-striped table-bordered table-hover\" width=\"95%\" border=\"0\" align=\"center\">
				<thead>
					<tr>
						<th>Denominazione Sponsor</th>
						<th style=\"text-align:center;\" >Inserisci</th>
					</tr>
				</thead>";
		while ($sql->get_row()){
			$body.="
					<tr>
						<td>{$sql->row['DENOMINAZIONE']} ({$sql->row['CITTA']} - {$sql->row['NAZIONE']})</td>
						<th style=\"text-align:center;\" >
							<button title=\"Inserisci Sponsor allo studio\" id=\"button-search\" class=\"btn btn-purple btn-sm\" type=\"submit\" onclick=\"".make_button_link($sql->row)."\">
								<i class=\"fa fa-plus\"></i>
							</button>
						</th>
					</tr>				
			";
		}
		$body.="</table>";
			
		if ($sql->numrows!=0) $body.="</table></ul></div>";
		}
	} else {
		
	}
}

$filetxt = str_replace ( "<!--body-->", $body, $filetxt );
die ( $filetxt );

function make_button_link($row){
	$row=make_row($row);
	foreach ($_GET as $key => $val){
		$row[$val]=str_replace("'", "\\'", $row[$val]);
		$js.="window.opener.document.forms[0].{$key}.value='{$row[$val]}';\n";
	}
	$js.="window.close();";
	return $js;
	
}
function make_row($row1){
  
  $row['DENOMINAZIONE']=$row1['DENOMINAZIONE'];
  $row['ID']=$row1['ID'];

	return $row;
}

?>