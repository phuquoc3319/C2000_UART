/*
 * uart.c
 *
 *  Created on: Jan 26, 2020
 *      Author: RICHARD
 */
#include "uart.h"

uint32_t count_rx = 0;
uint32_t count_tx = 0;

const char *c = "Hello World";
void UART1_Init(uint32_t Baudrate)
{
    // GPIO28 is the SCI Rx pin.
    //
    GPIO_setMasterCore(43, GPIO_CORE_CPU1);
    GPIO_setPinConfig(GPIO_43_SCIRXDA);
    GPIO_setDirectionMode(43, GPIO_DIR_MODE_IN);
    GPIO_setPadConfig(43, GPIO_PIN_TYPE_STD);
    GPIO_setQualificationMode(43, GPIO_QUAL_ASYNC);

    //
    // GPIO29 is the SCI Tx pin.
    //
    GPIO_setMasterCore(42, GPIO_CORE_CPU1);
    GPIO_setPinConfig(GPIO_42_SCITXDA);
    GPIO_setDirectionMode(42, GPIO_DIR_MODE_OUT);
    GPIO_setPadConfig(42, GPIO_PIN_TYPE_STD);
    GPIO_setQualificationMode(42, GPIO_QUAL_ASYNC);

    SCI_setConfig(SCIA_BASE, DEVICE_LSPCLK_FREQ, Baudrate, (SCI_CONFIG_WLEN_8 |
                                                           SCI_CONFIG_PAR_NONE |
                                                           SCI_CONFIG_STOP_ONE));
    SCI_disableLoopback(SCIA_BASE);
//    SCI_resetChannels(SCIA_BASE);
    SCI_enableFIFO(SCIA_BASE);
//    SCI_disableFIFO(SCIA_BASE);
//    SCI_performSoftwareReset(SCIA_BASE);

    SCI_enableInterrupt(SCIA_BASE, SCI_INT_RXFF);
    SCI_enableInterrupt(SCIA_BASE, SCI_INT_TXFF);
//    SCI_enableInterrupt(SCIA_BASE, SCI_INT_RXRDY_BRKDT);
//    SCI_enableInterrupt(SCIA_BASE, SCI_INT_TXRDY);
    SCI_disableInterrupt(SCIA_BASE, SCI_INT_RXERR);

    //
    // The transmit FIFO generates an interrupt when FIFO status
    // bits are less than or equal to 0 out of 16 words
    // The receive FIFO generates an interrupt when FIFO status
    // bits are greater than equal to 1 out of 16 words
    //
    SCI_setFIFOInterruptLevel(SCIA_BASE, SCI_FIFO_TX0, SCI_FIFO_RX1);
    SCI_resetRxFIFO(SCIA_BASE);
    SCI_resetTxFIFO(SCIA_BASE);

    SCI_enableModule(SCIA_BASE);

    Interrupt_enable(INT_SCIA_RX);
    Interrupt_enable(INT_SCIA_TX);
}

__interrupt void UART1_RX(void)
{
    GPIO_togglePin(31);
    count_rx++;

//    SCI_writeCharBlockingNonFIFO(SCIA_BASE, SCI_readCharBlockingFIFO(SCIA_BASE));

    SCI_resetRxFIFO(SCIA_BASE);
    SCI_clearOverflowStatus(SCIA_BASE);
    SCI_clearInterruptStatus(SCIA_BASE, SCI_INT_RXFF);
    SCI_clearInterruptStatus(SCIA_BASE, SCI_INT_RXRDY_BRKDT);
    Interrupt_clearACKGroup(INTERRUPT_ACK_GROUP9);

//    Interrupt_enable(INT_SCIA_TX);
}

__interrupt void UART1_TX(void)
{
    count_tx++;

    SCI_clearInterruptStatus(SCIA_BASE, SCI_INT_TXRDY);
    SCI_clearInterruptStatus(SCIA_BASE, SCI_INT_TXFF);
    Interrupt_clearACKGroup(INTERRUPT_ACK_GROUP9);
//    Interrupt_disable(INT_SCIA_TX);
}

