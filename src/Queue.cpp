/*!
 * @file Queue.cpp
 *
 * @page queue_page Queues
 *
 * @section intro_sec Introduction
 * This is an object oriented wrapper for freeRTOS queue functions
 *
 * @section intro_sec Code Examples
 * Here are some examples
 * 
 * @code
 * void setup() {
 *	 Serial.begin(9600);
 *	 Queue.create();
 * }
 * @endcode
 *
 */

#include "Arduino.h"
#include "Queue.h"

/**************************************************************************/
/*! 
    @brief  Delcare the queue with how many elements it will hold.
*/
/**************************************************************************/
Queue::Queue(int size) {
  _queueSize = size;
}

/**************************************************************************/
/*! 
    @brief  Create the queue. This function creates the queue and allocated memory for it in the stack. Use the createStatic() method to allocate it to static memory.
*/
/**************************************************************************/
bool Queue::create() {
  _queueHandle = xQueueCreate(_queueSize, sizeof(message_t));
  // check if the queue was successfully created
  if (_queueHandle == NULL) {
    return false;
  } else {
    return true;
  }
}

/**************************************************************************/
/*! 
    @brief  Create the queue. This function creates the queue and allocates it into static memory.
*/
/**************************************************************************/
bool Queue::createStatic() {
  uint8_t queueStorageArea[_queueSize * sizeof(message_t)];
  _queueHandle = xQueueCreateStatic(_queueSize, sizeof(message_t), queueStorageArea, &_staticQueue);
  // check if the queue was successfully created
  if (_queueHandle == NULL) {
    return false;
  } else {
    return true;
  }
}

/**************************************************************************/
/*! 
    @brief  Delete the queue and remove it from memory. This function prevents the queue from being used any more and removes it from memory.
*/
/**************************************************************************/
void Queue::destroy() {
  vQueueDelete(_queueHandle);
}

/**************************************************************************/
/*! 
    @brief  Remove the most recent message from the queue. This function waits for an item to arrive the the queue and remove it from the queue. It never times out.
*/
/**************************************************************************/
bool Queue::dequeue(message_t *message) {
  bool status;
  if (_queueHandle != NULL) {  // check just to make sure the queue actually exists
    int ret = xQueueReceive(_queueHandle, message, portMAX_DELAY);
    if (ret == pdPASS) {
      status = true;
    } else {
      status = false;
    }
  }
  return status;
}

/**************************************************************************/
/*! 
    @brief  Waits for the message to arrive in the queue until the timeout period has elapsed. This function waits for an item to arrive the the queue and remove it from the queue, unless the timeout period elapses first, in which case it returns a null value.
*/
/**************************************************************************/
bool Queue::dequeue(message_t *message, int msTimeout) {
  bool status;
  if (_queueHandle != NULL) {  // check just to make sure the queue actually exists
    int ret = xQueueReceive(_queueHandle, message, msTimeout / portTICK_PERIOD_MS);
    if (ret == pdPASS) {
      status = true;
    } else {
      status = false;
    }
  }
  return status;
}

bool Queue::enqueue(message_t messageToSend, int msTimeout) {
  bool status;
  if (_queueHandle != NULL && uxQueueSpacesAvailable(_queueHandle) > 0) {
    int ret = xQueueSend(_queueHandle, (void *)&messageToSend, msTimeout / portTICK_PERIOD_MS);
    if (ret == pdTRUE) {
      status = true;  // The message was successfully sent.
    }
  } else {
    status = false;
  }
  return status;
}

void Queue::enqueueISR(message_t *messageToSend) {
  BaseType_t xHigherPriorityTaskWoken;
  xQueueSendFromISR(_queueHandle, messageToSend, &xHigherPriorityTaskWoken);
  if (xHigherPriorityTaskWoken) {
    portYIELD_FROM_ISR();
  }
}

bool Queue::peek(message_t *message) {
  if (xQueuePeek(_queueHandle, message, portMAX_DELAY) == pdTRUE) {
    return true;
  }
  return false;
}

bool Queue::peek(message_t *message, int msTimeout) {
  if (xQueuePeek(_queueHandle, message, msTimeout / portTICK_PERIOD_MS) == pdTRUE) {
    return true;
  }
  return false;
}
