#ifndef TEMPERATUREREADER_H_
#define TEMPERATUREREADER_H_

#include <Module.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <DisplayControl.h>


class TemperatureReader : public Module {

    public:
        const char *getName();
        void setup(); 
        void everySecond();

    private:
        const int ONE_WIRE_PIN = 4;

        DallasTemperature *dallasTemperature;
        OneWire *oneWire;
};

#endif