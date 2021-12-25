#!/usr/bin/env bash
# Copyright (c) 2020-2021 The Eleccoin Core developers
# Distributed under the MIT software license, see the accompanying
# file COPYING or http://www.opensource.org/licenses/mit-license.php.

export LC_ALL=C
TOPDIR=${TOPDIR:-$(git rev-parse --show-toplevel)}
BUILDDIR=${BUILDDIR:-$TOPDIR}

BINDIR=${BINDIR:-$BUILDDIR/src}
MANDIR=${MANDIR:-$TOPDIR/doc/man}

ELECCOIND=${ELECCOIND:-$BINDIR/eleccoind}
ELECCOINCLI=${ELECCOINCLI:-$BINDIR/eleccoin-cli}
ELECCOINTX=${ELECCOINTX:-$BINDIR/eleccoin-tx}
WALLET_TOOL=${WALLET_TOOL:-$BINDIR/eleccoin-wallet}
ELECCOINUTIL=${ELECCOINQT:-$BINDIR/eleccoin-util}
ELECCOINQT=${ELECCOINQT:-$BINDIR/qt/eleccoin-qt}

[ ! -x $ELECCOIND ] && echo "$ELECCOIND not found or not executable." && exit 1

# Don't allow man pages to be generated for binaries built from a dirty tree
DIRTY=""
for cmd in $ELECCOIND $ELECCOINCLI $ELECCOINTX $WALLET_TOOL $ELECCOINUTIL $ELECCOINQT; do
  VERSION_OUTPUT=$($cmd --version)
  if [[ $VERSION_OUTPUT == *"dirty"* ]]; then
    DIRTY="${DIRTY}${cmd}\n"
  fi
done
if [ -n "$DIRTY" ]
then
  echo -e "WARNING: the following binaries were built from a dirty tree:\n"
  echo -e $DIRTY
  echo "man pages generated from dirty binaries should NOT be committed."
  echo "To properly generate man pages, please commit your changes to the above binaries, rebuild them, then run this script again."
fi

# The autodetected version git tag can screw up manpage output a little bit
read -r -a ECCVER <<< "$($ELECCOINCLI --version | head -n1 | awk -F'[ -]' '{ print $6, $7 }')"

# Create a footer file with copyright content.
# This gets autodetected fine for eleccoind if --version-string is not set,
# but has different outcomes for eleccoin-qt and eleccoin-cli.
echo "[COPYRIGHT]" > footer.h2m
$ELECCOIND --version | sed -n '1!p' >> footer.h2m

for cmd in $ELECCOIND $ELECCOINCLI $ELECCOINTX $WALLET_TOOL $ELECCOINUTIL $ELECCOINQT; do
  cmdname="${cmd##*/}"
  help2man -N --version-string=${ECCVER[0]} --include=footer.h2m -o ${MANDIR}/${cmdname}.1 ${cmd}
done

rm -f footer.h2m
