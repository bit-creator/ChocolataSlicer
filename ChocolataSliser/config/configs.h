#ifndef __CHOCOLATA_SLICER_CONFIGS_
#define __CHOCOLATA_SLICER_CONFIGS_


#include "labels.h"
#include "fileConfig.h"



namespace config {

    /**
     * SlicerConfig supports options for loading the slicer program. These settings only contain the slicing process definitions
     * for the ChocolataSlicer application.
     * 
     * SlicerConfig loads from binary file. User should be able to save/load other settings
     * 
    */
    class SlicerCfg {

    };


    /**
     * PrinterConfig supports options of current printer. These settings only contain the printer definitions
     * for the ChocolataSlicer application.
     * 
     * PrinterConfig loads from binary file. User should be able to save/load other settings
     * 
    */
    class PrinterCfg {

    };


    /**
     * MaterialCfg orientated to parameters of chocolate which will be used to printing.
     * 
     * This parameters must be avaliable to change to make possible use different recipes of used chocolate
     * 
    */
    class MaterialCfg {

    };



};


namespace cfg = config;


#endif // __CHOCOLATA_SLICER_CONFIGS_