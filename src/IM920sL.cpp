#include "IM920sL.h"
#include "IM920sL_Debug.h"

USE_DEBUG


void IM920sL::run() {
    if(_serial.available() > 0){
        DPRINTLN("[Received]");
        String received = _getLine();
        DPRINTLN(received);

        _handleEvent(received);
    }
}

void IM920sL::_sendCommand(String command) {
    DPRINTLN("[Send]");
    DPRINT(command);
    DPRINTLN("<CR><LF>");

    _waitBusy();

    _serial.print(command);
    _serial.print("\r\n");    
}

String IM920sL::sendCommand(String command) {
    _sendCommand(command);

    _waitReturn();
    String received = _getLine();
    return received;
}

bool IM920sL::sendCommandBool(String command) {
    _sendCommand(command);

    _waitReturn();
    String received = _getLine();
    return received.equals("OK");
}

void IM920sL::setCallback(IM920sL_callback callback) {
    _callback = callback;
}

void IM920sL::_handleEvent(String &received) {
    if(received.startsWith("00,")) {
        // Parse Data
        String node = received.substring(3, 7);
        uint16_t node_uint = (uint16_t)strtoul(node.c_str(), NULL, 16);

        String rssi = received.substring(8, 10);
        int rssi_int = (int)strtol(rssi.c_str(), NULL, 16);

        String send_data = received.substring(11);

        IM920sL_data_t data = {
            .node = node_uint,
            .rssi = rssi_int,
            .data = send_data,
            .raw = received,
        };

        _callback(data);
    }
}

void IM920sL::_waitReturn() {
    while(!_serial.available());
}

void IM920sL::_waitBusy() {
    if (_busyInd == NULL) return;
    unsigned long first_time = millis();
    while(digitalRead(_busyInd) == HIGH && millis() - first_time < 2000) {
        delay(10);
    }
}

String IM920sL::_getLine() {
    String received = _serial.readStringUntil('\r');
    _serial.readStringUntil('\n');
    return received;
}
