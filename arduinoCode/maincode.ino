#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_ADXL345_U.h>

// Replace with your network credentials
const char *ssid = "robot";
const char *password = "12345678";

int button = D0;

/* Assign a unique ID to this sensor at the same time */
Adafruit_ADXL345_Unified accel = Adafruit_ADXL345_Unified(12345);

void displaySensorDetails(void)
{
  sensor_t sensor;
  accel.getSensor(&sensor);
  Serial.println("------------------------------------");
  Serial.print("Sensor: ");
  Serial.println(sensor.name);
  Serial.print("Driver Ver: ");
  Serial.println(sensor.version);
  Serial.print("Unique ID: ");
  Serial.println(sensor.sensor_id);
  Serial.print("Max Value: ");
  Serial.print(sensor.max_value);
  Serial.println(" m/s^2");
  Serial.print("Min Value: ");
  Serial.print(sensor.min_value);
  Serial.println(" m/s^2");
  Serial.print("Resolution: ");
  Serial.print(sensor.resolution);
  Serial.println(" m/s^2");
  Serial.println("------------------------------------");
  Serial.println("");
  delay(500);
}

void displayDataRate(void)
{
  Serial.print("Data Rate: ");

  switch (accel.getDataRate())
  {
  case ADXL345_DATARATE_3200_HZ:
    Serial.print("3200 ");
    break;
  case ADXL345_DATARATE_1600_HZ:
    Serial.print("1600 ");
    break;
  case ADXL345_DATARATE_800_HZ:
    Serial.print("800 ");
    break;
  case ADXL345_DATARATE_400_HZ:
    Serial.print("400 ");
    break;
  case ADXL345_DATARATE_200_HZ:
    Serial.print("200 ");
    break;
  case ADXL345_DATARATE_100_HZ:
    Serial.print("100 ");
    break;
  case ADXL345_DATARATE_50_HZ:
    Serial.print("50 ");
    break;
  case ADXL345_DATARATE_25_HZ:
    Serial.print("25 ");
    break;
  case ADXL345_DATARATE_12_5_HZ:
    Serial.print("12.5 ");
    break;
  case ADXL345_DATARATE_6_25HZ:
    Serial.print("6.25 ");
    break;
  case ADXL345_DATARATE_3_13_HZ:
    Serial.print("3.13 ");
    break;
  case ADXL345_DATARATE_1_56_HZ:
    Serial.print("1.56 ");
    break;
  case ADXL345_DATARATE_0_78_HZ:
    Serial.print("0.78 ");
    break;
  case ADXL345_DATARATE_0_39_HZ:
    Serial.print("0.39 ");
    break;
  case ADXL345_DATARATE_0_20_HZ:
    Serial.print("0.20 ");
    break;
  case ADXL345_DATARATE_0_10_HZ:
    Serial.print("0.10 ");
    break;
  default:
    Serial.print("???? ");
    break;
  }
  Serial.println(" Hz");
}

void displayRange(void)
{
  Serial.print("Range: +/- ");

  switch (accel.getRange())
  {
  case ADXL345_RANGE_16_G:
    Serial.print("16 ");
    break;
  case ADXL345_RANGE_8_G:
    Serial.print("8 ");
    break;
  case ADXL345_RANGE_4_G:
    Serial.print("4 ");
    break;
  case ADXL345_RANGE_2_G:
    Serial.print("2 ");
    break;
  default:
    Serial.print("?? ");
    break;
  }
  Serial.println(" g");
}

