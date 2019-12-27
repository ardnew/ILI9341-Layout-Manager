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

#include <Arduino.h>

#include "Primitive.h"
#include "Panel.h"

// ------------------------------------------------------------------ defines --

/* nothing */

// ------------------------------------------------------------------- macros --

/* nothing */

// ----------------------------------------------------- forward declarations --

class Screen;
class Frame;

// ----------------------------------------------------------- exported types --

class Layer {
private:
  uint8_t _index;
  std::list<Panel> _panel;

public:
  Layer(void): _index(0U), _panel() /* non-const */ {}
  Layer(uint8_t index): _index(index), _panel() /* non-const */ {}

  constexpr uint8_t index(void) const { return _index; }
  void setIndex(uint8_t index) { _index = index; }
  void draw(Screen const &screen, Touch const &touch);
  Panel *addPanel(Panel panel)
  {
    _panel.push_back(panel);
    return &(_panel.back());
  }
  void clearPanels(Screen const &screen);
  void setNeedsUpdate(Screen const &screen);
  std::vector<Panel *> panelsOverlappingFrame(Screen const &screen, Frame const &frame);
};

// ------------------------------------------------------- exported variables --

/* nothing */

// ------------------------------------------------------- exported functions --

/* nothing */

#endif // __LAYER_H__
