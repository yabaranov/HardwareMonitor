#include "LanguageChooser.h"

#include <QCoreApplication>

LanguageChooser& LanguageChooser::instance(QQmlApplicationEngine* engine)
{
    static LanguageChooser languageChooser(engine);
    return languageChooser;
}

LanguageChooser::LanguageChooser(QQmlApplicationEngine* engine) : m_engine(engine)
{
}

bool LanguageChooser::setLanguage(const QString& languageCode)
{
    if(m_isTranslatorInstalled)
        qApp->removeTranslator(&m_translator);

    return loadTranslation(languageCode);
}

bool LanguageChooser::loadTranslation(const QString& languageCode)
{
    const bool loaded = m_translator.load("Translations/translate_" + languageCode);
    if (loaded)
    {
        qApp->installTranslator(&m_translator);
        m_isTranslatorInstalled = true;
        m_engine->retranslate();
    }

    return loaded;
}
