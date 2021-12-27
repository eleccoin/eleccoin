// Copyright (c) 2020-2021 The Eleccoin Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef ELECCOIN_SHUTDOWN_H
#define ELECCOIN_SHUTDOWN_H

#include <util/translation.h> // For bilingual_str

/** Abort with a message */
bool AbortNode(const std::string& strMessage, bilingual_str user_message = bilingual_str{});

/** Initialize shutdown state. This must be called before using either StartShutdown(),
 * AbortShutdown() or WaitForShutdown(). Calling ShutdownRequested() is always safe.
 */
bool InitShutdownState();

/** Request shutdown of the application. */
void StartShutdown();

/** Clear shutdown flag. Only use this during init (before calling WaitForShutdown in any
 * thread), or in the unit tests. Calling it in other circumstances will cause a race condition.
 */
void AbortShutdown();

/** Returns true if a shutdown is requested, false otherwise. */
bool ShutdownRequested();

/** Wait for StartShutdown to be called in any thread. This can only be used
 * from a single thread.
 */
void WaitForShutdown();

#endif
