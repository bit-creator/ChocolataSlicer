#ifndef __CHOCOLATA_SLICER_JSON_CONFIG_H
#define __CHOCOLATA_SLICER_JSON_CONFIG_H

#include "jsoncpp/json.h"
#include "labels.h"

#include "cinder/gl/gl.h"
#include <typeinfo>

namespace Json {
    /* Conversion to simple values */

    // Boolean
    bool            getValueExtracted(Json::Value& source, bool defaultValue = false );            

    // Intager
    int             getValueExtracted(Json::Value& source, int defaultValue = 0 );

    // Float
    float           getValueExtracted(Json::Value& source, float defaultValue = 0.0f );

    // Double
    double          getValueExtracted(Json::Value& source, double defaultValue = 0.0 );


    /* Conversion to array values */

    // CString
    const char*     getValueExtracted(Json::Value& source, const char* defaultValue = "" );

    // String
    std::string     getValueExtracted(Json::Value& source, std::string defaultValue = "" );


    /* Vectors */

    // glm::vec2
    glm::vec2       getValueExtracted(Json::Value& source, glm::vec2 defaultValue = {0,0} );

    // glm::vec3
    glm::vec3       getValueExtracted(Json::Value& source, glm::vec3 defaultValue = {0,0,0} );

    // glm::vec4
    glm::vec4       getValueExtracted(Json::Value& source, glm::vec4 defaultValue = {0,0,0,0} );






    /* Getting valuse by label */

    // Boolean
    bool            getValueByLabel(Json::Value& source, Label_ label, bool defaultValue = false );            

    // Intager
    int             getValueByLabel(Json::Value& source, Label_ label, int defaultValue = 0 );

    // Float
    float           getValueByLabel(Json::Value& source, Label_ label, float defaultValue = 0.0f );

    // Double
    double          getValueByLabel(Json::Value& source, Label_ label, double defaultValue = 0.0 );


    /* Conversion to array values */

    // CString
    const char*     getValueByLabel(Json::Value& source, Label_ label, const char* defaultValue = "" );

    // String
    std::string     getValueByLabel(Json::Value& source, Label_ label, std::string defaultValue = "" );


    /* Vectors */

    // glm::vec2
    glm::vec2       getValueByLabel(Json::Value& source, Label_ label, glm::vec2 defaultValue = {0,0} );

    // glm::vec3
    glm::vec3       getValueByLabel(Json::Value& source, Label_ label, glm::vec3 defaultValue = {0,0,0} );

    // glm::vec4
    glm::vec4       getValueByLabel(Json::Value& source, Label_ label, glm::vec4 defaultValue = {0,0,0,0} );
}





#endif // _PLANET_MOV_JSON_CONFIG_H


