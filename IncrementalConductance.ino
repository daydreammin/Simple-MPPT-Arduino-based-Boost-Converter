#include <Arduino.h>
const int voltagePin = A0;      // Analog pin for voltage measurement
const int currentPin = A1;      // Analog pin for current measurement
const int switchPin = 6;        // Digital pin connected to the TC4422 input
const float delta = 2.0;        // A constant for adjusting the PWM value
float voltage;                  // Measured voltage
float current;                  // Measured current
float power;                    // To calculate power
float prev_current = 0.0;       // Previous current
float prev_voltage = 0.0;       // Previous voltage
float pwm = 128;                // Initial pwm value

void setup() {
  pinMode(switchPin, OUTPUT);
  analogWrite(switchPin, pwm);
  // TIMER0 registers setup for PWM
  TCCR0A=0;                   // Reset the register
  TCCR0B=0;                   // Reset the register
  TCCR0A=0b10100011;          // Fast pwm mode 0b10100011
  TCCR0B=0b00000001;          // Prescaler 64
  Serial.begin(9600);
}

void loop() {
  
  // Read voltage 
  voltage = analogRead(voltagePin) * (5.0 / 1023.0) * 5;
  // Read current
  current = analogRead(currentPin) * (5.0 / 1023.0) ; 
  // Calculate power
  power = voltage * current;

  // Print voltage, current and power values
  Serial.print("Voltage: ");
  Serial.print(voltage);
  Serial.print("V, Current: ");
  Serial.print(current);
  Serial.print("A, Power:");
  Serial.print(power);
  Serial.print("W, Previous Voltage: ");
  Serial.println(prev_voltage);

  // Calculate voltage and current differences
  float voltage_diff = voltage - prev_voltage ;
  float current_diff = current - prev_current;

  if(voltage_diff == 0 ) {
    if(current_diff = 0)
      return;
    else{
      // Adjust PWM based on the sign of current_diff
      if(current_diff > 0){
        pwm = pwm + voltage_diff - delta ;
        analogWrite(switchPin, constrain(pwm, 10, 170));    // Constrain the duty cycle so it will never
      }                                                     // be zero or too big and deliver too much 
      else{                                                 // voltage on the load.
        pwm = pwm - voltage_diff + delta ;
        analogWrite(switchPin, constrain(pwm, 10, 170));
      }
    }
 }else{
  // Adjust PWM based on the ratio of current_diff to voltage_diff
    if(current_diff/voltage_diff == -current/voltage)
      return;
    else{
      if(current_diff/voltage_diff > -current/voltage){
        pwm = pwm + voltage_diff - delta ;
        analogWrite(switchPin, constrain(pwm, 10, 170));
        }

      else{
        pwm = pwm - voltage_diff + delta ;
        analogWrite(switchPin, constrain(pwm, 10, 170));
        }
    }
  }

  prev_voltage = voltage;
  prev_current = current;
  delay(1);
}