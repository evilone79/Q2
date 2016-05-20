#pragma once
#include "ItemChoiceStrategy.h"
#include <random>

//concrete implementation of random item choice
template<typename TDataItem>
class RandomChooser : public ItemChoiceStrategy<TDataItem>
{
public:
	std::vector<TDataItem> chooseItems(const std::vector<TDataItem>& data, int numOfItems) override
	{
		//init randomizer
		std::default_random_engine generator;
		std::uniform_int_distribution<int> distribution(0, data.size() - 1);

		std::vector<TDataItem> chosen;
		if (data.size() > numOfItems)
			numOfItems = data.size(); //seemed like logical optimization
		while(numOfItems > 0)
		{
			int idx = distribution(generator);
			chosen.push_back(data[idx]);
			--numOfItems;
		}
		return std::move(chosen);
	}
};
