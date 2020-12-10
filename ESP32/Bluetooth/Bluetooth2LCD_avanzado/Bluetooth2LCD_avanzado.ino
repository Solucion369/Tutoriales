#include <BluetoothSerial.h>
#include <Wire.h>
#include <hd44780.h>
#include <hd44780ioClass/hd44780_I2Cexp.h>

BluetoothSerial bt;
hd44780_I2Cexp lcd;
int fila, columna;

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

  int n = 0;
  if ( (n = bt.available()) ) {
    char msg[40] = "";

    while (n--) {
      char c = bt.read();
      if (c > 31) {
        sprintf(msg, "%s%c%c", msg, c, '\0');
      }
    }
    printMsg(msg);
  } 
  delay(20);
}

void printMsg(char *msg) {
  int columna, fila;
  columna = fila = 0;

  lcd.clear();
  while (*msg) {     
    lcd.setCursor (columna, fila);
    lcd.write(*msg++);
    
    columna++;
    if (columna > 15) {
      columna = 0;
      fila++;
    }
    if (fila > 1) return;    
  }
}
