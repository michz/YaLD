#include "updateServer.h"

WebServer webserver(WEBSERVER_DEFAUL_PORT);

void initUpdateServer() {
    webserver.on("/", []() {
        webserver.send(200, "text/plain", "GET /healthz ; GET /version ; POST /update\r\n");
    });

    webserver.on("/healthz", []() {
        webserver.send(200, "text/plain", "OK");
    });

    webserver.on("/version", []() {
        webserver.send(200, "text/plain", MZTX_FIRMWARE_VERSION);
    });

        webserver.on("/update", HTTP_POST, []() {
        webserver.sendHeader("Connection", "close");
        webserver.send(200, "text/plain", (Update.hasError()) ? "FAIL" : "OK");
        ESP.restart();
    }, []() {
        // this will take longer...

        // @TODO Update-Visualisierung?

        //ESP.wdtDisable();

        HTTPUpload& upload = webserver.upload();
        if (upload.status == UPLOAD_FILE_START) {
            MZTX_DEBUG_PRINT("Update: ");
            MZTX_DEBUG_PRINTLN(upload.filename.c_str());
            uint32_t maxSketchSpace = (ESP.getFreeSketchSpace() - 0x1000) & 0xFFFFF000;
            if (!Update.begin(maxSketchSpace)) { //start with max available size
                Update.printError(Serial);
            }
        } else if (upload.status == UPLOAD_FILE_WRITE) {
            //WATCHDOG_RESET();

            // flashing firmware to ESP
            if (Update.write(upload.buf, upload.currentSize) != upload.currentSize) {
                Update.printError(Serial);
            }
        } else if (upload.status == UPLOAD_FILE_END) {
            if (Update.end(true)) { //true to set the size to the current progress
                MZTX_DEBUG_PRINT("Update Success: ");
                MZTX_DEBUG_PRINTLN(upload.totalSize);
                MZTX_DEBUG_PRINTLN("Rebooting...");
            } else {
                Update.printError(Serial);
            }
        }
    });

    webserver.begin();
}

void loopUpdateServer() {
    webserver.handleClient();
}
