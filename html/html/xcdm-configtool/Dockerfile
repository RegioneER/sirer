FROM debian:buster
RUN apt-get update && \
    apt-get install -y apt-utils apt-transport-https curl lsb-release gnupg2 apt-transport-https ca-certificates wget dirmngr gnupg software-properties-common && \
    curl https://packages.sury.org/php/apt.gpg | apt-key add - && \
    wget -qO - https://adoptopenjdk.jfrog.io/adoptopenjdk/api/gpg/key/public | apt-key add - && \
    add-apt-repository --yes https://adoptopenjdk.jfrog.io/adoptopenjdk/deb/ && \
    echo "deb https://packages.sury.org/php/ $(lsb_release -sc) main" | tee /etc/apt/sources.list.d/php5.list && \
    apt-get update && \
    apt-get install -y php5.6 php5.6-dev php5.6-json php5.6-xml git zip apache2 adoptopenjdk-8-hotspot wkhtmltopdf libaio1 libapache2-mod-auth-cas htmldoc libtool curl nano less && \
    apt-get upgrade -y

WORKDIR /tmp
RUN wget -q http://siss20.private.cineca.it:8081/nexus/service/local/repositories/releases/content/com/oracle/clients/instantclient-basic-linux.x64/18.3.0.0.0dbru/instantclient-basic-linux.x64-18.3.0.0.0dbru.zip && \
    wget -q http://siss20.private.cineca.it:8081/nexus/service/local/repositories/releases/content/com/oracle/clients/instantclient-sdk-linux.x64/18.3.0.0.0dbru/instantclient-sdk-linux.x64-18.3.0.0.0dbru.zip && \
    wget -q http://siss20.private.cineca.it:8081/nexus/service/local/repositories/releases/content/com/oracle/clients/instantclient-sqlplus-linux.x64/18.3.0.0.0dbru/instantclient-sqlplus-linux.x64-18.3.0.0.0dbru.zip && \
    unzip /tmp/instantclient-basic-linux.x64-18.3.0.0.0dbru.zip -d /usr/local/ && \
    unzip /tmp/instantclient-sdk-linux.x64-18.3.0.0.0dbru.zip -d /usr/local/ && \
    unzip /tmp/instantclient-sqlplus-linux.x64-18.3.0.0.0dbru.zip -d /usr/local/ && \
    rm /tmp/*.zip

RUN pecl channel-update pecl.php.net
RUN ln -s /usr/local/instantclient_18_3/sqlplus /usr/bin/sqlplus && echo 'instantclient,/usr/local/instantclient_18_3' | pecl install oci8-2.0.12
RUN git clone https://github.com/ZeWaren/pecl-apd.git && cd pecl-apd && phpize && ./configure && make install
ENV LD_LIBRARY_PATH=/usr/local/instantclient_18_3:$LD_LIBRARY_PATH
ADD oci8.ini /etc/php/5.6/mods-available/oci8.ini
ADD apd.ini /etc/php/5.6/mods-available/apd.ini

RUN phpenmod oci8 && phpenmod apd

WORKDIR /opt
ADD db.inc /opt/db.inc
ADD sync-config.php /opt/sync-config.php
CMD php sync-config.php
