#include "func.h"

Equation::Equation(std::vector<double> x, std::vector<double> y) : x(x),y(y){
    down = x[0];
    up = x[x.size()-1];
}

Equation::Equation(double up, double down, std::string parametersString)
    : up(up), down(down), parametersString(parametersString) {
        x.push_back(0.0);
        y.push_back(0.0);
    }
void Equation::Plot(cv::Mat& plotImg, int width, int height) {
    cv::Point xStart(0, height / 2);
    cv::Point xEnd(width, height / 2);
    cv::line(plotImg, xStart, xEnd, cv::Scalar(0, 0, 0), 1);

    cv::Point yStart(width / 2, 0);
    cv::Point yEnd(width / 2, height);
    cv::line(plotImg, yStart, yEnd, cv::Scalar(0, 0, 0), 1);

    double xScale = width / 40.0;
    double yScale = height / 40.0;

    cv::Point origin(width / 2, height / 2);
    cv::Point prevPoint(origin.x - (x[0] * xScale), origin.y - (y[0] * yScale));

    for (int i = 0; i < x.size(); i++) {
        double xValue = origin.x + (x[i] * xScale);
        double yValue = origin.y - (y[i] * yScale);

        cv::Point currentPoint(xValue, yValue);

        if (i > 0)
            cv::line(plotImg, prevPoint, currentPoint, cv::Scalar(0, 0, 0), 2);

        prevPoint = currentPoint;
    }
}

int Equation::getSize() {return x.size();}
double Equation::getDown() {return down;}
double Equation::getUp() {return up;}
std::vector<double> Equation::getX() {return x;}
std::vector<double> Equation::getY() {return y;}

void Equation::translate(double xV, double yV) {
    for (int i = 0; i < x.size(); i++) {
        x[i] += xV*20;
        y[i] -= yV*20;

    }
    up += xV*20;
    down += xV*20;
}

void Equation::reverse(){
    for (int i =0; i< x.size(); i++){
        x[i] *= -1.0;
    }
    up *=-1.0;
    down *= -1.0;
    std::swap(up, down);
}

LinearEquation::LinearEquation(double up, double down, std::string parametersString)
    : Equation(up,down,parametersString)
{
  x = makeLinearEquation(up, down, parametersString).first;
  y = makeLinearEquation(up, down, parametersString).second;
}

SinusoidalEquation::SinusoidalEquation(double up, double down, std::string parametersString)
    : Equation(up,down,parametersString)
{
  x = makeSinusoidalEquation(up, down, parametersString).first;
  y = makeSinusoidalEquation(up, down, parametersString).second;
}

ExponentialEquation::ExponentialEquation(double up, double down, std::string parametersString)
    : Equation(up,down,parametersString)
{
  x = makeExponentialEquation(up, down, parametersString).first;
  y = makeExponentialEquation(up, down, parametersString).second;
}
