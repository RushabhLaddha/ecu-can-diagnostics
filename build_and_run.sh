#!/bin/bash

set -e   # exit immediately on error

PROJECT_ROOT=$(pwd)
BUILD_DIR="$PROJECT_ROOT/build"

ECU_BIN="$BUILD_DIR/ecu_simulator/ecu_simulator"
QT_BIN="$BUILD_DIR/qt_diagnostics/qt_diagnostics"

echo "=============================="
echo " ECU CAN Diagnostics Launcher "
echo "=============================="

# -------------------------------
# 1. Build project
# -------------------------------
echo "[1/5] Building project..."

mkdir -p "$BUILD_DIR"
cd "$BUILD_DIR"

cmake ..
cmake --build .

echo "Build completed."

# -------------------------------
# 2. Setup vcan0 if missing
# -------------------------------
echo "[2/5] Checking vcan0 interface..."

if ! ip link show vcan0 >/dev/null 2>&1; then
    echo "vcan0 not found. Creating it..."

    sudo modprobe vcan
    sudo ip link add dev vcan0 type vcan
    sudo ip link set up vcan0

    echo "vcan0 created and brought up."
else
    echo "vcan0 already exists."
fi

# -------------------------------
# 3. Run ECU simulator
# -------------------------------
echo "[3/5] Starting ECU simulator..."

if [ ! -f "$ECU_BIN" ]; then
    echo "ERROR: ecu_simulator binary not found!"
    exit 1
fi

"$ECU_BIN" &
ECU_PID=$!

echo "ECU simulator running (PID=$ECU_PID)"

# Give ECU time to initialize
sleep 1

# -------------------------------
# 4. Run Qt diagnostics
# -------------------------------
echo "[4/5] Starting Qt diagnostics UI..."

if [ ! -f "$QT_BIN" ]; then
    echo "ERROR: qt_diagnostics binary not found!"
    kill $ECU_PID
    exit 1
fi

"$QT_BIN" &
QT_PID=$!

echo "Qt diagnostics running (PID=$QT_PID)"

# -------------------------------
# 5. Wait & cleanup
# -------------------------------
echo "[5/5] Press Ctrl+C to stop everything."

trap "echo 'Stopping...'; kill $ECU_PID $QT_PID; exit" SIGINT SIGTERM

wait
