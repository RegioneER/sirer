package it.cineca.siss.axmr3.common.mvc.handlers;

import com.google.gson.Gson;
import com.google.gson.GsonBuilder;
import it.cineca.siss.axmr3.authentication.IUser;
import it.cineca.siss.axmr3.authentication.impl.UserImpl;
import it.cineca.siss.axmr3.authentication.services.SissUserService;
import org.apache.log4j.Logger;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.beans.factory.annotation.Qualifier;
import org.springframework.security.authentication.AnonymousAuthenticationToken;
import org.springframework.security.core.Authentication;
import org.springframework.security.core.context.SecurityContextHolder;
import org.springframework.security.core.userdetails.UserDetails;
import org.springframework.web.bind.annotation.RequestMethod;
import org.springframework.web.servlet.ModelAndView;
import org.springframework.web.servlet.handler.HandlerInterceptorAdapter;

import javax.servlet.ServletContext;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;
import javax.sql.DataSource;
import java.io.File;
import java.io.FileInputStream;
import java.io.InputStream;
import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.util.*;

/**
 * Created with IntelliJ IDEA.
 *
 * Controller per chiamate MVC
 */

public class ControllerHandler extends HandlerInterceptorAdapter {

    protected static final Logger log=Logger.getLogger(ControllerHandler.class);
    private static Properties supportedLanguages;
    private static final String DEFAULT="DEFAULT";
    private static final String LOGGED_USER_PARAM="loggedUser";
    private Locale requestLocale;

    @Autowired
    @Qualifier ("messagesFolder")
    protected String messagesFolder;

    @Autowired
    @Qualifier(value = "DocDataSource")
    protected DataSource dataSource;

    public DataSource getDataSource() {
        return dataSource;
    }

    public void setDataSource(DataSource dataSource) {
        this.dataSource = dataSource;
    }


    /**
     * Inizializza il Controller e imposta la lingua di default
     *
     *
     */
    public ControllerHandler() {
        supportedLanguages = new Properties();
        supportedLanguages.put(DEFAULT, Locale.ITALY);
        supportedLanguages.put("it_IT", new Locale("it", "IT"));
        supportedLanguages.put("en_UK", Locale.ENGLISH);
        requestLocale= (Locale) supportedLanguages.get(DEFAULT);
    }

    /**
     * Imposta la lingua recuperandola dalla request
     * @param request
     *
     *
     */
    private void detectLocale(HttpServletRequest request) {
        Enumeration locales = request.getLocales();
        while (locales.hasMoreElements()) {
            Locale locale = (Locale) locales.nextElement();
            if (supportedLanguages.contains(locale)) {
                requestLocale = locale;
                break;
            }
        }
    }

    public static Locale getLocale(HttpServletRequest request) {
        Enumeration locales = request.getLocales();
        Locale l=(Locale) supportedLanguages.get(DEFAULT);
        while (locales.hasMoreElements()) {
            Locale locale = (Locale) locales.nextElement();
            if (supportedLanguages.contains(locale)) {
                l = locale;
                break;
            }
        }
        return l;
    }

    public String getLanguage() {
        return requestLocale.getDisplayLanguage();
    }

    @Autowired
    protected SissUserService userService;
    public SissUserService getUserService() {
        return userService;
    }

    public void setUserService(SissUserService userService) {
        this.userService = userService;
    }


