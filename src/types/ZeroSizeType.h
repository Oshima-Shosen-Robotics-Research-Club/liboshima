/**
 * @file ZeroSizeType.h
 * @brief サイズ0の配列型の定義
 *
 * このファイルは、特定の用途で使われるサイズ0の配列型 `ZeroSizeType`
 * を定義します。サイズ0の配列型は、メモリ効率化や特殊な型表現に使用されます。
 * 通常の配列とは異なり、実際のメモリを消費しないため、特定の条件下で
 * メモリの無駄を省くことができます。
 */

#pragma once

#include <stdint.h>

/**
 * @typedef ZeroSizeType
 * @brief サイズ0の配列型
 *
 * `ZeroSizeType` は、サイズ0の配列型を定義します。この型は、
 * メモリ効率化や特殊な型表現に使用されます。例えば、構造体の一部として
 * 使用することで、条件付きでメモリを節約することができます。
 * サイズ0の配列は、実際にはメモリを消費しないため、
 * メモリフットプリントを最小限に抑えることができます。
 */
using ZeroSizeType = uint8_t[0];