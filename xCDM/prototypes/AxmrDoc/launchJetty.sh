#!/bin/sh
cd ../../document-managment
mvn install -DskipTests=true
cd ../prototypes/AxmrDoc/
mvn jetty:run

