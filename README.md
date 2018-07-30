# RoboRTS-ros
--------
[![Build Status](https://travis-ci.org/RMSC-Team3/RoboRTS-SC.svg?branch=master)](https://travis-ci.org/RMSC-Team3/RoboRTS-SC)
## Description

 - RoboRTS : Main package wrapper from RoboRTS original version.
 - RoboRTS_Gazebo : Robot description and gazebo simulator for RoboRTS.
 - RoboRTS_Gazebo_Plugins : Gazebo plugins used in RoboRTS_Gazebo

## Usage

### Install ROS

Please follow [the installing and configuring ROS environment tutorial](http://wiki.ros.org/ROS/Tutorials/InstallingandConfiguringROSEnvironment) on ROS Wiki.

### Thirdparty Library

```shell
sudo apt-get install ros-kinetic-opencv3 ros-kinetic-cv-bridge ros-kinetic-image-transport ros-kinetic-stage-ros ros-kinetic-map-server ros-kinetic-laser-geometry ros-kinetic-interactive-markers ros-kinetic-tf ros-kinetic-pcl-* ros-kinetic-libg2o protobuf-compiler libprotobuf-dev libsuitesparse-dev libgoogle-glog-dev ros-kinetic-rviz
```
### Build

```bash
mkdir -p ~/roborts_ws/src
cd ~/roborts_ws/src
# Clone this repo to src folder
cd ~/roborts_ws/
catkin_make messages_generate_messages
catkin_make
```

### Run Simulator

```bash
source ~/roborts_ws/devel/setup.bash
roslaunch roborts navigation_stage.launch
```

## Copyright and License

RoboRTS is provided under the [GPL-v3](COPYING).
