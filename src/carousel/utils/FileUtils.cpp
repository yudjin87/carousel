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

#include "utils/FileUtils.h"

#include <QtCore/QDir>
#include <QtCore/QFile>
#include <QtCore/QFileInfo>
#include <QtCore/QFileInfoList>

namespace fileUtils
{
bool removeTree(const QString &dirName)
{
    bool result = true;
    QDir dir(dirName);

    QDir::Filters filters = QDir::NoDotAndDotDot | QDir::System | QDir::Hidden  | QDir::AllDirs | QDir::Files;
    if (!dir.exists(dirName))
        return true;

    for (QFileInfo info : dir.entryInfoList(filters, QDir::DirsFirst)) {
        if (info.isDir())
            result = removeTree(info.absoluteFilePath());
        else
            result = QFile::remove(info.absoluteFilePath());

        if (!result)
            return result;
    }

    result = dir.rmdir(dirName);
    return result;
}

} //namespace fileUtils
