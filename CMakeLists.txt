cmake_minimum_required(VERSION 3.26)
project(AED2324_PRJ2_G109)

set(CMAKE_CXX_STANDARD 17)

add_executable(AED2324_PRJ2_G109
        main.cpp
        DataModel/Airline.cpp
        DataModel/Airline.h
        DataModel/Airport.cpp
        DataModel/Airport.h
        DataStructure/Edge.h
        DataStructure/Edge.cpp
        DataStructure/Vertex.h
        DataStructure/Vertex.cpp
        DataStructure/Graph.h
        DataStructure/Graph.cpp
        Managers/Parser.cpp
        Managers/Parser.h
        Managers/Manager.cpp
        Managers/Manager.h)
