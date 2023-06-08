#pragma once

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

#include "logger.hpp"

/**
 * Formatte le texte pour que le seul texte retourné soit celui de la plaque et rien d'autre
 * @param _plaque texte qui vient en input
 * @return le texte formatté
 */
std::string getProperName(std::string _plaque)
{
    char *plaque_chr = new char[_plaque.length() + 1];

    const int length = _plaque.length();
    strcpy(plaque_chr, _plaque.c_str());

    for (int i = 0; i < length; i++)
    {
        // enforce le format AA-123-BB
        // @TODO : via regex, écrire un système pour autoriser les plaques suivant l'ancien format
        if (i < 2 || i > 6)
        {
            if (plaque_chr[i] == '0')
            {
                plaque_chr[i] = 'Q';
            }
            if (plaque_chr[i] == '6')
            {
                plaque_chr[i] = 'G';
            }
        }

        if (i > 8)
        {
            plaque_chr[i] = ' ';
        }
    }
    std::string properPlate = plaque_chr;
    return properPlate;
}

/**
 * Detecte l'endroit où une plaque d'immatriculation peut exister
 * @param filename nom du fichier de l'image avec extention (path relatif)
 * @return le texte sur la plaque après passage dans <code>getProperName()</code>
 * @note ce code est une traduction du script python trouvé ici : https://shorturl.at/afjJO (gamingdeputy.com)
 */
std::string getPlaque(std::string filename)
{
    // lit l'image
    cv::Mat original_image = cv::imread(filename);

    // copie de l'image en noir, blanc, gris
    cv::Mat gray_image;
    cvtColor(original_image, gray_image, cv::COLOR_BGR2GRAY);

    // lit les contours de l'image
    cv::Mat edged_image;
    Canny(gray_image, edged_image, 30, 200);

    std::vector<std::vector<cv::Point>> contours;
    std::vector<cv::Vec4i> hierarchy;

    // trouve les contours dans l'image, met les points dans contours, et l'ordre dans hierarchy
    findContours(edged_image.clone(), contours, hierarchy, cv::RETR_LIST, cv::CHAIN_APPROX_SIMPLE);
    cv::Mat img1 = original_image.clone();

    cv::imwrite("edge" + filename + ".png", edged_image);

    // dessine les contours sur une copie de l'image originale
    drawContours(img1, contours, -1, cv::Scalar(0, 255, 0), 3);

    // trie les contours et garde seulement 30 éléments
    sort(contours.begin(), contours.end(), [](std::vector<cv::Point> a, std::vector<cv::Point> b)
         { return contourArea(a) > cv::contourArea(b); });
    contours.resize(30);

    std::vector<cv::Point> screenCnt;
    cv::Mat img2 = original_image.clone();

    drawContours(img2, contours, -1, cv::Scalar(0, 255, 0), 3);

    // écrit l'image sur le disque
    cv::imwrite("contours" + filename + ".png", img2);

    int count = 0;
    int idx = 7;
    int i = 0;

    // loop dans les points
    // met les 4 points les plus susceptibles de ressembler a un rectangle a part
    // puis crop l'image pour garder seulement notre supposée plaque
    for (std::vector<cv::Point> c : contours)
    {
        double contour_perimeter = arcLength(c, true);
        std::vector<cv::Point> approx;
        approxPolyDP(c, approx, 0.018 * contour_perimeter, true);

        if (approx.size() == 4)
        {
            screenCnt = approx;
            cv::Rect rect = boundingRect(c);
            cv::Mat new_img = original_image(rect);
            cv::imwrite(filename + ".png", new_img);
            idx++;
            break;
        }
    }

    // fixe un crash super stupide
    // si screenCnt (vecteur de points) est vide, essayer de dessiner des contours en prenant screenCnt comme référence cause un crash.
    // retourner un string vide si screenCnt l'est semble être une solution qui marche.
    if (screenCnt.empty())
    {
        return "";
    }
    else
    {
        drawContours(original_image, std::vector<std::vector<cv::Point>>{screenCnt}, -1, cv::Scalar(0, 255, 0), 3);
    }

    // partie Tesseract
    std::string cropped_License_Plate = filename + ".png";
    tesseract::TessBaseAPI tess;
    tess.Init(NULL, "fra", tesseract::OEM_LSTM_ONLY);
    tess.SetPageSegMode(tesseract::PSM_SINGLE_BLOCK);

    tess.SetImage(cv::imread(cropped_License_Plate).data, cv::imread(cropped_License_Plate).cols, cv::imread(cropped_License_Plate).rows, 3, cv::imread(cropped_License_Plate).step);
    std::string text = tess.GetUTF8Text();
#if DEBUG_MODE
    Log("texte detecté sur l'image : " + text);
#endif
    return getProperName(text);
}