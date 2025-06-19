# Simple-MPPT-Arduino-based-Boost-Converter

A MPPT (Maximum Power Point Tracker) boost converter is a DC-DC converter that steps up the input voltage to a higher level. To achieve the best results we use MPPT algorithms to set the PWM (Pulse-Width Modulation) value, which controls the speed at which the switch (mosfet) opens and closes. In this case the MPPT algorithm I use is incremental conductance.

## Circuit design and components.
![schematic](/schematic.png)

Ιn the schematic no arduino was used, however the wiring logic is the same.  
Make sure to use a 22 Ohm resistor that can withstand up to 30 Watts.  
Use jumpers only between the controlers. Use hook-up wires in the rest of the circuit.

## Setup 

Build the ciruit as shown in the schematic and upload the code file to your arduino.
