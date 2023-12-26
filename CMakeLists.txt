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
        Managers/Manager.h
        Menu/State.h
        Menu/State.cpp
        Menu/MainMenuState.h
        Menu/MainMenuState.cpp
        Menu/MenuManager.h
        Menu/MenuManager.cpp
        Menu/FlightSearchState.cpp
        Menu/FlightSearchState.cpp
        Menu/ChooseTypeOfAirportState.h
        Menu/ChooseTypeOfAirportState.cpp
        Menu/FilterState.h
        Menu/FilterState.cpp
        Menu/CoordinatesFilterState.h
        Menu/CoordinatesFilterState.cpp
        Menu/StatisticsState1.h
        Menu/StatisticsState1.cpp
        Menu/StatisticsState2.h
        Menu/StatisticsState2.cpp
        Menu/StatisticsStateCity.cpp
        Menu/StatisticsState3.h
        Menu/StatisticsState3.cpp
        Menu/StatisticsState4.h
        Menu/StatisticsState4.cpp
)
