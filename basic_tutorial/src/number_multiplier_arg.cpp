#include <ros/ros.h>
#include <std_msgs/Float32.h>



float number;
void chatterCallback(const std_msgs::Float32& msg)
{
  number = msg.data;
}

int main(int argc, char** argv)
{
  float mulNum;
  
  ros::init(argc, argv, "number_subscriber");
  ros::NodeHandle nh;
  ros::NodeHandle pnh("~");
  pnh.getParam("multiNum", mulNum);
  ros::Subscriber sub = nh.subscribe("number", 10, chatterCallback);
  ros::Publisher pub = nh.advertise<std_msgs::Float32>("result", 10);

  std_msgs::Float32 num;
  while(ros::ok())
  {
      num.data = number * mulNum;
      pub.publish(num);
      ros::spinOnce();
  }
  return 0;
}