#include "Draw.h"

// 具体的建造者类实现-----------------------------------------------
void DrawStrategyBuilder::build_Style_Strategy(std::unique_ptr<StyleFactory> styleFactory) {
    this->style = styleFactory->createStyle();
}

void DrawStrategyBuilder::build_IconFamily_Strategy(std::unique_ptr<IconFamilyFactory> iconFamilyFactory) {
    this->icon_family = iconFamilyFactory->createIconFamily();
}

void DrawStrategyBuilder::setJsonData(std::shared_ptr<JsonElement> json_data) {
    this->json_data = std::move(json_data);
}

std::string DrawStrategyBuilder::draw() {
    auto* obj = dynamic_cast<JsonObject*>(this->json_data.get());

    obj->setIcon(this->icon_family);                         //设置图案
    std::string rendered_output = style->render(json_data);  //改变风格

    return rendered_output; //输出结果
}
