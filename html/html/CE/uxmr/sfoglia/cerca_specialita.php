<?
include_once "config.inc";

$debug=$_GET{'DEBUG'};

$conn = new dbconn ( "farmaci_bduf", "sibdfc1$", "farmaci_prod" );

$page = $_POST ['Page'];
if ($page == '')
	$page = 1;

$body = "
	<form method=\"POST\" name='cerca_form'>
		<table border=0 cellpadding=0 cellspacing=0 align=center>
			<tr>
				<td align=right>Specialit&agrave; medicinale
				</td>
				<td><input type='text' size=40 name='SPECIALITA' value='{$_POST['SPECIALITA']}'>
				</td>
			</tr>
			<tr>
				<td align=right>AIC
				</td>
				<td><input type='text' name='AIC' value='{$_POST['AIC']}'>
				</td>
			</tr>
			<tr>
				<td align=right>Titolare AIC
				</td>
				<td><input type='text' size=40 name='TIT_AIC' value='{$_POST['TIT_AIC']}'>
				</td>
			</tr>
			<tr>
				<td align=right>Principio attivo
				</td>
				<td><input type='text'size=30 name='PRINC_ATT' value='{$_POST['PRINC_ATT']}'>
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
";

if (isset ( $_POST ['Cerca'] )) {
	if ($_POST ['SPECIALITA'] != '' || $_POST ['AIC'] != '' || $_POST ['TIT_AIC'] != '' || $_POST ['PRINC_ATT'] != '') {
		if ($_POST ['SPECIALITA'] != '') {
			$pattern = $_POST ['SPECIALITA'];
			$pattern = str_replace ( "'", "''", $pattern );
			$pattern = strtoupper ( $pattern );
			$sql_where [count ( $sql_where )] = "upper(specialita) like '%$pattern%'";
		}
		if ($_POST ['AIC'] != '') {
			$pattern = $_POST ['AIC'];
			$pattern = str_replace ( "'", "''", $pattern );
			$pattern = strtoupper ( $pattern );
			$sql_where [count ( $sql_where )] = "upper(aic_spec) like '%$pattern%'";
		}
		if ($_POST ['TIT_AIC'] != '') {
			$pattern = $_POST ['TIT_AIC'];
			$pattern = str_replace ( "'", "''", $pattern );
			$pattern = strtoupper ( $pattern );
			$sql_where [count ( $sql_where )] = "upper(ditta) like '%$pattern%'";
		}
		if ($_POST ['PRINC_ATT'] != '') {
			$pattern = $_POST ['PRINC_ATT'];
			$pattern = str_replace ( "'", "''", $pattern );
			$pattern = strtoupper ( $pattern );
			$sql_where [count ( $sql_where )] = "upper(dsost) like '%$pattern%'";
		}
		$sql_where_clause="";
		foreach ($sql_where as $key=>$val){
			if ($sql_where_clause!='') $sql_where_clause.=" and ";
			$sql_where_clause.=$val;
		}
		$sql_where_clause="where ".$sql_where_clause;
				
		$sql_query="select distinct (case
                  when spec is not null then
                   aic_spec
                  else
                   minsan10
                end) aic_minsan,
                case
                  when spec is not null then
                   spec
                  else
                   specialita
                end spec_specialita,
                atc,
                ditta
  from farmaci_sfoglia
 $sql_where_clause ";
		//echo $sql_query;
		//$sql_query="select distinct codice_farmaco, denominazione, descr, codice_atc, datc, descrizione1 from farmaci_osserv $sql_where_clause";
		if ($_GET{'DEBUG'}) echo "<br>$sql_query" ;
		$sql=new query($conn);
		$sql->exec($sql_query);
		if ($sql->numrows==0) $body.="<p class=titolo>La ricerca non ha prodotto risultati</p>";
		else {
			$body.="<p class=titolo>Risultati</p>
				<table border=0 cellpadding=0 cellspacing=2 align=center>
					
			";
		}
		$rpp=150;
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
		$body.="<center>$paging_bar</center>";
		if ($_GET{'DEBUG'}) echo "<br>$sql_query" ;
		$sql->exec($sql_query);
		while ($sql->get_row()){
			
					$body.="
					<tr>
						<td class=int>
							AIC (6 cifre)
						</td>
						<td class=int>
							Specialit&agrave;
						</td>
						<td class=int>
							ATC
						</td>
						<td class=int>
							Ditta
						</td>
						<td class=int>
							Seleziona
						</td>
					</tr>";
					
		 $sql_query_4=" select atc, datc, inn, length(atc) livello from atc_sfoglia where atc='{$sql->row['ATC']}'";		
		 $sql4=new query($conn);
		 $sql4->exec($sql_query_4);
		 $sql4->get_row();
		 #echo $sql4->row['DATC'];
		 $sql->row['DATC']=$sql4->row['DATC'];

			$body.="
					<tr>
						<td class=sc4bis>{$sql->row['AIC_MINSAN']}</td>
						<td class=sc4bis>{$sql->row['SPEC_SPECIALITA']}</td>
						<td class=sc4bis>{$sql->row['ATC']}</td>
						<td class=sc4bis>{$sql->row['DITTA']}</td>
						<td class=sc4bis><input type='button' value=\"&gt;&gt;\" onclick=\"".make_button_link($sql->row)."\"></td>
					</tr>
				";
				$sql_query_2=" select ditta,cod_dtt1,aic_spec,aic_conf,spec,specialita,atc,dsost,sostanza from farmaci_sfoglia $sql_where_clause and aic_spec='{$sql->row['AIC_MINSAN']}' and atc='{$sql->row['ATC']}'";
		    
				#echo "<br>$sql_query_2" ;
				$sql2=new query($conn);
				$sql2->exec($sql_query_2);
				if ($sql2->numrows>0){
					$body.="
					<tr>
						<td class=int style=\"background-color:silver\">
							AIC Confezione
						</td>
						<td class=int style=\"background-color:silver\">
							Descrizione confezione
						</td>
						<td class=int style=\"background-color:silver\">
							ATC
						</td>
						<td class=int style=\"background-color:silver\">
							Ditta
						</td>
						<td class=int style=\"background-color:silver\">
							&nbsp;
						</td>
					</tr>";				
				}
				while ($sql2->get_row()){
					
					$sql_query_3=" select atc, datc, inn, length(atc) livello from atc_sfoglia where atc='{$sql->row['ATC']}'";
					$sql3=new query($conn);
				  $sql3->exec($sql_query_3);
				  $sql3->get_row();
				  
				  $sql2->row['DATC']=$sql3->row['DATC'];
				  $sql2->row['INN']=$sql3->row['INN'];
				  $sql2->row['LIVELLO']=$sql3->row['LIVELLO'];
				
				
					$body.="
					<tr>
						<td  class=sc4bis>{$sql2->row['AIC_SPEC']}{$sql2->row['AIC_CONF']}</td>
						<td  class=sc4bis>{$sql2->row['SPEC']} ({$sql2->row['SPECIALITA']})</td>
						<td  class=sc4bis>{$sql2->row['ATC']}</td>
						<td  class=sc4bis>{$sql2->row['DITTA']}</td>
						<td class=sc4bis><input type='button' value=\"&gt;&gt;\" onclick=\"".make_button_link($sql2->row)."\"></td>
					</tr>					
					";
				}
		}
		if ($sql->numrows!=0) $body.="</table>";
	} 
}

$filetxt = str_replace ( "<!--body-->", $body, $filetxt );
die ( $filetxt );

function make_button_link($row){
	$row=make_row($row);
	foreach ($_GET as $key => $val){
		$row[$key]=str_replace("'", "\\'", $row[$key]);
		$js.="window.opener.document.forms[0].{$val}.value='{$row[$key]}';\n";
	}
	$js.="window.close();";
	return $js;
	
}

function make_row($row1){
	$row['ATC']=$row1['ATC'];
	$row['DATC']=$row1['DATC'];
	$row['ATC_INN']=$row1['INN'];
  $row['ATC_LIVELLO']=$row1['LIVELLO'];
	$row['SPECIALITA']=$row1['SPEC'];
	$row['PRINC_ATT']=$row1['DSOST'];
	$row['COD_PRINC_ATT']=$row1['SOSTANZA'];
	$row['TIT_AIC']=$row1['DITTA'];
	$row['COD_TIT_AIC']=$row1['COD_DTT1'];
	$row['CONFEZIONE']=$row1['SPECIALITA'];
	$row['AIC'].=$row1['AIC_CONF'];
	return $row;
}

?>