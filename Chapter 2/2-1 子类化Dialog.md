## 子类化QDialong

完全使用C++编写一个Find对话框。

```c++
/*finddialog.h*/
#ifndef FINDDIALOG_H
#define FINDDIALOG_H
#include <QDialog>

class QCheckBox;
class QLabel;
class QLineEdit;
class QPushButton;

class FindDialog : public QDialog
{
  Q_OBJECT
public:
  FindDialog(QWidget* parent = nullptr);
  
  /*声明信号，在findBUtton点击之后根据是否勾选了backwardCheckBox选项来进行不同的信号发射*/
signals:
  void findNext(const QString& str, Qt::CaseSensitivity cs);
  void findPrevious(const QString& str, Qt::CaseSensitivity cs);
  
  /*声明槽*/
private slots:
  void findClicked();
  void enableFindButton(const QString &text);
  
private:
  QLabel* label;					//QLabel部件,用于指示输入框
  QLineEdit* lineEdit;				//QLineEdit部件，文本输入框
  QCheckBox* caseCheckBox;			//QCheckBox部件，供用户选择查询方式
  QCheckBox* backwardCheckBox;		
  QPushButton* findButton;			//QPushButton部件，对用户进行查找和关闭的动作提供接口
  QPushButton* closeButton;
};

#endif // FINDDIALOG_H
```

```c++
/*finddialog.cpp*/
#include <QtWidgets>
#include "finddialog.h"

FindDialog::FindDialog(QWidget *parent):QDialog (parent)
{
    /*tr 用于国际化，如果程序安装了中文语言包，则会将Find What译为中文意思*/
    /*&用于指定快捷键*/
  label = new QLabel(tr("Find &what:"));
  lineEdit = new QLineEdit;
    /*将lineEdit设置为label的buddy，作用在label上的操作，例如上面设置的快捷键，就会将焦点放到lineEdit当中去*/
  label->setBuddy(lineEdit);
    

  caseCheckBox = new QCheckBox(tr("Match &case"));
  backwardCheckBox = new QCheckBox(tr("Search &backward"));

  findButton = new QPushButton(tr("&Find"));
  findButton->setDefault(true);		//设置默认按钮，当用户按下Enter时能够按下对应的按钮
   //禁用按钮，在后面的代码中通过发射信号，判断lineEdit的内容是否为空来解除禁用。
  findButton->setEnabled(false);	
    
  closeButton = new QPushButton(tr("close"));
    
   /*将信号发射和信号槽连接在一起*/
  connect(lineEdit, SIGNAL(textChanged(const QString&)), this, SLOT(enableFindButton(const QString&)));
  connect(findButton, SIGNAL(clicked()), this, SLOT(findClicked()));
  connect(closeButton, SIGNAL(clicked()), this, SLOT(close()));

    /*下面的内容都是设置布局*/
  QHBoxLayout* topLeftLayout = new QHBoxLayout();
  topLeftLayout->addWidget(label);
  topLeftLayout->addWidget(lineEdit);

  QVBoxLayout* leftLayout = new QVBoxLayout;
  leftLayout->addLayout(topLeftLayout);
  leftLayout->addWidget(caseCheckBox);
  leftLayout->addWidget(backwardCheckBox);

  QVBoxLayout* rightLayout = new QVBoxLayout;
  rightLayout->addWidget(findButton);
  rightLayout->addWidget(closeButton);

  QHBoxLayout* mainLayout = new QHBoxLayout;
  mainLayout->addLayout(leftLayout);
  mainLayout->addLayout(rightLayout);
  setLayout(mainLayout);
  setWindowTitle(tr("find"));
   /*设置大小为最佳状态*/
  setFixedHeight(sizeHint().height());
}

/*定义槽*/
void FindDialog::findClicked()
{
  QString text = lineEdit->text();
    
   /*CaseSensitivity是一个枚举类型，根据值表示是否对大小写敏感*/
  Qt::CaseSensitivity cs = caseCheckBox->isChecked() ? Qt::CaseSensitive : Qt::CaseInsensitive;

    /*根据用户的是否选择了backwardCheckBox来选择不同的查找方式*/
  if(backwardCheckBox->isChecked())
    {
      emit findPrevious(text, cs);
    }
  else
    {
      emit findNext(text, cs);
    }
}

void FindDialog::enableFindButton(const QString& text)
{
    /*接受信号，并根据text是否为空来确定是否解禁*/
  findButton->setEnabled(!text.isEmpty());
}

```

