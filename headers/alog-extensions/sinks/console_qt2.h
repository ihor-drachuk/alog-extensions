#pragma once
#include <alog/sink.h>

namespace ALog {
namespace Ext {

#ifdef ALOG_WINDOWS

#ifdef ALOG_HAS_QT_LIBRARY
class ConsoleQt2 : public ISinkWithFmtCnv
{
public:
    ConsoleQt2() = default;
    ~ConsoleQt2() = default;

protected:
    void writeBuffer(const Buffer& buffer) override;
};
#endif // ALOG_HAS_QT_LIBRARY

#else

using ConsoleQt2 = SinkStdStream;

#endif // ALOG_WINDOWS

} // namespace Ext
} // namespace ALog
