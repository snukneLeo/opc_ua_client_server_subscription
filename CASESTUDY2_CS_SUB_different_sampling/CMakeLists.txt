cmake_minimum_required(VERSION 3.10.2)
project(leo_problem)

#SET(CMAKE_CXX_STANDARD "17") 
#SET(CMAKE_CXX_EXTENSIONS "OFF")
SET(CMAKE_C_FLAGS "-std=c99 -lpthread -pthread")

#link_directories("../../../build/lib") #PATH ALLA LIBRERIA (SE IN usr/local non serve)
#include_directories("../../../build/include") #PATH ALLA INCLUDE (SE IN usr/local non serve)
#set(CLIENT_TEST "myclient.c") #SORGENTI
#set(SERVER_TEST "TestServerTesi.c") #SORGENTI
#set(SEARCH "client_find_servers.c") #SORGENTI
#set(LOOP_CLIENT "client_connect_loop.c") #SORGENTI
set(CLIENT_SUB1 "client1.c") #SORGENTI
set(CLIENT_SUB2 "client2.c") #SORGENTI
set(SERVER_TEST "server_test.c") #SORGENTI

#add_executable(CLIENT ${CLIENT_TEST}) #NOME ESEGUIBILE
add_executable(SERVER ${SERVER_TEST}) #NOME ESEGUIBILE
#add_executable(FIND ${SEARCH}) #NOME ESEGUIBILE
#add_executable(LOOP ${LOOP_CLIENT}) #NOME ESEGUIBILE
add_executable(C1 ${CLIENT_SUB1}) #NOME ESEGUIBILE
add_executable(C2 ${CLIENT_SUB2}) #NOME ESEGUIBILE

#target_link_libraries(CLIENT open62541)
target_link_libraries(SERVER open62541) 
#target_link_libraries(FIND open62541)
#target_link_libraries(LOOP open62541)
target_link_libraries(C1 open62541)
target_link_libraries(C2 open62541)

