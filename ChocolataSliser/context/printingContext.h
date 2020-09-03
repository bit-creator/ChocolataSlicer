#ifndef __CHOCOLATA_SLICER_PRINTING_CONTEXT_
#define __CHOCOLATA_SLICER_PRINTING_CONTEXT_

#include "cinder/Log.h"
#include "cinder/Serial.h"

#include "cstringFunctions.h"
#include "ui/uiWindow.h"

#include "SerialHard/SerialHard.h"

#include "Communicator/Transmitter.h"
#include "Communicator/Receiver.h"
#include "opcodes.h"

#include "definitions.h"

class PrintingContext {
    private :
        PrintingContext()  : _open(false) { initPrintingContext(); }

        void initPrintingContext();

        void connectPrinterBoard();


    public :
        static PrintingContext& getInstance() { static PrintingContext dialog; return dialog;  }


        void initPrinterBoard();



        void draw();


        void open();

        bool isOpen() { return _open; }


    private : // UI
        bool                            _open;

        ui::uiWindowRef                 _windowPtr;

        ui::uiWindowRef                 _windowBlurPtr;


    public : // Firmware
        ci::log::LoggerFile             _logger = ci::log::LoggerFile(__ChocolataSlicer_FirmwareLogFile_, false);

        ci::SerialRef                   _printerBoard;

};



#endif // __CHOCOLATA_SLICER_PRINTING_CONTEXT__

