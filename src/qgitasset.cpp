/*
 *  Copyright © 2018-2019 Hennadii Chernyshchyk <genaloner@gmail.com>
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

#include "qgitasset.h"

#include <QJsonObject>

QGitAsset::QGitAsset(const QJsonObject &asset)
    : m_contentType(asset["name"].toString())
    , m_type(asset["content_type"].toString())
    , m_url(asset["browser_download_url"].toString())
    , m_createdAt(QDateTime::fromString(asset["created_at"].toString(), Qt::ISODate))
    , m_publishedAt(QDateTime::fromString(asset["published_at"].toString(), Qt::ISODate))
    , m_id(asset["id"].toInt())
    , m_size(asset["size"].toInt())
    , m_downloadCount(asset["download_count"].toInt())
{
}

QString QGitAsset::name() const
{
    return m_contentType;
}

QString QGitAsset::contentType() const
{
    return m_type;
}

QUrl QGitAsset::url() const
{
    return m_url;
}

QDateTime QGitAsset::createdAt() const
{
    return m_createdAt;
}

QDateTime QGitAsset::publishedAt() const
{
    return m_publishedAt;
}

int QGitAsset::id() const
{
    return m_id;
}

int QGitAsset::size() const
{
    return m_size;
}

int QGitAsset::downloadCount() const
{
    return m_downloadCount;
}
