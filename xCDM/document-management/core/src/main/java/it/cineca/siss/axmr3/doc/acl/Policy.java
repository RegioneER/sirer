package it.cineca.siss.axmr3.doc.acl;

import it.cineca.siss.axmr3.authentication.IUser;
import org.hibernate.criterion.Criterion;
import org.hibernate.criterion.Restrictions;
import org.springframework.security.core.GrantedAuthority;

import java.util.LinkedList;
import java.util.List;

/**
 * Created with IntelliJ IDEA.
 * User: Carlo
 * Date: 29/08/13
 * Time: 10.03
 * To change this template use File | Settings | File Templates.
 */
public class Policy{

    protected boolean canView=false;
    protected boolean canCreate=false;
    protected boolean canUpdate=false;
    protected boolean canAddComment=false;
    protected boolean canModerate=false;
    protected boolean canDelete=false;
    protected boolean canChangePermission=false;
    protected boolean canAddChild=false;
    protected boolean canRemoveCheckOut=false;
    protected boolean canLaunchProcess=false;
    protected boolean canEnableTemplate=false;
    protected boolean canBrowse=false;
    private List<String> ftlTemplates;


    public List<String> getFtlTemplates() {
		return ftlTemplates;
	}

	public void setFtlTemplates(List<String> ftlTemplates) {
		this.ftlTemplates = ftlTemplates;
	}

	public boolean isCanBrowse() {
        return canBrowse;
    }

    public void setCanBrowse(boolean canBrowse) {
        this.canBrowse = canBrowse;
    }

    public Policy(){}

