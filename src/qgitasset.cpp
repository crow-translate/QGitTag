#include "qgitasset.h"

QGitAsset::QGitAsset(const QJsonObject &asset)
{
    m_contentType = asset["name"].toString();
    m_type = asset["content_type"].toString();
    m_url = asset["browser_download_url"].toString();

    m_createdAt = QDateTime::fromString(asset["created_at"].toString(), Qt::ISODate);
    m_publishedAt = QDateTime::fromString(asset["published_at"].toString(), Qt::ISODate);

    m_id = asset["id"].toInt();
    m_size = asset["size"].toInt();
    m_downloadCount = asset["download_count"].toInt();
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
