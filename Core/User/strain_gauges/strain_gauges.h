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

#endif /* USER_STRAIN_GAUGES_STRAIN_GAUGES_H_ */
