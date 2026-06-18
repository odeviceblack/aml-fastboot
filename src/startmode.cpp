#include "main.hpp"
#include <sstream>

enum class StartMode : int {
	None = 0,
	NewGame,
	LoadGame,
	LoadSlot,
	AutoNewGame,
	AutoLoadGame
};

struct State
{
	StartMode mode = StartMode::None;
	int resolved_slot = -1;
	std::vector<std::string> save_slots;

	inline void Reset()
	{
		*this = {};
	}

	inline bool IsEnabled() const
	{
		return mode != StartMode::None;
	}

	inline bool HasSlot() const
	{
		return resolved_slot != -1;
	}
};

static State state;

/*
 *  ============================================
 */

inline StartMode parseMode(const char* mode)
{
	static constexpr const char* modes[] = {
		"none", "newgame", "loadgame",
		"loadslot", "auto", "auto2"
	};

	for(size_t i = 0; i < std::size(modes); i++)
	{
		if(strcmp(mode, modes[i]) == 0)
			return static_cast<StartMode>(i);
	}

	return StartMode::None;
}

inline std::vector<std::string> parseSlots(const char* slots)
{
	if(!slots || !*slots)
		return {};

	std::stringstream ss(slots);
	std::vector<std::string> out;

	for(std::string s; ss >> s;)
		out.emplace_back(std::move(s));

	return out;
}

inline int parseSaveSlot(const std::string& slot)
{
	static constexpr char prefix[] = "GTASAsf";

	if(slot.rfind(prefix, 0) != 0)
		return -1;

	char* end = nullptr;
	const long value = strtol(slot.c_str() + sizeof(prefix) - 1, &end, 10);

	return (strcmp(end, ".b") != 0) ? -1 : (int)value;
}

inline int resolveSlot()
{
	const std::string base = aml->GetAndroidDataPath();
	const std::string autoPath = base + "GTASAsf10.b";

	for(const auto& slot : state.save_slots)
	{
		const std::string full = base + slot;

		if(!aml->FileExists(full.c_str()))
			continue;

		const int s = parseSaveSlot(slot);
		if(s >= 1 && s <= 6)
		{
			bool ok = aml->CopyFile(full.c_str(), autoPath.c_str());
			return ok ? 9 : -1;
		}

		if(s == 9)
			return 8;

		if(s == 10)
			return 9;
	}

	return -1;
}

/*
 *  ============================================
 */

void (*StartGameScreen_onNewGameCheck)() = nullptr;
void (*StartGameScreen_onLoadGame)() = nullptr;
void (*MainMenuScreen_onResume)(void*) = nullptr;

inline void executeAction(void* self)
{
	if(state.mode >= StartMode::LoadSlot)
	{
		if(state.HasSlot())
			return MainMenuScreen_onResume(self);
	}

	switch(state.mode)
	{
		case StartMode::NewGame:
		case StartMode::AutoNewGame:
			return StartGameScreen_onNewGameCheck();

		case StartMode::LoadGame:
		case StartMode::AutoLoadGame:
			return StartGameScreen_onLoadGame();

		default: return;
	}
}

void MenuEntryPoint(void* self, float dt)
{
	if(!state.IsEnabled())
		return;

	executeAction(self);
	state.Reset();
}

DECL_HOOK(void, Menu_LoadSlot, int slot)
{
	if(!state.HasSlot())
		return Menu_LoadSlot(slot);

	Menu_LoadSlot(state.resolved_slot);
	state.resolved_slot = -1;
}

/*
 *  ============================================
 */
 
void StartMode(const char* mode, const char* slots)
{
	state.Reset();
	state.mode = parseMode(mode);

	if(!state.IsEnabled())
		return;

	state.save_slots = parseSlots(slots);
	state.resolved_slot = resolveSlot();

	if(state.HasSlot())
		HOOKSYM(Menu_LoadSlot, g_pLibGTASA, "_Z13Menu_LoadSloti");

	SETSYM_TO(StartGameScreen_onNewGameCheck, g_pLibGTASA, "_ZN15StartGameScreen14OnNewGameCheckEv");
	SETSYM_TO(StartGameScreen_onLoadGame, g_pLibGTASA, "_ZN15StartGameScreen10OnLoadGameEv");
	SETSYM_TO(MainMenuScreen_onResume, g_pLibGTASA, "_ZN14MainMenuScreen8OnResumeEv");
}
