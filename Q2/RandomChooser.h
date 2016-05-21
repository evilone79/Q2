#pragma once
#include "ItemChoiceStrategy.h"
#include <random>

//concrete implementation of random item choice
template<typename TDataItem>
class RandomChooser : public ItemChoiceStrategy<TDataItem>
{
private:
	std::random_device m_rndDev;
public:
	std::vector<TDataItem> chooseItems(const std::vector<TDataItem>& data, int numOfItems) override
	{
		//init randomizer
		std::mt19937 generator(m_rndDev());
		std::uniform_int_distribution<int> distribution(0, data.size() - 1);

		std::vector<TDataItem> chosen;
		if (numOfItems > data.size())
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
