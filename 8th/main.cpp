#include <iostream>
#include <map>

// Base class for operators
class Operator {
public:
    virtual void printExpression() = 0;
    virtual int calculate(std::map<std::string, int>& context) = 0;
};

// class for sum operator
class Addition : public Operator {
private:
    Operator* left;
    Operator* right;
public:
    Addition(Operator* leftOperand, Operator* rightOperand) : left(leftOperand), right(rightOperand) {}

    void printExpression() {
        left->printExpression();
        std::cout << " + ";
        right->printExpression();
    }

    int calculate(std::map<std::string, int>& context) {
        return left->calculate(context) + right->calculate(context);
    }
};

// class for variable
class Variable : public Operator {
private:
    std::string name;
public:
    Variable(std::string varName) : name(varName) {}

    void printExpression() {
        std::cout << name;
    }

    int calculate(std::map<std::string, int>& context) {
        return context[name];
    }
};

// class for Constant
class Constant : public Operator {
private:
    int value;
public:
    Constant(int constValue) : value(constValue) {}

    void printExpression() {
        std::cout << value;
    }

    int calculate(std::map<std::string, int>& context) {
        return value;
    }
};

// class for variables and constant creation
class ExpressionFactory {
private:
    std::map<int, Constant*> constants;
    std::map<std::string, Variable*> variables;

    ExpressionFactory() {
        for (int i = -5; i <= 256; i++) {
            constants[i] = new Constant(i);
        }
    }
public:
    static ExpressionFactory& getInstance() {
        static ExpressionFactory instance;
        return instance;
    }

    Constant* createConstant(int value) {
        if (value >= -5 && value <= 256) {
            return constants[value];
        } else {
            return new Constant(value); // Создание новой константы, если значение не входит в диапазон
        }
    }
    Variable* createVariable(std::string name) {
        if (variables.find(name) != variables.end()) {
            return variables[name];
        } else {
            Variable* var = new Variable(name);
            variables[name] = var;
            return var;
        }
    }
    void deleteVariable(std::string name) {
        if (variables.find(name) != variables.end()) {
            delete variables[name];
            variables.erase(name);
        }
    }
};

int main() {
    ExpressionFactory factory = ExpressionFactory::getInstance();
    Constant* c = factory.createConstant(2);
    Variable* v = factory.createVariable("x");
    Addition* expression = new Addition(c, v);

    std::map<std::string, int> context;
    context["x"] = 7;

    expression->printExpression();
    std::cout << " = " << expression->calculate(context) << "\n\n\n";

    delete expression;
    factory.deleteVariable("x");

    return 0;
}
