/*******************************************************************************
 *
 *  name: ilm-demo.ino
 *  date: Dec 13, 2019
 *  auth: andrew
 *  desc:
 *
 ******************************************************************************/

#include <LayoutManager.h>

// ------------------------------------------------------------ configuration --

//#define WAIT_FOR_SERIAL

#define GRAND_CENTRAL_M4
//#define ITSY_BITSY_M4

// TFT Touchscreen GPIO pin definitions
#if defined(GRAND_CENTRAL_M4)
#define TFT_VCC_PIN    /* 3v3 */
#define TFT_GND_PIN    /* GND */
#define TFT_CS_PIN          7
#define TFT_RST_PIN    /* 3v3 */
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
#elif defined(ITSY_BITSY_M4)
#define TFT_VCC_PIN    /* 3v3 */
#define TFT_GND_PIN    /* GND */
#define TFT_CS_PIN          7
#define TFT_RST_PIN        13
#define TFT_DC_PIN         12
#define TFT_MOSI_PIN       25
#define TFT_SCK_PIN        24
#define TFT_LED_PIN    /* 3v3 */
#define TFT_MISO_PIN       23
#define TOUCH_CLK_PIN      24
#define TOUCH_CS_PIN       11
#define TOUCH_MOSI_PIN     25
#define TOUCH_MISO_PIN     23
#define TOUCH_IRQ_PIN       9
#endif

#define EXPAND(x) x ## 1
#define DEFINED_VAL(x) 1 != EXPAND(x)

// -------------------------------------------------------- screen components --

LayoutManager *man;

Panel *p1;
Field *p1f1;
Field *p1f2;

Panel *p2;
Field *p2f1;
Field *p2f2;
Field *p2f3;

void p1_press(Frame const &f, Touch const &t);
void p2_press(Frame const &f, Touch const &t);
void p1f1_begin(Frame const &f, Touch const &t);
void p1f1_end(Frame const &f, Touch const &t);
void p1f1_press(Frame const &f, Touch const &t);
void screenTouchEnd(Screen const &s, Touch const &t);

// -------------------------------------------------------- arduino functions --

void initGPIO(void);
void initPeripherals(void);

void setup()
{
  initGPIO();
  initPeripherals();

  // initialize the screen with all currently defined components
  if (!man->begin()) {
    Serial.println("failed to start!");
  }
  else {
    Serial.println("all good");
  }
}

void loop()
{
  static uint16_t time = 0U;
  static uint16_t curr;
  static char buf[32];

  curr = millis();
  if (curr - time > 500U) {
    uint16_t val1 = curr % 1000U;
    uint16_t val2 = time % 500U;
    if (val1 > 500) {
      snprintf(buf, 32, "%u", val1);
    }
    else {
      snprintf(buf, 32, "%u\n%u", val1, val2);
    }
    p1f1->setText(buf);
    time = curr;
  }

  // call once per iteration to effeciently update screen content and invoke
  // any user-defined callbacks for requested events
  man->draw();
}

// -------------------------------------------------------- private functions --

void initGPIO(void)
{
#if DEFINED_VAL(TFT_RST_PIN)
  // TFT reset is active low, i'm choosing to keep it high with a digital pin
  // instead of a fixed pullup so that we can actually reset it if needed.
  pinMode(TFT_RST_PIN, OUTPUT);
  digitalWrite(TFT_RST_PIN, LOW);
  delay(100);
  digitalWrite(TFT_RST_PIN, HIGH);
#endif
}

