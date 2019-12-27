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

void p1_begin(Frame const &f, Touch const &t) { Serial.printf("p1_begin {%u,%u}\n", t.x(), t.y()); }
void p1_end(Frame const &f, Touch const &t) { Serial.printf("p1_end {%u,%u}\n", t.x(), t.y()); }
void p1_press(Frame const &f, Touch const &t)
{
  Serial.printf("p1_press {%u,%u}\n", t.x(), t.y());

  // add another panel to the second layer
  if (nullptr == p2) {
    p2 = man->addPanel(
        1U,        // layer 1 (above-bottom-most)
        50U, 40U,  // origin, top-left (x,y) point
        30U, 40U,  // size, width and height
        0U,        // radius of rounded corners of panel, 0 for none (square)
        COLOR_GREEN, COLOR_YELLOW, // panel color touched, not-touched
        0U,        // rounded corner radius of border
        COLOR_RED, COLOR_BLUE      // border color touched, not-touched
     );
    // set some callbacks
    p2->setTouchBegin(p2_begin);
    p2->setTouchEnd(p2_end);
    p2->setTouchPress(p2_press);
  }

}

void p2_begin(Frame const &f, Touch const &t) { Serial.printf("p2_begin {%u,%u}\n", t.x(), t.y()); }
void p2_end(Frame const &f, Touch const &t) { Serial.printf("p2_end {%u,%u}\n", t.x(), t.y()); }
void p2_press(Frame const &f, Touch const &t)
{
  Serial.printf("p2_press {%u,%u}\n", t.x(), t.y());
  man->removeTopLayer();
  p2 = nullptr;
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

  // add one panel to the first layer
  p1 = man->addPanel(
      0U,        // layer 0 (bottom-most)
      30U, 60U,  // origin, top-left (x,y) point
      40U, 50U,  // size, width and height
      0U,        // radius of rounded corners of panel, 0 for none (square)
      COLOR_RED, COLOR_BLUE,    // panel color touched, not-touched
      0U,        // rounded corner radius of border
      COLOR_YELLOW, COLOR_GREEN // border color touched, not-touched
   );
  // set some callbacks
  p1->setTouchBegin(p1_begin);
  p1->setTouchEnd(p1_end);
  p1->setTouchPress(p1_press);

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