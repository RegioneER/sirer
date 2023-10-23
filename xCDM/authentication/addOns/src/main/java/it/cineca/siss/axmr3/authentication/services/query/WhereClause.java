package it.cineca.siss.axmr3.authentication.services.query;

/**
 * Created with IntelliJ IDEA.
 * User: cin0562a
 * Date: 24/10/13
 * Time: 14:06
 * To change this template use File | Settings | File Templates.
 */
public class WhereClause {

    private String fieldName;
    private String pattern;
    private String clauseType;

    public WhereClause(String fieldName, String pattern, String clauseType) {
        this.fieldName = fieldName;
        this.pattern = pattern;
        this.clauseType = clauseType;
    }

    public String getFieldName() {
        return fieldName;
    }

    public void setFieldName(String fieldName) {
        this.fieldName = fieldName;
    }

    public String getPattern() {
        return pattern;
    }

    public void setPattern(String pattern) {
        this.pattern = pattern;
    }

    public String getClauseType() {
        return clauseType;
    }

    public void setClauseType(String clauseType) {
        this.clauseType = clauseType;
    }

    @Override
    public String toString() {
        return "WhereClause{" +
                "fieldName='" + fieldName + '\'' +
                ", pattern='" + pattern + '\'' +
                ", clauseType='" + clauseType + '\'' +
                '}';
    }
}
