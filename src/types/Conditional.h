/**
 * @file Conditional.h
 * @brief 条件に基づいて型を選択するテンプレートクラス
 *
 * `std::conditional`に似た自作の `Conditional` クラスです。
 * コンパイル時に `condition` に基づいて、 `TrueType` または `FalseType`
 * のどちらかを選択します。
 *
 * @tparam condition コンパイル時の条件（`true` または `false`）。
 * @tparam TrueType `condition` が `true` の場合に選択される型。
 * @tparam FalseType `condition` が `false` の場合に選択される型。
 */

#pragma once

/**
 * @brief コンパイル時条件に基づき型を選択するクラス（`true`の場合）
 *
 * このクラスは `condition` が `true` である場合に `TrueType` を選択します。
 */
template <bool condition, typename TrueType, typename FalseType>
struct Conditional {
  using Type = TrueType; ///< `condition` が `true` の場合の型
};

/**
 * @brief コンパイル時条件に基づき型を選択するクラス（`false`の場合）
 *
 * この特殊化されたクラスは `condition` が `false` である場合に `FalseType`
 * を選択します。
 */
template <typename TrueType, typename FalseType>
struct Conditional<false, TrueType, FalseType> {
  using Type = FalseType; ///< `condition` が `false` の場合の型
};
