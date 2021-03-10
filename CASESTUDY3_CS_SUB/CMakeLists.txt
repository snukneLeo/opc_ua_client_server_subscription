cmake_minimum_required(VERSION 3.10.2)
project(leo_problem)

#SET(CMAKE_CXX_STANDARD "17") 
#SET(CMAKE_CXX_EXTENSIONS "OFF")
SET(CMAKE_C_FLAGS "-std=c99 -lpthread -pthread")

#link_directories("../../../build/lib") #PATH ALLA LIBRERIA (SE IN usr/local non serve)
#include_directories("../../../build/include") #PATH ALLA INCLUDE (SE IN usr/local non serve)
set(Server1 "server1.c") #SORGENTI
set(Server2 "server2.c") #SORGENTI
set(Client1 "client1.c") #SORGENTI
set(Client2 "client2.c") #SORGENTI
set(Client3 "client3.c") #SORGENTI

add_executable(SERVER1 ${Server1}) #NOME ESEGUIBILE
add_executable(SERVER2 ${Server2}) #NOME ESEGUIBILE
add_executable(CLIENT1 ${Client1}) #NOME ESEGUIBILE
add_executable(CLIENT2 ${Client2}) #NOME ESEGUIBILE
add_executable(CLIENT3 ${Client3}) #NOME ESEGUIBILE


target_link_libraries(SERVER1 open62541)
target_link_libraries(SERVER2 open62541)
target_link_libraries(CLIENT1 open62541)
target_link_libraries(CLIENT2 open62541)
target_link_libraries(CLIENT3 open62541)

