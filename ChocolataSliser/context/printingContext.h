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

#include "core.h"

class PrintingContext {
    private :
        PrintingContext()  : _open(false) { initPrintingContext(); }

        void initPrintingContext();

        void connectPrinterBoard();


    public :
        static PrintingContext& getInstance() { static PrintingContext dialog; return dialog;  }


        void initPrinterBoard();

        void disconnectPrinterBoard();


        void draw();


        void open();

        bool isOpen() { return _open; }


    private : // UI
        bool                            _open = false;

        ui::uiWindowRef                 _windowPtr;

        ui::uiWindowRef                 _windowBlurPtr;


    public : // Firmware
        ci::SerialRef                   _printerBoard;

    public : // Printirng
        bool                            _sliced = false;

        bool                            _printing = false;

        bool                            _printingPaused = false;

};



#endif // __CHOCOLATA_SLICER_PRINTING_CONTEXT__

