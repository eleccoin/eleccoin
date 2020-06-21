// Copyright (c) 2020 The Eleccoin Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef ELECCOIN_QT_ELECCOINUNITS_H
#define ELECCOIN_QT_ELECCOINUNITS_H

#include <amount.h>

#include <QAbstractListModel>
#include <QString>

// U+2009 THIN SPACE = UTF-8 E2 80 89
#define REAL_THIN_SP_CP 0x2009
#define REAL_THIN_SP_UTF8 "\xE2\x80\x89"

// QMessageBox seems to have a bug whereby it doesn't display thin/hair spaces
// correctly.  Workaround is to display a space in a small font.  If you
// change this, please test that it doesn't cause the parent span to start
// wrapping.
#define HTML_HACK_SP "<span style='white-space: nowrap; font-size: 6pt'> </span>"

// Define THIN_SP_* variables to be our preferred type of thin space
#define THIN_SP_CP   REAL_THIN_SP_CP
#define THIN_SP_UTF8 REAL_THIN_SP_UTF8
#define THIN_SP_HTML HTML_HACK_SP

/** Eleccoin unit definitions. Encapsulates parsing and formatting
   and serves as list model for drop-down selection boxes.
*/
class EleccoinUnits: public QAbstractListModel
{
    Q_OBJECT

public:
    explicit EleccoinUnits(QObject *parent);

    /** Eleccoin units.
      @note Source: https://en.eleccoin.it/wiki/Units . Please add only sensible ones
     */
    enum Unit
    {
        ECC,
        mECC,
        uECC,
        ELE
    };

    enum SeparatorStyle
    {
        separatorNever,
        separatorStandard,
        separatorAlways
    };

    //! @name Static API
    //! Unit conversion and formatting
    ///@{

    //! Get list of units, for drop-down box
    static QList<Unit> availableUnits();
    //! Is unit ID valid?
    static bool valid(int unit);
    //! Long name
    static QString longName(int unit);
    //! Short name
    static QString shortName(int unit);
    //! Longer description
    static QString description(int unit);
    //! Number of Electrons (1e-8) per unit
    static qint64 factor(int unit);
    //! Number of decimals left
    static int decimals(int unit);
    //! Format as string
    static QString format(int unit, const CAmount& amount, bool plussign=false, SeparatorStyle separators=separatorStandard);
    //! Format as string (with unit)
    static QString formatWithUnit(int unit, const CAmount& amount, bool plussign=false, SeparatorStyle separators=separatorStandard);
    //! Format as HTML string (with unit)
    static QString formatHtmlWithUnit(int unit, const CAmount& amount, bool plussign=false, SeparatorStyle separators=separatorStandard);
    //! Parse string to coin amount
    static bool parse(int unit, const QString &value, CAmount *val_out);
    //! Gets title for amount column including current display unit if optionsModel reference available */
    static QString getAmountColumnTitle(int unit);
    ///@}

    //! @name AbstractListModel implementation
    //! List model for unit drop-down selection box.
    ///@{
    enum RoleIndex {
        /** Unit identifier */
        UnitRole = Qt::UserRole
    };
    int rowCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    ///@}

    static QString removeSpaces(QString text)
    {
        text.remove(' ');
        text.remove(QChar(THIN_SP_CP));
        return text;
    }

    //! Return maximum number of base units (Electrons)
    static CAmount maxMoney();

private:
    QList<EleccoinUnits::Unit> unitlist;
};
typedef EleccoinUnits::Unit EleccoinUnit;

#endif // ELECCOIN_QT_ELECCOINUNITS_H
