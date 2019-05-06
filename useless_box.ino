/*
  MCU based "Ultimate machine" aka "Useless Box" aka "Leave me alone box"
  https://en.wikipedia.org/wiki/Useless_machine

  Works with Arduino or Open CM and for regular servos or smart servos
  Define OPEN_CM for Open CM 9.04 and define DYNAMIXEL_SERVOS for Dynamixel XL-320 smart servors
  Tested with Open CM 9.04 and with Arduino Nano V3
*/

#include "data.h"

#ifdef BOARD_CM904
  #define OPEN_CM
#endif

//#define DYNAMIXEL_SERVOS

#ifdef OPEN_CM
///////////// Pins definitions
  #define SWITCH_PIN 8 // Pin that supports internal pull-up connected to GND via switch 
  //Pins definitions //////////////
  #define LED_PIN BOARD_LED_PIN
  
  #define LOGLN(X) SerialUSB.println(X)
  #define LOG(X) SerialUSB.print(X)
#else //////// Arduino
///////////// Pins definitions
  #define SWITCH_PIN 3 //D3 // Pin that supports internal pull-up connected to GND via switch 
  //Pins definitions //////////////
  #define LED_PIN LED_BUILTIN
  
  #define LOGLN(X) Serial.println(X)
  #define LOG(X) Serial.print(X)
#endif //OPEN_CM

#ifdef DYNAMIXEL_SERVOS
  #define DXL_BUS_SERIAL1 1  //Dynamixel on Serial1(USART1)  <-OpenCM9.04
  Dynamixel Dxl(DXL_BUS_SERIAL1);
  
  #define ID_HAND_SERVO 1 //ID of the hand controlling XL-320 servo
  #define ID_COVER_SERVO 2 //ID of the cover controlling XL-320 servo
  
  #define MAP_POS(X) map(X, 0, 100, 0, 1023)
  #define MAP_SPEED(X) map(X, 0, 100, 0, 1023)
#else //////// Regular Servos
///////////// Pins definitions
  #define HAND_SERVO_PIN 5 //D5
  #define COVER_SERVO_PIN 9 //D9
  //Pins definitions //////////////
  
  #include <VarSpeedServo.h> 
  VarSpeedServo hand_servo;
  VarSpeedServo cover_servo;
  
  #define MAP_POS(X) map(X, 0, 100, 0, 180)
  #define MAP_SPEED(X) map(X, 0, 100, 0, 255)
#endif //DYNAMIXEL_SERVOS

///////////////////////////////////////////////////////
// Static variables
///////////////////////////////////////////////////////
static int previous_value = 1;
static boolean overrideSequenceIndex = false;
static int sequenceIndex = 0;
static String readString;

#define ENABLE_LOG // Uncomment to have log serial output 
//#define VERBOSE_LOG // Uncomment to have verbose log serial output, but be ware, it takes more than 1KB dynamic memory


#ifdef VERBOSE_LOG
  #define LOG_INFO LOG
  #define LOGLN_INFO LOGLN
#else
  #define LOG_INFO(...);
  #define LOGLN_INFO(...);
#endif // VERBOSE_LOG

#ifndef ENABLE_LOG
  #undef LOG
  #undef LOGLN
  #define LOG(...);
  #define LOGLN(...);
#endif
///////////////////////////////////////////////////////
// Setup
///////////////////////////////////////////////////////
void SetupServos()
{
#ifdef DYNAMIXEL_SERVOS
  Dxl.begin(3);

  Dxl.jointMode(ID_HAND_SERVO);
  Dxl.jointMode(ID_COVER_SERVO);

  Dxl.goalSpeed(ID_HAND_SERVO, 1023);
  Dxl.goalSpeed(ID_COVER_SERVO, 1023);

  // Cycle the colors of the servos, just because we can
  for (int color_id = 0; color_id <= 7; color_id++)
  {
    Dxl.ledOn(ID_HAND_SERVO, color_id);
    Dxl.ledOn(ID_COVER_SERVO, color_id + 1);
    delay(50);
    Dxl.ledOff(ID_HAND_SERVO);//All Dynamixel LED off
    Dxl.ledOff(ID_COVER_SERVO);//All Dynamixel LED off
    delay(50);
  }
#else
  hand_servo.attach(HAND_SERVO_PIN);
  cover_servo.attach(COVER_SERVO_PIN);

  cover_servo.write(MAP_POS(COVER_CLOSE_POS), MAP_SPEED(100), true);
  hand_servo.write(MAP_POS(HAND_CURTAIL_POS), MAP_SPEED(100), true);
#endif
}

///////////////////////////////////////////////////////
// Functions
///////////////////////////////////////////////////////
int GetSwitchValue()
{
  return digitalRead(SWITCH_PIN);  
}