    public Policy(int value){
        if (value-Permission.BROWSE.getValue()>=0) {
            canBrowse=true;
            value-=Permission.BROWSE.getValue();
        }
        if (value-Permission.ENABLE_TEMPLATE.getValue()>=0) {
            canEnableTemplate=true;
            value-=Permission.ENABLE_TEMPLATE.getValue();
        }
        if (value-Permission.LAUNCH_PROCESS.getValue()>=0) {
            canLaunchProcess=true;
            value-=Permission.LAUNCH_PROCESS.getValue();
        }
        if (value-Permission.REMOVE_CHECKOUT.getValue()>=0) {
            canRemoveCheckOut=true;
            value-=Permission.REMOVE_CHECKOUT.getValue();
        }
        if (value-Permission.ADDCHILD.getValue()>=0) {
            canAddChild=true;
            value-=Permission.ADDCHILD.getValue();
        }
        if (value-Permission.CHANGE_PERMISSION.getValue()>=0) {
            canChangePermission=true;
            value-=Permission.CHANGE_PERMISSION.getValue();
        }
        if (value-Permission.DELETE.getValue()>=0) {
            canDelete=true;
            value-=Permission.DELETE.getValue();
        }
        if (value-Permission.MODERATE.getValue()>=0) {
            canModerate=true;
            value-=Permission.MODERATE.getValue();
        }
        if (value-Permission.ADDCOMMENT.getValue()>=0) {
            canAddComment=true;
            value-=Permission.ADDCOMMENT.getValue();
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

    public Policy (String value){
        this(Integer.parseInt(value,2));
    }

    public void setPolicyByCommaSeparatedString(String permissions){
        String[] perms=permissions.split(",");
        for (int i=0;i<perms.length;i++){
            if (perms[i].equals("V")) this.setCanView(true);
            if (perms[i].equals("C")) this.setCanCreate(true);
            if (perms[i].equals("M")) this.setCanUpdate(true);
            if (perms[i].equals("AC")) this.setCanAddComment(true);
            if (perms[i].equals("MC")) this.setCanModerate(true);
            if (perms[i].equals("E")) this.setCanDelete(true);
            if (perms[i].equals("MP")) this.setCanChangePermission(true);
            if (perms[i].equals("A")) this.setCanAddChild(true);
            if (perms[i].equals("R")) this.setCanRemoveCheckOut(true);
            if (perms[i].equals("P")) this.setCanLaunchProcess(true);
            if (perms[i].equals("ET")) this.setCanEnableTemplate(true);
            if (perms[i].equals("B")) this.setCanBrowse(true);
        }
    }

    public static Policy createPolicyByCommaSeparatedString(String permissions){
        Policy pol=new Policy();
        pol.setPolicyByCommaSeparatedString(permissions);
        return pol;
    }

    public boolean isCanEnableTemplate() {
        return canEnableTemplate;
    }

    public void setCanEnableTemplate(boolean canEnableTemplate) {
        this.canEnableTemplate = canEnableTemplate;
    }

    public boolean isCanLaunchProcess() {
        return canLaunchProcess;
    }

    public void setCanLaunchProcess(boolean canLaunchProcess) {
        this.canLaunchProcess = canLaunchProcess;
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
            chk1=Restrictions.or(
                    Restrictions.and(
                            Restrictions.eq(containerAlias+".container", user.getUsername()),
                            Restrictions.eq(containerAlias+".authority", false)
                    ),
                    Restrictions.and(
                            Restrictions.eq(containerAlias+".authority", true),
                            Restrictions.in(containerAlias+".container", authNames)
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
        if (canAddComment) ret+=Permission.ADDCOMMENT.getValue();
        if (canModerate) ret+=Permission.MODERATE.getValue();
        if (canDelete) ret+=Permission.DELETE.getValue();
        if (canChangePermission) ret+=Permission.CHANGE_PERMISSION.getValue();
        if (canAddChild) ret+=Permission.ADDCHILD.getValue();
        if (canRemoveCheckOut) ret+=Permission.REMOVE_CHECKOUT.getValue();
        if (canLaunchProcess) ret+=Permission.LAUNCH_PROCESS.getValue();
        if (canEnableTemplate) ret+=Permission.ENABLE_TEMPLATE.getValue();
        if (canBrowse) ret+=Permission.BROWSE.getValue();
        return ret;
    }



    public String toCommaSeparatedString() {
        String stringa="";
        if(canView){
            stringa+="V,";
        }
        if(canUpdate){
            stringa+="M,";
        }
        if(canAddComment){
            stringa+="AC,";
        }
        if(canModerate){
            stringa+="MC,";
        }
        if(canDelete){
            stringa+="E,";
        }
        if(canChangePermission){
            stringa+="MP,";
        }
        if(canAddChild){
            stringa+="A,";
        }
        if(canRemoveCheckOut){
            stringa+="R,";
        }
        if(canLaunchProcess){
            stringa+="P,";
        }
        if(canEnableTemplate){
            stringa+="ET,";
        }
        if(canBrowse){
            stringa+="B";
        }
        stringa= stringa.replace(",$","");

        return stringa;
    }

    public String toString() {
        return "Policy{" +
                "canView=" + canView +
                ", canCreate=" + canCreate +
                ", canUpdate=" + canUpdate +
                ", canAddComment=" + canAddComment +
                ", canModerate=" + canModerate +
                ", canDelete=" + canDelete +
                ", canChangePermission=" + canChangePermission +
                ", canAddChild=" + canAddChild +
                ", canRemoveCheckOut=" + canRemoveCheckOut +
                ", canLaunchProcess=" + canLaunchProcess +
                ", canEnableTemplate=" + canEnableTemplate+
                ", canBrowse=" + canBrowse+
                ", valore intero="+toInt()+
                ", valore binario="+toBinary()+
                '}';
    }


    public boolean isCanAddChild() {
        return canAddChild;
    }

    public void setCanAddChild(boolean canAddChild) {
        this.canAddChild = canAddChild;
    }

    public boolean isCanAddComment() {
        return canAddComment;
    }

    public void setCanAddComment(boolean canAddComment) {
        this.canAddComment = canAddComment;
    }

    public boolean isCanChangePermission() {
        return canChangePermission;
    }

    public void setCanChangePermission(boolean canChangePermission) {
        this.canChangePermission = canChangePermission;
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

    public boolean isCanModerate() {
        return canModerate;
    }

    public void setCanModerate(boolean canModerate) {
        this.canModerate = canModerate;
    }

    public boolean isCanRemoveCheckOut() {
        return canRemoveCheckOut;
    }

    public void setCanRemoveCheckOut(boolean canRemoveCheckOut) {
        this.canRemoveCheckOut = canRemoveCheckOut;
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
