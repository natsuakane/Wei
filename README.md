# Wei-lang
我制作偽中国語之機械言語（笑）
適当言語

## 例
Fibonacci
```
関数「普伊墓那値」引数「数」行
「結果」是「数」
「数」大一場合「結果」是「普伊墓那値」（「数」引二）足「普伊墓那値」（「数」引一）
「結果」
終

「表示」（「普伊墓那値」（「入力」（『整数』）））
「表示」（「新行」）
```
入出力
```
10
55
```

本言語簡単物体定義可能
```
「亜」是物体《「伊」是三、「宇」是一》
「亜」之「伊」是五
「表示」（「亜」之「伊」）
「表示」（「新行」）
「表示」（「亜」之「宇」）
「表示」（「新行」）
「表示」（「亜」）
「表示」（「新行」）
```
出力
```
5
1
object(0x6000004d4840)
```

## 建築（Build）手順
```bash
git clone https://github.com/natsuakane/Wei-lang.git
cd Wei-lang
mkdir build
cd build
cmake ..
cmake --build .
```

## 実行方法
```
./weilang {FILE_NAME}
```
