#!/bin/sh
#
# This script is used to build and run a local executable
# NOTE: Running on a unix system is required, use docker for windows
set -e
cmake . >/dev/null
make >/dev/null
exec ./serverplusplus "$@"
