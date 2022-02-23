#ifndef IM920sL_h
#define IM920sL_h

#include <Arduino.h>
#include "IM920sL_Debug.h"

typedef struct {
    uint16_t node;
    int8_t rssi;
    String data;
    String raw;
} IM920sL_data_t;

typedef void (*IM920sL_callback)(IM920sL_data_t &data);

class IM920sL {
public:
    IM920sL(Stream &serial, int busyInd) : _serial(serial), _busyInd(busyInd) {
        pinMode(busyInd, INPUT);
    };
    IM920sL(Stream &serial) : _serial(serial), _busyInd(NULL) {};
    void run();
    String sendCommand(String command);
    bool sendCommandBool(String command);
    void setCallback(IM920sL_callback callback);
private:
    // Stream *_swSerial;
    Stream &_serial;
    int _busyInd;
    IM920sL_callback _callback;
    void _handleEvent(String &response);
    void _sendCommand(String command);
    void _waitReturn();
    void _waitBusy();
    String _getLine();
};

#endif
