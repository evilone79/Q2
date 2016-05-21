#pragma once

#include <memory>
#include "Model.h"
#include <vector>

template <typename TDataItem>
class RunStatistics
{
	std::unique_ptr<std::vector<TDataItem>> m_pAlsoinliers;
	std::vector<TDataItem> m_originItems;
	size_t m_bestIndex;

public:
	RunStatistics(std::unique_ptr<std::vector<TDataItem>>&& alsoinliers, const std::vector<TDataItem>& origin_items, size_t bestIdx)
		: m_pAlsoinliers(std::move(alsoinliers)),
		  m_originItems(origin_items), m_bestIndex(bestIdx)
	{
	}

	RunStatistics(RunStatistics&& other)
		: m_pAlsoinliers(std::move(other.m_pAlsoinliers)),
		  m_originItems(std::move(other.m_originItems)),
		  m_bestIndex(other.m_bestIndex)
	{
	}

	RunStatistics& operator=(RunStatistics&& other)
	{
		if (this == &other)
			return *this;
		m_pAlsoinliers = std::move(other.m_pAlsoinliers);
		m_originItems = std::move(other.m_originItems);
		m_bestIndex = other.m_bestIndex;
		return *this;
	}

	const std::vector<TDataItem>& alsoinliers() const
	{
		return *m_pAlsoinliers;
	}

	const std::vector<TDataItem>& origin_items() const
	{
		return m_originItems;
	}

	size_t best_index() const
	{
		return m_bestIndex;
	}
};

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
	RunStatistics<TDataItem> runWithModel(const std::vector<TDataItem>& data, Model<TDataItem>* model)
	{
		size_t bestScore = 0;		
		auto pBestinliers = std::make_unique<std::vector<TDataItem>>();
		decltype(model->getOriginItems()) origins;
		while(m_iterations > 0)
		{
			auto pAlsoinliers = std::make_unique<std::vector<TDataItem>>();
			model->buildModel(data);
			for(auto item : data)
			{
				double err = model->calculateError(item);
				if(err > 0.0 && err < m_threshold)
				{
					pAlsoinliers->push_back(item);
				}
			}
			if(pAlsoinliers->size() > bestScore)
			{
				bestScore = pAlsoinliers->size();
				pBestinliers = std::move(pAlsoinliers);
				origins = model->getOriginItems();				
			}	
			--m_iterations;				
		}
		if(pBestinliers->size() >= m_minForFit)
			return RunStatistics<TDataItem>{std::move(pBestinliers), origins, 0};

		return RunStatistics<TDataItem>{std::make_unique<std::vector<TDataItem>>(), origins, 0};
	}

private:
	
	int m_iterations = 0;
	double m_threshold = 0;
	int m_minForFit = 0;

};
