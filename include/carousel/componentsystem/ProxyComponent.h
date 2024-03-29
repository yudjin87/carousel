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
#include <carousel/componentsystem/BaseComponent.h>

class IDefinitionParser;
class IComponentLoader;

class CAROUSEL_API ProxyComponent : public BaseComponent
{
    Q_OBJECT
public:
    /*!
     * @details
     *   Initializes a new instance of the ProxyComponent class with
     *   default component loader and specified parent.
     */
    explicit ProxyComponent(ComponentDefinition *definition, QObject *parent = nullptr);

    /*!
     * @details
     *   Initializes a new instance of the ProxyComponent class with
     *   component loader and parent.
     */
    ProxyComponent(ComponentDefinition *definition, IComponentLoader *loader, QObject *parent = nullptr);

    ~ProxyComponent();

    /*!
     * @details
     *   Gets the value specified whether this component is enabled, disabled, or unavailable.
     *   When the availability is enabled, the component is checked in the Components dialog.
     * @sa setAvailability
     */
    Availability availability() const override;

    /*!
     * @details
     *   Gets the state in which the component currently is. See the description of the
     *   IComponent::State enum for details.
     * @sa setState
     */
    State state() const override;

    /*!
     * @details
     *   Finds extension's pointer associated with it type id
     *   in inner objects dictionary.
     * @return The raw pointer corresponded with specified type id if such found. Null pointer otherwise.
     */
    void *getExtension(const QString &byTypeId) const override;

    IComponent *loadedComponent() const;

    /*!
     * @details
     *   Sets up definition properties and component name using @a parser.
     *
     *   Returns false if component library could not be loaded.
     *
     *   @a parser should already read properties.
     */
    virtual bool initialize(QString *error = nullptr);

    /*!
     * @details
     *   Sets the value specified whether this component is enabled or disabled.
     *   The checked state of the component is saved in the user settings.
     * @sa availability
     */
    void setAvailability(Availability newMode) override;

    /*!
     * @details
     *   Sets the value specified the component current state.
     *
     * @note You should not use this method directly, it is for internal goals only.
     *
     * @sa state
     */
    void setState(State newState) override;

protected:
    /*!
     * @details
     *   It is a defensive declaration of the public shutdown() method, that invokes only after startup().
     *   When override in derived classes shuts down the component. Nothing to do by default.
     */
    virtual void onShutdown(IServiceLocator *serviceLocator) override;

    /*!
     * @details
     *   It is a defensive declaration of the public startup() method, that invokes only if component is
     *   not started.
     *   When override in derived classes starts up the component. Nothing to do by default.
     * @param serviceLocator is a reference to the services pool. It is needed to register/locate to
     *   common services and other components' services.
     */
    virtual bool onStartup(IServiceLocator *serviceLocator) override;

private:
    Q_DISABLE_COPY(ProxyComponent)
    IComponentLoader *m_loader;
    IComponent *m_component;
    bool m_initialized;
};

