#!/bin/sh
set -e

log() {
  printf '\n----------------[ %s ]----------------\n' "$1"
}

SCRIPT_DIR="$(CDPATH= cd -- "$(dirname -- "$0")" && pwd)"
BUILD_DIR="$SCRIPT_DIR/cmake-build-debug"

log "Generating build files"
cmake \
  -DCMAKE_BUILD_TYPE=Debug \
  -G "Unix Makefiles" \
  -S "$SCRIPT_DIR" \
  -B "$BUILD_DIR"

log "Building engine"
cmake --build "$BUILD_DIR" --target engine -- -j 6

log "Building game"
cmake --build "$BUILD_DIR" --target game -- -j 6

log "Running game"
"$BUILD_DIR/game"