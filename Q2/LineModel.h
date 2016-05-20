#pragma once

#include "Model.h"
#include "Point2d.h"
#include "ItemChoiceStrategy.h"
#include <memory>


class LineModel2D : public Model<Point2d>
{
public:

	LineModel2D(std::unique_ptr<ItemChoiceStrategy<Point2d>> point_chooser)
		: m_pointChooser(std::move(point_chooser))
	{
	}

	double calculateError(const Point2d& point) override
	{
		return calculateDistance(point);
	}

	void buildModel(const std::vector<Point2d>& data) override
	{
		//interested in exactly 2 points for this specific model
		auto chosen = m_pointChooser->chooseItems(data, 2); 
		m_p1 = chosen[0];
		m_p2 = chosen[1];
	}

private:

	//basic 2d line to point taken from Wikipedia
	double calculateDistance(const Point2d& p) const
	{
		double nom = (m_p2.Y - m_p1.Y)*p.X - (m_p2.X - m_p1.X)*p.Y + m_p2.X*m_p1.Y - m_p2.Y*m_p1.X;
		nom = std::abs(nom);
		double denom = std::sqrt(std::pow(m_p2.Y - m_p1.Y, 2) + std::pow(m_p2.X - m_p1.X, 2));
		_ASSERTE(denom > 0);
		return nom / denom;
	}
	std::unique_ptr<ItemChoiceStrategy<Point2d>> m_pointChooser;
	

	Point2d m_p1;
	Point2d m_p2;
};
