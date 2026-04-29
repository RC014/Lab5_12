#ifndef CONFIG_H
#define CONFIG_H

// Aplicatie activa:
// 51 = Lab 5.1 (control PID turatie motor)
// 52 = Lab 5.2 (control ON-OFF cu histereza pentru pozitie)
#define ACTIVE_APP_LAB 52

// Serial communication
#define SERIAL_BAUDRATE 9600

// ---------- Lab 5.1 ----------
// Driver L298
#define L298_ENA_PIN   9   // PWM
#define L298_IN1_PIN   8
#define L298_IN2_PIN   10

// Encoder rotativ tip CLK/DT/SW (ex: KY-040)
#define ENCODER_CLK_PIN 2
#define ENCODER_DT_PIN 3
#define ENCODER_SW_PIN 4
#define ENCODER_PPR 20

// Timpi aplicatie
#define CONTROL_PERIOD_MS 100
#define STATUS_PERIOD_MS 500

// Parametri Lab 5.2 (ON-OFF cu histereza)
#define ONOFF_HYSTERESIS_TICKS 3
#define ONOFF_SATURATION_POWER_PERCENT 50

// Pas de modificare manuala putere (%), folosit de srv_dc_motor
#define MOTOR_STEP_PERCENT 10
#endif
