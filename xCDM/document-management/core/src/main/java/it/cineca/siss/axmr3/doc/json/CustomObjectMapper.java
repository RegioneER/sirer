package it.cineca.siss.axmr3.doc.json;

import org.apache.log4j.Logger;
import org.codehaus.jackson.map.ObjectMapper;
import org.codehaus.jackson.map.SerializationConfig;

import javax.annotation.PostConstruct;


/**
 * Created with IntelliJ IDEA.
 * User: Carlo
 * Date: 24/07/13
 * Time: 15.26
 * To change this template use File | Settings | File Templates.
 */
public class CustomObjectMapper extends ObjectMapper {

    Logger log = Logger.getLogger(CustomObjectMapper.class);

    @PostConstruct
    public void afterProps()
    {
        log.info("PostConstruct... RUNNING - disabilito FAIL_ON_EMPTY_BEANS");
        configure(SerializationConfig.Feature.FAIL_ON_EMPTY_BEANS,false);


    }
}
