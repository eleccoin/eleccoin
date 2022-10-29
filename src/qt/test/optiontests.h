// Copyright (c) 2020-2022 The Eleccoin Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef ELECCOIN_QT_TEST_OPTIONTESTS_H
#define ELECCOIN_QT_TEST_OPTIONTESTS_H

#include <qt/optionsmodel.h>

#include <QObject>

class OptionTests : public QObject
{
    Q_OBJECT
public:
    explicit OptionTests(interfaces::Node& node) : m_node(node) {}

private Q_SLOTS:
    void optionTests();

private:
    interfaces::Node& m_node;
};

#endif // ELECCOIN_QT_TEST_OPTIONTESTS_H
