#pragma once

/**
 * @file liboshima.h
 * @brief Arduino IDE用の包括的なヘッダーファイル
 *
 * このヘッダーファイルは、Arduino
 * IDEで使用するための包括的なインクルードファイルです。 Arduino
 * IDEでは、サブディレクトリ内のファイルを直接インクルードすることができないため、
 * このファイルを通じて必要なすべてのヘッダーファイルを一括でインクルードします。
 * 例えば、`#include <parts\ims\IM920SL.h>` のような形式ではArduino
 * IDEで認識されないため、 このファイルを使用して一元的に管理します。
 */

// デバッグメッセージをシリアルポートに出力するためのクラス
#include "DebugLogger.h"

// さまざまなデータ型の変換を行うためのユーティリティクラス
#include "fasts/Converter.h"

// ボタンの状態を管理するためのクラス
#include "parts/Button.h"

// IM920SLモジュールを制御するためのクラス
#include "parts/IM920SL.h"

// 単一のLEDを制御するためのクラス
#include "parts/Led.h"

// 複数のLEDをテープ状に制御するためのクラス
#include "parts/LedTape.h"

// コントローラーデータを管理するためのクラス
#include "parts/controllers/ControllerData.h"

// 速度調整が不要なモーターを制御するためのクラス
#include "parts/motors/NonSpeedAdjustable.h"

// 速度調整が可能なモーターを制御するためのクラス（BD62193ドライバ使用）
#include "parts/motors/speed/BD62193.h"

// 速度調整が可能なモーターを制御するためのクラス（TB67H450ドライバ使用）
#include "parts/motors/speed/TB67H450.h"

// Null型を定義するヘッダーファイル
#include "types/NullType.h"