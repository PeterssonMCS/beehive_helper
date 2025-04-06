# Final Project of Embarcatech

This project contains a modular approach for a embbedded device that tracks temperature and umidity inside a bee hive,
as well a anti-theft approach.

## Features

- Measures internal temperature (°C)  
- Measures humidity (%RH)
- Indicator of bee hive Status
- Anti theft alarm
---

## Hardware Components

- **MCU**: Raspberry Pi Pico W (BitdogLab board)
- **Temperature/Humidity Sensor**: AHT10
- **Power Source**: Li-Ion battery with optional solar panel
- **Temperature Controller**: 12V Fan
- **Anti-Theft device**: Buzzer
- **Indicator of bee hive health status**: RGB Led

---

## 🛠️ Firmware Features

- Written in C/C++ using VsCode with Raspberry Pi Pico Project extension 
- Non preemptive RTOS
- Non-blocking sensor read routines  
- Periodic or on-demand data readings
- Optional real-time clock (RTC) for timestamped data