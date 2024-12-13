#include <Arduino.h>
#include <avr/pgmspace.h>
#include "Ticker.h"
#include <Servo.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <PololuBuzzer.h>

#include "Bitmaps.h"

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
// The pins for I2C are defined by the Wire-library.
// On an arduino UNO:       A4(SDA), A5(SCL)
// On an arduino MEGA 2560: 20(SDA), 21(SCL)
// On an arduino LEONARDO:   2(SDA),  3(SCL), ...
#define OLED_RESET -1       // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32

#define RED_PIN 11
#define GREEN_PIN 5
#define BLUE_PIN 6

#define TRAPDOOR_PIN 8
#define TRAPDOOR_OPEN_POS 0
#define TRAPDOOR_CLOSE_POS 90
#define SIDEDOOR_PIN 7
#define SIDEDOOR_OPEN_POS 90
#define SIDEDOOR_CLOSE_POS 10

#define BUTTON_SWITCH_PIN 2
#define BUTTON_LED_PIN 4
#define POTMETER_1_PIN A0
#define POTMETER_2_PIN A1

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
PololuBuzzer buzzer;
Servo trapdoorServo;
Servo sidepanelServo;

typedef struct St_color
{
  uint8_t red;
  uint8_t green;
  uint8_t blue;
} t_color;

typedef struct St_tone
{
  uint16_t frequency;
  uint16_t duration;
  uint8_t volume;
} t_tone;

typedef struct t_sequenceData
{
  uint16_t timeToNext;
  uint8_t setColor;
  t_color ledStripColor;
  uint8_t setTone;
  t_tone buzzerTone;
  uint8_t setDisplay;
  uint8_t displayPage;
} t_sequenceData;

typedef struct St_progressBar
{
  uint8_t x;
  uint8_t y;
  uint8_t w;
  uint8_t h;
  uint8_t progress;
} t_progressBar;

typedef struct St_targetSlider
{
  uint8_t x;
  uint8_t y;
  uint8_t w;
  uint8_t h;
  uint8_t windowWidth;
  uint8_t targetPos;
  uint8_t windowPos;
  uint8_t onTarget;
} t_targetSlider;

t_progressBar loadingBar1 = {.x = 2, .y = 34, .w = 124, .h = 28, .progress = 0};
t_targetSlider slider1 = {.x = 2, .y = 18, .w = 80, .h = 15, .windowWidth = 7, .targetPos = 0, .windowPos = 64};
t_targetSlider slider2 = {.x = 2, .y = 48, .w = 80, .h = 15, .windowWidth = 7, .targetPos = 0, .windowPos = 64};


void updateInputs();
void updateDisplay();
void sequenceRunner();

// Ticker inputTimer(updateInputs, 100);
// Ticker displayTimer(updateDisplay, 100);

void displayAsmlLogo();
void drawAsmlLogo(uint8_t y = 0);
void drawHorProgressBar(t_progressBar bar);
void updateHorProgressBar(t_progressBar bar);
void drawAsmlLoadingScreen(uint8_t progress);
void drawTargetSlider(t_targetSlider slider);
void updateTargetSlider(t_targetSlider slider);
void drawWafer(uint8_t x, uint8_t y, uint8_t index);

void openTrapdoor();
void closeTrapdoor();
void openSidedoor();
void closeSidedoor();
void startSequence(const t_sequenceData sequence[], uint8_t elements);
void startSequenceRec(const t_sequenceData sequence[], uint8_t index);
void setSequenceOutputs(t_sequenceData sequence);
void playTone(t_tone tone);
void setLedColor(t_color color);


uint8_t isSequenceRunning();

const PROGMEM t_color black = {0, 0, 0};
// const PROGMEM t_color red = {255, 0, 0};

const PROGMEM t_color green = {0, 128, 0};
const PROGMEM t_color blue = {0, 0, 128};
const PROGMEM t_color purple = {255, 0, 255};
const PROGMEM t_color yellow = {255, 128, 0};
const PROGMEM t_color orange = {255, 80, 0};
const PROGMEM t_color white = {255, 255, 255};

