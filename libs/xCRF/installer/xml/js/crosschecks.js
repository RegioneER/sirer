HH_CROSS_IDX = new Array();
HH_CROSS_IDX[0] = new Array();
HH_CROSS_IDX[1] = new Array();
HH_CROSS_IDX[1][26] = '#4'; //incl_exc_criteria
HH_CROSS_IDX[1][23] = '#88'; //visit date
HH_CROSS_IDX[1][1] = '#84#87'; //informed_consent_demog
HH_CROSS_IDX[1][3] = '#5#6#7#8#71';  //sub_medical_history
HH_CROSS_IDX[1][4] = '#9#10#11#12#13#14#15#16#17#18#19#20#21#22#23#24#25#26#72#76';  //Prostate cancer hystory and evaluation 
HH_CROSS_IDX[1][24] = '#27#69#74'; //laboratory tests main
HH_CROSS_IDX[1][25] = '#29#30#31#32#33#73#100#101#102#103#104#105#106'; //laboratory tests sub
HH_CROSS_IDX[1][7] = '#28'; //vital sign
HH_CROSS_IDX[1][8] = '#34#35'; //Gallbladder echotomography 
HH_CROSS_IDX[1][28] = '#36#37#38#39#40#41#63#64#65#66#77#85#86'; //Tumor specific laboratory tests
HH_CROSS_IDX[1][10] = '#43'; //Tumor related signs/symptoms 

HH_CROSS_IDX[2] = new Array();
HH_CROSS_IDX[2][23] = '#89'; //visit date
HH_CROSS_IDX[2][5] = '#1#2#3#70'; //incl_exc_criteria
HH_CROSS_IDX[2][7] = '#28'; //vital sign
HH_CROSS_IDX[2][29] = '#42'; //Tumor specific laboratory tests 
HH_CROSS_IDX[2][10] = '#43'; //Tumor related signs/symptoms 
HH_CROSS_IDX[2][6] = '#67#68'; //randomization

HH_CROSS_IDX[3] = new Array();
HH_CROSS_IDX[3][23] = '#90'; //visit date
HH_CROSS_IDX[3][24] = '#27#69#74'; //laboratory tests main
HH_CROSS_IDX[3][25] = '#29#30#31#32#33#73#100#101#102#103#104#105#106'; //laboratory tests sub
HH_CROSS_IDX[3][7] = '#28'; //vital sign
HH_CROSS_IDX[3][30] = '#36#37'; //Tumor specific laboratory tests 
HH_CROSS_IDX[3][10] = '#43'; //Tumor related signs/symptoms 

HH_CROSS_IDX[4] = new Array();
HH_CROSS_IDX[4][23] = '#91'; //visit date
HH_CROSS_IDX[4][7] = '#28'; //vital sign
HH_CROSS_IDX[4][31] = '#36#37#40#42#63#64'; //Tumor specific laboratory tests 
HH_CROSS_IDX[4][10] = '#43'; //Tumor related signs/symptoms 

HH_CROSS_IDX[5] = new Array();
HH_CROSS_IDX[5][23] = '#92'; //visit date
HH_CROSS_IDX[5][7] = '#28'; //vital sign
HH_CROSS_IDX[5][30] = '#36#37'; //Tumor specific laboratory tests 
HH_CROSS_IDX[5][10] = '#43'; //Tumor related signs/symptoms 

HH_CROSS_IDX[6] = new Array();
HH_CROSS_IDX[6][23] = '#93'; //visit date
HH_CROSS_IDX[6][24] = '#27#69#74'; //laboratory tests main
HH_CROSS_IDX[6][25] = '#29#30#31#32#33#73#100#101#102#103#104#105#106'; //laboratory tests sub
HH_CROSS_IDX[6][7] = '#28'; //vital sign
HH_CROSS_IDX[6][8] = '#34#35'; //Gallbladder echotomography 
HH_CROSS_IDX[6][32] = '#36#37#40#63#64'; //Tumor specific laboratory tests 
HH_CROSS_IDX[6][10] = '#43'; //Tumor related signs/symptoms 

HH_CROSS_IDX[7] = new Array();
HH_CROSS_IDX[7][23] = '#94'; //visit date
HH_CROSS_IDX[7][7] = '#28'; //vital sign
HH_CROSS_IDX[7][30] = '#36#37'; //Tumor specific laboratory tests 
HH_CROSS_IDX[7][10] = '#43'; //Tumor related signs/symptoms 

HH_CROSS_IDX[8] = new Array();
HH_CROSS_IDX[8][23] = '#95'; //visit date
HH_CROSS_IDX[8][7] = '#28'; //vital sign
HH_CROSS_IDX[8][32] = '#36#37#40#63#64'; //Tumor specific laboratory tests 
HH_CROSS_IDX[8][10] = '#43'; //Tumor related signs/symptoms 

HH_CROSS_IDX[9] = new Array();
HH_CROSS_IDX[9][23] = '#96'; //visit date
HH_CROSS_IDX[9][24] = '#27#69#74'; //laboratory tests main
HH_CROSS_IDX[9][25] = '#29#30#31#32#33#73#100#101#102#103#104#105#106'; //laboratory tests sub
HH_CROSS_IDX[9][7] = '#28'; //vital sign
HH_CROSS_IDX[9][30] = '#36#37'; //Tumor specific laboratory tests 
HH_CROSS_IDX[9][10] = '#43'; //Tumor related signs/symptoms 

