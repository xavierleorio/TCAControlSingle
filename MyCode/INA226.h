#ifndef __INA226_H
#define __INA226_H
#include "sys.h"
#include "MYIIC.h"
#include "usart.h"

/**
 ********************************************************************************
 * @brief   STM32 HAL Library for INA226 Current/Power Monitor
 * @date    Feb 2016
 * @version 1.0
 * @author  George Christidis
 ********************************************************************************
 * @details
 This library contains the necessary functions to initialize, read and
 write data to the TI INA226 Current/Power Monitor using the I2C
 protocol.
 ******************************************************************************
 */
#define INA226_Nylon	0x82
#define INA226_Metal	0x80

#define INA226_CALIB_VAL		1280 //校准寄存器，最大6A,Current_LSB=6/(2^15)=0.00018,取0.0002A,R_shut=0.02,CAL=0.00512/0.0002/0.02=1280
#define INA226_CURRENTLSB		0.5F // mA/bit
#define INA226_CURRENTLSB_INV	1/INA226_CURRENTLSB // bit/mA
#define INA226_POWERLSB_INV		1/(INA226_CURRENTLSB*25) // bit/mW
#define INA226_I2CTIMEOUT		10

#define INA226_MANUF_ID_DEFAULT	0x5449
#define INA226_DIE_ID_DEFAULT		0x2260

//寄存器地址
#define INA226_CONFIG		0x00 // Configuration Register (R/W)
#define INA226_SHUNTV		0x01 // Shunt Voltage (R) 分流器电压，直接由ADC分流通道获取
#define INA226_BUSV			0x02 // Bus Voltage (R) 总线电压，直接由ADC总线通道获取
#define INA226_POWER		0x03 // Power (R) 功率，由总线电压和换算电流得出
#define INA226_CURRENT		0x04 // Current (R) 换算电流，由分流器电压和校准值得出
#define INA226_CALIB		0x05 // Calibration (R/W) 分流器电压校准值， 校准寄存器被设置前，电流和功率寄存器值保持为0
#define INA226_MASK			0x06 // Mask/Enable (R/W)
#define INA226_ALERTL		0x07 // Alert Limit (R/W)
#define INA226_MANUF_ID		0xFE // Manufacturer ID (R)
#define INA226_DIE_ID		0xFF // Die ID (R)

/*config 寄存器设置值*/

// Averaging Mode (AVG Bit Settings[11-9]) //平均数的数量
#define INA226_AVG_1				(0<<9)
#define INA226_AVG_4				(1<<9)
#define INA226_AVG_16				(2<<9)
#define INA226_AVG_64				(3<<9)
#define INA226_AVG_128				(4<<9)
#define INA226_AVG_256				(5<<9)
#define INA226_AVG_512				(6<<9)
#define INA226_AVG_1024				(7<<9)

// Bus Voltage Conversion Time (VBUS CT Bit Settings[8-6])//总线电压测量转换时间
#define INA226_VBUS_140uS			(0<<6)
#define INA226_VBUS_204uS			(1<<6)
#define INA226_VBUS_332uS			(2<<6)
#define INA226_VBUS_588uS			(3<<6)
#define INA226_VBUS_1100uS			(4<<6)
#define INA226_VBUS_2116uS			(5<<6)
#define INA226_VBUS_4156uS			(6<<6)
#define INA226_VBUS_8244uS			(7<<6)

// Shunt Voltage Conversion Time	(VSH CT Bit Settings[5-3])//分流电压测量转换时间
#define INA226_VSH_140uS			(0<<3)
#define INA226_VSH_204uS			(1<<3)
#define INA226_VSH_332uS			(2<<3)
#define INA226_VSH_588uS			(3<<3)
#define INA226_VSH_1100uS			(4<<3)
#define INA226_VSH_2116uS			(5<<3)
#define INA226_VSH_4156uS			(6<<3)
#define INA226_VSH_8244uS			(7<<3)

