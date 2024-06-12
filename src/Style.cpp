#include "Style.h"

// 树形风格------------------------------------------------------------------
//--------------------------------------------------------------------------
std::string TreeStyle::render(std::shared_ptr<JsonElement> json_data) {
    return renderTree(std::move(json_data), "");
}

std::string TreeStyle::renderTree(std::shared_ptr<JsonElement> data, const std::string& prefix) const {
    std::string result;
    const auto* obj = dynamic_cast<const JsonObject*>(data.get());
    if (obj) {
        const auto& keys = obj->getKeys();
        const auto& values = obj->getValues();
        int len = (int)keys.size();
        for (int i = 0; i < len; ++i) {
            const auto& key = keys[i];
            auto& value = values[i];
            if (const auto* child_obj = dynamic_cast<const JsonObject*>(value.get())) {
                result += prefix;
                std::string newPrefix = prefix;
                if (i == len - 1) {
                    result += "└─";
                    newPrefix += "   ";
                } else {
                    result += "├─";
                    newPrefix += "│  ";
                }
                result += key + "\n";
                result += renderTree(value, newPrefix);
            } else if (const auto* child_obj = dynamic_cast<const JsonValue*>(value.get())) {
                result += prefix;
                if (i == len - 1) {
                    result += "└─";
                } else {
                    result += "├─";
                }
                result += key;
                if (child_obj->getValue() != "null") {
                    result += ": " + child_obj->getValue();
                }
                result += "\n";
            }
        }
    }
    return result;
}


//矩形风格----------------------------------------------------------------------
//-----------------------------------------------------------------------------
std::string RectangleStyle::render(std::shared_ptr<JsonElement> json_data) {
    std::string result = renderRectangle(json_data, "", true);
    result = renderRectangle(json_data, "", false);
    result.replace(0, 3, "┌");
    result.replace(result.find("┤"), 3, "┐");
    result.replace((int)result.size() - 4, 3, "┘");

    size_t secondLastPos = result.rfind('\n', (int)result.size()-2);

    size_t foundPos = result.find("│", secondLastPos);
    while (foundPos != std::string::npos) {
        result.replace(foundPos, 3, "└");
        foundPos = result.find("│", foundPos + std::string("│").length());
    }

    foundPos = result.find("├", secondLastPos);
    while (foundPos != std::string::npos) {
        result.replace(foundPos, 3, "└");
        foundPos = result.find("├", foundPos + std::string("├").length());
    }

    foundPos = result.find(" ", secondLastPos);
    while (foundPos != std::string::npos) {
        result.replace(foundPos, 1, "─");
        foundPos = result.find(" ", foundPos + std::string("│").length());
    }
    return result;
}

std::string RectangleStyle::renderRectangle(std::shared_ptr<JsonElement> data, const std::string& prefix, bool getDisplayLength) {
    std::string result;
    const auto* obj = dynamic_cast<const JsonObject*>(data.get());
    if (obj) {
        const auto& keys = obj->getKeys();
        const auto& values = obj->getValues();
        int len = (int)keys.size();
        for (int i = 0; i < len; ++i) {
            const auto& key = keys[i];
            auto& value = values[i];
            if (const auto* child_obj = dynamic_cast<const JsonObject*>(value.get())) {
                std::string curRow;
                curRow += prefix;
                curRow += "├─";
                curRow += key;
                if (getDisplayLength) {
                    this->displayLength = std::max(this->displayLength, calculateDisplayWidth(curRow));
                } else {
                    int num = this->displayLength + 10 - calculateDisplayWidth(curRow);
                    for (int k = 0; k < num; ++k) {
                        curRow += "─";
                    }
                }
                curRow += "┤\n"; 
                result += curRow;
                result += renderRectangle(value, prefix + "│  ", getDisplayLength);
            } else if (const auto* child_value = dynamic_cast<const JsonValue*>(value.get())) {
                std::string curRow;
                curRow += prefix;
                curRow += "├─";
                curRow += key;
                if (child_value->getValue() != "null") {
                    curRow += ": " + child_value->getValue();
                }
                if (getDisplayLength) {
                    this->displayLength = std::max(this->displayLength, calculateDisplayWidth(curRow));
                } else {
                    int num = this->displayLength + 10 - calculateDisplayWidth(curRow);
                    for (int k = 0; k < num; ++k) {
                        curRow += "─";
                    }
                }
                curRow += "┤\n";
                result += curRow;
            }
        }
    }
    return result;
}

int RectangleStyle::calculateDisplayWidth(std::string str) const {
    double width = 0;
    for (char ch : str) {
        if ((unsigned char)ch > 127)  width += 1.0 / 3;
        else width += 1;     
    }
    return (int)(width + 1.0 / 3); 
}


// 工厂方法-----------------------------------------------------------------------
//--------------------------------------------------------------------------------
std::shared_ptr<Style> TreeStyleFactory::createStyle() const {
    return std::make_unique<TreeStyle>();
}

std::shared_ptr<Style> RectangleStyleFactory::createStyle() const {
    return std::make_unique<RectangleStyle>();
}