/**
  * Author: Martin Chukaleski 28.03
  */

#include <gtkmm.h>
#include <iostream>
#include <cstdint>
#include <chrono>
#include <sstream>
#include <thread>

#include "cluon/OD4Session.hpp"
#include "cluon/Envelope.hpp"

#include "messages.hpp"
#include "VControl.hpp"

cluon::OD4Session *od4p;
VControl car;

using namespace std;

//functions that are triggered when a button is pressed
void on_forward_press();
void on_stop_rel();
void on_right_press();
void on_left_press();

int main(int argc, char* argv[]){

	auto arguments = cluon::getCommandlineArguments(argc, argv);
    	// convert the arg to correct type
    	//the cid is used to receive and store data about distance, angle and speed
    	const uint16_t cid = (uint16_t) std::stoi(arguments["cid"]);

	od4p = new cluon::OD4Session(cid, [](cluon::data::Envelope &&envelope) noexcept {});
	
	//creating the main kit from gtk
	Gtk::Main kit(argc,argv);
	
	//Initializing the box and window
	Gtk::Window window;
	Gtk::Box box;

    Gtk::Image rightImg("right.png");
	
	//initializing the buttons
	Gtk::Button forward(" ^ ");
	Gtk::Button left("<");
	Gtk::Button right(">");
	Gtk::Button stop("STOP");

	
	//setting the size, title and position // 400 , 50
	window.set_default_size(400, 50);
	window.set_title("GROUP3 GUI REMOTE CONTROLLER");
	window.set_position(Gtk::WIN_POS_CENTER);


	forward.set_size_request(15,15);
	
	//adding the box which holds the buttons in place to the window
	window.add(box);
	box.pack_start(forward);
	//packing the buttons so they all have the correct size according to the text
	box.pack_start(left);
	box.pack_start(right);
	box.pack_start(stop);

	//on press the function sends a request to move the car forward
	forward.signal_pressed().connect(
		sigc::ptr_fun(&on_forward_press)
		);
	//on release of button the function sends a request to stop the car
	forward.signal_released().connect(
		sigc::ptr_fun(&on_stop_rel)
		);

	right.signal_pressed().connect(
		sigc::ptr_fun(&on_right_press)
		);

	right.signal_released().connect(
		sigc::ptr_fun(&on_stop_rel)
		);

	left.signal_pressed().connect(
		sigc::ptr_fun(&on_left_press)
		);

	left.signal_released().connect(
		sigc::ptr_fun(&on_stop_rel)
		);

	stop.signal_pressed().connect(
		sigc::ptr_fun(&on_stop_rel)
		);

	stop.signal_released().connect(
		sigc::ptr_fun(&on_stop_rel)
		);

	//showing the box that contains the children
	window.show_all_children();
	
	//run the app with the window
	Gtk::Main::run(window);

	return 0;
}

//methods that are used to call the corresponding functions from the VControl object
void on_forward_press(){
	cout << "==> MOVE FORWARD" << endl;
	car.moveForward(od4p);
}

void on_right_press(){
	cout << "==> TURN RIGHT" << endl;
	car.turnRight(od4p);

}

void on_left_press(){
	cout << "==> TURN LEFT" << endl;
	car.turnLeft(od4p);
}

void on_stop_rel(){
	cout << "<== STOP" << endl;
    car.stop(od4p);
}
