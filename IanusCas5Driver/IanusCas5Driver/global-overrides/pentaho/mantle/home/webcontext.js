/** webcontext.js is created by a PentahoWebContextFilter. This filter searches for an incoming URI having "webcontext.js" in it. If it finds that, it write CONTEXT_PATH and FULLY_QUALIFIED_SERVER_URL and it values from the servlet request to this js **/ 


var CONTEXT_PATH = '/pentaho/';

var FULL_QUALIFIED_URL = 'https://siss-cas.dev.cineca.it/pentaho/';

var SERVER_PROTOCOL = 'https';

var requireCfg = {waitSeconds: 30, paths: {}, shim: {}};
<!-- Injecting web resources defined in by plugins as external-resources for: requirejs-->
document.write("<script language='javascript' type='text/javascript' src='"+CONTEXT_PATH + "content/reporting/reportviewer/reporting-require-js-cfg.js?context=mantle'></scr"+"ipt>");
document.write("<script language='javascript' type='text/javascript' src='"+CONTEXT_PATH + "content/pentaho-cdf-dd/js/cde-core-require-js-cfg.js?context=mantle'></scr"+"ipt>");
document.write("<script language='javascript' type='text/javascript' src='"+CONTEXT_PATH + "content/pentaho-cdf-dd/js/cde-pentaho-require-js-cfg.js?context=mantle'></scr"+"ipt>");
document.write("<script language='javascript' type='text/javascript' src='"+CONTEXT_PATH + "content/admin-plugin/resources/admin-plugin-require-js-cfg.js?context=mantle'></scr"+"ipt>");
document.write("<script language='javascript' type='text/javascript' src='"+CONTEXT_PATH + "api/repos/dashboards/script/dashboards-require-js-cfg.js?context=mantle'></scr"+"ipt>");
document.write("<script language='javascript' type='text/javascript' src='"+CONTEXT_PATH + "content/pentaho-cdf/js/cdf-require-js-cfg.js?context=mantle'></scr"+"ipt>");
document.write("<script language='javascript' type='text/javascript' src='"+CONTEXT_PATH + "content/pentaho-cdf/js/lib/cdf-lib-require-js-cfg.js?context=mantle'></scr"+"ipt>");
document.write("<script language='javascript' type='text/javascript' src='"+CONTEXT_PATH + "content/pentaho-cdf/js-legacy/cdf-require-js-cfg.js?context=mantle'></scr"+"ipt>");
document.write("<script language='javascript' type='text/javascript' src='"+CONTEXT_PATH + "content/pentaho-interactive-reporting/resources/web/pir-require-js-cfg.js?context=mantle'></scr"+"ipt>");
document.write("<script language='javascript' type='text/javascript' src='"+CONTEXT_PATH + "content/common-ui/resources/web/common-ui-require-js-cfg.js?context=mantle'></scr"+"ipt>");
document.write("<script language='javascript' type='text/javascript' src='"+CONTEXT_PATH + "content/pentaho-geo/resources/web/geo-require-js-cfg.js?context=mantle'></scr"+"ipt>");
document.write("<script language='javascript' type='text/javascript' src='"+CONTEXT_PATH + "content/analyzer/scripts/analyzer-require-js-cfg.js?context=mantle'></scr"+"ipt>");
document.write("<script language='javascript' type='text/javascript' src='"+CONTEXT_PATH + "js/require-js-cfg.js?context=mantle'></scr"+"ipt>");
requireCfg['urlArgs']='';
document.write("<script type='text/javascript' src='/pentaho/content/common-ui/resources/web/require.js'></scr"+"ipt>");
document.write("<script type='text/javascript' src='/pentaho/content/common-ui/resources/web/require-cfg.js'></scr"+"ipt>");
<!-- Providing name for session -->
document.write("<script type='text/javascript' src='/sessionNameJs'></scr"+"ipt>");
<!-- Providing computed Locale for session -->
var SESSION_LOCALE = 'it_IT';
if(typeof(pen) != 'undefined' && pen.define){pen.define('Locale', {locale:'it_IT'})};<!-- Providing home folder location for UI defaults -->
var RESERVED_CHARS = "\/\\\t\r\n";
var RESERVED_CHARS_DISPLAY = "\/, \\, \\t, \\r, \\n";
var RESERVED_CHARS_REGEX_PATTERN = /.*[\/\\\t\r\n]+.*/;
<!-- Injecting web resources defined in by plugins as external-resources for: global-->
document.write("<link rel='stylesheet' type='text/css' href='"+CONTEXT_PATH + "content/data-access/resources/gwt/datasourceEditorDialog.css?context=mantle'/>");
document.write("<link rel='stylesheet' type='text/css' href='"+CONTEXT_PATH + "content/data-access/resources/gwt/datasourceAdminDialog.css?context=mantle'/>");
document.write("<script language='javascript' type='text/javascript' src='"+CONTEXT_PATH + "content/pentaho-mobile/resources/mobile-utils.js?context=mantle'></scr"+"ipt>");
document.write("<link rel='stylesheet' type='text/css' href='"+CONTEXT_PATH + "content/common-ui/resources/web/angular-directives/angular-directives.css?context=mantle'/>");
document.write("<script language='javascript' type='text/javascript' src='"+CONTEXT_PATH + "content/common-ui/resources/web/dojo/djConfig.js?context=mantle'></scr"+"ipt>");
document.write("<script language='javascript' type='text/javascript' src='"+CONTEXT_PATH + "content/common-ui/resources/web/cache/cache-service.js?context=mantle'></scr"+"ipt>");
document.write("<script language='javascript' type='text/javascript' src='"+CONTEXT_PATH + "content/common-ui/resources/themes/jquery.js?context=mantle'></scr"+"ipt>");
document.write("<script language='javascript' type='text/javascript' src='"+CONTEXT_PATH + "content/common-ui/resources/themes/themeUtils.js?context=mantle'></scr"+"ipt>");
document.write("<script language='javascript' type='text/javascript' src='"+CONTEXT_PATH + "content/common-ui/resources/web/util/URLEncoder.js?context=mantle'></scr"+"ipt>");
document.write("<script language='javascript' type='text/javascript' src='"+CONTEXT_PATH + "js/themes.js?context=mantle'></scr"+"ipt>");
document.write("<script language='javascript' type='text/javascript' src='"+CONTEXT_PATH + "content/common-ui/resources/themes/jquery.js?context=mantle'></scr"+"ipt>");
document.write("<script language='javascript' type='text/javascript' src='"+CONTEXT_PATH + "api/repos/dashboards/resources/gwt/chartDesigner/chartDesigner.nocache.js?context=mantle'></scr"+"ipt>");
<!-- Injecting web resources defined in by plugins as external-resources for: mantle-->
var IS_VALID_PLATFORM_LICENSE = true;
