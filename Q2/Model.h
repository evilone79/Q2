#pragma once

#include <vector>

//interface for testing model. Initially designed to be mutable
template<typename TDataItem>
class Model
{
public:
	
	virtual double calculateError(const TDataItem& point) = 0;
	virtual void buildModel(const std::vector<TDataItem>& data) = 0;	
	virtual std::vector<TDataItem> getOriginItems() = 0;

};

