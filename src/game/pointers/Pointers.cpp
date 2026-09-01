#include "Pointers.hpp"

#include "core/memory/BytePatch.hpp"
#include "core/memory/ModuleMgr.hpp"
#include "core/memory/PatternScanner.hpp"
#include "util/Joaat.hpp"

namespace Elysium
{
	bool Pointers::Init()
	{
		const auto gta5 = ModuleMgr.Get("GTA5_Enhanced.exe"_J);
		if (!gta5)
		{
			LOG(FATAL) << "Could not find GTA5_Enhanced.exe, is this GTA 5 Enhanced?";
			return false;
		}

		auto scanner = PatternScanner(gta5);

		constexpr auto hWndPtrn = Pattern<"E8 ? ? ? ? 84 C0 74 25 48 8B 0D">("HWND");
		scanner.Add(hWndPtrn, [this](PointerCalculator ptr) {
			Hwnd = ptr.Add(9).Add(3).Rip().As<HWND*>();
		});


		if (!scanner.Scan())
		{
			LOG(FATAL) << "Some patterns could not be found, unloading.";

			return false;
		}

		if (*Hwnd = FindWindow("grcWindow", nullptr); !Hwnd)
		{
			LOG(FATAL) << "Failed to grab game window, unloading.";

			return false;
		}

		return true;
	}
}
