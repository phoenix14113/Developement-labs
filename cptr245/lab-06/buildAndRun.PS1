#!/bin/bash
cd code
docker-compose up --build
docker cp gcc:/usr/src/code/area ..
docker-compose down
cd ../web
cp ../area ./cgi-bin/
docker-compose up --build
cd ..