#!/bin/sh
set -eu
cd "$(dirname "$0")/.."
make >/dev/null
TMP="$(mktemp -d)"
trap 'rm -rf "$TMP"' EXIT HUP INT TERM

# macOS may provide gtimeout (coreutils) instead of timeout.
run_limited() {
    seconds="$1"
    shift
    if command -v timeout >/dev/null 2>&1; then
        timeout "$seconds" "$@"
    elif command -v gtimeout >/dev/null 2>&1; then
        gtimeout "$seconds" "$@"
    else
        "$@"
    fi
}

if ./philo 0 800 200 200 >"$TMP/invalid" 2>&1; then
    echo "FAIL: invalid input accepted"
    exit 1
fi

run_limited 5 ./philo 1 80 100 100 >"$TMP/one"
grep -q 'has taken a fork' "$TMP/one"
grep -q 'died' "$TMP/one"
if grep -q 'is eating' "$TMP/one"; then
    echo "FAIL: one philosopher ate using a single fork"
    exit 1
fi

run_limited 10 ./philo 5 800 200 200 3 >"$TMP/five"
if grep -q 'died' "$TMP/five"; then
    echo "FAIL: unexpected death in finite five-philosopher test"
    exit 1
fi
awk '/is eating/ { meals[$2]++ } END { for (i = 1; i <= 5; i++) if (meals[i] < 3) exit 1 }' "$TMP/five"

run_limited 10 ./philo 4 800 200 200 3 >"$TMP/four"
if grep -q 'died' "$TMP/four"; then
    echo "FAIL: unexpected death in finite four-philosopher test"
    exit 1
fi

run_limited 5 ./philo 3 100 200 200 >"$TMP/death"
grep -q 'died' "$TMP/death"
echo "All smoke tests passed."
