package it.cineca.siss.axmr3.activiti;

import javax.servlet.*;
import javax.servlet.http.HttpServletRequest;
import java.io.IOException;
import java.util.ArrayList;
import java.util.List;

/**
 * Created with IntelliJ IDEA.
 * User: cin0562a
 * Date: 21/10/13
 * Time: 12:24
 * To change this template use File | Settings | File Templates.
 */
public class ExplorerFilter extends org.activiti.explorer.filter.ExplorerFilter {

    private List<String> ignoreList = new ArrayList<String>();
    @Override
    public void init(FilterConfig filterConfig) throws ServletException {
        ignoreList.add("/ui");
        ignoreList.add("/VAADIN");
        ignoreList.add("/api");
        ignoreList.add("/editor");
        ignoreList.add("/explorer");
        ignoreList.add("/libs");
        ignoreList.add("/service");
        ignoreList.add("/diagram-viewer");
    }


    @Override
    public void doFilter(ServletRequest request, ServletResponse response, FilterChain chain) throws IOException, ServletException {
        HttpServletRequest req = (HttpServletRequest) request;
        String path = req.getRequestURI().substring(req.getContextPath().length());

        path=path.replace("pconsole/", "");
        int indexSlash = path.indexOf("/", 1);
        String firstPart = null;

        if (indexSlash > 0) {
            firstPart = path.substring(0, indexSlash);
        } else {
            firstPart = path;
        }
        if (ignoreList.contains(firstPart)) {
           chain.doFilter(request, response); // Goes to default servlet.
        } else {
            request.getRequestDispatcher("/pconsole/ui" + path).forward(request, response);
        }

    }


    @Override
    public void destroy() {
    }
}
