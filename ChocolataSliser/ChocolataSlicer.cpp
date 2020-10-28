#include "ChocolataSlicer.h"
#include "jsonConfig.h"

#include "EveryTick.cpp"
#include "SettingUp.cpp"

#include "cinder/app/AppBase.h"

///// TEMPORARY /////
#include "geometry.hpp"
#include "ChocolataSlicerMesh.h"
#include "vertexcloud.hpp"
#include "configs.hpp"
#include "ContentTree.h"

using namespace std::chrono;
///// TEMPORARY /////

void ChocolataSlicer::cleanup() {
    CHOCOLATA_SLIER_PROFILE_BEGIN_SESSION("closeProfiling", "assets/config/profiling/appCloseProfiling.json");

    {
        CHOCOLATA_SLIER_PROFILE_FUNCTION();


        PrintingContext::getInstance().disconnectPrinterBoard();

        // ContentTree
        ContentTree::getInstance().destroy();

        // FileSelector
        FileSelector::getInstance().destroy();

        // ShaderTree
        ShaderTree::getInstance().destroy();

        // ObjectPicker
        ObjectPicker::getInstance().destroy();
    }


    CHOCOLATA_SLIER_PROFILE_END_SESSION();
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
    _options.setVersion(3, 2);

	cinder::app::RendererRef renderer( new ci::app::RendererGl(_options ) );
	cinder::app::AppLinux::main<ChocolataSlicer>( renderer, "ChocolataSlicer", argc, argv, __preSettingUp );
    CHOCOLATA_SLIER_PROFILE_END_SESSION();

    // system("clear");
    //
    // cfg::get<i>(CfgNames::PERIMETRS) = 5u;
    // cfg::get<b>(CfgNames::DYNAMIC_LAYER) = true;
    // cfg::get<f>(CfgNames::MIN_LAYER) = 0.07f;
    // cfg::get<f>(CfgNames::LAYER) = 0.1f;
    // cfg::get<f>(CfgNames::INTERSECTION) = 0.55f;
    // cfg::get<f>(CfgNames::FIRST_LAYER) = 0.2f;
    // cfg::get<f>(CfgNames::MAX_LAYER) = 2.30f;
    // cfg::get<f>(CfgNames::MAX_LAYER) = 20.30f;
    //
    //
    //
    // auto start_load = high_resolution_clock::now();
    //
    // // auto item = make_mesh(Mesh::File::_STL, "test/bridge.stl");
    // // auto item = ContentItem("test/bridge.stl", ci::gl::BatchRef(nullptr));
    // ContentItemRef item = std::make_shared<ContentItem>("test/bridge.stl", ci::gl::BatchRef(nullptr));
    // // std::shared_ptr<ContentItem> ptr(item);
    //
    // item->_meshPtr = make_mesh(Mesh::File::_STL, "test/bridge.stl");
    //
    //
    // // ContentTree::getInstance()._items.push_back(std::make_shared<ContentItem>("test/bridge.stl", ci::gl::BatchRef(nullptr)));
    // auto finish_load = high_resolution_clock::now();
    //
    // auto load_time = duration_cast<milliseconds>(finish_load - start_load);
    //
    // std::cerr << "loading time - " << load_time.count() << " milliseconds" << '\n';
    //
    // // Slicer::vertexCloud cloud;
    // //
    // // Slicer::generateVertexCloud(cloud);
    // // //
    // // Slicer::heightInTerminal(cloud);
    //
    //
    // std::cerr << '\n' << '\n' << "triangles - " << item->_meshPtr -> getTriangles() << '\n'
    //     << "vertices - " << item->_meshPtr -> getVertices() << '\n' << '\n' <<'\n';

    return 0;
}
