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

#include "obj/Primitive.h"

// ------------------------------------------------------------------ defines --

#define FRAME_COLOR_DEFAULT                   COLOR_BLACK
#define FRAME_BORDER_COLOR_DEFAULT            COLOR_WHITE
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
protected:
  uint8_t _layerIndex;
  Point _origin;
  Size _size;
  uint16_t _left;
  uint16_t _right;
  uint16_t _top;
  uint16_t _bottom;
  int8_t _marginBorder;
  bool _canTouch;
  bool _isMomentary;
  bool _isSelected;
  bool _isBordered;
  Color _color;
  Color _colorTouched;
  Color _colorSelected;
  Color _colorBorder;
  Color _colorBorderTouched;
  Color _colorBorderSelected;
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
    _isMomentary(true),
    _isSelected(false),
    _isBordered(false),
    _color(FRAME_COLOR_DEFAULT),
    _colorTouched(FRAME_COLOR_DEFAULT),
    _colorSelected(FRAME_COLOR_DEFAULT),
    _colorBorder(FRAME_BORDER_COLOR_DEFAULT),
    _colorBorderTouched(FRAME_BORDER_COLOR_DEFAULT),
    _colorBorderSelected(FRAME_BORDER_COLOR_DEFAULT),
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
    _isMomentary(true),
    _isSelected(false),
    _isBordered(false),
    _color(color),
    _colorTouched(color),
    _colorSelected(color),
    _colorBorder(color),
    _colorBorderTouched(color),
    _colorBorderSelected(color),
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
    _isMomentary(true),
    _isSelected(false),
    _isBordered(false),
    _color(color),
    _colorTouched(colorTouched),
    _colorSelected(colorTouched),
    _colorBorder(FRAME_BORDER_COLOR_DEFAULT),
    _colorBorderTouched(FRAME_BORDER_COLOR_DEFAULT),
    _colorBorderSelected(FRAME_BORDER_COLOR_DEFAULT),
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
    _isMomentary(true),
    _isSelected(false),
    _isBordered(true),
    _color(color),
    _colorTouched(color),
    _colorSelected(color),
    _colorBorder(colorBorder),
    _colorBorderTouched(colorBorder),
    _colorBorderSelected(colorBorder),
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
    _isMomentary(true),
    _isSelected(false),
    _isBordered(true),
    _color(color),
    _colorTouched(colorTouched),
    _colorSelected(colorTouched),
    _colorBorder(colorBorder),
    _colorBorderTouched(colorBorderTouched),
    _colorBorderSelected(colorBorderTouched),
    _radiusCorner(radiusCorner),
    _radiusBorder(radiusBorder),
    _update(true),
    _remove(false),
    _touch(),
    _touchBegin(nullptr),
    _touchEnd(nullptr),
    _touchPress(nullptr)
  {}

  uint8_t layerIndex(void) const { return _layerIndex; }
  Point origin(void) const { return _origin; }
  void setOrigin(Point const origin);
  Size size(void) const { return _size; }
  void setSize(Size const size);
  uint16_t left(void) const { return _left; }
  uint16_t right(void) const { return _right; }
  uint16_t top(void) const { return _top; }
  uint16_t bottom(void) const { return _bottom; }
  bool canTouch(void) const { return _canTouch; }
  bool isMomentary(void) const { return _isMomentary; }
  void setIsMomentary(bool const isMomentary) { _isMomentary = isMomentary; }
  bool isSelected(void) const { return _isSelected; }
  void setIsSelected(bool const isSelected)
    { if (isSelected != _isSelected)
      { _isSelected = isSelected; setNeedsUpdate(); } }
  Color color(void) const { return _color; }
  void setColor(Color const color)
    { if (color != _color)
      { _color = color; setNeedsUpdate(); } }
  Color colorTouched(void) const { return _colorTouched; }
  void setColorTouched(Color const color)
    { if (color != _colorTouched)
      { _colorTouched = color; setNeedsUpdate(); } }
  Color colorSelected(void) const { return _colorSelected; }
  void setColorSelected(Color const color)
    { if (color != _colorSelected)
      { _colorSelected = color; setNeedsUpdate(); } }
  Color colorBorder(void) const { return _colorBorder; }
  void setColorBorder(Color const color)
    { if (color != _colorBorder)
      { _colorBorder = color; setNeedsUpdate(); } }
  Color colorBorderTouched(void) const { return _colorBorderTouched; }
  void setColorBorderTouched(Color const color)
    { if (color != _colorBorderTouched)
      { _colorBorderTouched = color; setNeedsUpdate(); } }
  Color colorBorderSelected(void) const { return _colorBorderSelected; }
  void setColorBorderSelected(Color const color)
    { if (color != _colorBorderSelected)
      { _colorBorderSelected = color; setNeedsUpdate(); } }
  Radius radiusCorner(void) const { return _radiusCorner; }
  bool needsUpdate(void) const { return _update; }
  void setNeedsUpdate(void) { _update = true; }
  void setNeedsRemove(void) { _remove = true; }
  Touch touch(void) const { return _touch; }
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
