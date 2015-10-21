#ifndef _MEEGA_SDK_Q_FLOAT_VALIDATOR_H_
#define _MEEGA_SDK_Q_FLOAT_VALIDATOR_H_

#include "../Config.h"

#include <QtGui/QValidator>

namespace MeegaSDK
{
	/**
	 * Validator for floating point textual input.
	 */
	class MEEGA_SDK_CLASS QFloatValidator : public QValidator
	{
	public:
		QFloatValidator(QObject *parent = 0);

		/**
		 * Sets the minimum acceptable value.  If this is greater than the current
		 * value, the value is adjusted and the valueChanged() signal is emitted.
		 *
		 * @param Min
		 * 	The minimum value to accept.
		 */
		void setMin(float Min);

		/**
		 * Sets the maximum acceptable value.  If this is less than the current
		 * value, the value is adjusted and the valueChanged() signal is emitted.
		 *
		 * @param Max
		 * 	The maximum value to accept.
		 */
		void setMax(float Max);

		/**
		 * Set the acceptable input range.  If the current value is outside of this
		 * range, the value is adjusted and the valueChanged() signal is emitted.
		 *
		 * @param Min
		 * 	The minimum value to accept.
		 *
		 * @param Max
		 * 	The maximum value to accept.
		 */
		void setBounds(float Min, float Max);

		/**
		 * @return
		 * 	The minimum acceptable value.
		 */
		float getMin() const;

		/**
		 * @return
		 * 	The maximum acceptable value.
		 */
		float getMax() const;

		virtual State validate(QString &input, int &pos) const override;

	private:
		float Minimum;
		float Maximum;
	};
}

#endif // _MEEGA_SDK_Q_FLOAT_VALIDATOR_H_