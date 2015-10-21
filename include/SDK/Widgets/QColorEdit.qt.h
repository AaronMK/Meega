#ifndef _MEEGA_SDK_Q_COLOR_EDIT_H_
#define _MEEGA_SDK_Q_COLOR_EDIT_H_

#include "../Config.h"

#include "QFloatEdit.qt.h"

#include <Engine/Core/Color.h>

#include <QtWidgets/QWidget>

namespace MeegaSDK
{
	class MEEGA_SDK_CLASS QColorEdit : public QWidget
	{
		Q_OBJECT
	public:
		QColorEdit(Engine::PixelFormat format, QWidget* parent = nullptr);
		virtual ~QColorEdit();

		Engine::RGBA_F32 getColor() const;

		void setColor(const Engine::RGBA_F32& color);

	signals:
		void colorChanged(Engine::RGBA_F32 color);
		void colorEdited(Engine::RGBA_F32 color);

	private:
		Engine::PixelFormat mFormat;

		QFloatEdit* mRedGray;
		QFloatEdit* mGreen;
		QFloatEdit* mBlue;
		QFloatEdit* mAlpha;

		bool isGray() const;
	};
}

#endif // _MEEGA_SDK_Q_COLOR_EDIT_H_