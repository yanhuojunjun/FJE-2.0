#ifndef ITERATOR_H
#define ITERATOR_H

#include <iostream>
#include <string>
#include <memory>
#include <locale>
#include <codecvt>
#include <cwchar>
#include <vector>

# include "JsonNode.h"

class Iterator {
public:
    virtual bool hasNext() = 0;
    virtual std::string getNextKey() = 0;
    virtual std::shared_ptr<JsonElement> getNextValue() = 0;
    virtual ~Iterator() = default;
};

class MyIterator : public Iterator {
public:
    MyIterator(JsonObject* collection);
    bool hasNext() override;
    std::string getNextKey() override;
    std::shared_ptr<JsonElement> getNextValue() override;

private:
    JsonObject* collection;
    int index;
};

#endif