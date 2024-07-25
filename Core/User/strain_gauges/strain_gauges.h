/*
 * strain_gauges.h
 *
 *  Created on: May 2, 2024
 *      Author: Steven
 */

#ifndef USER_STRAIN_GAUGES_STRAIN_GAUGES_H_
#define USER_STRAIN_GAUGES_STRAIN_GAUGES_H_

#include <stdint.h>
#include "strain_gauges_datatypes.h"

#define NUM_REGISTERS           (18u)

#define ADS124S08_FCLK		    (4096000)   // Standard internal clock frequency
#define ADS124S08_BITRES	    (24u)       // ADC resolution

#define DATA_LENGTH             (3u)

#define COMMAND_LENGTH			(2u)
#define STATUS_LENGTH			(1u)
#define CRC_LENGTH				(1u)
#define RDATA_COMMAND_LENGTH	(1u)

/********************************************************************************//**
 * 
 * @name Command byte definition
 * ---------------------------------------------------------------------------------
 * |  Bit 7  |  Bit 6  |  Bit 5  |  Bit 4  |  Bit 3  |  Bit 2  |  Bit 1  |  Bit 0  |
 * ---------------------------------------------------------------------------------
 * |                                  COMMAND                                      |
 * ---------------------------------------------------------------------------------
 */

    // SPI Control Commands
    #define OPCODE_NOP				    ((uint8_t) 0x00)
    #define OPCODE_WAKEUP				((uint8_t) 0x02)    
    #define OPCODE_POWERDOWN			((uint8_t) 0x04)    
    #define OPCODE_RESET				((uint8_t) 0x06)    
    #define OPCODE_START				((uint8_t) 0x08)    
    #define OPCODE_STOP					((uint8_t) 0x0A)  

    //SPI Calibration Commands
    #define OPCODE_SYOCAL				((uint8_t) 0x16)    
    #define OPCODE_SYGCAL				((uint8_t) 0x17)    
    #define OPCODE_SFOCAL				((uint8_t) 0x19)    
 
	// SPI Data Read Command
    #define OPCODE_RDATA				((uint8_t) 0x12)    

	// SPI Register Read and Write Commands
    #define OPCODE_RREG					((uint8_t) 0x20)
    #define OPCODE_WREG					((uint8_t) 0x40)
    #define OPCODE_RWREG_MASK			((uint8_t) 0x1F)

	/* Read mode enum */
    typedef enum { 
    	DIRECT, 
    	COMMAND 
    } readMode;

/********************************************************************************//**
 *
 * @name  Register definitions
 */

/* ADS124S08 Register 0x0 (ID) Definition
 *|  Bit 7   |   Bit 6   |   Bit 5   |   Bit 4   |   Bit 3   |   Bit 2   |   Bit 1   |   Bit 0  |
 *-----------------------------------------------------------------------------------------------
 *|       			RESERVED[4:0]      			 			 |  	      DEV_ID[2:0]           |
 *-----------------------------------------------------------------------------------------------
 *
 */
   	// ID register address
    #define REG_ADDR_ID             ((uint8_t) 0x00)

    /** ID default (reset) value */
    #define ID_DEFAULT          	((uint8_t) 0x00)

	// Define DEV_ID
	#define ADS_124S08				0x00
	#define ADS_124S06				0x01
	#define ADS_114S08				0x04
	#define ADS_114S06				0x05


/* ADS124S08 Register 0x1 (STATUS) Definition
 *|  Bit 7   |   Bit 6   |   Bit 5   |   Bit 4   |   Bit 3   |   Bit 2   |   Bit 1   |   Bit 0   |
 *------------------------------------------------------------------------------------------------
 *|  FL_POR  |    nRDY   | FL_P_RAILP| FL_P_RAILN| FL_N_RAILP| FL_N_RAILN| FL_REF_L1 | FL_REF_L0 |
 *------------------------------------------------------------------------------------------------
 */
   /** STATUS register address */
    #define REG_ADDR_STATUS         ((uint8_t) 0x01)

    /** STATUS default (reset) value */
    #define STATUS_DEFAULT          ((uint8_t) 0x80)

	#define ADS_FL_POR_MASK			0x80
	#define ADS_nRDY_MASK			0x40
	#define ADS_FL_P_RAILP_MASK		0x20
	#define ADS_FL_P_RAILN_MASK		0x10
	#define ADS_FL_N_RAILP_MASK		0x08
	#define ADS_FL_N_RAILN_MASK		0x04
	#define ADS_FL_REF_L1_MASK		0x02
	#define ADS_FL_REF_L0_MASK		0x10