///////////////////////////////////////////////////////
void ApplyAction(const Action& action)
{
  switch (action.type)
  {
    case CoverMotion: //////////////////////////////////////////////
      LOG_INFO("CoverMotion speed ");
      LOG_INFO(action.speed);
      LOG_INFO(" pos ");
      LOGLN_INFO(action.pos);
      
#ifdef DYNAMIXEL_SERVOS
      Dxl.goalSpeed(ID_COVER_SERVO, MAP(action.speed));
      Dxl.goalPosition(ID_COVER_SERVO, MAP(action.pos));
#else //////// Regular Servos
      cover_servo.write(MAP_POS(action.pos), MAP_SPEED(action.speed), false);
#endif
      break;
    case HandMotion: //////////////////////////////////////////////
      LOG_INFO("HandMotion speed ");
      LOG_INFO(action.speed);
      LOG_INFO(" pos ");
      LOGLN_INFO(action.pos);

#ifdef DYNAMIXEL_SERVOS
      Dxl.goalSpeed(ID_HAND_SERVO, MAP_SPEED(action.speed));
      Dxl.goalPosition(ID_HAND_SERVO, MAP_POS(action.pos));
#else //////// Regular Servos
      hand_servo.write(MAP_POS(action.pos), MAP_SPEED(action.speed), false);      
#endif
      break;
    case ColorLED: //////////////////////////////////////////////
      LOG_INFO("ColorLED color ");
      LOGLN_INFO(action.pos);
#ifdef DYNAMIXEL_SERVOS
      Dxl.ledOn(ID_HAND_SERVO, action.pos);
      Dxl.ledOn(ID_COVER_SERVO, action.pos);
#else //////// Regular Servos
      digitalWrite(LED_PIN, action.pos);
#endif
      break;
    case Wait: //////////////////////////////////////////////
      LOG_INFO("Wait for  ");
      LOG_INFO(action.pos*100);
      LOGLN_INFO(" ms");
      float delayChunk = (action.pos*100) / 20;    
      for (int i = 0; i < 20; i++)
      {
        if (previous_value == GetSwitchValue())
        {
          LOGLN("Abort delay");
          break;
        }
        else
        {
          delay(delayChunk);
        }
      }      
      break;
  }
}

///////////////////////////////////////////////////////
void SwitchValueChanged(int value)
{  
  if (!overrideSequenceIndex && sequenceIndex < NUM_SEQUENCES)
  {  
    // Pick a random sequence from the available onces, but only for the switch On, keep the same for the switch Off
    sequenceIndex = (value == LOW) ? random(0, NUM_SEQUENCES) : sequenceIndex;  
  }
  overrideSequenceIndex = false;
  
  LOG("Sequence selected with index ");
  LOGLN(sequenceIndex);
  
  Sequence const &seq = sequencesRepository[sequenceIndex];
  
  for (int i = 0; i < SEQUENCE_LENGTH_MAX; i++)
  {
    if (value != GetSwitchValue())
    {
      LOG("Switch was moved during sequence, abort sequence to run the next one");
      break;
    }
    
    byte actionIndex = seq.sequences[value][i]; // Low is 0, High is 1    
    
    if (actionIndex > 0)
    {      
      LOG_INFO("Running action ");
      LOGLN_INFO(actions_str[actionIndex]);
      ApplyAction(actionsRepository[actionIndex]);
    }
    else
    {
      LOG("Finish with sequence ");      
      LOG(sequenceIndex);
      LOGLN(value == HIGH ? " for closing!" : " for switching off!");  
      break;
    }
  }
}

///////////////////////////////////////////////////////
void CheckSwitchValue(int value)
{  
  if (value != previous_value)
  {
    LOGLN(value == HIGH ? "Switch Off Detected!" : "Switch On Detected!");  
    SwitchValueChanged(value);
    previous_value = value;    
  }
}
///////////////////////////////////////////////////////
// Default arduino functions
///////////////////////////////////////////////////////
void setup()
{
  SetupServos();

  // Switch connected to GND and pin SWITCH_PIN
  pinMode(SWITCH_PIN, INPUT_PULLUP);

#ifdef OPEN_CM
  SerialUSB.begin();
#else
  Serial.begin(9600);
#endif

  randomSeed(analogRead(0));
}

///////////////////////////////////////////////////////
void loop()
{
  CheckSwitchValue(GetSwitchValue());
  delay(50);
}


void serialEvent() 
{
  while (Serial.available()) 
  {
    char c = Serial.read();
    readString += c;
    delay(2);    
  }
  
  if (readString.length() >0) 
  {
    sequenceIndex = readString.toInt();
    readString = "";
    overrideSequenceIndex = true;
    LOG("Received index value from serial ");
    LOGLN(sequenceIndex);    
  }
}
