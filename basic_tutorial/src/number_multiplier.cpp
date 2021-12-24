#include <ros/ros.h>
#include <std_msgs/Float32.h>

std_msgs::Float32 num;
void chatterCallback(const std_msgs::Float32& msg)
{
  num.data = 2 * msg.data;
}

int main(int argc, char** argv)
{
  ros::init(argc, argv, "number_subscriber");
  ros::NodeHandle nh;
  ros::Subscriber sub = nh.subscribe("number", 10, chatterCallback);
  ros::Publisher pub = nh.advertise<std_msgs::Float32>("result", 10);

  while(ros::ok())
  {
      pub.publish(num);
      ros::spinOnce();
  }
  return 0;
}