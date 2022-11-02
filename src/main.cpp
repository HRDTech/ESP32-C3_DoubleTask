#include <Arduino.h>

int pinLed = 2;
char statusLed = '0';

//Task1code: blinks an LED every 1000 ms
void Task1code( void * parameter ){

  for(;;){
    if (statusLed == '0') {
      /* code */
      vTaskDelay(700/portTICK_PERIOD_MS);
      neopixelWrite(RGB_BUILTIN,RGB_BRIGHTNESS,0,0); // Red
      vTaskDelay(700/portTICK_PERIOD_MS);
      neopixelWrite(RGB_BUILTIN,0,RGB_BRIGHTNESS,0); // Green
      vTaskDelay(700/portTICK_PERIOD_MS);
      neopixelWrite(RGB_BUILTIN,0,0,RGB_BRIGHTNESS); // Blue
      vTaskDelay(700/portTICK_PERIOD_MS);
      neopixelWrite(RGB_BUILTIN,0,0,0); // Off / black
    } else if (statusLed == '1') {
      vTaskDelay(700/portTICK_PERIOD_MS);
      neopixelWrite(RGB_BUILTIN,RGB_BRIGHTNESS,0,0); // Red
    }  else if (statusLed == '2') {
      vTaskDelay(700/portTICK_PERIOD_MS);
      neopixelWrite(RGB_BUILTIN,0,RGB_BRIGHTNESS,0); // Green
    }  else if (statusLed == '3') {
      vTaskDelay(700/portTICK_PERIOD_MS);
      neopixelWrite(RGB_BUILTIN,0,0,RGB_BRIGHTNESS); // Blue
    } else {
      Serial.print("Blink Disactivate: ");
      Serial.println(statusLed);
      vTaskDelay(700/portTICK_PERIOD_MS);
    }
    
  }
  
}

//Task2code: blinks an LED every 700 ms
void Task2code( void * pvParameters ){

  for(;;){
    if (Serial.available()) {
      /* code */
      char data = Serial.read();
      statusLed = data;
      Serial.print("Data Rx: ");
      Serial.println(statusLed);
            
    }
    
    vTaskDelay(20/portTICK_PERIOD_MS);
  }

}

void setup() {
  Serial.begin(115200); 
  pinMode(pinLed, OUTPUT);
  digitalWrite(pinLed, HIGH);

  //create a task that will be executed in the Task2code() function, with priority 1 and executed on core 0
  xTaskCreatePinnedToCore(
                    Task2code,   /* Task function. */
                    "Task2",     /* name of task. */
                    5000,       /* Stack size of task */
                    NULL,        /* parameter of the task */
                    1,           /* priority of the task */
                    NULL,      /* Task handle to keep track of created task */
                    0);          /* pin task to core 0 */                  

//create a task that will be executed in the Task1code() function, with priority 1 and executed on core 0
  xTaskCreatePinnedToCore(
                    Task1code,   /* Task function. */
                    "Task1",     /* name of task. */
                    5000,       /* Stack size of task */
                    NULL,        /* parameter of the task */
                    1,           /* priority of the task */
                    NULL,      /* Task handle to keep track of created task */
                    1);          /* pin task to core 0 */                  

}

void loop() {
}