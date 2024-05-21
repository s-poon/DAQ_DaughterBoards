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

#define ID_ADDR_MASK		(0x00u)
#define STATUS_ADDR_MASK	(0x01u)
#define INPMUX_ADDR_MASK	(0x02u)
#define PGA_ADDR_MASK		(0x03u)
#define DATARATE_ADDR_MASK	(0x04u)
#define REF_ADDR_MASK		(0x05u)
#define IDACMAG_ADDR_MASK	(0x06u)
#define IDACMUX_ADDR_MASK	(0x07u)
#define VBIAS_ADDR_MASK		(0x08u)
#define SYS_ADDR_MASK		(0x09u)
#define OFCAL0_ADDR_MASK	(0x0Au)
#define OFCAL1_ADDR_MASK	(0x0Bu)
#define OFCAL2_ADDR_MASK	(0x0Cu)
#define FSCAL0_ADDR_MASK	(0x0Du)
#define FSCAL1_ADDR_MASK	(0x0Eu)
#define FSCAL2_ADDR_MASK	(0x0Fu)
#define GPIODAT_ADDR_MASK	(0x10u)
#define GPIOCON_ADDR_MASK	(0x11u)

/* Opcode masks */
#define NOP_OPCODE_MASK		(0x00u)
#define WAKE_OPCODE_MASK	(0x02u)
#define SLEEP_OPCODE_MASK	(0x04u)
#define RESET_OPCODE_MASK	(0x06u)
#define START_OPCODE_MASK	(0x08u)
#define STOP_OPCODE_MASK	(0x0Au)
#define SFOCAL_OPCODE_MASK	(0x19u)
#define SYOCAL_OPCODE_MASK	(0x16u)
#define SYGCAL_OPCODE_MASK	(0x17u)
#define RDATA_OPCODE_MASK	(0x12u)
#define REGRD_OPCODE_MASK	(0x20u)
#define REGWR_OPCODE_MASK	(0x40u)
/* Register sub masks */
/* ADS124S08 Register 0 (ID) Definition
 *   Bit 7   |   Bit 6   |   Bit 5   |   Bit 4   |   Bit 3   |   Bit 2   |   Bit 1   |   Bit 0
 *--------------------------------------------------------------------------------------------
 *        			RESERVED[4:0]      			 			 |  	      DEV_ID[2:0]
 *
 */
/* Define ID (revision) */
#define ADS_ID_A				(0x00u)
#define ADS_ID_B				(0x80u)
/* Define VER (device version) */
#define ADS_124S08				(0x00u)
#define ADS_124S06				(0x01u)
#define ADS_114S08				(0x04u)
#define ADS_114S06				(0x05u)
/* ADS124S08 Register 1 (STATUS) Definition */
/*   Bit 7   |   Bit 6   |   Bit 5   |   Bit 4   |   Bit 3   |   Bit 2   |   Bit 1   |   Bit 0
 *--------------------------------------------------------------------------------------------
 *   FL_POR  |    nRDY   | FL_P_RAILP| FL_P_RAILN| FL_N_RAILP| FL_N_RAILN| FL_REF_L1 | FL_REF_L0
 *
 */
#define ADS_FL_POR				(0x80u)
#define ADS_RDY					(0x40u)
#define ADS_FL_P_RAILP			(0x20u)
#define ADS_FL_P_RAILN			(0x10u)
#define ADS_FL_N_RAILP			(0x08u)
#define ADS_FL_N_RAILN			(0x04u)
#define ADS_FL_REF_L1			(0x02u)
#define ADS_FL_REF_L0			(0x10u)
/* ADS124S08 Register 2 (INPMUX) Definition */
/*   Bit 7   |   Bit 6   |   Bit 5   |   Bit 4   |   Bit 3   |   Bit 2   |   Bit 1   |   Bit 0
 *--------------------------------------------------------------------------------------------
 *         			MUXP[3:0]   				 |       			MUXN[3:0]
 *
 */
