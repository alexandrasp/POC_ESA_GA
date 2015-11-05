#include "headers/telosb_serial_msg.h"
#include "headers/telosb_sbt80_msg.h"

configuration SerialAppC
{
}

implementation
{
  components MainC, SerialC as App;
  components LedsC;
  components new TimerMilliC() as TimerSensoring;
  components new TimerMilliC() as TimerPropagation;
  App.Boot -> MainC.Boot;
  App.Leds -> LedsC;
  App.TimerSensoring -> TimerSensoring;
  App.TimerPropagation -> TimerPropagation;

  // Radio
  components ActiveMessageC as Radio;
  App.RadioPacket -> Radio;
  App.RadioControl -> Radio;
  App.RadioSend -> Radio.AMSend[AM_TELOSB_SBT80_MSG];

  // Serial
  components SerialActiveMessageC as Serial;
  App.SerialPacket -> Serial;
  App.SerialControl -> Serial;
  App.SerialSend -> Serial.AMSend[AM_TELOSB_SERIAL_MSG];

  // Sensors
  components new SensirionSht11C();
  //components new HamamatsuS10871TsrC();
  components new VoltageC();
  //App.LightSensor -> HamamatsuS10871TsrC;
  //App.HumiditySensor -> SensirionSht11C.Humidity;
  App.TemperatureSensor -> SensirionSht11C.Temperature;
  App.Voltage -> VoltageC;
}


