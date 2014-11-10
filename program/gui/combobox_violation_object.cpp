/// $Header
/// ============================================================================
///		Author		: M. Ivanchenko
///		Date create	: 09-11-2014
///		Date update	: 10-11-2014
///		Comment		:
/// ============================================================================
#include "combobox_violation_object.h"

#include "application.h"
#include "business_logic.h"

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
    const data_violation_object* combobox_violation_object::violation_object( )
    {
        int index = this->currentIndex( );
        if( index < 0 || index >= this->count( ) )
        {
            return 0;
        }
        QVariant val = this->itemData( index );
        if( !val.isValid( ) )
        {
            return 0;
        }
        return this->_objects.find( val.toInt( ) );
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
    int combobox_violation_object::object_id( int index ) const
    {
        if( index < 0 || index >= this->count( ) )
        {
            return -1;
        }
        QVariant val = this->itemData( index );
        if( !val.isValid( ) )
        {
            return -1;
        }
        return val.toInt( );
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
    ///	clear_data( )
    /// ------------------------------------------------------------------------
    void combobox_violation_object::clear_data( )
    {
        //empty text list
        this->clear( );
        //remove previous data
        this->_objects.free( );
    }


    /// ------------------------------------------------------------------------
    ///	refresh( )
    /// ------------------------------------------------------------------------
    void combobox_violation_object::refresh(const QString &violation_type, const QString &text )
    {
        this->clear( );

        business_logic &logic = application::the_business_logic( );
        data_violation_object_collection *p_coll = logic.violation_object_select( violation_type, text );
        if( !p_coll )
        {
            return;
        }

        data_violation_object_collection::iterator it = p_coll->begin( );
        for( ; it < p_coll->end( ); ++it )
        {
            data_violation_object *vobj = *it;

            if( !vobj ) continue;

            this->addItem( vobj->object_name( ), vobj->id_object( ) );
            this->_objects.append( vobj );
        }

        p_coll->free_data_pointer( );
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

        //Посылаем сигнал для определения типа
        //фиксируемого нарушения
        emit violation_type_request( text );

        QComboBox::keyPressEvent( e );
    }


}//namespace vcamdb
