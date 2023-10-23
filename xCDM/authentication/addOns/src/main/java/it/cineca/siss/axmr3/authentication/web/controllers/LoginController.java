package it.cineca.siss.axmr3.authentication.web.controllers;

import org.apache.log4j.Logger;
import org.dom4j.DocumentException;
import org.springframework.stereotype.Controller;
import org.springframework.ui.ModelMap;
import org.springframework.web.bind.annotation.ModelAttribute;
import org.springframework.web.bind.annotation.RequestMapping;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;
import java.util.Enumeration;
import java.util.Iterator;

/**
 * Created with IntelliJ IDEA.
 * User: Carlo
 * Date: 10/06/13
 * Time: 14.49
 * To change this template use File | Settings | File Templates.
 */
@Controller
public class LoginController {
    protected static final Logger log=Logger.getLogger(LoginController.class);
    @RequestMapping(value = "/login")
    public String instance(HttpServletRequest request, HttpServletResponse response, @ModelAttribute("model") ModelMap model) throws DocumentException, IOException {
        if (request.getParameter("error")!=null && !request.getParameter("error").isEmpty()){
            model.put("error", true);
        }
        log.debug("ORMAI SON DENTRO AL LOGIN CONTROLLER");

        Enumeration headerNames = request.getHeaderNames();
        while(headerNames.hasMoreElements()) {
            String headerName = (String)headerNames.nextElement();
            log.debug(headerName + ": " + request.getHeader(headerName));
            //response.getOutputStream().println(headerName + ": " + request.getHeader(headerName));
        }

        //response.getOutputStream().close();
        return "login";
    }

}
