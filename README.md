# ARTEL - MicronovaPelletStoveController — Projekt

Projekt zawiera pliki pomocnicze do odczytu pamięci EEPROM i RAM pieca Artel Model: BOILER16AR-AUTO.

- Zawartość katalogu: pliki nagłówkowe i skrypty YAML służące do odczytu/analizy: `eeprom_scanner.h`, `ram_scanner.h`, `artel.yaml`, `read_artel_eeprom.yaml`, `read_artel_ram.yaml`.

Jak używać
- Zapoznaj się z dostarczonymi plikami `.yaml` i nagłówkami; projekt to zbiór definicji i konfiguracji — nie zawiera binarnego oprogramowania urządzenia.

Licencja
- Projekt objęty jest licencją MIT — patrz plik `LICENSE`.

Główne pliki i rola
- `artel.yaml` — główny plik konfiguracyjny do wgrania na płytkę ESP32 (ESPHome). To on zawiera ustawienia Wi‑Fi, OTA, API, konfigurację UART/Micronova oraz definicje czujników i akcji. Należy wgrać właśnie `artel.yaml` na ESP32.
- `eeprom_scanner.h`, `ram_scanner.h`, `read_artel_eeprom.yaml`, `read_artel_ram.yaml` — pliki pomocnicze/diagnostyczne do analizy pamięci EEPROM/RAM pieca.

Główne elementy i możliwości po wgraniu `artel.yaml` na ESP32
- Integracja z magistralą Micronova przez UART (konfiguracja TX/RX, prędkość 1200 bps, dodatkowy pin RX enable).
- Udostępnienie danych przez API i OTA (aktualizacje firmware przez sieć).
- Sensory odczytujące: temperatura wody, temperatura spalin, ciśnienie wody, prędkość wentylatora (RPM), zadana moc, surowy status operacyjny.
- Template sensor/tekstowy: czytelny opis stanu pracy pieca (Wyłączony, Start, Rozpalanie, Praca robocza, Tryb ECO itp.).
- Obliczenie chwilowego spalania (kg/h) na podstawie stanu pieca, zadanej mocy oraz dynamicznej korekty pelletu.
- Przyciski/akcje: przycisk "Kalibruj czasy" wymuszający aktualizację wewnętrznej korekty pelletu.
- Logger z poziomem DEBUG (przydatne przy diagnostyce) oraz konfiguracja podstawowa ESP32 (`esp32dev`, framework Arduino).


English
----------------

This repository contains helper files for reading EEPROM and RAM of the Artel boiler Model: BOILER16AR-AUTO. The project name on GitHub is
"ARTEL - MicronovaPelletStoveController".

- Contents: header files and YAML configurations for reading/analysis: `eeprom_scanner.h`, `ram_scanner.h`, `artel.yaml`, `read_artel_eeprom.yaml`, `read_artel_ram.yaml`.

Usage
- Review the YAML definitions and headers; the main file to flash to an ESP32 running ESPHome is `artel.yaml`.

Main files and role
- `artel.yaml` — main configuration file to upload to an ESP32 (ESPHome). It contains Wi‑Fi, OTA, API, UART/Micronova configuration and sensors/actions. Flash this file to the ESP32.
- `eeprom_scanner.h`, `ram_scanner.h`, `read_artel_eeprom.yaml`, `read_artel_ram.yaml` — helper/diagnostic files for EEPROM/RAM analysis.

Key features and capabilities when `artel.yaml` runs on ESP32
- Micronova bus integration over UART (configured TX/RX, 1200 bps and RX enable pin).
- API and OTA support (network access and over-the-air updates).
- Sensors: water temperature, fumes temperature, water pressure, fan RPM, set power and raw operational status.
- Template text sensor: human-friendly stove operational state (Off, Start, Ignition, Working, ECO mode, etc.).
- Computation of instantaneous fuel consumption (kg/h) using stove state, set power and dynamic pellet correction.
- Template button/action: "Calibrate times" to update pellet timing correction.
- Debug `logger` (DEBUG level) and standard ESP32 (`esp32dev`) Arduino framework configuration.

License
- MIT License — see `LICENSE`.
