#include <iostream>
#include <thread>
#include "LFrl.Common/src/QuickRng.h"
#include "LFrl.Common/src/diagnostics/IMeasurable.h"
#include "LFrl.Common/src/diagnostics/IRepeatMeasurable.h"
#include "LFrl.Common/src/diagnostics/Stopwatch.h"
#include "LFrl.Common/src/utils/is_iterable.h"
#include "LFrl.Common/src/utils/reverse.h"
#include "LFrl.Common/src/memory/array_ptr.h"
#include "LFrl.OGL/src/primitives/primitives.h"
#include "LFrl.CG.Core/src/math/vector_typedefs.h"
#include "LFrl.CG.Core/src/math/LineSegment3.h"

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
	std::vector<int> vvvv;

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

	return 0;
}