/* Define the ADC positive input channels (MUXP) */
#define ADS_P_AIN0				(0x00u)
#define ADS_P_AIN1				(0x10u)
#define ADS_P_AIN2				(0x20u)
#define ADS_P_AIN3				(0x30u)
#define ADS_P_AIN4				(0x40u)
#define ADS_P_AIN5				(0x50u)
#define ADS_P_AIN6				(0x60u)
#define ADS_P_AIN7				(0x70u)
#define ADS_P_AIN8				(0x80u)
#define ADS_P_AIN9				(0x90u)
#define ADS_P_AIN10				(0xA0u)
#define ADS_P_AIN11				(0xB0u)
#define ADS_P_AINCOM			(0xC0u)
/* Define the ADC negative input channels (MUXN)*/
#define ADS_N_AIN0				(0x00u)
#define ADS_N_AIN1				(0x01u)
#define ADS_N_AIN2				(0x02u)
#define ADS_N_AIN3				(0x03u)
#define ADS_N_AIN4				(0x04u)
#define ADS_N_AIN5				(0x05u)
#define ADS_N_AIN6				(0x06u)
#define ADS_N_AIN7				(0x07u)
#define ADS_N_AIN8				(0x08u)
#define ADS_N_AIN9				(0x09u)
#define ADS_N_AIN10				(0x0Au)
#define ADS_N_AIN11				(0x0Bu)
#define ADS_N_AINCOM			(0x0Cu)
/* ADS124S08 Register 3 (PGA) Definition */
/*   Bit 7   |   Bit 6   |   Bit 5   |   Bit 4   |   Bit 3   |   Bit 2   |   Bit 1   |   Bit 0
 *--------------------------------------------------------------------------------------------
 *   		DELAY[2:0]		     	 |      PGA_EN[1:0]      |              GAIN[2:0]
 *
 */
/* Define conversion delay in tmod clock periods */
#define ADS_DELAY_14			(0x00u)
#define ADS_DELAY_25			(0x20u)
#define ADS_DELAY_64			(0x40u)
#define ADS_DELAY_256			(0x60u)
#define ADS_DELAY_1024			(0x80u)
#define ADS_DELAY_2048			(0xA0u)
#define ADS_DELAY_4096			(0xC0u)
#define ADS_DELAY_1				(0xE0u)
/* Define PGA control */
#define ADS_PGA_BYPASS			(0x00u)
#define ADS_PGA_ENABLED			(0x08u)
/* Define Gain */
#define ADS_GAIN_1				(0x00u)
#define ADS_GAIN_2				(0x01u)
#define ADS_GAIN_4				(0x02u)
#define ADS_GAIN_8				(0x03u)
#define ADS_GAIN_16				(0x04u)
#define ADS_GAIN_32				(0x05u)
#define ADS_GAIN_64				(0x06u)
#define ADS_GAIN_128			(0x07u)
/* ADS124S08 Register 4 (DATARATE) Definition */
/*   Bit 7   |   Bit 6   |   Bit 5   |   Bit 4   |   Bit 3   |   Bit 2   |   Bit 1   |   Bit 0
 *--------------------------------------------------------------------------------------------
 *   G_CHOP  |    CLK    |    MODE   |   FILTER  | 				  DR[3:0]
 *
 */
