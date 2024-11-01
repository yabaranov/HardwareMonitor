#pragma once

#include <memory>
#include <string_view>
#include <QObject>
#include <QVariantList>

#include <spdlog/spdlog.h>

class Logger : public QObject
{
    Q_OBJECT
public:
    static Logger& instance(std::string_view loggerName = "Logger", std::string_view loggerPath = "logs/commonLogs.txt");

    template <typename... Args>
    void critical(fmt::format_string<Args...> fmt, Args &&...args);
    template <typename... Args>
    void error(fmt::format_string<Args...> fmt, Args &&...args);
    template <typename... Args>
    void warn(fmt::format_string<Args...> fmt, Args &&...args);
    template <typename... Args>
    void info(fmt::format_string<Args...> fmt, Args &&...args);
    template <typename... Args>
    void debug(fmt::format_string<Args...> fmt, Args &&...args);
    template <typename... Args>
    void trace(fmt::format_string<Args...> fmt, Args &&...args);
    void init(std::string_view loggerName, std::string_view loggerPath);

    Q_INVOKABLE void critical(const QString& message, const QVariantList& args = {});
    Q_INVOKABLE void error(const QString& message, const QVariantList& args = {});
    Q_INVOKABLE void warn(const QString& message, const QVariantList& args = {});
    Q_INVOKABLE void info(const QString& message, const QVariantList& args = {});
    Q_INVOKABLE void debug(const QString& message, const QVariantList& args = {});
    Q_INVOKABLE void trace(const QString& message, const QVariantList& args = {});

private:
    Logger(std::string_view loggerName, std::string_view loggerPath);
    Logger(Logger &other) = delete;
    Logger& operator=(const Logger &) = delete;
    std::string createStdFormattedMessage(const QString& message, const QVariantList& args);

    std::shared_ptr<spdlog::logger> m_spdLogger;
};

template <typename... Args>
void Logger::critical(fmt::format_string<Args...> fmt, Args &&...args)
{
    m_spdLogger->critical(fmt, std::forward<Args>(args)...);
}

template <typename... Args>
void Logger::error(fmt::format_string<Args...> fmt, Args &&...args)
{
    m_spdLogger->error(fmt, std::forward<Args>(args)...);
}

template <typename... Args>
void Logger::warn(fmt::format_string<Args...> fmt, Args &&...args)
{
    m_spdLogger->warn(fmt, std::forward<Args>(args)...);
}

template <typename... Args>
void Logger::info(fmt::format_string<Args...> fmt, Args &&...args)
{
    m_spdLogger->info(fmt, std::forward<Args>(args)...);
}

template <typename... Args>
void Logger::debug(fmt::format_string<Args...> fmt, Args &&...args)
{
    m_spdLogger->debug(fmt, std::forward<Args>(args)...);
}

template <typename... Args>
void Logger::trace(fmt::format_string<Args...> fmt, Args &&...args)
{
    m_spdLogger->trace(fmt, std::forward<Args>(args)...);
}
