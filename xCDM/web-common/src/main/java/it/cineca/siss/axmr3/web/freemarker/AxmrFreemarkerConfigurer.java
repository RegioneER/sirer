package it.cineca.siss.axmr3.web.freemarker;

import freemarker.cache.*;
import freemarker.core.Configurable;
import freemarker.core.Environment;
import freemarker.template.Configuration;
import freemarker.template.TemplateException;

import freemarker.template.TemplateExceptionHandler;
import org.apache.log4j.Logger;
import org.springframework.web.servlet.view.freemarker.FreeMarkerConfigurer;

import java.io.File;
import java.io.IOException;

/**
 * Created with IntelliJ IDEA.
 * User: Carlo
 * Date: 13/09/13
 * Time: 10.22
 * To change this template use File | Settings | File Templates.
 */
public class AxmrFreemarkerConfigurer extends FreeMarkerConfigurer {

    private String addOnPath;

    public String getAddOnPath() {
        return addOnPath;
    }

    public void setAddOnPath(String addOnPath) {
        this.addOnPath = addOnPath;
    }

    @Override
    public Configuration getConfiguration() {
        Configuration conf = super.getConfiguration();
        FileTemplateLoader ftl1 = null;
        conf.setLogTemplateExceptions(false);
        //conf.setTemplateExceptionHandler(TemplateExceptionHandler.RETHROW_HANDLER);
        try {
            it.cineca.siss.axmr3.log.Log.info(getClass(),"Aggiungo path per template:" + this.addOnPath + "/templates");
            ftl1 = new FileTemplateLoader(new File(this.addOnPath + "/templates"));
            TemplateLoader defaultTl = conf.getTemplateLoader();
            it.cineca.siss.axmr3.log.Log.info(getClass(),"Aggiungo il path *.jar!/ftl al template loader");
            TemplateLoader d1 = new ClassTemplateLoader(this.getClass(), "/ftl");
            TemplateLoader[] loaders = new TemplateLoader[]{ftl1, defaultTl, d1};
            MultiTemplateLoader mtl = new MultiTemplateLoader(loaders);
            conf.setTemplateLoader(mtl);
            conf.setCacheStorage(new MruCacheStorage(20, 250));
        } catch (IOException e) {
            Logger.getLogger(this.getClass()).info(e.getMessage());
        }

        return conf;
    }





    @Override
    public void setTemplateLoaderPath(String templateLoaderPath) {
        super.setTemplateLoaderPath("WEB-INF/ftl");
        this.addOnPath = templateLoaderPath;
    }

    @Override
    public void afterPropertiesSet() throws IOException, TemplateException {
        super.afterPropertiesSet();
        //it.cineca.siss.axmr3.log.Log.info(getClass(),"Provo a caricare il template test.ftl");
        //this.getConfiguration().getTemplate("test.ftl");
        //it.cineca.siss.axmr3.log.Log.info(getClass(),"template caricato");

    }
}
