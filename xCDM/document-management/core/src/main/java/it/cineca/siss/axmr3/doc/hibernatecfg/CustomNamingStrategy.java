package it.cineca.siss.axmr3.doc.hibernatecfg;

import org.hibernate.cfg.DefaultNamingStrategy;
//import org.hibernate.boot.model.naming.ImplicitNamingStrategy

public class CustomNamingStrategy extends DefaultNamingStrategy {

    private String prefix;

    public String getPrefix() {
        return prefix;
    }

    public void setPrefix(String prefix) {
        this.prefix = prefix;
    }


    @Override
    public String tableName(String tableName) {
        return super.tableName(tableName).replaceAll("DOC_", this.prefix+"_");
    }

    @Override
    public String classToTableName(String className) {
        return super.classToTableName(className).replaceAll("DOC_", this.prefix+"_");
    }

    @Override
    public String collectionTableName(String ownerEntity, String ownerEntityTable, String associatedEntity, String associatedEntityTable, String propertyName) {
        return super.collectionTableName(ownerEntity, ownerEntityTable, associatedEntity, associatedEntityTable, propertyName).replaceAll("DOC_", this.prefix+"_");
    }

    @Override
    public String logicalCollectionTableName(String tableName, String ownerEntityTable, String associatedEntityTable, String propertyName) {
        return super.logicalCollectionTableName(tableName, ownerEntityTable, associatedEntityTable, propertyName).replaceAll("DOC_", this.prefix+"_");
    }




}
