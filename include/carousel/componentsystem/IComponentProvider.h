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

#include <QtCore/QList>
#include <QtCore/QObject>

class IComponent;

/*!
 * @brief
 *   This is the expected provider definition for the boot loading sequence.
 * @details
 *   The IComponentProvider defines the contract that CarouselBootloader uses for
 *   adding registered and/or discovered components to the IComponentManager.
 *
 *   At your application you can override BootloaderBase::createComponentProvider() method to instantiate your
 *   own component provider  (e.g. DirectoryComponentProvider, that can discovering components in the file system).
 *
 *   You also might to override BootloaderBase::configureComponentProvider() to add compile-time-known components 
 *   statically in code using registerComponent() method.
 *
 *   Note, that providers do not takes ownership for components - it is moved to the IComponentManager during
 *   boot loading sequence.
 */
class CAROUSEL_API IComponentProvider : public QObject
{
    Q_OBJECT
public:
    IComponentProvider(){}
    virtual ~IComponentProvider(){}
    
    /*!
     * @details
     *   Gets the all components registered at the provider.
     */
    virtual QList<IComponent *> components() const = 0;

    /*!
     * @details
     *   Initializes the provider, which may load and validate the components.
     *   Returns @a true, if initialization was succesful; otherwise, returns @a false.
     */
    virtual bool initialize() = 0;

    /*!
     * @details
     *   Returns @a true, if provider alreadyinitialzied; otherwise, returns @a false.
     */
    virtual bool isInitialized() const = 0;

    /*!
     * @details
     *   Registers the specified component at the provider.
     *   Usually, you can register the same components or components with same names using 
     *   existing providers, but when components will be pushed to the IComponentManager
     *   from the providers - the last one doesn't allow duplicating components.
     *   @a Null pointers will be skipped.
     */
    virtual void registerComponent(IComponent *component) = 0;

private:
    Q_DISABLE_COPY(IComponentProvider)
};

