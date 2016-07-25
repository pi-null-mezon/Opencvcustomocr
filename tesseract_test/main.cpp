#include <tesseract/baseapi.h>
#include <leptonica/allheaders.h>
#include <iostream>

#include <QString>

int main(int argc, char *argv[]){

    setlocale(LC_CTYPE, ""); // for the Cirillyc symbols output

    tesseract::TessBaseAPI api;
    api.Init("", "rus", tesseract::OEM_DEFAULT);
    api.SetPageSegMode(tesseract::PageSegMode::PSM_AUTO_OSD);
    //api.SetOutputName("out");

    std::cout << "File name: " ;
    char image[] = "E:/test/rus.jpg";
   // PIX   *pixs = pixRead(image);
    std::cout << image << std::endl;

    STRING text_out;
    api.ProcessPages(image, NULL, 0, &text_out);

    QString qstr = text_out.string();

    std::wcout << QString("Текст:\n").toStdWString();
    std::wcout << qstr.toStdWString() << std::endl;

    return 0;
}
