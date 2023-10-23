package it.cineca.siss.axmr3.doc.entities;

import it.cineca.siss.axmr3.authentication.IAuthority;
import it.cineca.siss.axmr3.authentication.IUser;
import it.cineca.siss.axmr3.doc.acl.TemplatePolicy;
import org.codehaus.jackson.annotate.JsonIgnore;

import javax.persistence.*;
import java.util.Collection;
import java.util.HashMap;
import java.util.LinkedList;
import java.util.List;

/**
 * Created with IntelliJ IDEA.
 * User: Carlo
 * Date: 03/09/13
 * Time: 10.06
 * To change this template use File | Settings | File Templates.
 */
@Entity
@Table(name = "DOC_TYPE_MD_TEMPLATE")
public class ElementTypeAssociatedTemplate extends BaseModelEntity {

    @ManyToOne
    @JoinColumn(name = "TYPE_ID", nullable = false)
    private ElementType type;
    @ManyToOne
    @JoinColumn(name = "TEMPLATE_ID", nullable = false)
    private MetadataTemplate metadataTemplate;
    @Column(name = "ENABLED")
    private boolean enabled;
    @OneToMany(fetch = FetchType.LAZY, mappedBy = "elementTypeAssociatedTemplate")
    private Collection<TemplateAcl> templateAcls;

    @JsonIgnore
    public ElementType getType() {
        return type;
    }

    public void setType(ElementType type) {
        this.type = type;
    }

    public Collection<TemplateAcl> getTemplateAcls() {
        return templateAcls;
    }

    public void setTemplateAcls(Collection<TemplateAcl> templateAcls) {
        this.templateAcls = templateAcls;
    }

    @JsonIgnore
    public MetadataTemplate getMetadataTemplate() {
        return metadataTemplate;
    }

    public String getMetadataTemplateName(){
        return metadataTemplate.getName();
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

    public Long getMetadataId(){
        return this.metadataTemplate.getId();
    }

    @JsonIgnore
    public TemplatePolicy getUserPolicy(IUser user, ElementType type) {
        List<String> userAuths = new LinkedList<String>();
        for (IAuthority auth : user.getAuthorities()) {
            userAuths.add(auth.getAuthority());
        }
        TemplatePolicy pol = new TemplatePolicy();
        if (templateAcls == null || templateAcls.size() == 0) {
            if (type.getUserPolicy(user).isCanUpdate()) {
                pol.setCanCreate(true);
                pol.setCanDelete(true);
                pol.setCanUpdate(true);
            }
            if (type.getUserPolicy(user).isCanView()) {
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

                }
            }
        }
        return pol;
    }

    @JsonIgnore
    public HashMap<String, TemplateAcl> getTemplateAclsMap() {
        HashMap<String, TemplateAcl> ret = new HashMap<String, TemplateAcl>();
        if (templateAcls != null) {
            for (TemplateAcl currAcl : templateAcls) {
                if (currAcl.getContainers().iterator().hasNext()) {
                    ret.put(currAcl.getContainers().iterator().next().getContainer(), currAcl);
                }
            }
        }
        return ret;
    }

}
