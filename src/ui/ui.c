// This file was generated by SquareLine Studio
// SquareLine Studio version: SquareLine Studio 1.4.0
// LVGL version: 8.3.11
// Project name: CameraControlBT-TDS3P

#include "ui.h"
#include "ui_helpers.h"

///////////////////// VARIABLES ////////////////////


// SCREEN: ui_StartScreen
void ui_StartScreen_screen_init(void);
lv_obj_t *ui_StartScreen;
lv_obj_t *ui_StartTabView;
lv_obj_t *ui_WirelessTabPage;
void ui_event_StartBluetoothButton( lv_event_t * e);
lv_obj_t *ui_StartBluetoothButton;
void ui_event_Image2( lv_event_t * e);
lv_obj_t *ui_Image2;
lv_obj_t *ui_Label7;
lv_obj_t *ui_SettingsTabPage;
lv_obj_t *ui_SettingsContainer;
lv_obj_t *ui_Label2;
void ui_event_MotorZoomCheckbox( lv_event_t * e);
lv_obj_t *ui_MotorZoomCheckbox;
lv_obj_t *ui_MaintenanceContainer;
lv_obj_t *ui_Label4;
void ui_event_RestartControllerButton( lv_event_t * e);
lv_obj_t *ui_RestartControllerButton;
lv_obj_t *ui_Label3;
void ui_event_ResetAllSettingsButton( lv_event_t * e);
lv_obj_t *ui_ResetAllSettingsButton;
lv_obj_t *ui_Label5;
lv_obj_t *ui_AboutTabPage;
lv_obj_t *ui_AppNameLabel;
lv_obj_t *ui_AppVersionLabel;
lv_obj_t *ui_AppCopyrightLabel;
lv_obj_t *ui_AppLicenseLabel;
lv_obj_t *ui_Apache2LicenseLabel;
lv_obj_t *ui_InfoContainer;
lv_obj_t *ui_PmuLabel;


// SCREEN: ui_BluetoothScreen
void ui_BluetoothScreen_screen_init(void);
void ui_event_BluetoothScreen( lv_event_t * e);
lv_obj_t *ui_BluetoothScreen;
void ui_event_BluetoothTabView( lv_event_t * e);
lv_obj_t *ui_BluetoothTabView;
lv_obj_t *ui_BTConnectTabPage;
void ui_event_BTPairingButton( lv_event_t * e);
lv_obj_t *ui_BTPairingButton;
lv_obj_t *ui_Label9;
void ui_event_BTConnectButton( lv_event_t * e);
lv_obj_t *ui_BTConnectButton;
lv_obj_t *ui_Label10;
lv_obj_t *ui_BTInfoContainer;
lv_obj_t *ui_BTCameraNameLabel;
lv_obj_t *ui_BTCameraAddressLabel;
lv_obj_t *ui_BTConnectLabel;
lv_obj_t *ui_BTRemoteTabPage;
lv_obj_t *ui_Container1;
void ui_event_BTHalfPressButton( lv_event_t * e);
lv_obj_t *ui_BTHalfPressButton;
lv_obj_t *ui_Label12;
void ui_event_BTFullPressButton( lv_event_t * e);
lv_obj_t *ui_BTFullPressButton;
lv_obj_t *ui_Label13;
lv_obj_t *ui_Container2;
lv_obj_t *ui_Label6;
lv_obj_t *ui_BTMovieModeSwitch;
lv_obj_t *ui_MotoZoomContainer;
void ui_event_BTWideButton( lv_event_t * e);
lv_obj_t *ui_BTWideButton;
lv_obj_t *ui_Label19;
void ui_event_BTTeleButton( lv_event_t * e);
lv_obj_t *ui_BTTeleButton;
lv_obj_t *ui_Label20;
lv_obj_t *ui_BTIntervalTabPage;
lv_obj_t *ui_Container8;
lv_obj_t *ui_Container3;
lv_obj_t *ui_PictureDigitRollerContainer;
lv_obj_t *ui_PRoller1000;
lv_obj_t *ui_PRoller100;
lv_obj_t *ui_PRoller10;
lv_obj_t *ui_PRoller1;
lv_obj_t *ui_Label14;
lv_obj_t *ui_Container4;
lv_obj_t *ui_IntervalDigitRollerContainer;
lv_obj_t *ui_IRoller100;
lv_obj_t *ui_IRoller10;
lv_obj_t *ui_IRoller1;
lv_obj_t *ui_IURoller;
lv_obj_t *ui_Label16;
lv_obj_t *ui_Container5;
lv_obj_t *ui_ExposureDigitRollerContainer;
lv_obj_t *ui_XRoller100;
lv_obj_t *ui_XRoller10;
lv_obj_t *ui_XRoller1;
lv_obj_t *ui_XURoller;
lv_obj_t *ui_Label17;
lv_obj_t *ui_IntervalProgressBar;
lv_obj_t *ui_IntervalProgressBarLabel;
lv_obj_t *ui_Container6;
void ui_event_BTIntStartButton( lv_event_t * e);
lv_obj_t *ui_BTIntStartButton;
lv_obj_t *ui_Image11;
void ui_event_BTIntPauseButton( lv_event_t * e);
lv_obj_t *ui_BTIntPauseButton;
lv_obj_t *ui_Image12;
void ui_event_BTIntStopButton( lv_event_t * e);
lv_obj_t *ui_BTIntStopButton;
lv_obj_t *ui_Image13;
lv_obj_t *ui_InfoContainer2;
lv_obj_t *ui_PmuLabel2;
lv_obj_t *ui____initial_actions0;
const lv_img_dsc_t *ui_imgset_bluetooth3_[1] = {&ui_img_bluetooth3_64_png};
const lv_img_dsc_t *ui_imgset_1605758535[1] = {&ui_img_1803052213};
const lv_img_dsc_t *ui_imgset_574278167[1] = {&ui_img_1941201141};
const lv_img_dsc_t *ui_imgset_273442535[1] = {&ui_img_766493279};
const lv_img_dsc_t *ui_imgset_wifi3_[1] = {&ui_img_wifi3_64_png};