// const PROGMEM t_tone noBeep = {0, 0, 0};
// const PROGMEM t_tone startupBeep = {1760, 100, 15};
// const PROGMEM t_tone startupBeep2 = {1976, 100, 15};
// const PROGMEM t_tone startupBeep3 = {2349, 100, 15};

const PROGMEM t_tone waferPrepBeep = {1200, 400, 15};

const PROGMEM t_tone lithographyBeep = {4000, 80, 15};
const PROGMEM t_tone lithographyBeep2 = {5000, 80, 15};

const PROGMEM t_tone bootBeep = {1760, 100, 15};

uint8_t switchState = false;
uint8_t buttonLedState = false;
uint8_t pot1State = 0;
uint8_t pot2State = 0;

// char inputMessage[128] = "";

// const t_sequenceData startupSequenceEnd = {200, true, black, false, noBeep, false, 0};
// const t_sequenceData startupSequence5 = {200, true, blue, true, startupBeep3, false, 0};
// const t_sequenceData startupSequence4 = {200, true, blue, true, startupBeep3, false, 0};
// const t_sequenceData startupSequence3 = {200, true, blue, true, startupBeep3, false, 0};
// const t_sequenceData startupSequence2 = {120, true, green, true, startupBeep2, false, 0};
// const t_sequenceData startupSequence1 = {200, true, red, true, startupBeep, false, 0};

const t_sequenceData waferPrepSequenceArray[] = {
    {.timeToNext = 500, .setColor = true, .ledStripColor = yellow, .setTone = true, .buzzerTone = waferPrepBeep},
    {.timeToNext = 500, .setColor = true, .ledStripColor = orange, .setTone = false,}
};

const t_sequenceData lithographySequenceArray[] = {
    {.timeToNext = 20, .setColor = true, .ledStripColor = white, .setTone = true, .buzzerTone = lithographyBeep},
    {.timeToNext = 180, .setColor = true, .ledStripColor = black, .setTone = false},
    {.timeToNext = 200, .setColor = true, .ledStripColor = purple, .setTone = true, .buzzerTone = lithographyBeep2}};

const t_sequenceData chipOutputSequenceArray[] = {
    {.timeToNext = 100, .setColor = true, .ledStripColor = purple, .setTone = true, .buzzerTone = bootBeep},
    {.timeToNext = 400, .setColor = true, .ledStripColor = yellow, .setTone = false}};

t_sequenceData *currentSequence = NULL;
uint8_t currentSequenceIndex = 0;
uint8_t maxSequenceIndex;
uint32_t sequenceMillis = millis();

enum E_machineState
{
  UNKNOWN,
  INIT,
  PREPARE_STARTUP,
  PREPARE_OPEN_DOORS,
  PREPARE_OPEN_DOORS_TRANSITION,
  PREPARE_CLOSE_TRAPDOOR,
  PREPARE_CLOSE_TRAPDOOR_TRANSITION,
  PREPARE_CLOSE_SIDEDOOR,
  PREPARE_CLOSE_SIDEDOOR_TRANSITION,
  BOOTSCREEN,
  BOOTSCREEN_DELAY,
  LOADINGSCREEN,
  WELCOMESCREEN,
  WELCOMESCREEN_TRANSITION,
  LENS_ALIGNMENT,
  COLUMNNATOR_SETPOINT,
  CALIBRATION_TRANSITION,
  PRODUCTION_READY,
  PRODUCTION_READY_TRANSITION,
  PREPARING_WAFERS,
  PREPARING_WAFERS_TRANSITION,
  LITHOGRAPHY,
  CHIP_OUTPUT,
  PRODUCTION_FINISHED,
  PRODUCTION_FINISHED_TRANSITION
};

enum E_machineState currentState = INIT;

enum E_displayState
{
  SCREEN_CLEAR,
  SCREEN_ASML_LOGO,
  SCREEN_ASML_LOGO_LOADING,
  SCREEN_WELCOMESCREEN,
  SCREEN_LENS_ALIGNMENT,
  SCREEN_LENS_ALIGNMENT_2,
  SCREEN_STARTING_PRODUCTION,
  SCREEN_PRODUCTION,
  SCREEN_PREPARING_WAFERS,
  SCREEN_LITHOGRAPHY,
  SCREEN_PRODUCTION_FINISHED
};

