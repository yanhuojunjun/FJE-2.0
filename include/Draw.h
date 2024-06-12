#ifndef DRAW_H
#define DRAW_H

#include "Style.h"
#include "Icon.h"
#include <string>
#include <map>
#include <memory>
#include <stdexcept>

class DrawBuilder {
public:
    virtual void setStyle(std::shared_ptr<Style> style) = 0;
    virtual void setIconFamily(std::shared_ptr<IconFamily> icon_family) = 0;
    virtual void setJsonData(std::shared_ptr<JsonElement> json_data) = 0;
    virtual std::string build() const = 0;
    virtual ~DrawBuilder() = default;
};


class ConcreteDrawBuilder : public DrawBuilder {
public:
    void setStyle(std::shared_ptr<Style> style) override;
    void setIconFamily(std::shared_ptr<IconFamily> icon_family) override;
    void setJsonData(std::shared_ptr<JsonElement> json_data) override;
    std::string build() const override;

private:
    std::shared_ptr<Style> style;
    std::shared_ptr<IconFamily> icon_family;
    std::shared_ptr<JsonElement> json_data;
};


class DrawDirector {
public:
    void setBuilder(std::shared_ptr<DrawBuilder> builder);
    std::string construct(std::shared_ptr<JsonElement> json_data) const;

private:
    std::shared_ptr<DrawBuilder> builder;
};

#endif 