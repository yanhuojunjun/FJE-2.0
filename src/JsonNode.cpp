#include "JsonNode.h"
#include "Iterator.h"

// 组合组件
void JsonObject::add(const std::string& key, std::shared_ptr<JsonElement> value) {
    keys.emplace_back(key);
    values.emplace_back(std::move(value));
}

const std::vector<std::string>& JsonObject::getKeys() const {
    return keys;
}

const std::vector<std::shared_ptr<JsonElement>>& JsonObject::getValues() const {
    return values;
}

void JsonObject::setIcon(std::shared_ptr<IconFamily> icon_family) {
    std::string internal_icon = icon_family->getInternalNodeIcon();
    std::string leaf_icon = icon_family->getLeafNodeIcon();
    int len = (int)keys.size();
    for (int i = 0; i < len; ++i) { // 遍历每一个子节点
        std::string current_icon = leaf_icon; //当前节点的图案 -> 叶子节点图案
        auto& value = values[i];
        if (auto* child_obj = dynamic_cast<JsonObject*>(value.get())) { //如果当前子节点不是叶子
            current_icon = internal_icon;     //当前节点的图案 -> 中间节点图案
            child_obj->setIcon(icon_family);  //递归
        }
        keys[i].insert(0, current_icon);      //插入当前节点图案（中间节点或者叶子节点图案）
    }
}

std::shared_ptr<Iterator> JsonObject::createIterator() { return std::make_shared<MyIterator>(this); }

// 叶子组件
JsonValue::JsonValue(std::string value) : value(std::move(value)) {}

const std::string& JsonValue::getValue() const {
    return value;
}