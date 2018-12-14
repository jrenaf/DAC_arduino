#include <ros.h>
#include <ArduinoHardware.h>
#include <std_msgs/Empty.h>
#include <Wire.h>
#include <Adafruit_MCP4725.h>

Adafruit_MCP4725 dac1(2); // ADDR pin of MCP4725 connected to Arduino pin 2
Adafruit_MCP4725 dac2(3); // ADDR pin of MCP4725 connected to Arduino pin 3
Adafruit_MCP4725 dac3(4); // ADDR pin of MCP4725 connected to Arduino pin 4
Adafruit_MCP4725 dac4(5); // ADDR pin of MCP4725 connected to Arduino pin 5

int i=1;
ros::NodeHandle nh;

void messageCb( const std_msgs::Empty& toggle_msg){
  dac1.setVoltage(2000,false);
  dac2.setVoltage(2000,false);
  if(i==1){i=0;}
  else{i=1;}
}
ros::Subscriber<std_msgs::Empty> sub("soft", &messageCb );

void setup(void) {
  Serial.begin(9600);
  Serial.println("Hello!");

  // The begin method must be called with the address of the MCP4725 when ADDR pin is tied to VCC
  // For Adafruit MCP4725A1 this is 0x63
  // For MCP4725A0 this is 0x61
  // For MCP4725A2 this is 0x65
  dac1.begin(0x61);
  dac2.begin(0x61);
  dac3.begin(0x61);
  dac4.begin(0x61); 
  Serial.println("Good Luck");
  
  nh.initNode();
  nh.subscribe(sub);
}

void loop(void) {
//  dac1.setVoltage(1000, false);
//  dac2.setVoltage(2000, false);
//  dac3.setVoltage(3000, false);
//  dac4.setVoltage(4000, false);
  nh.spinOnce();
  delay(0.1);
}
