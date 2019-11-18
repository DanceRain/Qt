#ifndef TEXTQUERYFRAME_H
#define TEXTQUERYFRAME_H

#include <QDialog>
#include "ui_textqueryframe.h"
#include "textquery.h"

namespace Ui {
  class TextQueryFrame;
}

class TextQueryFrame : public QDialog, public Ui::TextQueryFrame
{
  Q_OBJECT
private slots:
  void query();
public:
  TextQueryFrame(QWidget *parent = nullptr);
};

#endif // TEXTQUERYFRAME_H
