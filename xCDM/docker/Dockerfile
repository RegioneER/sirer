FROM docker-registry.default.svc:5000/openshift/jboss-webserver31-tomcat8-openshift

ENV PORT 8080
ENV DEV_MODE ON
USER root

RUN echo -e "[cineca]\nbaseurl = http://nexus.cineca.it/repository/RHEL_7/\ngpgcheck = 0\nname = Cineca x86_64 repository\npriority = 90" > /etc/yum.repos.d/cineca.repo
RUN yum update
RUN yum install -y cineca-rh7-base-rhui
RUN yum install -y less nano wget git vim patch

WORKDIR /opt/webserver/lib
#RUN wget https://nexus.saas.hand-china.com/content/repositories/rdc/com/oracle/ojdbc7/12.1.0.2/ojdbc7-12.1.0.2.jar
RUN mkdir -p /opt/application
RUN chown jboss /opt/application -R && chmod u+rw /opt/application && chown jboss /opt/webserver/conf -R && chmod u+rw /opt/webserver/conf
WORKDIR /deployments
ENV GC_MAX_METASPACE_SIZE 2048
RUN mv /etc/localtime /etc/localtime.backup && ln -s /usr/share/zoneinfo/Europe/Rome /etc/localtime
ADD clock /etc/sysconfig/clock
EXPOSE 8080
RUN mkdir -p /logs && chmod oug+rw /logs
USER jboss

ADD run /usr/local/s2i/run
WORKDIR /opt/application
ENV warname __WARNAME__
ENV BASE_LOG_LEVEL WARN
ENV INT_LOG_LEVEL INFO
ENV XCDM_PREFIX CRMS
ENV USERID_AUTHZ_HEADER REMOTE_USERID
ADD log4j.properties /opt/application/log4j.properties
ADD __WARNAME__-paas.war /deployments/__WARNAME__.war
RUN cd /deployments && mkdir __WARNAME__ && cd __WARNAME__ && unzip ../__WARNAME__.war && cd .. && rm __WARNAME__.war

RUN git clone --single-branch --branch __AMBIENTE__ __FTL_REPO__ crpms
ADD server.xml /opt/webserver/conf/server.xml
CMD sh /usr/local/s2i/run

EXPOSE 9090