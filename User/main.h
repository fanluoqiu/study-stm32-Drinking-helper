#ifndef MAIN_H
#define MAIN_H

typedef enum {normal=0,Timekeeping=1,Timeout=2} tp_maininterfmode;

tp_maininterfmode MainInterfMode(void);

extern tp_maininterfmode mode;

#endif
