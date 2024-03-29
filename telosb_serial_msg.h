#ifndef SERIAL_MSG
#define SERIAL_MSG

typedef nx_struct telosb_serial_msg
{
  nx_float raw_voltage_monitoramento;
  nx_float raw_voltage_analise;
  nx_float raw_voltage_planejamento;
  nx_float raw_voltage_execucao;
  nx_float raw_voltage_geral;
  nx_uint16_t raw_temperature;
  nx_uint16_t raw_voltage;
  nx_uint16_t raw_msg_number;
  nx_uint16_t raw_node_ID;

  nx_float converted_voltage_monitoramento;
  nx_float converted_voltage_analise;
  nx_float converted_voltage_planejamento;
  nx_float converted_voltage_execucao;
  nx_float converted_voltage_geral;
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
