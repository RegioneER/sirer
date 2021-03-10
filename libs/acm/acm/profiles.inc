<?php
define('PROFILE_GLOBAL',0);
define('PROFILE_SINGLE',1);
define('PROFILE_MULTIPLE',2);

global $profili;
$profili=array();

$profili['SIMPLE_FOLDER']['GRANTED']=array("descrizione" => "Granted User",

                                                                        "policy" => "RO",

                                                                        "molteplicita" => 0,

                                                                        "d_molteplicita" => "global");


$profili['DRUG_REGISTRY']['C']=array("descrizione" => "Clinician",

                                                                        "policy" => "DE",

                                                                        "molteplicita" => 1,

                                                                        "d_molteplicita" => "single");

 

$profili['DRUG_REGISTRY']['HP']=array("descrizione" => "Hospital Pharmacist",

                                                                        "policy" => "DE",

                                                                        "molteplicita" => 1,

                                                                        "d_molteplicita" => "single");

 

$profili['DRUG_REGISTRY']['LP']=array("descrizione" => "Local Pharmacist",

                                                                        "policy" => "DE",

                                                                        "molteplicita" => 2,

                                                                        "d_molteplicita" => "multiple");

 

$profili['DRUG_REGISTRY']['RPH']=array("descrizione" => "Responsible for the Pharmacovigilance in the Hospital",

                                                                        "policy" => "RO",

                                                                        "molteplicita" => 1,

                                                                        "d_molteplicita" => "single");

 

$profili['DRUG_REGISTRY']['PC']=array("descrizione" => "Pharmaceutical Company",

                                                                        "policy" => "RO",

                                                                        "molteplicita" => 0,

                                                                        "d_molteplicita" => "global");

 

$profili['DRUG_REGISTRY']['NA']=array("descrizione" => "National Authority",

                                                                        "policy" => "DM",

                                                                        "molteplicita" => 0,

                                                                        "d_molteplicita" => "global");

 

$profili['DRUG_REGISTRY']['SC']=array("descrizione" => "Steering Committee",

                                                                        "policy" => "RO",

                                                                        "molteplicita" => 0,

                                                                        "d_molteplicita" => "global");

 

$profili['DRUG_REGISTRY']['NAPO']=array("descrizione" => "National Authority - Pharmacovigilance Office",

                                                                        "policy" => "RO",

                                                                        "molteplicita" => 0,

                                                                        "d_molteplicita" => "global");

 

$profili['DRUG_REGISTRY']['RC']=array("descrizione" => "Region Councilors",

                                                                        "policy" => "RO",

                                                                        "molteplicita" => 2,

                                                                        "d_molteplicita" => "multiple");

 

$profili['DRUG_REGISTRY']['NDQ']=array("descrizione" => "National Data Quality",

                                                                        "policy" => "DM",

                                                                        "molteplicita" => 0,

                                                                        "d_molteplicita" => "global");

/*

* PER ORA TENIAMO $profili['CLINICAL_TRIAL']['DE'] perchè in dev ci sono servizi con questo profilo abilitato, se no non vanno più!

* magari sarebbe meglio cambiare il codice da DE a PI

*/

$profili['CLINICAL_TRIAL']['DE']=array("descrizione" => "Principal Investigator",

                                                                        "policy" => "DE",

                                                                        "molteplicita" => 2,

                                                                        "d_molteplicita" => "multiple");

                                                                        

$profili['CLINICAL_TRIAL']['CO_PI']=array("descrizione" => "Co-principal Investigator",

                                                                        "policy" => "DE",

                                                                        "molteplicita" => 2,

                                                                        "d_molteplicita" => "multiple");

 

$profili['CLINICAL_TRIAL']['ST']=array("descrizione" => "Site Staff",

                                                                        "policy" => "DE",

                                                                        "molteplicita" => 2,

                                                                        "d_molteplicita" => "multiple");

 

$profili['CLINICAL_TRIAL']['PM']=array("descrizione" => "Project Manager",

                                                                        "policy" => "RO",

                                                                        "molteplicita" => 0,

                                                                        "d_molteplicita" => "global");

 

$profili['CLINICAL_TRIAL']['DM']=array("descrizione" => "Data Manager",

                                                                        "policy" => "DM",

                                                                        "molteplicita" => 0,

                                                                        "d_molteplicita" => "global");

 

$profili['CLINICAL_TRIAL']['CRA']=array("descrizione" => "CRA",

                                                                        "policy" => "DM",

                                                                        "molteplicita" => 2,

                                                                        "d_molteplicita" => "multiple");

 

$profili['CLINICAL_TRIAL']['SP']=array("descrizione" => "Sponsor",

                                                                        "policy" => "RO",

                                                                        "molteplicita" => 0,

                                                                        "d_molteplicita" => "global");

/**

* PER ORA TENIAMO $profili['CLINICAL_TRIAL']['DE'] perchè in dev ci sono servizi con questo profilo abilitato, se no non vanno più!

* da eliminare

*/

$profili['CLINICAL_TRIAL']['RO']=array("descrizione" => "Read Only User",

                                                                        "policy" => "RO",

                                                                        "molteplicita" => 0,

                                                                        "d_molteplicita" => "global");


 
///////////////////////LABORATORY RANGE/////////////////
//Uguale a CLINICAL_TRIAL
$profili['LABORATORY_RANGE'] = $profili['CLINICAL_TRIAL'];
//$profili['LABORATORY_RANGE']['LBW']=array("descrizione" => "Lab Range ReadWrite", "policy" => "DE", "molteplicita" => 2, "d_molteplicita" => "multiple");
//$profili['LABORATORY_RANGE']['LBR']=array("descrizione" => "Lab Range ReadOnly", "policy" => "RO", "molteplicita" => 2, "d_molteplicita" => "multiple");

////////////////////////////////////////////////////////

$profili['DRUPAL']['DAC']=array("descrizione" => "Drupal Access", "policy" => "RO", "molteplicita" => 0, "d_molteplicita" => "global");

?>
