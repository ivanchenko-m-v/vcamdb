/// $Header
/// ============================================================================
///		Author		: M. Ivanchenko
///		Date create	: 09-11-2014
///		Date update	: 09-11-2014
///		Comment		:
/// ============================================================================
#include "combobox_violation_object.h"

#include "application.h"
#include "business_logic.h"

#include "data_violation_object.h"

namespace vcamdb
{

/// ############################################################################
///			class combobox_violation_object
/// ############################################################################

    /// ========================================================================
    ///		CONSTRUCTORS/DESTRUCTOR
    /// ========================================================================

    /// ------------------------------------------------------------------------
    ///	combobox_violation_object( )
    /// ------------------------------------------------------------------------
    combobox_violation_object::combobox_violation_object(QWidget *parent) :
        QComboBox(parent)
    {
        this->initialize( );
    }
    /// ------------------------------------------------------------------------
    ///	~combobox_violation_object( )
    /// ------------------------------------------------------------------------
    combobox_violation_object::~combobox_violation_object( )
    {
    }
    /// ========================================================================
    ///		PROPERTIES
    /// ========================================================================
    /// ------------------------------------------------------------------------
    ///	camera( ) get
    /// ------------------------------------------------------------------------
    const data_violation_object* combobox_violation_object::violation_object( ) const
    {
        return 0;
    }
    /// ------------------------------------------------------------------------
    ///	camera( ) set
    /// ------------------------------------------------------------------------
    void combobox_violation_object::violation_object( const data_violation_object *cam )
    {

    }
    /// ------------------------------------------------------------------------
    ///	camera_address( int index ) get
    /// ------------------------------------------------------------------------
    const QString& combobox_violation_object::object_id( int index ) const
    {
        if( index < 0 || index >= this->count( ) )
        {
            return QString( "-" );
        }
        return this->itemData( index ).toString( );
    }

    /// ========================================================================
    ///		FUNCTIONS
    /// ========================================================================

    /// ------------------------------------------------------------------------
	///	initialize( )
    /// ------------------------------------------------------------------------
    void combobox_violation_object::initialize( )
    {
        this->setEditable( true );
        //this->setSizeAdjustPolicy( AdjustToContents );
    }

    /// ------------------------------------------------------------------------
    ///	refresh( )
    /// ------------------------------------------------------------------------
    void combobox_violation_object::refresh( const QString &text )
    {
        this->clear( );

        business_logic &logic = application::the_business_logic( );
        /*
        this->_coll_cameras = logic.camera_select( text );
        if( !_coll_cameras )
        {
            return;
        }

        data_violation_object_collection::iterator it = this->_coll_cameras->begin( );
        for( ; it < this->_coll_cameras->end( ); ++it )
        {
            data_violation_object *cam = *it;

            if( !cam ) continue;

            this->addItem( cam->cam_name( ), cam->cam_address( ) );
        }
        */
    }

    /// ========================================================================
    ///		EVENTS
    /// ========================================================================

    /// ------------------------------------------------------------------------
    ///	keyPressEvent(QKeyEvent *e)
    /// ------------------------------------------------------------------------
    void combobox_violation_object::keyPressEvent( QKeyEvent *e )
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
