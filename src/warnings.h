// Copyright (c) 2020 The Eleccoin Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef ELECCOIN_WARNINGS_H
#define ELECCOIN_WARNINGS_H

#include <string>

void SetMiscWarning(const std::string& strWarning);
void SetfLargeWorkForkFound(bool flag);
bool GetfLargeWorkForkFound();
void SetfLargeWorkInvalidChainFound(bool flag);
/** Format a string that describes several potential problems detected by the core.
 * @param[in] verbose bool
 * - if true, get all warnings, translated (where possible), separated by <hr />
 * - if false, get the most important warning
 * @returns the warning string
 */
std::string GetWarnings(bool verbose);

#endif //  ELECCOIN_WARNINGS_H
