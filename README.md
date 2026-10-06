# Cooked!

**Cooked!** is a single-player, 2D cooking game developed by Team Cooked for **CSD1451S25 — Software Engineering Project 2** at DigiPen Institute of Technology Singapore.

You play as a chef racing to prepare dishes in a kitchen where ingredients change and mice interfere with your supplies. Gather the right ingredients, complete a cooking timing challenge, keep the stove clean, and use mouse repellent to keep the kitchen running. Reach **30 points before the five-minute timer runs out** to win.

## Gameplay

1. Choose one of the three active recipes displayed on screen.
2. Collect ingredients from the supply boxes, carrying one ingredient at a time. Each pickup replaces the box's ingredient with a random different ingredient.
3. Bring the ingredients to the stove and start cooking with **Q**.
4. Press **R** when the moving gauge reaches its target to pass the cooking timing challenge.
5. Earn points by cooking a dish that matches an active recipe. A matching dish earns twice its ingredient count; a dish that does not match costs points.
6. Clean the stove when it becomes dirty, discard unwanted ingredients in the dustbin, and activate the repellent when mice block access to ingredient boxes.

Recipes refresh when completed or when their individual timers expire. The six ingredients—chicken, rice, egg, cheese, potato, and beef—combine into dishes such as Cheese Omelette, Chicken Fried Rice, and Loaded Protein Bowl.

The game also includes a main menu, how-to-play instructions, a pause menu, audio options, credits, and win/lose screens.

## Controls

| Input | Action |
| --- | --- |
| **W / A / S / D** | Move |
| **Left Shift** | Dash while moving |
| **E** | Pick up an ingredient, add it to the stove, discard it at the dustbin, or activate the repellent when nearby |
| **Q** | Start the cooking timing challenge at the stove |
| **R** | Stop the cooking gauge |
| **C** | Clean a dirty stove when nearby |
| **T** | Pause the game |
| **Left mouse button** | Select menu buttons |

## Built With

- **C++** for gameplay and game systems.
- **DigiPen Alpha Engine** for graphics, input, audio, and the game loop.
- **Visual Studio 2022**, using the **v143** toolset and **Windows SDK 10.0**.
- **JSON** for rectangle/layout data in `Cooked/Source/Assets/Rect.json`.

## Build and Run

1. On Windows, install Visual Studio 2022 with the **Desktop development with C++** workload, the v143 toolset, and a Windows 10 SDK.
2. Open [`Cooked/Game_Project.sln`](Cooked/Game_Project.sln).
3. Select **Debug | x64** or **Release | x64** and build the solution.
4. Run the game from Visual Studio, or launch `Game_Project.exe` from the corresponding output directory:
   - `Cooked/bin/Debug-x64/`
   - `Cooked/bin/Release-x64/`

The project includes Alpha Engine headers and libraries. Its post-build steps copy assets and runtime DLLs into the output directory. When launching the executable directly, use that directory as the working directory so the game can find its `Assets` folder.

## My Contributions — Elvis Lim Sheng Jie

My work focused on player controls, interaction and collision handling, menu navigation, game-state integration, and the mouse-repellent mechanic. The examples below are based on changes authored by **`elvisshengjie`** in the Git history available on `origin/main`, covering January–April 2025.

