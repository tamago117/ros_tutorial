# launchについて
前回までの項では一つ一つのterminalでrosのノードを起動していた。しかし、これでは多数のノードを起動するのは大変な作業となる  
そこでrosのシステム全体を起動するためのシステムとしてlaunchが存在する。launchではlaunchファイルに起動するノードの情報を記述し、roslaunchを用いて起動する。  
## pubsubのlaunch化
### launch ファイルの記述
例としてpubsubのシステムをlaunchで記述してみよう。
```
#launch/pubsub.launch
<launch>
  <node name="number_publisher"   pkg="basic_tutorial" type="number_publisher" />
  <node name="number_subscriber" pkg="basic_tutorial" type="number_subscriber" output="screen"/>
</launch>
```
launchファイルではxml形式で開始タグ```<tag>```から閉じタグ```</tag>```までの間を一つの要素として記述する。  
launchファイルで起動するノードの記述は下記のようにする。
```
<node name="ノードの名前（自由につけられる、つまり同じノードを名前を変えて複数立ち上げられる）"   pkg="ノードのあるパッケージ名" type="ノードの名前（CMakeListsで記述した名前と同じにする）" output="screen"(terminalに情報を画面出力(coutとか))/>
```
### launchの立ち上げ
```
roslaunch basic_tutorial pubsub.launch
```

## 既存パッケージのシステムへの組み込み
ここで既存パッケージを自分のシステムへの組み込みを想定してみよう。下記のようなノードがあったとする。
```
number_multiplier : std_msgs/Float32の数値を定数倍（2倍）して返すノード

sub : std_msgs/Float32 topic名："/number"
pub : std_msgs/Float32 topic名："/result"
```
現状、このままではtopic名が一致していないためノード間でtopicの受け渡しをすることができない。また、できればソースコードの方でtopic名を変えることは好ましくない。（再利用ができないため）そこでlaunchの「remap」を使ってnodeのtopic名を変えてみよう。

```
#launch/pubsub_remap.launch
<launch>
  <node name="number_publisher"   pkg="basic_tutorial" type="number_publisher" >
    <remap from="chatter" to="number"/>
  </node>
  <node name="number_multiplier"   pkg="basic_tutorial" type="number_multiplier" />
  <node name="number_subscriber" pkg="basic_tutorial" type="number_subscriber" output="screen">
    <remap from="chatter" to="result"/>
</node>
</launch>
```
remapの記法としては下記のようになる。
```
<remap from="元topic名" to="変更後topic名"/>
```

正しく動作している場合、以下のようになる。
```
[ INFO] [1640440694.282695598]: subscribe: 246.000000
```
/numberと/resultのtopicの中身を確認すれば正しく定数倍できていることが確認出来るはずだ。
