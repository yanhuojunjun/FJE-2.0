#ifndef DRAW_H
#define DRAW_H

#include "Style.h"
#include "Icon.h"
#include <string>
#include <map>
#include <memory>
#include <stdexcept>

class DrawStrategyBuilder {
public:
    void build_Style_Strategy(std::unique_ptr<StyleFactory> styleFactory);
    void build_IconFamily_Strategy(std::unique_ptr<IconFamilyFactory> iconFamilyFactory);
    void setJsonData(std::shared_ptr<JsonElement> json_data);
    std::string draw();

private:
    std::shared_ptr<Style> style;
    std::shared_ptr<IconFamily> icon_family;
    std::shared_ptr<JsonElement> json_data;
};

#endif 