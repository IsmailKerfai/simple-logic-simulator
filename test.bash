#!/usr/bin/bash
cmake -DCMAKE_BUILD_TYPE:STRING=Debug -S . -B build -G Ninja
cmake --build build --config Debug --target all --
build/eda-lab examples/circuit01.yal CIRCUIT01 examples/library.yal
build/eda-lab examples/circuit02.yal CIRCUIT02 examples/library.yal
build/eda-lab examples/circuit03.yal CIRCUIT03 examples/library.yal
build/eda-lab examples/circuit04.yal CIRCUIT04 examples/library.yal
build/eda-lab examples/circuit05.yal CIRCUIT05 examples/library.yal
build/eda-lab examples/rca.yal RCA examples/library.yal
