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

#include <list>

#include "obj/Primitive.h"
#include "obj/Frame.h"
#include "obj/Field.h"

// ------------------------------------------------------------------ defines --

#define PANEL_LAYOUT_AXIS_DEFAULT LayoutAxis::Horizontal

// ------------------------------------------------------------------- macros --

/* nothing */

// ----------------------------------------------------- forward declarations --

class Screen;

// ----------------------------------------------------------- exported types --

class Panel {
protected:
  Frame _frame;
  uint16_t _margin;
  uint16_t _padding;
  LayoutAxis _axis;
  bool _proportional;
  bool _allowsMultipleSelection;
  std::list<Field> _field;

public:
  Panel(void):
    _frame(),
    _margin(0U),
    _padding(0U),
    _axis(PANEL_LAYOUT_AXIS_DEFAULT),
    _proportional(false),
    _field()
  {}
  Panel(Frame const frame):
    _frame(frame),
    _margin(0U),
    _padding(0U),
    _axis(PANEL_LAYOUT_AXIS_DEFAULT),
    _proportional(false),
    _field()
  {}

  void draw(Screen const &screen, Touch const &touch);

  Frame const *frame(void) const { return &_frame; }

  uint16_t margin() const { return _margin; }
  void setMargin(uint16_t const margin) { _margin = margin; }

  uint16_t padding() const { return _padding; }
  void setPadding(uint16_t const padding) { _padding = padding; }

  void setLineSpacing(uint16_t const spacing)
  {
    if (!_field.empty()) {
      for (auto it = _field.begin(); it != _field.end(); ++it)
        { it->setLineSpacing(spacing); }
    }
  }

  LayoutAxis axis() const { return _axis; }
  void setAxis(LayoutAxis const axis) { _axis = axis; }

  bool proportional() const { return _proportional; }
  void setProportional(bool proportional) { _proportional = proportional; }

  bool allowsMultipleSelection() const { return _allowsMultipleSelection; }
  void setAllowsMultipleSelection(bool const allowsMultipleSelection)
    { _allowsMultipleSelection = allowsMultipleSelection; }

  uint8_t fieldCount() const { return _field.empty() ? 0U : _field.size(); }
  Field *addField(Field field)
  {
    _field.push_back(field);
    return &(_field.back());
  }
  void clearFields()
  {
    if (!_field.empty()) {
      _field.clear();
      setNeedsUpdate();
    }
  }

  bool needsUpdate() const;
  void setNeedsUpdate();
  void setNeedsRemove();
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
