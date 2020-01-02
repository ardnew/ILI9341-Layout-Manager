/*******************************************************************************
 *
 *  name: LayoutManager.cpp
 *  date: Dec 24, 2019
 *  auth: andrew
 *  desc:
 *
 ******************************************************************************/

// ----------------------------------------------------------------- includes --

#include <Adafruit_GFX.h>

#include "LayoutManager.h"
#include "obj/Layer.h"
#include "obj/Panel.h"

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

Panel *LayoutManager::addPanel(
    uint8_t const layerIndex,
    uint16_t const x, uint16_t const y,
    uint16_t const width, uint16_t const height,
    Radius const radiusCorner,
    Color const color)
{
  Layer *layer = _screen.layer(layerIndex);
  if (layerIndex > _screen.layerIndexTop())
    { _screen.setLayerIndexTop(layerIndex); }
  if (nullptr != layer) {
    return layer->addPanel(Panel(Frame(
        layerIndex,
        Point(x, y),
        Size(width, height),
        radiusCorner,
        color
    )));
  }
  return nullptr;
}

Panel *LayoutManager::addPanel(
    uint8_t const layerIndex,
    uint16_t const x, uint16_t const y,
    uint16_t const width, uint16_t const height,
    Radius const radiusCorner,
    Color const color, Color const colorTouched)
{
  Layer *layer = _screen.layer(layerIndex);
  if (layerIndex > _screen.layerIndexTop())
    { _screen.setLayerIndexTop(layerIndex); }
  if (nullptr != layer) {
    return layer->addPanel(Panel(Frame(
        layerIndex,
        Point(x, y),
        Size(width, height),
        radiusCorner,
        color, colorTouched
    )));
  }
  return nullptr;
}

Panel *LayoutManager::addPanel(
    uint8_t const layerIndex,
    uint16_t const x, uint16_t const y,
    uint16_t const width, uint16_t const height,
    Radius const radiusCorner,
    Color const color,
    Radius const radiusBorder, int8_t const marginBorder,
    Color const colorBorder)
{
  Layer *layer = _screen.layer(layerIndex);
  if (layerIndex > _screen.layerIndexTop())
    { _screen.setLayerIndexTop(layerIndex); }
  if (nullptr != layer) {
    return layer->addPanel(Panel(Frame(
        layerIndex,
        Point(x, y),
        Size(width, height),
        radiusCorner,
        color,
        radiusBorder, marginBorder,
        colorBorder
    )));
  }
  return nullptr;
}

Panel *LayoutManager::addPanel(
    uint8_t const layerIndex,
    uint16_t const x, uint16_t const y,
    uint16_t const width, uint16_t const height,
    Radius const radiusCorner,
    Color const color, Color const colorTouched,
    Radius const radiusBorder, int8_t const marginBorder,
    Color const colorBorder, Color const colorBorderTouched)
{
  Layer *layer = _screen.layer(layerIndex);
  if (layerIndex > _screen.layerIndexTop())
    { _screen.setLayerIndexTop(layerIndex); }
  if (nullptr != layer) {
    return layer->addPanel(Panel(Frame(
        layerIndex,
        Point(x, y),
        Size(width, height),
        radiusCorner,
        color, colorTouched,
        radiusBorder, marginBorder,
        colorBorder, colorBorderTouched
    )));
  }
  return nullptr;
}

Field *LayoutManager::addField(
    Panel * const panel,
    std::string const text,
    uint8_t const sizeText,
    Color const colorText,
    Radius const radiusCorner,
    Color const colorPanel
)
{
  if (nullptr != panel) {
    return panel->addField(Field(Frame(
        panel->frame()->layerIndex(),
        Point(0U, 0U), // determined when drawing
        Size(0U, 0U),  // determined when drawing
        radiusCorner,
        colorPanel
    ), text, sizeText, colorText));
  }
  return nullptr;
}

Field *LayoutManager::addField(
    Panel * const panel,
    std::string const text,
    uint8_t const sizeText,
    Color const colorText, Color const colorTextTouched,
    Radius const radiusCorner,
    Color const colorPanel, Color const colorPanelTouched
)
{
  if (nullptr != panel) {
    return panel->addField(Field(Frame(
        panel->frame()->layerIndex(),
        Point(0U, 0U), // determined when drawing
        Size(0U, 0U),  // determined when drawing
        radiusCorner,
        colorPanel, colorPanelTouched
    ), text, sizeText, colorText, colorTextTouched));
  }
  return nullptr;
}

