#!/bin/bash

gradle clean
gradle build
gradle test 
gradle jacocoTestReport
