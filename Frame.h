/*******************************************************************************
 *
 *  name: Frame.h
 *  date: Dec 13, 2019
 *  auth: andrew
 *  desc:
 *
 ******************************************************************************/

#ifndef __FRAME_H__
#define __FRAME_H__

// ----------------------------------------------------------------- includes --

#include <Arduino.h>

#include <Adafruit_ILI9341.h>

#include "Primitive.h"

// ------------------------------------------------------------------ defines --

#define FRAME_COLOR_DEFAULT                   ILI9341_BLACK
#define FRAME_BORDER_COLOR_DEFAULT            ILI9341_WHITE
#define FRAME_CORNER_RADIUS_DEFAULT           0U
#define FRAME_BORDER_RADIUS_DEFAULT           0U

// ------------------------------------------------------------------- macros --

/* nothing */

// ----------------------------------------------------- forward declarations --

class Screen;
class Frame;

// ----------------------------------------------------------- exported types --

typedef void (* FrameTouchCallback)(Frame const &, Touch const &);

class Frame {
private:
  uint8_t _layerIndex;
  Point _origin;
  Size _size;
  uint16_t _left;
  uint16_t _right;
  uint16_t _top;
  uint16_t _bottom;
  int8_t _marginBorder;
  bool _canTouch;
  bool _isBordered;
  Color _color;
  Color _colorTouched;
  Color _colorBorder;
  Color _colorBorderTouched;
  Radius _radiusCorner;
  Radius _radiusBorder;
  bool _update;
  bool _remove;
  Touch _touch;
  FrameTouchCallback _touchBegin;
  FrameTouchCallback _touchEnd;
  FrameTouchCallback _touchPress;

public:
  constexpr Frame(void):
    _layerIndex(0U),
    _origin(0U, 0U),
    _size(0U, 0U),
    _left(0U),
    _right(0U),
    _top(0U),
    _bottom(0U),
    _marginBorder(0U),
    _canTouch(false),
    _isBordered(false),
    _color(FRAME_COLOR_DEFAULT),
    _colorTouched(FRAME_COLOR_DEFAULT),
    _colorBorder(FRAME_BORDER_COLOR_DEFAULT),
    _colorBorderTouched(FRAME_BORDER_COLOR_DEFAULT),
    _radiusCorner(FRAME_CORNER_RADIUS_DEFAULT),
    _radiusBorder(FRAME_BORDER_RADIUS_DEFAULT),
    _update(false),
    _remove(false),
    _touch(),
    _touchBegin(nullptr),
    _touchEnd(nullptr),
    _touchPress(nullptr)
  {}
  constexpr Frame(
      uint8_t const layerIndex,
      Point const origin,
      Size const size,
      Radius const radiusCorner,
      Color const color
  ):
    _layerIndex(layerIndex),
    _origin(origin),
    _size(size),
    _left(origin.x()),
    _right(origin.x() + size.width()),
    _top(origin.y()),
    _bottom(origin.y() + size.height()),
    _marginBorder(0U),
    _canTouch(false),
    _isBordered(false),
    _color(color),
    _colorTouched(color),
    _colorBorder(color),
    _colorBorderTouched(color),
    _radiusCorner(radiusCorner),
    _radiusBorder(FRAME_BORDER_RADIUS_DEFAULT),
    _update(true),
    _remove(false),
    _touch(),
    _touchBegin(nullptr),
    _touchEnd(nullptr),
    _touchPress(nullptr)
  {}
  constexpr Frame(
      uint8_t const layerIndex,
      Point const origin,
      Size const size,
      Radius const radiusCorner,
      Color const color,
      Color const colorTouched
  ):
    _layerIndex(layerIndex),
    _origin(origin),
    _size(size),
    _left(origin.x()),
    _right(origin.x() + size.width()),
    _top(origin.y()),
    _bottom(origin.y() + size.height()),
    _marginBorder(0U),
    _canTouch(true),
    _isBordered(false),
    _color(color),
    _colorTouched(colorTouched),
    _colorBorder(FRAME_BORDER_COLOR_DEFAULT),
    _colorBorderTouched(FRAME_BORDER_COLOR_DEFAULT),
    _radiusCorner(radiusCorner),
    _radiusBorder(FRAME_BORDER_RADIUS_DEFAULT),
    _update(true),
    _remove(false),
    _touch(),
    _touchBegin(nullptr),
    _touchEnd(nullptr),
    _touchPress(nullptr)
  {}
  constexpr Frame(
      uint8_t const layerIndex,
      Point const origin,
      Size const size,
      Radius const radiusCorner,
      Color const color,
      Radius const radiusBorder,
      int8_t const marginBorder,
      Color const colorBorder
  ):
    _layerIndex(layerIndex),
    _origin(origin),
    _size(size),
    _left(origin.x()),
    _right(origin.x() + size.width()),
    _top(origin.y()),
    _bottom(origin.y() + size.height()),
    _marginBorder(marginBorder),
    _canTouch(false),
    _isBordered(true),
    _color(color),
    _colorTouched(color),
    _colorBorder(colorBorder),
    _colorBorderTouched(colorBorder),
    _radiusCorner(radiusCorner),
    _radiusBorder(radiusBorder),
    _update(true),
    _remove(false),
    _touch(),
    _touchBegin(nullptr),
    _touchEnd(nullptr),
    _touchPress(nullptr)
  {}
  constexpr Frame(
      uint8_t const layerIndex,
      Point const origin,
      Size const size,
      Radius const radiusCorner,
      Color const color,
      Color const colorTouched,
      Radius const radiusBorder,
      int8_t const marginBorder,
      Color const colorBorder,
      Color const colorBorderTouched
  ):
    _layerIndex(layerIndex),
    _origin(origin),
    _size(size),
    _left(origin.x()),
    _right(origin.x() + size.width()),
    _top(origin.y()),
    _bottom(origin.y() + size.height()),
    _marginBorder(marginBorder),
    _canTouch(true),
    _isBordered(true),
    _color(color),
    _colorTouched(colorTouched),
    _colorBorder(colorBorder),
    _colorBorderTouched(colorBorderTouched),
    _radiusCorner(radiusCorner),
    _radiusBorder(radiusBorder),
    _update(true),
    _remove(false),
    _touch(),
    _touchBegin(nullptr),
    _touchEnd(nullptr),
    _touchPress(nullptr)
  {}

