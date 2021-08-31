
#include "Controller.h"


Controller controller_obj;


//static void Thermostat::normal_operation_task2(Thermostat* thermostat_obj);

Controller::Controller(){

    printf("Thermostat object created \n");
}

void Controller::begin(){
    this-> test1 = 50;
    this-> old_state = INITIAL;
    this->main_task_handle = NULL;
    this->secondary_task_handle = NULL;
    printf("Initialise the object with the default values \n");
    //xTaskCreate(task1,"thermostat normal operation task",10000,this,1,NULL); //receiving commands from main uart
}



void Controller::State_change_handle(e_thermostat_state state)
{
    this-> new_state = state;
    if(this-> old_state != this-> new_state ){ // if the new state is different than current state, delete the task
        printf("different state, delete the previous task \n");
        if (this ->main_task_handle != NULL){
            vTaskDelete(this ->main_task_handle);
        }

    }
    else{
        printf("same task \n"); // the same task is set, dont do anything
        return;
    }
        
    switch(this->new_state) 
    {   
        case MODE1:
            printf("NEW STATE = MODE1 \n");
            this-> old_state = MODE1;
            xTaskCreate(task1,"MODE1",10000,this,1,&this->main_task_handle); // receiving commands from main uart
            break;

        case MODE2:
            printf("NEW STATE = MODE2\n");
            this-> old_state = MODE2;
            xTaskCreate(task2,"MODE2",10000,this,1,&this->main_task_handle); // receiving commands from main uart
            break;


        default:
            printf("state not recognised \n");
    }
}






