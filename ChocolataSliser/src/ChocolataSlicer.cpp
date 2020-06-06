#include "ChocolataSlicer.h"

#include "EveryTick.cpp"
#include "SettingUp.cpp"

/**
 * General function for Setting up ChocolataSlicer before program will be loaded
*/
static void __preSettingUp(ci::app::App::Settings* settings ) {
}


CINDER_APP(ChocolataSlicer, ci::app::RendererGl(ci::app::RendererGl::Options().msaa(16 ) ), __preSettingUp )

