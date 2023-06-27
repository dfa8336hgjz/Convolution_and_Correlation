#pragma once
#ifndef PROCESS_H
#define PROCESS_H
#include <bits/stdc++.h>
#include <opencv2/opencv.hpp>


class Equation {
protected:
    std::vector<double> x;
    std::vector<double> y;
    double up;
    double down;
    std::string parametersString;
public:
    std::string equation;
    Equation(std::vector<double> x, std::vector<double> y);
    Equation(double up, double down, std::string parametersString);

    cv::Mat Plot(int width, int height, cv::Scalar color);
    int getSize();
    double getDown();
    double getUp();
    std::vector<double> getX();
    std::vector<double> getY();

    void translate(double xV, double yV);
    virtual void makeStringEquation(){};

};
class LinearEquation : public Equation{
public:
    LinearEquation(double up, double down, std::string parametersString);
    void makeStringEquation();
};
class SinusoidalEquation : public Equation{
public:
    SinusoidalEquation(double up, double down, std::string parametersString);
    void makeStringEquation();
};
class ExponentialEquation : public Equation{
public:
    ExponentialEquation(double up, double down, std::string parametersString);
    void makeStringEquation();
};


Equation *calCorrelation(Equation* signal, Equation* impulseResponse);
Equation *calConvolutional(Equation* signal, Equation* impulseResponse);



#endif // PROCESS_H
