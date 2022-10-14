# PushoverESP32

ESP32 library for Pushover.

Forked from [brunojoyal/PushoverESP32](https://github.com/brunojoyal/PushoverESP32), because I wanted a lightweight and more easy to use library.

# Usage

Initiate Pushover client:
```cpp
        Pushover pushoverClient(token, user);
```


Messages are encoded within the PushoverMessage struct:

```cpp
    struct PushoverMessage
    {
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
```

To write a message, simply declare a PushoverMessage object and modify the properties you need. 

```cpp

    PushoverMessage myMessage;

    myMessage.title = "Message title";
    myMessage.message = "Message body";
    pushoverClient.send(myMessage);
```


# Attachments

Attachments are not supported, if you need attachments, use the original library: [brunojoyal/PushoverESP32](https://github.com/brunojoyal/PushoverESP32).