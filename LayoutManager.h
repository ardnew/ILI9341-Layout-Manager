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

#include "Screen.h"

// ------------------------------------------------------------------ defines --

/* nothing */

// ------------------------------------------------------------------- macros --

/* nothing */

// ----------------------------------------------------------- exported types --

class LayoutManager {
private:
  Screen _screen;
  bool initScreen();

public:
  LayoutManager(
    uint16_t const tftCSPin, uint16_t const tftDCPin,
    uint16_t const tsCSPin, uint16_t const tsIRQPin,
    uint16_t const width, uint16_t const height,
    ScreenOrientation const orientation
  );
  bool begin();
  void draw();
};

// ------------------------------------------------------- exported variables --

/* nothing */

// ------------------------------------------------------- exported functions --

/* nothing */

#endif // __LAYOUTMANAGER_H__
