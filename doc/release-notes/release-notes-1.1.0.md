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

- Add multi-language.
- Fixed wrong contact information.

Credits
=======

Thanks to everyone who directly contributed to this release:

- -