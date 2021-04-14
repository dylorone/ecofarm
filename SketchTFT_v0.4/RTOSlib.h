#ifndef RTOSlib_h
#define RTOSlib_h

#define MAX_TASKS 10

typedef struct RTOSTask {
  void (*dispatch)(int tid);
  unsigned long last_exec;
  unsigned int exec_time;
  unsigned char tid;
  bool frozen;
};

extern RTOSTask rtos_tasks[MAX_TASKS];

extern unsigned char currentMaxTasks;

void registerTask(unsigned char id, unsigned int exec_time, void (*execute)(int tid));

void checkTasks();

#endif
