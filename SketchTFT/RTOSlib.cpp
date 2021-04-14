#include "Arduino.h"
#include "RTOSlib.h"
#include "TASK_ID.h"

//Инициализация
void RTOS_Init(){
  rtos_tasks = malloc(currentTasks * sizeof(struct RTOSTask));            //Создание массива заданий в динамической памяти
}

//Установка таймера задания
void RTOS_Set_Task_Timer(unsigned char id, unsigned long etime){
  RTOSTask *task = &rtos_tasks[id];                                       //Получение задания массива
  task->exec_time = etime;                                                //Установка времени исполнения
  //rtos_tasks[id] = *task;
}

void RTOS_Register_Task(unsigned char id, RTOSTaskType type, unsigned long exec_time1, void (*execute1)(int tid)){
  if(currentTasks == MAX_TASKS) return;                                   //Проверка лимита заданий
  
  currentTasks++;                                                         //Увелечение счетчика заданий
  RTOSTask task = {execute1, type, 0, exec_time1, id, false};             //Создание экземпляра
  //Увеличение размера массива
  rtos_tasks = (RTOSTask*) realloc(rtos_tasks, currentTasks * sizeof(struct RTOSTask));
  rtos_tasks[id] = task;                                                  //Присвоение
}

void RTOS_Remove_Task(unsigned char index){
  if(currentTasks == 0) return;                                           //Проверка существования заданий

  currentTasks--;                                                         //Уменьшение счетчика заданий
  RTOSTask *temp = malloc(currentTasks * sizeof(struct RTOSTask));        //Создание нового массива
  memcpy(temp, rtos_tasks, currentTasks);                                 //Копирование части массива, находящейся слева от удаляемого элемента
  //Копирование части массива, находящейся справа от удаляемого элемента
  memcpy(temp + (index * sizeof(struct RTOSTask)), rtos_tasks + ((index+1) * sizeof(struct RTOSTask)), (currentTasks + 1) - index);
  free(rtos_tasks);                                                       //Удаление текущего массива
  rtos_tasks = temp;                                                      //Присвоение новго массива
}

//Проверка и исполнение заданий
void RTOS_Check_Tasks(){
  RTOSTask* curr;
  //Перебор всех заданий
  for(int i=0;i<currentTasks;i++){
    curr = &rtos_tasks[i];
    if(millis() - curr->last_exec >= curr->exec_time){                    //Проверка времени прошедшего с последнего выполнения задания
      curr->dispatch(i);                                                  //Выполнение задания
      curr->last_exec = millis();                                         //Время прошлого исполнения = текущее время
      RTOS_Log_TaskInfo(&rtos_tasks[i]);                                  //Вывод информации о задании в Serial
      //if(rtos_tasks[i].type == SINGLE) RTOS_Remove_Task(i);
      //else rtos_tasks[i].last_exec = millis();
    }
  }
}

void RTOS_Log_TaskInfo(RTOSTask* task){
  if(!DEBUG_MODE) return;
  Serial.print("[RTOS Task Execution] ID=");
  Serial.print(task->tid);
  Serial.print(" ExecTime=");
  Serial.print(task->exec_time);
  Serial.print(" LastExec=");
  Serial.print(task->last_exec);
  Serial.print(" Type=");
  Serial.print(task->type);
  Serial.print(" Function Memory Address=0x");
  Serial.println((unsigned long) &task->dispatch);
}
