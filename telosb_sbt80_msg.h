#ifndef TELOSB_SBT80_MSG
#define TELOSB_SBT80_MSG

typedef nx_struct telosb_sbt80_msg
{
  nx_float converted_temperature;
  nx_float converted_voltage_monitoramento;
  nx_float converted_voltage_analise;
  nx_float converted_voltage_planejamento;
  nx_float converted_voltage_execucao;
  nx_float converted_voltage_geral;
  nx_uint16_t msg_number;
  nx_uint16_t node_ID;
} telosb_sbt80_msg_t;

enum
{
  AM_TELOSB_SBT80_MSG = 102,
};

#endif
