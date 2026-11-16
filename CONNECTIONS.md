# Example connection guide — verify against your build

| Module | Signal | Arduino Uno |
|---|---|---|
| HX711 | DT / DOUT | D3 |
| HX711 | SCK / CLK | D2 |
| I2C LCD | SDA | A4 |
| I2C LCD | SCL | A5 |
| Modules | GND | GND |
| Modules | VCC | Follow module specifications |

## Load cell to HX711
Identify E+, E-, A+, and A- using the load-cell datasheet. Wire colours are not universal; do not guess them.

## Checks
- Verify HX711 supply voltage and logic compatibility.
- Confirm LCD I2C address (often 0x27 or 0x3F, but not guaranteed).
- Mount the load cell as specified by its manufacturer.
- Tare with the empty platform.
- Calibrate using known reference masses.
- Never exceed the load cell's rated capacity.
