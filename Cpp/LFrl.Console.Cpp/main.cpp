#include <iostream>
#include <thread>
#include "LFrl.Common/src/QuickRng.h"
#include "LFrl.Common/src/diagnostics/IMeasurable.h"
#include "LFrl.Common/src/diagnostics/IRepeatMeasurable.h"
#include "LFrl.Common/src/diagnostics/Stopwatch.h"
#include "LFrl.Common/src/utils/is_iterable.h"
#include "LFrl.Common/src/utils/reverse.h"
#include "LFrl.Common/src/memory/array_ptr.h"
#include "LFrl.Common/src/collections/filtered.h"
#include "LFrl.OGL/src/primitives/primitives.h"
#include "LFrl.CG.Core/src/algorithms/Utility.h"
#include "LFrl.CG.Core/src/algorithms/convex_hull/ConvexHullGraham.h"
#include "LFrl.CG.Core/src/algorithms/convex_hull/ConvexHullJarvis.h"
#include "LFrl.CG.Core/src/algorithms/convex_hull/ConvexHullNaive.h"
#include "LFrl.CG.Core/src/algorithms/convex_hull/ConvexHullQuick.h"

using namespace LFRL;
using namespace LFRL_OGL;
using namespace LFRL_CG;

u64 ans = 0;

class TestMeasure : public IMeasurable
{
protected:
	virtual convertible_duration Invoke() override
	{
		StopWatch watch;
		watch.Start();

		auto c = _rng.NextUint32(4999999, 5000002);
		for (u32 i = 0; i < c; ++i)
			ans = _rng.NextUint64();

		return watch.GetElapsedConvertibleTime();
	}

private:
	QuickRng _rng;
};

class TestRepeatMeasure : public IRepeatMeasurable
{
protected:
	virtual convertible_duration::duration Invoke(u32, u32) override
	{
		StopWatch watch;
		watch.Start();

		auto c = 1U;
		for (u32 i = 0; i < c; ++i)
			ans = _rng.NextUint64();

		return watch.GetElapsedTime();
	}

private:
	QuickRng _rng;
};

int main()
{
	auto lamb = [](Vec2I const& a) -> bool { return a.x > 8; };
	std::vector<Vec2I> vvvv = { {1,1}, {2,2}, {3,3}, {5,5}, {8,8}, {13,13}, {21,21}, {14,14}, {9,9}, {6,6}, {4,4}, {3,3}, {2,2}, {0,0} };
	auto vvvvf = filter(vvvv, lamb);
	auto x = vvvvf.begin();
	const auto vvvvit = filter(vvvv.begin(), vvvv.end(), lamb);
	auto dist = std::distance(vvvvit, vvvvit.filter_end());

	for (auto iiit = vvvvit; iiit != vvvv.end(); ++iiit)
		std::cout << iiit->x << ' ' << iiit->y << std::endl;

	for (auto& iiit : vvvvf)
		std::cout << iiit.x << ' ' << iiit.y << std::endl;

	const auto vvvvitrev = filter(vvvv.rbegin(), vvvv.rend(), lamb);
	auto dist2 = std::distance(vvvvitrev, vvvv.rend());

	for (auto iiit = vvvvitrev; iiit != vvvv.rend(); ++iiit)
		std::cout << iiit->x << ' ' << iiit->y << std::endl;

	auto yit = filter(&vvvv.front(), &vvvv.back() + 1, lamb);
	auto ydist = std::distance(yit, yit.filter_end());

	for (auto iiit = yit; iiit != yit.end(); ++iiit)
		std::cout << iiit->x << ' ' << iiit->y << std::endl;

	std::vector<Vec2F> points = { { -1.0f, -1.0f }, { 0.5f, -0.5f }, { 1.0f, -1.0f }, { 0.0f, 0.0f }, { -1.0f, 1.0f }, { 1.0f, 1.0f } };
	ConvexHullGraham<float> graham;
	ConvexHullJarvis<float> jarvis;
	ConvexHullNaive<float> naive;
	auto arrayP = array_ptr<Vec2F>(&points.front(), &points.back() + 1);

	auto grahamResult = graham.Run(arrayP);
	auto jarvisResult = jarvis.Run(arrayP);
	auto naiveResult = naive.Run(arrayP);

	ConvexHullQuick<float> quick;
	std::vector<Vec2F> pointsQ = {
		{ -46.0f, -123.0f }, //A
		{ -99.0f, -70.0f }, //B
		{ -67.0f, -92.0f }, //C
		{ -102.0f, -65.0f }, //D
		{ -91.0f, -114.0f }, //E
		{ -106.0f, 0.0f }, //F
		{ 70.0f, -120.0f }, //H
		{ 82.0f, -112.0f }, //J
		{ 56.0f, -124.0f }, //K
		{ -2.0f, -68.0f }, //L
		{ 10.0f, -128.0f }, //M
		{ 45.0f, -39.0f }, //N
		{ 113.0f, 3.0f } // W
	};

	auto quickResult = quick.Run(array_ptr<Vec2F>(&pointsQ.front(), &pointsQ.back() + 1));

	auto iter = is_iterable<std::vector<int>>::value;
	auto iter_of = is_iterable_of<std::vector<int>, int>::value;
	auto iter2 = is_iterable<array_ptr<int>>::value;
	auto iter_of2 = is_iterable_of<array_ptr<int>, int>::value;
	auto riter = is_iterable_of<reverse<std::vector<int>>, int>::value;

	TestMeasure m;
	auto d = m.Measure();
	auto dms = d.get_ms();
	auto dns = d.get_ns();
	auto dmsd = d.get_as<double, std::chrono::milliseconds::period>();
	auto avg = dns / 5000000;
	std::cout << ans << std::endl;
	TestRepeatMeasure rm;
	auto rd = rm.Measure(5000);
	auto rdms = rd.get_sum();
	auto rdns = rd.get_average();
	//auto rdmsd = d.get_as<double, std::chrono::milliseconds::period>();

	Vec2F v2;
	Vector<float, 4> v4;

	v4.Add(7);
	v2.Sub(3);

	auto v3 = vector_type_cast<double>(v2);

	Seg2F s2;
	auto s3 = line_segment_type_cast<double>(s2);

	return 0;
}
