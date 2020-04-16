#include <PWMReader.h>

bool high = false;

void IRAM_ATTR changeIram()  {
    high = !high;
    if (high) {
        PWMReader::getInstance()->rising();
    } else {
        PWMReader::getInstance()->falling();
    }
}

PWMReader *PWMReader::instance = 0;

PWMReader::PWMReader() {
}

PWMReader::~PWMReader() {
}

const char *PWMReader::getName() {
    return "PWMReader";
}

PWMReader* PWMReader::getInstance() {
    if (!instance) {
        instance = new PWMReader();
    }
    return instance;
}

void PWMReader::setup() {
    pinMode(PWM_PIN, INPUT);
    attachInterrupt(PWM_PIN, changeIram, CHANGE);
    //attachInterrupt(PWM_PIN, fallingIram, FALLING);

    Log.notice("setup completed.");
}

void PWMReader::rising() {
    int64_t time = esp_timer_get_time();
    pwmFrequency = time - lastRising;
    lastRising = time;
}

void PWMReader::falling() {
    int64_t time = esp_timer_get_time();
    if (counter % SAMPLE_DISTANCE == 0) {
        samples[sampleNumber++] = time - lastRising;
        counter = 0;
    }
    counter++;

}

void PWMReader::loop() {
    if (sampleNumber > SAMPLE_COUNT) {
        Log.notice("---------\n");
        char logEntry[50];
        sprintf(logEntry, "PWM frequency: %.2f\n", (1000000.0 / pwmFrequency));
        Log.notice(logEntry);
        for (int i = 0; i < SAMPLE_COUNT; i++) {
            char number[30];
            sprintf(number, "%d\n", samples[i]);
            Log.notice("%s", number);
        }
        Log.notice("---------\n");
        sampleNumber = 0;
    }
}