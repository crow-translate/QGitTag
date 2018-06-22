#ifndef QGITRELEASE_H
#define QGITRELEASE_H

#include "qgitasset.h"

class QGitRelease
{
public:
    QGitRelease(const QString &owner, const QString &repo, int number = 0);

    QString name() const;
    QString tagName() const;
    QString body() const;

    QUrl url() const;
    QUrl tarUrl() const;
    QUrl zipUrl() const;

    QList<QGitAsset> assets() const;
    QDateTime createdAt() const;
    QDateTime publishedAt() const;

    int id() const;
    bool draft() const;
    bool prerelease() const;
    bool error() const;

private:
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
    bool m_draft;
    bool m_prerelease;
    bool m_error;
};

#endif // QGITRELEASE_H
