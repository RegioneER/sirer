--------------------------------------------------------
--  File creato - mercoledì-dicembre-02-2015   
--------------------------------------------------------
--------------------------------------------------------
--  DDL for Table S___installer__prefix___REGISTRAZIONE
--------------------------------------------------------

  CREATE TABLE "S___installer__prefix___REGISTRAZIONE" 
   (	"USERID" VARCHAR2(32 CHAR), 
	"MODDT" DATE, 
	"MODPROG" NUMBER, 
	"FL_QUERY" CHAR(1 CHAR), 
	"ID_QUERY" NUMBER, 
	"CODPAT" NUMBER, 
	"USERID_INS" VARCHAR2(40 CHAR), 
	"ESAM" NUMBER, 
	"PROGR" NUMBER, 
	"VISITNUM" NUMBER, 
	"VISITNUM_PROGR" NUMBER, 
	"CENTER" NUMBER
   ) ;
--------------------------------------------------------
--  DDL for Table __installer__prefix___ACTIVITI_MESSAGES
--------------------------------------------------------

  CREATE TABLE "__installer__prefix___ACTIVITI_MESSAGES" 
   (	"PROCESSID" VARCHAR2(200 CHAR), 
	"MESSAGE" VARCHAR2(200 CHAR), 
	"REDIRECT" VARCHAR2(2000 CHAR)
   ) ;
--------------------------------------------------------
--  DDL for Table __installer__prefix___CENTER_TB
--------------------------------------------------------

  CREATE TABLE "__installer__prefix___CENTER_TB" 
   (	"WHERE_" VARCHAR2(4000 CHAR)
   ) ;
--------------------------------------------------------
--  DDL for Table __installer__prefix___COORDINATE
--------------------------------------------------------

  CREATE TABLE "__installer__prefix___COORDINATE" 
   (	"VISITNUM" NUMBER, 
	"VISITNUM_PROGR" NUMBER, 
	"PROGR" NUMBER, 
	"ESAM" NUMBER, 
	"INIZIO" NUMBER(1,0), 
	"FINE" NUMBER(1,0), 
	"INSERTDT" DATE, 
	"MODDT" DATE, 
	"USERID" VARCHAR2(32 CHAR), 
	"VISITCLOSE" NUMBER(1,0) DEFAULT 0, 
	"INV_QUERY" VARCHAR2(200 CHAR), 
	"CODPAT" NUMBER, 
	"ABILITATO" NUMBER, 
	"EQ_ACTION" NUMBER, 
	"CREATE_USER" VARCHAR2(80 CHAR), 
	"SEND_DT" DATE
   ) ;
--------------------------------------------------------
--  DDL for Table __installer__prefix___EQUERY
--------------------------------------------------------

  CREATE TABLE "__installer__prefix___EQUERY" 
   (	"ID" NUMBER, 
	"CENTER" VARCHAR2(10 CHAR), 
	"CODPAT" NUMBER, 
	"VISITNUM" NUMBER, 
	"ESAM" NUMBER, 
	"PROGR" NUMBER, 
	"Q_USERID" VARCHAR2(32 CHAR), 
	"QUESTION" VARCHAR2(4000 CHAR), 
	"QUEST_DT" DATE, 
	"TO_BE_VALIDATE" NUMBER, 
	"ANSWER" VARCHAR2(4000 CHAR), 
	"ANS_DT" DATE, 
	"A_USERID" VARCHAR2(32 CHAR), 
	"VALIDATA" NUMBER, 
	"CHIUSA" NUMBER, 
	"VAL_DT" DATE, 
	"VAL_USERID" VARCHAR2(32 CHAR), 
	"VISITNUM_PROGR" NUMBER, 
	"CHIUSA_DT" DATE, 
	"REGISTRY" VARCHAR2(20 CHAR)
   ) ;
--------------------------------------------------------
--  DDL for Table __installer__prefix___I18N
--------------------------------------------------------

  CREATE TABLE "__installer__prefix___I18N" 
   (	"LANG" VARCHAR2(4), 
	"LABEL" VARCHAR2(4000), 
	"TEXT" VARCHAR2(4000)
   ) ;
--------------------------------------------------------
--  DDL for Table __installer__prefix___REGISTRAZIONE
--------------------------------------------------------

  CREATE TABLE "__installer__prefix___REGISTRAZIONE" 
   (	"CODPAT" NUMBER, 
	"USERID_INS" VARCHAR2(40 CHAR), 
	"ESAM" NUMBER, 
	"PROGR" NUMBER, 
	"VISITNUM" NUMBER, 
	"VISITNUM_PROGR" NUMBER, 
	"CENTER" NUMBER
   ) ;
--------------------------------------------------------
--  DDL for Table __installer__prefix___ROLE
--------------------------------------------------------

  CREATE TABLE "__installer__prefix___ROLE" 
   (	"ID" NUMBER, 
	"ROLE" VARCHAR2(40 CHAR), 
	"WHERE_" VARCHAR2(4000 CHAR)
   ) ;
--------------------------------------------------------
--  DDL for View __installer__prefix___CENTRI
--------------------------------------------------------

  CREATE OR REPLACE VIEW "__installer__prefix___CENTRI" ("CENTER", "DENOM", "USERID") AS 
  select s.id as CENTER, s.descr as DENOM, '' as USERID from 
			SITES s, SITES_STUDIES ss
			where ss.STUDY_PREFIX='__installer__prefix__'
			and ss.ACTIVE=1
			and ss.SITE_ID=s.id
		;
--------------------------------------------------------
--  DDL for View __installer__prefix___USER_PROFILE
--------------------------------------------------------

  CREATE OR REPLACE VIEW "__installer__prefix___USER_PROFILE" ("PROFILE_CODE", "DESCRIZIONE", "POLICY", "SCOPE", "USERID") AS 
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
							  AND s.prefix='__installer__prefix__';
--------------------------------------------------------
--  DDL for View __installer__prefix___USER_PROFILES
--------------------------------------------------------

  CREATE OR REPLACE VIEW "__installer__prefix___USER_PROFILES" ("PROFILE_CODE", "DESCRIZIONE", "POLICY", "SCOPE", "USERID", "ACTIVE", "PROFILE_ID") AS 
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
							  AND s.prefix='__installer__prefix__';
--------------------------------------------------------
--  DDL for View __installer__prefix___UTENTI_CENTRI
--------------------------------------------------------

  CREATE OR REPLACE VIEW "__installer__prefix___UTENTI_CENTRI" ("USERID", "CENTER", "TIPOLOGIA") AS 
  select up.userid as USERID, uss.SITE_ID as CENTER, sp.POLICY as TIPOLOGIA
				from users_profiles up, studies_profiles sp, USERS_SITES_STUDIES uss
				where 
				up.profile_id=sp.id
				and up.active=1
				and sp.active=1
				and sp.scope>0
				and sp.STUDY_PREFIX='__installer__prefix__'
				and uss.ACTIVE=1 and uss.STUDY_PREFIX=sp.STUDY_PREFIX and uss.USER_PROFILE_ID=up.PROFILE_ID
				union all
				select up.userid as USERID,ss.SITE_ID as CENTER,sp.POLICY as TIPOLOGIA
				from users_profiles up, studies_profiles sp, SITES_STUDIES ss
				where 
				up.profile_id=sp.id
				and up.active=1
				and sp.active=1
				and sp.scope=0
				and sp.STUDY_PREFIX='__installer__prefix__'
				and ss.ACTIVE=1 and ss.STUDY_PREFIX=sp.STUDY_PREFIX
				
		;
