#include <open62541/client_subscriptions.h>
#include <open62541/plugin/log_stdout.h>
#include <open62541/server.h>
#include <open62541/server_config_default.h>

#include <pthread.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>  //Header file for sleep(). man 3 sleep for details.

float valuetemp1 = 22.5;  // max value 35
float valuetemp2 = 27.5;  // max value 40
float valuetemp3 = 29.5;  // max value 45
float valuetemp4 = 17.5;  // max value 39


UA_Server *server;

static void
createstructureVerticalWarehouse(UA_Server *server) {
    UA_NodeId pumpId; /* get the nodeid assigned by the server */
    UA_ObjectAttributes oAttr = UA_ObjectAttributes_default;
    oAttr.displayName = UA_LOCALIZEDTEXT("en-US", "Vertical Warehouse");
    UA_Server_addObjectNode(
        server, UA_NODEID_NULL, UA_NODEID_NUMERIC(0, UA_NS0ID_OBJECTSFOLDER),
        UA_NODEID_NUMERIC(0, UA_NS0ID_ORGANIZES),
        UA_QUALIFIEDNAME(1, "Vertical Warehouse"),
        UA_NODEID_NUMERIC(0, UA_NS0ID_BASEOBJECTTYPE), oAttr, NULL, &pumpId);

    /* Define the attribute of the myInteger variable node */
    UA_VariableAttributes attrS1 = UA_VariableAttributes_default;
    UA_Float sens1 = valuetemp1;
    UA_Variant_setScalar(&attrS1.value, &sens1, &UA_TYPES[UA_TYPES_FLOAT]);
    attrS1.description = UA_LOCALIZEDTEXT("en-US", "Temp Sensor1");
    attrS1.displayName = UA_LOCALIZEDTEXT("en-US", "Temp Sensor1");
    attrS1.dataType = UA_TYPES[UA_TYPES_FLOAT].typeId;
    attrS1.accessLevel = UA_ACCESSLEVELMASK_READ | UA_ACCESSLEVELMASK_WRITE;

    /* Add the variable node to the information model */
    UA_NodeId nodeS1 = UA_NODEID_STRING(1, "Sensore1 di temperatura");
    UA_QualifiedName nodenameS1 = UA_QUALIFIEDNAME(1, "Sensore1 di temperatura");
    // UA_NodeId parentNodeIdS1 = UA_NODEID_NUMERIC(0, UA_NS0ID_OBJECTSFOLDER);
    UA_NodeId parentNodeS1 = UA_NODEID_NUMERIC(0, UA_NS0ID_ORGANIZES);
    // UA_Server_addVariableNode(server, nodeS1, pumpId, parentNodeS1, nodenameS1,
    // UA_NODEID_NUMERIC(0, UA_NS0ID_BASEDATAVARIABLETYPE), attrS1, NULL, &pumpId);
    UA_Server_addVariableNode(server, nodeS1, pumpId, parentNodeS1, nodenameS1,
                              UA_NODEID_NUMERIC(0, UA_NS0ID_BASEDATAVARIABLETYPE), attrS1,
                              NULL, &nodeS1);

    /* Define the attribute of the myInteger variable node */
    UA_VariableAttributes attrS2 = UA_VariableAttributes_default;
    UA_Float sens2 = valuetemp2;
    UA_Variant_setScalar(&attrS2.value, &sens2, &UA_TYPES[UA_TYPES_FLOAT]);
    attrS2.description = UA_LOCALIZEDTEXT("en-US", "Temp Sensor2");
    attrS2.displayName = UA_LOCALIZEDTEXT("en-US", "Temp Sensor2");
    attrS2.dataType = UA_TYPES[UA_TYPES_FLOAT].typeId;
    attrS2.accessLevel = UA_ACCESSLEVELMASK_READ | UA_ACCESSLEVELMASK_WRITE;

    /* Add the variable node to the information model */
    UA_NodeId nodeS2 = UA_NODEID_STRING(1, "Sensore2 di temperatura");
    UA_QualifiedName nodenameS2 = UA_QUALIFIEDNAME(1, "Sensore2 di temperatura");
    // UA_NodeId parentNodeId = UA_NODEID_NUMERIC(0, UA_NS0ID_OBJECTSFOLDER);
    UA_NodeId parentNodeS2 = UA_NODEID_NUMERIC(0, UA_NS0ID_ORGANIZES);
    UA_Server_addVariableNode(server, nodeS2, pumpId, parentNodeS2, nodenameS2,
                              UA_NODEID_NUMERIC(0, UA_NS0ID_BASEDATAVARIABLETYPE), attrS2,
                              NULL, &nodeS2);

    /* Define the attribute of the myInteger variable node */
    UA_VariableAttributes attrS3 = UA_VariableAttributes_default;
    UA_Float sens3 = valuetemp3;
    UA_Variant_setScalar(&attrS3.value, &sens3, &UA_TYPES[UA_TYPES_FLOAT]);
    attrS3.description = UA_LOCALIZEDTEXT("en-US", "Temp Sensor3");
    attrS3.displayName = UA_LOCALIZEDTEXT("en-US", "Temp Sensor3");
    attrS3.dataType = UA_TYPES[UA_TYPES_FLOAT].typeId;
    attrS3.accessLevel = UA_ACCESSLEVELMASK_READ | UA_ACCESSLEVELMASK_WRITE;

    /* Add the variable node to the information model */
    UA_NodeId nodeS3 = UA_NODEID_STRING(1, "Sensore3 di temperatura");
    UA_QualifiedName nodenameS3 = UA_QUALIFIEDNAME(1, "Sensore3 di temperatura");
    // UA_NodeId parentNodeId = UA_NODEID_NUMERIC(0, UA_NS0ID_OBJECTSFOLDER);
    UA_NodeId parentNodeS3 = UA_NODEID_NUMERIC(0, UA_NS0ID_ORGANIZES);
    UA_Server_addVariableNode(server, nodeS3, pumpId, parentNodeS3, nodenameS3,
                              UA_NODEID_NUMERIC(0, UA_NS0ID_BASEDATAVARIABLETYPE), attrS3,
                              NULL, &nodeS3);

    /* Define the attribute of the myInteger variable node */
    UA_VariableAttributes attrS4 = UA_VariableAttributes_default;
    UA_Float sens4 = valuetemp4;
    UA_Variant_setScalar(&attrS4.value, &sens4, &UA_TYPES[UA_TYPES_FLOAT]);
    attrS4.description = UA_LOCALIZEDTEXT("en-US", "Temp Sensore4");
    attrS4.displayName = UA_LOCALIZEDTEXT("en-US", "Temp Sensore4");
    attrS4.dataType = UA_TYPES[UA_TYPES_FLOAT].typeId;
    attrS4.accessLevel = UA_ACCESSLEVELMASK_READ | UA_ACCESSLEVELMASK_WRITE;

    /* Add the variable node to the information model */
    UA_NodeId nodeS4 = UA_NODEID_STRING(1, "Sensore4 di temperatura");
    UA_QualifiedName nodenameS4 = UA_QUALIFIEDNAME(1, "Sensore4 di temperatura");
    // UA_NodeId parentNodeId = UA_NODEID_NUMERIC(0, UA_NS0ID_OBJECTSFOLDER);
    UA_NodeId parentNodeS4 = UA_NODEID_NUMERIC(0, UA_NS0ID_ORGANIZES);
    UA_Server_addVariableNode(server, nodeS4, pumpId, parentNodeS4, nodenameS4,
                              UA_NODEID_NUMERIC(0, UA_NS0ID_BASEDATAVARIABLETYPE), attrS4,
                              NULL, &nodeS4);
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

    /* Write a different integer value */
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
changevaluetemps1(void *vargp) {
    while(true) {
        writeVariable(server, valuetemp1++, "Sensore1 di temperatura");
        if(valuetemp1 > 35)
            valuetemp1 = 22.5;
        sleep(10);  // 10 sec
    }
}

// A normal C function that is executed as a thread
// when its name is specified in pthread_create()
void *
changevaluetemps2(void *vargp) {
    while(true) {
        writeVariable(server, valuetemp2++, "Sensore2 di temperatura");
        if(valuetemp2 > 40)
            valuetemp2 = 27.5;
        sleep(30);  // 30 sec
    }
}

// A normal C function that is executed as a thread
// when its name is specified in pthread_create()
void *
changevaluetemps3(void *vargp) {
    while(true) {
        writeVariable(server, valuetemp3++, "Sensore3 di temperatura");
        if(valuetemp3 > 45)
            valuetemp3 = 29.5;
        sleep(15);  // 15 sec
    }
}

// A normal C function that is executed as a thread
// when its name is specified in pthread_create()
void *
changevaluetemps4(void *vargp) {
    while(true) {
        writeVariable(server, valuetemp4++, "Sensore4 di temperatura");
        if(valuetemp4 > 39)
            valuetemp4 = 17.5;
        sleep(60);  // 60 sec
    }
}

int
main(void) {
    signal(SIGINT, stopHandler);
    signal(SIGTERM, stopHandler);

    //define thread
    pthread_t threadSens1;
    pthread_t threadSens2;
    pthread_t threadSens3;
    pthread_t threadSens4;

    //create instance of server
    server = UA_Server_new();
    UA_ServerConfig_setDefault(UA_Server_getConfig(server));

    //start 4 thread
    int rc1 = pthread_create(&threadSens1, NULL, changevaluetemps1, NULL);
    if(rc1) {
        UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND, "ERROR: %i", rc1);
        exit(-1);
    }
    int rc2 = pthread_create(&threadSens2, NULL, changevaluetemps2, NULL);
    if(rc2) {
        UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND, "ERROR: %i", rc2);
        exit(-1);
    }
    int rc3 = pthread_create(&threadSens3, NULL, changevaluetemps3, NULL);
    if(rc3) {
        UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND, "ERROR: %i", rc3);
        exit(-1);
    }
    int rc4 = pthread_create(&threadSens4, NULL, changevaluetemps4, NULL);
    if(rc4) {
        UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND, "ERROR: %i", rc4);
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
    }
    retval = UA_Server_run_shutdown(server);

cleanup:
    UA_Server_delete(server);
    return retval == UA_STATUSCODE_GOOD ? EXIT_SUCCESS : EXIT_FAILURE;
}
