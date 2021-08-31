#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "stdint.h"
#include "stdio.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"



enum e_thermostat_state
{
    INITIAL,
    MODE1,
    MODE2,
	MODE3,
    MAX_STATES
};


class Controller
{
    private://only accesible for class
        int test1;
        e_thermostat_state new_state;
        e_thermostat_state old_state;
        TaskHandle_t main_task_handle;
        TaskHandle_t secondary_task_handle;
        

    public: 
    //accesible outside class
        Controller();                                                   // INIT OBJECT
        void begin();
        void State_change_handle(e_thermostat_state state);


        static void task1(void* parameters)
        {
            Controller controller_obj = *((Controller*)parameters);
            //CHECK IF TASK3 IS ACTIVE. IF IT IS ACTIVE, ALWAYS DELETE IT WHEN TASK1 IS STARTED
            printf("checking secondary task handle \n");
            if(this->secondary_task_handle != NULL){
                printf("task3 is active, delete it");
                vTaskDelete(this->secondary_task_handle);
            }
            for(;;)
            {     
                printf("hello from task 1\n");
                vTaskDelay(1000/portTICK_RATE_MS);
            }
        }


        static void task2(void* parameters)
        {
            Controller controller_obj = *((Controller*)parameters);
            for(;;)
            {   
                printf("hello from task 2\n");
                if(controller_obj.secondary_task_handle ==NULL){
                    printf("task3 started from task2 \n");
                    xTaskCreate(task3,"MODE3",10000,&controller_obj,1,&controller_obj.secondary_task_handle); 
                }
                
                vTaskDelay(1000/portTICK_RATE_MS);
            }
        }


        static void task3(void* parameters)
        {
            Controller controller_obj = *((Controller*)parameters);
            for(;;)
            {   
                printf("hello from task 3 which is created from task 2\n");
                vTaskDelay(1000/portTICK_RATE_MS);
            }
        }
        
        //static void normal_operation_task(void *argument);                                 // DECLARE DEFAULT THERMOSTAT STATES AND VARS       
};




#endif