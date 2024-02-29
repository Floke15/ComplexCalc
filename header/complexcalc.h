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

// regarding the class Token:
// SOURCE: https://gist.github.com/t-mat/b9f681b7591cdae712f6
// Author: Takayuki Matsuoka
// Edited to fit this usecase
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

public slots:
  void on_addVarButton_clicked();
  void on_operationInput_textEdited(const QString& text);
  void reparseText();

private:
  void compute(const std::string& expr);
  std::deque<Token> exprToTokens(const std::string& expr);
  ComplexVar* findFirstVariableInString(const QString text);
  std::deque<Token> shuntingYard(const std::deque<Token>& tokens);

  // Design elements
  OpenGLWindow* openGL3DWindow_;
  QLineEdit* operationInput_;
  ScrollWidget* scrollWidget_;
  QSlider* timeSlider_;
};
#endif // COMPLEXCALC_H
