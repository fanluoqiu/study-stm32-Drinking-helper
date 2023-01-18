#ifndef MAIN_H
#define MAIN_H

typedef enum {normal=0,Timekeeping=1,Timeout=2} tp_maininterfmode;

typedef struct 
{
    u8 hour;
    u8 min;
    u8 sec;
} tp_time;


tp_maininterfmode MainInterfMode(void);
void resettime(void);
tp_time time_h_m_s(void);

extern tp_maininterfmode mode;
extern tp_time init_delaytime;
#define INIT_TIME 30
#endif
