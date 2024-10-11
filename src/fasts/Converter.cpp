#include "Converter.h"

// 16進数文字への変換テーブル
// 0-9とA-Fの文字を含む
const char Converter::hexLookup[] = {'0', '1', '2', '3', '4', '5', '6', '7',
                                     '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};

// 文字から数値への変換テーブル
// 0-9とA-Fの文字を数値に変換するためのテーブル
const uint8_t Converter::valueLookup[] = {
    0,  1,  2,  3,  4,  5,  6,  7, 8, 9, // 0-9
    58, 59, 60, 61, 62, 63, 64,          // パディング（使用されない値）
    10, 11, 12, 13, 14, 15,              // A-F
};

// バイトデータを16進数表現に変換する関数
// data: 入力バイトデータの配列
// length: 入力バイトデータの長さ
// output: 変換された16進数文字列を格納するための配列
void Converter::toHex(const uint8_t *data, size_t length, char *output) {
  for (size_t i = 0; i < length; ++i) {
    // 上位4ビットを取得し、16進数文字に変換
    output[i * 2] = hexLookup[data[i] >> 4 & 0x0F];
    // 下位4ビットを取得し、16進数文字に変換
    output[i * 2 + 1] = hexLookup[data[i] & 0x0F];
  }
}

// 16進数表現からバイトデータに変換する関数
// hexString: 入力16進数文字列
// length: 入力16進数文字列の長さ（偶数である必要がある）
// output: 変換されたバイトデータを格納するための配列
void Converter::fromHex(const char *hexString, size_t length, uint8_t *output) {
  for (size_t i = 0; i < length / 2; ++i) {
    // 16進数文字列から上位4ビットの文字を取得
    char upperChar = hexString[i * 2];
    // 16進数文字列から下位4ビットの文字を取得
    char lowerChar = hexString[i * 2 + 1];
    // 上位4ビットの文字を数値に変換
    uint8_t upperValue = valueLookup[upperChar - '0'];
    // 下位4ビットの文字を数値に変換
    uint8_t lowerValue = valueLookup[lowerChar - '0'];
    // 上位4ビットと下位4ビットを結合して1バイトの値にする
    output[i] = (upperValue << 4) | lowerValue;
  }
}