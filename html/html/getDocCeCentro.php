<?php 

function error_page($a, $b, $c){
	print_r($a);
	print_r($b);
	print_r($c);
}

function enforceSaferDownload($wantedDir,$finalFile){
    $wantedDir=realpath($wantedDir);
    $finalFile=realpath($finalFile);
    $pos=strpos($finalFile,$wantedDir);
    if($pos===FALSE){
        echo "Bad Request!";
        die();
        return false;
    }
    else {
        return true;
    }
}

include_once "../libs/xCRF/db.inc";

$conn = new dbconn ();

	$sql_studi="select id_stud,progr from ce_centrilocali where CRPMS_CENTER_PROGR=:CRPMS_CENTER_PROGR";
    $bindsup['CRPMS_CENTER_PROGR']=isset($_GET['zip']) ? $_GET['codice'] : $_POST['codice'];
	$query_studi = new query ( $conn );
	$query_studi->get_row($sql_studi, $bindsup);
	$id_stud=$query_studi->row['ID_STUD']; //attenzione corrispondenza non univoca!!
	$progr=$query_studi->row['PROGR'];
	
	
	if($id_stud!="" && $progr!=""){
	$sql_studi="SELECT
  c.doc_centrospec,
  d.ext,
  d.nome_file,
  c.userid_ins,
  c.d_doc_loc,
  c.doc_vers,
  TO_CHAR(c.doc_dt,'DD/MM/YYYY') AS doc_dt,
  c.descr_agg
		FROM
  ce_docum_centro c,
  docs d
		WHERE
                      id_stud=:ID_STUD
                      and c.visitnum_progr=:PROGR-1
  AND d.id =c.doc_centrospec";
        $bindsup=array();
        $bindsup['ID_STUD']=$id_stud;
        $bindsup['PROGR']=$progr;
        $query_studi->exec($sql_studi,$bindsup);
        //var_dump($query_studi);
        //var_dump($bindsup);
        if(!isset($_GET['zip'])||$_GET['zip']!="true") { //TOSCANA-193 download documentazione centro in zip
            print("<table border=1>
                    <tr>
                        <th>Tipologia</th>
                        <th>Descrizione aggiuntiva</th>
                        <th>File</th>
                        <th>Versione</th>
                        <th>Data</th>
                        <th>Inserito da</th>
                    </tr>
            ");
	
            while ($query_studi->get_row()) {
		print("<tr>");
		print ("<td>{$query_studi->row['D_DOC_LOC']}</td>");
		print ("<td>{$query_studi->row['DESCR_AGG']}</td>");
                print ("<td><a target=\"_new\" href=\"/download.php?nome_file={$query_studi->row['NOME_FILE']}&code_file=" . $query_studi->row['DOC_CENTROSPEC'] . "." . $query_studi->row['EXT'] . "\">" . $query_studi->row['NOME_FILE'] . "</a></td>");
		print ("<td>{$query_studi->row['DOC_VERS']}</td>");
		print ("<td>{$query_studi->row['DOC_DT']}</td>");
		print ("<td>{$query_studi->row['USERID_INS']}</td>");
		print("</tr>");
	}
            print ("</table>");

            print ("<br>");
	}
        else{
            /*TOSCANA-193 vmazzeo 06.11.2017 copio da uxmr/getDocCeZipCentro.php*/
            if ($query_studi->numrows!=0) {
                //LUIGI CREO IL FILE ZIP RINOMINANDO IL CONTENUTO	
                $zip = new ZipArchive();
                $filename = "./WCA/docs/zipCentro_{$bindsup['ID_STUD']}_{$bindsup['PROGR']}_CRMS.zip";

                if ($zip->open($filename, ZipArchive::CREATE)!==TRUE) {
                    exit("cannot open <$filename>\n");
                }
	
                while ($query_studi->get_row()){
                    $zip->addFile("./WCA/docs/Doc_Area".$query_studi->row['DOC_CENTROSPEC'].".".$query_studi->row['EXT'] , $query_studi->row['NOME_FILE']);
                    print("./WCA/docs/Doc_Area".$query_studi->row['DOC_CENTROSPEC'].".".$query_studi->row['EXT']);
                    print ("<br>");
                    print($query_studi->row['NOME_FILE']);
                    print ("<br>");
	print ("<br>");
                }

                $zip->close();

                echo $filename;



                $wantedDir="./WCA/docs/";
                $dir=$filename;
                $nome_file="zipCentro_{$bindsup['ID_STUD']}_{$bindsup['PROGR']}_CRMS.zip";

                enforceSaferDownload($wantedDir,$dir);

                //LUIGI SCARICO IL FILE
                header("Content-type:application/zip;\n");
                header("Content-Transfer-Encoding: Binary");
                header("Content-Disposition: attachment; filename=".$nome_file);

                ob_clean();
                ob_end_flush();
                readfile($dir);

                exit;

            } else {
                echo "<font size=\"5px\">File zip non generato! <br> Non è stato inserito nessun file nella documentazione generale";
                echo "<br><br> <a href=\"#\" onclick=\"history.back()\">&lt;&lt;Torna alle schede dello studio</a></font>";
            }
        }
	//print ("<p>codice crpms: {$_POST['codice']} </p>");
	//print ("<p>codice ceveneto: {$id_stud} </p>");
    }
?>