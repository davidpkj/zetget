#include "util.hpp"

std::vector<cv::Point> sortRectangleVerticesCounterclockwise(std::vector<cv::Point> points)
{
    // Sort all elements by X coordinate, ascending
    std::sort(points.begin(), points.end(), [](cv::Point p1, cv::Point p2) { return (p1.x < p2.x); });
    // Sort first two elements by Y coordinate, ascending
    std::sort(points.begin(), points.begin() + 2, [](cv::Point p1, cv::Point p2) { return (p1.y < p2.y); });
    // Sort last two elements by Y coordinate, descending
    std::sort(points.begin() + 2, points.end(), [](cv::Point p1, cv::Point p2) { return (p1.y > p2.y); });

    return points;
}

// TODO: This only generates PDF in vertical format. For horizontals the longer side has to be devided.
cv::Size getTargetSize(std::vector<cv::Point2f> contour)
{
    // Get maximally possible height
    // double height = std::max({getEuclideanDistance(contour[0], contour[1]), getEuclideanDistance(contour[2], contour[3])});
    // Get maximally possible width
    double width = std::max({getEuclideanDistance(contour[1], contour[2]), getEuclideanDistance(contour[3], contour[4])});

    // Multiply maximal width with the standard DIN aspect ratio
    return cv::Size(width, width * 1.414);
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

void convertImageToPDF(cv::Mat source, char *destination) {
    cv::Size size = source.size();
    Magick::Image image(size.width, size.height, "RGB", Magick::CharPixel, source.data);

    Magick::Blob blob;
    image.write(&blob, std::string("pdf"));

    // std::cout.write(static_cast<const char*>(blob.data()), blob.length());
    std::FILE *outfile = std::fopen(destination, "w");

    fwrite(blob.data(), blob.length(), 1, outfile);
    fclose(outfile);
}