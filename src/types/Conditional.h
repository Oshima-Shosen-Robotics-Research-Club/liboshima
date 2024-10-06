#pragma once

// 自作 Conditional の定義
template <bool condition, typename TrueType, typename FalseType>
struct Conditional {
  using Type = TrueType;
};

template <typename TrueType, typename FalseType>
struct Conditional<false, TrueType, FalseType> {
  using Type = FalseType;
};