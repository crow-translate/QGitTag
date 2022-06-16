/*
 *  Copyright © 2018-2022 Hennadii Chernyshchyk <genaloner@gmail.com>
 *
 *  This file is part of QGitTag.
 *
 *  QGitTag is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  QGitTag is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with QGitTag. If not, see <https://www.gnu.org/licenses/>.
 */

#include "qgittag.h"

#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QNetworkReply>

QGitTag::QGitTag(QObject *parent)
    : QObject(parent)
    , m_network(new QNetworkAccessManager(this))
{
}

void QGitTag::get(const QString &owner, const QString &repo, int number)
{
    m_tagNumber = number;

    // Send request
    m_network->get(QNetworkRequest(QStringLiteral("https://api.github.com/repos/%1/%2/releases").arg(owner, repo)));
    QObject::connect(m_network, &QNetworkAccessManager::finished, this, &QGitTag::parseReply);
}

QString QGitTag::name() const
{
    return m_name;
}

QString QGitTag::tagName() const
{
    return m_tagName;
}

QString QGitTag::body() const
{
    return m_body;
}

QUrl QGitTag::url() const
{
    return m_url;
}

QUrl QGitTag::tarUrl() const
{
    return m_tarUrl;
}

QUrl QGitTag::zipUrl() const
{
    return m_zipUrl;
}

QList<QGitAsset> QGitTag::assets() const
{
    return m_assets;
}

int QGitTag::assetId(const QString &str) const
{
    for (int i = 0; i < m_assets.size(); ++i) {
        if (m_assets.at(i).name().contains(str))
            return i;
    }

    return -1; // No asset found
}

QDateTime QGitTag::createdAt() const
{
    return m_createdAt;
}

QDateTime QGitTag::publishedAt() const
{
    return m_publishedAt;
}

int QGitTag::id() const
{
    return m_id;
}

int QGitTag::tagNumber() const
{
    return m_tagNumber;
}

bool QGitTag::isDraft() const
{
    return m_draft;
}

bool QGitTag::isPrerelease() const
{
    return m_prerelease;
}

QGitTag::RequestError QGitTag::error() const
{
    return m_error;
}

QString QGitTag::errorString() const
{
    return m_errorString;
}

void QGitTag::parseReply(QNetworkReply *reply)
{
    reply->deleteLater();

    // Check for network error
    if (reply->error() != QNetworkReply::NoError) {
        setError(NetworkError, reply->errorString());
        return;
    }

    // Convert to JsonArray
    QJsonDocument jsonResponse = QJsonDocument::fromJson(reply->readAll());
    QJsonArray jsonData = jsonResponse.array();

    // Check if release number exists
    if (jsonData.at(m_tagNumber).type() == QJsonValue::Undefined) {
        setError(NoRelease, tr("Release number %1 is missing").arg(m_tagNumber));
        return;
    }

    QJsonObject release = jsonData.at(m_tagNumber).toObject();
    m_name = release[QLatin1String("name")].toString();
    m_tagName = release[QLatin1String("tag_name")].toString();
    m_body = release[QLatin1String("body")].toString();

    m_url = release[QLatin1String("html_url")].toString();
    m_tarUrl = release[QLatin1String("tarball_url")].toString();
    m_zipUrl = release[QLatin1String("zipball_url")].toString();

    m_createdAt = QDateTime::fromString(release[QLatin1String("created_at")].toString(), Qt::ISODate);
    m_publishedAt = QDateTime::fromString(release[QLatin1String("published_at")].toString(), Qt::ISODate);

    m_id = release[QLatin1String("id")].toInt();
    m_draft = release[QLatin1String("draft")].toBool();
    m_prerelease = release[QLatin1String("prerelease")].toBool();

    for (const QJsonValueRef asset : release[QLatin1String("assets")].toArray())
        m_assets << QGitAsset(asset.toObject());

    m_error = NoError;
    emit finished();
}

void QGitTag::setError(RequestError errorType, const QString &errorString)
{
    m_error = errorType;
    m_errorString = errorString;

    m_name.clear();
    m_tagName.clear();
    m_body.clear();
    m_url.clear();
    m_tarUrl.clear();
    m_zipUrl.clear();
    m_assets.clear();

    m_createdAt = QDateTime();
    m_publishedAt = QDateTime();

    m_id = 0;
    m_tagNumber = 0;
    m_draft = false;
    m_prerelease = false;

    emit finished();
}
