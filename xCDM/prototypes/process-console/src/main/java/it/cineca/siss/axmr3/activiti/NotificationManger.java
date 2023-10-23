package it.cineca.siss.axmr3.activiti;

import com.vaadin.ui.Window;
import org.activiti.explorer.NotificationManager;

import java.text.MessageFormat;

/**
 * Created with IntelliJ IDEA.
 * User: cin0562a
 * Date: 28/10/13
 * Time: 10:18
 * To change this template use File | Settings | File Templates.
 */
public class NotificationManger extends NotificationManager {

     public void ShowMessage(String message){
         mainWindow.showNotification("ProcessMessage", message);
     }

}
