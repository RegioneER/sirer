package it.cineca.siss.axmr3.doc.acl;

import it.cineca.siss.axmr3.authentication.IUser;
import org.hibernate.criterion.Criterion;
import org.hibernate.criterion.Restrictions;
import org.springframework.security.core.GrantedAuthority;

import java.util.LinkedList;
import java.util.List;

/**
 * Created with IntelliJ IDEA.
 * User: cin0562a
 * Date: 18/11/13
 * Time: 10:12
 * To change this template use File | Settings | File Templates.
 */
public class TemplatePolicy {

    protected boolean canView=false;
    protected boolean canCreate=false;
    protected boolean canUpdate=false;
    protected boolean canDelete=false;

    public TemplatePolicy(){}

    public TemplatePolicy(int value){
        if (value-Permission.DELETE.getValue()>=0) {
            canDelete=true;
            value-=Permission.DELETE.getValue();
        }
        if (value-Permission.UPDATE.getValue()>=0) {
            canUpdate=true;
            value-=Permission.UPDATE.getValue();
        }
        if (value-Permission.CREATE.getValue()>=0) {
            canCreate=true;
            value-=Permission.CREATE.getValue();
        }
        if (value-Permission.VIEW.getValue()>=0) {
            canView=true;
            value-=Permission.VIEW.getValue();
        }
    }

    public TemplatePolicy (String value){
        this(Integer.parseInt(value,2));
    }

    public void setPolicyByCommaSeparatedString(String permissions){
        String[] perms=permissions.split(",");
        for (int i=0;i<perms.length;i++){
            if (perms[i].equals("V")) this.setCanView(true);
            if (perms[i].equals("C")) this.setCanCreate(true);
            if (perms[i].equals("M")) this.setCanUpdate(true);
            if (perms[i].equals("E")) this.setCanDelete(true);
        }
    }

    public static TemplatePolicy createPolicyByCommaSeparatedString(String permissions){
        TemplatePolicy pol=new TemplatePolicy();
        pol.setPolicyByCommaSeparatedString(permissions);
        return pol;
    }

    public Criterion checkCriterion(String aclAlias, String containerAlias, IUser user){
        List<String> authNames=new LinkedList<String>();
        for (GrantedAuthority a:user.getAuthorities()){
            authNames.add(a.getAuthority());
            //it.cineca.siss.axmr3.log.Log.info(getClass(),"Autority: "+a.getAuthority());
        }
        //it.cineca.siss.axmr3.log.Log.info(getClass(),"Primo controllo: *");
        //it.cineca.siss.axmr3.log.Log.info(getClass(),"Secondo controllo: authority false e conteiner="+user.getUsername());
        //it.cineca.siss.axmr3.log.Log.info(getClass(),"Terzo controllo: authority false e conteiner lista authority");
        Criterion chk1=null;
        if (authNames!=null && authNames.size()>0){
            chk1= Restrictions.or(
                    Restrictions.and(
                            Restrictions.eq(containerAlias + ".container", user.getUsername()),
                            Restrictions.eq(containerAlias + ".authority", false)
                    ),
                    Restrictions.and(
                            Restrictions.eq(containerAlias + ".authority", true),
                            Restrictions.in(containerAlias + ".container", authNames)
                    )
            );
        }else {
            chk1=   Restrictions.and(
                    Restrictions.eq(containerAlias+".container", user.getUsername()),
                    Restrictions.eq(containerAlias+".authority", false)
            );
        }
        Criterion checkUser= Restrictions.or(Restrictions.eq(containerAlias+".container", "*"),chk1);
        return Restrictions.and(checkUser, Restrictions.ilike(aclAlias+".positionalAce", this.toLikeClause()));
    }

    public String toBinary(){
        return Integer.toBinaryString(toInt());
    }

    public String toLikeClause(){
        return "%"+Integer.toBinaryString(toInt()).replace('0', '_');
    }

    public int toInt(){
        int ret=0;
        if (canView) ret+=Permission.VIEW.getValue();
        if (canCreate) ret+=Permission.CREATE.getValue();
        if (canUpdate) ret+=Permission.UPDATE.getValue();
        if (canDelete) ret+=Permission.DELETE.getValue();
        return ret;
    }

    /**
     * chiamato tostring apposta per non fare l'override del toString qualora dovesse servire successivamente
     * @return stringa con VCME in base ai valori della policy
     */
    public String tostring(){
        String ret="";
        if (canView) ret+="V";
        if (canCreate) ret+="C";
        if (canUpdate) ret+="M";
        if (canDelete) ret+="E";
        return ret;
    }

    @Override
    public String toString() {
        return "Policy{" +
                "canView=" + canView +
                ", canCreate=" + canCreate +
                ", canUpdate=" + canUpdate +
                ", canDelete=" + canDelete +
                '}';
    }

    public boolean isCanCreate() {
        return canCreate;
    }

    public void setCanCreate(boolean canCreate) {
        this.canCreate = canCreate;
    }

    public boolean isCanDelete() {
        return canDelete;
    }

    public void setCanDelete(boolean canDelete) {
        this.canDelete = canDelete;
    }

    public boolean isCanUpdate() {
        return canUpdate;
    }

    public void setCanUpdate(boolean canUpdate) {
        this.canUpdate = canUpdate;
    }

    public boolean isCanView() {
        return canView;
    }

    public void setCanView(boolean canView) {
        this.canView = canView;
    }

}
