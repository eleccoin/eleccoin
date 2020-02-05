// Copyright (c) 2011-2014 The Eleccoin Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef ELECCOIN_QT_ELECCOINADDRESSVALIDATOR_H
#define ELECCOIN_QT_ELECCOINADDRESSVALIDATOR_H

#include <QValidator>

/** Base58 entry widget validator, checks for valid characters and
 * removes some whitespace.
 */
class EleccoinAddressEntryValidator : public QValidator
{
    Q_OBJECT

public:
    explicit EleccoinAddressEntryValidator(QObject *parent);

    State validate(QString &input, int &pos) const;
};

/** Eleccoin address widget validator, checks for a valid eleccoin address.
 */
class EleccoinAddressCheckValidator : public QValidator
{
    Q_OBJECT

public:
    explicit EleccoinAddressCheckValidator(QObject *parent);

    State validate(QString &input, int &pos) const;
};

#endif // ELECCOIN_QT_ELECCOINADDRESSVALIDATOR_H
