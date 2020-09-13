#ifndef __LFRL_COMMON_REPEAT_MEASURABLE_GUARD__
#define __LFRL_COMMON_REPEAT_MEASURABLE_GUARD__

#include <vector>
#include <atomic>
#include "duration_snapshot.h"

BEGIN_LFRLCOMMON_NAMESPACE

struct measurement_result final
{
	const duration_snapshot preparation;
	const duration_snapshot invocation;
	const duration_snapshot teardown;
	const duration_snapshot full;
};

struct measurement_aggregation_result final
{
	const convertible_duration preparation;
	const convertible_duration invocation;
	const convertible_duration teardown;
	const convertible_duration full;
};

struct measurement_range_result final
{
	const duration_snapshot full;
	const std::vector<measurement_result> results;

	measurement_aggregation_result get_sum() const;
	measurement_aggregation_result get_average() const;
};

struct IRepeatMeasurable
{
	IRepeatMeasurable(IRepeatMeasurable const&) = delete;
	IRepeatMeasurable(IRepeatMeasurable&&) = delete;
	IRepeatMeasurable& operator=(IRepeatMeasurable const&) = delete;
	IRepeatMeasurable& operator=(IRepeatMeasurable&&) = delete;

	virtual ~IRepeatMeasurable() = default;

	bool IsRunning() const noexcept { return _isRunning.load(); }
	measurement_range_result Measure(u32 count) noexcept(false);

protected:
	IRepeatMeasurable() noexcept;

	virtual void OnStarting(u32 count) {}
	virtual convertible_duration::duration Prepare(u32 index, u32 count) { return convertible_duration::duration::zero(); }
	virtual convertible_duration::duration Invoke(u32 index, u32 count) = 0;
	virtual convertible_duration::duration Teardown(u32 index, u32 count, duration_snapshot invocationMeasurement) { return convertible_duration::duration::zero(); }
	virtual void OnFinished(std::vector<measurement_result> const& results) {}

private:
	std::atomic_bool _isRunning;
};

END_LFRLCOMMON_NAMESPACE

#endif
