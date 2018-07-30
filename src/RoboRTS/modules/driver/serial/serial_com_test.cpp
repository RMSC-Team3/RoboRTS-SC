#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include <messages/EnemyPos.h>
#include <messages/ShootState.h>
#include <messages/ShootModeControl.h>
#include <termios.h>
#include <fcntl.h>

//using namespace std;

geometry_msgs::Twist chassis_data;
messages::ShootModeControl shoot_data;
float def_v = 0.3;

void init_data()
{
  chassis_data.linear.x  = 0.0;
  chassis_data.linear.y  = 0.0;
  chassis_data.linear.z  = 0.0;
  chassis_data.angular.z = 0.0;

  //shoot_data.request.shoot_cmd = 0;
  shoot_data.request.c_shoot_cmd = 0;
  shoot_data.request.fric_wheel_run = 0;
  //shoot_data.grip_czx = 0;
}

void move(char cmd)
{
  init_data();
  switch(cmd)
  {
    case 'w':
      def_v = 0.3;
      chassis_data.linear.x  =  def_v;
      break;
    case 's':
      def_v = 0.3;
      chassis_data.linear.x  = -def_v;
      break;
    case 'a':
      def_v = 0.3;
      chassis_data.linear.y  =  def_v;
      break;

    case 'd':
      def_v = 0.3;
      chassis_data.linear.y  = -def_v;
      break;
    case 'r':
      def_v = 0.3;
      chassis_data.angular.z =  def_v;
      break;
    case 'f':
      def_v = 0.3;
      chassis_data.angular.z = -def_v;
      break;
    case 'u':
      def_v = 0;
      break;
    case 'h':
      //shoot_data.request.shoot_cmd = 0;
      shoot_data.request.c_shoot_cmd = 1;
      shoot_data.request.fric_wheel_run = 0;
      break;
    case 'j':
      //shoot_data.request.shoot_cmd = 1;
      shoot_data.request.c_shoot_cmd = 2;
      shoot_data.request.fric_wheel_run = 0;
    break;
    case 'l':
      //shoot_data.request.shoot_cmd = 1;
      shoot_data.request.c_shoot_cmd = 0;
      shoot_data.request.fric_wheel_run = 0;
    break;
   
/*
    case 'g':
      shoot_data.grip_czx = 1;
      break;
*/
  }
}


void kbhit()
{
  struct termios oldt, newt;
  char ch;
  int oldf;
  tcgetattr(STDIN_FILENO, &oldt);
  newt = oldt;
  newt.c_lflag &= ~(ICANON | ECHO);
  tcsetattr(STDIN_FILENO, TCSANOW, &newt);
  oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
  fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);
  ch = getchar();
  tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
  fcntl(STDIN_FILENO, F_SETFL, oldf);
  if(ch=='w'||ch=='s'||ch=='a'||ch=='d'||ch=='r'||ch=='f'||ch=='h'||ch=='j'||ch=='l')
  {
    printf("You entered a character %c.", ch);
    printf("\nPlease enter your comment:\n");
    //ungetc(ch, stdin);
    move(ch);
  }
  //else
  //    ungetc(ch, stdin);
}

void ClearShootData() {
  //shoot_data.request.shoot_cmd = 0;
  shoot_data.request.c_shoot_cmd = 0;
  shoot_data.request.fric_wheel_run = 0;
}

int main(int argc, char** argv)
{
  ros::init(argc, argv, "car_console");
  init_data();
  ros::NodeHandle n;
  ros::Publisher pub_chassis_cantrol = n.advertise<geometry_msgs::Twist>("cmd_vel", 1000);
  //ros::Publisher pub_shoot_control   = n.advertise<messages::ShootState>("shoot_cmd", 1000);
  ros::ServiceClient shoot_cmd_client = n.serviceClient<messages::ShootModeControl>("shoot_mode_control");

  ros::Rate loop_rate(100);
  printf("Please enter your comment:\n");
  while(n.ok())
  {
    ros::spinOnce();
    kbhit();
    pub_chassis_cantrol.publish(chassis_data);
    //ros::Time now = ros::Time::now();
    //while (ros::Time::now() < now + ros::Duration(5)) {
      shoot_cmd_client.call(shoot_data);
    //}
	//shoot_data.request.c_shoot_cmd = 2;
    //    shoot_data.request.fric_wheel_run = 1;
	//shoot_cmd_client.call(shoot_data);

    loop_rate.sleep();
  }
}
