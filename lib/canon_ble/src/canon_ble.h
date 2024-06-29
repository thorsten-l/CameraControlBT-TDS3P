#pragma once

#include <Arduino.h>
#include <BLEDevice.h>
#include <memory>

#define BLE_SCAN_DURATION 20

#define SERVICE_UUID "00050000-0000-1000-0000-d8492fffa821"
#define PAIRING_SERVICE "00050002-0000-1000-0000-d8492fffa821"
#define SHUTTER_CONTROL_SERVICE "00050003-0000-1000-0000-d8492fffa821"

#define BUTTON_SHUTTER_FULL_PRESSED 0b10000000
#define BUTTON_SHUTTER_HALF_PRESSED 0b01000000
#define BUTTON_TELE 0b00100000
#define BUTTON_WIDE 0b00010000
#define MODE_IMMEDIATE 0b00001100
#define MODE_DELAY 0b00000100
#define MODE_MOVIE 0b00001000

enum class CanonBLEState
{
  IDLE,                // 0
  DEVICE_SCAN,         // 1
  DEVICE_FOUND,        // 2
  DEVICE_NOT_FOUND,    // 3
  PAIRING_IN_PROGRESS, // 4
  PAIRING_FAILED,      // 5
  PAIRING_SUCCESS,     // 6
  CONNECTION_FAILED,   // 7
  CONNECTION_SUCCESS,  // 8
  SHUTTER_FAILED,      // 9
  ZOOM_WIDE_FAILED,    // 10
  ZOOM_TELE_FAILED,    // 11
};

class CanonBLE : public BLEAdvertisedDeviceCallbacks,
                 BLEClientCallbacks,
                 BLESecurityCallbacks
{
private:
  BLEClient *bleClient = BLEDevice::createClient();
  String deviceName = "";
  BLEAddress cameraAddress = BLEAddress("");
  String cameraName = "";
  BLERemoteCharacteristic *bleRemoteCharacteristicTrigger = nullptr;

  CanonBLEState state = CanonBLEState::IDLE;

  bool connected = false;
  bool paired = false;
  bool initialized = false;

  bool scanForCamera();
  bool connectToPairingService();
  void setup(String _deviceName);

public:
  static void init(String _deviceName);

  bool pair();
  bool connect();
  bool disconnect();

  bool isPaired();
  bool isConnected();

  String getCameraName();
  String getCameraAddress();
  CanonBLEState getState();

  void setCameraName(String _cameraName);
  void setCameraAddress(String _cameraAddress);

  // shutter actions
  bool shutterHalfPressed();
  bool shutterFullPressed(bool movieMode);

  // motor zoom actions (PowerShot Cameras)
  bool zoomWidePressed();
  bool zoomTelePressed();

  // all buttons released
  bool allButtonsReleased();

  // BLEAdvertisedDeviceCallbacks
  void onResult(BLEAdvertisedDevice advertisedDevice);

  // BLEClientCallbacks
  void onConnect(BLEClient *bleClient) override;
  void onDisconnect(BLEClient *bleClient) override;

  // BLESecurityCallbacks
  uint32_t onPassKeyRequest();
  void onPassKeyNotify(uint32_t pass_key);
  bool onConfirmPIN(uint32_t pass_key);
  bool onSecurityRequest();
  void onAuthenticationComplete(esp_ble_auth_cmpl_t auth_cmpl);
};

extern std::shared_ptr<CanonBLE> canonBLE;
