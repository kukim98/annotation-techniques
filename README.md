# Annotation Techniques

This is for testing out various kinds of image segmentation annotation techniques that can facilitate creating annotations by users.

## Getting Started (WSL2 - Ubuntu 22.04)
### Preparations from Windows Side
1. Download and install Xming from [SourceForge For Xming](https://sourceforge.net/projects/xming/files/Xming/6.9.0.31/Xming-6-9-0-31-setup.exe/download).
2. The initial run of Xming should display a Firewall popup. Allow access for the application then exit program.
3. Create a copy of Xming Shortcut, open up **Properties**, and add `-ac` at the end of **Target**. Always, launch X Server via the shortcut.

### Preparations from WSL Side
1. Run `cat /etc/resolv.conf` and note the IP address for *nameserver*.
2. Run `export DISPLAY=<nameserver_ip>:0`. To set it permanently, run `nano ~/.bashrc` and add the command at the end of the file.
3. To check display porting from WSL to Windows, install sample x11 apps with `sudo apt-get install x11-apps` and run `xeyes` or `xclock`. You should see a GUI pop up.
4. Please run the commands below to install necessary components.
```
sudo apt-get update && sudo apt-get upgrade -y
sudo apt-get install g++ cmake libopencv-dev -y
```




## Getting Started (Windows)
### IDE - Visual Studio Code
1. Although Visual Studio 2022 is much better for C++ development in Windows, this guide is with Visual Studio Code, which is much more of a lightweight IDE.
2. Download and install Visual Studio Code from [Download Visual Studio Code](https://code.visualstudio.com/download).
3. Open VS Code and press `Ctrl+Shift+X`; then, search for and install the **C/C++** plugin.

### C++
1. Download and install **MSYS2** from [MSYS2 Installer Releases](https://github.com/msys2/msys2-installer/releases)
2. After installation open up MSYS2. This should bring up a terminal.
3. Run the below code to download **Mingw-w64**. Type in `y` to proceed with installation when prompted.
```
pacman -S mingw-w64-ucrt-x86_64-gcc
```
4. Install **Mingw-w64 toolchain** by running below command. When prompted for a selection, press enter and type in `y` to proceed with installation afterwards.
```
pacman -S --needed base-devel mingw-w64-x86_64-toolchain
```
5. Open **Edit the system environment variables** from the start menu.
6. Click on **Environment Variables** then **PATH** under **User variables** then **Edit**.
7. Click on **New** and paste in the absolute path to `mysys64\mingw64\bin`. If MSYS2 was installed with the default path, then the path to paste in is `C:\msys64\mingw64\bin`.
8. Open **CMD** and run the below commands to make sure that these C/C++ compilers and tools were successfully installed.
```
gcc --version
g++ --version
gdb --version
```

## CMake
1. Download and install CMake 3.25.0 from [Official Download Page](https://cmake.org/download/).
2. Open **Edit the system environment variables** from the start menu.
3. Click on **Environment Variables** then **PATH** under **User variables** then **Edit**.
4. Click on **New** and paste in the absolute path to `CMake\bin`. If CMake was installed with the default path, then the path to paste in is `C:\Program Files\CMake\bin`.
5. Open **CMD** and run `cmake --version` to ensure successful installation.

## OpenCV
1. Download OpenCV 4.6.0 library installer from [OpenCV SourceForge](https://sourceforge.net/projects/opencvlibrary/files/4.6.0/).
2. When running the installer, note the path where the library files will be extracted.
3. Open **Edit the system environment variables** from the start menu.
4. Click on **Environment Variables** then **New** under **System variables**.
5. Type in **OPENCV_DIR** for **Variable name** and the path to `opencv\build\` for **Variable value**.
