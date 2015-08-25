#include <Engine/DevSupport/Widgets/QFloatValidator.h>

#ifdef ENGINE_DEVEOPMENT_SUPPORT

#include <limits>

using namespace std;

namespace Engine
{
	QFloatValidator::QFloatValidator(QObject *parent)
		: QValidator(parent)
	{
		setBounds(-numeric_limits<float>::max(), numeric_limits<float>::max());
	}

	void QFloatValidator::setMin(float Min)
	{
		Q_ASSERT(Min <= Maximum);
		Minimum = Min;
	}

	void QFloatValidator::setMax(float Max)
	{
		Q_ASSERT(Max >= Maximum);
		Maximum = Max;
	}

	void QFloatValidator::setBounds(float Min, float Max)
	{
		Q_ASSERT(Min <= Max);
		Minimum = Min;
		Maximum = Max;
	}

	float QFloatValidator::getMin() const
	{
		return Minimum;
	}

	float QFloatValidator::getMax() const
	{
		return Maximum;
	}

	QValidator::State QFloatValidator::validate(QString &input, int &pos) const
	{
		float tVal;
		bool tBool;

		if ("" == input || ("-" == input && Minimum < 0))
			return Intermediate;

		tVal = input.toFloat(&tBool);

		if (false == tBool || tVal < Minimum || tVal > Maximum)
			return Invalid;

		return Acceptable;
	}
}

#endif // ENGINE_DEVEOPMENT_SUPPORT