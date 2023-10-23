<?php
    header('Content-type: application/json');
    
    include("../uxmr/libs/db_wl.inc");
    
    function error_page(){
        Logger::trace('debug');
    }
    $conn=new dbconn();
    $query=new query($conn);
    $bind['term']=$_GET['term'];
   
    if($_POST['new']){
    	$select="select nvl(max(codice),0) CODICE from EXT_PRESTAZIONI where CODICE like 'ALTRO%'";
        $query->get_row($select);
        $codice=explode('_',$query->row['CODICE']);
        $new_code='ALTRO_'.($codice[1]+1);
        $insert['CODICE']=$new_code;
        $insert['CEP']=$new_code;
        $insert['CEP_DESCRIZIONE']=$_POST['Prestazioni_CDC'];
        $insert['PRESTAZIONE']=$_POST['Prestazioni_prestazione'];
		$insert['UO_CODE']=$new_code;
		$insert['UO']=$_POST['Prestazioni_CDC'];
        $query->insert($insert,'EXT_PRESTAZIONI');
        $conn->commit();
        echo '{"status":"OK"}';
        die();
    }
    else if(isset($_GET['prestazione'])){
        $bind['prestazione']=$_GET['prestazione'];
        $output='{"id":"0","label":"PI"},{"id":"99","label":"CTO/TFA"},{"id":"98","label":"Comitato Etico"},{"id":"1","label":"Farmacia"},{"id":"2","label":"Radiologia"},{"id":"3","label":"Neuroradiologia"},{"id":"4","label":"Medicina di laboratorio"},{"id":"5","label":"Anatomia patologica"},{"id":"6","label":"Istologia e citodiagnosi"},{"id":"7","label":"Immunotrasfusionale"},{"id":"8","label":"Genetica medica"},{"id":"9","label":"Malattie infettive"},{"id":"10","label":"Servizio infermieristico"},{"id":"11","label":"Endocrinologia"},{"id":"12","label":"Neurologia"},{"id":"13","label":"Oculistica"},{"id":"14","label":"Cardiologia"},{"id":"15","label":"Ematologia"},{"id":"16","label":"Nessun servizio"},{"id":"17","label":"Medicina nucleare"},{"id":"18","label":"Chirurgia"},{"id":"19","label":"Radioterapia"},{"id":"20","label":"Endoscopia"},{"id":"21","label":"Oncologia Medica"},{"id":"22","label":"Medicina Interna 1"},{"id":"23","label":"Emodinamica"},{"id":"24","label":"Patologia Clinica"},{"id":"25","label":"Microbiologia e Virologia"},{"id":"26","label":"Radiologia Dea"},{"id":"27","label":"Laboratorio Di Analisi Chimico Cliniche (Urgenze)"},{"id":"28","label":"Pronto Soccorso e Medicina di Urgenza"},{"id":"29","label":"Farmacia Oncologica e Clinica"},{"id":"30","label":"Diabetologia"},{"id":"31","label":"Nefrologia"},{"id":"32","label":"Radiodiagnostica"},{"id":"33","label":"Laboratorio di analisi chimico cliniche"},{"id":"34","label":"Urologia"},{"id":"35","label":"Anestesia e Rianimazione"},{"id":"36","label":"Centro Multidisciplinare Chirurgia Robotica"},{"id":"37","label":"Psichiatria"},{"id":"38","label":"Medicina d\'Urgenza"},{"39":"Centro di Farmacologia Clinica per la Sperimentazione dei Farmaci"}';
    }else{
        $select="select distinct codice,substr(codice||' - '||prestazione,1,100) as PRESTAZIONE,tariffa_ssn,TARIFFA from EXT_PRESTAZIONI where lower(prestazione) like '%'||lower(:term)||'%'  or lower(codice) like '%'||lower(:term)||'%' ";
        $query->exec($select,$bind);
    
        while($query->get_row()){
            $output.='{"id":"'.$query->row['CODICE'].'","label":"'.str_replace("\r","",$query->row['PRESTAZIONE']).'","value":"'.$query->row['PRESTAZIONE'].'","ssn":"'.$query->row['TARIFFA_SSN'].'", "solvente":"'.$query->row['TARIFFA'].'","dizionario":"1"},';
        }
    }
   
    $output=rtrim($output,',');
    $output="[{$output}]";
    echo $output;
    
?>
