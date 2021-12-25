# ros debug toolsについて
開発において一回でうまくいくことはまずない。  
うまく行っていない原因をいち早く追求するために存在するのがdebug toolである。

## rostopic
topicについてのdebug toolである
### rostopic list
システム上のtopicのリストを確認することが出来る。
```
# rostopic list
/chatter
/rosout
/rosout_agg
```

### rostopic echo
topicの中身を見ることができる。
```
# rostopic echo /chatter
data: 123.0
---
data: 123.0
---
data: 123.0
---
```

### rostopic pub
topicをpublishすることが出来る。
```
rostopic pub /chatter std_msgs/Float32 "data: 111.0"
```
またオプションとして「-r 10」とつけることで10Hzでpublishし続けることが出来る。
```
rostopic pub -r 10 /chatter std_msgs/Float32 "data: 111.0"
```

### rostopic info
対象のtopicのmessage type、pub subをしているノードの情報を見ることができる。
```
# rostopic info /chatter 
Type: std_msgs/Float32

Publishers: 
 * /number_publisher (http://ubuntu:37775/)

Subscribers: 
 * /number_subscriber (http://ubuntu:44399/)
```

## rqt_graph
現在起動しているノードの一覧、繋がっているtopicを画像情報として確認することが出来る。
```
rqt_graph
```
![Screenshot from 2021-12-25 04-49-45](https://user-images.githubusercontent.com/38370926/147385447-c4e1d0dc-88af-4335-aa68-de3a0ad9b7e9.png)
ROSで実用のシステムを作動させる際，下図のように複雑となるため画像情報を表示させるのは有用である．
![134777815-eceb9985-c178-4d70-a401-cdee52b49079](https://user-images.githubusercontent.com/38370926/147385513-d1500d91-10dd-4d86-bed2-47e15495d523.png)
