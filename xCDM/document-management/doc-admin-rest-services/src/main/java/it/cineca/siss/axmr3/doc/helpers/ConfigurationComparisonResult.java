package it.cineca.siss.axmr3.doc.helpers;

import it.cineca.siss.axmr3.doc.entities.*;
import it.cineca.siss.axmr3.doc.web.services.AdminService;
import org.w3c.dom.Element;

import java.util.Collection;
import java.util.LinkedList;
import java.util.List;

/**
 * Created by cin0562a on 06/10/14.
 */
public class ConfigurationComparisonResult {

    protected ComparisonResultType comparisonResultType;
    protected String scope;
    protected String objName;
    protected List<ConfigurationComparisonResult> subComparisons;
    protected ComparisonResultType cTotal;

    public ComparisonResultType getcTotal() {
        return cTotal;
    }

    public void setcTotal(ComparisonResultType cTotal) {
        this.cTotal = cTotal;
    }

    public String getObjName() {
        return objName;
    }

    public void setObjName(String objName) {
        this.objName = objName;
    }

    public ConfigurationComparisonResult(String scope) {
        this.scope = scope;
    }

    public ComparisonResultType getComparisonResultType() {
        return comparisonResultType;
    }

    public void setComparisonResultType(ComparisonResultType comparisonResultType) {
        this.comparisonResultType = comparisonResultType;
    }

    public String getScope() {
        return scope;
    }

    public void setScope(String scope) {
        this.scope = scope;
    }

    public List<ConfigurationComparisonResult> getSubComparisons() {
        return subComparisons;
    }

    public void setSubComparisons(List<ConfigurationComparisonResult> subComparisons) {
        this.subComparisons = subComparisons;
    }

    public void addSubComparison(ConfigurationComparisonResult sub) {
        if (subComparisons == null) subComparisons = new LinkedList<ConfigurationComparisonResult>();
        subComparisons.add(sub);
    }

    public static ConfigurationComparisonResult typeCompare(Element node, AdminService adminService) {
        return typeCompare(ConfigurationUtils.typeFromXmlNode(node), adminService);
    }

