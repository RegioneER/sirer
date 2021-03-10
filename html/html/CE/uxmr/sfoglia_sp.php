<?
include_once "config.inc";

$conn = new dbconn ( );
$page = $_POST ['Page'];
if ($page == '')
	$page = 1;

$body = "
	
	<p align=left class=titolo>Cerca Promotore</p>
	<form method=\"POST\" name='cerca_form'>
		<table border=0 cellpadding=0 cellspacing=0 >
			<tr>
			<td width='50px'>
			</td>
				<td align='left'>Ricerca:
				</td>
				<td><input type='text' name='PATTERN' value='{$_POST['PATTERN']}'>
				</td>
			</tr>
			<tr>
			<td width='50px'>
			</td>
				<td colspan=2 align='center'>
					<input type='hidden' name='Page' value='$page'>
					<input type='hidden' name='Cerca' value='yes'>
					<input type='submit' name='Cerca1' value='Cerca' onclick=\"document.forms['cerca_form'].Page.value=1\">
					<input type='reset' name='Annulla' value='Annulla'>
				</td>
			</tr>
		</table>
	</form>
";

if (isset ( $_POST ['Cerca'] )) {
	if ($_POST ['PATTERN'] != '') {
		$sql_where_clause="where 
			(USERID like 'SP%' or USERID like '%CRO%') and
		 (UPPER(NOME) like '%".strtoupper($_POST['PATTERN'])."%'
			or UPPER(COGNOME) like '%".strtoupper($_POST['PATTERN'])."%'
			or UPPER(AZIENDA_ENTE) like '%".strtoupper($_POST['PATTERN'])."%')			
		";
		$sql_query="
			select 
			distinct
				USERID, COGNOME, NOME, AZIENDA_ENTE, EMAIL, NAZIONE, VIA, CITTA, PROV, CAP, TELEFONO, FAX
		   from ANA_UTENTI 
		   $sql_where_clause
		   ";
		  //echo "$sql_query";
		$sql=new query($conn);
		$sql->exec($sql_query);
		if ($sql->numrows==0) $body.="<p class=titolo>La ricerca non ha prodotto risultati</p>";
		else {
			$body.="<br><p class=titolo align='left'>Risultati</p>
				<table border=0 cellpadding=0 cellspacing=2 width=400>
			";
		}
		$rpp=10;
		$nrows=$sql->numrows;
		$pages=ceil($nrows/$rpp);
		
		$paging_bar='';
		if ($page!=1){
			$paging_bar.="<a href=\"#\" onclick=\"document.forms['cerca_form'].Page.value=1;document.forms['cerca_form'].submit();return false;\">|&lt;</a>&nbsp;";		
		}
		for ($i=1;$i<=$pages; $i++){
			if ($i==$page) $paging_bar.="<b>$i</b>&nbsp;";
			else {
				$paging_bar.="<a href=\"#\" onclick=\"document.forms['cerca_form'].Page.value=$i;document.forms['cerca_form'].submit();return false;\">$i</a>&nbsp;";
			}
		}
		if ($page!=$pages){
			$paging_bar.="<a href=\"#\" onclick=\"document.forms['cerca_form'].Page.value=$pages;document.forms['cerca_form'].submit();return false;\">&gt;|</a>&nbsp;";		
		}
		$first_row=$rpp*($page-1)+1;
		$last_row=$rpp*($page);
		$sql_query="select * from (
			select t.*, rownum as n_r from ($sql_query) t
		) t1
		where t1.n_r between $first_row and $last_row
		";
		$body.="<p>$paging_bar</p>";
		$sql->exec($sql_query);
		while ($sql->get_row()){			
			$body.="
				<tr>
					<td  class=sc4bis>{$sql->row['AZIENDA_ENTE']} <br> {$sql->row['VIA']} {$sql->row['CAP']} ({$sql->row['PROV']}) - {$sql->row['NAZIONE']}<br> {$sql->row['FAX']} - {$sql->row['EMAIL']} - {$sql->row['TELEFONO']}- {$sql->row['NOME']}- {$sql->row['COGNOME']}</td>
					<td class=sc4bis>
					<input type='button' value=\"&gt;&gt;\" onclick=\"".make_button_link($sql->row)."\">
					</td>
				</tr>					
			";
				
		}
		if ($sql->numrows!=0) $body.="</table><br><br>";
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
  
  $row['AZIENDA_ENTE']=$row1['AZIENDA_ENTE'];
  $row['NAZIONE']=$row1['NAZIONE'];
  $row['VIA']=$row1['VIA'];
  $row['CITTA']=$row1['CITTA'];
  $row['PROV']=$row1['PROV'];
	$row['CAP']=$row1['CAP'];
	$row['TELEFONO']=$row1['TELEFONO'];
	$row['FAX']=$row1['FAX'];
	$row['EMAIL']=$row1['EMAIL'];
	$row['NOME']=$row1['NOME'];
	$row['COGNOME']=$row1['COGNOME'];

	return $row;
}

?>