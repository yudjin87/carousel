/* BEGIN_COMMON_COPYRIGHT_HEADER
 * (c)LGPL2+
 *
 * Carousel - Qt-based managed component library.
 *
 * Copyright: 2011-2016 Carousel team
 * Authors:
 *   Yevhen Chuhui (Eugene Chuguy) <yevhen.chuhui@gmail.com>
 *
 * This program or library is free software; you can redistribute it
 * and/or modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.

 * You should have received a copy of the GNU Lesser General
 * Public License along with this library; if not, write to the
 * Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301 USA
 *
 * END_COMMON_COPYRIGHT_HEADER */

#pragma once
#include <carousel/carousel_global.h>

#include <QtCore/QObject>

/*!
 * @brief
 *   This class represents a Carousel component version.
 * @details
 *   The version format is a four-part string with the following format:
 *   <major version>.<minor version>.<build number>.<revision>
 *
 *   It derives from the QObject just for being enable from the scripting.
 */
class CAROUSEL_API Version : public QObject
{
    Q_OBJECT
public:
    explicit Version(QObject *parent = nullptr);
    Version(int major_version, int minor_version, QObject *parent = nullptr);
    Version(int major_version, int minor_version, int build_version, QObject *parent = nullptr);
    Version(int major_version, int minor_version, int build_version, int revision_version, QObject *parent = nullptr);
    ~Version();

public:
    static bool parseString(const QString &version, int *major, int *minor, int *build = nullptr, int *revision = nullptr);
    static Version *fromString(const QString &version, bool *ok = nullptr);

    void setVersion(int major_version, int minor_version, int build_version, int revision_version);
    void setMajor(int major_version);
    void setMinor(int minor_version);
    void setBuild(int build_version);
    void setRevision(int revision_version);

    int major() const;
    int minor() const;
    int build() const;
    int revision() const;

    bool operator<(const Version &other) const;
    bool operator<=(const Version &other) const;
    bool operator>(const Version &other) const;
    bool operator>=(const Version &other) const;
    bool operator==(const Version &other) const;
    bool operator!=(const Version &other) const;
    bool isEqual(const Version *other) const;

public slots:
    /*!
     * @details
     *   Returns @a true if all version components are 0.
     */
    bool isEmpty() const;

    /*!
     * @details
     *   Returns a string representation of the version in the following format:
     *   <major version>.<minor version>.<build number>.<revision>
     */
    QString toString() const;

private:
    Q_DISABLE_COPY(Version)
    int compare(const Version &other) const;

private:
    int m_major_version;
    int m_minor_version;
    int m_build_version;
    int m_revision_version;
};

