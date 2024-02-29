#ifndef Queue_h
#define Queue_h
#include "Arduino.h"

#if defined(ARDUINO_ARCH_RP2040)
#include <FreeRTOS.h>
#include <queue.h>
#endif

#ifndef QUEUE_DATA_BUFFER_SIZE
#define QUEUE_DATA_BUFFER_SIZE 25
#endif

typedef struct {
  int id;
  char data[QUEUE_DATA_BUFFER_SIZE];
} message_t;

class Queue {
public:
  // functions
  Queue(int size);
  bool create();
  bool createStatic();
  void destroy();
  bool sendMessage(message_t messageToSend, int msTimeout);
  bool receiveMessage(message_t *message);
  bool receiveMessage(message_t *message, int msTimeout);
  bool peek(message_t *message);
  bool peek(message_t *message, int msTimeout);
  // data

private:
  // data
  QueueHandle_t _queueHandle;
  int _queueSize;
  static StaticQueue_t _staticQueue;
};
#endif