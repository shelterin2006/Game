## Cài đặt môi trường phát triển

### 1. Cài đặt Visual Studio Components
1. Tải và cài đặt Visual Studio 2022 Community từ [trang chủ](https://visualstudio.microsoft.com/vs/community/)
2. Trong Visual Studio Installer:
   - Chọn "Modify" bên cạnh Visual Studio 2022
   - Chọn tab "Workloads"
   - **Bắt buộc**: Chọn "Desktop development with C++"
   - **Khuyến nghị**: Trong tab "Individual components", chọn:
     - "C++ CMake tools for Windows"
     - "Windows 10 SDK"
     - "MSVC v143 - VS 2022 C++ x64/x86 build tools"
3. Nhấn "Modify" để cài đặt các components

### 2. Cài đặt CMake
1. Tải CMake từ [trang chủ](https://cmake.org/download/)
2. Trong quá trình cài đặt, chọn "Add CMake to the system PATH"
3. Kiểm tra cài đặt:
   ```bash
   cmake --version
   ```

## Build
```bash
cmake -B build
```
```bash
cmake --build build
```

## Run
```bash
cd Release
./game.exe
```