HH_CROSS_IDX[10] = new Array();
HH_CROSS_IDX[10][23] = '#97'; //visit date
HH_CROSS_IDX[10][7] = '#28'; //vital sign
HH_CROSS_IDX[10][8] = '#34#35'; //Gallbladder echotomography 
HH_CROSS_IDX[10][32] = '#36#37#40#63#64'; //Tumor specific laboratory tests 
HH_CROSS_IDX[10][10] = '#43'; //Tumor related signs/symptoms 

HH_CROSS_IDX[11] = new Array();
HH_CROSS_IDX[11][12] = '#44#45#46#47#48'; //sub_Instrumental examinations
HH_CROSS_IDX[11][16] = '#49#50'; //sub_Standard treatments
HH_CROSS_IDX[11][18] = '#51#52#53#54#55#56'; //sub_Prior and concomitant medication
HH_CROSS_IDX[11][20] = '#57#58#59#60#61#62#80#81#82#83#98#99#110'; //sub_Adverse events
HH_CROSS_IDX[11][13] = '#75'; //study drug main
HH_CROSS_IDX[11][14] = '#78#79'; //study drug sub
HH_CROSS_IDX[11][21] = '#107#108#109'; //study termination

/*
NOTE:
--> se il campo da confrontare è di tipo testo (text_hyper) utilizzare gli apici nella condizione null es. #FINOTHSP#=="NULL" (la condizione deve essere UPPER)
--> se il campo è di tipo date, e si deve fare un controllo tra date utilizzare la funzione d1d2, se la data è presente nella form 
    come campo date e non come hidden utilizzare questa sintassi: "#MHSTDATD#/#MHSTDATM#/#MHSTDATY#"
	per i campi date ma hidden (quindi prelevati da altre form) utilizzare:#HD_DMDAT# e in più mettere sempre questacondizione: && #HD_DMDATRC#=="OKOKOK"
	perchè le date vengono considerate solo se complete, se contengono NA, NK il controllo viene annullato.
--> per fare un controllo sulla valorizzazione di una data presente nella form, non hidden, 
    utilizzare: #PRSTADTD#==null && #PRSTADTM#==null && #PRSTADTY#==null
--> per i checkbox utilizzare: #INC1#==1 o #INC1#!=1 (vuol dire null)
*/

