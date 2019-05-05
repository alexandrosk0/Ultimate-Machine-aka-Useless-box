#ifndef _DATA_H_
#define _DATA_H_
#include "classes.h"

Action actions[] = {
  {None, 0, 0, 0}, // 0 -No action, acts as end of sequence
  {CoverMotion, COVER_OPEN_POS, 100, HAND_MIN_EXTEND_DELAY}, // 1 -Cover open fast
  {HandMotion, HAND_EXTEND_POS, 100, 0}, // 2 -Extend hand fast
  {ColorLED, 0, 100, 0}, // 3 -Set led Off
  {ColorLED, 4, 100, 0}, // 4 -Set led On
  {HandMotion, HAND_CURTAIL_POS, 100, COVER_MIN_CLOSE_DELAY}, // 5 -Curtail hand fast
  {CoverMotion, COVER_CLOSE_POS, 100, 0}, // 6 - Close Cover fast
  {CoverMotion, COVER_CLOSE_POS, 20, 0}, // 7 - Close Cover medium
  {Wait, 0, 0, 2000}, // 8 Wait two seconds
  {HandMotion, 30, 10, 3000}, // 9 -Extend slowly close to switch and wait for two seconds from start of action
  };


#define NUM_SEQUENCES 3
Sequence sequencesRepository[NUM_SEQUENCES] = {
  {{{4, 1, 2}, {3, 5, 7}}}, // Standard fast open and close
  {{{4, 8, 1, 2}, {3, 5, 7}}},  // Wait two seconds before doing standard
  {{{4, 1, 9, 5, 8, 2}, {3, 5, 7}}}, // Extend slow till switch, but don't push, go back fast, pause for two seconds and fast switch off
};

#endif //_DATA_H_
