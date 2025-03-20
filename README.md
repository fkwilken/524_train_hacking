# Lionel Train Hacking Project

## ESP32 / NRF24 Transmitter

The ESP32 code is built using [platformio](https://platformio.org/). 
Get the VS Code extension or install it and use:
- `pio run` to build
- `pio run -t upload` to upload

The NRF transmitter chip is driven using the [RF24](https://nrf24.github.io/RF24/) arduino library.

- To change the frequency, use `radio.setChannel(offset);`, where offset is the integer frequency offset from 2400 Mhz.
- To jam the pairing, use `radio.setChannel(40);` to broadcast at the pairing frequency of 2440 Mhz.
- To jam the train while it is running, use an SDR to find the approximate frequency that the train is running on
  - Use one transmitter board to jam the pairing frequency, 2440 Mhz
  - Reprogram a second transmitter board to jam the actively running frequency. For example, if you see activity at 2420 Mhz, set the channel to 20.

## PCB

![image](https://github.com/user-attachments/assets/ef9f5487-ea21-4297-a308-bca34cef303d)
