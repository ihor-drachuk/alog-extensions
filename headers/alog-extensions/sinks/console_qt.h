#pragma once
#include <alog/sink.h>

class QTextStream;

namespace ALog {

#ifdef ALOG_WINDOWS

#ifdef ALOG_HAS_QT_LIBRARY
class ConsoleQt : public ISinkWithFmtCnv
{
public:
    enum class Stream {
        StdOut,
        StdErr
    };

    ConsoleQt(Stream stream);
    ~ConsoleQt();

protected:
    void writeBuffer(const Buffer& buffer) override;

private:
    ALOG_DECLARE_PIMPL
};
#endif // ALOG_HAS_QT_LIBRARY

#else

using ConsoleQt = SinkStdStream;

#endif // ALOG_WINDOWS

} // namespace ALog