    public static ConfigurationComparisonResult typeCompare(ElementType t1, AdminService adminService) {
        ElementType t2 = adminService.igetElementTypeByTypeId(t1.getTypeId());
        ConfigurationComparisonResult res = new ConfigurationComparisonResult("Type");
        res.setObjName(t1.getTypeId());
        if (t2 == null) {
            res.setComparisonResultType(ComparisonResultType.ADDED);
            return res;
        }
        res.setComparisonResultType(ComparisonResultType.EQ);
        boolean equal = true;
        res.addSubComparison(checkObject("typeAttribute", "isCheckOutEnabled", t1.isCheckOutEnabled(), t2.isCheckOutEnabled()));
        res.addSubComparison(checkObject("typeAttribute", "isContainer", t1.isContainer(), t2.isContainer()));
        res.addSubComparison(checkObject("typeAttribute", "isDeleted", t1.isDeleted(), t2.isDeleted()));
        res.addSubComparison(checkObject("typeAttribute", "isDraftable", t1.isDraftable(), t2.isDraftable()));
        res.addSubComparison(checkObject("typeAttribute", "isHasFileAttached", t1.isHasFileAttached(), t2.isHasFileAttached()));
        res.addSubComparison(checkObject("typeAttribute", "isNoFileinfo", t1.isNoFileinfo(), t2.isNoFileinfo()));
        res.addSubComparison(checkObject("typeAttribute", "isRootAble", t1.isRootAble(), t2.isRootAble()));
        res.addSubComparison(checkObject("typeAttribute", "isSearchable", t1.isSearchable(), t2.isSearchable()));
        res.addSubComparison(checkObject("typeAttribute", "isSelfRecursive", t1.isSelfRecursive(), t2.isSelfRecursive()));
        res.addSubComparison(checkObject("typeAttribute", "isSortable", t1.isSortable(), t2.isSortable()));
        if (t1.getTitleField() != null && t2.getTitleField() != null) {
            res.addSubComparison(checkObject("typeAttribute", "getTitleFieldName", t1.getTitleField().getName(), t2.getTitleField().getName()));
            res.addSubComparison(checkObject("typeAttribute", "getTitleFieldTemplateName", t1.getTitleField().getTemplate().getName(), t2.getTitleField().getTemplate().getName()));
        } else {
            if (t1.getTitleField() == null || t2.getTitleField() == null) {
                if (t1.getTitleField() != null) {
                    ConfigurationComparisonResult s1 = new ConfigurationComparisonResult("typeAttribute");
                    s1.setObjName("getTitleFieldName");
                    s1.setComparisonResultType(ComparisonResultType.ADDED);
                    ConfigurationComparisonResult s2 = new ConfigurationComparisonResult("typeAttribute");
                    s2.setObjName("getTitleFieldTemplateName");
                    s2.setComparisonResultType(ComparisonResultType.ADDED);
                    res.addSubComparison(s1);
                    res.addSubComparison(s2);
                }
                if (t2.getTitleField() != null) {
                    ConfigurationComparisonResult s1 = new ConfigurationComparisonResult("typeAttribute");
                    s1.setObjName("getTitleFieldName");
                    s1.setComparisonResultType(ComparisonResultType.DELETED);
                    ConfigurationComparisonResult s2 = new ConfigurationComparisonResult("typeAttribute");
                    s2.setObjName("getTitleFieldTemplateName");
                    s2.setComparisonResultType(ComparisonResultType.DELETED);
                    res.addSubComparison(s1);
                    res.addSubComparison(s2);
                }
            }
        }

        res.addSubComparison(checkObject("typeAttribute", "getFtlDetailTemplate", t1.getFtlDetailTemplate(), t2.getFtlDetailTemplate()));
        res.addSubComparison(checkObject("typeAttribute", "getFtlFormTemplate", t1.getFtlFormTemplate(), t2.getFtlFormTemplate()));
        res.addSubComparison(checkObject("typeAttribute", "getFtlRowTemplate", t1.getFtlRowTemplate(), t2.getFtlRowTemplate()));
        if (t2.getGroupUpLevel() == null) t2.setGroupUpLevel(Long.parseLong("0"));
        res.addSubComparison(checkObject("typeAttribute", "getGroupUpLevel", t1.getGroupUpLevel(), t2.getGroupUpLevel()));
        res.addSubComparison(checkObject("typeAttribute", "getTitleRegex", t1.getTitleRegex(), t2.getTitleRegex()));
        if (t1.getAllowedChilds() != null && t1.getAllowedChilds().size() > 0) {
            for (ElementType child1 : t1.getAllowedChilds()) {
                boolean found = false;
                if (t2.getAllowedChilds() != null && t2.getAllowedChilds().size() > 0) {
                    for (ElementType child2 : t2.getAllowedChilds()) {
                        if (child1.getTypeId().equals(t2.getTypeId())) found = true;
                    }
                }
                if (!found) {
                    ConfigurationComparisonResult s1 = new ConfigurationComparisonResult("typeChildren");
                    s1.setObjName(child1.getTypeId());
                    s1.setComparisonResultType(ComparisonResultType.ADDED);
                } else {
                    ConfigurationComparisonResult s1 = new ConfigurationComparisonResult("typeChildren");
                    s1.setObjName(child1.getTypeId());
                    s1.setComparisonResultType(ComparisonResultType.EQ);
                }
            }
        }
        if (t2.getAllowedChilds() != null && t2.getAllowedChilds().size() > 0) {
            for (ElementType child2 : t2.getAllowedChilds()) {
                boolean found = false;
                if (t1.getAllowedChilds() != null && t1.getAllowedChilds().size() > 0) {
                    for (ElementType child1 : t1.getAllowedChilds()) {
                        if (child1.getTypeId().equals(t2.getTypeId())) found = true;
                    }
                }
                if (!found) {
                    ConfigurationComparisonResult s1 = new ConfigurationComparisonResult("typeChildren");
                    s1.setObjName(child2.getTypeId());
                    s1.setComparisonResultType(ComparisonResultType.DELETED);
                }
            }
        }

        if (t1.getAssociatedTemplates() != null && t1.getAssociatedTemplates().size() > 0) {
            for (ElementTypeAssociatedTemplate child1 : t1.getAssociatedTemplates()) {
                boolean found = false;
                if (t2.getAssociatedTemplates() != null && t2.getAssociatedTemplates().size() > 0) {
                    for (ElementTypeAssociatedTemplate child2 : t2.getAssociatedTemplates()) {
                        if (child1.getMetadataTemplate().getName().equals(child2.getMetadataTemplate().getName())) {
                            found = true;
                            ConfigurationComparisonResult s1 = new ConfigurationComparisonResult("typeAssociatedTemplate");
                            s1.setObjName(child1.getMetadataTemplate().getName());
                            s1.setComparisonResultType(ComparisonResultType.EQ);
                            s1.addSubComparison(checkObject("typeAssociatedTemplateAttribute", "isEnabled", child1.isEnabled(), child2.isEnabled()));
                            if (!tplAclListCompare(child1.getTemplateAcls(), child2.getTemplateAcls())) {
                                s1.setComparisonResultType(ComparisonResultType.UPDATED);
                            }
                        }
                    }
                }
                if (!found) {
                    ConfigurationComparisonResult s1 = new ConfigurationComparisonResult("typeAssociatedTemplate");
                    s1.setObjName(child1.getMetadataTemplate().getName());
                    s1.setComparisonResultType(ComparisonResultType.ADDED);
                }
            }
        }
        if (t2.getAssociatedTemplates() != null && t2.getAssociatedTemplates().size() > 0) {
            for (ElementTypeAssociatedTemplate child2 : t2.getAssociatedTemplates()) {
                boolean found = false;
                if (t1.getAssociatedTemplates() != null && t1.getAssociatedTemplates().size() > 0) {
                    for (ElementTypeAssociatedTemplate child1 : t1.getAssociatedTemplates()) {
                        if (child1.getMetadataTemplate().getName().equals(child2.getMetadataTemplate().getName())) {
                            found = true;
                        }
                    }
                }
                if (!found) {
                    ConfigurationComparisonResult s1 = new ConfigurationComparisonResult("typeAssociatedTemplate");
                    s1.setObjName(child2.getMetadataTemplate().getName());
                    s1.setComparisonResultType(ComparisonResultType.DELETED);
                }
            }
        }
        res.isUpdated();
        return res;
    }

