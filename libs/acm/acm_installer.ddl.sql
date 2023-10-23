
-- DEPRECATO
-- utilizzare: http://confluence-siss.cineca.it/confluence/display/SUS/Installazione+nuovo+servizio



CREATE TABLE CMM_LANGUAGE
(
  CENTER      VARCHAR2(255 CHAR)                 NOT NULL,
  LANGUAGE    VARCHAR2(12 CHAR)                 NOT NULL,
  D_LANGUAGE  VARCHAR2(200 CHAR)
)
LOGGING 
NOCOMPRESS 
NOCACHE
NOPARALLEL
MONITORING;


CREATE TABLE CMM_USERS
(
  CMM_USERID      VARCHAR2(255 CHAR),
  ROLE            NUMBER,
  D_ROLE          VARCHAR2(50 CHAR),
  CODE            VARCHAR2(20 CHAR),
  NAME            VARCHAR2(255 CHAR),
  SURNAME         VARCHAR2(255 CHAR),
  EMAIL           VARCHAR2(255 CHAR),
  PHONE           VARCHAR2(255 CHAR),
  FAX             VARCHAR2(255 CHAR),
  ADDRESS         VARCHAR2(255 CHAR),
  CREATEDT        DATE,
  FSTACCDT        DATE,
  LSTACCDT        DATE,
  EXPDT           DATE,
  ENDDT           DATE,
  STATUS          NUMBER,
  D_STATUS        VARCHAR2(20 CHAR),
  SIGN            NUMBER,
  D_SIGN          VARCHAR2(20 CHAR),
  SIGNSAE         NUMBER,
  D_SIGNSAE       VARCHAR2(20 CHAR),
  GENURS          VARCHAR2(255 CHAR),
  FIRST_PASSWORD  VARCHAR2(200 CHAR),
  MAIL_SENT       CHAR(1 CHAR)
)
LOGGING 
NOCOMPRESS 
NOCACHE
NOPARALLEL
MONITORING;


CREATE TABLE INBOX_MESSAGGI
(
  ID_MESSAGGIO  NUMBER                          NOT NULL,
  DATA_INVIO    DATE                            NOT NULL,
  USERID        VARCHAR2(255 CHAR)               NOT NULL,
  OGGETTO       VARCHAR2(255 CHAR)              NOT NULL,
  CORPO         CLOB                            NOT NULL,
  DESTINATARI   CLOB                            NOT NULL
)
LOB (CORPO) STORE AS (
  TABLESPACE  GENERICI_INDX
  ENABLE      STORAGE IN ROW
  CHUNK       8192
  RETENTION
  NOCACHE
  LOGGING
      STORAGE    (
                  INITIAL          64K
                  NEXT             1M
                  MINEXTENTS       1
                  MAXEXTENTS       UNLIMITED
                  PCTINCREASE      0
                  BUFFER_POOL      DEFAULT
                  FLASH_CACHE      DEFAULT
                  CELL_FLASH_CACHE DEFAULT
                 ))
LOB (DESTINATARI) STORE AS (
  TABLESPACE  GENERICI_INDX
  ENABLE      STORAGE IN ROW
  CHUNK       8192
  RETENTION
  NOCACHE
  LOGGING
      STORAGE    (
                  INITIAL          64K
                  NEXT             1M
                  MINEXTENTS       1
                  MAXEXTENTS       UNLIMITED
                  PCTINCREASE      0
                  BUFFER_POOL      DEFAULT
                  FLASH_CACHE      DEFAULT
                  CELL_FLASH_CACHE DEFAULT
                 ))
LOGGING 
NOCOMPRESS 
NOCACHE
NOPARALLEL
MONITORING;


CREATE TABLE ML_SERVICE
(
  ID         NUMBER,
  EN         VARCHAR2(4000 CHAR)                NOT NULL,
  IT         VARCHAR2(4000 CHAR),
  LAST_USED  DATE
)
LOGGING 
NOCOMPRESS 
NOCACHE
NOPARALLEL
MONITORING;


CREATE TABLE S_ANA_FUNZIONI
(
  ID_STORICO   NUMBER(12),
  MODDATE      DATE,
  MODUSER      VARCHAR2(255 CHAR),
  NOME         VARCHAR2(255 CHAR),
  DESCRIZIONE  VARCHAR2(255 CHAR),
  UPDATE_ID    NUMBER
)
LOGGING 
NOCOMPRESS 
NOCACHE
NOPARALLEL
MONITORING;


CREATE TABLE S_ANA_GRUPPIF
(
  ID_STORICO   NUMBER(12),
  MODDATE      DATE,
  MODUSER      VARCHAR2(255 CHAR),
  ID_GRUPPOF   NUMBER(10),
  NOME_GRUPPO  VARCHAR2(255 CHAR),
  DESCRIZIONE  VARCHAR2(255 CHAR),
  UPDATE_ID    NUMBER
)
LOGGING 
NOCOMPRESS 
NOCACHE
NOPARALLEL
MONITORING;


CREATE TABLE S_ANA_GRUPPIU
(
  ID_STORICO   NUMBER(12),
  MODDATE      DATE,
  MODUSER      VARCHAR2(255 CHAR),
  ID_GRUPPOU   NUMBER(10),
  NOME_GRUPPO  VARCHAR2(255 CHAR),
  DESCRIZIONE  VARCHAR2(255 CHAR),
  UPDATE_ID    NUMBER
)
LOGGING 
NOCOMPRESS 
NOCACHE
NOPARALLEL
MONITORING;


CREATE TABLE S_ANA_UTENTI_1
(
  ID_STORICO      NUMBER(12),
  MODDATE         DATE,
  MODUSER         VARCHAR2(255 CHAR),
  USERID          VARCHAR2(255 CHAR),
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
  EMAIL           VARCHAR2(255 CHAR),
  UPDATE_ID       NUMBER
)
LOGGING 
NOCOMPRESS 
NOCACHE
NOPARALLEL
MONITORING;


CREATE TABLE S_CMM_USERS
(
  USERID          VARCHAR2(255 CHAR),
  MODDT           DATE,
  MODPROG         NUMBER(6)                     NOT NULL,
  FL_QUERY        CHAR(1 CHAR)                  NOT NULL,
  ID_QUERY        NUMBER(6),
  CMM_USERID      VARCHAR2(255 CHAR),
  ROLE            NUMBER,
  D_ROLE          VARCHAR2(50 CHAR),
  CODE            VARCHAR2(20 CHAR),
  NAME            VARCHAR2(255 CHAR),
  SURNAME         VARCHAR2(255 CHAR),
  EMAIL           VARCHAR2(255 CHAR),
  PHONE           VARCHAR2(255 CHAR),
  FAX             VARCHAR2(255 CHAR),
  ADDRESS         VARCHAR2(255 CHAR),
  CREATEDT        DATE,
  FSTACCDT        DATE,
  LSTACCDT        DATE,
  EXPDT           DATE,
  ENDDT           DATE,
  STATUS          NUMBER,
  D_STATUS        VARCHAR2(20 CHAR),
  SIGN            NUMBER,
  D_SIGN          VARCHAR2(20 CHAR),
  SIGNSAE         NUMBER,
  D_SIGNSAE       VARCHAR2(20 CHAR),
  GENURS          VARCHAR2(255 CHAR),
  FIRST_PASSWORD  VARCHAR2(32 CHAR),
  MAIL_SENT       CHAR(1 CHAR)
)
LOGGING 
NOCOMPRESS 
NOCACHE
NOPARALLEL
MONITORING;


CREATE TABLE SESSIONS
(
  ID          NUMBER                            NOT NULL,
  USERID      VARCHAR2(255 CHAR),
  DATA        DATE,
  URL         VARCHAR2(2000 CHAR),
  REFERER     VARCHAR2(2000 CHAR),
  TIPO        VARCHAR2(20 CHAR),
  SESSION_ID  CHAR(32 CHAR)
)
LOGGING 
NOCOMPRESS 
NOCACHE
NOPARALLEL
MONITORING;


