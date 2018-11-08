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
        m_error = true;
        m_body = reply->errorString();
        return;
    }

    // Convert to JsonArray
    QJsonDocument jsonResponse = QJsonDocument::fromJson(reply->readAll());
    QJsonArray jsonData = jsonResponse.array();

    // Check if release number is out of bounds
    if (jsonData.at(number).type() == QJsonValue::Undefined) {
        m_error = true;
        m_body = "Release number " + QString::number(number) + " is missing";
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

    foreach (auto asset, release["assets"].toArray())
        m_assets << QGitAsset(asset.toObject());
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

bool QGitRelease::error() const
{
    return m_error;
}
