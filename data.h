#ifndef _DATA_H_
#define _DATA_H_
#include "classes.h"


#define HAND_EXTEND_POS 0 // Find the right extended position for your setup of hand servo (0-100)
#define HAND_EXTEND_NO_SWITCH_POS 20
#define HAND_EXTEND_HALF_POS 60
#define HAND_EXTEND_LITTLE_POS 75
#define HAND_CURTAIL_POS 100 // Find the right curtailed position for your setup of hand servo

#define COVER_OPEN_POS 45 // Find the right extended position for your setup of cover servo
#define COVER_OVEREXTEND_POS 60 // Find the right extended position for your setup of cover servo
#define COVER_CLOSE_POS 0 // Find the right curtailed position for your setup of cover servo

#define HAND_MIN_EXTEND_DELAY 50
#define COVER_MIN_CLOSE_DELAY 100


#define ACTION_ENUM \
X(None) \
X(CoverOverF) \
X(CoverOverM) \
X(CoverOverS) \
X(CoverFullF) \
X(CoverFullM) \
X(CoverFullS) \
X(CoverHalveF) \
X(CoverHalveM) \
X(CoverHalveS) \
X(CoverPeakF) \
X(CoverPeakM) \
X(CoverPeakS) \
X(CoverCloseF) \
X(CoverCloseM) \
X(CoverCloseS) \
X(CoverR01) \
X(CoverR02) \
X(CoverR03) \
X(CoverR04) \
X(CoverR05) \
X(HandFullF) \
X(HandFullM) \
X(HandFullS) \
X(HandAlmostF) \
X(HandAlmostM) \
X(HandAlmostS) \
X(HandHalveF) \
X(HandHalveM) \
X(HandHalveS) \
X(HandTwitchF) \
X(HandTwitchM) \
X(HandTwitchS) \
X(HandCurtailF) \
X(HandCurtailM) \
X(HandCurtailS) \
X(HandR01) \
X(HandR02) \
X(HandR03) \
X(HandR04) \
X(HandR05) \
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

// Strings for logging, used lots of memory (around 1K). Make enum names shorter to reduce memory
char const* const actions_str[] = {
#   define X(a) #a,
ACTION_ENUM
#   undef X
    0
};


