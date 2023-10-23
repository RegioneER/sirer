package it.cineca.siss.axmr3.doc.beans;

import it.cineca.siss.axmr3.log.Log;
import org.apache.http.client.HttpClient;
import org.apache.http.client.config.RequestConfig;
import org.apache.http.client.fluent.Async;
import org.apache.http.client.fluent.Content;
import org.apache.http.client.fluent.Request;
import org.apache.http.client.methods.HttpGet;
import org.apache.http.client.utils.URIBuilder;
import org.apache.http.concurrent.FutureCallback;
import org.apache.http.impl.client.*;
import org.apache.log4j.Logger;
import org.springframework.beans.factory.InitializingBean;

import java.io.IOException;
import java.net.URI;
import java.net.URISyntaxException;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;

import org.springframework.scheduling.concurrent.*;

/**
 * Created by Carlo on 16/03/2017.
 */
public class InternalServiceBean implements InitializingBean {

    protected String status;
    protected String host;
    protected String protocol;
    protected int port;
    protected String basePath;
    protected ThreadPoolTaskExecutor taskExecutor;

    public ThreadPoolTaskExecutor getTaskExecutor() {
        return taskExecutor;
    }

    public void setTaskExecutor(ThreadPoolTaskExecutor taskExecutor) {
        this.taskExecutor = taskExecutor;
    }

    public String getProtocol() {
        return protocol;
    }

    public void setProtocol(String protocol) {
        this.protocol = protocol;
    }

    public String getStatus() {
        return status;
    }

    public void setStatus(String status) {
        this.status = status;
    }

    public String getHost() {
        return host;
    }

    public void setHost(String host) {
        this.host = host;
    }

    public int getPort() {
        return port;
    }

    public void setPort(int port) {
        this.port = port;
    }

    public String getBasePath() {
        return basePath;
    }

    public void setBasePath(String basePath) {
        this.basePath = basePath;
    }

    public boolean isActive() {
        if (this.status.toLowerCase().equals("on")) {
            return true;
        } else {
            return false;
        }
    }

    public void afterPropertiesSet() throws Exception {
        if (isActive()) {
            Log.info(this.getClass(), "InternalServiceBean attivo su host: " + this.protocol + "://" + this.host + ":" + this.port + this.basePath);
        } else {
            Log.info(this.getClass(), "InternalServiceBean non attivo");
        }
    }

    public void doInternalAsyncRequest(String servicepath) {
        Log.info(this.getClass(), " - - doInternalAsyncRequest - lancio richiesta");

        URIBuilder builder = new URIBuilder();
        builder.setScheme(this.protocol).setHost(this.host).setPort(this.port).setPath(this.basePath + servicepath);
        URI requestURL = null;
        try {
            requestURL = builder.build();
        } catch (URISyntaxException use) {
        }

        FutureCallback<Boolean> callback = new FutureCallback<Boolean>() {
            public void completed(Boolean result) {
                Log.info(this.getClass(), "completed with " + result);
            }

            public void failed(Exception ex) {
                Log.warn(this.getClass(), "failed with " + ex.getMessage());
            }

            public void cancelled() {
                Log.warn(this.getClass(), "cancelled");
            }
        };

        int timeout = 5000;
        int maxredirects = 5;
        RequestConfig.Builder requestBuilder = RequestConfig.custom();
        requestBuilder = requestBuilder.setConnectTimeout(timeout);
        requestBuilder = requestBuilder.setConnectionRequestTimeout(timeout);
        requestBuilder = requestBuilder.setSocketTimeout(timeout);
        requestBuilder = requestBuilder.setRedirectsEnabled(true);
        requestBuilder = requestBuilder.setMaxRedirects(maxredirects);

        final CloseableHttpClient client = HttpClientBuilder.create().setDefaultRequestConfig(requestBuilder.build()).disableAutomaticRetries().build();

        final HttpGet getRequest = new HttpGet(requestURL);
        //final Request request = Request.Get(requestURL);
        //request.connectTimeout(5000);
        //request.socketTimeout(5000);

        taskExecutor.execute(new Runnable() {
            public void run() {
                try {
                    Log.info(this.getClass(), " - - doInternalAsyncRequest - - Lancio richiesta get");
                    client.execute(getRequest);
                } catch (IOException e) {
                    Logger.getLogger(this.getClass()).info("Sembra ci sia un loop"+e.getMessage());
                    try {
                        client.close();
                    } catch (IOException e2) {
                        Log.error(this.getClass(), e2);
                    }
                } finally {
                    try {
                        client.close();
                    } catch (IOException e) {
                        Log.error(this.getClass(), e);
                    }
                }
            }
        }, 1000);
        //Log.info(this.getClass()," - - doInternalAsyncRequest - Restituisco controllo!!!");
    }

}
