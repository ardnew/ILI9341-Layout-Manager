/*******************************************************************************
 *
 *  name: LayoutManager.cpp
 *  date: Dec 24, 2019
 *  auth: andrew
 *  desc:
 *
 ******************************************************************************/

// ----------------------------------------------------------------- includes --

#include "LayoutManager.h"

// ---------------------------------------------------------- private defines --

/* nothing */

// ----------------------------------------------------------- private macros --

/* nothing */

// ------------------------------------------------------------ private types --

/* nothing */

// ------------------------------------------------------- exported variables --

/* nothing */

// -------------------------------------------------------- private variables --

/* nothing */

// ---------------------------------------------- private function prototypes --

/* nothing */

// ------------------------------------------------------- exported functions --

LayoutManager::LayoutManager(void):
    _tft(NULL),
    _ts(NULL),
    _screen(new Screen())
{
  /* nothing */
}

LayoutManager::initDisplay(uint16_t csPin, uint16_t dcPin)
{
  _tft = new Adafruit_ILI9341(csPin, dcPin);
}

LayoutManager::initTouchScreen(uint16_t csPin, uint16_t irqPin)
{
  _ts = new XPT2046_Calibrated(csPin, irqPin);
}

// -------------------------------------------------------- private functions --

/* nothing */
