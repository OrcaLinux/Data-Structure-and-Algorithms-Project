#include "qtexteditsetting.h"


QTextEditSettings::QTextEditSettings() {
    // Set default values here
    m_font.setPointSize(12);
    m_font.setFamily("Arial");
}

QFont QTextEditSettings::font() const {
    return m_font;
}

void QTextEditSettings::setFont(const QFont &font) {
    m_font = font;

}

QTextEdit *QTextEditSettings::createTextEdit() const {
    QTextEdit *textEdit = new QTextEdit;
    textEdit->setFont(m_font);
    // Set other properties as needed
    return textEdit;
}

