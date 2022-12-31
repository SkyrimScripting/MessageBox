> 📜 other templates available at https://github.com/SkyrimScripting/SKSE_Templates

# Skyrim Scripting SKSE Starter Kit

- [Skyrim Scripting SKSE Starter Kit](#skyrim-scripting-skse-starter-kit)
  - [Features](#features)
  - [What does it do?](#what-does-it-do)
  - [Skyrim Scripting helper libraries](#skyrim-scripting-helper-libraries)
    - [Skyrim Scripting Plugin helpers](#skyrim-scripting-plugin-helpers)
    - [Skyrim Scripting CMake helpers](#skyrim-scripting-cmake-helpers)
  - [Requirements](#requirements)
  - [Project setup](#project-setup)
  - [Setup your own repository](#setup-your-own-repository)

---

A simple SKSE plugin for Skyrim using:

- C++
- CMake
- [CommonLibSSE NG](https://github.com/CharmedBaryon/CommonLibSSE-NG)
- [Skyrim Scripting's CMake helpers](https://github.com/SkyrimScripting/CMake)
- [Skyrim Scripting's Plugin helpers](https://github.com/SkyrimScripting/Plugin)

> Because this uses CommonLibSSE NG, it supports Skyrim SSE, AE, GOG, and VR!


## Features

- [x] Easy deployment to mods folder (or `Data/` folder)
- [x] Easy SKSE event handlers!
- [x] Easy game event handlers!
- [ ] Easy Papyrus script bindings! (with easy script deployment!)
- [ ] Easy Save/Load data handlers!

## What does it do?

- It writes `"Hello log from SKSE Starter Kit!"` to a log file in `My Games/Skyrim Special Edition/SKSE/`
- It writes `"Hello console from SKSE Starter Kit!"` to the ~ game console (_viewable from the Main Menu_)
- Everytime any object in the game is activated, it logs details about the activation to the log file.

Read [`plugin.cpp`](plugin.cpp) for details on what it's doing!

## Skyrim Scripting helper libraries

Whereas the [other templates](https://github.com/SkyrimScripting/SKSE_Templates) use the raw features provided by [CommonLibSSE-NG](https://github.com/CharmedBaryon/CommonLibSSE-NG), the **Starter Kit** uses Skyrim Scripting authored helpers to make your SKSE development easier!

### [Skyrim Scripting Plugin helpers](https://github.com/skyrimScripting/Plugin)

```cpp
// Simply #include Plugin.h in your main .cpp file
#include <SkyrimScripting/Plugin.h>

// Then you can use a variety of macros for registering code to run at different points
OnInit {
    logger::info("Hello, plugin!");
}

// This event is when all of the Forms have been loaded, but it is
// also *basically* the same time as the Main Menu (and console) become ready
OnDataLoaded {
    ConsoleLog("Hello, console!");
}

// If there are certain events that you want to listen to, it's easy as well:
EventHandlers {
    On<RE::TESActivateEvent>([](const RE::TESActivateEvent* event) {
        auto activated = event->objectActivated->GetBaseObject()->GetName();
        auto activator = event->actionRef->GetBaseObject()->GetName();
        // This will print things to the game console like:
        // Hod activated Mill
        // Hilde activated Door
        ConsoleLog("{} activated {}", activator, activated);
    });
}
```

See https://github.com/SkyrimScripting/Plugin for latest documentation.

### [Skyrim Scripting CMake helpers](https://github.com/SkyrimScripting/CMake)

```cmake
# Load in your CMakeLists.txt
find_package(SkyrimScripting.CMake CONFIG REQUIRED)

# And simply define an "SKSE plugin"
# This is the magic which automatically deploys your mod to CMAKE_SKYRIM_MODS_FOLDER
add_skse_plugin(${PROJECT_NAME} SOURCES plugin.cpp)

# If you are using SkyrimScripting.Plugin, you currently need to manually link that:
find_package(SkyrimScripting.Plugin CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE SkyrimScriptingPlugin::SkyrimScripting.Plugin)
```

See https://github.com/SkyrimScripting/CMake for latest documentation.

## Requirements

- [Visual Studio 2022](https://visualstudio.microsoft.com/) (_the free Community edition is fine!_)
- [`vcpkg`](https://github.com/microsoft/vcpkg)
  - 1. Clone the repository using git OR [download it as a .zip](https://github.com/microsoft/vcpkg/archive/refs/heads/master.zip)
  - 2. Go into the `vcpkg` folder and double-click on `bootstrap-vcpkg.bat`
  - 3. Edit your system or user Environment Variables and add a new one:
    - Name: `VCPKG_ROOT`  
      Value: `C:\path\to\wherever\your\vcpkg\folder\is`

Once you have Visual Studio 2022 installed, you can open this folder in basically any C++ editor, e.g. [VS Code](https://code.visualstudio.com/) or [CLion](https://www.jetbrains.com/clion/) or [Visual Studio](https://visualstudio.microsoft.com/)
- > _for VS Code, if you are not automatically prompted to install the [C++](https://marketplace.visualstudio.com/items?itemName=ms-vscode.cpptools) and [CMake Tools](https://marketplace.visualstudio.com/items?itemName=ms-vscode.cmake-tools) extensions, please install those and then close VS Code and then open this project as a folder in VS Code_

You may need to click `OK` on a few windows, but the project should automatically run CMake!

It will _automatically_ download [CommonLibSSE NG](https://github.com/CharmedBaryon/CommonLibSSE-NG) and everything you need to get started making your new plugin!

## Project setup

By default, when this project compiles it will output a `.dll` for your SKSE plugin into the `build/` folder.

But you probably want to put the `.dll` into your Skyrim mods folder, e.g. the mods folder used by Mod Organizer 2 or Vortex.

You can configure this project to _automatically_ output the SKSE plugin `.dll` into:
- `<your mods folder>\<name you give this project>\SKSE\Plugins\<your mod>.dll`  
  if you set the `CMAKE_SKYRIM_MODS_FOLDER` environment variable to the **root of your mods folder** (i.e. `<your mods folder>`)

- **Example:**
    - Name: `CMAKE_SKYRIM_MODS_FOLDER`  
      Value: `C:\path\to\wherever\your\Skyrim\mods\are`

If you would prefer to deploy mods directly to your Skyrim `Data/` folder, you can set the `CMAKE_SKYRIM_FOLDER` to the path of your Skyrim folder. If the `CMAKE_SKYRIM_MODS_FOLDER` variable is no defined but `CMAKE_SKYRIM_FOLDER` contains a valid path to your Skyrim folder, your SKSE plugin will be output directly into your `Data/SKSE/Plugins/` folder. 

## Setup your own repository

If you clone this template on GitHub, please:

- Go into `LICENSE` and change the year and change `<YOUR NAME HERE>` to your name.
- Go into `CODE_OF_CONDUCT.md` and change `<YOUR CONTACT INFO HERE>` to your contact information.

It's good to have a `Code of Conduct` and GitHub will show your project's `CODE_OF_CONDUCT.md` in the project sidebar.

If you'd like to know more about open source licenses, see:
- [Licensing a repository](https://docs.github.com/en/repositories/managing-your-repositorys-settings-and-features/customizing-your-repository/licensing-a-repository)
- [Choose an open source license](https://choosealicense.com/)

**If you use this template, PLEASE release your project as a public open source project.** 💖

**PLEASE DO NOT RELEASE YOUR SKSE PLUGIN ON NEXUS/ETC WITHOUT MAKING THE SOURCE CODE AVAILABLE**
