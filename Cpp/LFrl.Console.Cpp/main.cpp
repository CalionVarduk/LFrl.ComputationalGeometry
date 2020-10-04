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

using namespace LFRL_COMMON;
using namespace LFRL_OGL;

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

void scalingTest()
{
	auto Cc = glm::ivec2(1500, 314);
	auto Ac = glm::vec2(0.78125f, 0.64798f);
	auto Ob = glm::vec2(-200.58104, -199.60675);
	auto Os = glm::vec2(1280.0f, 594.66669f);
	auto S = glm::vec2(1.5f, 1.5f);
	auto Ps = Os * S;
	auto T = -Ob * S;
	auto C = Os * Ac + Ob;
	auto M = glm::identity<glm::mat4>();
	M = glm::translate(M, glm::vec3(T, 0.0f));
	M = glm::scale(M, glm::vec3(S, 1.0f));

	auto Sn = S + glm::vec2(0.125f, 0.125f);
	auto Tno = (Sn / S - 1.0f) * (T - Ac * Ps);
	auto Tn = T + Tno;

	auto Mn = glm::identity<glm::mat4>();
	Mn = glm::translate(Mn, glm::vec3(Tn, 0.0f));
	Mn = glm::scale(Mn, glm::vec3(Sn, 1.0f));
}

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


	scalingTest();


	return 0;
}
