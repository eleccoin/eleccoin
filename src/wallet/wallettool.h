// Copyright (c) 2020-2021 The Eleccoin Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef ELECCOIN_WALLET_WALLETTOOL_H
#define ELECCOIN_WALLET_WALLETTOOL_H

#include <wallet/wallet.h>

namespace WalletTool {

void WalletShowInfo(CWallet* wallet_instance);
bool ExecuteWalletToolFunc(const std::string& command, const std::string& file);

} // namespace WalletTool

#endif // ELECCOIN_WALLET_WALLETTOOL_H
