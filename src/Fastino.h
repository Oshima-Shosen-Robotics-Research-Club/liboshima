/**
 * @file main.cpp
 * @brief アプリケーションのメインエントリポイント。
 *
 * このファイルには、メイン関数とセットアップおよびループ関数の宣言が含まれています。
 * ！注意！：現時点では正常に機能しません。（だれかよろしくお願いします）
 */

#pragma once

#include <stddef.h>
#include <stdint.h>

/**
 * @brief システムの初期化を行います。
 *
 * この関数は、必要な設定を行い、メインループに入る前に
 * 必要なコンポーネントを初期化します。
 */
inline void setup();

/**
 * @brief アプリケーションのメインループ。
 *
 * この関数は、セットアップが完了した後に継続的に実行される
 * ロジックを含んでいます。アプリケーションのコア機能を
 * 処理します。
 */
inline void loop();

/**
 * @brief メイン関数。
 *
 * アプリケーションのエントリポイントです。この関数は
 * 一度セットアップ関数を呼び出し、その後無限ループに入り
 * ループ関数を繰り返し呼び出します。
 *
 * @return int アプリケーションの終了ステータス（常に0を返します）。
 */
int main() {
  setup();
  while (true) {
    loop();
  }
  return 0;
}