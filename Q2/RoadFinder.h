#pragma once

#include <memory>
#include "Model.h"
#include <vector>



class RoadFinder
{
public:

	RoadFinder(int iterations, double threshold, int minForFit)
		: m_iterations(iterations),
		  m_threshold(threshold),
		  m_minForFit(minForFit)
	{
	}

	template <typename TDataItem>
	std::vector<TDataItem> runWithModel(const std::vector<TDataItem>& data, Model<TDataItem>* model)
	{
		size_t bestScore = 0;
		auto pBestinliers = std::make_unique<std::vector<TDataItem>>();
		while(m_iterations > 0)
		{
			auto pAlsoinliers = std::make_unique<std::vector<TDataItem>>();
			model->buildModel(data);
			for(auto item : data)
			{
				double err = model->calculateError(item);
				if(err < m_threshold)
				{
					pAlsoinliers->push_back(item);
				}
			}
			if(pAlsoinliers->size() > bestScore)
			{
				bestScore = pAlsoinliers->size();
				pBestinliers.swap(pAlsoinliers);
			}	
			--m_iterations;
		}
		if(pBestinliers->size() >= m_minForFit)
			return std::move(*pBestinliers);

		return{};
	}

private:
	
	int m_iterations = 0;
	double m_threshold = 0;
	int m_minForFit = 0;

};
