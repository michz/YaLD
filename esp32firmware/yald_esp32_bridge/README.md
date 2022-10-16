# YaLD esp32 MQTT bridge

## Build

Recommendation: Through PlatformIO extension in vscode.

## Deploy

Either "PlatformIO: Upload" in vscode.

Or:

```
curl -v -XPOST -F "upload=@.pio/build/wemos_d1_mini32/firmware.bin" http://192.168.0.119/update
```
