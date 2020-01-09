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

#include <vector>
#include <array>

#include <Adafruit_ILI9341.h>
#include <Adafruit_GFX.h>
#include <XPT2046_Calibrated.h>

#include "obj/Primitive.h"
#include "obj/Layer.h"

// ------------------------------------------------------------------ defines --

/* nothing */

// ------------------------------------------------------------------- macros --

/* nothing */

// ----------------------------------------------------- forward declarations --

/* nothing */

// ----------------------------------------------------------- exported types --

typedef void (* ScreenTouchCallback)(Screen const &, Touch const &);

class Screen {
protected:
  static const uint8_t _MAX_LAYERS = 10U;

  Adafruit_ILI9341 _tft;
  XPT2046_Calibrated _ts;
  uint16_t _tftCSPin;
  uint16_t _tftDCPin;
  uint16_t _tsCSPin;
  uint16_t _tsIRQPin;
  uint16_t _width;
  uint16_t _height;
  TS_Calibration _calibration;
  Orientation _orientation;
  Color _color;
  Touch _touch;
  bool _refresh;
  std::array<Layer,_MAX_LAYERS> _layer;
  uint8_t _layerIndexTop;
  ScreenTouchCallback _touchBegin;
  ScreenTouchCallback _touchEnd;

  bool initDisplay(void);
  bool initTouchScreen(TS_Calibration const &cal);

  Touch touched(void);

  void updateOverlappingPanels(
      uint8_t const layerIndexTop, Panel * const panel
  );

  void fillFrame(
      Point const &origin,
      Size const &size,
      Radius const radiusCorner,
      int8_t const margin,
      Color const color
  ) const;
  void drawQuarterCircle(
      int16_t const x0, int16_t const y0, int16_t const r,
      uint8_t const corner, uint16_t const color
  ) const;
  void fillQuarterCircle(
      int16_t const x0, int16_t const y0, int16_t const r,
      uint8_t const corner, int16_t const delta, uint16_t const color
  ) const;

public:
  Screen(
      uint16_t const tftCSPin,
      uint16_t const tftDCPin,
      uint16_t const tsCSPin,
      uint16_t const tsIRQPin,
      uint16_t const width,
      uint16_t const height,
      TS_Calibration const calibration,
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
    _calibration(calibration),
    _orientation(orientation),
    _color(color),
    _touch(),
    _refresh(true),
    _layer(),
    _layerIndexTop(0U),
    _touchBegin(nullptr),
    _touchEnd(nullptr)
  {
    for (uint8_t i = 0U; i < _MAX_LAYERS; ++i)
      { _layer[i].setIndex(i); } // index shall -never- change after this.
  }

  Screen(
      uint16_t const tftCSPin,
      uint16_t const tftDCPin,
      uint16_t const tsCSPin,
      uint16_t const tsIRQPin,
      uint16_t const width,
      uint16_t const height,
      Point const &calAScr, Point const &calATch,
      Point const &calBScr, Point const &calBTch,
      Point const &calCScr, Point const &calCTch,
      Orientation const orientation,
      Color const color
  ):
    Screen(
        tftCSPin, tftDCPin, tsCSPin, tsIRQPin,
        width, height, TS_Calibration(
            TS_Point(calAScr.x(), calAScr.y()), // point A (screen)
            TS_Point(calATch.x(), calATch.y()), // point A (touch)
            TS_Point(calBScr.x(), calBScr.y()), // point B (screen)
            TS_Point(calBTch.x(), calBTch.y()), // point B (touch)
            TS_Point(calCScr.x(), calCScr.y()), // point C (screen)
            TS_Point(calCTch.x(), calCTch.y()), // point C (touch)
            width, height
        ), orientation, color
    )
  {}

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
    Screen(
        tftCSPin, tftDCPin, tsCSPin, tsIRQPin,
        width, height, TS_Calibration(), orientation, color
    )
  {}

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

  bool needsRefresh() const { return _refresh; }
  void setNeedsRefresh() { _refresh = true; }

  void paintFrame(
      Point const &origin,
      Size const &size,
      Radius const radiusCorner,
      Color const color
  ) const;
  void paintFrame(
      Point const &origin,
      Size const &size,
      Radius const radiusCorner,
      Color const color,
      Radius const radiusBorder,
      int8_t const marginBorder,
      Color const colorBorder
  ) const;

  void paintText(
      Point const &center,
      GFXfont const *font,
      std::string const text,
      uint8_t const lineCount,
      uint16_t const lineSpacing,
      uint8_t const sizeText,
      Color const colorText
  ) const;

  uint8_t maxLayers() const { return _MAX_LAYERS; }

  Layer *layer(uint8_t const index) const
    { return index < _MAX_LAYERS ? (Layer *)&(_layer[index]) : nullptr; }

  uint8_t layerIndexTop() const { return _layerIndexTop; }
  void setLayerIndexTop(uint8_t const index);

  uint8_t layerIndexAbove(uint8_t const index) const;
  uint8_t layerIndexBelow(uint8_t const index) const;

  void setTouchBegin(ScreenTouchCallback const callback)
    { _touchBegin = callback; }
  void setTouchEnd(ScreenTouchCallback const callback)
    { _touchEnd = callback; }
};

// ------------------------------------------------------- exported variables --

extern uint8_t const LAYER_INDEX_INVALID;

// ------------------------------------------------------- exported functions --

/* nothing */

#endif // __SCREEN_H__
