#include "texteditmanager.h"

TextEditManager::TextEditManager(QWidget *parent) : QTextEdit(parent) {
    setTextEditProperties();
}

TextEditManager::~TextEditManager() {

}

void TextEditManager::setTextEditProperties() {
    setContextMenuPolicy(Qt::DefaultContextMenu);
    setUndoRedoEnabled(true);
    setAcceptRichText(true);
    setReadOnly(false);
}
