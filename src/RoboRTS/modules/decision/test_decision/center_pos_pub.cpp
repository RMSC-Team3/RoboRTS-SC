#include <std_msgs/Int32.h>
#include <ros/time.h>
#include <actionlib/client/simple_action_client.h>
#include <actionlib/client/terminal_state.h>
#include <thread>
#include "messages/GlobalPlannerAction.h"
#include "messages/LocalPlannerAction.h"
#include <geometry_msgs/PoseWithCovarianceStamped.h>
#include "modules/decision/behavior_tree/blackboard.h"
#include "messages/ShootState.h"
#include "modules/driver/serial/infantry_info.h"
#include "modules/decision/behavior_tree/blackboard.h"
#include <nav_msgs/Odometry.h>
#include <geometry_msgs/Twist.h>
#include <messages/EnemyPos.h>
#include <termios.h>
#include <fcntl.h>

int bboxoffset;

void bulletboxoffset_Callback(const std_msgs::Int32::ConstPtr& msg) {
  bboxoffset = msg->data;      
  ROS_INFO("dasvj %d :____: %d", bboxoffset , msg->data);
}

double x_coord;
void amcl_Callback(const geometry_msgs::PoseWithCovarianceStamped::ConstPtr& msg) {
  x_coord = msg->pose.pose.position.x;      
}


double x_vel;
double y_vel;
void cmd_vel_Callback(const geometry_msgs::Twist::ConstPtr& msg) {
    x_vel = msg->linear.x;
    y_vel = msg->linear.y;
}
geometry_msgs::Twist chassis_data;
messages::ShootModeControl shoot_data;
geometry_msgs::PoseStamped center;


void init_data()
{
  //bboxoffset = (int*) malloc(len(int));
  chassis_data.linear.x  = 0.0;
  chassis_data.linear.y  = 0.0;
  chassis_data.linear.z  = 0.0;
  chassis_data.angular.z = 0.0;

  shoot_data.request.c_shoot_cmd = 0;
  shoot_data.request.fric_wheel_run = 0;

  center.pose.position.x = 3.7;
  center.pose.position.y = 2.8;
  center.pose.orientation.w = 1.0;
}

int main(int argc, char **argv)
{

  ros::init(argc, argv, "center_goal"); //node name
  init_data();
  ros::NodeHandle n;
  ros::Publisher center_pos_pub = n.advertise<geometry_msgs::PoseStamped>("center_pos", 50); //rostopic /center_pos
  //ros::Subscriber bulletboxoffset_sub_ = n.subscribe<std_msgs::Int32>("bulletBox_offset", 1, bulletboxoffset_Callback);
  ros::Subscriber amcl_sub_ = n.subscribe<geometry_msgs::PoseWithCovarianceStamped>("amcl_pose", 2, amcl_Callback);
  //ros::Subscriber cmd_vel_sub_ = n.subscribe<geometry_msgs::Twist>("cmd_vel", 1, cmd_vel_Callback);
  ros::Publisher pub_chassis_cantrol = n.advertise<geometry_msgs::Twist>("cmd_vel", 1000);
  //ros::Publisher pub_shoot_control   = n.advertise<messages::ShootState>("shoot_cmd", 1000);
  ros::ServiceClient shoot_cmd_client = n.serviceClient<messages::ShootModeControl>("shoot_mode_control");
  ros::Rate loop_rate(500);      

  while (ros::ok) {
      //ROS_INFO("bboxoffset %d", bboxoffset);
      ros::spinOnce();
//      bool gripped = false;
      if (x_coord < 3.1) {
        center_pos_pub.publish(center);
      } 
      else if (x_coord >= 3.1 && x_coord < 3.65) {
        shoot_data.request.c_shoot_cmd = 2; //drop
	    shoot_cmd_client.call(shoot_data);

        chassis_data.linear.x = 0.5;
        pub_chassis_cantrol.publish(chassis_data);//forward
      }
      else {
        shoot_data.request.c_shoot_cmd = 1; //lift
	    shoot_cmd_client.call(shoot_data);

         ros::Duration(10).sleep();
        
      }
      
      
      
      
      
      /*
      if (bboxoffset < 200 || bboxoffset > 400 || bboxoffset == 0) {
           //ROS_INFO("bboxoffset %d", bboxoffset);
        center_pos_pub.publish(center);
      }
      //adjust
      if (chassis_data.linear.x == 0.0 && chassis_data.linear.y == 0.0){
          if (bboxoffset > 350) {
            chassis_data.linear.x = 0.5;
            pub_chassis_cantrol.publish(chassis_data);
	          ROS_INFO("czxczx");
          }
          else if (bboxoffset < 280) {
            ROS_INFO("qyyqyy");
            chassis_data.linear.x = -0.5;
            pub_chassis_cantrol.publish(chassis_data);
          }
        }
      
      //Grip
      bool gripped = false;
      
      if (bboxoffset > 280 && bboxoffset < 350 && !gripped) {
        ROS_INFO("Gripping cmd sent.");
        chassis_data.linear.x = 0.0;
        chassis_data.linear.y = 0.0;
        pub_chassis_cantrol.publish(chassis_data);
        shoot_data.request.c_shoot_cmd = 1;
        shoot_data.request.fric_wheel_run = 1;
        //pub_shoot_control.publish(shoot_data);
	shoot_cmd_client.call(shoot_data);
 	ros::Duration(5).sleep();
	shoot_data.request.c_shoot_cmd = 2;
        shoot_data.request.fric_wheel_run = 1;
	shoot_cmd_client.call(shoot_data);
	gripped = true;

      }
        

      ROS_INFO ("x:  y:  ");
      ROS_INFO ("%f", chassis_data.linear.x);
      ROS_INFO ("%f", chassis_data.linear.y);
      */
      loop_rate.sleep();
  }
    
  
  
  return 0;
}
