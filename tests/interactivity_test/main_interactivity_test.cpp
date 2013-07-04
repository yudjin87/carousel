#include "CarouselComponentConfigurationDelegateTest.h"
#include "OperationTest.h"
#include "OperationCatalogTest.h"
#include "DockWidgetCatalogTest.h"
#include "InputInterceptorTest.h"
#include "MenuCatalogTest.h"
#include "ToolBarCatalogTest.h"
#include "CarouselInteractionServiceTest.h"
#include "ToolBaseTest.h"
#include "DialogServiceTest.h"
#include "fakes/MockApplication.h"

#include <carousel/logging/NullLogger.h>

#include <QtTest/QtTest>

//------------------------------------------------------------------------------
int main(int argc, char *argv[])
{
    MockApplication app(argc, argv);
    NullLogger log;
    LoggerFacade::installLoggerEngine(&log);

//    InputInterceptorTest inputInterceptorTest;
//    QTest::qExec(&inputInterceptorTest, argc, argv);

//    OperationTest operationTest;
//    QTest::qExec(&operationTest, argc, argv);

//    MenuCatalogTest menuCatalogTest;
//    QTest::qExec(&menuCatalogTest, argc, argv);

//    ToolBarCatalogTest toolBarCatalogTest;
//    QTest::qExec(&toolBarCatalogTest, argc, argv);

//    OperationCatalogTest operationCatalogTest;
//    QTest::qExec(&operationCatalogTest, argc, argv);

//    DockWidgetCatalogTest dockWidgetCatalogTest;
//    QTest::qExec(&dockWidgetCatalogTest, argc, argv);

//    CarouselComponentConfigurationDelegateTest carouselComponentConfigurationDelegateTest;
//    QTest::qExec(&carouselComponentConfigurationDelegateTest, argc, argv);

//    CarouselInteractionServiceTest carouselInteractionServiceTest;
//    QTest::qExec(&carouselInteractionServiceTest, argc, argv);

//    ToolBaseTest toolBaseTest;
//    QTest::qExec(&toolBaseTest, argc, argv);

    DialogServiceTest dialogServiceTest;
    QTest::qExec(&dialogServiceTest, argc, argv);

    return 0;
}

//------------------------------------------------------------------------------

