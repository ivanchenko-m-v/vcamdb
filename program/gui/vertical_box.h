/// $Header
/// ============================================================================
///		Author		: M. Ivanchenko
///		Date create	: 14-10-2014
///		Date update	: 14-10-2014
///		Comment		:
/// ============================================================================
#ifndef __VERTICAL_BOX_H__
#define __VERTICAL_BOX_H__

#include <QWidget>
#include <QLabel>

namespace espira
{

namespace widgets
{

/// ############################################################################
///			class vertical_box
/// ############################################################################
    class vertical_box : public QWidget
    {
    Q_OBJECT
    /// ========================================================================
    ///		CONSTRUCTORS/DESTRUCTOR
    /// ========================================================================
    private:
        /// --------------------------------------------------------------------
        vertical_box( const vertical_box &rhs );

	public:
        /// --------------------------------------------------------------------
        vertical_box(
                        QWidget *w = 0,
                        const QString &x_lbl = QString( ),
                        QWidget *parent = 0
                    );
        /// --------------------------------------------------------------------
        virtual ~vertical_box( );

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
        vertical_box& operator=( const vertical_box &rhs );

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

    };//class vertical_box
/// ############################################################################
/// ----------------------------------------------------------------------------

}//namespace widgets

}//namespace espira

#endif // __VERTICAL_BOX_H__