  uint8_t layerIndex() const { return _layerIndex; }
  Point origin() const { return _origin; }
  Size size() const { return _size; }
  uint16_t left() const { return _left; }
  uint16_t right() const { return _right; }
  uint16_t top() const { return _top; }
  uint16_t bottom() const { return _bottom; }
  bool needsUpdate() const { return _update; }
  void setNeedsUpdate() { _update = true; }
  void setNeedsRemove() { _remove = true; }
  bool contains(Point const &p) const;
  bool overlaps(Frame const &f) const;
  bool covers(Frame const &f) const;
  bool draw(Screen const &screen, Touch const &touch);
  void setTouchBegin(FrameTouchCallback const callback)
    { _touchBegin = callback; }
  void setTouchEnd(FrameTouchCallback const callback)
    { _touchEnd = callback; }
  void setTouchPress(FrameTouchCallback const callback)
    { _touchPress = callback; }

  bool operator==(Frame const &f)
  {
    return
      (_layerIndex == f.layerIndex()) &&
      (_origin     == f.origin()    ) &&
      (_size       == f.size()      ) ;
  }
  bool operator!=(Frame const &f)
  {
    return
      (_layerIndex != f.layerIndex()) ||
      (_origin     != f.origin()    ) ||
      (_size       != f.size()      ) ;
  }
  //inline bool operator|=(Point const &p) const { return contains(p); }
  //inline bool operator|=(Frame const &f) const { return overlaps(f); }
  //inline bool operator||(Frame const &f) const { return covers(f); }
};

// ------------------------------------------------------- exported variables --

/* nothing */

// ------------------------------------------------------- exported functions --

/* nothing */

#endif // __FRAME_H__
