/* BEGIN_COMMON_COPYRIGHT_HEADER
 * (c)LGPL2+
 *
 * Carousel - Qt-based managed component library.
 *
 * Copyright: 2011-2015 Carousel team
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

#include "carto/CategorizedRenderer.h"
#include "carto/IFeatureRendererVisitor.h"
#include "carto/IFeatureRendererVisitor.h"
#include "carto/LegendGroup.h"
#include "carto/LegendClass.h"

#include <geodatabase/IFeatureClass.h>
#include <geodatabase/IFeature.h>
#include <geodatabase/IRecord.h>

#include <carousel/logging/LoggerFacade.h>

#include <algorithm>

namespace
{
static LoggerFacade Log = LoggerFacade::createLogger("Cat.Renderer");
}

CategorizedRenderer::CategorizedRenderer(QObject *parent)
    : IFeatureRenderer(parent)
    , m_legend(new LegendGroup())
    , m_categoryFieldIndex(0)
    , m_categories()
{
}

CategorizedRenderer::CategorizedRenderer(const CategorizedRenderer &other)
    : IFeatureRenderer()
    , m_legend(other.m_legend->clone())
    , m_categoryFieldIndex(other.m_categoryFieldIndex)
    , m_categories()
{
    for (const auto& symbolPair : other.m_categories)
    {
        const QVariant& value = symbolPair.first;
        const ISymbolUPtr& symbol = symbolPair.second;
        m_categories.insert(std::make_pair(value, ISymbolUPtr(symbol->clone())));
    }
}

CategorizedRenderer &CategorizedRenderer::operator=(const CategorizedRenderer &other)
{
    if (this == &other)
    {
        return *this;
    }

    m_legend.reset(other.m_legend->clone());
    m_categoryFieldIndex = other.m_categoryFieldIndex;

    for (const auto& symbolPair : other.m_categories)
    {
        const QVariant& value = symbolPair.first;
        const ISymbolUPtr& symbol = symbolPair.second;
        m_categories.insert(std::make_pair(value, ISymbolUPtr(symbol->clone())));
    }

    return *this;
}

CategorizedRenderer::~CategorizedRenderer()
{
}

void CategorizedRenderer::draw(const QVector<IFeature *> &features, QPainter *painter)
{
    for (const IFeature *feature : features)
    {
        const IRecordUPtr& rec = feature->record();
        const QVariant& featureValue = rec->value(m_categoryFieldIndex);
        ISymbol* symbolForCategory = symbol(featureValue);
        Q_ASSERT(symbolForCategory != nullptr && "Default symbols are not implemented yet");

        symbolForCategory->setupPainter(painter);
        symbolForCategory->draw(feature->geometry(), painter);
        symbolForCategory->resetPainter(painter);
    }
}

ILegendGroup *CategorizedRenderer::legend()
{
    return m_legend.get();
}

const ILegendGroup *CategorizedRenderer::legend() const
{
    return m_legend.get();
}

void CategorizedRenderer::accept(IFeatureRendererVisitor &visitor)
{
    visitor.visit(*this);
}

IFeatureRenderer *CategorizedRenderer::clone() const
{
    return new CategorizedRenderer(*this);
}

void CategorizedRenderer::setCategoryFieldIndex(const int index)
{
    m_categoryFieldIndex = index;
}

int CategorizedRenderer::categoryFieldIndex() const
{
    return m_categoryFieldIndex;
}

void CategorizedRenderer::addCategory(const QVariant &value, const QString &label, ISymbol *symbol)
{
    const auto it = m_categories.find(value);
    if (it == std::end(m_categories))
    {
        Log.w(QString("Value \"%1\" is already existed. Symbol won't be changed").arg(value.toString()));
        return;
    }

    ILegendClass* legendClass = new LegendClass(symbol, label);
    m_categories.insert(std::make_pair(value, ISymbolUPtr(legendClass->symbol()->clone())));
    m_legend->addClass(legendClass);
}

ISymbol *CategorizedRenderer::symbol(const QVariant &value)
{
    return const_cast<ISymbol *>(const_cast<const CategorizedRenderer*>(this)->symbol(value));
}

const ISymbol *CategorizedRenderer::symbol(const QVariant &value) const
{
    const auto it = m_categories.find(value);
    if (it == std::end(m_categories))
    {
        return nullptr;
    }

    const ISymbolUPtr& symbol = it->second;
    return symbol.get();
}
