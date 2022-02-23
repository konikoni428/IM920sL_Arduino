#ifndef IM920sL_Debug_h_
#define IM920sL_Debug_h_

// #define IM920sL_DEBUG // Switch debug output on and off by commentout 

#ifdef IM920sL_DEBUG
// #include <SoftwareSerial.h>
// #define USE_DEBUG       extern SoftwareSerial _swSerial;
#define USE_DEBUG       extern Serial_ Serial;
#define DPRINT(...)     Serial.print(__VA_ARGS__)
#define DPRINTLN(...)   Serial.println(__VA_ARGS__)
#else
#define USE_DEBUG 
#define DPRINT(...)
#define DPRINTLN(...)
#endif

#endif