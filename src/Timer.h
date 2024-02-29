#ifndef Timer_h
#define Timer_h
#include "Arduino.h"

#if defined(ARDUINO_ARCH_RP2040)
#include <FreeRTOS.h>
#include <timers.h>
#endif

// to-do
// 1) encapsulate the timer callback functions
class Timer {
public:
  // functions
  bool create(const char *timerName, int msDuration, bool autoRestart, int timerID, void callbackFunction(TimerHandle_t handle));
  bool createStatic(const char *timerName, int msDuration, bool autoRestart, int timerID, void callbackFunction(TimerHandle_t handle));
  bool start(int msToBlock);
  bool destroy(int msToBlock);
  bool reset(int msToBlock);
  bool changeDuration(int msDuration, int msToBlock);
  bool startFromISR();
  TimerHandle_t _timerHandle;
  // data

private:
  static StaticTimer_t _staticHandle;
  // data
};
#endif