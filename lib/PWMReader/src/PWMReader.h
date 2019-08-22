#ifndef PWMREADER_H_
#define PWMREADER_H_

#include <Arduino.h>
#include <esp_timer.h>

#define PWM_PIN 5

class PWMReader : public Module {

    public:
	    virtual ~PWMReader();
        static PWMReader* getInstance();    
        void setup();

    private:
        static PWMReader* instance;
        PWMReader();
}


#endif