/*******************************************************************************
 *
 *  name: LayoutManager.cpp
 *  date: Dec 24, 2019
 *  auth: andrew
 *  desc:
 *
 ******************************************************************************/

// ----------------------------------------------------------------- includes --

#include "LayoutManager.h"
#include "Layer.h"
#include "Panel.h"

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
    Radius const radiusBorder,
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
        radiusBorder,
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
    Radius const radiusBorder,
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
        radiusBorder,
        colorBorder, colorBorderTouched
    )));
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

