/*
 * @file TM1637.c
 *
 * @author Chris Hamilton
 *
 * @brief Implements TM1637 driver
 */

#include "TM1637.h"

static void start(const TM1637_config* config);
static void stop(const TM1637_config* config);
static uint8_t write(const TM1637_config* config, uint8_t byte);

void TM1637_init(TM1637_config* config)
{
	// check values are valid

	// set DIO and CLK to HIGH
	config->setDIO(TM1637_HIGH);
	config->setCLK(TM1637_HIGH);
	config->delay(config->delay_time);
}

void TM1637_write(const TM1637_config* config, const uint8_t data[], uint8_t length, uint8_t position)
{
	start(config);
	write(config, DATA_COMMAND);
	stop(config);

	start(config);
	write(config, ADDRESS_COMMAND | position);

	for (uint8_t i = 0; i < length; i++)
	{
		if (config->colon_on && (position + i) == ADDRESS_C1H)
		{
			write(config, data[i] | COLON);
		}
		else
		{
			write(config, data[i]);
		}
	}
	stop(config);

	start(config);
	write(config, DISPLAY_COMMAND | config->display_on | config->brightness);
	stop(config);

	start(config);
	write(config, DATA_COMMAND);
	stop(config);
}

void TM1637_clear(const TM1637_config* config)
{
	uint8_t data[ADDRESS_COUNT] = {0x00, 0x00, 0x00, 0x00};
	TM1637_write(config, data, ADDRESS_COUNT, ADDRESS_C0H);
}


void TM1637_set_brightness(TM1637_config* config, uint8_t brightness)
{
	config->brightness = brightness;
}

void TM1637_set_display_on(TM1637_config* config, uint8_t display_on)
{
	config->display_on = display_on ? DISPLAY_ON : 0x00;
}


static void start(const TM1637_config* config)
{
	config->setDIO(TM1637_LOW);
	config->delay(config->delay_time);
}

static void stop(const TM1637_config* config)
{
	config->setCLK(TM1637_LOW);
	config->delay(config->delay_time);
	config->setDIO(TM1637_LOW);
	config->delay(config->delay_time);
	config->setCLK(TM1637_HIGH);
	config->delay(config->delay_time);
	config->setDIO(TM1637_HIGH);
	config->delay(config->delay_time);
}

static uint8_t write(const TM1637_config* config, uint8_t byte)
{
	uint8_t ack = TM1637_HIGH;
	// Write byte to TM1637
	for (uint8_t i = 0; i < MESSAGE_SIZE; i++) {
		config->setCLK(TM1637_LOW);
		config->delay(config->delay_time);
		config->setDIO(byte & 0x01);
		config->delay(config->delay_time);
		config->setCLK(TM1637_HIGH);
		config->delay(config->delay_time);
		byte = byte >> 1;
	}

	// Read ACK from TM1637
	config->setCLK(TM1637_LOW);
	config->delay(config->delay_time);
	config->setDIO_pinMode(TM1637_INPUT);
	config->delay(config->delay_time);
	config->setCLK(TM1637_HIGH);
	config->delay(config->delay_time);
	ack = config->readDIO();
	config->delay(config->delay_time);
	config->setCLK(TM1637_LOW);
	config->delay(config->delay_time);
	config->setDIO_pinMode(TM1637_OUTPUT);
	config->setDIO(TM1637_LOW);
	return ack;
}
