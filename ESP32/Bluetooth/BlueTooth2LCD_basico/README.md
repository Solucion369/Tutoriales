Programa que recibe texto por bluetooth del ESP32 y lo escribe en un LCD LCD 16x2 (con módulo I2C)

Esta versión es muy básica y tiene limitaciones:

* Si la longitud del texto es mayor a 16 caracteres no se ve completo en el LCD
* Si el texto supera el buffer del LCD (normalmente unos 40 caracteres) el comportamiento es indefinido
