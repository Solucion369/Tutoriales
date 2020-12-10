#include <BluetoothSerial.h>
#include <Wire.h>
#include <hd44780.h>
#include <hd44780ioClass/hd44780_I2Cexp.h>

BluetoothSerial bt;
hd44780_I2Cexp lcd;

void setup() {
  Serial.begin(115200);
  bt.begin("ESP32 WROOM");
  Serial.print("Device ready");

  int status;
  status = lcd.begin(16, 2);
  if (status != 0)
  {
    hd44780::fatalError(status);    // Ya no vuelve, se queda aquí
  }
  lcd.clear();
}

void loop() {
  if (Serial.available()) {
    bt.write(Serial.read());
  }

  if (bt.available()) {
    char c = bt.read();
    
    // Descarta caracteres no visibles (0..31)
    if (c > 31) {
      lcd.write (c);
    }
  }
  delay(20);
}