    public boolean isUpdated() {
        cTotal = ComparisonResultType.EQ;
        if (!comparisonResultType.equals(ComparisonResultType.EQ)) cTotal = ComparisonResultType.UPDATED;
        if (subComparisons != null && subComparisons.size() > 0) {
            for (ConfigurationComparisonResult c : subComparisons) {
                if (c.isUpdated()) cTotal = ComparisonResultType.UPDATED;
            }
        }
        if (cTotal.equals(ComparisonResultType.UPDATED)) return true;
        else return false;
    }

    public static ConfigurationComparisonResult checkObject(String scope, String obj, Object s1, Object s2) {
        ConfigurationComparisonResult res = new ConfigurationComparisonResult(scope);
        res.setObjName(obj);
        res.setComparisonResultType(ComparisonResultType.EQ);
        if (s1 != null || s2 != null) {
            if (s1 == null) res.setComparisonResultType(ComparisonResultType.ADDED);
            if (s2 == null) res.setComparisonResultType(ComparisonResultType.DELETED);
            if (s1 != null && !s1.equals(s2)) res.setComparisonResultType(ComparisonResultType.UPDATED);
        }
        return res;
    }

    public static boolean compareFullAclContainer(AclContainer c1, AclContainer c2) {
        boolean equal = true;
        equal = equal && c1.getContainer().equals(c2.getContainer());
        equal = equal && c1.isAuthority() == c2.isAuthority();
        return equal;
    }


