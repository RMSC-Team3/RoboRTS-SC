#ifndef PROJECT_GAZEBOROSUWB_H
#define PROJECT_GAZEBOROSUWB_H

#include <gazebo/common/Plugin.hh>
#include <gazebo/physics/physics.hh>
#include <ros/ros.h>
#include <geometry_msgs/PoseStamped.h>
#include <dynamic_reconfigure/server.h>
#include <roborts_gazebo_plugins/UWBConfig.h>
#include "update_timer.h"

namespace gazebo {

class GazeboRosUwb : public ModelPlugin {

 public:
  GazeboRosUwb();
  virtual ~GazeboRosUwb();

 protected:
  virtual void Load(physics::ModelPtr _model, sdf::ElementPtr _sdf);
  virtual void Reset();
  virtual void Update();

  typedef roborts_gazebo_plugins::UWBConfig UWBConfig;
  void DynamicReconfigureCallback(GazeboRosUwb::UWBConfig &config,
                                                uint32_t level);
 private:
  gazebo::math::Vector3 ErrorModel(math::Pose pose);

 private:

  /// \brief The parent World
  physics::WorldPtr world;

  /// \brief The link referred to by this plugin
  physics::LinkPtr link;

  ros::NodeHandle* node_handle_;
  ros::Publisher uwb_publisher_;

  boost::shared_ptr<dynamic_reconfigure::Server<UWBConfig>> dynamic_reconfigure_server_;

  std::string namespace_;
  std::string link_name_;
  std::string frame_id_;
  std::string uwb_topic_;

  event::ConnectionPtr updateConnection;
  UpdateTimer updateTimer;

  double uwb_noise_x_ = 0.03;
  double uwb_noise_y_ = 0.03;
  geometry_msgs::PoseStamped uwb_pose_msg_;

  template <typename T>
  static inline T SensorModelGaussianKernel(T mu, T sigma)
  {
    // using Box-Muller transform to generate two independent standard normally distributed normal variables
    // see wikipedia
    T U = (T)rand()/(T)RAND_MAX; // normalized uniform random variable
    T V = (T)rand()/(T)RAND_MAX; // normalized uniform random variable
    T X = sqrt(-2.0 * ::log(U)) * cos( 2.0*M_PI * V);
    X = sigma * X + mu;
    return X;
  }

};


}
#endif //PROJECT_GAZEBOROSUWB_H
