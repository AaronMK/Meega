#include <SDK/Metatypes.h>

class MetaTypeRegister
{
public:
	MetaTypeRegister()
	{
		qRegisterMetaType<Engine::RGB_8>();
		qRegisterMetaType<Engine::RGBA_8>();
		qRegisterMetaType<Engine::RGB_F32>();
		qRegisterMetaType<Engine::RGBA_F32>();
		qRegisterMetaType<Engine::GRAY_8>();
		qRegisterMetaType<Engine::GRAY_ALPHA_8>();
		qRegisterMetaType<Engine::GRAY_F32>();
		qRegisterMetaType<Engine::GRAY_ALPHA_F32>();

		qRegisterMetaType<Engine::mat4x4>();
		
		qRegisterMetaType<Engine::Transform>();

		qRegisterMetaType<Engine::vec3>();
		qRegisterMetaType<Engine::vec4>();
	}
};
static MetaTypeRegister instMetaTypeRegister;