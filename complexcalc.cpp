#include "complexcalc.h"
#include "openglwindow.h"
#include "complexvar.h"
#include "scrollwidget.h"

#include <Qt3DExtras>
#include <QVBoxLayout>
#include <QSlider>
#include <QPushButton>
#include <QLineEdit>
#include <QScrollArea>

ComplexCalc::ComplexCalc(QWidget* parent) :
  QMainWindow(parent)
{

  // initialize Application window
  if (this->objectName().isEmpty())
    this->setObjectName("ComplexCalcClass");
  this->resize(1000, 750);
  QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
  sizePolicy.setHorizontalStretch(0);
  sizePolicy.setVerticalStretch(0);
  this->setSizePolicy(sizePolicy);

  // initialize centralWidget
  centralWidget_ = new QWidget(this);
  centralWidget_->setObjectName("centralWidget");
  
  // define verticalLayout as Layout of centralWidget
  verticalLayout_ = new QVBoxLayout(centralWidget_);
  verticalLayout_->setContentsMargins(10, 10, 10, 10);
  verticalLayout_->setSpacing(5);
  verticalLayout_->setObjectName("verticalLayout");

  //initialize timeSlider as part of centralWidget
  timeSlider_ = new QSlider(centralWidget_);
  timeSlider_->setObjectName("timeSlider");
  timeSlider_->setOrientation(Qt::Horizontal);
  timeSlider_->setMinimum(0);
  timeSlider_->setMaximum(1000);
  
  // initialize subWidget as part of centralWidget
  subWidget_ = new QWidget(centralWidget_);
  subWidget_->setObjectName("subWidget");

  verticalLayout_->addWidget(subWidget_);
  verticalLayout_->addWidget(timeSlider_);

  // define gridLayout as Layout of subWidget
  gridLayout_ = new QGridLayout(subWidget_);
  gridLayout_->setContentsMargins(10, 10, 10, 10);
  gridLayout_->setSpacing(5);
  gridLayout_->setObjectName("gridLayout");

  // initialize addVarButton as part of subWidget
  addVarButton_ = new QPushButton(subWidget_);
  addVarButton_->setObjectName("addVarButton");
  addVarButton_->setText(QCoreApplication::translate("ComplexCalc", "new Variable", nullptr));
  addVarButton_->setMinimumSize(220, 0);
  QSizePolicy sizePolicy1(QSizePolicy::MinimumExpanding, QSizePolicy::Fixed);
  sizePolicy1.setHorizontalStretch(1);
  sizePolicy1.setVerticalStretch(0);
  sizePolicy1.setHeightForWidth(addVarButton_->sizePolicy().hasHeightForWidth());
  addVarButton_->setSizePolicy(sizePolicy1);

  // initialize openGL3DWindow
  openGL3DWindow_ = new OpenGLWindow(true);

  // initialize the operationInput as part of subWidget
  operationInput_ = new QLineEdit(subWidget_);
  operationInput_->setObjectName("operationInput");
  QSizePolicy sizePolicy2(QSizePolicy::MinimumExpanding, QSizePolicy::Fixed);
  operationInput_->setFixedHeight(24);
  sizePolicy2.setHorizontalStretch(3);
  sizePolicy2.setVerticalStretch(0);
  sizePolicy2.setHeightForWidth(operationInput_->sizePolicy().hasHeightForWidth());
  operationInput_->setSizePolicy(sizePolicy2);
  operationInput_->setMaximumSize(QSize(16777215, 20));  // 16777215 is Max
  operationInput_->setPlaceholderText("Mathematical Operation");
  QRegularExpressionValidator* regex_validator = new QRegularExpressionValidator(QRegularExpression("[a-zA-Z0-9 +]*"));   //match one word (aka one potential variable)
  operationInput_->setValidator(regex_validator);
  
  scrollWidget_ = new ScrollWidget(subWidget_);
  scrollWidget_->setObjectName("scrollWidget");
  QSizePolicy sizePolicy3(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
  sizePolicy3.setHorizontalStretch(0);
  sizePolicy3.setVerticalStretch(0);
  sizePolicy3.setHeightForWidth(scrollWidget_->sizePolicy().hasHeightForWidth());
  connect(scrollWidget_, &ScrollWidget::about_to_delete, openGL3DWindow_, &OpenGLWindow::removeAllVariables);
  connect(scrollWidget_, &ScrollWidget::variable_deleted, this, &ComplexCalc::reparseText);

  // define verticalScrollLayout as Layout of scrollWidget
  verticalScrollLayout_ = new QVBoxLayout(scrollWidget_);
  verticalScrollLayout_->setContentsMargins(0, 0, 0, 0);
  verticalScrollLayout_->setSpacing(0);
  verticalScrollLayout_->setObjectName("verticalScrollLayout");
  verticalScrollLayout_->setAlignment(Qt::AlignTop);

  // initialize the scrollArea as part of subWidget
  scrollArea_ = new QScrollArea(subWidget_);
  scrollArea_->setObjectName("scrollArea");
  scrollArea_->setMinimumSize(220, 0);
  QSizePolicy sizePolicy4(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
  sizePolicy4.setHorizontalStretch(1);
  sizePolicy4.setVerticalStretch(0);
  sizePolicy4.setHeightForWidth(scrollArea_->sizePolicy().hasHeightForWidth());
  scrollArea_->setSizePolicy(sizePolicy4);
  scrollArea_->setWidgetResizable(true);
  scrollArea_->setWidget(scrollWidget_);

  // add elements to gridLayout in subWidget
  gridLayout_->addWidget(operationInput_, 0, 0, 1, 1);
  gridLayout_->addWidget(addVarButton_, 0, 1, 1, 1);
  gridLayout_->addWidget(QWidget::createWindowContainer(openGL3DWindow_), 1, 0, 1, 1);
  gridLayout_->addWidget(scrollArea_, 1, 1, 1, 1);

  connect(timeSlider_, &QSlider::valueChanged, openGL3DWindow_, &OpenGLWindow::setTime);
  this->setCentralWidget(centralWidget_);

  QMetaObject::connectSlotsByName(this);

  OpenGLWindow* openGL3DWindow = new OpenGLWindow(false);
  QWidget* fixWidget = QWidget::createWindowContainer(openGL3DWindow);
  QSizePolicy sizePolicy5(QSizePolicy::Fixed, QSizePolicy::Fixed);
  fixWidget->setMinimumSize(1, 1);
  //fixWidget->setVisible(false);
  fixWidget->setSizePolicy(sizePolicy5);
  verticalScrollLayout_->addWidget(fixWidget);
}

void ComplexCalc::on_operationInput_textEdited(const QString& text)
{
  operationInput_->setText(operationInput_->text().toUpper());

  openGL3DWindow_->removeAllVariables();

  compute(operationInput_->text().toStdString());
  //TODO: implement parsing and calculation of calculations

  /*QVector<ComplexVar*> variables;
  QString input = operationInput_->text();

  for (auto var_iter : scrollWidget_->variables_)
  {
    if (var_iter->getName() == "")
      continue;

    QString regex_str = "(^" + var_iter->getName() + "$)|(^" + var_iter->getName() + " .*$)|(^.* " + var_iter->getName() + " .*$)|(^.* " + var_iter->getName() + "$)";
    QRegularExpressionValidator* regex_validator = new QRegularExpressionValidator(QRegularExpression(regex_str));
    int pos = 0;

    if (int t = regex_validator->validate(input, pos) == 2)
     variables.push_back(var_iter);

    delete regex_validator;
  }

  openGL3DWindow_->removeAllVariables();

  for (auto var_iter : variables)
    openGL3DWindow_->insertVariable(var_iter, true);*/
}

void ComplexCalc::compute(const std::string& expr) {
  const auto tokens = exprToTokens(expr);
  auto queue = shuntingYard(tokens);
  std::vector<ComplexVar*> stack;

  //printf("\nCalculation\n");
  //printf(reportFmt, "Token", "Queue", "Stack", "");

  while (!queue.empty()) {
    std::string op;

    const auto token = queue.front();
    queue.pop_front();
    switch (token.type) {
    /*case Token::Type::Number:
      stack.push_back(std::stoi(token.str));
      op = "Push " + token.str;
      break;*/

    case Token::Type::Variable:
      stack.push_back(findFirstVariableInString(QString::fromStdString(token.str)));
      openGL3DWindow_->insertVariable(stack.back(), true);
      break;

    case Token::Type::Operator:
    {
      if (token.unary) {
        assert(0 && "");
        /*
        // unray operators
        const auto rhs = stack.back();
        stack.pop_back();
        switch (token.str[0]) {
        default:
          //printf("Operator error [%s]\n", token.str.c_str());
          assert(0 && "");
          break;
        case 'm':                   // Special operator name for unary '-'
          stack.push_back(-rhs);
          break;
        }
        op = "Push (unary) " + token.str + " " + std::to_string(rhs);*/
      }
      else if (stack.size() < 2)
        break;
      else {
        // binary operators
        const auto rhs = stack.back();
        stack.pop_back();
        const auto lhs = stack.back();
        stack.pop_back();

        switch (token.str[0]) {
        default:
          printf("Operator error [%s]\n", token.str.c_str());
          assert(0 && "");
          break;
        /*case '^':
          stack.push_back(static_cast<int>(pow(lhs, rhs)));
          break;
        case '*':
          stack.push_back(lhs * rhs);
          break;
        case '/':
          stack.push_back(lhs / rhs);
          break;*/
        case '+':
          on_addVarButton_clicked();
          ComplexVar* new_variable = scrollWidget_->variables_.back();
          new_variable->setName(lhs->getName() + "+" + rhs->getName());
          new_variable->setValue(lhs->getValue() + rhs->getValue());

          stack.push_back(new_variable);
          openGL3DWindow_->insertVariable(new_variable, true);
          break;
        /*case '-':
          stack.push_back(lhs - rhs);
          break;*/
        }
        //op = "Push " + std::to_string(lhs) + " " + token.str + " " + std::to_string(rhs);
      }
    }
    break;

    default:
      assert(0 && "");
    }
    //debugReport(token, queue, stack, op);
  }

  //return stack.back();
}

std::deque<Token> ComplexCalc::exprToTokens(const std::string& expr) {
  std::deque<Token> tokens;

  for (const auto* p = expr.c_str(); *p; ++p) {
    if (isblank(*p)) {
      // do nothing
    }
    else if (ComplexVar* variable = findFirstVariableInString(p)) {
      const auto* b = p;
      p += variable->getName().size() - 1;
      const auto s = std::string(b, p + 1);

      tokens.push_back(Token{ Token::Type::Variable, s });
    }
    /*else if (isdigit(*p)) {
      const auto* b = p;
      while (isdigit(*p)) {
        ++p;
      }
      const auto s = std::string(b, p);
      tokens.push_back(Token{ Token::Type::Number, s });
      --p;
    }*/
    else {
      Token::Type t = Token::Type::Unknown;
      int precedence = -1;
      bool rightAssociative = false;
      bool unary = false;
      char c = *p;
      switch (c) {
      default:                                    break;
      case '(':   t = Token::Type::LeftParen;     break;
      case ')':   t = Token::Type::RightParen;    break;
      //case '^':   t = Token::Type::Operator;      precedence = 4; rightAssociative = true;  break;
      //case '*':   t = Token::Type::Operator;      precedence = 3; break;
      //case '/':   t = Token::Type::Operator;      precedence = 3; break;
      case '+':   t = Token::Type::Operator;      precedence = 2; break;
      /*case '-':
        // If current token is '-'
        // and if it is the first token, or preceded by another operator, or left-paren,
        if (tokens.empty()
          || tokens.back().type == Token::Type::Operator
          || tokens.back().type == Token::Type::LeftParen
          ) {
          // it's unary '-'
          // note#1 : 'm' is a special operator name for unary '-'
          // note#2 : It has highest precedence than any of the infix operators
          unary = true;
          c = 'm';
          t = Token::Type::Operator;
          precedence = 5;
        }
        else {
          // otherwise, it's binary '-'
          t = Token::Type::Operator;
          precedence = 2;
        }
        break;*/
      }
      const auto s = std::string(1, c);
      tokens.push_back(Token{ t, s, precedence, rightAssociative, unary });
    }
  }

  return tokens;
}

ComplexVar* ComplexCalc::findFirstVariableInString(QString text)
{
  for (auto var_iter : scrollWidget_->variables_)
  {
    if (var_iter->getName() == "")
      continue;

    QString regex_str = "^(" + var_iter->getName() + ")";
    QRegularExpression regex(regex_str);
    QRegularExpressionMatch match = regex.match(text);

    if (match.hasMatch())
    {
      return var_iter;
    }
  }
  return nullptr;
}

std::deque<Token> ComplexCalc::shuntingYard(const std::deque<Token>& tokens) {
  std::deque<Token> queue;
  std::vector<Token> stack;

  // While there are tokens to be read:
  for (auto token : tokens) {
    // Read a token
    switch (token.type) {
    case Token::Type::Variable:
      queue.push_back(token);
      break;

    /*case Token::Type::Number:
      // If the token is a number, then add it to the output queue
      queue.push_back(token);
      break;*/

    case Token::Type::Operator:
    {
      // If the token is operator, o1, then:
      const auto o1 = token;

      // while there is an operator token,
      while (!stack.empty()) {
        // o2, at the top of stack, and
        const auto o2 = stack.back();

        // either o1 is left-associative and its precedence is
        // *less than or equal* to that of o2,
        // or o1 if right associative, and has precedence
        // *less than* that of o2,
        if (
          (!o1.rightAssociative && o1.precedence <= o2.precedence)
          || (o1.rightAssociative && o1.precedence < o2.precedence)
          ) {
          // then pop o2 off the stack,
          stack.pop_back();
          // onto the output queue;
          queue.push_back(o2);

          continue;
        }

        // @@ otherwise, exit.
        break;
      }

      // push o1 onto the stack.
      stack.push_back(o1);
    }
    break;

    case Token::Type::LeftParen:
      // If token is left parenthesis, then push it onto the stack
      stack.push_back(token);
      break;

    case Token::Type::RightParen:
      // If token is right parenthesis:
    {
      bool match = false;

      // Until the token at the top of the stack
      // is a left parenthesis,
      while (!stack.empty() && stack.back().type != Token::Type::LeftParen) {
        // pop operators off the stack
        // onto the output queue.
        queue.push_back(stack.back());
        stack.pop_back();
        match = true;
      }

      if (!match && stack.empty()) {
        // If the stack runs out without finding a left parenthesis,
        // then there are mismatched parentheses.
        printf("RightParen error (%s)\n", token.str.c_str());
        return {};
      }

      // Pop the left parenthesis from the stack,
      // but not onto the output queue.
      stack.pop_back();
    }
    break;

    default:
      assert(0 && "");
      //printf("error (%s)\n", token.str.c_str());
      return {};
    }

    //debugReport(token, queue, stack);
  }

  // When there are no more tokens to read:
  //   While there are still operator tokens in the stack:
  while (!stack.empty()) {
    // If the operator token on the top of the stack is a parenthesis,
    // then there are mismatched parentheses.
    if (stack.back().type == Token::Type::LeftParen) {
      printf("Mismatched parentheses error\n");
      return {};
    }

    // Pop the operator onto the output queue.
    queue.push_back(std::move(stack.back()));
    stack.pop_back();
  }

  //debugReport(Token{ Token::Type::Unknown, "End" }, queue, stack);

  //Exit.
  return queue;
}

void ComplexCalc::reparseText()
{
  on_operationInput_textEdited(operationInput_->text());
}

void ComplexCalc::clearMainWindow()
{
  openGL3DWindow_->removeAllVariables();
}

void ComplexCalc::on_addVarButton_clicked()
{
  ComplexVar* newVar = new ComplexVar(scrollWidget_, timeSlider_);
  scrollWidget_->layout()->addWidget(newVar);
  scrollWidget_->variables_.push_back(newVar);

  connect(newVar, &ComplexVar::variable_name_changed, this, &ComplexCalc::reparseText);
}
