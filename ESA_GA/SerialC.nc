#include "Timer.h"
#include "config.h"
#include "ESA_GA.h"


int SENSOR_INTERVAL = 2000;
int PROPAGATION_INTERVAL = 4000;

module SerialC
{
  uses
  {
    interface Boot;
    interface Leds;
    interface Timer<TMilli> as TimerPropagation;
    interface Timer<TMilli> as TimerSensoring;

    // Radio
    interface AMSend as RadioSend;
    interface Packet as RadioPacket;
    interface SplitControl as RadioControl;

    // Serial
    interface AMSend as SerialSend;
    interface Packet as SerialPacket;
    interface SplitControl as SerialControl;
    // Sensors
    //interface Read<uint16_t> as LightSensor;
    //interface Read<uint16_t> as HumiditySensor;
    interface Read<uint16_t> as TemperatureSensor;
    interface Read<uint16_t> as Voltage;
    
  }
}

implementation
{
  Temp knowledge_base_real;
  telosb_sbt80_msg_t* radio;
  telosb_serial_msg_t* serial;
  message_t radioPacket;
  message_t serialPacket;
  uint16_t msg_number=0;
    
  void sendSerial()
  {
    if ( serial != NULL )
    {
      call SerialSend.send(AM_BROADCAST_ADDR, &serialPacket, sizeof(telosb_serial_msg_t));
      
    }
  }

  void sendRadio()
  {
    if ( radio != NULL )
    {

      call RadioSend.send(SBT80_NODE_ID, &radioPacket, sizeof(telosb_sbt80_msg_t));


    }
  }


  event void Boot.booted()
  {
    call RadioControl.start();
    call SerialControl.start();
    serial = (telosb_serial_msg_t*)call SerialPacket.getPayload(&serialPacket, sizeof(telosb_serial_msg_t));
    radio = (telosb_sbt80_msg_t*)call RadioPacket.getPayload(&radioPacket, sizeof(telosb_sbt80_msg_t));
  }

  event void SerialControl.startDone( error_t err )
  {
    call TimerSensoring.startPeriodic( SENSOR_INTERVAL );
    call TimerPropagation.startPeriodic( PROPAGATION_INTERVAL );
  }

  event void SerialControl.stopDone( error_t err )
  {
  }

  event void RadioControl.startDone( error_t err ) {}
  event void RadioControl.stopDone( error_t err ) {}

  event void TimerSensoring.fired()
  {
    //start first sensor
    //call LightSensor.read();
    startList(&knowledge_base_real);
    startListAG(&knowledge_base_real);
    call Voltage.read();
    //call TemperatureSensor.read();
  }

  event void TimerPropagation.fired()
  {
    msg_number++;
    //call Voltage.read();
    sendSerial();
  }

  // Sensor Formulas:
  // http://docs.tinyos.net/tinywiki/index.php/Boomerang_ADC_Example#External_Humidity_and_Temperature_Sensors

  /*event void LightSensor.readDone( error_t result, uint16_t val )
  {
    // V = ( val / 4096 ) * 1.5
    // I = V / 100000.0
    // lx = 0.769 * 1e5 * I * 1000
    // lx = 0.2816 * val
    serial->raw_light = val;
    radio->converted_light = serial->converted_light = 0.2816 * (float)val;
    call TemperatureSensor.read();
  }*/

  event void TemperatureSensor.readDone( error_t result, uint16_t val )
  { 
    int temp_real=0;
    // T = -39.6 + 0.01 * val
    serial->raw_temperature = val;
    serial->r_node_ID = TOS_NODE_ID;
    serial->r_msg_number = msg_number;
    radio->converted_temperature = serial->converted_temperature = -39.6 + 0.01 * (float)val;
    temp_real =-39.6 + 0.01 * (float)val;
    radio->node_ID = serial->r_node_ID;
    radio->msg_number = serial->r_msg_number;
    //sendSerial();
    knowledge_base_control(&knowledge_base_real, temp_real);
    planning(data_analysis(&knowledge_base_real, temp_real), &SENSOR_INTERVAL, &PROPAGATION_INTERVAL);
    sendSerial();
  } 

  event void Voltage.readDone( error_t result, uint16_t val )
  {
    // T = -39.6 + 0.01 * val
    serial->raw_voltage = val;
    radio->converted_voltage = serial->converted_voltage =  ((float)val/4096) *3;
    call TemperatureSensor.read();
    //sendSerial();
  }

  /*event void HumiditySensor.readDone( error_t result, uint16_t val )
  {
    float linear_humidity;
    serial->raw_humidity = val;
    linear_humidity = -0.0000028 * val * val + 0.0405 * val - 4.0;
    radio->converted_humidity = serial->converted_humidity = ( radio->converted_temperature - 25.0 ) * ( 0.01 + 0.00008 * val ) + linear_humidity;
    sendSerial();
  }*/

  event void SerialSend.sendDone( message_t* msg, error_t error )
  { 
      //msg_number++;
      sendRadio();
  }

  event void RadioSend.sendDone( message_t* msg, error_t error )
  {
  }

  
}
