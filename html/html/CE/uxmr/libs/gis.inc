<?php
include_once "db.inc";
###class gis### 
/*
<b>Libreria di Gestione GIS:</b>
    
    <b>Autore Carlo Contino</b>
    Data 21/04/2006
    
    <b>Sintassi costruttore:</b>
        $nome_oggetto=new <b>gis</b>($decode as string, $cod_reg as string, $value as string, $from as string, $group_by as string, $where as string, $conn as bdconn abject, $d_decode as string, $d_value as string, $tipo as string)
    <b>Variabili:</b>
        <b>$colors:</b> Array delle clssificazione dei color;
        <b>$mapfile:</b> nome del file di configurazione .map;
        <b>$decode:</b> decodeifica del testuale;
        <b>$value:</b> decodeifica del campo numerico;
        <b>$class_str:</b> string di classificazione; 
        <b>$query:</b> oggetto query; 
        <b>$tb:</b> tabella dei risultati in formato html; 
        <b>$tipo:</b> tipo di cartina (regione, province, comuni); 
    <b>Metodi:</b>
        <b>gis($decode as string, $cod_reg as string, $value as string, $from as string, $group_by as string, $where as string, $conn as bdconn abject, $d_decode as string, $d_value as string) as void:</b>inizializza tutti i paramatri creando anche il file di configurazione e la tabella riassuntiva
        <b>print_img() as string:</b> Stringa dell' immagine in formato html
        <b>print_tb() as string:</b> Stringa della tabella in formato html 
        <b>print_all() as string:</b> Tabella con immagine a sinistra e tabella a destra 
        <b>classificazione() as void:</b> crea la stringa di classificazione 
        <b>make_mapfile() as void:</b> crea il file di configurazion .map 
        <b>make_colors() as void:</b> crea l'array dei colori in RGB
        <b>tb_res() as void:</b> Stringa dell' tabella in html 
        
        
*/
###endclass###
  
  
class gis{
    
    var $colors;
    var $mapfile;
    var $decode;
    var $value;    
    var $class_str;
    var $query;
    var $tb;
    var $tipo;

    
###sub gis($decode as string, $cod_reg as string, $value as string, $from as string, $group_by as string, $where as string, $conn as bdconn abject, $d_decode as string, $d_value as string, $tipo as string) as void###    
    function gis($decode, $cod_reg, $value, $from, $group_by, $where, $conn, $d_decode, $d_value, $tipo){
       $this->decode=$d_decode;
       $this->value=$d_value;     
       $this->query=new query($conn); 
       $this->tipo=$tipo;
       $query_sql="select $cod_reg as COD_REG, $decode as DECODE, $value as VALUE from $from ";
       if ($where!='') $query_sql.="where $where ";
       if ($group_by!='') $query_sql.="group by $group_by ";  
       $query_sql.="order by 2";
       echo "<!--$query_sql-->";
       $this->query->set_sql($query_sql);
       $this->query->exec();//obsoleto trovare dove testare
       $this->make_colors();
       $nome_file=time();
       $this->mapfile="/http/www/amr_xml/shape/temp/map_".$nome_file.".map";
       $this->make_mapfile();
       $this->tb_res();          
    }
###endsub###
    
    ###sub print_img() as string###    
    function print_img(){
        return "<img src=\"http://amr-xml.test.cineca.it/cgi-bin/mapserv?map=".$this->mapfile."&amp;mode=map\"/>";
    }
###endsub###
    
