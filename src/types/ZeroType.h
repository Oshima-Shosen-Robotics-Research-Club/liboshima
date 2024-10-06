/**
 * @file ZeroType.h
 * @brief サイズ0の配列型の定義
 *
 * このファイルは、特定の用途で使われるサイズ0の配列型 `ZeroSizeType`
 * を定義します。 メモリ効率化や特殊な型表現に使用されます。
 */

#pragma once

#include <stdint.h>

/// サイズ0の配列型の定義（用途に応じて使用）
using ZeroSizeType = uint8_t[0];
