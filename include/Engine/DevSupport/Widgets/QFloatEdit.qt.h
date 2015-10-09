#ifndef _ENGINE_Q_FLOAT_EDIT_H_
#define _ENGINE_Q_FLOAT_EDIT_H_

#include "../../Config.h"

#ifdef ENGINE_DEVEOPMENT_SUPPORT

#include "QFloatValidator.h"

#include <QtWidgets/QLineEdit>

namespace Engine
{
	/**
	 * A line edit widget to accept floating point input.
	 */
	class ENGINE_DYNAMIC_CLASS QFloatEdit : public QLineEdit
	{
		Q_OBJECT
	public:

		/**
		 * @param parent
		 * 	Optional parent QWidget.
		 */
		QFloatEdit(QWidget *parent = nullptr);
		virtual ~QFloatEdit();

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
		 * @param n
		 * 	The new value.
		 *
		 * @param precision
		 * 	The number of places past the decimal point to display.  If negative, the precision
		 *	specified by setDisplayPrecision() will be used.
		 *
		 * @param format
		 * 	The format used to display the float.  See Qt documentation of
		 * 	QString::setNum() for details.
		 *
		 * @return
		 * 	True if the value is within the acceptable bounds of the input and
		 *  has been successfully set, false otherwise.
		 */
		bool setValue(float n, int precision = -1, char format = 'f');

		/**
		 * Sets the display precision (the number of digits passed the decimal point),
		 * for the widget.  By default, the precision is 2.  This precision can be overridden
		 * for a single call of setValue() if
		 *
		 * @param precision
		 *	A non-negative precision.
		 *
		 * @return
		 *	True if a valid precision is passed and set, false otherwise.
		 */
		bool setDisplayPrecision(int precision);

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

		/**
		 * @return
		 * 	The current value.
		 */
		float getValue() const;

		virtual QSize sizeHint() const;

	signals:
		/**
		 * Emitted when the value of the float is programmatically changed to an acceptable value.
		 *
		 * @param V
		 * 	The new float value.
		 */
		void valueChanged(float V);

		/**
		 * Emitted when the value of the float is changed by the user to an acceptable value.
		 *
		 * @param V
		 * 	The new float value.
		 */
		void valueEdited(float V);

	private:
		QFloatValidator *m_ValidFloat;
		float m_Value;
		int m_Precision;

		bool m_inSetValue;

	private slots:
		void onEditingFinished();
	};
}

#endif // ENGINE_DEVEOPMENT_SUPPORT

#endif // _ENGINE_Q_FLOAT_EDIT_H_
