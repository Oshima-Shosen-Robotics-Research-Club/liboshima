/**
 * @file Conditional.h
 * @brief 条件に基づいて型を選択するテンプレートクラス
 *
 * このヘッダーファイルでは、コンパイル時の条件に基づいて型を選択する
 * テンプレートクラス `Conditional` を定義します。
 * `std::conditional` に似た機能を提供し、条件に応じて `TrueType` または
 * `FalseType` のどちらかを選択します。
 *
 * @tparam condition コンパイル時の条件（`true` または `false`）。
 * @tparam TrueType `condition` が `true` の場合に選択される型。
 * @tparam FalseType `condition` が `false` の場合に選択される型。
 */

#pragma once

/**
 * @brief コンパイル時条件に基づき型を選択するクラス（`true`の場合）
 *
 * このクラスは、テンプレート引数 `condition` が `true` である場合に
 * `TrueType` を選択します。
 *
 * @tparam condition コンパイル時の条件（`true`）。
 * @tparam TrueType `condition` が `true` の場合に選択される型。
 * @tparam FalseType `condition` が `false` の場合に選択される型。
 */
template <bool condition, typename TrueType, typename FalseType>
struct Conditional {
  /// `condition` が `true` の場合に選択される型を定義
  using Type = TrueType;
};

/**
 * @brief コンパイル時条件に基づき型を選択するクラス（`false`の場合）
 *
 * このクラスは、テンプレート引数 `condition` が `false` である場合に
 * `FalseType` を選択します。
 *
 * @tparam TrueType `condition` が `true` の場合に選択される型。
 * @tparam FalseType `condition` が `false` の場合に選択される型。
 */
template <typename TrueType, typename FalseType>
struct Conditional<false, TrueType, FalseType> {
  /// `condition` が `false` の場合に選択される型を定義
  using Type = FalseType;
};