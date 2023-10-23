package it.cineca.siss.axmr3.doc.xml;

import java.util.HashMap;

public class CheckResult {

    protected boolean passed;
    protected HashMap<String, String> errors;


    public boolean isPassed() {
        return passed;
    }

    public void setPassed(boolean passed) {
        this.passed = passed;
    }

    public HashMap<String, String> getErrors() {
        return errors;
    }

    public void setErrors(HashMap<String, String> errors) {
        this.errors = errors;
    }
}
