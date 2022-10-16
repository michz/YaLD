#ifndef __UPDATE_SERVER_H
#define __UPDATE_SERVER_H

#define WEBSERVER_DEFAUL_PORT 80
#define MZTX_FIRMWARE_VERSION "1"

#include <WebServer.h>
#include <Update.h>

#include "debug.h"

void initUpdateServer(void);
void loopUpdateServer(void);

#endif // __UPDATE_SERVER_H
