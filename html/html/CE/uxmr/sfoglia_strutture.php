<?
include_once "config.inc";

$conn = new dbconn ( );

$page = $_POST ['Page'];
if ($page == '')
	$page = 1;

$body = "
<p class=titolo>Ricerca:</p>
	<form method=\"POST\" name='cerca_form'>
		<table border=0 cellpadding=0 cellspacing=0>
			<tr>
				<td align=left>Codice struttura
				</td>
				<td><input type='text' name='ID_STRUT' value='{$_POST['ID_STRUT']}'>
				</td>
			</tr>
			<tr>
				<td align=left>Denominazione struttura
				</td>
				<td><input type='text' size=40  name='DENOM' value='{$_POST['DENOM']}'>
				</td>
			</tr>
			<tr>
				<td colspan=2 align=center>
					<input type='hidden' name='Page' value='$page'>
					<input type='hidden' name='Cerca' value='yes'>
					<input type='submit' name='Cerca1' value='Cerca' onclick=\"document.forms['cerca_form'].Page.value=1\">
					<input type='reset' name='Annulla' value='Annulla'>
				</td>
			</tr>
		</table>
	</form>
	<br>
	<br>
";

if (isset ( $_POST ['Cerca'] )) {
	if ($_POST ['ID_STRUT'] != '' || $_POST ['DENOM'] != '') {
		if ($_POST ['ID_STRUT'] != '') {
			$pattern = $_POST ['ID_STRUT'];
			$pattern = str_replace ( "'", "''", $pattern );
			$pattern = strtoupper ( $pattern );
			$sql_where [count ( $sql_where )] = "upper(ID_STRUT) like '%$pattern%'";
		}
		if ($_POST ['DENOM'] != '') {
			$pattern = $_POST ['DENOM'];
			$pattern = str_replace ( "'", "''", $pattern );
			$pattern = strtoupper ( $pattern );
			$sql_where [count ( $sql_where )] = "upper(DENOM_STRUTT) like '%$pattern%'";
		}
		$sql_where_clause="";
		foreach ($sql_where as $key=>$val){
			if ($sql_where_clause!='') $sql_where_clause.=" and ";
			$sql_where_clause.=$val;
		}
		$sql_where_clause="where ".$sql_where_clause;
		
		$sql_query="select distinct ID_STRUT, DENOM_STRUTT,INDIRIZZO||' - '||CAP||' '||COMUNE as INDIRIZZO_CENTRO from farmaci_bduf.strutture_ossc $sql_where_clause";
		$sql=new query($conn);
		$sql->exec($sql_query);
		//echo $sql_query;
		if ($sql->numrows==0) $body.="<p class=titolo>La ricerca non ha prodotto risultati</p>";
		else {
			$body.="<p class=titolo>Risultati</p>
				<table border=0 cellpadding=0 cellspacing=2 width='400px'>
					
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
						<td class=int>
							Codice Struttura
						</td>
						<td class=int>
							Denominazione Struttura
						</td>
						<td class=int>
							Seleziona
						</td>
					</tr>";			
			$body.="
					<tr>
						<td class=sc4bis>{$sql->row['ID_STRUT']}</td>
						<td class=sc4bis>{$sql->row['DENOM_STRUTT']}</td>
						<td class=sc4bis align='center'>
							<input type='button' value=\"&gt;&gt;\" onclick=\"".make_button_link($sql->row)."\">
						</td>
					</tr>
				";
				
//				$sql_query_2=" select s.*,INDIRIZZO||' - '||CAP||' '||COMUNE as INDIRIZZO_CENTRO from farmaci_bduf.strutture_ossc s $sql_where_clause and id_strut='{$sql->row['ID_STRUT']}'";
//				//$sql_query_2=" select s.*,INDIRIZZO||' - '||CAP||' '||COMUNE as INDIRIZZO_CENTRO from strut_ce_ossc s $sql_where_clause and id_strut='{$sql->row['ID_STRUT']}'";
//				
//				$sql2=new query($conn);
//				$sql2->exec($sql_query_2);
//				if ($sql2->numrows>0){
//					$body.="
//					<tr>
//						<td class=int>
//							Denominazione Comitato Etico
//						</td>
//						<td class=int>
//							Seleziona
//						</td>
//					</tr>";				
//				}
//				while ($sql2->get_row()){
//					
//					//Se viene selezionata un'ASL e la tipologia e' MMG/PLS o MISTA -> devo mostrare la textarea ELENCO_MMG_PLS
//					if (preg_match("!ASL!i",$sql2->row['ID_STRUT'])) $sql2->row['IS_ASL']=1;
//					else $sql2->row['IS_ASL']=0;
//					
//					$body.="
//					<tr>
//						<td  class=sc4bis>{$sql2->row['DENOMINAZIONE']}</td>
//						<td class=sc4bis>
//						<input type='button' value=\"&gt;&gt;\" onclick=\"".make_button_link($sql2->row)."\">
//						</td>
//					</tr>					
//					";
//				}
				$body.="
				<tr height='20px'>
				</tr>
				";
		}
		if ($sql->numrows!=0) $body.="</table>";
	} else {
		
	}
}

$filetxt = str_replace ( "<!--body-->", $body, $filetxt );

die ( $filetxt );

function make_button_link($row){
	$row=make_row($row);
	//print_r($row);
	foreach ($_GET as $key => $val){
		$row[$key]=str_replace("'", "\\'", $row[$key]);
		$row[$key]=str_replace("\"", "\\'", $row[$key]);
		$js.="window.opener.document.forms[0].{$val}.value='{$row[$key]}';\n";
	}
	$js.="
	window.opener.cf();  //funzione che controlla le condizioni
	window.close();";
	return $js;
	
}

function make_row($row1){
	
	//$row['INDIRIZZO_CENTRO']=$row1['INDIRIZZO_CENTRO'];
	$row['DENOM_STRUTT']=$row1['DENOM_STRUTT'];
	$row['ID_STRUT']=$row1['ID_STRUT'];
	//$row['CE_USERID']=$row1['USERID'];
	//$row['CE_DENOM']=$row1['DENOMINAZIONE'];
	//$row['IS_ASL']=$row1['IS_ASL'];
	return $row;
}

?>