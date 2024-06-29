#include <Arduino.h>
#include <alog.h>
#include <CCUI/CCUI.hpp>
#include <ui/ui.h>
#include <canon_ble.h>

// ---------------------------------------------------------------------------

void btHalfPressedPressed(lv_event_t *e)
{
  canonBLE->shutterHalfPressed();
}

void btHalfPressedReleased(lv_event_t *e)
{
  canonBLE->allButtonsReleased();
}

void btFullPressedPressed(lv_event_t *e)
{
  bool movieMode = lv_obj_has_state(ui_BTMovieModeSwitch, LV_STATE_CHECKED);
  ALOG_D( "btFullPressedPressed movieMode=%s", movieMode ? "true" : "false");
  canonBLE->shutterFullPressed(movieMode);
}

void btFullPressedReleased(lv_event_t *e)
{
  canonBLE->allButtonsReleased();
}

void btWidePressed(lv_event_t *e)
{
  ALOG_D("<->");
  canonBLE->zoomWidePressed();
}

void btWideReleased(lv_event_t *e)
{
  ALOG_D("<->");
  canonBLE->allButtonsReleased();
}

void btTelePressed(lv_event_t *e)
{
  ALOG_D(">-<");
  canonBLE->zoomTelePressed();
}

void btTeleReleased(lv_event_t *e)
{
  ALOG_D(">-<");
  canonBLE->allButtonsReleased();
}
