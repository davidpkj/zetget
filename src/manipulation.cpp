#include "manipulation.hpp"

cv::Mat resize(cv::Mat image)
{
    cv::Mat output;
    cv::resize(image, output, cv::Size(image.size().width, image.size().height));

    return output;
}

std::vector<cv::Point2f> correctContour(std::vector<cv::Point> contour)
{
    int offset = 5;
    std::vector<cv::Point2f> correction;
    contour = sortRectangleVerticesCounterclockwise(contour);

    for (cv::Point point : contour)
    {
        // Add offset to account for border width
        point.x = point.x + offset;
        point.y = point.y + offset;

        // This is just to make the list go from Point to Point2f, needed later
        correction.push_back(cv::Point2f(point.x, point.y));
    }

    return correction;
}

std::vector<cv::Mat> getPreprocessedImages(cv::Mat image)
{
    cv::Mat output;

    // Trial and error showed these are the best settings for this purpose
    cv::cvtColor(resize(image), output, cv::COLOR_RGB2GRAY);
    cv::bilateralFilter(output.clone(), output, 9, 75, 75);
    cv::adaptiveThreshold(output, output, 255, cv::ADAPTIVE_THRESH_GAUSSIAN_C, cv::THRESH_BINARY, 115, 4);
    cv::medianBlur(output, output, 11);
    cv::copyMakeBorder(output, output, 5, 5, 5, 5, cv::BORDER_CONSTANT, cv::Scalar(0));

    cv::Canny(output, output, 200, 250);

    return {image, output};
}

std::vector<cv::Point> getDocumentContour(cv::Mat image, cv::Mat threshhold)
{
    std::vector<std::vector<cv::Point>> contours;
    std::vector<cv::Vec4i> hierarchy;

    cv::findContours(threshhold.clone(), contours, hierarchy, cv::RETR_TREE, cv::CHAIN_APPROX_SIMPLE);

    // Some setup for whats coming next
    int height = image.size().height;
    int width = image.size().width;
    double maximalAllowedArea = (width - 10) * (height - 10);
    double minimalAllowedArea = maximalAllowedArea * 0.25;
    std::vector<cv::Point> pageContour = {cv::Point(5, 5), cv::Point(5, height - 5), cv::Point(width - 5, height - 5), cv::Point(width - 5, 5)};

    // Find the contour that might resemble a document
    for (std::vector<cv::Point> curve : contours)
    {
        std::vector<cv::Point> approximation;
        double perimeter = cv::arcLength(curve, true);
        cv::approxPolyDP(curve, approximation, 0.03 * perimeter, true);

        if (approximation.size() == 4 && cv::isContourConvex(approximation))
        {
            double area = cv::contourArea(approximation);

            if (minimalAllowedArea < area && area < maximalAllowedArea)
            {
                pageContour = approximation;
                maximalAllowedArea = area;
            }
        }
    }

    return pageContour;
}

cv::Mat getCorrectedDocument(cv::Mat image, std::vector<cv::Point> contour)
{
    std::vector<cv::Point2f> correction = correctContour(contour);

    // Some setup for perspective fix
    cv::Mat output;
    cv::Size targetSize = getTargetSize(correction);
    std::vector<cv::Point2f> target = {
        cv::Point2f(0, 0),
        cv::Point2f(0, targetSize.height),
        cv::Point2f(targetSize.width, targetSize.height),
        cv::Point2f(targetSize.width, 0),
    };

    // Perspective fix
    cv::Mat transform = cv::getPerspectiveTransform(correction, target);
    cv::warpPerspective(image, output, transform, cv::Size(int(targetSize.width), int(targetSize.height)));

    return output;
}
