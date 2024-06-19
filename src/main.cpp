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
        std::cout << "Usage: ./fje -f <json file> -s <style> -i <icon family>" << std::endl;
        std::cout << "<style>: rectangle or tree" << std::endl;
        std::cout << "<icon family>: poker-face or json_defined" << std::endl;
        return 0;
    }
    std::string json_file = argv[2];
    std::string style_name = argv[4];
    std::string icon_family_name = argv[6];

    // 获取json对象
    std::shared_ptr<JsonLoader> loader;
    auto json_data = loader->loadJson(json_file);

    // 风格
    std::unique_ptr<StyleFactory> style_factory;

    if (style_name == "tree") {
        style_factory = std::make_unique<TreeStyleFactory>();
    } else if (style_name == "rectangle") {
        style_factory = std::make_unique<RectangleStyleFactory>();
    } else {
        throw std::invalid_argument("Unknown style: " + style_name);
    }

    // icon
    std::unique_ptr<IconFamilyFactory> icon_family_factory;

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

    // 使用 建造者模式 + 策略模式 创建对象
    auto builder = std::make_shared<DrawStrategyBuilder>();
    builder->build_Style_Strategy(std::move(style_factory));
    builder->build_IconFamily_Strategy(std::move(icon_family_factory));
    builder->setJsonData(json_data);

    //构建输出
    std::string result = builder->draw();
    std::cout << result << std::endl;

    return 0;
}