enum E_displayState currentDisplayState = SCREEN_CLEAR;

void setup()
{
  Serial.begin(115200);
  trapdoorServo.attach(TRAPDOOR_PIN);
  closeTrapdoor();
  sidepanelServo.attach(SIDEDOOR_PIN);
  closeSidedoor();
  pinMode(RED_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
  pinMode(BLUE_PIN, OUTPUT);
  pinMode(BUTTON_LED_PIN, OUTPUT);
  pinMode(BUTTON_SWITCH_PIN, INPUT);
  setLedColor(black);

  if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS))
  {

    Serial.println(F("SSD1306 allocation failed"));
    buzzer.playFrequency(440, 1000, 15);
    delay(1000);
    for (;;)
      ; // Don't proceed, loop forever
  }
  Wire.setClock(400000UL);
  display.clearDisplay();
  display.display();

  // display.setTextSize(1);              // Normal 1:1 pixel scale
  // display.setTextColor(SSD1306_WHITE); // Draw white text
  // display.setCursor(0, 0);             // Start at top-left corner
  // display.display();
  delay(5000);

  // inputTimer.start();
  // displayTimer.start();

  updateInputs();
  updateDisplay();
}

void loop()
{
  static enum E_machineState lastState = UNKNOWN;
  if (currentState != lastState)
  {
    lastState = currentState;
    char newStateStr[20] = "";
    snprintf(newStateStr, sizeof(newStateStr) - 1, "New state: %u\r\n", currentState);
    Serial.print(newStateStr);
  }

  static uint32_t displayTime = millis();
  if (millis() >= displayTime + 100)
  {
    displayTime = millis();
    updateDisplay();
  }
  

  updateInputs();
  // inputTimer.update();
  // displayTimer.update();
  sequenceRunner();

  static uint32_t stateDelayTime = millis();
  static uint16_t incrementCounter = 0;
  switch (currentState)
  {
  case INIT:
  {
    currentDisplayState = SCREEN_ASML_LOGO;
    if (switchState)
    {
      currentState = PREPARE_OPEN_DOORS;
    }
    else
    {
      currentState = BOOTSCREEN;
    }
  }

  break;
  case PREPARE_OPEN_DOORS:

  {
    if (switchState)
    {
      openTrapdoor();
      openSidedoor();
      currentState = PREPARE_OPEN_DOORS_TRANSITION;
    }
  }
  break;
  case PREPARE_OPEN_DOORS_TRANSITION:
  {
    if (!switchState)
    {
      currentState = PREPARE_CLOSE_TRAPDOOR;
    }
  }
  break;
  case PREPARE_CLOSE_TRAPDOOR:

  {
    if (switchState)
    {
      closeTrapdoor();
      currentState = PREPARE_CLOSE_TRAPDOOR_TRANSITION;
    }
  }
  break;
  case PREPARE_CLOSE_TRAPDOOR_TRANSITION:
  {
    if (!switchState)
    {
      currentState = PREPARE_CLOSE_SIDEDOOR;
    }
  }
  break;
  case PREPARE_CLOSE_SIDEDOOR:

  {
    if (switchState)
    {
      closeSidedoor();
      currentState = PREPARE_CLOSE_SIDEDOOR_TRANSITION;
    }
  }
  break;
  case PREPARE_CLOSE_SIDEDOOR_TRANSITION:
  {
    if (!switchState)
    {
      currentState = INIT;
    }
  }
  break;
  case BOOTSCREEN:
  {
    currentDisplayState = SCREEN_ASML_LOGO;
    playTone(bootBeep);
    stateDelayTime = millis();
    currentState = BOOTSCREEN_DELAY;
  }
  break;
  case BOOTSCREEN_DELAY:
  {
    if (millis() > stateDelayTime + 2000)
    {
      stateDelayTime = millis();
      
      currentState = LOADINGSCREEN;
      // currentState = PREPARING_WAFERS;
    }
  }
  break;
  case LOADINGSCREEN:
  {
    currentDisplayState = SCREEN_ASML_LOGO_LOADING;
    uint32_t progress = stateDelayTime + 10000 - millis();    
    progress = map(progress, 10000, 0, 0, 255);
    loadingBar1.progress = progress;
    if (millis() > stateDelayTime + 10000)
    {
      playTone(bootBeep);
      currentState = WELCOMESCREEN;
    }
  }
  break;

  case WELCOMESCREEN:
  {
    currentDisplayState = SCREEN_WELCOMESCREEN;
    if (switchState)
    {
      currentState = WELCOMESCREEN_TRANSITION;
    }
  }
  break;
  case WELCOMESCREEN_TRANSITION:
  {
    if (!switchState)
    {
      currentState = LENS_ALIGNMENT;
    }
  }
  break;
  case LENS_ALIGNMENT:
  {
    slider1.windowPos = 80;
    slider2.windowPos = 130;
    slider1.targetPos = pot1State;
    slider2.targetPos = pot2State;
    Serial.print(F("pot1: "));
    Serial.print(slider1.targetPos);
    Serial.print(F(" pot2: "));
    Serial.println(slider2.targetPos);
    currentDisplayState = SCREEN_LENS_ALIGNMENT;
    if (slider1.targetPos > slider1.windowPos - 2 && slider1.targetPos < slider1.windowPos + 2)
    {
      slider1.onTarget = true;
    }
    else
    {
      slider1.onTarget = false;
    }
    if (slider2.targetPos > slider2.windowPos - 2 && slider2.targetPos < slider2.windowPos + 2)
    {
      slider2.onTarget = true;
    }
    else
    {
      slider2.onTarget = false;
    }

    if (slider1.onTarget && slider2.onTarget && switchState)
    {
      currentState = COLUMNNATOR_SETPOINT;
    }
  }
  break;
  case COLUMNNATOR_SETPOINT:
  {
    slider1.windowPos = 200;
    slider2.windowPos = 60;
    slider1.targetPos = pot1State;
    slider2.targetPos = pot2State;
    Serial.print(F("pot1: "));
    Serial.print(slider1.targetPos);
    Serial.print(F(" pot2: "));
    Serial.println(slider2.targetPos);
    currentDisplayState = SCREEN_LENS_ALIGNMENT_2;
    if (slider1.targetPos > slider1.windowPos - 2 && slider1.targetPos < slider1.windowPos + 2)
    {
      slider1.onTarget = true;
    }
    else
    {
      slider1.onTarget = false;
    }
    if (slider2.targetPos > slider2.windowPos - 2 && slider2.targetPos < slider2.windowPos + 2)
    {
      slider2.onTarget = true;
    }
    else
    {
      slider2.onTarget = false;
    }
    if (slider1.onTarget && slider2.onTarget && switchState)
    {
      currentState = CALIBRATION_TRANSITION;
    }
  }
  break;
  case CALIBRATION_TRANSITION:
  {

    if (!switchState)
    {
      currentState = PRODUCTION_READY;
    }
  }
  break;
  case PRODUCTION_READY:
  {
    currentDisplayState = SCREEN_STARTING_PRODUCTION;
    if (switchState)
    {
      openSidedoor();
      setLedColor(blue);
      currentState = PRODUCTION_READY_TRANSITION;
    }
  }
  break;
  case PRODUCTION_READY_TRANSITION:
  {
    
    if (!switchState)
    {
      currentState = PREPARING_WAFERS;
    }
  }
  break;
  case PREPARING_WAFERS:
  {
    stateDelayTime = millis();
    currentDisplayState = SCREEN_PREPARING_WAFERS;
    
      currentState = PREPARING_WAFERS_TRANSITION;
  }
  break;
  case PREPARING_WAFERS_TRANSITION:
  {
    if (!isSequenceRunning())
    {
      startSequence(waferPrepSequenceArray, sizeof(waferPrepSequenceArray)/sizeof(waferPrepSequenceArray[0]));
    }
    
    if (millis() > stateDelayTime + 10000)
    {
      stateDelayTime = millis();
      currentState = LITHOGRAPHY;
    }
  }
  break;
  case LITHOGRAPHY:
  { // sequence
    currentDisplayState = SCREEN_LITHOGRAPHY;
    if (!isSequenceRunning())
    {
      startSequence(lithographySequenceArray, sizeof(lithographySequenceArray)/sizeof(lithographySequenceArray[0]));
    }
    
    if (millis() > stateDelayTime + 5000)
    {
      openTrapdoor();
      stateDelayTime = millis();
      currentState = CHIP_OUTPUT;
    }

    // if (!isSequenceRunning() && incrementCounter < 20)
    // {
    //   startSequence(lithographySequenceArray, sizeof(lithographySequenceArray)/sizeof(lithographySequenceArray[0]));
    //   incrementCounter++;
    // }    
    // else if (!isSequenceRunning())
    // {
    //   openTrapdoor();
    //   incrementCounter = 0;
    //   stateDelayTime = millis();
    //   currentState = CHIP_OUTPUT;
    // }
  }
  break;
  case CHIP_OUTPUT:
  { // sequence
    if (!isSequenceRunning())
    {
      startSequence(chipOutputSequenceArray, sizeof(chipOutputSequenceArray)/sizeof(chipOutputSequenceArray[0]));
    }
    
    if (millis() > stateDelayTime + 2000)
    {
      setLedColor(green);
      stateDelayTime = millis();
      currentState = PRODUCTION_FINISHED;
    }

    // if (!isSequenceRunning() && incrementCounter < 20)
    // {
    //   startSequence(chipOutputSequenceArray, sizeof(chipOutputSequenceArray)/sizeof(chipOutputSequenceArray[0]));
    //   incrementCounter++;
    // }    
    // else if (!isSequenceRunning())
    // {
    //   incrementCounter = 0;
    //   stateDelayTime = millis();
    //   currentState = PRODUCTION_FINISHED;
    // }
  }
  break;
  case PRODUCTION_FINISHED:
  {
    
    currentDisplayState = SCREEN_PRODUCTION_FINISHED;
    if (switchState)
    {
      currentState = PRODUCTION_FINISHED_TRANSITION;
    }
  }
  break;
  case PRODUCTION_FINISHED_TRANSITION:
  {
    if (!switchState)
    {
      currentState = INIT;
    }
  }
  break;

  default:
  {
    currentState = INIT;
  }
  break;
  }
  delay(10);
}

