#ifndef __DEBUG_H
#define __DEBUG_H

//#define ENABLE_DEBUG

#ifdef ENABLE_DEBUG

#define MZTX_DEBUG_INIT()            Serial.begin(115200)
#define MZTX_DEBUG_PRINT(msg)        Serial.print(msg)
#define MZTX_DEBUG_PRINTLN(msg)      Serial.println(msg)
#define MZTX_DEBUG_FORCEFLUSH()      Serial.flush()

#else

#define MZTX_DEBUG_INIT()
#define MZTX_DEBUG_PRINT(msg)
#define MZTX_DEBUG_PRINTLN(msg)
#define MZTX_DEBUG_FORCEFLUSH()

#endif

#endif // __DEBUG_H
