#include <alog.h>
#include "canon_ble.h"

/////////////////////////////////////////////////////////////////////////////
// BLESecurityCallbacks

uint32_t CanonBLE::onPassKeyRequest()
{
  ALOG_D("onPassKeyRequest");
  return 123456;
}

void CanonBLE::onPassKeyNotify(uint32_t pass_key)
{
  ALOG_D("onPassKeyNotify");
  ALOG_D("The passkey Notify number:%d", pass_key);
}

bool CanonBLE::onConfirmPIN(uint32_t pass_key)
{
  ALOG_D("onConfirmPIN");
  ALOG_D("The passkey YES/NO number:%d", pass_key);
  vTaskDelay(5000);
  return true;
}

bool CanonBLE::onSecurityRequest()
{
  ALOG_D("onSecurityRequest");
  return true;
}

void CanonBLE::onAuthenticationComplete(esp_ble_auth_cmpl_t auth_cmpl)
{
  ALOG_D("onAuthenticationComplete");
  ALOG_D("pair status = %s", auth_cmpl.success ? "success" : "fail");
  paired = auth_cmpl.success;
  ALOG_D_HEAP();
}
