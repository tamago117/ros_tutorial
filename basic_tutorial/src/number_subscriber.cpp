#include <ros/ros.h>
#include <std_msgs/Float32.h>

void chatterCallback(const std_msgs::Float32& msg)
{
  ROS_INFO("subscribe: %f", msg.data);
}

int main(int argc, char** argv)
{
  ros::init(argc, argv, "number_subscriber");
  ros::NodeHandle nh;
  ros::Subscriber sub = nh.subscribe("chatter", 10, chatterCallback);

  while(ros::ok())
  {
      ros::spin();
  }
  
  return 0;
}