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
#include "Layer.h"

// ---------------------------------------------------------- private defines --

/* nothing */

// ----------------------------------------------------------- private macros --

/* nothing */

// ------------------------------------------------------------ private types --

/* nothing */

// ------------------------------------------------------- exported variables --

uint16_t const COORD_INVALID     =  0xFFFF;
uint16_t const DIMNS_INVALID     =  0xFFFF;
Pressure const PRESSURE_INVALID  =  0xFF;
Radius   const NO_RADIUS         =  0x00;

Point const POINT_INVALID(COORD_INVALID, COORD_INVALID);
Touch const NO_TOUCH(false);

// -------------------------------------------------------- private variables --

// touchscreen calibration values. DO NOT TOUCH.
static TS_Point const CAL_A_SCR(   13,   11 );
static TS_Point const CAL_B_SCR(  312,  113 );
static TS_Point const CAL_C_SCR(  167,  214 );
static TS_Point const CAL_A_TCH( 3795, 3735 );
static TS_Point const CAL_B_TCH(  482, 2200 );
static TS_Point const CAL_C_TCH( 2084,  583 );

// ---------------------------------------------- private function prototypes --

/* nothing */

// ------------------------------------------------------- exported functions --

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
  if (!_layer.empty()) {

    Touch touch = touched();
    Layer *layer;

    if (_refresh) {

      // if we are refreshing the screen, walk over the layers in forward
      // direction to draw lowest layer first, then subsequent layers on top.
      auto it = _layer.begin();
      while (it != _layer.end()) {
        layer = it;
        layer->draw(*this, touch);
        ++it;
      }
      _refresh = false;
    }
    else {

      // if we are not refreshing the screen, only redraw the top-most layer
      layer = &(_layer[_layerIndexTop]);
      layer->draw(*this, touch);
    }
  }
}

void Screen::paintFrame(
    Point const &origin,
    Size const &size,
    Color const color
) const
{
  tft()->startWrite();
  tft()->writeFillRect(origin.x(), origin.y(), size.width(), size.height(), color);
  tft()->endWrite();
}

void Screen::paintFrame(
    Point const &origin,
    Size const &size,
    Color const color,
    Color const colorBorder
) const
{
  tft()->startWrite();

  tft()->writeFillRect(origin.x(), origin.y(), size.width(), size.height(), color);

  tft()->writeFastHLine(origin.x(),                   origin.y(),  size.width(), colorBorder);
  tft()->writeFastHLine(origin.x(),   origin.y() + size.height(),  size.width(), colorBorder);
  tft()->writeFastVLine(origin.x(),                   origin.y(), size.height(), colorBorder);
  tft()->writeFastVLine(origin.x() + size.width(),    origin.y(), size.height(), colorBorder);

  tft()->endWrite();
}

void Screen::setLayerIndexTop(uint8_t const index)
{
  if (index != _layerIndexTop) {
    if (index < _MAX_LAYERS)
      { _layerIndexTop = index; }
    for (uint8_t i = index + 1; i < _MAX_LAYERS; ++i)
      { _layer[i].clearPanels(*this); }
    _layer[index].setNeedsUpdate(*this);
  }
}

// -------------------------------------------------------- private functions --

bool Screen::initDisplay()
{
  _tft.begin();
  _tft.setRotation((uint8_t)_orientation);
  _tft.fillScreen((uint16_t)_color);
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

Touch Screen::touched()
{
  uint16_t x, y;
  uint8_t z;

  if (_ts.tirqTouched()) {
    if (_ts.touched()) {
      _ts.readData(&x, &y, &z);
      return Touch(true, Point(x, y), (Pressure)z);
    }
  }
  return NO_TOUCH;
}