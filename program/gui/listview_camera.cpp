/// $Header
/// ============================================================================
///		Author		: M. Ivanchenko
///		Date create	: 14-10-2014
///		Date update	: 14-10-2014
///		Comment		:
/// ============================================================================
#include <QAbstractItemView>
#include <QHeaderView>
#include <QItemDelegate>
#include <QScrollBar>

#include "application.h"
#include "business_logic.h"

#include "data_model_camera.h"

#include "listview_camera.h"
#include "delegate_line_edit.h"

namespace vcamdb
{

/// ############################################################################
///			class listview_camera
/// ############################################################################

	/// ========================================================================
	///		CONSTRUCTORS/DESTRUCTOR
	/// ========================================================================

	/// ------------------------------------------------------------------------
    ///	listview_camera( )
	/// ------------------------------------------------------------------------
    listview_camera::listview_camera( QWidget *parent ) :
		QTableView( parent )
	{
		this->initialize( );
	}

	/// ------------------------------------------------------------------------
    ///	~listview_camera( )
	/// ------------------------------------------------------------------------
    listview_camera::~listview_camera( )
	{
		this->setModel( 0 );
	}

	/// ========================================================================
	///		PROPERTIES
	/// ========================================================================
	/// -----------------------------------------------------------------------
	///	current_request( )
	/// -----------------------------------------------------------------------
/*
    const data_request* listview_camera::current_request( )
	{
		QModelIndex idx = this->selectionModel( )->currentIndex( );
		if( !idx.isValid( ) )
		{
			return 0;
		}

		return application::the_business_logic( ).
							model_request( )->request( idx.row( ) );
	}
*/
	/// ========================================================================
	///		OPERATORS
	/// ========================================================================

	/// ========================================================================
	///		FUNCTIONS
	/// ========================================================================
	/// ------------------------------------------------------------------------
	///	initialize( )
	/// ------------------------------------------------------------------------
    void listview_camera::initialize( )
	{
		this->init_view( );

		this->init_connections( );
	}

	/// ------------------------------------------------------------------------
	///	init_view( )
	/// ------------------------------------------------------------------------
    void listview_camera::init_view( )
    {
        this->setShowGrid( true );
		this->setGridStyle( Qt::DotLine );
		this->horizontalHeader( )->setVisible( true );
		this->horizontalHeader( )->setClickable( true );
		this->verticalHeader( )->setVisible( false );
		this->verticalHeader( )->setClickable( false );

        this->setModel(
                application::the_business_logic( ).model_camera( )
					  );

        this->setSelectionMode( QAbstractItemView::SingleSelection );
		this->setSelectionBehavior( QAbstractItemView::SelectRows );

		this->setItemDelegate( new delegate_line_edit );
    }

	/// ------------------------------------------------------------------------
	///	init_connections( )
	/// ------------------------------------------------------------------------
    void listview_camera::init_connections( )
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
    void listview_camera::selected_item_changed( )
    {
        /*
        const data_request *request = this->current_request( );
        if( request )
        {
            emit current_request_changed( request );
        }
        */
    }

	/// ========================================================================
	///		EVENTS
	/// ========================================================================
	/// ------------------------------------------------------------------------
	///	resizeEvent( QResizeEvent *event )
	/// ------------------------------------------------------------------------
    void listview_camera::resizeEvent( QResizeEvent *event )
    {
        QTableView::resizeEvent( event );

        if( !this->model( ) )
        {
            return;
        }
        /*
        int n_cols = this->model( )->columnCount( );
        int n_width = this->viewport( )->width( );
        if( this->verticalScrollBar( ) )
        {
            n_width -= std::min( this->verticalScrollBar( )->width( ) - 1, 10 );
        }
        QFontMetrics fmt( this->font( ) );
        if( n_cols )
        {
            QRect rc = fmt.boundingRect( "type_violation" );
            //+2 for bounding lines
            this->setColumnWidth( 0, rc.width( ) + 2 );
            n_width -= this->columnWidth( 0 ) + 1;
        }
        if( n_cols > 1 )
        {
            QRect rc = fmt.boundingRect( "4444--44--44" );
            //+2 for bounding lines
            this->setColumnWidth( 1, rc.width( ) + 2 );
            n_width -= this->columnWidth( 1 ) + 1;
        }
        //calc left columns width
        int n_col_width = n_width/( n_cols - 2 );

        for( int i = 2; i < n_cols; ++i )
        {
            this->setColumnWidth( i, n_col_width );
        }
        */
    }

/// ############################################################################

}//namespace vcamdb
