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
private:
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
      Radius const radiusBorder,
      Color const colorBorder
  );
  Panel *addPanel(
      uint8_t const layerIndex,
      uint16_t const x, uint16_t const y,
      uint16_t const width, uint16_t const height,
      Radius const radiusCorner,
      Color const color, Color const colorTouched,
      Radius const radiusBorder,
      Color const colorBorder, Color const colorBorderTouched
  );

  void removeTopLayer();

};

// ------------------------------------------------------- exported variables --

/* nothing */

// ------------------------------------------------------- exported functions --

/* nothing */

#endif // __LAYOUTMANAGER_H__
