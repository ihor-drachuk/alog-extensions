#pragma once

#ifdef ALOG_HAS_QT_LIBRARY
#include <QtGlobal>
#include <alog/tools.h>

namespace ALog {
namespace Ext {

class QtQmlAdapter : public ALog::Internal::Singleton<QtQmlAdapter>
{
    friend class ConsoleQt2;
public:
    QtQmlAdapter(bool forwardToNative = false);
    QtQmlAdapter(const QtQmlAdapter&) = delete;
    ~QtQmlAdapter();

private:
    using Handler = decltype(qInstallMessageHandler(nullptr));

    Handler getBackHandler() const;
    static void messageOutput(QtMsgType type, const QMessageLogContext& context, const QString& msg);

private:
    ALOG_DECLARE_PIMPL
};

} // namespace Ext
} // namespace ALog

#endif // ALOG_HAS_QT_LIBRARY
