package it.cineca.siss.axmr3.log;

import org.apache.log4j.PatternLayout;
import org.apache.log4j.EnhancedPatternLayout;

public class Axmr3Appender extends org.apache.log4j.jdbc.JDBCAppender {


    public void setSql(String s) {
        this.sqlStatement = s;
        if (this.getLayout() == null) {
            this.setLayout(new EnhancedPatternLayout(s));
        } else {
            ((EnhancedPatternLayout)this.getLayout()).setConversionPattern(s);
        }

    }

}
