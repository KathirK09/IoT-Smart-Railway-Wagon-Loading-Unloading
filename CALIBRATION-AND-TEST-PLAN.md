# Calibration and test plan

## Pre-test checklist
- [ ] Identify load-cell model and rated capacity.
- [ ] Check mechanical mounting.
- [ ] Verify HX711 and LCD wiring.
- [ ] Confirm LCD I2C address.
- [ ] Install required Arduino libraries.
- [ ] Ensure platform is empty and stable before tare.
- [ ] Use known reference masses within the load-cell rating.

## Calibration record
- Load-cell model:
- Rated capacity:
- Reference mass and unit:
- Raw HX711 reading:
- Calibration factor:
- Date and notes:

Determine the calibration factor using the library's calibration procedure and known reference masses. The example factor in the sketch is not valid calibration data.

## Test record
| Test | Reference load | Displayed load | Difference | Observation |
|---|---:|---:|---:|---|
| Empty platform | | | | |
| Known mass 1 | | | | |
| Known mass 2 | | | | |
| Add load gradually | | | | |
| Remove load gradually | | | | |

Do not exceed the load cell rating. Secure test masses and platform. This prototype does not establish a real railway wagon's safe loading capacity.
