#include "Receiver.h"
#include "printingContext.h"
#include <thread>

#include "cinder/Log.h"
#include "cinder/Serial.h"

Receiver::Receiver() {
    ci::log::LoggerFile* _logger = &PrintingContext::getInstance()._logger;
    if (PrintingContext::getInstance()._printerBoard )
        _logger->write(ci::log::Metadata{ ci::log::LEVEL_DEBUG }, "Receiver connected to log..." );

}

Command Receiver::readCommand(Command* _cmd ) {
    ci::log::LoggerFile* _logger = &PrintingContext::getInstance()._logger;
    ci::SerialRef _printerBoard = PrintingContext::getInstance()._printerBoard;


    if (!_printerBoard ) {
        _logger->write(ci::log::Metadata{ .mLevel = ci::log::LEVEL_ERROR }, "ERR : cant read command, board didn't connect");
        return Command();
    }


    std::string _request;
    while (_printerBoard->getNumBytesAvailable() < 2) {
        std::this_thread::sleep_for(std::chrono::milliseconds(OP_INTERUPTION) );
    }

    while (_printerBoard->getNumBytesAvailable() ) {
        _request.append({(char)_printerBoard->readByte()} );
        if (_request.at(_request.size()-1) == OP_TERMINATOR)
            break;
        std::this_thread::sleep_for(std::chrono::milliseconds(OP_INTERUPTION) );
    }


    std::string lg = "<- "; lg += _request;
    _logger->write(ci::log::Metadata(), lg );


    // Parsing
    Command _command;
    _command.__native = _request;
    _command.__cmd = (uint8_t)_request.at(0);



    if (_request.find((char)OP_SEPARATOR) != std::string::npos ) {
        size_t pos = 0;
        std::string token;
        while ((pos = _request.find((char)OP_SEPARATOR)) != std::string::npos) {
            token = _request.substr(0, pos);
            _request.erase(0, pos + 1);


            if (pos == 1 ) continue;
            if (token.at(token.size()-1) == char(OP_TERMINATOR) ) token.pop_back();

            _command.__args.push_back(atof(token.c_str()) );
        }
    }


    if (_cmd ) { *_cmd = _command; }
    return _command;

}