void setup()
{
  Serial.begin(115200);
  pinMode(button, INPUT);
  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");
  Serial.println("Accelerometer Test");
  Serial.println("");

  /* Initialise the sensor */
  if (!accel.begin())
  {
    /* There was a problem detecting the ADXL345 ... check your connections */
    Serial.println("Ooops, no ADXL345 detected ... Check your wiring!");
    while (1)
      ;
  }

  /* Set the range to whatever is appropriate for your project */
  accel.setRange(ADXL345_RANGE_16_G);
  // displaySetRange(ADXL345_RANGE_8_G);
  // displaySetRange(ADXL345_RANGE_4_G);
  // displaySetRange(ADXL345_RANGE_2_G);

  /* Display some basic information on this sensor */
  displaySensorDetails();

  /* Display additional settings (outside the scope of sensor_t) */
  displayDataRate();
  displayRange();
  Serial.println("");
}
int count = 1;
char *url = "http://192.168.29.84:5000/getVehicleStatus?id=129839182&accident=true&rash=false&location=14.4292004,79.607890&severity=high&falseAlarmTrigger=false";
void loop()
{
  count = count + 1;
  // Check if NodeMCU is connected to the WiFi network
  sensors_event_t event;
  accel.getEvent(&event);
  int value = digitalRead(button);

  /* Display the results (acceleration is measured in m/s^2) */
  Serial.print("X: ");
  Serial.print(event.acceleration.x);
  Serial.print(" ");
  Serial.print("Y: ");
  Serial.print(event.acceleration.y);
  Serial.print(" ");
  Serial.print("Z: ");
  Serial.print(event.acceleration.z);
  Serial.print(" ");
  Serial.print("burron: ");
  Serial.print(value);
  Serial.print(" ");
  Serial.println("m/s^2 ");
  if (count > 100)
  {
    count = 1;
    url = "http://192.168.29.84:5000/getVehicleStatus?id=129839182&accident=false&rash=false&location=14.4292004,79.607492&severity=high&falseAlarmTrigger=false";
    if (WiFi.status() == WL_CONNECTED)
    {
      // Create a WiFi client object
      WiFiClient wifiClient;

      // Make HTTP GET request
      HTTPClient http;

      // char url[100];
      // sprintf(url, "http://192.168.253.153:5000/getVehicleStatus?accident=true&rash=false&location=%s,%s", dtostrf(latitude, 7, 6, url), dtostrf(longitude, 8, 6, url));

      http.begin(wifiClient, url);

      int httpResponseCode = http.GET();
      if (httpResponseCode > 0)
      {
        Serial.print("HTTP response code: ");
        Serial.println(httpResponseCode);
        String payload = http.getString();
        Serial.println("Response payload:");
        Serial.println(payload);
      }
      else
      {
        Serial.print("Error code: ");
        Serial.println(httpResponseCode);
        Serial.print("Error message: ");
        Serial.println(http.errorToString(httpResponseCode).c_str());
      }

      http.end(); // Close HTTP connection
    }
  }
  if (count == 50)
  {
    url = "http://192.168.29.84:5000/getVehicleStatus?id=129839182&accident=false&rash=false&location=14.4292004,79.607894&severity=high&falseAlarmTrigger=false";
    if (WiFi.status() == WL_CONNECTED)
    {
      // Create a WiFi client object
      WiFiClient wifiClient;

      // Make HTTP GET request
      HTTPClient http;

      // char url[100];
      // sprintf(url, "http://192.168.253.153:5000/getVehicleStatus?accident=true&rash=false&location=%s,%s", dtostrf(latitude, 7, 6, url), dtostrf(longitude, 8, 6, url));

      http.begin(wifiClient, url);

      int httpResponseCode = http.GET();
      if (httpResponseCode > 0)
      {
        Serial.print("HTTP response code: ");
        Serial.println(httpResponseCode);
        String payload = http.getString();
        Serial.println("Response payload:");
        Serial.println(payload);
      }
      else
      {
        Serial.print("Error code: ");
        Serial.println(httpResponseCode);
        Serial.print("Error message: ");
        Serial.println(http.errorToString(httpResponseCode).c_str());
      }

      http.end(); // Close HTTP connection
    }
  }
  if (event.acceleration.x >= 5)
  {
    url = "http://192.168.29.84:5000/getVehicleStatus?id=129839182&accident=false&rash=true&location=14.4292004,79.607899&severity=high&falseAlarmTrigger=false";
    if (WiFi.status() == WL_CONNECTED)
    {
      // Create a WiFi client object
      WiFiClient wifiClient;

      // Make HTTP GET request
      HTTPClient http;

      // char url[100];
      // sprintf(url, "http://192.168.253.153:5000/getVehicleStatus?accident=true&rash=false&location=%s,%s", dtostrf(latitude, 7, 6, url), dtostrf(longitude, 8, 6, url));

      http.begin(wifiClient, url);

      int httpResponseCode = http.GET();
      if (httpResponseCode > 0)
      {
        Serial.print("HTTP response code: ");
        Serial.println(httpResponseCode);
        String payload = http.getString();
        Serial.println("Response payload:");
        Serial.println(payload);
      }
      else
      {
        Serial.print("Error code: ");
        Serial.println(httpResponseCode);
        Serial.print("Error message: ");
        Serial.println(http.errorToString(httpResponseCode).c_str());
      }

      http.end(); // Close HTTP connection
    }
  }
  if (event.acceleration.y >= 5)
  {
    url = "http://192.168.29.84:5000/getVehicleStatus?id=129839182&accident=true&rash=false&location=14.4292004,79.607894&severity=high&falseAlarmTrigger=false";
    if (WiFi.status() == WL_CONNECTED)
    {
      // Create a WiFi client object
      WiFiClient wifiClient;

      // Make HTTP GET request
      HTTPClient http;

      // char url[100];
      // sprintf(url, "http://192.168.253.153:5000/getVehicleStatus?accident=true&rash=false&location=%s,%s", dtostrf(latitude, 7, 6, url), dtostrf(longitude, 8, 6, url));

      http.begin(wifiClient, url);

      int httpResponseCode = http.GET();
      if (httpResponseCode > 0)
      {
        Serial.print("HTTP response code: ");
        Serial.println(httpResponseCode);
        String payload = http.getString();
        Serial.println("Response payload:");
        Serial.println(payload);
      }
      else
      {
        Serial.print("Error code: ");
        Serial.println(httpResponseCode);
        Serial.print("Error message: ");
        Serial.println(http.errorToString(httpResponseCode).c_str());
      }

      http.end(); // Close HTTP connection
    }
  }
  if (value == 0)
  {
    url = "http://192.168.29.84:5000/getVehicleStatus?id=129839182&accident=true&rash=false&location=0&severity=high&falseAlarmTrigger=true";
    if (WiFi.status() == WL_CONNECTED)
    {
      // Create a WiFi client object
      WiFiClient wifiClient;

      // Make HTTP GET request
      HTTPClient http;

      // char url[100];
      // sprintf(url, "http://192.168.253.153:5000/getVehicleStatus?accident=true&rash=false&location=%s,%s", dtostrf(latitude, 7, 6, url), dtostrf(longitude, 8, 6, url));

      http.begin(wifiClient, url);

      int httpResponseCode = http.GET();
      if (httpResponseCode > 0)
      {
        Serial.print("HTTP response code: ");
        Serial.println(httpResponseCode);
        String payload = http.getString();
        Serial.println("Response payload:");
        Serial.println(payload);
      }
      else
      {
        Serial.print("Error code: ");
        Serial.println(httpResponseCode);
        Serial.print("Error message: ");
        Serial.println(http.errorToString(httpResponseCode).c_str());
      }

      http.end(); // Close HTTP connection
    }
  }
  delay(3000);
}