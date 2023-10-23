package it.cineca.siss.axmr3.doc.web.exceptions;

import it.cineca.siss.axmr3.exceptions.AxmrGenericException;
import it.cineca.siss.axmr3.transactions.MultiSessionTXManager;

/**
 * Created with IntelliJ IDEA.
 * User: Carlo
 * Date: 03/09/13
 * Time: 11.59
 * To change this template use File | Settings | File Templates.
 */
public class RestException extends AxmrGenericException {

    private Integer code;

    public Integer getCode() {
        return code;
    }

    public void setCode(Integer code) {
        this.code = code;
    }

    public RestException(String s, MultiSessionTXManager txManager) {
        super(s);
        txManager.setExceptionThrown(true);
    }

    public RestException(String s, Integer code){
       super(s);
        this.code=code;
    }
}
