<?php

global $custom_modules;
$custom_modules=array();

//MODULO PIANI TERAPEUTICI
$custom_modules['THERAPY']="0";//modulo gestione terapie per drug-registry
$custom_modules['THERAPY_TABLES']["LISTA_PT"]=array(
													 "PT_CODE"=>"NUMBER NOT NULL PRIMARY KEY",
													 "PT_DECODE"=>"VARCHAR2(200 BYTE)",
													 "PT_VALUTAZIONE"=>"VARCHAR2(200 BYTE)",
													 "PT_TIME_LAPSE"=>"NUMBER",
													 "F_TO_CALL_ELEG"=>"VARCHAR2(200 BYTE)",
													 "REIMB_MAX_DOSAGE"=>"VARCHAR2(20 BYTE)"
													 );
$custom_modules['THERAPY_TABLES']["MEDICO_PT"]=array(
													  "MEDICO"=>"VARCHAR2(40 CHAR) NOT NULL",
													  "PT_CODE"=>"NUMBER NOT NULL");
//MODULO PIANI TERAPEUTICI
$custom_modules['GLOBAL_PROFILES']="0";//modulo gestione gruppi globali

$custom_modules['SIGNATURES']="0";//modulo gestione firme elettroniche


$custom_modules['DBLOCK']=1;
$custom_modules['DBLOCK_FUNCTIONS']=array();
$custom_modules['DBLOCK_FUNCTIONS'][1]='NEWPATIENT'; //primo bit 0001
$custom_modules['DBLOCK_FUNCTIONS'][2]='SAVESEND'; //secondo bit 0010
$custom_modules['DBLOCK_FUNCTIONS'][3]='EQUERY'; //terzo bit 0100
$custom_modules['DBLOCK_FUNCTIONS'][4]='OBVIOUSCORRECTION'; //quarto bit 1000

?>