void openTrapdoor()
{
  trapdoorServo.write(TRAPDOOR_OPEN_POS);
}

void closeTrapdoor()
{
  trapdoorServo.write(TRAPDOOR_CLOSE_POS);
}

void openSidedoor()
{
  sidepanelServo.write(SIDEDOOR_OPEN_POS);
}

void closeSidedoor()
{
  sidepanelServo.write(SIDEDOOR_CLOSE_POS);
}

void updateInputs()
{
  switchState = !digitalRead(BUTTON_SWITCH_PIN);
  uint16_t potVal = analogRead(POTMETER_1_PIN);
  potVal = potVal / 4;
  pot1State = (uint8_t)potVal;
  potVal = analogRead(POTMETER_2_PIN);
  potVal = potVal / 4;
  pot2State = (uint8_t)potVal;
  buttonLedState = switchState;
  digitalWrite(BUTTON_LED_PIN, buttonLedState);
}

void updateDisplay()
{
  static uint8_t updateScreen = true;
  static enum E_displayState lastDisplayState = SCREEN_CLEAR;
  static uint32_t AnimationTime = millis();
  static uint8_t AnimationIndex = 0;
  if (currentDisplayState != lastDisplayState)
  {
    Serial.print(F("New screenState:"));
    Serial.println(currentDisplayState);
    lastDisplayState = currentDisplayState;
    updateScreen = true;
  }

  if (updateScreen)
  {
    updateScreen = false;
    switch (currentDisplayState)
    {
    case SCREEN_CLEAR:
      display.clearDisplay();
      display.display();
      break;
    case SCREEN_ASML_LOGO:
      displayAsmlLogo();
      break;
    case SCREEN_ASML_LOGO_LOADING:
      display.clearDisplay();
      drawAsmlLogo();
      drawHorProgressBar(loadingBar1);
      display.display();
      break;
    case SCREEN_WELCOMESCREEN:
      display.clearDisplay();
      display.setTextSize(2);
      display.setTextColor(SSD1306_WHITE);
      display.setCursor(2, 2);
      display.println(F("WELCOME"));
      display.setTextSize(1);
      display.println(F("Press the button"));
      display.println(F("to start machine"));
      display.println(F("initialization"));
      display.display();
      break;
    case SCREEN_LENS_ALIGNMENT:
      display.clearDisplay();
      display.setTextSize(1);
      display.setTextColor(SSD1306_WHITE);
      display.setCursor(2, 0);
      display.println(F("Align Laser"));
      display.setCursor(slider1.x, slider1.y-10);
      display.println(F("Mirror Alignment X:"));
      display.setCursor(slider2.x, slider2.y-10);
      display.println(F("Mirror Alignment Y:"));
      slider1.windowPos = 64;
      slider2.windowPos = 188;
      drawTargetSlider(slider1);
      drawTargetSlider(slider2);
      display.display();
      break;
    case SCREEN_LENS_ALIGNMENT_2:
      display.clearDisplay();
      display.setTextSize(1);
      display.setTextColor(SSD1306_WHITE);
      display.setCursor(2, 0);
      display.println(F("Configure Laser"));
      display.setCursor(slider1.x, slider1.y-10);
      display.println(F("Focus position:"));
      display.setCursor(slider2.x, slider2.y-10);
      display.println(F("Magnification factor:"));
      slider1.windowPos = 130;
      slider2.windowPos = 22;
      drawTargetSlider(slider1);
      drawTargetSlider(slider2);
      display.display();
      break;
    case SCREEN_STARTING_PRODUCTION:
      display.clearDisplay();
      display.setTextSize(2);
      display.setTextColor(SSD1306_WHITE);
      display.setCursor(2, 2);
      display.println(F("Setup"));
      display.println(F("complete"));
      display.setTextSize(1);
      display.println(F(""));
      display.println(F("Press button to"));
      display.println(F("start production"));
      display.display();
      break;
    case SCREEN_PRODUCTION:
      display.clearDisplay();
      display.setTextSize(2);
      display.setTextColor(SSD1306_WHITE);
      display.setCursor(2, 2);
      display.println(F("Production...."));
      display.display();
      break;
    case SCREEN_PREPARING_WAFERS:
      display.clearDisplay();
      display.setTextSize(2);
      display.setTextColor(SSD1306_WHITE);
      display.setCursor(0, 0);
      display.println(F("Stroop"));
      display.println(F("Wafer"));
      display.println(F(""));
      display.println(F("Prepping"));
      drawWafer(78, 0, 0);
      display.display();
      break;
    case SCREEN_LITHOGRAPHY:
      display.clearDisplay();
      display.setTextSize(2);
      display.setTextColor(SSD1306_WHITE);
      display.setCursor(34, 0);
      display.println(F("Laser"));
      display.setCursor(28, 18);
      display.println(F("Etching"));
      display.setCursor(34, 36);
      display.println(F("Chips"));
      display.display();
      break;
    case SCREEN_PRODUCTION_FINISHED:
      display.clearDisplay();
      display.setTextSize(2);
      display.setTextColor(SSD1306_WHITE);
      display.setCursor(32, 5);
      display.println(F("done!"));
      display.drawXBitmap(44, 22, doneCheckMark, 40, 40, SSD1306_WHITE);
      display.display();
      break;
    default:
      break;
    }
    AnimationIndex = 0;
  }

  // changing variables for partial updates
  static uint8_t lastLoading1State;
  if (currentDisplayState == SCREEN_ASML_LOGO_LOADING && loadingBar1.progress != lastLoading1State)
  {
    lastLoading1State = loadingBar1.progress;
    updateHorProgressBar(loadingBar1);
    display.display();
  }

  static uint8_t lastSliderState1;
  static uint8_t lastSliderState2;
  if ((currentDisplayState == SCREEN_LENS_ALIGNMENT || currentDisplayState == SCREEN_LENS_ALIGNMENT_2) && (slider1.targetPos != lastSliderState1 || slider2.targetPos != lastSliderState2))
  {
    lastSliderState1 = slider1.targetPos;
    lastSliderState2 = slider2.targetPos;
    updateTargetSlider(slider1);
    updateTargetSlider(slider2);
    display.fillRect(slider1.x + slider1.w + 2,slider1.y + 2,128-slider1.x + slider1.w + 2, slider1.h, SSD1306_BLACK);
    display.fillRect(slider2.x + slider2.w + 2,slider2.y + 2,128-slider2.x + slider2.w + 2, slider2.h, SSD1306_BLACK);
    display.setTextSize(2);
    display.setCursor(slider1.x + slider1.w + 2, slider1.y + 2);
    if (slider1.onTarget) display.println(F("OK"));
    else display.println(F("NOK"));
    display.setCursor(slider2.x + slider2.w + 2, slider2.y + 2);
    if (slider2.onTarget) display.println(F("OK"));
    else display.println(F("NOK"));
    
    
    display.display();
  }

  //wafer rotation animation
  if (currentDisplayState == SCREEN_PREPARING_WAFERS && millis() > AnimationTime + 200)
  {
    AnimationTime = millis();
    drawWafer(78, 0, AnimationIndex);
    display.display();
    AnimationIndex ++;
    if (AnimationIndex >= sizeof(waferBitmapArray)/sizeof(waferBitmapArray[0]))
    {
      AnimationIndex = 0;
    }
  }

  //production done checkmark
  if (currentDisplayState == SCREEN_PRODUCTION_FINISHED && millis() > AnimationTime + 2000)
  {
    AnimationTime = millis();
    switch (AnimationIndex)
    {
    case 0:
      display.clearDisplay();
      display.setCursor(32, 5);
      display.println(F("Done!"));
      display.drawXBitmap(44, 22, doneCheckMark, 40, 40, SSD1306_WHITE);
      break;
    case 1:
    case 3:
    case 5:
    display.clearDisplay();
      display.setCursor(4, 5);
      display.println(F("check SWOD"));
      display.drawXBitmap(44, 22, outputArrow, 40, 40, SSD1306_WHITE);
      break;
    case 2:
    case 4:
    case 6:
    display.clearDisplay();
      display.setCursor(4, 5);
      display.println(F("check SWOD"));
      display.drawXBitmap(44, 22, outputBasic, 40, 40, SSD1306_WHITE);
      break;
    
    default:
      AnimationIndex = 0;
      break;
    }
    AnimationIndex ++;
    if (AnimationIndex > 6)
    {
      AnimationIndex = 0;
    }
    display.display();    
    
  }

}