    /**
     * Operazioni da eseguire prima che venga passato il controllo al Controller MVC relativo
     * @param request
     * @param response
     * @param handler
     * @return
     * @throws Exception
     *
     *
     */
    @Override
    public boolean preHandle(HttpServletRequest request, HttpServletResponse response, Object handler) throws Exception {
        IUser user = null;

        if (request.getSession().getAttribute(LOGGED_USER_PARAM)!=null){
            user=(IUser) request.getSession().getAttribute(LOGGED_USER_PARAM);
        }else {
            try {
                user = (UserImpl) SecurityContextHolder.getContext().getAuthentication().getPrincipal();
            } catch (java.lang.ClassCastException ex) {
                try{
                    user = new UserImpl();
                    user.fromUserDetails((UserDetails) SecurityContextHolder.getContext().getAuthentication().getPrincipal());
                }catch (java.lang.ClassCastException ex1) {
                    user = new UserImpl();
                    String loggedUser=(String) SecurityContextHolder.getContext().getAuthentication().getPrincipal();
                    if (!loggedUser.equals("anonymousUser")) user=userService.getUser(loggedUser);
                }

            }
            if (user!=null){
                System.out.println("Controllo la presenza dell'header authz-authenticationmethod");
                if (request.getHeader("authz-authenticationmethod")!=null) {
                    //TODO: cambiare user.getUsername() perchè prende il CF di ANA_UTENTI e non l'userid di UTENTI (caso in cui sono diversi)
                    System.out.println("AUTHZ_AUTHENTICATIONMETHOD: " + request.getHeader("authz-authenticationmethod") + " USERNAME: " + user.getUsername());
                    if (request.getHeader("authz-authenticationmethod").equals("QueryDatabaseAuthenticationHandler")) {
                        String sqlScadenzaPWD = "select case when nvl(dttm_scadenzapwd,sysdate) < sysdate then 1 else 0 end as REDIRECT from utenti where UPPER(userid)=?";
                        try (Connection conn = dataSource.getConnection()) {
                            try (PreparedStatement stmt = conn.prepareStatement(sqlScadenzaPWD)) {
                                stmt.setString(1, user.getUsername());

                                try (ResultSet rset1 = stmt.executeQuery()) {
                                    rset1.next();
                                    if (rset1.getInt(1) == 1) {
                                        response.sendRedirect("/change_password");
                                        return false;
                                    }
                                }
                            }
                        }
                    }
                }
                request.getSession().setAttribute(LOGGED_USER_PARAM, user);
            }
        }
        Long emeSessionId = (Long)request.getSession().getAttribute("EME_SESSION_ID");
        if (user!=null && emeSessionId!=null && emeSessionId>0){
            user.setEmeSessionId(emeSessionId);
        }
        String reqUri=request.getRequestURI();
        Gson gson = new GsonBuilder().create();
        String reqParams= gson.toJson(request.getParameterMap());
        String reqMethod=request.getMethod();
        HashMap<String, String> headersMap=new HashMap<String, String>();
        Enumeration<String> hNames = request.getHeaderNames();
        while (hNames.hasMoreElements()){
            String hName=hNames.nextElement();
            headersMap.put(hName, request.getHeader(hName));
        }
        String reqHeaders=gson.toJson(headersMap);
        String loggedUserid="anon";
        String delegatedBy="";
        if (user==null){
            Logger.getLogger(this.getClass()).debug("Utente non loggato!!!");
            Logger.getLogger(this.getClass()).info("Uri: "+reqUri+" - Method: "+reqMethod);
        }else {
            loggedUserid=user.getUsername();
            if (user.getLoggedUserid()!=null && user.getLoggedUserid()!=user.getUsername()){
                delegatedBy=user.getUsername();
                loggedUserid=user.getLoggedUserid();
                Logger.getLogger(this.getClass()).info("Uri: "+reqUri+" - Method: "+reqMethod+" - Logged User: "+loggedUserid+" Delegated by: "+delegatedBy);
            }else {
                Logger.getLogger(this.getClass()).info("Uri: "+reqUri+" - Method: "+reqMethod+" - Logged User: "+loggedUserid);
            }
        }
        String sqlDelegationActive="select count(*) as C from user_tables where table_name='XDM_AUDIT_LOG'";
        try(Connection conn = dataSource.getConnection()){
            try(PreparedStatement stmt = conn.prepareStatement(sqlDelegationActive)){
                try(ResultSet rset1=stmt.executeQuery()){
                    rset1.next();
                    if (rset1.getInt(1)==0){
                        String createAudiTable="create table XDM_AUDIT_LOG(\n" +
                                "LOGGED_USERID varchar2(120 char),\n" +
                                "DELEGATED_BY varchar2(120 char),\n" +
                                "LOG_DATE DATE,\n" +
                                "REQUEST_URI varchar2(4000 char),\n" +
                                "REQUEST_HEADERS CLOB,\n" +
                                "REQUEST_PARAMS CLOB,\n" +
                                "REQUEST_METHOD VARCHAR2(20 char)\n" +
                                ")";
                        try(PreparedStatement stmtCreate = conn.prepareStatement(createAudiTable)){
                            stmtCreate.execute();
                        }
                    }
                    String insertAuditLog="insert into XDM_AUDIT_LOG (LOGGED_USERID, DELEGATED_BY, LOG_DATE, REQUEST_URI, REQUEST_HEADERS, REQUEST_PARAMS, REQUEST_METHOD) VALUES (?, ?, sysdate, ?, ?, ?, ?)";
                    try(PreparedStatement stmt1 = conn.prepareStatement(insertAuditLog)){
                        stmt1.setString(1, loggedUserid);
                        stmt1.setString(2, delegatedBy);
                        stmt1.setString(3, reqUri);
                        stmt1.setString(4, reqHeaders);
                        stmt1.setString(5, reqParams);
                        stmt1.setString(6, reqMethod);
                        stmt1.executeUpdate();

                    }
                    conn.commit();
                }

            }
        }

        if (user!=null && user.getEmeSessionId() != null && user.getEmeSessionId()>0){
            //Ho sessione emendamento attiva, lancio una query per cercare di riconoscere lo studio emendato (oggetto radice coinvolto)
            String sqlEmeRootElement="select s.id, s.centro_id, s.eme_id, o.parent_id, o.type_id from doc_eme_session s, doc_obj o where s.centro_id = o.id and s.id = ?";
            try(Connection conn = dataSource.getConnection()){
                try(PreparedStatement stmt = conn.prepareStatement(sqlEmeRootElement)){
                    stmt.setLong(1, user.getEmeSessionId());
                    try(ResultSet rset1=stmt.executeQuery()){
                        if (rset1.next()){
                            Long parentId = rset1.getLong("PARENT_ID");
                            if (parentId != null && parentId>0){
                                user.setEmeRootElementId(parentId);
                            }else{
                                user.setEmeRootElementId(0L);
                            }
                        }
                    }
                }
            }
        }

        return super.preHandle(request, response, handler);
    }

