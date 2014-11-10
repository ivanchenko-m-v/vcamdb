/// $Header
/// ============================================================================
///		Author		: M. Ivanchenko
///		Date create	: 03-11-2014
///		Date update	: 10-11-2014
///		Comment		:
/// ============================================================================
#include "combobox_camera_search.h"

#include "application.h"
#include "business_logic.h"

#include "data_adapter_camera.h"

namespace vcamdb
{

/// ############################################################################
///			class combobox_camera_search
/// ############################################################################

    /// ========================================================================
    ///		CONSTRUCTORS/DESTRUCTOR
    /// ========================================================================

    /// ------------------------------------------------------------------------
    ///	combobox_camera_search( )
    /// ------------------------------------------------------------------------
    combobox_camera_search::combobox_camera_search(QWidget *parent) :
        QComboBox(parent),
        _coll_cameras(0)
    {
        this->initialize( );
    }
    /// ------------------------------------------------------------------------
    ///	~combobox_camera_search( )
    /// ------------------------------------------------------------------------
    combobox_camera_search::~combobox_camera_search( )
    {
        this->clear_data( );
    }
    /// ========================================================================
    ///		PROPERTIES
    /// ========================================================================
    /// ------------------------------------------------------------------------
    ///	camera( ) get
    /// ------------------------------------------------------------------------
    const data_camera* combobox_camera_search::camera( ) const
    {
        return 0;
    }
    /// ------------------------------------------------------------------------
    ///	camera_address( int index ) get
    /// ------------------------------------------------------------------------
    QString combobox_camera_search::camera_address( int index ) const
    {
        int n_count = this->count( );
        if( index < 0 || index >= this->count( ) )
        {
            return QString( "-" );
        }
        QVariant val = this->itemData( index );
        if( !val.isValid( ) )
        {
            return QString( "-" );
        }
        return val.toString( );
    }
    /// ------------------------------------------------------------------------
    ///	camera( ) set
    /// ------------------------------------------------------------------------
    void combobox_camera_search::camera( const data_camera *cam )
    {

    }

    /// ========================================================================
    ///		FUNCTIONS
    /// ========================================================================

    /// ------------------------------------------------------------------------
	///	initialize( )
    /// ------------------------------------------------------------------------
    void combobox_camera_search::initialize( )
    {
        this->setEditable( true );
        //this->setSizeAdjustPolicy( AdjustToContents );
    }

    /// ------------------------------------------------------------------------
    ///	clear_data( )
    /// ------------------------------------------------------------------------
    void combobox_camera_search::clear_data( )
    {
        //empty text list
        this->clear( );
        //remove previous data
        if( this->_coll_cameras != 0 )
        {
            delete _coll_cameras;
            this->_coll_cameras = 0;
        }
    }

    /// ------------------------------------------------------------------------
    ///	refresh( )
    /// ------------------------------------------------------------------------
    void combobox_camera_search::refresh( const QString &text )
    {
        this->clear_data( );

        business_logic &logic = application::the_business_logic( );
        this->_coll_cameras = logic.camera_select( text );
        if( !_coll_cameras )
        {
            return;
        }

        data_camera_collection::iterator it = this->_coll_cameras->begin( );
        for( ; it < this->_coll_cameras->end( ); ++it )
        {
            data_camera *cam = *it;

            if( !cam ) continue;

            this->addItem( cam->cam_name( ), cam->cam_address( ) );
        }
    }

    /// ========================================================================
    ///		EVENTS
    /// ========================================================================

    /// ------------------------------------------------------------------------
    ///	keyPressEvent(QKeyEvent *e)
    /// ------------------------------------------------------------------------
    void combobox_camera_search::keyPressEvent( QKeyEvent *e )
    {
        int n_key = e->key( );
        if(
            n_key != Qt::Key_Enter &&
            n_key != Qt::Key_Return
          )
        {
            QComboBox::keyPressEvent( e );

            return;
        }

        QString text( this->currentText( ).simplified( ).remove( ' ' ) );

        const int MIN_INPUT_LETTERS = 5;
        if( text.length( ) < MIN_INPUT_LETTERS )
        {
            QComboBox::keyPressEvent( e );

            return;
        }
        this->refresh( text );

        QComboBox::keyPressEvent( e );
    }


}//namespace vcamdb
