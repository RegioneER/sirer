package it.cineca.siss.axmr3.doc.types;

import it.cineca.siss.axmr3.doc.web.exceptions.RestException;

import java.util.HashMap;
import java.util.Map;


/**
 * Created with IntelliJ IDEA.
 * User: Carlo
 * Date: 26/07/13
 * Time: 11.09
 * To change this template use File | Settings | File Templates.
 */
public class PostResult {

    private String result;
    private String redirect;
    private Object ret;
    private HashMap<String,Object> resultMap=new HashMap<String, Object>();

    public HashMap<String, Object> getResultMap() {
        return resultMap;
    }

    public void setResultMap(Map<String, Object> resultMap) {
        this.resultMap = (HashMap<String, Object>) resultMap;
    }

    public Object getRet() {
		return ret;
	}

	public void setRet(Object ret) {
		this.ret = ret;
	}

	public PostResult(Exception e) {
        this.result="ERROR";
        this.errorMessage=e.getMessage();
    }

    public String getErrorMessage() {
        return errorMessage;
    }

    public void setErrorMessage(String errorMessage) {
        this.errorMessage = errorMessage;
    }

    public Integer getErrorCode() {
        return errorCode;
    }

    public void setErrorCode(Integer errorCode) {
        this.errorCode = errorCode;
    }

    private String errorMessage;
    private Integer errorCode;

    public String getRedirect() {
        return redirect;
    }

    public void setRedirect(String redirect) {
        this.redirect = redirect;
    }

    public PostResult(String result) {
        this.result = result;
    }

    public String getResult() {

        return result;
    }

    public void setResult(String result) {
        this.result = result;
    }
}
