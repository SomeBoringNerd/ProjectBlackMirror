#ifndef HEADER_IMG_UTIL
#define HEADER_IMG_UTIL

#include <stdio.h>
#include <string>
#include <iostream>
#include <stdlib.h>

#include <opencv4/opencv2/core.hpp>
#include <opencv4/opencv2/imgproc.hpp>
#include <opencv4/opencv2/imgcodecs.hpp>
#include <opencv4/opencv2/highgui.hpp>
#include <opencv4/opencv2/opencv.hpp>
#include <tesseract/baseapi.h>
#include <iostream>

using namespace cv;
using namespace std;

#include "logger.hpp"

/**
 * Formatte le texte pour que le seul texte retourné soit celui de la plaque et rien d'autre
 * @param _plaque texte qui vient en input
 * @return le texte formatté
*/
string getProperName(string _plaque)
{
    char* plaque_chr = new char[_plaque.length() + 1];

    const int length = _plaque.length();
    strcpy(plaque_chr, _plaque.c_str());

    for (int i = 0; i < length; i++)
    {
        // enforce le format AA-123-BB
        // @TODO : via regex, écrire un système pour autoriser les plaques suivant l'ancien format
        if(i < 2 || i > 6)
        {
            if(plaque_chr[i] == '0')
            {
                plaque_chr[i] = 'Q';
            }
        }

        if(i > 8)
        {
            plaque_chr[i] = ' ';
        }
    }
    string properPlate = plaque_chr;
    return properPlate;
}

/**
 * Detecte l'endroit où une plaque d'immatriculation peut exister
 * @param filename nom du fichier de l'image avec extention (path relatif)
 * @return le texte sur la plaque après passage dans <code>getProperName()</code>
*/
string getPlaque(string filename)
{
    Mat original_image = imread(filename);
    
    Mat gray_image;
    cvtColor(original_image, gray_image, COLOR_BGR2GRAY);

    // @TODO : trouver le problème qui fait que cette ligne fait crash le programme
    //bilateralFilter(gray_image, gray_image, 11, 17, 17, 4);

    Mat edged_image;
    Canny(gray_image, edged_image, 30, 200);

    vector<vector<Point>> contours;
    vector<Vec4i> hierarchy;
    findContours(edged_image.clone(), contours, hierarchy, RETR_LIST, CHAIN_APPROX_SIMPLE);
    Mat img1 = original_image.clone();

    drawContours(img1, contours, -1, Scalar(0, 255, 0), 3);


    sort(contours.begin(), contours.end(), [](vector<Point> a, vector<Point> b) {
        return contourArea(a) > contourArea(b);
    });
    contours.resize(30);

    vector<Point> screenCnt;
    Mat img2 = original_image.clone();

    drawContours(img2, contours, -1, Scalar(0, 255, 0), 3);

    int count = 0;
    int idx = 7;

    for (vector<Point> c : contours) {
        double contour_perimeter = arcLength(c, true);
        vector<Point> approx;
        approxPolyDP(c, approx, 0.018 * contour_perimeter, true);

        if (approx.size() == 4) {
            screenCnt = approx;
            Rect rect = boundingRect(c);
            Mat new_img = original_image(rect);

            imwrite(filename + ".png", new_img);
            idx++;
            break;
        }
    }
    
    // crash
    if(screenCnt.empty())
    {
        return "";
    }else{
        drawContours(original_image, vector<vector<Point>>{screenCnt}, -1, Scalar(0, 255, 0), 3);
    }
    
    
    string cropped_License_Plate = filename + ".png";
    tesseract::TessBaseAPI tess;
    tess.Init(NULL, "fra", tesseract::OEM_LSTM_ONLY);
    tess.SetPageSegMode(tesseract::PSM_SINGLE_BLOCK);
    tess.SetImage(imread(cropped_License_Plate).data, imread(cropped_License_Plate).cols, imread(cropped_License_Plate).rows, 3, imread(cropped_License_Plate).step);
    string text = tess.GetUTF8Text();

    return getProperName(text);
}

#endif