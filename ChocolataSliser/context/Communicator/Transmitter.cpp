#include "Transmitter.h"
#include "printingContext.h"
#include <thread>

#include "cinder/Log.h"
#include "cinder/Serial.h"


Transmitter::Transmitter() {
    ci::log::LoggerFile* _logger = &PrintingContext::getInstance()._logger;
    if (PrintingContext::getInstance()._printerBoard )
        _logger->write(ci::log::Metadata{ ci::log::LEVEL_DEBUG }, "Transmitter connected to log..." );

}

void Transmitter::sendCommand(Command _cmd ) {
    ci::log::LoggerFile* _logger = &PrintingContext::getInstance()._logger;
    ci::SerialRef _printerBoard = PrintingContext::getInstance()._printerBoard;


    _commandsLog.insert({ {_commandsLog.size(), _cmd} });

    if (!_printerBoard ) {
        _logger->write(ci::log::Metadata{ .mLevel = ci::log::LEVEL_ERROR }, "ERR : cant sent command, board didn't connect");
        return;
    }



    #ifndef _OP_ARGS_AS_BYTES
        std::string sentCommand = "-> ";
        sentCommand += (char)_cmd.__cmd;
        if (_cmd.__args.size() >= 1 ) {
            for (int i = 0; i < _cmd.__args.size(); i++ ) {
                sentCommand += (char)OP_SEPARATOR;
                sentCommand += std::to_string(_cmd.__args.at(i));
            }
        }
        sentCommand += (char)OP_TERMINATOR;
        _logger->write(ci::log::Metadata(), sentCommand );



        _printerBoard->writeByte(_cmd.__cmd );
        for (int i = 0; i < _cmd.__args.size(); i++ ) {
            _printerBoard->writeByte(OP_SEPARATOR);
            _printerBoard->writeString(std::to_string(_cmd.__args.at(i)) );
        }      

    #else
        _printerBoard->writeByte(_cmd.__cmd );

        for (int i = 0; i < _cmd.__args.size(); i++ ) {
            _printerBoard->writeByte(OP_SEPARATOR);
            _printerBoard->writeBytes((char*)&_cmd.__args.at(i), sizeof(_cmd.__args.at(i) ) );
        }
    #endif



    _printerBoard->writeByte(OP_TERMINATOR);
    std::this_thread::sleep_for(std::chrono::milliseconds(OP_INTERUPTION) );

}