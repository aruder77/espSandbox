#include <PWMReader.h>

void IRAM_ATTR isr()  {
    PWMReader::getInstance()
    int64_t time = esp_timer_get_time();
}

PWMReader::PWMReader() {
}

PWMReader* PWMReader::getInstance() {
    if (!instance) {
        instance = new PWMReader();
    }
    return instance;
}

void PWMReader::setup() {
    pinMode(PWM_PIN, INPUT_PULLUP);
    attachInterrupt(PWM_PIN, isr, FALLING);
}