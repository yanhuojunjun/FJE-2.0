#ifndef ICON_H
#define ICON_H

#include <string>
#include <memory>
#include <fstream>
#include <iostream>

// 图标族接口
class IconFamily {
public:
    virtual std::string getInternalNodeIcon() const = 0;
    virtual std::string getLeafNodeIcon() const = 0;
    virtual ~IconFamily() = default;
};

// Poker Face 图标族
class PokerFaceIconFamily : public IconFamily {
public:
    std::string getInternalNodeIcon() const override;
    std::string getLeafNodeIcon() const override;
};

// JSON自定义图标族
class JsonIconFamily : public IconFamily {
public:
    JsonIconFamily(std::string internalNodeIcon, std::string leafNodeIcon);
    std::string getInternalNodeIcon() const override;
    std::string getLeafNodeIcon() const override;

private:
    std::string internalNodeIcon;
    std::string leafNodeIcon;
};

// 图标族工厂（
class IconFamilyFactory {
public:
    virtual std::shared_ptr<IconFamily> createIconFamily() const = 0;
    virtual ~IconFamilyFactory() = default;
};

// Poker Face 图标族工厂
class PokerFaceIconFamilyFactory : public IconFamilyFactory {
public:
    std::shared_ptr<IconFamily> createIconFamily() const override;
};

// JSON 自定义图标族工厂
class JsonIconFamilyFactory : public IconFamilyFactory {
public:
    JsonIconFamilyFactory(std::string internalNodeIcon, std::string leafNodeIcon);
    std::shared_ptr<IconFamily> createIconFamily() const override;

private:
    std::string internalNodeIcon, leafNodeIcon;
};

#endif
