package it.cineca.siss.axmr3.doc.web.controllers.frontend;

import org.dom4j.DocumentException;
import org.springframework.stereotype.Controller;
import org.springframework.ui.ModelMap;
import org.springframework.web.bind.annotation.ModelAttribute;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RequestMethod;

import javax.servlet.http.HttpServletRequest;
import java.io.IOException;

/**
 * Created with IntelliJ IDEA.
 * User: Carlo
 * Date: 31/07/13
 * Time: 14.41
 * To change this template use File | Settings | File Templates.
 */
@Controller
public class MainController {

    /**
     * Home Page
     * @param request
     * @param model
     * @return
     * @throws DocumentException
     * @throws IOException
     *
     *
     */
    @RequestMapping(value="/index", method= RequestMethod.GET)
    public String index(HttpServletRequest request, @ModelAttribute("model") ModelMap model) throws DocumentException, IOException {
        return "home";
    }

    /**
     * Home Page
     * @param request
     * @param model
     * @return
     * @throws DocumentException
     * @throws IOException
     *
     *
     */
    @RequestMapping(value="/", method=RequestMethod.GET)
    public String indexNull(HttpServletRequest request, @ModelAttribute("model") ModelMap model) throws DocumentException, IOException{
        return index(request, model);
    }

}
