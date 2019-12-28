/*******************************************************************************
 *
 *  name: ilm-demo.ino
 *  date: Dec 13, 2019
 *  auth: andrew
 *  desc:
 *
 ******************************************************************************/

#include <LayoutManager.h>

//
// TFT Touchscreen GPIO pin definitions
//
#define TFT_VCC_PIN    /* 3v3 */
#define TFT_GND_PIN    /* GND */
#define TFT_CS_PIN          7
#define TFT_RST_PIN         6
#define TFT_DC_PIN          5
#define TFT_MOSI_PIN       51
#define TFT_SCK_PIN        52
#define TFT_LED_PIN    /* 3v3 */
#define TFT_MISO_PIN       50
#define TOUCH_CLK_PIN      52
#define TOUCH_CS_PIN        4
#define TOUCH_MOSI_PIN     51
#define TOUCH_MISO_PIN     50
#define TOUCH_IRQ_PIN       3

LayoutManager *man = nullptr;
Panel *p1 = nullptr;
Panel *p2 = nullptr;

void p1_press(Frame const &f, Touch const &t)
{
  Serial.printf("p1_press {%u,%u}\n", t.x(), t.y());
}

void p2_press(Frame const &f, Touch const &t)
{
  Serial.printf("p2_press {%u,%u}\n", t.x(), t.y());
}

void screenTouchBegin(Screen const &s, Touch const &t)
{
  Serial.printf("BEG({%u,%u}, %u)\n", t.x(), t.y(), t.pressure());
}

void screenTouchEnd(Screen const &s, Touch const &t)
{
  Serial.printf("END({%u,%u}, %u)\n", t.x(), t.y(), t.pressure());

  if (t.x() > 160) {
    uint8_t index = man->layerIndexTop() + 1U;
    // add a panel to a new layer
    man->addPanel(
        index,
        20U + index * 20,
        20U + index * 10,  // origin, top-left (x,y) point
        75U, 20U,  // size, width and height
        0U,        // radius of rounded corners of panel, 0 for none (square)
        COLOR_WHITE, COLOR_PURPLE, // panel color, touched color
        0U,        // rounded corner radius of border, as above
        0,         // border margin, <0 outside panel, >0 inside panel
        COLOR_PURPLE, COLOR_WHITE  // border color, touched color
    );
  }
  else {
    // remove the top-most layer
    man->layerRemoveTop();
  }
}

void setup()
{

  while (!Serial && millis() < 1000) { continue; }
  Serial.begin(115200);
  Serial.printf("creating panels (%u)\n", 2);

  // primary object containing and organizing all components
  man = new LayoutManager(
      // TFT
      TFT_CS_PIN, TFT_DC_PIN,
      // Touchscreen
      TOUCH_CS_PIN, TOUCH_IRQ_PIN,
      // Both
      320, 240, Orientation::Landscape, COLOR_BLACK);
  man->setTouchBegin(screenTouchBegin);
  man->setTouchEnd(screenTouchEnd);

  // add one panel to the first layer
  p1 = man->addPanel(
      0U,        // layer 0 (bottom-most)
      20U, 20U,  // origin, top-left (x,y) point
      80U, 40U,  // size, width and height
      6U,        // radius of rounded corners of panel, 0 for none (square)
      COLOR_BLUE, COLOR_GREEN, // panel color, touched color
      6U,        // rounded corner radius of border, as above
      0,          // border margin, <0 outside panel, >0 inside panel
      COLOR_YELLOW, COLOR_RED  // border color, touched color
   );
  // set some callbacks
  p1->setTouchPress(p1_press);

  p2 = man->addPanel(
      0U,        // layer
      120U, 20U, // origin, top-left (x,y) point
      80U,  40U, // size, width and height
      8U,        // radius of rounded corners of panel, 0 for none (square)
      COLOR_RED, COLOR_YELLOW, // panel color, touched color
      8U,        // rounded corner radius of border, as above
      0,          // border margin, <0 outside panel, >0 inside panel
      COLOR_GREEN, COLOR_BLUE  // border color, touched color
   );
  // set some callbacks
  p2->setTouchPress(p2_press);

  // initialize the screen with all currently defined components
  if (!man->begin()) {
    Serial.println("failed to start!");
  }
  else {
    Serial.println("all ok :)");
  }
}

void loop()
{
  // call once per iteration to effeciently update screen content and invoke
  // any user-defined callbacks for requested events
  man->draw();
}

// -------------------------------------------------------- private functions --

void initPeripherals(void)
{

}