CREATE TABLE S_FUNZIONI
(
  ID_STORICO      NUMBER(12),
  MODDATE         DATE,
  MODUSER         VARCHAR2(255 CHAR),
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
MONITORING;


CREATE TABLE S_GRUPPIF
(
  ID_STORICO  NUMBER(12),
  MODDATE     DATE,
  MODUSER     VARCHAR2(255 CHAR),
  ID_GRUPPOF  NUMBER(10),
  ABILITATO   NUMBER(1),
  ID_VISTA    NUMBER(10),
  UPDATE_ID   NUMBER
)
LOGGING 
NOCOMPRESS 
NOCACHE
NOPARALLEL
MONITORING;


CREATE TABLE S_GRUPPIF_FUNZ
(
  ID_STORICO  NUMBER(12),
  MODDATE     DATE,
  MODUSER     VARCHAR2(255 CHAR),
  NOME_FUNZ   VARCHAR2(255 CHAR),
  ID_GRUPPOF  NUMBER(10),
  ABILITATO   NUMBER(1),
  UPDATE_ID   NUMBER
)
LOGGING 
NOCOMPRESS 
NOCACHE
NOPARALLEL
MONITORING;


CREATE TABLE S_GRUPPIU
(
  ID_STORICO  NUMBER(12),
  MODDATE     DATE,
  MODUSER     VARCHAR2(255 CHAR),
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
MONITORING;


CREATE TABLE S_GRUPPIU_FUNZ
(
  ID_STORICO      NUMBER(12),
  MODDATE         DATE,
  MODUSER         VARCHAR2(255 CHAR),
  NOME_FUNZ       VARCHAR2(255 CHAR),
  ID_GRUPPOU      NUMBER(10),
  TIPO_ECCEZIONE  NUMBER(1),
  UPDATE_ID       NUMBER
)
LOGGING 
NOCOMPRESS 
NOCACHE
NOPARALLEL
MONITORING;


CREATE TABLE S_GRUPPIU_GRUPPIF
(
  ID_STORICO  NUMBER(12),
  MODDATE     DATE,
  MODUSER     VARCHAR2(255 CHAR),
  ID_GRUPPOU  NUMBER(10),
  ID_GRUPPOF  NUMBER(10),
  ABILITATO   NUMBER(1),
  UPDATE_ID   NUMBER
)
LOGGING 
NOCOMPRESS 
NOCACHE
NOPARALLEL
MONITORING;


CREATE TABLE SHIBFORCEUSER
(
  USERID         VARCHAR2(255 CHAR),
  USERID_FORCED  VARCHAR2(255 CHAR),
  DT             DATE
)
LOGGING 
NOCOMPRESS 
NOCACHE
NOPARALLEL
MONITORING;


CREATE TABLE SITES
(
  ID         NUMBER,
  DESCR      VARCHAR2(255 CHAR),
  ACTIVE     NUMBER,
  CODE       VARCHAR2(10 CHAR),
  ADDRESS    VARCHAR2(200 CHAR),
  PI         VARCHAR2(255 CHAR),
  COUNTRY    NUMBER,
  D_COUNTRY  VARCHAR2(255 CHAR),
  PHONE      VARCHAR2(255 CHAR),
  FAX        VARCHAR2(255 CHAR),
  GENURS     VARCHAR2(255 CHAR)
)
LOGGING 
NOCOMPRESS 
NOCACHE
NOPARALLEL
MONITORING;


CREATE TABLE S_SITES
(
  ID_STORICO  NUMBER(12),
  MODDATE     DATE,
  MODUSER     VARCHAR2(255 CHAR),
  ID          NUMBER,
  DESCR       VARCHAR2(400 CHAR),
  ACTIVE      NUMBER,
  CODE        VARCHAR2(10 CHAR),
  ADDRESS     VARCHAR2(200 CHAR),
  PI          VARCHAR2(255 CHAR),
  COUNTRY     NUMBER,
  D_COUNTRY   VARCHAR2(255 CHAR),
  PHONE       VARCHAR2(255 CHAR),
  FAX         VARCHAR2(255 CHAR),
  GENURS      VARCHAR2(255 CHAR)
)
LOGGING 
NOCOMPRESS 
NOCACHE
NOPARALLEL
MONITORING;


CREATE TABLE S_SITES_STUDIES
(
  ID_STORICO    NUMBER(12),
  MODDATE       DATE,
  MODUSER       VARCHAR2(255 CHAR),
  SITE_ID       NUMBER,
  STUDY_PREFIX  VARCHAR2(10 CHAR),
  ACTIVE        NUMBER
)
LOGGING 
NOCOMPRESS 
NOCACHE
NOPARALLEL
MONITORING;


CREATE TABLE S_STUDIES
(
  ID_STORICO  NUMBER(12),
  MODDATE     DATE,
  MODUSER     VARCHAR2(255 CHAR),
  PREFIX      VARCHAR2(10 CHAR),
  DESCR       VARCHAR2(400 CHAR),
  ACTIVE      NUMBER,
  TYPE        VARCHAR2(20 CHAR),
  TITLE       VARCHAR2(200 CHAR)
)
LOGGING 
NOCOMPRESS 
NOCACHE
NOPARALLEL
MONITORING;


CREATE TABLE S_STUDIES_PROFILES
(
  ID_STORICO    NUMBER(12),
  MODDATE       DATE,
  MODUSER       VARCHAR2(255 CHAR),
  ID            NUMBER,
  CODE          VARCHAR2(40 CHAR),
  STUDY_PREFIX  VARCHAR2(10 CHAR),
  ACTIVE        NUMBER,
  POLICY        VARCHAR2(10 CHAR),
  SCOPE         VARCHAR2(20 CHAR)
)
LOGGING 
NOCOMPRESS 
NOCACHE
NOPARALLEL
MONITORING;


CREATE TABLE STUDIES
(
  PREFIX  VARCHAR2(10 CHAR),
  DESCR   VARCHAR2(400 CHAR),
  ACTIVE  NUMBER,
  TYPE    VARCHAR2(20 CHAR),
  TITLE   VARCHAR2(200 CHAR),
  NOTE    VARCHAR2(500 CHAR)
)
LOGGING 
NOCOMPRESS 
NOCACHE
NOPARALLEL
MONITORING;


CREATE TABLE STUDIES_PROFILES
(
  ID            NUMBER,
  CODE          VARCHAR2(40 CHAR),
  STUDY_PREFIX  VARCHAR2(10 CHAR),
  ACTIVE        NUMBER,
  POLICY        VARCHAR2(10 CHAR),
  SCOPE         VARCHAR2(20 CHAR)
)
LOGGING 
NOCOMPRESS 
NOCACHE
NOPARALLEL
MONITORING;


CREATE TABLE SUPERSHIBUSERS
(
  USERID  VARCHAR2(255 CHAR)
)
LOGGING 
NOCOMPRESS 
NOCACHE
NOPARALLEL
MONITORING;


CREATE TABLE S_USERS_PROFILES
(
  ID_STORICO  NUMBER(12),
  MODDATE     DATE,
  MODUSER     VARCHAR2(255 CHAR),
  USERID      VARCHAR2(255 CHAR),
  PROFILE_ID  NUMBER,
  ACTIVE      NUMBER
)
LOGGING 
NOCOMPRESS 
NOCACHE
NOPARALLEL
MONITORING;


CREATE TABLE S_USERS_SITES
(
  ID_STORICO  NUMBER(12),
  MODDATE     DATE,
  MODUSER     VARCHAR2(255 CHAR),
  USERID      VARCHAR2(255 CHAR),
  SITE_ID     NUMBER
)
LOGGING 
NOCOMPRESS 
NOCACHE
NOPARALLEL
MONITORING;


CREATE TABLE S_USERS_SITES_STUDIES
(
  ID_STORICO       NUMBER(12),
  MODDATE          DATE,
  MODUSER          VARCHAR2(255 CHAR),
  USERID           VARCHAR2(255 CHAR),
  SITE_ID          NUMBER,
  STUDY_PREFIX     VARCHAR2(10 CHAR),
  ACTIVE           NUMBER,
  USER_PROFILE_ID  NUMBER
)
LOGGING 
NOCOMPRESS 
NOCACHE
NOPARALLEL
MONITORING;


CREATE TABLE S_USERS_STUDIES
(
  ID_STORICO    NUMBER(12),
  MODDATE       DATE,
  MODUSER       VARCHAR2(255 CHAR),
  USERID        VARCHAR2(255 CHAR),
  STUDY_PREFIX  VARCHAR2(10 CHAR),
  ACTIVE        NUMBER
)
LOGGING 
NOCOMPRESS 
NOCACHE
NOPARALLEL
MONITORING;


CREATE TABLE S_UTENTI
(
  ID_STORICO          NUMBER(12),
  MODDATE             DATE,
  MODUSER             VARCHAR2(255 CHAR),
  USERID              VARCHAR2(255 CHAR),
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
  UPDATE_ID           NUMBER,
  INACTIVE            NUMBER(1),
  CREATED_ON          DATE
)
LOGGING 
NOCOMPRESS 
NOCACHE
NOPARALLEL
MONITORING;


CREATE TABLE S_UTENTI_FUNZ
(
  ID_STORICO      NUMBER(12),
  MODDATE         DATE,
  MODUSER         VARCHAR2(255 CHAR),
  USERID          VARCHAR2(255 CHAR),
  NOME_FUNZ       VARCHAR2(255 CHAR),
  TIPO_ECCEZIONE  NUMBER(1),
  UPDATE_ID       NUMBER
)
LOGGING 
NOCOMPRESS 
NOCACHE
NOPARALLEL
MONITORING;


CREATE TABLE S_UTENTI_GRUPPIU
(
  ID_STORICO  NUMBER(12),
  MODDATE     DATE,
  MODUSER     VARCHAR2(255 CHAR),
  USERID      VARCHAR2(255 CHAR),
  ID_GRUPPOU  NUMBER(10),
  ABILITATO   NUMBER(1),
  UPDATE_ID   NUMBER
)
LOGGING 
NOCOMPRESS 
NOCACHE
NOPARALLEL
MONITORING;


CREATE TABLE S_UTENTI_REDAZIONI
(
  ID_STORICO    NUMBER(12),
  MODDATE       DATE,
  MODUSER       VARCHAR2(255 CHAR),
  USERID        VARCHAR2(255 CHAR),
  ID_REDAZIONE  NUMBER(10),
  ABILITATO     NUMBER(1),
  UPDATE_ID     NUMBER
)
LOGGING 
NOCOMPRESS 
NOCACHE
NOPARALLEL
MONITORING;


CREATE TABLE S_UTENTI_VISTEAMMIN
(
  ID_STORICO  NUMBER(12),
  MODDATE     DATE,
  MODUSER     VARCHAR2(255 CHAR),
  USERID      VARCHAR2(255 CHAR),
  ID_VISTA    NUMBER(10),
  UPDATE_ID   NUMBER
)
LOGGING 
NOCOMPRESS 
NOCACHE
NOPARALLEL
MONITORING;


CREATE TABLE S_VISTEAMMIN
(
  ID_STORICO   NUMBER(12),
  MODDATE      DATE,
  MODUSER      VARCHAR2(255 CHAR),
  ID_VISTA     NUMBER(10),
  DESCRIZIONE  VARCHAR2(255 CHAR),
  UPDATE_ID    NUMBER
)
LOGGING 
NOCOMPRESS 
NOCACHE
NOPARALLEL
MONITORING;


CREATE TABLE USERS_PROFILES
(
  USERID      VARCHAR2(255 CHAR),
  PROFILE_ID  NUMBER,
  ACTIVE      NUMBER
)
LOGGING 
NOCOMPRESS 
NOCACHE
NOPARALLEL
MONITORING;


CREATE TABLE USERS_SITES
(
  USERID   VARCHAR2(255 CHAR),
  SITE_ID  NUMBER
)
LOGGING 
NOCOMPRESS 
NOCACHE
NOPARALLEL
MONITORING;


CREATE TABLE USERS_STUDIES
(
  USERID        VARCHAR2(255 CHAR),
  STUDY_PREFIX  VARCHAR2(10 CHAR),
  ACTIVE        NUMBER
)
LOGGING 
NOCOMPRESS 
NOCACHE
NOPARALLEL
MONITORING;


CREATE UNIQUE INDEX IDX_STD_PRF_CODEPREFIX ON STUDIES_PROFILES
(STUDY_PREFIX, CODE)
LOGGING
NOPARALLEL;




CREATE UNIQUE INDEX ML_SERVICE_EN_IDX ON ML_SERVICE
(EN)
LOGGING
NOPARALLEL;
























CREATE INDEX SESSION_ID_IDX ON SESSIONS
(ID)
LOGGING
NOPARALLEL;


CREATE INDEX SESSION_USERID_IDX ON SESSIONS
(USERID)
LOGGING
NOPARALLEL;




CREATE TABLE INBOX_CORRISPONDENZA
(
  ID_CORRISPONDENZA     NUMBER                  NOT NULL,
  ID_MESSAGGIO          NUMBER                  NOT NULL,
  USERID                VARCHAR2(255 CHAR)       NOT NULL,
  DATA_VISUALIZZAZIONE  DATE,
  DATA_ELIMINAZIONE     DATE
)
LOGGING 
NOCOMPRESS 
NOCACHE
NOPARALLEL
MONITORING;


CREATE TABLE SITES_STUDIES
(
  SITE_ID       NUMBER,
  STUDY_PREFIX  VARCHAR2(10 CHAR),
  ACTIVE        NUMBER
)
LOGGING 
NOCOMPRESS 
NOCACHE
NOPARALLEL
MONITORING;


CREATE TABLE USERS_SITES_STUDIES
(
  USERID           VARCHAR2(255 CHAR),
  SITE_ID          NUMBER,
  STUDY_PREFIX     VARCHAR2(10 CHAR),
  ACTIVE           NUMBER,
  USER_PROFILE_ID  NUMBER                       NOT NULL
)
LOGGING 
NOCOMPRESS 
NOCACHE
NOPARALLEL
MONITORING;





ALTER TABLE CMM_LANGUAGE ADD (
  CONSTRAINT PK_CMM_LANGUAGE
  PRIMARY KEY
  (CENTER, LANGUAGE)
  ENABLE VALIDATE);

ALTER TABLE CMM_USERS ADD (
  CONSTRAINT PK_CMM_USERS
  PRIMARY KEY
  (CMM_USERID)
  ENABLE VALIDATE);

ALTER TABLE INBOX_MESSAGGI ADD (
  CONSTRAINT INBOX_MESSAGGI_PK
  PRIMARY KEY
  (ID_MESSAGGIO)
  ENABLE VALIDATE);

ALTER TABLE ML_SERVICE ADD (
  CONSTRAINT ML_SERVICE_PK
  PRIMARY KEY
  (ID)
  ENABLE VALIDATE);

ALTER TABLE S_CMM_USERS ADD (
  CONSTRAINT S_PK_CMM_USERS
  PRIMARY KEY
  (MODPROG)
  ENABLE VALIDATE);

ALTER TABLE SHIBFORCEUSER ADD (
  CONSTRAINT PK_SHIBFORCEUSER
  PRIMARY KEY
  (USERID)
  ENABLE VALIDATE);

ALTER TABLE SITES ADD (
  CONSTRAINT PK_SITES
  PRIMARY KEY
  (ID)
  ENABLE VALIDATE);

ALTER TABLE STUDIES ADD (
  CONSTRAINT PK_STUDIES
  PRIMARY KEY
  (PREFIX)
  ENABLE VALIDATE);

ALTER TABLE STUDIES_PROFILES ADD (
  CONSTRAINT PK_STUDIES_PROFILES
  PRIMARY KEY
  (ID)
  ENABLE VALIDATE);

ALTER TABLE SUPERSHIBUSERS ADD (
  CONSTRAINT PK_SUPERSHIBUSERS
  PRIMARY KEY
  (USERID)
  ENABLE VALIDATE);

ALTER TABLE USERS_PROFILES ADD (
  CONSTRAINT PK_USERS_PROFILES
  PRIMARY KEY
  (PROFILE_ID, USERID)
  ENABLE VALIDATE);

ALTER TABLE USERS_SITES ADD (
  CONSTRAINT PK_USERS_SITES
  PRIMARY KEY
  (SITE_ID, USERID)
  ENABLE VALIDATE);

ALTER TABLE USERS_STUDIES ADD (
  CONSTRAINT PK_USERS_STUDIES
  PRIMARY KEY
  (STUDY_PREFIX, USERID)
  ENABLE VALIDATE);

ALTER TABLE INBOX_CORRISPONDENZA ADD (
  CONSTRAINT INBOX_CORRISPONDENZA_PK
  PRIMARY KEY
  (ID_CORRISPONDENZA)
  ENABLE VALIDATE);

ALTER TABLE SITES_STUDIES ADD (
  CONSTRAINT PK_SITES_STUDIES
  PRIMARY KEY
  (SITE_ID, STUDY_PREFIX)
  ENABLE VALIDATE);

ALTER TABLE USERS_SITES_STUDIES ADD (
  CONSTRAINT PK_USERS_SITES_STUDIES
  PRIMARY KEY
  (SITE_ID, USERID, STUDY_PREFIX, USER_PROFILE_ID)
  ENABLE VALIDATE);

ALTER TABLE STUDIES_PROFILES ADD (
  CONSTRAINT FK1_STUDIES_PROFILES 
  FOREIGN KEY (STUDY_PREFIX) 
  REFERENCES STUDIES (PREFIX)
  ENABLE VALIDATE);

ALTER TABLE USERS_PROFILES ADD (
  CONSTRAINT FK1_USERS_PROFILES 
  FOREIGN KEY (PROFILE_ID) 
  REFERENCES STUDIES_PROFILES (ID)
  ENABLE VALIDATE,
  CONSTRAINT FK2_USERS_PROFILES 
  FOREIGN KEY (USERID) 
  REFERENCES UTENTI (USERID)
  ENABLE VALIDATE);

ALTER TABLE USERS_SITES ADD (
  CONSTRAINT FK1_USERS_SITES 
  FOREIGN KEY (SITE_ID) 
  REFERENCES SITES (ID)
  ENABLE VALIDATE,
  CONSTRAINT FK2_USERS_SITES 
  FOREIGN KEY (USERID) 
  REFERENCES UTENTI (USERID)
  ENABLE VALIDATE);

ALTER TABLE USERS_STUDIES ADD (
  CONSTRAINT FK1_USERS_STUDIES 
  FOREIGN KEY (STUDY_PREFIX) 
  REFERENCES STUDIES (PREFIX)
  ENABLE VALIDATE,
  CONSTRAINT FK2_USERS_STUDIES 
  FOREIGN KEY (USERID) 
  REFERENCES UTENTI (USERID)
  ENABLE VALIDATE);

ALTER TABLE INBOX_CORRISPONDENZA ADD (
  CONSTRAINT INBOX_CORRISPONDENZA_FK1 
  FOREIGN KEY (ID_MESSAGGIO) 
  REFERENCES INBOX_MESSAGGI (ID_MESSAGGIO)
  ENABLE VALIDATE);

ALTER TABLE SITES_STUDIES ADD (
  CONSTRAINT FK1_SITES_STUDIES 
  FOREIGN KEY (SITE_ID) 
  REFERENCES SITES (ID)
  ENABLE VALIDATE,
  CONSTRAINT FK2_SITES_STUDIES 
  FOREIGN KEY (STUDY_PREFIX) 
  REFERENCES STUDIES (PREFIX)
  ENABLE VALIDATE);

ALTER TABLE USERS_SITES_STUDIES ADD (
  CONSTRAINT FK1_USERS_SITES_STUDIES 
  FOREIGN KEY (SITE_ID) 
  REFERENCES SITES (ID)
  ENABLE VALIDATE,
  CONSTRAINT FK2_USERS_SITES_STUDIES 
  FOREIGN KEY (USERID) 
  REFERENCES UTENTI (USERID)
  ENABLE VALIDATE,
  CONSTRAINT FK3_USERS_SITES_STUDIES 
  FOREIGN KEY (STUDY_PREFIX) 
  REFERENCES STUDIES (PREFIX)
  ENABLE VALIDATE,
  CONSTRAINT FK4_USERS_SITES_STUDIES 
  FOREIGN KEY (STUDY_PREFIX, USERID) 
  REFERENCES USERS_STUDIES (STUDY_PREFIX,USERID)
  ENABLE VALIDATE,
  CONSTRAINT FK5_USERS_SITES_STUDIES 
  FOREIGN KEY (SITE_ID, STUDY_PREFIX) 
  REFERENCES SITES_STUDIES (SITE_ID,STUDY_PREFIX)
  ENABLE VALIDATE,
  CONSTRAINT FK6_USERS_SITES_STUDIES 
  FOREIGN KEY (SITE_ID, USERID) 
  REFERENCES USERS_SITES (SITE_ID,USERID)
  ENABLE VALIDATE,
  CONSTRAINT FK7_USERS_SITES_STUDIES 
  FOREIGN KEY (USER_PROFILE_ID, USERID) 
  REFERENCES USERS_PROFILES (PROFILE_ID,USERID)
  ON DELETE CASCADE
  ENABLE VALIDATE);

CREATE TABLE ACM_I18N
(
  LANG   VARCHAR2(4 CHAR),
  LABEL  VARCHAR2(4000 CHAR),
  TEXT   VARCHAR2(4000 CHAR)
)
LOGGING
NOCOMPRESS
NOCACHE
NOPARALLEL
MONITORING;

CREATE TABLE ACM_STUDY_I18N
  (
    LANG  VARCHAR2(4 CHAR),
    LABEL VARCHAR2(4000 CHAR),
    TEXT  VARCHAR2(4000 CHAR)
  );

CREATE TABLE ACM_LOG
  (
    ID     NUMBER NOT NULL,
    USERID VARCHAR2(255 CHAR) NOT NULL,
    TIMESTAMP DATE NOT NULL ENABLE,
    ACTION      VARCHAR2(1000 CHAR) NOT NULL,
    DESCRIPTION VARCHAR2(4000 CHAR)
  )
  LOGGING
  NOCOMPRESS
  NOCACHE
  NOPARALLEL
  MONITORING;
  
ALTER TABLE ACM_LOG ADD ( 
	  CONSTRAINT ACM_LOG_PK PRIMARY KEY (ID) 
	  ENABLE VALIDATE);

CREATE TABLE ACM_S_X_DATA
(
  ID         INTEGER,
  TABNAME    VARCHAR2(1000 CHAR)                NOT NULL,
  FIELD      VARCHAR2(1000 CHAR)                NOT NULL,
  TSTAMP     DATE                               NOT NULL,
  USERID     VARCHAR2(255 CHAR)                 NOT NULL,
  ACTION     VARCHAR2(1000 CHAR)                NOT NULL,
  VALUE_OLD  VARCHAR2(4000 CHAR),
  VALUE_NEW  VARCHAR2(4000 CHAR),
  PKEY       VARCHAR2(4000 CHAR)                NOT NULL
)
LOGGING
NOCOMPRESS
NOCACHE
NOPARALLEL
MONITORING;


CREATE TABLE ACM_USERS_PROFILES
(
  USERID      VARCHAR2(255 CHAR),
  PROFILE_ID  NUMBER,
  ACTIVE      NUMBER
)
LOGGING
NOCOMPRESS
NOCACHE
NOPARALLEL
MONITORING;



ALTER TABLE ACM_I18N ADD (
  CONSTRAINT PK_ACM_I18N
  PRIMARY KEY
  (LANG, LABEL)
  ENABLE VALIDATE);

ALTER TABLE ACM_STUDY_I18N ADD (
  CONSTRAINT PK_ACM_STUDY_I18N
  PRIMARY KEY
  (LANG, LABEL)
  ENABLE VALIDATE);
  
ALTER TABLE ACM_S_X_DATA ADD (
  CONSTRAINT ACM_S_X_DATA_PK
  PRIMARY KEY
  (ID)
  ENABLE VALIDATE);

ALTER TABLE ACM_USERS_PROFILES ADD (
  CONSTRAINT PK_ACM_USERS_PROFILES
  PRIMARY KEY
  (PROFILE_ID, USERID)
  ENABLE VALIDATE);

ALTER TABLE ACM_USERS_PROFILES ADD (
  CONSTRAINT FK1_ACM_USERS_PROFILES
  FOREIGN KEY (USERID)
  REFERENCES UTENTI (USERID)
  ENABLE VALIDATE);

Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','FASTSEARCH.Patient Code (Pofile_CO_PI.profileName)','Patient Code');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','FASTSEARCH.Patient Code (Pofile_CO_PI.profileName)','Patient Code');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','FASTSEARCH.Patient Code (Pofile_CRA.profileName)','Patient Code');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','FASTSEARCH.Patient Code (Pofile_CRA.profileName)','Patient Code');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','FASTSEARCH.Patient Code (Pofile_DE.profileName)','Patient Code');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','FASTSEARCH.Patient Code (Pofile_DE.profileName)','Patient Code');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','FASTSEARCH.Patient Code (Pofile_DM.profileName)','Patient Code');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','FASTSEARCH.Patient Code (Pofile_DM.profileName)','Patient Code');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','FASTSEARCH.Patient Code (Pofile_PM.profileName)','Patient Code');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','FASTSEARCH.Patient Code (Pofile_PM.profileName)','Patient Code');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','FASTSEARCH.Patient Code (Pofile_RO.profileName)','Patient Code');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','FASTSEARCH.Patient Code (Pofile_RO.profileName)','Patient Code');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','FASTSEARCH.Patient Code (Pofile_SP.profileName)','Patient Code');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','FASTSEARCH.Patient Code (Pofile_SP.profileName)','Patient Code');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','FASTSEARCH.Patient Code (Pofile_ST.profileName)','Patient Code');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','FASTSEARCH.Patient Code (Pofile_ST.profileName)','Patient Code');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','FASTSEARCH.SiteID (Pofile_CO_PI.profileName)','SiteID');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','FASTSEARCH.SiteID (Pofile_CO_PI.profileName)','SiteID');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','FASTSEARCH.SiteID (Pofile_CRA.profileName)','SiteID');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','FASTSEARCH.SiteID (Pofile_CRA.profileName)','SiteID');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','FASTSEARCH.SiteID (Pofile_DE.profileName)','SiteID');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','FASTSEARCH.SiteID (Pofile_DE.profileName)','SiteID');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','FASTSEARCH.SiteID (Pofile_DM.profileName)','SiteID');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','FASTSEARCH.SiteID (Pofile_DM.profileName)','SiteID');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','FASTSEARCH.SiteID (Pofile_PM.profileName)','SiteID');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','FASTSEARCH.SiteID (Pofile_PM.profileName)','SiteID');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','FASTSEARCH.SiteID (Pofile_RO.profileName)','SiteID');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','FASTSEARCH.SiteID (Pofile_RO.profileName)','SiteID');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','FASTSEARCH.SiteID (Pofile_SP.profileName)','SiteID');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','FASTSEARCH.SiteID (Pofile_SP.profileName)','SiteID');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','FASTSEARCH.SiteID (Pofile_ST.profileName)','SiteID');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','FASTSEARCH.SiteID (Pofile_ST.profileName)','SiteID');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','FASTSEARCH.SubjID (Pofile_CO_PI.profileName)','SubjID');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','FASTSEARCH.SubjID (Pofile_CO_PI.profileName)','SubjID');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','FASTSEARCH.SubjID (Pofile_CRA.profileName)','SubjID');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','FASTSEARCH.SubjID (Pofile_CRA.profileName)','SubjID');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','FASTSEARCH.SubjID (Pofile_DE.profileName)','SubjID');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','FASTSEARCH.SubjID (Pofile_DE.profileName)','SubjID');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','FASTSEARCH.SubjID (Pofile_DM.profileName)','SubjID');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','FASTSEARCH.SubjID (Pofile_DM.profileName)','SubjID');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','FASTSEARCH.SubjID (Pofile_PM.profileName)','SubjID');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','FASTSEARCH.SubjID (Pofile_PM.profileName)','SubjID');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','FASTSEARCH.SubjID (Pofile_RO.profileName)','SubjID');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','FASTSEARCH.SubjID (Pofile_RO.profileName)','SubjID');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','FASTSEARCH.SubjID (Pofile_SP.profileName)','SubjID');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','FASTSEARCH.SubjID (Pofile_SP.profileName)','SubjID');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','FASTSEARCH.SubjID (Pofile_ST.profileName)','SubjID');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','FASTSEARCH.SubjID (Pofile_ST.profileName)','SubjID');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','Legend.Da_compilare','Schede da compilare. Cliccare sulla freccia bianca per iniziare l''inserimento.');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','Legend.Da_compilare','Empty forms.');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','Legend.Da_completare','Some forms to be completed.');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','Legend.Da_completare','Alcune schede devono ancora essere inserite. Cliccare sulla freccia gialla per proseguire l''inserimento.');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','Legend.Form_da_compilare','Form da compilare. Cliccare il riquadro per compilare la form.');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','Legend.Form_da_compilare','Click on the plus icon to fill in data');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','Legend.Form_inviata','Form inviata. Cliccare sul check verde per visualizzare i dati inseriti. Non  possibile la modifica dei dati per questo profilo.');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','Legend.Form_inviata','Click on green tick to read the inserted data. You cannot modify them.');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','Legend.Form_non_inserita','This form has not been compiled');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','Legend.Form_non_inserita','Legend.Form_non_inserita');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','Legend.Form_salvata','Click on red tick to modify data');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','Legend.Form_salvata','Form salvata. Cliccare sul check rosso per visualizzare/modificare i dati inseriti.');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','Legend.Morte','Fine Studio.');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','Legend.Morte','Dead patient.');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','Legend.Titolo','Legenda');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','Legend.Titolo','Legend');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','Legend.Tutte_complete','Tutte le schede sono state compilate. Cliccare sulla freccia verde per visualizzare i dati inseriti.');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','Legend.Tutte_complete','Forms completed.');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','List.equery_list_answered_DE.Column.','not selected');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','List.equery_list_answered_DE.Column.','non selezionata');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','List.equery_list_answered_DE.Column.Center','Center');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','List.equery_list_answered_DE.Column.Center','Centro');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','List.equery_list_answered_DE.Column.Date','Date');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','List.equery_list_answered_DE.Column.Date','Data');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','List.equery_list_answered_DE.Column.DM/CRA''s question','DM/CRA''s question');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','List.equery_list_answered_DE.Column.DM/CRA''s question','Domanda del DM/CRA');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','List.equery_list_answered_DE.Column.eQuery ID','eQuery ID');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','List.equery_list_answered_DE.Column.eQuery ID','eQuery ID');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','List.equery_list_answered_DE.Column.Form name','Form name');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','List.equery_list_answered_DE.Column.Form name','Nome form');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','List.equery_list_answered_DE.Column.Investigator''s question/answer','Investigator''s question/answer');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','List.equery_list_answered_DE.Column.Investigator''s question/answer','Risposta dell''investigatore');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','List.equery_list_answered_DE.Column.Link eQ','Link eQ');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','List.equery_list_answered_DE.Column.Link eQ','Link eQ');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','List.equery_list_answered_DE.Column.Patient ID','Patient ID');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','List.equery_list_answered_DE.Column.Patient ID','Patient ID');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','List.equery_list_answered_DM.Column.','Column');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','List.equery_list_answered_DM.Column.','Colonna');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','List.equery_list_answered_DM.Column.Center','Center');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','List.equery_list_answered_DM.Column.Center','Centro');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','List.equery_list_answered_DM.Column.Date','Data');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','List.equery_list_answered_DM.Column.Date','Date');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','List.equery_list_answered_DM.Column.DM/CRA''s question','Domanda del DM/CRA');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','List.equery_list_answered_DM.Column.DM/CRA''s question','DM/CRA''s question');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','List.equery_list_answered_DM.Column.eQuery ID','eQuery ID');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','List.equery_list_answered_DM.Column.eQuery ID','eQuery ID');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','List.equery_list_answered_DM.Column.Form name','Form name');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','List.equery_list_answered_DM.Column.Form name','Nome form');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','List.equery_list_answered_DM.Column.Investigator''s question/answer','Risposta dell''investigatore');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','List.equery_list_answered_DM.Column.Investigator''s question/answer','Investigator''s question/answer');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','List.equery_list_answered_DM.Column.Link eQ','Link eQ');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','List.equery_list_answered_DM.Column.Link eQ','Link eQ');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','List.equery_list_answered_DM.Column.Patient ID','Patient ID');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','List.equery_list_answered_DM.Column.Patient ID','Patient ID');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','List.equery_list_center.Column.','not selected');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','List.equery_list_center.Column.','non selezionata');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','List.equery_list_center.Column.Center ID','Center ID');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','List.equery_list_center.Column.Center ID','Center ID');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','List.equery_list_center.Column.Center Name','Nome Centro');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','List.equery_list_center.Column.Center Name','Center Name');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','List.equery_list_center.Column.eQ Answered','eQ Risposte');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','List.equery_list_center.Column.eQ Answered','eQ Answered');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','List.equery_list_center.Column.eQ Closed','eQ Closed');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','List.equery_list_center.Column.eQ Closed','eQ Chiuse');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','List.equery_list_center.Column.eQ Opened','eQ Opened');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','List.equery_list_center.Column.eQ Opened','eQ Aperte');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','List.equery_list_center.Column.num. eQ Answered','eQ Answered');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','List.equery_list_center.Column.num. eQ Answered','eQ Risposte');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','List.equery_list_center.Column.num. eQ Closed','eQ Closed');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','List.equery_list_center.Column.num. eQ Closed','eQ Chiuse');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','List.equery_list_center.Column.num. eQ Opened','eQ Aperte');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','List.equery_list_center.Column.num. eQ Opened','eQ Opened');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','List.equery_list_closed_DE.Column.','non selezionata');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','List.equery_list_closed_DE.Column.','not selected');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','List.equery_list_closed_DE.Column.Center','Centro');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','List.equery_list_closed_DE.Column.Center','Center');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','List.equery_list_closed_DE.Column.Date','Data');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','List.equery_list_closed_DE.Column.Date','Date');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','List.equery_list_closed_DE.Column.DM/CRA''s question','Domanda del DM/CRA');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','List.equery_list_closed_DE.Column.DM/CRA''s question','DM/CRA''s question');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','List.equery_list_closed_DE.Column.eQuery ID','eQuery ID');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','List.equery_list_closed_DE.Column.eQuery ID','eQuery ID');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','List.equery_list_closed_DE.Column.Form name','Nome form');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','List.equery_list_closed_DE.Column.Form name','Form name');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','List.equery_list_closed_DE.Column.Invetigator''s question/answer','Risposta dell''investigatore');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','List.equery_list_closed_DE.Column.Invetigator''s question/answer','Invetigator''s question/answer');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','List.equery_list_closed_DE.Column.Link eQ','Link eQ');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','List.equery_list_closed_DE.Column.Link eQ','Link eQ');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','List.equery_list_closed_DE.Column.Patient ID','Patient ID');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','List.equery_list_closed_DE.Column.Patient ID','Patient ID');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','List.equery_list_closed_DM.Column.','not selected');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','List.equery_list_closed_DM.Column.','non selezionata');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','List.equery_list_closed_DM.Column.Center','Center');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','List.equery_list_closed_DM.Column.Center','Centro');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','List.equery_list_closed_DM.Column.Date','Date');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','List.equery_list_closed_DM.Column.Date','Data');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','List.equery_list_closed_DM.Column.DM/CRA''s question','Domanda del DM/CRA');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','List.equery_list_closed_DM.Column.DM/CRA''s question','DM/CRA''s question');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','List.equery_list_closed_DM.Column.eQuery ID','eQuery ID');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','List.equery_list_closed_DM.Column.eQuery ID','eQuery ID');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','List.equery_list_closed_DM.Column.Form name','Form name');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','List.equery_list_closed_DM.Column.Form name','Nome form');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','List.equery_list_closed_DM.Column.Invetigator''s question/answer','Risposta dell''investigatore');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','List.equery_list_closed_DM.Column.Invetigator''s question/answer','Invetigator''s question/answer');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','List.equery_list_closed_DM.Column.Link eQ','Link eQ');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','List.equery_list_closed_DM.Column.Link eQ','Link eQ');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','List.equery_list_closed_DM.Column.Patient ID','Patient ID');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','List.equery_list_closed_DM.Column.Patient ID','Patient ID');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','List.equery_list_opened_DE.Column.','not selected');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','List.equery_list_opened_DE.Column.','non selezionata');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','List.equery_list_opened_DE.Column.Center','Center');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','List.equery_list_opened_DE.Column.Center','Centro');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','List.equery_list_opened_DE.Column.Date','Data');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','List.equery_list_opened_DE.Column.Date','Date');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','List.equery_list_opened_DE.Column.DM/CRA''s question','DM/CRA''s question');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','List.equery_list_opened_DE.Column.DM/CRA''s question','Domanda del DM/CRA');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','List.equery_list_opened_DE.Column.eQuery ID','eQuery ID');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','List.equery_list_opened_DE.Column.eQuery ID','eQuery ID');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','List.equery_list_opened_DE.Column.Form name','Form name');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','List.equery_list_opened_DE.Column.Form name','Nome form');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','List.equery_list_opened_DE.Column.Link eQ','Link eQ');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','List.equery_list_opened_DE.Column.Link eQ','Link eQ');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','List.equery_list_opened_DE.Column.Patient ID','Patient ID');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','List.equery_list_opened_DE.Column.Patient ID','Patient ID');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','List.equery_list_opened_DM.Column.','not selected');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','List.equery_list_opened_DM.Column.','non selezionata');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','List.equery_list_opened_DM.Column.Center','Centro');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','List.equery_list_opened_DM.Column.Center','Center');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','List.equery_list_opened_DM.Column.Date','Date');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','List.equery_list_opened_DM.Column.Date','Data');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','List.equery_list_opened_DM.Column.DM/CRA''s question','DM/CRA''s question');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','List.equery_list_opened_DM.Column.DM/CRA''s question','Domanda del DM/CRA');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','List.equery_list_opened_DM.Column.eQuery ID','eQuery ID');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','List.equery_list_opened_DM.Column.eQuery ID','eQuery ID');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','List.equery_list_opened_DM.Column.Form name','Nome form');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','List.equery_list_opened_DM.Column.Form name','Form name');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','List.equery_list_opened_DM.Column.Link eQ','Link eQ');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','List.equery_list_opened_DM.Column.Link eQ','Link eQ');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','List.equery_list_opened_DM.Column.Patient ID','Patient ID');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','List.equery_list_opened_DM.Column.Patient ID','Patient ID');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','List.Lista Pazienti','Registry Patients List');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','List.nRowsPage','Records in this page');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','List.nRowsPage','Righe per pagina');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','List.Orderby','Ordina per');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','List.Orderby','Ordered by');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','List.OrderDirection.ASC','ASC');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','List.OrderDirection.ASC','ASC');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','List.OrderDirection.asc','ASC');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','List.OrderDirection.asc','ASC');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','List.OrderDirection.DESC','DESC');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','List.OrderDirection.DESC','DESC');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','List.patients_list_center.Column.','View patients');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','List.patients_list_center.Column.','Vedi pazienti');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','List.patients_list_center.Column.Center ID','Center ID');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','List.patients_list_center.Column.Center ID','ID Centro');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','List.patients_list_center.Column.Center Name','Center Name');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','List.patients_list_center.Column.Center Name','Nome Centro');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','List.patients_list_center.Column.N. of Patients','Numero di pazienti');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','List.patients_list_center.Column.N. of Patients','N. of Patients');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','List.patients_list.Column.','View');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','List.patients_list.Column.','View');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','List.patients_list.Column.Center Code','Center Code');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','List.patients_list.Column.Center Code','Codice Centro');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','List.patients_list.Column.Patient Code','Codice Paziente');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','List.patients_list.Column.Patient Code','Patient Code');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','List.patients_list.Column.Patient view','Patient view');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','List.patients_list.Column.Patient view','Vista Paziente');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','List.patients_list.Column.Report','Report');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','List.patients_list.Column.Report','Report');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','List.patients_list.Column.Report PDF','Report PDF');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','List.patients_list.Column.Report PDF','Report PDF');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','List.patients_list_CRA.Column.','not selected');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','List.patients_list_CRA.Column.','non selezionata');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','List.patients_list_CRA.Column.Center','Center');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','List.patients_list_CRA.Column.Center','Centro');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','List.patients_list_CRA.Column.Pat. Visit','Vista Paziente');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','List.patients_list_CRA.Column.Pat. Visit','Patient view');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','List.patients_list_CRA.Column.Patient Id','Patient ID');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','List.patients_list_CRA.Column.Patient Id','Patient Id');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','List.patients_list_CRA.Column.Patient No.','Patient No.');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','List.patients_list_CRA.Column.Patient No.','Nr. Paziente');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','List.patients_list_CRA.Column.Patient Num.','Numero Paziente');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','List.patients_list_CRA.Column.Patient Num.','Patient Num.');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','List.patients_list_CRA.Column.Report','Report');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','List.patients_list_CRA.Column.Report','Report');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','List.patients_list_Data_Entry.Column.','non selezionata');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','List.patients_list_Data_Entry.Column.','not selected');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','List.patients_list_Data_Entry.Column.Pat. Visit','Patient Visit');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','List.patients_list_Data_Entry.Column.Pat. Visit','Visita Paziente');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','List.patients_list_Data_Entry.Column.Patient Num.','Patient Num.');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','List.patients_list_Data_Entry.Column.Patient Num.','Numero Paziente');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','List.patients_list_Data_Entry.Column.Report','Report');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','List.patients_list_Data_Entry.Column.Report','Report');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','List.Title.Lista Pazienti','Registro Lista Pazienti');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','List.Title.Lista Pazienti','Registry Patients List');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','List.Title.Sites List','Sites List');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','List.Totals','Total records found');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','List.Totals','Numero totale record trovati');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','MSG.NewMessage','Nuovo messaggio');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','MSG.NewMessage','New message');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','PATIENT_LIST.Patient registration visit','Visita di Registrazione');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','PATIENT_LIST.Patient registration visit','Patient registration visit');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','PATIENT_LIST.V1','PATIENT_LIST.V1');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','PATIENT_LIST.V1','V1');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','Profile_CO_PI.Actions','Azioni');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','Profile_CO_PI.Actions','Actions');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','Profile_CO_PI.Activity list by Site','Activity list by Site');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','Profile_CO_PI.Answered eQueries','Answered eQueries');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','Profile_CO_PI.Answered eQueries','eQuery Risposte');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','Profile_CO_PI.Azioni','Azioni');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','Profile_CO_PI.Baseline characteristics','Baseline characteristics');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','Profile_CO_PI.Baseline characteristics','Baseline characteristics');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','Profile_CO_PI.Closed eQueries','eQuery Chiuse');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','Profile_CO_PI.Closed eQueries','Closed eQueries');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','Profile_CO_PI.Data Entry','Data Entry');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','Profile_CO_PI.Data Entry','Data Entry');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','Profile_CO_PI.Data Quality','Data Quality');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','Profile_CO_PI.Data Quality','Data Quality');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','Profile_CO_PI.Drug prescriptions and administrations','Drug prescriptions and administrations');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','Profile_CO_PI.Drug prescriptions and administrations','Drug prescriptions and administrations');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','Profile_CO_PI.eCRFs','eCRFs');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','Profile_CO_PI.End of treatment','End of treatment');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','Profile_CO_PI.End of treatment','Fine Trattamento');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','Profile_CO_PI.Help','Help');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','Profile_CO_PI.Help','Help');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','Profile_CO_PI.Highlights','Highlights');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','Profile_CO_PI.Highlights','Highlights');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','Profile_CO_PI.Home Page','Home Page');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','Profile_CO_PI.Home Page','Home Page');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','Profile_CO_PI.Opened eQueries','eQuery Aperte');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','Profile_CO_PI.Outstanding eQueries','Outstanding eQueries');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','Profile_CO_PI.Outstanding eQueries','eQuery Pendenti');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','Profile_CO_PI.Predefined Reports','Report Predefiniti');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','Profile_CO_PI.Predefined Reports','Predefined Reports');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','Profile_CO_PI.profileName','Co-principal Investigator');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','Profile_CO_PI.profileName','Co-Principal Investigator');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','Profile_CO_PI.Register new patient','Register new patient');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','Profile_CO_PI.Register new patient','Registra nuovo Paziente');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','Profile_CO_PI.Registered patients','Pazienti registrati');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','Profile_CO_PI.Registered patients','Registered patients');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','Profile_CO_PI.Regulations','Regulations');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','Profile_CO_PI.SDV Signature Report','SDV Signature Report');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','Profile_CO_PI.SDV Signature Report','SDV Signature Report');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','Profile_CO_PI.SDV Status Report','SDV Status Report');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','Profile_CO_PI.SDV Status Report','SDV Status Report');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','Profile_CO_PI.SDV Strategy Report','SDV Strategy Report');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','Profile_CO_PI.SDV Strategy Report','SDV Strategy Report');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','Profile_CO_PI.SDV Violation Report','SDV Violation Report');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','Profile_CO_PI.SDV Violation Report','SDV Violation Report');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','Profile_CO_PI.Site''s list','Site''s list');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','Profile_CO_PI.Site''s list','Lista Centri');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','Profile_CO_PI.Source Data Verification','Source Data Verification');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','Profile_CO_PI.Source Data Verification','Source Data Verification');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','Profile_CRA.Actions','Actions');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','Profile_CRA.Actions','Azioni');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','Profile_CRA.Activity list by Site','Activity list by Site');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','Profile_CRA.Activity list by Site','Activity list by Site');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','Profile_CRA.Aiuto','Aiuto');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','Profile_CRA.Answered eQueries','Answered eQueries');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','Profile_CRA.Answered eQueries','eQuery Risposte');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','Profile_CRA.Azioni','Azioni');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','Profile_CRA.Baseline characteristics','Profile_CRA.Baseline characteristics');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','Profile_CRA.Baseline characteristics','Baseline characteristics');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','Profile_CRA.Browse Data','Naviga dati');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','Profile_CRA.Browse Data','Browse Data');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','Profile_CRA.Closed eQueries','eQuery Chiuse');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','Profile_CRA.Closed eQueries','Closed eQueries');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','Profile_CRA.Data Quality','Data Quality');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','Profile_CRA.Data Quality','Data Quality');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','Profile_CRA.Drug prescriptions and administrations','Drug prescriptions and administrations');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','Profile_CRA.Drug prescriptions and administrations','Profile_CRA.Drug prescriptions and administrations');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','Profile_CRA.eCRFs','eCRFs');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','Profile_CRA.eCRFs','eCRFs');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','Profile_CRA.End of treatment','Fine Trattamento');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','Profile_CRA.End of treatment','End of treatment');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','Profile_CRA.Help','Help');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','Profile_CRA.Help','Aiuto');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','Profile_CRA.Highlights','Highlights');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','Profile_CRA.Highlights','Highlights');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','Profile_CRA.Home Page','Home Page');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','Profile_CRA.Home Page','Home Page');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','Profile_CRA.Opened eQueries','Opened eQueries');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','Profile_CRA.Opened eQueries','eQuery Aperte');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','Profile_CRA.Outstanding eQueries','Outstanding eQueries');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','Profile_CRA.Outstanding eQueries','eQuery Pendenti');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','Profile_CRA.Predefined Reports','Report predefiniti');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','Profile_CRA.Predefined Reports','Predefined Reports');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','Profile_CRA.Profile_CRA.Regulations','Regulations');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','Profile_CRA.profileName','CRA');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','Profile_CRA.profileName','CRA');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','Profile_CRA.Registered patients','Registered patients');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','Profile_CRA.Registered patients','Pazienti Registrati');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','Profile_CRA.Regulations','Regulations');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','Profile_CRA.Regulations','Regulations');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','Profile_CRA.SDV eSign','SDV eSign');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','Profile_CRA.SDV eSign','SDV eSign');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','Profile_CRA.SDV Signature Report','SDV Signature Report');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','Profile_CRA.SDV Signature Report','SDV Signature Report');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','Profile_CRA.SDV Status Report','SDV Status Report');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','Profile_CRA.SDV Status Report','SDV Status Report');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','Profile_CRA.SDV Strategy Report','SDV Strategy Report');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','Profile_CRA.SDV Strategy Report','SDV Strategy Report');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','Profile_CRA.SDV Violation Report','SDV Violation Report');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','Profile_CRA.SDV Violation Report','SDV Violation Report');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','Profile_CRA.Site''s list','Site''s list');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','Profile_CRA.Site''s list','Lista Centri');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','Profile_CRA.Source Data Verification','Source Data Verification');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','Profile_CRA.Source Data Verification','Source Data Verification');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','Profile_DE.Actions','Actions');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','Profile_DE.Actions','Azioni');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','Profile_DE.Activity list by Site','Activity list by Site');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','Profile_DE.Activity list by Site','Attività per Centro');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','Profile_DE.Answered eQueries','Answered eQueries');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','Profile_DE.Answered eQueries','eQuery Risposte');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','Profile_DE.Attività per Centro','Attività per Centro');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','Profile_DE.Azioni','Azioni');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','Profile_DE.Closed eQueries','Closed eQueries');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','Profile_DE.Closed eQueries','eQuery Chiuse');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','Profile_DE.Data Entry','Data Entry');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','Profile_DE.Data Entry','Data Entry');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','Profile_DE.Data Quality','Data Quality');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','Profile_DE.Data Quality','Data Quality');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','Profile_DE.End of treatment','Fine Trattamento');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','Profile_DE.End of treatment','End of treatment');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','Profile_DE.Help','Help');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','Profile_DE.Help','Help');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','Profile_DE.Home Page','Home Page');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','Profile_DE.Home Page','Home Page');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','Profile_DE.Outstanding eQueries','eQuery Pendenti');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','Profile_DE.Outstanding eQueries','Outstanding eQueries');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','Profile_DE.Predefined Reports','Predefined Reports');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','Profile_DE.Predefined Reports','Report Predefiniti');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','Profile_DE.profileName','Principal Investigator');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','Profile_DE.profileName','Principal Investigator');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','Profile_DE.Register new patient','Register new patient');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','Profile_DE.Register new patient','Registra nuovo paziente');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','Profile_DE.Registered patients','Registered patients');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','Profile_DE.Registered patients','Pazienti registrati');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','Profile_DE.SDV Signature Report','SDV Signature Report');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','Profile_DE.SDV Signature Report','SDV Signature Report');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','Profile_DE.SDV Status Report','SDV Status Report');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','Profile_DE.SDV Status Report','SDV Status Report');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','Profile_DE.SDV Strategy Report','SDV Strategy Report');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','Profile_DE.SDV Strategy Report','SDV Strategy Report');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','Profile_DE.SDV Violation Report','SDV Violation Report');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','Profile_DE.SDV Violation Report','SDV Violation Report');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','Profile_DE.Site''s list','Site''s list');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','Profile_DE.Site''s list','Lista Centri');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','Profile_DE.Source Data Verification','Source Data Verification');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','Profile_DE.Source Data Verification','Source Data Verification');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','Profile_DE.<span label-id-selector=''label-Profile_DE_Actions''>Actions</span><span class=''editlabel'' data-id=''Profile_DE.Actions'' label-id=''label-Profile_DE_Actions''><i class=''fa fa-pencil''></i></span>','<span label-id-selector=''label-Profile_DE_Actions''>Actions</span><span class=''editlabel'' data-id=''Profile_DE.Actions'' label-id=''label-Profile_DE_Actions''><i class=''fa fa-pencil''></i></span>');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','Profile_DE.<span label-id-selector=''label-Profile_DE_Actions''>Azioni</span><span class=''editlabel'' data-id=''Profile_DE.Actions'' label-id=''label-Profile_DE_Actions''><i class=''fa fa-pencil''></i></span>','<span label-id-selector=''label-Profile_DE_Actions''>Azioni</span><span class=''editlabel'' data-id=''Profile_DE.Actions'' label-id=''label-Profile_DE_Actions''><i class=''fa fa-pencil''></i></span>');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','Profile_DE.<span label-id-selector=''label-Profile_DE_Activity list by Site''>Activity list by Site</span><span class=''editlabel'' data-id=''Profile_DE.Activity list by Site'' label-id=''label-Profile_DE_Activity list by Site''><i class=''fa fa-pencil''></i></span>','<span label-id-selector=''label-Profile_DE_Activity list by Site''>Activity list by Site</span><span class=''editlabel'' data-id=''Profile_DE.Activity list by Site'' label-id=''label-Profile_DE_Activity list by Site''><i class=''fa fa-pencil''></i></span>');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','Profile_DE.<span label-id-selector=''label-Profile_DE_Activity list by Site''>Attività per Centro</span><span class=''editlabel'' data-id=''Profile_DE.Activity list by Site'' label-id=''label-Profile_DE_Activity list by Site''><i class=''fa fa-pencil''></i></span>','<span label-id-selector=''label-Profile_DE_Activity list by Site''>Attività per Centro</span><span class=''editlabel'' data-id=''Profile_DE.Activity list by Site'' label-id=''label-Profile_DE_Activity list by Site''><i class=''fa fa-pencil''></i></span>');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','Profile_DE.<span label-id-selector=''label-Profile_DE_Help''>Help</span><span class=''editlabel'' data-id=''Profile_DE.Help'' label-id=''label-Profile_DE_Help''><i class=''fa fa-pencil''></i></span>','<span label-id-selector=''label-Profile_DE_Help''>Help</span><span class=''editlabel'' data-id=''Profile_DE.Help'' label-id=''label-Profile_DE_Help''><i class=''fa fa-pencil''></i></span>');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','Profile_DE.<span label-id-selector=''label-Profile_DE_Help''>Help</span><span class=''editlabel'' data-id=''Profile_DE.Help'' label-id=''label-Profile_DE_Help''><i class=''fa fa-pencil''></i></span>','<span label-id-selector=''label-Profile_DE_Help''>Help</span><span class=''editlabel'' data-id=''Profile_DE.Help'' label-id=''label-Profile_DE_Help''><i class=''fa fa-pencil''></i></span>');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','Profile_DM.Actions','Actions');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','Profile_DM.Actions','Azioni');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','Profile_DM.Activity list by Site','Activity list by Site');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','Profile_DM.Activity list by Site','Attività per Centro');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','Profile_DM.Add/remove centers','Add/remove centers');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','Profile_DM.Add/remove centers','Aggiungi/rimuovi Centri');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','Profile_DM.Add/remove global users','Add/remove global users');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','Profile_DM.Add/remove global users','Aggiungi/rimuovi Utenti Globali');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','Profile_DM.Add/remove profiles','Aggiunti/rimuovi Profili');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','Profile_DM.Add/remove profiles','Add/remove profiles');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','Profile_DM.Administrative Console','Administrative Console');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','Profile_DM.Administrative Console','ACM');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','Profile_DM.Answered eQueries','eQuery Risposte');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','Profile_DM.Answered eQueries','Answered eQueries');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','Profile_DM.Attività per Centro','Attività per Centro');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','Profile_DM.Azioni','Azioni');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','Profile_DM.Baseline characteristics','Baseline characteristics');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','Profile_DM.Baseline characteristics','Profile_DM.Baseline characteristics');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','Profile_DM.Browse Data','Browse Data');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','Profile_DM.Browse Data','Naviga Dati');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','Profile_DM.Browse Tables','Browse Tables');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','Profile_DM.Browse Tables','Naviga Tabelle');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','Profile_DM.Browse tables','Browse tables');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','Profile_DM.Browse tables','Browse tables');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','Profile_DM.Closed eQueries','Closed eQueries');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','Profile_DM.Closed eQueries','eQuery Chiuse');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','Profile_DM.Data Management','Data Management');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','Profile_DM.Data Management','Data Management');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','Profile_DM.Data Quality','Data Quality');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','Profile_DM.Data Quality','Data Quality');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','Profile_DM.Drug prescriptions and administrations','Drug prescriptions and administrations');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','Profile_DM.Drug prescriptions and administrations','Profile_DM.Drug prescriptions and administrations');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','Profile_DM.End of treatment','Fine Trattamento');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','Profile_DM.End of treatment','End of treatment');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','Profile_DM.Export CSV','Export CSV');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','Profile_DM.Export CSV','Export CSV');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','Profile_DM.Export FLAT','Export FLAT');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','Profile_DM.Export FLAT','Export FLAT');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','Profile_DM.Export SAS XPT','Export SAS XPT');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','Profile_DM.Export SAS XPT','Export SAS XPT');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','Profile_DM.Export Tables','Esporta Tabelle');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','Profile_DM.Export Tables','Export Tables');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','Profile_DM.Export XLS','Export XLS');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','Profile_DM.Export XLS','Export XLS');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','Profile_DM.Export XLSX','Export XLSX');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','Profile_DM.Export XLSX','Export XLSX');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','Profile_DM.Export XML','Export XML');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','Profile_DM.Export XML','Export XML');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','Profile_DM.Help','Help');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','Profile_DM.Help','Help');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','Profile_DM.Home Page','Home Page');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','Profile_DM.Home Page','Home Page');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','Profile_DM.Lock Database','Lock Database');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','Profile_DM.Lock Database','Lock Database');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','Profile_DM.Open Builder','Open Builder');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','Profile_DM.Open Builder','Apri Builder');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','Profile_DM.Outstanding eQueries','Outstanding eQueries');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','Profile_DM.Outstanding eQueries','eQuery Pendenti');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','Profile_DM.Patients'' List','Patients'' List');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','Profile_DM.Patients'' List','Lista Pazienti');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','Profile_DM.Predefined Reports','Predefined Reports');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','Profile_DM.Predefined Reports','Report Predefiniti');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','Profile_DM.Profile_DM.Actions','Azioni');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','Profile_DM.Profile_DM.Activity list by Site','Attività per Centro');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','Profile_DM.Profile_DM.Help','Help');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','Profile_DM.profileName','Data Manager');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','Profile_DM.profileName','Data Manager');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','Profile_DM.Registered patients','Pazienti registrati');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','Profile_DM.Registered patients','Registered patients');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','Profile_DM.Shell SQL','Shell SQL');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','Profile_DM.Shell SQL','Shell SQL');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','Profile_DM.System Tables','System Tables');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','Profile_DM.System Tables','System Tables');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','Profile_DM.Upload XML Code','Upload XML Code');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','Profile_DM.Upload XML Code','Upload XML Code');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','Profile_DM.Upload XML File','Upload XML File');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','Profile_DM.Upload XML File','Upload XML File');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','Profile_DM.Wizard study configurator','Wizard study configurator');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','Profile_DM.Wizard study configurator','Wizard study configurator');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','Profile_PM.Actions','Azioni');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','Profile_PM.Actions','Actions');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','Profile_PM.Activity list by Site','Activity list by Site');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','Profile_PM.Answered eQueries','eQuery Risposte');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','Profile_PM.Answered eQueries','Answered eQueries');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','Profile_PM.Azioni','Azioni');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','Profile_PM.Baseline characteristics','Baseline characteristics');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','Profile_PM.Baseline characteristics','Profile_PM.Baseline characteristics');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','Profile_PM.Browse Data','Browse Data');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','Profile_PM.Browse Data','Naviga Dati');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','Profile_PM.Closed eQueries','Closed eQueries');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','Profile_PM.Closed eQueries','eQuery Chiuse');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','Profile_PM.Data Quality','Data Quality');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','Profile_PM.Data Quality','Data Quality');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','Profile_PM.Drug prescriptions and administrations','Drug prescriptions and administrations');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','Profile_PM.Drug prescriptions and administrations','Profile_PM.Drug prescriptions and administrations');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','Profile_PM.eCRFs','eCRFs');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','Profile_PM.eCRFs','eCRFs');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','Profile_PM.End of treatment','Fine trattamento');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','Profile_PM.End of treatment','End of treatment');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','Profile_PM.Help','Help');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','Profile_PM.Help','Help');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','Profile_PM.Highlights','Highlights');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','Profile_PM.Highlights','Highlights');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','Profile_PM.Home Page','Home Page');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','Profile_PM.Home Page','Home Page');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','Profile_PM.Opened eQueries','Opened eQueries');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','Profile_PM.Opened eQueries','eQuery Aperte');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','Profile_PM.Opened SDV strategy','Apri Strategia SDV');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','Profile_PM.Opened SDV strategy','Opened SDV strategy');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','Profile_PM.Outstanding eQueries','Outstanding eQueries');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','Profile_PM.Outstanding eQueries','eQuery Pendenti');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','Profile_PM.Predefined Reports','Report Predefiniti');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','Profile_PM.Predefined Reports','Predefined Reports');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','Profile_PM.profileName','Project Manager');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','Profile_PM.profileName','Project Manager');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','Profile_PM.Profile_PM.Actions','Azioni');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','Profile_PM.Profile_PM.eCRFs','eCRFs');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','Profile_PM.Profile_PM.Help','Help');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','Profile_PM.Profile_PM.Highlights','Highlights');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','Profile_PM.Profile_PM.Regulations','Regulations');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','Profile_PM.Registered patients','Pazienti Registrati');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','Profile_PM.Registered patients','Registered patients');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','Profile_PM.Regulations','Regulations');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','Profile_PM.Regulations','Regulations');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','Profile_PM.SDV Signature Report','SDV Signature Report');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','Profile_PM.SDV Signature Report','SDV Signature Report');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','Profile_PM.SDV Status Report','SDV Status Report');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','Profile_PM.SDV Status Report','SDV Status Report');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','Profile_PM.SDV Strategy Report','SDV Strategy Report');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','Profile_PM.SDV Strategy Report','SDV Strategy Report');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','Profile_PM.SDV Violation Report','SDV Violation Report');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','Profile_PM.SDV Violation Report','SDV Violation Report');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','Profile_PM.Site''s list','Site''s list');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','Profile_PM.Site''s list','Lista Centri');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','Profile_PM.Source Data Verification','Source Data Verification');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','Profile_PM.Source Data Verification','Source Data Verification');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','Profile_PM.View/Define Strategy','View/Define Strategy');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','Profile_PM.View/Define Strategy','Visualizza/definisci Strategia');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','Profile_RO.Actions','Actions');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','Profile_RO.Actions','Actions');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','Profile_RO.Activity list by Site','Activity list by Site');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','Profile_RO.Activity list by Site','Activity list by Site');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','Profile_RO.Answered eQueries','Answered eQueries');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','Profile_RO.Answered eQueries','Answered eQueries');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','Profile_RO.Baseline characteristics','Baseline characteristics');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','Profile_RO.Baseline characteristics','Baseline characteristics');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','Profile_RO.Browse Data','Browse Data');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','Profile_RO.Browse Data','Browse Data');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','Profile_RO.Closed eQueries','Closed eQueries');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','Profile_RO.Closed eQueries','Closed eQueries');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','Profile_RO.Data Quality','Data Quality');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','Profile_RO.Data Quality','Data Quality');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','Profile_RO.Drug prescriptions and administrations','Drug prescriptions and administrations');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','Profile_RO.Drug prescriptions and administrations','Drug prescriptions and administrations');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','Profile_RO.eCRFs','eCRFs');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','Profile_RO.eCRFs','eCRFs');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','Profile_RO.End of treatment','End of treatment');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','Profile_RO.End of treatment','End of treatment');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','Profile_RO.Help','Help');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','Profile_RO.Help','Help');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','Profile_RO.Home Page','Home Page');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','Profile_RO.Home Page','Home Page');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','Profile_RO.Outstanding eQueries','Outstanding eQueries');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','Profile_RO.Outstanding eQueries','Outstanding eQueries');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','Profile_RO.Predefined Reports','Predefined Reports');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','Profile_RO.Predefined Reports','Predefined Reports');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','Profile_RO.profileName','Read Only User');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','Profile_RO.profileName','Read Only User');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','Profile_RO.Registered patients','Registered patients');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','Profile_RO.Registered patients','Registered patients');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','Profile_RO.Regulations','Regulations');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','Profile_RO.Regulations','Regulations');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','Profile_RO.SDV Signature Report','SDV Signature Report');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','Profile_RO.SDV Signature Report','SDV Signature Report');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','Profile_RO.SDV Status Report','SDV Status Report');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','Profile_RO.SDV Status Report','SDV Status Report');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','Profile_RO.SDV Strategy Report','SDV Strategy Report');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','Profile_RO.SDV Strategy Report','SDV Strategy Report');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','Profile_RO.SDV Violation Report','SDV Violation Report');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','Profile_RO.SDV Violation Report','SDV Violation Report');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','Profile_RO.Site''s list','Site''s list');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','Profile_RO.Site''s list','Site''s list');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','Profile_RO.Source Data Verification','Source Data Verification');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','Profile_RO.Source Data Verification','Source Data Verification');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','Profile_SP.Actions','Actions');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','Profile_SP.Actions','Azioni');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','Profile_SP.Activity list by Site','Activity list by Site');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','Profile_SP.Answered eQueries','Answered eQueries');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','Profile_SP.Baseline characteristics','Profile_SP.Baseline characteristics');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','Profile_SP.Baseline characteristics','Baseline characteristics');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','Profile_SP.Browse Data','Browse Data');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','Profile_SP.Browse Data','Naviga Dati');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','Profile_SP.Closed eQueries','Closed eQueries');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','Profile_SP.Data Quality','Data Quality');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','Profile_SP.Drug prescriptions and administrations','Drug prescriptions and administrations');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','Profile_SP.Drug prescriptions and administrations','Profile_SP.Drug prescriptions and administrations');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','Profile_SP.eCRFs','eCRFs');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','Profile_SP.eCRFs','eCRFs');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','Profile_SP.End of treatment','End of treatment');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','Profile_SP.End of treatment','Fine Trattamento');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','Profile_SP.Help','Help');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','Profile_SP.Help','Help');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','Profile_SP.Highlights','Highlights');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','Profile_SP.Highlights','Highlights');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','Profile_SP.Home Page','Home Page');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','Profile_SP.Home Page','Home Page');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','Profile_SP.Outstanding eQueries','Outstanding eQueries');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','Profile_SP.Predefined Reports','Predefined Reports');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','Profile_SP.Predefined Reports','Report Predefiniti');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','Profile_SP.profileName','Sponsor');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','Profile_SP.profileName','Sponsor');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','Profile_SP.Registered patients','Pazienti Registrati');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','Profile_SP.Registered patients','Registered patients');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','Profile_SP.Regulations','Regulations');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','Profile_SP.Regulations','Regulations');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','Profile_SP.SDV Signature Report','SDV Signature Report');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','Profile_SP.SDV Status Report','SDV Status Report');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','Profile_SP.SDV Strategy Report','SDV Strategy Report');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','Profile_SP.SDV Violation Report','SDV Violation Report');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','Profile_SP.Site''s list','Site''s list');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','Profile_SP.Site''s list','Lista Centri');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','Profile_SP.Source Data Verification','Source Data Verification');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','Profile_ST.Actions','Actions');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','Profile_ST.Actions','Actions');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','Profile_ST.Activity list by Site','Activity list by Site');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','Profile_ST.Activity list by Site','Activity list by Site');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','Profile_ST.Answered eQueries','Answered eQueries');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','Profile_ST.Answered eQueries','Answered eQueries');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','Profile_ST.Baseline characteristics','Baseline characteristics');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','Profile_ST.Baseline characteristics','Baseline characteristics');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','Profile_ST.Closed eQueries','Closed eQueries');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','Profile_ST.Closed eQueries','Closed eQueries');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','Profile_ST.Data Entry','Data Entry');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','Profile_ST.Data Entry','Data Entry');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','Profile_ST.Data Quality','Data Quality');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','Profile_ST.Data Quality','Data Quality');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','Profile_ST.Drug prescriptions and administrations','Drug prescriptions and administrations');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','Profile_ST.Drug prescriptions and administrations','Drug prescriptions and administrations');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','Profile_ST.eCRFs','eCRFs');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','Profile_ST.eCRFs','eCRFs');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','Profile_ST.End of treatment','End of treatment');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','Profile_ST.End of treatment','End of treatment');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','Profile_ST.Help','Help');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','Profile_ST.Help','Help');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','Profile_ST.Home Page','Home Page');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','Profile_ST.Home Page','Home Page');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','Profile_ST.Outstanding eQueries','Outstanding eQueries');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','Profile_ST.Outstanding eQueries','Outstanding eQueries');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','Profile_ST.Predefined Reports','Predefined Reports');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','Profile_ST.Predefined Reports','Predefined Reports');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','Profile_ST.profileName','Site Staff');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','Profile_ST.profileName','Site Staff');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','Profile_ST.Register new patient','Register new patient');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','Profile_ST.Register new patient','Register new patient');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','Profile_ST.Registered patients','Registered patients');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','Profile_ST.Registered patients','Registered patients');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','Profile_ST.Regulations','Regulations');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','Profile_ST.Regulations','Regulations');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','Profile_ST.SDV Signature Report','SDV Signature Report');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','Profile_ST.SDV Signature Report','SDV Signature Report');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','Profile_ST.SDV Status Report','SDV Status Report');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','Profile_ST.SDV Status Report','SDV Status Report');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','Profile_ST.SDV Strategy Report','SDV Strategy Report');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','Profile_ST.SDV Strategy Report','SDV Strategy Report');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','Profile_ST.SDV Violation Report','SDV Violation Report');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','Profile_ST.SDV Violation Report','SDV Violation Report');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','Profile_ST.Site''s list','Site''s list');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','Profile_ST.Site''s list','Site''s list');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','Profile_ST.Source Data Verification','Source Data Verification');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','Profile_ST.Source Data Verification','Source Data Verification');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','registration.ButtonSend','Send');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','registration.ButtonSend','Invia');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('IT','registration.CODPAT.next','registration.CODPAT.next');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','registration.CODPAT.next','__EMPTY_STRING__');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','registration.CODPAT.next','__EMPTY_STRING__');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','registration.contextHelp.MYTITLE','__EMPTY_STRING__');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','registration.contextHelp.MYTITLE','__EMPTY_STRING__');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('IT','registration.contextHelp.MYTITLE','__EMPTY_STRING__');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','registration.contextHelp.SITEID','__EMPTY_STRING__');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('IT','registration.contextHelp.SITEID','__EMPTY_STRING__');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','registration.contextHelp.SITEID','__EMPTY_STRING__');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','registration.contextHelp.SITEIDDISPLAY','__EMPTY_STRING__');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('IT','registration.contextHelp.SITEIDDISPLAY','__EMPTY_STRING__');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','registration.contextHelp.SITEIDDISPLAY','__EMPTY_STRING__');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('IT','registration.contextHelp.SUBJID','__EMPTY_STRING__');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','registration.contextHelp.SUBJID','__EMPTY_STRING__');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','registration.contextHelp.SUBJID','__EMPTY_STRING__');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','registration.MYTITLE','<div class="titolo" align="center" >PATIENT REGISTRATION</div>');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','registration.MYTITLE','<div class="titolo" align="center" >REGISTRAZIONE PAZIENTE</div>');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('IT','registration.MYTITLE','<div class="titolo" align="center" >PATIENT REGISTRATION</div>');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('IT','registration.SITEID','Site No.');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','registration.SITEID','Nr. Centro');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','registration.SITEID','Site No.');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','registration.SITEIDDISPLAY','Nr. Centro');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','registration.SITEIDDISPLAY','Site No.');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('IT','registration.SITEIDDISPLAY','Site No.');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','registration.SUBJID','Nr. Paziente');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('IT','registration.SUBJID','Patient No.');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','registration.SUBJID','Patient No.');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','System.add_form','Add a new esam');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','System.add_form','Aggiungi nuovo esame');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','System.alldEqL','List of all eQuery');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','System.alldEqL','Lista di tutte le eQuery');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','System.allEq','View all eQueries');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','System.allEq','Vedi tutte le eQuery');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','System.apply_changes','Applica cambiamenti');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','System.apply_changes','Apply changes');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','System.audit_trail.audit_trail','Audit Trail');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','System.audit_trail.not_available','Not Available');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','System.audit_trail.set_audit_trail','Set Audit Trail');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','System.audit_trail.txt_CRA_eQ','Correction due to eQuery by CRA');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','System.audit_trail.txt_CRA_eQ','Correzione dovuta a eQuery del CRA');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','System.audit_trail.txt_DE_edit','Change/update by Investigator');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','System.audit_trail.txt_DE_edit','Modifica/aggiornamento dell''Investigator');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','System.audit_trail.txt_DE_eQ','Correzione del Data Entry');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','System.audit_trail.txt_DE_eQ','Correction by Data Entry');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','System.audit_trail.txt_DE_eQ_reopen_mainsub','Correzione ovvia dell''Investigator');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','System.audit_trail.txt_DE_eQ_reopen_mainsub','Obvious correction by Investigator');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','System.audit_trail.txt_DM_eQ','Correction by Data Entry due to eQuery by Data Manager');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','System.audit_trail.txt_DM_eQ','Correzione del Data Entry dovuta a eQuery del Data Manager');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','System.audit_trail.txt_DM_notify','Correzione ovvia del Data Manager');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','System.audit_trail.txt_DM_notify','Obvious correction by Data Manager');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','System.audit_trail.txt_first_insert','Primo inserimento');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','System.audit_trail.txt_first_insert','Original Entry');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','System.audit_trail.unset_audit_trail','Unset Audit Trail');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','System.badRequest','THE REQUEST IS NOT PROPERLY FORMED, THEREFORE IT CANNOT BE PROCESSED.');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','System.badRequest','LA RICHIESTA NON E'' FORMULATA CORRETTAMENTE, QUINDI NON PUO'' ESSERE PROCESSATA.');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','System.cancel','Annulla');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','System.cancel','Cancel');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','System.Center','Center');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','System.Center','Centro');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','System.Change Language','Cambia Lingua');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','System.Change Language','Change Language');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','System.Change Password','Change Password');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','System.Change Password','Cambia Password');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','System.Change Profile','Change Profile');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','System.Change Profile','Cambia Profilo');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','System.ChangeMadeAt','Modifice eseguite al');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','System.ChangeMadeAt','Changes made to the');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','System.ChangeNecessary','Cambiamento necessario');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','System.ChangeNecessary','Change is necessary');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','System.ChangeNotNecessary','Cambiamento non necessario');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','System.ChangeNotNecessary','Change is not necessary');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','System.closeDate','close date');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','System.closeDate','data chiusura');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','System.closedEq','Visualizza eQuery Chiuse');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','System.closedEq','View closed eQueries');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','System.closedEqL','Lista delle eQuery Chiuse');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','System.closedEqL','List of closed eQueries');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','System.Dateofanswer','Date of answer');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','System.Dateofanswer','Data risposta');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','System.enableEditLabelInLine','Abilita/Disabilita modifica inline etichette');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','System.enableEditLabelInLine','Enable/Disable inline label editing');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','System.eQueryDate','Data eQuery');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','System.eQueryDate','eQuery Date');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','System.eQueryList','eQuery List');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','System.eQueryList','Lista eQuery');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','System.eQueryType','eQuery Type');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','System.eQueryType','Tipo eQuery');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','System.eQueryTypeNull','Tipo eQuery Nuòòp');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','System.eQueryTypeNull','eQuery Type Null');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','System.eQueryType1','eQuery Type 1');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','System.eQueryType1','eQuery Tipo 1');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','System.eQueryType2','eQuery Tipo 2');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','System.eQueryType2','eQuery Type 2');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','System.Esam','Esame');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','System.Esam','Esam');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','System.Exam.Completed','Completed');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','System.Exam.Completed','Completato');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','System.exams.data','data');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','System.exams.data','Dati');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','System.exams.enter','Invia');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','System.exams.enter','Enter');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','System.FormButtonLegend','Legenda bottoni');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','System.FormButtonLegend','Button Legend');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','System.gest_prof','Profile Administration');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','System.gest_prof','Gestione Profili');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','System.Home','Home');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','System.Home','Home');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','System.is incomplete','is incomplete');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','System.is incomplete','Incompleto');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','System.lastMessages','Last Messages');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','System.lastMessages','Ultimi Messaggi');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','System.Lista completa','Complete patient''s view');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','System.Lista completa','Lista Completa');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','System.Localization Management','System.Localization Management');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','System.Localization Management','Gestione Localizzazione');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','System.Logout','Logout');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','System.Logout','Logout');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','System.MainSub.back_record_list','Back to records list');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','System.Messages','InBox');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','System.Messages','InBox');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','System.mismatchedCenter','MISMATCHED CENTER AND PATIENT: AUTHORIZATION DENIED');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','System.mismatchedCenter','MANCATA CORRISPONDENZA CENTRO/PAZIENTE: AUTORIZZAZIONE NEGATA');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','System.Modify','Modify');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','System.Modify','Modifica');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','System.ModifyForm','Modify form');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','System.ModifyForm','Modifica form');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','System.necessary','Necessario');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','System.necessary','Necessary');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','System.New','Nuovo');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','System.New','New');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','System.newEq','New eQuery');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','System.newEq','Nuova eQuery');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','System.newEquery','New eQuery');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','System.newEquery','Nuova eQuery');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','System.newMessage','Nuovo Messaggio');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','System.newMessage','New Message');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','System.noPatient','There are no patients in this center');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','System.noPatient','Non ci sono pazianti in questo centro');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','System.NOTCREABLE','No rights to create the visit');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','System.NOTCREABLE','Nessun permesso per creare la visita');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','System.NOTDELETABLE','Nessun permesso per eliminare la visita o l''esame');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','System.NOTDELETABLE','No rights to delete the esam or visit');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','System.notNecessary','Non necessario');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','System.notNecessary','Not necessary');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','System.openedEq','List of open eQueries');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','System.openedEq','Lista eQuery Aperte');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','System.openedEqS','Show open eQuery');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','System.openedEqS','Visualizza eQuery Aperte');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','System.PatientFolder','Cartella Paziente');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','System.PatientFolder','Patient''s Folder');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','System.PatientLatestActivities','Patient''s Latest Activities');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','System.PatientLatestActivities','Ultime attività sul paziente');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','System.patient_table.center_code','Center Code');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','System.patient_table.center_code','Codice Centro');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','System.patient_table.eq_not_available','Not Available');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','System.patient_table.eq_not_available','Non disponibile');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','System.patient_table.label_dblock','DB LOCK STATUS');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','System.patient_table.link_eq_on','Data Quality');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','System.patient_table.link_eq_on','Data Quality');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','System.patient_table.link_modify_form','Modify Form');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','System.patient_table.link_set_eq','Open eQ');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','System.patient_table.link_set_mod','Open');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','System.patient_table.link_unset_eq','Close eQ');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','System.patient_table.link_unset_mod','Close');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','System.patient_table.lock_obvious_label','Obvious corrections');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','System.patient_table.lock_query_label','eQuery');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','System.patient_table.lock_save_send_label','Save/Send forms');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','System.patient_table.patient_code','Patient Code');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','System.patient_table.patient_code','Codice Paziente');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','System.patient_table.registration_date','Registration Date');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','System.patient_table.registration_date','Data registrazione');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','System.RangeCheck.Alert','Edit Check Alert');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('IT','System.RangeCheck.Alert','Edit Check Alert');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','System.RangeCheck.Alert','Edit Check Alert');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','System.RangeCheck.Ok','Ok');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','System.RangeCheck.Ok','Ok');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('IT','System.RangeCheck.Ok','Ok');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','System.receivedEq','eQuery Ricevuta');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','System.receivedEq','eQuery Received');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','System.Registro Lista Centri','Registry Center List');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','System.Registro Lista Centri','Registro Lista Centri');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','System.Registro Lista Pazienti','Registry Patients List');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','System.Registro Lista Pazienti','Registro Lista Pazienti');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','System.Registry','Registro');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','System.Registry','Registry');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','System.rowPerPage','Records per page');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','System.rowPerPage','Righe per pagina');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','System.save_neccessary','Attenzione, è necessario usare questo bottone per salvare i cambiamenti');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','System.save_neccessary','Attention, it is necessary to use the following button in order to apply the changes.');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','System.schedaInviata','<p align=center><b>This form has been sent !!!<br>Impossible to modify</p>');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','System.schedaInviata','<p align=center><b>Questa form è già stata inviata !!!<br>Impossibile modificarla</p>');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','System.Search','Cerca');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','System.Search','Search');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','System.searchEq','Cerca eQuery');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','System.searchEq','Search eQuery');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','System.sendAnswer','Invia Risposta');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','System.sendAnswer','Send answer');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','System.sendedEq','eQuery Sent');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','System.sendedEq','eQuery inviata');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','System.The form','The form');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','System.The form','La form');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','System.userNotCenter','USER NOT IN CENTER LIST');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','System.userNotCenter','UTENTE NON IN LISTA CENTRO');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','System.userNotHaveCenter','USER CAN''T VIEW THIS CENTER: AUTHORIZATION DENIED');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','System.userNotHaveCenter','L''UTENTE NON PUO'' VISUALIZZARE IL CENTRO: AUTORIZZAZIONE NEGATA');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','System.Visit','Visit');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','System.Visit','vISITA');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','System.Vista Paziente','Vista Paziente');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','System.Vista Paziente','Patient''s View');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','System.visualizzaScheda','Show form');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','System.visualizzaScheda','Visualizza Scheda');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','VISIT.0.EXAM.0.NAME','Registrazione');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','VISIT.0.EXAM.0.NAME','Registration');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('en','VISIT.0.NAME','Registration');
Insert into ACM_STUDY_I18N (LANG,LABEL,TEXT) values ('it','VISIT.0.NAME','Registrazione');
Insert into ACM_STUDY_I18N (LANG, LABEL, TEXT) VALUES ('en', 'List.patients_list_CRA.Column.Center Code', 'Center Code')
Insert into ACM_STUDY_I18N (LANG, LABEL, TEXT) VALUES ('it', 'List.patients_list_CRA.Column.Patient Code', 'Codice Paziente')
Insert into ACM_STUDY_I18N (LANG, LABEL, TEXT) VALUES ('en', 'List.patients_list_CRA.Column.Patient view', 'Patient view')
Insert into ACM_STUDY_I18N (LANG, LABEL, TEXT) VALUES ('en', 'List.patients_list_CRA.Column.Patient Code', 'Patient Code')
Insert into ACM_STUDY_I18N (LANG, LABEL, TEXT) VALUES ('it', 'List.patients_list_CRA.Column.Center Code', 'Codice Centro')


