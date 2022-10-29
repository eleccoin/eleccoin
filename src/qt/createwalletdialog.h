// Copyright (c) 2020-2022 The Eleccoin Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef ELECCOIN_QT_CREATEWALLETDIALOG_H
#define ELECCOIN_QT_CREATEWALLETDIALOG_H

#include <QDialog>

#include <memory>

namespace interfaces {
class ExternalSigner;
} // namespace interfaces

class WalletModel;

namespace Ui {
    class CreateWalletDialog;
}

/** Dialog for creating wallets
 */
class CreateWalletDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CreateWalletDialog(QWidget* parent);
    virtual ~CreateWalletDialog();

    void setSigners(const std::vector<std::unique_ptr<interfaces::ExternalSigner>>& signers);

    QString walletName() const;
    bool isEncryptWalletChecked() const;
    bool isDisablePrivateKeysChecked() const;
    bool isMakeBlankWalletChecked() const;
    bool isDescriptorWalletChecked() const;
    bool isExternalSignerChecked() const;

private:
    Ui::CreateWalletDialog *ui;
    bool m_has_signers = false;
};

#endif // ELECCOIN_QT_CREATEWALLETDIALOG_H
