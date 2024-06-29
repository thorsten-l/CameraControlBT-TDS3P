#include <alog.h>
#include <canon_ble.h>

/////////////////////////////////////////////////////////////////////////////
// BLEClientCallbacks
void CanonBLE::onConnect(BLEClient *bleClient)
{
  ALOG_D("BLEClientCallbacksImpl::onConnect");
}

void CanonBLE::onDisconnect(BLEClient *bleClient)
{
  ALOG_D("BLEClientCallbacksImpl::onDisconnect");
  connected = false;
}

