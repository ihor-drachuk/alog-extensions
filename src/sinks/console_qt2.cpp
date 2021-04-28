#include <alog-extensions/sinks/console_qt2.h>

#ifdef ALOG_WINDOWS
#ifdef ALOG_HAS_QT_LIBRARY

#include <QDebug>

namespace ALog {

void ConsoleQt2::writeBuffer(const Buffer& buffer)
{
    QDebug (QMessageLogger::*logFunc)() const = nullptr;
    auto record = getCurrentRecord();

    switch (record->severity) {
        case ALog::Severity::Verbose: logFunc = &QMessageLogger::debug; break;
        case ALog::Severity::Debug: logFunc = &QMessageLogger::debug; break;
        case ALog::Severity::Info: logFunc = &QMessageLogger::info; break;
        case ALog::Severity::Warning: logFunc = &QMessageLogger::warning; break;
        case ALog::Severity::Error: logFunc = &QMessageLogger::critical; break;
        case ALog::Severity::Fatal: logFunc = &QMessageLogger::critical; break;
    }

    assert(logFunc);

    QMessageLogger qtLogger(record->filenameFull, record->line, record->func, nullptr);
    (qtLogger.*logFunc)().noquote() << QString::fromUtf8((const char*)buffer.data(), buffer.size());
}

} // namespace ALog

#endif // ALOG_HAS_QT_LIBRARY
#endif // ALOG_WINDOWS
