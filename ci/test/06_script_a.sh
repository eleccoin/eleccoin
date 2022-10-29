#!/usr/bin/env bash
#
# Copyright (c) 2020-2022 The Eleccoin Core developers
# Distributed under the MIT software license, see the accompanying
# file COPYING or http://www.opensource.org/licenses/mit-license.php.

export LC_ALL=C.UTF-8

if [ -n "$ANDROID_TOOLS_URL" ]; then
  CI_EXEC make distclean || true
  CI_EXEC ./autogen.sh
  CI_EXEC ./configure "$ELECCOIN_CONFIG" --prefix="${DEPENDS_DIR}/aarch64-linux-android" || ( (CI_EXEC cat config.log) && false)
  CI_EXEC "make $MAKEJOBS && cd src/qt && ANDROID_HOME=${ANDROID_HOME} ANDROID_NDK_HOME=${ANDROID_NDK_HOME} make apk"
  exit 0
fi

ELECCOIN_CONFIG_ALL="--enable-external-signer --enable-suppress-external-warnings --disable-dependency-tracking --prefix=$DEPENDS_DIR/$HOST --bindir=$BASE_OUTDIR/bin --libdir=$BASE_OUTDIR/lib"
if [ -z "$NO_WERROR" ]; then
  ELECCOIN_CONFIG_ALL="${ELECCOIN_CONFIG_ALL} --enable-werror"
fi
CI_EXEC "ccache --zero-stats --max-size=$CCACHE_SIZE"

if [ -n "$CONFIG_SHELL" ]; then
  CI_EXEC "$CONFIG_SHELL" -c "./autogen.sh"
else
  CI_EXEC ./autogen.sh
fi

CI_EXEC mkdir -p "${BASE_BUILD_DIR}"
export P_CI_DIR="${BASE_BUILD_DIR}"

CI_EXEC "${BASE_ROOT_DIR}/configure" --cache-file=config.cache "$ELECCOIN_CONFIG_ALL" "$ELECCOIN_CONFIG" || ( (CI_EXEC cat config.log) && false)

CI_EXEC make distdir VERSION="$HOST"

export P_CI_DIR="${BASE_BUILD_DIR}/eleccoin-$HOST"

CI_EXEC ./configure --cache-file=../config.cache "$ELECCOIN_CONFIG_ALL" "$ELECCOIN_CONFIG" || ( (CI_EXEC cat config.log) && false)

set -o errtrace
trap 'CI_EXEC "cat ${BASE_SCRATCH_DIR}/sanitizer-output/* 2> /dev/null"' ERR

if [[ ${USE_MEMORY_SANITIZER} == "true" ]]; then
  # MemorySanitizer (MSAN) does not support tracking memory initialization done by
  # using the Linux getrandom syscall. Avoid using getrandom by undefining
  # HAVE_SYS_GETRANDOM. See https://github.com/google/sanitizers/issues/852 for
  # details.
  CI_EXEC 'grep -v HAVE_SYS_GETRANDOM src/config/eleccoin-config.h > src/config/eleccoin-config.h.tmp && mv src/config/eleccoin-config.h.tmp src/config/eleccoin-config.h'
fi

CI_EXEC make "$MAKEJOBS" "$GOAL" || ( echo "Build failure. Verbose build follows." && CI_EXEC make "$GOAL" V=1 ; false )

CI_EXEC "ccache --version | head -n 1 && ccache --show-stats"
CI_EXEC du -sh "${DEPENDS_DIR}"/*/
CI_EXEC du -sh "${PREVIOUS_RELEASES_DIR}"