CREATE SEQUENCE ACM_LOG_ID
  START WITH 1
  MAXVALUE 9999999999999999999999999999
  MINVALUE 1
  NOCYCLE
  NOCACHE
  NOORDER;

CREATE SEQUENCE ACM_STORICO_ID
  START WITH 1
  MAXVALUE 9999999999999999999999999999
  MINVALUE 1
  NOCYCLE
  NOCACHE
  NOORDER;


CREATE SEQUENCE INBOX_CORRISPONDENZA_SEQ
  START WITH 1
  MAXVALUE 999999999999
  MINVALUE 1
  NOCYCLE
  NOCACHE
  ORDER;


CREATE SEQUENCE INBOX_MESSAGGI_SEQ
  START WITH 1
  MAXVALUE 999999999999
  MINVALUE 1
  NOCYCLE
  NOCACHE
  ORDER;


CREATE SEQUENCE SESSIONS_SEQ
  START WITH 1
  MAXVALUE 9999999999999999999999999999
  MINVALUE 1
  NOCYCLE
  NOCACHE
  NOORDER;


CREATE SEQUENCE STUDIES_PROFILES_SEQ
  START WITH 1
  MAXVALUE 999999999999999999999999999
  MINVALUE 1
  NOCYCLE
  NOCACHE
  NOORDER;

