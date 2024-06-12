#include "Draw.h"

// 具体的建造者类实现-----------------------------------------------
void ConcreteDrawBuilder::setStyle(std::shared_ptr<Style> style) {
    this->style = std::move(style);
}

void ConcreteDrawBuilder::setIconFamily(std::shared_ptr<IconFamily> icon_family) {
    this->icon_family = std::move(icon_family);
}

void ConcreteDrawBuilder::setJsonData(std::shared_ptr<JsonElement> json_data) {
    this->json_data = std::move(json_data);
}

std::string ConcreteDrawBuilder::build() const {
    auto* obj = dynamic_cast<JsonObject*>(this->json_data.get());

    obj->setIcon(this->icon_family);                         //设置图案
    std::string rendered_output = style->render(json_data);  //改变风格

    return rendered_output; //输出结果
}
