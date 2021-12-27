# Internal c++ interfaces

The following interfaces are defined here:

* [`Chain`](chain.h) — used by wallet to access blockchain and mempool state.

* [`ChainClient`](chain.h) — used by node to start & stop `Chain` clients.

* [`Node`](node.h) — used by GUI to start & stop eleccoin node.

* [`Wallet`](wallet.h) — used by GUI to access wallets.

* [`Handler`](handler.h) — returned by `handleEvent` methods on interfaces above and used to manage lifetimes of event handlers.

* [`Init`](init.h) — used by multiprocess code to access interfaces above on startup.

* [`Ipc`](ipc.h) — used by multiprocess code to access `Init` interface across processes.

The interfaces above define boundaries between major components of eleccoin code (node, wallet, and gui), making it possible for them to run in [different processes](../../doc/multiprocess.md), and be tested, developed, and understood independently. These interfaces are not currently designed to be stable or to be used externally.
