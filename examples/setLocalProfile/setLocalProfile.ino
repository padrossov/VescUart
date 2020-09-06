/*
  Name:    setLocalProfile.ino
  Created: 19-08-2018
  Author:  Mr_fish77
  Description: Example to use the setLocalProfile method, to modify the max speed
*/

#include <VescUart.h>

/** Initiate VescUart class */
VescUart UART;

void setup() {

  /** Setup Serial port to display data */
  Serial.begin(115200);

  /** Setup UART port (Serial1 on Atmega32u4) */
  Serial1.begin(115200);

  while (!Serial) {
    ;
  }
  /** Define which ports to use as UART */
  UART.setSerialPort(&Serial1);
  UART.setDebugPort(&Serial);
  delay(2000);

  /** Call the function getVescValues() to acquire data from VESC */
  if ( UART.getFWversion()) {
    Serial.print("FW v");
    Serial.print(UART.fw_version.major);
    Serial.print(".");
    Serial.println(UART.fw_version.minor);

  }
  else
  {
    Serial.println("Failed to get data!");
  }


  delay(1000);
  Serial.println("Set new  profile!");

  bool store = false;
  bool forward_can = false;
  bool ack = false;
  bool divide_by_controllers = false;
  float current_min_rel = 1.0;
  float current_max_rel = 1.0;
  float speed_max_reverse = -15;
  float speed_max = 15;
  float duty_min = 0.005;
  float duty_max = 0.95;
  float watt_min = -1500000.0;
  float watt_max = 1500000.0 ;

  /**
     @brief      Set a profile
     @param    store save persistently the new profile in vesc memory
     @param    forward_can forward profile to slave Vesc through  can bus (not tested)
     @param    divide_by_controllers divied the watt limit by the number of VESC
     @param    current_min_rel this value is multiplied with the maximum current. It is a convenient method to scale the current limits without forgetting the actual maximum value.  DEFAULT = 1
     @param    current_min_rel this value is multiplied with the minimum current. It is a convenient method to scale the current limits without forgetting the actual minimal value.  DEFAULT = 1
     @param    speed_max_reverse maximum reverse speed in m/s. In order, to use it make sure to set the wheel diameter and gear ratio in VESC Tool   (m/s = (km/h / 3.6) )
     @param    speed_max_reverse maximum speed in m/s. In order, to use it make sure to set the wheel diameter and gear ratio in VESC Tool
     @param    duty_min minimum duty cycle. DEFAULT = 0.005
     @param    duty_min maximum duty cycle. DEFAULT = 1
     @param    watt_min minimum watt value. DEFAULT = - 1500000.0
     @param    watt_max maximum watt value. DEFAULT =  1500000.0
  */
  UART.setLocalProfile(store, forward_can, divide_by_controllers, current_min_rel, current_max_rel, speed_max_reverse, speed_max, duty_min, duty_max, watt_min, watt_max);

  delay(1000);
}

void loop() {

}
