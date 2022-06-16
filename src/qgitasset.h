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

#ifndef QGITASSET_H
#define QGITASSET_H

#include <QDateTime>
#include <QUrl>

class QJsonObject;

/**
 * @brief Provides information about tag assets
 *
 * Can be obtained from the QGitTag object, which contains a list of assets for a particular release.
 *
 * Example:
 * @code
 * QGitTag tag;
 * // Obtain information
 * 
 * QTextStream out(stdout);
 * out << "Asset: " + tag.assets().at(0).name() << endl; // Prints asset filename
 * out << "Type: " + tag.assets().at(0).type() << endl; // Prints asset type
 * out << "Download Url: " + tag.assets().at(0).url() << endl; // Prints download link
 * @endcode
 */
class QGitAsset
{
public:
    /**
     * @brief Create object
     *
     * Constructs an object from asset. Normally you don't need call this function.
     *
     * @param asset asset object
     */
    explicit QGitAsset(const QJsonObject &asset);

    /**
     * @brief Name
     *
     * @return name of represented asset file
     */
    QString name() const;

    /**
     * @brief MIME-type
     *
     * @return asset MIME-type
     */
    QString contentType() const;

    /**
     * @brief URL
     *
     * @return asset download link
     */
    QUrl url() const;

    /**
     * @brief Creation date
     *
     * @return asset creation date
     */
    QDateTime createdAt() const;

    /**
     * @brief Publication date
     *
     * @return asset publication date
     */
    QDateTime publishedAt() const;

    /**
     * @brief ID
     *
     * @return asset identifier
     */
    int id() const;

    /**
     * @brief Size
     *
     * @return asset file size
     */
    int size() const;

    /**
     * @brief Downloads count
     *
     * @return number of the the asset downloads
     */
    int downloadCount() const;

private:
    QString m_contentType;
    QString m_type;
    QUrl m_url;

    QDateTime m_createdAt;
    QDateTime m_publishedAt;

    int m_id;
    int m_size;
    int m_downloadCount;
};

#endif // QGITASSET_H
