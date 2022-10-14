#ifndef PUSHOVERESP32_H_
#define PUSHOVERESP32_H_

#include <Arduino.h>
#include <WiFiClientSecure.h>
#include <HTTPClient.h>

struct PushoverMessage {
public:
    String message = "";
    String title = "";
    String url = "";
    String url_title = "";
    String sound = "";
    String device = "";
    bool html = false;
    uint8_t priority = 0;
    uint32_t timestamp = -1;
};

class Pushover {
private:
    uint16_t _timeout = 5000;
    String _token;
    String _user;

public:
    Pushover(String, String);
    void setUser(String);
    void setToken(String);
    int send(PushoverMessage message);
};

#endif