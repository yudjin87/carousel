#include "ComponentLoader.h"

#include "IComponent.h"
#include "ComponentExport.h"

#include <logging/LoggerFacade.h>

#include <QtCore/QFileInfo>
#include <QtCore/QLibrary>

//------------------------------------------------------------------------------
namespace
{
static LoggerFacade log = LoggerFacade::createLogger("ComponentLoader");
}

//------------------------------------------------------------------------------
const QString ComponentLoader::m_createFuncName = CREATE_FUNCTION_NAME;
const QString ComponentLoader::m_releaseFuncName = RELEASE_FUNCTION_NAME;

//------------------------------------------------------------------------------
ComponentLoader::ComponentLoader(QObject *parent)
    : QObject(parent)
    , m_instance(nullptr)
    , m_fileName("")
    , m_errorString("")
    , m_loaded(false)
    , m_loadHits(QLibrary::ResolveAllSymbolsHint | QLibrary::ExportExternalSymbolsHint)
    , m_createFunc(nullptr)
    , m_releaseFunc(nullptr)
    , m_library(nullptr)
{
}

//------------------------------------------------------------------------------
ComponentLoader::ComponentLoader(const QString &fileName, QObject *parent)
    : QObject(parent)
    , m_instance(nullptr)
    , m_fileName("")
    , m_errorString("")
    , m_loaded(false)
    , m_loadHits(QLibrary::ResolveAllSymbolsHint | QLibrary::ExportExternalSymbolsHint)
    , m_createFunc(nullptr)
    , m_releaseFunc(nullptr)
{
    setFileName(fileName);
}

//------------------------------------------------------------------------------
ComponentLoader::~ComponentLoader()
{
    unload();
}

//------------------------------------------------------------------------------
QString ComponentLoader::errorString() const
{
    return m_errorString;
}

//------------------------------------------------------------------------------
QString ComponentLoader::fileName() const
{
    return m_fileName;
}

//------------------------------------------------------------------------------
IComponent *ComponentLoader::instance()
{
    if (!m_loaded)
        load();

    return m_instance;
}

//------------------------------------------------------------------------------
bool ComponentLoader::isLoaded() const
{
    return m_loaded;
}

//------------------------------------------------------------------------------
bool ComponentLoader::load()
{
    if (m_loaded)
        return true;

    if (m_fileName.isEmpty()) {
        log.w("Cannot load component - file name is empty.");
        return false;
    }

    m_errorString = "";

    m_library = new QLibrary(m_fileName);
    m_library->setLoadHints(loadHints());
    if (!m_library->load()) {
        m_errorString = m_library->errorString();
        log.e(QString("Cannot load component. Error: %1").arg(m_errorString));
        return false;
    }

    void *createFunc = m_library->resolve(m_createFuncName.toLatin1().data());
    m_createFunc = reinterpret_cast<createComponentFunc>(createFunc);
    if (m_createFunc == nullptr) {
        m_errorString = QString("Cannot found create function \"%1\" at the \"%2\". See internal error: %3")
                .arg(m_createFuncName, m_library->fileName(), m_library->errorString());
        log.e(m_errorString);
        return false;
    }

    void *releaseFunc = m_library->resolve(m_releaseFuncName.toLatin1().data());
    m_releaseFunc = reinterpret_cast<releaseComponentFunc>(releaseFunc);
    if (m_releaseFunc == nullptr) {
        m_errorString = QString("Cannot found release function \"%1\" at the \"%2\". See internal error: %3")
                .arg(m_releaseFuncName, m_library->fileName(), m_library->errorString());
        log.e(m_errorString);
        return false;
    }

    QObject *obj = reinterpret_cast<QObject *>(m_createFunc());
    m_instance = dynamic_cast<IComponent *>(obj);

    m_loaded = true;

    log.d(QString("Component \"%1\" was successfully loaded.").arg(m_fileName));

    return true;
}

//------------------------------------------------------------------------------
QLibrary::LoadHints ComponentLoader::loadHints() const
{
    return m_loadHits;
}

//------------------------------------------------------------------------------
void ComponentLoader::setFileName(const QString &fileName)
{
    QFileInfo file(fileName);
    if (!file.exists()) {
        log.w(QString("Cannot use \"%1\" file name. It does not exist.").arg(fileName));
        return;
    }

    if (m_loaded)
        return;

    m_fileName = fileName;
}

//------------------------------------------------------------------------------
void ComponentLoader::setLoadHints(QLibrary::LoadHints loadHints)
{
    m_loadHits = loadHints;
}

//------------------------------------------------------------------------------
bool ComponentLoader::unload()
{
    if (!m_loaded)
        return true;

    if (!deleteInstance())
        return false;

    bool result = m_library->unload();
    delete m_library;
    m_library = nullptr;

    return result;
}

//------------------------------------------------------------------------------
bool ComponentLoader::deleteInstance()
{
    if (!m_loaded) {
        log.w("Cannot delete instance, because it was not load.");
        return false;
    }

    log.d("Delete loaded instance.");
    m_releaseFunc(m_instance);
    m_releaseFunc = nullptr;
    m_createFunc = nullptr;
    m_instance = nullptr;
    m_loaded = false;

    return true;
}

//------------------------------------------------------------------------------