/* ADS124S08 Register 0x2 (INPMUX) Definition
 *|   Bit 7   |   Bit 6   |   Bit 5   |   Bit 4   |   Bit 3   |   Bit 2   |   Bit 1   |   Bit 0  |
 *------------------------------------------------------------------------------------------------
 *|        			MUXP[3:0]   				 |       			MUXN[3:0]                    |
 *------------------------------------------------------------------------------------------------
 */
  	// INPMUX register address
    #define REG_ADDR_INPMUX			((uint8_t) 0x02)

    /** INPMUX default (reset) value */
    #define INPMUX_DEFAULT          ((uint8_t) 0x01)

	// Define the ADC positive input channels (MUXP)
	#define ADS_P_AIN0				0x00
	#define ADS_P_AIN1				0x10
	#define ADS_P_AIN2				0x20
	#define ADS_P_AIN3				0x30
	#define ADS_P_AIN4				0x40
	#define ADS_P_AIN5				0x50
	#define ADS_P_AIN6				0x60
	#define ADS_P_AIN7				0x70
	#define ADS_P_AIN8				0x80
	#define ADS_P_AIN9				0x90
	#define ADS_P_AIN10				0xA0
	#define ADS_P_AIN11				0xB0
	#define ADS_P_AINCOM			0xC0

	// Define the ADC negative input channels (MUXN)
	#define ADS_N_AIN0				0x00
	#define ADS_N_AIN1				0x01
	#define ADS_N_AIN2				0x02
	#define ADS_N_AIN3				0x03
	#define ADS_N_AIN4				0x04
	#define ADS_N_AIN5				0x05
	#define ADS_N_AIN6				0x06
	#define ADS_N_AIN7				0x07
	#define ADS_N_AIN8				0x08
	#define ADS_N_AIN9				0x09
	#define ADS_N_AIN10				0x0A
	#define ADS_N_AIN11				0x0B
	#define ADS_N_AINCOM			0x0C


/* ADS124S08 Register 0x3 (PGA) Definition
 *|  Bit 7   |   Bit 6   |   Bit 5   |   Bit 4   |   Bit 3   |   Bit 2   |   Bit 1   |   Bit 0  |
 *-----------------------------------------------------------------------------------------------
 *|  		DELAY[2:0]		     	 |      PGA_EN[1:0]      |              GAIN[2:0]           |
 *-----------------------------------------------------------------------------------------------
 */
  	// PGA register address
    #define REG_ADDR_PGA			((uint8_t) 0x03)

    /** PGA default (reset) value */
    #define PGA_DEFAULT          	((uint8_t) 0x00)

	// Define conversion delay in tmod clock periods
	#define ADS_DELAY_14			0x00
	#define ADS_DELAY_25			0x20
	#define ADS_DELAY_64			0x40
	#define ADS_DELAY_256			0x60
	#define ADS_DELAY_1024			0x80
	#define ADS_DELAY_2048			0xA0
	#define ADS_DELAY_4096			0xC0
	#define ADS_DELAY_1				0xE0

	// Define PGA control 
	#define ADS_PGA_BYPASS			0x00
	#define ADS_PGA_ENABLED			0x08

	// Define Gain
	#define ADS_GAIN_1				0x00
	#define ADS_GAIN_2				0x01
	#define ADS_GAIN_4				0x02
	#define ADS_GAIN_8				0x03
	#define ADS_GAIN_16				0x04
	#define ADS_GAIN_32				0x05
	#define ADS_GAIN_64				0x06
	#define ADS_GAIN_128			0x07
	#define ADS_GAIN_MASK			0x07


