package it.cineca.siss.axmr3.doc.elk;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.beans.factory.annotation.Qualifier;
import org.springframework.web.client.RestTemplate;

public class ElkService {

    @Autowired
    @Qualifier("externalIndexerUrl")
    public String externalIndexerUrl;

    public String simpleIndex(Long elId) {
        RestTemplate restTemplate = new RestTemplate();
        return restTemplate.getForObject(this.externalIndexerUrl+"/rest/elk/simpleIndexById/"+elId, String.class);
    }

    public String fullIndex(Long elId) {
        RestTemplate restTemplate = new RestTemplate();
        return restTemplate.getForObject(this.externalIndexerUrl+"/rest/elk/fullIndexById/"+elId, String.class);
    }

    public String fieldIndex(Long elId) {
        RestTemplate restTemplate = new RestTemplate();
        return restTemplate.getForObject(this.externalIndexerUrl+"/rest/elk/fieldsIndexById/"+elId, String.class);
    }

    public String doSimpleIndex(String type) {
        RestTemplate restTemplate = new RestTemplate();
        return restTemplate.getForObject(this.externalIndexerUrl+"/rest/elk/index/"+type, String.class);
    }

    public String doFullIndex(String type) {
        RestTemplate restTemplate = new RestTemplate();
        return restTemplate.getForObject(this.externalIndexerUrl+"/rest/elk/fullIndex/"+type, String.class);
    }

    public String doFieldIndex(String type) {
        RestTemplate restTemplate = new RestTemplate();
        return restTemplate.getForObject(this.externalIndexerUrl+"/rest/elk/fieldsIndex/"+type, String.class);
    }

    public static String escape(String stringa) {
        return stringa.replaceAll("[-]*", "");
    }

    

    
    
}
