#ifndef _CLASSES_H_
#define _CLASSES_H_

#define SEQUENCE_LENGTH 12

enum ActionType : byte
{
  CoverMotion,
  HandMotion,
  ColorLED,
  Wait,
  None
};

class Action
{
public:
  ActionType type;
  byte pos; //(0-100)
  byte speed; //(0-100)
  short pause; //(0-100000)
  void Assign(ActionType _type, byte _pos, byte _speed, short _pause) 
  {
    type = _type;
    pos = _pos;
    speed = _speed;
    pause = _pause;    
  }  
};

class Sequence
{
public:
  byte sequences[2][SEQUENCE_LENGTH];

};


#endif //_CLASSES_H_
