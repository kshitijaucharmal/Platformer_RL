# Multiplayer Platformer Prototype 🎮


https://github.com/user-attachments/assets/324ea6e8-e11b-47cf-8d58-9b73f3ff0e72


A prototype multiplayer game built **from scratch in C++** using [raylib](https://www.raylib.com/) for graphics and [ENet](https://github.com/lsalzman/enet) for networking (UDP).  

- **Server–Client architecture** (multiple players supported)  
- **Real-time updates** (UDP-based)

This project is released under the **MIT License**.  
PRs and contributions are always welcome!

---

## 📦 Releases

Prebuilt binaries are available for **Linux** in the [Releases Section](../../releases).  
- `server.zip` – Run the server  
- `client.zip` – Run the client  

For **Windows** and **macOS**, build from source (see instructions below).  

---

## 🔨 Building from Source

### Requirements
- C++17 or later  
- [CMake](https://cmake.org/)  
- [raylib](https://www.raylib.com/)  
- [ENet](https://github.com/lsalzman/enet)  

---

### Linux
Make sure `raylib` and `enet` are installed (via your package manager or from source). Example (Debian/Ubuntu):
```bash
sudo apt install libraylib-dev libenet-dev cmake build-essential
````

Build:

```bash
git clone https://github.com/<your-username>/<your-repo>.git
cd <your-repo>
mkdir build && cd build
cmake ..
make -j$(nproc)
```

Run:

```bash
./server   # start server
./client   # run client(s)
```

---

### Windows

1. Install [raylib](https://www.raylib.com/) and [ENet](https://github.com/lsalzman/enet) manually or via [vcpkg](https://github.com/microsoft/vcpkg).

   ```powershell
   vcpkg install raylib enet
   ```
2. Clone and build:

   ```powershell
   git clone https://github.com/<your-username>/<your-repo>.git
   cd <your-repo>
   mkdir build && cd build
   cmake .. -DCMAKE_TOOLCHAIN_FILE=[path-to-vcpkg]/scripts/buildsystems/vcpkg.cmake
   cmake --build . --config Release
   ```
3. Run the `server.exe` and `client.exe` binaries.

---

### macOS

Install dependencies via Homebrew:

```bash
brew install raylib enet cmake
```

Build:

```bash
git clone https://github.com/<your-username>/<your-repo>.git
cd <your-repo>
mkdir build && cd build
cmake ..
make -j$(sysctl -n hw.ncpu)
```

Run:

```bash
./server
./client
```

---

## ✅ Checklist

* [x] Simple platformer in raylib
* [x] Map system using pixel images
* [x] Learning and using ENet
* [x] Server–Client architecture (many players supported)
* [x] Sending basic info (positions only for now)
* [x] Lerping positions
* [ ] System for sending any data (batched)
* [ ] Techniques to compress packets
* [ ] Deterministic lockstep **or** snapshot interpolation (experiment & decide)
* [ ] Shooting guns in-game
* [ ] Simple upgrade system
* [ ] Gameover screen, lobby, and main menu (ImGui-based)
* [ ] Hosting server online (Google Cloud)

---

## 📜 License

This project is licensed under the [MIT License](LICENSE).
