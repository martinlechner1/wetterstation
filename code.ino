#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
#include <LiquidCrystal.h>

Adafruit_BME280 bme;
LiquidCrystal lcd(7, 8, 9, 10, 11, 12);

#define I2C_ADDRESS (0x76) // If you sensor does not work switch this to 0x77
#define REFRESH_RATE (5000)

void setup()
{
  lcd.begin(16, 2);

  if (!bme.begin(I2C_ADDRESS) {
    lcd.setCursor(0, 0);
    lcd.print("SENSOR NOT CONNECTED");
    while (1)
      ;
  }
  // This is needed to make the temperature reading more reliable
  bme.setSampling(Adafruit_BME280::MODE_FORCED, // takeForcedMeasurement must be called before each reading
                  Adafruit_BME280::SAMPLING_X1, // Temp. oversampling
                  Adafruit_BME280::SAMPLING_X1, // Pressure oversampling
                  Adafruit_BME280::SAMPLING_X1, // Humidity oversampling
                  Adafruit_BME280::FILTER_OFF,
                  Adafruit_BME280::STANDBY_MS_1000);
}

void loop()
{
  bme.takeForcedMeasurement();
  lcd.setCursor(0, 0);
  lcd.print(bme.readTemperature());
  lcd.print(" C ");
  lcd.print(bme.readPressure() / 100.0F);
  lcd.setCursor(0, 1);
  lcd.print(bme.readHumidity());
  lcd.print(" % ");
  delay(REFRESH_RATE);
}