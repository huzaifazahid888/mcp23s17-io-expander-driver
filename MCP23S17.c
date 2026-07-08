/*
 * MCP23S17.c
 *      Author: M HUZAIFA
 */
#include "main.h"
#include "MCP23S17.h"

static void SPI_Tx(uint8_t data, MCP23S17_t *expander) {
    HAL_SPI_Transmit(expander->hspi, &data, 1, 100);
}

static uint8_t SPI_Rx(MCP23S17_t *expander) {
    uint8_t retVal;
    HAL_SPI_Receive(expander->hspi, &retVal, 1, 100);
    return retVal;
}

static void IOexpander_CS_Low(MCP23S17_t *expander) {
    HAL_GPIO_WritePin(expander->CS_PORT_EXPANDER, expander->CS_PIN_EXPANDER, GPIO_PIN_RESET);
}

static void IOexpander_CS_High(MCP23S17_t *expander) {
    HAL_GPIO_WritePin(expander->CS_PORT_EXPANDER, expander->CS_PIN_EXPANDER, GPIO_PIN_SET);
}



void IOexpander_init(MCP23S17_t *expander) {
    IOexpander_CS_Low(expander);
    HAL_Delay(1);

    uint8_t reg = 0b01000000 | (expander->hardware_address << 1);
    SPI_Tx(reg, expander);

    reg = 0x0A; // Address IOCON register
    SPI_Tx(reg, expander);

    reg = 0x38; // Enable hardware addressing
    SPI_Tx(reg, expander);

    IOexpander_CS_High(expander);
    HAL_Delay(1);
}

void set_IOexpander_direction(MCP23S17_t *expander, uint8_t IODIR, uint8_t pinconfig) {
    IOexpander_CS_Low(expander);
    HAL_Delay(1);

    uint8_t reg = 0b01000000 | (expander->hardware_address << 1);
    SPI_Tx(reg, expander);

    reg = (IODIR == PORT_A) ? 0x00 : 0x01;
    SPI_Tx(reg, expander);

    reg = pinconfig; // Configure pins as input (1) or output (0)
    SPI_Tx(reg, expander);

    IOexpander_CS_High(expander);
    HAL_Delay(1);
}

void write_IOexpander(MCP23S17_t *expander, uint8_t expander_port, uint8_t dataWrite) {
    IOexpander_CS_Low(expander);

    uint8_t reg = 0b01000000 | (expander->hardware_address << 1);
    SPI_Tx(reg, expander);

    reg = (expander_port == PORT_A) ? 0x12 : 0x13;
    SPI_Tx(reg, expander);

    reg = dataWrite;
    SPI_Tx(reg, expander);

    IOexpander_CS_High(expander);
}

uint8_t read_IOexpander(MCP23S17_t *expander, uint8_t expander_port) {
    uint8_t tempVal = 0;

    IOexpander_CS_Low(expander);

    uint8_t reg = 0b01000001 | (expander->hardware_address << 1);
    SPI_Tx(reg, expander);

    reg = (expander_port == PORT_A) ? 0x12 : 0x13;
    SPI_Tx(reg, expander);

    tempVal = SPI_Rx(expander);

    IOexpander_CS_High(expander);

    return tempVal;
}


