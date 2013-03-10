/* BEGIN_COMMON_COPYRIGHT_HEADER
 * (c)LGPL2+
 *
 * Carousel - Qt-based managed component library.
 *
 * Copyright: 2011-2013 Carousel team
 * Authors:
 *   Eugene Chuguy <eugene.chuguy@gmail.com>
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

#ifndef SINGLELIBRARYFILECOMPONENTPROVIDER_H
#define SINGLELIBRARYFILECOMPONENTPROVIDER_H

#include "componentsystem/ComponentProvider.h"

class IDefinitionParser;
class ProxyComponent;

/*!
 * @brief
 * @details
 */
class COMP_API FileComponentProvider : public ComponentProvider
{
    Q_OBJECT
public:
    explicit FileComponentProvider(QObject *parent = nullptr);
    FileComponentProvider(const QString &path, QObject *parent = nullptr);
    ~FileComponentProvider();

public:
   /*!
    * @details
    *   Sets the path to the component definition.
    */
   void setPath(const QString &path);

   /*!
    * @details
    *   Gets the path to the component definition.
    */
   const QString &path() const;

   /*!
    * @details
    *   This method is added for convinient. It is a shortkey to the
    *   components().back().
    *
    *   Returns the last loaded component.
    */
    IComponent *lastLoadedComponent() const;

   /*!
    * @details
    *   Loads definition from the specified path and tries to create
    *   proxy component from it.
    *
    *   Returns a new discovered component.
    */
    virtual IComponent *loadComponent();

protected:
    /*!
     * @details
     *   Initializes the provider and calls update() to load component.
     *
     * @return @a false, if path is empty.
     */
    bool _initialize();

    /*!
     * @details
     *   Creates a definition parser.
     *
     *   Note that it takes ownership for the parser.
     */
    virtual IDefinitionParser *createParser();

    /*!
     * @details
     *   Creates a proxy component for loaded definition.
     *
     *   Note that it takes ownership for the proxy.
     */
    virtual ProxyComponent *createProxy();

private:
    QString m_path;
    IComponent *mp_lastLoadedComponent;
};

#endif // SINGLELIBRARYFILECOMPONENTPROVIDER_H
