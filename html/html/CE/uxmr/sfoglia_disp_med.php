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
			<td width='50px'>
			</td>
				<td align='left'>Cerca Dispositivo Medico: &nbsp;&nbsp;</td>
				<td><input type='text' name='PATTERN' value='{$_POST['PATTERN']}' placeholder=\"Dispositivo\">
				</td>
			</tr>
			<tr>
			<td width='50px'>
			</td>
				<td colspan=2 align='center'>
					<input type='hidden' name='Page' value='$page'>
					<input type='hidden' name='Cerca' value='yes'>
					
					<!--input type='submit' name='Cerca1' value='Cerca' onclick=\"document.forms['cerca_form'].Page.value=1\"-->
					<!--input type='reset' name='Annulla' value='Annulla'-->
					
					<button title=\"Cerca Dispositivo Medico in Banca Dati\" name=\"Cerca1\" id=\"button-search\" class=\"btn btn-purple btn-sm\" type=\"submit\" onclick=\"document.forms['cerca_form'].Page.value=1\">
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
		$sql_where_clause="where UPPER(DENOMINAZIONE_COMMERCIALE) like '%".strtoupper($_POST['PATTERN'])."%'";
		$sql_query="
			select 
			distinct
				tipo,progressivo_dm_ass,data_prima_pubblicazione,dm_riferimento,gruppo_dm_simili,iscrizione_repertorio,inizio_validita,fine_validita,
				fabbricante_assemblatore,codice_fiscale,partita_iva_vatnumber,codice_catalogo_fabbr_ass,denominazione_commerciale,classificazione_cnd,descrizione_cnd,datafine_commercio
		   from DISPOSITIVI_MEDICI 
		   $sql_where_clause
		   ";
		  if($in['DEBUG']==1) echo "$sql_query";
		$sql=new query($conn);
		$sql->exec($sql_query);
		$body.="<div style=\"margin-bottom: 0px;\">";
		if ($sql->numrows==0) $body.="
		<br>
		<table class=\"table table-striped table-bordered table-hover\" width=\"95%\" border=\"0\" align=\"center\">
					<tr>
						<td>La ricerca non ha prodotto risultati</td>
					</tr>
			</table>";
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
						<th>Denominazione</th>
						<th style=\"text-align:center;\" >Inserisci</th>
					</tr>
				</thead>";
		while ($sql->get_row()){			
			$body.="
				<tr>
					<td  class=sc4bis>{$sql->row['DENOMINAZIONE_COMMERCIALE']} <br> {$sql->row['FABBRICANTE_ASSEMBLATORE']} <br> ({$sql->row['CODICE_CATALOGO_FABBR_ASS']})</td>
					<td class=sc4bis>
					<!--input type='button' value=\"&gt;&gt;\" onclick=\"".make_button_link($sql->row)."\"-->
					<button title=\"Inserisci dispositivo allo studio\" id=\"button-search\" class=\"btn btn-purple btn-sm\" type=\"submit\" onclick=\"".make_button_link($sql->row)."\">
								<i class=\"fa fa-plus\"></i>
							</button>
					
					</td>
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
  
  $row['DISPOSITIVO']=$row1['DENOMINAZIONE_COMMERCIALE'];
  $row['DITTA_PROD']=$row1['FABBRICANTE_ASSEMBLATORE'];
  $row['DESC_CARATT']=$row1['DENOMINAZIONE_COMMERCIALE'];
  $row['CLASSIFICAZIONE_CND']=$row1['CLASSIFICAZIONE_CND'];
  $row['DESCRIZIONE_CND']=$row1['DESCRIZIONE_CND'];
	return $row;
}

?>