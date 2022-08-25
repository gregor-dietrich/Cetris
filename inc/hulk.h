#pragma once
#include <iostream>
#include <random>
#include <string>
#include <thread>

#include "fcntl.h"
#include "io.h"
#include "Windows.h"

namespace hulk
{
	/* Type Aliases */
	using i8 = int8_t;
	using i16 = int16_t;
	using i32 = int32_t;
	using i64 = int64_t;
	using u8 = uint8_t;
	using u16 = uint16_t;
	using u32 = uint32_t;
	using u64 = uint64_t;
	using f32 = float;
	using f64 = double;
	using wchar = wchar_t;
	using str = std::string;
	using wstr = std::wstring;
	using thread = std::thread;

	/* Globals */
	constexpr i8 I8_MAX = INT8_MAX;
	constexpr i16 I16_MAX = INT16_MAX;
	constexpr i32 I32_MAX = INT32_MAX;
	constexpr i64 I64_MAX = INT64_MAX;
	constexpr u8 U8_MAX = UINT8_MAX;
	constexpr u16 U16_MAX = UINT16_MAX;
	constexpr u32 U32_MAX = UINT32_MAX;
	constexpr u64 U64_MAX = UINT64_MAX;

	/* Internals */
	namespace internal
	{
		using lf64 = long double; // instant deprecated
		static auto UNICODE_ENABLED = false;
		static const auto& H_CONSOLE = GetStdHandle(STD_OUTPUT_HANDLE);
		static thread_local std::mt19937* RAND_GENERATOR = nullptr;
	}

	/* Functions */
	// Time
	inline auto sleep(const u64& ms) -> void
	{
		const std::chrono::milliseconds timespan(ms);
		std::this_thread::sleep_for(timespan);
	}

	// Random Number Generator
	inline auto rand_int(const i32& min, const i32& max) -> i32
	{
		if (!internal::RAND_GENERATOR)
			internal::RAND_GENERATOR = new std::mt19937(std::random_device{}());
		std::uniform_int_distribution<i32> distribution(min, max);
	    return distribution(*internal::RAND_GENERATOR);
	}
	inline auto rand_int(const i32& max) -> i32
	{
		return rand_int(0, max);
	}

	// Conversions
	inline auto to_str(const i16& val) -> str
	{
		return std::to_string(val);
	}
	inline auto to_str(const i32& val) -> str
	{
		return std::to_string(val);
	}
	inline auto to_str(const i64& val) -> str
	{
		return std::to_string(val);
	}
	inline auto to_str(const u16& val) -> str
	{
		return std::to_string(val);
	}
	inline auto to_str(const u32& val) -> str
	{
		return std::to_string(val);
	}
	inline auto to_str(const u64& val) -> str
	{
		return std::to_string(val);
	}
	inline auto to_str(const f32& val) -> str
	{
		return std::to_string(val);
	}
	inline auto to_str(const f64& val) -> str
	{
		return std::to_string(val);
	}
	inline auto to_str(const internal::lf64& val) -> str
	{
		return std::to_string(val);
	}
	inline auto to_wstr(const i16& val) -> wstr
	{
		return std::to_wstring(val);
	}
	inline auto to_wstr(const i32& val) -> wstr
	{
		return std::to_wstring(val);
	}
	inline auto to_wstr(const i64& val) -> wstr
	{
		return std::to_wstring(val);
	}
	inline auto to_wstr(const u16& val) -> wstr
	{
		return std::to_wstring(val);
	}
	inline auto to_wstr(const u32& val) -> wstr
	{
		return std::to_wstring(val);
	}
	inline auto to_wstr(const u64& val) -> wstr
	{
		return std::to_wstring(val);
	}
	inline auto to_wstr(const f32& val) -> wstr
	{
		return std::to_wstring(val);
	}
	inline auto to_wstr(const f64& val) -> wstr
	{
		return std::to_wstring(val);
	}
	inline auto to_wstr(const internal::lf64& val) -> wstr
	{
		return std::to_wstring(val);
	}

	// Output
	inline auto print(const str& str, const u16& n = 1) -> void
	{
		for (u16 i = 0; i < n; i++)
			std::cout << str;
	}
	inline auto println(const str& str = "", const u16& n = 1) -> void
	{
		print(str + "\n", n);
	}
	inline auto print(const wstr& str, const u16& n = 1) -> void
	{
		for (u16 i = 0; i < n; i++)
			std::wcout << str;
	}
	inline auto println(const wstr& str = L"", const u16& n = 1) -> void
	{
		print(str + L"\n", n);
	}

	// Console
	namespace console
	{		
		enum color
		{
			black,
			blue,
			green,
			aqua,
			red,
			purple,
			yellow,
			light_gray,
			dark_gray,
			light_blue,
			light_green,
			light_aqua,
			light_red,
			light_purple,
			light_yellow,
			white
		};

		inline auto enable_unicode() -> bool
		{
			if (internal::UNICODE_ENABLED)
				return true;
			if (_setmode(_fileno(stdout), _O_WTEXT) != -1)
				internal::UNICODE_ENABLED = true;
			return internal::UNICODE_ENABLED;
		}

		inline auto disable_unicode() -> bool
		{
			if (!internal::UNICODE_ENABLED)
				return true;
			if (_setmode(_fileno(stdout), _O_TEXT) != -1)
				internal::UNICODE_ENABLED = false;
			return !internal::UNICODE_ENABLED;
		}

		inline auto is_unicode() -> bool
		{
			return internal::UNICODE_ENABLED;
		}

		inline auto text_color(const color& c = light_gray) -> bool
		{
			return SetConsoleTextAttribute(internal::H_CONSOLE, c);
		}

		inline auto clear(const wchar& fill = ' ') -> void
		{
			constexpr COORD tl = {0,0};
		    CONSOLE_SCREEN_BUFFER_INFO s;
		    GetConsoleScreenBufferInfo(internal::H_CONSOLE, &s);
		    DWORD written;
			const DWORD cells = s.dwSize.X * s.dwSize.Y;
			FillConsoleOutputCharacter(internal::H_CONSOLE, fill, cells, tl, &written);
		    FillConsoleOutputAttribute(internal::H_CONSOLE, s.wAttributes, cells, tl, &written);
		    SetConsoleCursorPosition(internal::H_CONSOLE, tl);
		}
	}
}
