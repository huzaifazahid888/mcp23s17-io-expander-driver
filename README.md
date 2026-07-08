# MCP23S17 I/O Expander Driver for STM32

A lightweight C driver for the **Microchip MCP23S17** 16-bit SPI I/O expander, designed for STM32 microcontrollers using the STM32 HAL SPI interface.

The driver provides a simple API for initializing the device, configuring GPIO directions, and reading or writing the I/O ports.

---

## Features

- STM32 HAL SPI interface
- Supports MCP23S17 hardware addressing
- Configure Port A and Port B directions
- Read GPIO Port A and Port B
- Write GPIO Port A and Port B
- Supports multiple MCP23S17 devices on the same SPI bus using hardware addressing
- Simple and lightweight implementation

---

## Repository Structure

```text
.
├── MCP23S17.c
├── MCP23S17.h
└── README.md
```

---

## Hardware Requirements

- STM32 MCU
- MCP23S17
- SPI Interface

---

## Quick Start

### Create Driver Instance

```c
MCP23S17_t ioExpander =
{
    .hspi = &hspi1,
    .CS_PORT_EXPANDER = GPIOA,
    .CS_PIN_EXPANDER = GPIO_PIN_4,
    .hardware_address = 0
};
```

### Initialize

```c
IOexpander_init(&ioExpander);
```

### Configure GPIO Direction

```c
// Configure all pins on Port A as outputs
set_IOexpander_direction(&ioExpander, PORT_A, 0x00);

// Configure all pins on Port B as inputs
set_IOexpander_direction(&ioExpander, PORT_B, 0xFF);
```

### Write GPIO

```c
write_IOexpander(&ioExpander, PORT_A, 0x55);
```

### Read GPIO

```c
uint8_t value = read_IOexpander(&ioExpander, PORT_B);
```

---

## API

| Function | Description |
|----------|-------------|
| `IOexpander_init()` | Initialize the MCP23S17 |
| `set_IOexpander_direction()` | Configure GPIO direction for Port A or Port B |
| `write_IOexpander()` | Write data to a GPIO port |
| `read_IOexpander()` | Read data from a GPIO port |

---

## Tested Hardware

| Component | Description |
|-----------|-------------|
| MCU | STM32F407 |
| I/O Expander | MCP23S17 |
| Framework | STM32 HAL |
| IDE | STM32CubeIDE |

---

## License

This project is released under the MIT License.
