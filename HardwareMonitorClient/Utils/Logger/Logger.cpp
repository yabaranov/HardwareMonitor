#include "Logger.h"

#include <spdlog/async.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/rotating_file_sink.h>

Logger::Logger(std::string_view loggerName, std::string_view loggerPath)
{
    init(loggerName, loggerPath);
}

Logger& Logger::instance(std::string_view loggerName, std::string_view loggerPath)
{
    static Logger logger(loggerName, loggerPath);
    return logger;
}

void Logger::init(std::string_view loggerName, std::string_view loggerPath)
{
    auto console_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
    console_sink->set_level(spdlog::level::info);

    auto file_sink = std::make_shared<spdlog::sinks::rotating_file_sink_mt>(loggerPath.data(), 5 * 1024 * 1024, 3);
    file_sink->set_level(spdlog::level::trace);

    spdlog::init_thread_pool(8192, 1);

    m_spdLogger = std::make_shared<spdlog::async_logger>(loggerName.data(),
                                                      spdlog::sinks_init_list{ console_sink, file_sink },
                                                      spdlog::thread_pool(),
                                                      spdlog::async_overflow_policy::block);
    m_spdLogger->set_level(spdlog::level::trace);
}

std::string Logger::createStdFormattedMessage(const QString& message, const QVariantList& args)
{
    QString formattedMessage = message;

    for (const auto &arg : args)
        formattedMessage = formattedMessage.arg(arg.toString());

    return formattedMessage.toStdString();
}

void Logger::critical(const QString& message, const QVariantList& args)
{
    m_spdLogger->critical(createStdFormattedMessage(message, args));
}

void Logger::error(const QString& message, const QVariantList& args)
{
    m_spdLogger->error(createStdFormattedMessage(message, args));
}

void Logger::warn(const QString& message, const QVariantList& args)
{
    m_spdLogger->warn(createStdFormattedMessage(message, args));
}

void Logger::info(const QString& message, const QVariantList &args)
{
    m_spdLogger->info(createStdFormattedMessage(message, args));
}

void Logger::debug(const QString& message, const QVariantList& args)
{
    m_spdLogger->debug(createStdFormattedMessage(message, args));
}

void Logger::trace(const QString& message, const QVariantList& args)
{
    m_spdLogger->trace(createStdFormattedMessage(message, args));
}
