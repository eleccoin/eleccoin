// Copyright (c) 2020-2022 The Eleccoin Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef ELECCOIN_TEST_UTIL_WALLET_H
#define ELECCOIN_TEST_UTIL_WALLET_H

#include <string>

namespace wallet {
class CWallet;
} // namespace wallet

// Constants //

extern const std::string ADDRESS_ECRT1_UNSPENDABLE;

// RPC-like //

/** Import the address to the wallet */
void importaddress(wallet::CWallet& wallet, const std::string& address);
/** Returns a new address from the wallet */
std::string getnewaddress(wallet::CWallet& w);


#endif // ELECCOIN_TEST_UTIL_WALLET_H
