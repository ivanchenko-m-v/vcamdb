/// $Header
/// ============================================================================
///		Author		: M. Ivanchenko
///		Date create	: 14-10-2014
///		Date update	: 19-11-2014
///		Comment		:
/// ============================================================================
#include <QAbstractItemView>
#include <QHeaderView>
#include <QItemDelegate>
#include <QScrollBar>

#include "application.h"
#include "business_logic.h"

#include "data_model_violation.h"

#include "listview_volation.h"
#include "delegate_line_edit.h"

#include "data_adapter_violation.h"

namespace vcamdb
{

/// ############################################################################
///			class listview_violation
/// ############################################################################

	/// ========================================================================
	///		CONSTRUCTORS/DESTRUCTOR
	/// ========================================================================

	/// ------------------------------------------------------------------------
    ///	listview_violation( )
	/// ------------------------------------------------------------------------
    listview_violation::listview_violation( QWidget *parent ) :
		QTableView( parent )
	{
		this->initialize( );
	}

	/// ------------------------------------------------------------------------
    ///	~listview_violation( )
	/// ------------------------------------------------------------------------
    listview_violation::~listview_violation( )
	{
		this->setModel( 0 );
	}

	/// ========================================================================
	///		PROPERTIES
	/// ========================================================================
	/// -----------------------------------------------------------------------
	///	current_violation( )
	/// -----------------------------------------------------------------------
    const data_violation* listview_violation::current_violation( )
	{
		QModelIndex idx = this->selectionModel( )->currentIndex( );
		if( !idx.isValid( ) )
		{
			return 0;
		}

		return application::the_business_logic( ).
							model_violation( )->violation( idx.row( ) );
	}

	/// ========================================================================
	///		OPERATORS
	/// ========================================================================

	/// ========================================================================
	///		FUNCTIONS
	/// ========================================================================
	/// ------------------------------------------------------------------------
	///	initialize( )
	/// ------------------------------------------------------------------------
    void listview_violation::initialize( )
	{
		this->init_view( );

		this->init_connections( );
	}

	/// ------------------------------------------------------------------------
	///	init_view( )
	/// ------------------------------------------------------------------------
    void listview_violation::init_view( )
    {
        this->setShowGrid( true );
		this->setGridStyle( Qt::DotLine );
		this->horizontalHeader( )->setVisible( true );
		this->horizontalHeader( )->setClickable( true );
		this->verticalHeader( )->setVisible( false );
		this->verticalHeader( )->setClickable( false );

        this->setModel(
                application::the_business_logic( ).model_violation( )
					  );

        this->setSelectionMode( QAbstractItemView::SingleSelection );
		this->setSelectionBehavior( QAbstractItemView::SelectRows );

		this->setItemDelegate( new delegate_line_edit );
    }

	/// ------------------------------------------------------------------------
	///	init_connections( )
	/// ------------------------------------------------------------------------
    void listview_violation::init_connections( )
    {
        if( this->selectionModel( ) )
        {
            this->connect(
                   this->selectionModel( ),
                   SIGNAL( selectionChanged( QItemSelection, QItemSelection ) ),
                   this,
                   SLOT( selected_item_changed( ) )
                         );
        }
    }

	/// ========================================================================
	///		SLOTS
	/// ========================================================================
	/// ------------------------------------------------------------------------
	///	selected_item_changed( )
	/// ------------------------------------------------------------------------
    void listview_violation::selected_item_changed( )
    {
        const data_violation *violation = this->current_violation( );
        if( violation )
        {
            emit current_violation_changed( violation );
        }
    }

    void listview_violation::select_new_violation( )
    {
        if( this->model( ) && this->selectionModel( ) )
        {
            this->selectionModel( )->select( this->model( )->index( 0, 0 ), QItemSelectionModel::Select );
        }
    }

    void listview_violation::select_updated_violation( const data_violation &v )
    {
        if( !this->model( ) ) return;
        if( !this->selectionModel( ) ) return;

        const business_logic &logic = application::the_business_logic( );
        int row_index = logic.model_violation( )->row_index( v.id_violation( ) );
        this->selectionModel( )->select( this->model( )->index( row_index, 0 ), QItemSelectionModel::Select );
    }

	/// ========================================================================
	///		EVENTS
	/// ========================================================================
	/// ------------------------------------------------------------------------
	///	resizeEvent( QResizeEvent *event )
	/// ------------------------------------------------------------------------
    void listview_violation::resizeEvent( QResizeEvent *event )
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
