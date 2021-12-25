# 主要なmessage typeについて
rosのmessageではstructでmessageの型を定義している。  
## std_msgs/Float32
float32の数値を渡す
float32 data
## std_msgs/Float32MultiArray
配列上にデータを渡す
std_msgs/MultiArrayLayout layout
float32[] data
## std_msgs/String
stringを渡す
string data
## geometry_msgs/Twist
ロボットへの指令値送信に使う。
http://docs.ros.org/en/melodic/api/geometry_msgs/html/msg/Twist.html
## nav_msgs/PoseStamped
3次元座標、角度を示すのに使う
http://docs.ros.org/en/noetic/api/geometry_msgs/html/msg/PoseStamped.html

## nav_msgs/Path
ロボットの走行経路を示すのに使う
http://docs.ros.org/en/noetic/api/nav_msgs/html/msg/Path.html

またmessageは自分でも作れるので無限に存在する。ぜひ自分でも色々調べてみてほしい。