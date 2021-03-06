#pragma once
#include <alog/sink.h>
#include <alog/sinks/console.h>

class QTextStream;

namespace ALog {
namespace Ext {

#ifdef ALOG_WINDOWS

#ifdef ALOG_HAS_QT_LIBRARY
class ConsoleQt : public ISink
{
public:
    enum class Stream {StdOut, StdErr};

    ConsoleQt(Stream stream);
    ~ConsoleQt();

    void write(const Buffer& buffer, const Record&) override;

private:
    ALOG_DECLARE_PIMPL
};
#endif // ALOG_HAS_QT_LIBRARY

#else // ALOG_WINDOWS

using ConsoleQt = ::ALog::Sinks::Console;

#endif // ALOG_WINDOWS

} // namespace Ext
} // namespace ALog
