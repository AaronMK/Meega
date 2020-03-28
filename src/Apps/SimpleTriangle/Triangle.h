#ifndef _TRIANGLE_H_
#define _TRIANGLE_H_

#include <Engine/Memory/VertexBufferObject.h>
#include <Engine/Memory/VertexArrayObject.h>
#include <Engine/DevSupport/Property.h>
#include <Engine/Camera/Camera.h>
#include <Engine/Core/Color.h>

#include <SDK/DevObject.h>

#include <AppsCommon/BasicShader.h>

class Triangle : public MeegaSDK::DevObject
{
public:
	Triangle();
	virtual ~Triangle();

	void draw(const Engine::Camera &camera);

private:
	bool mDirty;

	Engine::RGB_F32 mColor;

	Engine::VBO mVerts;
	Engine::VAO mVoa;

	AppsCommon::BasicShader mShader;

#ifdef ENGINE_DEVELOPMENT_SUPPORT
	Q_OBJECT
public:
	virtual QWidget* makePropertiesWidget() override;
	Engine::Property<Engine::RGB_F32> color;

signals:
	void colorChanged(Engine::RGBA_F32 color);

private:
	void onColorEdited(Engine::RGBA_F32 color);

#endif // ENGINE_DEVELOPMENT_SUPPORT
};

#endif // _TRIANGLE_H_