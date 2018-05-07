# Remote Control with Graphical Interface to control the scaled car

*****************************************************************************************************

## How to use

#### For this application the gtkmm library is used. What is GTK+?
#### GTK+ is the GUI widget toolkit, written in C, which serves as the foundation for the GNOME project as well as many stand-alone #### applications. GTK+ is the foundation on which gtkmm is built. See http://www.gtk.org/ .

#### To be able to run this app you have to first instal gtkmm with this command:
` sudo apt-get install libgtkmm-3.0-dev `

##### 1. After the repository is cloned you should open a terminal inside the Remote Control GUI folder.

##### 2. In the terminal write  to create a build directory for the binaries.
` mkdir build `

##### 3. Go inside the build folder.
`cd build `

##### 4. Run CMake .
` cmake .. `

##### 5. Run make.
` make `

##### 6. Run the generated binary to test the program.
` ./RemoteGUI.main --cid=###`

