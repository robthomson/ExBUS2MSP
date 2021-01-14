/*
  Copyright (C) Rob Thomson

  This program is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License version 2 as
  published by the Free Software Foundation.
 
  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.
  Jeti  EX Bus C++ Library for Teensy 3.x
  -------------------------------------------------------------------
  
  Copyright (C) 2018 Bernd Wokoeck
  
  Version history:
  0.90   02/04/2018  created
  0.91   02/09/2018  Support for AtMega32u4 added
  0.92   02/14/2018  Support for ESP32 added
  0.93   02/16/2018  ESP32 uart initialization changed
  0.94   02/17/2018  Generic arduino HardwareSerial support for AtMega328PB
  0.95   03/17/2018  Synchronization (IsBusReleased) for time consuming operations
  Permission is hereby granted, free of charge, to any person obtaining
  a copy of this software and associated documentation files (the "Software"),
  to deal in the Software without restriction, including without limitation
  the rights to use, copy, modify, merge, publish, distribute, sublicense,
  and/or sell copies of the Software, and to permit persons to whom the
  Software is furnished to do so, subject to the following conditions:
  The above copyright notice and this permission notice shall be included in
  all copies or substantial portions of the Software.
  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
  OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
  THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
  FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
  IN THE SOFTWARE.
**************************************************************/

 
#include "JetiExBusProtocol.h"
#include "EXBUS2MSP.h"
#include "ExbusSensor.h"
#include <stdint.h> 
#include <limits.h>
#include "RTClib.h"
#include <Time.h>
#include <inttypes.h>


int channelPulse=PULSE_LOW;

JetiExBusProtocol exBus;
ExbusSensor        exbusSensor; 


enum
{
  ID_VAL0
};





// sensor definition (max. 31 for DC/DS-16)
// name plus unit must be < 20 characters
// precision = 0 --> 0, precision = 1 --> 0.0, precision = 2 --> 0.00

JETISENSOR_CONST sensors[] PROGMEM =
{
  // id             name          unit         data type             precision 
  { ID_VAL0,      "Voltage",        "V",       JetiSensor::TYPE_14b, 1 },
  { 0 } // end of array
};



void setup()
{
  Serial.begin(9600);


	exBus.SetDeviceId(0x76, 0x32); // 0x3276
	exBus.Start("EXBUS2MSP", sensors, 2 ); // com port: 1..3 for Teeny, 0 or 1 for AtMega328PB UART0/UART1, others: not used 


}


void loop()
{



   //run jeti telemetry and pulses
   if ( exBus.HasNewChannelData() )
  {

  #ifdef DEBUG  
  Serial.print("CH");
  Serial.print(ARM_CHANNEL);
  Serial.print(" ");
  Serial.println(exBus.GetChannel(ARM_CHANNEL));
  #endif

  channelPulse = exBus.GetChannel(ARM_CHANNEL);

      if((channelPulse >= ARM_PULSE_LOW) && (channelPulse <= ARM_PULSE_HIGH)){
        Serial.println("ARMED");  
      } else {
        Serial.println("DISARMED");    
      }

  
  }

   exBus.DoJetiExBus();



}
