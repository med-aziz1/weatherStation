#include "Screen.h"
TwoWire I2Cdisplay = TwoWire(1);
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &I2Cdisplay, -1);

dhtSensor value;
// Insert your network credentials
const char *ssid = "Wokwi-GUEST";
const char *password = "";

// NTP Server Details
const char *ntpServer = "pool.ntp.org";
const long gmtOffset_sec = 1;
const int daylightOffset_sec = 3600;

unsigned char temperature_icon[] = {
    0b00000001, 0b11000000, //        ###
    0b00000011, 0b11100000, //       #####
    0b00000111, 0b00100000, //      ###  #
    0b00000111, 0b11100000, //      ######
    0b00000111, 0b00100000, //      ###  #
    0b00000111, 0b11100000, //      ######
    0b00000111, 0b00100000, //      ###  #
    0b00000111, 0b11100000, //      ######
    0b00000111, 0b00100000, //      ###  #
    0b00001111, 0b11110000, //     ########
    0b00011111, 0b11111000, //    ##########
    0b00011111, 0b11111000, //    ##########
    0b00011111, 0b11111000, //    ##########
    0b00011111, 0b11111000, //    ##########
    0b00001111, 0b11110000, //     ########
    0b00000111, 0b11100000, //      ######
};
unsigned char humidity_icon[] = {
    0b00000000, 0b00000000, //
    0b00000001, 0b10000000, //        ##
    0b00000011, 0b11000000, //       ####
    0b00000111, 0b11100000, //      ######
    0b00001111, 0b11110000, //     ########
    0b00001111, 0b11110000, //     ########
    0b00011111, 0b11111000, //    ##########
    0b00011111, 0b11011000, //    ####### ##
    0b00111111, 0b10011100, //   #######  ###
    0b00111111, 0b10011100, //   #######  ###
    0b00111111, 0b00011100, //   ######   ###
    0b00011110, 0b00111000, //    ####   ###
    0b00011111, 0b11111000, //    ##########
    0b00001111, 0b11110000, //     ########
    0b00000011, 0b11000000, //       ####
    0b00000000, 0b00000000, //
};
void Screens::beginS()
{
    I2Cdisplay.begin(OLED_SDA_PIN, OLED_SCL_PIN, 100000);
    // Initialize OLED Display
    if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C))
    {
        Serial.println(F("SSD1306 allocation failed"));
        for (;;)
            ;
    }
    display.clearDisplay();
    display.setTextColor(WHITE);

    // Connect to Wi-Fi
    Serial.print("Connecting to ");
    Serial.println(ssid);
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.print(".");
    }
    Serial.println("");
    Serial.println("WiFi connected.");

    // Init and get the time
    configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
    value.begin();
}

void Screens::end()
{
}

void Screens::handle()
{
    value.handle();
    
}

void Screens::displayTemperature()
{
    display.clearDisplay();
    display.setTextSize(2);
    display.drawBitmap(15, 5, temperature_icon, 16, 16, 1);
    display.setCursor(35, 5);
    display.print(value.Temperature());
    display.cp437(true);
    display.setTextSize(1);
    display.print(" ");
    display.write(167);
    display.print("C");
    display.setCursor(0, 34);
    display.setTextSize(1);
    display.print("Humidity: ");
    display.print(value.Humidity());
    display.print(" %");
    display.setCursor(0, 44);
    display.setTextSize(1);
    display.print("Pressure: ");
    display.print(" hpa");
    displayIndicator(displayScreenNum);
    display.display();
}

void Screens::displayHumidity()
{
    display.clearDisplay();
    display.setTextSize(2);
    display.drawBitmap(15, 5, humidity_icon, 16, 16, 1);
    display.setCursor(35, 5);
    display.print(value.Humidity());
    display.print(" %");
    display.setCursor(0, 34);
    display.setTextSize(1);
    display.print("Temperature: ");
    display.print(value.Temperature());
    display.cp437(true);
    display.print(" ");
    display.write(167);
    display.print("C");
    display.setCursor(0, 44);
    display.setTextSize(1);
    display.print("Pressure: ");
    display.print(" hpa");
    displayIndicator(displayScreenNum);
    display.display();
}

void Screens::displayTime()
{
    struct tm timeinfo;
    if (!getLocalTime(&timeinfo))
    {
        Serial.println("Failed to obtain time");
    }
    Serial.println(&timeinfo, "%A, %B %d %Y %H:%M:%S");

    // GET DATE
    // Get full weekday name
    char weekDay[10];
    strftime(weekDay, sizeof(weekDay), "%a", &timeinfo);
    // Get day of month
    char dayMonth[4];
    strftime(dayMonth, sizeof(dayMonth), "%d", &timeinfo);
    // Get abbreviated month name
    char monthName[5];
    strftime(monthName, sizeof(monthName), "%b", &timeinfo);
    // Get year
    char year[6];
    strftime(year, sizeof(year), "%Y", &timeinfo);

    // GET TIME
    // Get hour (12 hour format)
    /*char hour[4];
    strftime(hour, sizeof(hour), "%I", &timeinfo);*/

    // Get hour (24 hour format)
    char hour[4];
    strftime(hour, sizeof(hour), "%H", &timeinfo);
    // Get minute
    char minute[4];
    strftime(minute, sizeof(minute), "%M", &timeinfo);

    // Display Date and Time on OLED display
    display.clearDisplay();
    display.setTextColor(WHITE);
    display.setTextSize(3);
    display.setCursor(19, 5);
    display.print(hour);
    display.print(":");
    display.print(minute);
    display.setTextSize(1);
    display.setCursor(16, 40);
    display.print(weekDay);
    display.print(", ");
    display.print(dayMonth);
    display.print(" ");
    display.print(monthName);
    display.print(" ");
    display.print(year);
    displayIndicator(displayScreenNum);
    display.display();
}

void Screens::displayIndicator(uint8_t displayNumber)
{
    uint8_t xCoordinates[5] = {44, 54, 64};//74,84
    for (uint8_t i = 0; i < 3; i++)
    {
        if (i == displayNumber)
        {
            display.fillCircle(xCoordinates[i], 60, 2, WHITE);
        }
        else
        {
            display.drawCircle(xCoordinates[i], 60, 2, WHITE);
        }
    }
}

