// Copyright (c) 2020-2022 The Eleccoin Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef ELECCOIN_QT_OPENURIDIALOG_H
#define ELECCOIN_QT_OPENURIDIALOG_H

#include <QDialog>

class PlatformStyle;

namespace Ui {
    class OpenURIDialog;
}

class OpenURIDialog : public QDialog
{
    Q_OBJECT

public:
    explicit OpenURIDialog(const PlatformStyle* platformStyle, QWidget* parent);
    ~OpenURIDialog();

    QString getURI();

protected Q_SLOTS:
    void accept() override;
    void changeEvent(QEvent* e) override;

private:
    Ui::OpenURIDialog* ui;

    const PlatformStyle* m_platform_style;
};

#endif // ELECCOIN_QT_OPENURIDIALOG_H
