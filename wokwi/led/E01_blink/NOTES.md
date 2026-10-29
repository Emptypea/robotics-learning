# E01 — Blink (baseline, with `delay`)

**Status:** ✅ Done — 2026-10-29
**Level:** 0 (Foundations)
**Board:** Arduino Uno (simulated in Wokwi)
**Circuit:** 1 LED on pin 11 — see `diagram.json`

## Goal
Get the classic blink working as a reference point: 500 ms on / 500 ms off (1 Hz), printing `ON` / `OFF` to Serial at each change.

## What I did
Wrote a sketch to the E01 requirements in `led_experiments.md`:
- LED on pin 11 (`const uint8_t LED_RED`) blinks 500 ms on / 500 ms off using `delay()`.
- Prints `ON` / `OFF` to Serial at each state change.
- Prints `millis()` at the top of `loop()` to observe the loop period.

### Bug: Serial log lagged the LED
- **Symptom:** `ON` appeared in the Serial Monitor just as the LED turned *off*, and vice versa.
- **Cause:** each `Serial.println` was placed after its `delay(500)`, so it ran half a period late.
- **Fix:** moved each print directly after its `digitalWrite`.

## What I learned

### Code habits
- **Put the log next to the action it describes**, not after the wait.
- **Name your pins.** Use `const uint8_t LED_RED = 11;` instead of a magic `11` repeated across the sketch.
- **`uint8_t` for pin numbers.** It fits in 1 byte, is idiomatic on an 8-bit MCU, and documents intent.

### `Serial.write()` vs `Serial.print()` vs `digitalWrite()`
- `digitalWrite(pin, HIGH/LOW)` sets the voltage on a pin (5 V / 0 V).
- `Serial.write()` sends **raw bytes** to the UART peripheral (TX pin / USB). The Serial Monitor is just whatever is listening on the other end.
- `Serial.write(55)` sends byte 55, which is ASCII `'7'`. `Serial.print(55)` sends the text `"55"` (two bytes).
- **Observed:** `Serial.write(55)` in `setup()`, followed by the first `millis()` print of `0`, showed up as `70`. That's `'7'` and `"0"` on the same line, because `write` adds no newline.

### `millis()` and `delay()` timing
- The gap between `millis()` prints is **not exactly 1000 ms**, for two reasons:
  1. `delay()` waits a fixed time *after* the other work in `loop()` (`digitalWrite`, `Serial.println`, the loop overhead). That work adds a few microseconds per iteration, and over time the period drifts.
  2. On the Uno, Timer0 ticks every **1.024 ms**, and `millis()` is kept roughly right by an occasional correction, so it's only accurate to about ±1 ms. I saw a gap of **999**.
- For finer timing, `micros()` has 4 µs resolution at 16 MHz.
- The drift from `delay()` is what E04 (blink without `delay()`) is meant to fix.

## Questions to answer
- **Difference between `Serial.write()` and `digitalWrite()`?** `Serial.write` sends data out through a communication peripheral (UART). `digitalWrite` sets the voltage on a pin. Neither can do the other's job.
- **Why do `millis()` prints jump by ~1000?** The two `delay(500)` calls make up 1000 ms per iteration. The rest of `loop()` adds a little on top, and `millis()` has ~1 ms resolution, so the gap is ~1000, not exactly 1000.

## Next
E02 — PWM brightness levels (already in progress; pin 11 is PWM-capable, Timer2 ≈ 490 Hz).