#define ADS_GLOBALCHOP			(0x80u)
#define ADS_CLKSEL_EXT			(0x40u)
#define ADS_CONVMODE_SS			(0x20u)
#define ADS_FILTERTYPE_LL		(0x10u)
/* Define the data rate */
#define ADS_DR_2_5				(0x00u)
#define ADS_DR_5				(0x01u)
#define ADS_DR_10				(0x02u)
#define ADS_DR_16				(0x03u)
#define ADS_DR_20				(0x04u)
#define ADS_DR_50				(0x05u)
#define ADS_DR_60				(0x06u)
#define ADS_DR_100				(0x07u)
#define ADS_DR_200				(0x08u)
#define ADS_DR_400				(0x09u)
#define ADS_DR_800				(0x0Au)
#define ADS_DR_1000				(0x0Bu)
#define ADS_DR_2000				(0x0Cu)
#define ADS_DR_4000				(0x0Du)
/* ADS124S08 Register 5 (REF) Definition */
/*   Bit 7   |   Bit 6   |   Bit 5   |   Bit 4   |   Bit 3   |   Bit 2   |   Bit 1   |   Bit 0
 *--------------------------------------------------------------------------------------------
 *	  FL_REF_EN[1:0]	 | nREFP_BUF | nREFN_BUF | 		REFSEL[1:0]		 | 		REFCON[1:0]
 *
 */
#define ADS_FLAG_REF_DISABLE	(0x00u)
#define ADS_FLAG_REF_EN_L0		(0x40u)
#define ADS_FLAG_REF_EN_BOTH	(0x80u)
#define ADS_FLAG_REF_EN_10M		(0xC0u)
#define ADS_REFP_BYP_DISABLE	(0x20u)
#define ADS_REFP_BYP_ENABLE		(0x00u)
#define ADS_REFN_BYP_DISABLE	(0x10u)
#define ADS_REFN_BYP_ENABLE		(0x00u)
#define ADS_REFSEL_P0			(0x00u)
#define ADS_REFSEL_P1			(0x04u)
#define ADS_REFSEL_INT			(0x08u)
#define ADS_REFINT_OFF			(0x00u)
#define ADS_REFINT_ON_PDWN		(0x01u)
#define ADS_REFINT_ON_ALWAYS	(0x02u)
/* ADS124S08 Register 6 (IDACMAG) Definition */
/*   Bit 7   |   Bit 6   |   Bit 5   |   Bit 4   |   Bit 3   |   Bit 2   |   Bit 1   |   Bit 0
 *--------------------------------------------------------------------------------------------
 * FL_RAIL_EN|	  PSW	 |     0     | 		0	 | 			    	IMAG[3:0]
 *
 */
#define ADS_FLAG_RAIL_ENABLE	(0x80u)
#define ADS_FLAG_RAIL_DISABLE	(0x00u)
#define ADS_PSW_OPEN			(0x00u)
#define ADS_PSW_CLOSED			(0x40u)
#define ADS_IDACMAG_OFF			(0x00u)
#define ADS_IDACMAG_10			(0x01u)
#define ADS_IDACMAG_50			(0x02u)
#define ADS_IDACMAG_100			(0x03u)
#define ADS_IDACMAG_250			(0x04u)
#define ADS_IDACMAG_500			(0x05u)
#define ADS_IDACMAG_750			(0x06u)
#define ADS_IDACMAG_1000		(0x07u)
#define ADS_IDACMAG_1500		(0x08u)
#define ADS_IDACMAG_2000		(0x09u)
/* ADS124S08 Register 7 (IDACMUX) Definition */
/*   Bit 7   |   Bit 6   |   Bit 5   |   Bit 4   |   Bit 3   |   Bit 2   |   Bit 1   |   Bit 0
 *--------------------------------------------------------------------------------------------
 *                    I2MUX[3:0]                 |                   I1MUX[3:0]
 *
 */
