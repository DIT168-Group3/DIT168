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

void on_forward_press();
void on_stop_rel();
void on_right_press();
void on_left_press();

int main(int argc, char* argv[]){
	od4p = new cluon::OD4Session(111, [](cluon::data::Envelope &&envelope) noexcept {});

	Gtk::Main kit(argc,argv);

	Gtk::Window window;
	Gtk::Box box;

	Gtk::Button forward("FORWARD");
	Gtk::Button left("LEFT");
	Gtk::Button right("RIGHT");
	Gtk::Button stop("STOP");

	window.set_default_size(400, 50);
	window.set_title("GROUP3 GUI REMOTE CONTROLLER");
	window.set_position(Gtk::WIN_POS_CENTER);

	/*
	forward.show();
	left.show();
	right.show();
	stop.show();
	*/

	forward.set_size_request(15,15);

	window.add(box);
	box.pack_start(forward);
	box.pack_start(left);
	box.pack_start(right);
	box.pack_start(stop);

	forward.signal_pressed().connect(
		sigc::ptr_fun(&on_forward_press)
		);

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

	window.show_all_children();

	Gtk::Main::run(window);

	return 0;
}

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