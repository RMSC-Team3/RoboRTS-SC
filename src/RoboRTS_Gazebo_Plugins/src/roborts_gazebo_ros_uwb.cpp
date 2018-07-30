
#include "roborts_gazebo_ros_uwb.h"

namespace gazebo{

GazeboRosUwb::GazeboRosUwb() {

}
GazeboRosUwb::~GazeboRosUwb() {
  updateTimer.Disconnect(updateConnection);
  node_handle_->shutdown();
  delete node_handle_;
}

void GazeboRosUwb::Load(physics::ModelPtr _model, sdf::ElementPtr _sdf) {

  ROS_INFO("Load Uwb Plugin");

  world = _model->GetWorld();

//  world->

  // load parameters
  if (!_sdf->HasElement("robotNamespace"))
    namespace_.clear();
  else
    namespace_ = _sdf->GetElement("robotNamespace")->GetValue()->GetAsString();

  if (!_sdf->HasElement("body_name"))
  {
    link = _model->GetLink();
    link_name_ = link->GetName();
  }
  else {
    link_name_ = _sdf->GetElement("body_name")->GetValue()->GetAsString();
    link = _model->GetLink(link_name_);
  }

  if (!link)
  {
    ROS_FATAL("GazeboRosUwb plugin error: bodyName: %s does not exist\n", link_name_.c_str());
    return;
  }

  // default parameters
  frame_id_ = "uwb";
  uwb_topic_ = "uwb";
  uwb_noise_x_ = uwb_noise_y_ = 0.03;

  if (_sdf->HasElement("frame_id"))
    frame_id_ = _sdf->GetElement("frame_id")->GetValue()->GetAsString();

  if (_sdf->HasElement("topic_name"))
    uwb_topic_ = _sdf->GetElement("topic_name")->GetValue()->GetAsString();

  if (_sdf->HasElement("gaussian_noise")){
    uwb_noise_x_ = _sdf->GetElement("gaussian_noise")->GetValue()->Get(uwb_noise_x_);
    uwb_noise_y_ = _sdf->GetElement("gaussian_noise")->GetValue()->Get(uwb_noise_y_);
  }

  if (!ros::isInitialized())
  {
    ROS_FATAL_STREAM("A ROS node for Gazebo has not been initialized, unable to load plugin. "
                         << "Load the Gazebo system plugin 'libgazebo_ros_api_plugin.so' in the gazebo_ros package)");
    return;
  }

  node_handle_ = new ros::NodeHandle(namespace_);
  uwb_publisher_ = node_handle_->advertise<geometry_msgs::PoseStamped>(uwb_topic_, 10);


  dynamic_reconfigure_server_.reset(new dynamic_reconfigure::Server<UWBConfig>(ros::NodeHandle(*node_handle_, uwb_topic_ + "/noise")));

  dynamic_reconfigure_server_->setCallback(boost::bind(&GazeboRosUwb::DynamicReconfigureCallback,this,_1,_2));

  Reset();
  updateTimer.setUpdateRate(20);
  updateTimer.Load(world, _sdf);
  updateConnection = updateTimer.Connect(boost::bind(&GazeboRosUwb::Update,this));

}


void GazeboRosUwb::Reset() {
  ModelPlugin::Reset();
}

void GazeboRosUwb::DynamicReconfigureCallback(GazeboRosUwb::UWBConfig &config, uint32_t level)
{
  if (level == 1) {
    uwb_noise_x_ = config.gaussian_noise_position;
    uwb_noise_y_ = config.gaussian_noise_position;
  } else{
    config.gaussian_noise_position = (uwb_noise_x_ + uwb_noise_y_) / 2.0;
  }
}

void GazeboRosUwb::Update() {
  common::Time sim_time = world->GetSimTime();
//  double dt = updateTimer.getTimeSinceLastUpdate().Double();
  math::Pose pose = link->GetWorldPose();
  math::Vector3 pose_vec = ErrorModel(pose);
  uwb_pose_msg_.header.frame_id = frame_id_;
  uwb_pose_msg_.header.stamp = ros::Time::now();
  uwb_pose_msg_.pose.position.x = pose_vec.x;
  uwb_pose_msg_.pose.position.y = pose_vec.y;
  uwb_pose_msg_.pose.position.z = pose_vec.z;
  uwb_publisher_.publish(uwb_pose_msg_);
}

gazebo::math::Vector3 GazeboRosUwb::ErrorModel(math::Pose pose){
  gazebo::math::Vector3 pose_with_noise;
  pose_with_noise.x = pose.pos.x + SensorModelGaussianKernel<double>(0.0,uwb_noise_x_);
  pose_with_noise.y = pose.pos.y + SensorModelGaussianKernel<double>(0.0,uwb_noise_y_);
  pose_with_noise.z = pose.pos.z;
  return  pose_with_noise;
}

GZ_REGISTER_MODEL_PLUGIN(GazeboRosUwb)

}