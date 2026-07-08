/*
 * MCP23S17.h
 *      Author: M HUZAIFA
 */

#ifndef INC_MCP23S17_H_
#define INC_MCP23S17_H_


#define PORT_A  'A'
#define PORT_B  'B'

typedef struct {
    SPI_HandleTypeDef *hspi;
    GPIO_TypeDef *CS_PORT_EXPANDER;
    uint16_t CS_PIN_EXPANDER;
    uint8_t hardware_address;
} MCP23S17_t;


void IOexpander_init(MCP23S17_t *);
void set_IOexpander_direction(MCP23S17_t *, uint8_t , uint8_t );
void write_IOexpander(MCP23S17_t *, uint8_t , uint8_t );
uint8_t read_IOexpander(MCP23S17_t *, uint8_t );



#endif /* INC_MCP23S17_H_ */