/* ADS124S08 Register 0x4 (DATARATE) Definition
 *|  Bit 7   |   Bit 6   |   Bit 5   |   Bit 4   |   Bit 3   |   Bit 2   |   Bit 1   |   Bit 0  |
 *-----------------------------------------------------------------------------------------------
 *|   G_CHOP  |    CLK    |    MODE   |   FILTER  | 				  DR[3:0]                   |
 *-----------------------------------------------------------------------------------------------
 */
  	// DATARATE register address
    #define REG_ADDR_DATARATE		((uint8_t) 0x04)

    /** DATARATE default (reset) value */
    #define DATARATE_DEFAULT   		((uint8_t) 0x14)

	#define ADS_GLOBALCHOP			0x80
	#define ADS_CLKSEL_EXT			0x40
	#define ADS_CONVMODE_SS			0x20
	#define ADS_CONVMODE_CONT		0x00
	#define ADS_FILTERTYPE_LL		0x10

	// Define the data rate */
	#define ADS_DR_2_5				0x00
	#define ADS_DR_5				0x01
	#define ADS_DR_10				0x02
	#define ADS_DR_16				0x03
	#define ADS_DR_20				0x04
	#define ADS_DR_50				0x05
	#define ADS_DR_60				0x06
	#define ADS_DR_100				0x07
	#define ADS_DR_200				0x08
	#define ADS_DR_400				0x09
	#define ADS_DR_800				0x0A
	#define ADS_DR_1000				0x0B
	#define ADS_DR_2000				0x0C
	#define ADS_DR_4000				0x0D


/* ADS124S08 Register 0x5 (REF) Definition
 *|  Bit 7   |   Bit 6   |   Bit 5   |   Bit 4   |   Bit 3   |   Bit 2   |   Bit 1   |   Bit 0  |
 *-----------------------------------------------------------------------------------------------
 *|	  FL_REF_EN[1:0]	 | nREFP_BUF | nREFN_BUF | 		REFSEL[1:0]		 | 		REFCON[1:0]     |
 *-----------------------------------------------------------------------------------------------
 */
  	// REF register address
    #define REG_ADDR_REF			((uint8_t) 0x05)

    /** REF default (reset) value */
    #define REF_DEFAULT          	((uint8_t) 0x10)

	#define ADS_FLAG_REF_DISABLE	0x00
	#define ADS_FLAG_REF_EN_L0		0x40
	#define ADS_FLAG_REF_EN_BOTH	0x80
	#define ADS_FLAG_REF_EN_10M		0xC0
	#define ADS_REFP_BYP_DISABLE	0x20
	#define ADS_REFP_BYP_ENABLE		0x00
	#define ADS_REFN_BYP_DISABLE	0x10
	#define ADS_REFN_BYP_ENABLE		0x00
	#define ADS_REFSEL_P0			0x00
	#define ADS_REFSEL_P1			0x04
	#define ADS_REFSEL_INT			0x08
	#define ADS_REFINT_OFF			0x00
	#define ADS_REFINT_ON_PDWN		0x01
	#define ADS_REFINT_ON_ALWAYS	0x02


/* ADS124S08 Register 0x6 (IDACMAG) Definition
 *|  Bit 7   |   Bit 6   |   Bit 5   |   Bit 4   |   Bit 3   |   Bit 2   |   Bit 1   |   Bit 0  |
 *-----------------------------------------------------------------------------------------------
 *|FL_RAIL_EN|	  PSW	 |     0     | 		0	 | 			    	IMAG[3:0]                   |
 *-----------------------------------------------------------------------------------------------
 */
  	// IDACMAG register address
    #define REG_ADDR_IDACMAG		((uint8_t) 0x06)

    /** IDACMAG default (reset) value */
    #define IDACMAG_DEFAULT      	((uint8_t) 0x00)

	#define ADS_FLAG_RAIL_ENABLE	0x80
	#define ADS_FLAG_RAIL_DISABLE	0x00
	#define ADS_PSW_OPEN			0x00
	#define ADS_PSW_CLOSED			0x40
	#define ADS_IDACMAG_OFF			0x00
	#define ADS_IDACMAG_10			0x01
	#define ADS_IDACMAG_50			0x02
	#define ADS_IDACMAG_100			0x03
	#define ADS_IDACMAG_250			0x04
	#define ADS_IDACMAG_500			0x05
	#define ADS_IDACMAG_750			0x06
	#define ADS_IDACMAG_1000		0x07
	#define ADS_IDACMAG_1500		0x08
	#define ADS_IDACMAG_2000		0x09


