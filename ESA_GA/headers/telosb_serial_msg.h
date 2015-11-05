#ifndef SERIAL_MSG
#define SERIAL_MSG

typedef nx_struct telosb_serial_msg
{
  nx_float raw_voltage;
  nx_float raw_temperature;
  nx_uint16_t r_msg_number;
  nx_uint16_t r_node_ID;

  nx_float converted_voltage;
  nx_float converted_temperature;
  nx_uint16_t msg_number;
  nx_uint16_t node_ID;
  
} telosb_serial_msg_t;

enum
{
  AM_TELOSB_SERIAL_MSG = 101,
};

#endif
