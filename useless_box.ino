/* 
  MCU based "Ultimate machine" aka "Useless Box" aka "Leave me alone box"
  https://en.wikipedia.org/wiki/Useless_machine
  
  Works with Arduino or Open CM and for regular servos or smart servos
  Define OPEN_CM for Open CM 9.04 and define DYNAMIXEL_SERVOS for Dynamixel XL-320 smart servors  
  Tested with Open CM 9.04 and with Arduino Nano V3
 */
 
#ifdef BOARD_CM904
#define OPEN_CM
#endif

//#define DYNAMIXEL_SERVOS

#ifdef OPEN_CM
///////////// Pins definitions
  #define SWITCH_PIN 8 // Pin that supports internal pull-up connected to GND via switch 
//Pins definitions //////////////
  #define LED_PIN BOARD_LED_PIN  
#else //////// Arduino
///////////// Pins definitions
  #define SWITCH_PIN 3 //D3 // Pin that supports internal pull-up connected to GND via switch 
//Pins definitions //////////////
  #define LED_PIN LED_BUILTIN
#endif

#ifdef DYNAMIXEL_SERVOS  
  #define DXL_BUS_SERIAL1 1  //Dynamixel on Serial1(USART1)  <-OpenCM9.04
  Dynamixel Dxl(DXL_BUS_SERIAL1);
  
  #define ID_HAND_SERVO 1 //ID of the hand controlling XL-320 servo
  #define ID_COVER_SERVO 2 //ID of the cover controlling XL-320 servo
 
  #define HAND_EXTEND_POS 0 // Find the right extended position for your setup of hand servo (0-1023)
  #define HAND_CURTAIL_POS 300 // Find the right curtailed position for your setup of hand servo (0-1023)

  #define COVER_OPEN_POS 0 // Find the right extended position for your setup of cover servo (0-1023)
  #define COVER_CLOSE_POS 200 // Find the right curtailed position for your setup of cover servo (0-1023) 
#else //////// Regular Servos
///////////// Pins definitions
  #define HAND_SERVO_PIN 5 //D5
  #define COVER_SERVO_PIN 9 //D9
//Pins definitions //////////////

  #include <Servo.h> 
  Servo hand_servo;
  Servo cover_servo;

  #define HAND_EXTEND_POS 20 // Find the right extended position for your setup of hand servo (0-180)
  #define HAND_CURTAIL_POS 150 // Find the right curtailed position for your setup of hand servo (0-180)
  
  #define COVER_OPEN_POS 45 // Find the right extended position for your setup of cover servo (0-180)
  #define COVER_CLOSE_POS 0 // Find the right curtailed position for your setup of cover servo (0-180)
#endif

#define HAND_EXTEND_DELAY 200
#define COVER_CLOSE_DELAY 200


///////////////////////////////////////////////////////
// Setup
///////////////////////////////////////////////////////
void servos_setup()
{  
#ifdef DYNAMIXEL_SERVOS
  Dxl.begin(3);

  Dxl.jointMode(ID_HAND_SERVO);
  Dxl.jointMode(ID_COVER_SERVO);
  
  Dxl.goalSpeed(ID_HAND_SERVO, 1023);
  Dxl.goalSpeed(ID_COVER_SERVO, 1023);
#else
  hand_servo.attach(HAND_SERVO_PIN);
  cover_servo.attach(COVER_SERVO_PIN);
#endif
}

void init_servos()
{  
#ifdef DYNAMIXEL_SERVOS
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
#endif
}

///////////////////////////////////////////////////////
void setup() 
{
  servos_setup();
 
  // Switch connected to GND and pin SWITCH_PIN
  pinMode(SWITCH_PIN, INPUT_PULLUP);

#ifdef OPEN_CM
  SerialUSB.begin();
#else
  Serial.begin(9600);
#endif

  init_servos();
}

///////////////////////////////////////////////////////
// Functions
///////////////////////////////////////////////////////

void switch_changed(int value)
{
#ifdef OPEN_CM
  SerialUSB.println(value == HIGH ? "HIGH Detected!" : "LOW Detected!");
#else
  Serial.println(value == HIGH ? "HIGH Detected!" : "LOW Detected!");
#endif

#ifdef DYNAMIXEL_SERVOS
  if (value == HIGH)
  {
    Dxl.goalPosition(ID_HAND_SERVO, HAND_CURTAIL_POS);
    delay(COVER_CLOSE_DELAY);
    Dxl.goalPosition(ID_COVER_SERVO, COVER_CLOSE_POS);
    
    Dxl.ledOn(ID_HAND_SERVO, 4);
    Dxl.ledOn(ID_COVER_SERVO, 6);
  }
  else
  {
    Dxl.goalPosition(ID_COVER_SERVO, COVER_OPEN_POS);
    delay(HAND_EXTEND_DELAY);
    Dxl.goalPosition(ID_HAND_SERVO, HAND_EXTEND_POS);

    Dxl.ledOn(ID_HAND_SERVO, 2);
    Dxl.ledOn(ID_COVER_SERVO, 1);
  }
#else
  if (value == HIGH)
  {    
    hand_servo.write(HAND_CURTAIL_POS);
    delay(COVER_CLOSE_DELAY);
    cover_servo.write(COVER_CLOSE_POS);
  }
  else
  {
    cover_servo.write(COVER_OPEN_POS);
    delay(HAND_EXTEND_DELAY);
    hand_servo.write(HAND_EXTEND_POS);
  }
#endif
}

int previous_value = -1;
///////////////////////////////////////////////////////
void check_value(int value)
{
  if (value != previous_value)
  {
    switch_changed(value);
    previous_value = value;
    digitalWrite(LED_PIN, value);    
  }
}

///////////////////////////////////////////////////////
// Update
///////////////////////////////////////////////////////
void loop()
{
  check_value(digitalRead(SWITCH_PIN));  
  delay(10);
}
