# Build Directories
BUILD_DIR_DESKTOP = build_desktop
BUILD_DIR_WEB     = build_web
PROJECT_NAME			= Platformer_RL

.PHONY: all desktop web clean help

# Default target
all: desktop web

help:
	@echo "Available Ninja build targets:"
	@echo "  make desktop  - Build native app and server using Ninja"
	@echo "  make web      - Build WebAssembly via Emscripten using Ninja"
	@echo "  make all      - Build both targets"
	@echo "  make clean    - Wipe out build directories"

# 1. Desktop Native Build (with Ninja)
desktop:
	@echo "=== Configuring Native Desktop Build (Ninja) ==="
	mkdir -p $(BUILD_DIR_DESKTOP)
	cd $(BUILD_DIR_DESKTOP) && cmake -G Ninja -DCMAKE_BUILD_TYPE=Release ..
	@echo "=== Compiling Desktop Build ==="
	cmake --build $(BUILD_DIR_DESKTOP) -j $(shell nproc 2>/dev/null || echo 4)

# 2. WebAssembly Emscripten Build (with Ninja)
web:
	@echo "=== Configuring WebAssembly Build (Ninja) ==="
	mkdir -p $(BUILD_DIR_WEB)
	cd $(BUILD_DIR_WEB) && emcmake cmake -G Ninja -DCMAKE_BUILD_TYPE=Release ..
	@echo "=== Compiling WebAssembly Build ==="
	cmake --build $(BUILD_DIR_WEB) -j $(shell nproc 2>/dev/null || echo 4)

# 3. Clean Target
clean:
	@echo "=== Cleaning Up All Build Artifacts ==="
	rm -rf $(BUILD_DIR_DESKTOP)
	rm -rf $(BUILD_DIR_WEB)

run:
	npx browser-sync start --server "$(BUILD_DIR_WEB)" --files "$(BUILD_DIR_WEB)/**/*" --browser "brave" --startPath "${PROJECT_NAME}.html"
