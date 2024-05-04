/*
 * strain_gauges.h
 *
 *  Created on: May 2, 2024
 *      Author: Steven
 */

#ifndef USER_STRAIN_GAUGES_STRAIN_GAUGES_H_
#define USER_STRAIN_GAUGES_STRAIN_GAUGES_H_

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

#define READ_REG_OPCODE_MASK    (0x20u)
#define WRITE_REG_OPCODE_MASK   (0x40u)
#define READ_DATA_COMMAND       (0x12u)

#define AIN0                    (0b0000u)
#define AIN1                    (0b0001u)
#define AIN2                    (0b0010u)
#define AIN3                    (0b0011u)
#define AIN4                    (0b0100u)
#define AIN5                    (0b0101u)
#define AIN6                    (0b0110u)
#define AIN7                    (0b0111u)
#define AIN8                    (0b1000u)
#define AIN9                    (0b1001u)
#define AIN10                   (0b1010u)
#define AIN11                   (0b1011u)

#endif /* USER_STRAIN_GAUGES_STRAIN_GAUGES_H_ */
