#include <iostream>
#include <stdexcept>
#include <any>
#include <memory>

#include "Icon.h"
#include "Style.h"
#include "Draw.h"
#include "JsonLoader.h"


int main(int argc, char* argv[]) {
    if (argc < 7) {
        std::cerr << "Usage: fje -f <json file> -s <style> -i <icon family>" << std::endl;
        return 1;
    }

    std::string json_file = argv[2];
    std::string style_name = argv[4];
    std::string icon_family_name = argv[6];

    // 获取json对象
    std::shared_ptr<JsonLoader> loader;
    auto json_data = loader->loadJson(json_file);

    // 使用工厂方法模式创建风格对象
    std::shared_ptr<StyleFactory> factory;

    if (style_name == "tree") {
        factory = std::make_unique<TreeStyleFactory>();
    } else if (style_name == "rectangle") {
        factory = std::make_unique<RectangleStyleFactory>();
    } else {
        throw std::invalid_argument("Unknown style: " + style_name);
    }

    auto style = factory->createStyle();

    // 使用抽象工厂创建icon对象
    std::shared_ptr<IconFamilyFactory> icon_family_factory;

    if (icon_family_name == "poker-face") {
        icon_family_factory = std::make_unique<PokerFaceIconFamilyFactory>();
    } else if (icon_family_name == "json_defined") {
        std::shared_ptr<JsonLoader> Json_loader;
        auto json_data = Json_loader->loadJson("../input/icon.json");
        const auto* obj = dynamic_cast<const JsonObject*>(json_data.get());
        const auto& keys = obj->getKeys();
        const auto& values = obj->getValues();

        std::string internalNodeIcon, leafNodeIcon;
        if (keys[0] == "internalNodeIcon" && keys[1] == "leafNodeIcon") {
            const auto* child_obj_0 = dynamic_cast<const JsonValue*>(values[0].get());
            const auto* child_obj_1 = dynamic_cast<const JsonValue*>(values[1].get());

            internalNodeIcon = child_obj_0->getValue();
            leafNodeIcon = child_obj_1->getValue();
        } else if (keys[0] == "leafNodeIcon" && keys[1] == "internalNodeIcon") {
            const auto* child_obj_0 = dynamic_cast<const JsonValue*>(values[0].get());
            const auto* child_obj_1 = dynamic_cast<const JsonValue*>(values[1].get());

            internalNodeIcon = child_obj_1->getValue();
            leafNodeIcon = child_obj_0->getValue();
        } else {
            internalNodeIcon = "+";
            leafNodeIcon = "-";
        }
        icon_family_factory = std::make_unique<JsonIconFamilyFactory>(internalNodeIcon, leafNodeIcon);
    } else {
        throw std::invalid_argument("Unknown icon family: " + icon_family_name);
    }

    auto icon_family = icon_family_factory->createIconFamily();

    // 使用建造者模式创建可视化对象
    auto builder = std::make_shared<ConcreteDrawBuilder>();
    DrawDirector director;
    director.setBuilder(builder);

    // 设置建造者的参数
    builder->setStyle(std::move(style));
    builder->setIconFamily(std::move(icon_family));

    std::string result = director.construct(json_data);
    std::cout << result << std::endl;

    return 0;
}