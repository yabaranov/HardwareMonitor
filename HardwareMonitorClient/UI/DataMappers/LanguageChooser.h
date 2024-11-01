#pragma once

#include <QTranslator>
#include <QObject>
#include <QQmlApplicationEngine>

class LanguageChooser : public QObject
{
    Q_OBJECT
public:
    explicit LanguageChooser(QQmlApplicationEngine& engine, QObject *parent = nullptr);

    Q_INVOKABLE bool setLanguage(const QString& languageCode);

private:
    bool loadTranslation(const QString& languageCode);

    QTranslator m_translator;
    bool m_isTranslatorInstalled = false;
    QQmlApplicationEngine& m_engine;
};
