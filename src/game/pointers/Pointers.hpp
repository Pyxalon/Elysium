#pragma once
#include <d3d11.h>
#include <windows.h>

namespace Elysium
{
	struct PointerData
	{
		HWND* Hwnd;
	};

	struct Pointers : PointerData
	{
		bool Init();
	};

	inline Elysium::Pointers Pointers;
}
