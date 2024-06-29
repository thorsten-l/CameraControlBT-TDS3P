#include <Arduino.h>

#include <CCUI/CCUI.hpp>
#include <CCUI/Controller/Settings.hpp>
#include <alog.h>
#include <ui/ui.h>
#include <canon_ble.h>
#include <display_init.h>

#include "utilities.h"
#include <SensorLTR553.hpp>
#include <Wire.h>
#include <XPowersLib.h>

#define APPNVS_MOTOR_ZOOM "motorzoom"
#define APPNVS_CAMERA_NAME "camname"
#define APPNVS_CAMERA_ADDRESS "camaddr"

Settings settings;
ArduinoNvs appNvs;
static bool hasSensor = false, hasPMU = false;
static SensorLTR553 als;
static PowersSY6970 PMU;

static time_t restartControllerTimestamp;
static time_t eraseAllSettingsTimestamp;
static lv_point_t touch_points_cal[6];

bool initSensor()
{

  if (!als.begin(Wire, LTR553_SLAVE_ADDRESS, BOARD_I2C_SDA, BOARD_I2C_SCL))
  {
    ALOG_D("Failed to find LTR553 - check your wiring!");
    return false;
  }

  ALOG_D("Init LTR553 Sensor success!");
  als.setLightSensorThreshold(10, 200);
  als.setLightSensorPersists(1);
  als.setProximityPersists(1);
  als.setIRQLevel(SensorLTR553::ALS_IRQ_ACTIVE_LOW);
  als.enableIRQ(SensorLTR553::ALS_IRQ_BOTH);
  als.setLightSensorGain(SensorLTR553::ALS_GAIN_1X);
  als.setPsLedPulsePeriod(SensorLTR553::PS_LED_PLUSE_100KHZ);
  als.setPsLedDutyCycle(SensorLTR553::PS_LED_DUTY_100);
  als.setPsLedCurrnet(SensorLTR553::PS_LED_CUR_100MA);
  als.setProximityRate(SensorLTR553::PS_MEAS_RATE_50MS);
  als.setPsLedPulses(1);
  als.enableLightSensor();
  als.enableProximity();
  als.enablePsIndicator();
  return true;
}

void updatePMU(lv_timer_t *t)
{
  if (!hasPMU) return;

  uint16_t batteryVoltage = PMU.getBattVoltage();
  while( batteryVoltage < 2200 )
  {
    delay(50);
    batteryVoltage = PMU.getBattVoltage();
  }

  ALOG_D( "PMU");
  ALOG_D( "  - is charging = %s", PMU.isCharging() ? "true" : "false" );
  ALOG_D( "  - vbus voltage = %.2fV", PMU.getVbusVoltage() / 1000.0 );
  ALOG_D( "  - battery voltage in = %.2fV", PMU.getBattVoltage() / 1000.0 );
  ALOG_D( "  - system voltage in = %.2fV", PMU.getSystemVoltage() / 1000.0 );
  ALOG_D_HEAP();

  char buffer[200];
  sprintf( buffer, "c=%s v=%.1fV b=%.1fV s=%.1fV",
    PMU.isVbusIn() ? "t" : "f",
    PMU.getVbusVoltage() / 1000.0,
    batteryVoltage / 1000.0,
    PMU.getSystemVoltage() / 1000.0
  );

  lv_label_set_text(ui_PmuLabel, buffer);
  lv_label_set_text(ui_PmuLabel2, buffer);
}


void return_home_cd(void *)
{
  lv_scr_load(ui_StartScreen);
}

void restartControllerButtonClicked(lv_event_t *e)
{
  ALOG_D("restartControllerButtonClicked");
  ccui.showHandlerMessageBox(CCUIMessageBoxType::INFO, "Restarting Controller",
                             false);
  restartControllerTimestamp = millis();
}

static void resetAllSettingsMessageBoxEventCallback(lv_event_t *e)
{
  lv_obj_t *obj = lv_event_get_current_target(e);
  const char *result = lv_msgbox_get_active_btn_text(obj);
  ALOG_D("Button %s clicked", result);
  lv_msgbox_close(obj);

  if (strcmp("YES", result) == 0)
  {
    ccui.showHandlerMessageBox(CCUIMessageBoxType::INFO,
                               "Erasing all settings.", false);
    eraseAllSettingsTimestamp = millis();
  }
}

void resetAllSettingsButtonClicked(lv_event_t *e)
{
  ALOG_D("resetAllSettingsButtonClicked");

  ccui.showHandlerMessageBoxNOYES(CCUIMessageBoxType::WARNING,
                                  "Erase all settings?", true,
                                  resetAllSettingsMessageBoxEventCallback);
}

