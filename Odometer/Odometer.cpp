#include "cluon/OD4Session.hpp"
#include "cluon/Envelope.hpp"
#include "messages.hpp"
#include "rc_usefulincludes.h"
#include "roboticscape.h"


/*******************************************************************************
* 
*A program that reads  odometer's data.
* Reference: https://github.com/StrawsonDesign/Robotics_Cape_Installer
* Author: Yazan Alsahhar 2018-04-03
*
*******************************************************************************/

/*
int rc_initialize_imu_dmp(imu_data_t* data, imu_config_t conf); // Initializing the imu for DMP operation
int rc_set_imu_interrupt_func(int (*func)(void));               // Used to assign which of the functions should be called every time the IMU has new data available
int rc_stop_imu_interrupt_func();                               // Used to temporarily stop the function from being called
int rc_read_accel_data(imu_data_t* data);                       // Used to read the accelerometer data
*/

//IMU Data Struct

typedef struct rc_imu_data_t{
	
	int16_t raw_accel[3];            // 16 bit raw adc readings from each sensor (X/Y/Z)
	
} rc_imu_data_t; 

int main(){

        cluon::OD4Session *od4 = new cluon::OD4Session (111,[](cluon::data::Envelope) noexcept {});
        
        opendlv::proxy::OdometerReading msgValue;
            
        float accel[raw_accel];	         // Used for displaying Sensor values in an arrays containing X, Y, and Z axis values in that order.
        float temp;                      // Used for displaying degrees Celsius  
        bool status = true;              // Used for while loop 
        rc_imu_data_t data;              // Struct to hold new data
	
	// IMU default confiruration
	rc_imu_config_t conf = rc_default_imu_config();

	if(rc_initialize_imu_dmp(&data, conf)){
		cout << "rc_initialize_imu_failed\n" << endl;
		return -1;
	}

	while (status) {
           	
		// Printing the accelerometer data
		if(rc_read_accel_data(&data) < 0){
                        cout << "read accel data failed \n" << endl;

     
		
                }
		else{
                  msgValue.OdometerReading(accel[data.raw_accel]);
                     cout << "The accelerometer data are: %6.2f %6.2f %6.2f |" << data.raw_accel[0] << data.raw_accel[1] << data.raw_accel[2] << endl;
		}
		
		// Reading the temperature
		if(rc_read_imu_temp(&data) < 0){
                        cout << "read temp data failed \n" << endl;
                return -1;
		}
		else{
                        cout << "%4.1f" << data.temp << endl;
														
		fflush(stdout);
		rc_usleep(100000);
                }
	        }
        // For sending a message
        od4->send(msgValue);

        // Turning off and cleaning up the IMU
	rc_power_off_imu();
	rc_cleanup();
	
        return 0;
}

