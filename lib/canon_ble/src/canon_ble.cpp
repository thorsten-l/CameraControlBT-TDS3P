#include <alog.h>
#include "canon_ble.h"

std::shared_ptr<CanonBLE> canonBLE = nullptr;

/////////////////////////////////////////////////////////////////////////////

void CanonBLE::setup(String _deviceName)
{
  ALOG_D("CanonBLE::setup");
  ALOG_D_HEAP();
  if (!initialized)
  {
    initialized = true;
    deviceName = _deviceName;
    BLEDevice::init(deviceName.c_str()); // 87184 bytes heap
    ALOG_D_HEAP();
    BLEDevice::setEncryptionLevel(ESP_BLE_SEC_ENCRYPT_NO_MITM);
    BLEDevice::setSecurityCallbacks(this);
    bleClient->setClientCallbacks(this);
  }
  paired = false;
  connected = false;
  ALOG_D_HEAP();
}

bool CanonBLE::scanForCamera()
{
  bool success = false;
  ALOG_D("CanonBLE::scanForCamera");
  ALOG_D_HEAP();

  BLEScan *pBLEScan = BLEDevice::getScan();
  ALOG_D_HEAP();

  pBLEScan->setAdvertisedDeviceCallbacks(this);

  ALOG_D_HEAP();
  pBLEScan->setActiveScan(true);
  state = CanonBLEState::DEVICE_SCAN;
  pBLEScan->start(BLE_SCAN_DURATION); // blocking

  if (state == CanonBLEState::DEVICE_SCAN)
  {
    ALOG_D("BLE scan timeout - device not found");
    state = CanonBLEState::DEVICE_NOT_FOUND;
  }

  if (state == CanonBLEState::DEVICE_FOUND)
  {
    ALOG_D("Device found");
    ALOG_D("camera name = %s", cameraName.c_str());
    ALOG_D("camera mac address = %s", cameraAddress.toString().c_str());
    success = true;
  }

  ALOG_D_HEAP();
  return success;
}

bool CanonBLE::pair()
{
  bool success = false;
  ALOG_D("CanonBLE::pair");
  ALOG_D_HEAP();
  BLEDevice::setEncryptionLevel(ESP_BLE_SEC_ENCRYPT_MITM);
  paired = false;
  connected = false;
  if (scanForCamera())
  {
    success = connectToPairingService();
  }
  return success;
}

bool CanonBLE::connectToPairingService()
{
  bool success = false;
  state = CanonBLEState::PAIRING_IN_PROGRESS;
  // pairing
  if (bleClient->connect(cameraAddress))
  {
    ALOG_D("get remote service");
    BLERemoteService *bleRemoteService = bleClient->getService(SERVICE_UUID);
    if (bleRemoteService != nullptr)
    {
      BLERemoteCharacteristic *bleRemoteCharacteristicPairing =
          bleRemoteService->getCharacteristic(PAIRING_SERVICE);
      if ((bleRemoteCharacteristicPairing != nullptr))
      {
        String _deviceName = " " + deviceName + " ";
        byte buffer[_deviceName.length()];
        _deviceName.getBytes(buffer, _deviceName.length());
        buffer[0] = {0x03};
        bleRemoteCharacteristicPairing->writeValue(buffer, sizeof(buffer),
                                                   false);
        ALOG_D("Camera paring success : %s", cameraName);
        delay(200);
        disconnect();
        BLEDevice::setEncryptionLevel(ESP_BLE_SEC_ENCRYPT_NO_MITM);
        delay(200);
        connect();
        state = CanonBLEState::PAIRING_SUCCESS;
        success = true;
      }
      else
      {
        state = CanonBLEState::PAIRING_FAILED;
        ALOG_D("Couldn't acquire the pairing or shutter service");
      }
    }
    else
    {
      state = CanonBLEState::PAIRING_FAILED;
      ALOG_D("Couldn't acquire the remote main service");
    }
  }
  else
  {
    state = CanonBLEState::PAIRING_FAILED;
    ALOG_D("Couldn't connect the BLEClient to the device");
  }

  return success;
}

