# DIT168-Project-Industrial IT and Embedded Systems 

****************************************************************************************************

# How to package and release the binaries 

### Running and testing the build on the car:

#### Option 1 use docker hub

##### 1. Build the image using this command.
`docker build -t dit168 -f Dockerfile.armhf .`

##### 2. Login to docker using your account.
`docker login `

##### 3. Push the image to your repo
`docker push reponame/dit168 `

##### 4. Turn the car on connect to the WIFI hotspot.
`no need to explain this i assume.. `

##### 5. Open a new terminal and ssh to the car using the following command.
`ssh debian@192.168.8.1`

`password: temppwd`

##### 6. Create a new folder to test your build give a name in the format mm_dd_YOURNAME we will use this to trace the working builds.
`mkdir mm_dd_YOURNAME`

##### 7. Go inside the folder and transfer your docker compose yml file using the following commands.
`cd mm_dd_YOURNAME`

`scp [file_name] debian@192.168.8.1:[target_path]`

##### 8. Now you have to pull the image from your docker hub NOTE! you have to be connected to a wifi network with an internet connection , if not follow the steps from bellow.
`docker login `

`docker pull reponame/dit168 `

##### 9. The image se-research is on the car so there is no need to pull it, now you can test your code running this command:
`docker-compose up `

##### 10. This command terminates the docker compose:
`docker-compose stop `
###### or 
`CTRL + C `

##### 10. Did your build work ? If not use this command:
`sudo work_harder now `



### Saving and sharing Docker image as a tar file using scp if you cannot connect to a wifi network:

`docker save dit168 > dit168.tar`

`cat dit168.tar | docker load`

`scp dit168.tar debian@192.168.8.1:[target_path]`

****************************************************************************************************

[![Build Status](https://travis-ci.org/DIT168-Group3/DIT168.svg?branch=master)](https://travis-ci.org/DIT168-Group3/DIT168)

