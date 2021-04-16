#pragma once
#include <alog/sink.h>

namespace ALog {

#ifdef ALOG_WINDOWS

#ifdef ALOG_HAS_QT_LIBRARY
class ConsoleQt2 : public ISinkWithFmtCnv
{
public:
    ConsoleQt2();
    ~ConsoleQt2();

protected:
    void writeBuffer(const Buffer& buffer) override;
};
#endif // ALOG_HAS_QT_LIBRARY

#else

using ConsoleQt2 = SinkStdStream;

#endif // ALOG_WINDOWS

} // namespace ALog
