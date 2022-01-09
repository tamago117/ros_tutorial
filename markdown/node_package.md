# ROSの簡単な仕組み

## publish、subscribe
ROSでは各ノード（プログラム）間でトピックという情報をやり取りすることでプログラムの細分化が簡単になっている。このトピックを話す方を「publisher」、聞く方を「subscriber」という。
![image](https://user-images.githubusercontent.com/38370926/148685935-9713f623-76f5-4c43-a4d8-451b0eaddc5d.png)


### 実際のケースに当てはめると以下のようになるだろう。
![image](https://user-images.githubusercontent.com/38370926/148685842-02951cfd-1b28-4bcc-ad44-924f17703f5e.png)


### また細分化できるというということはシステムの全体設計、プログラムの再利用が簡単になる。
![image](https://user-images.githubusercontent.com/38370926/148685877-a377a375-fbd9-42c7-9290-6ae7f5acf1c8.png)
![image](https://user-images.githubusercontent.com/38370926/148685900-2ec15c5c-0605-4b56-85cd-fd1e101f7acf.png)

## nodeについて
nodeではソースコードを一つ動作させることになる。このノードを複数立ち上げられる、つまりソースコードの並列化が簡単にできるため複雑なシステムも簡単につくることが出来る。

## packageについて
packageとは複数のnodeをまとめた入れ物のような概念である。（ファイルに対するフォルダ的な）nodeを実行する際、どこのpackageの何のnodeを立ち上げるといった記述をすることになる。
![image](https://user-images.githubusercontent.com/38370926/148686010-c896e3ef-807d-43a6-992a-66ee8148763a.png)
