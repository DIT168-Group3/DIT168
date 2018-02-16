# Introduction

The purpose of this project is to develop a self-driving vehicle by working on an embedded system that can be divided into sub-systems. 

As a group, we are going to follow some steps to achieve the project’s goal. The steps are:

1- Working on the project (self-driving vehicle) according to the requirements (functional and non-functional ) that are provided by the customer (teacher). 

2- Researching for suitable algorithms that can be implemented, for lane detection, lane following and being used for vehicle-to-vehicle communication (V2V).

3- Implementing and adapting desired algorithms to the project and making sure that they meet the customer’s requirements.
 
4- Testing and evaluating the implemented algorithms.

5- Finally, documenting the previous steps; hardware & software that’s used, algorithms (code) that are implemented, test methods that are applied and project’s retrospective (e.g. lessons learned).
*****************************************************************************************************

# Git work layout

The team will develop the project by making use of GIT’s branching system. The way this will work is that we will have 3 fixed branches, and a branch for each feature. While working on each feature, the team will push the changes to the appropriate branch, and once the feature is ready to be tested, it will be pushed to the beta branch. The beta branch will consist of all the features from the individual feature branches, finally the developer branch will be used for maintaining a stable version of the system. The master branch will be used to store the final version of the system, which will be used for deployment purposes.

Mention that the team will work on seperate branches depending on the feature currently being worked on. When that feature is working but not 100% stable, we push to beta branch.
****************************************************************************************************

# Cloning, building and testing the project steps

For Linux:
1- After the repository is cloned you should open a terminal inside the Communication example folder.
2- In the terminal write “ mkdir build ” to create a build directory for the binaries.
3- Copy messages.cpp and messages.hpp into the build folder
4- Go inside the build folder “ cd build “ 
5- Run CMake “ cmake .. “
6- Run make “ make ”
7- Run the generated main binary “ ./main “
8- Open a new terminal in the build directory “ CTRL + SHIFT + N “
9- Run the generated main binary in the newly opened terminal “ ./main “
10- The program will require you to enter a number, after entering it check the second terminal a “ Received message : #number “ should be displayed.
