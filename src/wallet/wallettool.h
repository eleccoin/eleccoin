// Copyright (c) 2020-2022 The Eleccoin Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef ELECCOIN_WALLET_WALLETTOOL_H
#define ELECCOIN_WALLET_WALLETTOOL_H

#include <string>

class ArgsManager;

namespace wallet {
namespace WalletTool {

bool ExecuteWalletToolFunc(const ArgsManager& args, const std::string& command);

} // namespace WalletTool
} // namespace wallet

#endif // ELECCOIN_WALLET_WALLETTOOL_H
