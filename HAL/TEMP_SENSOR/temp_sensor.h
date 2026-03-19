#ifndef TEMP_SENSOR_H_
#define TEMP_SENSOR_H_

/*********************Registers Address*********************/
#define TEMP_SENSOR_ADDRESS 0x48
#define TEMP_REG            0x00
#define CONFIGURATION_REG   0x01
#define THYST_REG           0x02
#define TOS_REG             0x03

/*********************Sensor's Modes************************/
#define SHUTDOWN_MODE       0x01
#define NORMAL_MODE         0x00


/***********************Functions****************************/
void Temp_Sensor_Init();
void Temp_Sensor_config(uint8 config);
float temp_reading();
void setThyst(float temp);
void setTos(float temp);

#endif /* TEMP_SENSOR_H_ */
