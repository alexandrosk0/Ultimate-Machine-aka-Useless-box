#ifndef _DATA_H_
#define _DATA_H_
#include "classes.h"


#define HAND_EXTEND_POS 20 // Find the right extended position for your setup of hand servo (0-100)
#define HAND_EXTEND_NO_SWITCH_POS 28
#define HAND_EXTEND_HALF_POS 70
#define HAND_EXTEND_LITTLE_POS 85
#define HAND_CURTAIL_POS 100 // Find the right curtailed position for your setup of hand servo

#define COVER_OPEN_POS 30 // Find the right extended position for your setup of cover servo
#define COVER_CLOSE_POS 5 // Find the right curtailed position for your setup of cover servo

#define HAND_MIN_EXTEND_DELAY 50
#define COVER_MIN_CLOSE_DELAY 100


#define ACTION_ENUM \
X(None) \
X(CoverOpenFullFast) \
X(CoverOpenFullMedium) \
X(CoverOpenFullSlow) \
X(CoverOpenMiddleFast) \
X(CoverOpenMiddleMedium) \
X(CoverOpenMiddleSlow) \
X(CoverOpenLittleFast) \
X(CoverOpenLittleMedium) \
X(CoverOpenLittleSlow) \
X(CoverCloseFast) \
X(CoverCloseMedium) \
X(CoverCloseSlow) \
X(CoverReserved01) \
X(CoverReserved02) \
X(CoverReserved03) \
X(CoverReserved04) \
X(CoverReserved05) \
X(HandExtendFullFast) \
X(HandExtendFullMedium) \
X(HandExtendFullSlow) \
X(HandExtendAlmostFast) \
X(HandExtendAlmostMedium) \
X(HandExtendAlmostSlow) \
X(HandExtendMiddleFast) \
X(HandExtendMiddleMedium) \
X(HandExtendMiddleSlow) \
X(HandExtendLittleFast) \
X(HandExtendLittleMedium) \
X(HandExtendLittleSlow) \
X(HandCurtailFast) \
X(HandCurtailMedium) \
X(HandCurtailSlow) \
X(HandReserved01) \
X(HandReserved02) \
X(HandReserved03) \
X(HandReserved04) \
X(HandReserved05) \
X(LEDOn) \
X(LEDOff) \
X(Wait100ms) \
X(Wait300ms) \
X(Wait500ms) \
X(Wait1sec) \
X(Wait2sec) \
X(Wait5sec) \

enum ActionEnum {
#   define X(a) a,
ACTION_ENUM
#   undef X
    ActionsCount
};

// Strings for logging, used lots of memory (854 bytes)
char const* const actions_str[] = {
#   define X(a) #a,
ACTION_ENUM
#   undef X
    0
};



Action actionsRepository[] = 
{
  {NoAction, 0, 0},                                                    // None No action, acts as end of sequence
  {CoverMotion, COVER_OPEN_POS, 100},                                  // CoverOpenFullFast
  {CoverMotion, COVER_OPEN_POS, 10},                                   // CoverOpenFullMedium
  {CoverMotion, COVER_OPEN_POS, 3},                                    // CoverOpenFullSlow
  
  {CoverMotion, COVER_OPEN_POS/2, 100},                                // CoverOpenMiddleFast
  {CoverMotion, COVER_OPEN_POS/2, 10},                                 // CoverOpenMiddleMedium
  {CoverMotion, COVER_OPEN_POS/2, 3},                                  // CoverOpenMiddleMedium

  {CoverMotion, COVER_OPEN_POS/4, 100},                                // CoverOpenLittleFast
  {CoverMotion, COVER_OPEN_POS/4, 10},                                 // CoverOpenLittleMedium
  {CoverMotion, COVER_OPEN_POS/4, 3},                                  // CoverOpenLittleSlow

  {CoverMotion, COVER_CLOSE_POS, 100},                                 // CoverCloseFast
  {CoverMotion, COVER_CLOSE_POS, 10},                                  // CoverCloseMedium
  {CoverMotion, COVER_CLOSE_POS, 3},                                   // CoverCloseSlow

  {CoverMotion, 0, 0},                                                 // CoverReserved01
  {CoverMotion, 0, 0},                                                 // CoverReserved02
  {CoverMotion, 0, 0},                                                 // CoverReserved03
  {CoverMotion, 0, 0},                                                 // CoverReserved04
  {CoverMotion, 0, 0},                                                 // CoverReserved05

  {HandMotion, HAND_EXTEND_POS, 100},                                  // HandExtendFullFast
  {HandMotion, HAND_EXTEND_POS, 10},                                   // HandExtendFullMedium
  {HandMotion, HAND_EXTEND_POS, 3},                                    // HandExtendFullSlow
  
  {HandMotion, HAND_EXTEND_NO_SWITCH_POS, 100},                        // HandExtendAlmostFast
  {HandMotion, HAND_EXTEND_NO_SWITCH_POS, 10},                         // HandExtendAlmostMedium
  {HandMotion, HAND_EXTEND_NO_SWITCH_POS, 3},                          // HandExtendAlmostSlow
  
  {HandMotion, HAND_EXTEND_HALF_POS, 100},                             // HandExtendMiddleFast
  {HandMotion, HAND_EXTEND_HALF_POS, 10},                              // HandExtendMiddleMedium
  {HandMotion, HAND_EXTEND_HALF_POS, 3},                               // HandExtendMiddleSlow
  
  {HandMotion, HAND_EXTEND_LITTLE_POS, 100},                           // HandExtendLittleFast
  {HandMotion, HAND_EXTEND_LITTLE_POS, 10},                            // HandExtendLittleMedium
  {HandMotion, HAND_EXTEND_LITTLE_POS, 3},                             // HandExtendLittleSlow

  {HandMotion, HAND_CURTAIL_POS, 100},                                 // HandCurtailFast
  {HandMotion, HAND_CURTAIL_POS, 10},                                  // HandCurtailMedium
  {HandMotion, HAND_CURTAIL_POS, 3},                                   // HandCurtailSlow
  
  {HandMotion, 0, 0},                                                  // HandReserved01
  {HandMotion, 0, 0},                                                  // HandReserved02
  {HandMotion, 0, 0},                                                  // HandReserved03
  {HandMotion, 0, 0},                                                  // HandReserved04
  {HandMotion, 0, 0},                                                  // HandReserved05

  {ColorLED, 0, 100},                                                  // LEDOn
  {ColorLED, 1, 100},                                                  // LEDOff

  {Wait, 1, 0},                                                        // Wait100ms
  {Wait, 3, 0},                                                        // Wait300ms
  {Wait, 5, 0},                                                        // Wait500ms
  {Wait, 10, 0},                                                       // Wait1sec
  {Wait, 20, 0},                                                       // Wait2sec
  {Wait, 50, 0},                                                       // Wait5sec
};

