win32{

TESSERACT_PATH = "C:/Program Files (x86)/Tesseract-OCR"

INCLUDEPATH += $${TESSERACT_PATH}/include

LIBS += -L$${TESSERACT_PATH}/lib

LIBS += -lliblept168 \
        -lliblept168d \
        -llibtesseract302 \
        -llibtesseract302d

    message(Tesseract library will be linked to project)
}
