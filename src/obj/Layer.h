/*******************************************************************************
 *
 *  name: Layer.h
 *  date: Dec 13, 2019
 *  auth: andrew
 *  desc:
 *
 ******************************************************************************/

#ifndef __LAYER_H__
#define __LAYER_H__

// ----------------------------------------------------------------- includes --

#include <list>
#include <vector>

#include "obj/Primitive.h"
#include "obj/Panel.h"

// ------------------------------------------------------------------ defines --

/* nothing */

// ------------------------------------------------------------------- macros --

/* nothing */

// ----------------------------------------------------- forward declarations --

class Screen;
class Frame;

// ----------------------------------------------------------- exported types --

class Layer {
protected:
  uint8_t _index;
  bool _remove;
  std::list<Panel> _panel;

  void clearPanels(Screen const &screen);

public:
  Layer(void):
    _index(0U),
    _remove(false),
    _panel() /* non-const */
  {}
  Layer(uint8_t index):
    _index(index),
    _remove(false),
    _panel()
  {}

  uint8_t index(void) const { return _index; }
  void setIndex(uint8_t index) { _index = index; } // INTERNAL (DO NOT USE)

  void draw(Screen const &screen, Touch const &touch);

  Panel *addPanel(Panel panel)
  {
    _panel.push_back(panel);
    return &(_panel.back());
  }

  void setNeedsUpdate(Screen const &screen);
  void setNeedsRemove(Screen const &screen);

  uint16_t panelCount() const
    { return _panel.empty() ? 0U : _panel.size(); }

  std::vector<Panel *> panels(Screen const &screen);
  std::vector<Panel *> panelsOverlappingFrame(
      Screen const &screen, Frame const &frame);
};

// ------------------------------------------------------- exported variables --

/* nothing */

// ------------------------------------------------------- exported functions --

/* nothing */

#endif // __LAYER_H__
