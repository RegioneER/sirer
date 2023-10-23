<?
include_once "study_prototype.inc";

/**
 * Classe di gestione degli Audit Trail
 *
 * @package Hyper
 */
class DoubleDataEntry
{

    function DoubleDataEntry($session_vars, $conn, $service, $vlist, $xml_dir, $config_service)
    {

        $this->conn = $conn;
        $this->session_vars = $session_vars;
        $this->service = $service;
        $this->vlist = $vlist;
        $this->xml_dir = $xml_dir;
        $this->config_service = $config_service;

    }


    /**
     * Vecchio compare: con il layout della form, il nuovo solo con le description.
     */
    function dde_page()
    {
// 		print_r($this->config_service);
        $dde_centers = "";
        /**
         * In config_service['DDE'] vengono definiti i centri dedicati al double data entry (o triple ...)
         *
         */
        /**
         * 1 foreach: genero la pagina con la lista delle form con i due codpat
         */
        foreach ($this->config_service['DDE'] as $key => $val) {
            if ($dde_centers != "") {
                $dde_centers .= " OR ";
            }
            $dde_centers .= "CENTER='" . $val . "'";
        }
        $sql_query = "select codpat from {$this->service}_REGISTRAZIONE where SUBJID='{$this->session_vars['SUBJID']}' AND ( $dde_centers )";
        $sql = new query ($this->conn);
        $sql->exec($sql_query);

        while ($sql->get_row()) {
            $this->crf($sql->row['CODPAT']);
        }

        /**
         * Faccio i controlli per vedere le differenze e valorizzo l'array $difference
         */
// 		print_r($this->dde_form);
// 		print_r($this->dde_vals);
//		print_r($this->config_service['DDE'][1]);
        foreach ($this->dde_vals as $k_ar => $v_ar) {
            //print_r($v_ar);
            ${"array_{$k_ar}"} = $v_ar;
            //print("<hr />");
        }
//		print_r($array_001);
        foreach (${"array_{$this->config_service['DDE'][1]}"} as $k => $v) {
            if (${"array_{$this->config_service['DDE'][1]}"}[$k] != ${"array_{$this->config_service['DDE'][2]}"}[$k]) {
//					echo "$k<br>DE1-> ";
//					print_r(${"array_{$this->config_service['DDE'][1]}"}[$k]);
//					echo "<br>DE2->";
//					print_r(${"array_{$this->config_service['DDE'][2]}"}[$k]);
//					echo "<hr>";
                $difference[$k] = $k;
            }
        }
//		print_r($difference);	

        /**
         * 2 foreach: rigenero la pagina con la lista delle form con i due codpat, passando ora l'array $difference
         * con tale parametro viene chiamata la funzione Set_DDE_Difference, che mi settala variabile di stato $this->difference
         * In base a questa vengono evidenziati i field in field.inc
         */
        $sql_query = "select codpat from {$this->service}_REGISTRAZIONE where SUBJID='{$this->session_vars['SUBJID']}' AND ( $dde_centers )";
        $sql = new query ($this->conn);
        $sql->exec($sql_query);

        $page = "<div align=center><font color=blue size=5><u>XMR - COMPARE</u></font></div><br>";
        $page .= "<table align=center width=30%><tr><td align='center' ><a href='index.php?SUBJID={$this->session_vars['SUBJID']}&DDE=1&ONLY_EQUAL=1'>Only equal</a></td><td  align='center'><a href='index.php?SUBJID={$this->session_vars['SUBJID']}&DDE=1&ONLY_DIFF=1'>Only difference</a></td><td  align='center'><a href='index.php?SUBJID={$this->session_vars['SUBJID']}&DDE=1'>All</a></td></tr></table>";
        $page .= "<table align=center id=dde_table width=100%><tr>";

        while ($sql->get_row()) {
            $page .= "<td id=dde_td align=center>";
            $page .= $this->crf($sql->row['CODPAT'], $difference);
            $page .= "</td>";

        }
        $page .= "</tr></table>";

        return $page;
    }

    function crf($codpat, $difference = null)
    {
        $service = $this->service;
        $return = null;
        $this->session_vars['CODPAT'] = $codpat;

        $sql_query = "select esam, visitnum, visitnum_progr, progr from {$service}_COORDINATE where codpat='$codpat'";
        $sql = new query ($this->conn);
        $sql->exec($sql_query);
        while ($sql->get_row()) {
            if (isset($this->vlist->esams[$sql->row['VISITNUM']][$sql->row['ESAM']]) && $sql->row['VISITNUM'] < 2) {

                $return .= $this->printable_form($sql->row ['ESAM'], $sql->row ['VISITNUM'], $sql->row ['VISITNUM_PROGR'], $sql->row ['PROGR'], $difference);
            }
        }

        return $return;
    }

    function printable_form($esam, $visitnum, $visitnum_progr, $progr, $difference = null)
    {
        $_GET['ESAM'] = $this->session_vars['ESAM'] = $esam;
        $_GET['VISITNUM'] = $this->session_vars['VISITNUM'] = $visitnum;
        $_GET['VISITNUM_PROGR'] = $this->session_vars['VISITNUM_PROGR'] = $visitnum_progr;
        $_GET['PROGR'] = $this->session_vars['PROGR'] = $progr;
        $form = $this->vlist->esams[$visitnum][$esam]['XML'];
        $xml_form = new xml_form ($this->conn, $this->service, $this->config_service, $this->session_vars, $this->uploaded_file_dir);
        if ($difference != '') {
            $xml_form->Set_DDE_Difference($difference);
        }
        $xml_form->xml_form_by_file($this->xml_dir . '/' . $form);
        $xml_form->make_html(true, true);

        // Nell'array this->dde_form ci sono le informazioni di tutte le schede inserite dai due DE
        $this->dde_form[$xml_form->tb_vals['CENTER']] = $xml_form;
        // Nell'array this->dde_vals ci sono i valori di tutte le schede inseriti dai due DE
        $this->dde_vals[$xml_form->tb_vals['CENTER']] = $xml_form->tb_vals;

        unset($_GET['ESAM']);
        unset($_GET['VISITNUM']);
        unset($_GET['VISITNUM_PROGR']);
        unset($_GET['PROGR']);
        $xml_form->body = "<table style='width:80% ;' align=center ><tr><td>" . $xml_form->body . "</td></tr></table>";
        return $xml_form->body;
    }


}