#include <tesseract/baseapi.h>
#include <leptonica/allheaders.h>
#include <iostream>

#include <QString>

#include <opencv2/opencv.hpp>

QString qprocessMat(tesseract::TessBaseAPI *_ptess, const cv::Mat &img);

QString getUTF8Text(const cv::Mat &img, const char *langcode="rus", tesseract::PageSegMode psm=tesseract::PageSegMode::PSM_AUTO_OSD);

int main(int argc, char *argv[]){

    setlocale(LC_CTYPE, ""); // for the Cirillyc symbols output

   /*----------------------------------------Tesseract image format
    tesseract::TessBaseAPI api;
    api.Init("", "rus", tesseract::OEM_DEFAULT);
    api.SetPageSegMode(tesseract::PageSegMode::PSM_AUTO_OSD);

    std::cout << "File name: " ;
    char image[] = "C:/OCR/passrus1.jpg";
    PIX   *pixs = pixRead(image);
    std::cout << image << std::endl;

    STRING text_out;
    api.SetImage(pixs);
    QString qstr = QString(api.GetUTF8Text());

    std::wcout << QString("Текст:\n").toStdWString();
    std::wcout << qstr.toStdWString() << std::endl;
    ----------------------------------------------------------*/

    /*---------------------------------------Opencv image format
    tesseract::TessBaseAPI api;
    api.Init("", "rus", tesseract::OEM_DEFAULT);
    api.SetPageSegMode(tesseract::PageSegMode::PSM_AUTO_OSD);
    //api.SetOutputName("out");

    std::cout << "File name: " ;
    char image[] = "C:/OCR/passrus1.jpg";
    cv::Mat _mat = cv::imread(image);
    cv::cvtColor(_mat, _mat, CV_BGR2RGBA);
    std::cout << image << std::endl;

    api.SetImage(_mat.data, _mat.cols, _mat.rows, 4, 4*_mat.cols);
    QString qstr = QString(api.GetUTF8Text());

    std::wcout << QString("Текст:\n").toStdWString();
    std::wcout << qstr.toStdWString() << std::endl;
    ----------------------------------------------------------*/

    /*-----------------------------------------------------------------
    tesseract::TessBaseAPI api;
    api.Init("", "rus", tesseract::OEM_DEFAULT);
    api.SetPageSegMode(tesseract::PageSegMode::PSM_AUTO_OSD);

    std::cout << "File name: " ;
    char image[] = "C:/OCR/passrus1.jpg";
    cv::Mat _mat = cv::imread(image);

    std::wcout << QString("Текст:\n").toStdWString();
    std::wcout << qprocessMat(&api, _mat).toStdWString() << std::endl;
    api.End();
    ------------------------------------------------------------*/

    std::cout << "File name: ";
    char image[] = "C:/OCR/passrus1.jpg";
    cv::Mat _mat = cv::imread(image);
    std::cout << image << "\n--------------------------\n" ;
    std::wcout << QString("Текст:\n").toStdWString();
    std::wcout << getUTF8Text(_mat,"rus", tesseract::PageSegMode::PSM_AUTO).toStdWString() << std::endl;
    std::cout<< "\n--------------------------\n";

    return 0;
}

QString qprocessMat(tesseract::TessBaseAPI *_ptess, const cv::Mat &img)
{
    cv::Mat _mat;
    switch(img.channels()) {
        case 1:
            cv::cvtColor(img, _mat, CV_GRAY2RGBA);
            break;
        case 3:
            cv::cvtColor(img, _mat, CV_BGR2RGBA);
            break;
        case 4:
            cv::cvtColor(img, _mat, CV_BGRA2RGBA);
            break;
    }

    _ptess->SetImage(_mat.data, _mat.cols, _mat.rows, 4, 4*_mat.cols);
    return QString(_ptess->GetUTF8Text());
}

QString getUTF8Text(const cv::Mat &img, const char *langcode, tesseract::PageSegMode psm)
{
    tesseract::TessBaseAPI _tesseract;
    _tesseract.Init("", langcode, tesseract::OEM_DEFAULT);
    _tesseract.SetPageSegMode(psm);
    cv::Mat _mat;
    switch(img.channels()) {
        case 1:
            cv::cvtColor(img, _mat, CV_GRAY2RGBA);
            break;
        case 3:
            cv::cvtColor(img, _mat, CV_BGR2RGBA);
            break;
        case 4:
            cv::cvtColor(img, _mat, CV_BGRA2RGBA);
            break;
    }
    _tesseract.SetImage(_mat.data, _mat.cols, _mat.rows, 4, 4*_mat.cols);    
    QString qtstr(_tesseract.GetUTF8Text());

    tesseract::ResultIterator* ri = _tesseract.GetIterator();
    tesseract::PageIteratorLevel level = tesseract::RIL_WORD;
    if (ri != 0) {
        do {
            const char* word = ri->GetUTF8Text(level);
            float conf = ri->Confidence(level);
            printf("\nword: '%s';  \tconf: %.2f;",
                   QString(word).toLocal8Bit().constData(), conf);
            //delete[] word;
        } while (ri->Next(level));
    }

    return qtstr;
}
