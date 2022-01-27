// PRN_No.  => 210950130009
// Name     => KAJOL

// Q2. Create 3 realtime tasks each with the periodcity T1=1000ms, T2=2000ms, T3=5000ms. Also create use oneshot software timer to trigger a callback function from T3 after 10000ms.

#include <stdio.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <freertos/timers.h>


TaskHandle_t task1, task2, task3;
TimerHandle_t motor_timer_handle;

uint32_t count =0;

void Task1(void *pv)
{
     printf("Task1 in queue\n");
     vTaskDelete(task1);
}

void Task2(void *pv)
{
     printf("Task2 in queue\n");
     vTaskDelete(task2);
}

void TurnMotorOFF(TimerHandle_t xTimer)   // call back function when timer off
{
  count++;
  printf("callback function when motor off\n");

   if (count == 5)
  {
   printf("Turning off the timer\n");
   xTimerStop(xTimer, 0);
  }  
}


void Task3(void *pv)
{
   motor_timer_handle = xTimerCreate("MotorOFF", pdMS_TO_TICKS(2000),pdFALSE, NULL, TurnMotorOFF);
  xTimerStart(motor_timer_handle, 0);  // when you want to interrupt the main task frequently.
  
  while(1)
  {   
   printf("motor Task\n");
   vTaskDelay(pdMS_TO_TICKS(10000));
  }
}

 
void app_main()
{
  BaseType_t result1 , result2, result3;
  printf("Welcome to program (Main Task)\n");
  
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

}

