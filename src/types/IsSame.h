/**
 * @file IsSame.h
 * @brief 型の同一性をチェックするテンプレートクラス
 *
 * このヘッダーファイルでは、2つの型が同一であるかどうかをコンパイル時にチェックする
 * テンプレートクラス `IsSame` を定義します。
 * このクラスは、2つの型が同一である場合に `true` を、異なる場合に `false`
 * を返します。
 */

#pragma once

/**
 * @brief 2つの型が異なる場合の部分特殊化
 *
 * このテンプレートクラスは、2つの型 `T` と `U`
 * が異なる場合に部分特殊化されます。 `value` は `false` に設定されます。
 *
 * @tparam T チェック対象の最初の型。
 * @tparam U チェック対象の2番目の型。
 */
template <typename T, typename U> struct IsSame {
  /// 型 `T` と `U` が異なるため、`value` は `false`。
  static const bool value = false;
};

/**
 * @brief 2つの型が同一である場合の部分特殊化
 *
 * このテンプレートクラスは、2つの型 `T` が同一である場合に部分特殊化されます。
 * `value` は `true` に設定されます。
 *
 * @tparam T チェック対象の型。
 */
template <typename T> struct IsSame<T, T> {
  /// 型 `T` が同一であるため、`value` は `true`。
  static const bool value = true;
};