#pragma once

#include <stddef.h>
#include <stdint.h>

class Converter {
public:
    // 16進数表現に変換
    static void toHex(const uint8_t* data, size_t length, char* output);

    // 16進数表現からバイトデータに変換
    static void fromHex(const char* hexString, size_t length, uint8_t* output);

private:
    // 16進数用の変換表 (0-9, A-F)
    static const char hexLookup[16];
    // 16進数文字列から数値への変換表
    static const uint8_t valueLookup[23];
};
