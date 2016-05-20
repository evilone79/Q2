#pragma once
#include <vector>

//this is an interface for choosing strategy of items from data set (replaces intial MinimumForCreate idea)
template<typename TDataItem>
class ItemChoiceStrategy
{
public:
	virtual std::vector<TDataItem> chooseItems(const std::vector<TDataItem>& data, int numOfItems) = 0;
};
