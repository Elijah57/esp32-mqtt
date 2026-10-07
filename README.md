# esp32-node

ESP32 firmware (Arduino framework, PlatformIO) that joins a Wi-Fi network and talks to an MQTT broker on the local network. It publishes sensor readings and accepts commands such as toggling the on-board LED.

## Hardware

- An ESP32 dev board (`esp32dev`), for example an ESP32-DevKitC
- The on-board LED on GPIO 2 is used as the MQTT-controlled output

## Requirements

- [PlatformIO](https://platformio.org/) (CLI or IDE plugin)
- An MQTT broker on your network, such as [Mosquitto](https://mosquitto.org/) running on your laptop
- Optional: clangd for editor support (see [Editor setup](#editor-setup))

PlatformIO downloads the `espressif32` platform and the `knolleary/PubSubClient` library on the first build.

## Setup

1. Create your secrets file from the template:

   ```sh
   cp include/secrets.h.example include/secrets.h
   ```

2. Edit `include/secrets.h` and fill in your values:

   | Define      | Meaning                                       |
   |-------------|-----------------------------------------------|
   | `WIFI_SSID` | Wi-Fi network name                            |
   | `WIFI_PASS` | Wi-Fi password                                |
   | `MQTT_HOST` | IP address of the MQTT broker                 |
   | `MQTT_PORT` | Broker port (1883 for plain MQTT)             |

   `secrets.h` is gitignored. Never commit it.

3. Make sure the broker accepts connections from the LAN. With Mosquitto 2.x, add this to `mosquitto.conf`:

   ```
   listener 1883 0.0.0.0
   allow_anonymous true
   ```

## Build, flash, monitor

```sh
pio run                    # build
pio run -t upload          # flash to the board
pio device monitor         # serial monitor at 115200 baud
```

## MQTT topics

The client ID is `esp32-node-01`.

| Topic                    | Direction        | Payload                       |
|--------------------------|------------------|-------------------------------|
| `home/esp32/hello`       | device → broker  | Greeting sent on connect      |
| `home/esp32/temperature` | device → broker  | Temperature reading           |
| `home/esp32/led`         | broker → device  | `ON` turns the LED on, anything else turns it off |
| `home/esp32/status`      | device → broker  | Node status                   |

Test from your machine with the Mosquitto clients:

```sh
mosquitto_sub -h <broker-ip> -t 'home/esp32/#' -v
mosquitto_pub -h <broker-ip> -t home/esp32/led -m ON
```

## Project layout

```
include/
  secrets.h.example   Template for Wi-Fi and MQTT credentials
  config.h            Runtime settings (publish interval)
  wifi_manager.h      Wi-Fi connect, info printout, event handler
  mqtt_manager.h      MQTT setup, loop, publish helpers
  topic_handler.h     Topic enum and topic-string lookup table
  http_test.h         Simple HTTP GET used for connectivity checks
src/
  main.cpp            setup() / loop()
  config.cpp
  wifi_manager.cpp
  mqtt_manager.cpp
  topic_handler.cpp
  http_test.cpp
platformio.ini        Board, framework, and library dependencies
```

## Editor setup

`.clangd` is committed and strips the Xtensa-only compiler flags that clangd doesn't understand. To get a compilation database, run:

```sh
pio run -t compiledb
```

This writes `compile_commands.json` to the project root. The file is gitignored because it contains absolute paths. Your editor also needs to point clangd at the toolchain with `--query-driver`, for example:

```
--query-driver=~/.platformio/packages/toolchain-xtensa-esp32/bin/xtensa-esp32-elf-*
```

## Status

This is a work in progress. `main.cpp` currently handles MQTT directly. The `mqtt_manager` and `topic_handler` modules, which will replace that code, are still being written.
