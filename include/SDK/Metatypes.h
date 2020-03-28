#ifndef _MEEGA_SDK_Q_METATYPES_H_
#define _MEEGA_SDK_Q_METATYPES_H_

#include <Engine/Core/Ray.h>
#include <Engine/Core/Vec.h>
#include <Engine/Core/Color.h>
#include <Engine/Core/Matrix4x4.h>
#include <Engine/Core/Transform.h>

#include <QtCore/QMetaType>

Q_DECLARE_METATYPE(Engine::RGB_8)
Q_DECLARE_METATYPE(Engine::RGBA_8)
Q_DECLARE_METATYPE(Engine::RGB_F32)
Q_DECLARE_METATYPE(Engine::RGBA_F32)
Q_DECLARE_METATYPE(Engine::GRAY_8)
Q_DECLARE_METATYPE(Engine::GRAY_ALPHA_8)
Q_DECLARE_METATYPE(Engine::GRAY_F32)
Q_DECLARE_METATYPE(Engine::GRAY_ALPHA_F32)

Q_DECLARE_METATYPE(Engine::mat4x4)

Q_DECLARE_METATYPE(Engine::Ray3)
Q_DECLARE_METATYPE(Engine::Ray4)

Q_DECLARE_METATYPE(Engine::Transform)

Q_DECLARE_METATYPE(Engine::vec3)
Q_DECLARE_METATYPE(Engine::vec4)

#endif // !_MEEGA_SDK_Q_METATYPES_H_