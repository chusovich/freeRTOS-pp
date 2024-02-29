#ifndef Task_h
#define Task_h
#include "Arduino.h"

#if defined(ARDUINO_ARCH_RP2040)
#include <FreeRTOS.h>
#include <task.h>
#endif

class Task {
public:
  // functions
  Task(String name, int stackSize, int priority);
  void createTask(void (*TaskFunction)(void*));
  void createTask(void (*TaskFunction)(void*), byte core);
  void setPriority(int priority);
  void suspendTask();
  void resumeTask();
  
#if defined(ARDUINO_ARCH_RP2040)
  void getCoreAffinity();
#endif

private:
  // data
  TaskHandle_t _taskHandle;
  String _name;
  int _stackSize;
  int _priority;
};
#endif