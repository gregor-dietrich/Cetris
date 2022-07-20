#pragma once

#include "hulk.h"

namespace cetris
{
	constexpr hulk::u8 LEVEL_WIDTH = 10;
	constexpr hulk::u8 LEVEL_HEIGHT = 20;
	constexpr hulk::u8 BUFFER_HEIGHT = 4;

	const hulk::wstr U_SQUARE = L"\u25a0";
	const hulk::wstr U_EMPTY = L" ";
	const hulk::wstr U_HORIZONTAL = L"\u2550";
	const hulk::wstr U_VERTICAL = L"\u2551";
	const hulk::wstr U_CORNER_TOP_LEFT = L"\u2554";
	const hulk::wstr U_CORNER_TOP_RIGHT = L"\u2557";
	const hulk::wstr U_CORNER_BOTTOM_LEFT = L"\u255a";
	const hulk::wstr U_CORNER_BOTTOM_RIGHT = L"\u255d";
	const hulk::wstr U_VERTICAL_LEFT = L"\u2560";
	const hulk::wstr U_VERTICAL_RIGHT = L"\u2563";
	const hulk::wstr U_HORIZONTAL_TOP = L"\u2566";
	const hulk::wstr U_HORIZONTAL_BOT = L"\u2569";
	const hulk::wstr U_CROSS = L"\u256c";
}
