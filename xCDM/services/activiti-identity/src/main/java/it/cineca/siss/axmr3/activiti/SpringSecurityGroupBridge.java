package it.cineca.siss.axmr3.activiti;

import it.cineca.siss.axmr3.authentication.IAuthority;
import org.activiti.engine.identity.Group;

/**
 * Created with IntelliJ IDEA.
 * User: cin0562a
 * Date: 20/10/13
 * Time: 10:38
 * To change this template use File | Settings | File Templates.
 */
public class SpringSecurityGroupBridge implements Group {

    protected String id;
    protected String name;
    protected String type;

    public SpringSecurityGroupBridge(IAuthority auth){
        this.id=auth.getAuthority();
        this.name=auth.getAuthority();
        this.type=auth.getAuthority();

    }

    public String getId() {
        return id;
    }

    public void setId(String id) {
       this.id=id;
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name=name;
    }

    public String getType() {
        return this.type;
    }

    public void setType(String string) {
        this.type=string;

    }
}