CREATE SEQUENCE SITES_SEQ
  START WITH 1
  MAXVALUE 999999999999999999999999999
  MINVALUE 1
  NOCYCLE
  NOCACHE
  NOORDER;



CREATE OR REPLACE TRIGGER PENTAHO_XCRFAUTH_TR
AFTER INSERT OR DELETE  ON STUDIES_PROFILES REFERENCING OLD AS v NEW AS newRow for each row
BEGIN
if inserting then
insert into [IDP_DBNAME].AUTHORITIES (AUTHORITY,DESCRIPTION) values(:newRow.study_prefix||'_'||:newRow.code||'@[ID_SERVIZIO].[IDP_NAME]',:newRow.study_prefix||'_'||:newRow.code||'@[ID_SERVIZIO].[IDP_NAME]');
end if;
if deleting then
delete [IDP_DBNAME].AUTHORITIES where AUTHORITY=:v.study_prefix||'_'||:v.code||'@[ID_SERVIZIO].[IDP_NAME]';
end if;
END;
/


CREATE OR REPLACE TRIGGER PENTAHO5_XCRFAUTH_TR
AFTER INSERT OR DELETE  ON STUDIES_PROFILES REFERENCING OLD AS v NEW AS newRow for each row
BEGIN
if inserting then
insert into PENTAHO5.AUTHORITIES (AUTHORITY) values(:newRow.study_prefix||'_'||:newRow.code||'@[ID_SERVIZIO].[IDP_NAME]');
end if;
if deleting then
delete PENTAHO5.AUTHORITIES where AUTHORITY=:v.study_prefix||'_'||:v.code||'@[ID_SERVIZIO].[IDP_NAME]';
end if;
END;
/


