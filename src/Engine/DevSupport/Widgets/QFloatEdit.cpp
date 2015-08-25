#include <Engine/DevSupport/Widgets/QFloatEdit.qt.h>

#ifdef ENGINE_DEVEOPMENT_SUPPORT

#include <limits>

using namespace std;

namespace Engine
{
	QFloatEdit::QFloatEdit(QWidget *parent)
	: QLineEdit(parent),
	  m_ValidFloat(new QFloatValidator(this)),
	  m_Precision(2),
	  m_inSetValue(false)
	{
		setText("0.0");
		setValidator(m_ValidFloat);

		connect(this, &QFloatEdit::editingFinished, this, &QFloatEdit::onEditingFinished);
	}

	QFloatEdit::~QFloatEdit()
	{
	}

	void QFloatEdit::setMin(float Min)
	{
		m_ValidFloat->setMin(Min);
	}

	void QFloatEdit::setMax(float Max)
	{
		m_ValidFloat->setMax(Max);
	}

	void QFloatEdit::setBounds(float Min, float Max)
	{
		m_ValidFloat->setBounds(Min, Max);

		if (Min > m_Value)
			setValue(Min);

		if (Max < m_Value)
			setValue(Max);
	}

	bool QFloatEdit::setValue(float n, int precision, char format)
	{
		if (m_ValidFloat->getMin() <= n && m_ValidFloat->getMax() >= n)
		{
			m_inSetValue = true;
			if (precision < 0)
				precision = m_Precision;

			setText(QString().setNum(n, format, precision));

			m_Value = n;
			emit valueChanged(n);

			m_inSetValue = false;
			return true;
		}

		return false;
	}

	bool QFloatEdit::setDisplayPrecision(int precision)
	{
		if (precision >= 0)
		{
			m_Precision = precision;
			return true;
		}
		else
		{
			return false;
		}
	}

	float QFloatEdit::getMin() const
	{
		return m_ValidFloat->getMin();
	}

	float QFloatEdit::getMax() const
	{
		return m_ValidFloat->getMax();
	}

	float QFloatEdit::getValue() const
	{
		return m_Value;
	}

	void QFloatEdit::onEditingFinished()
	{
		if (false == m_inSetValue)
		{
			bool cvrtSuccess;
			m_Value = this->text().toFloat(&cvrtSuccess);
			Q_ASSERT(cvrtSuccess);

			emit valueEdited(m_Value);
		}
	}

	QSize QFloatEdit::sizeHint() const
	{
		return QSize((6 + m_Precision)*fontMetrics().width("0"), QLineEdit::sizeHint().height());
	}
}

#endif // ENGINE_DEVEOPMENT_SUPPORT