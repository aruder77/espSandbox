#include "TemperatureReader.h"

const char* TemperatureReader::getName() {
    return "TemperatureReader";
}

void TemperatureReader::setup() {
    oneWire = new OneWire(ONE_WIRE_PIN);
    dallasTemperature = new DallasTemperature(oneWire);
    dallasTemperature->begin();
}

void TemperatureReader::everySecond() {
    dallasTemperature->requestTemperatures();
    float temperatureC = dallasTemperature->getTempCByIndex(0);
    DisplayControl::getInstance()->displayOutsideTemperature(temperatureC);
    Serial.print(temperatureC);
    Serial.println("°C");
}