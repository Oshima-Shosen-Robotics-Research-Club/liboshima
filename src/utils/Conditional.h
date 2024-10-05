#pragma once

// 自作 conditional の定義
template <bool condition, typename TrueType, typename FalseType>
struct conditional {
  using Type = TrueType;
};

template <typename TrueType, typename FalseType>
struct conditional<false, TrueType, FalseType> {
  using Type = FalseType;
};