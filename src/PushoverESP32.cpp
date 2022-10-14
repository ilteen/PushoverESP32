#include "PushoverESP32.h"

const char *PUSHOVER_ROOT_CA = "-----BEGIN CERTIFICATE-----\n"
                               "MIIDrzCCApegAwIBAgIQCDvgVpBCRrGhdWrJWZHHSjANBgkqhkiG9w0BAQUFADBh\n"
                               "MQswCQYDVQQGEwJVUzEVMBMGA1UEChMMRGlnaUNlcnQgSW5jMRkwFwYDVQQLExB3\n"
                               "d3cuZGlnaWNlcnQuY29tMSAwHgYDVQQDExdEaWdpQ2VydCBHbG9iYWwgUm9vdCBD\n"
                               "QTAeFw0wNjExMTAwMDAwMDBaFw0zMTExMTAwMDAwMDBaMGExCzAJBgNVBAYTAlVT\n"
                               "MRUwEwYDVQQKEwxEaWdpQ2VydCBJbmMxGTAXBgNVBAsTEHd3dy5kaWdpY2VydC5j\n"
                               "b20xIDAeBgNVBAMTF0RpZ2lDZXJ0IEdsb2JhbCBSb290IENBMIIBIjANBgkqhkiG\n"
                               "9w0BAQEFAAOCAQ8AMIIBCgKCAQEA4jvhEXLeqKTTo1eqUKKPC3eQyaKl7hLOllsB\n"
                               "CSDMAZOnTjC3U/dDxGkAV53ijSLdhwZAAIEJzs4bg7/fzTtxRuLWZscFs3YnFo97\n"
                               "nh6Vfe63SKMI2tavegw5BmV/Sl0fvBf4q77uKNd0f3p4mVmFaG5cIzJLv07A6Fpt\n"
                               "43C/dxC//AH2hdmoRBBYMql1GNXRor5H4idq9Joz+EkIYIvUX7Q6hL+hqkpMfT7P\n"
                               "T19sdl6gSzeRntwi5m3OFBqOasv+zbMUZBfHWymeMr/y7vrTC0LUq7dBMtoM1O/4\n"
                               "gdW7jVg/tRvoSSiicNoxBN33shbyTApOB6jtSj1etX+jkMOvJwIDAQABo2MwYTAO\n"
                               "BgNVHQ8BAf8EBAMCAYYwDwYDVR0TAQH/BAUwAwEB/zAdBgNVHQ4EFgQUA95QNVbR\n"
                               "TLtm8KPiGxvDl7I90VUwHwYDVR0jBBgwFoAUA95QNVbRTLtm8KPiGxvDl7I90VUw\n"
                               "DQYJKoZIhvcNAQEFBQADggEBAMucN6pIExIK+t1EnE9SsPTfrgT1eXkIoyQY/Esr\n"
                               "hMAtudXH/vTBH1jLuG2cenTnmCmrEbXjcKChzUyImZOMkXDiqw8cvpOp/2PV5Adg\n"
                               "06O/nVsJ8dWO41P0jmP6P6fbtGbfYmbW0W5BjfIttep3Sp+dWOIrWcBAI+0tKIJF\n"
                               "PnlUkiaY4IBIqDfv8NZ5YBberOgOzW6sRBc4L0na4UU+Krk2U886UAb3LujEV0ls\n"
                               "YSEY1QSteDwsOoBrp+uvFRTp2InBuThs4pFsiv9kuXclVzDAGySj4dzp30d8tbQk\n"
                               "CAUw7C29C79Fv1C5qfPrmAESrciIxpg0X40KPMbp1ZWVbd4=\n"
                               "-----END CERTIFICATE-----\n";

const char *PUSHOVER_API_URL = "https://api.pushover.net/1/messages.json";

Pushover::Pushover(String token, String user) : _token(token), _user(user) {;}

int Pushover::send(PushoverMessage newMessage) {
    int responseCode = -1;
    if (WiFi.status() == WL_CONNECTED) { 

        HTTPClient httpClient;
        httpClient.begin(PUSHOVER_API_URL, PUSHOVER_ROOT_CA);
        httpClient.addHeader("Content-Type", "application/x-www-form-urlencoded");

        String httpRequestData = "token=" + _token + "&user=" + _user + "&message=" + newMessage.message;
        if (!newMessage.title.isEmpty()) httpRequestData += "&title=" + newMessage.title;
        if (!newMessage.url.isEmpty()) httpRequestData += "&url=" + newMessage.url;
        if (!newMessage.url_title.isEmpty()) httpRequestData += "&url_title=" + newMessage.url_title;
        if (!newMessage.device.isEmpty()) httpRequestData += "&device=" + newMessage.device;
        if (newMessage.html) httpRequestData += "&html=1";
        if (newMessage.priority != 0) httpRequestData += "&priority=" + newMessage.priority;
        if (!newMessage.sound.isEmpty()) httpRequestData += "&sound=" + newMessage.sound;
        if (newMessage.timestamp > -1) httpRequestData += "&timestamp=" + newMessage.timestamp;

        responseCode = httpClient.POST(httpRequestData);

        if (responseCode != 200) {
            String response = httpClient.getString();
            Serial.println("Response Code: " + String(responseCode));
            Serial.println("Response: " + response);
        }
        httpClient.end();
    }
    else {
        Serial.println("Pushover message can't be send, because WiFi is not connected.");
    }
    return responseCode;
}

void Pushover::setToken(String token) {
    _token = token;
}

void Pushover::setUser(String user) {
    _user = user;
}