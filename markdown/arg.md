# node、launchへのパラメータ渡し
システムを動作させる際、いくつか動作上のパラメータを変更したい時があるだろう。この項ではノードへのパラメータの渡し方を学習する。  
試しに前回の項のnumber_multiplierの定数倍のところの数値を変更出来るようにしてみよう。
## nodeへのパラメータ渡し
```
// src/number_multiplier_arg.cpp
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
  
  ros::init(argc, argv, "number_");
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
```

ここで注目すべきが下記の文だ
```
ros::NodeHandle pnh("~");
pnh.getParam("multiNum", mulNum);
```
ここでmultiNumがparameterにあたる  
それではCmakeLists.txtに以下の文を追加しコンパイルしてみよう
```
//CMakeLists.txt

//以下を追加

add_executable(number_multiplier_arg   src/number_multiplier_arg.cpp)
target_link_libraries(number_multiplier_arg
  ${catkin_LIBRARIES}
)

```
```
catkin build
cd ~/catkin_ws
source devel/setup.bash
```

## launchへのパラメータ渡し
それでは新しく作ったnodeをlaunchに組み込み起動してみよう
```
<launch>
  <arg name="multiNum" default="2"/>

  <node name="number_publisher"   pkg="basic_tutorial" type="number_publisher" >
    <remap from="chatter" to="number"/>
  </node>
  <node name="number_multiplier_arg"   pkg="basic_tutorial" type="number_multiplier_arg" >
    <param name="multiNum" value="$(arg multiNum)"/>
  </node>
  <node name="number_subscriber" pkg="basic_tutorial" type="number_subscriber" output="screen">
    <remap from="chatter" to="result"/>
  </node>
</launch>
```
ここで注目するのは以下の2文だ  
まずparamでlaunch→nodeへのパラメータ渡しをすることが出来る。
```
<param name="multiNum" value="$(arg multiNum)"/>
```
```
<param name="パラメータの名前" value="パラメータの値"/>
```
次にargにてlaunchへのパラメータ渡しをすることが出来る。
```
<arg name="multiNum" default="2"/>
```
```
<arg name="名前" default="値"/>
```
それでは実際にパラメータを渡して起動してみよう
```
roslaunch basic_tutorial pubsub_arg.launch multiNum:=10
```
正しく動作していれば以下のようになるはずだ
```
[ INFO] [1640442811.100315048]: subscribe: 1230.000000
```
