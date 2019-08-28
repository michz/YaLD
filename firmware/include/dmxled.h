#ifdef TARGET_STORM
#define DEVICE_ID   (1)
#endif
#ifdef TARGET_DESK
#define DEVICE_ID   (2)
#endif

#define get_millisecond_timer millis

#include "millis/millis/millis.h"

enum {INIT, MODE_DMX, MODE_IR, EADDR, ERECEIVER};
