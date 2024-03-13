#include <freeRTOS-pp.h>

/* Basic Task Example
  This sketch uses two tasks to blink two leds simultaneously at two different rate.
  The tasks are paused and resumes after different amounts of time and eventually the tasks are deleted
*/

Task slowBlinkyTask("Slow Blinky",1024,1); // name, task stack size in bytes, priority
Task fastBlinkyTask("Fast Blinky",1024,1);

#define LED1 1 // slow led pin
#define LED2 2 // fast led pin

void blinkSlow(void *) {
  for(;;) {
    digitalWrite(LED1, HIGH);
    vTaskDelay(500);
    digitalWrite(LED1, LOW);
    vTaskDelay(500);
  }
}

void blinkFast(void *) {
  for(;;) {
    digitalWrite(LED1, HIGH);
    vTaskDelay(100);
    digitalWrite(LED1, LOW);
    vTaskDelay(100);
  }
}
void setup() {
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  slowBlinkyTask.create(blinkSlow); // start the task
  fastBlinkyTask.create(blinkFast);
}

void loop() {
  vTaskDelay(10000);
  slowBlinkyTask.suspend(); // stop the slow blinky task after 10 sec
  vTaskDelay(5000);
  slowBlinkyTask.resume(); // start blinking slowly again
  fastBlinkyTask.suspend(); // stop the fast blinky task
  vTaskDelay(5000);
  slowBlinkTask.destroy(); // delete the slow blinkly task
  fastBlinklyTask.resume(); // start fast blinky task
  vTaskDelay(2000);
  fastBlinkyTask.destroy(); // stop the fast blinky task
}