void motorZoomCheckboxClicked(lv_event_t *e)
{
  ALOG_D("state=%u", lv_obj_get_state(ui_MotorZoomCheckbox));

  if ((lv_obj_get_state(ui_MotorZoomCheckbox) & LV_STATE_CHECKED) ==
      LV_STATE_CHECKED)
  {
    lv_obj_clear_flag(ui_MotoZoomContainer, LV_OBJ_FLAG_HIDDEN);
    appNvs.setInt(APPNVS_MOTOR_ZOOM, 1);
  }
  else
  {
    lv_obj_add_flag(ui_MotoZoomContainer, LV_OBJ_FLAG_HIDDEN);
    appNvs.setInt(APPNVS_MOTOR_ZOOM, 0);
  }
}

// class -----------------------------------------------------------

void Settings::restartController()
{
  ALOG_D("Restarting Controller");
  ESP.restart();
  delay(10000);
}

void Settings::initialize()
{
  ALOG_D_HEAP();
  NVS.begin();

  if (!appNvs.begin("appNvs"))
  {
    ALOG_D("NVS for appNvs not initialized.");
  }

  restartControllerTimestamp = 0l;
  eraseAllSettingsTimestamp = 0l;

  ALOG_D("CPU: %s rev%d, CPU Freq: %d Mhz, %d core(s)", ESP.getChipModel(),
         ESP.getChipRevision(), getCpuFrequencyMhz(), ESP.getChipCores());
  ALOG_D("Free heap: %d bytes", ESP.getFreeHeap());
  ALOG_D("Free PSRAM: %d bytes", ESP.getPsramSize());
  ALOG_D("SDK version: %s", ESP.getSdkVersion());
  ALOG_D("LV version: %d.%d.%d", lv_version_major(), lv_version_minor(),
         lv_version_patch());

  ALOG_D_HEAP();

  lv_helper();

  ALOG_D_HEAP();
 
  lv_touch_homekey_set_cb(return_home_cd);

  ui_init();

  lv_label_set_text(ui_AppVersionLabel, APP_VERSION);
  ALOG_D_HEAP();

  if (appNvs.getInt(APPNVS_MOTOR_ZOOM) == 1)
  {
    lv_obj_clear_flag(ui_MotoZoomContainer, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_state(ui_MotorZoomCheckbox, LV_STATE_CHECKED);
  }
  else
  {
    lv_obj_add_flag(ui_MotoZoomContainer, LV_OBJ_FLAG_HIDDEN);
    lv_obj_clear_state(ui_MotorZoomCheckbox, LV_STATE_CHECKED);
  }

  String value = appNvs.getString(APPNVS_CAMERA_NAME);
  if ( value != nullptr && value.length() > 0 )
  {
    ALOG_I("paired camera name = %s", value.c_str());
    canonBLE->setCameraName(value);
  }
  value = appNvs.getString(APPNVS_CAMERA_ADDRESS);
  if ( value != nullptr && value.length() > 0 )
  {
    ALOG_I("paired camera address = %s", value.c_str());
    canonBLE->setCameraAddress(value);
  }

  hasPMU = PMU.init(Wire, BOARD_I2C_SDA, BOARD_I2C_SCL, SY6970_SLAVE_ADDRESS);
  if (!hasPMU)
  {
    ALOG_D("PMU is not online...");
  }
  else
  {
    ALOG_D("PMU is online...");
    PMU.disableOTG();
    PMU.enableADCMeasure();
    PMU.enableCharge();
    updatePMU(nullptr);
  }

  hasSensor = initSensor();

  lv_timer_create(updatePMU, 10000, NULL);
}

void Settings::handler()
{
  if (restartControllerTimestamp > 0l &&
      (millis() - restartControllerTimestamp) > 1000)
  {
    restartController();
  }

  if (eraseAllSettingsTimestamp > 0l &&
      (millis() - eraseAllSettingsTimestamp) > 1000)
  {
    ALOG_D("Ereasing all NVS data.");
    ArduinoNvs nvs;
    nvs.begin();
    nvs.eraseAll();
    nvs.close();
    appNvs.eraseAll();
    delay(1000);
    restartController();
  }
}

void Settings::saveNvs()
{
  ALOG_D("saveNvs");
  appNvs.setString(APPNVS_CAMERA_NAME, canonBLE->getCameraName());
  appNvs.setString(APPNVS_CAMERA_ADDRESS, canonBLE->getCameraAddress());
}
