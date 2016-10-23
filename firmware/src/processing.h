//DOM-IGNORE-BEGIN
/*******************************************************************************
Copyright (c) 2013-2014 released Microchip Technology Inc.  All rights reserved.

Microchip licenses to you the right to use, modify, copy and distribute
Software only when embedded on a Microchip microcontroller or digital signal
controller that is integrated into your product or third party product
(pursuant to the sublicense terms in the accompanying license agreement).

You should refer to the license agreement accompanying this Software for
additional information regarding your rights and obligations.

SOFTWARE AND DOCUMENTATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT LIMITATION, ANY WARRANTY OF
MERCHANTABILITY, TITLE, NON-INFRINGEMENT AND FITNESS FOR A PARTICULAR PURPOSE.
IN NO EVENT SHALL MICROCHIP OR ITS LICENSORS BE LIABLE OR OBLIGATED UNDER
CONTRACT, NEGLIGENCE, STRICT LIABILITY, CONTRIBUTION, BREACH OF WARRANTY, OR
OTHER LEGAL EQUITABLE THEORY ANY DIRECT OR INDIRECT DAMAGES OR EXPENSES
INCLUDING BUT NOT LIMITED TO ANY INCIDENTAL, SPECIAL, INDIRECT, PUNITIVE OR
CONSEQUENTIAL DAMAGES, LOST PROFITS OR LOST DATA, COST OF PROCUREMENT OF
SUBSTITUTE GOODS, TECHNOLOGY, SERVICES, OR ANY CLAIMS BY THIRD PARTIES
(INCLUDING BUT NOT LIMITED TO ANY DEFENSE THEREOF), OR OTHER SIMILAR COSTS.
 *******************************************************************************/
//DOM-IGNORE-END

#ifndef _PROCESSING_H
#define _PROCESSING_H

// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include "system_config.h"
#include "system_definitions.h"

#include "network/recv.h"
#define MY_NAME "Geordon Worley"
#define PROCESSING_QUEUE_LEN 5
// DOM-IGNORE-BEGIN
#ifdef __cplusplus  // Provide C++ Compatibility

extern "C" {

#endif
// DOM-IGNORE-END
typedef enum {
    PR_TMR,
    PR_NR,
    PR_PWM,
} PRType;

typedef struct
{
    //this value determines if there is something in the block (i.e item or object) 0-65
    unsigned difficulty;
    unsigned weight;
    
}tiles;

typedef struct
{
	short int xy;
}edges;

typedef enum{
    ROVER_INIT,
    ROVER_MOVE,
    ROVER_BLOCK,
    ROVER_ROTATE_R,
    ROVER_ROTATE_L,
    ROVER_STOP,
}RStates;


typedef union {
    NRMessage nr_message;
    TimerDebug timer;
} PRUnion;

typedef struct{
    uint32_t tick_left;
    uint32_t tick_right;
}pwm_ticks;

typedef struct{
    uint8_t test_move_val;
    uint8_t test_rotate_val;
}debug_vals;
typedef struct{
    bool stop_left;
    bool stop_right;
    bool slow_left;
    bool slow_right;
    bool got_name;
    bool test_move;
    bool test_rotate;
}boolean_vals;
typedef struct{
    pwm_ticks ticks;
    RStates rover_state;
    boolean_vals bools;
    debug_vals debug_test;
    MSGPoint xy_points;
}rover;

typedef struct {
    PRType type;
    PRUnion data;
} PRMessage;

typedef struct{
    double wanted_speed_right;
    double wanted_speed_left;
}pwm_to_isr;

void processing_add_recvmsg(NRMessage *message); 
void interrupt_add_pwm(pwm_to_isr *pwm);
void processing_add_pwm_reading(uint32_t left_pwm, uint32_t right_pwm, uint32_t tmr3, uint32_t tmr4, double left_error, double right_error);
void processing_add_tmr_reading(uint32_t tmr3, uint32_t tmr4);
void move_wheels(unsigned right, unsigned left);
void enable_init();
void init_rover();
void PROCESSING_Initialize();
void PROCESSING_Tasks();
void map_init();
void find_path();
void my_path();
void path_init();
void init_world_diff();

#endif /* _PROCESSING_H */

//DOM-IGNORE-BEGIN
#ifdef __cplusplus
}
#endif
//DOM-IGNORE-END

/*******************************************************************************
 End of File
 */
