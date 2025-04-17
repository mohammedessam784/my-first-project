#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_memmap.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"

// Define LED pins
#define RED_LED     GPIO_PIN_1     // PF1
#define YELLOW_LED  GPIO_PIN_2     // PF2
#define LED_PORT    GPIO_PORTF_BASE  // Port F base address

// Delay function (approximately 1 second delay)
void delay(void) {
    SysCtlDelay(SysCtlClockGet() / 3);  // Each SysCtlDelay step takes 3 clock cycles
}

int main(void) {
    // Set the system clock to 40MHz using PLL with 16MHz crystal oscillator
    SysCtlClockSet(SYSCTL_SYSDIV_5 | SYSCTL_USE_PLL | SYSCTL_OSC_MAIN | SYSCTL_XTAL_16MHZ);

    // Enable the clock for GPIO Port F
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);

    // Wait until the GPIO module is ready
    while (!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOF)) {}

    // Configure PF1 and PF2 as output pins (for RED and YELLOW LEDs)
    GPIOPinTypeGPIOOutput(LED_PORT, RED_LED | YELLOW_LED);

    while (1) {
        // Turn ON RED LED and turn OFF YELLOW LED
        GPIOPinWrite(LED_PORT, RED_LED | YELLOW_LED, RED_LED);
        delay();

        // Turn OFF both LEDs
        GPIOPinWrite(LED_PORT, RED_LED | YELLOW_LED, 0);
        delay();

        // Turn ON YELLOW LED and keep RED OFF
        GPIOPinWrite(LED_PORT, RED_LED | YELLOW_LED, YELLOW_LED);
        delay();
    }
}
