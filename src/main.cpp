#include "main.hpp"

int main(int argc, char **argv)
{
    return scan(argc, argv);
}

int scan(int argc, char **argv) 
{
    Magick::InitializeMagick(*argv);

    if (argc != 3)
    {
        printf("[ Error ] Failed to get files.\nUsage: zetget [source image] [destination image]\n");
        return 1;
    }

    // Prepare the magic
    cv::Mat image;
    image = cv::imread(argv[1], 1);

    if (!image.data)
    {
        printf("[ Error ] Couldn't read image data.\n");
        return 1;
    }

    // Do the magic
    std::vector<cv::Mat> vector = getPreprocessedImages(image);
    std::vector<cv::Point> contour = getDocumentContour(vector[0], vector[1]);
    image = getCorrectedDocument(vector[0], contour);

    // Save the magic
    // cv::imwrite(argv[2], image);
    convertImageToPDF(image, argv[2]);

    return 0;
}