#ifndef _ENGINE_Q_COLOR_EDIT_H_
#define _ENGINE_Q_COLOR_EDIT_H_

#include <Engine/Config.h>

#ifdef ENGINE_DEVEOPMENT_SUPPORT

#include <Engine/Core/Color.h>
#include <Engine/DevSupport/Widgets/QFloatEdit.qt.h>

#include <QtWidgets/QWidget>

namespace Engine
{
	class ENGINE_DYNAMIC_CLASS QColorEdit : public QWidget
	{
		Q_OBJECT
	public:
		QColorEdit(PixelFormat format, QWidget* parent = nullptr);
		virtual ~QColorEdit();

		RGBA_F32 getColor() const;

		void setColor(const RGBA_F32& color);

	signals:
		void colorChanged(RGBA_F32 color);
		void colorEdited(RGBA_F32 color);

	private:
		PixelFormat mFormat;

		QFloatEdit* mRedGray;
		QFloatEdit* mGreen;
		QFloatEdit* mBlue;
		QFloatEdit* mAlpha;

		bool isGray() const;
	};
}


#endif // ENGINE_DEVEOPMENT_SUPPORT

#endif // _ENGINE_Q_COLOR_EDIT_H_