/// $Header
/// ============================================================================
///		Author		: M. Ivanchenko
///		Date create	: 06-01-2015
///		Date update	: 06-01-2015
///		Comment		:
/// ============================================================================
#include <QAbstractItemView>
#include <QHeaderView>
#include <QItemDelegate>
#include <QScrollBar>

#include "application.h"
#include "business_logic.h"

#include "data_model_violation_type.h"

#include "listview_violation_type.h"
#include "delegate_line_edit.h"

namespace vcamdb
{

/// ############################################################################
///			class listview_violation_type
/// ############################################################################

	/// ========================================================================
	///		CONSTRUCTORS/DESTRUCTOR
	/// ========================================================================

	/// ------------------------------------------------------------------------
    ///	listview_violation_type( )
	/// ------------------------------------------------------------------------
    listview_violation_type::listview_violation_type( QWidget *parent ) :
		QTableView( parent )
	{
		this->initialize( );
	}

	/// ------------------------------------------------------------------------
    ///	~listview_violation_type( )
	/// ------------------------------------------------------------------------
    listview_violation_type::~listview_violation_type( )
	{
		this->setModel( 0 );
	}

	/// ========================================================================
	///		PROPERTIES
	/// ========================================================================
	/// ========================================================================
	///		OPERATORS
	/// ========================================================================

	/// ========================================================================
	///		FUNCTIONS
	/// ========================================================================
	/// ------------------------------------------------------------------------
	///	initialize( )
	/// ------------------------------------------------------------------------
    void listview_violation_type::initialize( )
	{
		this->init_view( );

		this->init_connections( );
	}

	/// ------------------------------------------------------------------------
	///	init_view( )
	/// ------------------------------------------------------------------------
    void listview_violation_type::init_view( )
    {
        this->setShowGrid( true );
		this->setGridStyle( Qt::DotLine );
		this->horizontalHeader( )->setVisible( true );
		this->horizontalHeader( )->setClickable( true );
		this->verticalHeader( )->setVisible( false );
		this->verticalHeader( )->setClickable( false );

        this->setModel(
                application::the_business_logic( ).model_violation_type( )
					  );

        this->setSelectionMode( QAbstractItemView::SingleSelection );
		this->setSelectionBehavior( QAbstractItemView::SelectRows );

		this->setItemDelegate( new delegate_line_edit );
    }

	/// ------------------------------------------------------------------------
	///	init_connections( )
	/// ------------------------------------------------------------------------
    void listview_violation_type::init_connections( )
    {
        /*
        if( this->selectionModel( ) )
        {
            this->connect(
                       this->selectionModel( ), SIGNAL(selectionChanged(QItemSelection,QItemSelection)),
                       this, SLOT( selected_item_changed( ) )
                         );
        }
        */
    }

	/// ========================================================================
	///		SLOTS
	/// ========================================================================
	/// ------------------------------------------------------------------------
	///	selected_item_changed( )
	/// ------------------------------------------------------------------------
    void listview_violation_type::selected_item_changed( )
    {
    }

	/// ========================================================================
	///		EVENTS
	/// ========================================================================
	/// ------------------------------------------------------------------------
	///	resizeEvent( QResizeEvent *event )
	/// ------------------------------------------------------------------------
    void listview_violation_type::resizeEvent( QResizeEvent *event )
    {
        QTableView::resizeEvent( event );

        if( !this->model( ) )
        {
            return;
        }
        int n_cols = this->model( )->columnCount( );
        if( n_cols == 0 )
        {
            return;
        }
        int n_width = this->viewport( )->width( );
        if( this->verticalScrollBar( ) )
        {
            n_width -= std::min( this->verticalScrollBar( )->width( ) - 1, 10 );
        }
        int n_col_width = n_width / n_cols;
        for( int i = 0; i < n_cols - 1; ++i )
        {
            this->setColumnWidth( i, n_col_width );
        }
        //set last column width
        this->setColumnWidth( n_cols - 1, n_width - ( n_col_width*(n_cols - 1) ) );
    }

/// ############################################################################

}//namespace vcamdb
