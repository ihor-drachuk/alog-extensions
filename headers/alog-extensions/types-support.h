#pragma once

#ifdef ALOG_HAS_QT_LIBRARY
#include <alog/record.h>
class QJsonObject;
class QJsonArray;
class QJsonValue;
class QJsonDocument;

ALog::Record&& operator<< (ALog::Record&& record, const QJsonObject& value);
ALog::Record&& operator<< (ALog::Record&& record, const QJsonArray& value);
ALog::Record&& operator<< (ALog::Record&& record, const QJsonValue& value);
ALog::Record&& operator<< (ALog::Record&& record, const QJsonDocument& value);

namespace ALog {
namespace Internal {
void logJsonData(Record& record, const QString& jsonType, const QString& jsonContent);
} // namespace Internal
} // namespace ALog

#endif // ALOG_HAS_QT_LIBRARY
