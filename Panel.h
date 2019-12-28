/*******************************************************************************
 *
 *  name: Panel.h
 *  date: Dec 13, 2019
 *  auth: andrew
 *  desc:
 *
 ******************************************************************************/

#ifndef __PANEL_H__
#define __PANEL_H__

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

class Panel {
private:
  Frame _frame;
  bool drawPanel(Screen const &screen, Touch const &touch);

public:
  constexpr Panel(void): _frame() {}
  constexpr Panel(Frame frame): _frame(frame) {}

  constexpr Frame frame() const { return _frame; }
  void draw(Screen const &screen, Touch const &touch);
  bool needsUpdate() const { return _frame.needsUpdate(); }
  void setNeedsUpdate() { _frame.setNeedsUpdate(); }
  void setNeedsRemove() { _frame.setNeedsRemove(); }
  void setTouchBegin(FrameTouchCallback const callback)
    { _frame.setTouchBegin(callback); }
  void setTouchEnd(FrameTouchCallback const callback)
    { _frame.setTouchEnd(callback); }
  void setTouchPress(FrameTouchCallback const callback)
    { _frame.setTouchPress(callback); }
};

// ------------------------------------------------------- exported variables --

/* nothing */

// ------------------------------------------------------- exported functions --

/* nothing */

#endif // __PANEL_H__
