/**
 * Digital output pins (any digital pin)
 */
const uint8_t LEFT_IN1 = 8;
const uint8_t LEFT_IN2 = 9;
const uint8_t RIGHT_IN1 = 10;
const uint8_t RIGHT_IN2 = 11;

/**
 * Power pins must be PWM type in order to method analogWrite work)
 * In Leonardo PWM pins are: 3, 5-6, 9-11, 13
 */
const uint8_t LEFT_POWER = 5;
const uint8_t RIGHT_POWER = 6;

/*
 * LEFT_ENC_A and RIGHT_ENC_A must be an INTERRUPT type (in Leonardo INT pins are 0-3 and 7).
 * LEFT_ENC_A and RIGHT_ENC_A could by any digital pins.
 */
/* ENC_A must be INT pins (internal interrupt) */
const uint8_t LEFT_ENC_A = 2;
const uint8_t RIGHT_ENC_A = 3;
/* ENC_B is regular digital pin */
const uint8_t LEFT_ENC_B = 12;
const uint8_t RIGHT_ENC_B = 13;

/**
 * Joystick pin settings. Used when joystick is serial device (bluetooth).
 * Serial1 TX/RX pins
 */
const uint8_t JOYSTICK_WIRE_RX = 0;
const uint8_t JOYSTICK_WIRE_TX = 1;
const uint8_t JOYSTICK_TIMER = 0;
