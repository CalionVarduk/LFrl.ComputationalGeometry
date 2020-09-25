#include "IRepeatMeasurable.h"

#include "Stopwatch.h"

BEGIN_LFRL_COMMON_NAMESPACE

measurement_aggregation_result __aggregate_results(std::vector<measurement_result> const& results)
{
	auto count = static_cast<u32>(results.size());

	auto preparation = convertible_duration::duration::zero();
	auto invocation = convertible_duration::duration::zero();
	auto teardown = convertible_duration::duration::zero();
	auto full = convertible_duration::duration::zero();

	for (u32 i = 0; i < count; ++i)
	{
		preparation += results[i].preparation.get_elapsed_time();
		invocation += results[i].invocation.get_elapsed_time();
		teardown += results[i].teardown.get_elapsed_time();
		full += results[i].full.get_elapsed_time();
	}
	return {
		convertible_duration(preparation),
		convertible_duration(invocation),
		convertible_duration(teardown),
		convertible_duration(full)
	};
}

measurement_aggregation_result measurement_range_result::get_sum() const
{
	return __aggregate_results(results);
}

measurement_aggregation_result measurement_range_result::get_average() const
{
	auto count = results.size();
	if (count == 0)
		return get_sum();

	auto result = __aggregate_results(results);
	return {
		convertible_duration(result.preparation.get() / count),
		convertible_duration(result.invocation.get() / count),
		convertible_duration(result.teardown.get() / count),
		convertible_duration(result.full.get() / count)
	};
}

measurement_range_result IRepeatMeasurable::Measure(u32 count) noexcept(false)
{
	if (_isRunning.exchange(true))
		throw std::runtime_error("measurable is already running");

	StopWatch mainWatch;
	StopWatch watch;

	mainWatch.Start();

	std::vector<measurement_result> results;

	OnStarting(count);

	for (u32 i = 0; i < count; ++i)
	{
		watch.Restart();

		auto calculator = duration_calculator();
		auto duration = Prepare(i, count);
		auto preparationMeasurement = duration_snapshot(calculator, calculator.get_start() + duration);

		calculator = duration_calculator();
		duration = Invoke(i, count);
		auto invocationMeasurement = duration_snapshot(calculator, calculator.get_start() + duration);

		calculator = duration_calculator();
		duration = Teardown(i, count, invocationMeasurement);
		auto teardownMeasurement = duration_snapshot(calculator, calculator.get_start() + duration);

		auto fullMeasurement = watch.CreateDurationSnapshot();

		measurement_result result = {
			preparationMeasurement,
			invocationMeasurement,
			teardownMeasurement,
			fullMeasurement
		};
		results.push_back(std::move(result));
	}

	OnFinished(results);

	_isRunning.store(false);
	return {
		mainWatch.CreateDurationSnapshot(),
		results
	};
}

IRepeatMeasurable::IRepeatMeasurable() noexcept
	: _isRunning(false)
{}

END_LFRL_COMMON_NAMESPACE
