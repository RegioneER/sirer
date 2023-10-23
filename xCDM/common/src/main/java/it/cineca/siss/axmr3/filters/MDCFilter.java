package it.cineca.siss.axmr3.filters;

import org.slf4j.MDC;
import org.springframework.security.core.Authentication;
import org.springframework.security.core.context.SecurityContextHolder;

import javax.servlet.*;
import java.io.IOException;

public class MDCFilter implements Filter {
    @Override
    public void init(FilterConfig filterConfig) throws ServletException {
    }

    @Override
    public void doFilter(ServletRequest req, ServletResponse resp, FilterChain chain)
            throws IOException, ServletException {
        Authentication authentication =
                SecurityContextHolder.getContext().getAuthentication();
        if (authentication != null) {
            MDC.put("userName", authentication.getName());
        }
        try {
            chain.doFilter(req, resp);
        } finally {
            if (authentication != null) {
                MDC.remove("userName");
            }
        }
    }

    @Override
    public void destroy() {
    }
}
