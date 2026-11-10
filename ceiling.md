| Image size | My prediction             | Measured | FPS  | Accuracy |
|------------|---------------------------|----------|------|----------|
| 96 × 96    | 500 ms (guess)            | 136 ms   | 7.4  | 95 %     |
| 160 × 160  | 381 ms (136 × 2.8)        | 272 ms   | 3.7  | 83 %     |
| 48 × 48    | 34 ms (136 ÷ 4)           | 66 ms    | 15.2 | 66 %     |

### Notes
- Config: ESP-NN **on** (`EI_CLASSIFIER_TFLITE_ENABLE_ESP_NN=1` + `_ESP_NN_S3=1`),
  not the course default (`=0`). With the default, 160 x 160 took ~12 000 ms (0.1 FPS).
- With ESP-NN on, every size first failed with `AllocateTensors() failed` (error -3):
  ESP-NN needs scratch memory that Edge Impulse's arena estimate doesn't include.
  Fixed by enlarging the arena by hand (160 px: 283 KB to 349 KB; 48 px: 60 KB to 192 KB).
- 48 px is slower than predicted because ~35 ms per call is fixed overhead
  (interpreter setup inside `run_classifier`); the model itself took 31 ms.

## Which budget breaks first - time or memory?

1. A doorbell: decide "person or not" within 1 second of the button press, at 96 x 96.
    **Memory.** 136 ms is ~7x under the 1 s limit, but the tensor arena already had to
    be enlarged to run at all. The time margin is much larger than the memory margin.
2. A people counter: keeps one 320 × 240 colour photo in memory and checks it once a minute.
    **Memory.** The photo alone is 320 x 240 x 3 = 230 KB, which together with the arena
    doesn't fit in the ~370 KB of free internal RAM, so it needs PSRAM.

3. Your team's project: which budget is tighter for your model, and why?
   **Time, but neither is close.** Our input is 54 x 42 grayscale = 2.3 KB, about the
   same number of pixels as the 48 x 48 test here but a third of the data (1 channel
   instead of 3). Memory is not an issue on the STM32N6 MCU we are using. It has 4.2 MB of internal
   RAM, against the 80 KB arena the 48 px model needed on the ESP32-S3. Time is the
   only budget that could bite, and only if some layers fall back from the NPU to the
   CPU. Even then the Cortex-M55 runs at 800 MHz versus the S3's 240 MHz, and the
   48 px model already took just 31 ms on the S3. Our real limit is accuracy: telling
   standing from sitting at 54 x 42 grayscale is harder than the binary task.