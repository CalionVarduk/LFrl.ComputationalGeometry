#ifndef __LFRL_OGL_CAPACITIES_MACROS_GUARD__
#define __LFRL_OGL_CAPACITIES_MACROS_GUARD__

#define __LFRL_OGL_DEFINE_CAPACITY_GETTER(CNAME, CTYPE, GL_ENUM, GL_TYPE, GL_GET_FUNC_NAME)\
inline CTYPE CNAME() noexcept { GL_TYPE result; GL_GET_FUNC_NAME(GL_ENUM, &result); return static_cast<CTYPE>(result); }

#define __LFRL_OGL_DEFINE_TOGGLE_CAPACITY_SETTER(VALUE)\
if (VALUE) Enable(); \
else Disable();

#define LFRL_OGL_DEFINE_CAPACITY_GETTER_I32(CNAME, CTYPE, GL_ENUM)\
__LFRL_OGL_DEFINE_CAPACITY_GETTER(Get##CNAME, CTYPE, GL_ENUM, GLint, glGetIntegerv)

#define LFRL_OGL_DEFINE_CAPACITY_GETTER_F32(CNAME, CTYPE, GL_ENUM)\
__LFRL_OGL_DEFINE_CAPACITY_GETTER(Get##CNAME, CTYPE, GL_ENUM, GLfloat, glGetFloatv)

#define LFRL_OGL_DEFINE_CAPACITY_GETTER_F64(CNAME, CTYPE, GL_ENUM)\
__LFRL_OGL_DEFINE_CAPACITY_GETTER(Get##CNAME, CTYPE, GL_ENUM, GLdouble, glGetDoublev)

#define LFRL_OGL_DEFINE_CAPACITY_GETTER_BOOL(CNAME, GL_ENUM)\
__LFRL_OGL_DEFINE_CAPACITY_GETTER(CNAME, bool, GL_ENUM, GLboolean, glGetBooleanv)

#define LFRL_OGL_DEFINE_BOOL_CAPACITY_FUNCTIONS(GL_ENUM)\
inline bool IsEnabled() noexcept { return static_cast<bool>(glIsEnabled(GL_ENUM)); } \
inline void Enable() noexcept { glEnable(GL_ENUM); } \
inline void Disable() noexcept { glDisable(GL_ENUM); }

#define LFRL_OGL_DEFINE_CAPACITY_SNAPSHOT_STRUCT(CNAME, CTYPE, CDEFAULT_VALUE, VALUE_GETTER, VALUE_SETTER)\
struct CNAME##Snapshot final { \
static CNAME##Snapshot Load() noexcept { \
CNAME##Snapshot result; \
result.value = VALUE_GETTER(); \
return result; \
} \
CTYPE value; \
CNAME##Snapshot() noexcept : value(CDEFAULT_VALUE) {} \
CNAME##Snapshot(CNAME##Snapshot const&) = default; \
CNAME##Snapshot(CNAME##Snapshot&&) = default; \
CNAME##Snapshot& operator= (CNAME##Snapshot const&) = default; \
CNAME##Snapshot& operator= (CNAME##Snapshot&&) = default; \
void Apply() noexcept { \
VALUE_SETTER(value); \
} \
}

#define LFRL_OGL_DEFINE_BOOL_CAPACITY_SNAPSHOT_STRUCT(CNAME, GL_ENUM, CDEFAULT_VALUE)\
LFRL_OGL_DEFINE_BOOL_CAPACITY_FUNCTIONS(GL_ENUM) \
LFRL_OGL_DEFINE_CAPACITY_SNAPSHOT_STRUCT(CNAME, bool, CDEFAULT_VALUE, IsEnabled, __LFRL_OGL_DEFINE_TOGGLE_CAPACITY_SETTER)

#define LFRL_OGL_DEFINE_TOGGLE_CAPACITY_SNAPSHOT_STRUCT(GL_ENUM, CDEFAULT_VALUE)\
LFRL_OGL_DEFINE_BOOL_CAPACITY_SNAPSHOT_STRUCT(Toggle, GL_ENUM, CDEFAULT_VALUE)

#define LFRL_OGL_DECLARE_COMPLEX_CAPACITY_SNAPSHOT_STRUCT(...)\
struct Snapshot final { \
static Snapshot Load() noexcept; \
__VA_ARGS__ \
Snapshot() noexcept; \
Snapshot(Snapshot const&) = default; \
Snapshot(Snapshot&&) = default; \
Snapshot& operator= (Snapshot const&) = default; \
Snapshot& operator= (Snapshot&&) = default; \
void Apply() noexcept; \
}

#endif
