echo -e "\033[31mRunning on P cores (baseline):\033[0m"
taskset -c "$(cat /sys/bus/event_source/devices/cpu_core/cpus)" cmake-build-release/baseline data/fast_lio/mat.bin
echo -e "\033[31mRunning on E cores (baseline):\033[0m"
taskset -c "$(cat /sys/bus/event_source/devices/cpu_atom/cpus)" cmake-build-release/baseline data/fast_lio/mat.bin

echo "\n"
echo -e "\033[31mRunning on P cores (native version):\033[0m"
taskset -c "$(cat /sys/bus/event_source/devices/cpu_core/cpus)" cmake-build-release/baseline_native data/fast_lio/mat.bin
echo -e "\033[31mRunning on E cores (native version):\033[0m"
taskset -c "$(cat /sys/bus/event_source/devices/cpu_atom/cpus)" cmake-build-release/baseline_native data/fast_lio/mat.bin