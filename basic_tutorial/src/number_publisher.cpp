#include <ros/ros.h>
#include <std_msgs/Float32.h>


int main(int argc, char** argv)
{
  ros::init(argc, argv, "number_publisher");
  ros::NodeHandle nh;
  ros::Publisher pub = nh.advertise<std_msgs::Float32>("chatter", 10);
  ros::Rate loop_rate(10);


  while (ros::ok())
  {
    std_msgs::Float32 msg;
    msg.data = 123;
    
    pub.publish(msg);


    ros::spinOnce();
    loop_rate.sleep();
  }
  return 0;
}