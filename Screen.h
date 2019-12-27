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

#include <array>

#include <Arduino.h>

#include <Adafruit_ILI9341.h>
#include <XPT2046_Calibrated.h>

#include "Primitive.h"
#include "Layer.h"

// ------------------------------------------------------------------ defines --

/* nothing */

// ------------------------------------------------------------------- macros --

/* nothing */

// ----------------------------------------------------- forward declarations --

/* nothing */

// ----------------------------------------------------------- exported types --

class Screen {
private:
  static const uint8_t _MAX_LAYERS = 10U;

  Adafruit_ILI9341 _tft;
  XPT2046_Calibrated _ts;
  uint16_t _tftCSPin;
  uint16_t _tftDCPin;
  uint16_t _tsCSPin;
  uint16_t _tsIRQPin;
  uint16_t _width;
  uint16_t _height;
  Orientation _orientation;
  Color _color;
  bool _refresh;
  std::array<Layer,_MAX_LAYERS> _layer;
  uint8_t _layerIndexTop;

  bool initDisplay(void);
  bool initTouchScreen(void);
  Touch touched(void);

public:
  Screen(
      uint16_t const tftCSPin,
      uint16_t const tftDCPin,
      uint16_t const tsCSPin,
      uint16_t const tsIRQPin,
      uint16_t const width,
      uint16_t const height,
      Orientation const orientation,
      Color const color
  ):
    _tft(tftCSPin, tftDCPin),
    _ts(tsCSPin, tsIRQPin),
    _tftCSPin(tftCSPin),
    _tftDCPin(tftDCPin),
    _tsCSPin(tsCSPin),
    _tsIRQPin(tsIRQPin),
    _width(width),
    _height(height),
    _orientation(orientation),
    _color(color),
    _refresh(true),
    _layer(),
    _layerIndexTop(0U)
  {
    for (uint8_t i = 0U; i < _MAX_LAYERS; ++i)
      { _layer[i].setIndex(i); } // index shall not -ever- change after this.
  }

  // the following two accessors return non-const references, which are
  // required when calling mutating member methods in certain contexts.
  Adafruit_ILI9341 *tft() const { return (Adafruit_ILI9341 *)&_tft; }
  XPT2046_Calibrated *ts() const { return (XPT2046_Calibrated *)&_ts; }
  uint16_t width(void) const { return _width; }
  uint16_t height(void) const { return _height; }
  Color color(void) const { return _color; }
  Orientation orientation(void) const { return _orientation; }
  bool begin(void);
  void draw(void);
  void refresh() { _refresh = true; }
  void paintFrame(
      Point const &origin,
      Size const &size,
      Color const color
  ) const;
  void paintFrame(
      Point const &origin,
      Size const &size,
      Color const color,
      Color const colorBorder
  ) const;
  uint8_t maxLayers() const { return _MAX_LAYERS; }
  Layer *layer(uint8_t const index) const
    { return index < _MAX_LAYERS ? (Layer *)&(_layer[index]) : nullptr; }
  uint8_t layerIndexTop() const { return _layerIndexTop; }
  void setLayerIndexTop(uint8_t const index);
};

// ------------------------------------------------------- exported variables --

/* nothing */

// ------------------------------------------------------- exported functions --

/* nothing */

#endif // __SCREEN_H__
