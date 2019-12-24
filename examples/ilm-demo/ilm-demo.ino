/*******************************************************************************
 *
 *  name: ilm-demo.ino
 *  date: Dec 13, 2019
 *  auth: andrew
 *  desc:
 *
 ******************************************************************************/

// ----------------------------------------------------------------- includes --

#include <LayoutManager.h>

// ---------------------------------------------------------- private defines --

#define __WAIT_FOR_SERIAL__

// Grand Central M4
#define __GPIO_NEOPIXEL_PIN__ 88

// TFT / Touchscreen
#define __GPIO_TFT_VCC_PIN__    /* 3v3 */
#define __GPIO_TFT_GND_PIN__    /* GND */
#define __GPIO_TFT_CS_PIN__          7
#define __GPIO_TFT_RST_PIN__         6
#define __GPIO_TFT_DC_PIN__          5
#define __GPIO_TFT_MOSI_PIN__       51
#define __GPIO_TFT_SCK_PIN__        52
#define __GPIO_TFT_LED_PIN__    /* 3v3 */
#define __GPIO_TFT_MISO_PIN__       50
#define __GPIO_TOUCH_CLK_PIN__      52
#define __GPIO_TOUCH_CS_PIN__        4
#define __GPIO_TOUCH_MOSI_PIN__     51
#define __GPIO_TOUCH_MISO_PIN__     50
#define __GPIO_TOUCH_IRQ_PIN__       3

// ----------------------------------------------------------- private macros --

/* nothing */

// ------------------------------------------------------------ private types --

/* nothing */

// ------------------------------------------------------- exported variables --

LayoutManager *man;

// -------------------------------------------------------- private variables --

/* nothing */

// ---------------------------------------------- private function prototypes --

void initGPIO(void);
void initPeripherals(void);

// ------------------------------------------------------- exported functions --

void setup()
{
  initGPIO();
  initPeripherals();
}

void loop()
{
  man->draw();
}

// -------------------------------------------------------- private functions --

void initGPIO(void)
{
  pinMode(__GPIO_TFT_CS_PIN__, OUTPUT);
  pinMode(__GPIO_TFT_RST_PIN__, OUTPUT);
  pinMode(__GPIO_TFT_DC_PIN__, OUTPUT);
  pinMode(__GPIO_TFT_MOSI_PIN__, OUTPUT);
  pinMode(__GPIO_TFT_SCK_PIN__, OUTPUT);
  pinMode(__GPIO_TFT_MISO_PIN__, INPUT);
  pinMode(__GPIO_TOUCH_CLK_PIN__, OUTPUT);
  pinMode(__GPIO_TOUCH_CS_PIN__, OUTPUT);
  pinMode(__GPIO_TOUCH_MOSI_PIN__, OUTPUT);
  pinMode(__GPIO_TOUCH_MISO_PIN__, INPUT);
  pinMode(__GPIO_TOUCH_IRQ_PIN__, INPUT);
}

void initPeripherals(void)
{
  man = new LayoutManager(
    __GPIO_TFT_CS_PIN__, __GPIO_TFT_DC_PIN__,
    __GPIO_TOUCH_CS_PIN__, __GPIO_TOUCH_IRQ_PIN__,
    320, 240,
    soLandscape);

  if (!man->begin()) {
    Serial.println("failed to start!");
  }
  else {
    Serial.println("all ok");
  }
}