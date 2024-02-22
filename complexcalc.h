#ifndef COMPLEXCALC_H
#define COMPLEXCALC_H

#include <QMainWindow>
#include <QWidget>
#include <deque>

class OpenGLWindow;
class QVBoxLayout;
class QGridLayout;
class QPushButton;
class QLineEdit;
class QScrollArea;
class QSlider;
class ScrollWidget;
class ComplexVar;

class Token {
public:
  enum class Type {
    Unknown,
    Variable,
    Number,
    Operator,
    LeftParen,
    RightParen,
  };

  Token(Type type,
    const std::string& s,
    int precedence = -1,
    bool rightAssociative = false,
    bool unary = false
  )
    : type{ type }
    , str(s)
    , precedence{ precedence }
    , rightAssociative{ rightAssociative }
    , unary{ unary }
  {}

  const Type type;
  const std::string str;
  const int precedence;
  const bool rightAssociative;
  const bool unary;
};

class ComplexCalc : public QMainWindow
{
  Q_OBJECT

public:
  ComplexCalc(QWidget* parent = nullptr);
  //~ComplexCalc();

private slots:
  void on_addVarButton_clicked();
  void on_operationInput_textEdited(const QString& text);
  void reparseText();
  void clearMainWindow();

private:
  void compute(const std::string& expr);
  std::deque<Token> exprToTokens(const std::string& expr);
  ComplexVar* findFirstVariableInString(QString text);
  std::deque<Token> shuntingYard(const std::deque<Token>& tokens);

  // Design elements
  QWidget* centralWidget_;
  QVBoxLayout* verticalLayout_;
  QWidget* subWidget_;
  QGridLayout* gridLayout_;
  QPushButton* addVarButton_;
  OpenGLWindow* openGL3DWindow_;
  QLineEdit* operationInput_;
  ScrollWidget* scrollWidget_;
  QVBoxLayout* verticalScrollLayout_;
  QScrollArea* scrollArea_;
  QSlider* timeSlider_;
};
#endif // COMPLEXCALC_H
