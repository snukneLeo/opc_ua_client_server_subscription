#include <open62541/client_subscriptions.h>
#include <open62541/plugin/log_stdout.h>
#include <open62541/server.h>
#include <open62541/server_config_default.h>

#include <pthread.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>  //Header file for sleep(). man 3 sleep for details.

float pressure = 22.5;  // max value 100
/*float valuetemp2 = 27.5;  // max value 40
float valuetemp3 = 29.5;  // max value 45
float valuetemp4 = 17.5;  // max value 39*/


UA_Server *server;

static void
createstructureVerticalWarehouse(UA_Server *server) {
    UA_NodeId pumpId; /* get the nodeid assigned by the server */
    UA_ObjectAttributes oAttr = UA_ObjectAttributes_default;
    oAttr.displayName = UA_LOCALIZEDTEXT("en-US", "Cell Robot");
    UA_Server_addObjectNode(
        server, UA_NODEID_NULL, UA_NODEID_NUMERIC(0, UA_NS0ID_OBJECTSFOLDER),
        UA_NODEID_NUMERIC(0, UA_NS0ID_ORGANIZES),
        UA_QUALIFIEDNAME(1, "Cell Robot"),
        UA_NODEID_NUMERIC(0, UA_NS0ID_BASEOBJECTTYPE), oAttr, NULL, &pumpId);

    /* Define the attribute of the myInteger variable node */
    UA_VariableAttributes attrS1 = UA_VariableAttributes_default;
    UA_Float sens1 = pressure;
    UA_Variant_setScalar(&attrS1.value, &sens1, &UA_TYPES[UA_TYPES_FLOAT]);
    attrS1.description = UA_LOCALIZEDTEXT("en-US", "Pressure Sensors");
    attrS1.displayName = UA_LOCALIZEDTEXT("en-US", "Pressure Sensors");
    attrS1.dataType = UA_TYPES[UA_TYPES_FLOAT].typeId;
    attrS1.accessLevel = UA_ACCESSLEVELMASK_READ | UA_ACCESSLEVELMASK_WRITE;

    /* Add the variable node to the information model */
    UA_NodeId nodeS1 = UA_NODEID_STRING(1, "Sensore di pressione Robot");
    UA_QualifiedName nodenameS1 = UA_QUALIFIEDNAME(1, "Sensore di pressione Robot");
    // UA_NodeId parentNodeIdS1 = UA_NODEID_NUMERIC(0, UA_NS0ID_OBJECTSFOLDER);
    UA_NodeId parentNodeS1 = UA_NODEID_NUMERIC(0, UA_NS0ID_ORGANIZES);
    // UA_Server_addVariableNode(server, nodeS1, pumpId, parentNodeS1, nodenameS1,
    // UA_NODEID_NUMERIC(0, UA_NS0ID_BASEDATAVARIABLETYPE), attrS1, NULL, &pumpId);
    UA_Server_addVariableNode(server, nodeS1, pumpId, parentNodeS1, nodenameS1,
                              UA_NODEID_NUMERIC(0, UA_NS0ID_BASEDATAVARIABLETYPE), attrS1,
                              NULL, &nodeS1);
}

static volatile UA_Boolean running = true;
static void
stopHandler(int sig) {
    UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND, "received ctrl-c");
    running = false;
}

/**
 * Now we change the value with the write service. This uses the same service
 * implementation that can also be reached over the network by an OPC UA client.
 */

static void
writeVariable(UA_Server *server, float value, char node[]) {
    UA_NodeId mynode = UA_NODEID_STRING(1, node);

    /* Write a different float value */
    UA_Float myInteger = value;
    UA_Variant myVar;
    UA_Variant_init(&myVar);
    UA_Variant_setScalar(&myVar, &myInteger, &UA_TYPES[UA_TYPES_FLOAT]);
    UA_Server_writeValue(server, mynode, myVar);

    /* Set the status code of the value to an error code. The function
     * UA_Server_write provides access to the raw service. The above
     * UA_Server_writeValue is syntactic sugar for writing a specific node
     * attribute with the write service. */
    UA_WriteValue wv;
    UA_WriteValue_init(&wv);
    wv.nodeId = mynode;
    wv.attributeId = UA_ATTRIBUTEID_VALUE;
    wv.value.status = UA_STATUSCODE_BADNOTCONNECTED;
    wv.value.hasStatus = true;
    UA_Server_write(server, &wv);

    /* Reset the variable to a good statuscode with a value */
    wv.value.hasStatus = false;
    wv.value.value = myVar;
    wv.value.hasValue = true;
    UA_Server_write(server, &wv);
}

// A normal C function that is executed as a thread
// when its name is specified in pthread_create()
void *
changevaluepressure(void *vargp) {
    while(true) {
        writeVariable(server, pressure++, "Sensore di pressione Robot");
        if(pressure > 100)
            pressure = 22.5;
        sleep(10);  // 10 sec
    }
}

int
main(void) {
    signal(SIGINT, stopHandler);
    signal(SIGTERM, stopHandler);

    pthread_t threadSens1;

    server = UA_Server_new();
    UA_ServerConfig_setDefault(UA_Server_getConfig(server));

    int rc1 = pthread_create(&threadSens1, NULL, changevaluepressure, NULL);
    if(rc1) {
        UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND, "ERROR: %i", rc1);
        exit(-1);
    }
    /* Should the server networklayer block (with a timeout) until a message
       arrives or should it return immediately? */
    UA_Boolean waitInternal = true;

    UA_StatusCode retval = UA_Server_run_startup(server);
    if(retval != UA_STATUSCODE_GOOD)
        goto cleanup;

    createstructureVerticalWarehouse(server);

    while(running) {
        /* timeout is the maximum possible delay (in millisec) until the next
           _iterate call. Otherwise, the server might miss an internal timeout
           or cannot react to messages with the promised responsiveness. */
        /* If multicast discovery server is enabled, the timeout does not not consider new
         * input data (requests) on the mDNS socket. It will be handled on the next call,
         * which may be too late for requesting clients. if needed, the select with
         * timeout on the multicast socket server->mdnsSocket (see example in mdnsd
         * library)
         */
        UA_UInt16 timeout = UA_Server_run_iterate(server, waitInternal);
        // printf("TIMEOUT SERVER: %i", timeout);

        /* writeVariable(server, valuetemp1++, "Sensore1 di temperatura");
        writeVariable(server, valuetemp2++, "Sensore2 di temperatura");
        writeVariable(server, valuetemp3++, "Sensore3 di temperatura");
        writeVariable(server, valuetemp4++, "Sensore4 di temperatura");*/

        /*if(valuetemp1 > 35)
            valuetemp1 = 22.5;
        if(valuetemp2 > 40)
            valuetemp2 = 27.5;
        if(valuetemp3 > 45)
            valuetemp3 = 29.5;
        if(valuetemp4 > 39)
            valuetemp4 = 17.5;*/

        /* Now we can use the max timeout to do something else. In this case, we
           just sleep. (select is used as a platform-independent sleep
           function.) */
        /*struct timeval tv;
        tv.tv_sec = 0;
        tv.tv_usec = (timeout)*1000;
        select(0, NULL, NULL, NULL, &tv);

        UA_sleep_ms(tv.tv_usec);*/
    }
    retval = UA_Server_run_shutdown(server);
    // thread_join(thread_id, NULL);

cleanup:
    UA_Server_delete(server);
    return retval == UA_STATUSCODE_GOOD ? EXIT_SUCCESS : EXIT_FAILURE;
}
