#include <alog-extensions/sinks/console_qt2.h>

#ifdef ALOG_WINDOWS
#ifdef ALOG_HAS_QT_LIBRARY

#include <QDebug>

namespace ALog {

ConsoleQt2::ConsoleQt2()
{
}

ConsoleQt2::~ConsoleQt2()
{
}

void ConsoleQt2::writeBuffer(const Buffer& buffer)
{
    QDebug (QMessageLogger::*logFunc)() const = nullptr;
    auto record = getCurrentRecord();

    switch (record->severity) {
        case ALog::Severity::Verbose: logFunc = &QMessageLogger::debug;
        case ALog::Severity::Debug: logFunc = &QMessageLogger::debug;
        case ALog::Severity::Info: logFunc = &QMessageLogger::info;
        case ALog::Severity::Warning: logFunc = &QMessageLogger::warning;
        case ALog::Severity::Error: logFunc = &QMessageLogger::critical;
        case ALog::Severity::Fatal: logFunc = &QMessageLogger::critical;
    }

    assert(logFunc);

    QMessageLogger qtLogger(record->file, record->line, record->func, nullptr);
    (qtLogger.*logFunc)() << (const char*)buffer.data();
}

} // namespace ALog

#endif // ALOG_HAS_QT_LIBRARY
#endif // ALOG_WINDOWS