///////////////////// TEST LVGL SETTINGS ////////////////////
#if LV_COLOR_DEPTH != 16
    #error "LV_COLOR_DEPTH should be 16bit to match SquareLine Studio's settings"
#endif
#if LV_COLOR_16_SWAP !=1
    #error "LV_COLOR_16_SWAP should be 1 to match SquareLine Studio's settings"
#endif

///////////////////// ANIMATIONS ////////////////////

///////////////////// FUNCTIONS ////////////////////
void ui_event_StartBluetoothButton( lv_event_t * e) {
    lv_event_code_t event_code = lv_event_get_code(e);lv_obj_t * target = lv_event_get_target(e);
if ( event_code == LV_EVENT_PRESSED) {
      _ui_screen_change( &ui_BluetoothScreen, LV_SCR_LOAD_ANIM_NONE, 50, 0, &ui_BluetoothScreen_screen_init);
}
}
void ui_event_Image2( lv_event_t * e) {
    lv_event_code_t event_code = lv_event_get_code(e);lv_obj_t * target = lv_event_get_target(e);
if ( event_code == LV_EVENT_CLICKED) {
      _ui_screen_change( &ui_BluetoothScreen, LV_SCR_LOAD_ANIM_FADE_ON, 500, 0, &ui_BluetoothScreen_screen_init);
}
}
void ui_event_MotorZoomCheckbox( lv_event_t * e) {
    lv_event_code_t event_code = lv_event_get_code(e);lv_obj_t * target = lv_event_get_target(e);
if ( event_code == LV_EVENT_CLICKED) {
      motorZoomCheckboxClicked( e );
}
}
void ui_event_RestartControllerButton( lv_event_t * e) {
    lv_event_code_t event_code = lv_event_get_code(e);lv_obj_t * target = lv_event_get_target(e);
if ( event_code == LV_EVENT_PRESSED) {
      restartControllerButtonClicked( e );
}
}
void ui_event_ResetAllSettingsButton( lv_event_t * e) {
    lv_event_code_t event_code = lv_event_get_code(e);lv_obj_t * target = lv_event_get_target(e);
if ( event_code == LV_EVENT_PRESSED) {
      resetAllSettingsButtonClicked( e );
}
}
void ui_event_BluetoothScreen( lv_event_t * e) {
    lv_event_code_t event_code = lv_event_get_code(e);lv_obj_t * target = lv_event_get_target(e);
if ( event_code == LV_EVENT_SCREEN_LOADED) {
      btScreenLoaded( e );
}
}
void ui_event_BluetoothTabView( lv_event_t * e) {
    lv_event_code_t event_code = lv_event_get_code(e);lv_obj_t * target = lv_event_get_target(e);
if ( event_code == LV_EVENT_VALUE_CHANGED) {
      btBluetoothTabViewValueChanged( e );
}
}
void ui_event_BTPairingButton( lv_event_t * e) {
    lv_event_code_t event_code = lv_event_get_code(e);lv_obj_t * target = lv_event_get_target(e);
if ( event_code == LV_EVENT_PRESSED) {
      btPairingClicked( e );
}
}
void ui_event_BTConnectButton( lv_event_t * e) {
    lv_event_code_t event_code = lv_event_get_code(e);lv_obj_t * target = lv_event_get_target(e);
if ( event_code == LV_EVENT_PRESSED) {
      btConnectButtonClicked( e );
}
}
void ui_event_BTHalfPressButton( lv_event_t * e) {
    lv_event_code_t event_code = lv_event_get_code(e);lv_obj_t * target = lv_event_get_target(e);
if ( event_code == LV_EVENT_PRESSED) {
      btHalfPressedPressed( e );
}
if ( event_code == LV_EVENT_RELEASED) {
      btHalfPressedReleased( e );
}
}
void ui_event_BTFullPressButton( lv_event_t * e) {
    lv_event_code_t event_code = lv_event_get_code(e);lv_obj_t * target = lv_event_get_target(e);
if ( event_code == LV_EVENT_PRESSED) {
      btFullPressedPressed( e );
}
if ( event_code == LV_EVENT_RELEASED) {
      btFullPressedReleased( e );
}
}
void ui_event_BTWideButton( lv_event_t * e) {
    lv_event_code_t event_code = lv_event_get_code(e);lv_obj_t * target = lv_event_get_target(e);
if ( event_code == LV_EVENT_PRESSED) {
      btWidePressed( e );
}
if ( event_code == LV_EVENT_RELEASED) {
      btWideReleased( e );
}
}
void ui_event_BTTeleButton( lv_event_t * e) {
    lv_event_code_t event_code = lv_event_get_code(e);lv_obj_t * target = lv_event_get_target(e);
if ( event_code == LV_EVENT_PRESSED) {
      btTelePressed( e );
}
if ( event_code == LV_EVENT_RELEASED) {
      btTeleReleased( e );
}
}
void ui_event_BTIntStartButton( lv_event_t * e) {
    lv_event_code_t event_code = lv_event_get_code(e);lv_obj_t * target = lv_event_get_target(e);
if ( event_code == LV_EVENT_PRESSED) {
      intervalStartButtonClicked( e );
}
}
void ui_event_BTIntPauseButton( lv_event_t * e) {
    lv_event_code_t event_code = lv_event_get_code(e);lv_obj_t * target = lv_event_get_target(e);
if ( event_code == LV_EVENT_PRESSED) {
      intervalPauseButtonClicked( e );
}
}
void ui_event_BTIntStopButton( lv_event_t * e) {
    lv_event_code_t event_code = lv_event_get_code(e);lv_obj_t * target = lv_event_get_target(e);
if ( event_code == LV_EVENT_PRESSED) {
      intervalStopButtonClicked( e );
}
}

///////////////////// SCREENS ////////////////////

void ui_init( void )
{
lv_disp_t *dispp = lv_disp_get_default();
lv_theme_t *theme = lv_theme_default_init(dispp, lv_palette_main(LV_PALETTE_BLUE), lv_palette_main(LV_PALETTE_RED), true, LV_FONT_DEFAULT);
lv_disp_set_theme(dispp, theme);
ui_StartScreen_screen_init();
ui_BluetoothScreen_screen_init();
ui____initial_actions0 = lv_obj_create(NULL);
lv_disp_load_scr( ui_StartScreen);
}
