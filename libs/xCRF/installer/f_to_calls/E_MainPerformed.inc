<?php

$ftc_name="MainPerformed";
$ftc_description="To be called by a main form to enable the main-sub feature. The main form <u>must</u> include the <b>main_field</b>, <b>main_field_value</b> and <b>table_sub</b> to function properly.";

/**
 * per le form laboratory_main_v1.xml e laboratory_main.xml esiste una domanda chiave “Was the examination performed?” (LBM. LBPERF) che influenza la form successiva.

Infatti se risponde “Yes”, rimane tutto com’è adesso quindi si deve cliccare sul pulsante”Continue ” il quale farà solo un save e andrà alla form_sub,

mentre se risponde “No”  dovrà fare il send dei dati e il link_to alla lista degli esami.
 *
 * 
 * @return sql op
 */
function MainPerformed($xml_form ){
	global $in;
	global $conn;
	global $service;
	global $lang;
	
	$sub_esam=$in['ESAM']+1;
	$sub_table=$xml_form->form['TABLE_SUB'];
	
	if( !$in['ajax_call']){
	
		 if($in[$xml_form->form['MAIN_FIELD']]!=$xml_form->form['MAIN_FIELD_VALUE']){
		 	/**
		 	* Risposta alla Domanda principale che si cerca di inserire: no. La main e la sub devono essere nella stessa visita e deveono essere consecutivi.
		 	 1- Controllo se in banca dati aveva salvato yes :  Quindi ora vuole passare a no.  Ma aveva salvato delle sub .
		 	 2- Se vuole passare a no nelle sub non ci devono essere esami. (a meno che non siano  sotto eQ , pending o solved)
		 	  -->	 and {$service}_sub.progr not in (select progr from {$service}_eqfield where codpat={$in['CODPAT']}  and esam={$sub_esam} and visitnum={$in['VISITNUM']} group by progr)	<--
		 	  e a meno che non siano stati cancellati , ovvero abilitato = 2 in coordinate:
		 	  -->  and {$service}_sub.progr not in ( select progr from {$service}_coordinate where codpat={$in['CODPAT']} and esam={$sub_esam} and visitnum={$in['VISITNUM']} and abilitato = 2)";  <--
		 	*/
		 	if($lang=='en'){
				$confirm_skip="Please, click yes and delete records using the trash icon.";
			}
			else{
				$confirm_skip="Cliccare si e cancellare i record usando l'icona del cestino.";
			}
			
			$sql_maintb_exist="
				select count(*) as CONTO from user_tables  where table_name='{$service}_{$sub_table}' ";
	//			 echo $sql_maintb_exist;
				$sql2=new query($conn);
				$sql2->set_sql($sql_maintb_exist);
				$sql2->exec();
				$sql2->get_row();
	//			echo $sql2->row['CONTO'];
	
				if($sql2->row['CONTO']==1){
					
				 	$sql2=new query($conn);
					$sql_check="select count(*) as CONTO  from {$service}_{$sub_table}  where {$service}_{$sub_table}.codpat={$in['CODPAT']} and {$service}_{$sub_table}.visitnum={$in['VISITNUM']}
						and {$service}_{$sub_table}.progr not in (select progr from {$service}_eqfield where codpat={$in['CODPAT']}  and esam={$sub_esam} and visitnum={$in['VISITNUM']} group by progr)
						and {$service}_{$sub_table}.progr not in ( select progr from {$service}_coordinate where codpat={$in['CODPAT']} and esam={$sub_esam} and visitnum={$in['VISITNUM']} and abilitato = 2)";
					$sql2->set_sql($sql_check);
					$sql2->exec();
					$sql2->get_row();
			//		echo "<hr>--";echo $sql2->row['CONTO']; echo "--<hr>";
			//		echo $sql_check; die();
					if($sql2->row['CONTO']>0){
						if( $in['ajax_call']!=''){
								echo "Error:#error#";
								die($confirm_skip);
						}
			//			header("location: index.php?CODPAT={$in['CODPAT']}&CENTER={$in['CENTER']}&VISITNUM=50&ESAM=2&form=training2.xml");
					}
					else{
				 		$sql3=new query($conn);
				 		$pk='';
						$vals['FINE']=1;
						$pk['ESAM']=$in['ESAM'];
						$pk['VISITNUM']=$in['VISITNUM'];
						$pk['VISITNUM_PROGR']=$in['VISITNUM_PROGR'];
						$pk['PROGR']=$in['PROGR'];
						$pk['CODPAT']=$in['CODPAT'];
						$sql3->update($vals, $service."_COORDINATE",$pk);	
						
						$pk['ESAM']=$in['ESAM']+1;
						$sql3->update($vals, $service."_COORDINATE",$pk);	
						$conn->commit();
						header("location: index.php?CODPAT={$in['CODPAT']}&CENTER={$in['CENTER']}&exams=visite_exams.xml");
					}
				}
		 }
		 else{
	//	 	global $vlist;
	//	 	print_R($vlist);die();
	//	 	header("location: index.php?CODPAT={$in['CODPAT']}&CENTER={$in['CENTER']}&VISITNUM={$in['VISITNUM']}&ESAM={$sub_esam}&form=training2.xml");
		 	return;
		 }
	}
}

?>