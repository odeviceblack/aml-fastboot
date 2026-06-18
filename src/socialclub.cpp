#include "main.hpp"

DECL_HOOK(void, hal_ViewManager_render)
{
	hal_ViewManager_render();

	static const bool once = [] {
		jobject instance = aml->InjectSmaliDEX(classes_dex, classes_dex_len, "net.deviceblack.fastboot.RemoveSocialClub");
		aml->GetJNIEnvironment()->DeleteGlobalRef(instance);
		return true;
	}();
}

void RemoveSocialClub()
{
	HOOKSYM(hal_ViewManager_render, g_pLibSCAnd, "_ZN3hal11ViewManager6renderEv");
}
