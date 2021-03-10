/* This work is licensed under a Creative Commons CCZero 1.0 Universal License.
 * See http://creativecommons.org/publicdomain/zero/1.0/ for more information. */

/**
 * Client disconnect handling
 * --------------------------
 * This example shows you how to handle a client disconnect, e.g., if the server
 * is shut down while the client is connected. You just need to call connect
 * again and the client will automatically reconnect.
 *
 * This example is very similar to the tutorial_client_firststeps.c. */

#include <open62541/client_config_default.h>
#include <open62541/client_subscriptions.h>
#include <open62541/plugin/log_stdout.h>

#include <signal.h>
#include <stdlib.h>

bool ENABLE_BROWSE = true;

static void
createsub(UA_Client *client);  // define method for subscrption

UA_Boolean running = true;

static void
stopHandler(int sign) {
    UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND, "Received Ctrl-C");
    running = 0;
}

static void
handler_currentTemp1(UA_Client *client, UA_UInt32 subId, void *subContext,
                     UA_UInt32 monId, void *monContext, UA_DataValue *value) {
    // PRINT CHANGE VALUE
    UA_Float dato = *(UA_Float *)value->value.data;
    // printf("SENSOR1: %i", dato);
    UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND, "S1 TEMP: %.2f", dato);
}

static void
handler_currentTemp2(UA_Client *client, UA_UInt32 subId, void *subContext,
                     UA_UInt32 monId, void *monContext, UA_DataValue *value) {
    // PRINT CHANGE VALUE
    UA_Float dato = *(UA_Float *)value->value.data;
    // printf("SENSOR2: %i", dato);
    UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND, "S2 PRESS: %.2f", dato);
}
static void
handler_currentTemp3(UA_Client *client, UA_UInt32 subId, void *subContext,
                     UA_UInt32 monId, void *monContext, UA_DataValue *value) {
    // PRINT CHANGE VALUE
    UA_Float dato = *(UA_Float *)value->value.data;
    // printf("SENSOR3: %i", dato);
    UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND, "S3 TEMP: %.2f", dato);
}
static void
handler_currentTemp4(UA_Client *client, UA_UInt32 subId, void *subContext,
                     UA_UInt32 monId, void *monContext, UA_DataValue *value) {
    // PRINT CHANGE VALUE
    UA_Float dato = *(UA_Float *)value->value.data;
    // printf("SENSOR4: %i", dato);
    UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND, "S4 VIBRA: %.2f", dato);
}

static void
deleteSubscriptionCallback(UA_Client *client, UA_UInt32 subscriptionId,
                           void *subscriptionContext) {
    UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND, "Subscription Id %u was deleted",
                subscriptionId);
}

static void
subscriptionInactivityCallback(UA_Client *client, UA_UInt32 subId, void *subContext) {
    UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND, "Inactivity for subscription %u",
                subId);
}

static void
stateCallback(UA_Client *client, UA_SecureChannelState channelState,
              UA_SessionState sessionState, UA_StatusCode recoveryStatus) {
    switch(channelState) {
        case UA_SECURECHANNELSTATE_CLOSED:
            UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND,
                        "The client is disconnected");
            break;
        case UA_SECURECHANNELSTATE_HEL_SENT:
            UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND, "Waiting for ack");
            break;
        case UA_SECURECHANNELSTATE_OPN_SENT:
            UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND,
                        "Waiting for OPN Response");
            break;
        case UA_SECURECHANNELSTATE_OPEN:
            UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND,
                        "A SecureChannel to the server is open");
            break;
        default:
            break;
    }

    switch(sessionState) {
        case UA_SESSIONSTATE_ACTIVATED: {
            UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND,
                        "A session with the server is activated");

            // call method for subscription
            createsub(client);

        } break;
        case UA_SESSIONSTATE_CLOSED:
            UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND, "Session disconnected");
            break;
        default:
            break;
    }
}