    public static boolean compareFullAcl(Acl a1, Acl a2) {
        ConfigurationComparisonResult res = new ConfigurationComparisonResult("Acl");
        boolean equal = true;
        equal = equal && checkObject("Acl.attribute", "name", a1.getPredifinedPolicy().getName(), a2.getPredifinedPolicy().getName()).getComparisonResultType().equals(ComparisonResultType.EQ);
        equal = equal && checkObject("Acl.attribute", "positionlAce", a1.getPositionalAce(), a2.getPositionalAce()).getComparisonResultType().equals(ComparisonResultType.EQ);
        equal = equal && checkObject("Acl.attribute", "policyValue", a1.getPolicyValue(), a2.getPolicyValue()).getComparisonResultType().equals(ComparisonResultType.EQ);
        equal = equal && checkObject("Acl.attribute", "detailTempalte", a1.getDetailTemplate(), a2.getDetailTemplate()).getComparisonResultType().equals(ComparisonResultType.EQ);
        if (a1.getContainers() != null && a2.getContainers() != null) {
            equal = equal && a1.getContainers().size() == a2.getContainers().size();
            for (AclContainer c1 : a1.getContainers()) {
                boolean found = false;
                for (AclContainer c2 : a2.getContainers()) {
                    if (compareFullAclContainer(c1, c2)) found = true;
                }
                equal = equal && found;
            }
            for (AclContainer c2 : a2.getContainers()) {
                boolean found = false;
                for (AclContainer c1 : a1.getContainers()) {
                    if (compareFullAclContainer(c1, c2)) found = true;
                }
                equal = equal && found;
            }
        } else {
            if (a1.getContainers() != null || a2.getContainers() != null) equal = false;
        }
        return equal;
    }

    public static boolean aclListCompare(List<Acl> l1, List<Acl> l2) {
        boolean equal = true;
        for (Acl a1 : l1) {
            boolean found = false;
            for (Acl a2 : l2) {
                if (compareFullAcl(a1, a2)) found = true;
            }
            equal = equal && found;
        }
        for (Acl a2 : l2) {
            boolean found = false;
            for (Acl a1 : l1) {
                if (compareFullAcl(a1, a2)) found = true;
            }
            equal = equal && found;
        }
        return equal;
    }

    public static boolean compareFullTplAclContainer(TemplateAclContainer c1, TemplateAclContainer c2) {
        boolean equal = true;
        equal = equal && c1.getContainer().equals(c2.getContainer());
        equal = equal && c1.isAuthority() == c2.isAuthority();
        return equal;
    }


    public static boolean compareFullTplAcl(TemplateAcl a1, TemplateAcl a2) {
        ConfigurationComparisonResult res = new ConfigurationComparisonResult("Acl");
        boolean equal = true;
        equal = equal && checkObject("Acl.attribute", "positionlAce", a1.getPositionalAce(), a2.getPositionalAce()).getComparisonResultType().equals(ComparisonResultType.EQ);
        equal = equal && checkObject("Acl.attribute", "policyValue", a1.getPolicyValue(), a2.getPolicyValue()).getComparisonResultType().equals(ComparisonResultType.EQ);
        if (a1.getContainers() != null && a2.getContainers() != null) {
            equal = equal && a1.getContainers().size() == a2.getContainers().size();
            for (TemplateAclContainer c1 : a1.getContainers()) {
                boolean found = false;
                for (TemplateAclContainer c2 : a2.getContainers()) {
                    if (compareFullTplAclContainer(c1, c2)) found = true;
                }
                equal = equal && found;
            }
            for (TemplateAclContainer c2 : a2.getContainers()) {
                boolean found = false;
                for (TemplateAclContainer c1 : a1.getContainers()) {
                    if (compareFullTplAclContainer(c1, c2)) found = true;
                }
                equal = equal && found;
            }
        } else {
            if (a1.getContainers() != null || a2.getContainers() != null) equal = false;
        }
        return equal;
    }

    public static boolean tplAclListCompare(Collection<TemplateAcl> l1, Collection<TemplateAcl> l2) {
        boolean equal = true;
        for (TemplateAcl a1 : l1) {
            boolean found = false;
            for (TemplateAcl a2 : l2) {
                if (compareFullTplAcl(a1, a2)) found = true;
            }
            equal = equal && found;
        }
        for (TemplateAcl a2 : l2) {
            boolean found = false;
            for (TemplateAcl a1 : l1) {
                if (compareFullTplAcl(a1, a2)) found = true;
            }
            equal = equal && found;
        }
        return equal;
    }

}
