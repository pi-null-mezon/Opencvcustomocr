#Pri file for tesseract-OCR linkage
win32{

    TESSERACT_PATH = "C:/Program Files (x86)/Tesseract-OCR"

    INCLUDEPATH += $${TESSERACT_PATH}/include

    LIBS += -L$${TESSERACT_PATH}/lib

    LIBS += -lliblept168 \
            -llibtesseract302

    message(Tesseract library will be linked to project)
}
