create table SITES(
ID number, 
DESCR varchar2(400 CHAR),
CODE varchar2(10 CHAR),
ACTIVE number,
CONSTRAINT "PK_SITES" PRIMARY KEY ("ID") ENABLE
);

CREATE SEQUENCE SITES_SEQ MINVALUE 1 MAXVALUE 999999999999999999999999999 INCREMENT BY 1 START WITH 1 NOCACHE NOORDER NOCYCLE ;

create table STUDIES(
PREFIX varchar2(10 CHAR),
DESCR varchar2(400 CHAR),
ACTIVE number,
CONSTRAINT "PK_STUDIES" PRIMARY KEY ("PREFIX") ENABLE
);

create table SITES_STUDIES(
SITE_ID number,
STUDY_PREFIX varchar2(10 CHAR),
ACTIVE number,
CONSTRAINT "PK_SITES_STUDIES" PRIMARY KEY ("SITE_ID", "STUDY_PREFIX") ENABLE,
CONSTRAINT "FK1_SITES_STUDIES" FOREIGN KEY ("SITE_ID") REFERENCES "SITES" ("ID") ENABLE,
CONSTRAINT "FK2_SITES_STUDIES" FOREIGN KEY ("STUDY_PREFIX") REFERENCES "STUDIES" ("PREFIX") ENABLE
);

create table USERS_SITES(
USERID varchar2(200 char),
SITE_ID number,
CONSTRAINT "PK_USERS_SITES" PRIMARY KEY ("SITE_ID", "USERID") ENABLE,
CONSTRAINT "FK1_USERS_SITES" FOREIGN KEY ("SITE_ID") REFERENCES "SITES" ("ID") ENABLE,
CONSTRAINT "FK2_USERS_SITES" FOREIGN KEY ("USERID") REFERENCES "UTENTI" ("USERID") ENABLE
);

create table STUDIES_PROFILES(
ID number,
CODE varchar2(40 CHAR),
STUDY_PREFIX varchar2(10 CHAR),
ACTIVE number,
CONSTRAINT "PK_STUDIES_PROFILES" PRIMARY KEY ("ID") ENABLE,
CONSTRAINT "FK1_STUDIES_PROFILES" FOREIGN KEY ("STUDY_PREFIX") REFERENCES "STUDIES" ("PREFIX") ENABLE
);


CREATE SEQUENCE STUDIES_PROFILES_SEQ MINVALUE 1 MAXVALUE 999999999999999999999999999 INCREMENT BY 1 START WITH 1 NOCACHE NOORDER NOCYCLE ;


create table USERS_STUDIES(
USERID varchar2(200 char),
STUDY_PREFIX varchar2(10 CHAR),
ACTIVE number,
CONSTRAINT "PK_USERS_STUDIES" PRIMARY KEY ("STUDY_PREFIX", "USERID") ENABLE,
CONSTRAINT "FK1_USERS_STUDIES" FOREIGN KEY ("STUDY_PREFIX") REFERENCES "STUDIES" ("PREFIX") ENABLE,
CONSTRAINT "FK2_USERS_STUDIES" FOREIGN KEY ("USERID") REFERENCES "UTENTI" ("USERID") ENABLE
);

create table USERS_PROFILES(
USERID varchar2(200 char),
PROFILE_ID number,
ACTIVE number,
CONSTRAINT "PK_USERS_PROFILES" PRIMARY KEY ("PROFILE_ID", "USERID") ENABLE,
CONSTRAINT "FK1_USERS_PROFILES" FOREIGN KEY ("PROFILE_ID") REFERENCES "STUDIES_PROFILES" ("ID") ENABLE,
CONSTRAINT "FK2_USERS_PROFILES" FOREIGN KEY ("USERID") REFERENCES "UTENTI" ("USERID") ENABLE
);

create table USERS_SITES_STUDIES(
USERID  VARCHAR2(200 CHAR),
SITE_ID NUMBER,
STUDY_PREFIX varchar2(10 CHAR),
ACTIVE number,
CONSTRAINT PK_USERS_SITES_STUDIES PRIMARY KEY (SITE_ID, USERID, STUDY_PREFIX) ENABLE,
CONSTRAINT FK1_USERS_SITES_STUDIES FOREIGN KEY (SITE_ID) REFERENCES SITES (ID) ENABLE,
CONSTRAINT FK2_USERS_SITES_STUDIES FOREIGN KEY (USERID) REFERENCES UTENTI (USERID) ENABLE,
CONSTRAINT FK3_USERS_SITES_STUDIES FOREIGN KEY (STUDY_PREFIX) REFERENCES STUDIES (PREFIX) ENABLE,
CONSTRAINT FK4_USERS_SITES_STUDIES FOREIGN KEY (USERID, STUDY_PREFIX) REFERENCES USERS_STUDIES (USERID, STUDY_PREFIX) ENABLE,
CONSTRAINT FK5_USERS_SITES_STUDIES FOREIGN KEY (SITE_ID, STUDY_PREFIX) REFERENCES SITES_STUDIES (SITE_ID, STUDY_PREFIX) ENABLE,
CONSTRAINT FK6_USERS_SITES_STUDIES FOREIGN KEY (SITE_ID, USERID) REFERENCES USERS_SITES (SITE_ID, USERID) ENABLE
);




