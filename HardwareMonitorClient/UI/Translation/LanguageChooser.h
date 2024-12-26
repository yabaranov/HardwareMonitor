#pragma once

#include <QTranslator>
#include <QObject>
#include <QQmlApplicationEngine>

class LanguageChooser : public QObject
{
    Q_OBJECT
public:

    static LanguageChooser& instance(QQmlApplicationEngine* engine = nullptr);

    Q_INVOKABLE bool setLanguage(const QString& languageCode);

private:

    explicit LanguageChooser(QQmlApplicationEngine* engine);
    ~LanguageChooser() override = default;

    bool loadTranslation(const QString& languageCode);

    QTranslator m_translator;
    bool m_isTranslatorInstalled = false;
    QQmlApplicationEngine* m_engine;
};
