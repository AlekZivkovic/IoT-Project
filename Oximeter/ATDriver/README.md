## ESP AT Firmware Driver README

The main functionality of this driver is to simplify the process of establishing a connection with an MQTT server. It achieves this by leveraging a Trie data structure for efficient identification of received UART command responses.

### Configuration

To configure the ATDriver, you need to include the "ATDriverConfig.h" file. Below are the configuration parameters you can set in "ATDriverConfig.h":

```c
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

#define WIFI_SSID           "your_SSID"
#define WIFI_PASSWORD       "your_password"
#define MODULE_NAME         "module_name"
#define IP_ADDRESS          "your_ip_addr"

#define AT_SEND_SIZE 25
```

### Usage Guidelines

When working with the ATDriver:
- Include only the "ATDriver.h" file.
- Initialize the driver by calling the `ATDriver_init` function with appropriate parameters.
- When calling 'ATDriver_init', set `read_task_priority` to the highest priority task in the system for delayed interrupt processing.
- If the module only sends data and does not receive, pass to 'ATDriver_init' `SPO2_buffer_handle` and `HR_buffer_handle` as NULL.
- Enable UART interrupt and after clearing the interrupt flag, call `ATDriverUARTISR`.
- Note: ATDriver uses UART0 for debugging.