/* ADS124S08 Register 0x7 (IDACMUX) Definition
 *|  Bit 7   |   Bit 6   |   Bit 5   |   Bit 4   |   Bit 3   |   Bit 2   |   Bit 1   |   Bit 0  |
 *-----------------------------------------------------------------------------------------------
 *|                   I2MUX[3:0]                 |                   I1MUX[3:0]                 |
 *-----------------------------------------------------------------------------------------------
 */
  	// IDACMUX register address
    #define REG_ADDR_IDACMUX		((uint8_t) 0x07)

    /** IDACMUX default (reset) value */
    #define IDACMUX_DEFAULT      	((uint8_t) 0xFF)

	// Define IDAC2 Output
	#define ADS_IDAC2_A0			0x00
	#define ADS_IDAC2_A1			0x10
	#define ADS_IDAC2_A2			0x20
	#define ADS_IDAC2_A3			0x30
	#define ADS_IDAC2_A4			0x40
	#define ADS_IDAC2_A5			0x50
	#define ADS_IDAC2_A6			0x60
	#define ADS_IDAC2_A7			0x70
	#define ADS_IDAC2_A8			0x80
	#define ADS_IDAC2_A9			0x90
	#define ADS_IDAC2_A10			0xA0
	#define ADS_IDAC2_A11			0xB0
	#define ADS_IDAC2_AINCOM		0xC0
	#define ADS_IDAC2_OFF			0xF0

	// Define IDAC1 Output
	#define ADS_IDAC1_A0			0x00
	#define ADS_IDAC1_A1			0x01
	#define ADS_IDAC1_A2			0x02
	#define ADS_IDAC1_A3			0x03
	#define ADS_IDAC1_A4			0x04
	#define ADS_IDAC1_A5			0x05
	#define ADS_IDAC1_A6			0x06
	#define ADS_IDAC1_A7			0x07
	#define ADS_IDAC1_A8			0x08
	#define ADS_IDAC1_A9			0x09
	#define ADS_IDAC1_A10			0x0A
	#define ADS_IDAC1_A11			0x0B
	#define ADS_IDAC1_AINCOM		0x0C
	#define ADS_IDAC1_OFF			0x0F


/* ADS124S08 Register 0x8 (VBIAS) Definition
 *|  Bit 7   |   Bit 6   |   Bit 5   |   Bit 4   |   Bit 3   |   Bit 2   |   Bit 1   |   Bit 0  |
 *-----------------------------------------------------------------------------------------------
 *| VB_LEVEL | 	VB_AINC  |  VB_AIN5  |  VB_AIN4  |  VB_AIN3  |  VB_AIN2  |  VB_AIN1  |  VB_AIN0 |
 *-----------------------------------------------------------------------------------------------
 */
  	// VBIAS register address
    #define REG_ADDR_VBIAS			((uint8_t) 0x08)

    /** VBIAS default (reset) value */
    #define VBIAS_DEFAULT      		((uint8_t) 0x00)

	#define ADS_VBIAS_LVL_DIV2		0x00
	#define ADS_VBIAS_LVL_DIV12		0x80

	// Define VBIAS here
	#define ADS_VB_AINC				0x40
	#define ADS_VB_AIN5				0x20
	#define ADS_VB_AIN4				0x10
	#define ADS_VB_AIN3				0x08
	#define ADS_VB_AIN2				0x04
	#define ADS_VB_AIN1				0x02
	#define ADS_VB_AIN0				0x01


