package it.cineca.siss.axmr3.doc.scheduler.dbTables;

import java.util.LinkedList;
import java.util.List;

/**
 * Created by Carlo on 14/02/2016.
 */
public class Oracle {

    private List<String> stmts;

    public List<String> getStmts() {
        return stmts;
    }

    public void setStmts(List<String> stmts) {
        this.stmts = stmts;
    }


    public Oracle(String prefix) {
        this.stmts=new LinkedList<String>();
        this.stmts.add("CREATE TABLE "+prefix+"job_details\n" +
                "  (\n" +
                "    SCHED_NAME VARCHAR2(120) NOT NULL,\n" +
                "    JOB_NAME  VARCHAR2(200) NOT NULL,\n" +
                "    JOB_GROUP VARCHAR2(200) NOT NULL,\n" +
                "    DESCRIPTION VARCHAR2(250) NULL,\n" +
                "    JOB_CLASS_NAME   VARCHAR2(250) NOT NULL, \n" +
                "    IS_DURABLE VARCHAR2(1) NOT NULL,\n" +
                "    IS_NONCONCURRENT VARCHAR2(1) NOT NULL,\n" +
                "    IS_UPDATE_DATA VARCHAR2(1) NOT NULL,\n" +
                "    REQUESTS_RECOVERY VARCHAR2(1) NOT NULL,\n" +
                "    JOB_DATA BLOB NULL,\n" +
                "    CONSTRAINT "+prefix+"_JOB_DETAILS_PK PRIMARY KEY (SCHED_NAME,JOB_NAME,JOB_GROUP)\n" +
                ")");
        this.stmts.add("CREATE TABLE "+prefix+"triggers\n" +
                "  (\n" +
                "    SCHED_NAME VARCHAR2(120) NOT NULL,\n" +
                "    TRIGGER_NAME VARCHAR2(200) NOT NULL,\n" +
                "    TRIGGER_GROUP VARCHAR2(200) NOT NULL,\n" +
                "    JOB_NAME  VARCHAR2(200) NOT NULL, \n" +
                "    JOB_GROUP VARCHAR2(200) NOT NULL,\n" +
                "    DESCRIPTION VARCHAR2(250) NULL,\n" +
                "    NEXT_FIRE_TIME NUMBER(13) NULL,\n" +
                "    PREV_FIRE_TIME NUMBER(13) NULL,\n" +
                "    PRIORITY NUMBER(13) NULL,\n" +
                "    TRIGGER_STATE VARCHAR2(16) NOT NULL,\n" +
                "    TRIGGER_TYPE VARCHAR2(8) NOT NULL,\n" +
                "    START_TIME NUMBER(13) NOT NULL,\n" +
                "    END_TIME NUMBER(13) NULL,\n" +
                "    CALENDAR_NAME VARCHAR2(200) NULL,\n" +
                "    MISFIRE_INSTR NUMBER(2) NULL,\n" +
                "    JOB_DATA BLOB NULL,\n" +
                "    CONSTRAINT "+prefix+"TRIGGERS_PK PRIMARY KEY (SCHED_NAME,TRIGGER_NAME,TRIGGER_GROUP),\n" +
                "    CONSTRAINT "+prefix+"TRIGGER_TO_JOBS_FK FOREIGN KEY (SCHED_NAME,JOB_NAME,JOB_GROUP) \n" +
                "      REFERENCES "+prefix+"JOB_DETAILS(SCHED_NAME,JOB_NAME,JOB_GROUP) \n" +
                ")");
        this.stmts.add("CREATE TABLE "+prefix+"simple_triggers\n" +
                "  (\n" +
                "    SCHED_NAME VARCHAR2(120) NOT NULL,\n" +
                "    TRIGGER_NAME VARCHAR2(200) NOT NULL,\n" +
                "    TRIGGER_GROUP VARCHAR2(200) NOT NULL,\n" +
                "    REPEAT_COUNT NUMBER(7) NOT NULL,\n" +
                "    REPEAT_INTERVAL NUMBER(12) NOT NULL,\n" +
                "    TIMES_TRIGGERED NUMBER(10) NOT NULL,\n" +
                "    CONSTRAINT "+prefix+"SIMPLE_TRIG_PK PRIMARY KEY (SCHED_NAME,TRIGGER_NAME,TRIGGER_GROUP),\n" +
                "    CONSTRAINT "+prefix+"SIMPLE_TRIG_TO_TRIG_FK FOREIGN KEY (SCHED_NAME,TRIGGER_NAME,TRIGGER_GROUP) \n" +
                "\tREFERENCES "+prefix+"TRIGGERS(SCHED_NAME,TRIGGER_NAME,TRIGGER_GROUP)\n" +
                ")");
        this.stmts.add("CREATE TABLE "+prefix+"cron_triggers\n" +
                "  (\n" +
                "    SCHED_NAME VARCHAR2(120) NOT NULL,\n" +
                "    TRIGGER_NAME VARCHAR2(200) NOT NULL,\n" +
                "    TRIGGER_GROUP VARCHAR2(200) NOT NULL,\n" +
                "    CRON_EXPRESSION VARCHAR2(120) NOT NULL,\n" +
                "    TIME_ZONE_ID VARCHAR2(80),\n" +
                "    CONSTRAINT "+prefix+"CRON_TRIG_PK PRIMARY KEY (SCHED_NAME,TRIGGER_NAME,TRIGGER_GROUP),\n" +
                "    CONSTRAINT "+prefix+"CRON_TRIG_TO_TRIG_FK FOREIGN KEY (SCHED_NAME,TRIGGER_NAME,TRIGGER_GROUP) \n" +
                "      REFERENCES "+prefix+"TRIGGERS(SCHED_NAME,TRIGGER_NAME,TRIGGER_GROUP)\n" +
                ")");
        this.stmts.add("CREATE TABLE "+prefix+"simprop_triggers\n" +
                "  (          \n" +
                "    SCHED_NAME VARCHAR2(120) NOT NULL,\n" +
                "    TRIGGER_NAME VARCHAR2(200) NOT NULL,\n" +
                "    TRIGGER_GROUP VARCHAR2(200) NOT NULL,\n" +
                "    STR_PROP_1 VARCHAR2(512) NULL,\n" +
                "    STR_PROP_2 VARCHAR2(512) NULL,\n" +
                "    STR_PROP_3 VARCHAR2(512) NULL,\n" +
                "    INT_PROP_1 NUMBER(10) NULL,\n" +
                "    INT_PROP_2 NUMBER(10) NULL,\n" +
                "    LONG_PROP_1 NUMBER(13) NULL,\n" +
                "    LONG_PROP_2 NUMBER(13) NULL,\n" +
                "    DEC_PROP_1 NUMERIC(13,4) NULL,\n" +
                "    DEC_PROP_2 NUMERIC(13,4) NULL,\n" +
                "    BOOL_PROP_1 VARCHAR2(1) NULL,\n" +
                "    BOOL_PROP_2 VARCHAR2(1) NULL,\n" +
                "    CONSTRAINT "+prefix+"SIMPROP_TRIG_PK PRIMARY KEY (SCHED_NAME,TRIGGER_NAME,TRIGGER_GROUP),\n" +
                "    CONSTRAINT "+prefix+"SIMPROP_TRIG_TO_TRIG_FK FOREIGN KEY (SCHED_NAME,TRIGGER_NAME,TRIGGER_GROUP) \n" +
                "      REFERENCES "+prefix+"TRIGGERS(SCHED_NAME,TRIGGER_NAME,TRIGGER_GROUP)\n" +
                ")");
        this.stmts.add("CREATE TABLE "+prefix+"blob_triggers\n" +
                "  (\n" +
                "    SCHED_NAME VARCHAR2(120) NOT NULL,\n" +
                "    TRIGGER_NAME VARCHAR2(200) NOT NULL,\n" +
                "    TRIGGER_GROUP VARCHAR2(200) NOT NULL,\n" +
                "    BLOB_DATA BLOB NULL,\n" +
                "    CONSTRAINT "+prefix+"BLOB_TRIG_PK PRIMARY KEY (SCHED_NAME,TRIGGER_NAME,TRIGGER_GROUP),\n" +
                "    CONSTRAINT "+prefix+"BLOB_TRIG_TO_TRIG_FK FOREIGN KEY (SCHED_NAME,TRIGGER_NAME,TRIGGER_GROUP) \n" +
                "        REFERENCES "+prefix+"TRIGGERS(SCHED_NAME,TRIGGER_NAME,TRIGGER_GROUP)\n" +
                ")");
        this.stmts.add("CREATE TABLE "+prefix+"calendars\n" +
                "  (\n" +
                "    SCHED_NAME VARCHAR2(120) NOT NULL,\n" +
                "    CALENDAR_NAME  VARCHAR2(200) NOT NULL, \n" +
                "    CALENDAR BLOB NOT NULL,\n" +
                "    CONSTRAINT "+prefix+"CALENDARS_PK PRIMARY KEY (SCHED_NAME,CALENDAR_NAME)\n" +
                ")");
        this.stmts.add("CREATE TABLE "+prefix+"paused_trigger_grps\n" +
                "  (\n" +
                "    SCHED_NAME VARCHAR2(120) NOT NULL,\n" +
                "    TRIGGER_GROUP  VARCHAR2(200) NOT NULL, \n" +
                "    CONSTRAINT "+prefix+"PAUSED_TRIG_GRPS_PK PRIMARY KEY (SCHED_NAME,TRIGGER_GROUP)\n" +
                ")");
        this.stmts.add("CREATE TABLE "+prefix+"fired_triggers \n" +
                "  (\n" +
                "    SCHED_NAME VARCHAR2(120) NOT NULL,\n" +
                "    ENTRY_ID VARCHAR2(95) NOT NULL,\n" +
                "    TRIGGER_NAME VARCHAR2(200) NOT NULL,\n" +
                "    TRIGGER_GROUP VARCHAR2(200) NOT NULL,\n" +
                "    INSTANCE_NAME VARCHAR2(200) NOT NULL,\n" +
                "    FIRED_TIME NUMBER(13) NOT NULL,\n" +
                "    PRIORITY NUMBER(13) NOT NULL,\n" +
                "    STATE VARCHAR2(16) NOT NULL,\n" +
                "    JOB_NAME VARCHAR2(200) NULL,\n" +
                "    JOB_GROUP VARCHAR2(200) NULL,\n" +
                "    IS_NONCONCURRENT VARCHAR2(1) NULL,\n" +
                "    REQUESTS_RECOVERY VARCHAR2(1) NULL,\n" +
                "    CONSTRAINT "+prefix+"FIRED_TRIGGER_PK PRIMARY KEY (SCHED_NAME,ENTRY_ID)\n" +
                ")");
        this.stmts.add("CREATE TABLE "+prefix+"scheduler_state \n" +
                "  (\n" +
                "    SCHED_NAME VARCHAR2(120) NOT NULL,\n" +
                "    INSTANCE_NAME VARCHAR2(200) NOT NULL,\n" +
                "    LAST_CHECKIN_TIME NUMBER(13) NOT NULL,\n" +
                "    CHECKIN_INTERVAL NUMBER(13) NOT NULL,\n" +
                "    CONSTRAINT "+prefix+"SCHEDULER_STATE_PK PRIMARY KEY (SCHED_NAME,INSTANCE_NAME)\n" +
                ")");
        this.stmts.add("CREATE TABLE "+prefix+"locks\n" +
                "  (\n" +
                "    SCHED_NAME VARCHAR2(120) NOT NULL,\n" +
                "    LOCK_NAME  VARCHAR2(40) NOT NULL, \n" +
                "    CONSTRAINT "+prefix+"LOCKS_PK PRIMARY KEY (SCHED_NAME,LOCK_NAME)\n" +
                ")");
        this.stmts.add("create index idx_"+prefix+"1 on "+prefix+"job_details(SCHED_NAME,REQUESTS_RECOVERY)");
        this.stmts.add("create index idx_"+prefix+"2 on "+prefix+"job_details(SCHED_NAME,JOB_GROUP)");
        this.stmts.add("create index idx_"+prefix+"3 on "+prefix+"triggers(SCHED_NAME,JOB_NAME,JOB_GROUP)");
        this.stmts.add("create index idx_"+prefix+"4 on "+prefix+"triggers(SCHED_NAME,JOB_GROUP)");
        this.stmts.add("create index idx_"+prefix+"5 on "+prefix+"triggers(SCHED_NAME,CALENDAR_NAME)");
        this.stmts.add("create index idx_"+prefix+"6 on "+prefix+"triggers(SCHED_NAME,TRIGGER_GROUP)");
        this.stmts.add("create index idx_"+prefix+"7 on "+prefix+"triggers(SCHED_NAME,TRIGGER_STATE)");
        this.stmts.add("create index idx_"+prefix+"8 on "+prefix+"triggers(SCHED_NAME,TRIGGER_NAME,TRIGGER_GROUP,TRIGGER_STATE)");
        this.stmts.add("create index idx_"+prefix+"9 on "+prefix+"triggers(SCHED_NAME,TRIGGER_GROUP,TRIGGER_STATE)");
        this.stmts.add("create index idx_"+prefix+"10 on "+prefix+"triggers(SCHED_NAME,NEXT_FIRE_TIME)");
        this.stmts.add("create index idx_"+prefix+"11 on "+prefix+"triggers(SCHED_NAME,TRIGGER_STATE,NEXT_FIRE_TIME)");
        this.stmts.add("create index idx_"+prefix+"12 on "+prefix+"triggers(SCHED_NAME,MISFIRE_INSTR,NEXT_FIRE_TIME)");
        this.stmts.add("create index idx_"+prefix+"13 on "+prefix+"triggers(SCHED_NAME,MISFIRE_INSTR,NEXT_FIRE_TIME,TRIGGER_STATE)");
        this.stmts.add("create index idx_"+prefix+"14 on "+prefix+"triggers(SCHED_NAME,MISFIRE_INSTR,NEXT_FIRE_TIME,TRIGGER_GROUP,TRIGGER_STATE)");
        this.stmts.add("create index idx_"+prefix+"15 on "+prefix+"fired_triggers(SCHED_NAME,INSTANCE_NAME)");
        this.stmts.add("create index idx_"+prefix+"16 on "+prefix+"fired_triggers(SCHED_NAME,INSTANCE_NAME,REQUESTS_RECOVERY)");
        this.stmts.add("create index idx_"+prefix+"17 on "+prefix+"fired_triggers(SCHED_NAME,JOB_NAME,JOB_GROUP)");
        this.stmts.add("create index idx_"+prefix+"18 on "+prefix+"fired_triggers(SCHED_NAME,JOB_GROUP)");
        this.stmts.add("create index idx_"+prefix+"19 on "+prefix+"fired_triggers(SCHED_NAME,TRIGGER_NAME,TRIGGER_GROUP)");
        this.stmts.add("create index idx_"+prefix+"20 on "+prefix+"fired_triggers(SCHED_NAME,TRIGGER_GROUP)");
    }
}