void playTone(t_tone tone)
{
  buzzer.playFrequency(tone.frequency, tone.duration, tone.volume);
}

void setLedColor(t_color color)
{
  analogWrite(RED_PIN, color.red);
  analogWrite(GREEN_PIN, color.green);
  analogWrite(BLUE_PIN, color.blue);
}

void startSequence(const t_sequenceData sequence[], uint8_t elements)
{
  if (isSequenceRunning())
    return;
  currentSequence = (t_sequenceData *)sequence;
  maxSequenceIndex = elements;
  startSequenceRec(sequence, 0);
}

void startSequenceRec(const t_sequenceData sequence[], uint8_t index)
{
  setSequenceOutputs(sequence[currentSequenceIndex]);
  
  if (currentSequenceIndex < maxSequenceIndex)
  {
    currentSequenceIndex++;
    sequenceMillis = millis() + sequence->timeToNext;
  }
  else
  {
    currentSequence = NULL;
    currentSequenceIndex = 0;
  }
}

void sequenceRunner()
{
  if (currentSequence != NULL)
  {
    if (millis() >= sequenceMillis)
    {
      startSequenceRec(currentSequence, currentSequenceIndex);
    }
  }
}

void setSequenceOutputs(t_sequenceData sequence)
{
  if (sequence.setColor)
  {
    setLedColor(sequence.ledStripColor);
  }
  if (sequence.setTone)
  {
    playTone(sequence.buzzerTone);
  }
}

