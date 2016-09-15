// DOM-IGNORE-BEGIN
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
// DOM-IGNORE-END

#include "processing.h"
#include "network_send.h"
#include "debug.h"
#include "int_wifly.h"

#define PROCESSING_QUEUE_LEN 1

QueueHandle_t queue;

void processing_add_recvmsg(NRMessage *message) {
    xQueueSendToBack(queue, message, portMAX_DELAY);
}

void PROCESSING_Initialize() {
    SYS_PORTS_PinWrite(0, PORT_CHANNEL_C, PORTS_BIT_POS_1, 0);
    queue = xQueueCreate(PROCESSING_QUEUE_LEN, sizeof(NRMessage));
    wifly_int_init();
}

void PROCESSING_Tasks() {
    SYS_PORTS_PinWrite(0, PORT_CHANNEL_C, PORTS_BIT_POS_1, 0);
    debug_loc(DEBUG_PROCESSING_ENTER);
    NRMessage message;

    // Create netstats message.
    NSMessage netstats_message;
    netstats_message.type = NS_NETSTATS;
    MSGNetstats *netstats = &netstats_message.data.netstats;
    netstats->numGoodMessagesRecved = 0;
    netstats->numCommErrors = 0;
    netstats->numJSONRequestsRecved = 0;
    netstats->numJSONResponsesRecved = 0;
    netstats->numJSONRequestsSent = 0;
    netstats->numJSONResponsesSent = 0;

    debug_loc(DEBUG_PROCESSING_WHILE);
    while (1) {
        debug_loc(DEBUG_PROCESSING_BEFORE_SEND);
        network_send_add_message(&netstats_message);
        debug_loc(DEBUG_PROCESSING_AFTER_SEND);

        // We responded to a request, so we increase the responses sent.
        netstats->numJSONResponsesSent++;
        /*debug_loc(DEBUG_PROCESSING_BEFORE_RECV);
        xQueueReceive(queue, &message, portMAX_DELAY);
        debug_loc(DEBUG_PROCESSING_AFTER_RECV);
        switch (message.type) {
            case NR_QUERY_STATS: {
                MSGQueryStats *stats = &message.data.query_stats;
                netstats->numGoodMessagesRecved++;
                netstats->numJSONRequestsRecved++;
                debug_loc(DEBUG_PROCESSING_BEFORE_SEND);
                network_send_add_message(&netstats_message);
                debug_loc(DEBUG_PROCESSING_AFTER_SEND);

                // We responded to a request, so we increase the responses sent.
                netstats->numJSONResponsesSent++;
            } break;
        }*/
    }
}



/*******************************************************************************
 End of File
 */
