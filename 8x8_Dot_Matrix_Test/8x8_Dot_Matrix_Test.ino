#include <MD_Parola.h>
#include <MD_MAX72xx.h>
#include <SPI.h>

#define HARDWARE_TYPE MD_MAX72XX::GENERIC_HW

#define MAX_DEVICES 1

#define DATA_PIN 11
#define CLK_PIN 13
#define CS_PIN 7

MD_Parola display = MD_Parola(HARDWARE_TYPE, DATA_PIN, CLK_PIN, CS_PIN, MAX_DEVICES);

void setup()
{
  display.begin();
  display.setIntensity(5);
  display.displayClear();

  display.displayText(
    "HELLO WORLD",
    PA_CENTER,
    75,       // scroll speed
    0,
    PA_SCROLL_LEFT,
    PA_SCROLL_LEFT
  );
}

void loop()
{
  if (display.displayAnimate())
  {
    display.displayReset();
  }
}