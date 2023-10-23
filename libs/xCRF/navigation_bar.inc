<?
include_once "study_prototype.inc";

/**
 * @package Hyper
 *
 *  Tale libreria crea una barra di navigazione sui pazienti , mantenendo fisso l'esame che si sta guardando.
 * In questo modo si evita di tornare alla patients_list per cambiare paziente.
 * Il risultato  la generazione di una tabella html con i link ai pazienti succesivo,precedente,primo e ultimo.
 */
class navigation_bar
{
    /**
     * Costruttore dell'oggetto, vengono presi in ingresso le informazione relative alla
     * connessione oracle, al prefisso in banca dati del serviio, alle configurazioni di sistema,
     * e all'array multiplo $vlist contenente lo schema delle form xml, degli esami e delle visite dello studio.
     *
     * @param String $service
     * @param dbconn_hyper $conn
     * @param array $config_service
     * @param array $vlist
     *
     * @return navigation_bar
     */
    function navigation_bar($service = null, $conn = null, $config_service, $vlist)
    {
        /*Costruttore dell'oggetto, engono presi in ingresso le informazione relative alla
         * connessione oracle, al prefisso in banca dati del serviio, alle configurazioni di sistema,
         * e all'array multiplo $vlist contenente lo schema delle form xml, degli esami e delle visite dello studio. */
        $this->conn = $conn;
        $this->service = $service;
        $this->config_service = $config_service;
        $this->vlist = $vlist;
    }

