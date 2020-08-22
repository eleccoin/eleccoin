1.2.1 Release Notes
====================

Eleccoin Core version 1.2.1 is now available from:

  <https://eleccoin.org/>

How to Upgrade
==============

If you are running an older version, shut it down. Wait until it has completely
shut down (which might take a few minutes in some cases), then run the
installer (on Windows) or just copy over `/Applications/Eleccoin-Qt` (on Mac)
or `eleccoind`/`eleccoin-qt` (on Linux).

Upgrading directly from a version of Eleccoin Core that has reached its EOL is
possible, but it might take some time if the data directory needs to be migrated. Old
wallet versions of Eleccoin Core are generally supported.

Compatibility
==============

Eleccoin Core is supported and extensively tested on operating systems
using the Linux kernel, macOS 10.12+, and Windows 7 and newer.  Eleccoin
Core should also work on most other Unix-like systems but is not as
frequently tested on them.  It is not recommended to use Eleccoin Core on
unsupported systems.

From Eleccoin Core 1.2.0 onwards, macOS versions earlier than 10.12 are no
longer supported. Additionally, Eleccoin Core does not yet change appearance
when macOS "dark mode" is activated.

Known Bugs
==========

The process for generating the source code release ("tarball") has changed in an
effort to make it more complete, however, there are a few regressions in
this release:

- The generated `configure` script is currently missing, and you will need to
  install autotools and run `./autogen.sh` before you can run
  `./configure`. This is the same as when checking out from git.

- Instead of running `make` simply, you should instead run
  `ELECCOIN_GENBUILD_NO_GIT=1 make`.

Notable changes
===============

Changes regarding misbehaving peers
-----------------------------------

Peers that misbehave (e.g. send us invalid blocks) are now referred to as
discouraged nodes in log output, as they're not (and weren't) strictly banned:
incoming connections are still allowed from them, but they're preferred for
eviction.

Furthermore, a few additional changes are introduced to how discouraged
addresses are treated:

- Discouraging an address does not time out automatically after 24 hours
  (or the `-bantime` setting). Depending on traffic from other peers,
  discouragement may time out at an indeterminate time.

- Discouragement is not persisted over restarts.

- There is no method to list discouraged addresses. They are not returned by
  the `listbanned` RPC. That RPC also no longer reports the `ban_reason`
  field, as `"manually added"` is the only remaining option.

- Discouragement cannot be removed with the `setban remove` RPC command.
  If you need to remove a discouragement, you can remove all discouragements by
  stop-starting your node.

Notification changes
--------------------

`-walletnotify` notifications are now sent for wallet transactions that are
removed from the mempool because they conflict with a new block.

1.2.1 change log
=================

### Mining
- Fix GBT: Restore "!segwit" and "csv" to "rules" key

### P2P protocol and network code
- Replace automatic bans with discouragement filter

### Wallet
- Handle concurrent wallet loading 
- Minimal fix to restore conflicted transaction notifications

### RPC and other APIs
- Increment input value sum only once per UTXO in decodepsbt
- psbt: Increment input value sum only once per UTXO in decodepsbt

### GUI
- Add missing QPainterPath include
- update Qt base translations for macOS release

### Build system
- improve build OS configure output
- qt, build: Fix QFileDialog for static builds

### Tests and QA
- Remove cached directories and associated script blocks from appveyor config
- appveyor: Remove clcache

### Miscellaneous
- util: Don't reference errno when pthread fails
- Fix locking on WSL using flock instead of fcntl

Credits
=======

Thanks to everyone who directly contributed to this release:

- Unify


