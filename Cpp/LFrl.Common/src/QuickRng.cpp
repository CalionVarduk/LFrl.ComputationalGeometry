#include "QuickRng.h"

using namespace LFRLCOMMON;

QuickRng::QuickRng() noexcept
	: _seed(0)
{
	SetSeed(0);
}

QuickRng::QuickRng(u32 seed) noexcept
	: _seed(0)
{
	SetSeed(seed);
}

u32 QuickRng::GetSeed() const noexcept
{
	return _seed;
}

void QuickRng::SetSeed(u32 v) noexcept
{
	if (v == 0)
	{
		auto t = time(nullptr);
		_seed = (u32)(t * (u64)(this - 1) * (u64)(&v - 1) * (u64)(&t - 1));
		if (_seed == 0)
			_seed = (u32)t;
	}
	else
		_seed = v;
}

u32 QuickRng::NextUint32() noexcept
{
	return _Next();
}

u32 QuickRng::NextUint32(u32 max) noexcept
{
	return _Next() % max;
}

u32 QuickRng::NextUint32(u32 min, u32 max) noexcept
{
	return _Next() % (max - min) + min;
}

u64 QuickRng::NextUint64() noexcept
{
	return (u64)_Next() | ((u64)_Next() << 32);
}

u64 QuickRng::NextUint64(u64 max) noexcept
{
	return NextUint64() % max;
}

u64 QuickRng::NextUint64(u64 min, u64 max) noexcept
{
	return NextUint64() % (max - min) + min;
}

i32 QuickRng::NextInt32() noexcept
{
	return (i32)NextUint32();
}

i32 QuickRng::NextInt32(i32 max) noexcept
{
	return (i32)NextUint32((u32)max);
}

i32 QuickRng::NextInt32(i32 min, i32 max) noexcept
{
	return (i32)NextUint32((u32)min, (u32)max);
}

i64 QuickRng::NextInt64() noexcept
{
	return (i64)NextUint64();
}

i64 QuickRng::NextInt64(i64 max) noexcept
{
	return (i64)NextUint64((u64)max);
}

i64 QuickRng::NextInt64(i64 min, i64 max) noexcept
{
	return (i64)NextUint64((u64)min, (u64)max);
}

u8 QuickRng::NextByte() noexcept
{
	return (u8)_Next();
}

bool QuickRng::NextBool() noexcept
{
	return (_Next() & 1) == 1;
}

f32 QuickRng::NextFloat() noexcept
{
	return (f32)_Next() / std::numeric_limits<u32>::max();
}

f64 QuickRng::NextDouble() noexcept
{
	return (f64)_Next() / std::numeric_limits<u32>::max();
}

void QuickRng::NextByteRange(array_ptr<u8> buffer)
{
	return NextByteRange(buffer.begin(), buffer.size());
}

void QuickRng::NextByteRange(u8* buffer, u32 count)
{
	if (buffer == nullptr || count <= 0)
		return;

	auto full_block_count = count >> 2;
	auto last_block_size = count & 3;

	for (u32 i = 0; i < full_block_count; ++i)
	{
		auto v = _Next();
		memcpy(buffer, &v, 4);
		buffer += 4;
	}
	if (last_block_size > 0)
	{
		auto v = _Next();
		memcpy(buffer, &v, last_block_size);
	}
}

u32 QuickRng::_Next() noexcept
{
	_seed ^= _seed << 13;
	_seed ^= _seed >> 17;
	_seed ^= _seed << 5;
	return _seed;
}