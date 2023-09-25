#!/bin/bash

# Run db_bench with the given mutex and given number of threads and print the results to stdout.
# Passing multiple integer arguments after number of threads will benchmark the same mutex with different contention levels.


# default db_bench path
DB_BENCH_PATH="cmake_build_RelWithDebInfo/leveldb/db_bench"

# seed the db with fillseq
tmpdb=$(mktemp -d)
echo "Filling db at $tmpdb with fillseq"
"$DB_BENCH_PATH" --threads=1 --benchmarks=fillseq --use_existing_db=0 --db="$tmpdb"

# run db_bench readrandom with the given mutex and given number of threads
mutex=$1
for threads in "${@:2}"; do
    echo "Running db_bench with $mutex and $threads threads"
    if [ "$mutex" != "std" ]; then
      test -f "cmake_build_RelWithDebInfo/locks/lib$mutex.so" || (echo "Mutex $mutex not found" && exit 1)

      export LD_PRELOAD="cmake_build_RelWithDebInfo/locks/lib$mutex.so"
    fi
    "$DB_BENCH_PATH" --threads="$threads" --benchmarks=readrandom --use_existing_db=1 --db="$tmpdb" > "./results/$mutex-$threads.txt"
done
