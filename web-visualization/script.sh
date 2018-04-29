#!/bin/bash
#Author: Martin Chukaleski
# This is a script used to build and run the web signal viewer on port 8085 and use the 200 cid since our v2v broadcast channel is using that cid.

docker build -t webgui -f Dockerfile .
echo "Running the docker container on port 8085 "
docker run --rm -ti --net=host -p 8085:8085 webgui --cid=200
echo "Open =====> localhost:8085 "