// MODE SET	(MODE Bit Settings[2-0])//模式设置
#define INA226_MODE_POWER_DOWN			(0<<0) // Power-Down
#define INA226_MODE_TRIG_SHUNT_VOLTAGE	(1<<0) // Shunt Voltage, Triggered
#define INA226_MODE_TRIG_BUS_VOLTAGE	(2<<0) // Bus Voltage, Triggered
#define INA226_MODE_TRIG_SHUNT_AND_BUS	(3<<0) // Shunt and Bus, Triggered
#define INA226_MODE_POWER_DOWN2			(4<<0) // Power-Down
#define INA226_MODE_CONT_SHUNT_VOLTAGE	(5<<0) // Shunt Voltage, Continuous
#define INA226_MODE_CONT_BUS_VOLTAGE	(6<<0) // Bus Voltage, Continuous
#define INA226_MODE_CONT_SHUNT_AND_BUS	(7<<0) // Shunt and Bus, Continuous //正常模式

// Reset Bit (RST bit [15]) //复位
#define INA226_RESET_ACTIVE			(1<<15)
#define INA226_RESET_INACTIVE		(0<<15)

/*警报寄存器*/

// Mask/Enable Register
#define INA226_MER_SOL				(1<<15) // Shunt Voltage Over-Voltage
#define INA226_MER_SUL				(1<<14) // Shunt Voltage Under-Voltage
#define INA226_MER_BOL				(1<<13) // Bus Voltagee Over-Voltage
#define INA226_MER_BUL				(1<<12) // Bus Voltage Under-Voltage
#define INA226_MER_POL				(1<<11) // Power Over-Limit
#define INA226_MER_CNVR				(1<<10) // Conversion Ready
#define INA226_MER_AFF				(1<<4)  // Alert Function Flag
#define INA226_MER_CVRF				(1<<3)  // Conversion Ready Flag
#define INA226_MER_OVF				(1<<2)  // Math Overflow Flag
#define INA226_MER_APOL				(1<<1)  // Alert Polarity Bit
#define INA226_MER_LEN				(1<<0)  // Alert Latch Enable

typedef struct INA226
{
	s16 VBUS;
	s16 VSH;
	s16 CURRENT;
	s16 POWER;
} INA226Typedef;

s16 InitINA226(void);

float INA226GetData(INA226Typedef *ina226data,u8 INA226_ADDRESS);

#endif
/*
 Kernel driver ina2xx
 ====================

 Supported chips:
 * Texas Instruments INA219
 Prefix: 'ina219'
 Addresses: I2C 0x40 - 0x4f
 Datasheet: Publicly available at the Texas Instruments website
 http://www.ti.com/

 * Texas Instruments INA220
 Prefix: 'ina220'
 Addresses: I2C 0x40 - 0x4f
 Datasheet: Publicly available at the Texas Instruments website
 http://www.ti.com/

 * Texas Instruments INA226
 Prefix: 'ina226'
 Addresses: I2C 0x40 - 0x4f
 Datasheet: Publicly available at the Texas Instruments website
 http://www.ti.com/

 * Texas Instruments INA230
 Prefix: 'ina230'
 Addresses: I2C 0x40 - 0x4f
 Datasheet: Publicly available at the Texas Instruments website
 http://www.ti.com/

 * Texas Instruments INA231
 Prefix: 'ina231'
 Addresses: I2C 0x40 - 0x4f
 Datasheet: Publicly available at the Texas Instruments website
 http://www.ti.com/

 Author: Lothar Felten <l-felten@ti.com>

 Description
 -----------

 The INA219 is a high-side current shunt and power monitor with an I2C
 interface. The INA219 monitors both shunt drop and supply voltage, with
 programmable conversion times and filtering.

 The INA220 is a high or low side current shunt and power monitor with an I2C
 interface. The INA220 monitors both shunt drop and supply voltage.

 The INA226 is a current shunt and power monitor with an I2C interface.
 The INA226 monitors both a shunt voltage drop and bus supply voltage.

 INA230 and INA231 are high or low side current shunt and power monitors
 with an I2C interface. The chips monitor both a shunt voltage drop and
 bus supply voltage.

 The shunt value in micro-ohms can be set via platform data or device tree at
 compile-time or via the shunt_resistor attribute in sysfs at run-time. Please
 refer to the Documentation/devicetree/bindings/i2c/ina2xx.txt for bindings
 if the device tree is used.

 Additionally ina226 supports update_interval attribute as described in
 Documentation/hwmon/sysfs-interface. Internally the interval is the sum of
 bus and shunt voltage conversion times multiplied by the averaging rate. We
 don't touch the conversion times and only modify the number of averages. The
 lower limit of the update_interval is 2 ms, the upper limit is 2253 ms.
 The actual programmed interval may vary from the desired value.
 */
