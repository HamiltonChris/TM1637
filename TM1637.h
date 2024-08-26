/* @file TM1637.h
 *
 * @author Chris Hamilton
 *
 * @brief header file for a TM1637 IC powering a 3426BS seven segment display
 */

#ifndef TM1637_H
#define TM1637_H

#include <stdint.h>

#define DATA_COMMAND 	0x40
#define ADDRESS_COMMAND 0xC0
#define DISPLAY_COMMAND 0x80

#define DATA_READ  		0x02
#define FIXED_ADDRESS 	0x04
#define TEST_MODE		0x08

#define ADDRESS_C0H		0x00
#define ADDRESS_C1H		0x01
#define ADDRESS_C2H		0x02
#define ADDRESS_C3H		0x03
#define ADDRESS_C4H		0x04 // Not used
#define ADDRESS_C5H		0x05 // Not used

#define PULSE_WIDTH_1_16  0x00
#define PULSE_WIDTH_2_16  0x01
#define PULSE_WIDTH_4_16  0x02
#define PULSE_WIDTH_10_16 0x03
#define PULSE_WIDTH_11_16 0x04
#define PULSE_WIDTH_12_16 0x05
#define PULSE_WIDTH_13_16 0x06
#define PULSE_WIDTH_14_16 0x07

#define DISPLAY_ON		  0x08

#define SEGMENT_A	0x01
#define SEGMENT_B	0x02
#define SEGMENT_C	0x04
#define SEGMENT_D	0x08
#define SEGMENT_E	0x10
#define SEGMENT_F	0x20
#define SEGMENT_G	0x40
#define COLON   	0x80 	// Only for address C1H

#define ONE 		(SEGMENT_B | SEGMENT_C)
#define TWO 		(SEGMENT_A | SEGMENT_B | SEGMENT_D | SEGMENT_E | SEGMENT_G)
#define THREE 		(SEGMENT_A | SEGMENT_B | SEGMENT_C | SEGMENT_D | SEGMENT_G)
#define FOUR 		(SEGMENT_B | SEGMENT_C | SEGMENT_F | SEGMENT_G)
#define FIVE 		(SEGMENT_A | SEGMENT_C | SEGMENT_D | SEGMENT_F | SEGMENT_G)
#define SIX 		(SEGMENT_C | SEGMENT_D | SEGMENT_E | SEGMENT_F | SEGMENT_G)
#define SEVEN 		(SEGMENT_A | SEGMENT_B | SEGMENT_C)
#define EIGHT 		(SEGMENT_A | SEGMENT_B | SEGMENT_C | SEGMENT_D | SEGMENT_E | SEGMENT_F | SEGMENT_G)
#define NINE 		(SEGMENT_A | SEGMENT_B | SEGMENT_C | SEGMENT_F | SEGMENT_G)
#define ZERO 		(SEGMENT_A | SEGMENT_B | SEGMENT_C | SEGMENT_D | SEGMENT_E | SEGMENT_F)

#define LETTER_A 	(SEGMENT_A | SEGMENT_B | SEGMENT_C | SEGMENT_E | SEGMENT_F | SEGMENT_G)
#define LETTER_B	(SEGMENT_C | SEGMENT_D | SEGMENT_E | SEGMENT_F | SEGMENT_G)
#define LETTER_C	(SEGMENT_A | SEGMENT_D | SEGMENT_E | SEGMENT_F)
#define LETTER_D	(SEGMENT_B | SEGMENT_C | SEGMENT_D | SEGMENT_E | SEGMENT_G)
#define LETTER_E	(SEGMENT_A | SEGMENT_D | SEGMENT_E | SEGMENT_F | SEGMENT_G)
#define LETTER_F	(SEGMENT_A | SEGMENT_E | SEGMENT_F | SEGMENT_G)
#define LETTER_H	(SEGMENT_B | SEGMENT_C | SEGMENT_E | SEGMENT_F | SEGMENT_G)
#define LETTER_I	(SEGMENT_E)
#define LETTER_L	(SEGMENT_D | SEGMENT_E | SEGMENT_F)
#define LETTER_N	(SEGMENT_C | SEGMENT_E | SEGMENT_G)
#define LETTER_O	(SEGMENT_C | SEGMENT_D | SEGMENT_E | SEGMENT_G)
#define LETTER_P	(SEGMENT_A | SEGMENT_B | SEGMENT_E | SEGMENT_F | SEGMENT_G)
#define LETTER_R	(SEGMENT_E | SEGMENT_G)
#define LETTER_S 	FIVE
#define LETTER_U	(SEGMENT_B | SEGMENT_C | SEGMENT_D | SEGMENT_E | SEGMENT_F)

#define COLON_OFF 0
#define COLON_ON  1

#define MESSAGE_SIZE 8

#define TM1637_INPUT  0
#define TM1637_OUTPUT 1

#define TM1637_LOW 	0
#define TM1637_HIGH 1

#define ADDRESS_COUNT (ADDRESS_C3H + 1U)

typedef struct TM1637_config_s {
	uint8_t brightness;
	uint8_t display_on;
	uint8_t colon_on;
	uint16_t delay_time;
    void (*setDIO)(uint8_t);
    void (*setCLK)(uint8_t);
    void (*setDIO_pinMode)(uint8_t);
    uint8_t (*readDIO)(void);
    void (*delay)(uint16_t); // delay in microseconds
} TM1637_config;

void TM1637_init(TM1637_config* config);
void TM1637_write(const TM1637_config* config,
				  const uint8_t data[],
				  uint8_t length,
				  uint8_t position);
void TM1637_clear(const TM1637_config* config);
void TM1637_set_brightness(TM1637_config* config, uint8_t brightness);
void TM1637_set_display_on(TM1637_config* config, uint8_t display_on);


#endif // TM1637_H