Field *LayoutManager::addField(
    Panel * const panel,
    std::string const text,
    uint8_t const sizeText,
    Color const colorText,
    Radius const radiusCorner,
    Color const colorPanel,
    Radius const radiusBorder, int8_t const marginBorder,
    Color const colorBorder
)
{
  if (nullptr != panel) {
    return panel->addField(Field(Frame(
        panel->frame()->layerIndex(),
        Point(0U, 0U), // determined when drawing
        Size(0U, 0U),  // determined when drawing
        radiusCorner,
        colorPanel,
        radiusBorder, marginBorder,
        colorBorder
    ), text, sizeText, colorText));
  }
  return nullptr;

}

Field *LayoutManager::addField(
    Panel * const panel,
    std::string const text,
    uint8_t const sizeText,
    Color const colorText, Color const colorTextTouched,
    Radius const radiusCorner,
    Color const colorPanel, Color const colorPanelTouched,
    Radius const radiusBorder, int8_t const marginBorder,
    Color const colorBorder, Color const colorBorderTouched
)
{
  if (nullptr != panel) {
    return panel->addField(Field(Frame(
        panel->frame()->layerIndex(),
        Point(0U, 0U), // determined when drawing
        Size(0U, 0U),  // determined when drawing
        radiusCorner,
        colorPanel, colorPanelTouched,
        radiusBorder, marginBorder,
        colorBorder, colorBorderTouched
    ), text, sizeText, colorText, colorTextTouched));
  }
  return nullptr;
}

Field *LayoutManager::addField(
    Panel * const panel,
    std::string const text,
    uint8_t const sizeText,
    GFXfont const * const font,
    Color const colorText,
    Radius const radiusCorner,
    Color const colorPanel
)
{
  if (nullptr != panel) {
    return panel->addField(Field(Frame(
        panel->frame()->layerIndex(),
        Point(0U, 0U), // determined when drawing
        Size(0U, 0U),  // determined when drawing
        radiusCorner,
        colorPanel
    ), text, sizeText, (GFXfont * const)font, colorText));
  }
  return nullptr;
}

Field *LayoutManager::addField(
    Panel * const panel,
    std::string const text,
    uint8_t const sizeText,
    GFXfont const * const font,
    Color const colorText, Color const colorTextTouched,
    Radius const radiusCorner,
    Color const colorPanel, Color const colorPanelTouched
)
{
  if (nullptr != panel) {
    return panel->addField(Field(Frame(
        panel->frame()->layerIndex(),
        Point(0U, 0U), // determined when drawing
        Size(0U, 0U),  // determined when drawing
        radiusCorner,
        colorPanel, colorPanelTouched
    ), text, sizeText, (GFXfont * const)font, colorText, colorTextTouched));
  }
  return nullptr;
}

Field *LayoutManager::addField(
    Panel * const panel,
    std::string const text,
    uint8_t const sizeText,
    GFXfont const * const font,
    Color const colorText,
    Radius const radiusCorner,
    Color const colorPanel,
    Radius const radiusBorder, int8_t const marginBorder,
    Color const colorBorder
)
{
  if (nullptr != panel) {
    return panel->addField(Field(Frame(
        panel->frame()->layerIndex(),
        Point(0U, 0U), // determined when drawing
        Size(0U, 0U),  // determined when drawing
        radiusCorner,
        colorPanel,
        radiusBorder, marginBorder,
        colorBorder
    ), text, sizeText, (GFXfont * const)font, colorText));
  }
  return nullptr;

}

Field *LayoutManager::addField(
    Panel * const panel,
    std::string const text,
    uint8_t const sizeText,
    GFXfont const * const font,
    Color const colorText, Color const colorTextTouched,
    Radius const radiusCorner,
    Color const colorPanel, Color const colorPanelTouched,
    Radius const radiusBorder, int8_t const marginBorder,
    Color const colorBorder, Color const colorBorderTouched
)
{
  if (nullptr != panel) {
    return panel->addField(Field(Frame(
        panel->frame()->layerIndex(),
        Point(0U, 0U), // determined when drawing
        Size(0U, 0U),  // determined when drawing
        radiusCorner,
        colorPanel, colorPanelTouched,
        radiusBorder, marginBorder,
        colorBorder, colorBorderTouched
    ), text, sizeText, (GFXfont * const)font, colorText, colorTextTouched));
  }
  return nullptr;
}

void LayoutManager::layerRemoveTop()
{
  // locate the previous top-most layer that actually has panels populated on it
  //   (not necessarily indexTop - 1)
  uint8_t indexPrev = layerIndexPrev();

  if (LAYER_INDEX_INVALID != indexPrev)
    { _screen.setLayerIndexTop(indexPrev); }
  else
    { _screen.setLayerIndexTop(0U); }
}

// -------------------------------------------------------- private functions --