HH_CROSS_CHECK = new Array();
HH_CROSS_CHECK[0] = new Array();
HH_CROSS_CHECK[0] = ['VISIT','FOCUS','RECORD','TYPE','RULE','MESSAGE'];
HH_CROSS_CHECK[1] = ['2','IEYN','','B','(#IEYN#==806002 &&(#INC1#==1||#INC2#==1||#INC3#==1||#INC4#==1||#INC5#==1||#INC6#==1||#INC7#==1||#INC8#==1||#INC9#==1))','Answer to the first question is Yes but at least one criteria has been ticked. If answer to the first question is correct, no criteria must be ticked.'];
HH_CROSS_CHECK[2] = ['2','IEYN','','B','(#IEYN#==806002 &&(#EXC1#==1||#EXC2#==1||#EXC3#==1||#EXC4#==1||#EXC5#==1||#EXC6#==1||#EXC7#==1||#EXC8#==1||#EXC9#==1||#EXC10#==1||#EXC11#==1||#EXC12#==1||#EXC13#==1||#EXC14#==1||#EXC15#==1))','Answer to the first question is Yes but at least one criteria has been ticked. If answer to the first question is correct, no criteria must be ticked.'];
HH_CROSS_CHECK[3] = ['2','IEYN','','B','(#IEYN#==806001 && #INC1#==null && #INC2#==null && #INC3#==null && #INC4#==null && #INC5#==null && #INC6#==null && #INC7#==null && #INC8#==null && #INC9#==null && #EXC1#==null && #EXC2#==null && #EXC3#==null && #EXC4#==null && #EXC5#==null && #EXC6#==null && #EXC7#==null && #EXC8#==null && #EXC9#==null && #EXC10#==null && #EXC11#==null && #EXC12#==null && #EXC13#==null && #EXC14#==null && #EXC15#==null)','The subject did not meet all eligibility criteria (answer to the first question is "\No\"). Please tick all the criteria not met or change the answer to the first question.'];
HH_CROSS_CHECK[4] = ['1','INC1','','W','(#INC1#==806001||#INC2#==806001||#INC3#==806001||#INC4#==806001||#INC5#==806001||#INC6#==806001||#INC7#==806001||#INC8#==806001||#INC9#==806001||#EXC1#==806002||#EXC2#==806002||#EXC3#==806002||#EXC4#==806002||#EXC5#==806002||#EXC6#==806002||#EXC7#==806002||#EXC8#==806002||#EXC9#==806002||#EXC10#==806002||#EXC11#==806002||#EXC12#==806002||#EXC13#==806002||#EXC14#==806002||#EXC15#==806002)','At least one inclusion criterion is No or exclusion criterion is Yes. The patient is a violator or should be excluded from the study. If it is an error, please change the data.'];
HH_CROSS_CHECK[5] = ['1','MHSTDAT','','B','(d1d2("#MHSTDATD#/#MHSTDATM#/#MHSTDATY#",#HD_DMDAT#,">=") && #HD_DMDATRC#=="OKOKOK" )','Start date is after informed consent date. Please record the disease in the Adverse events form.'];
HH_CROSS_CHECK[6] = ['1','MHONGO','','B','(#MHONGO#==1 && #MHENDATD#!=null && #MHENDATM#!=null && #MHENDATY#!=null)','\"Ongoing or sequelae at start of study\" is ticked but also end date is filled in. Please check the data'];
HH_CROSS_CHECK[7] = ['1','MHENDAT','','B','(d1d2("#MHSTDATD#/#MHSTDATM#/#MHSTDATY#","#MHENDATD#/#MHENDATM#/#MHENDATY#",">"))','End date is before start date. Please check the data.'];
HH_CROSS_CHECK[8] = ['1','MHENDAT','','B','(d1d2("#MHENDATD#/#MHENDATM#/#MHENDATY#",#HD_DMDAT#,">=") && #HD_DMDATRC#=="OKOKOK" )','End date is after informed consent date. Please check the dates, if correct tick "\Ongoing or sequelae at start of study\" and delete end date.'];
HH_CROSS_CHECK[9] = ['1','DIAGDAT','','B','(d1d2("#DIAGDATD#/#DIAGDATM#/#DIAGDATY#",#HD_DMDAT#,">") && #HD_DMDATRC#=="OKOKOK" )','Date of histologically proven diagnosis is after informed consent date. Please check the data.'];
HH_CROSS_CHECK[10] = ['1','PRSTATEC','','B','(#PRSTATEC#==806002 && #PRSTADTD#==null && #PRSTADTM#==null && #PRSTADTY#==null)','Answer to the question "\Did the patient undergo prostatectomy?\" is Yes but Date of intervention is not specified. Please check the data.'];
HH_CROSS_CHECK[11] = ['1','ORCHIECT','','B','(#ORCHIECT#==806002 && #ORCHIEDTD#==null && #ORCHIEDTM#==null && #ORCHIEDTY#==null)','Answer to the question "\Did the patient undergo orchiectomy?\" is Yes but Date of intervention is not specified. Please check the data.'];
HH_CROSS_CHECK[12] = ['1','PRSTADTD','','B','(d1d2("#PRSTADTD#/#PRSTADTM#/#PRSTADTY#","#DIAGDATD#/#DIAGDATM#/#DIAGDATY#","<"))','Date of prostatectomy is before date of histologically proven diagnosis. Please check the data.'];
HH_CROSS_CHECK[13] = ['1','ORCHIEDTD','','B','(d1d2("#ORCHIEDTD#/#ORCHIEDTM#/#ORCHIEDTY#","#DIAGDATD#/#DIAGDATM#/#DIAGDATY#","<"))','Date of orchiectomy is before date of histologically proven diagnosis. Please check the data.'];
HH_CROSS_CHECK[14] = ['1','LHRHA','','B','(#LHRHA#==806002 && #LHRHSTDTD#==null && #LHRHSTDTM#==null && #LHRHSTDTY#==null)','Answer to the question "\Previous therapy with LHRH-a\" is Yes but Date of first administration is not specified. Please check the data.'];
HH_CROSS_CHECK[15] = ['1','LHRHSTDTD','','B','(d1d2("#LHRHSTDTD#/#LHRHSTDTM#/#LHRHSTDTY#",#HD_DMDAT#,">") && #HD_DMDATRC#=="OKOKOK" )','Date of first administration for therapy with LHRH-a is after informed consent date. Please check the data.'];
HH_CROSS_CHECK[16] = ['1','LHRHSTDTD','','B','(d1d2("#LHRHSTDTD#/#LHRHSTDTM#/#LHRHSTDTY#","#DIAGDATD#/#DIAGDATM#/#DIAGDATY#","<"))','Date of first administration (LHRH-a) is before date of histologically proven diagnosis. Please check the data.'];
HH_CROSS_CHECK[17] = ['1','LHRHA','','B','(#LHRHA#==806002 && (#LHRHENDTD#==null && #LHRHENDTM#==null && #LHRHENDTY#==null && #LHRHONG#!=1 ))','Please specify date of last administration (LHRH-a) or Ongoing at time of screening.'];
HH_CROSS_CHECK[18] = ['1','LHRHONG','','B','(#LHRHONG#==1 && #LHRHENDTD#!=null && #LHRHENDTM#!=null && #LHRHENDTY#!=null)','Date of last administration (LHRH-a) is filled in but also Ongoing at time of screening is ticked. Please check the data'];
HH_CROSS_CHECK[19] = ['1','LHRHENDTD','','B','(d1d2("#LHRHENDTD#/#LHRHENDTM#/#LHRHENDTY#",#HD_DMDAT#,">") && #HD_DMDATRC#=="OKOKOK" )','Date of last administration (LHRH-a) is after informed consent date. Please check the dates, if correct tick "Ongoing at time of screening" and delete Date of last administration.'];
HH_CROSS_CHECK[20] = ['1','LHRHENDTD','','B','(d1d2("#LHRHSTDTD#/#LHRHSTDTM#/#LHRHSTDTY#","#LHRHENDTD#/#LHRHENDTM#/#LHRHENDTY#",">"))','Date of last administration (LHRH-a) is before date of first administration. Please check the data.'];
HH_CROSS_CHECK[21] = ['1','ANDPRE','','B','(#ANDPRE#==806002 && (#ANDSTDTD#==null && #ANDSTDTM#==null && #ANDSTDTY#==null))','Date of first administration (therapy with Antiandrogens) is not specified. Please provide data.'];
HH_CROSS_CHECK[22] = ['1','ANDSTDTD','','B','(d1d2("#ANDSTDTD#/#ANDSTDTM#/#ANDSTDTY#",#HD_DMDAT#,">") && #HD_DMDATRC#=="OKOKOK" )','Date of first administration for therapy with Antiandrogens is after informed consent date. Please check the data.'];
HH_CROSS_CHECK[23] = ['1','ANDSTDTD','','B','(d1d2("#ANDSTDTD#/#ANDSTDTM#/#ANDSTDTY#","#DIAGDATD#/#DIAGDATM#/#DIAGDATY#","<"))','Date of first administration (therapy with Antiandrogens) is before date of histologically proven diagnosis. Please check the data.'];
HH_CROSS_CHECK[24] = ['1','ANDPRE','','B','(#ANDPRE#==806002 && (#ANDENDTD#==null && #ANDENDTM#==null && #ANDENDTY#==null && #ANDONG#!=1 ))','Please specify date of last administration (therapy with Antiandrogens) or Ongoing at time of screening.'];
HH_CROSS_CHECK[25] = ['1','ANDONG','','B','(#ANDONG#==1 && #ANDENDTD#!=null && #ANDENDTM#!=null && #ANDENDTY#!=null)','Date of last administration (therapy with Antiandrogens) is filled in but also Ongoing at time of screening is ticked. Please check the data.'];
HH_CROSS_CHECK[26] = ['1','ANDENDTD','','B','(d1d2("#ANDENDTD#/#ANDENDTM#/#ANDENDTY#","#ANDSTDTD#/#ANDSTDTM#/#ANDSTDTY#","<="))','Date of last administration (therapy with Antiandrogens) is before date of first administration. Please check the data.'];
HH_CROSS_CHECK[27] = ['1','LBPERF','','B','(#LBPERF#==806002 && #LBDATD#==null && #LBDATM#==null && #LBDATY#==null )','Answer to the question "\Tests performed?\" is Yes but Sampling Date is not specified. Please check the data.'];
HH_CROSS_CHECK[28] = ['1','SYSBP','','B','(#SYSBP#!=null  && #SYSBP#!=-9911 && #SYSBP#!="NA" && #DIASBP#!=-9911 && #DIASBP#!="NA" && #DIASBP#!=null && #SYSBP#<=#DIASBP# )','Systolic blood pressure is lower than diastolic. Please check the data.'];
HH_CROSS_CHECK[29] = ['1','LBNRIND1_1','','B','((#LBNRIND1_1#==1 && #LBCLSIG1#==null) || (#LBNRIND2_1#==1 && #LBCLSIG2#==null) || (#LBNRIND3_1#==1 && #LBCLSIG3#==null) || (#LBNRIND4_1#==1 && #LBCLSIG4#==null) || (#LBNRIND5_1#==1 && #LBCLSIG5#==null) || (#LBNRIND6_1#==1 && #LBCLSIG6#==null) || (#LBNRIND7_1#==1 && #LBCLSIG7#==null) )','At least one parameter is out of range but there is no indication about clinically relevance. Please provide the data.'];
HH_CROSS_CHECK[30] = ['1','LBCLSIG1','','W','( #LBCLSIG1#==806002 || #LBCLSIG2#==806002 || #LBCLSIG3#==806002 || #LBCLSIG4#==806002 || #LBCLSIG5#==806002 || #LBCLSIG6#==806002 || #LBCLSIG7#==806002)','At least one parameter is clinically relevant. Please record the relevant adverse event in the Adverse events form.'];
HH_CROSS_CHECK[31] = ['1','LBURPER','','B','(#LBURPER#==806001 && (#LBURDATD#!=null||#LBURDATM#!=null||#LBURDATY#!=null||#LBUREVA#!=null||#LBURDET#!="NULL"))','Answer to the question "\Test performed\" for urinalysis is No, but some details were specified. Please check the data.'];
HH_CROSS_CHECK[32] = ['1','LBURPER','','B','(#LBURPER#==806002 && ((#LBURDATD#==null && #LBURDATM#==null && #LBURDATY#==null) || #LBUREVA#==null))','Urinalysis test was performed, please specify sampling date and Result evaluation.'];
HH_CROSS_CHECK[33] = ['1','LBUREVA','','B','(#LBUREVA#==840003 && #LBURDET#=="NULL")','Result evaluation for urinalisys is Clinically relevant. Please specify details.'];
HH_CROSS_CHECK[34] = ['1','ABNORM','','B','(#ABNORM#==806002 && #GALLSTON#!=1 && #BILTRDIL#!=1 && #FINOTH#!=1 && #FINOTHSP#=="NULL")','Answer to the question "\Any abnormality\" is Yes, please specify Findings (tick all applicable choices).'];
HH_CROSS_CHECK[35] = ['1','FINOTH','','B','(#FINOTH#==1 && #FINOTHSP#=="NULL")','Findings: Other is ticked, please specify the findings.'];
HH_CROSS_CHECK[36] = ['1','PSAPERF','','B','(#PSAPERF#==806002 && ((#PSADATD#==null && #PSADATM#==null && #PSADATY#==null) || #PSARES#=="NULL"))','PSA test was perforemd. Please specify details (sampling date and result).'];
HH_CROSS_CHECK[37] = ['1','PSAREDO','','B','(#PSAREDO#==806002 && ((#PSADAT2D#==null && #PSADAT2M#==null && #PSADAT2Y#==null) || #PSARES2#=="NULL"))','PSA test was re-done. Please specify details (sampling date and result).'];
HH_CROSS_CHECK[38] = ['1','TSTPERF','','B','(#TSTPERF#==806002 && ((#TSTDATD#==null && #TSTDATM#==null && #TSTDATY#==null) || #TSTRES#=="NULL" || #TSTUN#==null))','Testosterone test was perforemd. Please specify details (sampling date, result and unit).'];
HH_CROSS_CHECK[39] = ['1','TSTREDO','','B','(#TSTREDO#==806002 && ((#TSTDAT2D#==null && #TSTDAT2M#==null && #TSTDAT2Y#==null) || #TSTRES2#=="NULL" || #TSTUN2#==null))','Testosterone test was re-done. Please specify details (sampling date, result and unit).'];
HH_CROSS_CHECK[40] = ['1','CGAPERF','','B','(#CGAPERF#==806002 && ((#CGADATD#==null && #CGADATM#==null && #CGADATY#==null) || #CGAMETH#==null))','Cga test was perforemd. Please specify details (sampling date and method used).'];
HH_CROSS_CHECK[41] = ['1','CGAREDO','','B','(#CGAREDO#==806002 && ((#CGADAT2D#==null && #CGADAT2M#==null && #CGADAT2Y#==null) || #CGAMETH2#==null))','Cga test was re-done. Please specify details (sampling date and method used).'];
HH_CROSS_CHECK[42] = ['1','CTCPERF','','B','(#CTCPERF#==806002 && #CTCDATD#==null && #CTCDATM#==null && #CTCDATY#==null )','CTC test was perforemd. Please specify sampling date.'];
HH_CROSS_CHECK[43] = ['1','OTHER','','B','(#OTHER#==838002 && #OTHERSP#=="NULL" )','Other symptoms is Yes, please specify details.'];
HH_CROSS_CHECK[44] = ['1','EXAM','','B','(#EXAM#==826003 && #EXAMOTH#=="NULL" )','Exam performed is Other, please specify.'];
HH_CROSS_CHECK[45] = ['1','BONE','','B','(#BONE#==827002 && #B_SKULL#!=1 && #B_JAW#!=1 && #B_CERVER#!=1 && #B_THOVER#!=1 && #B_RIBS#!=1 && #B_LUMVER#!=1 && #B_SACRUM#!=1 && #B_PELVIS#!=1 && #B_SCAPULA#!=1 && #B_HUULRA#!=1 && #B_HAND#!=1 && #B_FETIFI#!=1 && #B_FEET#!=1 && #B_OTH#!=1)','Answer to the question "Bone metastases" is Yes. Please specify location.'];
HH_CROSS_CHECK[46] = ['1','B_OTH','','B','(#B_OTH#==1 && #B_OTHSP#=="NULL" )','Bone metastases: Other location is ticked. Please specify the location.'];
HH_CROSS_CHECK[47] = ['1','LYMPH','','B','(#LYMPH#==827002 && #LYMPHLOC#=="NULL" )','Answer to the question "\Lymph nodes involvement\" is Yes. Please specify location.'];
HH_CROSS_CHECK[48] = ['1','OTHLOC','','B','(#OTHLOC#==827002 && #OTHLOCSP#=="NULL" )','Answer to the question "\Other metastases\" is Yes. Please specify location.'];
HH_CROSS_CHECK[49] = ['1','FREQ','','B','(#FREQ#==828004 && #FREQOTH#=="NULL" )','Frequency: Other has been ticked, please specify.'];
HH_CROSS_CHECK[50] = ['1','ROUTE','','B','(#ROUTE#==938290 && #ROUTEOTH#=="NULL" )','Route of administration: Other has been ticked, please specify.'];
HH_CROSS_CHECK[51] = ['1','CMENDATD','','B','(#CMENDATD#==null && #CMENDATM#==null && #CMENDATY#==null && #CMONGO#!=1 )','Please specify end date or Ongoing at the end of the study.'];
HH_CROSS_CHECK[52] = ['1','CMENDATD','','B','(#CMENDATD#!=null && #CMENDATM#!=null && #CMENDATY#!=null && #CMONGO#==1 )','End date is filled in but also Ongoing is ticked. Please check the data.'];
HH_CROSS_CHECK[53] = ['1','CMSTDATD','','B','(d1d2("#CMSTDATD#/#CMSTDATM#/#CMSTDATY#","#CMENDATD#/#CMENDATM#/#CMENDATY#",">"))','Start date is after end date. Please check the data.'];
HH_CROSS_CHECK[54] = ['1','CMDOSU','','B','(#CMDOSU#==830002 && #CMDOSUOT#=="NULL" )','Unit: Other has been ticked, please specify.'];
HH_CROSS_CHECK[55] = ['1','CMDOSFRQ','','B','(#CMDOSFRQ#==831010 && #CMDSFROT#=="NULL" )','Frequency: Other has been ticked, please specify.'];
HH_CROSS_CHECK[56] = ['1','CMROUTE','','B','(#CMROUTE#==832003 && #CMROUTOT#=="NULL" )','Route of administration: Other has been ticked, please specify.'];
HH_CROSS_CHECK[57] = ['1','AESTDATD','','B','(d1d2("#AESTDATD#/#AESTDATM#/#AESTDATY#",#HD_DMDAT#,"<") && #HD_DMDATRC#=="OKOKOK" )','Start date is before informed consent date. If start date is correct, the event should be recorded in the medical history form. Please check the data.'];
HH_CROSS_CHECK[58] = ['1','AESTDATD','','B','(d1d2("#AESTDATD#/#AESTDATM#/#AESTDATY#","#AEENDATD#/#AEENDATM#/#AEENDATY#",">"))','Start date is after end date. Please check the data.'];
HH_CROSS_CHECK[59] = ['1','AESER','','B','(#AESER#==806002 && #AESDTH#!=1 && #AESLIFE#!=1 && #AESHOSP#!=1 && #AESDISAB#!=1 && #AESCONG#!=1 && #AESMIE#!=1)','Answer to the question Is the AE serious? Is Yes. Please specify seriousness criteria.'];
HH_CROSS_CHECK[60] = ['1','AEOUT','','B','(#AEOUT#==949498 && #AEENDATD#==null && #AEENDATM#==null && #AEENDATY#==null)','Outcome is Recovered. Please specify end date.'];
HH_CROSS_CHECK[61] = ['1','AEOUT','','B','(#AEOUT#!=949498 && #AEENDATD#!=null && #AEENDATM#!=null && #AEENDATY#!=null)','End date is specified but should be filled in only if Outcome is Recovered.'];
HH_CROSS_CHECK[62] = ['1','AEOUT','','B','(#AEOUT#==948275 && #AEDEDATD#==null && #AEDEDATM#==null && #AEDEDATY#==null)','Outcome is Fatal. Please specify Date of death.'];
HH_CROSS_CHECK[63] = ['1','CGAMETH','','B','(#CGAMETH#==841001 && #CGARESE#=="NULL")','Cga test was perforemd. Please specify result.'];
HH_CROSS_CHECK[64] = ['1','CGAMETH','','B','(#CGAMETH#==841002 && #CGARESI#=="NULL")','Cga test was perforemd. Please specify result.'];
HH_CROSS_CHECK[65] = ['1','CGAMETH2','','B','(#CGAMETH2#==841001 && #CGARESE2#=="NULL")','Cga test was re-done. Please specify result.'];
HH_CROSS_CHECK[66] = ['1','CGAMETH2','','B','(#CGAMETH2#==841002 && #CGARESI2#=="NULL")','Cga test was re-done. Please specify result.'];
HH_CROSS_CHECK[67] = ['1','RNDYN','','B','(#RNDYN#==806002 && #RNDNOREA#=="NULL")','The patient cannot be randomised (answer to the first question is Yes). Please specify the reason.'];
HH_CROSS_CHECK[68] = ['1','RNDYN','','W','(#RNDYN#==806002)','The patient cannot be randomized, please fill in the Study termination form.'];
HH_CROSS_CHECK[69] = ['1','LBPERF','','B','(#LBPERF#==806002 && isNotDate("#LBDATD#/#LBDATM#/#LBDATY#"))','Sampling Date is not a date. Please check the data.'];
HH_CROSS_CHECK[70] = ['1','IEYN','','W','(#IEYN#==806001)','Eligibility criteria are not still met. The patient is a violator or should be excluded from the study. If it is an error, please change the data.'];
HH_CROSS_CHECK[71] = ['1','MHONGO','','B','(#MHONGO#!=1 && #MHENDATD#==null && #MHENDATM#==null && #MHENDATY#==null)','Please specify End date or Ongoing or sequelae at start of study.'];
HH_CROSS_CHECK[72] = ['1','ANDENDTD','','B','(d1d2("#ANDENDTD#/#ANDENDTM#/#ANDENDTY#",#HD_DMDAT#,">") && #HD_DMDATRC#=="OKOKOK" )','Date of last administration (therapy with Antiandrogens) is after informed consent date. Please check the dates, if correct tick "\Ongoing at time of screening\" and delete Date.'];
HH_CROSS_CHECK[73] = ['1','LBNRIND1_1','','B','((#LBNRIND1_1#!=1 && #LBCLSIG1#!=null) || (#LBNRIND2_1#!=1 && #LBCLSIG2#!=null) || (#LBNRIND3_1#!=1 && #LBCLSIG3#!=null) || (#LBNRIND4_1#!=1 && #LBCLSIG4#!=null) || (#LBNRIND5_1#!=1 && #LBCLSIG5#!=null) || (#LBNRIND6_1#!=1 && #LBCLSIG6#!=null) || (#LBNRIND7_1#!=1 && #LBCLSIG7#!=null) )','Clinical relevance must be specified only if the parameter is out of range. Please delete the data about Clinical relevance where not required.'];
HH_CROSS_CHECK[74] = ['1','LBPERF','','B','(#LBPERF#==806001 && #LBDATD#!=null && #LBDATM#!=null && #LBDATY#!=null )','Answer to the question "\Test performed\"  is No, but date was specified. Please check the data.'];
HH_CROSS_CHECK[75] = ['1','DRUGADM','','W','(#DRUGADM#==806002 && (#HD_RANDARM#==825001 || #HD_RNDYN#==806002))','The patient has been randomised in Arm A (treatment with non steroidal anti androgens and LHRH-a, without Lanreotide) or has not been randomised. Please check the data.'];
HH_CROSS_CHECK[76] = ['1','PSADATD','','B','(d1d2("#PSADATD#/#PSADATM#/#PSADATY#",#HD_DMDAT#,">") && #HD_DMDATRC#=="OKOKOK" )','PSA sampling date is after informed consent date. Please check the data.'];
HH_CROSS_CHECK[77] = ['1','PSAPREDTD','','B','(d1d2("#PSAPREDTD#/#PSAPREDTM#/#PSAPREDTY#",#HD_DMDAT#,">") && #HD_DMDATRC#=="OKOKOK" )','Date of PSA before study inclusion is after informed consent date. Please check the data.'];
HH_CROSS_CHECK[78] = ['1','INJDONE','','B','(#INJDONE#==806002 && #INJDATD#==null && #INJDATM#==null && #INJDATY#==null)','The injection was done but the date of injection is missing. Please check the data.'];
HH_CROSS_CHECK[79] = ['1','INJDONE','','B','(#INJDONE#==806001 && #INJCOMM#=="NULL" )','The injection wasn\'t done. Please specify why the injection was missed.'];
HH_CROSS_CHECK[80] = ['1','AESEV','','B','((#AESEV#==941341 || #AESEV#==941342) && #AESER#==806001 )','Life threatening/disabling and Death are AE serious. Please tick "Yes" to the answer "\Is the AE serious?\" or check the field "\Maximal Intensity\".'];
HH_CROSS_CHECK[81] = ['1','AESEV','','B','( #AESEV#==941342 && #AEOUT#!=948275 )','Maximal intensity is "\Death\" but Outcome is not "\Fatal\". Please check the data.'];
HH_CROSS_CHECK[82] = ['1','AESEV','','B','( #AESEV#==941342 && #AESDTH#!=1 )','Maximal intensity is "\Death\" but Seriousness criteria "\Fatal\" is not ticked. Please check the data.'];
HH_CROSS_CHECK[83] = ['1','AESEV','','B','(#AESEV#==941341 && #AESLIFE#!=1 && #AESDISAB#!=1 )','Maximal intensity is "\Life threatening/disabling\": at least one between "\Life threatening\"  or "\Significant disability/incapacity\" must be ticked as seriousness criteria.'];
HH_CROSS_CHECK[84] = ['1','RACE','','B','(#RACE#==805005 && #RACE_OTH#=="NULL")','Race is "\Other\". Please specify the race.'];
HH_CROSS_CHECK[85] = ['1','TSTUN','','B','(#TSTUN#==824003 && #TSTUNOT#=="NULL")','Serum testosterone unit: Other is ticked, please specify the unit.'];
HH_CROSS_CHECK[86] = ['1','TSTUN2','','B','(#TSTUN2#==824003 && #TSTUN2OT#=="NULL")','Serum testosterone unit: Other is ticked, please specify the unit.'];
HH_CROSS_CHECK[87] = ['1','DMDATD','','B','(d1d2("#DMDATD#/#DMDATM#/#DMDATY#",#HD_VIDAT#,">") && #HD_VIDATRC#=="OKOKOK" )','Informed consent date cannot be after Visit 1 date. Please check the data.'];
HH_CROSS_CHECK[88] = ['1','VIDATD','','B','(d1d2("#VIDATD#/#VIDATM#/#VIDATY#",#HD_DMDAT#,"<") && #HD_DMDATRC#=="OKOKOK" )','Visit 1 date cannot be before informed consent date. Please check the data.'];
HH_CROSS_CHECK[89] = ['1','VIDATD','','B','(d1d2("#VIDATD#/#VIDATM#/#VIDATY#",#HD_VIDAT1#,"<=") && #HD_VIDATRC1#=="OKOKOK" )','This visit date is before previous visit date. Please check the data.'];
HH_CROSS_CHECK[90] = ['1','VIDATD','','B','(d1d2("#VIDATD#/#VIDATM#/#VIDATY#",#HD_VIDAT2#,"<=") && #HD_VIDATRC2#=="OKOKOK" )','This visit date is before previous visit date. Please check the data.'];
HH_CROSS_CHECK[91] = ['1','VIDATD','','B','(d1d2("#VIDATD#/#VIDATM#/#VIDATY#",#HD_VIDAT3#,"<=") && #HD_VIDATRC3#=="OKOKOK" )','This visit date is before previous visit date. Please check the data.'];
HH_CROSS_CHECK[92] = ['1','VIDATD','','B','(d1d2("#VIDATD#/#VIDATM#/#VIDATY#",#HD_VIDAT4#,"<=") && #HD_VIDATRC4#=="OKOKOK" )','This visit date is before previous visit date. Please check the data.'];
HH_CROSS_CHECK[93] = ['1','VIDATD','','B','(d1d2("#VIDATD#/#VIDATM#/#VIDATY#",#HD_VIDAT5#,"<=") && #HD_VIDATRC5#=="OKOKOK" )','This visit date is before previous visit date. Please check the data.'];
HH_CROSS_CHECK[94] = ['1','VIDATD','','B','(d1d2("#VIDATD#/#VIDATM#/#VIDATY#",#HD_VIDAT6#,"<=") && #HD_VIDATRC6#=="OKOKOK" )','This visit date is before previous visit date. Please check the data.'];
HH_CROSS_CHECK[95] = ['1','VIDATD','','B','(d1d2("#VIDATD#/#VIDATM#/#VIDATY#",#HD_VIDAT7#,"<=") && #HD_VIDATRC7#=="OKOKOK" )','This visit date is before previous visit date. Please check the data.'];
HH_CROSS_CHECK[96] = ['1','VIDATD','','B','(d1d2("#VIDATD#/#VIDATM#/#VIDATY#",#HD_VIDAT8#,"<=") && #HD_VIDATRC8#=="OKOKOK" )','This visit date is before previous visit date. Please check the data.'];
HH_CROSS_CHECK[97] = ['1','VIDATD','','B','(d1d2("#VIDATD#/#VIDATM#/#VIDATY#",#HD_VIDAT9#,"<=") && #HD_VIDATRC9#=="OKOKOK" )','This visit date is before previous visit date. Please check the data.'];
HH_CROSS_CHECK[98] = ['1','AEACNOTH','','B','(#AEACNOTH#==817003 && #AEACNOT2#=="NULL")','Other action taken is "\Other\", please specify Other action taken.'];
HH_CROSS_CHECK[99] = ['1','AEOUT','','B','(#AEOUT#!=948275 && #AEDEDATD#!=null && #AEDEDATM#!=null && #AEDEDATY#!=null)','Date of death must be filled in only if Outcome is Fatal. Please check the data.'];
HH_CROSS_CHECK[100] = ['1','LBEXT1_1','','B','(#LBEXT1_1#==1 && (#LBORRESUE1#=="NULL" || #LBORNRLOE1#=="NULL" || #LBORNRHIE1#=="NULL"))','Hemoglobin: Ext.Lab is ticked; please specify Unit Min e Max.'];
HH_CROSS_CHECK[101] = ['1','LBEXT2_1','','B','(#LBEXT2_1#==1 && (#LBORRESUE2#=="NULL" || #LBORNRLOE2#=="NULL" || #LBORNRHIE2#=="NULL"))','Absolute neutrophil count: Ext.Lab is ticked; please specify Unit Min e Max.'];
HH_CROSS_CHECK[102] = ['1','LBEXT3_1','','B','(#LBEXT3_1#==1 && (#LBORRESUE3#=="NULL" || #LBORNRLOE3#=="NULL" || #LBORNRHIE3#=="NULL"))','Platelets: Ext.Lab is ticked; please specify Unit Min e Max.'];
HH_CROSS_CHECK[103] = ['1','LBEXT4_1','','B','(#LBEXT4_1#==1 && (#LBORRESUE4#=="NULL" || #LBORNRLOE4#=="NULL" || #LBORNRHIE4#=="NULL"))','Total bilirubin: Ext.Lab is ticked; please specify Unit Min e Max.'];
HH_CROSS_CHECK[104] = ['1','LBEXT5_1','','B','(#LBEXT5_1#==1 && (#LBORRESUE5#=="NULL" || #LBORNRLOE5#=="NULL" || #LBORNRHIE5#=="NULL"))','AST: Ext.Lab is ticked; please specify Unit Min e Max.'];
HH_CROSS_CHECK[105] = ['1','LBEXT6_1','','B','(#LBEXT6_1#==1 && (#LBORRESUE6#=="NULL" || #LBORNRLOE6#=="NULL" || #LBORNRHIE6#=="NULL"))','ALT: Ext.Lab is ticked; please specify Unit Min e Max.'];
HH_CROSS_CHECK[106] = ['1','LBEXT7_1','','B','(#LBEXT7_1#==1 && (#LBORRESUE7#=="NULL" || #LBORNRLOE7#=="NULL" || #LBORNRHIE7#=="NULL"))','Serum creatinine: Ext.Lab is ticked; please specify Unit Min e Max.'];
HH_CROSS_CHECK[107] = ['1','DSCOMP','','B','(#DSCOMP#==806002 && #DSSTDATD#==null && #DSSTDATM#==null && #DSSTDATY#==null)','The patient discontinued the study before week 96, please specify Date of last contact.'];
HH_CROSS_CHECK[108] = ['1','DSCOMP','','B','(#DSCOMP#==806002 && #DSDECOD#==null )','The patient discontinued the study before week 96, please specify Main reason for discontinuation.'];
HH_CROSS_CHECK[109] = ['1','DSDECOD','','B','(#DSDECOD#==917649 && #DSDECODS#=="NULL")','Main reason for discontinuation is Other. Please specify the main reason for discontinuation.'];
HH_CROSS_CHECK[110] = ['1','AESEV','','W','((#AESEV#==941341 || #AESEV#==941342) && #AEREL#==803004 )','At least one adverse event occurred with maximal intensity \> Grade 3 and related to study treatment. The patient should be withdrawn form the study.'];






