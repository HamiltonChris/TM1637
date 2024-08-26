# TM1637 Driver
Simple portable driver for a TM1637 IC powering 4 digit seven segment display with a colon in the middle and no decimal points (3462BS-7.3).
## Interface
- `TM1637_init`: initializes the DIO and CLK pins
- `TM1637_write`: used to write digits to the display by passing a byte array that corresponds to each segment and the position of the first digit to be written to
- `TM1637_clear`: clears all segments
- `TM1637_set_brightness`: set the brightness level
- `TM1637_set_display_on`: configure whether the screen is on or off
## Configuration
Prior to calling `TM1637_init` a configuration structure `TM1637_config` must be created and intialized with function pointers for a delay function, GPIO setting for CLK and DIO and a function to change the DIO pin's GPIO mode and DIO read input function.
This configuration structure also contains members to control brightness, the display, and the delay time (max 2 micro seconds).
