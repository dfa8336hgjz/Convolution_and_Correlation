#include "process.h"

std::pair<std::vector<double>,std::vector<double>> makeLinearEquation(double up, double down, std::string parametersString) {
    double step = 0.001;
    std::vector<double> x;
    std::vector<double> y;
    std::vector<double> parameters;
    std::istringstream iss(parametersString);
    double num;
    while (iss >> num) {
            parameters.push_back(num);

        }
    if (step != 0.0) {
        for (double i = down; i <= up; i += step) {
            double xValue = i;
            x.push_back(xValue);
            double yValue = 0;

            for (int j = 0; j < parameters.size(); j++) {
                yValue += parameters[j] * pow(i, j);
            }

            y.push_back(yValue);
        }
    }
        return std::make_pair(x,y);
}
std::pair<std::vector<double>, std::vector<double>> makeSinusoidalEquation(double up, double down, std::string parametersString) {
    double step = 0.001;
    std::vector<double> x;
    std::vector<double> y;
    std::vector<double> parameters;
    std::istringstream iss(parametersString);
    double num;
    while (iss >> num) {
        parameters.push_back(num);
        if (parameters.size() > 3) break;
    }
    if (step != 0.0) {
        for (double t = down; t <= up; t += step) {
            double xValue = t;
            x.push_back(xValue);
            double yValue = parameters[0] * sin(parameters[1] * t + parameters[2]) + parameters[3];
            y.push_back(yValue);
        }
    }
    return std::make_pair(x, y);
}

std::pair<std::vector<double>, std::vector<double>> makeExponentialEquation(double up, double down, std::string parametersString) {
    double step = 0.001;
    std::vector<double> x;
    std::vector<double> y;
    std::vector<double> parameters;
    std::istringstream iss(parametersString);
    double num;
    while (iss >> num) {
        parameters.push_back(num);
        if (parameters.size() > 3) break;

    }
    if (step != 0.0) {
        for (double t = down; t <= up; t += step) {
            double xValue = t;
            x.push_back(xValue);
            double yValue = parameters[0] * exp(parameters[1] * t + parameters[2]) + parameters[3];
            y.push_back(yValue);
        }
    }
    return std::make_pair(x, y);
}

Equation::Equation(std::vector<double> x, std::vector<double> y) : x(x),y(y){
    down = x[0];
    up = x[x.size()-1];
}
Equation::Equation(double up, double down, std::string parametersString)
    : up(up), down(down), parametersString(parametersString) {
        x.push_back(0.0);
        y.push_back(0.0);
    }

cv::Mat Equation::Plot(int width, int height, cv::Scalar color) {
    cv::Mat plotImg(height, width, CV_8UC3, cv::Scalar(255, 255, 255));

    cv::Point xStart(0, height / 2);
    cv::Point xEnd(width, height / 2);
    cv::line(plotImg, xStart, xEnd, cv::Scalar(0, 0, 0), 1);

    cv::Point yStart(width / 2, 0);
    cv::Point yEnd(width / 2, height);
    cv::line(plotImg, yStart, yEnd, cv::Scalar(0, 0, 0), 1);

    double xScale = width / 20.0;
    double yScale = height / 20.0;

    cv::Point origin(width / 2, height / 2);
    cv::Point prevPoint(origin.x - (x[0] * xScale), origin.y - (y[0] * yScale));
    double maxY = 0;
    for (int i = 0; i < y.size(); i++) {
        if (std::abs(y[i]) > maxY) {
            maxY = std::abs(y[i]);
        }
    }
    double yMaxValue = origin.y - (maxY * yScale);
    if (yMaxValue >= 40) yScale = yScale * 40 / yMaxValue;
    for (int i = 0; i < x.size(); i++) {
        double xValue = origin.x + (x[i] * xScale);
        double yValue = origin.y - (y[i] * yScale);

        cv::Point currentPoint(xValue, yValue);

        if (i > 0)
            cv::line(plotImg, prevPoint, currentPoint, color, 2);

        prevPoint = currentPoint;
    }

    return plotImg;
}