CREATE OR REPLACE TRIGGER PENTAHO_XCRFGRANTED_AUTH_TR
AFTER INSERT OR DELETE  ON USERS_PROFILES REFERENCING OLD AS v NEW AS newRow for each row
BEGIN
if inserting then
insert into [IDP_DBNAME].GRANTED_AUTHORITIES (USERNAME,AUTHORITY) select :newRow.userid||'@[ID_SERVIZIO].[IDP_NAME]', study_prefix||'_'||code||'@[ID_SERVIZIO].[IDP_NAME]' from STUDIES_PROFILES where ID=:newRow.PROFILE_ID;
end if;
if deleting then
delete [IDP_DBNAME].GRANTED_AUTHORITIES where (USERNAME,AUTHORITY)=(select :v.userid||'@[ID_SERVIZIO].[IDP_NAME]', study_prefix||'_'||code||'@[ID_SERVIZIO].[IDP_NAME]' from STUDIES_PROFILES where ID=:v.PROFILE_ID);
end if;
END;
/


CREATE OR REPLACE TRIGGER PENTAHO5_XCRFGRANTED_AUTH_TR
AFTER INSERT OR DELETE  ON USERS_PROFILES REFERENCING OLD AS v NEW AS newRow for each row
BEGIN
if inserting then
insert into PENTAHO5.GRANTED_AUTHORITIES (USERNAME,AUTHORITY) select :newRow.userid||'@[ID_SERVIZIO].[IDP_NAME]', study_prefix||'_'||code||'@[ID_SERVIZIO].[IDP_NAME]' from STUDIES_PROFILES where ID=:newRow.PROFILE_ID;
end if;
if deleting then
delete PENTAHO5.GRANTED_AUTHORITIES where (USERNAME,AUTHORITY)=(select :v.userid||'@[ID_SERVIZIO].[IDP_NAME]', study_prefix||'_'||code||'@[ID_SERVIZIO].[IDP_NAME]' from STUDIES_PROFILES where ID=:v.PROFILE_ID);
end if;
END;
/