// create subscription
static void
createsub(UA_Client *client) {
    /* A new session was created. We need to create the subscription. */
    /* Create a subscription */
    UA_CreateSubscriptionRequest request = UA_CreateSubscriptionRequest_default();
    request.requestedPublishingInterval = 10000.0;  // 10 sec
    request.requestedLifetimeCount = 1000;
    request.requestedMaxKeepAliveCount = 10;
    request.maxNotificationsPerPublish = 0;
    request.publishingEnabled = true;
    request.priority = 0;
    UA_CreateSubscriptionResponse response = UA_Client_Subscriptions_create(
        client, request, NULL, NULL, deleteSubscriptionCallback);

    if(response.responseHeader.serviceResult == UA_STATUSCODE_GOOD)
        UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND,
                    "Create subscription succeeded, id %u", response.subscriptionId);
    else
        return;

    // ADD MONITORED ITEM DEI SENSORI DELLA TEMPERATURA
    // UA_NodeId temp = UA_NODEID_STRING(1, "Sensore di temperatura");
    UA_MonitoredItemCreateRequest mirTemp1 = UA_MonitoredItemCreateRequest_default(
        UA_NODEID_STRING(1, "Sensore1 di temperatura"));
    UA_MonitoredItemCreateResult monTemp1 = UA_Client_MonitoredItems_createDataChange(
        client, response.subscriptionId, UA_TIMESTAMPSTORETURN_BOTH, mirTemp1, NULL,
        handler_currentTemp1, NULL);

    if(monTemp1.statusCode == UA_STATUSCODE_GOOD)
        UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND,
                    "Monitoring UA_NS0ID_INTEGER, id %u", monTemp1.monitoredItemId);

    // second subscription
    /* A new session was created. We need to create the subscription. */
    /* Create a subscription */
    UA_CreateSubscriptionRequest request2 = UA_CreateSubscriptionRequest_default();
    request2.requestedPublishingInterval = 30000.0;  // 30 sec
    request2.requestedLifetimeCount = 1000;
    request2.requestedMaxKeepAliveCount = 10;
    request2.maxNotificationsPerPublish = 0;
    request2.publishingEnabled = true;
    request2.priority = 0;
    UA_CreateSubscriptionResponse response2 = UA_Client_Subscriptions_create(
        client, request2, NULL, NULL, deleteSubscriptionCallback);

    if(response2.responseHeader.serviceResult == UA_STATUSCODE_GOOD)
        UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND,
                    "Create subscription succeeded, id %u", response2.subscriptionId);
    else
        return;

    // ADD MONITORED ITEM DEI SENSORI DELLA TEMPERATURA
    // UA_NodeId temp = UA_NODEID_STRING(1, "Sensore di temperatura");
    UA_MonitoredItemCreateRequest mirTemp2 = UA_MonitoredItemCreateRequest_default(
        UA_NODEID_STRING(1, "Sensore2 di pressione"));
    UA_MonitoredItemCreateResult monTemp2 = UA_Client_MonitoredItems_createDataChange(
        client, response2.subscriptionId, UA_TIMESTAMPSTORETURN_BOTH, mirTemp2, NULL,
        handler_currentTemp2, NULL);

    if(monTemp2.statusCode == UA_STATUSCODE_GOOD)
        UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND,
                    "Monitoring UA_NS0ID_INTEGER, id %u", monTemp2.monitoredItemId);

    // third subscription
    /* A new session was created. We need to create the subscription. */
    /* Create a subscription */
    UA_CreateSubscriptionRequest request3 = UA_CreateSubscriptionRequest_default();
    request3.requestedPublishingInterval = 15000.0;  // 15 sec
    request3.requestedLifetimeCount = 1000;
    request3.requestedMaxKeepAliveCount = 10;
    request3.maxNotificationsPerPublish = 0;
    request3.publishingEnabled = true;
    request3.priority = 0;
    UA_CreateSubscriptionResponse response3 = UA_Client_Subscriptions_create(
        client, request3, NULL, NULL, deleteSubscriptionCallback);

    if(response3.responseHeader.serviceResult == UA_STATUSCODE_GOOD)
        UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND,
                    "Create subscription succeeded, id %u", response3.subscriptionId);
    else
        return;

    // ADD MONITORED ITEM DEI SENSORI DELLA TEMPERATURA
    // UA_NodeId temp = UA_NODEID_STRING(1, "Sensore di temperatura");
    UA_MonitoredItemCreateRequest mirTemp3 = UA_MonitoredItemCreateRequest_default(
        UA_NODEID_STRING(1, "Sensore3 di temperatura"));
    UA_MonitoredItemCreateResult monTemp3 = UA_Client_MonitoredItems_createDataChange(
        client, response3.subscriptionId, UA_TIMESTAMPSTORETURN_BOTH, mirTemp3, NULL,
        handler_currentTemp3, NULL);

    if(monTemp3.statusCode == UA_STATUSCODE_GOOD)
        UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND,
                    "Monitoring UA_NS0ID_INTEGER, id %u", monTemp3.monitoredItemId);

    // fourth subscription
    /* A new session was created. We need to create the subscription. */
    /* Create a subscription */
    UA_CreateSubscriptionRequest request4 = UA_CreateSubscriptionRequest_default();
    request4.requestedPublishingInterval = 60000.0;  // 60 sec
    request4.requestedLifetimeCount = 1000;
    request4.requestedMaxKeepAliveCount = 10;
    request4.maxNotificationsPerPublish = 0;
    request4.publishingEnabled = true;
    request4.priority = 0;
    UA_CreateSubscriptionResponse response4 = UA_Client_Subscriptions_create(
        client, request4, NULL, NULL, deleteSubscriptionCallback);

    if(response4.responseHeader.serviceResult == UA_STATUSCODE_GOOD)
        UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND,
                    "Create subscription succeeded, id %u", response4.subscriptionId);
    else
        return;

    // ADD MONITORED ITEM DEI SENSORI DELLA TEMPERATURA
    // UA_NodeId temp = UA_NODEID_STRING(1, "Sensore di temperatura");
    UA_MonitoredItemCreateRequest mirTemp4 = UA_MonitoredItemCreateRequest_default(
        UA_NODEID_STRING(1, "Sensore4 di vibrazione"));
    UA_MonitoredItemCreateResult monTemp4 = UA_Client_MonitoredItems_createDataChange(
        client, response4.subscriptionId, UA_TIMESTAMPSTORETURN_BOTH, mirTemp4, NULL,
        handler_currentTemp4, NULL);

    if(monTemp4.statusCode == UA_STATUSCODE_GOOD)
        UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND,
                    "Monitoring UA_NS0ID_INTEGER, id %u", monTemp4.monitoredItemId);
}

