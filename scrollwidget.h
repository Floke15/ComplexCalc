#ifndef SCROLLWIDGET_H
#define SCROLLWIDGET_H

#include <QWidget>

class ComplexVar;

class ScrollWidget : public QWidget
{
  Q_OBJECT

public:
  ScrollWidget(QWidget* parent = 0);

  void deleteVariable(ComplexVar* variable);
  ComplexVar* getVariable(QString name);

  std::vector<ComplexVar*> variables_;

private:
    std::vector<ComplexVar*> variables_to_delete_;

private slots:
  void update();

signals:
  void about_to_delete();
  void variable_deleted();
};


#endif // SCROLLWIDGET_H