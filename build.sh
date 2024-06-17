#!/bin/bash

set -xe

mkdir -p ./build
mkdir -p ./codegen

cp ./src/infinity-quine.c ./codegen/infinity-quine.c

cc ./scripts/format-quine.c -o ./scripts/format-quine
./scripts/format-quine ./codegen/infinity-quine.c ./codegen/formatted-infinity-quine.c
rm ./scripts/format-quine
rm ./codegen/infinity-quine.c
mv ./codegen/formatted-infinity-quine.c ./codegen/infinity-quine.c

cc ./scripts/compile-quine.c -o ./scripts/compile-quine
./scripts/compile-quine ./codegen/infinity-quine.c > ./codegen/compiled-infinity-quine.c
rm ./scripts/compile-quine
rm ./codegen/infinity-quine.c
mv ./codegen/compiled-infinity-quine.c ./codegen/infinity-quine.c

cc -Wall -Wextra -include stdio.h -include stdlib.h -include unistd.h codegen/infinity-quine.c -o ./build/infinity-quine
