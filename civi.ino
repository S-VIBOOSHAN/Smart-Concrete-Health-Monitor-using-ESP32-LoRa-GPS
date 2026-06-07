#include <WiFi.h>
#include <HTTPClient.h>
#include <Wire.h>
#include <Adafruit_SHT31.h>
#include <TinyGPS++.h>
#include <HX711.h>
#include <MPU6050.h>
#include <SPI.h>
// #include <LoRa.h>   // Uncomment if using LoRa

// -------------------- Wi-Fi --------------------
const char* WIFI_SSID = "YOUR_WIFI";
const char* WIFI_PASSWORD = "YOUR_PASSWORD";

// -------------------- ThingSpeak --------------------
String apiKey = "YOUR_THINGSPEAK_WRITE_API_KEY";

// -------------------- Sensors --------------------
Adafruit_SHT31 sht31 = Adafruit_SHT31();
TinyGPSPlus gps;
HardwareSerial GPSserial(2);

HX711 scale;
MPU6050 mpu;

// HX711 pins
#define HX711_DOUT 32
#define HX711_SCK  33

// GPS pins
#define GPS_RX 16
#define GPS_TX 17

// -------------------- Variables --------------------
float temperature = 0;
float humidity = 0;
float strainValue = 0;
float vibrationValue = 0;
float latitude = 0;
float longitude = 0;
int healthScore = 100;

// -------------------- Setup --------------------
void setup()
{
  Serial.begin(115200);

  Serial.println("====================================");
  Serial.println("SMART CONCRETE HEALTH MONITOR");
  Serial.println("ESP32 + GPS + SHT31 + MPU6050");
  Serial.println("====================================");

  Wire.begin();

  // Wi-Fi
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi Connected");

  // SHT31
  if (!sht31.begin(0x44))
  {
    Serial.println("SHT31 not found");
  }

  // HX711
  scale.begin(HX711_DOUT, HX711_SCK);

  // MPU6050
  mpu.initialize();

  // GPS
  GPSserial.begin(9600, SERIAL_8N1, GPS_RX, GPS_TX);

  Serial.println("System Ready");
}

// -------------------- Loop --------------------
void loop()
{
  readTemperatureHumidity();
  readStrain();
  readVibration();
  readGPS();
  calculateHealthScore();

  displayData();

  if (WiFi.status() == WL_CONNECTED)
  {
    sendThingSpeak();
  }

  // sendLoRaPacket(); // Enable if using LoRa

  delay(15000);
}

// -------------------- Read Sensors --------------------
void readTemperatureHumidity()
{
  temperature = sht31.readTemperature();
  humidity = sht31.readHumidity();
}

void readStrain()
{
  strainValue = scale.get_units(10);
}

void readVibration()
{
  int16_t ax, ay, az;
  mpu.getAcceleration(&ax, &ay, &az);

  vibrationValue =
    sqrt((float)ax * ax +
         (float)ay * ay +
         (float)az * az);
}

void readGPS()
{
  while (GPSserial.available())
  {
    gps.encode(GPSserial.read());
  }

  if (gps.location.isValid())
  {
    latitude = gps.location.lat();
    longitude = gps.location.lng();
  }
}

// -------------------- Health Score --------------------
void calculateHealthScore()
{
  healthScore = 100;

  if (temperature > 50)
    healthScore -= 15;

  if (humidity < 50)
    healthScore -= 10;

  if (strainValue > 500)
    healthScore -= 40;

  if (vibrationValue > 20000)
    healthScore -= 20;

  if (healthScore < 0)
    healthScore = 0;
}

// -------------------- ThingSpeak Upload --------------------
void sendThingSpeak()
{
  HTTPClient http;

  String url =
      "http://api.thingspeak.com/update?api_key=" +
      apiKey +
      "&field1=" + String(temperature) +
      "&field2=" + String(humidity) +
      "&field3=" + String(strainValue) +
      "&field4=" + String(vibrationValue) +
      "&field5=" + String(healthScore) +
      "&field7=" + String(latitude, 6) +
      "&field8=" + String(longitude, 6);

  http.begin(url);

  int code = http.GET();

  Serial.print("ThingSpeak Response: ");
  Serial.println(code);

  http.end();
}

// -------------------- Serial Monitor --------------------
void displayData()
{
  Serial.println();
  Serial.println("==================================");

  Serial.print("Temperature : ");
  Serial.print(temperature);
  Serial.println(" C");

  Serial.print("Humidity    : ");
  Serial.print(humidity);
  Serial.println(" %");

  Serial.print("Strain      : ");
  Serial.println(strainValue);

  Serial.print("Vibration   : ");
  Serial.println(vibrationValue);

  Serial.print("Latitude    : ");
  Serial.println(latitude, 6);

  Serial.print("Longitude   : ");
  Serial.println(longitude, 6);

  Serial.print("HealthScore : ");
  Serial.print(healthScore);
  Serial.println("%");

  if (strainValue > 500)
    Serial.println("CRACK ALERT");

  if (vibrationValue > 25000)
    Serial.println("EARTHQUAKE ALERT");

  Serial.println("==================================");
}void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:

}
