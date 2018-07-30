# RoboRTS Gazebo Plugin 

## 1. roborts_gazebo_ros_force_based_omni_move

Use force (torque) control the mobile robot for omni-directional movement with dynamic character.

### 1.1 Subscribe Topics

* cmd_vel (`geometry_msgs/Twist`)

  Target velocity for mobile robot.

### 1.2 Publish Topics

* odom (`nav_msgs/Odometry`)

  Publish odometry message by DR.


* tf (`tf/tfMessage`)

​	Publishes the transform from `odom` to  `robot_base_frame`.

### 1.3 XML Param

* robot_base_frame (`string`, default: "base_link")
* robot_namespace (`string`, default: "")
* cmd_vel_topic (`string`, default: "cmd_vel")
* odom_topic (`string`, default: "odom")
* odom_frame (`string`, default: "odom")
* odom_rate (`double`, default: 20)
* publish_odom_tf (`bool`, default: true)
* rotation_velocity_p_gain (`double`, default: 400)
* velocity_x_p_gain (`double`, default: 10000)
* velocity_y_p_gain (`double`, default: 10000)

### 1.4 Dynamic Param

* vel_x_kp (`double`, default: 10000)
* vel_y_kp (`double`, default: 10000)
* vel_rot_kp (`double`, default: 40000)
* vel_x_ki (`double`, default: 0)
* vel_y_ki (`double`, default: 0)
* vel_rot_ki (`double`, default: 0)
* vel_x_kd (`double`, default: 0)
* vel_y_kd (`double`, default: 0)
* vel_rot_kd (`double`, default: 0)