#define NUM_SEQUENCES 7
Sequence sequencesRepository[NUM_SEQUENCES] = 
{
  //0 Standard fast open and close
  {{{LEDOn, CoverOpenFullFast, HandExtendFullFast}, 
  {LEDOff, HandCurtailFast, CoverCloseMedium}}},

  //1 Wait two seconds before doing standard
  {{{LEDOn, Wait2sec, CoverOpenFullFast, HandExtendFullFast}, 
  {LEDOff, HandCurtailFast, CoverCloseMedium}}},

  //2 Extend slow till switch, but don't push, go back fast, pause for two seconds and fast switch off
  {{{LEDOn, CoverOpenFullFast, HandExtendAlmostFast, Wait2sec, HandCurtailFast, CoverCloseFast, Wait2sec, CoverOpenFullFast, HandExtendFullFast}, 
  {LEDOff, HandCurtailFast, CoverCloseMedium}}},

  //3 Extend till switch, but don't push, pause for four seconds and fast switch off
  {{{LEDOn, CoverOpenFullFast, HandExtendAlmostFast, Wait2sec, Wait2sec, HandExtendFullFast}, 
  {LEDOff, HandCurtailFast, CoverCloseMedium}}},

  //4 Open to a third, close, 4 open to third, close and open full and swith off. At end of switch off, poke after two seconds
  {{{LEDOn, CoverOpenMiddleFast, Wait1sec, CoverCloseFast, Wait2sec, CoverCloseFast, CoverOpenFullFast, HandExtendFullFast}, 
  {LEDOff, HandCurtailFast, CoverCloseMedium, Wait2sec, CoverOpenMiddleFast, Wait1sec, CoverCloseFast}}},

  //5 Fast open, close door while hand is extended three time and switch off
  {{{LEDOn, CoverOpenFullFast, HandExtendAlmostFast, Wait300ms, CoverCloseFast, Wait300ms, CoverOpenFullFast, Wait300ms, CoverCloseFast, Wait300ms, CoverOpenFullFast, Wait300ms, CoverCloseFast, Wait300ms, HandExtendFullFast}, 
  {LEDOff, HandCurtailFast, CoverCloseMedium}}},
  
  //6 German's amazing move
  {{{LEDOn, HandExtendLittleFast, Wait300ms, HandCurtailFast, Wait300ms, HandExtendLittleFast, Wait300ms, HandCurtailFast, Wait300ms, HandExtendLittleFast, Wait300ms, HandCurtailFast, Wait300ms, HandExtendLittleFast, Wait300ms, HandCurtailFast, Wait300ms, CoverOpenFullMedium, Wait500ms, HandExtendFullFast}, 
  {HandCurtailFast, CoverCloseSlow, Wait100ms, HandExtendLittleFast, Wait300ms, HandCurtailFast, Wait300ms, HandExtendFullFast, Wait300ms, HandCurtailFast, Wait300ms, HandExtendLittleFast, Wait300ms, HandCurtailFast, Wait300ms, HandExtendLittleFast, Wait300ms, HandCurtailFast, LEDOff}}},  
};

#endif //_DATA_H_
