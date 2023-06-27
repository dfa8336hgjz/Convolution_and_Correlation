#pragma once
#ifndef FUNC_H
#define FUNC_H
#include <opencv2/opencv.hpp>
#include <bits/stdc++.h>

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

class Equation {
protected:
    std::vector<double> x;
    std::vector<double> y;
    int type;
    double up;
    double down;
    std::string parametersString;
public:
    Equation(std::vector<double> x, std::vector<double> y);
    Equation(double up, double down, std::string parametersString);
    void Plot(cv::Mat& plotImg, int width, int height);
    int getSize();
    double getDown();
    double getUp();
    std::vector<double> getX();
    std::vector<double> getY();
    void translate(double xV, double yV);
    void reverse();

};

class LinearEquation : public Equation{
public:
    LinearEquation(double up, double down, std::string parametersString);
};

class SinusoidalEquation : public Equation{
public:
    SinusoidalEquation(double up, double down, std::string parametersString);
};

class ExponentialEquation : public Equation{
public:
    ExponentialEquation(double up, double down, std::string parametersString);
};

#endif // FUNC_H
