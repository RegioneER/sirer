package it.cineca.siss.axmr3.doc.types;

import org.activiti.engine.FormService;
import org.activiti.engine.ProcessEngine;
import org.activiti.engine.RepositoryService;
import org.activiti.engine.RuntimeService;
import org.activiti.engine.repository.ProcessDefinition;
import org.activiti.engine.runtime.ProcessInstance;
import org.activiti.engine.runtime.ProcessInstanceQuery;

import java.io.Serializable;
import java.util.LinkedList;
import java.util.List;
import java.util.Map;

/**
 * Created with IntelliJ IDEA.
 * User: cin0562a
 * Date: 10/11/13
 * Time: 12:32
 * To change this template use File | Settings | File Templates.
 */
public class Task implements Serializable{

    private String id;
    private String name;
    private String taskKey;
    private String type;
    private String assignee;
    private Map<String, Object> processVariables;
    private Map<String, Object> taskVariables;
    private List<TaskFormProperty> taskFormProperties;
    private String processName;
    private String processKey;
    private String processId;
    private String processInstanceId;

    public List<TaskFormProperty> getTaskFormProperties() {
        return taskFormProperties;
    }

    public void setTaskFormProperties(List<TaskFormProperty> taskFormProperties) {
        this.taskFormProperties = taskFormProperties;
    }

    public String getTaskKey() {
        return taskKey;
    }

    public void setTaskKey(String taskKey) {
        this.taskKey = taskKey;
    }

    public String getProcessName() {
        return processName;
    }

    public void setProcessName(String processName) {
        this.processName = processName;
    }

    public String getProcessKey() {
        return processKey;
    }

    public void setProcessKey(String processKey) {
        this.processKey = processKey;
    }

    public String getProcessId() {
        return processId;
    }

    public void setProcessId(String processId) {
        this.processId = processId;
    }

    public String getProcessInstanceId() {
        return processInstanceId;
    }

    public void setProcessInstanceId(String processInstanceId) {
        this.processInstanceId = processInstanceId;
    }

    public String getId() {
        return id;
    }

    public void setId(String id) {
        this.id = id;
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public String getType() {
        return type;
    }

    public void setType(String type) {
        this.type = type;
    }

    public String getAssignee() {
        return assignee;
    }

    public void setAssignee(String assignee) {
        this.assignee = assignee;
    }

    public Map<String, Object> getProcessVariables() {
        return processVariables;
    }

    public void setProcessVariables(Map<String, Object> processVariables) {
        this.processVariables = processVariables;
    }

    public Map<String, Object> getTaskVariables() {
        return taskVariables;
    }

    public void setTaskVariables(Map<String, Object> taskVariables) {
        this.taskVariables = taskVariables;
    }

    public static Task fromActivitiTask(org.activiti.engine.task.Task t, ProcessEngine engine){
        Task task=new Task();
        task.setId(t.getId());
        if (t.getTaskDefinitionKey() != null && !t.getTaskDefinitionKey().isEmpty())
            task.setTaskKey(t.getTaskDefinitionKey());
        task.setName(t.getName());
        task.setProcessVariables(t.getProcessVariables());
        task.setTaskVariables(t.getTaskLocalVariables());
        RepositoryService processRepositoryService = engine.getRepositoryService();
        FormService formService = engine.getFormService();
        task.taskFormProperties=TaskFormProperty.fromActivitiFormPropertyList(formService.getTaskFormData(t.getId()).getFormProperties());
        task.processId=t.getProcessDefinitionId();
        task.processInstanceId=t.getProcessInstanceId();
        ProcessDefinition process = processRepositoryService.getProcessDefinition(t.getProcessDefinitionId());
        task.processKey=process.getKey();
        task.processName=process.getName();
        if (t.getName().startsWith("alert-")){
            task.setType("Alert");
        }else if (task.getTaskFormProperties().size()>0){
            task.setType("Form");
        }else {
            task.setType("Confirm");
        }
        return task;
    }

    public static List<Task> fromActivitiTaskLisk(List<org.activiti.engine.task.Task> tasks, ProcessEngine engine){
        List<Task> ret=new LinkedList<Task>();
        for (org.activiti.engine.task.Task t:tasks){
            ret.add(fromActivitiTask(t, engine));
        }
        return ret;
    }


}
