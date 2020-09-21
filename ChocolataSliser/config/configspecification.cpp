#include "configspecification.h"

flpt Configs::Infill::Instance()      { static Infill       instance; __instance = &instance; return __instance; }
inpt Configs::Perimetrs::Instance()   { static Perimetrs    instance; __instance = &instance; return __instance; }
blpt Configs::DynamicLayer::Instance(){ static DynamicLayer instance; __instance = &instance; return __instance; }
flpt Configs::MinLayer::Instance()    { static MinLayer     instance; __instance = &instance; return __instance; }
flpt Configs::MaxLayer::Instance()    { static MaxLayer     instance; __instance = &instance; return __instance; }
flpt Configs::Layer::Instance()       { static Layer        instance; __instance = &instance; return __instance; }
flpt Configs::Intersection::Instance(){ static Intersection instance; __instance = &instance; return __instance; }
flpt Configs::FirstLayer::Instance()  { static FirstLayer   instance; __instance = &instance; return __instance; }


void Configs::Infill::check()      { std::cout << "Infill config was changed\n\n";  }
void Configs::Perimetrs::check()   { std::cout << "Perimetrs config was changed\n\n";  }
void Configs::DynamicLayer::check(){ std::cout << "LayerHeight config was changed\n\n";  }
void Configs::MinLayer::check()    { std::cout << "LayerHeight config was changed\n\n";  }
void Configs::MaxLayer::check()    { std::cout << "Max Layer config was changed\n\n";  }
void Configs::Layer::check()       { std::cout << "LayerHeight config was changed\n\n";  }
void Configs::Intersection::check(){ std::cout << "LayerHeight config was changed\n\n";  }
void Configs::FirstLayer::check()  { std::cout << "LayerHeight config was changed\n\n";  }