void initPeripherals(void)
{

#ifdef WAIT_FOR_SERIAL
  while (!Serial) { continue; }
#else
  while (!Serial && millis() < 1000) { continue; }
#endif
  Serial.begin(115200);

  Serial.printf("creating panels (%u)", 2);

  // ---- MANAGER OBJECT ----

  // primary object containing and organizing all components
  man = new LayoutManager(
      // TFT
      TFT_CS_PIN, TFT_DC_PIN,
      // Touchscreen
      TOUCH_CS_PIN, TOUCH_IRQ_PIN,
      // Both
      320, 240, Orientation::Landscape, COLOR_BLACK);
  man->setTouchEnd(screenTouchEnd);

  // ---- PANEL 1 ----

  // add one panel to the first layer
  p1 = man->addPanel(
      0U,         // layer 0 (bottom-most)
      10U,  20U,  // origin, top-left (x,y) point
      120U, 120U, // size, width and height
      6U,         // radius of rounded corners of panel, 0 for none (square)
      COLOR_RED, COLOR_GREEN, // panel color, touched color
      6U,         // rounded corner radius of border, as above
      0,          // border margin, <0 outside panel, >0 inside panel
      COLOR_GREEN, COLOR_RED  // border color, touched color
  );

  p1->setAxis(LayoutAxis::Vertical);
  p1->setMargin(8U);
  p1->setPadding(8U);

  // set some callbacks
  p1->setTouchPress(p1_press);

  // ---- PANEL 1 FIELDS ----

  p1f1 = man->addField(
      p1,     // parent panel
      "p1f1", // field text
      1U,     // text size
      COLOR_WHITE, COLOR_NAVY, // text color, touched color
      6U,     // rounded corner radius of border, 0 for none (square)
      COLOR_NAVY, COLOR_WHITE  // panel color, touched color
  );
  p1f2 = man->addField(
      p1,     // parent panel
      "p1f2", // field text
      3U,     // text size
      COLOR_NAVY, COLOR_ORANGE, // text color, touched color
      6U,     // rounded corner radius of border, 0 for none (square)
      COLOR_ORANGE, COLOR_NAVY, // panel color, touched color
      3U,     // rounded corner radius of border, as above
      3,      // border margin, <0 outside panel, >0 inside panel
      COLOR_NAVY, COLOR_ORANGE  // border color, touched color
  );

  p1f1->setTouchBegin(p1f1_begin);
  p1f1->setTouchEnd(p1f1_end);
  p1f1->setTouchPress(p1f1_press);

  // ---- PANEL 2 ----

  p2 = man->addPanel(
      0U,          // layer
      20U, 160U,   // origin, top-left (x,y) point
      200U, 40U,   // size, width and height
      8U,          // radius of rounded corners of panel, 0 for none (square)
      COLOR_GREEN, // panel color,
      8U,          // rounded corner radius of border, as above
      0,           // border margin, <0 outside panel, >0 inside panel
      COLOR_RED    // border color
  );

  p2->setAxis(LayoutAxis::Horizontal);
  p2->setMargin(2U);
  p2->setPadding(2U);

  // set some callbacks
  p2->setTouchPress(p2_press);

  // ---- PANEL 2 FIELDS ----

  p2f1 = man->addField(
      p2,     // parent panel
      "p2f1", // field text
      2U,     // text size
      COLOR_WHITE, COLOR_NAVY, // text color, touched color
      6U,     // rounded corner radius of border, 0 for none (square)
      COLOR_NAVY, COLOR_WHITE  // panel color, touched color
  );
  p2f2 = man->addField(
      p2,     // parent panel
      "p2f2", // field text
      1U,     // text size
      COLOR_NAVY, COLOR_ORANGE, // text color, touched color
      6U,     // rounded corner radius of border, 0 for none (square)
      COLOR_ORANGE, COLOR_NAVY, // panel color, touched color
      3U,     // rounded corner radius of border, as above
      -3,     // border margin, <0 outside panel, >0 inside panel
      COLOR_NAVY, COLOR_ORANGE  // border color, touched color
  );
  p2f3 = man->addField(
      p2,     // parent panel
      "p2f3", // field text
      1U,     // text size
      COLOR_NAVY, COLOR_ORANGE, // text color, touched color
      8U,     // rounded corner radius of border, 0 for none (square)
      COLOR_GREEN, COLOR_RED,   // panel color, touched color
      3U,     // rounded corner radius of border, as above
      4,     // border margin, <0 outside panel, >0 inside panel
      COLOR_NAVY, COLOR_ORANGE  // border color, touched color
  );
}

void p1_press(Frame const &f, Touch const &t)
{
  Serial.printf("p1_press {%u,%u}", t.x(), t.y());
}

void p2_press(Frame const &f, Touch const &t)
{
  Serial.printf("p2_press {%u,%u}", t.x(), t.y());
}

void p1f1_begin(Frame const &f, Touch const &t)
{
  Serial.printf("p1f1_begin: {%u,%u}", t.x(), t.y());
}

void p1f1_end(Frame const &f, Touch const &t)
{
  Serial.printf("p1f1_end: {%u,%u}", t.x(), t.y());
}

void p1f1_press(Frame const &f, Touch const &t)
{
  Serial.printf("p1f1_press: {%u,%u}", t.x(), t.y());
}

void screenTouchEnd(Screen const &s, Touch const &t)
{
  if (t.x() > 280) {
    Serial.printf("screen({%u,%u}, %u): adding new layer\n", t.x(), t.y(), t.pressure());
    // if we touch the far-right of the screen, add a panel to a new layer
    uint8_t index = man->layerIndexTop() + 1U;
    man->addPanel(
        index,
        20U + index * 20,
        20U + index * 10,
        75U, 20U,
        0U,
        COLOR_WHITE,
        0U,
        -6,
        COLOR_PURPLE
    );
  }
  else {
    Serial.printf("screen({%u,%u}, %u): removing top layer\n", t.x(), t.y(), t.pressure());
    // otherwise, we touched somewhere to the left, remove the top-most layer
    man->layerRemoveTop();
  }
}
