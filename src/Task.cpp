/*!
 * @file Task.cpp
 *
 * @mainpage freeRTOS Task Object
 *
 * @section intro_sec Introduction
 * This is an object oriented wrapper for freeRTOS task functions
 *
 * @section dependencies Dependencies
 * no dependencies
 *
 * @section author Author
 * Written by Caleb Husovich.
 *
 * @section license License
 * BSD license, all text here must be included in any redistribution.
 *
 */

#include "Arduino.h"
#include "Task.h"

Task::Task(String name, int stackSize, int priority) {
  _name = name;
  _stackSize = stackSize;
  _priority = priority;
}

/**************************************************************************/
/*!
    @brief  Sets the task function to be used. This function tells the object with function to use to run in the task.
    @param TaskFunction A function that contains the code to run int he task. Typically includes a infinite while or for loop.
*/
/**************************************************************************/
void Task::createTask(void (*TaskFunction)(void*)) {
  // (task function, name, stack size, parameter, priority, task handle )
  char nameArray[_name.length()];
  _name.toCharArray(nameArray, _name.length());
  xTaskCreate(TaskFunction, nameArray, _stackSize, NULL, _priority, &_taskHandle);
}


#if defined(ARDUINO_ARCH_ESP32)
void Task::createTask(void (*TaskFunction)(void*), byte core) {
  // (task function, name, stack size, parameter to pass, priority, task handle )
  char nameArray[_name.length()];
  _name.toCharArray(nameArray, _name.length());
  xTaskCreatePinnedToCore(TaskFunction, nameArray, _stackSize, NULL, _priority, &_taskHandle, core);
}
#endif
#if defined(ARDUINO_ARCH_RP2040)
void Task::createTask(void (*TaskFunction)(void*), byte core) {
  // (task function, name, stack size, parameter, priority, task handle )
  char nameArray[_name.length()];
  _name.toCharArray(nameArray, _name.length());
  xTaskCreate(TaskFunction, nameArray, _stackSize, NULL, _priority, &_taskHandle);
  /* Define the core affinity mask such that this task can only run on core 0
     * and core 2. */
  UBaseType_t uxCoreAffinityMask = ((1 << 0) | (1 << 2));
  /* Set the core affinity mask for the task. */
  vTaskCoreAffinitySet(_taskHandle, uxCoreAffinityMask);
}
#endif


/**************************************************************************/
/*!
    @brief  Sets the priority the task will run at function to be used. This function tells the object with function to use to run in the task.
    @param priority A function that contains the code to run int he task. Typically includes a infinite while or for loop.
*/
/**************************************************************************/
void Task::setPriority(int priority) {
  vTaskPrioritySet(_taskHandle, priority);
}

void Task::suspendTask() {
  vTaskSuspend(_taskHandle);
}

void Task::resumeTask() {
  vTaskResume(_taskHandle);
}

#if defined(ARDUINO_ARCH_RP2040)
void Task::getCoreAffinity() {
  vTaskCoreAffinityGet(_taskHandle);
}
#endif
