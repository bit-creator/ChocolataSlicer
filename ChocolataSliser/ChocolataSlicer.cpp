#include "ChocolataSlicer.h"
#include "jsonConfig.h"

#include "EveryTick.cpp"
#include "SettingUp.cpp"

#include "cinder/app/AppBase.h"

void ChocolataSlicer::cleanup() {
    CI_LOG_D("End program. Memory cleaning : ");

    // ContentTree
    ContentTree::getInstance().destroy();

    // FileSelector
    FileSelector::getInstance().destroy();

    // ShaderTree
    ShaderTree::getInstance().destroy();

    // ObjectPicker
    ObjectPicker::getInstance().destroy();

}

/**
 * @brief General function for Setting up ChocolataSlicer before program will be loaded
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




int main(int argc, char* argv[] ) {
    ci::app::RendererGl::Options _options = ci::app::RendererGl::Options().msaa(16);
    _options.stencil(true );
	cinder::app::RendererRef renderer( new ci::app::RendererGl(_options ) );
	cinder::app::AppLinux::main<ChocolataSlicer>( renderer, "ChocolataSlicer", argc, argv, __preSettingUp );
	return 0;
}

// Insted
// CINDER_APP(ChocolataSlicer, ci::app::RendererGl(ci::app::RendererGl::Options().msaa(16) ) , __preSettingUp )