/* Define IDAC2 Output */
#define ADS_IDAC2_A0			(0x00u)
#define ADS_IDAC2_A1			(0x10u)
#define ADS_IDAC2_A2			(0x20u)
#define ADS_IDAC2_A3			(0x30u)
#define ADS_IDAC2_A4			(0x40u)
#define ADS_IDAC2_A5			(0x50u)
#define ADS_IDAC2_A6			(0x60u)
#define ADS_IDAC2_A7			(0x70u)
#define ADS_IDAC2_A8			(0x80u)
#define ADS_IDAC2_A9			(0x90u)
#define ADS_IDAC2_A10			(0xA0u)
#define ADS_IDAC2_A11			(0xB0u)
#define ADS_IDAC2_AINCOM		(0xC0u)
#define ADS_IDAC2_OFF			(0xF0u)
/* Define IDAC1 Output */
#define ADS_IDAC1_A0			(0x00u)
#define ADS_IDAC1_A1			(0x01u)
#define ADS_IDAC1_A2			(0x02u)
#define ADS_IDAC1_A3			(0x03u)
#define ADS_IDAC1_A4			(0x04u)
#define ADS_IDAC1_A5			(0x05u)
#define ADS_IDAC1_A6			(0x06u)
#define ADS_IDAC1_A7			(0x07u)
#define ADS_IDAC1_A8			(0x08u)
#define ADS_IDAC1_A9			(0x09u)
#define ADS_IDAC1_A10			(0x0Au)
#define ADS_IDAC1_A11			(0x0Bu)
#define ADS_IDAC1_AINCOM		(0x0Cu)
#define ADS_IDAC1_OFF			(0x0Fu)
/* ADS124S08 Register 8 (VBIAS) Definition */
/*   Bit 7   |   Bit 6   |   Bit 5   |   Bit 4   |   Bit 3   |   Bit 2   |   Bit 1   |   Bit 0
 *--------------------------------------------------------------------------------------------
 *  VB_LEVEL | 	VB_AINC  |  VB_AIN5  |  VB_AIN4  |  VB_AIN3  |  VB_AIN2  |  VB_AIN1  |  VB_AIN0
 *
 */
#define ADS_VBIAS_LVL_DIV2		(0x00u)
#define ADS_VBIAS_LVL_DIV12		(0x80u)
/* Define VBIAS here */
#define ADS_VB_AINC				(0x40u)
#define ADS_VB_AIN5				(0x20u)
#define ADS_VB_AIN4				(0x10u)
#define ADS_VB_AIN3				(0x08u)
#define ADS_VB_AIN2				(0x04u)
#define ADS_VB_AIN1				(0x02u)
#define ADS_VB_AIN0				(0x01u)
/* ADS124S08 Register 9 (SYS) Definition */
/*   Bit 7   |   Bit 6   |   Bit 5   |   Bit 4   |   Bit 3   |   Bit 2   |   Bit 1   |   Bit 0
 *--------------------------------------------------------------------------------------------
 *			   SYS_MON[2:0]			 |	   CAL_SAMP[1:0]     |  TIMEOUT  | 	  CRC	 | SENDSTAT
 *
 */
#define ADS_SYS_MON_OFF			(0x00u)
#define ADS_SYS_MON_SHORT		(0x20u)
#define ADS_SYS_MON_TEMP		(0x40u)
#define ADS_SYS_MON_ADIV4		(0x60u)
#define ADS_SYS_MON_DDIV4		(0x80u)
#define ADS_SYS_MON_BCS_2		(0xA0u)
#define ADS_SYS_MON_BCS_1		(0xC0u)
#define ADS_SYS_MON_BCS_10		(0xE0u)
#define ADS_CALSAMPLE_1			(0x00u)
#define ADS_CALSAMPLE_4			(0x08u)
#define ADS_CALSAMPLE_8			(0x10u)
#define ADS_CALSAMPLE_16		(0x18u)
#define ADS_TIMEOUT_DISABLE		(0x00u)
#define ADS_TIMEOUT_ENABLE		(0x04u)
#define ADS_CRC_DISABLE			(0x00u)
#define ADS_CRC_ENABLE			(0x02u)
#define ADS_SENDSTATUS_DISABLE	(0x00u)
#define ADS_SENDSTATUS_ENABLE	(0x01u)
/* ADS124S08 Register A (OFCAL0) Definition */
/*   Bit 7   |   Bit 6   |   Bit 5   |   Bit 4   |   Bit 3   |   Bit 2   |   Bit 1   |   Bit 0
 *--------------------------------------------------------------------------------------------
 *                                         OFC[7:0]
 *
 */