int
main(void) {
    signal(SIGINT, stopHandler); /* catches ctrl-c */

    UA_Client *client = UA_Client_new();
    UA_ClientConfig *cc = UA_Client_getConfig(client);
    UA_ClientConfig_setDefault(cc);

    /* Set stateCallback */
    cc->stateCallback = stateCallback;
    cc->subscriptionInactivityCallback = subscriptionInactivityCallback;

    /* Endless loop runAsync */
    while(running) {
        /* if already connected, this will return GOOD and do nothing */
        /* if the connection is closed/errored, the connection will be reset and then
         * reconnected */
        /* Alternatively you can also use UA_Client_getState to get the current state */
        UA_StatusCode retval = UA_Client_connect(client, "opc.tcp://localhost:4840");

        if(retval != UA_STATUSCODE_GOOD) {
            UA_LOG_ERROR(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND,
                         "Not connected. Retrying to connect in 1 second");
            /* The connect may timeout after 1 second (see above) or it may fail
             * immediately on network errors */
            /* E.g. name resolution errors or unreachable network. Thus there should be a
             * small sleep here */
            UA_sleep_ms(1000);
            continue;
        }

        if(ENABLE_BROWSE) {
            /* Browse some objects */
            printf("Browsing nodes in objects folder:\n");
            UA_BrowseRequest bReq;
            UA_BrowseRequest_init(&bReq);
            bReq.requestedMaxReferencesPerNode = 0;
            bReq.nodesToBrowse = UA_BrowseDescription_new();
            bReq.nodesToBrowseSize = 1;
            bReq.nodesToBrowse[0].nodeId =
                UA_NODEID_NUMERIC(0, UA_NS0ID_OBJECTSFOLDER); /* browse objects folder */
            bReq.nodesToBrowse[0].resultMask =
                UA_BROWSERESULTMASK_ALL; /* return everything */
            UA_BrowseResponse bResp = UA_Client_Service_browse(client, bReq);
            printf("%-9s %-16s %-16s %-16s\n", "NAMESPACE", "NODEID", "BROWSE NAME",
                   "DISPLAY NAME");
            for(size_t i = 0; i < bResp.resultsSize; ++i) {
                for(size_t j = 0; j < bResp.results[i].referencesSize; ++j) {
                    UA_ReferenceDescription *ref = &(bResp.results[i].references[j]);
                    if(ref->nodeId.nodeId.identifierType == UA_NODEIDTYPE_NUMERIC) {
                        printf("%-9d %-16d %-16.*s %-16.*s\n",
                               ref->nodeId.nodeId.namespaceIndex,
                               ref->nodeId.nodeId.identifier.numeric,
                               (int)ref->browseName.name.length,
                               ref->browseName.name.data,
                               (int)ref->displayName.text.length,
                               ref->displayName.text.data);
                    } else if(ref->nodeId.nodeId.identifierType == UA_NODEIDTYPE_STRING) {
                        printf("%-9d %-16.*s %-16.*s %-16.*s\n",
                               ref->nodeId.nodeId.namespaceIndex,
                               (int)ref->nodeId.nodeId.identifier.string.length,
                               ref->nodeId.nodeId.identifier.string.data,
                               (int)ref->browseName.name.length,
                               ref->browseName.name.data,
                               (int)ref->displayName.text.length,
                               ref->displayName.text.data);
                    }
                    /* TODO: distinguish further types */
                }
            }
            UA_BrowseRequest_clear(&bReq);
            UA_BrowseResponse_clear(&bResp);
            ENABLE_BROWSE = false;
        }
        UA_Client_run_iterate(client, 30000);  // 30000 --> 30 sec
    };

    /* Clean up */
    UA_Client_delete(client); /* Disconnects the client internally */
    return EXIT_SUCCESS;
}