    /**
     * Viene eseguita una query in DB per prendere il codpat successivo a quello attuale, presente nell'URL, quindi nela $in
     * Viene eseguita una query in DB per prendere il primo e l'ultimo codpat registrati con gli esami abilitati, quindi nella tabella coordinate.
     * Vengono costruiti due array: uno per le visite ed uno per gli esami partendo dall'oggetto vlist. Tali array hano gli stessi indici
     * in modo da collegare esami e visite.
     * Viene poi fatto un doppio ciclo per valorizzare gli indici precedente e successivo dell'esame e della visita precedenti e successivi a
     * quelli correnti presenti nella $in.
     * Viene preso il nome del file della form corrente, esso rester fisso: a variare sar il codice del paziente
     * A seconda che ci si trovi all'interno di una form o al livello superiore (vista degli esami del paziente)
     * viene fatto variare il codpat. In questo caso non si avr bisogno della variabile $form.
     * Si va a creare i link per i vari casi in cui si vogliano andare (paziente successivo, precedente etc..)
     * Viene creata la tabella html con i link relativi e assegnata ad una variabile. Tale variabile
     * sar l'output del metodo navigation_bar_html($in).
     * Viene creata la tabella html con i link relativi e assegnata ad una variabile. Tale variabile
     * sar l'output del metodo navigation_bar_html($in).
     * @param array $in
     *
     * @return $nav_bar
     */
    function navigation_bar_html($in = null)
    {
        $next_esam_lnk = null;
        $prev_esam_lnk = null;
        $debug = null;
        /*Viene eseguita una query in DB per prendere il codpat successivo a quelo attuale, presente nell'URL, quindi nela $in*/
        $sql_query = "
		select  min(codpat) as next
		  from {$this->service}_coordinate 
		  where codpat > {$in['CODPAT']}
		  and substr(userid,0,3)={$in['CENTER']}		
		 ";
        $sql = new query($this->conn);
        $sql->set_sql($sql_query);
        $sql->exec();
        $sql->get_row();
        $next_pat = $sql->row['NEXT'];
        /*Viene eseguita una query in DB per prendere il codpat precedente a quelo attuale, presente nell'URL, quindi nela $in*/
        $sql_query = "
		select  max(codpat) as prev
		  from {$this->service}_coordinate 
		  where codpat < {$in['CODPAT']}
		  	and substr(userid,0,3)={$in['CENTER']}	
		 ";
        $sql = new query($this->conn);
        $sql->set_sql($sql_query);
        $sql->exec();
        $sql->get_row();
        $prev_pat = $sql->row['PREV'];
        /*Viene eseguita una query in DB per prendere il primo e l'ultimo codpat registrati con gli esami abilitati, quindi nella tabella coordinate.*/
        $sql_query = "
		select  max(codpat) as last , min(codpat) as first 
		  from {$this->service}_coordinate 
		  	where substr(userid,0,3)={$in['CENTER']}	
		 ";
        $sql = new query($this->conn);
        $sql->set_sql($sql_query);
        $sql->exec();
        $sql->get_row();
        $first_pat = $sql->row['FIRST'];
        $last_pat = $sql->row['LAST'];

        /*
         * Vengono costruiti due array: uno per le visite ed uno per gli esami partendo dall'oggetto vlist. Tali array hano gli stessi indici
         * in modo da collegare esami e visite.
         * Viene poi fatto un doppio ciclo per valorizzare gli indici precedente e successivo dell'esame e della visita precedenti e successivi a
         * quelli correnti presenti nella $in.
         */
        $i = 0;
        $j = 0;
//		print_r($this->vlist->esams);
        foreach ($this->vlist->visitnums as $key => $val) {

            foreach ($this->vlist->esams[$key] as $k => $v) {
//				print_r($this->vlist->visitnums[$key]['NUMBER']);
                $esams[$i] = $this->vlist->esams[$key][$k]['NUMBER'];
                $visitnums[$i] = $this->vlist->visitnums[$key]['NUMBER'];
                if ($this->vlist->esams[$key][$k]['NUMBER'] == $in['ESAM'] && $this->vlist->visitnums[$key]['NUMBER'] == $in['VISITNUM']) {
//						print_r($i);
                    $next_idx = $i + 1;
                    $prev_idx = $i - 1;
//						echo $next_idx;


                }
                $i++;
            }
        }
        if ($this->vlist->esams[$visitnums[$next_idx]][$esams[$next_idx]]['SUB'] == "yes") {
            $next_idx++;
        }
        if ($this->vlist->esams[$visitnums[$prev_idx]][$esams[$prev_idx]]['SUB'] == "yes") {
            $prev_idx--;
        }

        $next_esam = $esams[$next_idx];
        $next_visit = $visitnums[$next_idx];
        $next_form = $this->vlist->esams[$next_visit][$next_esam]['XML'];
        $prev_esam = $esams[$prev_idx];
        $prev_visit = $visitnums[$prev_idx];
        $prev_form = $this->vlist->esams[$prev_visit][$prev_esam]['XML'];

//		$debug=1;
        if ($debug == 1) {
            echo "Array costruito con le visite :<br>";
            echo "<pre>";
            print_r($visitnums);
            echo "</pre>";
            echo "Array costruito con gli esami :<br>";
            echo "<pre>";
            print_r($esams);
            echo "</pre>";
            echo "Indice precedente :<br>";
            echo "<pre>";
            print_r($prev_idx);
            echo "</pre>";
            echo "Visita precedente :<br>";
            echo "<pre>";
            print_r($prev_visit);
            echo "</pre>";
            echo "Esame precedente :<br>";
            echo "<pre>";
            print_r($prev_esam);
            echo "</pre>";
            echo "Form precedente :<br>";
            echo "<pre>";
            print_r($prev_form);
            echo "</pre>";
            echo "Indice successivo :<br>";
            echo "<pre>";
            print_r($next_idx);
            echo "</pre>";
            echo "Visita successiva :<br>";
            echo "<pre>";
            print_r($next_visit);
            echo "</pre>";
            echo "Esame successivo :<br>";
            echo "<pre>";
            print_r($next_esam);
            echo "</pre>";
            echo "Form successiva :<br>";
            echo "<pre>";
            print_r($next_form);
            echo "</pre>";
        }


        /*Prendo il nome del file della form corrente, esso rester fisso: a variare sar il codice del paziente*/
        $form = $this->vlist->esams[$in['VISITNUM']][$in['ESAM']]['XML'];


        //Andrea : rendere dinamica il nome della tabella di registrazione
        /*Generazione della tendina per cambiare paziente*/
        $sql_query = "
					select
					 codpat , subjid
					from {$this->service}_registrazione where center={$in['CENTER']} order by CODPAT
					";
        if (isset($_GET['time'])) echo $sql_query;
        $sql = new query($this->conn);
        $sql->set_sql($sql_query);
        $sql->exec();
        $options = "";
        /**
         * Prova di allegerimento
         */
        $patients = array();
        if ($sql->numrows > 0) {
            $idx = 0;
            while ($sql->get_row()) {
                $idx++;
                $patients[$idx]['CODPAT'] = $sql->row['CODPAT'];
                $patients[$idx]['SUBJID'] = $sql->row['SUBJID'];

                if (isset($in['CODPAT']) && $in['CODPAT'] == $patients[$idx]['CODPAT']) {
                    $selected = "selected";
                    $current_subjid = $patients[$idx]['SUBJID'];
                } else {
                    $selected = '';
                }
                $options .= "
						<option value=\"{$patients[$idx]['CODPAT']}\" $selected>{$patients[$idx]['SUBJID']}</option>";
            }
            $codice_paziente = "
					<select name=\"CODPAT\" onchange=\"doRedirect(this.value); \">
						$options
					</select>
				";
        }
//			echo $sql_query;
//			print_r($patients);

        /*Generazione della tendina per cambiare centro*/
        $sql_query = "
					select
						 center
					from {$this->service}_utenti_centri where userid='{$in['remote_userid']}'
					";
//			echo $sql_query;
        $sql = new query($this->conn);
        $sql->set_sql($sql_query);
        $sql->exec();
        $options = "";
        if ($sql->numrows > 0) {
            while ($sql->get_row()) {
//					print_r($sql->row['CENTER']);
//					print_r($in['CENTER']);
                if (isset($in['CENTER']) && $in['CENTER'] == $sql->row['CENTER']) {
                    $selected = "selected";
                } else {
                    $selected = '';
                }
                $options .= "
						<option value=\"{$sql->row['CENTER']}\" $selected>{$sql->row['CENTER']}</option>";
            }
            $codice_centro = "
					<select name=\"CENTER\" id=\"CENTER\" onchange=\"doRedirect2(this.value);\">
						$options
					</select>
				";
        }

        if (!isset($in['PROGR']) || $in['PROGR'] == "") {
            /**
             *  Il link per cambiare paziente, lascio l'add_progr vuoto , se sto ad esempio in una sub arriverò in una sub.
             *  Il link per cambiare form , metto di default il PROGR=1 , se passo da una sub ad una form normale
             */
            $add_progr = "";
            $add_progr_form = "&PROGR=1";
        } else {
            $add_progr_form = $add_progr = "&PROGR={$in['PROGR']}";
        }

        /*A seconda che mi trovi all'interno di una form o al livello superiore (vista degli esami del paziente)
         * scorro facendo variare il codpat. In questo caso non si avr bisogno della variabile $form.
         * Si va a creare i link per i vari casi in cui vogliamo andare (paziente successivo, precedente etc..)*/
        if (isset($in['ESAM']) && isset($in['form'])) {
            if ($first_pat != '' && $in['CODPAT'] != $first_pat) {
                $first_pat_lnk = "<a href=\"index.php?CENTER={$in['CENTER']}&{$this->config_service['PK_SERVICE']}={$first_pat}&VISITNUM={$in['VISITNUM']}&ESAM={$in['ESAM']}{$add_progr}&VISITNUM_PROGR={$in['VISITNUM_PROGR']}&form={$form}\" title=\"" . $this->testo("Primo_Paziente") . "\"><u>|<</u></a>";
            }
            if ($prev_pat != '') {
                $prev_pat_lnk = "<a href=\"index.php?CENTER={$in['CENTER']}&{$this->config_service['PK_SERVICE']}={$prev_pat}&VISITNUM={$in['VISITNUM']}&ESAM={$in['ESAM']}{$add_progr}&VISITNUM_PROGR={$in['VISITNUM_PROGR']}&form={$form}\" title=\"" . $this->testo("Prec_Paziente") . "\"><u><</u></a>";
            }
            if ($next_pat != '') {
                $next_pat_lnk = "<a href=\"index.php?CENTER={$in['CENTER']}&{$this->config_service['PK_SERVICE']}={$next_pat}&VISITNUM={$in['VISITNUM']}&ESAM={$in['ESAM']}{$add_progr}&VISITNUM_PROGR={$in['VISITNUM_PROGR']}&form={$form}\" title=\"" . $this->testo("Prossimo_Paziente") . "\"><u>></u></a>";
            }
            if ($last_pat != '' && $in['CODPAT'] != $last_pat) {
                $last_pat_lnk = "<a href=\"index.php?CENTER={$in['CENTER']}&{$this->config_service['PK_SERVICE']}={$last_pat}&VISITNUM={$in['VISITNUM']}&ESAM={$in['ESAM']}{$add_progr}&VISITNUM_PROGR={$in['VISITNUM_PROGR']}&form={$form}\" title=\"" . $this->testo("Ultimo_Paziente") . "\"><u>>|</u></a>";
            }
            if ($prev_esam != '') {
                $prev_esam_lnk = "<a href=\"index.php?CENTER={$in['CENTER']}&{$this->config_service['PK_SERVICE']}={$in['CODPAT']}&VISITNUM={$prev_visit}&ESAM={$prev_esam}{$add_progr_form}&VISITNUM_PROGR={$in['VISITNUM_PROGR']}&form={$prev_form}\"><u>" . $this->testo("Form_dietro") . "</u></a>";
            }
            if ($next_esam != '') {
                $next_esam_lnk = "<a href=\"index.php?CENTER={$in['CENTER']}&{$this->config_service['PK_SERVICE']}={$in['CODPAT']}&VISITNUM={$next_visit}&ESAM={$next_esam}{$add_progr_form}&VISITNUM_PROGR={$in['VISITNUM_PROGR']}&form={$next_form}\"><u>" . $this->testo("Form_avanti") . "</u></a>";
            }

            if ($this->vlist->esams[$in['VISITNUM']][$in['ESAM']]['SUB'] == "yes") {
                $codice_paziente = $current_subjid;
                $first_pat_lnk = $prev_pat_lnk = $next_pat_lnk = $last_pat_lnk = "";
            }
            /*Viene creata la tabella html con i link relativi e assegnata ad una variabile. Tale variabile
         * sar l'output del metodo navigation_bar_html($in).*/
            $nav_bar = "
			 <script type=\"text/javascript\">
				function doRedirect(value) { 
					var url;	
					url=\"index.php?CENTER={$in['CENTER']}&VISITNUM={$in['VISITNUM']}&ESAM={$in['ESAM']}{$add_progr}&VISITNUM_PROGR={$in['VISITNUM_PROGR']}&form={$form}\";
						
					if (location.href.match(/CODPAT=/)) {
						url+='&{$this->config_service['PK_SERVICE']}='+value;
						window.document.location.href =	url;
										
//						location.href.replace(/CODPAT=(.*?)&/i,'CODPAT='+value);
//						window.document.location.href=location.href.replace(/CODPAT=(.*?)&/i,'CODPAT='+value+'&');
					}
				}
				function doRedirect2(value) {
					if (location.href.match(/CENTER=/)) {
						window.document.location.href='index.php?list=patients_list.xml&CENTER='+value;

//						location.href.replace(/CENTER=(.*?)&/i,'CENTER='+value);
//						window.document.location.href=location.href.replace(/CENTER=(.*?)&/i,'CENTER='+value+'&');
					}
				}
			</script>
			<table class=sf width=100%  align=center>
			<tr>
				<td class=int colspan=8 align=center style=\"vertical-align:top; height:15px;\">" . $this->testo("Titolo") . "</td> 
			</tr>
			<tr>
				<td class=int_pt2 style=\"height:50px\">{$first_pat_lnk}</td>
				<td class=int_pt2>{$prev_pat_lnk}</td>
				<td class=int_pt2 align=center>$codice_centro</td>
				<td class=int_pt2 align=center>$codice_paziente</td>
				<td class=int_pt2>{$next_pat_lnk}</td>
				<td class=int_pt2>{$last_pat_lnk}</td>
				<!--td class=int_pt2 align=center width=100px>{$prev_esam_lnk}</td>
				<td class=int_pt2 align=center width=100px>{$next_esam_lnk}</td-->
				</table>
				";
        } else {
            if ($first_pat != '' && $in['CODPAT'] != $first_pat) {
                $first_pat_lnk = "<a href=\"index.php?&exams=visite_exam.xml&CENTER={$in['CENTER']}&{$this->config_service['PK_SERVICE']}={$first_pat}\" title=\"" . $this->testo("Primo_Paziente") . "\"><u>|<</u></a>";
            }
            if ($prev_pat != '') {
                $prev_pat_lnk = "<a href=\"index.php?&exams=visite_exam.xml&CENTER={$in['CENTER']}&{$this->config_service['PK_SERVICE']}={$prev_pat}\" title=\"" . $this->testo("Prec_Paziente") . "\"><u><</u></a>";
            }
            if ($next_pat != '') {
                $next_pat_lnk = "<a href=\"index.php?&exams=visite_exam.xml&CENTER={$in['CENTER']}&{$this->config_service['PK_SERVICE']}={$next_pat}\" title=\"" . $this->testo("Prossimo_Paziente") . "\"><u>></u></a>";
            }
            if ($last_pat != '' && $in['CODPAT'] != $last_pat) {
                $last_pat_lnk = "<a href=\"index.php?&exams=visite_exam.xml&CENTER={$in['CENTER']}&{$this->config_service['PK_SERVICE']}={$last_pat}\" title=\"" . $this->testo("Ultimo_Paziente") . "\"><u>>|</u></a>";
            }
            /*Viene creata la tabella html con i link relativi e assegnata ad una variabile. Tale variabile
         * sar l'output del metodo navigation_bar_html($in).*/
            $nav_bar = "
			 <script type=\"text/javascript\">
				function doRedirect(value) { 
					if (location.href.match(/CODPAT=/)) {
						location.href.replace(/CODPAT=(.*?)&/i,'CODPAT='+value);
//Vecchio modo:
//						window.document.location.href=location.href.replace(/CODPAT=(.*?)&/i,'CODPAT='+value+'&');alert(window.document.location.href);
//Nuovo:	
						var center_value=document.getElementById('CENTER').value;
						window.document.location.href='index.php?&exams=visite_exams.xml&CODPAT='+value+'&CENTER='+center_value;
					}
				}
				function doRedirect2(value) {
					if (location.href.match(/CENTER=/)) {
						location.href.replace(/CENTER=(.*?)&/i,'CENTER='+value);
						window.document.location.href='index.php?list=patients_list.xml&CENTER='+value;
						//window.document.location.href=location.href.replace(/CENTER=(.*?)&/i,'CENTER='+value+'&');
					}
				}
			</script>
			<table class=sf width=100%    align=center>
			<tr>
				<td class=int colspan=6 align=center style=\"vertical-align:top; height:15px;\">" . $this->testo("Titolo") . "</td> 
			</tr>
			<tr>
				<td class=int_pt2 style=\"height:50px\">{$first_pat_lnk}</td>
				<td class=int_pt2>{$prev_pat_lnk}</td>
				<td class=int_pt2 align=center>$codice_centro</td>
				<td class=int_pt2 align=center>$codice_paziente</td>
				<td class=int_pt2>{$next_pat_lnk}</td>
				<td class=int_pt2>{$last_pat_lnk}</td>
				<!--td class=int_pt2>{$prev_esam_lnk}</td>
				<td class=int_pt2>{$next_esam_lnk}</td-->
				</table>
				";
        }
        return $nav_bar;
    }

