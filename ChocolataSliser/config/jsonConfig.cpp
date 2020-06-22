#include "jsonConfig.h"

// Boolean
bool Json::getValueExtracted(Json::Value &source, bool defaultValue)
{
    if (source.empty() || source.isArray())
        return defaultValue;

    try
    {
        bool returnValue = source.asBool();
        return returnValue;
    }
    catch (...)
    {
    }

    return defaultValue;
}

// Intager
int Json::getValueExtracted(Json::Value &source, int defaultValue)
{
    if (source.empty() || source.isArray())
        return defaultValue;

    try
    {
        int returnValue = source.asInt();
        return returnValue;
    }
    catch (...)
    {
    }

    return defaultValue;
}

// Float
float Json::getValueExtracted(Json::Value &source, float defaultValue)
{
    if (source.empty() || source.isArray())
        return defaultValue;

    try
    {
        float returnValue = source.asFloat();
        return returnValue;
    }
    catch (...)
    {
    }

    return defaultValue;
}

// Double
double Json::getValueExtracted(Json::Value &source, double defaultValue)
{
    if (source.empty() || source.isArray())
        return defaultValue;

    try
    {
        double returnValue = source.asDouble();
        return returnValue;
    }
    catch (...)
    {
    }

    return defaultValue;
}

// CString
const char *Json::getValueExtracted(Json::Value &source, const char *defaultValue)
{
    if (source.empty() || source.isArray())
        return defaultValue;

    try
    {
        const char *returnValue = source.asCString();
        return returnValue;
    }
    catch (...)
    {
    }

    return defaultValue;
}

// String
std::string Json::getValueExtracted(Json::Value &source, std::string defaultValue)
{
    if (source.empty() || source.isArray())
        return defaultValue;

    try
    {
        std::string returnValue = source.asString();
        return returnValue;
    }
    catch (...)
    {
    }

    return defaultValue;
}

glm::vec2 Json::getValueExtracted(Json::Value &source, glm::vec2 defaultValue)
{
    if (source.empty())
        return defaultValue;
    if (source.size() < 2)
        return defaultValue;

    try
    {
        glm::vec2 returnValue = glm::vec2(source[0].asFloat(), source[1].asFloat());
        return returnValue;
    }
    catch (...)
    {
    }

    return defaultValue;
}

glm::vec3 Json::getValueExtracted(Json::Value &source, glm::vec3 defaultValue)
{
    if (source.empty())
        return defaultValue;
    if (source.size() < 3)
        return defaultValue;

    try
    {
        glm::vec3 returnValue = glm::vec3(source[0].asFloat(), source[1].asFloat(), source[2].asFloat());
        return returnValue;
    }
    catch (...)
    {
    }

    return defaultValue;
}

glm::vec4 Json::getValueExtracted(Json::Value &source, glm::vec4 defaultValue)
{
    if (source.empty())
        return defaultValue;
    if (source.size() < 4)
        return defaultValue;

    try
    {
        glm::vec4 returnValue = {source[0].asFloat(), source[1].asFloat(), source[2].asFloat(), source[3].asFloat()};
        return returnValue;
    }
    catch (...)
    {
    }

    return defaultValue;
}

bool Json::getValueByLabel(Json::Value &source, Label_ label, bool defaultValue)
{
    if (source[Labels.at((int)label).first].empty() || source.isArray())
        goto second;

    try
    {
        bool returnValue = source[Labels.at((int)label).first].asBool();
        return returnValue;
    }
    catch (...)
    {
    }

second:

    if (source[Labels.at((int)label).second].empty() || source.isArray())
        goto end;

    try
    {
        bool returnValue = source[Labels.at((int)label).second].asBool();
        return returnValue;
    }
    catch (...)
    {
    }

end:
    return defaultValue;
}

int Json::getValueByLabel(Json::Value &source, Label_ label, int defaultValue)
{
    if (source[Labels.at((int)label).first].empty() || source.isArray())
        goto second;

    try
    {
        int returnValue = source[Labels.at((int)label).first].asBool();
        return returnValue;
    }
    catch (...)
    {
    }

second:

    if (source[Labels.at((int)label).second].empty() || source.isArray())
        goto end;

    try
    {
        int returnValue = source[Labels.at((int)label).second].asInt();
        return returnValue;
    }
    catch (...)
    {
    }

end:
    return defaultValue;
}

float Json::getValueByLabel(Json::Value &source, Label_ label, float defaultValue)
{
    if (source[Labels.at((int)label).first].empty() || source.isArray())
        goto second;

    try
    {
        float returnValue = source[Labels.at((int)label).first].asFloat();
        return returnValue;
    }
    catch (...)
    {
    }

second:

    if (source[Labels.at((int)label).second].empty() || source.isArray())
        goto end;

    try
    {
        float returnValue = source[Labels.at((int)label).second].asFloat();
        return returnValue;
    }
    catch (...)
    {
    }

end:
    return defaultValue;
}