// Endings of enum represents speed: F fast, M medium, S Slow
Action actionsRepository[] = 
{
  {NoAction, 0, 0},                                                    // None No action, acts as end of sequence

  {CoverMotion, COVER_OVEREXTEND_POS, 100},                            // CoverOverF
  {CoverMotion, COVER_OVEREXTEND_POS, 10},                             // CoverOverM
  {CoverMotion, COVER_OVEREXTEND_POS, 3},                              // CoverOverS

  {CoverMotion, COVER_OPEN_POS, 100},                                  // CoverFullF
  {CoverMotion, COVER_OPEN_POS, 10},                                   // CoverFullM
  {CoverMotion, COVER_OPEN_POS, 3},                                    // CoverFullS
  
  {CoverMotion, COVER_OPEN_POS/2, 100},                                // CoverHalveF
  {CoverMotion, COVER_OPEN_POS/2, 10},                                 // CoverHalveM
  {CoverMotion, COVER_OPEN_POS/2, 3},                                  // CoverHalveM

  {CoverMotion, COVER_OPEN_POS/4, 100},                                // CoverPeakF
  {CoverMotion, COVER_OPEN_POS/4, 10},                                 // CoverPeakM
  {CoverMotion, COVER_OPEN_POS/4, 3},                                  // CoverPeakS

  {CoverMotion, COVER_CLOSE_POS, 100},                                 // CoverCloseF
  {CoverMotion, COVER_CLOSE_POS, 10},                                  // CoverCloseM
  {CoverMotion, COVER_CLOSE_POS, 3},                                   // CoverCloseS

  {CoverMotion, 0, 0},                                                 // CoverR01
  {CoverMotion, 0, 0},                                                 // CoverR02
  {CoverMotion, 0, 0},                                                 // CoverR03
  {CoverMotion, 0, 0},                                                 // CoverR04
  {CoverMotion, 0, 0},                                                 // CoverR05

  {HandMotion, HAND_EXTEND_POS, 100},                                  // HandFullF
  {HandMotion, HAND_EXTEND_POS, 10},                                   // HandFullM
  {HandMotion, HAND_EXTEND_POS, 3},                                    // HandFullS
  
  {HandMotion, HAND_EXTEND_NO_SWITCH_POS, 100},                        // HandAlmostF
  {HandMotion, HAND_EXTEND_NO_SWITCH_POS, 10},                         // HandAlmostM
  {HandMotion, HAND_EXTEND_NO_SWITCH_POS, 3},                          // HandAlmostS
  
  {HandMotion, HAND_EXTEND_HALF_POS, 100},                             // HandHalveF
  {HandMotion, HAND_EXTEND_HALF_POS, 10},                              // HandHalveM
  {HandMotion, HAND_EXTEND_HALF_POS, 3},                               // HandHalveS
  
  {HandMotion, HAND_EXTEND_LITTLE_POS, 100},                           // HandTwitchF
  {HandMotion, HAND_EXTEND_LITTLE_POS, 10},                            // HandTwitchM
  {HandMotion, HAND_EXTEND_LITTLE_POS, 3},                             // HandTwitchS

  {HandMotion, HAND_CURTAIL_POS, 100},                                 // HandCurtailF
  {HandMotion, HAND_CURTAIL_POS, 10},                                  // HandCurtailM
  {HandMotion, HAND_CURTAIL_POS, 3},                                   // HandCurtailS
  
  {HandMotion, 0, 0},                                                  // HandR01
  {HandMotion, 0, 0},                                                  // HandR02
  {HandMotion, 0, 0},                                                  // HandR03
  {HandMotion, 0, 0},                                                  // HandR04
  {HandMotion, 0, 0},                                                  // HandR05

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
  //0 Standard F open and close
  {{{LEDOn, CoverFullF, HandFullF}, 
  {LEDOff, HandCurtailF, CoverCloseM}}},

  //1 Wait two seconds before doing standard
  {{{LEDOn, Wait2sec, CoverFullF, HandFullF}, 
  {LEDOff, HandCurtailF, CoverCloseM}}},

  //2 Extend S till switch, but don't push, go back F, pause for two seconds and F switch off
  {{{LEDOn, CoverFullF, HandAlmostF, Wait2sec, HandCurtailF, CoverCloseF, Wait2sec, CoverFullF, HandFullF}, 
  {LEDOff, HandCurtailF, CoverCloseM}}},

  //3 Extend till switch, but don't push, pause for four seconds and F switch off
  {{{LEDOn, CoverFullF, HandAlmostF, Wait2sec, Wait2sec, HandFullF}, 
  {LEDOff, HandCurtailF, CoverCloseM}}},

  //4 Open to a third, close, 4 open to third, close and open full and swith off. At end of switch off, poke after two seconds
  {{{LEDOn, CoverHalveF, Wait1sec, CoverCloseF, Wait2sec, CoverCloseF, CoverFullF, HandFullF}, 
  {LEDOff, HandCurtailF, CoverCloseM, Wait5sec, CoverHalveF, Wait1sec, CoverCloseF}}},

  //5 F open, close door while hand is extended three time and switch off
  {{{LEDOn, CoverFullF, HandAlmostF, Wait300ms, CoverCloseF, Wait300ms, CoverFullF, Wait300ms, CoverCloseF, Wait300ms, CoverFullF, Wait500ms, CoverCloseF, Wait300ms, CoverOverF, Wait1sec, CoverCloseF, Wait300ms, CoverOverF, Wait2sec, CoverCloseF, HandFullF}, 
  {LEDOff, HandCurtailF, CoverCloseF}}},
  
  //6 German's amazing move
  {{{LEDOn, HandTwitchF, Wait300ms, HandCurtailF, Wait300ms, HandHalveF, Wait300ms, HandCurtailF, Wait300ms, HandHalveF, Wait300ms, HandCurtailF, Wait300ms, HandHalveF, Wait300ms, HandCurtailF, Wait300ms, CoverFullF, Wait500ms, HandFullF}, 
  {HandCurtailF, CoverCloseS, Wait100ms, HandHalveF, Wait300ms, HandCurtailF, Wait300ms, HandFullF, Wait300ms, HandCurtailF, Wait300ms, HandHalveF, Wait300ms, HandCurtailF, Wait300ms, HandTwitchF, Wait300ms, HandCurtailF, LEDOff}}},  
};

#endif //_DATA_H_
