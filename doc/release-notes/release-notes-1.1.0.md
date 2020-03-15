Eleccoin Core version 1.1.0 is now available from:

  <https://static.eleccoin.org/bin/eleccoin-core-1.1.0/>

This release includes new features, various bug fixes and performance
improvements, as well as updated translations.

Please report bugs using the issue tracker at GitHub:

  <https://github.com/eleccoin/eleccoin/issues>

To receive security and update notifications, please subscribe to:

  <https://www.eleccoin.org>

How to Upgrade
==============

If you are running an older version, shut it down. Wait until it has completely
shut down (which might take a few minutes for older versions), then run the
installer (on Windows) or just copy over `/Applications/Eleccoin-Qt` (on Mac)
or `eleccoind`/`eleccoin-qt` (on Linux).

Upgrading directly from a version of Eleccoin Core that has reached its EOL is
possible, but might take some time if the datadir needs to be migrated.  Old
wallet versions of Eleccoin Core are generally supported.

Compatibility
=============

Eleccoin Core is supported and extensively tested on operating systems using
the Linux kernel, macOS 10.10+, and Windows 7 and newer. It is not recommended
to use Eleccoin Core on unsupported systems.

Eleccoin Core should also work on most other Unix-like systems but is not
as frequently tested on them.

MacOS <10.10 is no longer supported because of Qt 5.9.x which doesn't 
support versions of macOS older than 10.10. 
Additionally, Eleccoin Core does not yet change appearance when
macOS "dark mode" is activated.

Users running macOS Catalina may need to "right-click" and then choose "Open"
to open the Eleccoin Core .dmg. This is due to new signing requirements
imposed by Apple, which the Eleccoin Core project does not yet adhere too.

1.1.0 change log
================

### Wallet
- Fix origfee return for bumpfee with feerate arg (instagibbs)
- Fix `unique_ptr` usage in boost::signals2 (promag)
- Fix issue with conflicted mempool tx in listsinceblock (adamjonas, mchrostowski)
- Bug: IsUsedDestination shouldn't use key id as script id for ScriptHash (instagibbs)
- IsUsedDestination should count any known single-key address (instagibbs)
- Reset reused transactions cache (fjahr)

### RPC and other APIs
- cli: Fix fatal leveldb error when specifying -blockfilterindex=basic twice (brakmic)
- require second argument only for scantxoutset start action (achow101)
- zmq: Fix due to invalid argument and multiple notifiers (promag)
- psbt: handle unspendable psbts (achow101)
- psbt: check that various indexes and amounts are within bounds (achow101)

### GUI
- Add multi-language
- Fix missing qRegisterMetaType for `size_t` (hebasto)
- disable File-\>CreateWallet during startup (fanquake)
- Fix comparison function signature (hebasto)
- Fix unintialized WalletView::progressDialog (promag)

### Tests and QA
- Fixed wrong contact information
- Appveyor improvement - text file for vcpkg package list (sipsorcery)
- fix "eleccoind already running" warnings on macOS (fanquake)
- add missing #include to fix compiler errors (kallewoof)

### Platform support
- Update msvc build for Visual Studio 2019 v16.4 (sipsorcery)
- Updates to appveyor config for VS2019 and Qt5.9.8 + msvc project fixes (sipsorcery)
- bug-fix macos: give free bytes to `F_PREALLOCATE` (kallewoof)

### Miscellaneous
- init: Stop indexes on shutdown after ChainStateFlushed callback (jimpo)
- util: Add missing headers to util/fees.cpp (hebasto)
- Unbreak build with Boost 1.72.0 (jbeich)
- scripts: Fix symbol-check & security-check argument passing (fanquake)
- Log to net category for exceptions in ProcessMessages (laanwj)
- Update univalue subtree (MarcoFalke)

Credits
=======

Thanks to everyone who directly contributed to this release:

- Aaron Clauson
- Adam Jonas
- Andrew Chow
- Fabian Jahr
- fanquake
- Gregory Sanders
- Harris
- Hennadii Stepanov
- Jan Beich
- Jim Posen
- João Barbosa
- Karl-Johan Alm
- Luke Dashjr
- MarcoFalke
- Michael Chrostowski
- Russell Yanofsky
- Wladimir J. van der Laan