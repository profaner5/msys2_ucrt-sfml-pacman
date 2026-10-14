# Pac-Man C++ Implementation

A standalone, zero-dependency C++ implementation of the arcade classic Pac-Man, engineered specifically for native execution within the Windows UCRT64 toolchain environment utilizing SFML 3.

## Technical Architecture

The application is structured around a single-translation-unit design pattern to minimize build complexity and eliminate external asset loading dependencies during runtime.

### Core Systems
- **Grid-Based State Engine**: Discrete coordinate mapping utilizing a two-dimensional integer array representing the 19x21 tile layout.
- **Interpolated Movement Mechanics**: Sub-pixel movement calculations coupled with directional buffering to facilitate seamless cornering and grid alignment.
- **Tunnel Wrap-Around Logic**: Boundary condition checking for horizontal coordinate translation across the lateral map bounds.
- **Event Polling**: Asynchronous input handling utilizing the modern SFML 3 `std::optional` event loop architecture.

## System Prerequisites

The compilation environment requires MSYS2 configured with the UCRT64 runtime and the corresponding development toolchain.

```bash
pacman -S mingw-w64-ucrt-x86_64-toolchain mingw-w64-ucrt-x86_64-sfml
```

## Compilation Instructions

Execute the following commands within the MSYS2 UCRT64 terminal to compile the source code with optimization flags enabled:

```bash
g++ main.cpp -o pacman.exe -O3 -lsfml-graphics -lsfml-window -lsfml-system
```

## Runtime Dependencies and Deployment

To distribute the application binaries independently of the MSYS2 runtime environment, ensure the following dynamic link libraries (DLLs) are placed within the same directory as `pacman.exe`:

- `libsfml-graphics-3.dll`
- `libsfml-window-3.dll`
- `libsfml-system-3.dll`
- `libstdc++-6.dll`
- `libgcc_s_seh-1.dll`
- `libwinpthread-1.dll`

## Control Schema

| Key Designation | Mapped Action |
| :--- | :--- |
| Left Arrow | Translate Left |
| Right Arrow | Translate Right |
| Up Arrow | Translate Up |
| Down Arrow | Translate Down |

## Licensing

This project is distributed under the terms of the MIT License. See the `LICENSE` file for full legal terms and conditions.