    /**
     *
     * Viene gestita la multilingua.
     *
     * @param String $testo
     *
     * @return $this->testi[$testo]
     *
     */
    function testo($testo)
    {
        //TODO: mettere $this->config_service ['Lista_schede'] nelle frasi in modo da configurarle dallo study.xml

        //HOW TO
        /* Per utilizzare questa funzione chiamarla cosi nel codice:
         * $this->testo("PAROLACHIAVE")
         * e qui dentro definire per ogni lingua
         * $this->testi['PAROLACHIAVE']="Frase da far apparire";
         */
//		print_r($this->config_service);
        if (!isset($this->testi[$testo])) {
            if (strtolower($this->config_service['lang']) == 'en') {
                $this->testi['Titolo'] = "Navigation Toolbar";
                $this->testi['Form_avanti'] = "Next Form";
                $this->testi['Form_dietro'] = "Previous Form";
                $this->testi['Primo_Paziente'] = "First patient";
                $this->testi['Prec_Paziente'] = "Previous patient";
                $this->testi['Prossimo_Paziente'] = "Next patient";
                $this->testi['Ultimo_Paziente'] = "Last patient";
            } else {
                $this->testi['Titolo'] = "Navigazione";
                $this->testi['Form_avanti'] = "Scheda successiva";
                $this->testi['Form_dietro'] = "Scheda precedente";
                $this->testi['Primo_Paziente'] = "Primo paziente";
                $this->testi['Prec_Paziente'] = "Paziente precedente";
                $this->testi['Prossimo_Paziente'] = "Paziente successivo";
                $this->testi['Ultimo_Paziente'] = "Ultimo paziente";
            }

        }
        return $this->testi[$testo];
    }

}

?>