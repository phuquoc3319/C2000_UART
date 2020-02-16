#include "device.h"
#include "driverlib.h"

#include "uart.h"

// Global Variables
uint16_t Test_FIFO = 0;
const char *s = "Te";

// Functions prototype
void LED_Init(void);

int main(void)
{
    Device_init();
    Device_initGPIO();

    //
    // Initialize PIE and clear PIE registers. Disables CPU interrupts.
    //
    Interrupt_initModule();

    //
    // Initialize the PIE vector table with pointers to the shell Interrupt
    // Service Routines (ISR).
    //
    Interrupt_initVectorTable();

    Interrupt_register(INT_SCIA_RX,&UART1_RX);
    Interrupt_register(INT_SCIA_TX, &UART1_TX);

    UART1_Init(115200);



    LED_Init();
    //
    // Enable Global Interrupt (INTM) and realtime interrupt (DBGM)
    //
    EINT;
    ERTM;

//    SCI_writeCharNonBlocking(SCIA_BASE, 'r');

//    Interrupt_disable(INT_SCIA_TX);
//    SCI_disableInterrupt(SCIA_BASE, SCI_INT_TXFF);

//    SCI_writeCharArray(SCIA_BASE, (uint16_t *)s,strlen(s));
    while(1)
    {
        GPIO_togglePin(34);

//        SCI_writeCharArray(SCIA_BASE, (uint16_t *)s, strlen(s));
//        Test_FIFO = SCI_getTxFIFOStatus(SCIA_BASE);
//
//        DEVICE_DELAY_US(1000000);
//
//        SCI_resetTxFIFO(SCIA_BASE);
//        Test_FIFO = SCI_getTxFIFOStatus(SCIA_BASE);
//        DEVICE_DELAY_US(1000000);
    }
}

void LED_Init(void)
{
    GPIO_setPadConfig(31, GPIO_PIN_TYPE_STD);
    GPIO_setDirectionMode(31, GPIO_DIR_MODE_OUT);
    GPIO_setMasterCore(31, GPIO_CORE_CPU1);
    GPIO_setPinConfig(GPIO_31_GPIO31);

    GPIO_setDirectionMode(34, GPIO_DIR_MODE_OUT);
    GPIO_setMasterCore(34, GPIO_CORE_CPU1);
    GPIO_setPadConfig(34, GPIO_PIN_TYPE_STD);
    GPIO_setPinConfig(GPIO_34_GPIO34);
}




