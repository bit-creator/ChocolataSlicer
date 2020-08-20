#include "printingContext.h"
#include "cinder/app/App.h"

#include "definitions.h"

void PrintingContext::open() { 
    initPrinterBoard();

    _open = true;

}

void PrintingContext::initPrintingContext() {
    _windowPtr = ui::uiWindow::create( ImVec2(), ImVec2(60,60), "FileSelector", ui::uiLocation_None,
                                       ImGuiWindowFlags_NoResize |
                                       ImGuiWindowFlags_NoCollapse
    );

    _windowBlurPtr = ui::uiWindow::create( ImVec2(), ImVec2(), "FileSelectorBlur", ui::uiLocation_None, 
                                        ImGuiWindowFlags_NoDecoration |
                                        ImGuiWindowFlags_NoNavInputs |
                                        ImGuiWindowFlags_NoFocusOnAppearing
    );



    _logger.write(ci::log::Metadata { .mLevel = ci::log::LEVEL_INFO }, "PrinterContext -> Firmware log" );

}


void PrintingContext::connectPrinterBoard() {
    _printerBoard->flush();

    Command _request = Receiver::getInstance().readCommand();
    if (_request.__cmd == OP_CONNECT_REQUEST ) {
        Transmitter::getInstance().sendCommand(Command { .__cmd = OP_CONNECT_ACCEPT } );
    }



    _logger.write(ci::log::Metadata{ .mLevel = ci::log::LEVEL_INFO }, "PrinterBoard connected. Version checking");
    Transmitter::getInstance().sendCommand( Command { .__cmd = OP_GET_VERSION } );
    Command _version = Receiver::getInstance().readCommand();
    if (_version.__args.at(0) != __ChocolataSlicer_Release_Version_  &&
        _version.__args.at(1) != __ChocolataSlicer_Major_Version_ &&
        _version.__args.at(2) != __ChocolataSlicer_Minor_Version_
    ) {    // FIXME: Check version
        Transmitter::getInstance().sendCommand(Command { .__cmd = OP_DISCONNECT } );
        _logger.write(ci::log::Metadata{ .mLevel = ci::log::LEVEL_WARNING }, "WARNING : Firmware version and slicer version are not compatible\n");
    }
    else {
        _logger.write(ci::log::Metadata{ .mLevel = ci::log::LEVEL_INFO }, "Versions of software are compatible, work continue\n=============================\n");
    }

}


void PrintingContext::initPrinterBoard() {
    if (_printerBoard ) return; // If boar is initted

    try {
        try {
            __SerialHard _serial;   _serial.__port = "/dev/ttyUSB0";
            if (!__serialHardIsOpen(&_serial) ) __serialHardOpen(&_serial );
        }
        catch (ci::Exception& ex ) {
            throw ex;
        }


        _printerBoard = ci::Serial::create(ci::Serial::findDeviceByNameContains("USB0", true ), 19200 );


        connectPrinterBoard();

    }
    catch (ci::Exception& ex ) {
        _logger.write(ci::log::Metadata { .mLevel = ci::log::LEVEL_WARNING }, "WARNING : Printer board was not connected" );
        CI_LOG_EXCEPTION("Serial device didn't init. Connect printer board", ex );
    }

}



void PrintingContext::draw() {
    ImVec2 offsets = ImVec2(35,35);

    ImGui::PushStyleColor(ImGuiCol_WindowBg, { 0.23137,0.20784,0.21961,0.5 } );
    _windowBlurPtr->_size = ImVec2(ci::app::getWindow()->getSize().x, ci::app::getWindow()->getSize().y );
    _windowBlurPtr->Begin();
    ImGui::PopStyleColor();
    ImGui::SetNextWindowFocus();

    _windowPtr->_size = ImVec2(ci::app::getWindow()->getSize().x-(2*offsets.x), ci::app::getWindow()->getSize().y-(2*offsets.y));
    _windowPtr->_pos = offsets;
    _windowPtr->Begin();
        ImGui::Columns(2, "printingWindowColumns" ); {
            ImGui::SetColumnWidth(0, _windowPtr->_size.x - 250 );
            ImGui::Text("Layer previewing");


            std::string _lb = "No connection";
            ImVec4 _cl = ImVec4(1,0,0, 0.4);
            ImVec2 _pos = ImGui::GetCursorScreenPos();
            ImGui::SetCursorScreenPos(ImVec2(_pos.x, _windowPtr->_pos.y + _windowPtr->_size.y - 9 - (ImGui::GetStyle().WindowPadding.y * 2) ) );

            if (_printerBoard != nullptr ) {
                _lb = "Connected device : " + _printerBoard->getDevice().getName();
                _cl = ImVec4(0,0,0, 0.4);
            }

            ImGui::TextColored(_cl, _lb.c_str() );
        }

        ImGui::NextColumn(); {
            ImGui::Text("Commands log");


            ImVec2 _pos = ImGui::GetCursorScreenPos();
            ImGui::SetCursorScreenPos(ImVec2(_pos.x, _windowPtr->_pos.y + _windowPtr->_size.y - 32 - (ImGui::GetStyle().WindowPadding.y * 2) ) );
            ImGui::Button("Pause", ImVec2(ImGui::GetColumnWidth() - (ImGui::GetStyle().WindowPadding.x * 2), 32) );
        }

        ImGui::Columns(1);
    _windowPtr->End();
    _windowBlurPtr->End();
}
