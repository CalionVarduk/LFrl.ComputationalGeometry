#ifndef __LFRL_OGL_VERTEX_ARRAY_OBJECT_GUARD__
#define __LFRL_OGL_VERTEX_ARRAY_OBJECT_GUARD__

#include <array>
#include "../ObjectState.h"
#include "LFrl.Common/src/utils/requires.h"
#include "LFrl.Common/src/utils/dynamic_buffer.h"

BEGIN_LFRL_OGL_NAMESPACE

struct VertexArrayObject final
{
	enum struct ActionResult
	{
		OK = 0,
		ALREADY_INITIALIZED = 1,
		ARRAY_GEN_FAILURE = 2,
		ALREADY_DISPOSED = 3,
		NOT_READY = 4
	};

	static void Bind(GLuint id);
	static void Unbind() { Bind(NULL); }
	static GLuint GetBoundId();
	static bool IsAnyBound() { return GetBoundId() != NULL; }

	template <class TIter, LFRL_COMMON::requires<std::is_same<typename std::iterator_traits<TIter>::value_type, VertexArrayObject*>::value> = 0>
	static void InitializeRange(TIter begin, TIter end);

	template <GLuint count, LFRL_COMMON::requires<!(count <= 0)> = 0>
	static void InitializeRange(std::array<VertexArrayObject*, count>& arrays);

	template <class TIter, LFRL_COMMON::requires<std::is_same<typename std::iterator_traits<TIter>::value_type, VertexArrayObject*>::value> = 0>
	static void DisposeRange(TIter begin, TIter end);

	template <GLuint count, LFRL_COMMON::requires<!(count <= 0)> = 0>
	static void DisposeRange(std::array<VertexArrayObject*, count>& arrays);

	VertexArrayObject(VertexArrayObject const&) = delete;
	VertexArrayObject(VertexArrayObject&&) = default;
	VertexArrayObject& operator=(VertexArrayObject const&) = delete;
	VertexArrayObject& operator=(VertexArrayObject&&) = default;

	VertexArrayObject() noexcept;
	~VertexArrayObject() { Dispose(); }

	GLuint GetId() const noexcept { return _id; }
	ObjectState GetState() const noexcept { return _state; }

	ActionResult Initialize();

	void Bind() { Bind(_id); }
	bool IsBound() const { return GetBoundId() == _id; }

	ActionResult Dispose();

private:
	GLuint _id;
	ObjectState _state;
};

template <class TIter, LFRL_COMMON::requires<std::is_same<typename std::iterator_traits<TIter>::value_type, VertexArrayObject*>::value>>
void VertexArrayObject::InitializeRange(TIter begin, TIter end)
{
	auto count = 0;
	for (auto cur = begin; cur != end; ++cur)
		++count;

	if (count <= 0)
		return;

	LFRL_COMMON::dynamic_buffer<GLuint> ids(count);
	glGenVertexArrays(count, ids.data());

	count = 0;
	for (auto current = begin; current != end; ++current, ++count)
	{
		current->_id = ids[count];
		current->_state = current->_id == 0 ? ObjectState::INIT_FAILURE : ObjectState::READY;
	}
}

template <GLuint count, LFRL_COMMON::requires<!(count <= 0)>>
void VertexArrayObject::InitializeRange(std::array<VertexArrayObject*, count>& arrays)
{
	std::array<GLuint, count> ids;
	glGenVertexArrays(count, ids.data());

	for (GLsizei i = 0; i < count; ++i)
	{
		arrays[i]->_id = ids[i];
		arrays[i]->_state = arrays[i]->_id == 0 ? ObjectState::INIT_FAILURE : ObjectState::READY;
	}
}

template <class TIter, LFRL_COMMON::requires<std::is_same<typename std::iterator_traits<TIter>::value_type, VertexArrayObject*>::value>>
void VertexArrayObject::DisposeRange(TIter begin, TIter end)
{
	auto count = 0;
	for (auto cur = begin; cur != end; ++cur)
		++count;

	if (count <= 0)
		return;

	LFRL_COMMON::dynamic_buffer<GLuint> ids(count);

	count = 0;
	for (auto current = begin; current != end; ++current, ++count)
	{
		ids[count] = current->_id;
		current->_id = 0;
		current->_state = ObjectState::DISPOSED;
	}
	glDeleteVertexArrays(ids.size(), ids.data());
}

template <GLuint count, LFRL_COMMON::requires<!(count <= 0)>>
void VertexArrayObject::DisposeRange(std::array<VertexArrayObject*, count>& arrays)
{
	std::array<GLuint, count> ids;

	for (GLsizei i = 0; i < count; ++i)
	{
		ids[i] = arrays[i]->_id;
		arrays[i]->_id = 0;
		arrays[i]->_state = ObjectState::DISPOSED;
	}
	glDeleteVertexArrays(count, ids.data());
}

END_LFRL_OGL_NAMESPACE

#endif
