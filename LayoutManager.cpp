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

LayoutManager::LayoutManager(
    uint16_t const tftCSPin, uint16_t const tftDCPin,
    uint16_t const tsCSPin, uint16_t const tsIRQPin,
    uint16_t const width, uint16_t const height,
    ScreenOrientation const orientation
):
  _screen(Screen(
      tftCSPin, tftDCPin, tsCSPin, tsIRQPin, width, height, orientation
  ))
{
  /* nothing */
}

bool LayoutManager::begin()
{
  if (!initScreen())
    { return false; }

  return true;
}

void LayoutManager::draw()
{
  _screen.draw();
}

// -------------------------------------------------------- private functions --

bool LayoutManager::initScreen()
{
  return _screen.begin();
}