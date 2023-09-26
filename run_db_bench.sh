#!/bin/bash

# Run db_bench with the given mutex and given number of threads and print the results to stdout.


CMAKE_BINARY_DIR="${CMAKE_BINARY_DIR:-cmake_build_RelWithDebInfo}"
DB_BENCH_PATH="${DB_BENCH_PATH:-$CMAKE_BINARY_DIR/leveldb/db_bench}"

# seed the db with fillseq
tmpdb="${TMP_DIR:-$(mktemp -d)}"
echo "Filling db at $tmpdb with fillseq"
"$DB_BENCH_PATH" --threads=1 --benchmarks=fillseq --use_existing_db=0 --db="$tmpdb"

# create results directory
mkdir -p results

# run db_bench readrandom with the given mutex and given number of threads
mutex=$1
threads=$2
echo "Running db_bench with $mutex and $threads threads"
if [ "$mutex" != "std" ]; then
    so_path="cmake_build_RelWithDebInfo/locks/lib$mutex.so"

    if [ ! -f "$so_path" ]; then
        echo "Mutex $mutex not found"
        exit 1
    fi

    preload="$so_path"
else
    preload=""
fi

LD_PRELOAD="$preload" "$DB_BENCH_PATH" --threads="$threads" --benchmarks=readrandom --use_existing_db=1 --db="$tmpdb" > "./results/$mutex-$threads.txt"

# clean up
echo "Cleaning up $tmpdb"
rm -rf "$tmpdb"
