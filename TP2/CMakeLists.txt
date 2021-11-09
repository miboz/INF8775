cmake_minimum_required(VERSION 3.20)
project(TP2)

set(CMAKE_CXX_STANDARD 20)

add_executable(TP2
        main.cpp utils.cpp Graph.cpp Graph.h Node.cpp Node.h GreedyAlgorithm.cpp GreedyAlgorithm.h BranchAndBound.cpp BranchAndBound.h TabuSearch.cpp TabuSearch.h updatable_priority_queue.h)
