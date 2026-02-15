# CS2 Auto-Accept by ironlim

A high-performance Counter-Strike 2 match auto-accept utility built with C++ and OpenCV. [cite_start]This tool utilizes real-time screen capturing and color-based contour detection to identify and interact with the "Accept" button automatically. [cite: 1]

## 🚀 Features
* **Image Recognition**: Leverages OpenCV for real-time frame processing and color filtering.
* **Precise Interaction**: Automatically calculates the center of the detected button and simulates a mouse click via Win32 API.
* **DPI Aware**: Integrated with `SetProcessDPIAware()` to ensure accurate coordinate mapping across different display scales.
* **Console Feedback**: Provides real-time status updates and visual ASCII art on startup.

## 🛠️ Technical Stack
* [cite_start]**Language**: C++20. [cite: 4, 5, 6, 7]
* [cite_start]**Library**: OpenCV 4.12.0. [cite: 6, 7]
* [cite_start]**Platform**: Windows (x64). [cite: 6, 7]
* [cite_start]**Toolchain**: Visual Studio 2022 (v145). [cite: 2, 3]

## 📋 Requirements
To compile or run this project, you need:
* [cite_start]**Visual Studio 2022** with "Desktop development with C++" installed. [cite: 2]
* [cite_start]**OpenCV 4.12.0**: The project is configured to look for OpenCV at `C:\CPP\opencv\build\`. [cite: 6, 7]
* **CS2 Settings**: Must be running in Windowed or Non-Bordered Window mode for screen capture to function.

## ⚙️ Project Structure
* [cite_start]`auto_accept_cs2.cpp`: Core logic including screen capture, color thresholding (`cv::inRange`), and input simulation. [cite: 8]
* [cite_start]`auto_accept_cs2.vcxproj`: The main Visual Studio project configuration. [cite: 1]
* [cite_start]`auto_accept_cs2.vcxproj.filters`: Organization of source and header files within the IDE. [cite: 8]

## 📝 Usage
1. [cite_start]Compile the project in **Release | x64** mode within Visual Studio. [cite: 7]
2. Launch the executable.
3. The program will wait 3 seconds before it starts searching for the "Accept" button color signature.
4. Once detected, it will move your cursor and click automatically.

## 🔗 Author
* **GitHub**: [limwengming](https://github.com/limwengming)

---

**Disclaimer**: This project is for educational purposes only. Use it at your own risk. The developer is not responsible for any account bans or restrictions resulting from the use of this software.