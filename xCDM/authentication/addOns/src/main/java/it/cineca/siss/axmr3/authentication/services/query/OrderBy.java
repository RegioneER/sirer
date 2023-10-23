package it.cineca.siss.axmr3.authentication.services.query;

/**
 * Created with IntelliJ IDEA.
 * User: cin0562a
 * Date: 24/10/13
 * Time: 14:06
 * To change this template use File | Settings | File Templates.
 */
public class OrderBy {

    protected String fieldName;
    protected String orderType;

    public OrderBy(String fieldName, String orderType) {
        this.fieldName = fieldName;
        this.orderType = orderType;
    }

    public String getFieldName() {
        return fieldName;
    }

    public void setFieldName(String fieldName) {
        this.fieldName = fieldName;
    }

    public String getOrderType() {
        return orderType;
    }

    public void setOrderType(String orderType) {
        this.orderType = orderType;
    }

    @Override
    public String toString() {
        return "OrderBy{" +
                "fieldName='" + fieldName + '\'' +
                ", orderType='" + orderType + '\'' +
                '}';
    }
}
