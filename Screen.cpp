/*******************************************************************************
 *
 *  name: Screen.cpp
 *  date: Dec 24, 2019
 *  auth: andrew
 *  desc:
 *
 ******************************************************************************/

// ----------------------------------------------------------------- includes --

#include "Screen.h"

// ---------------------------------------------------------- private defines --

/* nothing */

// ----------------------------------------------------------- private macros --

/* nothing */

// ------------------------------------------------------------ private types --

/* nothing */

// ------------------------------------------------------- exported variables --

/* nothing */

// -------------------------------------------------------- private variables --

static TS_Point const CAL_A_SCR(   13,   11 );
static TS_Point const CAL_B_SCR(  312,  113 );
static TS_Point const CAL_C_SCR(  167,  214 );
static TS_Point const CAL_A_TCH( 3795, 3735 );
static TS_Point const CAL_B_TCH(  482, 2200 );
static TS_Point const CAL_C_TCH( 2084,  583 );

// ---------------------------------------------- private function prototypes --

/* nothing */

// ------------------------------------------------------- exported functions --

Screen::Screen(
    uint16_t const tftCSPin,
    uint16_t const tftDCPin,
    uint16_t const tsCSPin,
    uint16_t const tsIRQPin,
    uint16_t const width,
    uint16_t const height,
    ScreenOrientation const orientation
):
  _tft(Adafruit_ILI9341(tftCSPin, tftDCPin)),
  _ts(XPT2046_Calibrated(tsCSPin, tsIRQPin)),
  _tftCSPin(tftCSPin),
  _tftDCPin(tftDCPin),
  _tsCSPin(tsCSPin),
  _tsIRQPin(tsIRQPin),
  _width(width),
  _height(height),
  _orientation(orientation),
  _refresh(true)
{
  /* nothing */
}

uint16_t Screen::width() const
{
  return _width;
}

uint16_t Screen::height() const
{
  return _height;
}

ScreenOrientation Screen::orientation() const
{
  return _orientation;
}

bool Screen::begin()
{
  if (!initDisplay())
    { return false; }

  if (!initTouchScreen())
    { return false; }

  return true;
}

void Screen::draw()
{
  if (_refresh) {

  }
  else {

  }
  _refresh = false;
}

void Screen::refresh()
{
  _refresh = true;
}

// -------------------------------------------------------- private functions --

bool Screen::initDisplay()
{
  _tft.begin();
  _tft.setRotation((uint8_t)_orientation);
  return true;
}

bool Screen::initTouchScreen()
{
  _ts.begin();
  _ts.setRotation((uint8_t)_orientation);
  _ts.calibrate(
      TS_Calibration(
          CAL_A_SCR, CAL_A_TCH,
          CAL_B_SCR, CAL_B_TCH,
          CAL_C_SCR, CAL_C_TCH,
          _width, _height
      )
  );
  return true;
}
