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

#include <Adafruit_ILI9341.h>
#include <XPT2046_Calibrated.h>

#include "Screen.h"
#include "Layer.h"
#include "Panel.h"
#include "Field.h"
#include "Frame.h"

// ------------------------------------------------------------------ defines --

/* nothing */

// ------------------------------------------------------------------- macros --

/* nothing */

// ----------------------------------------------------------- exported types --

class LayoutManager {
private:
  Adafruit_ILI9341 *_tft;
  XPT2046_Calibrated *_ts;

  Screen *_screen;

public:
  LayoutManager(void);
  initDisplay(uint16_t csPin, uint16_t dcPin);
  initTouchScreen(uint16_t csPin, uint16_t irqPin);
};

// ------------------------------------------------------- exported variables --

/* nothing */

// ------------------------------------------------------- exported functions --

/* nothing */

#endif // __LAYOUTMANAGER_H__
