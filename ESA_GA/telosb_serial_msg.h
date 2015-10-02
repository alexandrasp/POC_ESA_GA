#ifndef SERIAL_MSG
#define SERIAL_MSG

typedef nx_struct telosb_serial_msg
{
  //nx_uint16_t raw_light;
  //nx_uint16_t raw_humidity;
  nx_uint16_t raw_temperature;
  nx_uint16_t raw_voltage;
  nx_uint16_t raw_msg_number;
  nx_uint16_t raw_node_ID;

  //x_float converted_light;
  //nx_float converted_humidity;
  nx_float converted_temperature;
  nx_float converted_voltage;
  nx_uint16_t msg_number;
  nx_uint16_t node_ID;
  
} telosb_serial_msg_t;

enum
{
  AM_TELOSB_SERIAL_MSG = 101,
};

#endif
