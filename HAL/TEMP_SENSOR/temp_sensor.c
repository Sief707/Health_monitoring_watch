#include"twi.h"
#include"temp_sensor.h"


void Temp_Sensor_Init()
{
	Temp_Sensor_config(0x00);  // operating sensor in normal configurations so it reads the temperature continuously
}

void Temp_Sensor_config(uint8 config)
{
	
	TWI_start();  // starting the communication
	TWI_writeByte((TEMP_SENSOR_ADDRESS<< 1) | 0); // selection for the I2C bus (the shift is for the R/W bit 0 = write & 1 = read)
	
	TWI_writeByte(CONFIGURATION_REG); // selection for the needed register in the sensor by its address
	TWI_writeByte(config); // fills the needed bits in the configuration register
	
	TWI_stop(); // finishing the communication
}
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                    
float temp_reading()
{
	uint8 LSB,MSB;
	uint16 raw_value;

	TWI_start();
	TWI_writeByte((TEMP_SENSOR_ADDRESS<< 1) | 0);
	TWI_writeByte(TEMP_REG);
	
	TWI_start();
	TWI_writeByte((TEMP_SENSOR_ADDRESS<< 1) | 1);

	MSB = TWI_readByteWithACK(); // waiting for more bytes
	LSB = TWI_readByteWithNACK(); // reading the last byte

	TWI_stop();

	raw_value = (MSB << 8) | LSB;

	return ((raw_value / 256.0)+ 8.0); // (256) according to the sensor precision

}





// This function sets the lower threshold in the sensor
void setThyst(float temp)
{
	

	uint16 raw = temp * 256; // convert temperature into the register format

	TWI_start();
	TWI_writeByte((TEMP_SENSOR_ADDRESS<<1) | 0);
	TWI_writeByte(THYST_REG);

	// According to the read sequence of the sensor it reads the MSB then the LSB
	TWI_writeByte(raw>>8);  // extracting only the 8 MSB
	TWI_writeByte(raw);  // only the lower 8 bits will be taken
	TWI_stop();

}

// This function sets the upper threshold in the sensor
void setTos(float temp)
{
	
	uint16 raw = temp * 256; // convert temperature into the register format

	TWI_start();
	TWI_writeByte((TEMP_SENSOR_ADDRESS<<1) | 0);
	TWI_writeByte(TOS_REG);

	// According to the read sequence of the sensor it reads the MSB then the LSB
	TWI_writeByte(raw>>8);  // extracting only the 8 MSB
	TWI_writeByte(raw);  // only the lower 8 bits will be taken
	TWI_stop();

}
