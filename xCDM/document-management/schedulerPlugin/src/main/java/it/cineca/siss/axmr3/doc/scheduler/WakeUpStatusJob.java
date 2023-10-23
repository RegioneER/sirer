package it.cineca.siss.axmr3.doc.scheduler;

import org.apache.log4j.Logger;
import org.quartz.JobDetail;
import org.quartz.Scheduler;
import org.quartz.SimpleTrigger;
import org.springframework.beans.factory.InitializingBean;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.scheduling.quartz.SchedulerFactoryBean;

import static org.quartz.JobBuilder.newJob;
import static org.quartz.SimpleScheduleBuilder.simpleSchedule;
import static org.quartz.TriggerBuilder.newTrigger;

/**
 * Created by Carlo on 14/02/2016.
 */
public class WakeUpStatusJob implements InitializingBean{

    @Autowired
    protected SchedulerFactoryBean fb;

    public SchedulerFactoryBean getFb() {
        return fb;
    }

    public void setFb(SchedulerFactoryBean fb) {
        this.fb = fb;
    }

    protected String instanceName;

    public String getInstanceName() {
        return instanceName;
    }

    public void setInstanceName(String instanceName) {
        this.instanceName = instanceName;
    }

    public void afterPropertiesSet() throws Exception {
        Scheduler sched = fb.getScheduler();

        sched.start();
        StatusJob.instanceName=instanceName;
        JobDetail job = newJob(StatusJob.class)
                .withIdentity("WakeUpStatusJob", "Status")
                .build();

        SimpleTrigger trigger = newTrigger()
                .withIdentity("WakeUpStatusJob", "Status")
                .startNow()
                .withSchedule(simpleSchedule()
                        .withIntervalInSeconds(60)
                        .repeatForever())
                .build();
        if (!sched.checkExists(job.getKey())) {
            Logger.getLogger(this.getClass()).info("Scheduling Job "+job.getKey()+" ...");

            sched.scheduleJob(job, trigger);
        }else {
            Logger.getLogger(this.getClass()).info("Job "+job.getKey()+" already scheduled");
        }
    }
}
