#include <alog-extensions/adapters/qt_qml_adapter.h>

#ifdef ALOG_HAS_QT_LIBRARY

#define ALOGGER_PREFIX thisPtr->impl().
#include <mutex>
#include <QString>
#include <alog/logger.h>

namespace ALog {
namespace Ext {

using Handler = decltype(qInstallMessageHandler(nullptr));

static void messageOutput(QtMsgType type, const QMessageLogContext& context, const QString& msg);

struct QtQmlAdapter::impl_t
{
    DEFINE_ALOGGER_MODULE(QtQmlAdapter);

    std::mutex mx;
    bool forwardToNative;
    Handler oldHandler;

    std::unique_ptr<std::lock_guard<std::mutex>> lock() { return std::make_unique<std::lock_guard<std::mutex>>(mx); }
};

QtQmlAdapter::QtQmlAdapter(bool forwardToNative)
{
    createImpl();
    impl().forwardToNative = forwardToNative;
    impl().oldHandler = qInstallMessageHandler(messageOutput);
}

QtQmlAdapter::~QtQmlAdapter()
{
    qInstallMessageHandler(impl().oldHandler);
}

static void messageOutput(QtMsgType type, const QMessageLogContext& context, const QString& msg)
{
    Severity severity;

    switch (type) {
        case QtDebugMsg: severity = Severity::Debug; break;
        case QtInfoMsg: severity = Severity::Info; break;
        case QtWarningMsg: severity = Severity::Warning; break;
        case QtCriticalMsg: severity = Severity::Error; break;
        case QtFatalMsg: severity = Severity::Fatal; break;
        default:
            assert(!"Unexpected type in `messageOutput`!");
    }

    auto thisPtr = QtQmlAdapter::instance();
    //auto _lck = thisPtr->impl().lock();

    auto record = Record::create(severity, context.line, context.file, ALog::Internal::extractFileNameOnly(context.file), context.function);
    record.module = context.category;

    record.flagsOn(Record::Flags::Flush);

    auto msgUtf8 = msg.toUtf8();
    record.message.appendString(msgUtf8.constData(), msgUtf8.size());

    auto logger = ALog::LoggerHolder<0>::instance()->get();
    static bool hasDebt = false;

    if (logger) {
        if (hasDebt) {
            hasDebt = false;
            ACCESS_ALOGGER_MODULE.flush();
        }

        logger->addRecord(std::move(record));
    } else {
        hasDebt = true;
        LOGE << "Can't send log message!";
    }

    if (thisPtr->impl().forwardToNative && thisPtr->impl().oldHandler) {
        thisPtr->impl().oldHandler(type, context, msg);
    }
}

} // namespace Ext
} // namespace ALog

#endif // ALOG_HAS_QT_LIBRARY
