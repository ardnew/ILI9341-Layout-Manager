/*******************************************************************************
 *
 *  name: Field.h
 *  date: Dec 13, 2019
 *  auth: andrew
 *  desc:
 *
 ******************************************************************************/

#ifndef __FIELD_H__
#define __FIELD_H__

// ----------------------------------------------------------------- includes --

#include <Arduino.h>

#include "Primitive.h"
#include "Frame.h"

// ------------------------------------------------------------------ defines --

/* nothing */

// ------------------------------------------------------------------- macros --

/* nothing */

// ----------------------------------------------------- forward declarations --

class Screen;

// ----------------------------------------------------------- exported types --

class Field {
private:
  Frame _frame;

public:
  constexpr Field(void): _frame() {}
  constexpr Field(Frame frame): _frame(frame) {}

  void draw(Screen const &screen, Touch const &touch);
};

// ------------------------------------------------------- exported variables --

/* nothing */

// ------------------------------------------------------- exported functions --

/* nothing */

#endif // __FIELD_H__
