package it.cineca.siss.axmr3.web.userservice.controllers;

import it.cineca.siss.axmr3.authentication.UserService;
import it.cineca.siss.axmr3.authentication.entities.User;
import org.apache.log4j.Logger;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.security.core.userdetails.UserDetailsService;
import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.PathVariable;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.ResponseBody;

/**
 * Created with IntelliJ IDEA.
 * User: Carlo
 * Date: 31/05/13
 * Time: 11.56
 * To change this template use File | Settings | File Templates.
 */
@Controller
@RequestMapping(value="userService/**")
public class UserServiceController {

    protected static Logger log=Logger.getLogger(UserServiceController.class);

    @Autowired
    protected UserDetailsService service;

    public UserDetailsService getService() {
        return service;
    }

    public void setService(UserDetailsService service) {
        this.service = service;
    }

    @RequestMapping(value = "getUserDetail/{username:.+}")
    @ResponseBody
    public User getByUsername(@PathVariable("username") String username){
        User user= ((UserService) this.service).getUserByUsername(username);
        return user;
    }
}
