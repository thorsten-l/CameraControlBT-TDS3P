#include <alog.h>
#include "canon_ble.h"

/////////////////////////////////////////////////////////////////////////////
// BLEAdvertisedDeviceCallbacks

void CanonBLE::onResult(BLEAdvertisedDevice advertisedDevice)
{
  if (advertisedDevice.haveServiceUUID())
  {
    if (BLEUUID(SERVICE_UUID).equals(advertisedDevice.getServiceUUID()))
    {
      ALOG_D("Advertised device name = %s", advertisedDevice.getName().c_str());
      cameraAddress = advertisedDevice.getAddress();
      cameraName = String(advertisedDevice.getName().c_str());
      state = CanonBLEState::DEVICE_FOUND;
      advertisedDevice.getScan()->stop();
    }
  }
}
