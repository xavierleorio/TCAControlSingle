#ifndef  __X9C104_H
#define  __X9C104_H
#include "sys.h"
#include "DEFINE_GPIO.h"
#include "delay.h"

//**********************************************************************************
#define X9C104_CLK      			  RCC_APB2Periph_GPIOC
#define X9C104_GPIO_PORT        GPIOC                        /* GPIOC */
#define UD_PIN                  GPIO_Pin_14                  /* PC.14 *///方向
#define CS_PIN                  GPIO_Pin_15                  /* PC.15 *///位选

#define X9C104_INC_CLK      			  RCC_APB2Periph_GPIOB
#define X9C104_INC_GPIO_PORT        GPIOB                       /* GPIOB */
#define INC_PIN                 GPIO_Pin_9                  /* PB.9 *///脉冲

#define INC_ON()				  PBout(9)=1                   /* PB.9  */
#define INC_OFF()				  PBout(9)=0                   /* PB.9  */
#define UD_ON()				    PCout(14)=1                  /* PC.14 */
#define UD_OFF()				  PCout(14)=0                  /* PC.14 */
#define CS_ON()				    PCout(15)=1                  /* PC.15 */
#define CS_OFF()				  PCout(15)=0                  /* PC.15 */

//**********************************************************************************

void X9C104_INIT(void);
void X9C104_DOWN(void);
void X9C104_UP(void);

#endif

