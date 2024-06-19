#ifndef STYLE_H
#define STYLE_H

#include <iostream>
#include <string>
#include <memory>
#include <locale>
#include <codecvt>
#include <cwchar>

#include "JsonNode.h"
#include "Iterator.h"

// 风格接口
class Style {
public:
    virtual std::string render(std::shared_ptr<JsonElement> json_data) = 0;
    virtual ~Style() = default;
};

// 树形风格
class TreeStyle : public Style {
public:
    std::string render(std::shared_ptr<JsonElement> json_data) override;

private:
    std::string renderTree(std::shared_ptr<JsonElement> data, const std::string& prefix) const;
};

// 矩形风格
class RectangleStyle : public Style {
public:
    std::string render(std::shared_ptr<JsonElement> json_data) override;

private:
    std::string renderRectangle(std::shared_ptr<JsonElement> data, const std::string& prefix, bool getDisplayLength);
    int calculateDisplayWidth(std::string str) const;
    int displayLength = 0;
};



// 风格接口工厂
class StyleFactory {
public:
    virtual std::shared_ptr<Style> createStyle() const = 0;
    virtual ~StyleFactory() = default;
};

// 树形风格工厂
class TreeStyleFactory : public StyleFactory {
public:
    std::shared_ptr<Style> createStyle() const override;
};

// 矩形风格工厂
class RectangleStyleFactory : public StyleFactory {
public:
    std::shared_ptr<Style> createStyle() const override;
};

#endif
