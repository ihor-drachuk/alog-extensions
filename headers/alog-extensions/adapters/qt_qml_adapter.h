#pragma once

#ifdef ALOG_HAS_QT_LIBRARY
#include <QtGlobal>
#include <alog/tools.h>

namespace ALog {
namespace Ext {

class QtQmlAdapter : ALog::Internal::Singleton<QtQmlAdapter>
{
    friend void messageOutput(QtMsgType type, const QMessageLogContext& context, const QString& msg);
public:
    QtQmlAdapter(bool forwardToNative = false);
    QtQmlAdapter(const QtQmlAdapter&) = delete;
    ~QtQmlAdapter();

private:
    ALOG_DECLARE_PIMPL
};

} // namespace Ext
} // namespace ALog

#endif // ALOG_HAS_QT_LIBRARY
