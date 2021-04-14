#ifndef RTOSlib_h
#define RTOSlib_h

#define MAX_TASKS 10
#define DEBUG_MODE 0

enum RTOSTaskType {
  REPEATING,
  SINGLE
};

typedef struct RTOSTask {
  void (*dispatch)(int tid);
  RTOSTaskType type;
  unsigned long last_exec;
  unsigned long exec_time;
  unsigned char tid;
  bool frozen;
};

static RTOSTask* rtos_tasks;
static unsigned char currentTasks;

void RTOS_Init();
void RTOS_Set_Task_Timer(unsigned char id, unsigned long etime);
void RTOS_Register_Task(unsigned char id, RTOSTaskType type, unsigned long exec_time, void (*execute)(int tid));
void RTOS_Unregister_Task(unsigned char index);
void RTOS_Log_TaskInfo(RTOSTask* task);
void RTOS_Check_Tasks();

#endif
