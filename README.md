[![ESP32](https://img.shields.io/badge/ESP32-Arduino-blue)](
https://en.wikipedia.org/wiki/ESP32
)
[![cpp-logo](https://img.shields.io/badge/C++17-Solutions-blue.svg?style=flat&logo=c%2B%2B)](
https://en.wikipedia.org/wiki/C++
)
[![php-logo](https://img.shields.io/badge/Php-Solutions-blue.svg?logo=Symfony)](
https://en.wikipedia.org/wiki/PHP
)
[![doсker-logo](https://img.shields.io/badge/Docker-Solutions-blue.svg?style=flat&logo=Docker)](
https://en.wikipedia.org/wiki/Docker
)

# UpdaterEsp32
Update Esp32 from remote host

---

# Arduino Framework Project

## Description
Firmware for ESP32 microcontroller written in C++ using Arduino framework. Core functionality includes Wi-Fi connectivity, UART interface management, and OTA update capabilities.

## Project Structure

### Core Files
- `Arduino.ino` - Main entry point with `setup()` and `loop()`
- `src/Application.h` - UART interface controller
- `src/Container.h` - Global objects container
- `src/Configure.h` - Environment configuration
- `partitions.csv` - ESP32 memory partition table

### Support Files
- `build-flashing-monitor.sh` - Build and flash script
- `Dockerfile` - Docker environment configuration

## Functionality

### Initialization
- UART configuration with:
  - Baud rate
  - Data bits
  - Parity control
  - Stop bits
  - Flow control

### Network
- Wi-Fi network connection
- Connection status monitoring

### System Features
- Periodic firmware version output
- OTA update support
- Optional LED status indicator

## Requirements
- Arduino CLI
- Docker (for containerized build)
- Libraries:
  - WiFi
  - HTTPClient
  - AsyncTCP
  - ArduinoJson

## Building
Supported build methods:
- Arduino CLI
- Docker container

Required configurations:
- Wi-Fi SSID and password
- Firmware version specification

## Technical Notes
- Singleton pattern for global object access
- Custom memory partitioning via partitions.csv
- Dual-mode operation:
  - Debug (verbose logging)
  - Production

## Docker Usage

### Purpose
Docker is used for:
1. Building firmware in isolated environment
2. Flashing to microcontroller
3. Serial port monitoring

### Requirements
- Installed Docker
- USB port access (for flashing)

### Environment Variables
Must be set:
- `A0S_SSID` - WiFi network name
- `A0S_PASSWORD` - WiFi password
- `A0S_SW_VER` - Firmware version
- `A0S_USBNAME` - Serial device path

---

# ESP32 Firmware Update Server

## Project Description
Web server component for managing ESP32 firmware updates, built with Symfony PHP framework.

## Technical Stack
- **Backend**: Symfony 7.0
- **Database**: SQLite
- **File Storage**: VichUploaderBundle
- **Frontend**: Bootstrap 5.3, Twig templates
- **Server**: Caddy (configurable)

## Installation
1. Clone repository
2. Run `composer install`
3. Configure `.env` file:
   ```ini
   DATABASE_URL=sqlite:///%kernel.project_dir%/data/database.sqlite
   SERVER_NAME=:80
   ```

---
   
## Contributing
PRs and questions are welcome! No strict requirements for contributors.

## License
Project is MIT licensed. See [LICENSE](https://github.com/Alex0vSky/UpdaterEsp32/blob/main/LICENSE) for details.
