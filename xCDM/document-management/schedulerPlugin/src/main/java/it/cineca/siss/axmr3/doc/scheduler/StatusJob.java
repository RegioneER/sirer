package it.cineca.siss.axmr3.doc.scheduler;

import org.quartz.DisallowConcurrentExecution;
import org.quartz.Job;
import org.quartz.JobExecutionContext;
import org.quartz.JobExecutionException;

/**
 * Created by Carlo on 14/02/2016.
 */
@DisallowConcurrentExecution
public class StatusJob implements Job {

    public static String instanceName;

    public void execute(JobExecutionContext jobExecutionContext) throws JobExecutionException {}
}
