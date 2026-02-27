#include "esphome.h"
#include "driver/uart.h"

HardwareSerial* StoveSerialEeprom;
int current_eeprom_address = 0;

void init_eeprom_scanner() {
  pinMode(33, OUTPUT);
  digitalWrite(33, LOW);
  pinMode(16, INPUT_PULLUP);

  StoveSerialEeprom = new HardwareSerial(1);
  StoveSerialEeprom->begin(1200, SERIAL_8N2, 16, 17);
  uart_set_line_inverse(UART_NUM_1, UART_SIGNAL_TXD_INV);
  
  ESP_LOGI("EEPROM", "Rozpoczeto skanowanie pamieci EEPROM...");
}

void scan_next_eeprom() {
  while(StoveSerialEeprom->available()) StoveSerialEeprom->read();

  StoveSerialEeprom->write((byte)0x20);
  delay(1);
  StoveSerialEeprom->write((byte)current_eeprom_address);
  StoveSerialEeprom->flush();

  digitalWrite(33, HIGH);
  delay(2);

  unsigned long startTime = millis();
  byte response[2];
  int bytesRead = 0;

  while (millis() - startTime < 120) {
    if (StoveSerialEeprom->available()) {
      response[bytesRead] = StoveSerialEeprom->read();
      bytesRead++;
      if (bytesRead == 2) break;
    }
    delay(1);
  }

  digitalWrite(33, LOW);

  if (bytesRead == 2) {
    byte checksum = response[0];
    byte value = response[1];
    
    byte expected_checksum = (0x20 + current_eeprom_address + value) & 0xFF;

    if (checksum == expected_checksum) {
      ESP_LOGI("EEPROM", "Adres: 0x%02X ---> Wartosc: %3d", current_eeprom_address, value);
    }
  }
  
  current_eeprom_address++;
  if (current_eeprom_address > 255) {
    ESP_LOGI("EEPROM", "=== ZAKONCZONO SKANOWANIE EEPROM ===");
    // Wyzerowanie licznika wymusza kolejny pełny skan
    current_eeprom_address = 0; 
  }
}