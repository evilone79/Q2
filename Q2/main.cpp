
#include <iostream>
#include <fstream>
#include "RoadFinder.h"
#include "Point2d.h"
#include "LineModel.h"
#include "RandomChooser.h"
#include <string>
#include <boost/algorithm/string.hpp>

using namespace std;

class Dog
{
public:
	virtual void Bark()
	{
		cout << "Dog barks" << endl;
	}
};

class RedDog
{
public:
	virtual void Bark()
	{
		cout << "RedDog barks" << endl;
	}
};

vector<Point2d> readAllLines(const string& fileName)
{	
	std::ifstream ifs(fileName, ios::in);
	if (!ifs)
	{
		//string err = strerror((int)errno,);		
	}
	vector<Point2d> vec;
	string line;
	while (getline(ifs, line))
	{
		vector<string> split;
		boost::split(split, line, boost::is_any_of("{},"), boost::token_compress_off);
		vec.push_back(Point2d{std::stod(split[1]), std::stod(split[2])});
	}
	ifs.close();
	return vec;
}

int main()
{
	auto points = readAllLines("D:\\vs_projects\\Q2\\C2Tester\\bin\\Debug\\points.txt");
	/*for(auto& p: points)
	{
		cout << p.X << "," << p.Y << "\n";
	}*/
	/*vector<Point2d> initialData{ {3.0,5.3},{ 3.1,5.0 },{ 2.8,5.6 } };*/
	RoadFinder roadFinder{100, 10.0, 20};
		
	auto model = make_unique<LineModel2D>(make_unique<RandomChooser<Point2d>>());
	auto stats = roadFinder.runWithModel(points, model.get());
	cout << "Found " << stats.alsoinliers().size() << " inliners" << endl;	
	cout << "Origin points are " << stats.origin_items()[0] << " and " << stats.origin_items()[1];
	cin.get();
}