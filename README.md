## PlatformIOでの使い方

- `platformio.ini`に以下を追加する。
    ```
    lib_deps = liboshima
    ```
    又は
    ```
    lib_deps = https://github.com/Oshima-Shosen-Robotics-Research-Club/liboshima
    ```
- プログラムの中で以下のように使う。(examplesフォルダを参照。)
    ```cpp
    #include <liboshima.h>
    ```

## Arduino IDEでの使い方

- Library Managerから"liboshima"を検索してインストールする。
- プログラムの中で以下のように使う。(examplesフォルダを参照。)
    ```cpp
    #include <liboshima.h>
    ```

## PlatformIO Library Registry

[https://registry.platformio.org/libraries/oshima-shosen-robotics-research-club/liboshima](https://registry.platformio.org/libraries/oshima-shosen-robotics-research-club/liboshima)

## Library Manager

[https://www.ardu-badge.com/liboshima](https://www.ardu-badge.com/liboshima)

## こころがけていること

- 様々なプラットフォームで動作するようにすること。
- String型などのメモリを消費する型を使わないこと。
- 不必要な処理や重い処理を含むライブラリ関数を使わないこと。
- フォルダ内に存在するファイルの数が、大きすぎず、小さすぎないようにすること。
- スコープの広い物には、名前空間やクラス名でアクセスするようにすること。
  - 例外: `FastSerial`（ArduinoのSerialに似せるため。）
- インライン展開すべきクラスは、ヘッダファイルに実装すること。

## git cloneできない場合

- `git config --global http.postBuffer 524288000`
  - This command increases the buffer size for HTTP POST requests to 500MB, which can help resolve issues when cloning large repositories or pushing large commits.
- WiFiの代わりにモバイルデータ通信や有線LANを使う。

## このリポジトリの開発環境

[https://github.com/Oshima-Shosen-Robotics-Research-Club/library-workspace](https://github.com/Oshima-Shosen-Robotics-Research-Club/library-workspace) を参照。

## versionを上げる方法

- `library.json`の`version`を変更する。
- `library.properties`の`version`を変更する。
- pushすると、GitHub Actionsが自動で新しいバージョンをリリースする。
- 数時間待つと使えるようになる。