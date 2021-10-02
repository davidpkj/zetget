#ifndef manipulation_hpp
#define manipulation_hpp

#include <stdio.h>
#include <iostream>

#include <opencv2/opencv.hpp>

#include "util.hpp"

/*
    Resizes an image to double its size.
    @param image The image to resize
    @return The resized image
*/
cv::Mat resize(cv::Mat image);

/*
    Sorts and adjusts a contour to better represent whatever it marks.
    @param contour The contour to be corrected
    @return A corrected contour
*/
std::vector<cv::Point2f> correctContour(std::vector<cv::Point> contour);

/*
    Preprocesses an image to be used for various detection.
    @param image The image to preprocess
    @return The preprocessed image
*/
std::vector<cv::Mat> getPreprocessedImages(cv::Mat image);

/*
    Uses a threshhold image (see preprocess) to find the contour of a document in the image.
    @param image The original image
    @param threshhold The preprocessed image
    @return A contour of possible document
*/
std::vector<cv::Point> getDocumentContour(cv::Mat image, cv::Mat threshhold);

/*
    Uses a contour (see getDocumentContour) to extract a flat, straight piece of the image, 
    which, if the contour was obtained correctly, should be a document.
    @param image The image for the contour to be extracted from
    @param contour The contour to be used to extract the document
    @return An image showing the extract
*/
cv::Mat getCorrectedDocument(cv::Mat image, std::vector<cv::Point> contour);

#endif