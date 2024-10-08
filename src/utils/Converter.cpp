#include "Converter.h"

// 16進数文字への変換テーブル
const char Converter::hexLookup[] = {'0', '1', '2', '3', '4', '5', '6', '7',
                                     '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};

// 文字から数値への変換テーブル
const uint8_t Converter::valueLookup[] = {
    0,  1,  2,  3,  4,  5,  6,  7, 8, 9, // 0-9
    58, 59, 60, 61, 62, 63, 64,          // パディング
    10, 11, 12, 13, 14, 15,              // A-F
};

// バイトデータを16進数表現に変換する関数
void Converter::toHex(const uint8_t *data, size_t length, char *output) {
  for (size_t i = 0; i < length; ++i) {
    output[i * 2] = hexLookup[data[i] >> 4 & 0x0F];       // 上位4ビットを取得
    output[i * 2 + 1] = hexLookup[data[i] & 0x0F]; // 下位4ビットを取得
  }
}

// 16進数表現からバイトデータに変換する関数
void Converter::fromHex(const char *hexString, size_t length, uint8_t *output) {
  for (size_t i = 0; i < length / 2; ++i) {
    char upperChar = hexString[i * 2];
    char lowerChar = hexString[i * 2 + 1];
    uint8_t upperValue = valueLookup[upperChar - '0'];
    uint8_t lowerValue = valueLookup[lowerChar - '0'];
    output[i] =
        (upperValue << 4) | lowerValue; // 上位4ビットと下位4ビットを結合
  }
}