| Area | My contribution | Representative commits |
| --- | --- | --- |
| **Player movement and dash** | Updated movement to use frame time, normalized diagonal movement to keep its speed consistent, and implemented dash movement with duration and cooldown handling. | [Movement fix](https://github.com/elvisshengjie/Cooked_game/commit/45c8e5903858f0d393d58111c535953f6188dbdb), [Dash](https://github.com/elvisshengjie/Cooked_game/commit/b94af3c5027997a37f3048b65258f102030400b1) |
| **Collision and screen boundaries** | Worked on rectangle collision detection and player collision checks, added screen-boundary clamping, and refined interaction highlights. | [Collision implementation/fixes](https://github.com/elvisshengjie/Cooked_game/commit/518b572464b0e6c779025d854494423a74d39313), [Screen boundaries](https://github.com/elvisshengjie/Cooked_game/commit/560710ddbe94366a93ed2751bf9cc01752aa806b), [Highlight adjustment](https://github.com/elvisshengjie/Cooked_game/commit/bd78c92aaac587e94f542ba7c6b4e09bc6c0d537) |
| **Ingredient interactions** | Developed ingredient pickup/drop handling, tracked the ingredient held by the player, displayed held ingredients, and connected pickups to random supply-box replenishment. | [Ingredient pickup/drop](https://github.com/elvisshengjie/Cooked_game/commit/d9674d0271f489c971c364f40d02d183c46afc4c) |
| **Main menu and game states** | Added menu/game state switching in `CoreEngine`, developed main-menu buttons and mouse/keyboard navigation, and contributed exit-confirmation functionality. | [Initial state switching](https://github.com/elvisshengjie/Cooked_game/commit/ddcca55b04d7e64449c78c7e20c08f24efae1ed1), [Main-menu interaction](https://github.com/elvisshengjie/Cooked_game/commit/e20e058080c678005d66154b8daed82e68ff61c8), [Exit confirmation](https://github.com/elvisshengjie/Cooked_game/commit/6c7996eda29d243cb30d6a345cfc586db11ffb71) |
| **Mouse repellent** | Implemented the temporary chase-away behavior and repellent activation/cooldown. Later moved device interaction into `mouse::handleDeviceInteraction`, including activation prompts and cooldown feedback. | [Mouse repellent](https://github.com/elvisshengjie/Cooked_game/commit/49c004973dae975ecc507571fc004023d5ea4928), [Device interaction refactor](https://github.com/elvisshengjie/Cooked_game/commit/0b40d8214f5833223abab2aeafedc016c4a6745d) |
| **Startup and credits** | Worked on the DigiPen logo screen and developed credits rendering, scrolling, and integration with the game states. | [DigiPen logo](https://github.com/elvisshengjie/Cooked_game/commit/49f59a3dd9cf2c7baaf15b080d593070a701a3be), [Credits outline](https://github.com/elvisshengjie/Cooked_game/commit/c44df0e076478bf7e8a27fe281b039757bbb9e4f), [Credits implementation](https://github.com/elvisshengjie/Cooked_game/commit/4b406ccdce2d5de554e0dd1f722aaaad0186d074) |
| **Documentation and polish** | Added source documentation and contributor annotations, wrote the original game instructions, and disabled the debug console for the game launch. | [Source documentation](https://github.com/elvisshengjie/Cooked_game/commit/c473bacd742b257eb534b137901822577fcc2b13), [Original README](https://github.com/elvisshengjie/Cooked_game/commit/2a9cae415f84044fe403cefbc641fe0ce4d55fb7), [Console removal](https://github.com/elvisshengjie/Cooked_game/commit/dd2e9d1ca0aa6be888f448d7cfa94acf8e7048e0) |

These are contributions to a team project. Shared systems were also developed and refined by teammates; the linked commits identify my specific changes rather than exclusive ownership of entire systems.

## Project Layout

| Path | Contents |
| --- | --- |
| `Cooked/Game_Project.sln` | Visual Studio solution |
| `Cooked/Game_Project/` | Visual Studio project configuration |
| `Cooked/Source/` | Gameplay, rendering, menus, collision, and utility code |
| `Cooked/Source/Assets/` | Textures, audio, fonts, icons, and layout data |
| `Cooked/Source/Extern/` | Alpha Engine dependencies and documentation |
| `Cooked/Documents/` | Team planning document |

## Team and Copyright

Team Cooked: **Elvis, Norman, Kerrin, and Justin**.

All content © 2025 DigiPen Institute of Technology Singapore. All rights reserved.
