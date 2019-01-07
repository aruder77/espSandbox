#ifndef CONTROLLER_H_
#define CONTROLLER_H_

#include <Arduino.h>
#include <WiFi.h>
#include <DNSServer.h>
#include <WebServer.h>
#include <WiFiManager.h>
#include "HttpFOTA.h"
#include <PubSubClient.h>
#include <Ticker.h>
#include <Preferences.h>
#include <ArduinoLog.h>
#include "NetworkControl.h"
#include "Prefs.h"
#include "LedController.h"
#include "NetworkModule.h"

/* topics */
#define OTA_TOPIC "ota"

typedef enum
{
  Runnning_e = 0x01,
  Fota_e
} SysState;


class Controller : public NetworkModule {
    public:
        Controller();
        ~Controller();

        void setup();
        void loop();
        
        virtual void commandReceived(char *command, char *payload);
        virtual char *getTelemetryData();        

    private:
        char *mqtt_server = new char[16];
        const int baud_rate = 115200;
        const uint8_t interruptPin = A4;
        char *root_ca = \
            "-----BEGIN CERTIFICATE-----\n"\
            "MIIDSjCCAjKgAwIBAgIQRK+wgNajJ7qJMDmGLvhAazANBgkqhkiG9w0BAQUFADA/\n"\
            "MSQwIgYDVQQKExtEaWdpdGFsIFNpZ25hdHVyZSBUcnVzdCBDby4xFzAVBgNVBAMT\n"\
            "DkRTVCBSb290IENBIFgzMB4XDTAwMDkzMDIxMTIxOVoXDTIxMDkzMDE0MDExNVow\n"\
            "PzEkMCIGA1UEChMbRGlnaXRhbCBTaWduYXR1cmUgVHJ1c3QgQ28uMRcwFQYDVQQD\n"\
            "Ew5EU1QgUm9vdCBDQSBYMzCCASIwDQYJKoZIhvcNAQEBBQADggEPADCCAQoCggEB\n"\
            "AN+v6ZdQCINXtMxiZfaQguzH0yxrMMpb7NnDfcdAwRgUi+DoM3ZJKuM/IUmTrE4O\n"\
            "rz5Iy2Xu/NMhD2XSKtkyj4zl93ewEnu1lcCJo6m67XMuegwGMoOifooUMM0RoOEq\n"\
            "OLl5CjH9UL2AZd+3UWODyOKIYepLYYHsUmu5ouJLGiifSKOeDNoJjj4XLh7dIN9b\n"\
            "xiqKqy69cK3FCxolkHRyxXtqqzTWMIn/5WgTe1QLyNau7Fqckh49ZLOMxt+/yUFw\n"\
            "7BZy1SbsOFU5Q9D8/RhcQPGX69Wam40dutolucbY38EVAjqr2m7xPi71XAicPNaD\n"\
            "aeQQmxkqtilX4+U9m5/wAl0CAwEAAaNCMEAwDwYDVR0TAQH/BAUwAwEB/zAOBgNV\n"\
            "HQ8BAf8EBAMCAQYwHQYDVR0OBBYEFMSnsaR7LHH62+FLkHX/xBVghYkQMA0GCSqG\n"\
            "SIb3DQEBBQUAA4IBAQCjGiybFwBcqR7uKGY3Or+Dxz9LwwmglSBd49lZRNI+DT69\n"\
            "ikugdB/OEIKcdBodfpga3csTS7MgROSR6cz8faXbauX+5v3gTt23ADq1cEmv8uXr\n"\
            "AvHRAosZy5Q6XkjEGB5YGV8eAlrwDPGxrancWYaLbumR9YbK+rlmM6pZW87ipxZz\n"\
            "R8srzJmwN0jP41ZL9c8PDHIyh8bwRLtTcm1D9SZImlJnt1ir/md2cXjbDaJWFBM5\n"\
            "JDGFoqgCWjBH4d1QB7wCCZAA62RjYJsWvIjJEubSfZGL+T0yjWW06XyxV3bqxbYo\n"\
            "Ob8VZRzI9neWagqNdwvYkQsEjgfbKbYK7p2CNTUQ\n"\
            "-----END CERTIFICATE-----";

        Ticker ticker;
        WiFiManager wifiManager;

        WiFiClient *espClient;
        PubSubClient *client;

        NetworkControl* networkControl;
        Prefs* prefs;
        LedController* ledController;

        Preferences preferences;

        char url[100];
        char md5_check[50];
        SysState state = Runnning_e;

        static void receivedCallback(char *topic, byte *payload, unsigned int length);
        void mqttconnect();

        void configModeCallback(WiFiManager *myWiFiManager);
};

#endif