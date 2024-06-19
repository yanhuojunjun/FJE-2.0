# include "Iterator.h"

MyIterator::MyIterator(JsonObject* collection): collection(collection),index(0){}

bool MyIterator::hasNext() { return index < collection->keys.size(); }

std::string MyIterator::getNextKey() { return collection->keys[index]; }

std::shared_ptr<JsonElement> MyIterator::getNextValue() { return collection->values[index++]; }