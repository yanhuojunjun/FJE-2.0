#ifndef JSONNODE_H
#define JSONNODE_H

#include "Icon.h"

#include <any>
#include <string>
#include <vector>
#include <memory>

class Iterator;

// 抽象组件
class JsonElement {
public:
    virtual ~JsonElement() = default;
};

// 组合组件：json对象，非叶子节点
class JsonObject : public JsonElement {
public:
    void add(const std::string& key, std::shared_ptr<JsonElement> value);
    const std::vector<std::string>& getKeys() const;
    const std::vector<std::shared_ptr<JsonElement>>& getValues() const;
    void setIcon(std::shared_ptr<IconFamily> icon_family);
    std::shared_ptr<Iterator> createIterator();

private:
    std::vector<std::string> keys;
    std::vector<std::shared_ptr<JsonElement>> values;
    friend class MyIterator;
};

// 叶子组件：json值
class JsonValue : public JsonElement {
public:
    explicit JsonValue(std::string value);
    const std::string& getValue() const;

private:
    std::string value;
};

#endif