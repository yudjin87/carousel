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
#include <carousel/componentsystem/IComponentProvider.h>

#include <QtCore/QObject>

/*!
 * @brief
 *   The CompositeComponentProvider class provides access to members that control a collection
 *   of providers that behaves like a single provider.
 * @details
 *   You can use this class overriding the BootloaderBase::createComponentProvider() method in your
 *   bootloader. For example, if you want your application discovers system components from the
 *   nested @a "bin/" directory and custom user components from the @a "plugins/" it is a good idea
 *   to use CompositeComponentProvider class:
 * @code
 *   class MyBootloader : public CarouselBootloader
 *   {
 *   protected:
 *      IComponentProvider *MyBootloader::createComponentProvider()
 *      {
 *          return new CompositeComponentProvider();
 *      }
 *      void MyBootloader::configureComponentProvider()
 *      {
 *          DirectoryComponentProvider *sysDir = new DirectoryComponentProvider("bin/");
 *          (static_cast<CompositeComponentProvider *>(m_componentProvider))->addProvider(sysDir);
 *
 *          DirectoryComponentProvider *contribProvider = new DirectoryComponentProvider("plugins/");
 *          (static_cast<CompositeComponentProvider *>(m_componentProvider))->addProvider(contribProvider);
 *      }
 *      // other customization
 *      // ....
 *   };
 * @endcode
 *   The ComponentProvider also serves as a base class for more specialized Providers.
 *   Note, that it takes ownership for added providers, but not for components.
 *   Components' ownership is moved to the IComponentManager during boot loading sequence.
 */
class CAROUSEL_API CompositeComponentProvider : public IComponentProvider
{
    Q_OBJECT
public:
    /*!
     * @details
     *   Initializes a new instance of the CompositeComponentProvider class
     *   and adds a default ComponentProvider to the providers list.
     */
    explicit CompositeComponentProvider(QObject *parent = nullptr);
    ~CompositeComponentProvider();

    /*!
     * @details
     *   Adds the provider to the list of providers. Also takes ownership for the
     *   provider.
     */
    CompositeComponentProvider &addProvider(IComponentProvider *provider);

    /*!
     * @details
     *   Gets the all components that are registered at the providers.
     */
    QList<IComponent *> components() const override;

    /*!
     * @details
     *   Initializes the all providers, which may load and validate the components.
     */
    bool initialize() override;

    /*!
     * @details
     *   Returns @a true, if provider alreadyinitialzied; otherwise, returns @a false.
     */
    bool isInitialized() const override;

    /*!
     * @details
     *   Registers the specified component at the default provider.
     *   @a Null pointers will be skipped.
     */
    void registerComponent(IComponent *component) override;

protected:
    /*!
     * @details
     *   The list of added providers.
     */
    QList<IComponentProvider *> m_providers;

private:
    bool m_alreadyInit;
};

