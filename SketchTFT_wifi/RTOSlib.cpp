#include "Arduino.h"
#include "RTOSlib.h"

RTOSTask rtos_tasks[MAX_TASKS];
unsigned char currentMaxTasks;

void registerTask(unsigned char id, unsigned int exec_time1, void (*execute1)(int tid)){
  if(currentMaxTasks == MAX_TASKS) return;
  
  RTOSTask task = {execute1, 0, exec_time1, id, false};
  rtos_tasks[id] = task;
  currentMaxTasks++;
}

void checkTasks(){
  for(int i=0;i<currentMaxTasks;i++){
    if(millis() - rtos_tasks[i].last_exec >= rtos_tasks[i].exec_time){
      rtos_tasks[i].dispatch(i);
      rtos_tasks[i].last_exec = millis();
    }
  }
}
