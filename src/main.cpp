#include <Arduino.h>
#include <ArduinoNvs.h>

#include <CCUI/CCUI.hpp>
#include <CCUI/Controller/Intervalometer.hpp>
#include <CCUI/Controller/Settings.hpp>
#include <canon_ble.h>
#include <alog.h>
#include <math.h>
#include <ui/ui.h>

#include "utilities.h"
#include <SensorLTR553.hpp>
#include <Wire.h>
#include <XPowersLib.h>

void setup()
{
#ifdef ALOG_LEVEL
  Serial.begin(115200);

  while (!Serial.availableForWrite())
  {
    delay(100);
  }

  Serial.println("\nCameraControl, Version: " APP_VERSION "\n");
  Serial.flush();
#endif

  ALOG_D_HEAP();
  CanonBLE::init("CameraControl");
  ALOG_D_HEAP();

  // vibrating motor init
  pinMode(VIBRATING_MOTOR, OUTPUT);
  digitalWrite(VIBRATING_MOTOR, LOW);
  settings.initialize();
  ALOG_D_HEAP();
  ccui.initialize();
  ALOG_D_HEAP();
}

void loop()
{
  lv_timer_handler();
  // lv_task_handler();
  intervalometer.handler();
  settings.handler();
  ccui.handler();
  delay(25);
}

void startBluetooth(lv_event_t *e)
{
  ALOG_D("startBluetooth");
  ALOG_D_HEAP();
}
