#include <freeRTOS_API.h>

Task slowBlinkyTask("Slow Blinky",1024,1); // name, task stack size in bytes, priority
Task fastBlinkyTask("Fast Blinky",1024,1);

#define LED1 1 // slow led pin
#define LED2 2 // fast led pin

void blinkSlow(void *) {
  digitalWrite(LED1, HIGH);
  vTaskDelay(200);
  digitalWrite(LED1, LOW);
  vTaskDelay(200);
}

void blinkFast(void *) {
  digitalWrite(LED2, HIGH);
  vTaskDelay(200);
  digitalWrite(LED2, LOW);
  vTaskDelay(200);
}

void setup() {
  slowBlinkyTask.create(blinkSlow); // start the task
  fastBlinkyTask.create(blinkFast);
}

void loop() {
  vTaskDelay(10000);
  slowBlinkyTask.suspend(); // stop the slow blinky task after 10 sec
  vTaskDelay(5000);
  fastBlinkyTask.suspend(); // stop the fast blinky task after 5 more sec
}
