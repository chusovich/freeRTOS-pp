#include "Arduino.h"
#include "Queue.h"

Queue::Queue(int size) {
  _queueSize = size;
}

bool Queue::create() {
  _queueHandle = xQueueCreate(_queueSize, sizeof(message_t));
  // check if the queue was successfully created
  if (_queueHandle == NULL) {
    return false;
  } else {
    return true;
  }
}

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

void Queue::destroy() {
  vQueueDelete(_queueHandle);
}

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