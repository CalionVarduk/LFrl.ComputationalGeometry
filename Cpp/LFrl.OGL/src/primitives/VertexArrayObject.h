#ifndef __LFRL_OGL_VERTEX_ARRAY_OBJECT_GUARD__
#define __LFRL_OGL_VERTEX_ARRAY_OBJECT_GUARD__

#include <array>
#include "LFrl.Common/src/utils/requires.h"
#include "LFrl.Common/src/utils/is_iterable.h"
#include "LFrl.Common/src/utils/dynamic_buffer.h"
#include "../ObjectState.h"

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

	template <class TIterable, LFRL::requires<LFRL::is_iterable_of<TIterable, VertexArrayObject*>::value> = 0>
	static void InitializeRange(TIterable const& iterable);

	template <GLuint count, LFRL::requires<!(count <= 0)> = 0>
	static void InitializeRange(std::array<VertexArrayObject*, count>& arrays);

	template <class TIterable, LFRL::requires<LFRL::is_iterable_of<TIterable, VertexArrayObject*>::value> = 0>
	static void DisposeRange(TIterable const& iterable);

	template <GLuint count, LFRL::requires<!(count <= 0)> = 0>
	static void DisposeRange(std::array<VertexArrayObject*, count>& arrays);

	VertexArrayObject(VertexArrayObject const&) = delete;
	VertexArrayObject& operator=(VertexArrayObject const&) = delete;

	VertexArrayObject() noexcept;
	VertexArrayObject(VertexArrayObject&&) noexcept;
	VertexArrayObject& operator=(VertexArrayObject&&) noexcept;
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

template <class TIterable, LFRL::requires<LFRL::is_iterable_of<TIterable, VertexArrayObject*>::value>>
void VertexArrayObject::InitializeRange(TIterable const& iterable)
{
	auto count = 0;
	for (auto current = iterable.begin(); current != iterable.end(); ++current)
		++count;

	if (count <= 0)
		return;

	LFRL::dynamic_buffer<GLuint> ids(count);
	glGenVertexArrays(count, ids.data());

	count = 0;
	for (auto current = iterable.begin(); current != iterable.end(); ++current, ++count)
	{
		current->_id = ids[count];
		current->_state = current->_id == 0 ? ObjectState::INIT_FAILURE : ObjectState::READY;
	}
}

template <GLuint count, LFRL::requires<!(count <= 0)>>
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

template <class TIterable, LFRL::requires<LFRL::is_iterable_of<TIterable, VertexArrayObject*>::value>>
void VertexArrayObject::DisposeRange(TIterable const& iterable)
{
	auto count = 0;
	for (auto current = iterable.begin(); current != iterable.end(); ++current)
		++count;

	if (count <= 0)
		return;

	LFRL::dynamic_buffer<GLuint> ids(count);

	count = 0;
	for (auto current = iterable.begin(); current != iterable.end(); ++current, ++count)
	{
		ids[count] = current->_id;
		current->_id = 0;
		current->_state = ObjectState::DISPOSED;
	}
	glDeleteVertexArrays(ids.size(), ids.data());
}

template <GLuint count, LFRL::requires<!(count <= 0)>>
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
