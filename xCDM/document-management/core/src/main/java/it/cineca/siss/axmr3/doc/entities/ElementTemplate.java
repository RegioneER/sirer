package it.cineca.siss.axmr3.doc.entities;

import it.cineca.siss.axmr3.authentication.IAuthority;
import it.cineca.siss.axmr3.authentication.IUser;
import it.cineca.siss.axmr3.doc.acl.TemplatePolicy;

import javax.persistence.*;
import java.util.Collection;
import java.util.LinkedList;
import java.util.List;

/**
 * Created with IntelliJ IDEA.
 * User: cin0562a
 * Date: 18/11/13
 * Time: 11:21
 * To change this template use File | Settings | File Templates.
 */
@Entity
@Table(name = "DOC_OBJ_TEMPLATE")
public class ElementTemplate extends BaseMDValueEntity {

    @ManyToOne
    @JoinColumn(name = "TEMPLATE_ID")
    private MetadataTemplate metadataTemplate;
    @OneToMany(fetch = FetchType.LAZY, mappedBy = "elementTemplate")
    protected Collection<TemplateAcl> templateAcls;
    @Column(name = "ENABLED")
    private boolean enabled;

    public MetadataTemplate getMetadataTemplate() {
        return metadataTemplate;
    }

    public void setMetadataTemplate(MetadataTemplate metadataTemplate) {
        this.metadataTemplate = metadataTemplate;
    }

    public boolean isEnabled() {
        return enabled;
    }

    public void setEnabled(boolean enabled) {
        this.enabled = enabled;
    }

    public TemplatePolicy getUserPolicy(IUser user, Element el) {
        List<String> userAuths = new LinkedList<String>();
        for (IAuthority auth : user.getAuthorities()) {
            userAuths.add(auth.getAuthority());
        }
        TemplatePolicy pol = new TemplatePolicy();
        if (templateAcls == null || templateAcls.size() == 0) {
            if (el.getUserPolicy(user).isCanUpdate()) {
                pol.setCanCreate(true);
                pol.setCanDelete(true);
                pol.setCanUpdate(true);
            }
            if (el.getUserPolicy(user).isCanView()) {
                pol.setCanView(true);
            }
        } else {
            for (TemplateAcl acl : templateAcls) {
                boolean isApplicable = false;
                for (TemplateAclContainer container : acl.getContainers()) {
                    if (!container.isAuthority() && container.getContainer().equals("*")) isApplicable = true;
                    if (container.isAuthority()) {
                        for (String auth : userAuths)
                            if (container.getContainer().equals(auth)) {
                                isApplicable = true;
                            }
                    }
                    if (!container.isAuthority() && user.getUsername().equals(container.getContainer()))
                        isApplicable = true;
                }
                if (isApplicable) {
                    TemplatePolicy thisPol = new TemplatePolicy(acl.getPolicyValue());
                    if (!pol.isCanCreate()) pol.setCanCreate(thisPol.isCanCreate());
                    if (!pol.isCanDelete()) pol.setCanDelete(thisPol.isCanDelete());
                    if (!pol.isCanUpdate()) pol.setCanUpdate(thisPol.isCanUpdate());
                    if (!pol.isCanView()) pol.setCanView(thisPol.isCanView());
                } else {
                    //Fallback intelligente in visualizzazione (se posso vedere l'elemento) se oggetto presente nella lista di oggetti configurati in questo modo nel file properties
                    if (el.isFallbackTemplatePolicy()) {
                        //Verifico solo la visualizzazione, non faccio nulla per modifica ecc...
                        if (el.getUserPolicy(user).isCanView()) {
                            pol.setCanView(true);
                        }
                    }
                }
            }
        }
        return pol;

    }

    public Collection<TemplateAcl> getTemplateAcls() {
        return templateAcls;
    }

    public void setTemplateAcls(Collection<TemplateAcl> templateAcls) {
        this.templateAcls = templateAcls;
    }
}
