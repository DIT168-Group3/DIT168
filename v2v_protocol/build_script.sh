#!/bin/bash
#Author: Martin Chukaleski
# This is a script used to build and save the image

echo "Building the image"
docker build -t v2v -f Dockerfile.armhf .
echo "Saving the image ... "
docker save v2v > v2v.tar
echo "Image is saved as v2v.tar in the current directory "
