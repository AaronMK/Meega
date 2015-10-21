#include <SDK/Widgets/QColorEdit.qt.h>

#include <QtWidgets/QBoxLayout>
#include <QtCore/QString>

#include <QtGui/QPalette>
#include <QtGui/QBrush>

#include <functional>

namespace MeegaSDK
{
	static char* styleRed =
		"QLineEdit {\n"
		"  border: 2px solid red;\n"
		"  border-radius: 5px;"
		"  padding: 1px;\n}";

	static char* styleGreen =
		"QLineEdit {\n"
		"  border: 2px solid green;\n"
		"  border-radius: 5px;"
		"  padding: 1px;\n}";

	static char* styleBlue =
		"QLineEdit {\n"
		"  border: 2px solid blue;\n"
		"  border-radius: 5px;"
		"  padding: 1px;\n}";

	QColorEdit::QColorEdit(Engine::PixelFormat format, QWidget* parent)
		: QWidget(parent), mFormat(format)
	{
		std::function<void(float)> changeHandler = [this](float param)
		{
			emit colorChanged(getColor());
		};

		std::function<void()> editHandler = [this]()
		{
			emit colorEdited(getColor());
		};

		mRedGray = nullptr;
		mGreen = nullptr;
		mBlue = nullptr;
		mAlpha = nullptr;

		QHBoxLayout* layout = new QHBoxLayout();

		mRedGray = new QFloatEdit();

		layout->addWidget(mRedGray);

		connect(mRedGray, &QFloatEdit::valueChanged, this, changeHandler);
		connect(mRedGray, &QFloatEdit::editingFinished, this, editHandler);

		switch (mFormat)
		{
		case Engine::PixelFormat::PF_RGBA_F32:
		case Engine::PixelFormat::PF_RGBA_UI8:
			mAlpha = new QFloatEdit();
			mAlpha->setBounds(0.0f, 1.0f);

			connect(mAlpha, &QFloatEdit::valueChanged, this, changeHandler);
			connect(mAlpha, &QFloatEdit::editingFinished, this, editHandler);

		case Engine::PixelFormat::PF_RGB_F32:
		case Engine::PixelFormat::PF_RGB_UI8:
			mGreen = new QFloatEdit();
			mBlue = new QFloatEdit();

			mGreen->setMin(0.0f);
			mBlue->setMin(0.0f);

			connect(mBlue, &QFloatEdit::valueChanged, this, changeHandler);
			connect(mBlue, &QFloatEdit::editingFinished, this, editHandler);

			connect(mGreen, &QFloatEdit::valueChanged, this, changeHandler);
			connect(mGreen, &QFloatEdit::editingFinished, this, editHandler);

			mRedGray->setStyleSheet(styleRed);
			mGreen->setStyleSheet(styleGreen);
			mBlue->setStyleSheet(styleBlue);
		}

		if (mGreen && mBlue)
		{
			layout->addWidget(mGreen);
			layout->addWidget(mBlue);
		}

		if (mAlpha)
			layout->addWidget(mAlpha);


		setLayout(layout);
	}

	QColorEdit::~QColorEdit()
	{

	}

	Engine::RGBA_F32 QColorEdit::getColor() const
	{
		Engine::RGBA_F32 ret;

		ret.R = mRedGray->getValue();

		if ( isGray() )
		{
			ret.G = ret.R;
			ret.B = ret.R;
		}
		else
		{
			ret.G = mGreen->getValue();
			ret.B = mBlue->getValue();
		}

		ret.A = (mAlpha) ? mAlpha->getValue() : 0.0f;

		return ret;
	}

	void QColorEdit::setColor(const Engine::RGBA_F32& color)
	{
		blockSignals(true);

		mRedGray->setValue(color.R);

		if ( false == isGray() )
		{
			mGreen->setValue(color.G);
			mBlue->setValue(color.B);
		}

		if (mAlpha)
			mAlpha->setValue(color.A);

		blockSignals(false);

		emit colorChanged(getColor());
	}

	bool QColorEdit::isGray() const
	{
		return ( (Engine::PixelFormat::PF_GRAY_ALPHA_F32 == mFormat) || (Engine::PixelFormat::PF_GRAY_ALPHA_F32 == mFormat) ||
		         (Engine::PixelFormat::PF_GRAY_ALPHA_UI8 == mFormat) || (Engine::PixelFormat::PF_GRAY_UI8 == mFormat) );
	}
}