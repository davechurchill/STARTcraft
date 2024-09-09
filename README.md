# AutoPilot

A fork of STARTcraft (https://github.com/davechurchill/STARTcraft) for the University of Portland capstone team.

# Setup Instructions:

## Windows / C++

STARTcraft comes with a StarterBot written in C++ using BWAPI 4.4.0. This repo comes with BWAPI, and uses Injectory to launch StarCraft with BWAPI, so Chaoslauncher is not required.

1. Download / Clone this repo to your computer
2. Download and unzip [Starcraft Broodwar 1.16.1](https://www.cs.mun.ca/~dchurchill/starcraftaicomp/files/startcraft/scbw_bwapi440.zip) to the included `starcraft` folder
3. Run `bin/RunStarterBotAndStarcraft.bat` which will launch the bot executable and Starcraft / BWAPI
4. Open `visualstudio/STARTcraft.sln` in Visual Studio 2022 to modify / recompile the code

## Linux / C++

1. Download / Clone this repo to your computer
2. Download and unzip [Starcraft Broodwar 1.16.1](https://www.cs.mun.ca/~dchurchill/starcraftaicomp/files/startcraft/scbw_bwapi440.zip) to the included `starcraft` folder
3. Install Mingw-w64 using: `sudo apt install build-essential mingw-w64`
4. Install wine using: `sudo dpkg --add-architecture i386 && sudo apt update && sudo apt install wine32`. You can skip this step if you use [WINE_AppImage](https://github.com/mmtrt/WINE_AppImage) or something similar, but in this case you should modify `WINEPREFIX` and the path to wine in `bin_linux/RunStarterBotAndStarcraft.sh`.
5. Run `bash bin_linux/RunStarterBotAndStarcraft.sh` which will launch the bot executable and Starcraft / BWAPI
6. Modify the code in any preferred editor / recompile the code using: `make`

Note. In the `bin_linux` folder, the `libgcc_s_seh-1.dll` and `libstdc++-6.dll` files are exactly the same ones you will find in `/usr/lib/gcc/x86_64-w64-mingw32/12-win32` after installing Mingw-w64.