/* ADS124S08 Register 0x9 (SYS) Definition
 *|  Bit 7   |   Bit 6   |   Bit 5   |   Bit 4   |   Bit 3   |   Bit 2   |   Bit 1   |   Bit 0  |
 *-----------------------------------------------------------------------------------------------
 *|			   SYS_MON[2:0]			 |	   CAL_SAMP[1:0]     |  TIMEOUT  | 	  CRC	 | SENDSTAT |
 *-----------------------------------------------------------------------------------------------
 */
  	// SYS register address
    #define REG_ADDR_SYS			((uint8_t) 0x09)

    /** SYS default (reset) value */
    #define SYS_DEFAULT      		((uint8_t) 0x10)

	#define ADS_SYS_MON_OFF			0x00
	#define ADS_SYS_MON_SHORT		0x20
	#define ADS_SYS_MON_TEMP		0x40
	#define ADS_SYS_MON_ADIV4		0x60
	#define ADS_SYS_MON_DDIV4		0x80
	#define ADS_SYS_MON_BCS_2		0xA0
	#define ADS_SYS_MON_BCS_1		0xC0
	#define ADS_SYS_MON_BCS_10		0xE0
	#define ADS_CALSAMPLE_1			0x00
	#define ADS_CALSAMPLE_4			0x08
	#define ADS_CALSAMPLE_8			0x10
	#define ADS_CALSAMPLE_16		0x18
	#define ADS_TIMEOUT_DISABLE		0x00
	#define ADS_TIMEOUT_ENABLE		0x04
	#define ADS_CRC_DISABLE			0x00
	#define ADS_CRC_ENABLE			0x02
	#define ADS_CRC_MASK			0x02
	#define ADS_SENDSTATUS_DISABLE	0x00
	#define ADS_SENDSTATUS_ENABLE	0x01
	#define ADS_SENDSTATUS_MASK		0x01

/* ADS124S08 Register 0xA (OFCAL0) Definition 
 *|  Bit 7   |   Bit 6   |   Bit 5   |   Bit 4   |   Bit 3   |   Bit 2   |   Bit 1   |   Bit 0  |
 *-----------------------------------------------------------------------------------------------
 *|                                        OFC[7:0]                                             |
 *-----------------------------------------------------------------------------------------------
 */
  	// OFCAL0 register address
    #define REG_ADDR_OFCAL0			((uint8_t) 0x0A)

    /** OFCAL0 default (reset) value */
    #define OFCAL0_DEFAULT      	((uint8_t) 0x00)



/* ADS124S08 Register 0xB (OFCAL1) Definition
 *|  Bit 7   |   Bit 6   |   Bit 5   |   Bit 4   |   Bit 3   |   Bit 2   |   Bit 1   |   Bit 0  |
 *-----------------------------------------------------------------------------------------------
 *|                                        OFC[15:8]                                            |
 *-----------------------------------------------------------------------------------------------
 */
  	// OFCAL1 register address
    #define REG_ADDR_OFCAL1			((uint8_t) 0x0B)

    /** OFCAL1 default (reset) value */
    #define OFCAL1_DEFAULT      	((uint8_t) 0x00)


/* ADS124S08 Register 0xC (OFCAL2) Definition
 *|  Bit 7   |   Bit 6   |   Bit 5   |   Bit 4   |   Bit 3   |   Bit 2   |   Bit 1   |   Bit 0  |
 *-----------------------------------------------------------------------------------------------
 *|                                        OFC[23:16]                                           |
 *-----------------------------------------------------------------------------------------------
 */
  	// OFCAL2 register address
    #define REG_ADDR_OFCAL2			((uint8_t) 0x0C)

    /** OFCAL2 default (reset) value */
    #define OFCAL2_DEFAULT      	((uint8_t) 0x00)


/* ADS124S08 Register 0xD (FSCAL0) Definition
 *|  Bit 7   |   Bit 6   |   Bit 5   |   Bit 4   |   Bit 3   |   Bit 2   |   Bit 1   |   Bit 0  |
 *-----------------------------------------------------------------------------------------------
 *|                                        FSC[7:0]                                             |
 *-----------------------------------------------------------------------------------------------
 */
  	// FSCAL0 register address
    #define REG_ADDR_FSCAL0			((uint8_t) 0x0D)

    /** FSCAL0 default (reset) value */
    #define FSCAL0_DEFAULT      	((uint8_t) 0x00)


