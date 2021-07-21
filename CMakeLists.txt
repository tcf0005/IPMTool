cmake_minimum_required(VERSION 2.8)
project( IPMTool )                                 #replace test
find_package( OpenCV REQUIRED )
add_executable( IPMTool IPMTool.cpp )                 #replace test and test.cpp
target_link_libraries( IPMTool ${OpenCV_LIBS} )    #replace test