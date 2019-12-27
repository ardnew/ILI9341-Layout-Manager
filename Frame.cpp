/*******************************************************************************
 *
 *  name: Frame.cpp
 *  date: Dec 24, 2019
 *  auth: andrew
 *  desc:
 *
 ******************************************************************************/

// ----------------------------------------------------------------- includes --

#include "Frame.h"
#include "Screen.h"

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

bool Frame::contains(Point const &p) const
{
  return
    in_range_u16(p.x(), _left, _right) &&
    in_range_u16(p.y(), _top, _bottom) ;
}

bool Frame::overlaps(Frame const &f) const
{
  // proof of this logic is in an excellent SO answer here:
  //   https://stackoverflow.com/a/306332/1054397
  return
    (   _left <= f.right()  ) &&
    (  _right >= f.left()   ) &&
    (    _top <= f.bottom() ) &&
    ( _bottom >= f.top()    ) ;
}

bool Frame::covers(Frame const &f) const
{
  // checks if this frame completely covers the argument on all sides
  return
    (   _left <= f.left()   ) &&
    (  _right >= f.right()  ) &&
    (    _top <= f.top()    ) &&
    ( _bottom >= f.bottom() ) ;
}

bool Frame::draw(Screen const &screen, Touch const &touch)
{
  bool isActiveLayer = (screen.layerIndexTop() == _layerIndex);
  bool isTouchingFrame = false;

  if (_canTouch) {

    isTouchingFrame =
        isActiveLayer && touch.isTouched() && contains(touch.position());

    if (_touch.isTouched() && !isTouchingFrame) {
      if (!touch.isTouched()) {
        if (nullptr != _touchPress) {
          // use the last-read touch, since the current one is not touched
          _touchPress(*this, _touch);
        }
      }
      else {
        if (nullptr != _touchEnd) {
          _touchEnd(*this, touch);
        }
      }
      _update = true;
    }
    else if (!_touch.isTouched() && isTouchingFrame) {
      if (nullptr != _touchBegin) {
        _touchBegin(*this, touch);
      }
      _update = true;
    }

    _touch = Touch(isTouchingFrame, touch.position(), touch.pressure());
  }

  if (!_remove && _update) {

    if (!isTouchingFrame) {
      if (_isBordered) {
        screen.paintFrame(_origin, _size, _color, _colorBorder);
      }
      else {
        screen.paintFrame(_origin, _size, _color);
      }
    }
    else {
      if (_isBordered) {
        screen.paintFrame(_origin, _size, _colorTouched, _colorBorderTouched);
      }
      else {
        screen.paintFrame(_origin, _size, _colorTouched);
      }
    }
    _update = false;

    return true; // performed an update
  }
  return false; // DID NOT perform an update
}

// -------------------------------------------------------- private functions --

/* nothing */
