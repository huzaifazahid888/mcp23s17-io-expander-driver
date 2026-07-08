# MCP23S17 I/O Expander Driver for STM32

A lightweight C driver for the Microchip MCP23S17 16-bit SPI I/O expander, built for STM32 using the HAL SPI interface. This is just the driver itself (`.c`/`.h`), meant to be dropped into an existing STM32 project rather than a full standalone example project. I'm using it in my own STM32F407 project alongside it.

The API is intentionally minimal: initialize the device, set GPIO direction on Port A/B, and read or write those ports.

## Features

- STM32 HAL SPI interface
- Supports MCP23S17 hardware addressing, so multiple devices can share the same SPI bus
- Configure direction for Port A and Port B independently
- Read and write both GPIO ports
- Small, dependency-free implementation

## Repo structure

```text
.
├── MCP23S17.c
├── MCP23S17.h
└── README.md
```

## Hardware used

STM32F407, MCP23S17, over SPI, built with STM32CubeIDE and STM32 HAL.

## Quick start

Create the driver instance:

```c
MCP23S17_t ioExpander =
{
    .hspi = &hspi1,
    .CS_PORT_EXPANDER = GPIOA,
    .CS_PIN_EXPANDER = GPIO_PIN_4,
    .hardware_address = 0
};
```

Initialize it:

```c
IOexpander_init(&ioExpander);
```

Set GPIO direction:

```c
// all pins on Port A as outputs
set_IOexpander_direction(&ioExpander, PORT_A, 0x00);

// all pins on Port B as inputs
set_IOexpander_direction(&ioExpander, PORT_B, 0xFF);
```

Write to a port:

```c
write_IOexpander(&ioExpander, PORT_A, 0x55);
```

Read from a port:

```c
uint8_t value = read_IOexpander(&ioExpander, PORT_B);
```

## API

| Function | Description |
|----------|-------------|
| `IOexpander_init()` | Initializes the MCP23S17 |
| `set_IOexpander_direction()` | Sets GPIO direction for Port A or Port B |
| `write_IOexpander()` | Writes data to a GPIO port |
| `read_IOexpander()` | Reads data from a GPIO port |
