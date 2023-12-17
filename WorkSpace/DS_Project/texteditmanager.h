#ifndef TEXTEDITMANAGER_H
#define TEXTEDITMANAGER_H

#include <QTextEdit>

class TextEditManager : public QTextEdit {
    Q_OBJECT

public:
    explicit TextEditManager(QWidget *parent = nullptr);
    ~TextEditManager();

    void setTextEditProperties();
};

#endif // TEXTEDITMANAGER_H
