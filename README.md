# DIT168-Project-Industrial IT and Embedded Systems 
Link: https://github.com/martincukal/DIT168

*****************************************************************************************************

## Introduction

The purpose of this project is to develop a self-driving vehicle by working on an embedded system that can be divided into sub-systems. 
As a group, we are going to follow some steps to achieve the project’s goal. The steps are:

1- Working on the project (self-driving vehicle) according to the requirements (functional and non-functional) that are provided by the customer (teacher). 

2- Researching for suitable algorithms that can be implemented, for lane detection, lane following and being used for vehicle-to-vehicle communication (V2V).

3- Implementing and adapting desired algorithms to the project and making sure that they meet the customer’s requirements.
 
4- Testing and evaluating the implemented algorithms.

5- Finally, documenting the previous steps; hardware & software that’s used, algorithms (code) that are implemented, test methods that are applied and project’s retrospective (e.g. lessons learned).

*****************************************************************************************************

## Git Workflow

The team will develop the project by making use of GIT’s branching system. The workflow we will use for the branches is called feature branching, and the way it works is that we create a branch for every feature being developed, with the end aim of merging them into one branch. To merge these feature branches, we will make use of pull requests, which is created once a feature is done, and its purpose is to create discussion around the commit. We will also make use of pull requests when the work in progress is having trouble fullfilling a requirement. The pull request allows other team members to comment on and provide suggestions for the pull requests.

The way this will work is that we will have 3 fixed branches, and a branch for each feature. While working on each feature, the team will push the changes to the appropriate branch, and once the feature is ready to be tested, it will be pushed to the beta branch. This allows the team to work efficiently on seperate features, and then to focus on integration process afterwards. The beta branch will consist of all the features from the individual feature branches, finally the developer branch will be used for maintaining a stable version of the system. The master branch will be used to store the final version of the system, which will be used for deployment purposes and its goal is to be bug-free.

****************************************************************************************************

### Cloning, building and testing the project steps

Linux OS:

#### 1. After the repository is cloned you should open a terminal inside the Communication example folder.

#### 2. In the terminal write  to create a build directory for the binaries.
` mkdir build `

#### 3. Go inside the build folder.
`cd build `

#### 4. Run CMake .
` cmake .. `

#### 5. Run make.
` make `

#### 6. Run the generated main binary to test the program.
` ./main `

#### 7. Open a new terminal in the build directory.
` CTRL + SHIFT + N `

#### 8. Run the generated main binary in the newly opened terminal.
` ./main `

#### 9. The program will require you to enter a number, after entering it check the second terminal a “ Received message : #number ” should be displayed.
