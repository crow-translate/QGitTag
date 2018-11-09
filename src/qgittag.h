/*
 *  Copyright © 2018 Gennady Chernyshchuk <genaloner@gmail.com>
 *
 *  This file is part of Crow Translate.
 *
 *  Crow Translate is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a get of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#ifndef QGITTAG_H
#define QGITTAG_H

#include <QObject>
#include <QNetworkAccessManager>

#include "qgitasset.h"

class QGitTag : public QObject
{
    Q_OBJECT

public:
    enum RequestError {
        NoError,
        NetworkError,
        NoRelease
    };

    QGitTag(QObject *parent = nullptr);
    void get(const QString &owner, const QString &repo, int number = 0);

    QString name() const;
    QString tagName() const;
    QString body() const;

    QUrl url() const;
    QUrl tarUrl() const;
    QUrl zipUrl() const;

    QList<QGitAsset> assets() const;
    int assetId(const QString &str) const;

    QDateTime createdAt() const;
    QDateTime publishedAt() const;

    int id() const;
    int tagNumber() const;
    bool draft() const;
    bool prerelease() const;
    RequestError error() const;
    QString errorName() const;

signals:
    void requestFinished();

private slots:
    void parseReply();

private:
    void clearData();

    QNetworkAccessManager m_network{this};

    QString m_name;
    QString m_tagName;
    QString m_body;

    QUrl m_url;
    QUrl m_tarUrl;
    QUrl m_zipUrl;
    QList<QGitAsset> m_assets;

    QDateTime m_createdAt;
    QDateTime m_publishedAt;

    int m_id;
    int m_tagNumber;
    bool m_draft;
    bool m_prerelease;

    RequestError m_error;
    QString m_errorName;
};

#endif // QGITTAG_H
