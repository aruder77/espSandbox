#ifndef PWMREADER_H_
#define PWMREADER_H_

#include <Arduino.h>
#include <esp_timer.h>
#include <ArduinoLog.h>
#include <Module.h>

#define PWM_PIN 12
#define SAMPLE_COUNT 400

class PWMReader : public Module {

    public:
	    virtual ~PWMReader();
        static PWMReader* getInstance();  

        const char *getName();                  
        void setup();

        void rising();
        void falling();

        virtual void loop();

    private:
        const int SAMPLE_DISTANCE = 400;

        static PWMReader* instance;
        PWMReader();

        int counter = 0;
        int sampleNumber = 0;
        int64_t lastRising = 0;
        int64_t pwmFrequency = 0;

        int64_t samples[SAMPLE_COUNT + 200] = { 0 };
};


#endif