<?php
include_once "config.inc";

if($_GET['DEBUG']==1) echo "uploadZip.php<br><br>";

if($_FILES["zip_file"]["name"]) {
	$filename = $_FILES["zip_file"]["name"];
	$source = $_FILES["zip_file"]["tmp_name"];
	$type = $_FILES["zip_file"]["type"];
	$id_stud=$_GET['ID_STUD'];
	$center=$_GET['CENTER'];
	$userid=$_GET['USERID'];
	$visitnum=$_GET['VISITNUM'];
	$esam=$_GET['ESAM'];
	$upload_zip=$_GET['UPLOAD_ZIP'];
	$visitnum_progr=$_GET['VISITNUM_PROGR'];
	if(!$visitnum_progr) $visitnum_progr=0;

	$name = explode(".", $filename);
	$accepted_types = array('application/zip', 'application/x-zip-compressed', 'multipart/x-zip', 'application/x-compressed');
	foreach($accepted_types as $mime_type) {
		if($mime_type == $type) {
			$okay = true;
			break;
		} 
	}
	
	$continue = strtolower($name[1]) == 'zip' ? true : false;
	if(!$continue) {
		$message = "The file you are trying to upload is not a .zip file. Please try again.";
	}
	
	#GIULIO DECOMMENTARE QUESTO PERCORSO PER VERIFICARE MANCATA SCRITTURA DEL FILE DA PARTE DI WWWRUN in /uxmr/
	#$target_path = "{$_SERVER['DOCUMENT_ROOT']}/uxmr/".$filename;
	#echo $source."<br>";
	#echo $target_path;
	$target_path = "{$_SERVER['DOCUMENT_ROOT']}/WCA/docs/".$filename;  // change this to the correct site path

	if(move_uploaded_file($source, $target_path)) {
		$zip = new ZipArchive();
		
		$conn=new dbconn();
		
		if ($zip->open($target_path) === true) {
	    for($i = 0; $i < $zip->numFiles; $i++) {
	        $filename = $zip->getNameIndex($i);
	        //echo $filename."<br>";
	        $filename2=str_replace(" ","_",$filename);
	        //echo $filename."<br>";
	        
	        #Estraggo l'estensione
	        $ext = pathinfo($filename, PATHINFO_EXTENSION);
	        $fileinfo = pathinfo($filename);
	        
	        #Recupero l'id da assegnare al documento dalla sequence
	        $doc_id_query="select docs_id.nextval as id_doc from dual";
					$sql=new query($conn);
				  $sql->get_row($doc_id_query);
					$id_doc=$sql->row['ID_DOC'];
	        
	        #Costruisco il nome del file
	        $fileinfo['basename']="Doc_Area".$id_doc.".".$ext;
	        
	        #Copio il documento su FileSystem
	        copy("zip://".$target_path."#".$filename, "{$_SERVER['DOCUMENT_ROOT']}/uxmr/WCA/docs/".$fileinfo['basename']);
	        
	        $max_keywords=getMaxProgrInizio($id_stud,$visitnum,$visitnum_progr,$esam,$conn);
	        
	        $tipo_doc="Doc_Area";
	        $id_area = 1;
	        $id_tipo_ref = $id_stud + (AREA_OFFSET*$id_area);
	        
	        if($max_keywords==0){
		        $sql_delete="delete from ce_coordinate where id_stud=$id_stud and visitnum=$visitnum and visitnum_progr=$visitnum_progr and	esam=$esam and progr=1";
						$sql_del = new query ($conn);
						$sql_del->set_sql($sql_delete);
						$sql_del->ins_upd();
	        }
	        
	        $next_progr=$max_keywords+1;
	        
	        $tab_doc=$doc_field=$tab_doc_cme=$topic=$add_fields=$add_values=$bindedVars=$bindedVars_cme=$bindedVars_doc="";
					if($upload_zip==1){
						$tab_doc="CE_DOCUMENTAZIONE";
						$doc_field="DOC_CORE";
						$tab_doc_cme="CE_DOC_CORE_CME";
						$topic="Core";
						};
					if($upload_zip==2){
						$tab_doc="CE_DOCUM_CENTRO";
						$doc_field="DOC_CENTROSPEC";
						$tab_doc_cme="CE_DOC_CENTRO_CME";
						$topic="Centro Specifica";
						
						$progr_centro=$visitnum_progr+1;
						$sql_info_centro="select * from ce_centrilocali where id_stud=$id_stud and visitnum=0 and visitnum_progr=0 and esam=10 and progr=$progr_centro";
						$sql_ic = new query ($conn);
						$sql_ic->get_row($sql_info_centro);
						$centro=$sql_ic->row['CENTRO'];
						$d_centro=$sql_ic->row['D_CENTRO'];
						$add_fields=",CENTRO,D_CENTRO";
						$add_values=",:centro,:d_centro";
						$bindedVars['centro']=$centro;
						$bindedVars['d_centro']=$d_centro;
					}
					if($upload_zip==3){
						$tab_doc="CE_DOCUM_EME";
						$doc_field="DOC_EMENDAMENTO";
						$tab_doc_cme="CE_DOC_VAL_EME_CME";
						$topic="Emendamento";
						}
	        
	        $kw=$doc_field;
					if ($in['VISITNUM_PROGR']>0 || $next_progr>1) {
						if($in['VISITNUM_PROGR']>0) $kw.="_{$next_progr}_{$in['VISITNUM_PROGR']}";
						else $kw.="_{$next_progr}";
					}
	        
	        $sql_query_user="select nome, cognome from ana_utenti where userid='{$userid}'";
					$sql_nu = new query ($conn);
					$sql_nu->get_row($sql_query_user);
					$autore=$sql_nu->row['NOME']." ".$sql_nu->row['COGNOME'];
	        
	        #Inserimento in DOCS
	        $query_docs="insert into docs(id,ext,userid,id_ref,tipo_doc,data,nome_file,autore,id_tipo_ref,keywords,topic,approved) 
	        										 values(:id,:ext,:userid,:id_ref,:tipo_doc,sysdate,:nome_file,:autore,:id_tipo_ref,:keywords,:topic,:approved)";
	        										 #values('$id_doc','$ext','$userid',$id_doc,'$tipo_doc',sysdate,'{$filename}','$autore','$id_tipo_ref','$kw','$topic','1')";
	        //echo $query_docs."<br>";
	        $sql_docs = new query ($conn);
	        $bindedVars_doc['id']=$id_doc;
	        $bindedVars_doc['ext']=$ext;
	        $bindedVars_doc['userid']=$userid;
	        $bindedVars_doc['id_ref']=$id_doc;
	        $bindedVars_doc['tipo_doc']=$tipo_doc;
	        $bindedVars_doc['nome_file']=$filename2;
	        $bindedVars_doc['autore']=$autore;
	        $bindedVars_doc['id_tipo_ref']=$id_tipo_ref;
	        $bindedVars_doc['keywords']=$kw;
	        $bindedVars_doc['topic']=$topic;
	        $bindedVars_doc['approved']=1;
	        //print_r($bindedVars_doc);
					$sql_docs->ins_upd($query_docs,$bindedVars_doc);
					
			//LUIGI: INIZIO salva-workflow
			$sql_query_coo="select nvl(max(visitclose),0) as MAXVC from ce_coordinate where id_stud=$id_stud and visitnum=$visitnum and visitnum_progr=$visitnum_progr and esam=$esam"; // and esam=1";
			
			$sql_coo=new query($conn);
			$sql_coo->exec($sql_query_coo);
			//echo $sql_query."<br/>";
			if ($sql_coo->get_row()){
				if ($sql_coo->row['MAXVC']==1){
					$visitclose=1;
					$fine=1;
				}
				else{
					$visitclose=0;
					$fine=0;
				}
			}
			//LUIGI: FINE salva-workflow
			
					#Inserimento in COORDINATE
					$query_coord="insert into ce_coordinate(visitnum, visitnum_progr, progr, esam, inizio, fine, insertdt, moddt, userid, visitclose, id_stud, abilitato) 
	        											values('$visitnum', '$visitnum_progr', '$next_progr', '$esam', '1', $fine, sysdate, sysdate, '$userid', $visitclose, '$id_stud', '1')";
	        //echo $query_coord."<br>";
	        $sql_coord = new query ($conn);
	        $sql_coord->set_sql($query_coord);
					$sql_coord->ins_upd();
					
					#Inserimento in tabella documentale
					$query_docum="insert into $tab_doc (id_stud, userid_ins, esam, progr, visitnum, visitnum_progr, center, $doc_field $add_fields)
											  values(:id,:userid,:esam,:progr,:visitnum,:visitnum_progr,:center,:id_doc $add_values)";
											 #values('$id_stud', '$userid', '$esam', '$next_progr', '$visitnum', '$visitnum_progr', '$center', '$id_doc' $add_values)";
	   			//echo $query_docum."<br>";
					$sql_docum = new query ($conn);
					$bindedVars['id']=$id_stud;
					$bindedVars['userid']=$userid;
					$bindedVars['esam']=$esam;
					$bindedVars['progr']=$next_progr;
					$bindedVars['visitnum']=$visitnum;
					$bindedVars['visitnum_progr']=$visitnum_progr;
					$bindedVars['center']=$center;
					$bindedVars['id_doc']=$id_doc;
					//print_r($bindedVars);
					$sql_docum->ins_upd($query_docum,$bindedVars);
				
					
					#Inserimento in tabella metadati cme
					$query_docum_cme="insert into $tab_doc_cme (id_stud, userid_ins, esam, visitnum, visitnum_progr, center, progr, id, id_ref, var_name, topic) 
	        							    values(:id_stud,:userid_ins,:esam,:visitnum,:visitnum_progr,:center,:progr,:id,:id_ref,:var_name,:topic)";
	        							    #values('$id_stud','$userid','$esam','$visitnum','$visitnum_progr','$center','$next_progr','$id_doc','$id_doc','$doc_field','$topic')";
	        //echo $query_docum_cme."<br>";
	        $sql_docum_cme = new query ($conn);
	        $bindedVars_cme['id_stud']=$id_stud;
					$bindedVars_cme['userid_ins']=$userid;
					$bindedVars_cme['esam']=$esam;
					$bindedVars_cme['visitnum']=$visitnum;
					$bindedVars_cme['visitnum_progr']=$visitnum_progr;					
					$bindedVars_cme['center']=$center;
					$bindedVars_cme['progr']=$next_progr;
					$bindedVars_cme['id']=$id_doc;
					$bindedVars_cme['id_ref']=$id_doc;
					$bindedVars_cme['var_name']=$doc_field;
					$bindedVars_cme['topic']=$topic;
					//print_r($bindedVars_cme);
					$sql_docum_cme->ins_upd($query_docum_cme,$bindedVars_cme);
	        
	        
	    }                  
	    $zip->close();                  
		}
		
		//die();
		
		unlink($target_path);
		$conn->commit();
		
		header("Location: index.php?CENTER=$center&ID_STUD=$id_stud&VISITNUM=$visitnum&VISITNUM_PROGR=$visitnum_progr&ESAM=$esam");
		
//		$x = $zip->open($target_path);
//		echo "file estratti:<br>";
//		for ($i = 0; $i < $zip->numFiles; $i++) {
//		  $stat = $zip->statIndex( $i );
//      $tounes = array( basename( $stat['name'] ) . PHP_EOL );
//      foreach($tounes as $toune) {
//      	echo "<li>".$toune."</li>";
//      }
//		 }
//		
//		if ($x === true) {
//			#$zip->extractTo("{$_SERVER['DOCUMENT_ROOT']}/uxmr/"); // change this to the correct site path
//			$zip->close();
//	
//			unlink($target_path);
//		}
//		$message = "Your .zip file was uploaded and unpacked.";
		
		
	} else {	
		$message = "There was a problem with the upload. Please try again.";
	}
}

function getMaxProgrInizio($pkid,$vid,$vprogr,$esam,$conn){
			//echo "getMaxProgrInizio($pkid,$vid,$vprogr,$esam) <br/>";
			$retval = 0;
			//Caricamento xml
			$sql_query="select nvl(max(PROGR),0) as MAXP from ce_coordinate where id_stud={$pkid} and visitnum=$vid and visitnum_progr=$vprogr and esam=$esam and nvl(inizio,0)<>0"; // and esam=1";
			$sql=new query($conn);
			$sql->exec($sql_query);
			//echo $sql_query."<br/>";
			if ($sql->get_row()){
				if (is_numeric($sql->row['MAXP'])){
					$retval = $sql->row['MAXP'];
				}
				//echo $retval."<br/>";
			}	
			//echo $retval."<br/>";
			return $retval;	
		}

?>