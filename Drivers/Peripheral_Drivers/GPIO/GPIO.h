/*
 * GPIO.h
 *
 *  Created on: Jan 7, 2024
 *      Author: Ramy Sorial
 */

#ifndef MYGPIO_DRIVER_GPIO_H_
#define MYGPIO_DRIVER_GPIO_H_

#include <stdint.h>

/**
 * @headerfile GPIO main header file
 * */

/// @section GPIO Port definitions
#define GPIOA_Base 0x40010800
#define GPIOB_Base 0x40010C00
#define GPIOC_Base 0x40011000
#define GPIOD_Base 0x40011400
#define GPIOE_Base 0x40011800
#define GPIOF_Base 0x40011C00
#define GPIOG_Base 0x40012000

/// @struct
/// @brief
/// Contains the control and status registers of the GPIO peripheral
typedef struct
{
	uint32_t GPIO_CRL; // offset 0
	uint32_t GPIO_CRH; // offset 4
	uint32_t GPIO_IDR;
	uint32_t GPIO_ODR;
	uint32_t GPIO_BSRR;
	uint32_t GPIO_BRR;
	uint32_t GPIO_LCKR;
} GPIO_Struct;

/// @enum
/// @brief
/// GPIO mode selection
typedef enum
{
	GPIO_Out_PP = 0b0000,   ///< GPIO_Out_PP
	GPIO_Out_OD = 0b0100,   ///< GPIO_Out_OD

	GPIO_AF_Out_PP = 0b1000,///< GPIO_AF_Out_PP
	GPIO_AF_Out_OD = 0b1100,///< GPIO_AF_Out_OD

	GPIO_Input_Analog,      ///< GPIO_Input_Analog

	GPIO_Input_Float,       ///< GPIO_Input_Float
	GPIO_Input_Pullup,      ///< GPIO_Input_Pullup
	GPIO_Input_Pulldown,    ///< GPIO_Input_Pulldown
} GPIO_Mode;

/// @enum
/// @brief
/// GPIO Available speed options
typedef enum
{
	GPIO_Speed_Low = 0b10,///< GPIO_Speed_Low
	GPIO_Speed_Med = 0b01,///< GPIO_Speed_Med
	GPIO_Speed_High = 0b11///< GPIO_Speed_High
} GPIO_Speed_Config;

/// @enum
/// @brief
/// GPIO pin selection
/// Multiple pins can be selected at once by using the | operator
typedef enum
{
	GPIO_P0 = 0b0000000000000001, ///< GPIO_P0
	GPIO_P1 = 0b0000000000000010, ///< GPIO_P1
	GPIO_P2 = 0b0000000000000100, ///< GPIO_P2
	GPIO_P3 = 0b0000000000001000, ///< GPIO_P3
	GPIO_P4 = 0b0000000000010000, ///< GPIO_P4
	GPIO_P5 = 0b0000000000100000, ///< GPIO_P5
	GPIO_P6 = 0b0000000001000000, ///< GPIO_P6
	GPIO_P7 = 0b0000000010000000, ///< GPIO_P7
	GPIO_P8 = 0b0000000100000000, ///< GPIO_P8
	GPIO_P9 = 0b0000001000000000, ///< GPIO_P9
	GPIO_P10 = 0b0000010000000000,///< GPIO_P10
	GPIO_P11 = 0b0000100000000000,///< GPIO_P11
	GPIO_P12 = 0b0001000000000000,///< GPIO_P12
	GPIO_P13 = 0b0010000000000000,///< GPIO_P13
	GPIO_P14 = 0b0100000000000000,///< GPIO_P14
	GPIO_P15 = 0b1000000000000000,///< GPIO_P15
} GPIO_Pin;

/// @struct
/// @brief
/// Main config structure to be filled by the user and used by the
/// GPIO_Init function
typedef struct
{
	GPIO_Pin pin;
	GPIO_Mode Mode;
	GPIO_Speed_Config Speed;
} GPIO_Config_t;

#define GPIO_PortA ((GPIO_Struct *)(GPIOA_Base))
#define GPIO_PortB ((GPIO_Struct *)(GPIOB_Base))
#define GPIO_PortC ((GPIO_Struct *)(GPIOC_Base))
#define GPIO_PortD ((GPIO_Struct *)(GPIOD_Base))
#define GPIO_PortE ((GPIO_Struct *)(GPIOE_Base))
#define GPIO_PortF ((GPIO_Struct *)(GPIOF_Base))
#define GPIO_PortG ((GPIO_Struct *)(GPIOG_Base))

/* User exposed functions */

/// @fn void GPIO_Init(GPIO_Struct*, GPIO_Config_t*)
/// @brief
/// Initializes the GPIo peripheral
/// @param Port pointer to the GPIO port struct to be configured
/// @param conf pointer to the config struct containing the configuration data
void GPIO_Init(GPIO_Struct *Port, GPIO_Config_t *conf);

/// @fn uint8_t GPIO_Get_Pin(GPIO_Struct*, GPIO_Pin)
/// @brief
/// Reads the logical level of a GPIO pin
/// @param Port pointer to the GPIO port struct where the pin resides
/// @param pin pin number to be read
/// @return 1 if a logic high is applied, and 0 in the case of a logic low
uint8_t GPIO_Get_Pin(GPIO_Struct *Port, GPIO_Pin pin);

/// @fn void GPIO_Set_Pin(GPIO_Struct*, GPIO_Pin, uint8_t)
/// @brief
/// Write the ligic level of a GPIO pin(s)
/// @param Port pointer to the GPIO port struct where the pin resides
/// @param pin pin number(s) to be written, to use multiple pins,
/// use the or | operator
/// @param State 1 for high and 0 for low
void GPIO_Set_Pin(GPIO_Struct *Port, GPIO_Pin pin, uint8_t State);

/// @fn void GPIO_TogglePin(GPIO_Struct*, GPIO_Pin)
/// @brief
/// Toggles the status of a GPIO output pin
/// @param Port pointer to the GPIO port struct where the pin resides
/// @param pin  pin number(s) to be written, to use multiple pins,
/// use the or | operator
void GPIO_TogglePin(GPIO_Struct *Port, GPIO_Pin pin);

/// @fn void GPIO_Lock_Pin(GPIO_Struct*, GPIO_Pin)
/// @brief
/// Locks or unlocks a GPIO pin
/// @param Port pointer to the GPIO port struct where the pin resides
/// @param pin pin number(s) to be written, to use multiple pins,
/// use the or | operator
void GPIO_Lock_Pin(GPIO_Struct *Port, GPIO_Pin pin, uint8_t Lock_Unlock);
#endif /* MYGPIO_DRIVER_GPIO_H_ */
