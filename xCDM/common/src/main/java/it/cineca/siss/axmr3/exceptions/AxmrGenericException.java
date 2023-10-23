package it.cineca.siss.axmr3.exceptions;

import it.cineca.siss.axmr3.transactions.Axmr3TXManager;
import org.springframework.beans.factory.annotation.Autowire;
import org.springframework.beans.factory.annotation.Autowired;

/**
 * Created with IntelliJ IDEA.
 * User: Carlo
 * Date: 10/09/13
 * Time: 9.35
 * To change this template use File | Settings | File Templates.
 */
public class AxmrGenericException extends Exception {

    public AxmrGenericException(String s) {
        super(s);
    }

}
