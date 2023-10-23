package it.cineca.siss.axmr3.web.userservice.controllers;

import it.cineca.siss.axmr3.authentication.UserService;
import it.cineca.siss.axmr3.authentication.entities.Authority;
import it.cineca.siss.axmr3.authentication.entities.User;
import it.cineca.siss.axmr3.authentication.services.SissUserService;
import org.springframework.beans.factory.annotation.Autowire;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RequestMethod;
import org.springframework.web.bind.annotation.ResponseBody;

import javax.servlet.http.HttpServletRequest;
import java.util.List;

/**
 * Created with IntelliJ IDEA.
 * User: Carlo
 * Date: 30/08/13
 * Time: 16.31
 * To change this template use File | Settings | File Templates.
 */
@Controller
public class RestUserController {

    @Autowired
    private UserService uService;

    public UserService getuService() {
        return uService;
    }

    public void setuService(UserService uService) {
        this.uService = uService;
    }

    @RequestMapping(value="/rest/user/searchUser", method = RequestMethod.GET)
    public @ResponseBody
    List<User> searchUser(HttpServletRequest request){
        return uService.searchUserByUsername(request.getParameter("term"));
    }

    @RequestMapping(value="/rest/user/searchAuth", method = RequestMethod.GET)
    public @ResponseBody List<Authority> searchAuth(HttpServletRequest request){
        return uService.searchAuthorityByName(request.getParameter("term"));
    }


}
