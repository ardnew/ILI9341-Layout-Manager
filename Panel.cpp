/*******************************************************************************
 *
 *  name: Panel.cpp
 *  date: Dec 24, 2019
 *  auth: andrew
 *  desc:
 *
 ******************************************************************************/

// ----------------------------------------------------------------- includes --

#include "Panel.h"
#include "Screen.h"
#include "Layer.h"

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

void Panel::draw(Screen const &screen, Touch const &touch)
{
  (void)drawPanel(screen, touch);
}

// -------------------------------------------------------- private functions --

bool Panel::drawPanel(Screen const &screen, Touch const &touch)
{
  return _frame.draw(screen, touch);
}
