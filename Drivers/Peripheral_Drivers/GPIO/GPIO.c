/*
 * GPIO.c
 *
 *  Created on: Jan 7, 2024
 *      Author: Ramy Sorial
 */

#include "GPIO.h"

#ifdef _Test_Mode
GPIO_Struct G, *GPIO_PortA = &G;
#endif

#define Config_Mask ((uint32_t)0b1111)

void GPIO_Init(GPIO_Struct *Port, GPIO_Config_t *conf)
{
	/// From the reference manual (P 161, P 171),
	/// every GPIO pin can be
	/// configured through 4 bits
	uint32_t Config_Data;

	switch (conf->Mode)
	{
		case GPIO_Input_Analog:
			Config_Data = 0b0000;
			break;
		case GPIO_Input_Float:
			Config_Data = 0b0100;
			break;
		case GPIO_Input_Pullup:
			Config_Data = 0b1000;
			Port->GPIO_ODR |= conf->pin;
			break;
		case GPIO_Input_Pulldown:
			Config_Data = 0b1000;
			Port->GPIO_ODR &= ~(conf->pin);
			break;
		default:
			Config_Data = conf->Speed | conf->Mode;
			break;
	}
	// apply the configuration on the selected pins
	for (uint16_t x = 0; x < 16; x++)
	{
		// if the pin is supposed to be configured
		if (conf->pin & (1 << x))
		{
			// CRL is responsible fro pins 0-7
			if (x < 8)
			{
				// clear the old configuration using the 4-bit mask
				Port->GPIO_CRL &= ~(Config_Mask << (4 * x));
				// apply the new configuration
				Port->GPIO_CRL |= (Config_Data << (4 * x));
			}
			// CRH is responsible for pins 8-15
			else
			{
				// clear the old configuration using the 4-bit mask
				Port->GPIO_CRH &= ~(Config_Mask << (4 * (x - 8)));
				// apply the new configuration
				Port->GPIO_CRH |= (Config_Data << (4 * (x - 8)));
			}
		}
	}
}

uint8_t GPIO_Get_Pin(GPIO_Struct *Port, GPIO_Pin pin)
{
	return ((Port->GPIO_IDR & pin) > 0) ? 1 : 0;
}

void GPIO_Set_Pin(GPIO_Struct *Port, GPIO_Pin pin, uint8_t State)
{
	if (State > 0)
	{
		// use one of the first 16bit inside the register
		//Port->GPIO_ODR |= pin;
		Port->GPIO_BSRR |= pin;
	}
	else
	{
		//Port->GPIO_ODR &= (~pin);
		Port->GPIO_BRR |= pin;
	}
}

void GPIO_TogglePin(GPIO_Struct *Port, GPIO_Pin pin)
{
	//write your code here to toggle a GPIO pin
}

void GPIO_Lock_Pin(GPIO_Struct *Port, GPIO_Pin pin, uint8_t Lock_Unlock)
{
	//write your code here to lock/unlock a GPIO Pin
}
