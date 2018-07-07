#ifndef __DEFINE_GPIO_H
#define __DEFINE_GPIO_H

#include "sys.h"

//**********************************************************************************
#define RELAY1_ON()				  PBout(12)=0                   /* PB.12 */
#define RELAY1_OFF()			  PBout(12)=1
#define RELAY1_PIN                GPIO_Pin_12
#define RELAY2_ON()				  PBout(13)=0                   /* PB.13 */
#define RELAY2_OFF()			  PBout(13)=1
#define RELAY2_PIN                GPIO_Pin_13
#define RELAY3_ON()				  PBout(14)=0                   /* PB.14 */
#define RELAY3_OFF()			  PBout(14)=1
#define RELAY3_PIN                GPIO_Pin_14
#define RELAY4_ON()				  PBout(15)=0                   /* PB.15 */
#define RELAY4_OFF()			  PBout(15)=1
#define RELAY4_PIN                GPIO_Pin_15
#define RELAY_CLK      			  RCC_APB2Periph_GPIOB
#define RELAY_GPIO_PORT           GPIOB                        /* GPIOB */

#define MOS_ON()				  PAout(3)=1                   /* PA.3 */
#define MOS_OFF()			  	PAout(3)=0
#define Fan_ON()				  PAout(0)=1                   /* PA.3 */
#define Fan_OFF()			  	PAout(0)=0

//**********************************************************************************

extern void Init_GPIOpin(void);

#endif
