#!/bin/sh
set -e
if test "$CONFIGURATION" = "Debug"; then :
  cd /Users/omaroubari/repositories/opencvcourse/build
  make -f /Users/omaroubari/repositories/opencvcourse/build/CMakeScripts/ReRunCMake.make
fi
if test "$CONFIGURATION" = "Release"; then :
  cd /Users/omaroubari/repositories/opencvcourse/build
  make -f /Users/omaroubari/repositories/opencvcourse/build/CMakeScripts/ReRunCMake.make
fi
if test "$CONFIGURATION" = "MinSizeRel"; then :
  cd /Users/omaroubari/repositories/opencvcourse/build
  make -f /Users/omaroubari/repositories/opencvcourse/build/CMakeScripts/ReRunCMake.make
fi
if test "$CONFIGURATION" = "RelWithDebInfo"; then :
  cd /Users/omaroubari/repositories/opencvcourse/build
  make -f /Users/omaroubari/repositories/opencvcourse/build/CMakeScripts/ReRunCMake.make
fi