    ###sub print_tb() as string###    
    function print_tb(){
        return $this->tb;
    }
###endsub###
    
###sub print_all() as string###
    function print_all(){
       return "<table border=0 cellpadding=0 cellspacing=0>
                <tr><td valign=top width=600>
                   ".$this->print_img()."
                </td>
                <td valign=top> 
                    ".$this->print_tb()."
                </td></tr> 
                </table>  
                ";
    }
###endsub###
    
###sub classificazione() as void###
    function classificazione(){
       foreach($this->colors as $key => $val) {
            #if ($this->tipo=="regione") $field="COD_REG";
            #if ($this->tipo=="comuni") $field="COD_ISTAT";            
            if ($this->tipo=="regione") $this->class_str.="CLASS
					          EXPRESSION ([COD_REG] = $key)
					          METADATA
					          END
					          STYLE
					            ANGLE 360
					              COLOR ".$val."
                                  OUTLINECOLOR 0 0 0
					            SYMBOL 0
					          END
					        END
                            ";
            if ($this->tipo=="comuni") $this->class_str.="CLASS
					          EXPRESSION ([COD_ISTAT] = $key)
					          METADATA
					          END
					          STYLE
					            ANGLE 360
					              COLOR ".$val."
					            SYMBOL 0
					          END
					        END
                            ";
            if ($this->tipo=="province") $this->class_str.="CLASS
					          EXPRESSION ([COD_PRO] = $key)
					          METADATA
					          END
					          STYLE
					            ANGLE 360
					              COLOR ".$val."
                                  OUTLINECOLOR 0 0 0
					            SYMBOL 0
					          END
					        END
                            ";
        }
        if ($this->tipo!="comuni")$this->class_str.="
              CLASS
                OUTLINECOLOR 0 0 0   
               END
        ";                      
    }
###endsub###
    
###sub make_mapfile() as void###
    function make_mapfile(){
        $filename = "/http/www/amr_xml/shape/mappa_".$this->tipo.".map";
        $handle = fopen($filename, "r");
        $contents = fread($handle, filesize($filename));
        fclose($handle);    
        $this->classificazione();
        $new_map=preg_replace("/\<\<classificazione\>\>/", $this->class_str, $contents);                  
        if (!$handle = fopen($this->mapfile, 'w')) {
                 echo "Cannot open file ($this->mapfile)";
                 exit;
        }                                           
        if (fwrite($handle, $new_map) == FALSE) {
                echo "Cannot write to file ($mapfile)";
                exit;
        }       
        fclose($handle);
    }
###endsub###
    
###sub make_colors() as void###
    function make_colors(){
        for ($i=0;$this->query->get_row();$i++)
            {   
                if ($this->tipo!='comuni') $cod_reg=$this->query->row['COD_REG']+0; 
                else $cod_reg=$this->query->row['COD_REG'];
                $result[$cod_reg]=$this->query->row['VALUE'];
            }
        $totval=0;
        $max=0;
       if ($this->query->numrows>0){
	       foreach ($result as $key => $val) {
	            $totval+=$val;  
	            if ($max<$val) $max=$val;
	       }
	       $rapp=150/$max; 
	       foreach ($result as $key => $val) {
	           $valore=$rapp*$val;
	           $valore=round($valore);     
	           $valore=255-$valore;
	           $this->colors[$key]="$valore $valore 255"; 
	       }    
	     }                       
       $this->totval=$totval;   
    } 
###endsub###
    
###sub tb_res() as void###
    function tb_res(){
            $this->tb="<table border=1 cellpadding=0 cellspacing=0><tr><th><b>".$this->decode."</b></th><th><b>".$this->value."</b></th></tr>";
            for ($r=0;$r<$this->query->numrows;$r++){
                $this->tb.="<tr>";
                for ($i=1;$i<$this->query->numcols;$i++) {
                    $cod_reg=$this->query->res['COD_REG'][$r]+0;
                    $colors=$this->colors[$cod_reg];
                    $color=explode(" ", $colors);
                    $rh=dechex($color[0])."00"; 
                    $gh=dechex($color[1])."00";     
                    $bh=dechex($color[2])."00";  
                    $rh=substr($rh, 0,2); 
                    $gh=substr($gh, 0,2); 
                    $bh=substr($bh, 0,2);  
                    $bgcolor="#".$rh.$gh.$bh;
                    $this->tb.="<td bgcolor=\"$bgcolor\"><b>".$this->query->res[$this->query->keys[$i]][$r]."</b></td>";   
                }
                $this->tb.="</tr>"; 
            }
            $this->tb.="<tr><td><b>Totale:</b></td><td><b>".$this->totval."</b></td></tr></table>";
        }
###endsub###
    
  }
  
  
?>
