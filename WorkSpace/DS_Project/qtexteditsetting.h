#ifndef QTEXTEDITSETTINGS_H
#define QTEXTEDITSETTINGS_H

#include <QFont>
#include <QTextEdit>

class QTextEditSettings {
public:
    QTextEditSettings();

    QFont font() const;
    void setFont(const QFont &font);
    QTextEdit *createTextEdit() const;


private:
    QFont m_font;

};

#endif // QTEXTEDITSETTINGS_H
