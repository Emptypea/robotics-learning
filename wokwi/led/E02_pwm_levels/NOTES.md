# E02 — PWM brightness levels

**Status:** ✅ Done — 2026-10-29
**Level:** 0 (Foundations)
**Board:** Arduino Uno (simulated in Wokwi)
**Circuit:** 1 LED on PWM pin 6 (also tested on pin 11). See `diagram.json`.

## Goal
Build intuition for duty cycle: step through brightness values 0, 10, 50, 128, 200, 255 with a 1 s pause between each, printing each value. Values stored in an array and played by one loop instead of six copy-pasted blocks.

## Bugs found

### `Serial.println` is not `printf`
- **Symptom:** compile error `no matching function for call to 'println(const char [23], const int&)'` from `Serial.println("Current Brightness: %d", value)`.
- **Cause:** `println` prints one value. Its optional second argument is the **number base** (`DEC`, `HEX`, `BIN`), not a value to substitute. There are no format specifiers.
- **Lesson:** `Serial.println(255, HEX)` prints `FF`. To mix text and values, use separate `print` / `println` calls.

### `sizeof` returns bytes, not elements
- **Symptom:** after the six correct values, the loop printed `28483, 28013, 28261, 25955, 29728, 25960`.
- **Cause:** `int` is 2 bytes on the Uno, so `sizeof(brightness)` = 12. The loop ran 12 times and read past the end of the 6-element array (out-of-bounds, undefined behaviour).
- **The "garbage" was my own string:** read as little-endian byte pairs, the values decode to ASCII `"Co" "mm" "en" "ce" " t" "he"`, i.e. `"Commence the"`. The compiler placed that string literal right after the array in memory. The same values were also sent to `analogWrite`.
- **Fix:** loop over the element count, `sizeof(arr) / sizeof(arr[0])`, not the byte count.
- **Trap:** switching the array to `uint8_t` would make `sizeof` return 6 and *hide* the bug without fixing it.

## What PWM actually does
- A digital pin only ever outputs **0 V or 5 V**. It is never at 2.5 V.
- PWM switches the pin between them very fast. The `analogWrite` value (0–255) sets the **duty cycle**: the fraction of each cycle spent HIGH.
- `analogWrite(pin, 128)` ≈ 50% duty, so the *average* is ~2.5 V. The LED is flashing faster than the eye can see, and the eye averages it.
- 256 steps = 256 duty cycles, not 256 voltages. True analog output needs a DAC, which the Uno doesn't have.

## Measurements (Wokwi Logic Analyzer → `.vcd` → PulseView)
Import settings: compress idle periods `0`, downsampling factor `1`.

| Pin | Timer | Mode | Period | Frequency | HIGH time at 128 |
|---|---|---|---|---|---|
| 11 | Timer2 | Phase-correct PWM | ~2.04 ms | **490 Hz** (measured) | — |
| 6 | Timer0 | Fast PWM | **1.024 ms** (measured) | ~976.6 Hz | **0.512 ms** (measured, 50%) |

**Where the frequencies come from:**
- Arduino core sets a prescaler of 64: 16 MHz ÷ 64 = 250 kHz, so one tick = 4 µs.
- **Fast PWM** counts 0 → 255 and wraps: 256 ticks = 1.024 ms, giving ≈ 976.6 Hz.
- **Phase-correct PWM** counts 0 → 255 → 0: 510 ticks, giving 250,000 ÷ 510 ≈ 490.2 Hz.
- Fine detail: in fast PWM the pin is HIGH for (value + 1) ticks, so 128 → 129 ticks ≈ 0.516 ms. That's within one sample of my 0.512 ms reading. It's also why `analogWrite(pin, 0)` is special-cased to a plain `digitalWrite` LOW: otherwise there'd be a 1-tick spike instead of true off.

## Timers (how `millis()`, `delay()` and PWM share hardware)
- A **timer** is a hardware counter that ticks on its own, independently of my code, even during `delay()`.
- **Timer0:** ticks every 4 µs, counts 0 → 255, then wraps. One lap = **1.024 ms**.
  - Each lap triggers an overflow interrupt. The Arduino core counts laps, and `millis()` reads that count, **assuming 1.024 ms per lap** (with a small correction). `delay()` watches the same count.
  - The same counter drives PWM on pins 5 and 6: the pin is HIGH while the count is below the `analogWrite` value.
- **This is the 1.024 ms I measured on pin 6**, the same tick that made `millis()` read 999 instead of 1000 in E01.
- **Why reconfiguring Timer0 breaks `millis()` / `delay()`:**
  - Change its speed (e.g. 8× faster for higher PWM frequency) and `millis()` runs 8× too fast; `delay(1000)` ends after ~125 ms.
  - Disable its overflow interrupt and `millis()` freezes; `delay()` never returns.
  - One counter, two jobs. Changing it for one job breaks the other. (That's why E20 uses Timer1.)

### Uno timers

| Timer | Size | Arduino uses it for | PWM pins |
|---|---|---|---|
| Timer0 | 8-bit (0–255) | `millis()`, `micros()`, `delay()` | 5, 6 |
| Timer1 | 16-bit (0–65535) | Servo library | 9, 10 |
| Timer2 | 8-bit (0–255) | `tone()` | 3, 11 |

- Using the Servo library disables PWM on 9 and 10. `tone()` interferes with PWM on 3 and 11.
- **Rover relevance:** motor PWM and servos both need timers, so pin choice must account for this table.
- (There is also a separate watchdog timer, which is a safety reset mechanism, not a general-purpose timer.)

## Questions to answer
1. **What does `analogWrite(11, 128)` physically do to the pin voltage over time?**
   It switches the pin between 0 V and 5 V at ~490 Hz, HIGH for about half of each ~2.04 ms cycle. The average is ~2.5 V, but the pin is never actually at 2.5 V.
2. **What happens with `analogWrite` on pin 7 (not PWM)?**
   It compiles. `analogWrite` falls back to `digitalWrite`: values below 128 → LOW, 128 and above → HIGH. So 0, 10, 50 are off and 128, 200, 255 are on.
3. **Why does 10 → 50 look like a bigger change than 200 → 255?**
   The eye compares **ratios**, not differences (roughly logarithmic perception). 10 → 50 is 5× the light; 200 → 255 is only 1.27×. In Wokwi the steps looked roughly equal. Wokwi's LED rendering likely doesn't model human perception (unconfirmed). On a real LED the difference shows. This is the topic of E03.

## Next
E03 — Perceived brightness & gamma correction (core path: E04).