uint8_t isSequenceRunning()
{
  return currentSequence != NULL;
}

void displayAsmlLogo()
{
  display.clearDisplay();
  drawAsmlLogo();
  display.display();
}

void drawAsmlLogo(uint8_t y = 0)
{
  display.drawXBitmap(0, y, asmlLogo, 128, 32, SSD1306_WHITE);
}

void drawWafer(uint8_t x, uint8_t y, uint8_t index)
{
  display.fillRect(x, y, 50, 50, SSD1306_BLACK);
  display.drawXBitmap(x, y, waferBitmapArray[index], 50, 50, SSD1306_WHITE);
}

void drawHorProgressBar(t_progressBar bar)
{
  // clear used space
  display.fillRect(bar.x, bar.y, bar.w, bar.h, SSD1306_BLACK);
  // draw bounding rectangle
  display.drawRoundRect(bar.x, bar.y, bar.w, bar.h, 3, SSD1306_WHITE);
  // draw bar
  uint8_t barHeight = bar.h - 6;
  uint8_t barWidth = bar.w - 6;
  uint8_t filWidth = map(bar.progress, 0, 255, 0, barWidth);
  display.fillRect(bar.x + 3, bar.y + 3, filWidth, barHeight, SSD1306_WHITE);
}

void updateHorProgressBar(t_progressBar bar)
{
  uint8_t barHeight = bar.h - 6;
  uint8_t barWidth = bar.w - 6;
  uint8_t filWidth = map(bar.progress, 0, 255, 0, barWidth);
  display.fillRect(bar.x + 3, bar.y + 3, filWidth, barHeight, SSD1306_WHITE);
  display.fillRect(bar.x + 3 + filWidth, bar.y + 3, barWidth - filWidth, barHeight, SSD1306_BLACK);
}

