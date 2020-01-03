/*******************************************************************************
 *
 *  name: Frame.cpp
 *  date: Dec 24, 2019
 *  auth: andrew
 *  desc:
 *
 ******************************************************************************/

// ----------------------------------------------------------------- includes --

#include "obj/Frame.h"
#include "obj/Screen.h"

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

void Frame::setOrigin(Point const origin)
{
  _origin = origin;

  _left = origin.x();
  _right = origin.x() + _size.width();
  _top = origin.y();
  _bottom = origin.y() + _size.height();

  setNeedsUpdate();
}

void Frame::setSize(Size const size)
{
  _size = size;

  _left = _origin.x();
  _right = _origin.x() + size.width();
  _top = _origin.y();
  _bottom = _origin.y() + size.height();

  setNeedsUpdate();
}

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
        if (!_isMomentary)
          { _isSelected = !_isSelected; }
        else
          { _isSelected = false; }
        if (nullptr != _touchPress) {
          // use the last-read touch, since the current one is not touched
          _touchPress(*this, _touch);
        }
      }
      else {
        if (_isMomentary)
          { _isSelected = false; }
        if (nullptr != _touchEnd) {
          _touchEnd(*this, touch);
        }
      }
      _update = true;
    }
    else if (!_touch.isTouched() && isTouchingFrame) {
      if (_isMomentary)
        { _isSelected = true; }
      if (nullptr != _touchBegin) {
        _touchBegin(*this, touch);
      }
      _update = true;
    }

    _touch = Touch(isTouchingFrame, touch.position(), touch.pressure());
  }

  if (!_remove && _update) {

    if (!isTouchingFrame) {
      if (_isMomentary || !_isSelected) {
        if (_isBordered) {
          screen.paintFrame(_origin, _size, _radiusCorner, _color, _radiusBorder, _marginBorder, _colorBorder);
        }
        else {
          screen.paintFrame(_origin, _size, _radiusCorner, _color);
        }
      }
      else {
        if (_isBordered) {
          screen.paintFrame(_origin, _size, _radiusCorner, _colorSelected, _radiusBorder, _marginBorder, _colorBorderSelected);
        }
        else {
          screen.paintFrame(_origin, _size, _radiusCorner, _colorSelected);
        }
      }
    }
    else {
      if (_isMomentary || !_isSelected) {
        if (_isBordered) {
          screen.paintFrame(_origin, _size, _radiusCorner, _colorTouched, _radiusBorder, _marginBorder, _colorBorderTouched);
        }
        else {
          screen.paintFrame(_origin, _size, _radiusCorner, _colorTouched);
        }
      }
      else {
        if (_isBordered) {
          screen.paintFrame(_origin, _size, _radiusCorner, _colorSelected, _radiusBorder, _marginBorder, _colorBorderSelected);
        }
        else {
          screen.paintFrame(_origin, _size, _radiusCorner, _colorSelected);
        }
      }
    }

    _update = false;

    return true; // performed an update
  }
  return false; // DID NOT perform an update
}

// -------------------------------------------------------- private functions --

/* nothing */
