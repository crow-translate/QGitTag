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

#include <QNetworkReply>
#include <QEventLoop>
#include <QJsonDocument>
#include <QJsonArray>

#include "qgitrelease.h"

QGitRelease::QGitRelease(QObject *parent) :
    QObject (parent)
{

}

void QGitRelease::get(const QString &owner, const QString &repo, int number)
{
    // Generate URL
    QUrl apiUrl("https://api.github.com/repos/" + owner + "/" + repo + "/releases");

    // Send request
    QNetworkAccessManager manager;
    QNetworkReply *reply = manager.get(QNetworkRequest(apiUrl));

    // Wait for the response
    QEventLoop event;
    QObject::connect(reply, &QNetworkReply::finished, &event, &QEventLoop::quit);
    event.exec();

    // Check for network error
    if (reply->error() != QNetworkReply::NoError) {
        m_error = NetworkError;
        m_errorName = reply->errorString();
        clearData();
        return;
    }

    // Convert to JsonArray
    QJsonDocument jsonResponse = QJsonDocument::fromJson(reply->readAll());
    QJsonArray jsonData = jsonResponse.array();

    // Check if release number is out of bounds
    if (jsonData.at(number).type() == QJsonValue::Undefined) {
        m_error = NoRelease;
        m_errorName = "Release number " + QString::number(number) + " is missing";
        clearData();
        return;
    }

    QJsonObject release = jsonData.at(number).toObject();
    m_name = release["name"].toString();
    m_tagName = release["tag_name"].toString();
    m_body = release["body"].toString();

    m_url = release["html_url"].toString();
    m_tarUrl = release["tarball_url"].toString();
    m_zipUrl = release["zipball_url"].toString();

    m_createdAt = QDateTime::fromString(release["created_at"].toString(), Qt::ISODate);
    m_publishedAt = QDateTime::fromString(release["published_at"].toString(), Qt::ISODate);

    m_id = release["id"].toInt();
    m_draft = release["draft"].toBool();
    m_prerelease = release["prerelease"].toBool();

    foreach (const auto &asset, release["assets"].toArray())
        m_assets << QGitAsset(asset.toObject());

    m_error = NoError;
}

QString QGitRelease::name() const
{
    return m_name;
}

QString QGitRelease::tagName() const
{
    return m_tagName;
}

QString QGitRelease::body() const
{
    return m_body;
}

QUrl QGitRelease::url() const
{
    return m_url;
}

QUrl QGitRelease::tarUrl() const
{
    return m_tarUrl;
}

QUrl QGitRelease::zipUrl() const
{
    return m_zipUrl;
}

QList<QGitAsset> QGitRelease::assets() const
{
    return m_assets;
}

int QGitRelease::asset(const QString &contentType) const
{
    for (int i = 0; i < m_assets.size(); ++i) {
        if (m_assets.at(i).contentType() == contentType)
            return i;
    }

    return -1; // No asset found
}

QDateTime QGitRelease::createdAt() const
{
    return m_createdAt;
}

QDateTime QGitRelease::publishedAt() const
{
    return m_publishedAt;
}

int QGitRelease::id() const
{
    return m_id;
}

bool QGitRelease::draft() const
{
    return m_draft;
}

bool QGitRelease::prerelease() const
{
    return m_prerelease;
}

QGitRelease::RequestError QGitRelease::error() const
{
    return m_error;
}

QString QGitRelease::errorName() const
{
    return m_errorName;
}

void QGitRelease::clearData()
{
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
    m_draft = false;
    m_prerelease = false;
}
