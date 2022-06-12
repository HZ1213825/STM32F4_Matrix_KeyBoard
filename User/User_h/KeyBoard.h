#ifndef _KEYBOARD_H
#define _KEYBOARD_H
#include "stm32f4xx.h"
#include "Delay.h"
#include "Usart.h"

#define Key_L0 GPIO_Pin_0
#define Key_L1 GPIO_Pin_1
#define Key_L2 GPIO_Pin_2
#define Key_L3 GPIO_Pin_3
#define Key_L4 GPIO_Pin_4
#define Key_L5 GPIO_Pin_5
#define Key_L_GPIOx GPIOA
#define Key_L_GPIO_RCC RCC_AHB1Periph_GPIOA

#define Key_R0 GPIO_Pin_0
#define Key_R1 GPIO_Pin_1
#define Key_R2 GPIO_Pin_10
#define Key_R3 GPIO_Pin_3
#define Key_R4 GPIO_Pin_4
#define Key_R5 GPIO_Pin_5
#define Key_R_GPIOx GPIOB
#define Key_R_GPIO_RCC RCC_AHB1Periph_GPIOB

#define Key_Tim_RCC RCC_APB1Periph_TIM3
#define Key_Timx TIM3
#define Tim_IRQn TIM3_IRQn
#define TIM_IRQHandler TIM3_IRQHandler

#define Key_L 1
#define Key_R 0

#define Key_Down 1
#define Key_Up 2
#define Key_Keep 0
extern u8 Key_OK;
extern u8 Key_Key[6][6];

void Key_Scan_init(void);
void Key_RLreverse_init(void);
void Key_Scan_Action(void (*Down)(u8 R, u8 L), void (*Up)(u8 R, u8 L));
void Key_RLreverse_Action(void (*Down)(u8 R, u8 L), void (*Up)(u8 R, u8 L));
#endif
