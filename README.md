# Eigen vs Armadillo Performance Analysis on Intel Hybrid Architecture

This project benchmarks matrix multiplication operations using Eigen and Armadillo libraries on Intel hybrid CPUs (P-cores and E-cores).

## Project Overview

- **Purpose**: Compare numerical precision and performance of Eigen vs Armadillo libraries on Intel's hybrid architecture (P-cores/E-cores)
- **Test CPU**: 12th Gen Intel(R) Core(TM) i7-12700H
- **Matrix Operation**: HTH computation (H^T * H) where H is a matrix loaded from binary file
- **Test Executable**: `baseline` - measures cache sizes and computes H[0,5] element using both libraries

## Build Instructions

```bash
mkdir -p cmake-build-release
cd cmake-build-release
cmake -DCMAKE_BUILD_TYPE=Release ..
make
```

This creates two executables:
- `baseline` - compiled with `-O2`
- `baseline_native` - compiled with `-O2 -march=native`

## Running Tests

Execute with the binary matrix file path as argument:

```bash
./baseline data/fast_lio/mat.bin
./baseline_native data/fast_lio/mat.bin
```

Or run the automated test script:

```bash
bash run.sh
```

## Test Results

### Baseline Version (-O3)

| Core Type | Library    | Cache L1d | Cache L2 | Cache L3 | H[0,5] Result |
|-----------|------------|-----------|----------|----------|--------------------------------|
| P-cores   | Eigen      | 48 KiB    | 1280 KiB | 24576 KiB| -1381.119139790782355703 |
| P-cores   | Armadillo  | 48 KiB    | 1280 KiB | 24576 KiB| -1381.119139790781900956 |
| E-cores   | Eigen      | 32 KiB    | 2048 KiB | 24576 KiB| -1381.119139790782583077 |
| E-cores   | Armadillo  | 32 KiB    | 2048 KiB | 24576 KiB| -1381.119139790781900956 |

### Native Version (-O3 -march=native)

| Core Type | Library    | Cache L1d | Cache L2 | Cache L3 | H[0,5] Result |
|-----------|------------|-----------|----------|----------|--------------------------------|
| P-cores   | Eigen      | 48 KiB    | 1280 KiB | 24576 KiB| -1381.119139790781900956 |
| P-cores   | Armadillo  | 48 KiB    | 1280 KiB | 24576 KiB| -1381.119139790781900956 |
| E-cores   | Eigen      | 32 KiB    | 2048 KiB | 24576 KiB| -1381.119139790781900956 |
| E-cores   | Armadillo  | 32 KiB    | 2048 KiB | 24576 KiB| -1381.119139790781900956 |

## Key Observations

1. **Cache Differences**: P-cores have larger L1d (48 KiB vs 32 KiB) and L2 (1280 KiB vs 2048 KiB) caches, while L3 is shared (24576 KiB)
2. **Precision Variance**: Baseline version shows different precision results between Eigen and Armadillo, but both converge to the same value with `-march=native`
3. **Native Optimization**: The `-march=native` flag produces consistent results across all configurations, suggesting better numerical stability
4. **Library Equivalence**: Both libraries produce identical H[0,5] values when using native optimization flags
