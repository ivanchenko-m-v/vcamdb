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

#include "data_model_cam_selection.h"

#include "listview_cam_selection.h"
#include "delegate_line_edit.h"

namespace vcamdb
{

/// ############################################################################
///			class listview_cam_selection
/// ############################################################################

	/// ========================================================================
	///		CONSTRUCTORS/DESTRUCTOR
	/// ========================================================================

	/// ------------------------------------------------------------------------
    ///	listview_cam_selection( )
	/// ------------------------------------------------------------------------
    listview_cam_selection::listview_cam_selection( QWidget *parent ) :
		QTableView( parent )
	{
		this->initialize( );
	}

	/// ------------------------------------------------------------------------
    ///	~listview_cam_selection( )
	/// ------------------------------------------------------------------------
    listview_cam_selection::~listview_cam_selection( )
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
    const data_request* listview_cam_selection::current_request( )
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
    void listview_cam_selection::initialize( )
	{
		this->init_view( );

		this->init_connections( );
	}

	/// ------------------------------------------------------------------------
	///	init_view( )
	/// ------------------------------------------------------------------------
    void listview_cam_selection::init_view( )
    {
        this->setShowGrid( true );
		this->setGridStyle( Qt::DotLine );
        this->horizontalHeader( )->setVisible( true );
        this->horizontalHeader( )->setClickable( false );
        this->verticalHeader( )->setVisible( false );
        this->verticalHeader( )->setClickable( false );

        this->setModel(
                application::the_business_logic( ).model_cam_selection( )
					  );

        this->setSelectionMode( QAbstractItemView::SingleSelection );
		this->setSelectionBehavior( QAbstractItemView::SelectRows );

		this->setItemDelegate( new delegate_line_edit );
    }

	/// ------------------------------------------------------------------------
	///	init_connections( )
	/// ------------------------------------------------------------------------
    void listview_cam_selection::init_connections( )
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
    void listview_cam_selection::selected_item_changed( )
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
    void listview_cam_selection::resizeEvent( QResizeEvent *event )
    {
        QTableView::resizeEvent( event );

        if( !this->model( ) )
        {
            return;
        }
        if( !this->isVisible( ) )
        {
            return;
        }
        int n_cols = this->model( )->columnCount( );
        int n_width = this->viewport( )->width( );
        if( this->verticalScrollBar( ) )
        {
            n_width -= std::min( this->verticalScrollBar( )->width( ) - 1, 10 );
        }
        QFontMetrics fmt( this->font( ) );
        if( n_cols )
        {
            QRect rc = fmt.boundingRect( "00-00000000" );
            //+2 for bounding lines
            this->setColumnWidth( 0, rc.width( ) + 2 );
            n_width -= this->columnWidth( 0 ) + 1;
        }
        if( n_cols > 1 )
        {
            this->setColumnWidth( 1, n_width );
        }
     }

/// ############################################################################

}//namespace vcamdb