/* ADS124S08 Register B (OFCAL1) Definition */
/*   Bit 7   |   Bit 6   |   Bit 5   |   Bit 4   |   Bit 3   |   Bit 2   |   Bit 1   |   Bit 0
 *--------------------------------------------------------------------------------------------
 *                                         OFC[15:8]
 *
 */
/* ADS124S08 Register C (OFCAL2) Definition */
/*   Bit 7   |   Bit 6   |   Bit 5   |   Bit 4   |   Bit 3   |   Bit 2   |   Bit 1   |   Bit 0
 *--------------------------------------------------------------------------------------------
 *                                         OFC[23:16]
 *
 */
/* ADS124S08 Register D (FSCAL0) Definition */
/*   Bit 7   |   Bit 6   |   Bit 5   |   Bit 4   |   Bit 3   |   Bit 2   |   Bit 1   |   Bit 0
 *--------------------------------------------------------------------------------------------
 *                                         FSC[7:0]
 *
 */
/* ADS124S08 Register E (FSCAL1) Definition */
/*   Bit 7   |   Bit 6   |   Bit 5   |   Bit 4   |   Bit 3   |   Bit 2   |   Bit 1   |   Bit 0
 *--------------------------------------------------------------------------------------------
 *                                         FSC[15:8]
 *
 */
/* ADS124S08 Register F (FSCAL2) Definition */
/*   Bit 7   |   Bit 6   |   Bit 5   |   Bit 4   |   Bit 3   |   Bit 2   |   Bit 1   |   Bit 0
 *--------------------------------------------------------------------------------------------
 *                                         FSC[23:16]
 *
 */
/* ADS124S08 Register 10 (GPIODAT) Definition */
/*   Bit 7   |   Bit 6   |   Bit 5   |   Bit 4   |   Bit 3   |   Bit 2   |   Bit 1   |   Bit 0
 *--------------------------------------------------------------------------------------------
 *                      DIR[3:0]    			 | 					DAT[3:0]
 *
 */
/* Define GPIO direction (0-Output; 1-Input) here */
#define ADS_GPIO0_DIR_INPUT		(0x10u)
#define ADS_GPIO1_DIR_INPUT		(0x20u)
#define ADS_GPIO2_DIR_INPUT		(0x40u)
#define ADS_GPIO3_DIR_INPUT		(0x80u)
/*
 *
 */
/* Define GPIO data here */
/*
 *
 */
/* ADS124S08 Register 11 (GPIOCON) Definition */
/*   Bit 7   |   Bit 6   |   Bit 5   |   Bit 4   |   Bit 3   |   Bit 2   |   Bit 1   |   Bit 0
 *--------------------------------------------------------------------------------------------
 *     0	 |	   0	 |	   0	 |	   0     |                    CON[3:0]
 *
 */
/* Define GPIO configuration (0-Analog Input; 1-GPIO) here */
#define ADS_GPIO0_DIR_INPUT		(0x10u)
#define ADS_GPIO1_DIR_INPUT		(0x20u)
#define ADS_GPIO2_DIR_INPUT		(0x40u)
#define ADS_GPIO3_DIR_INPUT		(0x80u)



uint8_t InitDevice();

uint8_t ReadRegister(
    ads124S08Control_t* device,
    uint16_t registerNum
);

uint8_t ReadRegisters(
    ads124S08Control_t* device,
    uint16_t registerNum,
    uint16_t readCount
);

uint8_t WriteRegister(
	ads124S08Control_t* device,
	uint16_t registerNum,
	uint8_t data
);

uint8_t WriteRegisters(
    ads124S08Control_t* device,
    uint16_t registerNum,
    uint16_t writeCount,
    uint8_t* data
);

uint8_t SendCommand(
	ads124S08Control_t* device,
	uint8_t command
);

extern ads124S08Control_t externalADC1, externalADC2;

#endif /* USER_STRAIN_GAUGES_STRAIN_GAUGES_H_ */
