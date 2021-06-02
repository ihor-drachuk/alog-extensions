#include <alog-extensions/types-support.h>

#ifdef ALOG_HAS_QT_LIBRARY
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>
#include <QJsonDocument>

ALog::Record&& operator<< (ALog::Record&& record, const QJsonObject& value)
{
    ALog::Internal::logJsonData(record, "Object", QString::fromUtf8(QJsonDocument(value).toJson()));
    return std::move(record);
}

ALog::Record&& operator<< (ALog::Record&& record, const QJsonArray& value)
{
    ALog::Internal::logJsonData(record, "Array", QString::fromUtf8(QJsonDocument(value).toJson()));
    return std::move(record);
}

ALog::Record&& operator<< (ALog::Record&& record, const QJsonValue& value)
{
    if (value.isObject()) {
        std::move(record) << value.toObject();

    } else if (value.isArray()) {
        std::move(record) << value.toArray();

    } else {
        QJsonObject obj;
        obj[""] = value;
        ALog::Internal::logJsonData(record, "Value", QString::fromUtf8(QJsonDocument(obj).toJson()));

    }

    return std::move(record);
}

ALog::Record&& operator<< (ALog::Record&& record, const QJsonDocument& value)
{
    ALog::Internal::logJsonData(record, "JsonDocument", QString::fromUtf8(value.toJson()));
    return std::move(record);
}

namespace ALog {
namespace Internal {

void logJsonData(ALog::Record& record, const QString& jsonType, const QString& jsonContent)
{
    auto _flagsRestorer = record.backupFlags();

    auto jsonTypeU8 = jsonType.toUtf8();
    auto jsonContentU8 = jsonContent.toUtf8();

    assert(*jsonTypeU8.rbegin() != 0);

    record.appendMessage("{Json; ");
    record << ALog::Record::Flags::Internal_NoSeparators;
    record.appendMessage(jsonTypeU8.constData(), jsonTypeU8.size());
    record.appendMessage("; Content = \"");
    record.appendMessage(jsonContentU8.constData(), jsonContentU8.size());
    record.appendMessage("\"}");
}

} // namespace Internal
} // namespace ALog

#endif // ALOG_HAS_QT_LIBRARY