int Equation::getSize() { return x.size(); }
double Equation::getDown() { return down; }
double Equation::getUp() { return up; }
std::vector<double> Equation::getX() { return x; }
std::vector<double> Equation::getY() { return y; }

void Equation::translate(double xV, double yV) {
    for (int i = 0; i < x.size(); i++) {
        x[i] += xV;
        y[i] += yV;

    }
    up += xV;
    down += xV;
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

Equation *calConvolutional(Equation* signal, Equation* impulseResponse) {
    int signalSize = signal->getSize();
    int impulseResponseSize = impulseResponse->getSize();
    int convolutionalSize = signalSize + impulseResponseSize - 1;

    std::vector<double> signalPower = signal->getY();
    std::vector<double> impulsePower = impulseResponse->getY();
    std::vector<double> x(convolutionalSize);
    std::vector<double> y(convolutionalSize);

    // Tính giá trị của vector x
    double x0 = signal->getDown() + impulseResponse->getDown();
    for (int i = 0; i < convolutionalSize; i++) {
        x[i] = x0 + i * 0.001;
    }

    // Tính giá trị của vector y
    double max = 0;
    for (int i = 0; i < convolutionalSize; i++) {
        y[i] = 0;
        for (int j = 0; j <= i; j++) {
            int k = i - j;
            if (k < signalSize && j < impulseResponseSize) {
                y[i] += signalPower[k] * impulsePower[j];
            }
        }
        if (y[i] >= max) max = y[i];
    }
    double scale = 1;
    if (max >= 40) scale = 40 / max;
    for (int i = 0; i < convolutionalSize; i++) {
        y[i] *= scale;
    }

    return new Equation(x, y);
}
Equation *calCorrelation(Equation* signal, Equation* impulseResponse) {
    int signalSize = signal->getSize();
    int impulseResponseSize = impulseResponse->getSize();
    int correlationSize = signalSize + impulseResponseSize - 1;

    std::vector<double> signalPower = signal->getY();
    std::vector<double> impulsePower = impulseResponse->getY();
    std::vector<double> x(correlationSize);
    std::vector<double> y(correlationSize);

    // Tính giá trị của vector x
    double x0 = signal->getDown() + impulseResponse->getDown();
    for (int i = 0; i < correlationSize; i++) {
        x[i] = x0 + i * 0.001;
    }
    for (int i = 0; i <= 1.0 * impulseResponseSize / 2; i++)
    {
        std::swap(impulsePower[i], impulsePower[impulseResponseSize - 1 - i]);
    }
    double max = 0;
    // Tính giá trị của vector y
    for (int i = 0; i < correlationSize; i++) {
        y[i] = 0;
        for (int j = 0; j < impulseResponseSize; j++) {
            int k = i - j;
            if (k >= 0 && k < signalSize) {
                y[i] += signalPower[k] * impulsePower[j];
            }
        }
        if (y[i] > max) max = y[i];
    }
    double scale = 1;
    if (max >= 40) scale = 40 / max;
    for (int i = 0; i < correlationSize; i++) {
        y[i] *= scale;
    }


    return new Equation(x, y);
}

void LinearEquation::makeStringEquation(){
    std::istringstream iss(parametersString);
    std::string param;
    int power = 0;
    equation = "";

    while (iss >> param) {
        double value = std::stod(param);
        equation += std::to_string(value);
        if (power > 0) {
            equation += "x^" + std::to_string(power);
        }
        if (iss.peek() != std::char_traits<char>::eof()) {
            equation += " + ";
        }
        power++;
    }
}

void SinusoidalEquation::makeStringEquation(){
    std::istringstream iss(parametersString);
    std::string param;
    double A, B, C, D;

    if (iss >> A >> B >> C >> D) {
        equation = std::to_string(A) + "sin(" + std::to_string(B) + "x+" + std::to_string(C) + ")+" + std::to_string(D);
    }

}

void ExponentialEquation::makeStringEquation(){
    std::istringstream iss(parametersString);
    std::string param;
    double A, B, C, D;

    if (iss >> A >> B >> C >> D) {
        equation = std::to_string(A) + "exp(" + std::to_string(B) + "x+" + std::to_string(C) + ")+" + std::to_string(D);
    }


}
