/// $Header
/// ============================================================================
///		Author		: M. Ivanchenko
///		Date create	: 18-02-2015
///		Date update	: 18-02-2015
///		Comment		:
/// ============================================================================
#include "combobox_contractor.h"

#include "application.h"
#include "business_logic.h"

namespace vcamdb
{

/// ############################################################################
///			class combobox_contractor
/// ############################################################################

    /// ========================================================================
    ///		CONSTRUCTORS/DESTRUCTOR
    /// ========================================================================

    /// ------------------------------------------------------------------------
    ///	combobox_contractor( )
    /// ------------------------------------------------------------------------
    combobox_contractor::combobox_contractor(QWidget *parent) :
        QComboBox(parent)
    {
        this->initialize( );
    }
    /// ------------------------------------------------------------------------
    ///	~combobox_contractor( )
    /// ------------------------------------------------------------------------
    combobox_contractor::~combobox_contractor( )
    {
    }
    /// ========================================================================
    ///		PROPERTIES
    /// ========================================================================
    /// ------------------------------------------------------------------------
    ///	contractor( ) get
    /// ------------------------------------------------------------------------
    const data_contractor* combobox_contractor::contractor( )
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
        //return this->_objects.find( val.toInt( ) );
        return 0;
    }

    /// ------------------------------------------------------------------------
    ///	contractor( ) set
    /// ------------------------------------------------------------------------
    void combobox_contractor::contractor( const data_contractor *data )
    {

    }

    /// ========================================================================
    ///		FUNCTIONS
    /// ========================================================================

    /// ------------------------------------------------------------------------
	///	initialize( )
    /// ------------------------------------------------------------------------
    void combobox_contractor::initialize( )
    {
        this->setEditable( true );
        //this->setSizeAdjustPolicy( AdjustToContents );
    }

    /// ------------------------------------------------------------------------
    ///	clear_data( )
    /// ------------------------------------------------------------------------
    void combobox_contractor::clear_data( )
    {
        //empty text list
        this->clear( );
        //remove previous data
        this->_objects.free( );
    }


    /// ------------------------------------------------------------------------
    ///	refresh( )
    /// ------------------------------------------------------------------------
    void combobox_contractor::refresh(const QString &violation_type, const QString &text )
    {
        this->clear( );
/*
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
        */
    }

    /// ========================================================================
    ///		EVENTS
    /// ========================================================================

    /// ------------------------------------------------------------------------
    ///	keyPressEvent(QKeyEvent *e)
    /// ------------------------------------------------------------------------
    void combobox_contractor::keyPressEvent( QKeyEvent *e )
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
        //emit violation_type_request( text );

        QComboBox::keyPressEvent( e );
    }


}//namespace vcamdb
