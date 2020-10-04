#ifndef __LFRL_OGL_CACHED_TIMER_QUERY_GUARD__
#define __LFRL_OGL_CACHED_TIMER_QUERY_GUARD__

#include "TimerQuery.h"

BEGIN_LFRL_OGL_NAMESPACE

template <GLuint size>
struct CachedTimerQuery final
{
	static_assert(size > 0, "CachedTimerQuery<size>: size must be greater than 0.");

	static constexpr GLuint Size = size;

	CachedTimerQuery(CachedTimerQuery<size> const&) = delete;
	CachedTimerQuery<size>& operator=(CachedTimerQuery<size> const&) = delete;

	CachedTimerQuery() noexcept;
	CachedTimerQuery(CachedTimerQuery<size>&&) noexcept;
	CachedTimerQuery<size>& operator=(CachedTimerQuery<size>&&) noexcept;
	~CachedTimerQuery() { Dispose(); }

	TimerQuery const& GetTimer() const noexcept { return _timer; }
	GLuint GetLength() const noexcept { return _length; }
	GLdouble GetAverageElapsedTimeNs() const noexcept { return _length == 0 ? 0.0 : _cacheTotalNs / static_cast<GLdouble>(_length); }
	std::chrono::duration<GLdouble, std::chrono::nanoseconds::period> GetAverageElapsedTime() const noexcept;
	GLuint64 GetElapsedTimeNs(GLint offset) const;
	std::chrono::duration<GLuint64, std::chrono::nanoseconds::period> GetElapsedTime(GLint offset) const;

	TimerQuery::ActionResult Initialize() { return _timer.Initialize(); }

	bool IsRunning() const { return _timer.IsRunning(); }
	void Reset();
	void Begin() { _timer.Begin(); }
	void End();

	TimerQuery::ActionResult Dispose() { return _timer.Dispose(); }

private:
	TimerQuery _timer;
	GLuint _length;
	GLuint _index;
	GLuint64 _cacheNs[size];
	GLuint64 _cacheTotalNs;
};

template <GLuint size>
CachedTimerQuery<size>::CachedTimerQuery() noexcept
	: _timer(), _length(0), _index(0), _cacheNs(), _cacheTotalNs(0)
{
	std::memset(_cacheNs, 0, sizeof(_cacheNs));
}

template <GLuint size>
CachedTimerQuery<size>::CachedTimerQuery(CachedTimerQuery<size>&& other) noexcept
	: _timer(), _length(0), _index(0), _cacheNs(), _cacheTotalNs(0)
{
	std::memset(_cacheNs, 0, sizeof(_cacheNs));

	std::swap(_timer, other._timer);
	std::swap(_length, other._length);
	std::swap(_index, other._index);
	std::swap(_cacheNs, other._cacheNs);
	std::swap(_cacheTotalNs, other._cacheTotalNs);
}

template <GLuint size>
CachedTimerQuery<size>& CachedTimerQuery<size>::operator= (CachedTimerQuery<size>&& other) noexcept
{
	if (this != &other)
	{
		std::swap(_timer, other._timer);
		std::swap(_length, other._length);
		std::swap(_index, other._index);
		std::swap(_cacheNs, other._cacheNs);
		std::swap(_cacheTotalNs, other._cacheTotalNs);
	}
	return *this;
}

template <GLuint size>
std::chrono::duration<GLdouble, std::chrono::nanoseconds::period> CachedTimerQuery<size>::GetAverageElapsedTime() const noexcept
{
	return std::chrono::duration<GLdouble, std::chrono::nanoseconds::period>(GetAverageElapsedTimeNs());
}

template <GLuint size>
GLuint64 CachedTimerQuery<size>::GetElapsedTimeNs(GLint offset) const
{
	if (_length == 0)
		return 0;

	offset = (static_cast<GLint>(_index) - offset - 1) % _length;
	if (offset < 0)
		offset += _length;

	return _cacheNs[offset];
}

template <GLuint size>
std::chrono::duration<GLuint64, std::chrono::nanoseconds::period> CachedTimerQuery<size>::GetElapsedTime(GLint offset) const
{
	return std::chrono::duration<GLuint64, std::chrono::nanoseconds::period>(GetElapsedTimeNs(offset));
}

template <GLuint size>
void CachedTimerQuery<size>::Reset()
{
	_timer.Reset();
	_length = 0;
	_index = 0;
	_cacheTotalNs = 0;
	std::memset(_cacheNs, 0, sizeof(_cacheNs));
}

template <GLuint size>
void CachedTimerQuery<size>::End()
{
	_timer.End();
	_cacheTotalNs -= _cacheNs[_index];
	_cacheNs[_index] = _timer.GetLastElapsedTimeNs();
	_cacheTotalNs += _cacheNs[_index];
	if (++_index == size)
		_index = 0;
	if (_length < size)
		++_length;
}

END_LFRL_OGL_NAMESPACE

#endif