double Json::getValueByLabel(Json::Value &source, Label_ label, double defaultValue)
{
    if (source[Labels.at((int)label).first].empty() || source.isArray())
        goto second;

    try
    {
        double returnValue = source[Labels.at((int)label).first].asDouble();
        return returnValue;
    }
    catch (...)
    {
    }

second:

    if (source[Labels.at((int)label).second].empty() || source.isArray())
        goto end;

    try
    {
        double returnValue = source[Labels.at((int)label).second].asDouble();
        return returnValue;
    }
    catch (...)
    {
    }

end:
    return defaultValue;
}

const char *Json::getValueByLabel(Json::Value &source, Label_ label, const char *defaultValue)
{
    if (source[Labels.at((int)label).first].empty() || source.isArray())
        goto second;

    try
    {
        const char *returnValue = source[Labels.at((int)label).first].asCString();
        return returnValue;
    }
    catch (...)
    {
    }

second:

    if (source[Labels.at((int)label).second].empty() || source.isArray())
        goto end;

    try
    {
        const char *returnValue = source[Labels.at((int)label).second].asCString();
        return returnValue;
    }
    catch (...)
    {
    }

end:
    return defaultValue;
}

std::string Json::getValueByLabel(Json::Value &source, Label_ label, std::string defaultValue)
{
    if (source[Labels.at((int)label).first].empty() || source.isArray())
        goto second;

    try
    {
        std::string returnValue = source[Labels.at((int)label).first].asString();
        return returnValue;
    }
    catch (...)
    {
    }

second:

    if (source[Labels.at((int)label).second].empty() || source.isArray())
        goto end;

    try
    {
        std::string returnValue = source[Labels.at((int)label).second].asString();
        return returnValue;
    }
    catch (...)
    {
    }

end:
    return defaultValue;
}

glm::vec2 Json::getValueByLabel(Json::Value &source, Label_ label, glm::vec2 defaultValue)
{
    if (source[Labels.at((int)label).first].empty() || source[Labels.at((int)label).first].size() < 2)
        goto second;

    try
    {
        glm::vec2 returnValue = glm::vec2(source[Labels.at((int)label).first][0].asFloat(), source[Labels.at((int)label).first][1].asFloat());
        return returnValue;
    }
    catch (...)
    {
        goto end;
    }

second:

    if (source[Labels.at((int)label).second].empty() || source[Labels.at((int)label).second].size() < 2)
        goto end;

    try
    {
        glm::vec2 returnValue = glm::vec2(source[Labels.at((int)label).second][0].asFloat(), source[Labels.at((int)label).second][1].asFloat());
        return returnValue;
    }
    catch (...)
    {
    }

end:
    return defaultValue;
}

glm::vec3 Json::getValueByLabel(Json::Value &source, Label_ label, glm::vec3 defaultValue)
{
    if (source[Labels.at((int)label).first].empty() || source[Labels.at((int)label).first].size() < 3)
        goto second;

    try
    {
        glm::vec3 returnValue = glm::vec3(source[Labels.at((int)label).first][0].asFloat(), source[Labels.at((int)label).first][1].asFloat(), source[Labels.at((int)label).first][2].asFloat());
        return returnValue;
    }
    catch (...)
    {
    }

second:

    if (source[Labels.at((int)label).second].empty() || source[Labels.at((int)label).second].size() < 3)
        goto end;

    try
    {
        glm::vec3 returnValue = glm::vec3(source[Labels.at((int)label).second][0].asFloat(), source[Labels.at((int)label).second][1].asFloat(), source[Labels.at((int)label).second][2].asFloat());
        return returnValue;
    }
    catch (...)
    {
        goto end;
    }

end:
    return defaultValue;
}

glm::vec4 Json::getValueByLabel(Json::Value &source, Label_ label, glm::vec4 defaultValue)
{
    if (source[Labels.at((int)label).first].empty() || source[Labels.at((int)label).first].size() < 4)
        goto second;

    try
    {
        glm::vec4 returnValue = glm::vec4(source[Labels.at((int)label).first][0].asFloat(), source[Labels.at((int)label).first][1].asFloat(), source[Labels.at((int)label).first][2].asFloat(), source[Labels.at((int)label).first][3].asFloat());
        return returnValue;
    }
    catch (...)
    {
    }

second:

    if (source[Labels.at((int)label).second].empty() || source[Labels.at((int)label).second].size() < 4)
        goto end;

    try
    {
        glm::vec4 returnValue = glm::vec4(source[Labels.at((int)label).second][0].asFloat(), source[Labels.at((int)label).second][1].asFloat(), source[Labels.at((int)label).second][2].asFloat(), source[Labels.at((int)label).second][3].asFloat());
        return returnValue;
    }
    catch (...)
    {
        goto end;
    }

end:
    return defaultValue;
}