void drawAsmlLoadingScreen(uint8_t progress)
{
  display.clearDisplay();
  drawAsmlLogo();
  drawHorProgressBar(loadingBar1);
}

void drawTargetSlider(t_targetSlider slider)
{
  // clear used space
  display.fillRect(slider.x, slider.y, slider.w, slider.h, SSD1306_BLACK);
  // draw bounding rectangle
  display.drawRoundRect(slider.x, slider.y, slider.w, slider.h, 3, SSD1306_WHITE);
  // draw window
  uint8_t barHeight = slider.h - 6;
  uint8_t barWidth = slider.w - 6;
  uint8_t windowStartPos = map(slider.windowPos, 0, 255, 0, barWidth - slider.windowWidth);
  display.drawRect(slider.x + 3 + windowStartPos, slider.y + 3, slider.windowWidth, barHeight, SSD1306_WHITE);
  // draw target
  uint8_t targetStartPos = map(slider.windowPos, 0, 255, 0, barWidth - 4);
  display.drawFastHLine(slider.x + 3 + targetStartPos, slider.y + 3 + barHeight / 2, 5, SSD1306_INVERSE);
  display.drawFastVLine(slider.x + 3 + 2 + targetStartPos, slider.y + 3 + barHeight / 2 - 2, 5, SSD1306_INVERSE);
}

void updateTargetSlider(t_targetSlider slider)
{

  // draw window
  uint8_t barHeight = slider.h - 6;
  uint8_t barWidth = slider.w - 6;
  // clear used space
  display.fillRect(slider.x + 3, slider.y + 3, barWidth, barHeight, SSD1306_BLACK);
  uint8_t windowStartPos = map(slider.windowPos, 0, 255, 0, barWidth - slider.windowWidth);
  display.drawRect(slider.x + 3 + windowStartPos, slider.y + 3, slider.windowWidth, barHeight, SSD1306_WHITE);
  // draw target
  uint8_t targetStartPos = map(slider.targetPos, 0, 255, 0, barWidth - 4);
  display.drawFastHLine(slider.x + 3 + targetStartPos, slider.y + 3 + barHeight / 2, 5, SSD1306_INVERSE);
  display.drawFastVLine(slider.x + 3 + 2 + targetStartPos, slider.y + 3 + barHeight / 2 - 2, 5, SSD1306_INVERSE);
}