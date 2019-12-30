/*******************************************************************************
 *
 *  name: LayoutManager.h
 *  date: Dec 13, 2019
 *  auth: andrew
 *  desc:
 *
 ******************************************************************************/

#ifndef __LAYOUTMANAGER_H__
#define __LAYOUTMANAGER_H__

// ----------------------------------------------------------------- includes --

#include <string>

#include <Arduino.h>

#include "Primitive.h"
#include "Screen.h"

// ------------------------------------------------------------------ defines --

/* nothing */

// ------------------------------------------------------------------- macros --

/* nothing */

// ----------------------------------------------------- forward declarations --

class Panel;

// ----------------------------------------------------------- exported types --

class LayoutManager {
protected:
  Screen _screen;

  bool initScreen() { return _screen.begin(); }

public:
  LayoutManager(
      uint16_t const tftCSPin, uint16_t const tftDCPin,
      uint16_t const tsCSPin, uint16_t const tsIRQPin,
      uint16_t const width, uint16_t const height,
      Orientation const orientation,
      Color const color
  ):
    _screen(
        tftCSPin, tftDCPin, tsCSPin, tsIRQPin,
        width, height, orientation, color)
  {}

  bool begin() { return initScreen(); }
  void draw() { _screen.draw(); }

  Panel *addPanel(
      uint8_t const layerIndex,
      uint16_t const x, uint16_t const y,
      uint16_t const width, uint16_t const height,
      Radius const radiusCorner,
      Color const color
  );
  Panel *addPanel(
      uint8_t const layerIndex,
      uint16_t const x, uint16_t const y,
      uint16_t const width, uint16_t const height,
      Radius const radiusCorner,
      Color const color, Color const colorTouched
  );
  Panel *addPanel(
      uint8_t const layerIndex,
      uint16_t const x, uint16_t const y,
      uint16_t const width, uint16_t const height,
      Radius const radiusCorner,
      Color const color,
      Radius const radiusBorder, int8_t const marginBorder,
      Color const colorBorder
  );
  Panel *addPanel(
      uint8_t const layerIndex,
      uint16_t const x, uint16_t const y,
      uint16_t const width, uint16_t const height,
      Radius const radiusCorner,
      Color const color, Color const colorTouched,
      Radius const radiusBorder, int8_t const marginBorder,
      Color const colorBorder, Color const colorBorderTouched
  );

  Field *addField(
      Panel * const panel,
      std::string const text,
      uint8_t const sizeText,
      Color const colorText,
      Radius const radiusCorner,
      Color const color
  );
  Field *addField(
      Panel * const panel,
      std::string const text,
      uint8_t const sizeText,
      Color const colorText, Color const colorTextTouched,
      Radius const radiusCorner,
      Color const color, Color const colorTouched
  );
  Field *addField(
      Panel * const panel,
      std::string const text,
      uint8_t const sizeText,
      Color const colorText,
      Radius const radiusCorner,
      Color const color,
      Radius const radiusBorder, int8_t const marginBorder,
      Color const colorBorder
  );
  Field *addField(
      Panel * const panel,
      std::string const text,
      uint8_t const sizeText,
      Color const colorText, Color const colorTextTouched,
      Radius const radiusCorner,
      Color const color, Color const colorTouched,
      Radius const radiusBorder, int8_t const marginBorder,
      Color const colorBorder, Color const colorBorderTouched
  );

  uint8_t layerIndexTop() const
    { return _screen.layerIndexTop(); }
  uint8_t layerIndexNext() const
    { return _screen.layerIndexAbove(_screen.layerIndexTop()); }
  uint8_t layerIndexPrev() const
    { return _screen.layerIndexBelow(_screen.layerIndexTop()); }
  void layerRemoveTop();

  void setTouchBegin(ScreenTouchCallback callback)
    { _screen.setTouchBegin(callback); }
  void setTouchEnd(ScreenTouchCallback callback)
    { _screen.setTouchEnd(callback); }

};

// ------------------------------------------------------- exported variables --

/* nothing */

// ------------------------------------------------------- exported functions --

/* nothing */

#endif // __LAYOUTMANAGER_H__
