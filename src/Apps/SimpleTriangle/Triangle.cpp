#include "Triangle.h"

#ifdef ENGINE_DEVEOPMENT_SUPPORT
#	include <Engine/DevSupport/Widgets/QColorEdit.qt.h>
#endif

#include <Engine/Core/Vec.h>
#include <Engine/Timing/Timing.h>
#include <Engine/Tasking/Pipeline.h>

#include <functional>
#include <math.h>


using namespace Engine;

////////////////////////////////////

Triangle::Triangle()
	: DevObject(), mColor(1.0f, 1.0f, 1.0f),
	  mDirty(true)
{
#	ifdef ENGINE_DEVEOPMENT_SUPPORT
	setObjectName(QStringLiteral("Triangle"));

	color.setter = [this](RGB_F32 _color)
	{
		mColor = _color;
		mDirty = true;

		emit colorChanged(RGBA_F32(mColor));

		return mColor;
	};

	color.getter = [this]()
	{
		return mColor;
	};
#	endif // ENGINE_DEVEOPMENT_SUPPORT

	Render::enqueue([this]()
	{
		vec3 points[3];
		points[0] = vec3(0.0f, 0.8f, 0.0f);
		points[1] = vec3(cosf(toRadians(-30.0f)), sinf(toRadians(-30.0f)), 0.0f) * 0.8f;
		points[2] = vec3(cosf(toRadians(-150.0f)), sinf(toRadians(-150.0f)), 0.0f) * 0.8f;

		VBO::bind(&mVerts, VBO::Target::Array);
		VBO::BufferData(VBO::Target::Array, 3 * sizeof(vec3), &points[0], VBO::Usage::StaticDraw);

		VAO::bind(&mVoa);

		VBO::bind(&mVerts, VBO::Target::Array);
		VAO::enableAttribArray(0);
		VAO::attribPointerFloat(0, 3, false, 0, 0);

		VBO::unbind(VBO::Target::Array);
		VAO::unbind();
	});
}

Triangle::~Triangle()
{

}

void Triangle::draw(const Camera &camera)
{
	Transform modelviewTrans = camera.world() * Transform::Rotate(vec3(0.0f, 0.0f, 1.0f), toRadians(float(Timing::EngineMSecs()) * 0.1f));

	mat4x4 modelview(modelviewTrans.matrix());
	mat4x4 projection(camera.projection().matrix());

	Render::enqueue([this, projection, modelview]()
	{
		mShader.load();

		mShader.setView(modelview, projection);

		if (mDirty)
		{
			mShader.setColor(mColor);
			mDirty = false;
		}

		VAO::bind(&mVoa);
		VAO::drawArrays(VAO::Mode::Triangles, 0, 3);
		VAO::unbind();
	});
}

#ifdef ENGINE_DEVEOPMENT_SUPPORT

QWidget* Triangle::makePropertiesWidget()
{
	QColorEdit* widget = new QColorEdit(PixelFormat::PF_RGB_F32);
	
	widget->setColor(mColor);

	connect(widget, &QColorEdit::colorEdited, this, &Triangle::onColorEdited);
	connect(this, &Triangle::colorChanged, widget, &QColorEdit::setColor);

	return widget;
}

void Triangle::onColorEdited(Engine::RGBA_F32 color)
{
	mColor = RGB_F32(color);
	mDirty = true;
}

#endif // ENGINE_DEVEOPMENT_SUPPORT
