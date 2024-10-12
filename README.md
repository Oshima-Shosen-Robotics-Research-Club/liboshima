## PlatformIOでの使い方

- `platformio.ini`に以下を追加する。
    ```
    lib_deps = liboshima
    ```
    又は
    ```
    lib_deps = https://github.com/Oshima-Shosen-Robotics-Research-Club/liboshima
    ```
- プログラムの中で以下のように使う。(examplesフォルダを参照)
    ```cpp
    #include <libohima.h>
    ```

## Arduino IDEでの使い方

- Library Managerから"liboshima"を検索してインストールする。
- プログラムの中で以下のように使う。(examplesフォルダを参照)
    ```cpp
    #include <liboshima.h>
    ```

## PlatformIO Library Registry

[https://registry.platformio.org/libraries/oshima-shosen-robotics-research-club/liboshima](https://registry.platformio.org/libraries/oshima-shosen-robotics-research-club/liboshima)

## Library Manager

[https://www.ardu-badge.com/liboshima](https://www.ardu-badge.com/liboshima)

## こころがけていること

- 様々なプラットフォームで動作するようにすること
- String型などのメモリを消費する型を使わないこと
- 不必要な処理や重い処理を含むライブラリ関数を使わないこと
- フォルダ内に存在するファイルの数が、大きすぎず、小さすぎないようにすること
- スコープの広い物には、名前空間やクラス名でアクセスするようにすること
    - 例: `IM920SL::SEND_INTERVAL_MS`（defineを使わない）
    - 例外: `FastSerial`（ArduinoのSerialに似せるため）
- インライン展開すべきクラスは、ヘッダファイルに実装すること

## git cloneできない場合

- `git config --global http.postBuffer 524288000`
- WiFiの代わりにモバイルデータ通信や有線LANを使う

## このリポジトリの変更の仕方

- [https://github.com/Oshima-Shosen-Robotics-Research-Club/library-workspace](https://github.com/Oshima-Shosen-Robotics-Research-Club/library-workspace) をVisual Studio Codeでクローンする。
- クローンしたフォルダをVisual Studio Codeで開く。
- `lib`ディレクトリに移動する。
- そこでこのリポジトリをVisual Studio Codeでクローンする。
- このリポジトリに変更を加える。
- このリポジトリの変更をコミットする。
- このリポジトリの変更をプッシュする。

## ブランチの使い方

### developブランチ

- 新しい機能や修正を開発するためのブランチである。
- このブランチでの変更は、動作確認がされるまで`stable`ブランチにはマージされない。
- もし`platformio.ini`で`develop`ブランチを指定するには、以下のようにする。
    ```
    lib_deps = https://github.com/Oshima-Shosen-Robotics-Research-Club/liboshima#develop
    ```

### stableブランチ

- 安定版のコードが含まれるブランチですある。
- 直接コミットすることはなく、マージのみ行う。
- 十分に動作確認された変更のみがこのブランチにマージされる。
- もし`platformio.ini`で`stable`ブランチを指定するには、以下のようにする。
    ```
    lib_deps = https://github.com/Oshima-Shosen-Robotics-Research-Club/liboshima#stable
    ```

## todo

- `develop`ブランチのiniの`#develop`指定を`stable`ブランチには反映させないようにする。