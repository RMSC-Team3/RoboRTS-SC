cmake_minimum_required(VERSION 2.8.3)
project(roborts_gazebo_plugins)

find_package(catkin REQUIRED COMPONENTS roscpp std_msgs std_srvs geometry_msgs nav_msgs tf dynamic_reconfigure message_generation)
include_directories(${catkin_INCLUDE_DIRS})

find_package(gazebo REQUIRED)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${GAZEBO_CXX_FLAGS}")
include_directories(${GAZEBO_INCLUDE_DIRS})
link_directories(${GAZEBO_LIBRARY_DIRS})

generate_dynamic_reconfigure_options(
        cfg/UWB.cfg
        cfg/OmniMovePid.cfg
)

catkin_package(
        CATKIN_DEPENDS roscpp std_msgs geometry_msgs nav_msgs tf message_runtime
        INCLUDE_DIRS
        LIBRARIES
)

add_library(roborts_gazebo_ros_uwb src/roborts_gazebo_ros_uwb.cpp src/roborts_gazebo_ros_uwb.h)
target_link_libraries(roborts_gazebo_ros_uwb ${GAZEBO_LIBRARIES} ${catkin_LIBRARIES})

add_library(roborts_gazebo_ros_force_based_omni_move
        src/roborts_gazebo_ros_force_based_omni_move.cpp
        src/roborts_gazebo_ros_force_based_omni_move.h
        src/pid.h
        )
add_dependencies(roborts_gazebo_ros_force_based_omni_move roborts_gazebo_plugins_gencfg)
target_link_libraries(roborts_gazebo_ros_force_based_omni_move ${GAZEBO_LIBRARIES} ${catkin_LIBRARIES})

install(TARGETS
        roborts_gazebo_ros_uwb
        roborts_gazebo_ros_force_based_omni_move
        ARCHIVE DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
        LIBRARY DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
        RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
        )