#ifndef Queue_h
#define Queue_h
#include "Arduino.h"

#if defined(ARDUINO_ARCH_RP2040)
#include <FreeRTOS.h>
#include <queue.h>
#endif

typedef struct {
  String name;
  String data;
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
  // data

private:
  // data
  QueueHandle_t _queueHandle;
  int _queueSize;
  static StaticQueue_t _staticQueue;
};
#endif