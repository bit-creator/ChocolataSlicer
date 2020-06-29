#include "ChocolataSlicer.h"
#include "jsonConfig.h"

#include "EveryTick.cpp"
#include "SettingUp.cpp"


void ChocolataSlicer::cleanup() {
    CI_LOG_D("End program. Memory cleaning : ");

    // uiContentTree
    ui::uiContentTree::getInstance().destroy();

    // FileSelector
    FileSelector::getInstance().destroy();

}

/**
 * General function for Setting up ChocolataSlicer before program will be loaded
*/
static void __preSettingUp(ci::app::App::Settings* settings ) {
    Json::Value windowCfg;
    std::ifstream configFile("assets/config/windowSettings.json" );
    configFile >> windowCfg;
    configFile.close();

    // Loading arguments or set default values
    settings->setWindowSize(getValueByLabel(windowCfg, Label_winSize, glm::vec2(1124, 590)) );
    settings->setFrameRate(getValueByLabel(windowCfg, Label_winFrameRate, 45) );
}


CINDER_APP(ChocolataSlicer, ci::app::RendererGl(ci::app::RendererGl::Options().msaa(16 ) ), __preSettingUp )

