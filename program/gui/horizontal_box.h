/// $Header
/// ============================================================================
///		Author		: M. Ivanchenko
///		Date create	: 14-10-2014
///		Date update	: 14-10-2014
///		Comment		:
/// ============================================================================
#ifndef __HORIZONTAL_BOX_H__
#define __HORIZONTAL_BOX_H__

#include <QWidget>
#include <QLabel>

namespace espira
{

namespace widgets
{

/// ############################################################################
///			class horizontal_box
/// ############################################################################
    class horizontal_box : public QWidget
    {
    Q_OBJECT
    /// ========================================================================
    ///		CONSTRUCTORS/DESTRUCTOR
    /// ========================================================================
    private:
        /// --------------------------------------------------------------------
        horizontal_box( const horizontal_box &rhs );

	public:
        /// --------------------------------------------------------------------
        horizontal_box(
                        QWidget *w = 0,
                        const QString &x_lbl = QString( ),
                        QWidget *parent = 0
                    );
        /// --------------------------------------------------------------------
        virtual ~horizontal_box( );

    /// ========================================================================
    ///		FUNCTIONS
    /// ========================================================================
    private:
        /// --------------------------------------------------------------------
        void initialize( );
        void init_layout( );

    /// ========================================================================
    ///		PROPERTIES
    /// ========================================================================
    private:

	public:

    /// ========================================================================
    ///		OPERATORS
    /// ========================================================================
    private:
        /// --------------------------------------------------------------------
        horizontal_box& operator=( const horizontal_box &rhs );

    /// ========================================================================
    ///		EVENTS
    /// ========================================================================
	protected:

    /// ========================================================================
    ///		SLOTS
    /// ========================================================================
    public slots:
        /// --------------------------------------------------------------------

    /// ========================================================================
    ///			FIELDS
    /// ========================================================================
    private:
        const int _MAX_STRETCH_ = 1000;
        const int _MIN_STRETCH_ = 1;

        QWidget *_widget;
        QString _x_lbl;

    };//class horizontal_box
/// ############################################################################
/// ----------------------------------------------------------------------------

}//namespace widgets

}//namespace espira

#endif // __HORIZONTAL_BOX_H__