bool CanonBLE::connect()
{
  ALOG_D("CanonBLE::connect");
  ALOG_D_HEAP();

  ALOG_I("connecting camera ...");
  if (bleClient->connect(cameraAddress))
  {
    ALOG_I("getting service ...");
    BLERemoteService *bleRemoteService = bleClient->getService(SERVICE_UUID);
    if (bleRemoteService != nullptr)
    {
      ALOG_I("service ok");

      bleRemoteCharacteristicTrigger =
          bleRemoteService->getCharacteristic(SHUTTER_CONTROL_SERVICE);

      if (bleRemoteCharacteristicTrigger != nullptr)
      {
        ALOG_I("Camera connection Success");
        state = CanonBLEState::CONNECTION_SUCCESS;
        connected = true;
        return true;
      }
      else
      {
        ALOG_E("Get trigger service failed");
      }
    }
    else
    {
      ALOG_E("Couldn't acquire the remote main service");
    }
    disconnect();
  }

  ALOG_E("Camera connection failed");
  state = CanonBLEState::CONNECTION_FAILED;
  connected = false;
  ALOG_D_HEAP();
  return false;
}

bool CanonBLE::disconnect()
{
  ALOG_D("CanonBLE::disconnect");
  ALOG_D_HEAP();
  bleClient->disconnect();
  connected = false;
  state = CanonBLEState::IDLE;
  return true;
}

bool CanonBLE::isPaired()
{
  return paired;
}

bool CanonBLE::isConnected()
{
  return connected;
}

String CanonBLE::getCameraName()
{
  return cameraName;
}

String CanonBLE::getCameraAddress()
{
  return String(cameraAddress.toString().c_str());
}

void CanonBLE::setCameraName(String _cameraName)
{
  cameraName = _cameraName;
}

void CanonBLE::setCameraAddress(String _cameraAddress)
{
  cameraAddress = BLEAddress(_cameraAddress.c_str());
  paired = true;
}

CanonBLEState CanonBLE::getState()
{
  return state;
}

bool CanonBLE::shutterHalfPressed()
{
  ALOG_D("shutterHalfPressed");
  ALOG_D_HEAP();
  if (paired && (connected || connect()))
  {
    bleRemoteCharacteristicTrigger->writeValue(
        (uint8_t)(MODE_IMMEDIATE | BUTTON_SHUTTER_HALF_PRESSED), false);
    state = CanonBLEState::IDLE;
    return true;
  }
  state = CanonBLEState::SHUTTER_FAILED;
  return false;
}

bool CanonBLE::shutterFullPressed(bool movieMode)
{
  ALOG_D("shutterFullPressed, movie mode = %s", movieMode ? "true" : "false");

  if (paired && (connected || connect()))
  {
    uint8_t value =
        movieMode ? (uint8_t)(MODE_MOVIE | BUTTON_SHUTTER_FULL_PRESSED)
                  : (uint8_t)(MODE_IMMEDIATE | BUTTON_SHUTTER_FULL_PRESSED);

    bleRemoteCharacteristicTrigger->writeValue(value, true);
    state = CanonBLEState::IDLE;
    return true;
  }
  state = CanonBLEState::SHUTTER_FAILED;
  return false;
}

bool CanonBLE::allButtonsReleased()
{
  ALOG_D("shutterReleased");
  ALOG_D_HEAP();
  if (paired && (connected || connect()))
  {
    ALOG_D("writeValue");
    bleRemoteCharacteristicTrigger->writeValue(MODE_IMMEDIATE);
    state = CanonBLEState::IDLE;
    return true;
  }
  state = CanonBLEState::SHUTTER_FAILED;
  return false;
}

bool CanonBLE::zoomWidePressed()
{
  ALOG_D("zoomWidePressed");
  ALOG_D_HEAP();
  if (paired && (connected || connect()))
  {
    ALOG_D("writeValue");
    bleRemoteCharacteristicTrigger->writeValue((MODE_IMMEDIATE | BUTTON_WIDE));
    state = CanonBLEState::IDLE;
    return true;
  }
  state = CanonBLEState::ZOOM_WIDE_FAILED;
  return false;
}

bool CanonBLE::zoomTelePressed()
{
  ALOG_D("zoomWidePressed");
  ALOG_D_HEAP();
  if (paired && (connected || connect()))
  {
    ALOG_D("writeValue");
    bleRemoteCharacteristicTrigger->writeValue((MODE_IMMEDIATE | BUTTON_TELE));
    state = CanonBLEState::IDLE;
    ALOG_D("t state=%d", state);
    return true;
  }
  state = CanonBLEState::ZOOM_TELE_FAILED;
  ALOG_D("f state=%d", state);
  return false;
}

// create CanonBLE instance only if you really need it,
// it accuires a huge ammount of heap
void CanonBLE::init(String _deviceName)
{
  ALOG_D("CanonBLE::init");
  ALOG_D_HEAP();

  if (canonBLE == nullptr)
  {
    canonBLE = std::make_shared<CanonBLE>();
    canonBLE->setup(_deviceName);
  }
  ALOG_D_HEAP();
}
