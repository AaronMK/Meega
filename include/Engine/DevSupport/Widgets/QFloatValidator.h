#ifndef _ENGINE_Q_FLOAT_VALIDATOR_H_
#define _ENGINE_Q_FLOAT_VALIDATOR_H_

#include <Engine/Config.h>

#ifdef ENGINE_DEVEOPMENT_SUPPORT

#include <QtGui/QValidator>

namespace Engine
{

	/**
	* Validator for floating point textual input.
	*/
	class ENGINE_DYNAMIC_CLASS QFloatValidator : public QValidator
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

		virtual State validate(QString &input, int &pos) const;

	private:
		float Minimum;
		float Maximum;
	};
}

#endif // ENGINE_DEVEOPMENT_SUPPORT

#endif // _ENGINE_Q_FLOAT_VALIDATOR_H_