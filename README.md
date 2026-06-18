# FastBoot

> An AML mod for **GTA: SA Android** that dramatically reduces the time between launching the game and actually playing it.

FastBoot is the third generation of this project, built to take full control of the game's startup sequence — skipping unnecessary screens and jumping straight into a new game, the load menu, or your most recent save.

---

## Features

- Skip the Social Club screen
- Configurable startup behavior
- Automatic save slot resolution
- Resume the latest valid save instantly
- Start a new game automatically
- Open the Load Game menu automatically
- Lightweight, dependency-free build

---

## Requirements

- [GTA: SA Android (AML)](https://discord.gg/aml-android-mod-loader-877187821511794730)

---

## Installation

1. Copy `libFastBoot.so` to the AML mods directory.
2. Configure FastBoot through its generated configuration file.
3. Launch the game.
---

## Configuration

FastBoot generates a configuration file on first launch:

```
net.deviceblack.fastboot.ini
```

Example:

```ini
[Preferences]

; Skips the Social Club screen.
Remove Social Club = 1

; Startup behavior.
Start Mode = auto

; Save slots checked from left to right.
Slot List = GTASAsf9.b GTASAsf10.b
```

---

## Startup Modes

FastBoot supports multiple startup modes via the `Start Mode` key.

| Mode | Behavior |
|------|----------|
| `none` | Disables all startup automation. |
| `newgame` | Starts a new game automatically. |
| `loadgame` | Opens the **Load Game** menu automatically. |
| `loadslot` | Loads the first valid save slot found in the configured slot list. |
| `auto` | Attempts to resume a valid save. If none is found, starts a new game. |
| `auto2` | Attempts to resume a valid save. If none is found, opens the Load Game menu. |

---

## Save Slot Resolution

FastBoot evaluates the configured save slots **left to right**. The first valid slot found determines the action to perform.

```ini
Slot List = GTASAsf9.b GTASAsf10.b
Slot List = GTASAsf1.b GTASAsf5.b GTASAsf10.b
```

---

## Version History

| Generation | Name |
|------------|------|
| 1st | SCAndSkip |
| 2nd | SmartBoot |
| 3rd | **FastBoot** |

---

## License

This project is provided **as-is** for educational and modding purposes.

Use at your own responsibility.
