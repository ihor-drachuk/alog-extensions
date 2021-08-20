#include <alog/logger.h>
#include <alog-extensions/adapters/qt_qml_adapter.h>

int main()
{
    SIMPLE_SETUP_ALOG;
    LOGMD << "Test";
    return 0;
}
