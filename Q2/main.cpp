
#include <iostream>
#include "RoadFinder.h"
#include "Point2d.h"
#include "LineModel.h"
#include "RandomChooser.h"

using namespace std;

int main()
{
	
	vector<Point2d> initialData{ {3.0,5.3},{ 3.1,5.0 },{ 2.8,5.6 } };
	RoadFinder roadFinder{100, 5.0, 50};
		
	auto model = make_unique<LineModel2D>(make_unique<RandomChooser<Point2d>>());
	auto inliners = roadFinder.runWithModel(initialData, model.get());
	cout << "Found " << inliners.size() << " inliners";	

	cin.get();
}