/* ADS124S08 Register 0xE (FSCAL1) Definition 
 *|  Bit 7   |   Bit 6   |   Bit 5   |   Bit 4   |   Bit 3   |   Bit 2   |   Bit 1   |   Bit 0  |
 *-----------------------------------------------------------------------------------------------
 *|                                        FSC[15:8]                                            |
 *-----------------------------------------------------------------------------------------------
 */
  	// FSCAL1 register address
    #define REG_ADDR_FSCAL1			((uint8_t) 0x0E)

    /** FSCAL1 default (reset) value */
    #define FSCAL1_DEFAULT      	((uint8_t) 0x00)


/* ADS124S08 Register 0xF (FSCAL2) Definition 
 *|  Bit 7   |   Bit 6   |   Bit 5   |   Bit 4   |   Bit 3   |   Bit 2   |   Bit 1   |   Bit 0  |
 *-----------------------------------------------------------------------------------------------
 *|                                        FSC[23:16]                                           |
 *-----------------------------------------------------------------------------------------------
 */
  	// FSCAL2 register address
    #define REG_ADDR_FSCAL2			((uint8_t) 0x0F)

    /** FSCAL2 default (reset) value */
    #define FSCAL2_DEFAULT      	((uint8_t) 0x40)


/* ADS124S08 Register 0x10 (GPIODAT) Definition
 *|  Bit 7   |   Bit 6   |   Bit 5   |   Bit 4   |   Bit 3   |   Bit 2   |   Bit 1   |   Bit 0  |
 *-----------------------------------------------------------------------------------------------
 *|                     DIR[3:0]    			 | 					DAT[3:0]                    |
 *-----------------------------------------------------------------------------------------------
 */
  	// GPIODAT register address 
    #define REG_ADDR_GPIODAT		((uint8_t) 0x10)

    /** GPIODAT default (reset) value */
    #define GPIODAT_DEFAULT      	((uint8_t) 0x00)

	// Define GPIO direction (0-Output; 1-Input) here
	#define ADS_GPIO0_DIR_INPUT		0x10
	#define ADS_GPIO1_DIR_INPUT		0x20
	#define ADS_GPIO2_DIR_INPUT		0x40
	#define ADS_GPIO3_DIR_INPUT		0x80


/* ADS124S08 Register 0x11 (GPIOCON) Definition
 *|  Bit 7   |   Bit 6   |   Bit 5   |   Bit 4   |   Bit 3   |   Bit 2   |   Bit 1   |   Bit 0  |
 *-----------------------------------------------------------------------------------------------
 *|    0	 |	   0	 |	   0	 |	   0     |                    CON[3:0]                  |
 *-----------------------------------------------------------------------------------------------
 */
  	// GPIOCON register address
    #define REG_ADDR_GPIOCON		((uint8_t) 0x11)

    /** GPIOCON default (reset) value */
    #define GPIOCON_DEFAULT      	((uint8_t) 0x00)

	// Define GPIO configuration (0-Analog Input; 1-GPIO) here
	#define ADS_GPIO0_CFG_GPIO		0x01
	#define ADS_GPIO1_CFG_GPIO		0x02
	#define ADS_GPIO2_CFG_GPIO		0x04
	#define ADS_GPIO3_CFG_GPIO		0x08



#define ADS_RESET_TIME          (0x01u)

bool StartUpRoutine(ads124S08Control_t* device);

void ToggleReset(
    ads124S08Control_t* device
);

uint8_t ReadRegister(
    ads124S08Control_t* device,
    uint16_t registerNum
);

uint8_t ReadMultipleRegisters(
    ads124S08Control_t* device,
    uint16_t registerNum,
    uint16_t readCount
);

uint8_t WriteRegister(
	ads124S08Control_t* device,
	uint16_t registerNum,
	uint8_t data
);

uint8_t WriteMultipleRegisters(
    ads124S08Control_t* device,
    uint16_t registerNum,
    uint16_t writeCount,
    uint8_t* data
);

uint8_t SendCommand(
	ads124S08Control_t* device,
	uint8_t command
);

uint32_t ReadADCData(
	ads124S08Control_t* device,
	uint8_t* deviceStatus,
	uint8_t mode
);

extern ads124S08Control_t externalADC1, externalADC2;

#endif /* USER_STRAIN_GAUGES_STRAIN_GAUGES_H_ */
