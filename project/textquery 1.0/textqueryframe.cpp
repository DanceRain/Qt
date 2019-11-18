#include "textqueryframe.h"
#include "ui_textqueryframe.h"
#include <QtWidgets>
#include <QPlainTextEdit>

TextQueryFrame::TextQueryFrame(QWidget *parent) : QDialog(parent)
{
  setupUi(this);
  resultArea->hide();
  connect(queryButton, SIGNAL(clicked()), this, SLOT(query()));
  layout()->setSizeConstraint(QLayout::SetFixedSize);
}

void TextQueryFrame::query()
{
  resultArea->clear();

  string cstr = addressLineEdit->text().toStdString();
  std::ifstream file(cstr);
  TextQuery _query(file);
  QueryResult result = _query.query(wordLineEdit->text().toStdString());
  resultArea->appendPlainText(wordLineEdit->text() + " occur " + QString::number(result.getSet().size()) + " times");
  for(auto &lineNo : result.getSet())
    {
      QString data = QString::fromUtf8(result.getLine(lineNo).c_str());
      resultArea->appendPlainText("line " + QString::number(lineNo) + " " + data);
   }
}
