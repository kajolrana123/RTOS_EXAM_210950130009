// PRN_No. => 210950130009
// Name    => KAJOL


// Q1. Create 3 realtime tasks each with the periodcity T1=1000ms, T2=2000ms, T3=5000ms. Also create two additional task T4 and T5 where T4 sends integer data to T5 using Messsage Queues.


#include <stdio.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <freertos/queue.h>

TaskHandle_t task1, task2, task3, task4, task5;   // task handler opaque data type.
QueueHandle_t sensor_queue;  // queue handler opaque data type.

void Task1(void *pv)
{
     printf("Task1 in queue\n");
     vTaskDelay(1000 / portTICK_PERIOD_MS);
    vTaskDelete(task1);
}

void Task2(void *pv)
{
     printf("Task2 in queue\n");
     vTaskDelay(2000 / portTICK_PERIOD_MS);
    vTaskDelete(task2);
}

void Task3(void *pv)
{
     printf("Task3 in queue\n");
     vTaskDelay(500 / portTICK_PERIOD_MS);
    vTaskDelete(task3);
}

void Task4(void *pv)
{
  uint32_t recv_data = 0;
 while(1)
 {
   xQueueReceive(sensor_queue, &recv_data, portMAX_DELAY);
   printf("Task4: recv_data = %d\n", recv_data);
 }
}

void Task5(void *pv)
{
  uint32_t int_send_data = 0;
 while(1)
 {
     int_send_data++;
     printf("Task3: int_sensor_data = %d\n", int_send_data);
     xQueueSend(sensor_queue, &int_send_data, portMAX_DELAY);
     vTaskDelay(2000 / portTICK_PERIOD_MS);

  /*   if(sensor_data == 10)
     {
       printf("Sensor task : sensor_data = %d\n", sensor_data);
       vTaskDelay(10000 / portTICK_PERIOD_MS);
     }
 */
 }
}


void app_main()
{
  BaseType_t result1 , result2, result3, result4, result5;
  sensor_queue = xQueueCreate(10, sizeof(int));
  
  printf("Multitask program\n");  
   
   result1 = xTaskCreate(Task1, "Task1", 2048, NULL, 5, &task1);
   if (result1 != pdPASS)
  {
   printf("task 1 is not created\n");
  }
   
   result2 = xTaskCreate(Task2, "Task2", 2048, NULL, 6, &task2);   
   if (result2 != pdPASS)
   {
   printf("task 2 is not created\n");
   }
   
   result3 = xTaskCreate(Task3, "Task3", 2048, NULL, 7, &task3);   
   if (result3 != pdPASS)
   {
   printf("task 3 is not created\n");
   }
   result4 = xTaskCreate(Task4, "Task4", 2048, NULL, 8, &task4);   
   if (result4 != pdPASS)
   {
   printf("task 4 is not created\n");
   }
   
   result5 = xTaskCreate(Task5, "Task5", 2048, NULL, 9, &task5);   
   if (result5 != pdPASS)
   {
   printf("task 5 is not created\n");
   }   
   
   
   
   
}


