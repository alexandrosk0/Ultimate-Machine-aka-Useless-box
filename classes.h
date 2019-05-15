#ifndef _CLASSES_H_
#define _CLASSES_H_

#define SEQUENCE_LENGTH_MAX 26

enum ActionType : byte
{
  CoverMotion,
  HandMotion,
  ColorLED, //pos as the LED value
  Wait, // pos as the miliseconds value (25 sec max)
  NoAction
};

class Action
{
public:
  ActionType type;
  byte pos; //(0-100)
  byte speed; //(0-100)
};

class Sequence
{
public:
  byte sequences[2][SEQUENCE_LENGTH_MAX]; // // Low is 0, High is 1
};


#endif //_CLASSES_H_
