# publish、subscribe実装

## package作成
以下のコマンドを用いてpackage作成
```
catkin_create_pkg basic_tutorial roscp rospy std_mss tf
```

## publish
```
// src/number_publisher.cpp

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
```
### headerファイルのinclude
```
#include <ros/ros.h>
#include <std_msgs/Float32.h>
```
rosのpublish、subscribeを提供している<ros/ros.h>
topicのmessage typeの一つである<std_msgs/Float32.h>

### nodeの初期化
```
ros::init(argc, argv, "number_publisher");
```
第一、二引数(argc,argv)　プログラムの引数  
第3引数("number_publisher")　ノードの名前。通常ソースファイルの名前と一緒にする。

### publisherの宣言
```
ros::NodeHandle nh;
```
publisherのためのNodeHandleのインスタンスを作成
```
ros::Publisher pub = nh.advertise<std_msgs::Float32>("chatter", 10);
```
publisherの宣言。  
nh.advertise<(topicのmessage type)>("(topic名)", (バッファサイズ（最初はそこまで気にせず10程度で)));

### nodeの更新周期の宣言
```
ros::Rate loop_rate(10);
```
10hzでノードを動かすという意味

### ノードのメイン処理を記述
```
while (ros::ok()) //nodeの動作確認
{
    std_msgs::Float32 msg; //messageの型宣言
    msg.data = 123; //Float32のmsgのdataに数値を入れる
    
    pub.publish(msg); //ここでtopicを送信（の命令）


    ros::spinOnce(); //rosの更新処理(実はここでpublishが実行される)
    loop_rate.sleep(); //宣言した更新周期になるようプログラムを休止
}
```
    


## subscribe
```
// src/number_subscriber.cpp

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
```
### callback関数の記述
```
void chatterCallback(const std_msgs::Float32& msg)
{
  ROS_INFO("subscribe: %f", msg.data); //rosのcout（コンソール出力）的な
}
```
引数(const std_msgs::Float32& msg) : 受け取るtopic(const 参照←わからない人は「c++ const 参照」でぐぐってみよう!)  
ROS_INFO("subscribe: %f", msg.data); ←printfと使いかた同じ

### subscriberの宣言
```
ros::Subscriber sub = nh.subscribe("chatter", 10, chatterCallback);
```
subscriberの宣言。
nh.subscribe("(topic名)", (バッファサイズ), (topicを受け取るcallback関数));

### ros::spin()について
```
while(ros::ok())
{
    ros::spin();
}
```
spinOnceと役割は同じ。違いとしてはspinの場合callback関数の中身しか実行されない。(while(ros::ok()){}の中身が今後実行されることはない)

## コンパイルについて
以下のようにCMakeListsを編集
```
//CMakeLists.txt

//以下を追加

add_executable(number_publisher   src/number_publisher.cpp)
target_link_libraries(number_publisher
  ${catkin_LIBRARIES}
)
add_executable(number_subscriber   src/number_subscriber.cpp)
target_link_libraries(number_subscriber
  ${catkin_LIBRARIES}
)
```

コンパイルには以下のコマンドを使う
```
catkin build
```
コンパイルが無事成功したら以下を実行。  
変更内容を更新する。
```
cd ~/catkin_ws
source devel/setup.bash
```

## 実行
実行には以下のコマンドを用いる  

１つめのterminal  
rosのシステムの起動にはroscoreが必ず必要である
```
roscore
```
2つめのterminal  
rosrun package名 node名
```
rosrun ros_basic number_publisher
```
  
3つめのterminal
```
rosrun ros_basic number_subscriber
```
うまくいっていると以下の画像のようになる。
![Screenshot from 2021-12-25 04-33-05](https://user-images.githubusercontent.com/38370926/147384917-55942a89-97c0-4fec-8143-559f5cce3984.png)
