# Qt入门

概要:

+ 第一个Qt程序
+ 信号和槽
+ 布局



## 1.1	Hello Qt

```c++
#include <QApplication>
#include <QLabel>
#include <QPushButton>

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);				//用来管理整个应用程序所用到的资源
  QLabel* label = new QLabel("hello Qt");
  label->show();
  return a.exec();							//将控制权传给Qt。程序进入事件循环状态
}

```

## 1.2	建立连接

```c++
#include <QApplication>
#include <QPushButton>

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  QPushButton *button = new QPushButton("Quit");
  QObject::connect(button, SIGNAL(clicked()), &a, SLOT(quit()));
  button->show();
  return a.exec();
}

```

## 1.3	窗口部件的布局

```c++
#include <QApplication>
#include <QHBoxLayout>
#include <QSlider>
#include <QSpinBox>

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  QWidget *window = new QWidget;					//程序主窗口
  window->setWindowTitle("Enter Your Age");			//设置窗口标题栏文字

  QSpinBox* spinBox = new QSpinBox();				//创建微调框
  QSlider* slider = new QSlider(Qt::Horizontal);
  spinBox->setRange(0, 100);
  spinBox->setRange(0, 100);

  /*使用connnec确保滑块和slider同步，SIGNAL（valueChanged（int））用于在值改变时发射信号，SLOT用于（setValue(int))）接受信号并改变成对应的值。值得注意的是，在信号槽改变值后又会发射一个信号，不过此时这个信号槽的接收者不会再发射信号，因为值已经想通了，如果继续发射就会造成无限循环。*/
  QObject::connect(spinBox, SIGNAL(valueChanged(int)),slider, SLOT(setValue(int)));
  QObject::connect(slider, SIGNAL(valueChanged(int)), spinBox, SLOT(setValue(int)));
  spinBox->setValue(35);

  QHBoxLayout* layout = new QHBoxLayout;
  layout->addWidget(spinBox);
  layout->addWidget(slider);
    
   /*在本步骤过后，QSpinBox和QSlider会自动“重定义父对象”，他们会成为这个安装了布局窗口部件的子对象。所以在之前的语句当中，我们就没有为两个类的实例指定父对象。*/
  window->setLayout(layout);
  window->show();
  return a.exec();
}

```

### 布局

布局管理器就是一个能够对其所负责窗口部件的尺寸大小和位置进行设置的对象。

Qt有三个主要的布局管理器类：

- QHBoxLayout。在水平方向上排列窗口部件，从左到右。
- QVBoxLayout。在竖直方向上排列窗口部件，从上到下。
- QGridLayouy。把各个窗口部件排列在一个网格中。