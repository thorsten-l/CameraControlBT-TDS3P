#pragma once

#include <Arduino.h>
#include <ArduinoNvs.h>
#include <ui/ui.h>

class Settings
{
private:
  void restartController();

public:
  void initialize();
  void handler();
  void saveNvs();
};

extern Settings settings;
extern ArduinoNvs appNvs;
