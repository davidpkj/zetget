#ifndef util_hpp
#define util_hpp

#include <stdio.h>
#include <iostream>

#include <opencv2/opencv.hpp>

/*
    Sorts the given points of a rectangle counterclockwise.
    @param points The list of points to sort
    @return A sorted list
*/
std::vector<cv::Point> sortRectangleVerticesCounterclockwise(std::vector<cv::Point> points);

/*
    Calculates the target size for the image extract.
    @param contour The contour which is used to calculate
    @return The target size
*/
cv::Size getTargetSize(std::vector<cv::Point2f> contour);

/*
    Calculates the euclidean distance between two points.
    @param p1 Calculates distance to here
    @param p2 Calculates distance from here
    @return Distance between the two points
*/
double getEuclideanDistance(cv::Point p1, cv::Point p2);

/*
    Shows an image. If any contours (see getDocumentContour) are passed, they are drawn onto the image.
    This function is mostly used for debug purposes, and I like it the way it is.
    @param image The image to show
    @param contours The contours to draw
*/
void showImage(cv::Mat image, std::vector<std::vector<cv::Point>> contours = {});

#endif