    /**
     * getBaseUrl
     * @param request
     * @return
     *
     * Restituisce l'url base
     *
     */
    public static String getBaseUrl(HttpServletRequest request){
        String servletPath=request.getServletPath();
        String requestedMappedUrl=request.getPathInfo();
        String baseUrl=request.getRequestURI().replaceAll( ";(.*)$","");
        baseUrl=baseUrl.replaceAll( ""+servletPath+requestedMappedUrl+"$","");
        return baseUrl;
    }
    /**
     * Gestisce le operazioni successivamente al Controller relativo.
     * Recupera le stringe dei messaggi definiti in /WEB-INF/messages/[language]_[country].properties
     * Aggiunge un set di variabili al modello tra cui: userDetails, messages, baseUrl (Attenzione queste variabili vengono ignettate direttamente nella pagina freemarker e non all'interno della variabile model come succede dal controller MVC)
     * @param request
     * @param response
     * @param handler
     * @param modelAndView
     * @throws Exception
     *
     * */
    @Override
    public void postHandle(HttpServletRequest request, HttpServletResponse response, Object handler, ModelAndView modelAndView) throws Exception {
        if (request.getMethod().equals(RequestMethod.POST.toString())){
            super.postHandle(request, response, handler, modelAndView);
        }else if (modelAndView==null){
            super.postHandle(request, response, handler, modelAndView);
        }
        else {
        /*Trovo la lingua del browser e carico i testi per la lingua in questione*/
        detectLocale(request);
        ServletContext context = request.getSession().getServletContext();
        InputStream stream = context.getResourceAsStream("/WEB-INF/messages/general.properties");
        Properties messProps=new Properties();
        messProps.load(stream);
        HashMap<String, String> messages=new HashMap<String, String>();
        Enumeration e = messProps.propertyNames();
        while (e.hasMoreElements()) {
            String key = (String) e.nextElement();
            messages.put(key,messProps.getProperty(key));
        }
            Properties adHocProps=new Properties();
            String filename=messagesFolder+"/messages/"+requestLocale.getLanguage()+"_"+requestLocale.getCountry()+".properties";
            File file=new File(filename);
            if(file.exists()) {
                FileInputStream fis=new FileInputStream(file);
                adHocProps.load(fis);
                fis.close();
            }else{
                filename=messagesFolder+"/messages/it_IT.properties";
                if(file.exists()) {
                    FileInputStream fis=new FileInputStream(file);
                    adHocProps.load(fis);
                    fis.close();
                }
            }
            Enumeration e1 = adHocProps.propertyNames();
            while (e1.hasMoreElements()) {
                String key = (String) e1.nextElement();
                messages.put(key,adHocProps.getProperty(key));
            }
            HttpSession session=request.getSession();
            Enumeration<String> attrs=session.getAttributeNames();
            while (attrs.hasMoreElements()){
                String attrName=attrs.nextElement();
                modelAndView.getModelMap().put(attrName, session.getAttribute(attrName));
            }

        /*Calcolo e ignetto il baseUrl*/


        modelAndView.addObject("baseUrl",getBaseUrl(request));
        modelAndView.addObject("messages", messages);
        /*Controllo che l'utente sia loggato e ignetto l'utente nel template*/
        Authentication auth = SecurityContextHolder.getContext().getAuthentication();
        if (!(auth instanceof AnonymousAuthenticationToken)) {
            UserDetails userDetails =(UserDetails)SecurityContextHolder.getContext().getAuthentication().getPrincipal();
            modelAndView.addObject("userDetails",userDetails);
        }
            LinkedList<String> includes=new LinkedList<String>();
           String viewName=modelAndView.getViewName();
            if (viewName.startsWith("multiStepForms")) {

                includes.add("../lib/macros.ftl");
                modelAndView.addObject("includes", includes);
                super.postHandle(request,response,handler,modelAndView);
            }
            else {
                includes.add("../lib/macros.ftl");
                modelAndView.addObject("includes", includes);
                modelAndView.addObject("mainContent",viewName+".ftl");
                modelAndView.setViewName(getContainer(viewName));
                super.postHandle(request, response, handler, modelAndView);
            }
        }
    }

    protected String getContainer(String viewName){
        //TODO: gestire la gestione dei container ftl
        return "container-01";
    }



}
