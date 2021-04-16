#include <alog/sink.h>
#include <alog/record.h>

namespace ALog {

namespace Ext {

#ifdef ALOG_HAS_P7_LIBRARY

class SinkBaical : public ISink
{
public:
    SinkBaical();
    ~SinkBaical() override;

    void write(const Record& record) override;

private:
    ALOG_DECLARE_PIMPL
};

#endif // ALOG_HAS_P7_LIBRARY

} // namespace Ext

} // namespace ALog
