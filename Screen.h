/*******************************************************************************
 *
 *  name: Screen.h
 *  date: Dec 13, 2019
 *  auth: andrew
 *  desc:
 *
 ******************************************************************************/

#ifndef __SCREEN_H__
#define __SCREEN_H__

// ----------------------------------------------------------------- includes --

#include <Adafruit_ILI9341.h>
#include <XPT2046_Calibrated.h>

// ------------------------------------------------------------------ defines --

/* nothing */

// ------------------------------------------------------------------- macros --

/* nothing */

// ----------------------------------------------------------- exported types --

typedef enum
{
  // orientation is based on position of board pins when looking at the screen
  soNONE                     = -1,
  soBottom, soPortrait      = soBottom, // = 0
  soRight,  soLandscape     = soRight,  // = 1
  soTop,    soPortraitFlip  = soTop,    // = 2
  soLeft,   soLandscapeFlip = soLeft,   // = 3
  soCOUNT                               // = 4
}
ScreenOrientation;

class Screen {
private:
  Adafruit_ILI9341 _tft;
  XPT2046_Calibrated _ts;
  uint16_t _tftCSPin;
  uint16_t _tftDCPin;
  uint16_t _tsCSPin;
  uint16_t _tsIRQPin;
  uint16_t _width;
  uint16_t _height;
  ScreenOrientation _orientation;
  bool _refresh;
  bool initDisplay();
  bool initTouchScreen();

public:
  Screen(
    uint16_t const tftCSPin,
    uint16_t const tftDCPin,
    uint16_t const tsCSPin,
    uint16_t const tsIRQPin,
    uint16_t const width,
    uint16_t const height,
    ScreenOrientation const orientation
  );
  uint16_t width() const;
  uint16_t height() const;
  ScreenOrientation orientation() const;
  bool begin();
  void draw();
  void refresh();
};

// ------------------------------------------------------- exported variables --

/* nothing */

// ------------------------------------------------------- exported functions --

/* nothing */

#endif // __SCREEN_H__
