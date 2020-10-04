#ifndef __LFRL_COMMON_QUICK_RNG_GUARD__
#define __LFRL_COMMON_QUICK_RNG_GUARD__

#include <ctime>
#include <limits>
#include "memory/array_ptr.h"

BEGIN_LFRL_NAMESPACE

class QuickRng
{
public:
	QuickRng(QuickRng const&) noexcept = default;
	QuickRng(QuickRng&&) noexcept = default;
	~QuickRng() noexcept = default;
	QuickRng& operator= (QuickRng const&) noexcept = default;
	QuickRng& operator= (QuickRng&&) noexcept = default;

	QuickRng() noexcept;
	explicit QuickRng(u32 seed) noexcept;

	u32 GetSeed() const noexcept;
	void SetSeed(u32 seed) noexcept;

	u32 NextUint32() noexcept;
	u32 NextUint32(u32 max) noexcept;
	u32 NextUint32(u32 min, u32 max) noexcept;

	u64 NextUint64() noexcept;
	u64 NextUint64(u64 max) noexcept;
	u64 NextUint64(u64 min, u64 max) noexcept;

	i32 NextInt32() noexcept;
	i32 NextInt32(i32 max) noexcept;
	i32 NextInt32(i32 min, i32 max) noexcept;

	i64 NextInt64() noexcept;
	i64 NextInt64(i64 max) noexcept;
	i64 NextInt64(i64 min, i64 max) noexcept;

	u8 NextByte() noexcept;
	bool NextBool() noexcept;

	f32 NextFloat() noexcept;
	f64 NextDouble() noexcept;

	void NextByteRange(array_ptr<u8> buffer);
	void NextByteRange(u8* buffer, sz count);

private:
	u32 _seed;
	u32 _Next() noexcept;
};

END_LFRL_NAMESPACE

#endif
