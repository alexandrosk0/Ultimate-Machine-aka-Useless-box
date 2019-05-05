#ifndef _DATA_H_
#define _DATA_H_
#include "classes.h"

#define HAND_EXTEND_POS 20 // Find the right extended position for your setup of hand servo (0-100)
#define HAND_CURTAIL_POS 100 // Find the right curtailed position for your setup of hand servo

#define COVER_OPEN_POS 30 // Find the right extended position for your setup of cover servo
#define COVER_CLOSE_POS 5 // Find the right curtailed position for your setup of cover servo

#define HAND_MIN_EXTEND_DELAY 50
#define COVER_MIN_CLOSE_DELAY 100

Action actions[] = 
{
  {None, 0, 0, 0},                                                      // 0 -No action, acts as end of sequence
  {CoverMotion, COVER_OPEN_POS, 100, HAND_MIN_EXTEND_DELAY},            // 1 -Cover open fast
  {HandMotion, HAND_EXTEND_POS, 100, 0},                                // 2 -Extend hand fast
  {ColorLED, 0, 100, 0},                                                // 3 -Set led Off
  {ColorLED, 4, 100, 0},                                                // 4 -Set led On
  {HandMotion, HAND_CURTAIL_POS, 100, COVER_MIN_CLOSE_DELAY},           // 5 -Curtail hand fast
  {CoverMotion, COVER_CLOSE_POS, 100, 0},                               // 6 - Close Cover fast
  {CoverMotion, COVER_CLOSE_POS, 20, 0},                                // 7 - Close Cover medium
  {CoverMotion, COVER_OPEN_POS/2, 100, HAND_MIN_EXTEND_DELAY},          // 8 -Cover open fast to halve
  {HandMotion, 30, 10, 3000},                                           // 9 -Extend slowly close to switch and wait for two seconds from start of action
  {Wait, 0, 0, 100},                                                    // 10 Wait 100 ms
  {Wait, 0, 0, 1000},                                                   // 11 Wait one seconds
  {Wait, 0, 0, 2000},                                                   // 12 Wait two seconds  
};


#define NUM_SEQUENCES 4
Sequence sequencesRepository[NUM_SEQUENCES] = 
{
  {{{4, 1, 2}, {3, 5, 7}}},                                             // Standard fast open and close
  {{{4, 12, 1, 2}, {3, 5, 7}}},                                         // Wait two seconds before doing standard
  {{{4, 1, 9, 5, 6, 12, 1, 2}, {3, 5, 7}}},                             // Extend slow till switch, but don't push, go back fast, pause for two seconds and fast switch off
  {{{4, 8, 11, 6, 12, 6, 1, 2}, {3, 5, 7, 12, 8, 11, 6}}},              // Open to a thrid, close,4 open to third, close and open full and swith off. At end of switch off, poke after two seconds
};

#endif //_DATA_H_
