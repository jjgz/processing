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

#include "network_recv.h"
#include "processing.h"

#define NETWORK_RECV_QUEUE_LEN 1

QueueHandle_t queue;

void network_recv_add_buffer(CharBuffer buffer) {
    xQueueSendToBack(queue, &buffer, portMAX_DELAY);
}

void NETWORK_RECV_Initialize() {
    queue = xQueueCreate(NETWORK_RECV_QUEUE_LEN, sizeof(CharBuffer));
}

void NETWORK_RECV_Tasks() {
    CharBuffer buffer;
    NRMessage message;
    while (1) {
        xQueueReceive(queue, &buffer, portMAX_DELAY);
        // Parse the JSON into objects.
        // TODO: Parse from JSON.
        // Assume the object is a stat query.
        message.type = NR_QUERY_STATS;
        message.data.query_stats.dummy = 'd';
        processing_add_recvmsg(&message);

        // Free buffer.
        free(buffer.buff);
    }
}
