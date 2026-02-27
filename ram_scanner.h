#include "esphome.h"
#include "driver/uart.h"

HardwareSerial* StoveSerialRam;
int current_ram_address = 0;

void init_ram_scanner() {
  pinMode(33, OUTPUT);
  digitalWrite(33, LOW);
  pinMode(16, INPUT_PULLUP);

  StoveSerialRam = new HardwareSerial(1);
  StoveSerialRam->begin(1200, SERIAL_8N2, 16, 17);
  uart_set_line_inverse(UART_NUM_1, UART_SIGNAL_TXD_INV);
  
  ESP_LOGI("RAM", "Rozpoczeto skanowanie pamieci RAM...");
}

void scan_next_ram() {
  while(StoveSerialRam->available()) StoveSerialRam->read();

  StoveSerialRam->write((byte)0x00);
  delay(1);
  StoveSerialRam->write((byte)current_ram_address);
  StoveSerialRam->flush();

  digitalWrite(33, HIGH);
  delay(2);

  unsigned long startTime = millis();
  byte response[2];
  int bytesRead = 0;

  while (millis() - startTime < 120) {
    if (StoveSerialRam->available()) {
      response[bytesRead] = StoveSerialRam->read();
      bytesRead++;
      if (bytesRead == 2) break;
    }
    delay(1);
  }

  digitalWrite(33, LOW);

  if (bytesRead == 2) {
    byte checksum = response[0];
    byte value = response[1];
    
    byte expected_checksum = (0x00 + current_ram_address + value) & 0xFF;

    if (checksum == expected_checksum) {
      ESP_LOGI("RAM", "Adres: 0x%02X ---> Wartosc: %3d", current_ram_address, value);
    }
  }
  
  current_ram_address++;
  if (current_ram_address > 255) {
    ESP_LOGI("RAM", "=== ZAKONCZONO SKANOWANIE RAM ===");
    current_ram_address = 0; 
  }
}