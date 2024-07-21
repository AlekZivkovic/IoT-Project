#ifndef ATDRIVERCONFIG_H_
#define ATDRIVERCONFIG_H_

#include "inc/hw_ints.h"
#include "inc/hw_memmap.h"
#include "driverlib/pin_map.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"


/* UART Exposed port for communication with sensor */
#define ATD_SYSCTL_UART     SYSCTL_PERIPH_UART3
#define ATD_SYSCTL_GPIO     SYSCTL_PERIPH_GPIOC
#define ATD_UART_RX         GPIO_PC6_U3RX
#define ATD_UART_TX         GPIO_PC7_U3TX
#define ATD_GPIO_BASE       GPIO_PORTC_BASE
#define ATD_GPIO_PIN        GPIO_PIN_6 | GPIO_PIN_7
#define ATD_UART_BASE       UART3_BASE
#define ATD_UART_INT        INT_UART3

#define SPO2_TOPIC_TX       "O"
#define HR_TOPIC_TX         "H"
#define SPO2_TOPIC_RX       "X"
#define HR_TOPIC_RX         "Z"

#define WIFI_SSID           "localc"
#define WIFI_PASSWORD       "aleksandar"
#define MODULE_NAME         "broker"
#define IP_ADDRESS          ""

#define AT_SEND_SIZE 25

#endif
