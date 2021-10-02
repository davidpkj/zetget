#include "util.hpp"

std::vector<cv::Point> sortRectangleVerticesCounterclockwise(std::vector<cv::Point> points)
{
    // Sort all elements by X coordinate, ascending
    std::sort(points.begin(), points.end(), [](cv::Point p1, cv::Point p2) { return (p1.x < p2.x); });
    // Sort first two elements by Y coordinate, descending
    std::sort(points.begin(), points.begin() + 1, [](cv::Point p1, cv::Point p2) { return (p1.y > p2.y); });
    // Sort last two elements by Y coordinate, descending
    std::sort(points.end() - 2, points.end(), [](cv::Point p1, cv::Point p2) { return (p1.y > p2.y); });

    return points;
}

cv::Size getTargetSize(std::vector<cv::Point2f> contour)
{
    // Get maximally possible height
    double height = std::max({getEuclideanDistance(contour[0], contour[1]), getEuclideanDistance(contour[2], contour[3])});
    // Get maximally possible width
    double width = std::max({getEuclideanDistance(contour[1], contour[2]), getEuclideanDistance(contour[3], contour[4])});

    return cv::Size(width, height);
}

double getEuclideanDistance(cv::Point p1, cv::Point p2)
{
    return std::sqrt(abs((p2.x - p1.x) * (p2.x - p1.x)) + abs((p2.y - p1.y) * (p2.y - p1.y)));
}

void showImage(cv::Mat image, std::vector<std::vector<cv::Point>> contours)
{
    cv::Mat imageClone = image.clone();

    if (!contours.empty())
    {
        cv::drawContours(imageClone, contours, -1, cv::Scalar(0, 255, 0, 255), 2);
    }

    cv::imshow("Display", imageClone);
    cv::waitKey(0);
    cv::waitKey(0);
}