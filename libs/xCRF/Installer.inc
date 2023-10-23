<?
include_once "study_prototype.inc";
 /**
  * Classe per l'installazione di un nuovo servizio
  *
  * @package Hyper
  */
 class Installer{
 		
 	/**
 	 * Costruttore dell'oggetto, vengono presi in ingresso le informazione relative alla
     * connessione oracle, al prefisso in banca dati del servizio, alle configurazioni di sistema.
 	 *
 	 * @param String $service
 	 * @param dbconn_hyper $conn
 	 * @param array $config_service
 	 * @return Installing XMR ...
 	 * 
	 *
	 ************************
	 *  					*
	 *  NUOVO INSTALLER 	*
	 *  VMAZZEO 29.01.2014	*
	 * 						* 
	 ************************
	 *    
	 *  1) sotto study/[nuovostudio]/
	 *	cp -p  ../libs/cro/installer/index.php .
	 *	cp -rp ../libs/cro/installer/uxmr/ .
	 *
	 *	2) Configurare study.xml --> sezione WF standard, non modificare! (cambiare solo prefisso e nome servizio/studio)
	 *	4) Lanciare ?init_service. 
 	 *  5) Lanciare ?install.
 	 *  6)  	 
 	 *  
 	 *  
 	 *  
 	 *  
 	 ************************************ 
 	 * TIP: SE STUDIO CON DDE INSTALLARE DDE IN DEV PRIMA DI COPIARE IN PRODUZIONE 
 	 * 
 	 * ***INSTALLAZIONE DDE (da InQuPl_DDECOOMPARE_1.0.doc):
 	 * ***1		Link /http/lib/XMR/hyperibs/libs_dde:
 	 *  
	 *			ln -s /http/lib/XMR/hyperlibs/libs_dde/ libs
	 *			
	 * ***2		Link ai fields from /http/lib/XMR/hyperlibs/libs_dde/fields sotto fields
	 * 
	 *			cp -s /http/lib/XMR/hyperlibs/libs_dde/fields/* ./
	 *			
 	 * ***3 	Link DDEPatientExists sotto f_to_calls (e disabilitare  E_subjid_exist.inc ->  D_subjid_exist.inc )
 	 *  
	 *			ln -s /http/lib/XMR/hyperlibs/modules/f_to_calls/dde_patient_exists.inc E_dde_patient_exists.inc
 	 *
 	 * ***4		Register DDEPatientExists as f_to_call in the registration form xml
	 *			
	 *			f_to_call="DDEPatientExists"
 	 * 
 	 * ***5		Create registration table for the study (da  new patient registration COME 59900001)
 	 * 			
 	 * ***6		Create class DDE_module extends DDE_module_prototype nel config.inc
	 *			
	 *			class DDE_module extends DDE_module_prototype{}
	 *
	 * ***7		Make an access by web
	 * 	
	 * ***8		Verify tha following elements has been created  in db:
	 *			tables
	 *			[service]_dde_exams, 
	 *			[service] _dde_logcomp, 
	 *			[service]_dde_patients	
	 *			sequence:
	 *			[service] _DDE_LOGSEQ,
	 *			triggers:
	 *			[service] _check_status_query_ai, 
	 *			[service]_check_status_query_ai2, 
	 *			[service] _check_status_query_bi
	 *			packages:
	 *			[service]_check_status_query_pkg
	 *
	 * ***9		INSERIRE LINK IN HOMEPAGE DEL DM COME PER ALTRI STUDI DDE (prendi ad esempio igpro20-4002)
	 * 			sotto html
	 * 			ln -s /http/lib/XMR/hyperlibs/clear_compare_cache.php .
	 *
	 * ***10	AGGIORNARE LA HOME DEL DATAMANGER INSERENDO I LINK ALLA FUNZIONE COMPARE E CLEAR COMPARE (prendi ad esempio igpro20-4002)
	 ************************************
 	 * 8-COPIA IN PRODUZIONE: 
 	 * *** MEMO PER STUDI TEDESCHI: MODIFICA TUTTE LE PWD IN P123456% ( $apr1$vmt.....$YrBa7rSPbsYjr2cXVQhfp0 ) ***
DB:
source /etc/oraenv
cd estrazioni
--db04
exp [ORAUSER_DEV]/[PASSWORD_DEV (il punto escalamativo della password vuole lo \)]@pierrel_siss_dev file=[NOMESTUDIO][DATA].dmp
imp [ORAUSER]/[PASSWORD_PREPROD(TEST)]@pierrel_siss_preprod file=[NOMESTUDIO][DATA].dmp  fromuser=[ORAUSER_DEV] touser=[ORAUSER_DEST]  
--> dopo ogni importazione bisogna ricreare il job
imp [ORAUSER_QA]/[PASSWORD_PREPROD(-preprod)]@pierrel_siss_preprod file=[NOMESTUDIO][DATA].dmp  fromuser=[ORAUSER_DEV] touser=[ORAUSER_QA]  
--> dopo ogni importazione bisogna ricreare il job
--db03
imp [ORAUSER]/[PASSWORD_PROD]@pierrel_siss_prod file=[NOMESTUDIO][DATA].dmp  fromuser=[NOMESTUDIO] touser=[NOMESTUDIO_DEST]  
--> dopo ogni importazione bisogna ricreare il job

DECLARE
  X NUMBER;
BEGIN
  SYS.DBMS_JOB.SUBMIT
  ( job       => X 
   ,what      => 'begin DBMS_MVIEW.REFRESH(''T_USER_TAB_COLUMNS''); end; '
   ,next_date => TRUNC(SYSDATE+1)+6/24
   ,interval  => 'TRUNC(SYSDATE+1)+6/24'
   ,no_parse  => FALSE
  );
  SYS.DBMS_OUTPUT.PUT_LINE('Job Number is: ' || to_char(x));
COMMIT;
END;

EXAMPLE:
exp sire_dev/SRE2411\!@pierrel_siss_dev file=sire_dev25112010.dmp
imp sire/SRE2411\!@pierrel_siss_preprod file=sire_dev25112010.dmp fromuser=sire_dev touser=sire
imp sire/SRE2411\!@pierrel_siss_prod file=sire_dev25112010.dmp fromuser=sire_dev touser=sire

IDP:
FARE LE OPERAZIONE PER CONFIGURARE IDP SU http://idp-aifa.sissdev.cineca.it/Servizi.php:
	- cambiare i triggers di shibboleth modificando l'utenza di IDP corretta (preprod) - in produzione è già ok.
	- eventualmente verificare anche il dominio -preprod (che ha un ID diverso)
	
	- su IDP preprod e prod dare i grant
	- su IDP preprod e prod inserire gli utenti:
insert into  IDP_PIERREL(_PREPROD).utenti_gruppi_view select u.USERID, u.ID_GRUPPOU, u.ABILITATO, [ID] as ID_SERVIZIO from utenti_gruppiu u;
insert into IDP_PIERREL(_PREPROD).utenti_view select u.userid, u.password, [ID] as id_princ_serv, u.abilitato from utenti u;
commit;
CREATE OR REPLACE SYNONYM IDP_SERVIZI FOR IDP_PIERREL(_PREPROD).SERVIZI;
CREATE OR REPLACE SYNONYM IDP_SPEC FOR IDP_PIERREL(_PREPROD).IDP_SPEC;
 

=====> ATTIVARE PROCEDURA PCONNECT E RELATIVO JOB (vedi sotto) <=====

FS:
rsync -Cavuzn /http/servizi/PIERREL/[NOMESTUDIO]/ /sissprep/http/servizi/PIERREL/[NOMESTUDIO]/
rsync -Cavuzn /sissprep/http/servizi/PIERREL/[NOMESTUDIO]/ /sissprod/http/servizi/PIERREL/[NOMESTUDIO]/ --exclude "html/filemanager/" --exclude "html/phporaadmin" --exclude "html/XMLValidator"

***** NEL CASO DIA ERRORE SHIBBOLETH *******
* controllare che sia tutto a posto in /etc/shibboleth/shibboleth2.xml
* e controllare il metadata
*

	 * 10) Generare il report da consegnare:
	 * - partendo dal doc "generico", compilarlo con tutti gli screenshot richiesti (pwd 59900001-> m123456%->m123456+
	 * - copiare da /http/servizi/PIERREL/[SERVIZIO]/html/uxmr/xml:
	 * 		- [SERVIZIO]_IQ_report
	 * 		- [SERVIZIO]InstallReport.log
	 * 		- InstallReport.log
	 * - fare alcuni screenshot:
	 * 		- ping di .test e prod. (es. ping inside.test.hypernetproject.com)
	 * 		- tracert di .test e prod (es. tracert inside.test.hypernetproject.com)
	 * - zippare tutto (compresa la cartella installation_[SERVIZIO]_report
	 * - inviare via mail: oggetto Studio [SERVIZIO] inviare a:
	 * 		- Marco Francesconi (m.francesconi@pierrel-research.com)
	 * 		- CC:Margherita Di Caro (m.dicaro@pierrel-research.com)
	 * 		- CC:Francesco Camapana (hypersuite@cineca.it)
	 * 
	 * 
	 * 11) Copiare i nuovi fields da un servizio recente (dovrebbe sparire questa operazione)
	 * - da dentro [SERVIZIO]/html/uxmr: rsync -Cavuzn /sissprep/http/servizi/PIERREL/aaaiii01/html/uxmr/fields/ fields/
	 * 
*
*
***************** PENTAHO *********************
--Test
sqlplus pentaho_preprod/htn0110\!@sissdevel

insert into AUTHORITIES (AUTHORITY, DESCRIPTION) values ('&nomestudio.-INV','User has logged in &nomestudio. as Investigator');
insert into AUTHORITIES (AUTHORITY, DESCRIPTION) values ('&nomestudio.-991','User has logged in &nomestudio.');
insert into AUTHORITIES (AUTHORITY, DESCRIPTION) values ('&nomestudio.-995','User has logged in &nomestudio.');
insert into AUTHORITIES (AUTHORITY, DESCRIPTION) values ('&nomestudio.-994','User has logged in &nomestudio.');
insert into AUTHORITIES (AUTHORITY, DESCRIPTION) values ('&nomestudio.-996','User has logged in &nomestudio.');
insert into AUTHORITIES (AUTHORITY, DESCRIPTION) values ('&nomestudio.-997','User has logged in &nomestudio.');
grant all on USERS to &nomestudio.;
grant all on GRANTED_AUTHORITIES to &nomestudio.;
commit;
exit;

--es. "liaison"

--pentaho_preprod da servizio@sissdevel

sqlplus nomeservizio/password@sissdevel

CREATE OR REPLACE TRIGGER PENTAHO_UTENTI_TR
AFTER INSERT OR UPDATE OR DELETE  ON UTENTI REFERENCING OLD AS v NEW AS newRow for each row
BEGIN
if updating then
update PENTAHO_PREPROD.USERS
set 
"PASSWORD"=:newRow.password,
"ENABLED"=:newRow.abilitato
where "USERNAME"=:v.userid||'@&ID..PIERREL_PREPROD';
end if;
if inserting and (
    substr(:newRow.userid,0,3) like '997' or
    substr(:newRow.userid,0,3) like '996' or
    substr(:newRow.userid,0,3) like '995' or
    substr(:newRow.userid,0,3) like '994' or
    substr(:newRow.userid,0,3) like '991' or
   (substr(:newRow.userid,0,2) >='0' and substr(:newRow.userid,0,2) <='9')) then
insert into PENTAHO_PREPROD.USERS (USERNAME, PASSWORD, ENABLED)
values(:newRow.userid||'@&ID..PIERREL_PREPROD',:newRow."PASSWORD",:newRow.abilitato);
insert into PENTAHO_PREPROD.GRANTED_AUTHORITIES (USERNAME, AUTHORITY)
values(:newRow.userid||'@&ID..PIERREL_PREPROD','Authenticated');
insert into PENTAHO_PREPROD.GRANTED_AUTHORITIES (USERNAME, AUTHORITY)
values(:newRow.userid||'@&ID..PIERREL_PREPROD','bi-authenticated');
end if;
if inserting and substr(:newRow.userid,0,3) = '997' then
insert into PENTAHO_PREPROD.GRANTED_AUTHORITIES (USERNAME, AUTHORITY)
values(:newRow.userid||'@&ID..PIERREL_PREPROD','&nomestudio.-997');
end if;
if inserting and substr(:newRow.userid,0,3) = '996' then
insert into PENTAHO_PREPROD.GRANTED_AUTHORITIES (USERNAME, AUTHORITY)
values(:newRow.userid||'@&ID..PIERREL_PREPROD','&nomestudio.-996');
end if;
if inserting and substr(:newRow.userid,0,3) = '995' then
insert into PENTAHO_PREPROD.GRANTED_AUTHORITIES (USERNAME, AUTHORITY)
values(:newRow.userid||'@&ID..PIERREL_PREPROD','&nomestudio.-995');
end if;
if inserting and substr(:newRow.userid,0,3) = '994' then
insert into PENTAHO_PREPROD.GRANTED_AUTHORITIES (USERNAME, AUTHORITY)
values(:newRow.userid||'@&ID..PIERREL_PREPROD','&nomestudio.-994');
end if;
if inserting and substr(:newRow.userid,0,3) = '991' then
insert into PENTAHO_PREPROD.GRANTED_AUTHORITIES (USERNAME, AUTHORITY)
values(:newRow.userid||'@&ID..PIERREL_PREPROD','&nomestudio.-991');
end if;
if inserting and substr(:newRow.userid,0,2) >='0' and substr(:newRow.userid,0,2) <='9' then
insert into PENTAHO_PREPROD.GRANTED_AUTHORITIES (USERNAME, AUTHORITY)
values(:newRow.userid||'@&ID..PIERREL_PREPROD','&nomestudio.-INV');
end if;
if deleting then
delete PENTAHO_PREPROD.GRANTED_AUTHORITIES where USERNAME=:v.userid||'@&ID..PIERREL_PREPROD';
delete PENTAHO_PREPROD.USERS where USERNAME=:v.userid||'@&ID..PIERREL_PREPROD';
end if;
END;
/

--da eseguire dal servizio

insert into PENTAHO_PREPROD.USERS (USERNAME, PASSWORD, ENABLED)
select  userid||'@&ID..PIERREL_PREPROD',PASSWORD,abilitato
from utenti where (userid like '991%' or userid like '995%' or userid like '994%' or userid like '996%' or
userid like '997%' or userid <'9') and userid||'@&ID..PIERREL_PREPROD' not in (select USERNAME from PENTAHO_PREPROD.USERS);

insert into PENTAHO_PREPROD.GRANTED_AUTHORITIES (USERNAME, AUTHORITY)
select userid||'@&ID..PIERREL_PREPROD','Authenticated' from utenti where (userid like '991%' or userid like '995%' or userid like '994%' or userid like '996%' or
userid like '997%' or userid <'9') and userid||'@&ID..PIERREL_PREPROD' not in (select USERNAME from PENTAHO_PREPROD.GRANTED_AUTHORITIES 
where AUTHORITY like 'Authenticated');

insert into PENTAHO_PREPROD.GRANTED_AUTHORITIES (USERNAME, AUTHORITY)
select userid||'@&ID..PIERREL_PREPROD','bi-authenticated' from utenti where (userid like '991%' or userid like '995%' or userid like '994%' or userid like '996%' or
userid like '997%' or userid <'9') and userid||'@&ID..PIERREL_PREPROD' not in (select USERNAME from PENTAHO_PREPROD.GRANTED_AUTHORITIES 
where AUTHORITY like 'bi-authenticated');

insert into PENTAHO_PREPROD.GRANTED_AUTHORITIES (USERNAME, AUTHORITY)
select userid||'@&ID..PIERREL_PREPROD','&nomestudio.-INV' from utenti where (userid <'9') and userid||'@&ID..PIERREL_PREPROD' not in (select USERNAME from PENTAHO_PREPROD.GRANTED_AUTHORITIES 
where AUTHORITY like '&nomestudio.-INV');

insert into PENTAHO_PREPROD.GRANTED_AUTHORITIES (USERNAME, AUTHORITY)
select userid||'@&ID..PIERREL_PREPROD','&nomestudio.-997' from utenti where (userid like '997%') and userid||'@&ID..PIERREL_PREPROD' not in (select USERNAME from PENTAHO_PREPROD.GRANTED_AUTHORITIES 
where AUTHORITY like '&nomestudio.-997');

insert into PENTAHO_PREPROD.GRANTED_AUTHORITIES (USERNAME, AUTHORITY)
select userid||'@&ID..PIERREL_PREPROD','&nomestudio.-991' from utenti where (userid like '991%') and userid||'@&ID..PIERREL_PREPROD' not in (select USERNAME from PENTAHO_PREPROD.GRANTED_AUTHORITIES 
where AUTHORITY like '&nomestudio.-991');

insert into PENTAHO_PREPROD.GRANTED_AUTHORITIES (USERNAME, AUTHORITY)
select userid||'@&ID..PIERREL_PREPROD','&nomestudio.-995' from utenti where (userid like '995%') and userid||'@&ID..PIERREL_PREPROD' not in (select USERNAME from PENTAHO_PREPROD.GRANTED_AUTHORITIES 
where AUTHORITY like '&nomestudio.-995');

insert into PENTAHO_PREPROD.GRANTED_AUTHORITIES (USERNAME, AUTHORITY)
select userid||'@&ID..PIERREL_PREPROD','&nomestudio.-994' from utenti where (userid like '994%') and userid||'@&ID..PIERREL_PREPROD' not in (select USERNAME from PENTAHO_PREPROD.GRANTED_AUTHORITIES 
where AUTHORITY like '&nomestudio.-994');

insert into PENTAHO_PREPROD.GRANTED_AUTHORITIES (USERNAME, AUTHORITY)
select userid||'@&ID..PIERREL_PREPROD','&nomestudio.-996' from utenti where (userid like '996%') and userid||'@&ID..PIERREL_PREPROD' not in (select USERNAME from PENTAHO_PREPROD.GRANTED_AUTHORITIES 
where AUTHORITY like '&nomestudio.-996');

commit;
CREATE SEQUENCE &prefisso._REP_LINKS_SEQ
  START WITH 1
  MAXVALUE 999999999999999999999999999
  MINVALUE 1
  NOCYCLE
  NOCACHE
  NOORDER;

CREATE TABLE &prefisso._REP_AMMIN
(
  USERID      VARCHAR2(40 CHAR)                 NOT NULL,
  GROUP_LINK  NUMBER                            NOT NULL,
  CONSTRAINT PK_&prefisso._REP_AMMIN
 PRIMARY KEY
 (USERID, GROUP_LINK)
)
LOGGING 
NOCOMPRESS 
NOCACHE
NOPARALLEL
MONITORING;

CREATE TABLE &prefisso._REP_LINKS
(
  ID          NUMBER                            NOT NULL,
  ID_REF      NUMBER,
  GROUP_LINK  NUMBER                            NOT NULL,
  TIPOLOGIA   NUMBER,
  TESTO       VARCHAR2(1000 CHAR),
  HREF        VARCHAR2(1000 CHAR),
  ABILITATO   NUMBER,
  ORDER_COL   NUMBER,
  TARGET      varchar2(100),
  CONSTRAINT PK_&prefisso._REP_LINKS
 PRIMARY KEY
 (ID, GROUP_LINK)
)
LOGGING 
NOCOMPRESS 
NOCACHE
NOPARALLEL
MONITORING;

CREATE TABLE &prefisso._REP_LINKS_THEME
(
  CONSTANT    VARCHAR2(40 CHAR)                 NOT NULL,
  VALUE       VARCHAR2(200 CHAR)                NOT NULL,
  GROUP_LINK  NUMBER                            NOT NULL,
  CONSTRAINT PK_&prefisso._REP_LINKS_THEME
 PRIMARY KEY
 (CONSTANT, GROUP_LINK)
)
LOGGING 
NOCOMPRESS 
NOCACHE
NOPARALLEL
MONITORING;


Insert into &prefisso._REP_AMMIN
   (USERID, GROUP_LINK)
 Values
   ('99700099', 0);
COMMIT;


Insert into &prefisso._REP_LINKS_THEME
   (CONSTANT, VALUE, GROUP_LINK)
 Values
   ('LK_HEIGHT', '0px', 0);
COMMIT;


CREATE TABLE &prefisso._LINK_GRUPPIU
(
  ID_LINK     NUMBER                            NOT NULL,
  GROUP_LINK  NUMBER                            NOT NULL,
  ID_GRUPPOU  NUMBER                            NOT NULL,
  CONSTRAINT PK_&prefisso._LINK_GRUPPIU
 PRIMARY KEY
 (ID_LINK, ID_GRUPPOU, GROUP_LINK),
  CONSTRAINT FK_&prefisso._LINK_GRUPPIU_IDGU 
 FOREIGN KEY (ID_GRUPPOU) 
 REFERENCES GRUPPIU (ID_GRUPPOU),
  CONSTRAINT FK_&prefisso._LINK_GRUPPIU_IDLINK 
 FOREIGN KEY (ID_LINK, GROUP_LINK) 
 REFERENCES &prefisso._REP_LINKS (ID,GROUP_LINK)
)
LOGGING 
NOCOMPRESS 
NOCACHE
NOPARALLEL
MONITORING;


exit;

--Preprod
sqlplus pentaho_preprod/htn0110\!@sissdevel

insert into AUTHORITIES (AUTHORITY, DESCRIPTION) values ('&nomestudio._qa-INV','User has logged in &nomestudio._qa as Investigator');
insert into AUTHORITIES (AUTHORITY, DESCRIPTION) values ('&nomestudio._qa-991','User has logged in &nomestudio._qa');
insert into AUTHORITIES (AUTHORITY, DESCRIPTION) values ('&nomestudio._qa-995','User has logged in &nomestudio._qa');
insert into AUTHORITIES (AUTHORITY, DESCRIPTION) values ('&nomestudio._qa-994','User has logged in &nomestudio._qa');
insert into AUTHORITIES (AUTHORITY, DESCRIPTION) values ('&nomestudio._qa-996','User has logged in &nomestudio._qa');
insert into AUTHORITIES (AUTHORITY, DESCRIPTION) values ('&nomestudio._qa-997','User has logged in &nomestudio._qa');
grant all on USERS to &nomestudio._qa;
grant all on GRANTED_AUTHORITIES to &nomestudio._qa;
commit;
exit;

--pentaho_preprod da servizio@sissdevel

sqlplus nomeservizio/password@sissdevel

CREATE OR REPLACE TRIGGER PENTAHO_UTENTI_TR
AFTER INSERT OR UPDATE OR DELETE  ON UTENTI REFERENCING OLD AS v NEW AS newRow for each row
BEGIN
if updating then
update PENTAHO_PREPROD.USERS
set 
"PASSWORD"=:newRow.password,
"ENABLED"=:newRow.abilitato
where "USERNAME"=:v.userid||'@&ID..PIERREL_PREPROD';
end if;
if inserting and (
    substr(:newRow.userid,0,3) like '997' or
    substr(:newRow.userid,0,3) like '996' or
    substr(:newRow.userid,0,3) like '995' or
    substr(:newRow.userid,0,3) like '994' or
    substr(:newRow.userid,0,3) like '991' or
   (substr(:newRow.userid,0,2) >='0' and substr(:newRow.userid,0,2) <='9')) then
insert into PENTAHO_PREPROD.USERS (USERNAME, PASSWORD, ENABLED)
values(:newRow.userid||'@&ID..PIERREL_PREPROD',:newRow."PASSWORD",:newRow.abilitato);
insert into PENTAHO_PREPROD.GRANTED_AUTHORITIES (USERNAME, AUTHORITY)
values(:newRow.userid||'@&ID..PIERREL_PREPROD','Authenticated');
insert into PENTAHO_PREPROD.GRANTED_AUTHORITIES (USERNAME, AUTHORITY)
values(:newRow.userid||'@&ID..PIERREL_PREPROD','bi-authenticated');
end if;
if inserting and substr(:newRow.userid,0,3) = '997' then
insert into PENTAHO_PREPROD.GRANTED_AUTHORITIES (USERNAME, AUTHORITY)
values(:newRow.userid||'@&ID..PIERREL_PREPROD','&nomestudio._qa-997');
end if;
if inserting and substr(:newRow.userid,0,3) = '996' then
insert into PENTAHO_PREPROD.GRANTED_AUTHORITIES (USERNAME, AUTHORITY)
values(:newRow.userid||'@&ID..PIERREL_PREPROD','&nomestudio._qa-996');
end if;
if inserting and substr(:newRow.userid,0,3) = '995' then
insert into PENTAHO_PREPROD.GRANTED_AUTHORITIES (USERNAME, AUTHORITY)
values(:newRow.userid||'@&ID..PIERREL_PREPROD','&nomestudio._qa-995');
end if;
if inserting and substr(:newRow.userid,0,3) = '994' then
insert into PENTAHO_PREPROD.GRANTED_AUTHORITIES (USERNAME, AUTHORITY)
values(:newRow.userid||'@&ID..PIERREL_PREPROD','&nomestudio._qa-994');
end if;
if inserting and substr(:newRow.userid,0,3) = '991' then
insert into PENTAHO_PREPROD.GRANTED_AUTHORITIES (USERNAME, AUTHORITY)
values(:newRow.userid||'@&ID..PIERREL_PREPROD','&nomestudio._qa-991');
end if;
if inserting and substr(:newRow.userid,0,2) >='0' and substr(:newRow.userid,0,2) <='9' then
insert into PENTAHO_PREPROD.GRANTED_AUTHORITIES (USERNAME, AUTHORITY)
values(:newRow.userid||'@&ID..PIERREL_PREPROD','&nomestudio._qa-INV');
end if;
if deleting then
delete PENTAHO_PREPROD.GRANTED_AUTHORITIES where USERNAME=:v.userid||'@&ID..PIERREL_PREPROD';
delete PENTAHO_PREPROD.USERS where USERNAME=:v.userid||'@&ID..PIERREL_PREPROD';
end if;
END;
/

--da eseguire dal servizio

insert into PENTAHO_PREPROD.USERS (USERNAME, PASSWORD, ENABLED)
select  userid||'@&ID..PIERREL_PREPROD',PASSWORD,abilitato
from utenti where (userid like '991%' or userid like '995%' or userid like '994%' or userid like '996%' or
userid like '997%' or userid <'9') and userid||'@&ID..PIERREL_PREPROD' not in (select USERNAME from PENTAHO_PREPROD.USERS);

insert into PENTAHO_PREPROD.GRANTED_AUTHORITIES (USERNAME, AUTHORITY)
select userid||'@&ID..PIERREL_PREPROD','Authenticated' from utenti where (userid like '991%' or userid like '995%' or userid like '994%' or userid like '996%' or
userid like '997%' or userid <'9') and userid||'@&ID..PIERREL_PREPROD' not in (select USERNAME from PENTAHO_PREPROD.GRANTED_AUTHORITIES 
where AUTHORITY like 'Authenticated');

insert into PENTAHO_PREPROD.GRANTED_AUTHORITIES (USERNAME, AUTHORITY)
select userid||'@&ID..PIERREL_PREPROD','bi-authenticated' from utenti where (userid like '991%' or userid like '995%' or userid like '994%' or userid like '996%' or
userid like '997%' or userid <'9') and userid||'@&ID..PIERREL_PREPROD' not in (select USERNAME from PENTAHO_PREPROD.GRANTED_AUTHORITIES 
where AUTHORITY like 'bi-authenticated');

insert into PENTAHO_PREPROD.GRANTED_AUTHORITIES (USERNAME, AUTHORITY)
select userid||'@&ID..PIERREL_PREPROD','&nomestudio._qa-INV' from utenti where (userid <'9') and userid||'@&ID..PIERREL_PREPROD' not in (select USERNAME from PENTAHO_PREPROD.GRANTED_AUTHORITIES 
where AUTHORITY like '&nomestudio._qa-INV');

insert into PENTAHO_PREPROD.GRANTED_AUTHORITIES (USERNAME, AUTHORITY)
select userid||'@&ID..PIERREL_PREPROD','&nomestudio._qa-997' from utenti where (userid like '997%') and userid||'@&ID..PIERREL_PREPROD' not in (select USERNAME from PENTAHO_PREPROD.GRANTED_AUTHORITIES 
where AUTHORITY like '&nomestudio._qa-997');

insert into PENTAHO_PREPROD.GRANTED_AUTHORITIES (USERNAME, AUTHORITY)
select userid||'@&ID..PIERREL_PREPROD','&nomestudio._qa-991' from utenti where (userid like '991%') and userid||'@&ID..PIERREL_PREPROD' not in (select USERNAME from PENTAHO_PREPROD.GRANTED_AUTHORITIES 
where AUTHORITY like '&nomestudio._qa-991');

insert into PENTAHO_PREPROD.GRANTED_AUTHORITIES (USERNAME, AUTHORITY)
select userid||'@&ID..PIERREL_PREPROD','&nomestudio._qa-995' from utenti where (userid like '995%') and userid||'@&ID..PIERREL_PREPROD' not in (select USERNAME from PENTAHO_PREPROD.GRANTED_AUTHORITIES 
where AUTHORITY like '&nomestudio._qa-995');

insert into PENTAHO_PREPROD.GRANTED_AUTHORITIES (USERNAME, AUTHORITY)
select userid||'@&ID..PIERREL_PREPROD','&nomestudio._qa-994' from utenti where (userid like '994%') and userid||'@&ID..PIERREL_PREPROD' not in (select USERNAME from PENTAHO_PREPROD.GRANTED_AUTHORITIES 
where AUTHORITY like '&nomestudio._qa-994');

insert into PENTAHO_PREPROD.GRANTED_AUTHORITIES (USERNAME, AUTHORITY)
select userid||'@&ID..PIERREL_PREPROD','&nomestudio._qa-996' from utenti where (userid like '996%') and userid||'@&ID..PIERREL_PREPROD' not in (select USERNAME from PENTAHO_PREPROD.GRANTED_AUTHORITIES 
where AUTHORITY like '&nomestudio._qa-996');

commit;

CREATE SEQUENCE &prefisso._REP_LINKS_SEQ
  START WITH 1
  MAXVALUE 999999999999999999999999999
  MINVALUE 1
  NOCYCLE
  NOCACHE
  NOORDER;

CREATE TABLE &prefisso._REP_AMMIN
(
  USERID      VARCHAR2(40 CHAR)                 NOT NULL,
  GROUP_LINK  NUMBER                            NOT NULL,
  CONSTRAINT PK_&prefisso._REP_AMMIN
 PRIMARY KEY
 (USERID, GROUP_LINK)
)
LOGGING 
NOCOMPRESS 
NOCACHE
NOPARALLEL
MONITORING;

CREATE TABLE &prefisso._REP_LINKS
(
  ID          NUMBER                            NOT NULL,
  ID_REF      NUMBER,
  GROUP_LINK  NUMBER                            NOT NULL,
  TIPOLOGIA   NUMBER,
  TESTO       VARCHAR2(1000 CHAR),
  HREF        VARCHAR2(1000 CHAR),
  ABILITATO   NUMBER,
  ORDER_COL   NUMBER,
  TARGET      varchar2(100),
  CONSTRAINT PK_&prefisso._REP_LINKS
 PRIMARY KEY
 (ID, GROUP_LINK)
)
LOGGING 
NOCOMPRESS 
NOCACHE
NOPARALLEL
MONITORING;

CREATE TABLE &prefisso._REP_LINKS_THEME
(
  CONSTANT    VARCHAR2(40 CHAR)                 NOT NULL,
  VALUE       VARCHAR2(200 CHAR)                NOT NULL,
  GROUP_LINK  NUMBER                            NOT NULL,
  CONSTRAINT PK_&prefisso._REP_LINKS_THEME
 PRIMARY KEY
 (CONSTANT, GROUP_LINK)
)
LOGGING 
NOCOMPRESS 
NOCACHE
NOPARALLEL
MONITORING;


Insert into &prefisso._REP_AMMIN
   (USERID, GROUP_LINK)
 Values
   ('99700099', 0);
COMMIT;


Insert into &prefisso._REP_LINKS_THEME
   (CONSTANT, VALUE, GROUP_LINK)
 Values
   ('LK_HEIGHT', '0px', 0);
COMMIT;


CREATE TABLE &prefisso._LINK_GRUPPIU
(
  ID_LINK     NUMBER                            NOT NULL,
  GROUP_LINK  NUMBER                            NOT NULL,
  ID_GRUPPOU  NUMBER                            NOT NULL,
  CONSTRAINT PK_&prefisso._LINK_GRUPPIU
 PRIMARY KEY
 (ID_LINK, ID_GRUPPOU, GROUP_LINK),
  CONSTRAINT FK_&prefisso._LINK_GRUPPIU_IDGU 
 FOREIGN KEY (ID_GRUPPOU) 
 REFERENCES GRUPPIU (ID_GRUPPOU),
  CONSTRAINT FK_&prefisso._LINK_GRUPPIU_IDLINK 
 FOREIGN KEY (ID_LINK, GROUP_LINK) 
 REFERENCES &prefisso._REP_LINKS (ID,GROUP_LINK)
)
LOGGING 
NOCOMPRESS 
NOCACHE
NOPARALLEL
MONITORING;


exit;


--Produzione


sqlplus pentaho/htn0110\!@sissprod

insert into AUTHORITIES (AUTHORITY, DESCRIPTION) values ('&nomestudio.-INV','User has logged in &nomestudio. as Investigator');
insert into AUTHORITIES (AUTHORITY, DESCRIPTION) values ('&nomestudio.-991','User has logged in &nomestudio.');
insert into AUTHORITIES (AUTHORITY, DESCRIPTION) values ('&nomestudio.-995','User has logged in &nomestudio.');
insert into AUTHORITIES (AUTHORITY, DESCRIPTION) values ('&nomestudio.-994','User has logged in &nomestudio.');
insert into AUTHORITIES (AUTHORITY, DESCRIPTION) values ('&nomestudio.-996','User has logged in &nomestudio.');
insert into AUTHORITIES (AUTHORITY, DESCRIPTION) values ('&nomestudio.-997','User has logged in &nomestudio.');
grant all on USERS to &nomestudio.;
grant all on GRANTED_AUTHORITIES to &nomestudio.;
commit;
exit;

--pentaho per servizio@sissprod
sqlplus nomeservizio/password@sissprod

CREATE OR REPLACE TRIGGER PENTAHO_UTENTI_TR
AFTER INSERT OR UPDATE OR DELETE  ON UTENTI REFERENCING OLD AS v NEW AS newRow for each row
BEGIN
if updating then
update PENTAHO.USERS
set 
"PASSWORD"=:newRow.password,
"ENABLED"=:newRow.abilitato
where "USERNAME"=:v.userid||'@&ID..PIERREL';
end if;
if inserting and (
    substr(:newRow.userid,0,3) like '997' or
    substr(:newRow.userid,0,3) like '996' or
    substr(:newRow.userid,0,3) like '995' or
    substr(:newRow.userid,0,3) like '994' or
    substr(:newRow.userid,0,3) like '991' or
   (substr(:newRow.userid,0,2) >='0' and substr(:newRow.userid,0,2) <='9')) then
insert into PENTAHO.USERS (USERNAME, PASSWORD, ENABLED)
values(:newRow.userid||'@&ID..PIERREL',:newRow."PASSWORD",:newRow.abilitato);
insert into PENTAHO.GRANTED_AUTHORITIES (USERNAME, AUTHORITY)
values(:newRow.userid||'@&ID..PIERREL','Authenticated');
insert into PENTAHO.GRANTED_AUTHORITIES (USERNAME, AUTHORITY)
values(:newRow.userid||'@&ID..PIERREL','bi-authenticated');
end if;
if inserting and substr(:newRow.userid,0,3) = '997' then
insert into PENTAHO.GRANTED_AUTHORITIES (USERNAME, AUTHORITY)
values(:newRow.userid||'@&ID..PIERREL','&nomestudio.-997');
end if;
if inserting and substr(:newRow.userid,0,3) = '996' then
insert into PENTAHO.GRANTED_AUTHORITIES (USERNAME, AUTHORITY)
values(:newRow.userid||'@&ID..PIERREL','&nomestudio.-996');
end if;
if inserting and substr(:newRow.userid,0,3) = '995' then
insert into PENTAHO.GRANTED_AUTHORITIES (USERNAME, AUTHORITY)
values(:newRow.userid||'@&ID..PIERREL','&nomestudio.-995');
end if;
if inserting and substr(:newRow.userid,0,3) = '994' then
insert into PENTAHO.GRANTED_AUTHORITIES (USERNAME, AUTHORITY)
values(:newRow.userid||'@&ID..PIERREL','&nomestudio.-994');
end if;
if inserting and substr(:newRow.userid,0,3) = '991' then
insert into PENTAHO.GRANTED_AUTHORITIES (USERNAME, AUTHORITY)
values(:newRow.userid||'@&ID..PIERREL','&nomestudio.-991');
end if;
if inserting and substr(:newRow.userid,0,2) >='0' and substr(:newRow.userid,0,2) <='9' then
insert into PENTAHO.GRANTED_AUTHORITIES (USERNAME, AUTHORITY)
values(:newRow.userid||'@&ID..PIERREL','&nomestudio.-INV');
end if;
if deleting then
delete PENTAHO.GRANTED_AUTHORITIES where USERNAME=:v.userid||'@&ID..PIERREL';
delete PENTAHO.USERS where USERNAME=:v.userid||'@&ID..PIERREL';
end if;
END;
/


--da eseguire dal servizio

insert into PENTAHO.USERS (USERNAME, PASSWORD, ENABLED)
select  userid||'@&ID..PIERREL',PASSWORD,abilitato
from utenti where (userid like '991%' or userid like '995%' or userid like '994%' or userid like '996%' or
userid like '997%' or userid <'9') and userid||'@&ID..PIERREL' not in (select USERNAME from PENTAHO.USERS);

insert into PENTAHO.GRANTED_AUTHORITIES (USERNAME, AUTHORITY)
select userid||'@&ID..PIERREL','Authenticated' from utenti where (userid like '991%' or userid like '995%' or userid like '994%' or userid like '996%' or
userid like '997%' or userid <'9') and userid||'@&ID..PIERREL' not in (select USERNAME from PENTAHO.GRANTED_AUTHORITIES 
where AUTHORITY like 'Authenticated');

insert into PENTAHO.GRANTED_AUTHORITIES (USERNAME, AUTHORITY)
select userid||'@&ID..PIERREL','bi-authenticated' from utenti where (userid like '991%' or userid like '995%' or userid like '994%' or userid like '996%' or
userid like '997%' or userid <'9') and userid||'@&ID..PIERREL' not in (select USERNAME from PENTAHO.GRANTED_AUTHORITIES 
where AUTHORITY like 'bi-authenticated');

insert into PENTAHO.GRANTED_AUTHORITIES (USERNAME, AUTHORITY)
select userid||'@&ID..PIERREL','&nomestudio.-INV' from utenti where (userid <'9') and userid||'@&ID..PIERREL' not in (select USERNAME from PENTAHO.GRANTED_AUTHORITIES 
where AUTHORITY like '&nomestudio.-INV');

insert into PENTAHO.GRANTED_AUTHORITIES (USERNAME, AUTHORITY)
select userid||'@&ID..PIERREL','&nomestudio.-997' from utenti where (userid like '997%') and userid||'@&ID..PIERREL' not in (select USERNAME from PENTAHO.GRANTED_AUTHORITIES 
where AUTHORITY like '&nomestudio.-997');

insert into PENTAHO.GRANTED_AUTHORITIES (USERNAME, AUTHORITY)
select userid||'@&ID..PIERREL','&nomestudio.-991' from utenti where (userid like '991%') and userid||'@&ID..PIERREL' not in (select USERNAME from PENTAHO.GRANTED_AUTHORITIES 
where AUTHORITY like '&nomestudio.-991');

insert into PENTAHO.GRANTED_AUTHORITIES (USERNAME, AUTHORITY)
select userid||'@&ID..PIERREL','&nomestudio.-995' from utenti where (userid like '995%') and userid||'@&ID..PIERREL' not in (select USERNAME from PENTAHO.GRANTED_AUTHORITIES 
where AUTHORITY like '&nomestudio.-995');

insert into PENTAHO.GRANTED_AUTHORITIES (USERNAME, AUTHORITY)
select userid||'@&ID..PIERREL','&nomestudio.-994' from utenti where (userid like '994%') and userid||'@&ID..PIERREL' not in (select USERNAME from PENTAHO.GRANTED_AUTHORITIES 
where AUTHORITY like '&nomestudio.-994');

insert into PENTAHO.GRANTED_AUTHORITIES (USERNAME, AUTHORITY)
select userid||'@&ID..PIERREL','&nomestudio.-996' from utenti where (userid like '996%') and userid||'@&ID..PIERREL' not in (select USERNAME from PENTAHO.GRANTED_AUTHORITIES 
where AUTHORITY like '&nomestudio.-996');
commit;

CREATE SEQUENCE &prefisso._REP_LINKS_SEQ
  START WITH 1
  MAXVALUE 999999999999999999999999999
  MINVALUE 1
  NOCYCLE
  NOCACHE
  NOORDER;

CREATE TABLE &prefisso._REP_AMMIN
(
  USERID      VARCHAR2(40 CHAR)                 NOT NULL,
  GROUP_LINK  NUMBER                            NOT NULL,
  CONSTRAINT PK_&prefisso._REP_AMMIN
 PRIMARY KEY
 (USERID, GROUP_LINK)
)
LOGGING 
NOCOMPRESS 
NOCACHE
NOPARALLEL
MONITORING;

CREATE TABLE &prefisso._REP_LINKS
(
  ID          NUMBER                            NOT NULL,
  ID_REF      NUMBER,
  GROUP_LINK  NUMBER                            NOT NULL,
  TIPOLOGIA   NUMBER,
  TESTO       VARCHAR2(1000 CHAR),
  HREF        VARCHAR2(1000 CHAR),
  ABILITATO   NUMBER,
  ORDER_COL   NUMBER,
  TARGET      varchar2(100),
  CONSTRAINT PK_&prefisso._REP_LINKS
 PRIMARY KEY
 (ID, GROUP_LINK)
)
LOGGING 
NOCOMPRESS 
NOCACHE
NOPARALLEL
MONITORING;

CREATE TABLE &prefisso._REP_LINKS_THEME
(
  CONSTANT    VARCHAR2(40 CHAR)                 NOT NULL,
  VALUE       VARCHAR2(200 CHAR)                NOT NULL,
  GROUP_LINK  NUMBER                            NOT NULL,
  CONSTRAINT PK_&prefisso._REP_LINKS_THEME
 PRIMARY KEY
 (CONSTANT, GROUP_LINK)
)
LOGGING 
NOCOMPRESS 
NOCACHE
NOPARALLEL
MONITORING;


Insert into &prefisso._REP_AMMIN
   (USERID, GROUP_LINK)
 Values
   ('99700099', 0);
COMMIT;


Insert into &prefisso._REP_LINKS_THEME
   (CONSTANT, VALUE, GROUP_LINK)
 Values
   ('LK_HEIGHT', '0px', 0);
COMMIT;


CREATE TABLE &prefisso._LINK_GRUPPIU
(
  ID_LINK     NUMBER                            NOT NULL,
  GROUP_LINK  NUMBER                            NOT NULL,
  ID_GRUPPOU  NUMBER                            NOT NULL,
  CONSTRAINT PK_&prefisso._LINK_GRUPPIU
 PRIMARY KEY
 (ID_LINK, ID_GRUPPOU, GROUP_LINK),
  CONSTRAINT FK_&prefisso._LINK_GRUPPIU_IDGU 
 FOREIGN KEY (ID_GRUPPOU) 
 REFERENCES GRUPPIU (ID_GRUPPOU),
  CONSTRAINT FK_&prefisso._LINK_GRUPPIU_IDLINK 
 FOREIGN KEY (ID_LINK, GROUP_LINK) 
 REFERENCES &prefisso._REP_LINKS (ID,GROUP_LINK)
)
LOGGING 
NOCOMPRESS 
NOCACHE
NOPARALLEL
MONITORING;

exit;

*** Configurare l'ambiente di deploy per PIERREL
* Loggare in Pentaho (https://pentaho-siss.pp.cineca.it/pentaho/Home) come admin / xxx
* creare la cartella root/[NOMESERVIZIO]
* assegnare i permessi "All Permissions" a pierrel-publisher (solo test e preprod)
* assegnare i permessi "Execute"
* 	[NOMESERVIZIO]-997, [NOMESERVIZIO]-996, [NOMESERVIZIO]-995, [NOMESERVIZIO]-994,
* 	[NOMESERVIZIO]-991, [NOMESERVIZIO]-INV
* * creare la connessione [NOMESERVIZIO] prendendo i parametri da
*   /oracle/app/oracle/product/11.1.0/client/network/admin/tnsnames.ora
* e /(sissprep|sissprod)/http/www/[NOMESERVIZIO]/config/ammnistrazione.cfg
* 	"Nuovo Ad-Hoc Report" -> Select Data Source -> New Data Source -> 
* 	Parametri:
*		Host Name (file HOST)
*		Database Name (file SERVICE_NAME) (CON / davanti)
* 		Port Number (file PORT)
*		User Name (file OraUserid)
*		Password (file OraPassword)

*** Per errori con Pentaho
* controllare [/ | /sissprep | /sissprod]http/lib/pentaho-solutions/logs/solution/pentaho01-siss0[1-8]/pentaho.log
* xmr_to_pdf: copiare un serivizio  es. xmr_to_pdf_sire.xaction to xmr_to_pdf_[nomeservizio].xaction e configurarlo 
* sostituendo le occorenze del nomeservizio di partenza con quelle di quello di destinazione
* caricare il file prpt indicato da Pierrel nel direttorio  [/ | /sissprep | /sissprod]/http/lib/pentaho-solutions/solution/xmr_to_pdf/ con il nome corretto per la xaction
* configurare lo share in pentaho dei file prpt e xaction della cartella xmr_to_pdf, assegnando l'esecuzione all'utente exec_xaction
* fare un refresh del repository cash
* 

*	** INSERIMENTO SUPERSHIBUSER **

INSERT INTO UTENTI T (USERID, PASSWORD, ABILITATO, ID_TIPOLOGIA, BUDGET, CONSUMO, SCADENZAPWD, DTTM_SCADENZAPWD, DTTM_ULTIMOACCESSO, SBLOCCOPWD, ID_VISTA, UPDATE_ID)
  VALUES ('ADM_VRM', '$apr1$ubT.....$r6WQzeSTdCG47CyS0WwFM/', 1, 1, 0, 0, 8, TO_DATE('2030/07/11 18:09:30', 'YYYY/MM/DD HH24:MI:SS'), TO_DATE('2011/07/11 18:39:19', 'YYYY/MM/DD HH24:MI:SS'), 'pT34S0t8heQbZbaK1rb95u13AYHYMg5m', 0, 2);
INSERT INTO ANA_UTENTI_1 T (USERID, ID_TIPOLOGIA, COGNOME, NOME, CODICE_FISCALE, AZIENDA_ENTE, VIA, CAP, CITTA, PROV, NAZIONE, TELEFONO, FAX, MEMO, EMAIL, UPDATE_ID)
  VALUES ('ADM_VRM', 1, 'SITE 99', 'Test User', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 'l.limonta@pierrel-research.com', 2);

INSERT INTO SUPERSHIBUSERS T (USERID)
  VALUES ('ADM_VRM');

INSERT INTO UTENTI_GRUPPIU T (USERID, ID_GRUPPOU, ABILITATO, UPDATE_ID)
  VALUES ('ADM_VRM', 2, 1, 0);

COMMIT;



--Installazione Query Online:

CREATE OR REPLACE function DATEDIFF (
  dateFrom in date,
  dateTo in date,
  interval in char
)
return number
AS
  result number;
begin
  --
  select
    case lower(interval)
      when 'm' then round(MONTHS_BETWEEN(dateTo, dateFrom))
      when 'd' then round(dateTo - dateFrom)
      when 'y' then round(MONTHS_BETWEEN(dateTo, dateFrom)/12)
      else 0
    end into result
  from dual;
  --
  return(result);
  --
end DATEDIFF;
/

CREATE OR REPLACE PROCEDURE QUERY_ONLINE
(v_codpat in NUMBER,v_esam in NUMBER,v_visitnum in number, v_visitnum_progr in number, v_progr in number, 
 v_field IN VARCHAR2, v_note in varchar2, v_value in varchar2 ,v_typefield in varchar2, 
 v_val_dec in varchar2, v_valhour in varchar2,v_valminute in varchar2,v_daterc in varchar2,v_tablename in varchar2,v_service in varchar2)
AS 
  myfine number(5):=0;
  mystato number(5):=3;
  v_counteq number(5):=0;
  v_fieldhour varchar2(20):='';
  v_fieldminute varchar2(20):='';
  v_fielddecod varchar2(20):='';
  v_fielddaterc varchar2(20):='';
  sql_txt    varchar2(3000);
  sql_txt1    varchar2(3000);
BEGIN
    sql_txt:='select fine from '||v_service||'coordinate where codpat='||v_codpat||' and visitnum='||v_visitnum||' and esam='||v_esam||' and visitnum_progr='||v_visitnum_progr||' and progr='||v_progr;
    execute immediate sql_txt into myfine;
      
    --deve ripartire la query solo se stato di eqfiled è 3 di default è 3
    sql_txt:='select count(*) from '||v_service||'eqfield where codpat='||v_codpat||' and visitnum='||v_visitnum||' and esam='||v_esam||' and visitnum_progr='||v_visitnum_progr||' and progr='||v_progr||' and field='''||v_field||'''';
    execute immediate sql_txt into v_counteq ;
        
    if (v_counteq >0) then
        sql_txt1:='select statofield from '||v_service||'eqfield where codpat='||v_codpat||' and visitnum='||v_visitnum||' and esam='||v_esam||' and visitnum_progr='||v_visitnum_progr||' and progr='||v_progr||' and field='''||v_field||'''';
        sql_txt:=sql_txt1||'  and eq_int =(select max(eq_int) from '||v_service||'eqfield where codpat='||v_codpat||' and visitnum='||v_visitnum||' and esam='||v_esam||' and visitnum_progr='||v_visitnum_progr||' and progr='||v_progr||' and field='''||v_field||''')';
        execute immediate sql_txt into mystato ;
    end if;

    if (myfine=1 and (mystato=3  or v_counteq=0 )) 
    then

        sql_txt:='insert into '||v_service||'eqfield values ('||v_codpat||','||v_esam||','||v_visitnum||','||v_visitnum_progr||','||v_progr||','||v_service||'eqseq.nextval,'''||v_field||''','''||v_value||''','''||v_note||''',NULL,0)';
        execute immediate sql_txt ;
        if (v_typefield='TIME')
        then
            v_fieldhour:=v_field||'_H';
            v_fieldminute:=v_field||'_M';
            sql_txt:='insert into '||v_service||'eqfield values ('||v_codpat||','||v_esam||','||v_visitnum||','||v_visitnum_progr||','||v_progr||','||v_service||'eqseq.currval,'''||v_fieldhour||''','''||v_valhour||''','''||v_note||''',NULL,0)';
            execute immediate sql_txt;
            sql_txt:='insert into '||v_service||'eqfield values ('||v_codpat||','||v_esam||','||v_visitnum||','||v_visitnum_progr||','||v_progr||','||v_service||'eqseq.currval,'''||v_fieldminute||''','''||v_valminute||''','''||v_note||''',NULL,0)';
            execute immediate sql_txt ;
        end if;
        if (v_typefield='DATE')
        then
            v_fielddaterc:=v_field||'RC';
            sql_txt:='insert into '||v_service||'eqfield values ('||v_codpat||','||v_esam||','||v_visitnum||','||v_visitnum_progr||','||v_progr||','||v_service||'eqseq.currval,'''||v_fielddaterc||''','''||v_daterc||''','''||v_note||''','''',0)';
            execute immediate sql_txt ;
        end if;
        if (v_typefield='DECOD') 
        then
            v_fielddecod:='D_'||v_field;
            sql_txt:='insert into '||v_service||'eqfield values ('||v_codpat||','||v_esam||','||v_visitnum||','||v_visitnum_progr||','||v_progr||','||v_service||'eqseq.currval,'''||v_fielddecod||''','''||v_val_dec||''','''||v_note||''','''',0)';
            execute immediate sql_txt ;
        end if;
        sql_txt:='insert into '||v_service||'eq (EQUERY_INT, CODPAT, USERID_INS, INS_DT, STATO, RICH_DM, RICH_DE, RISP_DM, CLOSE_DT) values ('||v_service||'eqseq.currval,'||v_codpat||',''99788888'',SYSDATE,0,'''','''','''','''')';
        execute immediate sql_txt ;
    end if;
    
    if (myfine=1)
    then
        sql_txt:='insert into '||v_service||'log_eq_online values ('||v_codpat||','||v_esam||','||v_visitnum||','||v_visitnum_progr||','||v_progr||','||v_service||'log_eqidseq.nextval,'''||v_field||''','''||v_value||''','''||v_note||''','||mystato||')';
        execute immediate sql_txt;
    end if;
END QUERY_ONLINE;
/

create or replace 
PROCEDURE         QUERY_ONLINE_NOCLOSE
(v_codpat in NUMBER,v_esam in NUMBER,v_visitnum in number, v_visitnum_progr in number, v_progr in number, 
 v_field IN VARCHAR2, v_note in varchar2, v_value in varchar2 ,v_typefield in varchar2, 
 v_val_dec in varchar2, v_valhour in varchar2,v_valminute in varchar2,v_daterc in varchar2,v_tablename in varchar2,v_service in varchar2, myfine in number)
AS 
  --myfine number(5):=0;
  mystato number(5):=3;
  v_counteq number(5):=0;
  v_fieldhour varchar2(20):='';
  v_fieldminute varchar2(20):='';
  v_fielddecod varchar2(20):='';
  v_fielddaterc varchar2(20):='';
  sql_txt    varchar2(3000);
  sql_txt1    varchar2(3000);
BEGIN
    --sql_txt:='select fine from '||v_service||'coordinate where codpat='||v_codpat||' and visitnum='||v_visitnum||' and esam='||v_esam||' and visitnum_progr='||v_visitnum_progr||' and progr='||v_progr;
    --execute immediate sql_txt into myfine;
      
    --deve ripartire la query solo se stato di eqfiled è 3 di default è 3
    sql_txt:='select count(*) from '||v_service||'eqfield where codpat='||v_codpat||' and visitnum='||v_visitnum||' and esam='||v_esam||' and visitnum_progr='||v_visitnum_progr||' and progr='||v_progr||' and field='''||v_field||'''';
    execute immediate sql_txt into v_counteq ;
        
    if (v_counteq >0) then
        sql_txt1:='select statofield from '||v_service||'eqfield where codpat='||v_codpat||' and visitnum='||v_visitnum||' and esam='||v_esam||' and visitnum_progr='||v_visitnum_progr||' and progr='||v_progr||' and field='''||v_field||'''';
        sql_txt:=sql_txt1||'  and eq_int =(select max(eq_int) from '||v_service||'eqfield where codpat='||v_codpat||' and visitnum='||v_visitnum||' and esam='||v_esam||' and visitnum_progr='||v_visitnum_progr||' and progr='||v_progr||' and field='''||v_field||''')';
        execute immediate sql_txt into mystato ;
    end if;

    if (myfine=1 and (mystato=3  or v_counteq=0 )) 
    then

        sql_txt:='insert into '||v_service||'eqfield values ('||v_codpat||','||v_esam||','||v_visitnum||','||v_visitnum_progr||','||v_progr||','||v_service||'eqseq.nextval,'''||v_field||''','''||v_value||''','''||v_note||''',NULL,0)';
        execute immediate sql_txt ;
        if (v_typefield='TIME')
        then
            v_fieldhour:=v_field||'_H';
            v_fieldminute:=v_field||'_M';
            sql_txt:='insert into '||v_service||'eqfield values ('||v_codpat||','||v_esam||','||v_visitnum||','||v_visitnum_progr||','||v_progr||','||v_service||'eqseq.currval,'''||v_fieldhour||''','''||v_valhour||''','''||v_note||''',NULL,0)';
            execute immediate sql_txt;
            sql_txt:='insert into '||v_service||'eqfield values ('||v_codpat||','||v_esam||','||v_visitnum||','||v_visitnum_progr||','||v_progr||','||v_service||'eqseq.currval,'''||v_fieldminute||''','''||v_valminute||''','''||v_note||''',NULL,0)';
            execute immediate sql_txt ;
        end if;
        if (v_typefield='DATE')
        then
            v_fielddaterc:=v_field||'RC';
            sql_txt:='insert into '||v_service||'eqfield values ('||v_codpat||','||v_esam||','||v_visitnum||','||v_visitnum_progr||','||v_progr||','||v_service||'eqseq.currval,'''||v_fielddaterc||''','''||v_daterc||''','''||v_note||''','''',0)';
            execute immediate sql_txt ;
        end if;
        if (v_typefield='DECOD') 
        then
            v_fielddecod:='D_'||v_field;
            sql_txt:='insert into '||v_service||'eqfield values ('||v_codpat||','||v_esam||','||v_visitnum||','||v_visitnum_progr||','||v_progr||','||v_service||'eqseq.currval,'''||v_fielddecod||''','''||v_val_dec||''','''||v_note||''','''',0)';
            execute immediate sql_txt ;
        end if;
        sql_txt:='insert into '||v_service||'eq (EQUERY_INT, CODPAT, USERID_INS, INS_DT, STATO, RICH_DM, RICH_DE, RISP_DM, CLOSE_DT) values ('||v_service||'eqseq.currval,'||v_codpat||',''99788888'',SYSDATE,0,'''','''','''','''')';
        execute immediate sql_txt ;
    end if;
    
    if (myfine=1)
    then
        sql_txt:='insert into '||v_service||'log_eq_online values ('||v_codpat||','||v_esam||','||v_visitnum||','||v_visitnum_progr||','||v_progr||','||v_service||'log_eqidseq.nextval,'''||v_field||''','''||v_value||''','''||v_note||''','||mystato||')';
        execute immediate sql_txt;
    end if;
END QUERY_ONLINE_NOCLOSE;
/

--
-- INS_LOG_EQIDSEQ  (Sequence) 
--
CREATE SEQUENCE &SERVIZIO._LOG_EQIDSEQ
  START WITH 1
  MAXVALUE 999999999999999999999999999
  MINVALUE 1
  NOCYCLE
  NOCACHE
  ORDER;



--
-- INS_LOG_EQ_ONLINE  (Table) 
--
CREATE TABLE &SERVIZIO._LOG_EQ_ONLINE
(
  CODPAT          NUMBER(38)                    NOT NULL,
  ESAM            NUMBER(38)                    NOT NULL,
  VISITNUM        NUMBER(38)                    NOT NULL,
  VISITNUM_PROGR  NUMBER(38)                    NOT NULL,
  PROGR           NUMBER(38)                    NOT NULL,
  EQID            NUMBER(38)                    NOT NULL,
  FIELD           VARCHAR2(200 CHAR)            NOT NULL,
  VALORE          VARCHAR2(4000 CHAR),
  NOTE            VARCHAR2(4000 CHAR),
  STATOFIELD      NUMBER(38)
)
LOGGING 
NOCOMPRESS 
NOCACHE
NOPARALLEL
MONITORING;





Report installazione:

[NOMESERVIZIO]/html/uxmr> ls -lR ../../ >xml/[NOMESERVIZIO]_IQ_report

popolare screenshot doc con gli screenshot 

xml/InstallReport.log da allegare come [NOMESERVIZIO]InstallReport.log



/*
--Gestione unfreeze per i tedeschi
DROP TRIGGER TR_&NOMESERVIZIO._EQFIELD_UNFREEZE;

CREATE OR REPLACE TRIGGER TR_&NOMESERVIZIO._EQFIELD_UNFREEZE
after UPDATE ON &NOMESERVIZIO._EQFIELD REFERENCING OLD AS v NEW AS newRow for each row
declare 
  sql_txt varchar2(2000);
  total_mainsubsent number:=0;
BEGIN
if ((:v.STATOFIELD in (0,2) and :newRow.STATOFIELD=1) AND (UPPER(:newRow.NOTE) LIKE '%UNFREEZE%' OR UPPER(:newRow.NOTE_DE) LIKE '%UNFREEZE%')) then
 sql_txt:='select count(*) from &NOMESERVIZIO._COORDINATE WHERE FINE=1 AND ESAM='||:newRow.ESAM||' AND VISITNUM='||:newRow.VISITNUM||' AND VISITNUM_PROGR='||:newRow.VISITNUM_PROGR||' AND CODPAT='||:newRow.CODPAT||' and INV_QUERY=''MAINSUBSENT''';
 execute immediate sql_txt into total_mainsubsent;
 if (total_mainsubsent>0) then
   update &NOMESERVIZIO._COORDINATE set INV_QUERY=null WHERE FINE=1 AND (ESAM=:newRow.ESAM or ESAM=:newRow.ESAM+1) AND VISITNUM=:newRow.VISITNUM AND VISITNUM_PROGR=:newRow.VISITNUM_PROGR AND CODPAT=:newRow.CODPAT;
 end if;  
 update &NOMESERVIZIO._COORDINATE set FINE=null WHERE FINE=1 AND ESAM=:newRow.ESAM AND VISITNUM=:newRow.VISITNUM AND VISITNUM_PROGR=:newRow.VISITNUM_PROGR AND CODPAT=:newRow.CODPAT;
 update &NOMESERVIZIO._COORDINATE set VISITCLOSE=0 WHERE VISITCLOSE=1 AND VISITNUM=:newRow.VISITNUM AND VISITNUM_PROGR=:newRow.VISITNUM_PROGR AND CODPAT=:newRow.CODPAT;
end if;
END;
/


DROP TRIGGER TR_&NOMESERVIZIO._UNFREEZE_SKIPPED;

CREATE OR REPLACE TRIGGER TR_&NOMESERVIZIO._UNFREEZE_SKIPPED
after UPDATE ON &NOMESERVIZIO._EQFIELD REFERENCING OLD AS v NEW AS n for each row
BEGIN
if ((:v.STATOFIELD in (0,2) and :n.STATOFIELD=1) AND (UPPER(:n.NOTE) LIKE '%UNFREEZE%SKIPPED%' OR UPPER(:n.NOTE_DE) LIKE '%UNFREEZE%%SKIPPED%')) then
update &NOMESERVIZIO._COORDINATE set INIZIO=null, FINE=null WHERE FINE=1 AND ESAM=:n.ESAM AND VISITNUM=:n.VISITNUM AND VISITNUM_PROGR=:n.VISITNUM_PROGR AND CODPAT=:n.CODPAT;
update &NOMESERVIZIO._COORDINATE set VISITCLOSE=0, MODDT=SYSDATE WHERE VISITCLOSE=1 AND VISITNUM=:n.VISITNUM AND VISITNUM_PROGR=:n.VISITNUM_PROGR AND CODPAT=:n.CODPAT;
DELETE &NOMESERVIZIO._SKIP_VISIT WHERE ESAM=:n.ESAM AND VISITNUM=:n.VISITNUM AND VISITNUM_PROGR=:n.VISITNUM_PROGR AND PROGR=:n.PROGR AND CODPAT=:n.CODPAT; 
end if;
END;
/

*
*
*/	

/*
--Grant di select per pierrelconnect da SAS server


--TEST/PREPROD
CREATE OR REPLACE PROCEDURE PCONNECT IS
BEGIN
   FOR x IN (SELECT * FROM user_tables) LOOP EXECUTE IMMEDIATE 'GRANT SELECT ON ' || x.table_name || ' TO PIERREL_REPORTING'; END LOOP;
   FOR x IN (SELECT * FROM user_objects WHERE OBJECT_TYPE IN ('SEQUENCE')) LOOP EXECUTE IMMEDIATE 'GRANT SELECT,ALTER ON ' || x.object_name || ' TO PIERRELCONNECT'; END LOOP;
   FOR x IN (SELECT * FROM user_objects WHERE OBJECT_TYPE IN ('MATERIALIZED VIEW')) LOOP EXECUTE IMMEDIATE 'GRANT SELECT ON ' || x.object_name || ' TO PIERRELCONNECT'; END LOOP;
   FOR x IN (SELECT * FROM user_objects WHERE OBJECT_TYPE IN ('TABLE')) LOOP EXECUTE IMMEDIATE 'GRANT SELECT,INSERT,UPDATE,DELETE,DEBUG ON ' || x.object_name || ' TO PIERRELCONNECT'; END LOOP;
   FOR x IN (SELECT * FROM user_objects WHERE OBJECT_TYPE IN ('VIEW')) LOOP EXECUTE IMMEDIATE 'GRANT SELECT,INSERT,UPDATE,DELETE,DEBUG ON ' || x.object_name || ' TO PIERRELCONNECT'; END LOOP;
   FOR x IN (SELECT * FROM user_objects WHERE OBJECT_TYPE IN ('PROCEDURE','FUNCTION','PACKAGE')) LOOP EXECUTE IMMEDIATE 'GRANT EXECUTE, DEBUG ON ' || x.object_name || ' TO PIERRELCONNECT'; END LOOP;
END PCONNECT;
/

DECLARE
  X NUMBER;
BEGIN
  SYS.DBMS_JOB.SUBMIT
  ( job       => X 
   ,what      => 'begin PCONNECT(); end; '
   ,next_date => to_date('26/10/2012 06.00.00','dd/mm/yyyy hh24:mi:ss')
   ,interval  => 'SYSDATE+1'
   ,no_parse  => FALSE
  );
  SYS.DBMS_OUTPUT.PUT_LINE('Job Number is: ' || to_char(x));
COMMIT;
END;
/


--PROD

CREATE OR REPLACE PROCEDURE PCONNECT IS
BEGIN
   FOR x IN (SELECT * FROM user_objects WHERE OBJECT_TYPE IN ('TABLE')) LOOP EXECUTE IMMEDIATE 'GRANT SELECT ON ' || x.object_name || ' TO PIERRELCONNECT'; END LOOP;
   FOR x IN (SELECT * FROM user_objects WHERE OBJECT_TYPE IN ('PROCEDURE','FUNCTION','PACKAGE')) LOOP EXECUTE IMMEDIATE 'GRANT DEBUG ON ' || x.object_name || ' TO PIERRELCONNECT'; END LOOP;
   FOR x IN (SELECT * FROM user_objects WHERE OBJECT_TYPE IN ('MATERIALIZED VIEW')) LOOP EXECUTE IMMEDIATE 'GRANT SELECT ON ' || x.object_name || ' TO PIERRELCONNECT'; END LOOP;
   FOR x IN (SELECT * FROM user_objects WHERE OBJECT_TYPE IN ('VIEW')) LOOP EXECUTE IMMEDIATE 'GRANT SELECT ON ' || x.object_name || ' TO PIERRELCONNECT'; END LOOP;
END PCONNECT;
/

DECLARE
  X NUMBER;
BEGIN
  SYS.DBMS_JOB.SUBMIT
  ( job       => X 
   ,what      => 'begin PCONNECT(); end; '
   ,next_date => to_date('26/10/2012 06.00.00','dd/mm/yyyy hh24:mi:ss')
   ,interval  => 'SYSDATE+1'
   ,no_parse  => FALSE
  );
  SYS.DBMS_OUTPUT.PUT_LINE('Job Number is: ' || to_char(x));
COMMIT;
END;
/

*/

	 function Installer($service=null, $conn=null, $config_service=null, $service_name=null){
	 
	 	$this->conn = $conn;
 		$this->service = $service;
 		$this->config_service = $config_service;
 		$this->service_name = $service_name;
 			
 		
// 		print_r($this->conn);print_r($this->service);print_r($this->config_service);die();
	 }
 		
	function IanusUsers(){
 			$sql=new query($this->conn);
			$pk='';
			
			/**
			 * Tabella FUNZIONI
			 */
			$vals=array();
			
			$vals['ABILITATO']=1;
			$vals['PASSWD_FLAG']=1;
			$vals['IANUSGATE_FLAG']=0;
			$vals['SSL_ONLY_FLAG']=0;
			$vals['CRT_ONLY_FLAG']=0;
			$vals['ID_VISTA']=0;
			$vals['UPDATE_ID']=0;

			//echo "TEST";
			$vals['NOME']="/cgi-bin/index_gen"; 
			$sql->insert($vals,"FUNZIONI",$pk);
			//echo "ENDTEST";
			
			$vals['NOME']="/cgi-bin/reports"; 
			$sql->insert($vals,"FUNZIONI",$pk);
			//die("VAI");
			$vals['NOME']="/cgi-bin/reports2"; 
			$sql->insert($vals,"FUNZIONI",$pk);
			
			$vals['NOME']="/public/"; 
			$sql->insert($vals,"FUNZIONI",$pk);
			
			$vals['NOME']="/cgi-bin/browse_table"; 
			$sql->insert($vals,"FUNZIONI",$pk);
			
			$vals['NOME']="/cf/"; 
			$sql->insert($vals,"FUNZIONI",$pk);
			
			$vals['NOME']="/cgi-bin/multiple_dnl_stf"; 
			$sql->insert($vals,"FUNZIONI",$pk);
			
			$vals['NOME']="/cgi-bin/multiple_dnl_xpt"; 
			$sql->insert($vals,"FUNZIONI",$pk);

			$vals['NOME']="/cgi-bin/multiple_dnl_csv"; 
			$sql->insert($vals,"FUNZIONI",$pk);
			
			$vals['NOME']="/cgi-bin/multiple_dnl_flat"; 
			$sql->insert($vals,"FUNZIONI",$pk);
			
			$vals['NOME']="/cgi-bin/multiple_dnl_xml"; 
			$sql->insert($vals,"FUNZIONI",$pk);
			
			$vals['NOME']="/cgi-bin/multiple_dnl"; 
			$sql->insert($vals,"FUNZIONI",$pk);
			
			$vals['NOME']="/cgi-bin/multiple_dnl_dmp"; 
			$sql->insert($vals,"FUNZIONI",$pk);
			
			$vals['NOME']="/cgi-bin/multiple_dnl_sas"; 
			$sql->insert($vals,"FUNZIONI",$pk);
			
			$vals['NOME']="/cgi-bin/multiple_dnl_xls"; 
			$sql->insert($vals,"FUNZIONI",$pk);
			
			$vals['NOME']="/cgi-bin/gestione_CRA"; 
			$sql->insert($vals,"FUNZIONI",$pk);
			
			$vals['NOME']="/phpinfo.php"; 
			$sql->insert($vals,"FUNZIONI",$pk);
			
			$vals['UPDATE_ID']=0;
			$vals['NOME']="/uxmr/"; 
			$sql->insert($vals,"FUNZIONI",$pk);
			$vals['NOME']="/uxmr/xml/"; 
			$sql->insert($vals,"FUNZIONI",$pk);

 			if (preg_match("/\.dev\./i",$_SERVER['HTTP_HOST'])) {
				// Dev
				$vals['NOME']="/cgi-bin/upload_xml?UPLOAD_XML=1' || CHR(38) || 'ACTION=START"; 
				$sql->insert($vals,"FUNZIONI",$pk);
			} elseif (preg_match("/\.test\./i",$_SERVER['HTTP_HOST'])) {
				// Test 
				$vals['NOME']="/cgi-bin/upload_xml?UPLOAD_XML=1' || CHR(38) || 'ACTION=START"; 
				$sql->insert($vals,"FUNZIONI",$pk);
			} elseif (preg_match("/-preprod\./i",$_SERVER['HTTP_HOST'])) {
				// PreProd
				$vals['NOME']="/cgi-bin/upload_xml?UPLOAD_XML=1' || CHR(38) || 'ACTION=START"; 
				$sql->insert($vals,"FUNZIONI",$pk);
			} else {
				// Prod
			}
			/**
			 * Tabella ANA_FUNZIONI
			 */
			 $vals2="";
			 
			$vals2['UPDATE_ID']=0;
			$vals2['DESCRIZIONE']="Amministrazione IANUS, manage the information with to the Administration interface";
			$vals2['NOME']="/cgi-bin/index_gen"; 
			$sql->insert($vals2,"ANA_FUNZIONI",$pk);
			$vals2['NOME']="/cgi-bin/reports"; 
			$sql->insert($vals2,"ANA_FUNZIONI",$pk);
			$vals2['NOME']="/cgi-bin/reports2"; 
			$sql->insert($vals2,"ANA_FUNZIONI",$pk);
			$vals2['NOME']="/cgi-bin/browse_table"; 
			$sql->insert($vals2,"ANA_FUNZIONI",$pk);
			$vals2['NOME']="/cf/"; 
			$sql->insert($vals2,"ANA_FUNZIONI",$pk);
			$vals2['NOME']="/phpinfo.php";
			$sql->insert($vals2,"ANA_FUNZIONI",$pk);
				
			$vals2['DESCRIZIONE']="public";
			$vals2['NOME']="/public/"; 
			$sql->insert($vals2,"ANA_FUNZIONI",$pk);
			
			$vals2['DESCRIZIONE']="Root directory dell'xmr";
			$vals2['UPDATE_ID']=1;
			$vals2['NOME']="/uxmr/"; 
			$sql->insert($vals2,"ANA_FUNZIONI",$pk);
			$vals2['NOME']="/uxmr/xml/"; 
			$sql->insert($vals2,"ANA_FUNZIONI",$pk);
			
			
			$vals2['DESCRIZIONE']="Funzione per il download dello studio";
			$vals2['UPDATE_ID']=0;
			$vals2['NOME']="/cgi-bin/multiple_dnl_stf"; 
			$sql->insert($vals2,"ANA_FUNZIONI",$pk);
			
			$vals2['NOME']="/cgi-bin/multiple_dnl_xpt"; 
			$sql->insert($vals2,"ANA_FUNZIONI",$pk);

			$vals2['NOME']="/cgi-bin/multiple_dnl_csv"; 
			$sql->insert($vals2,"ANA_FUNZIONI",$pk);
			
			$vals2['NOME']="/cgi-bin/multiple_dnl_flat"; 
			$sql->insert($vals2,"ANA_FUNZIONI",$pk);
			
			$vals2['NOME']="/cgi-bin/multiple_dnl_xml"; 
			$sql->insert($vals2,"ANA_FUNZIONI",$pk);
			
			$vals2['NOME']="/cgi-bin/multiple_dnl"; 
			$sql->insert($vals2,"ANA_FUNZIONI",$pk);
			
			$vals2['NOME']="/cgi-bin/multiple_dnl_dmp"; 
			$sql->insert($vals2,"ANA_FUNZIONI",$pk);
			
			$vals2['NOME']="/cgi-bin/multiple_dnl_sas"; 
			$sql->insert($vals2,"ANA_FUNZIONI",$pk);
			
			$vals2['NOME']="/cgi-bin/multiple_dnl_xls"; 
			$sql->insert($vals2,"ANA_FUNZIONI",$pk);
			
			$vals2['DESCRIZIONE']="Gestione visualizzazione utenti CRA";
			$vals2['NOME']="/cgi-bin/gestione_CRA"; 
			$sql->insert($vals2,"ANA_FUNZIONI",$pk);
			
 			if (preg_match("/\.dev\./i",$_SERVER['HTTP_HOST'])) {
				// Dev
				$vals2['DESCRIZIONE']="UploadXML";
				$vals2['NOME']="/cgi-bin/upload_xml?UPLOAD_XML=1' || CHR(38) || 'ACTION=START"; 
				$sql->insert($vals2,"ANA_FUNZIONI",$pk);
			} elseif (preg_match("/\.test\./i",$_SERVER['HTTP_HOST'])) {
				// Test 
				$vals2['DESCRIZIONE']="UploadXML";
				$vals2['NOME']="/cgi-bin/upload_xml?UPLOAD_XML=1' || CHR(38) || 'ACTION=START"; 
				$sql->insert($vals2,"ANA_FUNZIONI",$pk);
			} elseif (preg_match("/-preprod\./i",$_SERVER['HTTP_HOST'])) {
				// PreProd
				$vals2['DESCRIZIONE']="UploadXML";
				$vals2['NOME']="/cgi-bin/upload_xml?UPLOAD_XML=1' || CHR(38) || 'ACTION=START"; 
				$sql->insert($vals2,"ANA_FUNZIONI",$pk);
			} else {
				// Prod
			}

			
			/**
			 * Tabella GRUPPIF
			 */
			$vals3="";
			$vals3['ID_GRUPPOF']=3;
			$vals3['ABILITATO']=1;
			$vals3['ID_VISTA']=0;
			$vals3['UPDATE_ID']=0;
			$sql->insert($vals3,"GRUPPIF",$pk);

			/**
			 * Tabella ANA_GRUPPIF
			 */
			$vals4="";
			$vals4['ID_GRUPPOF']=3;
			$vals4['NOME_GRUPPO']="uxmr";
			$vals4['DESCRIZIONE']="funzioni dell'uxmr";
			$vals4['UPDATE_ID']=0;
			$sql->insert($vals4,"ANA_GRUPPIF",$pk);

			/**
			 * Tabella GRUPPIF_FUNZ
			 */
			$vals5="";
			$vals5['UPDATE_ID']=0;
			$vals5['ABILITATO']=1;
			
			$vals5['ID_GRUPPOF']=1;
			$vals5['NOME_FUNZ']="/cgi-bin/index_gen"; 
			$sql->insert($vals5,"GRUPPIF_FUNZ",$pk);
			$vals5['NOME_FUNZ']="/cgi-bin/reports"; 
			$sql->insert($vals5,"GRUPPIF_FUNZ",$pk);
			$vals5['NOME_FUNZ']="/cgi-bin/reports2"; 
			$sql->insert($vals5,"GRUPPIF_FUNZ",$pk);
			$vals5['NOME_FUNZ']="/cgi-bin/browse_table"; 
			$sql->insert($vals5,"GRUPPIF_FUNZ",$pk);
			$vals5['NOME_FUNZ']="/cf/"; 
			$sql->insert($vals5,"GRUPPIF_FUNZ",$pk);
			$vals5['NOME_FUNZ']="/public/"; 
			$sql->insert($vals5,"GRUPPIF_FUNZ",$pk);
			$vals5['NOME_FUNZ']="/cgi-bin/gestione_CRA"; 
			$sql->insert($vals5,"GRUPPIF_FUNZ",$pk);
			$vals5['NOME_FUNZ']="/phpinfo.php";
			$sql->insert($vals5,"GRUPPIF_FUNZ",$pk);
			
			$vals5['NOME_FUNZ']="/cgi-bin/multiple_dnl_stf"; 
			$sql->insert($vals5,"GRUPPIF_FUNZ",$pk);
			$vals5['NOME_FUNZ']="/cgi-bin/multiple_dnl_xpt"; 
			$sql->insert($vals5,"GRUPPIF_FUNZ",$pk);
			$vals5['NOME_FUNZ']="/cgi-bin/multiple_dnl_csv"; 
			$sql->insert($vals5,"GRUPPIF_FUNZ",$pk);
			$vals5['NOME_FUNZ']="/cgi-bin/multiple_dnl_flat"; 
			$sql->insert($vals5,"GRUPPIF_FUNZ",$pk);
			$vals5['NOME_FUNZ']="/cgi-bin/multiple_dnl_xml"; 
			$sql->insert($vals5,"GRUPPIF_FUNZ",$pk);
			$vals5['NOME_FUNZ']="/cgi-bin/multiple_dnl"; 
			$sql->insert($vals5,"GRUPPIF_FUNZ",$pk);
			$vals5['NOME_FUNZ']="/cgi-bin/multiple_dnl_dmp"; 
			$sql->insert($vals5,"GRUPPIF_FUNZ",$pk);
			$vals5['NOME_FUNZ']="/cgi-bin/multiple_dnl_sas"; 
			$sql->insert($vals5,"GRUPPIF_FUNZ",$pk);
			$vals5['NOME_FUNZ']="/cgi-bin/multiple_dnl_xls"; 
			$sql->insert($vals5,"GRUPPIF_FUNZ",$pk);
			
// 			$vals5['ID_GRUPPOF']=2;
// 			$vals5['NOME_FUNZ']="/cgi-bin/multiple_dnl_stf"; 
// 			$sql->insert($vals5,"GRUPPIF_FUNZ",$pk);
// 			$vals5['NOME_FUNZ']="/cgi-bin/multiple_dnl_xpt"; 
// 			$sql->insert($vals5,"GRUPPIF_FUNZ",$pk);
// 			$vals5['NOME_FUNZ']="/cgi-bin/multiple_dnl_csv"; 
// 			$sql->insert($vals5,"GRUPPIF_FUNZ",$pk);
// 			$vals5['NOME_FUNZ']="/cgi-bin/multiple_dnl_flat"; 
// 			$sql->insert($vals5,"GRUPPIF_FUNZ",$pk);
// 			$vals5['NOME_FUNZ']="/cgi-bin/multiple_dnl_xml"; 
// 			$sql->insert($vals5,"GRUPPIF_FUNZ",$pk);
// 			$vals5['NOME_FUNZ']="/cgi-bin/multiple_dnl"; 
// 			$sql->insert($vals5,"GRUPPIF_FUNZ",$pk);
// 			$vals5['NOME_FUNZ']="/cgi-bin/multiple_dnl_dmp"; 
// 			$sql->insert($vals5,"GRUPPIF_FUNZ",$pk);
// 			$vals5['NOME_FUNZ']="/cgi-bin/multiple_dnl_sas"; 
// 			$sql->insert($vals5,"GRUPPIF_FUNZ",$pk);
// 			$vals5['NOME_FUNZ']="/cgi-bin/multiple_dnl_xls"; 
// 			$sql->insert($vals5,"GRUPPIF_FUNZ",$pk);
			
			$vals5['ID_GRUPPOF']=3;
			$vals5['NOME_FUNZ']="/uxmr/"; 
			$sql->insert($vals5,"GRUPPIF_FUNZ",$pk);
			$vals5['NOME_FUNZ']="/uxmr/xml/"; 
			$sql->insert($vals5,"GRUPPIF_FUNZ",$pk);
			
			
			/**
			 * Tabella GRUPPI_U
			 */
			 
			 $vals6="";
			 $vals6['ID_GRUPPOU']=2;
			 $vals6['ABILITATO']=1;
			 $vals6['ID_TIPO']=0;
			 $vals6['BUDGET']=0;
			 $vals6['CONSUMO']=0;
			 $vals6['ID_VISTA']=0;
			 $vals6['UPDATE_ID']=0;
			 $sql->insert($vals6,"GRUPPIU",$pk);

			 $vals6="";
			 $vals6['ID_GRUPPOU']=3;
			 $vals6['ABILITATO']=1;
			 $vals6['ID_TIPO']=0;
			 $vals6['BUDGET']=0;
			 $vals6['CONSUMO']=0;
			 $vals6['ID_VISTA']=0;
			 $vals6['UPDATE_ID']=0;
			 $sql->insert($vals6,"GRUPPIU",$pk);

 			 $vals6="";
			 $vals6['ID_GRUPPOU']=4;
			 $vals6['ABILITATO']=1;
			 $vals6['ID_TIPO']=0;
			 $vals6['BUDGET']=0;
			 $vals6['CONSUMO']=0;
			 $vals6['ID_VISTA']=0;
			 $vals6['UPDATE_ID']=0;
			 $sql->insert($vals6,"GRUPPIU",$pk);

 			 $vals6="";
			 $vals6['ID_GRUPPOU']=5;
			 $vals6['ABILITATO']=1;
			 $vals6['ID_TIPO']=0;
			 $vals6['BUDGET']=0;
			 $vals6['CONSUMO']=0;
			 $vals6['ID_VISTA']=0;
			 $vals6['UPDATE_ID']=0;
			 $sql->insert($vals6,"GRUPPIU",$pk);
			 
			 /**
			  * CMM_MANAGEMENT
			  * vmazzeo 20122203
			  */
			 $vals6="";
			 $vals6['ID_GRUPPOU']=6;
			 $vals6['ABILITATO']=1;
			 $vals6['ID_TIPO']=0;
			 $vals6['BUDGET']=0;
			 $vals6['CONSUMO']=0;
			 $vals6['ID_VISTA']=0;
			 $vals6['UPDATE_ID']=0;
			 $sql->insert($vals6,"GRUPPIU",$pk);
			 /**
			  * END
			  * CMM_MANAGEMENT
			  * vmazzeo 20122203
			 */
			 
			/**
			 * Tabella GRUPPIU_GRUPPIF
			 */
			 $vals7="";
			 $vals7['ID_GRUPPOU']=1;
   		     $vals7['ID_GRUPPOF']=3;
			 $vals7['ABILITATO']=1;
			 $vals7['UPDATE_ID']=0;
			 $sql->insert($vals7,"GRUPPIU_GRUPPIF",$pk);
			 
			 $vals7['ID_GRUPPOU']=2;
   		     $vals7['ID_GRUPPOF']=3;
			 $sql->insert($vals7,"GRUPPIU_GRUPPIF",$pk);
			 
			 $vals7['ID_GRUPPOU']=2;
   		     $vals7['ID_GRUPPOF']=2;
			 $sql->insert($vals7,"GRUPPIU_GRUPPIF",$pk);
			 
			 /**
			 * CMM_MANAGEMENT
			 * vmazzeo 20122203
			 */
			 $vals7['ID_GRUPPOU']=6;
			 $vals7['ID_GRUPPOF']=3;
			 $sql->insert($vals7,"GRUPPIU_GRUPPIF",$pk);
			 
			 $vals7['ID_GRUPPOU']=3;
			 $vals7['ID_GRUPPOF']=3;
			 $sql->insert($vals7,"GRUPPIU_GRUPPIF",$pk);

			 $vals7['ID_GRUPPOU']=3;
			 $vals7['ID_GRUPPOF']=1;
			 $sql->insert($vals7,"GRUPPIU_GRUPPIF",$pk);
			 
			 $vals7['ID_GRUPPOU']=4;
			 $vals7['ID_GRUPPOF']=3;
			 $sql->insert($vals7,"GRUPPIU_GRUPPIF",$pk);
			 
			 $vals7['ID_GRUPPOU']=5;
			 $vals7['ID_GRUPPOF']=3;
			 $sql->insert($vals7,"GRUPPIU_GRUPPIF",$pk);
			 
			 $vals7['ID_GRUPPOU']=3;
			 $vals7['ID_GRUPPOF']=2;
			 $sql->insert($vals7,"GRUPPIU_GRUPPIF",$pk);
			 
			 /**
			 * END
			 * CMM_MANAGEMENT
			 * vmazzeo 20122203
			 */
			 
			 /**
			  * Tabella ANA_GRUPPIU
			  */
		  	 $vals8="";
			 $vals8['ID_GRUPPOU']=2;
   		     $vals8['NOME_GRUPPO']="utenti";
			 $vals8['DESCRIZIONE']="Data Entry e Data Manager";
			 $vals8['UPDATE_ID']=0;
			 $sql->insert($vals8,"ANA_GRUPPIU",$pk);
			 
		  	 $vals8="";
			 $vals8['ID_GRUPPOU']=3;
   		     $vals8['NOME_GRUPPO']="utenti_pm";
			 $vals8['DESCRIZIONE']="utenti_pm";
			 $vals8['UPDATE_ID']=0;
			 $sql->insert($vals8,"ANA_GRUPPIU",$pk);
			 
		  	 $vals8="";
			 $vals8['ID_GRUPPOU']=4;
   		     $vals8['NOME_GRUPPO']="utenti_sponsor";
			 $vals8['DESCRIZIONE']="utenti_sponsor";
			 $vals8['UPDATE_ID']=0;
			 $sql->insert($vals8,"ANA_GRUPPIU",$pk);
			 
		  	 $vals8="";
			 $vals8['ID_GRUPPOU']=5;
   		     $vals8['NOME_GRUPPO']="utenti_dm";
			 $vals8['DESCRIZIONE']="utenti_dm";
			 $vals8['UPDATE_ID']=0;
			 $sql->insert($vals8,"ANA_GRUPPIU",$pk);
			 
			 /**
			 * CMM_MANAGEMENT
			 * vmazzeo 20122203
			 */
			 $vals8="";
			 $vals8['ID_GRUPPOU']=6;
			 $vals8['NOME_GRUPPO']="utenti_cra";
			 $vals8['DESCRIZIONE']="CRA";
			 $vals8['UPDATE_ID']=4;
			 $sql->insert($vals8,"ANA_GRUPPIU",$pk);
			 /**
			 * END
			 * CMM_MANAGEMENT
			 * vmazzeo 20122203
			 */
			 
			 /**
			  * Tabella UTENTI
			  */
			 //Utenti di default 			 
			 $vals9="";
			 $vals9['USERID']="59900001";
// 			 $vals9['USERID']="09900001";
			 $vals9['PASSWORD']='$apr1$s5b.....$zmvUcxBldAkv4weDnn3rP.'; //m123456%
			 $vals9['ABILITATO']=1;
			 $vals9['ID_TIPOLOGIA']=1;
			 $vals9['BUDGET']=0;
			 $vals9['CONSUMO']=0;
			 $vals9['SCADENZAPWD']=8;
			 $vals9['DTTM_SCADENZAPWD']="sysdate-1";
			 $vals9['DTTM_ULTIMOACCESSO']="";
			 $vals9['SBLOCCOPWD']="";
			 $vals9['ID_VISTA']=0;
			 $vals9['UPDATE_ID']=0;
			 $sql->insert($vals9,"UTENTI",$pk); 
			  
			 $vals9['USERID']="99100099";
			 $sql->insert($vals9,"UTENTI",$pk); 
			 
//			 $vals9['USERID']="99400099";
//			 $sql->insert($vals9,"UTENTI",$pk);
			 
			 $vals9['USERID']="99500099";
			 $sql->insert($vals9,"UTENTI",$pk);
			 
			 $vals9['USERID']="99400099";
			 $sql->insert($vals9,"UTENTI",$pk);
			 
			 $vals9['USERID']="99600099";
			 $sql->insert($vals9,"UTENTI",$pk);
			 
			 $vals9['USERID']="99700099";
			 $sql->insert($vals9,"UTENTI",$pk);
			 
			 $vals9['USERID']="99800099";
			 $sql->insert($vals9,"UTENTI",$pk);
			 
			 //modifica password user ADMIN (m123456% -> prima era xxx)
			 $valuesADMIN="";
			 $valuesADMIN['PASSWORD']='$apr1$s5b.....$zmvUcxBldAkv4weDnn3rP.';
			 $whereADMIN="";
			 $whereADMIN['USERID']='ADMIN';
			 $sql->update($valuesADMIN, "UTENTI", $whereADMIN);
			 
			 //Utente admin shibsuperuser
			 $vals9['USERID']="ADM_VRM";
			 $vals9['DTTM_SCADENZAPWD']="sysdate+365";
			 $vals9['PASSWORD']='$apr1$ubT.....$r6WQzeSTdCG47CyS0WwFM/'; //cineca2012!
			 $sql->insert($vals9,"UTENTI",$pk);
			 
			 //Utente admin shibsuperuser
			 $vals9['USERID']="ADM_MZV";
			 $vals9['DTTM_SCADENZAPWD']="sysdate+365";
			 $vals9['PASSWORD']='$apr1$ubT.....$r6WQzeSTdCG47CyS0WwFM/'; //cineca2012!
			 $sql->insert($vals9,"UTENTI",$pk);
			 
			 
			 /**
			  * Tabella UTENTI , utente pingdom
			  */
			 $vals9a="";
			 $vals9a['USERID']="PNGCHKID";
			 $vals9a['PASSWORD']='$apr1$Uo.....$pFv2b.0nWrtUT82o5V6fs/';
			 $vals9a['ABILITATO']=1;
			 $vals9a['ID_TIPOLOGIA']=1;
			 $vals9a['BUDGET']=0;
			 $vals9a['CONSUMO']=0;
			 $vals9a['SCADENZAPWD']=2;
			 $vals9a['DTTM_SCADENZAPWD']="";
			 $vals9a['DTTM_ULTIMOACCESSO']="TO_DATE('12/13/2010 05:07:31', 'MM/DD/YYYY HH24:MI:SS')";
			 $vals9a['SBLOCCOPWD']="";
			 $vals9a['ID_VISTA']=0;
			 $vals9a['UPDATE_ID']=0;
			 $sql->insert($vals9a,"UTENTI",$pk);  
			 
			 
			  /**
			   * Tabella ANA_UTENTI_1
			  */
			   
			   $vals10="";
			   $vals10['USERID']="59900001";
// 			   $vals10['USERID']="09900001";
			   $vals10['ID_TIPOLOGIA']=1;
			   $vals10['COGNOME']="SITE 99";
			   $vals10['NOME']="Test User";
			   $vals10['EMAIL']="hypernet@pierrel-research.com";
			   $vals10['UPDATE_ID']=0;
			   $sql->insert($vals10,"ANA_UTENTI_1",$pk);  
			   
			   $vals10['USERID']="99100099";
			   $vals10['COGNOME']="PM";
			   $sql->insert($vals10,"ANA_UTENTI_1",$pk); 
			   
			   $vals10['USERID']="99500099";
			   $vals10['COGNOME']="SPONSOR";
			   $sql->insert($vals10,"ANA_UTENTI_1",$pk); 

//			   $vals10['USERID']="99400099";
//			   $vals10['COGNOME']="SPONSOR";
//			   $sql->insert($vals10,"ANA_UTENTI_1",$pk); 
			   
			   $vals10['USERID']="99600099";
			   $vals10['COGNOME']="CRA";
			   $sql->insert($vals10,"ANA_UTENTI_1",$pk); 
			   
			   $vals10['USERID']="99700099";
			   $vals10['COGNOME']="DM";
			   $sql->insert($vals10,"ANA_UTENTI_1",$pk); 
			   
			   $vals10['USERID']="99800099";
			   $vals10['COGNOME']="DSM";
			   $sql->insert($vals10,"ANA_UTENTI_1",$pk); 
			   
			   $vals10['USERID']="99400099";
			   $vals10['COGNOME']="SPECIAL";
			   $sql->insert($vals10,"ANA_UTENTI_1",$pk); 
			  
			   $vals10['USERID']="ADM_VRM";
			   $vals10['COGNOME']="SUPERSPECIAL";
			   $sql->insert($vals10,"ANA_UTENTI_1",$pk); 
			  
			   $vals10['USERID']="ADM_MZV";
			   $vals10['COGNOME']="SUPERSPECIAL";
			   $sql->insert($vals10,"ANA_UTENTI_1",$pk);
			   	
		    /**
			  * Tabella UTENTI_GRUPPIU
			 */
			 
			 $vals11="";
			 $vals11['USERID']="59900001";
// 			 $vals11['USERID']="09900001";
			 $vals11['ID_GRUPPOU']=2;
			 $vals11['ABILITATO']=1;
			 $vals11['UPDATE_ID']=0;
			 $sql->insert($vals11,"UTENTI_GRUPPIU",$pk);
			  
			 $vals11['USERID']="99100099";
			 $sql->insert($vals11,"UTENTI_GRUPPIU",$pk);
			 
//			 $vals11['USERID']="99400099";
//			 $sql->insert($vals11,"UTENTI_GRUPPIU",$pk);
			 
			 $vals11['USERID']="99500099";
			 $sql->insert($vals11,"UTENTI_GRUPPIU",$pk);
			 
			 $vals11['USERID']="99400099";
			 $sql->insert($vals11,"UTENTI_GRUPPIU",$pk);
			 
			 $vals11['USERID']="99600099";
			 $sql->insert($vals11,"UTENTI_GRUPPIU",$pk);
			 
			 $vals11['USERID']="99700099";
			 $sql->insert($vals11,"UTENTI_GRUPPIU",$pk);
			 
			 $vals11['USERID']="99800099";
			 $sql->insert($vals11,"UTENTI_GRUPPIU",$pk);
			 
			 $vals11['USERID']="ADM_VRM";
			 $sql->insert($vals11,"UTENTI_GRUPPIU",$pk);
			 
			 $vals11['USERID']="ADM_MZV";
			 $sql->insert($vals11,"UTENTI_GRUPPIU",$pk);
			 
			 /**
			 * CMM_MANAGEMENT
			 * vmazzeo 20122203
			 */
			 $vals11['USERID']="99700099";
			 $vals11['ID_GRUPPOU']=3;
			 $sql->insert($vals11,"UTENTI_GRUPPIU",$pk);
			 
			 $vals11['USERID']="99500099";
			 $vals11['ID_GRUPPOU']=4;
			 $sql->insert($vals11,"UTENTI_GRUPPIU",$pk);
			 
			 $vals11['USERID']="99400099";
			 $vals11['ID_GRUPPOU']=4;
			 $sql->insert($vals11,"UTENTI_GRUPPIU",$pk);
			 
			 $vals11['USERID']="99100099";
			 $vals11['ID_GRUPPOU']=5;
			 $sql->insert($vals11,"UTENTI_GRUPPIU",$pk);
			 
			 $vals11['USERID']="99600099";
			 $vals11['ID_GRUPPOU']=6;
			 $sql->insert($vals11,"UTENTI_GRUPPIU",$pk);
			 
			 /**
			 * END
			 * CMM_MANAGEMENT
			 * vmazzeo 20122203
			 */
			 
			 /**
			  * Tabella UTENTI_GRUPPIU , utente PINGDOM
			  */
			 $vals11a="";
			 $vals11a['USERID']="PNGCHKID";
			 $vals11a['ID_GRUPPOU']=2;
			 $vals11a['ABILITATO']=1;
			 $vals11a['UPDATE_ID']=0;
			 $sql->insert($vals11a,"UTENTI_GRUPPIU",$pk);
			 
			  /**
			  * Tabella UTENTI_FUNZ
			 */
			 
			 $vals12="";
			 $vals12['USERID']="99700099";
			 $vals12['NOME_FUNZ']="/cgi-bin/browse_table";
			 $vals12['TIPO_ECCEZIONE']=1;
			 $vals12['UPDATE_ID']=0;
			 $sql->insert($vals12,"UTENTI_FUNZ",$pk);




 			if (preg_match("/\.dev\./i",$_SERVER['HTTP_HOST'])) {
				// Dev
				$vals12="";
				$vals12['USERID']="99700099";
 				$vals12['NOME_FUNZ']="/cgi-bin/upload_xml?UPLOAD_XML=1' || CHR(38) || 'ACTION=START";
				$vals12['TIPO_ECCEZIONE']=1;
				$vals12['UPDATE_ID']=0;
				$sql->insert($vals12,"UTENTI_FUNZ",$pk);
			} elseif (preg_match("/\.test\./i",$_SERVER['HTTP_HOST'])) {
				// Test 
			    $vals12="";
			    $vals12['USERID']="99700099";
				$vals12['NOME_FUNZ']="/cgi-bin/upload_xml?UPLOAD_XML=1' || CHR(38) || 'ACTION=START";
				$vals12['TIPO_ECCEZIONE']=1;
				$vals12['UPDATE_ID']=0;
				$sql->insert($vals12,"UTENTI_FUNZ",$pk);
			} elseif (preg_match("/-preprod\./i",$_SERVER['HTTP_HOST'])) {
				// PreProd
			    $vals12="";
			    $vals12['USERID']="99700099";
				$vals12['NOME_FUNZ']="/cgi-bin/upload_xml?UPLOAD_XML=1' || CHR(38) || 'ACTION=START";
				$vals12['TIPO_ECCEZIONE']=1;
				$vals12['UPDATE_ID']=0;
				$sql->insert($vals12,"UTENTI_FUNZ",$pk);
			} else {
				// Prod
			}

			 $vals12['NOME_FUNZ']="/cgi-bin/multiple_dnl_csv";
			 $vals12['TIPO_ECCEZIONE']=1;
			 $vals12['UPDATE_ID']=0;
			 $sql->insert($vals12,"UTENTI_FUNZ",$pk);
			 
			 $vals12['NOME_FUNZ']="/cgi-bin/multiple_dnl_dmp";
			 $vals12['TIPO_ECCEZIONE']=1;
			 $vals12['UPDATE_ID']=0;
			 $sql->insert($vals12,"UTENTI_FUNZ",$pk);
			 
 			 $vals12['NOME_FUNZ']="/cgi-bin/multiple_dnl_flat";
			 $vals12['TIPO_ECCEZIONE']=1;
			 $vals12['UPDATE_ID']=0;
			 $sql->insert($vals12,"UTENTI_FUNZ",$pk);
			 
			 $vals12['NOME_FUNZ']="/cgi-bin/multiple_dnl_sas";
			 $vals12['TIPO_ECCEZIONE']=1;
			 $vals12['UPDATE_ID']=0;
			 $sql->insert($vals12,"UTENTI_FUNZ",$pk);
			 
			 $vals12['NOME_FUNZ']="/cgi-bin/multiple_dnl_xls";
			 $vals12['TIPO_ECCEZIONE']=1;
			 $vals12['UPDATE_ID']=0;
			 $sql->insert($vals12,"UTENTI_FUNZ",$pk);
			 
			 $vals12['NOME_FUNZ']="/cgi-bin/multiple_dnl_xml";
			 $vals12['TIPO_ECCEZIONE']=1;
			 $vals12['UPDATE_ID']=0;
			 $sql->insert($vals12,"UTENTI_FUNZ",$pk);
			 
			 $vals12['NOME_FUNZ']="/cgi-bin/multiple_dnl_xpt";
			 $vals12['TIPO_ECCEZIONE']=1;
			 $vals12['UPDATE_ID']=0;
			 $sql->insert($vals12,"UTENTI_FUNZ",$pk);
			 
			 $vals12['USERID']="99100099";
			 $vals12['NOME_FUNZ']="/cgi-bin/gestione_CRA";
			 $vals12['TIPO_ECCEZIONE']=1;
			 $vals12['UPDATE_ID']=0;
			 $sql->insert($vals12,"UTENTI_FUNZ",$pk);
			 
			 
			 /**
			  * SUPERSHIBUSERS per inserire l'utente
			  * che puoi cambiare l'utenza con l'addon di Delsignore
			  */
			 
			 $vals13="";
			 $vals13['USERID']="ADM_VRM";
			 $sql->insert($vals13,"SUPERSHIBUSERS",$pk);

			 $vals13="";
			 $vals13['USERID']="ADM_MZV";
			 $sql->insert($vals13,"SUPERSHIBUSERS",$pk);
			 
			 
			 $vals14="";
			 $vals14['CODE']="T599";
			 $vals14['COUNTRY']="380";
			 $vals14['D_COUNTRY']="Italy";
			 $vals14['ID_CENTER']="599";
			 $vals14['NAME']="site test no.599";
			 $vals14['STATUS']="1";
			 $vals14['D_STATUS']="Enabled";
			 $sql->insert($vals14,"CMM_CENTER",$pk);
			 
			 //FIX TABELLA COORDINATE
			 $sqlfix = "ALTER TABLE {$this->service}_COORDINATE MODIFY(VISITNUM NUMBER)";
			 $sql->exec ( $sqlfix );
			 $sqlfix = "ALTER TABLE {$this->service}_COORDINATE MODIFY(VISITNUM_PROGR NUMBER)";
			 $sql->exec ( $sqlfix );
			 $sqlfix = "ALTER TABLE {$this->service}_COORDINATE MODIFY(ESAM NUMBER)";
			 $sql->exec ( $sqlfix );
			 $sqlfix = "ALTER TABLE {$this->service}_COORDINATE MODIFY(PROGR NUMBER)";
			 $sql->exec ( $sqlfix );

			 
			 /**
			  * ulteriori fix su _coordinate
			  * vmazzeo 20120530
			  * START
			  */
			 $sqlfix = "ALTER TABLE {$this->service}_COORDINATE add CENTER VARCHAR2(256 CHAR)";
			 $sql->exec ( $sqlfix );
             //Aggiunte nuove librerie x recuperare utente di creazione e modifica
             $sqlfix = "ALTER TABLE {$this->service}_COORDINATE add CREATE_USER VARCHAR2(256 CHAR)";
             $sql->exec ( $sqlfix );
             $sqlfix = "ALTER TABLE {$this->service}_COORDINATE add LAST_MOD_USER VARCHAR2(256 CHAR)";
             $sql->exec ( $sqlfix );
             //FINE: Aggiunte nuove librerie x recuperare utente di creazione e modifica

			 $query = new query ( $this->conn );
			 $query_check_existence = "select table_name from user_tables where table_name=upper('S_X_{$this->service}_COORDINATE')";
			 $query->set_sql ( $query_check_existence );
			 $query->exec ();
			 if($query->get_row ()==''){
			 	$query_create = "CREATE TABLE S_X_{$this->service}_COORDINATE
								(
								  ID              NUMBER                        NOT NULL,
								  TIPO            CHAR(2 CHAR),
								  NOMECAMPO       VARCHAR2(256 CHAR)            NOT NULL,
								  VALORE_OLD      VARCHAR2(4000 CHAR),
								  VALORE_NEW      VARCHAR2(4000 CHAR),
								  ID_QUERY        NUMBER,
								  DATA            DATE,
								  USERID          VARCHAR2(200 CHAR),
								  PROG_S          NUMBER,
								  VISITNUM        NUMBER(2)                     NOT NULL,
								  VISITNUM_PROGR  NUMBER(3)                     NOT NULL,
								  PROGR           NUMBER(3)                     NOT NULL,
								  ESAM            NUMBER(22)                    NOT NULL,
								  CODPAT          NUMBER(22)                    NOT NULL,
								  CONSTRAINT CK_SX_{$this->service}_COORDINATE
								 CHECK (TIPO IN ('I','U','D')),
								  CONSTRAINT PK_SX_{$this->service}_COORDINATE
								 PRIMARY KEY
								 (ID, TIPO, NOMECAMPO, VISITNUM, VISITNUM_PROGR, PROGR, ESAM, CODPAT)
								)
								LOGGING 
								NOCOMPRESS 
								NOCACHE
								NOPARALLEL
								MONITORING";
			 	$sql=new query($this->conn);
			 	$sql->set_sql ( $query_create );
			 	$sql->ins_upd ();
			 	$this->report .= "<hr>$query_create";
			 }
			 
			 $query_create = "CREATE OR REPLACE TRIGGER {$this->service}_COORDINATE_CENTER
			 										after insert or update on S_X_{$this->service}
			 										        for each row
			 										begin
			 										    update {$this->service}_coordinate c set c.center=(select r.center from {$this->service}_REGISTRAZIONE r where r.codpat=c.codpat) where c.center is null;
			 										end;";
			 $sql=new query($this->conn);
			 $sql->set_sql ( $query_create );
			 $sql->ins_upd ();
			 $this->report .= "<hr>$query_create";
			 /**
			 * END
			 * ulteriori fix su _coordinate
			 * vmazzeo 20120530
			 */

			 
			 
			 
			 /**
			 *CREAZIONE TABELLE STORICO IANUS
			 *vmazzeo 20120530
			 *START
			 */
			 
			 //S_UTENTI_VISTEAMMIN
			 $query = new query ( $this->conn );
			 $query_check_existence = "select table_name from user_tables where table_name=upper('S_UTENTI_VISTEAMMIN')";
			 $query->set_sql ( $query_check_existence );
			 $query->exec ();
			 if($query->get_row ()==''){
			 	$query_create = "
			 					CREATE TABLE S_UTENTI_VISTEAMMIN
								(
								  USERIDS    VARCHAR2(32 CHAR),
								  MODDT      DATE,
								  MODPROG    NUMBER(6)                          NOT NULL,
								  FL_QUERY   CHAR(1 CHAR)                       NOT NULL,
								  ID_QUERY   NUMBER(6),
								  USERID     VARCHAR2(32 CHAR),
								  ID_VISTA   NUMBER(10),
								  UPDATE_ID  NUMBER
								)
								LOGGING 
								NOCOMPRESS 
								NOCACHE
								NOPARALLEL
								MONITORING
			 					";
			 	$sql=new query($this->conn);
			 	$sql->set_sql ( $query_create );
			 	$sql->ins_upd ();
			 	$this->report .= "<hr>$query_create";
			 }
			 
			 //S_UTENTI_GRUPPIU
			 $query_check_existence = "select table_name from user_tables where table_name=upper('S_UTENTI_GRUPPIU')";
			 $query->set_sql ( $query_check_existence );
			 $query->exec ();
			 if($query->get_row ()==''){
			 	$query_create = "
			 					CREATE TABLE S_UTENTI_GRUPPIU
			 					(
			 					 USERIDS     VARCHAR2(32 CHAR),
								 MODDT       DATE,
								 MODPROG     NUMBER(6)                         NOT NULL,
								 FL_QUERY    CHAR(1 CHAR)                      NOT NULL,
								 ID_QUERY    NUMBER(6),
								 USERID      VARCHAR2(32 CHAR),
								 ID_GRUPPOU  NUMBER(10),
								 ABILITATO   NUMBER(1),
								 UPDATE_ID   NUMBER
								)
			 			 		LOGGING 
								NOCOMPRESS 
								NOCACHE
								NOPARALLEL
								MONITORING
			 					";
			 	$sql=new query($this->conn);
			 	$sql->set_sql ( $query_create );
			 	$sql->ins_upd ();
			 	$this->report .= "<hr>$query_create";
			 }
			 
			 //S_UTENTI_FUNZ
			 $query_check_existence = "select table_name from user_tables where table_name=upper('S_UTENTI_FUNZ')";
			 $query->set_sql ( $query_check_existence );
			 $query->exec ();
			 if($query->get_row ()==''){
			 	$query_create = "
			 			 		CREATE TABLE S_UTENTI_FUNZ
								(
								  USERIDS         VARCHAR2(32 CHAR),
								  MODDT           DATE,
								  MODPROG         NUMBER(6)                     NOT NULL,
								  FL_QUERY        CHAR(1 CHAR)                  NOT NULL,
								  ID_QUERY        NUMBER(6),
								  USERID          VARCHAR2(32 CHAR),
								  NOME_FUNZ       VARCHAR2(255 CHAR),
								  TIPO_ECCEZIONE  NUMBER(1),
								  UPDATE_ID       NUMBER
								 )
			 					LOGGING 
								NOCOMPRESS 
								NOCACHE
								NOPARALLEL
								MONITORING
			 					";
			 	$sql=new query($this->conn);
			 	$sql->set_sql ( $query_create );
			 	$sql->ins_upd ();
			 	$this->report .= "<hr>$query_create";
			 }
			 
			 //S_UTENTI
			 $query_check_existence = "select table_name from user_tables where table_name=upper('S_UTENTI')";
			 $query->set_sql ( $query_check_existence );
			 $query->exec ();
			 if($query->get_row ()==''){
			 	$query_create = "CREATE TABLE S_UTENTI
								(
								  USERIDS             VARCHAR2(32 CHAR),
								  MODDT               DATE,
								  MODPROG             NUMBER(6)                 NOT NULL,
								  FL_QUERY            CHAR(1 CHAR)              NOT NULL,
								  ID_QUERY            NUMBER(6),
								  USERID              VARCHAR2(32 CHAR),
								  PASSWORD            VARCHAR2(40 CHAR),
								  ABILITATO           NUMBER(1),
								  ID_TIPOLOGIA        NUMBER(10),
								  BUDGET              NUMBER,
								  CONSUMO             NUMBER,
								  SCADENZAPWD         NUMBER(1),
								  DTTM_SCADENZAPWD    DATE,
								  DTTM_ULTIMOACCESSO  DATE,
								  SBLOCCOPWD          VARCHAR2(32 CHAR),
								  ID_VISTA            NUMBER(10),
								  UPDATE_ID           NUMBER
								)
								LOGGING 
								NOCOMPRESS 
								NOCACHE
								NOPARALLEL
								MONITORING
								";
			 	$sql=new query($this->conn);
			 	$sql->set_sql ( $query_create );
			 	$sql->ins_upd ();
			 	$this->report .= "<hr>$query_create";
			 }
			 
			 //S_GRUPPIU_GRUPPIF
			 $query_check_existence = "select table_name from user_tables where table_name=upper('S_GRUPPIU_GRUPPIF')";
			 $query->set_sql ( $query_check_existence );
			 $query->exec ();
			 if($query->get_row ()==''){
			 	$query_create = "CREATE TABLE S_GRUPPIU_GRUPPIF
								(
								  USERID      VARCHAR2(32 CHAR),
								  MODDT       DATE,
								  MODPROG     NUMBER(6)                         NOT NULL,
								  FL_QUERY    CHAR(1 CHAR)                      NOT NULL,
								  ID_QUERY    NUMBER(6),
								  ID_GRUPPOU  NUMBER(10),
								  ID_GRUPPOF  NUMBER(10),
								  ABILITATO   NUMBER(1),
								  UPDATE_ID   NUMBER
								)
								LOGGING 
								NOCOMPRESS 
								NOCACHE
								NOPARALLEL
								MONITORING
								";
			 	$sql=new query($this->conn);
			 	$sql->set_sql ( $query_create );
			 	$sql->ins_upd ();
			 	$this->report .= "<hr>$query_create";
			 }
			 
			 //S_GRUPPIU_FUNZ
			 $query_check_existence = "select table_name from user_tables where table_name=upper('S_GRUPPIU_FUNZ')";
			 $query->set_sql ( $query_check_existence );
			 $query->exec ();
			 if($query->get_row ()==''){
			 	$query_create = "CREATE TABLE S_GRUPPIU_FUNZ
								(
								  USERID          VARCHAR2(32 CHAR),
								  MODDT           DATE,
								  MODPROG         NUMBER(6)                     NOT NULL,
								  FL_QUERY        CHAR(1 CHAR)                  NOT NULL,
								  ID_QUERY        NUMBER(6),
								  NOME_FUNZ       VARCHAR2(255 CHAR),
								  ID_GRUPPOU      NUMBER(10),
								  TIPO_ECCEZIONE  NUMBER(1),
								  UPDATE_ID       NUMBER
								)
								LOGGING 
								NOCOMPRESS 
								NOCACHE
								NOPARALLEL
								MONITORING
			 					";
			 	$sql=new query($this->conn);
			 	$sql->set_sql ( $query_create );
			 	$sql->ins_upd ();
			 	$this->report .= "<hr>$query_create";
			 }
			 
			 //S_GRUPPIU
			 $query_check_existence = "select table_name from user_tables where table_name=upper('S_GRUPPIU')";
			 $query->set_sql ( $query_check_existence );
			 $query->exec ();
			 if($query->get_row ()==''){
			 	$query_create = "CREATE TABLE S_GRUPPIU
								(
								  USERID      VARCHAR2(32 CHAR),
								  MODDT       DATE,
								  MODPROG     NUMBER(6)                         NOT NULL,
								  FL_QUERY    CHAR(1 CHAR)                      NOT NULL,
								  ID_QUERY    NUMBER(6),
								  ID_GRUPPOU  NUMBER(10),
								  ABILITATO   NUMBER(1),
								  ID_TIPO     NUMBER(10),
								  BUDGET      NUMBER,
								  CONSUMO     NUMBER,
								  ID_VISTA    NUMBER(10),
								  UPDATE_ID   NUMBER
								)
								LOGGING 
								NOCOMPRESS 
								NOCACHE
								NOPARALLEL
								MONITORING
			 					";
			 	$sql=new query($this->conn);
			 	$sql->set_sql ( $query_create );
			 	$sql->ins_upd ();
			 	$this->report .= "<hr>$query_create";
			 }
			 
			 //S_GRUPPIF_FUNZ
			 $query_check_existence = "select table_name from user_tables where table_name=upper('S_GRUPPIF_FUNZ')";
			 $query->set_sql ( $query_check_existence );
			 $query->exec ();
			 if($query->get_row ()==''){
			 	$query_create = "CREATE TABLE S_GRUPPIF_FUNZ
								(
								  USERID      VARCHAR2(32 CHAR),
								  MODDT       DATE,
								  MODPROG     NUMBER(6)                         NOT NULL,
								  FL_QUERY    CHAR(1 CHAR)                      NOT NULL,
								  ID_QUERY    NUMBER(6),
								  NOME_FUNZ   VARCHAR2(255 CHAR),
								  ID_GRUPPOF  NUMBER(10),
								  ABILITATO   NUMBER(1),
								  UPDATE_ID   NUMBER
								)
								LOGGING 
								NOCOMPRESS 
								NOCACHE
								NOPARALLEL
								MONITORING
								";
			 	$sql=new query($this->conn);
			 	$sql->set_sql ( $query_create );
			 	$sql->ins_upd ();
			 	$this->report .= "<hr>$query_create";
			 }
			 
			 //S_GRUPPIF
			 $query_check_existence = "select table_name from user_tables where table_name=upper('S_GRUPPIF')";
			 $query->set_sql ( $query_check_existence );
			 $query->exec ();
			 if($query->get_row ()==''){
			 	$query_create = "CREATE TABLE S_GRUPPIF
								(
								  USERID      VARCHAR2(32 CHAR),
								  MODDT       DATE,
								  MODPROG     NUMBER(6)                         NOT NULL,
								  FL_QUERY    CHAR(1 CHAR)                      NOT NULL,
								  ID_QUERY    NUMBER(6),
								  ID_GRUPPOF  NUMBER(10),
								  ABILITATO   NUMBER(1),
								  ID_VISTA    NUMBER(10),
								  UPDATE_ID   NUMBER
								)
								LOGGING 
								NOCOMPRESS 
								NOCACHE
								NOPARALLEL
								MONITORING
			 					";
			 	$sql=new query($this->conn);
			 	$sql->set_sql ( $query_create );
			 	$sql->ins_upd ();
			 	$this->report .= "<hr>$query_create";
			 }
			 
			 //S_FUNZIONI
			 $query_check_existence = "select table_name from user_tables where table_name=upper('S_FUNZIONI')";
			 $query->set_sql ( $query_check_existence );
			 $query->exec ();
			 if($query->get_row ()==''){
			 	$query_create = "CREATE TABLE S_FUNZIONI
								(
								  USERID          VARCHAR2(32 CHAR),
								  MODDT           DATE,
								  MODPROG         NUMBER(6)                     NOT NULL,
								  FL_QUERY        CHAR(1 CHAR)                  NOT NULL,
								  ID_QUERY        NUMBER(6),
								  NOME            VARCHAR2(255 CHAR),
								  ABILITATO       NUMBER(1),
								  PASSWD_FLAG     NUMBER(1),
								  IANUSGATE_FLAG  NUMBER(1),
								  SSL_ONLY_FLAG   NUMBER(1),
								  CRT_ONLY_FLAG   NUMBER(1),
								  ID_VISTA        NUMBER(10),
								  UPDATE_ID       NUMBER
								)
								LOGGING 
								NOCOMPRESS 
								NOCACHE
								NOPARALLEL
								MONITORING
								";
			 	$sql=new query($this->conn);
			 	$sql->set_sql ( $query_create );
			 	$sql->ins_upd ();
			 	$this->report .= "<hr>$query_create";
			 }
			 
			 //S_ANA_UTENTI_1
			 $query_check_existence = "select table_name from user_tables where table_name=upper('S_ANA_UTENTI_1')";
			 $query->set_sql ( $query_check_existence );
			 $query->exec ();
			 if($query->get_row ()==''){
			 	$query_create = "CREATE TABLE S_ANA_UTENTI_1
								(
								  USERIDS         VARCHAR2(32 CHAR),
								  MODDT           DATE,
								  MODPROG         NUMBER(6)                     NOT NULL,
								  FL_QUERY        CHAR(1 CHAR)                  NOT NULL,
								  ID_QUERY        NUMBER(6),
								  USERID          VARCHAR2(32 CHAR),
								  ID_TIPOLOGIA    NUMBER(10),
								  COGNOME         VARCHAR2(100 CHAR),
								  NOME            VARCHAR2(100 CHAR),
								  CODICE_FISCALE  VARCHAR2(16 CHAR),
								  AZIENDA_ENTE    VARCHAR2(200 CHAR),
								  VIA             VARCHAR2(100 CHAR),
								  CAP             VARCHAR2(100 CHAR),
								  CITTA           VARCHAR2(100 CHAR),
								  PROV            VARCHAR2(100 CHAR),
								  NAZIONE         VARCHAR2(100 CHAR),
								  TELEFONO        VARCHAR2(50 CHAR),
								  FAX             VARCHAR2(50 CHAR),
								  MEMO            VARCHAR2(200 CHAR),
								  EMAIL           VARCHAR2(100 CHAR),
								  UPDATE_ID       NUMBER
								)
								LOGGING 
								NOCOMPRESS 
								NOCACHE
								NOPARALLEL
								MONITORING
								";
			 	$sql=new query($this->conn);
			 	$sql->set_sql ( $query_create );
			 	$sql->ins_upd ();
			 	$this->report .= "<hr>$query_create";
			 }
			 
			 //S_ANA_GRUPPIU
			 $query_check_existence = "select table_name from user_tables where table_name=upper('S_ANA_GRUPPIU')";
			 $query->set_sql ( $query_check_existence );
			 $query->exec ();
			 if($query->get_row ()==''){
			 	$query_create = "CREATE TABLE S_ANA_GRUPPIU
								(
								  USERID       VARCHAR2(32 CHAR),
								  MODDT        DATE,
								  MODPROG      NUMBER(6)                        NOT NULL,
								  FL_QUERY     CHAR(1 CHAR)                     NOT NULL,
								  ID_QUERY     NUMBER(6),
								  ID_GRUPPOU   NUMBER(10),
								  NOME_GRUPPO  VARCHAR2(255 CHAR),
								  DESCRIZIONE  VARCHAR2(255 CHAR),
								  UPDATE_ID    NUMBER
								)
								LOGGING 
								NOCOMPRESS 
								NOCACHE
								NOPARALLEL
								MONITORING
			 					";
			 	$sql=new query($this->conn);
			 	$sql->set_sql ( $query_create );
			 	$sql->ins_upd ();
			 	$this->report .= "<hr>$query_create";
			 }
			 
			 //S_ANA_GRUPPIF
			 $query_check_existence = "select table_name from user_tables where table_name=upper('S_ANA_GRUPPIF')";
			 $query->set_sql ( $query_check_existence );
			 $query->exec ();
			 if($query->get_row ()==''){
			 	$query_create = "CREATE TABLE S_ANA_GRUPPIF
								(
								  USERID       VARCHAR2(32 CHAR),
								  MODDT        DATE,
								  MODPROG      NUMBER(6)                        NOT NULL,
								  FL_QUERY     CHAR(1 CHAR)                     NOT NULL,
								  ID_QUERY     NUMBER(6),
								  ID_GRUPPOF   NUMBER(10),
								  NOME_GRUPPO  VARCHAR2(255 CHAR),
								  DESCRIZIONE  VARCHAR2(255 CHAR),
								  UPDATE_ID    NUMBER
								)
								LOGGING 
								NOCOMPRESS 
								NOCACHE
								NOPARALLEL
								MONITORING
			 					";
			 	$sql=new query($this->conn);
			 	$sql->set_sql ( $query_create );
			 	$sql->ins_upd ();
			 	$this->report .= "<hr>$query_create";
			 }
			 
			 //S_ANA_FUNZIONI
			 $query_check_existence = "select table_name from user_tables where table_name=upper('S_ANA_FUNZIONI')";
			 $query->set_sql ( $query_check_existence );
			 $query->exec ();
			 if($query->get_row ()==''){
			 	$query_create = "CREATE TABLE S_ANA_FUNZIONI
								(
								  USERID       VARCHAR2(32 CHAR),
								  MODDT        DATE,
								  MODPROG      NUMBER(6)                        NOT NULL,
								  FL_QUERY     CHAR(1 CHAR)                     NOT NULL,
								  ID_QUERY     NUMBER(6),
								  NOME         VARCHAR2(255 CHAR),
								  DESCRIZIONE  VARCHAR2(255 CHAR),
								  UPDATE_ID    NUMBER
								)
								LOGGING 
								NOCOMPRESS 
								NOCACHE
								NOPARALLEL
								MONITORING
			 					";
			 	$sql=new query($this->conn);
			 	$sql->set_sql ( $query_create );
			 	$sql->ins_upd ();
			 	$this->report .= "<hr>$query_create";
			 }

			 //TR_S_ANA_GRUPPIU
			 $query_create = "CREATE OR REPLACE TRIGGER TR_S_ANA_GRUPPIU 
								after insert or update or delete
								on ANA_GRUPPIU REFERENCING OLD AS v NEW AS n
								for each row
								BEGIN
								if (inserting) then
								INSERT INTO S_ANA_GRUPPIU values (null, sysdate, STORICO_ID.nextval, 'N', null,:n.ID_GRUPPOU, :n.NOME_GRUPPO, :n.DESCRIZIONE, :n.UPDATE_ID);
								end if;
								if (updating) then
								INSERT INTO S_ANA_GRUPPIU values (null, sysdate, STORICO_ID.nextval, 'O', null,:v.ID_GRUPPOU, :v.NOME_GRUPPO, :v.DESCRIZIONE, :v.UPDATE_ID );
								INSERT INTO S_ANA_GRUPPIU values (null, sysdate, STORICO_ID.currval, 'N', null,:n.ID_GRUPPOU, :n.NOME_GRUPPO, :n.DESCRIZIONE, :n.UPDATE_ID );
								end if;
								if (deleting) then
								INSERT INTO S_ANA_GRUPPIU values (null, sysdate, STORICO_ID.nextval, 'D', null,:v.ID_GRUPPOU, :v.NOME_GRUPPO, :v.DESCRIZIONE, :v.UPDATE_ID);
								end if;
								END;";
			 $sql=new query($this->conn);
			 $sql->set_sql ( $query_create );
			 $sql->ins_upd ();
			 $this->report .= "<hr>$query_create";
			 
			 //TR_S_ANA_UTENTI_1
			 $query_create = "CREATE OR REPLACE TRIGGER TR_S_ANA_UTENTI_1 
								after insert or update or delete
								on ANA_UTENTI_1 REFERENCING OLD AS v NEW AS n
								for each row
								BEGIN
								if (inserting) then
								INSERT INTO S_ANA_UTENTI_1 values (null, sysdate, STORICO_ID.nextval, 'N', null,:n.USERID,:n.ID_TIPOLOGIA,:n.COGNOME,:n.NOME,:n.CODICE_FISCALE,:n.AZIENDA_ENTE,:n.VIA,:n.CAP,:n.CITTA,:n.PROV,:n.NAZIONE,:n.TELEFONO,:n.FAX,:n.MEMO,:n.EMAIL,:n.UPDATE_ID);
								end if;
								if (updating) then
								INSERT INTO S_ANA_UTENTI_1 values (null, sysdate, STORICO_ID.nextval, 'O', null,:v.USERID,:v.ID_TIPOLOGIA,:v.COGNOME,:v.NOME,:v.CODICE_FISCALE,:v.AZIENDA_ENTE,:v.VIA,:v.CAP,:v.CITTA,:v.PROV,:v.NAZIONE,:v.TELEFONO,:v.FAX,:v.MEMO,:v.EMAIL,:v.UPDATE_ID );
								INSERT INTO S_ANA_UTENTI_1 values (null, sysdate, STORICO_ID.currval, 'N', null,:n.USERID,:n.ID_TIPOLOGIA,:n.COGNOME,:n.NOME,:n.CODICE_FISCALE,:n.AZIENDA_ENTE,:n.VIA,:n.CAP,:n.CITTA,:n.PROV,:n.NAZIONE,:n.TELEFONO,:n.FAX,:n.MEMO,:n.EMAIL,:n.UPDATE_ID );
								end if;
								if (deleting) then
								INSERT INTO S_ANA_UTENTI_1 values (null, sysdate, STORICO_ID.nextval, 'D', null,:v.USERID,:v.ID_TIPOLOGIA,:v.COGNOME,:v.NOME,:v.CODICE_FISCALE,:v.AZIENDA_ENTE,:v.VIA,:v.CAP,:v.CITTA,:v.PROV,:v.NAZIONE,:v.TELEFONO,:v.FAX,:v.MEMO,:v.EMAIL,:v.UPDATE_ID);
								end if;
								END;";
			 $sql=new query($this->conn);
			 $sql->set_sql ( $query_create );
			 $sql->ins_upd ();
			 $this->report .= "<hr>$query_create";
			 
			 //TR_S_FUNZIONI
			 $query_create = "CREATE OR REPLACE TRIGGER TR_S_FUNZIONI 
								after insert or update or delete
								on FUNZIONI REFERENCING OLD AS v NEW AS n
								for each row
								BEGIN
								if (inserting) then
								INSERT INTO S_FUNZIONI values (null, sysdate, STORICO_ID.nextval, 'N', null,:n.NOME,:n.ABILITATO,:n.PASSWD_FLAG,:n.IANUSGATE_FLAG,:n.SSL_ONLY_FLAG,:n.CRT_ONLY_FLAG,:n.ID_VISTA,:n.UPDATE_ID);
								end if;
								if (updating) then
								INSERT INTO S_FUNZIONI values (null, sysdate, STORICO_ID.nextval, 'O', null,:v.NOME,:v.ABILITATO,:v.PASSWD_FLAG,:v.IANUSGATE_FLAG,:v.SSL_ONLY_FLAG,:v.CRT_ONLY_FLAG,:v.ID_VISTA,:v.UPDATE_ID);
								INSERT INTO S_FUNZIONI values (null, sysdate, STORICO_ID.currval, 'N', null,:n.NOME,:n.ABILITATO,:n.PASSWD_FLAG,:n.IANUSGATE_FLAG,:n.SSL_ONLY_FLAG,:n.CRT_ONLY_FLAG,:n.ID_VISTA,:n.UPDATE_ID);
								end if;
								if (deleting) then
								INSERT INTO S_FUNZIONI values (null, sysdate, STORICO_ID.nextval, 'D', null,:v.NOME,:v.ABILITATO,:v.PASSWD_FLAG,:v.IANUSGATE_FLAG,:v.SSL_ONLY_FLAG,:v.CRT_ONLY_FLAG,:v.ID_VISTA,:v.UPDATE_ID);
								end if;
								END;";
			 $sql=new query($this->conn);
			 $sql->set_sql ( $query_create );
			 $sql->ins_upd ();
			 $this->report .= "<hr>$query_create";
			 
			 //TR_S_GRUPPIF
			 $query_create = "CREATE OR REPLACE TRIGGER TR_S_GRUPPIF 
								after insert or update or delete
								on GRUPPIF REFERENCING OLD AS v NEW AS n
								for each row
								BEGIN
								if (inserting) then
								INSERT INTO S_GRUPPIF values (null, sysdate, STORICO_ID.nextval, 'N', null,:n.ID_GRUPPOF,:n.ABILITATO,:n.ID_VISTA,:n.UPDATE_ID);
								end if;
								if (updating) then
								INSERT INTO S_GRUPPIF values (null, sysdate, STORICO_ID.nextval, 'O', null,:v.ID_GRUPPOF,:v.ABILITATO,:v.ID_VISTA,:v.UPDATE_ID);
								INSERT INTO S_GRUPPIF values (null, sysdate, STORICO_ID.currval, 'N', null,:n.ID_GRUPPOF,:n.ABILITATO,:n.ID_VISTA,:n.UPDATE_ID);
								end if;
								if (deleting) then
								INSERT INTO S_GRUPPIF values (null, sysdate, STORICO_ID.nextval, 'D', null,:v.ID_GRUPPOF,:v.ABILITATO,:v.ID_VISTA,:v.UPDATE_ID);
								end if;
								END;";
			 $sql=new query($this->conn);
			 $sql->set_sql ( $query_create );
			 $sql->ins_upd ();
			 $this->report .= "<hr>$query_create";
			 
			 //TR_S_GRUPPIU
			 $query_create = "CREATE OR REPLACE TRIGGER TR_S_GRUPPIU 
								after insert or update or delete
								on GRUPPIU REFERENCING OLD AS v NEW AS n
								for each row
								BEGIN
								if (inserting) then
								INSERT INTO S_GRUPPIU values (null, sysdate, STORICO_ID.nextval, 'N', null,:n.ID_GRUPPOU,:n.ABILITATO,:n.ID_TIPO,:n.BUDGET,:n.CONSUMO,:n.ID_VISTA,:n.UPDATE_ID);
								end if;
								if (updating) then
								INSERT INTO S_GRUPPIU values (null, sysdate, STORICO_ID.nextval, 'O', null,:v.ID_GRUPPOU,:v.ABILITATO,:v.ID_TIPO,:v.BUDGET,:v.CONSUMO,:v.ID_VISTA,:v.UPDATE_ID);
								INSERT INTO S_GRUPPIU values (null, sysdate, STORICO_ID.currval, 'N', null,:n.ID_GRUPPOU,:n.ABILITATO,:n.ID_TIPO,:n.BUDGET,:n.CONSUMO,:n.ID_VISTA,:n.UPDATE_ID);
								end if;
								if (deleting) then
								INSERT INTO S_GRUPPIU values (null, sysdate, STORICO_ID.nextval, 'D', null,:v.ID_GRUPPOU,:v.ABILITATO,:v.ID_TIPO,:v.BUDGET,:v.CONSUMO,:v.ID_VISTA,:v.UPDATE_ID);
								end if;
								END;";
			 $sql=new query($this->conn);
			 $sql->set_sql ( $query_create );
			 $sql->ins_upd ();
			 $this->report .= "<hr>$query_create";
			 
			 //TR_S_GRUPPIU_FUNZ
			 $query_create = "CREATE OR REPLACE TRIGGER TR_S_GRUPPIU_FUNZ 
								after insert or update or delete
								on GRUPPIU_FUNZ REFERENCING OLD AS v NEW AS n
								for each row
								BEGIN
								if (inserting) then
								INSERT INTO S_GRUPPIU_FUNZ values (null, sysdate, STORICO_ID.nextval, 'N', null,:n.NOME_FUNZ,:n.ID_GRUPPOU,:n.TIPO_ECCEZIONE,:n.UPDATE_ID);
								end if;
								if (updating) then
								INSERT INTO S_GRUPPIU_FUNZ values (null, sysdate, STORICO_ID.nextval, 'O', null,:v.NOME_FUNZ,:v.ID_GRUPPOU,:v.TIPO_ECCEZIONE,:v.UPDATE_ID);
								INSERT INTO S_GRUPPIU_FUNZ values (null, sysdate, STORICO_ID.currval, 'N', null,:n.NOME_FUNZ,:n.ID_GRUPPOU,:n.TIPO_ECCEZIONE,:n.UPDATE_ID);
								end if;
								if (deleting) then
								INSERT INTO S_GRUPPIU_FUNZ values (null, sysdate, STORICO_ID.nextval, 'D', null,:v.NOME_FUNZ,:v.ID_GRUPPOU,:v.TIPO_ECCEZIONE,:v.UPDATE_ID);
								end if;
								END;";
			 $sql=new query($this->conn);
			 $sql->set_sql ( $query_create );
			 $sql->ins_upd ();
			 $this->report .= "<hr>$query_create";
			 
			 //TR_S_GRUPPIF_FUNZ
			 $query_create = "CREATE OR REPLACE TRIGGER TR_S_GRUPPIF_FUNZ 
								after insert or update or delete
								on GRUPPIF_FUNZ REFERENCING OLD AS v NEW AS n
								for each row
								BEGIN
								if (inserting) then
								INSERT INTO S_GRUPPIF_FUNZ values (null, sysdate, STORICO_ID.nextval, 'N', null,:n.NOME_FUNZ,:n.ID_GRUPPOF,:n.ABILITATO,:n.UPDATE_ID);
								end if;
								if (updating) then
								INSERT INTO S_GRUPPIF_FUNZ values (null, sysdate, STORICO_ID.nextval, 'O', null,:v.NOME_FUNZ,:v.ID_GRUPPOF,:v.ABILITATO,:v.UPDATE_ID);
								INSERT INTO S_GRUPPIF_FUNZ values (null, sysdate, STORICO_ID.currval, 'N', null,:n.NOME_FUNZ,:n.ID_GRUPPOF,:n.ABILITATO,:n.UPDATE_ID);
								end if;
								if (deleting) then
								INSERT INTO S_GRUPPIF_FUNZ values (null, sysdate, STORICO_ID.nextval, 'D', null,:v.NOME_FUNZ,:v.ID_GRUPPOF,:v.ABILITATO,:v.UPDATE_ID);
								end if;
								END;";
			 $sql=new query($this->conn);
			 $sql->set_sql ( $query_create );
			 $sql->ins_upd ();
			 $this->report .= "<hr>$query_create";
			 
			 //TR_S_ANA_FUNZIONI
			 $query_create = "CREATE OR REPLACE TRIGGER TR_S_ANA_FUNZIONI
								after insert or update or delete
								on ANA_FUNZIONI REFERENCING OLD AS v NEW AS n
								for each row
								BEGIN
								if (inserting) then
								INSERT INTO S_ANA_FUNZIONI values (null, sysdate, STORICO_ID.nextval, 'N', null, :n.NOME, :n.DESCRIZIONE, :n.UPDATE_ID);
								end if;
								if (updating) then
								INSERT INTO S_ANA_FUNZIONI values (null, sysdate, STORICO_ID.nextval, 'O', null,:v.NOME, :v.DESCRIZIONE, :v.UPDATE_ID );
								INSERT INTO S_ANA_FUNZIONI values (null, sysdate, STORICO_ID.currval, 'N', null,:n.NOME, :n.DESCRIZIONE, :n.UPDATE_ID );
								end if;
								if (deleting) then
								INSERT INTO S_ANA_FUNZIONI values (null, sysdate, STORICO_ID.nextval, 'D', null,:v.NOME, :v.DESCRIZIONE, :v.UPDATE_ID);
								end if;
								END;";
			 $sql=new query($this->conn);
			 $sql->set_sql ( $query_create );
			 $sql->ins_upd ();
			 $this->report .= "<hr>$query_create";
			 
			 
			 //TR_S_ANA_GRUPPIF
			 $query_create = "CREATE OR REPLACE TRIGGER TR_S_ANA_GRUPPIF 
								after insert or update or delete
								on ANA_GRUPPIF REFERENCING OLD AS v NEW AS n
								for each row
								BEGIN
								if (inserting) then
								INSERT INTO S_ANA_GRUPPIF values (null, sysdate, STORICO_ID.nextval, 'N', null,:n.ID_GRUPPOF, :n.NOME_GRUPPO, :n.DESCRIZIONE, :n.UPDATE_ID);
								end if;
								if (updating) then
								INSERT INTO S_ANA_GRUPPIF values (null, sysdate, STORICO_ID.nextval, 'O', null,:v.ID_GRUPPOF, :v.NOME_GRUPPO, :v.DESCRIZIONE, :v.UPDATE_ID );
								INSERT INTO S_ANA_GRUPPIF values (null, sysdate, STORICO_ID.currval, 'N', null,:n.ID_GRUPPOF, :n.NOME_GRUPPO, :n.DESCRIZIONE, :n.UPDATE_ID );
								end if;
								if (deleting) then
								INSERT INTO S_ANA_GRUPPIF values (null, sysdate, STORICO_ID.nextval, 'D', null,:v.ID_GRUPPOF, :v.NOME_GRUPPO, :v.DESCRIZIONE, :v.UPDATE_ID);
								end if;
								END;";
			 $sql=new query($this->conn);
			 $sql->set_sql ( $query_create );
			 $sql->ins_upd ();
			 $this->report .= "<hr>$query_create";
			 
			 //TR_S_UTENTI
			 $query_create = "CREATE OR REPLACE TRIGGER TR_S_UTENTI
								after insert or update or delete
								on UTENTI REFERENCING OLD AS v NEW AS n
								for each row
								BEGIN
								if (inserting) then
								INSERT INTO S_UTENTI values (null, sysdate, STORICO_ID.nextval, 'N', null,:n.USERID,:n.PASSWORD,:n.ABILITATO,:n.ID_TIPOLOGIA,:n.BUDGET,:n.CONSUMO,:n.SCADENZAPWD,:n.DTTM_SCADENZAPWD,:n.DTTM_ULTIMOACCESSO,:n.SBLOCCOPWD,:n.ID_VISTA,:n.UPDATE_ID);
								end if;
								if (updating) then
								INSERT INTO S_UTENTI values (null, sysdate, STORICO_ID.nextval, 'O', null,:v.USERID,:v.PASSWORD,:v.ABILITATO,:v.ID_TIPOLOGIA,:v.BUDGET,:v.CONSUMO,:v.SCADENZAPWD,:v.DTTM_SCADENZAPWD,:v.DTTM_ULTIMOACCESSO,:v.SBLOCCOPWD,:v.ID_VISTA,:v.UPDATE_ID);
								INSERT INTO S_UTENTI values (null, sysdate, STORICO_ID.currval, 'N', null,:n.USERID,:n.PASSWORD,:n.ABILITATO,:n.ID_TIPOLOGIA,:n.BUDGET,:n.CONSUMO,:n.SCADENZAPWD,:n.DTTM_SCADENZAPWD,:n.DTTM_ULTIMOACCESSO,:n.SBLOCCOPWD,:n.ID_VISTA,:n.UPDATE_ID);
								end if;
								if (deleting) then
								INSERT INTO S_UTENTI values (null, sysdate, STORICO_ID.nextval, 'D', null,:v.USERID,:v.PASSWORD,:v.ABILITATO,:v.ID_TIPOLOGIA,:v.BUDGET,:v.CONSUMO,:v.SCADENZAPWD,:v.DTTM_SCADENZAPWD,:v.DTTM_ULTIMOACCESSO,:v.SBLOCCOPWD,:v.ID_VISTA,:v.UPDATE_ID);
								end if;
								END;";
			 $sql=new query($this->conn);
			 $sql->set_sql ( $query_create );
			 $sql->ins_upd ();
			 $this->report .= "<hr>$query_create";
			 
			 //TR_S_UTENTI_FUNZ
			 $query_create = "CREATE OR REPLACE TRIGGER TR_S_UTENTI_FUNZ 
								after insert or update or delete
								on UTENTI_FUNZ REFERENCING OLD AS v NEW AS n
								for each row
								BEGIN
								if (inserting) then
								INSERT INTO S_UTENTI_FUNZ values (null, sysdate, STORICO_ID.nextval, 'N', null,:n.USERID,:n.NOME_FUNZ,:n.TIPO_ECCEZIONE,:n.UPDATE_ID);
								end if;
								if (updating) then
								INSERT INTO S_UTENTI_FUNZ values (null, sysdate, STORICO_ID.nextval, 'O', null,:v.USERID,:v.NOME_FUNZ,:v.TIPO_ECCEZIONE,:v.UPDATE_ID);
								INSERT INTO S_UTENTI_FUNZ values (null, sysdate, STORICO_ID.currval, 'N', null,:n.USERID,:n.NOME_FUNZ,:n.TIPO_ECCEZIONE,:n.UPDATE_ID);
								end if;
								if (deleting) then
								INSERT INTO S_UTENTI_FUNZ values (null, sysdate, STORICO_ID.nextval, 'D', null,:v.USERID,:v.NOME_FUNZ,:v.TIPO_ECCEZIONE,:v.UPDATE_ID);
								end if;
								END;";
			 $sql=new query($this->conn);
			 $sql->set_sql ( $query_create );
			 $sql->ins_upd ();
			 $this->report .= "<hr>$query_create";
			 
			 //TR_S_GRUPPIU_GRUPPIF
			 $query_create = "CREATE OR REPLACE TRIGGER TR_S_GRUPPIU_GRUPPIF
								after insert or update or delete
								on GRUPPIU_GRUPPIF REFERENCING OLD AS v NEW AS n
								for each row
								BEGIN
								if (inserting) then
								INSERT INTO S_GRUPPIU_GRUPPIF values (null, sysdate, STORICO_ID.nextval, 'N', null,:n.ID_GRUPPOU,:n.ID_GRUPPOF,:n.ABILITATO,:n.UPDATE_ID);
								end if;
								if (updating) then
								INSERT INTO S_GRUPPIU_GRUPPIF values (null, sysdate, STORICO_ID.nextval, 'O', null,:v.ID_GRUPPOU,:v.ID_GRUPPOF,:v.ABILITATO,:v.UPDATE_ID);
								INSERT INTO S_GRUPPIU_GRUPPIF values (null, sysdate, STORICO_ID.currval, 'N', null,:n.ID_GRUPPOU,:n.ID_GRUPPOF,:n.ABILITATO,:n.UPDATE_ID);
								end if;
								if (deleting) then
								INSERT INTO S_GRUPPIU_GRUPPIF values (null, sysdate, STORICO_ID.nextval, 'D', null,:v.ID_GRUPPOU,:v.ID_GRUPPOF,:v.ABILITATO,:v.UPDATE_ID);
								end if;
								END;";
			 $sql=new query($this->conn);
			 $sql->set_sql ( $query_create );
			 $sql->ins_upd ();
			 $this->report .= "<hr>$query_create";
			 
			 //TR_S_UTENTI_GRUPPIU
			 $query_create = "CREATE OR REPLACE TRIGGER TR_S_UTENTI_GRUPPIU 
								after insert or update or delete
								on UTENTI_GRUPPIU REFERENCING OLD AS v NEW AS n
								for each row
								BEGIN
								if (inserting) then
								INSERT INTO S_UTENTI_GRUPPIU values (null, sysdate, STORICO_ID.nextval, 'N', null,:n.USERID,:n.ID_GRUPPOU,:n.ABILITATO,:n.UPDATE_ID);
								end if;
								if (updating) then
								INSERT INTO S_UTENTI_GRUPPIU values (null, sysdate, STORICO_ID.nextval, 'O', null,:v.USERID,:v.ID_GRUPPOU,:v.ABILITATO,:v.UPDATE_ID);
								INSERT INTO S_UTENTI_GRUPPIU values (null, sysdate, STORICO_ID.currval, 'N', null,:n.USERID,:n.ID_GRUPPOU,:n.ABILITATO,:n.UPDATE_ID);
								end if;
								if (deleting) then
								INSERT INTO S_UTENTI_GRUPPIU values (null, sysdate, STORICO_ID.nextval, 'D', null,:v.USERID,:v.ID_GRUPPOU,:v.ABILITATO,:v.UPDATE_ID);
								end if;
								END;";
			 $sql=new query($this->conn);
			 $sql->set_sql ( $query_create );
			 $sql->ins_upd ();
			 $this->report .= "<hr>$query_create";
			 
			 //TR_S_UTENTI_VISTEAMMIN
			 $query_create = "CREATE OR REPLACE TRIGGER TR_S_UTENTI_VISTEAMMIN 
								after insert or update or delete
								on UTENTI_VISTEAMMIN REFERENCING OLD AS v NEW AS n
								for each row
								BEGIN
								if (inserting) then
								INSERT INTO S_UTENTI_VISTEAMMIN values (null, sysdate, STORICO_ID.nextval, 'N', null,:n.USERID,:n.ID_VISTA,:n.UPDATE_ID);
								end if;
								if (updating) then
								INSERT INTO S_UTENTI_VISTEAMMIN values (null, sysdate, STORICO_ID.nextval, 'O', null,:v.USERID,:v.ID_VISTA,:v.UPDATE_ID);
								INSERT INTO S_UTENTI_VISTEAMMIN values (null, sysdate, STORICO_ID.currval, 'N', null,:n.USERID,:n.ID_VISTA,:n.UPDATE_ID);
								end if;
								if (deleting) then
								INSERT INTO S_UTENTI_VISTEAMMIN values (null, sysdate, STORICO_ID.nextval, 'D', null,:v.USERID,:v.ID_VISTA,:v.UPDATE_ID);
								end if;
								END;";
			 $sql=new query($this->conn);
			 $sql->set_sql ( $query_create );
			 $sql->ins_upd ();
			 $this->report .= "<hr>$query_create";
			 
			 /**
			 *END
			 *CREAZIONE TABELLE STORICO IANUS
			 *vmazzeo 20120530
			 */
			 
			 
			 
			 //Fine
			 $this->report .= "<hr><hr><b><font color='green'>INSTALLAZIONE EFFETTUATA CON SUCCESSO</font><b></hr></hr>";	
			 
 			$this->conn->commit();
 			
 			$service_name = $this->config_service['WF_NAME'];
		 	$this->report=str_replace("<hr>","\n",$this->report);
 			$handle = @fopen('xml/'.$service_name.'InstallReport.log', 'w');
			fwrite($handle, $this->report);
			fclose($handle);
 			
 			return;
 		}
 
	 	function fileSystem(){
	 		$service_name = $this->config_service['WF_NAME'];
			echo "fileSystem()";
	 		/**
	 		 * Sotto nomeservizio:
	 		 */
	 		$this->report .= "<hr>mkdir ../../estrazioni</hr>";
			system ( "mkdir ../../estrazioni" );
			$this->report .= "<hr>mkdir ../../sql</hr>";
			system ( "mkdir ../../sql" );
			$this->report .= "<hr>mkdir ../../temp</hr>";
			system ( "mkdir ../../temp" );
			$this->report .= "<hr>mkdir ../../xml</hr>";
			system ( "mkdir ../../xml" );
			$this->report .= "<hr>cp -rp  /http/lib/XMR/hyperlibs/estrazioni_tmp/ /http/servizi/PIERREL/$service_name/ </hr>";
			system ( "cp -rp  /http/lib/XMR/hyperlibs/estrazioni_tmp/ /http/servizi/PIERREL/$service_name/ " );
			
			system ( "chgrp -R devj /http/servizi/PIERREL/$service_name/* " );
			system ( "chmod ug+rw -R /http/servizi/PIERREL/$service_name/* " );
			$this->report .= "<hr>chmod ug+rw -R /http/servizi/PIERREL/$service_name/*";
			$this->report .= "<hr>chgrp -R devj /http/servizi/PIERREL/$service_name/*";
			
			/**
	 		 * Sotto cgi:
	 		 */
	 		$cgi_dir = "/http/servizi/PIERREL/$service_name/cgi/";
			$this->report .= "<hr>ln -sf /http/lib/AMR_3.0/upload_sql $cgi_dir </hr>";
			system ( "ln -sf /http/lib/AMR_3.0/upload_sql $cgi_dir " );
			$this->report .= "<hr>ln -sf /http/lib/AMR_3.0/utility_perl.pl $cgi_dir </hr>";
			system ( "ln -sf /http/lib/AMR_3.0/utility_perl.pl $cgi_dir " );
			$this->report .= "<hr>ln -sf /http/lib/AMR_3.0/utility_html.pl $cgi_dir </hr>";
			system ( "ln -sf /http/lib/AMR_3.0/utility_html.pl $cgi_dir " );
			$this->report .= "<hr>ln -sf /http/lib/AMR_3.0/fm_server.pl $cgi_dir </hr>";
			system ( "ln -sf /http/lib/AMR_3.0/fm_server.pl  $cgi_dir " );
			$this->report .= "<hr>ln -sf /http/lib/AMR_3.0/browse_table $cgi_dir </hr>";
			system ( "ln -sf /http/lib/AMR_3.0/browse_table $cgi_dir " );
			$this->report .= "<hr>ln -sf /http/lib/AMR_3.0/multiple_dnl_xpt $cgi_dir </hr>";
			system ( "ln -sf /http/lib/AMR_3.0/multiple_dnl_xpt  $cgi_dir " );
			$this->report .= "<hr>ln -sf /http/lib/AMR_3.0/multiple_dnl_csv $cgi_dir </hr>";
			system ( "ln -sf /http/lib/AMR_3.0/multiple_dnl_csv  $cgi_dir " );
			
			
			
			$this->report .= "<hr>ln -sf /http/lib/AMR_3.0/multiple_dnl_dmp $cgi_dir </hr>";
			system ( "ln -sf /http/lib/AMR_3.0/multiple_dnl_dmp $cgi_dir " );
			$this->report .= "<hr>ln -sf /http/lib/AMR_3.0/multiple_dnl_flat $cgi_dir </hr>";
			system ( "ln -sf /http/lib/AMR_3.0/multiple_dnl_flat $cgi_dir " );
			$this->report .= "<hr>ln -sf /http/lib/AMR_3.0/multiple_dnl_sas $cgi_dir </hr>";
			system ( "ln -sf /http/lib/AMR_3.0/multiple_dnl_sas $cgi_dir " );
			$this->report .= "<hr>ln -sf /http/lib/AMR_3.0/multiple_dnl_xls $cgi_dir </hr>";
			system ( "ln -sf /http/lib/AMR_3.0/multiple_dnl_xls $cgi_dir " );
			$this->report .= "<hr>ln -sf /http/lib/AMR_3.0/multiple_dnl_xml $cgi_dir </hr>";
			system ( "ln -sf /http/lib/AMR_3.0/multiple_dnl_xml $cgi_dir " );
			$this->report .= "<hr>ln -sf /http/lib/AMR_3.0/upload_xml_utenti  ".$cgi_dir."upload_xml </hr>";
			system ( "ln -sf /http/lib/AMR_3.0/upload_xml_utenti  ".$cgi_dir."upload_xml " );
			$this->report .= "<hr>ln -sf /http/lib/AMR_3.0/upload_xml.config_utenti  ".$cgi_dir."upload_xml.config </hr>";
			system ( "ln -sf /http/lib/AMR_3.0/upload_xml.config_utenti  ".$cgi_dir."upload_xml.config " );
			$this->report .= "<hr>ln -sf /http/lib/AMR_3.0/utility_storico.pl $cgi_dir </hr>";
			system ( "ln -sf /http/lib/AMR_3.0/utility_storico.pl $cgi_dir " );
			$this->report .= "<hr>ln -sf /http/lib/AMR_3.0/utility_xml.pl_utenti  ".$cgi_dir."utility_xml.pl </hr>";
			system ( "ln -sf /http/lib/AMR_3.0/utility_xml.pl_utenti  ".$cgi_dir."utility_xml.pl " );
			$this->report .= "<hr>ln -sf /http/lib/AMR_3.0/XmlObj.pm $cgi_dir </hr>";
			system ( "ln -sf /http/lib/AMR_3.0/XmlObj.pm $cgi_dir " );
			$this->report .= "<hr>ln -sf /http/lib/AMR_3.0/gestione_CRA $cgi_dir </hr>";
			system ( "ln -sf /http/lib/AMR_3.0/gestione_CRA $cgi_dir " );


			$this->report .= "<hr>ln -sf /http/lib/AMR_3.0/reports  $cgi_dir </hr>";
			system ( "ln -sf /http/lib/AMR_3.0/reports  $cgi_dir " );
			$this->report .= "<hr>ln -sf /http/lib/AMR_3.0/reports2  $cgi_dir </hr>";
			system ( "ln -sf /http/lib/AMR_3.0/reports2  $cgi_dir " );
			$this->report .= "<hr>ln -sf ../html/sys/".$service_name.".config   ".$cgi_dir."utility_study.config </hr>";
			system ( "ln -sf ../html/sys/".$service_name.".config   ".$cgi_dir."utility_study.config " );
			$this->report .= "<hr>ln -sf ../html/sys/".$service_name."_dm.config  ".$cgi_dir."utility_study_dm.config  </hr>";
			system ( "ln -sf ../html/sys/".$service_name."_dm.config  ".$cgi_dir."utility_study_dm.config " );
			
			$this->report .= "<hr>ln -sf /http/lib/AMR_3.0/utility_xml.pl_at  ".$cgi_dir."utility_xml.pl </hr>";
			system ( "ln -sf /http/lib/AMR_3.0/utility_xml.pl_at ".$cgi_dir."utility_xml.pl " );
			$this->report .= "<hr>ln -sf /http/lib/AMR_3.0/utility_storico.pl_at   ".$cgi_dir."utility_storico.pl </hr>";
			system ( "ln -sf /http/lib/AMR_3.0/utility_storico.pl_at  ".$cgi_dir."utility_storico.pl " );
			$this->report .= "<hr>ln -sf /http/lib/AMR_3.0/VALIDA_XML/ $cgi_dir </hr>";
			system ( "ln -sf /http/lib/AMR_3.0/VALIDA_XML/ $cgi_dir " );
			$this->report .= "<hr>ln -sf /http/lib/AMR_2.0/Expect.pm ".$cgi_dir."Expect.pm </hr>";
			system ( "ln -sf /http/lib/AMR_2.0/Expect.pm ".$cgi_dir."Expect.pm" );
			$this->report .= "<hr>cp -p /http/lib/XMR/hyperlibs/cgi/.allinea_sito_new  $cgi_dir   <b>DA CONFIGURARE</b></hr>";
			system ( "cp -p /http/lib/XMR/hyperlibs/cgi/.allinea_sito_new $cgi_dir".".allinea_sito_new" );
			$this->report .= "<hr>ln -sf /http/lib/AMR_3.0/allinea_sito_preprod $cgi_dir"."allinea_sito_new </hr>";
			system ( "ln -sf /http/lib/AMR_3.0/allinea_sito_preprod ".$cgi_dir."allinea_sito_new" );

			/**
	 		 * Sotto config:
	 		 */
	 		 $config_dir = "/http/servizi/PIERREL/$service_name/config/ ";
	 		$this->report .= "<hr>cp -p /http/lib/XMR/hyperlibs/config/logs.config  $config_dir  <b>DA CONFIGURARE</b></hr>";
			system ( "cp -p /http/lib/XMR/hyperlibs/config/logs.config  $config_dir  " );
			$this->report .= "<hr>cp -p /http/lib/XMR/hyperlibs/config/reports.cfg  $config_dir  <b>DA CONFIGURARE</b></hr>";
			system ( "cp -p /http/lib/XMR/hyperlibs/config/reports.cfg  $config_dir " );
			$this->report .= "<hr>cp -p /http/lib/XMR/hyperlibs/config/reports2.cfg  $config_dir  <b>DA CONFIGURARE</b></hr>";
			system ( "cp -p /http/lib/XMR/hyperlibs/config/reports2.cfg  $config_dir " );
			$this->report .= "<hr>cp -p /http/lib/XMR/hyperlibs/config/browsetable.xml  $config_dir </hr>";
			system ( "cp -p /http/lib/XMR/hyperlibs/config/browsetable.xml  $config_dir  " );

			system ( "chgrp -R devj /http/servizi/PIERREL/$service_name/* " );
			system ( "chmod ug+rw -R /http/servizi/PIERREL/$service_name/* " );
			$this->report .= "<hr>chmod ug+rw -R /http/servizi/PIERREL/$service_name/*";
			$this->report .= "<hr>chgrp -R devj /http/servizi/PIERREL/$service_name/*";

			/**
	 		 * Sotto scripts:
	 		 */
 			$scripts_dir = "/http/servizi/PIERREL/$service_name/scripts/";
			$this->report .= "<hr>ln -s /http/lib/AMR_2.0/update_authusers_dav $scripts_dir"."update_authusers_dav</hr>";
			system ( "ln -s /http/lib/AMR_2.0/update_authusers_dav $scripts_dir"."update_authusers_dav" );

			/**
	 		 * Sotto html:
	 		 */
 			$html_dir = "/http/servizi/PIERREL/$service_name/html/ ";
			$this->report .= "<hr>ln -sf uxmr/xml/imgserv/ $html_dir  </hr>";
			system ( "ln -sf uxmr/xml/imgserv/ $html_dir " );
			$this->report .= "<hr>mkdir ../sys</hr>";
			system ( "mkdir ../sys" );
 			$this->report .= "<hr>ln -sf /http/lib/XMR/hyperlibs/libs/images/ $html_dir  </hr>";
			system ( "ln -sf /http/lib/XMR/hyperlibs/libs/images/ $html_dir " );
			$this->report .= "<hr>ln -sf /http/lib/XMR/hyperlibs/libs/img/ $html_dir  </hr>";
			system ( "ln -sf /http/lib/XMR/hyperlibs/libs/img/ $html_dir " );
			$this->report .= "<hr>cp -rp /http/lib/php_utils/filemanager_8.34/To_Install_copy_me/filemanager/ $html_dir  </hr>";
			system ( "cp -rp /http/lib/php_utils/filemanager_8.34/To_Install_copy_me/filemanager/ $html_dir " );
			$this->report .= "<hr>ln -sf /http/lib/XMR/hyperlibs/public/ $html_dir  </hr>";
			system ( "ln -sf /http/lib/XMR/hyperlibs/public/ $html_dir " );
			$this->report .= "<hr>ln -sf /http/lib/XMR/hyperlibs/cf/ $html_dir  </hr>";
			system ( "ln -sf /http/lib/XMR/hyperlibs/cf/ $html_dir " );
			$this->report .= "<hr>ln -sf /http/lib/XMR/hyperlibs/css/ $html_dir  </hr>";
			system ( "ln -sf /http/lib/XMR/hyperlibs/css/ $html_dir " );
			$this->report .= "<hr>ln -sf /http/lib/php_utils/phporaadmin/ $html_dir  </hr>";
			system ( "ln -sf /http/lib/php_utils/phporaadmin/ $html_dir " );
			$this->report .= "<hr>cp -rp /http/lib/XMR/hyperlibs/XMLValidator/to_install_copy_me/XMLValidator/ $html_dir  </hr>";
			system ( "cp -rp /http/lib/XMR/hyperlibs/XMLValidator/to_install_copy_me/XMLValidator/ $html_dir " );
			$this->report .= "<hr>ln -sf uxmr/xml/login_template.htm $html_dir  </hr>";
			system ( "ln -sf uxmr/xml/login_template.htm $html_dir " );
				
			
			/**
			 * Sotto sys
			 */
			$sys_dir = "/http/servizi/PIERREL/$service_name/html/sys/";
			$this->report .= "<hr>cp -rp /http/lib/XMR/hyperlibs/sys/error/ $sys_dir  </hr>";
			system ( "cp -rp /http/lib/XMR/hyperlibs/sys/error/ $sys_dir  " );
			$this->report .= "<hr>cp -p /http/lib/XMR/hyperlibs/sys/nomestudio.config  ".$sys_dir.$service_name.".config  <b>DA CONFIGURARE</b></hr>";
			system ( "cp -p /http/lib/XMR/hyperlibs/sys/nomestudio.config  ".$sys_dir.$service_name.".config  " );
//			$this->report .= "<hr>mv ".$sys_dir."nomestudio.config ".$sys_dir.$service_name.".config</hr>";
//			system ( "mv ".$sys_dir."nomestudio.config ".$sys_dir.$service_name.".config" );
			$this->report .= "<hr>ln -sf /http/lib/XMR/hyperlibs/sys/upload/ $sys_dir  </hr>";
			system ( "ln -sf /http/lib/XMR/hyperlibs/sys/upload/ $sys_dir  " );
			$this->report .= "<hr>ln -sf /http/lib/XMR/hyperlibs/sys/shell/ $sys_dir  </hr>";
			system ( "ln -sf /http/lib/XMR/hyperlibs/sys/shell/ $sys_dir  " );
			$this->report .= "<hr>cp -rp /http/lib/XMR/hyperlibs/sys/browse_table/ $sys_dir  </hr>";
			system ( "cp -rp /http/lib/XMR/hyperlibs/sys/browse_table/  $sys_dir  " );
			$this->report .= "<hr>cp -rp /http/lib/XMR/hyperlibs/sys/sinc/ $sys_dir  </hr>";
			system ( "cp -rp /http/lib/XMR/hyperlibs/sys/sinc/  $sys_dir  " );
			$this->report .= "<hr>cp -rp /http/lib/XMR/hyperlibs/sys/reports/ $sys_dir  </hr>";
			system ( "cp -rp /http/lib/XMR/hyperlibs/sys/reports/  $sys_dir  " );
			$this->report .= "<hr>ln -sf /http/lib/XMR/hyperlibs/sys/search_engines/ $sys_dir  </hr>";
			system ( "ln -sf /http/lib/XMR/hyperlibs/sys/search_engines/  $sys_dir  " );
			$this->report .= "<hr>cp -p /http/lib/XMR/hyperlibs/sys/browse_table.xml  $sys_dir <b>DA CONFIGURARE multiple_dnl.config</b></hr>";
			system ( "cp -p /http/lib/XMR/hyperlibs/sys/browse_table.xml  $sys_dir  " );
			
			/**
			 * Sotto uxmr
			 */
			$this->report .= "<hr>cp -rp /http/lib/XMR/hyperlibs/uxmr/DB/ .</hr>";
			system ( "cp -rp /http/lib/XMR/hyperlibs/uxmr/DB/ ." );
			$this->report .= "<hr>ln -sf /http/lib/XMR/hyperlibs/uxmr/tb_variabili.php</hr>";
			system ( "ln -sf /http/lib/XMR/hyperlibs/uxmr/tb_variabili.php" );
			
			/**
			 * Sotto xml
			 */
			$xml_dir = "/http/servizi/PIERREL/$service_name/html/uxmr/xml/";
			$this->report .= "<hr>ln -sf ../../sys/ $xml_dir  </hr>";
			system ( "ln -sf ../../sys/ $xml_dir " );
			
			$this->report .= "<hr>mkdir  ".$xml_dir."OLDVERSIONS  </hr>";
			system ( "mkdir  ".$xml_dir."OLDVERSIONS" );
			
			/**
			 * File phpinfo.php
			 */
			$this->report .= "<hr>cp -p /http/lib/XMR/hyperlibs/phpinfo.php</hr>";
			system ( "cp -p /http/lib/XMR/hyperlibs/phpinfo.php /http/servizi/PIERREL/$service_name/html/" );
				
			/**
			 * Sotto logs
			 */
			$xml_dir = "/http/servizi/PIERREL/$service_name/html/logs/";
			$this->report .= "<hr>mkdir $xml_dir/LOGS_SQL  </hr>";
			system ( "mkdir $xml_dir/LOGS_SQL " );
			system ( "chmod 2770 $xml_dir/LOGS_SQL " );
			$this->report .= "<hr>mkdir $xml_dir/LOGS_XML  </hr>";
			system ( "mkdir $xml_dir/LOGS_XML " );
			system ( "chmod 2770 $xml_dir/LOGS_XML " );
			
			
			system ( "chgrp -R devj /http/servizi/PIERREL/$service_name/* " );
			system ( "chmod ug+rw -R /http/servizi/PIERREL/$service_name/* " );
			
			$service_name = $this->config_service['WF_NAME'];
		 	$this->report=str_replace("<hr>","\n",$this->report);
 			$handle = @fopen('xml/'.$service_name.'InstallReport.log', 'w');
			fwrite($handle, $this->report);
			fclose($handle);
			
			return;
	 	}
 	
		
		/**
 		 * Creazione Di : 
 		 * 
 		 * CMM_CENTER (Table) ;
 		 * $this->service_CMM_CENTER (View) ;
 		 * ID_XML (Sequence) ;
 		 * XML_FILES (Table) ;
 		 * ID_SQL (Sequence) ;
 		 * SQL_FILES (Table) ;
 		 * CRA_CENTER (Table) ;
 		 * S_X_ID (Sequence) ;
 		 * 
 		 */
		function checkTableExist(){
			
//			NUOVA PROCEDURA IN CreataCMMTable()
//
// 		$query_check_existence = "select table_name from user_tables where table_name=upper('CMM_CENTER')";
// 		$query = new query ( $this->conn );
// 		$query->set_sql ( $query_check_existence );
// 		$query->exec ();
// 		if($query->get_row ()){
// 			print_r($query->row['TABLE_NAME']);
// 			print_r($query_check_existence);
// 			$return = true;
// 		}
// 		else
// 		{
// 			$query_create = '
// 			CREATE TABLE CMM_CENTER
// 				  (
// 				    "ID_CENTER"  NUMBER(5,0) NOT NULL ENABLE,
// 				    "NAME"       VARCHAR2(255 CHAR),
// 				    "CODE"       VARCHAR2(20 CHAR),
// 				    "ADDRESS"    VARCHAR2(255 CHAR),
// 				    "CITY"       VARCHAR2(100 CHAR),
// 				    "ZIPCODE"    VARCHAR2(20 CHAR),
// 				    "COUNTRY"    NUMBER(3,0),
// 				    "EXP_PAT"    NUMBER(4,0),
// 				    "STATUS"     NUMBER(1,0) DEFAULT 0,
// 				    "HFILE_S"    NUMBER(1,0) DEFAULT 0,
// 				    "CENTERTYPE" VARCHAR2(10 CHAR),
// 				    CONSTRAINT "CK_CMM_CENTER_STATUS" CHECK (STATUS  IN (0,1)) ENABLE,
// 				    CONSTRAINT "CK_CMM_CENTER_HFILE_S" CHECK (STATUS IN (0,1)) ENABLE,
// 				    CONSTRAINT "PK_CMM_CENTER_ID_CENTER" PRIMARY KEY ("ID_CENTER") USING INDEX PCTFREE 10 INITRANS 2 MAXTRANS 255 COMPUTE STATISTICS STORAGE(INITIAL 65536 NEXT 1048576 MINEXTENTS 1 MAXEXTENTS 2147483645 PCTINCREASE 0 FREELISTS 1 FREELIST GROUPS 1 BUFFER_POOL DEFAULT) TABLESPACE "HYPERNET_OLTP" ENABLE
// 				  )
// 			';
// 			$sql = new query ( $this->conn );
// 			$sql->set_sql ( $query_create );
// 			$sql->ins_upd ();
// 			$this->report .= "<hr>$query_create";
// 		}

// 			$query = new query ( $this->conn );
// 			$query_check_existence2 = "select view_name from user_views where view_name=upper('{$this->service}_CMM_CENTER')";
// 			$query->set_sql ( $query_check_existence2 );
// 			$query->exec ();
// 			if($query->get_row ()){
// 				$return = true;
// 			}
// 			else
// 			{
// 				$query_create = "
// 				create or replace view {$this->config_service['service']}_CMM_CENTER as
// 					select id_center, name, code, address, city, zipcode, country, exp_pat, status, hfile_s, centertype from cmm_center
// 				";
// 				$sql = new query ( $this->conn );
// 				$sql->set_sql ( $query_create );
// 				$sql->ins_upd ();
// 				$this->report .= "<hr>$query_create";
// 			}
			
			/**
			 * Sequence per upload XML con storico S_X_ID
			 */
			 $query = new query ( $this->conn );
			$query_check_existence3 = "select sequence_name from user_sequences where sequence_name=upper('S_X_ID')";  
			$query->set_sql ( $query_check_existence3 );
			$query->exec ();
			if($query->get_row ()){
				$return = true;
			}
			else
			{
				
				$query_create = "
				CREATE SEQUENCE S_X_ID MINVALUE 1 MAXVALUE 9999999 INCREMENT BY 1 START WITH 1 NOCACHE ORDER  NOCYCLE
				";
				$sql = new query ( $this->conn );
				$sql->set_sql ( $query_create );
				$sql->ins_upd ();
				$this->report .= "<hr>$query_create";
			}
			
			/**
			 * Sequence per upload XML
			 */
//			 $query = new query ( $this->conn );
			$query_check_existence3 = "select sequence_name from user_sequences where sequence_name=upper('ID_XML')";  
			$query->set_sql ( $query_check_existence3 );
			$query->exec ();
			if($query->get_row ()){
				$return = true;
			}
			else
			{
				
				$query_create = "
				CREATE SEQUENCE ID_XML MINVALUE 1 MAXVALUE 9999999 INCREMENT BY 1 START WITH 1 NOCACHE ORDER  NOCYCLE
				";
				$sql = new query ( $this->conn );
				$sql->set_sql ( $query_create );
				$sql->ins_upd ();
				$this->report .= "<hr>$query_create";
			}
			
			/**
			 * Tabella per upload XML
			 */
//			 $query = new query ( $this->conn );
				$query_check_existence4 = "select table_name from user_tables where table_name=upper('XML_FILES')";
				$query->set_sql ( $query_check_existence4 );
				$query->exec ();
				if($query->get_row ()){
					$return = true;
				}
				else
				{
					$query_create = "
					create table XML_FILES
						(
						  USERID VARCHAR2(32 CHAR),
						  NF_XML VARCHAR2(200 CHAR),
						  INS_DT DATE,
						  ID     NUMBER,
						  PATH   VARCHAR2(200 CHAR)
						)
					";
					$sql = new query ( $this->conn );
					$sql->set_sql ( $query_create );
					$sql->ins_upd ();
					$this->report .= "<hr>$query_create";
				}
				
				/**
				 * Sequence per shell SQL
				 */
	//			 $query = new query ( $this->conn );
				$query_check_existence5 = "select sequence_name from user_sequences where sequence_name=upper('ID_SQL')";  
				$query->set_sql ( $query_check_existence5 );
				$query->exec ();
				if($query->get_row ()){
					$return = true;
				}
				else
				{
					$query_create = "
					CREATE SEQUENCE ID_SQL MINVALUE 1 MAXVALUE 9999999 INCREMENT BY 1 START WITH 1 NOCACHE ORDER  NOCYCLE
					";
					$sql = new query ( $this->conn );
					$sql->set_sql ( $query_create );
					$sql->ins_upd ();
					$this->report .= "<hr>$query_create";
				}
				
				/**
				 * Tabella per shell SQL
				 */
	//			 $query = new query ( $this->conn );
				$query_check_existence6 = "select table_name from user_tables where table_name=upper('SQL_FILES')";
				$query->set_sql ( $query_check_existence6 );
				$query->exec ();
				if($query->get_row ()){
					$return = true;
				}
				else
				{
					$query_create = "
					create table SQL_FILES
						(
						  USERID VARCHAR2(32 CHAR),
						  NF_SQL VARCHAR2(32 CHAR),
						  INS_DT DATE,
						  ID     NUMBER,
						  PATH   VARCHAR2(200 CHAR)
						)
					";
					$sql = new query ( $this->conn );
					$sql->set_sql ( $query_create );
					$sql->ins_upd ();
					$this->report .= "<hr>$query_create";
				}
				
				//echo "800A";
				/**
				 * COMMENTO PERCHE' DA ERRORE (vmazzeo 31.01.14)
// 				 * Tabella per conversione dei dati con download in SAS
// 				 */
// 				$this->service=$this->config_service['service'];
// 				$query_check_existence7 = "select table_name from user_tables where table_name=upper('{$this->service}_ORA2SAS')";
// 				$query->set_sql ( $query_check_existence7 );
// 				$query->exec ();
// 				if($query->get_row ()){
// 					$return = true;
// 				}
// 				else
// 				{
// 					$query_create = "
// 					create table {$this->service}_ORA2SAS
// 					(
// 					  old_tab VARCHAR2(200) not null,
// 					  new_tab VARCHAR2(200),
// 					  old_col VARCHAR2(200) not null,
// 					  new_col VARCHAR2(200),
// 					  constraint PK_ORA2SAS primary key (OLD_TAB, OLD_COL)  using index  tablespace HYPERNET_OLTP pctfree 10 initrans 2 maxtrans 255 storage ( initial 64K  next 1M  minextents 1  maxextents unlimited )
// 					)
// 					";
// 					$sql = new query ( $this->conn );
// 					$sql->set_sql ( $query_create );
// 					$sql->ins_upd ();
// 					$this->report .= "<hr>$query_create";
// 				}


				/**
				 * Tabella per emulare la user_tab_columns nell'export db
				 */
				$this->service=$this->config_service['service'];
				$query_check_existence8 = "select table_name from user_tables where table_name=upper('T_USER_TAB_COLUMNS')";
				$query->set_sql ( $query_check_existence8 );
				$query->exec ();
				if($query->get_row ()){
					$return = true;
				}
				else
				{
					$query_create = "
CREATE MATERIALIZED VIEW T_USER_TAB_COLUMNS
NOCACHE
LOGGING
NOCOMPRESS
NOPARALLEL
BUILD IMMEDIATE
REFRESH FORCE ON DEMAND
WITH PRIMARY KEY
AS 
SELECT table_name, column_name, data_type, data_type_mod, data_type_owner,
       data_length, data_precision, data_scale, nullable, column_id,
       default_length, num_distinct, low_value, high_value, density,
       num_nulls, num_buckets, last_analyzed, sample_size, character_set_name,
       char_col_decl_length, global_stats, user_stats, avg_col_len,
       char_length, char_used, v80_fmt_image, data_upgraded, histogram
  FROM user_tab_columns
					";
					$sql = new query ( $this->conn );
					$sql->set_sql ( $query_create );
					$sql->ins_upd ();
					$this->report .= "<hr>$query_create";
				}
				


				/**
				 * commento da aggiungere alla vista materializzata appena creata
				 */
					$query_create = "COMMENT ON MATERIALIZED VIEW T_USER_TAB_COLUMNS IS 'snapshot table for snapshot T_USER_TAB_COLUMNS'";
					$sql = new query ( $this->conn );
					$sql->set_sql ( $query_create );
					$sql->ins_upd ();
					$this->report .= "<hr>$query_create";


/*
					$query_create = "
DECLARE
  X NUMBER;
BEGIN
  SYS.DBMS_JOB.SUBMIT
  ( job       => X 
   ,what      => 'begin DBMS_MVIEW.REFRESH(''t_user_tab_columns''); end; '
   ,next_date => to_date('06/10/2011 05.00.00','dd/mm/yyyy hh24:mi:ss')
   ,interval  => 'SYSDATE+1'
   ,no_parse  => FALSE
  );
  SYS.DBMS_OUTPUT.PUT_LINE('Job Number is: ' || to_char(x));
COMMIT;
END
";
*/
										
					$query_create = "
DECLARE
  X NUMBER;
BEGIN
  SYS.DBMS_JOB.SUBMIT
  ( job       => X 
   ,what      => 'begin DBMS_MVIEW.REFRESH(''T_USER_TAB_COLUMNS''); end; '
   ,next_date => TRUNC(SYSDATE+1)+6/24
   ,interval  => 'TRUNC(SYSDATE+1)+6/24'
   ,no_parse  => FALSE
  );
  SYS.DBMS_OUTPUT.PUT_LINE('Job Number is: ' || to_char(x));
COMMIT;
END;
";
					
					$sql = new query ( $this->conn );
					$sql->set_sql ( $query_create );
					$sql->ins_upd ();
					$this->report .= "<hr>$query_create";

				/**
				 * 
				 * Sinonimi per il Single Sign On 
				 * @var unknown_type
				 */
//				$query_create = "
//					create or replace synonym IDP_SSO_ASSOCIATIONS
//					  for IDP_PIERREL.SSO_ASSOCIATIONS
//					";
//				$sql = new query ( $this->conn );
//				$sql->set_sql ( $query_create );
//				$sql->ins_upd ();
//				$this->report .= "<hr>$query_create";
//				
//				$query_create = "
//					create or replace synonym IDP_SSO_USERS
//					  for IDP_PIERREL.SSO_USERS;
//					";
//				$sql = new query ( $this->conn );
//				$sql->set_sql ( $query_create );
//				$sql->ins_upd ();
//				$this->report .= "<hr>$query_create";
				
				
				$service_name = $this->config_service['WF_NAME'];
			 	$this->report=str_replace("<hr>","\n",$this->report);
	 			$handle = @fopen('xml/'.$service_name.'InstallReport.log', 'w');
				fwrite($handle, $this->report);
				fclose($handle);
				
				return $return;
				
		}	
		
	
	/**
	 * 
	 * Controlla l'esistenza delle tabelle e viste necessarie alle eQ per campo, che in caso negativo vengono create in automatico.
	 * 
	 * 
	 * @return $exist
	 *
	 * Creazione Di : 
	 * 
	 * $this->service_INTEGRAZIONI_SCHEDE (View) ;
	 * $this->service_EQ (Table) ;
	 * $this->service_EQSEQ (Sequence) ;
	 * $this->service_EQFIELD (Table) ;
	 * 
	 */
	function checkCreateEqTb($xml_form=null){
		$exist=false;
		$this->service=$this->config_service['service'];
		$this->pk_field=$this->config_service['PK_SERVICE'];
		
		
		/**
		* CREAZIONE TABELLE _REGISTRAZIONE
		* vmazzeo 20120530
		* START
		*/
		
		//{$this->service}_REGISTRAZIONE
		$query = new query ( $this->conn );
		$query_check_existence = "select table_name from user_tables where table_name=upper('{$this->service}_REGISTRAZIONE')";
		$query->set_sql ( $query_check_existence );
		$query->exec ();
		if($query->get_row ()==''){
			$query_create = "CREATE TABLE {$this->service}_REGISTRAZIONE
										(
										  CODPAT          NUMBER,
										  USERID_INS      VARCHAR2(32 CHAR),
										  ESAM            NUMBER,
										  PROGR           NUMBER,
										  VISITNUM        NUMBER,
										  VISITNUM_PROGR  NUMBER,
										  CENTER          VARCHAR2(40 CHAR),
										  HD_SUBJID       NUMBER,
										  INITIALS        VARCHAR2(2 CHAR),
										  PATIENT_LANG    VARCHAR2(3 CHAR),
										  PASSWORD        VARCHAR2(8 CHAR),
										  SITEID          VARCHAR2(10 CHAR),
										  SUBJID          VARCHAR2(4 CHAR),
										  CONSTRAINT PK_{$this->service}_REGISTRAZIONE
										 PRIMARY KEY
										 (CODPAT, ESAM, PROGR, VISITNUM, VISITNUM_PROGR),
										  CONSTRAINT FK_{$this->service}_REGISTRAZIONE_COORD 
										 FOREIGN KEY (VISITNUM, VISITNUM_PROGR, PROGR, ESAM, CODPAT) 
										 REFERENCES {$this->service}_COORDINATE (VISITNUM,VISITNUM_PROGR,PROGR,ESAM,CODPAT)
										    ON DELETE CASCADE
										)
										LOGGING 
										NOCOMPRESS 
										NOCACHE
										NOPARALLEL
										MONITORING
					 	";
			$sql=new query($this->conn);
			$sql->set_sql ( $query_create );
			$sql->ins_upd ();
			$this->report .= "<hr>$query_create";
		}
		
		//EQ_{$this->service}_REGISTRAZIONE
		$query = new query ( $this->conn );
		$query_check_existence = "select table_name from user_tables where table_name=upper('EQ_{$this->service}_REGISTRAZIONE')";
		$query->set_sql ( $query_check_existence );
		$query->exec ();
		if($query->get_row ()==''){
			$query_create = "CREATE TABLE EQ_{$this->service}_REGISTRAZIONE
										(
										  ID              NUMBER,
										  COMMENTO        VARCHAR2(400 CHAR),
										  CODPAT          NUMBER,
										  USERID_INS      VARCHAR2(32 CHAR),
										  ESAM            NUMBER,
										  PROGR           NUMBER,
										  VISITNUM        NUMBER,
										  VISITNUM_PROGR  NUMBER,
										  CENTER          VARCHAR2(40 CHAR),
										  HD_SUBJID       NUMBER,
										  INITIALS        VARCHAR2(2 CHAR),
										  PATIENT_LANG    VARCHAR2(3 CHAR),
										  PASSWORD        VARCHAR2(8 CHAR),
										  SITEID          VARCHAR2(10 CHAR),
										  SUBJID          VARCHAR2(4 CHAR),
										  CONSTRAINT EQ_PK_{$this->service}_REGISTRAZIONE
										 PRIMARY KEY
										 (ID)
										)
										LOGGING 
										NOCOMPRESS 
										NOCACHE
										NOPARALLEL
										MONITORING";
			$sql=new query($this->conn);
			$sql->set_sql ( $query_create );
			$sql->ins_upd ();
			$this->report .= "<hr>$query_create";
		}
		
		//S_{$this->service}_REGISTRAZIONE
		$query = new query ( $this->conn );
		$query_check_existence = "select table_name from user_tables where table_name=upper('S_{$this->service}_REGISTRAZIONE')";
		$query->set_sql ( $query_check_existence );
		$query->exec ();
		if($query->get_row ()==''){
			$query_create = "CREATE TABLE S_{$this->service}_REGISTRAZIONE
										(
										  USERID          VARCHAR2(32 CHAR),
										  MODDT           DATE,
										  MODPROG         NUMBER(6)                     NOT NULL,
										  FL_QUERY        CHAR(1 CHAR)                  NOT NULL,
										  ID_QUERY        NUMBER(6),
										  CODPAT          NUMBER,
										  USERID_INS      VARCHAR2(32 CHAR),
										  ESAM            NUMBER,
										  PROGR           NUMBER,
										  VISITNUM        NUMBER,
										  VISITNUM_PROGR  NUMBER,
										  CENTER          VARCHAR2(40 CHAR),
										  HD_SUBJID       NUMBER,
										  INITIALS        VARCHAR2(2 CHAR),
										  PATIENT_LANG    VARCHAR2(3 CHAR),
										  PASSWORD        VARCHAR2(8 CHAR),
										  SITEID          VARCHAR2(10 CHAR),
										  SUBJID          VARCHAR2(4 CHAR),
										  CONSTRAINT S_PK_{$this->service}_REGISTRAZIONE
										 PRIMARY KEY
										 (MODPROG)
										)
										LOGGING 
										NOCOMPRESS 
										NOCACHE
										NOPARALLEL
										MONITORING";
			$sql=new query($this->conn);
			$sql->set_sql ( $query_create );
			$sql->ins_upd ();
			$this->report .= "<hr>$query_create";
		}
		
		//S_X_{$this->service}
		$query = new query ( $this->conn );
		$query_check_existence = "select table_name from user_tables where table_name=upper('S_X_{$this->service}')";
		$query->set_sql ( $query_check_existence );
		$query->exec ();
		if($query->get_row ()==''){
			$query_create = "CREATE TABLE S_X_{$this->service}
												(
												  	CODPAT NUMBER,
													ESAM NUMBER, 
													PROGR NUMBER, 
													VISITNUM NUMBER, 
													VISITNUM_PROGR NUMBER, 
													CENTER VARCHAR2(200 CHAR), 
													VALUE_NEW VARCHAR2(4000 CHAR), 
													D_VALUE_NEW VARCHAR2(4000 CHAR), 
													VALUE_OLD VARCHAR2(4000 CHAR), 
													D_VALUE_OLD VARCHAR2(4000 CHAR), 
													NOMETAB VARCHAR2(100 CHAR), 
													VAR VARCHAR2(200 CHAR), 
													FIELD VARCHAR2(200 CHAR), 
													MODDT DATE, 
													ACTION VARCHAR2(256 CHAR), 
													USERID VARCHAR2(256 CHAR)
												) 
												LOGGING
												NOCOMPRESS 
												NOCACHE
												NOPARALLEL
												MONITORING";
			$sql=new query($this->conn);
			$sql->set_sql ( $query_create );
			$sql->ins_upd ();
			$this->report .= "<hr>$query_create";
		}
		
		
		/**
		 * END
		 * CREAZIONE TABELLE _REGISTRAZIONE
		 * vmazzeo 20120530
		 *
		 */
		
		
		 //creazione tabella se non esiste
		$query_check_existence = "select table_name from user_tables where table_name=upper('{$this->service}_EQ')";
//		echo $query_check_existence;
		$query = new query ( $this->conn );
		$query->set_sql ( $query_check_existence );
		$query->exec ();
		if($query->get_row ()){
//			print_r($query->row['TABLE_NAME']);
//			print_r($query_check_existence);
			$exist=true;
		}
		else
		{ 
			//vmazzeo 20120530 inserito campo MOD_DT date in $query_create 
			$query_create = "
			create table {$this->service}_EQ
			(
			  EQUERY_INT NUMBER not null,
			  {$this->pk_field}     NUMBER not null,
			  USERID_INS VARCHAR2(32 CHAR),
			  INS_DT     DATE,
			  MOD_DT	 DATE,
			  STATO      NUMBER,
			  RICH_DM VARCHAR2(4000 CHAR),
			  RICH_DE VARCHAR2(4000 CHAR),
			  RISP_DM VARCHAR2(4000 CHAR),
			  CLOSE_DT   DATE,
									  CONSTRAINT PK_{$this->service}_EQ
									 PRIMARY KEY
									 (EQUERY_INT)
			)
			";


			$sql = new query ( $this->conn );
			$sql->set_sql ( $query_create );
			$sql->ins_upd ();
			$this->report .= "<hr>$query_create";
			$exist=true;
		}

		
		
		/**
		 * CREAZIONE TABELLA STORICO S_{$this->service}_EQ
		 * vmazzeo 20120530
		 * START
		 */
		$query_check_existence = "select table_name from user_tables where table_name=upper('S_{$this->service}_EQ')";
		//		echo $query_check_existence;
		$query = new query ( $this->conn );
		$query->set_sql ( $query_check_existence );
		$query->exec ();
		if($query->get_row ()){
			//			print_r($query->row['TABLE_NAME']);
			//			print_r($query_check_existence);
			$exist=true;
		}
		else
		{
			//vmazzeo 20120530 inserito campo MOD_DT date in $query_create
			$query_create = "CREATE TABLE S_{$this->service}_EQ
							(
							  USERID      VARCHAR2(32 CHAR),
							  MODDT       DATE,
							  MODPROG     NUMBER(6)                         NOT NULL,
							  FL_QUERY    CHAR(1 CHAR)                      NOT NULL,
							  ID_QUERY    NUMBER(6),
							  EQUERY_INT  NUMBER                            NOT NULL,
							  CODPAT      NUMBER                            NOT NULL,
							  USERID_INS  VARCHAR2(32 CHAR),
							  INS_DT      DATE,
							  MOD_DT      DATE,
							  STATO       NUMBER,
							  RICH_DM     VARCHAR2(4000 CHAR),
							  RICH_DE     VARCHAR2(4000 CHAR),
							  RISP_DM     VARCHAR2(4000 CHAR),
							  CLOSE_DT    DATE,
							  CONSTRAINT S_PK_{$this->service}_EQ
							 PRIMARY KEY
							 (MODPROG)
							)
							LOGGING 
							NOCOMPRESS 
							NOCACHE
							NOPARALLEL
							MONITORING";
		
		
			$sql = new query ( $this->conn );
			$sql->set_sql ( $query_create );
			$sql->ins_upd ();
			$this->report .= "<hr>$query_create";
			$exist=true;
		}
		/**
		* END
		* CREAZIONE TABELLA STORICO S_{$this->service}_EQ
		* vmazzeo 20120530
		*/
		
		
		 //creazione tabella se non esiste
		$query_check_existence = "select table_name from user_tables where table_name=upper('{$this->service}_EQFIELD')";
//		echo $query_check_existence;
		$query = new query ( $this->conn );
		$query->set_sql ( $query_check_existence );
		$query->exec ();
		if($query->get_row ()){
//			print_r($query->row['TABLE_NAME']);
//			print_r($query_check_existence);
			$exist=true;
		}
		else
		{

			$query_create = "
			create table {$this->service}_EQFIELD
			(
			  {$this->pk_field}       NUMBER not null,
			  ESAM           NUMBER not null,
			  VISITNUM       NUMBER not null,
			  VISITNUM_PROGR NUMBER not null,
			  PROGR          NUMBER not null,
			  EQ_INT         NUMBER not null,
			  FIELD          VARCHAR2(200) not null,
			  VALORE         VARCHAR2(4000),
			  NOTE           VARCHAR2(4000),
			  NOTE_DE           VARCHAR2(4000),
			  STATOFIELD          NUMBER,
			  VALORE_OLD	VARCHAR2(4000 CHAR),
			  ACTION	NUMBER,
									  CONSTRAINT PK_{$this->service}_EQFIELD
									 PRIMARY KEY
									 (EQ_INT,FIELD)
			)
			";

			$sql = new query ( $this->conn );
			$sql->set_sql ( $query_create );
			$sql->ins_upd ();
			$this->report .= "<hr>$query_create";
			$exist=true;
		}

		/**
		* CREAZIONE TABELLA STORICO S_{$this->service}_EQFIELD
		* vmazzeo 20120530
		* START
		*/
		$query_check_existence = "select table_name from user_tables where table_name=upper('S_{$this->service}_EQFIELD')";
		//		echo $query_check_existence;
		$query = new query ( $this->conn );
		$query->set_sql ( $query_check_existence );
		$query->exec ();
		if($query->get_row ()){
			//			print_r($query->row['TABLE_NAME']);
			//			print_r($query_check_existence);
			$exist=true;
		}
		else
		{
			//vmazzeo 20120530 inserito campo MOD_DT date in $query_create
			$query_create = "CREATE TABLE S_{$this->service}_EQFIELD
									(
									  USERID          VARCHAR2(32 CHAR),
									  MODDT           DATE,
									  MODPROG         NUMBER(6)                     NOT NULL,
									  FL_QUERY        CHAR(1 CHAR)                  NOT NULL,
									  ID_QUERY        NUMBER(6),
									  CODPAT          NUMBER                        NOT NULL,
									  ESAM            NUMBER                        NOT NULL,
									  VISITNUM        NUMBER                        NOT NULL,
									  VISITNUM_PROGR  NUMBER                        NOT NULL,
									  PROGR           NUMBER                        NOT NULL,
									  EQ_INT          NUMBER                        NOT NULL,
									  FIELD           VARCHAR2(200 CHAR)            NOT NULL,
									  VALORE          VARCHAR2(4000 CHAR),
									  NOTE            VARCHAR2(4000 CHAR),
									  NOTE_DE         VARCHAR2(4000 CHAR),
									  STATOFIELD      NUMBER,
									  VALORE_OLD	VARCHAR2(4000 CHAR),
									  ACTION	NUMBER,
									  CONSTRAINT S_PK_{$this->service}_EQFIELD
									 PRIMARY KEY
									 (MODPROG)
									)
									LOGGING 
									NOCOMPRESS 
									NOCACHE
									NOPARALLEL
									MONITORING";
		
		
			$sql = new query ( $this->conn );
			$sql->set_sql ( $query_create );
			$sql->ins_upd ();
			$this->report .= "<hr>$query_create";
			$exist=true;
		}
		/**
		 * END
		 * CREAZIONE TABELLA STORICO S_{$this->service}_EQFIELD
		 * vmazzeo 20120530
		 */
		
		 //creazione sequence se non esiste
		$query_check_existence = "select sequence_name from user_sequences where sequence_name=upper('{$this->service}_EQSEQ')";
//		echo $query_check_existence;
		$query = new query ( $this->conn );
		$query->set_sql ( $query_check_existence );
		$query->exec ();
		if($query->get_row ()){
//			print_r($query->row['SEQUENCE_NAME']);
//			print_r($query_check_existence);
			$exist=true;
		}
		else
		{
			$query_create = "
			create sequence {$this->service}_EQSEQ
			minvalue 1
			maxvalue 999999999999999999999999999
			start with 1
			increment by 1
			nocache
			";
			$sql = new query ( $this->conn );
			$sql->set_sql ( $query_create );
			$sql->ins_upd ();
			$this->report .= "<hr>$query_create";
			$exist=true;
		}
		
		/**
		 * CREAZIONE TRIGGER TR_{$this->service}_EQ ed _EQFIELD
		 * vmazzeo 20120530
		 * START
		 */
		$query_create = "CREATE OR REPLACE TRIGGER TR_{$this->service}_EQ
						AFTER INSERT OR UPDATE OR DELETE  ON {$this->service}_EQ REFERENCING OLD AS v NEW AS newRow for each row
						BEGIN
						if updating then
						insert into s_{$this->service}_eq (USERID, MODDT, MODPROG, FL_QUERY, ID_QUERY, EQUERY_INT, CODPAT, USERID_INS, INS_DT, STATO, RICH_DM, RICH_DE, RISP_DM, CLOSE_DT, MOD_DT) 
						values (:newRow.userid_ins, sysdate, STORICO_ID.nextval, 'O', :v.EQUERY_INT,:v.EQUERY_INT, :v.CODPAT, :v.USERID_INS, 
						:v.INS_DT,:v.STATO, :v.RICH_DM, :v.RICH_DE, :v.RISP_DM, :v.CLOSE_DT, :v.MOD_DT);
						insert into s_{$this->service}_eq (USERID, MODDT, MODPROG, FL_QUERY, ID_QUERY, EQUERY_INT, CODPAT, USERID_INS, INS_DT, STATO, RICH_DM, RICH_DE, RISP_DM, CLOSE_DT, MOD_DT) 
						values (:newRow.userid_ins, sysdate, STORICO_ID.nextval, 'N', :newRow.EQUERY_INT,:newRow.EQUERY_INT, :newRow.CODPAT, :newRow.USERID_INS, 
						:newRow.INS_DT,:newRow.STATO, :newRow.RICH_DM, :newRow.RICH_DE, :newRow.RISP_DM, :newRow.CLOSE_DT, :newRow.MOD_DT);
						end if;
						END;";
		$sql=new query($this->conn);
		$sql->set_sql ( $query_create );
		$sql->ins_upd ();
		$this->report .= "<hr>$query_create";
		
		$query_create = "CREATE OR REPLACE TRIGGER TR_{$this->service}_EQFIELD
						AFTER INSERT OR UPDATE OR DELETE  ON {$this->service}_EQFIELD REFERENCING OLD AS v NEW AS newRow for each row
						declare username_tmp VARCHAR2(20);
						BEGIN
						if updating then
						if :newRow.NOTE_DE is not null then
						select USERID_INS into username_tmp from {$this->service}_REGISTRAZIONE where CODPAT=:newRow.CODPAT;
						else 
						select USERID_INS into username_tmp from {$this->service}_EQ where EQUERY_INT=:newRow.EQ_INT;
						end if; 
						if (:newRow.NOTE_DE is not null and :v.NOTE_DE is null) then
						update {$this->service}_EQ set mod_dt=sysdate where EQUERY_INT=:newRow.EQ_INT and mod_dt is null;
						end if;
						insert into s_{$this->service}_eqfield (USERID, MODDT, MODPROG, FL_QUERY, ID_QUERY, CODPAT, ESAM, VISITNUM, VISITNUM_PROGR, PROGR, EQ_INT, FIELD, VALORE, NOTE, NOTE_DE, STATOFIELD,VALORE_OLD,ACTION) 
						values (username_tmp, sysdate, STORICO_ID.nextval, 'O', :v.EQ_INT, :v.CODPAT, :v.ESAM, :v.VISITNUM, 
						:v.VISITNUM_PROGR, :v.PROGR, :v.EQ_INT, :v.FIELD, :v.VALORE, :v.NOTE, :v.NOTE_DE, :v.STATOFIELD,:v.VALORE_OLD,:v.ACTION);
						insert into s_{$this->service}_eqfield (USERID, MODDT, MODPROG, FL_QUERY, ID_QUERY, CODPAT, ESAM, VISITNUM, VISITNUM_PROGR, PROGR, EQ_INT, FIELD, VALORE, NOTE, NOTE_DE, STATOFIELD,VALORE_OLD,ACTION) 
						values (username_tmp, sysdate, STORICO_ID.nextval, 'N', :newRow.EQ_INT, :newRow.CODPAT, :newRow.ESAM, :newRow.VISITNUM, 
						:newRow.VISITNUM_PROGR, :newRow.PROGR, :newRow.EQ_INT, :newRow.FIELD, :newRow.VALORE, :newRow.NOTE, :newRow.NOTE_DE, :newRow.STATOFIELD,:newRow.VALORE_OLD,:newRow.ACTION);
						end if;
						END;";
		$sql=new query($this->conn);
		$sql->set_sql ( $query_create );
		$sql->ins_upd ();
		$this->report .= "<hr>$query_create";
		
		$service_name = $this->config_service['WF_NAME'];
	 	$this->report=str_replace("<hr>","\n",$this->report);
		$handle = @fopen('xml/'.$service_name.'InstallReport.log', 'w');
		fwrite($handle, $this->report);
		fclose($handle);

		return $exist;
 	}
 	
 	function CreateSessionsTable(){
 		$query = new query ( $this->conn );
 		
 		$sessions_table_exist = "select table_name from user_tables where table_name=upper('SESSIONS')";
		$query->set_sql ( $sessions_table_exist );
		$query->exec ();
		if($query->get_row ()){
			$return =  true;
		}
		else
		{
			$query_create = '
			create table SESSIONS
			(
			  ID      NUMBER not null,
			  USERID  VARCHAR2(32 CHAR),
			  DATA    DATE,
			  URL     VARCHAR2(2000),
			  REFERER VARCHAR2(2000),
			  TIPO    VARCHAR2(20)
			)
			';
			$sql = new query ( $this->conn );
			$sql->set_sql ( $query_create );
			$sql->exec ();
			
			
			$query_create = '
			CREATE INDEX SESSION_ID_IDX ON SESSIONS
			(ID)
			LOGGING
			NOPARALLEL
			';
			$sql = new query ( $this->conn );
			$sql->set_sql ( $query_create );
			$sql->exec ();

			$query_create = '
			CREATE INDEX SESSION_USERID_IDX ON SESSIONS
			(USERID)
			LOGGING
			NOPARALLEL
			';
			$sql = new query ( $this->conn );
			$sql->set_sql ( $query_create );
			$sql->exec ();
				
		}
		
// 		$query_check_existence7 = "select table_name from user_tables where table_name=upper('CRA_CENTER')";
// 		$query->set_sql ( $query_check_existence7 );
// 		$query->exec ();
// 		if($query->get_row ()){
// //			print_r($query->row['TABLE_NAME']);
// //			print_r($query_check_existence);
// 			$return =  true;
// 		}
// 		else
// 		{
// 			$query_create = "
// 			create table CRA_CENTER
// 				(
// 				  USERID_CRA VARCHAR2(8 CHAR) not null,
// 				  CENTER     NUMBER(4) not null,
// 				  constraint PK_CRA_CENTER primary key (USERID_CRA, CENTER) using index tablespace HYPERNET_OLTP pctfree 10  initrans 2 maxtrans 255 storage ( initial 64K  next 1M minextents 1  maxextents unlimited ),
// 				  CONSTRAINT FK_CRA_CENTER_USERID_CRA FOREIGN KEY (USERID_CRA) REFERENCES UTENTI (USERID)  DISABLE					
// 				)
// 			";
			
// 			$sql = new query ( $this->conn );
// 			$sql->set_sql ( $query_create );
// 			$sql->ins_upd ();
			
// 			$query_create2 = "
// 			create table S_CRA_CENTER
// 			(
// 			  USERID     VARCHAR2(8 CHAR) not null,
// 			  MODDT      DATE,
// 			  MODPROG    NUMBER(6) not null,
// 			  USERID_CRA VARCHAR2(8 CHAR) not null,
// 			  CENTER     NUMBER(3) not null
// 			)
// 			";
			
// 			$sql = new query ( $this->conn );
// 			$sql->set_sql ( $query_create2 );
// 			$sql->exec ();
			
			
// 			$query_create3 = "
// 			create table S_X_CRA_CENTER
// 			(
// 			  ID         NUMBER not null,
// 			  TIPO       CHAR(1) not null,
// 			  NOMECAMPO  VARCHAR2(256) not null,
// 			  VALORE_OLD VARCHAR2(4000),
// 			  VALORE_NEW VARCHAR2(4000),
// 			  ID_QUERY   NUMBER,
// 			  DATA       DATE,
// 			  USERID     VARCHAR2(32),
// 			  PROG_S     NUMBER,
// 			  USERID_CRA VARCHAR2(8) not null,
// 			  CENTER     NUMBER(4) not null
// 			)
// 			";
			
// 			$sql = new query ( $this->conn );
// 			$sql->set_sql ( $query_create3 );
// 			$sql->exec ();
// 		}

		$service_name = $this->config_service['WF_NAME'];
	 	$this->report=str_replace("<hr>","\n",$this->report);
		$handle = @fopen('xml/'.$service_name.'InstallReport.log', 'w');
		fwrite($handle, $this->report);
		fclose($handle);
		
		return $return;
 	}
 	
	/**
	 * 
	 * TODO: MODIFICARE NOME FUNZIONE!
	 *
	 * crea la tabella [PREFIX]_FIRMA_UTENTI_CENTRI E [PREFIX]_DBLOCK
	 * 
	 */
	function CreateCMMTable() {
		$query = new query ( $this->conn );
			
		// FIRMA_UTENTI_CENTRI
		$sessions_table_exist = "SELECT COUNT(*) as CONTO FROM ALL_VIEWS WHERE VIEW_NAME=upper('".$this->service."_FIRMA_UTENTI_CENTRI')";
		$query->set_sql ( $sessions_table_exist );
		$query->exec ();
		if($query->get_row ()){
			$return =  true;
		}
		else
		{
			$query_create = "
			CREATE OR REPLACE FORCE VIEW {$this->service}_FIRMA_UTENTI_CENTRI
			(
			   USERNAME,
			   CENTER,
			   USER_ROLE
			)
			AS
			   SELECT uss.userid AS username, uss.site_id AS center, sp.code AS user_role
			     FROM users_sites_studies uss, studies_profiles sp
			    WHERE USS.STUDY_PREFIX = SP.STUDY_PREFIX AND sp.STUDY_PREFIX = '{$this->service}'";
			$sql = new query ( $this->conn );
			$sql->set_sql ( $query_create );
			$sql->exec ();
			$this->report .= "<hr>$query_create";
		}
		
		// DB_LOCK
		$query_check_existenceDBLOCK = "SELECT TABLE_NAME FROM USER_TABLES WHERE TABLE_NAME='{$this->service}_DBLOCK'";
		$query->set_sql ( $query_check_existenceDBLOCK );
		$query->exec ();
		if($query->get_row ()){
			$return = true;
		}
		else
		{
			$query_create = "
				create table {$this->service}_DBLOCK
				(
				  	CENTER NUMBER DEFAULT -1 NOT NULL ENABLE, 
					CODPAT NUMBER DEFAULT -1 NOT NULL ENABLE, 
					VISITNUM NUMBER DEFAULT -1 NOT NULL ENABLE, 
					ESAM NUMBER DEFAULT -1 NOT NULL ENABLE, 
					DBLOCK NUMBER, 
					D_DBLOCK VARCHAR2(25 CHAR),
				  CONSTRAINT PK_{$this->service}_DBLOCK PRIMARY KEY (CENTER,CODPAT,VISITNUM,ESAM)
				)
				";
			$sql = new query ( $this->conn );
			$sql->set_sql ( $query_create );
			$sql->exec ();
			$this->report .= "<hr>$query_create";
		}
		
		// S_DB_LOCK
		$query_check_existenceS_DBLOCK = "SELECT TABLE_NAME FROM USER_TABLES WHERE TABLE_NAME='S_{$this->service}_DBLOCK'";
		$query->set_sql ( $query_check_existenceS_DBLOCK );
		$query->exec ();
		if($query->get_row ()){
			$return = true;
		}
		else
		{
			$query_create = "
			create table S_{$this->service}_DBLOCK
			(
			ID_STORICO NUMBER(12,0),
    		MODDATE DATE,
    		MODUSER VARCHAR2(200 CHAR),
			CENTER NUMBER DEFAULT -1 NOT NULL ENABLE, 
			CODPAT NUMBER DEFAULT -1 NOT NULL ENABLE, 
			VISITNUM NUMBER DEFAULT -1 NOT NULL ENABLE, 
			ESAM NUMBER DEFAULT -1 NOT NULL ENABLE, 
			DBLOCK NUMBER, 
			D_DBLOCK VARCHAR2(25 CHAR),
			CONSTRAINT PK_S_{$this->service}_DBLOCK PRIMARY KEY (ID_STORICO)
			)";
			$sql = new query ( $this->conn );
			$sql->set_sql ( $query_create );
			$sql->exec ();
			$this->report .= "<hr>$query_create";
		}
		
		// I18N
		$query_check_existenceI18N = "SELECT TABLE_NAME FROM USER_TABLES WHERE TABLE_NAME='{$this->service}_I18N'";
		$query->set_sql ( $query_check_existenceI18N );
		$query->exec ();
		if($query->get_row ()){
			$return = true;
		}
		else
		{
			$query_create = "
				CREATE
				TABLE {$this->service}_I18N
				(
				LANG  VARCHAR2(4 BYTE)
				, LABEL VARCHAR2(4000 BYTE)
				, TEXT  VARCHAR2(4000 BYTE)
				, CONSTRAINT PK_{$this->service}_I18N PRIMARY KEY (LANG, LABEL)
				)
				";
			$sql = new query ( $this->conn );
			$sql->set_sql ( $query_create );
			$sql->exec ();
			$this->report .= "<hr>$query_create";
		}
		//COPIA TRADUZIONI DI DEFAULT DALLA TABELLA ACM_STUDY_I18N (se esiste, cioè se creata durante inizializzazione istanza: vedi file acm_installer.ddl.sql)
		$query_check_existence_STUDY_I18N = "SELECT TABLE_NAME FROM USER_TABLES WHERE TABLE_NAME='ACM_STUDY_I18N'";
		$query->set_sql ( $query_check_existence_STUDY_I18N );
		$query->exec ();
		if($query->get_row ()){
			$query_insert_I18N = "INSERT INTO {$this->service}_I18N (LANG,LABEL,TEXT) SELECT LANG,LABEL,TEXT FROM ACM_STUDY_I18N";
			$sql = new query ( $this->conn );
			$sql->set_sql ( $query_insert_I18N );
			$sql->exec ();
			$this->report .= "<hr>$query_insert_I18N";

		}
		// USER_PROFILE
			$query_create = "CREATE OR REPLACE FORCE VIEW {$this->service}_USER_PROFILE 
							(PROFILE_CODE, 
							 DESCRIZIONE, 
							 POLICY, 
							 SCOPE, 
							 USERID)
							AS
							  SELECT
							    sp.code AS profile_code
							  , ag.descrizione
							  , sp.policy
							  , sp.scope
							  , us.userid
							  FROM
							    studies_profiles sp
							  , studies s
							  , users_profiles up
							  , users_studies us
							  , utenti_gruppiu ug
							  , ana_gruppiu ag
							  WHERE
							    sp.study_prefix  =s.prefix
							  AND us.study_prefix=s.prefix
							  AND up.profile_id  =sp.id
							  AND us.userid      =up.userid
							  AND s.active       =1
							  AND sp.active      =1
							  AND up.active      =1
							  AND ug.userid      =us.userid
							  AND ug.abilitato   =1
							  AND ug.id_gruppou  =ag.id_gruppou
							  AND ag.nome_gruppo =s.prefix
							    ||'_'
							    ||sp.code
							  AND s.prefix='{$this->service}'";
			$sql = new query ( $this->conn );
			$sql->set_sql ( $query_create );
			$sql->exec ();
			$this->report .= "<hr>$query_create";
		
		
			// USER_PROFILES
			$query_create = "CREATE OR REPLACE FORCE VIEW {$this->service}_USER_PROFILES (PROFILE_CODE,
							  DESCRIZIONE, POLICY, SCOPE, USERID, ACTIVE, PROFILE_ID)
							AS
							  SELECT
							    sp.code AS profile_code
							  , ag.descrizione
							  , sp.policy
							  , sp.scope
							  , us.userid
							  , up.active
							  , sp.id
							  FROM
							    studies_profiles sp
							  , studies s
							  , users_profiles up
							  , users_studies us
							  , utenti_gruppiu ug
							  , ana_gruppiu ag
							  WHERE
							    sp.study_prefix  =s.prefix
							  AND us.study_prefix=s.prefix
							  AND up.profile_id  =sp.id
							  AND us.userid      =up.userid
							  AND s.active       =1
							  AND sp.active      =1
							  AND ug.userid      =us.userid
							  AND ug.abilitato   =1
							  AND ug.id_gruppou  =ag.id_gruppou
							  AND ag.nome_gruppo =s.prefix
							    ||'_'
							    ||sp.code
							  AND s.prefix='{$this->service}'";
			$sql = new query ( $this->conn );
			$sql->set_sql ( $query_create );
			$sql->exec ();
			$this->report .= "<hr>$query_create";
			
			
			
		$service_name = $this->config_service['WF_NAME'];
	 	$this->report=str_replace("<hr>","\n",$this->report);
		$handle = @fopen('xml/'.$service_name.'InstallReport.log', 'w');
		fwrite($handle, $this->report);
		fclose($handle);
		
		return $return;
	}
	
	/**
	* Fix delle viste {$service}_UTENTI_CENTRI e {$service}_CMM_CENTER
	*
	*/
	function FixViews() {
		$query = new query ( $this->conn );
	
		$query_create = 
		"CREATE OR REPLACE FORCE VIEW ".$this->service."_CENTRI (CENTER, DENOM, USERID)
		AS
		  SELECT
		    s.id    AS CENTER
		  , s.descr AS DENOM
		  , ''      AS USERID
		  FROM
		    SITES s
		  , SITES_STUDIES ss
		  WHERE
		    ss.STUDY_PREFIX='".$this->service."'
		  AND ss.ACTIVE    =1
  		  AND ss.SITE_ID   =s.id";
		
		$sql = new query ( $this->conn );
		$sql->exec ( $query_create );
		$this->report .= "<hr>$query_create";
		
		$query_create = "
			CREATE OR REPLACE FORCE VIEW ".$this->service."_UTENTI_CENTRI (USERID,
			  CENTER, TIPOLOGIA)
			AS
			  SELECT
			    up.userid   AS USERID
			  , uss.SITE_ID AS CENTER
			  , sp.POLICY   AS TIPOLOGIA
			  FROM
			    users_profiles up
			  , studies_profiles sp
			  , USERS_SITES_STUDIES uss
			  WHERE
			    up.profile_id        =sp.id
			  AND up.active          =1
			  AND sp.active          =1
			  AND sp.scope           >0
			  AND sp.STUDY_PREFIX    ='".$this->service."'
			  AND uss.ACTIVE         =1
			  AND uss.STUDY_PREFIX   =sp.STUDY_PREFIX
			  AND uss.USER_PROFILE_ID=up.PROFILE_ID
			  AND up.userid          =uss.userid
			  UNION ALL
			  SELECT
			    up.userid AS USERID
			  ,ss.SITE_ID AS CENTER
			  ,sp.POLICY  AS TIPOLOGIA
			  FROM
			    users_profiles up
			  , studies_profiles sp
			  , SITES_STUDIES ss
			  WHERE
			    up.profile_id    =sp.id
			  AND up.active      =1
			  AND sp.active      =1
			  AND sp.scope       =0
			  AND sp.STUDY_PREFIX='".$this->service."'
			  AND ss.ACTIVE      =1
			  AND ss.STUDY_PREFIX=sp.STUDY_PREFIX
		";
		$sql = new query ( $this->conn );
		$sql->exec ( $query_create );
		$this->report .= "<hr>$query_create";
		/*
		$query_create = '
			create or replace view '.$this->service.'_cmm_center as
			select id_center, name, code, address, country, status from cmm_center
		';
		$sql = new query ( $this->conn );
		$sql->exec ( $query_create );
		*
		$this->report .= "<hr>$query_create";
	*/
		$query_create = '
 	 CREATE OR REPLACE VIEW ANA_UTENTI AS
		SELECT userid, cognome, nome, email, azienda_ente
    	 FROM ana_utenti_1
		';

		$sql = new query ( $this->conn );
		$sql->exec ( $query_create );
		$this->report .= "<hr>$query_create";


	}

	function PrintReport() {
		die($this->report);
	}
 }
