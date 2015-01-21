/// $Header
/// ============================================================================
///		Author		: M. Ivanchenko
///		Date create	: 06-01-2015
///		Date update	: 06-01-2015
///		Comment		:
/// ============================================================================
#ifndef __LISTVIEW_VIOLATION_TYPE_H__
#define __LISTVIEW_VIOLATION_TYPE_H__

#include <QTableView>
#include <QWidget>

namespace vcamdb
{

/// ############################################################################
///			class listview_violation_type
/// ############################################################################
    class listview_violation_type : public QTableView
	{
	Q_OBJECT
	/// ========================================================================
	///		CONSTRUCTORS/DESTRUCTOR
	/// ========================================================================
	private:
	/// ------------------------------------------------------------------------
        listview_violation_type( const listview_violation_type &rhs );

	public:
	/// ------------------------------------------------------------------------
        explicit listview_violation_type( QWidget *parent = 0 );
	/// ------------------------------------------------------------------------
        ~listview_violation_type( );

	/// ========================================================================
	///		PROPERTIES
	/// ========================================================================
	public:
	/// ------------------------------------------------------------------------

	/// ========================================================================
	///		FUNCTIONS
	/// ========================================================================
    private:
	/// ------------------------------------------------------------------------
		void initialize( );
	/// ------------------------------------------------------------------------
        void init_view( );
	/// ------------------------------------------------------------------------
		void init_connections( );

	/// ========================================================================
	///		OPERATORS
	/// ========================================================================
	private:
	/// ------------------------------------------------------------------------
        listview_violation_type& operator=( const listview_violation_type &rhs );

	/// ========================================================================
	///		EVENTS
	/// ========================================================================
	protected:
	/// ------------------------------------------------------------------------
        virtual void resizeEvent( QResizeEvent *event );

	/// ========================================================================
	///		SIGNALS
	/// ========================================================================
	signals:
	/// ------------------------------------------------------------------------

	/// ========================================================================
	///		SLOTS
	/// ========================================================================
    private slots:
	/// ------------------------------------------------------------------------
        void selected_item_changed( );

	/// ========================================================================
	///			FIELDS
	/// ========================================================================
	private:

    };//class listview_violation_type
/// ############################################################################
/// ----------------------------------------------------------------------------

}//namespace vcamdb

#endif // __LISTVIEW_VIOLATION_TYPE_H__