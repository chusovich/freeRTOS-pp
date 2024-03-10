/*!
 * @file Task.cpp
 *
 * @page Tasks Tasks
 *
 * @section intro_sec Introduction
 * Tasks are main drivers in freeRTOS. 
 *
 *
 */

#include "Arduino.h"
#include "Task.h"

/**************************************************************************/
/*! 
    @brief  Class that wraps common freeRTOS task functions. Here set a name of the task, the number of bytes in the stack to be allocated to the task, and the priority of the task the scheduler will use.
*/
/**************************************************************************/
Task::Task(String name, int stackSize, int priority) {
  _name = name;
  _stackSize = stackSize;
  _priority = priority;
}

/**************************************************************************/
/*!
    @brief  Sets the task function to be used. The tasks function is typically a infinite while- or for- loop. This functions initializes the task and immeadiately start being run by the schduler. If this function is called on a multi-core system, the freeRTOS will decide which core to run the task on.
    @param TaskFunction A function that contains the code that runs in the task. Typically involves a infinite while or for loop.
*/
/**************************************************************************/
void Task::createTask(void (*TaskFunction)(void*)) {
  // (task function, name, stack size, parameter, priority, task handle )
  char nameArray[_name.length()];
  _name.toCharArray(nameArray, _name.length());
  xTaskCreate(TaskFunction, nameArray, _stackSize, NULL, _priority, &_taskHandle);
}

#if defined(ARDUINO_ARCH_ESP32)
/**************************************************************************/
/*!
    @brief  Sets the task function to be used. This functions initializes the task and immeadiately start being run by the schduler. The tasks function is typically a infinite while- or for- loop. This function assigns the task to run on a specific core
    @param TaskFunction A function that contains the code that runs in the task. Typically involves a infinite while or for loop.
*/
/**************************************************************************/
void Task::createTask(void (*TaskFunction)(void*), byte core) {
  // (task function, name, stack size, parameter to pass, priority, task handle )
  char nameArray[_name.length()];
  _name.toCharArray(nameArray, _name.length());
  xTaskCreatePinnedToCore(TaskFunction, nameArray, _stackSize, NULL, _priority, &_taskHandle, core);
}
#endif

#if defined(ARDUINO_ARCH_RP2040)
/**************************************************************************/
/*!
    @brief  Sets the task function to be used. This functions initializes the task and immeadiately start being run by the schduler. The tasks function is typically a infinite while- or for- loop. This function assigns the task to run on a specific core
    @param TaskFunction A function that contains the code that runs in the task. Typically involves a infinite while or for loop.
*/
/**************************************************************************/
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
    @brief  Sets the priority the scheduler will use when scheduling the task. 
	The priority of a tasks determines when a task will run if multiple tasks are in the ready state. The lowest priority is zero, the highest priority is seven.
    @param priority A function that contains the code to run int he task. Typically includes a infinite while or for loop.
*/
/**************************************************************************/
void Task::setPriority(int priority) {
  vTaskPrioritySet(_taskHandle, priority);
}

/**************************************************************************/
/*!
    @brief  Stops the task from running. This function stops the task from running, but it does not remove from memory. It puts it in the 'suspended' state.
*/
/**************************************************************************/
void Task::suspendTask() {
  vTaskSuspend(_taskHandle);
}

/**************************************************************************/
/*!
    @brief  Starts running the task again if suspended. This function moves a task from the suspended to the ready state. The schedule will immeadiately start to run the task if no higher priority task is in a ready state.
*/
/**************************************************************************/
void Task::resumeTask() {
  vTaskResume(_taskHandle);
}

#if defined(ARDUINO_ARCH_RP2040)
void Task::getCoreAffinity() {
  vTaskCoreAffinityGet(_taskHandle);
}
#endif
