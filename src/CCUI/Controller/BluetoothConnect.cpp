#include <Arduino.h>
#include <CCUI/CCUI.hpp>
#include <canon_ble.h>
#include <alog.h>
#include <ui/ui.h>
#include <CCUI/Controller/Settings.hpp>

static lv_obj_t *mbox1;
static int lastTab = 0;

// ---------------------------------------------------------------------------

void btScreenLoaded(lv_event_t *e)
{
  ALOG_D("btScreenLoaded");

  if (!canonBLE->isPaired())
  {
    ALOG_D("Camera is not paired");
    ccui.disableButton(ui_BTConnectButton);
  }
  else
  {
    ALOG_D("Camera is paired");
    lv_label_set_text(ui_BTCameraNameLabel,
                      canonBLE->getCameraName().c_str());
    lv_label_set_text(ui_BTCameraAddressLabel,
                      canonBLE->getCameraAddress().c_str());

    if (canonBLE->isConnected())
    {
      lv_label_set_text(ui_BTConnectLabel, "Camera is connected.");
      lv_obj_set_style_bg_color(ui_BTConnectLabel, ccui.colorGreen, 0);
      ccui.disableButton(ui_BTConnectButton);
    }
    else
    {
      lv_label_set_text(ui_BTConnectLabel, "Camera NOT connected!");
      lv_obj_set_style_bg_color(ui_BTConnectLabel, ccui.colorRed, 0);
      ccui.enableButton(ui_BTConnectButton);
    }
  }
  ALOG_D("btScreenLoaded - done");
}

static void msgbox_event_cb(lv_event_t *e)
{
  lv_obj_t *obj = lv_event_get_current_target(e);
  ALOG_D("Button %s clicked", lv_msgbox_get_active_btn_text(obj));
  lv_msgbox_close(obj);
  lv_tabview_set_act(ui_BluetoothTabView, 0, LV_ANIM_OFF);
}

void btBluetoothTabViewValueChanged(lv_event_t *e)
{
  ALOG_D("btBluetoothTabViewValueChanged=%d", e->code);

  int activeTab = lv_tabview_get_tab_act(e->current_target);

  if (activeTab == 0)
  {
    btScreenLoaded(e);
  }

  if (lastTab != activeTab)
  {
    ALOG_D("current_target tab %d active", activeTab);
    lastTab = activeTab;

    if (activeTab != 0 && !canonBLE->isConnected())
    {
      ccui.showHandlerMessageBoxRETURN(
          CCUIMessageBoxType::ERROR, "Camera NOT connected.", msgbox_event_cb);
    }
  }
}

void checkCameraConnect(lv_event_t *e)
{
  ALOG_D("checkCameraConnect");

  if (canonBLE->isConnected() || canonBLE->connect())
  {
    ALOG_I("camera is connected");
  }
  else
  {
    ALOG_I("camera NOT connected");
  }
  ALOG_D("done.");
  btScreenLoaded(nullptr);
}

void checkCameraParing(lv_event_t *e)
{
  ALOG_D("checkCameraParing");

  if (canonBLE->pair())
  {
    ALOG_I("camera is paired");
    settings.saveNvs();
  }
  else
  {
    ALOG_I("camera NOT paired");
  }
  ALOG_D("done.");
  btScreenLoaded(nullptr);
}

void btPairingClicked(lv_event_t *e)
{
  ALOG_D("btPairingClicked");
  static const char *buttons[] = {""};
  ccui.showTaskMessageBox("Pairing", "Please wait...\nTimeout about 40s", false,
                          checkCameraParing, buttons);
}

void btConnectButtonClicked(lv_event_t *e)
{
  ALOG_D("btConnectButtonClicked");

  static const char *buttons[] = {""};

  ccui.showTaskMessageBox("Connecting", "Please wait...", false,
                          checkCameraConnect, buttons);
}
